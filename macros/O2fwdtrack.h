//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 17 18:51:15 2025 by ROOT version 6.36.000
// from TTree O2fwdtrack/O2fwdtrack
// found on file: AO2D_MC_promptJpsi_anch24_merged.root
//////////////////////////////////////////////////////////

#ifndef O2fwdtrack_h
#define O2fwdtrack_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSystem.h>
#include <TDirectory.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <vector>
#include <string>
#include <unordered_map>

#include <TH2.h>          
#include <TEfficiency.h>  
#include "TError.h"  


// In O2fwdtrack.h, inside struct VarConfig:
// In O2fwdtrack.h
struct VarConfig {
    std::string name;
    bool isVariable;
    
    // Parameters for both binning types
    int nbins;
    double min;
    double max;
    std::vector<double> edges;  // For variable binning

    // Fixed binning constructor
    VarConfig(std::string n, int nb, double mn, double mx)
        : name(std::move(n)), isVariable(false), 
          nbins(nb), min(mn), max(mx) {}

    // Variable binning constructor
    VarConfig(std::string n, std::vector<double> binEdges)
        : name(n), isVariable(true),
          nbins(binEdges.size()-1), min(0), max(0),
          edges(std::move(binEdges)) {}
};

//using generic histogram set for efficiency/purity
struct EffPurityHists2D {
    TH2D* hEffDen;    // denominator histogram
    TH2D* hEffNum;    // numerator histogram
    TH2D* hPurityTotal; // total purity histogram
    TH2D* hPurityTrue; // true purity histogram
    
};

struct MatchCandidate {
    Long64_t entry;
    double chi2;
    UChar_t mcMask;
    double eta;
};

struct EffPurityHists {
    TH1D* hEffDen;
    TH1D* hEffNum;
    TH1D* hPurityTrue;
    TH1D* hPurityTotal;
};


// Header file for the classes stored in the TTree if any.

class O2fwdtrack {
private:
  double fChi2Threshold{100.0}; // Default threshold for Chi2
  
public :
   TTree          *fChain{nullptr};   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent{-1}; //!current Tree number in a TChain
   TH1D* fHDen  = nullptr;
   TH1D* fHNum  = nullptr;
   TTree* fMCLabelTree = nullptr;

   TTree* fMFTTree = nullptr;
   ULong64_t fMFTClusterSizesAndFlags;  // MFT cluster data


// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fIndexCollisions;
   UChar_t         fTrackType;
   UChar_t         fMcMask;        // MC truth mask added by me
   Float_t         fX;
   Float_t         fY;
   Float_t         fZ;
   Float_t         fPhi;
   Float_t         fTgl;
   Float_t         fSigned1Pt;
   Char_t          fNClusters;
   Float_t         fPDca;
   Float_t         fRAtAbsorberEnd;
   Float_t         fChi2;
   Float_t         fChi2MatchMCHMID;
   Float_t         fChi2MatchMCHMFT;
   Float_t         fMatchScoreMCHMFT;
   Int_t           fIndexMFTTracks;
   Int_t           fIndexFwdTracks_MatchMCHTrack;
   UShort_t        fMCHBitMap;
   UChar_t         fMIDBitMap;
   UInt_t          fMIDBoards;
   Float_t         fTrackTime;
   Float_t         fTrackTimeRes;

   // List of branches
   TBranch        *b_fIndexCollisions;   //!
   TBranch        *b_fTrackType;   //!
   TBranch        *b_fX;   //!
   TBranch        *b_fY;   //!
   TBranch        *b_fZ;   //!
   TBranch        *b_fPhi;   //!
   TBranch        *b_fTgl;   //!
   TBranch        *b_fSigned1Pt;   //!
   TBranch        *b_fNClusters;   //!
   TBranch        *b_fPDca;   //!
   TBranch        *b_fRAtAbsorberEnd;   //!
   TBranch        *b_fChi2;   //!
   TBranch        *b_fChi2MatchMCHMID;   //!
   TBranch        *b_fChi2MatchMCHMFT;   //!
   TBranch        *b_fMatchScoreMCHMFT;   //!
   TBranch        *b_fIndexMFTTracks;   //!
   TBranch        *b_fIndexFwdTracks_MatchMCHTrack;   //!
   TBranch        *b_fMCHBitMap;   //!
   TBranch        *b_fMIDBitMap;   //!
   TBranch        *b_fMIDBoards;   //!
   TBranch        *b_fTrackTime;   //!
   TBranch        *b_fTrackTimeRes;   //!

