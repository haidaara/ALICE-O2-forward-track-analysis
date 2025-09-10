
// ==========================================================================================================================================
//==========================================================================================================================================
// ==========================================================================================================================================
//==========================================================================================================================================


//  Helper-function definitions for efficiency/purity analysis

// ==========================================================================================================================================
//==========================================================================================================================================
// ==========================================================================================================================================
//==========================================================================================================================================
#include "O2fwdtrack.h"
#include <TH2.h>
#include <TH1.h>
#include <TGraphAsymmErrors.h>
#include <TMarker.h>
#include <TLatex.h>
#include <TMath.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLegend.h>
#include <unordered_map>

#include <TEfficiency.h>
#include <TFile.h>
#include <TSystem.h>
#include <TDirectory.h>
#include <TROOT.h>
#include <cmath>
#include <limits>



double O2fwdtrack::GetVarValue(const std::string& varname)
{
    if (varname == "pt_MCH")      return 1.0 / std::abs(fSigned1Pt);
    if (varname == "eta")         return std::asinh(fTgl);
    if (varname == "phi")         return fPhi;
    if (varname == "chi2_MCH")    return fChi2;                 // MCH tracking χ² (tree value)
    if (varname == "chi2_match")  return fChi2MatchMCHMFT;      // matching χ²

    // MFT-dependent (only valid when we've fetched the MFT track for this entry)
    if (varname == "chi2_MFT")    return fMFTTree ? fMFTTrackChi2 : -1.0;
    if (varname == "nClusters_MCH") return static_cast<double>(fNClusters);
    if (varname == "nClusters_MFT") {
        if (!fMFTTree) return -1.0;
        return static_cast<double>(getMFTClusterCount(fMFTClusterSizesAndFlags));
    }

    return 0.0;
}



// Check if the track is in the acceptance range

bool O2fwdtrack::IsInAcceptance(double eta)
{
    return (eta > -3.6) && (eta < -2.5);
}

int O2fwdtrack::getMFTClusterCount(ULong64_t clusterSizesAndFlags)
{
    int count = 0;
    for (int i = 0; i < 10; i++)
    {                                                           // 10 possible clusters
        UChar_t size = (clusterSizesAndFlags >> (i * 4)) & 0xF; // 4 bits per cluster
        if (size > 0)
            count++;
    }
    return count;
}

void O2fwdtrack::CalculateEfficiencyPurity(TFile *outfile)
{
    if (!fMCLabelTree)
    {
        std::cerr << "Error: MC label tree not initialized!" << std::endl;
        return;
    }




std::vector<std::pair<std::string,std::string>> varPairs = {
    {"pt_MCH","chi2_match"},
    {"pt_MCH","chi2_MCH"},
    {"pt_MCH","chi2_MFT"},
    {"pt_MCH","nClusters_MFT"},
    {"eta","chi2_match"},
    {"eta","nClusters_MFT"}
};

std::vector<VarConfig> vars = {
  VarConfig("pt_MCH",       {0.0,0.05,0.1,0.2,0.5,1.0,2.0,4.0,6.0,8.0,12.0,20.0,50.0}),
  VarConfig("chi2_MCH",     {0.0,0.25,0.5,0.8,1.2,1.6,2.0,3.0,5.0,8.0,12.0,20.0,35.0,50.0}),
  VarConfig("chi2_MFT",     {0.0,0.25,0.5,0.8,1.2,1.6,2.0,3.0,5.0,8.0,12.0,20.0,35.0,50.0}),
  VarConfig("chi2_match",   {0.0,0.5,1.0,1.5,2.0,3.0,5.0,10.0,20.0,50.0,100.0}),
  VarConfig("nClusters_MFT",{0,6,10,14,18,24}),              // [0–6), [6–10), …, [18–24)
  VarConfig("phi",           36, -TMath::Pi(), TMath::Pi()),
  VarConfig("eta",           11, -3.6, -2.5)
};



    // Book one EffPurityHists2D per pair
    std::vector<EffPurityHists2D> hists2DSets;
    Create2DEffPurHists(outfile, varPairs, vars, hists2DSets);

    const double minEta = -3.6;
    const double maxEta = -2.5;

    std::vector<EffPurityHists> histSets;
    TH1D *hChi2Optimization = nullptr;
    CreateEfficiencyPurityHistograms(outfile, vars, histSets, hChi2Optimization);

    // Collect match candidates
    std::unordered_map<Long64_t, std::vector<MatchCandidate>> matchCandidates;
    CollectMatchCandidates(matchCandidates);

    // Select best matches
    std::unordered_map<Long64_t, const MatchCandidate *> bestMatches;
    SelectBestMatches(matchCandidates, bestMatches);

    // Fill efficiency/purity counts
    Long64_t nTotalType3 = 0, nMatchedType3 = 0;
    Long64_t nTotalType0 = 0, nTrueType0 = 0;
    FillEfficiencyPurityCounts(bestMatches, vars, histSets, varPairs, hists2DSets, nTotalType3, nMatchedType3, nTotalType0, nTrueType0);

    // Report results and optimize

ReportAndOptimize(outfile, vars, histSets,
                  nTotalType3, nMatchedType3, nTotalType0, nTrueType0,
                  hChi2Optimization, matchCandidates);

    // calling 2D Processing
    Graphing2D(outfile, varPairs, hists2DSets);

    // Cleanup
    for (auto &set : histSets)
    {
        delete set.hEffDen;
        delete set.hEffNum;
        delete set.hPurityTrue;
        delete set.hPurityTotal;
    }
}

