
// ==========================================================================================================================================
//==========================================================================================================================================
// ==========================================================================================================================================
//=========================================================================================================================================

//  Helper-function definitions for graphing and histogram management;

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
#include <map>
#include <TLine.h>   


// near the top of O2fwdtrackGraphing.C
static inline bool isDiscreteVar(const std::string& n) {
  return n.rfind("nClusters", 0) == 0 || n == "nClusters_MCH" || n == "nClusters_MFT";
}


static inline bool isDiscreteVar(const std::string& n) {
  return n.rfind("nClusters", 0) == 0 || n == "nClusters_MCH" || n == "nClusters_MFT";
}



// O2fwdtrackGraphing.C
// BEFORE: void ReportAndOptimize( ...
void O2fwdtrack::ReportAndOptimize(
    TFile* outfile, const std::vector<VarConfig>& vars,
    std::vector<EffPurityHists>& histSets,
    Long64_t nTotalType3,
    Long64_t nMatchedType3,
    Long64_t nTotalType0, 
    Long64_t nTrueType0,
    TH1D* hChi2Optimization,
    const std::unordered_map<Long64_t, std::vector<MatchCandidate>>& matchCandidates)

{
    // Calculate and report results
    double efficiency = (nTotalType3 > 0) ? static_cast<double>(nMatchedType3) / nTotalType3 : 0;
    double purity = (nTotalType0 > 0) ? static_cast<double>(nTrueType0) / nTotalType0 : 0;

    std::cout << "\nEfficiency: " << efficiency
              << "\nPurity: " << purity
              << "\n\nTotalType0: " << nTotalType0
              << "\nnMatchedType3: " << nMatchedType3
              << "\nnTrueType0: " << nTrueType0
              << "\nnTotalType3: " << nTotalType3 << "\n\n";

    // Chi2 optimization
     std::vector<double> xs, vEff, vPur;
for (double thr = 1.0; thr <= 50.0; thr += 1.0) {
    // For each MCH track (key), pick the best candidate under this thr
    Long64_t matchedTrue = 0;   // numerator for efficiency (true matches)
    Long64_t matchedAll  = 0;   // counts how many MCH true tracks got any match (for efficiency)
    Long64_t selTotal    = 0;   // selected global muons
    Long64_t selTrue     = 0;   // selected & true
    // efficiency denom uses total true MCH in acceptance = nTotalType3
    for (const auto& kv : matchCandidates) {
        const auto& cands = kv.second;
        const MatchCandidate* best = nullptr;
        for (const auto& c : cands) {
            if (c.chi2 >= 0 && c.chi2 <= thr) {
                if (!best || c.chi2 < best->chi2) best = &c;
            }
        }
        if (best) {
            matchedAll++;
            selTotal++;                 // selecting one global per MCH
            if (best->mcMask == 0) {
                matchedTrue++;
                selTrue++;
            }
        }
    }
    double eff = (nTotalType3 > 0) ? double(matchedTrue) / double(nTotalType3) : 0.0;
    double pur = (selTotal   > 0) ? double(selTrue)     / double(selTotal)     : 0.0;
    hChi2Optimization->Fill(thr, eff * pur);


   

    xs.push_back(thr);
    vEff.push_back(eff);
    vPur.push_back(pur);

}


    double maxX = hChi2Optimization->GetBinCenter(hChi2Optimization->GetMaximumBin());
    double maxY = hChi2Optimization->GetMaximum();

    TCanvas *cScan = new TCanvas("cChi2Scan", "Eff & Pur vs #chi^{2}_{thr}", 1000, 800);
    cScan->SetGrid(1,1);
    cScan->SetLogx(1);

    TGraph *gEff = new TGraph(xs.size(), xs.data(), vEff.data());
    TGraph *gPur = new TGraph(xs.size(), xs.data(), vPur.data());
    gEff->SetLineColor(kBlue);  gEff->SetMarkerColor(kBlue);  gEff->SetMarkerStyle(20); gEff->SetLineWidth(2);
    gPur->SetLineColor(kRed);   gPur->SetMarkerColor(kRed);   gPur->SetMarkerStyle(21); gPur->SetLineWidth(2);

    gEff->GetXaxis()->SetTitle("#chi^{2}_{threshold}");
    gEff->GetYaxis()->SetTitle("Rate");
    gEff->GetXaxis()->SetLimits(1.0, 50.0);
    gEff->SetMinimum(0.0); gEff->SetMaximum(1.05);

    gEff->Draw("ALP");
    gPur->Draw("LP SAME");

    TLine *lMax = new TLine(maxX, 0.0, maxX, 1.05);  lMax->SetLineColor(kRed);     lMax->SetLineStyle(2); lMax->Draw("same");
    TLine *lSel = new TLine(fChi2Threshold, 0.0, fChi2Threshold, 1.05); lSel->SetLineColor(kGray+2); lSel->SetLineStyle(3); lSel->Draw("same");

    TLegend* leg = new TLegend(0.70, 0.75, 0.90, 0.90);
    leg->AddEntry(gEff, "Efficiency", "lp");
    leg->AddEntry(gPur, "Purity", "lp");
    leg->SetBorderSize(0); leg->SetFillStyle(0); leg->Draw();

    outfile->cd();
    gEff->Write("Chi2Scan_Eff");
    gPur->Write("Chi2Scan_Pur");
    cScan->Write();
    cScan->SaveAs("output/Chi2Scan_EffPur.png");



    // Set histogram properties for chi2 optimization.
    hChi2Optimization->SetLineWidth(3);
    hChi2Optimization->SetLineColor(kMagenta + 2);
    hChi2Optimization->GetXaxis()->SetTitle("#chi^{2}_{threshold}");
    hChi2Optimization->GetYaxis()->SetTitle("Efficiency #times Purity");


    TCanvas *cOpt = new TCanvas("cChi2Opt", "Chi2 Optimization", 1000, 800);
    cOpt->SetGrid(1,1);
    hChi2Optimization->GetXaxis()->SetRangeUser(1.0, 50.0); // avoid log(0)
    cOpt->SetLogx(1);
    hChi2Optimization->SetLineWidth(3);
    hChi2Optimization->SetLineColor(kMagenta+2);
    hChi2Optimization->GetXaxis()->SetTitle("#chi^{2}_{threshold}");
    hChi2Optimization->GetYaxis()->SetTitle("Efficiency #times Purity");
    hChi2Optimization->Draw("HIST L");


    
    

    

    // Add marker at maximum
   
    TMarker *m = new TMarker(maxX, maxY, 29);
    m->SetMarkerSize(2.5);
    m->SetMarkerColor(kRed);
    m->Draw();

    TLatex *tex = new TLatex(maxX * 1.1, maxY * 0.95,
                             Form("Max: %.1f", maxX));
    tex->SetTextColor(kRed);
    tex->SetTextSize(0.04);
    tex->Draw();

    // Save results
    outfile->cd();
    Graphing(outfile, vars, histSets);
    hChi2Optimization->Write();
    cOpt->SaveAs("output/Chi2Optimization.png");

    delete hChi2Optimization;
    delete cOpt;
}

