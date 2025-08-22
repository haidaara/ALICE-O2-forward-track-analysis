#define O2fwdtrack_cxx
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

void O2fwdtrack::Loop(TFile *outputfile)
{
    bool closeFile = false;

    TFile *outfile = outputManagement(outputfile, closeFile);

    std::vector<std::string> branches = {"fX", "fY", "fZ", "fPhi", "fTgl", "fSigned1Pt", "fChi2",
                                         "fChi2MatchMCHMID", "fChi2MatchMCHMFT", "fMatchScoreMCHMFT"};

    int nbranches = branches.size();

    int ntype = 4; // Number of track types
    int trackTypes[] = {0, 2, 3, 4};

    // Create a 2D array of histograms for each branch and track type
    std::vector<std::vector<TH1D *>> hist(nbranches, std::vector<TH1D *>(ntype, nullptr));

    if (fChain == 0)
        return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;

    gStyle->SetOptStat(0); // no stats box
    gStyle->SetTitleFont(42, "XY");
    gStyle->SetLabelFont(42, "XY");
    gStyle->SetLabelSize(0.04, "XY");
    gStyle->SetTitleSize(0.05, "XY");
    gStyle->SetPalette(kViridis); // colorblind-friendly

    // initailize histograms:
    initializeHistograms(branches, nbranches, ntype, trackTypes, hist);

    // Enable batch mode to prevent temporary canvas display
    bool originalBatchMode = gROOT->IsBatch();
    gROOT->SetBatch(kTRUE);

    // Fill histograms:
    fillHistograms(nentries, nbytes, nb, branches, nbranches, ntype, trackTypes, hist);

    // normalization
    // normalizeHistograms(nbranches, ntype, hist);

    // canvas manipulation
    canvasManipulation(branches, nbranches, ntype, trackTypes, hist, outfile);

    CalculateEfficiencyPurity(outfile);

    // Restore original batch mode
    gROOT->SetBatch(originalBatchMode);

    if (closeFile)
        outfile->Close();
}
// ——————————————————————————————————————

// ==========================================================================================================================================
//==========================================================================================================================================
// ==========================================================================================================================================
//==========================================================================================================================================

// void O2fwdtrack::Loop()
// {

//    if (fChain == 0) return;

//    Long64_t nentries = fChain->GetEntriesFast();

//    Long64_t nbytes = 0, nb = 0;
//    for (Long64_t jentry=0; jentry<nentries;jentry++) {
//       Long64_t ientry = LoadTree(jentry);
//       if (ientry < 0) break;
//       nb = fChain->GetEntry(jentry);   nbytes += nb;
//       // if (Cut(ientry) < 0) continue;
//    }
// }

//   In a ROOT session, you can do:
//      root> .L O2fwdtrack.C
//      root> O2fwdtrack t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
// by  b_branchname->GetEntry(ientry); //read only this branch

// Add after other function implementations

bool O2fwdtrack::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return true;
}

void O2fwdtrack::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain)
        return;
    fChain->Show(entry);
}
Int_t O2fwdtrack::Cut(Long64_t entry)
{
    // This function may be called from Loop.
    // returns  1 if entry is accepted.
    // returns -1 otherwise.
    return 1;
}