   O2fwdtrack(TTree *tree=0);
   virtual ~O2fwdtrack();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TFile* outputfile = nullptr);
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
   
//==========================================================================================================================================
//  Helper-function definitions for graphing and histogram management;
// =========================================================================================================================
void ReportAndOptimize(TFile* outfile, const std::vector<VarConfig>& vars, std::vector<EffPurityHists>& histSets,
    Long64_t nTotalType3,
    Long64_t nMatchedType3,
    Long64_t nTotalType0,
    Long64_t nTrueType0,
    TH1D* hChi2Optimization) ;



void Graphing(TFile* outfile, const std::vector<struct VarConfig>& vars,
                const std::vector<struct EffPurityHists>& histSets);


// Helper for LaTeX-formatted axis labels
TString GetFormattedAxisName(const std::string& varname);

// New helper function for consistent styling
void DrawEfficiencyPlot(TEfficiency* eff, Color_t color, Style_t marker, TCanvas* canvas);

void DrawCombinedPlot(TEfficiency* eff, TEfficiency* pur, TCanvas* canvas);

void Graphing2D(TFile* outfile, const std::vector<std::pair<std::string,std::string>>& varPairs, 
                const std::vector<EffPurityHists2D>& hists2DSets);



//==========================================================================================================================================
//  Helper-function definitions for efficiency/purity analysis;
// ==========================================================================================================================================

double GetVarValue(const std::string& varname);

bool IsInAcceptance(double eta);

int getMFTClusterCount(ULong64_t clusterSizesAndFlags);

void CalculateEfficiencyPurity(TFile* outfile);

void CreateEfficiencyPurityHistograms( TFile* outfile, const std::vector<VarConfig>& vars, std::vector<EffPurityHists>& histSets,  TH1D*& hChi2Optimization);

void CollectMatchCandidates(std::unordered_map<Long64_t, std::vector<MatchCandidate>>& matchCandidates);

void SelectBestMatches(const std::unordered_map<Long64_t, std::vector<MatchCandidate>>& matchCandidates, 
            std::unordered_map<Long64_t, const MatchCandidate*>& bestMatches);

void FillEfficiencyPurityCounts(
    const std::unordered_map<Long64_t,const MatchCandidate*>& bestMatches,
    const std::vector<VarConfig>& vars,
    std::vector<EffPurityHists>& histSets,
    const std::vector<std::pair<std::string,std::string>>& varPairs,
    const std::vector<EffPurityHists2D>& hists2DSets,
    Long64_t& nTotalType3,
    Long64_t& nMatchedType3,
    Long64_t& nTotalType0,
    Long64_t& nTrueType0);

void SetChi2Threshold(double thresh) { fChi2Threshold = thresh; };

void Create2DEffPurHists(TFile* outfile, const std::vector<std::pair<std::string,std::string>>& varPairs,
            const std::vector<VarConfig>& vars, std::vector<EffPurityHists2D>& hists2DSets);


//==========================================================================================================================================
//  Helper-function definitions for fwdtrack analysis;
// ==========================================================================================================================================

TFile* outputManagement(TFile* outputfile, bool& closeFile);


void initializeHistograms(const std::vector<std::string>& branches,
                                      int nbranches, int ntype,const int trackTypes[],
                                      std::vector<std::vector<TH1D*>>& hist);

void fillHistograms(Long64_t nentries, Long64_t& nbytes, Long64_t& nb,
                                const std::vector<std::string>& branches,int nbranches, int ntype,
                                const int trackTypes[], std::vector<std::vector<TH1D*>>& hist);

void normalizeHistograms(int nbranches, int ntype,
                                     std::vector<std::vector<TH1D*>>& hist);

void canvasManipulation(const std::vector<std::string>& branches,int nbranches, int ntype,
            const int trackTypes[],std::vector<std::vector<TH1D*>>& hist,TFile* outfile);


//==========================================================================================================================================
//==========================================================================================================================================


};

#endif