void O2fwdtrack::CreateEfficiencyPurityHistograms(TFile *outfile, const std::vector<VarConfig> &vars, std::vector<EffPurityHists> &histSets, TH1D *&hChi2Optimization)
{
    for (const auto &var : vars)
    {
        TH1D *hEffDen = nullptr;
        TH1D *hEffNum = nullptr;
        TH1D *hPurityTrue = nullptr;
        TH1D *hPurityTotal = nullptr;

        if (var.isVariable)
        {
            hEffDen = new TH1D(Form("hEffDen_%s", var.name.c_str()), "MCH-MID tracks in acceptance", var.nbins, var.edges.data());
            hEffNum = new TH1D(Form("hEffNum_%s", var.name.c_str()), "True matched global muons", var.nbins, var.edges.data());
            hPurityTrue = new TH1D(Form("hPurityTrue_%s", var.name.c_str()), "True matched global muons", var.nbins, var.edges.data());
            hPurityTotal = new TH1D(Form("hPurityTotal_%s", var.name.c_str()), "All global muons", var.nbins, var.edges.data());
        }
        else
        {
            // Fixed binning
            hEffDen = new TH1D(Form("hEffDen_%s", var.name.c_str()), "MCH-MID tracks in acceptance", var.nbins, var.min, var.max);
            hEffNum = new TH1D(Form("hEffNum_%s", var.name.c_str()), "True matched global muons", var.nbins, var.min, var.max);
            hPurityTrue = new TH1D(Form("hPurityTrue_%s", var.name.c_str()), "True matched global muons", var.nbins, var.min, var.max);
            hPurityTotal = new TH1D(Form("hPurityTotal_%s", var.name.c_str()), "All global muons", var.nbins, var.min, var.max);
        }

        // Set histogram directory to the output file
        hEffDen->SetDirectory(outfile);
        hEffNum->SetDirectory(outfile);
        hPurityTrue->SetDirectory(outfile);
        hPurityTotal->SetDirectory(outfile);

        hEffDen->Sumw2();
        hEffNum->Sumw2();
        hPurityTrue->Sumw2();
        hPurityTotal->Sumw2();

        // Set axis titles
        TString varName = GetFormattedAxisName(var.name);
        hEffDen->GetXaxis()->SetTitle(varName);
        hEffNum->GetXaxis()->SetTitle(varName);
        hPurityTrue->GetXaxis()->SetTitle(varName);
        hPurityTotal->GetXaxis()->SetTitle(varName);

        histSets.push_back({hEffDen, hEffNum, hPurityTrue, hPurityTotal});
    }
    hChi2Optimization = new TH1D("hChi2Optimization", 
                "Optimization vs #chi^{2} threshold; #chi^{2} threshold; Efficiency #times Purity", 50, 0.5, 50.5);
    hChi2Optimization->SetDirectory(outfile);
}

void O2fwdtrack::CollectMatchCandidates(std::unordered_map<Long64_t, std::vector<MatchCandidate>> &matchCandidates)
{
    Long64_t nEntries = fChain->GetEntries();
    for (Long64_t ientry = 0; ientry < nEntries; ientry++)
    {
        GetEntry(ientry);

        if (fTrackType != 0)      continue;

        if (fChi2MatchMCHMFT < 0) continue;

        double eta = std::asinh(fTgl);
        if (!IsInAcceptance(eta))
            continue;


        Long64_t mchIndex = fIndexFwdTracks_MatchMCHTrack;
        if (mchIndex < 0)
            continue;

        UInt_t mftCl = 0;
        if (fIndexMFTTracks >= 0 && fMFTTree) {
          fMFTTree->GetEntry(fIndexMFTTracks);
          mftCl = getMFTClusterCount(fMFTClusterSizesAndFlags);
        }

        fMCLabelTree->GetEntry(ientry);

        // record mftIndex so we can read its χ² later if needed
        matchCandidates[mchIndex].push_back({
                ientry,
                fChi2MatchMCHMFT,
                fMcMask,
                eta,
                fIndexMFTTracks,
                mftCl
        });
    }
}

