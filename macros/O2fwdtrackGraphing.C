
// ==========================================================================================================================================
//==========================================================================================================================================
// ==========================================================================================================================================
//==========================================================================================================================================

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

void O2fwdtrack::ReportAndOptimize(TFile *outfile, const std::vector<VarConfig> &vars, std::vector<EffPurityHists> &histSets,
                                   Long64_t nTotalType3,
                                   Long64_t nMatchedType3,
                                   Long64_t nTotalType0,
                                   Long64_t nTrueType0,
                                   TH1D *hChi2Optimization)
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
    for (double thresh = 1.0; thresh <= 50.0; thresh += 1.0)
    {
        SetChi2Threshold(thresh);
        double quality = efficiency * purity;
        hChi2Optimization->Fill(thresh, quality);
    }
    // Set histogram properties for chi2 optimization.
    hChi2Optimization->SetLineWidth(3);
    hChi2Optimization->SetLineColor(kMagenta + 2);
    hChi2Optimization->GetXaxis()->SetTitle("#chi^{2}_{threshold}");
    hChi2Optimization->GetYaxis()->SetTitle("Efficiency #times Purity");

    TCanvas *cOpt = new TCanvas("cChi2Opt", "Chi2 Optimization", 1000, 800);
    cOpt->SetLogx(1);
    cOpt->SetGrid(1, 1);

    hChi2Optimization->Draw("HIST L");

    // Add marker at maximum
    double maxX = hChi2Optimization->GetBinCenter(hChi2Optimization->GetMaximumBin());
    double maxY = hChi2Optimization->GetMaximum();
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
        if (vars[i].name == "pt")
            gPad->SetLogx();
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
        std::vector<std::string> summaryNames = {"pt", "phi", "nClusters", "chi2"};
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
            label.DrawTextNDC(0.15, 0.85, Form("(%zu) vs %s", 'a' + j, GetFormattedAxisName(summaryNames[j]).Data()));
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
TString O2fwdtrack::GetFormattedAxisName(const std::string &varname)
{
    static std::map<std::string, TString> axisNames = {
        {"pt", "p_{T} (GeV/c)"},
        {"chi2", "#chi^{2}/ndf"},
        {"nClusters", "N_{clusters}"},
        {"phi", "#phi (rad)"}};

    if (axisNames.find(varname) != axisNames.end())
    {
        return axisNames[varname];
    }
    return TString(varname.c_str());
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

void O2fwdtrack::DrawCombinedPlot(TEfficiency *eff, TEfficiency *pur, TCanvas *canvas)
{
    canvas->cd();
    gPad->SetGrid(1, 1);

    // Draw efficiency first
    eff->SetLineColor(kBlue);
    eff->SetMarkerColor(kBlue);
    eff->SetMarkerStyle(20);
    eff->SetFillColorAlpha(kBlue, 0.2);
    eff->Draw("AP E3");

    // Then draw purity on top
    pur->SetLineColor(kRed);
    pur->SetMarkerColor(kRed);
    pur->SetMarkerStyle(21);
    pur->SetFillColorAlpha(kRed, 0.2);
    pur->Draw("P E3 SAME");

    // Add legend
    TLegend *leg = new TLegend(0.7, 0.75, 0.9, 0.9);
    leg->AddEntry(eff, "Efficiency", "P");
    leg->AddEntry(pur, "Purity", "P");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    // Unified axes
    auto* grE = eff->GetPaintedGraph();
    auto* grP = pur->GetPaintedGraph();
    if (grE && grP) {
        double mn = std::min(grE->GetHistogram()->GetMinimum(), grP->GetHistogram()->GetMinimum());
        grE->GetYaxis()->SetRangeUser(std::max(0.0, mn-0.05), 1.05);
    }

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