// creating function to manage the output Tcanvas and histograms

void O2fwdtrack::Graphing(TFile *outfile, const std::vector<struct VarConfig> &vars,
                          const std::vector<struct EffPurityHists> &histSets)
{
    // to manage it so that it can work on the loop
    // we mean the needed argument of the function

    for (size_t i = 0; i < vars.size(); i++)
    {

        if (histSets[i].hEffDen->GetEntries() == 0 || histSets[i].hPurityTotal->GetEntries() == 0)
        {
            std::cerr << "Skipping " << vars[i].name << " (empty denominator)" << std::endl;
            continue;
        }

        // Create efficiency graph
        TEfficiency *eff = new TEfficiency(*histSets[i].hEffNum, *histSets[i].hEffDen);
        eff->SetName(Form("eff_%s", vars[i].name.c_str()));
        eff->SetStatisticOption(TEfficiency::kFCP);
        eff->SetConfidenceLevel(0.68);

        // Create purity graph
        TEfficiency *pur = new TEfficiency(*histSets[i].hPurityTrue, *histSets[i].hPurityTotal);
        pur->SetName(Form("pur_%s", vars[i].name.c_str()));
        pur->SetStatisticOption(TEfficiency::kFCP);
        pur->SetConfidenceLevel(0.68);

        // Configure style
        const TString varName = GetFormattedAxisName(vars[i].name);
        eff->SetTitle(Form("Efficiency vs %s;%s;Efficiency", varName.Data(), varName.Data()));
        pur->SetTitle(Form("Purity vs %s;%s;Purity", varName.Data(), varName.Data()));

        // creating canvases
        TCanvas *cEff = new TCanvas(Form("cEff_%s", vars[i].name.c_str()),
                                    Form("Efficiency_%s", vars[i].name.c_str()), 800, 600);
        TCanvas *cPurity = new TCanvas(Form("cPurity_%s", vars[i].name.c_str()),
                                       Form("Purity_%s", vars[i].name.c_str()), 800, 600);
        TCanvas *cCombined = new TCanvas(Form("cCombined_%s", vars[i].name.c_str()),
                                         Form("Combined_%s", vars[i].name.c_str()), 800, 600);

        // Draw plots
        cEff->cd();
        if (vars[i].name == "pt" || vars[i].name == "pt_MCH") gPad->SetLogx();

        DrawEfficiencyPlot(eff, kBlue, 20, cEff);

        cPurity->cd();
        DrawEfficiencyPlot(pur, kRed, 21, cPurity);

        cCombined->cd();
        DrawCombinedPlot(eff, pur, cCombined);

        // Save plots
        cEff->SaveAs(Form("output/Efficiency_%s.png", vars[i].name.c_str()));
        cPurity->SaveAs(Form("output/Purity_%s.png", vars[i].name.c_str()));
        cCombined->SaveAs(Form("output/Combined_%s.png", vars[i].name.c_str()));

        cEff->Write();
        cPurity->Write();
        cCombined->Write();

        // Save to output file
        outfile->cd();
        eff->Write();
        pur->Write();

        // summary canvas
        std::vector<std::string> summaryNames = {"pt_MCH", "phi", "nClusters_MFT", "chi2_MFT"};
        TCanvas *cSummary = new TCanvas("cSummary", "Eff/Pur Overview", 1600, 1200);
        cSummary->Divide(2, 2);

        for (size_t j = 0; j < summaryNames.size(); ++j)
        {
            cSummary->cd(j + 1);
            TString key = Form("eff_%s", summaryNames[j].c_str());
            auto e = dynamic_cast<TEfficiency *>(outfile->Get(key));

            if (!e)
            {
                Warning("Graphing", "Missing TEfficiency \"%s\", skipping panel %zu", key.Data(), j + 1);
                continue;
            }

            e->Draw("AP E3");
            TLatex label;
            label.DrawTextNDC(0.15, 0.85,
                  Form("(%c) vs %s", char('a' + j), GetFormattedAxisName(summaryNames[j]).Data()));
        }
        outfile->cd();
        cSummary->Write();
        cSummary->SaveAs("output/Summary_Efficiency.png");
        cSummary->Close();

        // Cleanup
        delete cEff;
        delete cPurity;
        delete cCombined;
        delete eff;
        delete pur;

        std::cout << "Saved plots for variable: " << vars[i].name << std::endl;

        //    //log to user saving process if successful
        //    if (Form("output/Efficiency_%s.png", vars[i].name.c_str())) {
        //       std::cout << "Efficiency and Purity histograms saved as Efficiency_" << vars[i].name.c_str() <<
        //                 ".png and Purity_" << vars[i].name.c_str() << ".png" << std::endl;
        //    }
    }
}