void O2fwdtrack::SelectBestMatches(const std::unordered_map<Long64_t, std::vector<MatchCandidate>> &matchCandidates,
                                   std::unordered_map<Long64_t, const MatchCandidate *> &bestMatches)
{
    for (auto &pair : matchCandidates)
    {
        const MatchCandidate *bestCandidate = nullptr;
        for (auto &candidate : pair.second)
        {
            if (candidate.chi2 < 0 || candidate.chi2 > fChi2Threshold)
                continue;
            if (!bestCandidate || candidate.chi2 < bestCandidate->chi2)
            {
                bestCandidate = &candidate;
            }
        }
        if (bestCandidate)
        {
            bestMatches[pair.first] = bestCandidate;
        }
    }
}


void O2fwdtrack::FillEfficiencyPurityCounts(
    const std::unordered_map<Long64_t, const MatchCandidate *> &bestMatches,
    const std::vector<VarConfig> &vars,
    std::vector<EffPurityHists> &histSets,
    const std::vector<std::pair<std::string, std::string>> &varPairs,
    const std::vector<EffPurityHists2D> &hists2DSets,
    Long64_t &nTotalType3,
    Long64_t &nMatchedType3,
    Long64_t &nTotalType0,
    Long64_t &nTrueType0)
{
    Long64_t nEntries = fChain->GetEntries();
 for (Long64_t ientry = 0; ientry < nEntries; ++ientry) {
     GetEntry(ientry);
     fMCLabelTree->GetEntry(ientry);
    
     double ptMCH     = 1.0 / std::abs(fSigned1Pt);
     double eta       = std::asinh(fTgl);
     double phi       = fPhi;
     double chi2MCH   = fChi2;
     double chi2Match = fChi2MatchMCHMFT;
    
     if (!IsInAcceptance(eta)) continue;
    
     // MFT info (only meaningful for global muons)
     bool   hasMFTData = false;
     UInt_t mftClusterCount = 0;
     double chi2MFT = -1.0;
     if (fTrackType == 0 && fIndexMFTTracks >= 0 && fMFTTree) {
         fMFTTree->GetEntry(fIndexMFTTracks);
         chi2MFT = fMFTTrackChi2;
         mftClusterCount = getMFTClusterCount(fMFTClusterSizesAndFlags);
         hasMFTData = true;
     }
     double nClMCH = static_cast<double>(fNClusters);
     double nClMFT = hasMFTData ? static_cast<double>(mftClusterCount) : -1.0;

    // Get variable values
    std::vector<double> values;
    for (const auto &var : vars)
        {
            if      (var.name == "pt_MCH")        values.push_back(ptMCH);
            else if (var.name == "eta")           values.push_back(eta);
            else if (var.name == "phi")           values.push_back(phi);
            else if (var.name == "chi2_MCH")      values.push_back(chi2MCH);
            else if (var.name == "chi2_match")    values.push_back(chi2Match);
            else if (var.name == "chi2_MFT")      
                { if (chi2MFT >= 0) values.push_back(chi2MFT); else values.push_back(-1); }
            else if (var.name == "nClusters_MFT") 
                { if (nClMFT  >= 0) values.push_back(nClMFT);  else values.push_back(-1); }
        }
// ------- Efficiency (denominator = true MCH in acceptance) -------
if (fTrackType == 3) {
    nTotalType3++;

    // Denominator for MCH-based axes
    for (size_t i = 0; i < vars.size(); ++i) {
        const auto& name = vars[i].name;
        double val = 0.0;

        // MCH-only variables: always defined for truth
        if      (name == "pt_MCH")        { val = ptMCH;   histSets[i].hEffDen->Fill(val); continue; }
        else if (name == "eta")           { val = eta;     histSets[i].hEffDen->Fill(val); continue; }
        else if (name == "phi")           { val = phi;     histSets[i].hEffDen->Fill(val); continue; }
        else if (name == "chi2_MCH")      { val = chi2MCH; histSets[i].hEffDen->Fill(val); continue; }
        else if (name == "nClusters_MCH") { val = nClMCH;  histSets[i].hEffDen->Fill(val); continue; }

        // MFT-based axes: use the best match (truth or background) to define the value
        else if (name == "chi2_MFT" || name == "nClusters_MFT") {
            auto bm = bestMatches.find(ientry);
            if (bm != bestMatches.end()) {
                if (name == "chi2_MFT") {
                    if (fMFTTree && bm->second->mftIndex >= 0) {
                        fMFTTree->GetEntry(bm->second->mftIndex);
                        val = fMFTTrackChi2;
                        histSets[i].hEffDen->Fill(val);
                    }
                } else { // nClusters_MFT
                    val = static_cast<double>(bm->second->mftClusters);
                    histSets[i].hEffDen->Fill(val);
                }
            }
            continue;
        }
        // other variables (e.g. chi2_match) have no meaning for the denom here
    }

    // Numerator: only if the best match is TRUE (mcMask==0)
    auto matchIt = bestMatches.find(ientry);
    if (matchIt != bestMatches.end() && matchIt->second->mcMask == 0) {
        nMatchedType3++;

        for (size_t i = 0; i < vars.size(); ++i) {
            const auto& name = vars[i].name;
            double val = 0.0;

            if      (name == "pt_MCH")        { val = ptMCH;   histSets[i].hEffNum->Fill(val); continue; }
            else if (name == "eta")           { val = eta;     histSets[i].hEffNum->Fill(val); continue; }
            else if (name == "phi")           { val = phi;     histSets[i].hEffNum->Fill(val); continue; }
            else if (name == "chi2_MCH")      { val = chi2MCH; histSets[i].hEffNum->Fill(val); continue; }
            else if (name == "nClusters_MCH") { val = nClMCH;  histSets[i].hEffNum->Fill(val); continue; }

            // MFT-based numerator from the (true) best match
            else if (name == "chi2_MFT") {
                if (fMFTTree && matchIt->second->mftIndex >= 0) {
                    fMFTTree->GetEntry(matchIt->second->mftIndex);
                    val = fMFTTrackChi2;
                    histSets[i].hEffNum->Fill(val);
                }
            } else if (name == "nClusters_MFT") {
                val = static_cast<double>(matchIt->second->mftClusters);
                histSets[i].hEffNum->Fill(val);
            }
        }
    }
}


 // ---------------- Purity (type 0, gated by selection) ----------------
    if (fTrackType == 0) {
        if (chi2Match < 0 || chi2Match > fChi2Threshold) continue;

        nTotalType0++;
        for (size_t i = 0; i < vars.size(); ++i) {
            const auto& name = vars[i].name;
            double val = 0.0;
            if      (name == "pt_MCH")        val = ptMCH;
            else if (name == "eta")           val = eta;
            else if (name == "phi")           val = phi;
            else if (name == "chi2_MCH")      val = chi2MCH;
            else if (name == "nClusters_MCH") val = nClMCH;
            else if (name == "chi2_MFT")      { if (chi2MFT < 0) continue; val = chi2MFT; }
            else if (name == "nClusters_MFT") { if (nClMFT  < 0) continue; val = nClMFT;  }
            else if (name == "chi2_match")    val = chi2Match;
            else                              continue;

            histSets[i].hPurityTotal->Fill(val);
            if (fMcMask == 0) histSets[i].hPurityTrue->Fill(val);
        }
        if (fMcMask == 0) nTrueType0++;
    }
    //  2-D maps for every booked pair
//  2-D maps for every booked pair
for (size_t ip = 0; ip < hists2DSets.size(); ++ip) {
    auto &h2 = hists2DSets[ip];
    const auto &pr = varPairs[ip];

    auto get2D = [&](const std::string &var) -> double {
        if      (var == "pt_MCH")        return ptMCH;
        else if (var == "eta")           return eta;
        else if (var == "phi")           return phi;
        else if (var == "chi2_MCH")      return chi2MCH;
        else if (var == "chi2_match")    return chi2Match;

        // MFT-based variables: derive from context
        else if (var == "chi2_MFT") {
            if (fTrackType == 0) return (chi2MFT >= 0 ? chi2MFT : std::numeric_limits<double>::quiet_NaN());
            auto bm = bestMatches.find(ientry);
            if (bm != bestMatches.end() && fMFTTree && bm->second->mftIndex >= 0) {
                fMFTTree->GetEntry(bm->second->mftIndex);
                return fMFTTrackChi2;
            }
            return std::numeric_limits<double>::quiet_NaN();
        } else if (var == "nClusters_MFT") {
            if (fTrackType == 0) return (nClMFT >= 0 ? nClMFT : std::numeric_limits<double>::quiet_NaN());
            auto bm = bestMatches.find(ientry);
            if (bm != bestMatches.end()) {
                return static_cast<double>(bm->second->mftClusters);
            }
            return std::numeric_limits<double>::quiet_NaN();
        }

        // fallback
        return GetVarValue(var);
    };

    const double x = get2D(pr.first);
    const double y = get2D(pr.second);
    const bool valid = !(std::isnan(x) || std::isnan(y));

    // Efficiency 2D (denominator NOT gated)
    if (fTrackType == 3 && valid) {
        h2.hEffDen->Fill(x, y);
        auto mIt = bestMatches.find(ientry);
        if (mIt != bestMatches.end() && mIt->second->mcMask == 0) {
            h2.hEffNum->Fill(x, y);
        }
    }

    // Purity 2D (gated by selection)
    if (fTrackType == 0 && (chi2Match >= 0 && chi2Match <= fChi2Threshold) && valid) {
        h2.hPurityTotal->Fill(x, y);
        if (fMcMask == 0) h2.hPurityTrue->Fill(x, y);
    }
}

}
}
void O2fwdtrack::Create2DEffPurHists(
    TFile *outfile,
    const std::vector<std::pair<std::string, std::string>> &varPairs,
    const std::vector<VarConfig> &vars,
    std::vector<EffPurityHists2D> &hists2DSets)
{
    // helper to find binning config by name
    auto cfg = [&](const std::string &name) -> const VarConfig &
    {
        for (auto &v : vars)
            if (v.name == name)
                return v;
        throw std::runtime_error("No VarConfig for " + name);
    };

    for (auto &pr : varPairs)
    {
        const auto &vx = cfg(pr.first);
        const auto &vy = cfg(pr.second);
        EffPurityHists2D h;

        // denominator histogram
        if (vx.isVariable && vy.isVariable)
        {
            h.hEffDen = new TH2D(
                Form("hEffDen_%s_vs_%s", pr.first.c_str(), pr.second.c_str()),
                Form("Gen; %s; %s",
                     GetFormattedAxisName(pr.first).Data(),
                     GetFormattedAxisName(pr.second).Data()),
                vx.nbins, vx.edges.data(),
                vy.nbins, vy.edges.data());
        }
        else if (vx.isVariable)
        {
            h.hEffDen = new TH2D(
                Form("hEffDen_%s_vs_%s", pr.first.c_str(), pr.second.c_str()),
                Form("Gen; %s; %s",
                     GetFormattedAxisName(pr.first).Data(),
                     GetFormattedAxisName(pr.second).Data()),
                vx.nbins, vx.edges.data(),
                vy.nbins, vy.min, vy.max);
        }
        else if (vy.isVariable)
        {
            h.hEffDen = new TH2D(
                Form("hEffDen_%s_vs_%s", pr.first.c_str(), pr.second.c_str()),
                Form("Gen; %s; %s",
                     GetFormattedAxisName(pr.first).Data(),
                     GetFormattedAxisName(pr.second).Data()),
                vx.nbins, vx.min, vx.max,
                vy.nbins, vy.edges.data());
        }
        else
        {
            h.hEffDen = new TH2D(
                Form("hEffDen_%s_vs_%s", pr.first.c_str(), pr.second.c_str()),
                Form("Gen; %s; %s",
                     GetFormattedAxisName(pr.first).Data(),
                     GetFormattedAxisName(pr.second).Data()),
                vx.nbins, vx.min, vx.max,
                vy.nbins, vy.min, vy.max);
        }

        // clone for numerator, total-reco, true-reco
        h.hEffNum = (TH2D *)h.hEffDen->Clone(
            Form("hEffNum_%s_vs_%s", pr.first.c_str(), pr.second.c_str()));
        h.hEffNum->Reset();
        h.hPurityTotal = (TH2D *)h.hEffDen->Clone(
            Form("hPurityTotal_%s_vs_%s", pr.first.c_str(), pr.second.c_str()));
        h.hPurityTotal->Reset();
        h.hPurityTrue = (TH2D *)h.hEffDen->Clone(
            Form("hPurityTrue_%s_vs_%s", pr.first.c_str(), pr.second.c_str()));
        h.hPurityTrue->Reset();

        // send to file & enable errors
        for (auto ptr : {h.hEffDen, h.hEffNum, h.hPurityTotal, h.hPurityTrue})
        {
            ptr->SetDirectory(outfile);
            ptr->Sumw2();
        }

        hists2DSets.push_back(h);
    }
}