#ifdef O2fwdtrack_cxx
O2fwdtrack::O2fwdtrack(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
if (tree == 0) {
        TFile* f = TFile::Open("data/AO2D_MC_promptJpsi_anch24_merged.root");
        TDirectory* dir = f->GetDirectory("DF_2397811916393856");
        dir->GetObject("O2mfttrack_001", fMFTTree);
        if (fMFTTree) {
            fMFTTree->SetBranchAddress("fMFTClusterSizesAndTrackFlags", &fMFTClusterSizesAndFlags);
        }
      }
if (tree == 0) {
   TString fname = "data/AO2D_MC_promptJpsi_anch24_merged.root";
   TFile   *f    = nullptr;

   // 1) current folder
   if (!gSystem->AccessPathName(fname))
      f = TFile::Open(fname);

   // 2) parent folder  (“../”)
   if (!f || f->IsZombie()) {
      TString up = (TString)(gSystem->DirName(gSystem->pwd())) + "/" + fname;
      if (!gSystem->AccessPathName(up))
         f = TFile::Open(up);
   }

   // 3) give up gracefully
   if (!f || f->IsZombie()) {
      Error("O2fwdtrack","Cannot open %s – start ROOT from the project "
              "folder or move the file next to the macro.", fname.Data());
      return;
   }

   TDirectory *dir = f->GetDirectory("DF_2397811916393856");
   dir->GetObject("O2fwdtrack", tree);

   Init(tree);
   
   if (f) {
        TDirectory* dir = f->GetDirectory("DF_2397811916393856");
        if (dir) {
            dir->GetObject("O2mcfwdtracklabel", fMCLabelTree);
            if (fMCLabelTree) {
                // ADD THIS LINE
                fMCLabelTree->SetBranchAddress("fMcMask", &fMcMask);
            }
        }
    }
   }
   
}

O2fwdtrack::~O2fwdtrack()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t O2fwdtrack::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t O2fwdtrack::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void O2fwdtrack::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fIndexCollisions", &fIndexCollisions, &b_fIndexCollisions);
   fChain->SetBranchAddress("fTrackType", &fTrackType, &b_fTrackType);
   fChain->SetBranchAddress("fX", &fX, &b_fX);
   fChain->SetBranchAddress("fY", &fY, &b_fY);
   fChain->SetBranchAddress("fZ", &fZ, &b_fZ);
   fChain->SetBranchAddress("fPhi", &fPhi, &b_fPhi);
   fChain->SetBranchAddress("fTgl", &fTgl, &b_fTgl);
   fChain->SetBranchAddress("fSigned1Pt", &fSigned1Pt, &b_fSigned1Pt);
   fChain->SetBranchAddress("fNClusters", &fNClusters, &b_fNClusters);
   fChain->SetBranchAddress("fPDca", &fPDca, &b_fPDca);
   fChain->SetBranchAddress("fRAtAbsorberEnd", &fRAtAbsorberEnd, &b_fRAtAbsorberEnd);
   fChain->SetBranchAddress("fChi2", &fChi2, &b_fChi2);
   fChain->SetBranchAddress("fChi2MatchMCHMID", &fChi2MatchMCHMID, &b_fChi2MatchMCHMID);
   fChain->SetBranchAddress("fChi2MatchMCHMFT", &fChi2MatchMCHMFT, &b_fChi2MatchMCHMFT);
   fChain->SetBranchAddress("fMatchScoreMCHMFT", &fMatchScoreMCHMFT, &b_fMatchScoreMCHMFT);
   fChain->SetBranchAddress("fIndexMFTTracks", &fIndexMFTTracks, &b_fIndexMFTTracks);
   fChain->SetBranchAddress("fIndexFwdTracks_MatchMCHTrack", &fIndexFwdTracks_MatchMCHTrack, &b_fIndexFwdTracks_MatchMCHTrack);
   fChain->SetBranchAddress("fMCHBitMap", &fMCHBitMap, &b_fMCHBitMap);
   fChain->SetBranchAddress("fMIDBitMap", &fMIDBitMap, &b_fMIDBitMap);
   fChain->SetBranchAddress("fMIDBoards", &fMIDBoards, &b_fMIDBoards);
   fChain->SetBranchAddress("fTrackTime", &fTrackTime, &b_fTrackTime);
   fChain->SetBranchAddress("fTrackTimeRes", &fTrackTimeRes, &b_fTrackTimeRes);
   Notify();

   // Initialize MFT tree from same file
  TFile *currentFile = fChain->GetCurrentFile();
   if (currentFile) {
      TDirectory *dir = currentFile->GetDirectory("DF_2397811916393856"); // Use actual dir pattern
   if (dir) dir->GetObject("O2mfttrack_001", fMFTTree);
   if (fMFTTree) {
     fMFTTree->SetBranchAddress("fMFTClusterSizesAndTrackFlags", 
                               &fMFTClusterSizesAndFlags);
   }

   }
}

#endif // #ifdef O2fwdtrack_cxx
