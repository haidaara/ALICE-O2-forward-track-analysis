// ==========================================================================================================================================
//==========================================================================================================================================
// ==========================================================================================================================================
//==========================================================================================================================================

//  Helper-function definitions for fwdtrack analysis;

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

TFile *O2fwdtrack::outputManagement(TFile *outputfile, bool &closeFile)
{
    if (!outputfile)
    {
        outputfile = new TFile("output/output.root", "RECREATE");
        closeFile = true;
    }
    if (!outputfile || outputfile->IsZombie())
    {
        std::cerr << "Error creating output file!" << std::endl;
        return nullptr;
    }
    TDirectory *subdir = outputfile->mkdir("O2fwdtrack");
    subdir->cd();
    return outputfile;
}

void O2fwdtrack::initializeHistograms(const std::vector<std::string> &branches,
                                      int nbranches, int ntype, const int trackTypes[],
                                      std::vector<std::vector<TH1D *>> &hist)
{
    for (int i = 0; i < nbranches; i++)
    {
        for (int j = 0; j < ntype; j++)
        {
            double min = -10, max = 10;
            if (branches[i] == "fZ")
            {
                min = -1000;
                max = 1000;
            }
            else if (branches[i] == "fSigned1Pt")
            {
                min = -0.01;
                max = 0.01;
            }
            else if (branches[i].find("Chi2") != std::string::npos && trackTypes[j] <= 2)
            {
                min = 0;
                max = 50;
            }
            else if (branches[i].find("Chi2") != std::string::npos && trackTypes[j] > 2)
            {
                min = 0;
                max = 2;
            }
            else if (branches[i] == "fMatchScoreMCHMFT")
            {
                min = 0;
                max = 2;
            }
            else if (branches[i] == "fTgl")
            {
                min = -10;
                max = 10;
            }

            hist[i][j] = new TH1D(Form("h_FWD_%s_type%d", branches[i].c_str(), trackTypes[j]),
                                  Form("FWD %s for track type %d;%s;Entries",
                                       branches[i].c_str(), trackTypes[j], branches[i].c_str()),
                                  100, min, max);
        }
    }
}

void O2fwdtrack::fillHistograms(Long64_t nentries, Long64_t &nbytes, Long64_t &nb,
                                const std::vector<std::string> &branches, int nbranches, int ntype,
                                const int trackTypes[], std::vector<std::vector<TH1D *>> &hist)
{
    for (Long64_t jentry = 0; jentry < nentries; ++jentry)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0)
            break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;

        int index = -1;
        for (int k = 0; k < ntype; ++k)
        {
            if (fTrackType == trackTypes[k])
            {
                index = k;
                break;
            }
        }
        if (index < 0)
            continue;

        for (int i = 0; i < nbranches; ++i)
        {
            double value = 0.0;
            if (branches[i] == "fX")
                value = fX;
            else if (branches[i] == "fY")
                value = fY;
            else if (branches[i] == "fZ")
                value = fZ;
            else if (branches[i] == "fPhi")
                value = fPhi;
            else if (branches[i] == "fTgl")
                value = fTgl;
            else if (branches[i] == "fSigned1Pt")
                value = fSigned1Pt;
            else if (branches[i] == "fChi2")
                value = fChi2;
            else if (branches[i] == "fChi2MatchMCHMID")
                value = fChi2MatchMCHMID;
            else if (branches[i] == "fChi2MatchMCHMFT")
                value = fChi2MatchMCHMFT;
            else if (branches[i] == "fMatchScoreMCHMFT")
                value = fMatchScoreMCHMFT;

            hist[i][index]->Fill(value);
        }
    }
}

void O2fwdtrack::normalizeHistograms(int nbranches, int ntype,
                                     std::vector<std::vector<TH1D *>> &hist)
{
    for (int i = 0; i < nbranches; ++i)
        for (int j = 0; j < ntype; ++j)
            if (hist[i][j]->Integral() > 0)
                hist[i][j]->Scale(1.0 / hist[i][j]->Integral());
}

void O2fwdtrack::canvasManipulation(const std::vector<std::string> &branches, int nbranches, int ntype,
                                    const int trackTypes[], std::vector<std::vector<TH1D *>> &hist, TFile *outfile)
{
    for (int i = 0; i < nbranches; ++i)
    {
        TCanvas *c1 = new TCanvas(Form("c1_%s", branches[i].c_str()),
                                  Form("O2fwdtrack Analysis - %s", branches[i].c_str()),
                                  800, 600);
        c1->Divide(2, 2);

        for (int j = 0; j < ntype; ++j)
        {
            c1->cd(j + 1);
            hist[i][j]->Draw("hist");
            TLegend *leg = new TLegend(0.15, 0.7, 0.45, 0.9);
            leg->AddEntry(hist[i][j], Form("track_type = %d", trackTypes[j]), "l");
            leg->Draw();
        }
        c1->SaveAs(Form("./output/png_graph_class/O2fwdtrack_Class_%s.png",
                        branches[i].c_str()));
        outfile->cd();
        for (int j = 0; j < ntype; ++j)
            hist[i][j]->Write();
        delete c1;
    }
}