// Helper for LaTeX-formatted axis labels
// In O2fwdtrackGraphing.C, update GetFormattedAxisName:
TString O2fwdtrack::GetFormattedAxisName(const std::string& key) {
  static const std::map<std::string, TString> kAxis = {
    {"pt_MCH", "p_{T}^{MCH} (GeV/c)"},
    {"eta", "#eta"},
    {"phi", "#phi (rad)"},
    {"nClusters_MCH", "N_{clusters}^{MCH}"},
    {"chi2_match", "#chi^{2}_{match}"},
    {"chi2_MCH", "#chi^{2}_{MCH}"},
    {"chi2_MFT", "#chi^{2}_{MFT}"},
    {"nClusters_MFT", "N_{clusters}^{MFT}"}
  };
  auto it = kAxis.find(key);
  return (it != kAxis.end()) ? it->second : TString(key.c_str());
}

// New helper function for consistent styling
void O2fwdtrack::DrawEfficiencyPlot(TEfficiency *eff, Color_t color, Style_t marker, TCanvas *canvas)
{
    canvas->cd();
    gPad->SetGrid(1, 1);
    gPad->SetTicky();
    gPad->SetTickx();

    eff->SetLineWidth(2);
    eff->SetLineColor(color);
    eff->SetMarkerColor(color);
    eff->SetMarkerStyle(marker);
    eff->SetMarkerSize(1.5);
    eff->SetFillColorAlpha(color, 0.3);
    eff->SetFillStyle(3001);

    // graph->GetYaxis()->SetRangeUser(0.0, 1.0);

    eff->Draw("AP E3"); // Draw with error band

    // Configure axes Styling
    TGraphAsymmErrors *graph = eff->GetPaintedGraph();
    if (graph)
    {
        TAxis *xaxis = eff->GetPaintedGraph()->GetXaxis();
        TAxis *yaxis = eff->GetPaintedGraph()->GetYaxis();
        xaxis->SetTitleSize(0.05);
        yaxis->SetTitleSize(0.05);
        yaxis->SetRangeUser(0.0, 1.05);
    }
    // Add uncertainty band
    eff->Draw("E3 same");               // Draw uncertainty band // 68% confidence interval, this means the band will be drawn around the efficiency curve
    eff->SetFillColorAlpha(color, 0.3); // Set fill color
    eff->SetFillStyle(3001);            // Set fill style for the band
    eff->Draw("P same");                // Central value markers
}

