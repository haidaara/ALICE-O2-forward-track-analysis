
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


double O2fwdtrack::GetVarValue(const std::string &varname)
{
    if (varname == "pt")
        return 1. / std::abs(fSigned1Pt);
    if (varname == "eta")
        return std::asinh(fTgl);
    if (varname == "chi2")
        return fChi2;
    if (varname == "nClusters")
        return fNClusters;
    if (varname == "phi")
        return fPhi;

    return 0;
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

    std::vector<VarConfig> vars = {
        // Variable binning - edges stored directly
        VarConfig("pt", {0.0, 0.05, 0.1, 0.2, 0.5, 1.0, 2.0, 4.0, 6.0, 8.0, 12.0, 20.0, 50.0}),
        VarConfig("chi2", {0, 1, 2, 5, 10, 20, 50, 100}),
        // Fixed binning
        VarConfig("nClusters", {0, 1, 2, 3, 4, 5, 7, 10, 15, 20}),
        VarConfig("phi", 36, -TMath::Pi(), TMath::Pi()),
        VarConfig("eta", 11, -3.6, -2.5) // -3.6 to -2.5 with 11 bins
    };

    // ——— 2-D variable pairs to plot ———
    std::vector<std::pair<std::string, std::string>> varPairs = {
        {"pt", "phi"},        // kinematic azimuthal scan
        {"eta", "phi"},       // acceptance vs φ
        {"pt", "nClusters"},  // track-quality vs pT
        {"pt", "chi2"},       // fit‐quality vs pT
        {"eta", "nClusters"}, // QC vs η
        {"eta", "chi2"}       // QC vs η
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
    ReportAndOptimize(outfile, vars, histSets, nTotalType3, nMatchedType3, nTotalType0, nTrueType0, hChi2Optimization);

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
    hChi2Optimization = new TH1D("hChi2Optimization", "Optimal #chi^{2} threshold; #chi^{2} threshold; Efficiency #times Purity", 50, 0, 100);
    hChi2Optimization->SetDirectory(outfile);
}

void O2fwdtrack::CollectMatchCandidates(std::unordered_map<Long64_t, std::vector<MatchCandidate>> &matchCandidates)
{
    Long64_t nEntries = fChain->GetEntries();
    for (Long64_t ientry = 0; ientry < nEntries; ientry++)
    {
        GetEntry(ientry);

        if (fTrackType != 0)
            continue;
        if (fChi2MatchMCHMFT < 0 || fChi2MatchMCHMFT > fChi2Threshold)
            continue;

        double eta = std::asinh(fTgl);
        if (!IsInAcceptance(eta))
            continue;

        Long64_t mchIndex = fIndexFwdTracks_MatchMCHTrack;
        if (mchIndex < 0)
            continue;

        fMCLabelTree->GetEntry(ientry);
        matchCandidates[mchIndex].push_back({ientry,
                                             fChi2MatchMCHMFT,
                                             fMcMask,
                                             eta});
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
    for (Long64_t ientry = 0; ientry < nEntries; ientry++)
    {
        GetEntry(ientry);
        fMCLabelTree->GetEntry(ientry);

        double pT = 1. / std::abs(fSigned1Pt);
        double eta = std::asinh(fTgl);
        double phi = fPhi;

        if (!IsInAcceptance(eta))
            continue;

        // Initialize cluster variables
        UInt_t clusterValue = fNClusters;
        UInt_t mftClusterCount = 0;
        bool hasMFTData = false;

        // Handle MFT clusters for global muons
        if (fTrackType == 0 && fIndexMFTTracks >= 0 && fMFTTree)
        {
            fMFTTree->GetEntry(fIndexMFTTracks);
            mftClusterCount = getMFTClusterCount(fMFTClusterSizesAndFlags);
            hasMFTData = true;
        }

        // Get variable values
        std::vector<double> values;
        for (const auto &var : vars)
        {
            if (var.name == "pt")
            {
                values.push_back(pT);
            }
            else if (var.name == "chi2")
            {
                values.push_back(fChi2);
            }
            else if (var.name == "nClusters")
            {
                // Use combined clusters for global muons with MFT data
                if (fTrackType == 0 && hasMFTData)
                {
                    values.push_back(fNClusters + mftClusterCount);
                }
                else
                {
                    values.push_back(clusterValue);
                }
            }
            else if (var.name == "phi")
            {
                values.push_back(fPhi);
            }
            else if (var.name == "eta")
            {
                values.push_back(std::asinh(fTgl));
            }
            else
            {
                std::cerr << "Unknown variable: " << var.name << std::endl;
                values.push_back(0); // Default value for unknown variables
            }
        }

        // Efficiency calculation
        if (fTrackType == 3)
        {
            nTotalType3++;
            for (size_t i = 0; i < vars.size(); i++)
            {
                histSets[i].hEffDen->Fill(values[i]);
            }

            auto matchIt = bestMatches.find(ientry);
            if (matchIt != bestMatches.end() && matchIt->second->mcMask == 0)
            {
                nMatchedType3++;
                for (size_t i = 0; i < vars.size(); i++)
                {
                    histSets[i].hEffNum->Fill(values[i]);
                }
            }
        }

        // Purity calculation
        if (fTrackType == 0)
        {
            nTotalType0++;
            for (size_t i = 0; i < vars.size(); i++)
            {
                histSets[i].hPurityTotal->Fill(values[i]);
                if (fMcMask == 0)
                {
                    histSets[i].hPurityTrue->Fill(values[i]);
                }
            }
            if (fMcMask == 0)
                nTrueType0++;
        }

        //  2-D maps for every booked pair
        for (size_t ip = 0; ip < hists2DSets.size(); ++ip)
        {
            auto &h2 = hists2DSets[ip];
            auto pr = varPairs[ip];

            double x = GetVarValue(pr.first);
            double y = GetVarValue(pr.second);

            // always recompute these per-entry
            double pT = 1. / std::abs(fSigned1Pt);
            double eta = std::asinh(fTgl);
            double phi = fPhi;

            // Efficiency (MC true tracks)
            if (fTrackType == 3)
            {
                h2.hEffDen->Fill(x, y);
                auto mIt = bestMatches.find(ientry);
                if (mIt != bestMatches.end() && mIt->second->mcMask == 0)
                {
                    h2.hEffNum->Fill(x, y);
                }
            }
            if (fTrackType == 0)
            {
                h2.hPurityTotal->Fill(x, y);
                if (fMcMask == 0)
                {
                    h2.hPurityTrue->Fill(x, y);
                }
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