void O2fwdtrack::DrawCombinedPlot(TEfficiency* eff, TEfficiency* pur, TCanvas* canvas)
{
    canvas->cd();
    gPad->SetGrid(1, 1);

    // styling
    eff->SetLineColor(kBlue); 
    eff->SetMarkerColor(kBlue);  
    eff->SetMarkerStyle(20);
    eff->SetFillColorAlpha(kBlue, 0.20);  
    eff->SetLineWidth(2);
    
    pur->SetLineColor(kRed);   
    pur->SetMarkerColor(kRed);   
    pur->SetMarkerStyle(21);
    pur->SetFillColorAlpha(kRed, 0.20);   
    pur->SetLineWidth(2);

    // 1) Draw axes with efficiency only, then update to materialize the painted graph
    eff->Draw("AP");
    gPad->Update();

    // Fix a common axis for both
    if (auto* grE = eff->GetPaintedGraph()) {
        grE->GetYaxis()->SetRangeUser(0.0, 1.05);
    }

    // 2) Draw both uncertainty bands behind
    eff->Draw("E3 SAME");
    pur->Draw("E3 SAME");

    // 3) Draw both central value markers on top
    eff->Draw("P SAME");
    pur->Draw("P SAME");

    // 4) Legend + tidy axis
    TLegend* leg = new TLegend(0.70, 0.75, 0.90, 0.90);
    leg->AddEntry(eff, "Efficiency", "lp");
    leg->AddEntry(pur, "Purity",     "lp");
    leg->SetBorderSize(0); leg->SetFillStyle(0);
    leg->Draw();

    gPad->RedrawAxis();
}

void O2fwdtrack::Graphing2D(TFile* outfile,
                           const std::vector<std::pair<std::string,std::string>>& varPairs,
                           const std::vector<EffPurityHists2D>& hists2DSets)
{
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kViridis);

    for (size_t i = 0; i < varPairs.size(); ++i) {
        // unpack the variable names
        const auto& xVar = varPairs[i].first;
        const auto& yVar = varPairs[i].second;
        // grab the corresponding 2D hist pointers
        const auto& h = hists2DSets[i];

        // build nice axis labels
        TString xLabel = GetFormattedAxisName(xVar);
        TString yLabel = GetFormattedAxisName(yVar);

        // ——— Efficiency 2D ———
        {
          // pass the numerator & denominator TH2D into TEfficiency
          auto* eff2D = new TEfficiency(*h.hEffNum, *h.hEffDen);
          eff2D->SetName(Form("eff2D_%s_vs_%s", xVar.c_str(), yVar.c_str()));
          eff2D->SetTitle(Form("Efficiency vs %s and %s;%s;%s;Efficiency",
                               xVar.c_str(), yVar.c_str(),
                               xLabel.Data(), yLabel.Data()));
          auto* cE = new TCanvas(
            Form("cE2D_%s_vs_%s", xVar.c_str(), yVar.c_str()),
            Form("Eff %s vs %s", xVar.c_str(), yVar.c_str()),
            800, 600
          );
          cE->SetRightMargin(0.15);
          eff2D->Draw("COLZ");
          cE->SaveAs(Form("output/Eff2D_%s_vs_%s.png", xVar.c_str(), yVar.c_str()));
          outfile->cd();  eff2D->Write();
          delete cE;
          delete eff2D;
        }

        // ——— Purity 2D ———
        {
          auto* pur2D = new TEfficiency(*h.hPurityTrue, *h.hPurityTotal);
          pur2D->SetName(Form("pur2D_%s_vs_%s", xVar.c_str(), yVar.c_str()));
          pur2D->SetTitle(Form("Purity vs %s and %s;%s;%s;Purity",
                               xVar.c_str(), yVar.c_str(),
                               xLabel.Data(), yLabel.Data()));
          auto* cP = new TCanvas(
            Form("cP2D_%s_vs_%s", xVar.c_str(), yVar.c_str()),
            Form("Pur %s vs %s", xVar.c_str(), yVar.c_str()),
            800, 600
          );
          cP->SetRightMargin(0.15);
          pur2D->Draw("COLZ");
          cP->SaveAs(Form("output/Pur2D_%s_vs_%s.png", xVar.c_str(), yVar.c_str()));
          outfile->cd();  pur2D->Write();
          delete cP;
          delete pur2D;
        }
    }
}
