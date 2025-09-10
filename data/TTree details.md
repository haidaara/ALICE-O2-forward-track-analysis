# AOD_file_contents

### example of the prompt discussion:
```bash
root [0] TFile* file = TFile::Open("AO2D_MC_promptJpsi_anch24.root");
root [1] file->ls()
TFile**         AO2D_MC_promptJpsi_anch24.root
 TFile*         AO2D_MC_promptJpsi_anch24.root
  KEY: TDirectoryFile   DF_2397811916393856;1   DF_2397811916393856
  KEY: TDirectoryFile   DF_2397811916393888;1   DF_2397811916393888
  KEY: TDirectoryFile   DF_2397811916393920;1   DF_2397811916393920
  KEY: TDirectoryFile   DF_2397811916393952;1   DF_2397811916393952
  KEY: TDirectoryFile   DF_2397811916393984;1   DF_2397811916393984
  KEY: TMap     metaData;1      A (key,value) map

root [8] TDirectory* dir = (TDirectory*)file->Get("DF_2397811916393856");
root [9] dir->ls()
TDirectoryFile*         DF_2397811916393856     DF_2397811916393856
 KEY: TTree     O2ambiguousfwdtr;1      O2ambiguousfwdtr
 KEY: TTree     O2ambiguousmfttr;1      O2ambiguousmfttr
 KEY: TTree     O2ambiguoustrack;1      O2ambiguoustrack
 KEY: TTree     O2bc_001;1      O2bc_001
 KEY: TTree     O2bcflag;1      O2bcflag
 KEY: TTree     O2calo;1        O2calo
 KEY: TTree     O2calotrigger;1 O2calotrigger
 KEY: TTree     O2cascade_001;1 O2cascade_001
 KEY: TTree     O2collision_001;1       O2collision_001
 KEY: TTree     O2cpvcluster;1  O2cpvcluster
 KEY: TTree     O2decay3body;1  O2decay3body
 KEY: TTree     O2fdd_001;1     O2fdd_001
 KEY: TTree     O2fddextra;1    O2fddextra
 KEY: TTree     O2ft0;1 O2ft0
 KEY: TTree     O2ft0extra;1    O2ft0extra
 KEY: TTree     O2fv0a;1        O2fv0a
 KEY: TTree     O2fv0aextra;1   O2fv0aextra
 KEY: TTree     O2fwdtrack;1    O2fwdtrack
 KEY: TTree     O2fwdtrackcov;1 O2fwdtrackcov
 KEY: TTree     O2fwdtrkcl;1    O2fwdtrkcl
 KEY: TTree     O2hepmcheavyion;1       O2hepmcheavyion
 KEY: TTree     O2hepmcpdfinfo;1        O2hepmcpdfinfo
 KEY: TTree     O2hepmcxsection;1       O2hepmcxsection
 KEY: TTree     O2hmpid_001;1   O2hmpid_001
 KEY: TTree     O2mccalolabel_001;1     O2mccalolabel_001
 KEY: TTree     O2mccollision_001;1     O2mccollision_001
 KEY: TTree     O2mccollisionlabel;1    O2mccollisionlabel
 KEY: TTree     O2mcfwdtracklabel;1     O2mcfwdtracklabel
 KEY: TTree     O2mcmfttracklabel;1     O2mcmfttracklabel
 KEY: TTree     O2mcparticle_001;1      O2mcparticle_001
 KEY: TTree     O2mctracklabel;1        O2mctracklabel
 KEY: TTree     O2mfttrack_001;1        O2mfttrack_001
 KEY: TTree     O2mfttrackcov;1 O2mfttrackcov
 KEY: TTree     O2origin;1      O2origin
 KEY: TTree     O2track_iu;1    O2track_iu
 KEY: TTree     O2trackcov_iu;1 O2trackcov_iu
 KEY: TTree     O2tracked3body;1        O2tracked3body
 KEY: TTree     O2trackedcascade;1      O2trackedcascade
 KEY: TTree     O2trackedv0;1   O2trackedv0
 KEY: TTree     O2trackextra_002;1      O2trackextra_002
 KEY: TTree     O2trackqa_003;1 O2trackqa_003
 KEY: TTree     O2v0_002;1      O2v0_002
 KEY: TTree     O2zdc_001;1     O2zdc_001
root [10]

```

# fwdtracklabelTTree:

```bash
PS C:\cern_project\muons_perf_project>
PS C:\cern_project\muons_perf_project> root -l
root [0] TFile * file = TFile::Open("AO2D_MC_promptJpsi_anch24.root")
(TFile *) 0x2465feac0d0
root [1] files-ls()
input_line_29:2:3: error: use of undeclared identifier 'files'
 (files - ls())
  ^
input_line_29:2:11: error: use of undeclared identifier 'ls'
 (files - ls())
          ^
root [2] files->ls()
input_line_31:2:3: error: use of undeclared identifier 'files'
 (files->ls())
  ^
root [3] file->ls()
TFile**         AO2D_MC_promptJpsi_anch24.root
 TFile*         AO2D_MC_promptJpsi_anch24.root
  KEY: TDirectoryFile   DF_2397811916393856;1   DF_2397811916393856
  KEY: TDirectoryFile   DF_2397811916393888;1   DF_2397811916393888
  KEY: TDirectoryFile   DF_2397811916393920;1   DF_2397811916393920
  KEY: TDirectoryFile   DF_2397811916393952;1   DF_2397811916393952
  KEY: TDirectoryFile   DF_2397811916393984;1   DF_2397811916393984
  KEY: TMap     metaData;1      A (key,value) map
root [4] DF_2397811916393856->ls()
TDirectoryFile*         DF_2397811916393856     DF_2397811916393856
 KEY: TTree     O2ambiguousfwdtr;1      O2ambiguousfwdtr
 KEY: TTree     O2ambiguousmfttr;1      O2ambiguousmfttr
 KEY: TTree     O2ambiguoustrack;1      O2ambiguoustrack
 KEY: TTree     O2bc_001;1      O2bc_001
 KEY: TTree     O2bcflag;1      O2bcflag
 KEY: TTree     O2calo;1        O2calo
 KEY: TTree     O2calotrigger;1 O2calotrigger
 KEY: TTree     O2cascade_001;1 O2cascade_001
 KEY: TTree     O2collision_001;1       O2collision_001
 KEY: TTree     O2cpvcluster;1  O2cpvcluster
 KEY: TTree     O2decay3body;1  O2decay3body
 KEY: TTree     O2fdd_001;1     O2fdd_001
 KEY: TTree     O2fddextra;1    O2fddextra
 KEY: TTree     O2ft0;1 O2ft0
 KEY: TTree     O2ft0extra;1    O2ft0extra
 KEY: TTree     O2fv0a;1        O2fv0a
 KEY: TTree     O2fv0aextra;1   O2fv0aextra
 KEY: TTree     O2fwdtrack;1    O2fwdtrack
 KEY: TTree     O2fwdtrackcov;1 O2fwdtrackcov
 KEY: TTree     O2fwdtrkcl;1    O2fwdtrkcl
 KEY: TTree     O2hepmcheavyion;1       O2hepmcheavyion
 KEY: TTree     O2hepmcpdfinfo;1        O2hepmcpdfinfo
 KEY: TTree     O2hepmcxsection;1       O2hepmcxsection
 KEY: TTree     O2hmpid_001;1   O2hmpid_001
 KEY: TTree     O2mccalolabel_001;1     O2mccalolabel_001
 KEY: TTree     O2mccollision_001;1     O2mccollision_001
 KEY: TTree     O2mccollisionlabel;1    O2mccollisionlabel
 KEY: TTree     O2mcfwdtracklabel;1     O2mcfwdtracklabel
 KEY: TTree     O2mcmfttracklabel;1     O2mcmfttracklabel
 KEY: TTree     O2mcparticle_001;1      O2mcparticle_001
 KEY: TTree     O2mctracklabel;1        O2mctracklabel
 KEY: TTree     O2mfttrack_001;1        O2mfttrack_001
 KEY: TTree     O2mfttrackcov;1 O2mfttrackcov
 KEY: TTree     O2origin;1      O2origin
 KEY: TTree     O2track_iu;1    O2track_iu
 KEY: TTree     O2trackcov_iu;1 O2trackcov_iu
 KEY: TTree     O2tracked3body;1        O2tracked3body
 KEY: TTree     O2trackedcascade;1      O2trackedcascade
 KEY: TTree     O2trackedv0;1   O2trackedv0
 KEY: TTree     O2trackextra_002;1      O2trackextra_002
 KEY: TTree     O2trackqa_003;1 O2trackqa_003
 KEY: TTree     O2v0_002;1      O2v0_002
 KEY: TTree     O2zdc_001;1     O2zdc_001
root [5] O2mcfwdtracklabel->show()
input_line_35:2:3: error: use of undeclared identifier 'O2mcfwdtracklabel'
 (O2mcfwdtracklabel->show())
  ^
root [6] dir->cd()
input_line_37:2:3: error: use of undeclared identifier 'dir'
 (dir->cd())
  ^
root [7] DF_2397811916393856->cd()
(bool) true
root [8] O2mcfwdtracklabel->show()
ROOT_prompt_8:1:20: error: no member named 'show' in 'TTree'
O2mcfwdtracklabel->show()
~~~~~~~~~~~~~~~~~  ^
root [9] O2mcfwdtracklabel->Show()
[IncrementalJIT] addModule() failed: Duplicate definition of symbol '?O2mcfwdtracklabel@__ROOT_SpecialObjects@@3PEAVTTree@@EA'
======> EVENT:-1
 fIndexMcParticles = 0
 fMcMask         = 0
root [10] O2mcfwdtracklabel->Show(0)
======> EVENT:0
 fIndexMcParticles = 1032511
 fMcMask         = 0
root [11] O2mcfwdtracklabel->Show(1)
======> EVENT:1
 fIndexMcParticles = 847340
 fMcMask         = 0
root [12] O2mcfwdtracklabel->Show(2)
======> EVENT:2
 fIndexMcParticles = 662306
 fMcMask         = 0
root [13] O2mcfwdtracklabel->Show(3)
======> EVENT:3
 fIndexMcParticles = 1286963
 fMcMask         = 0
root [14] O2mcfwdtracklabel->Show(10)
======> EVENT:10
 fIndexMcParticles = 1104767
 fMcMask         = 128
root [15] O2mcfwdtracklabel->Show(11)
======> EVENT:11
 fIndexMcParticles = 847340
 fMcMask         = 128
root [16] O2mcfwdtracklabel->Show(12)
======> EVENT:12
 fIndexMcParticles = 847340
 fMcMask         = 128
root [17] O2mcfwdtracklabel->Show(13)
======> EVENT:13
 fIndexMcParticles = 847340
 fMcMask         = 128
root [18] O2mcfwdtracklabel->Print()
******************************************************************************
*Tree    :O2mcfwdtracklabel: O2mcfwdtracklabel                                      *
*Entries :     3168 : Total =           17453 bytes  File  Size =       3608 *
*        :          : Tree compression factor =   5.10                       *
******************************************************************************
*Br    0 :fIndexMcParticles : fIndexMcParticles/I                            *
*Entries :     3168 : Total  Size=      13306 bytes  File Size  =       2586 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   4.94     *
*............................................................................*
*Br    1 :fMcMask   : fMcMask/b                                              *
*Entries :     3168 : Total  Size=       3746 bytes  File Size  =        556 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   5.85     *
*............................................................................*
root [19]

```


# fwdtrack TTree:

```bash 

root [1] TFile* file = TFile::Open("AO2D_MC_promptJpsi_anch24.root")
(TFile *) 0x2c82afd24b0
root [2] file->ls()
TFile**         AO2D_MC_promptJpsi_anch24.root
 TFile*         AO2D_MC_promptJpsi_anch24.root
  KEY: TDirectoryFile   DF_2397811916393856;1   DF_2397811916393856
  KEY: TDirectoryFile   DF_2397811916393888;1   DF_2397811916393888
  KEY: TDirectoryFile   DF_2397811916393920;1   DF_2397811916393920
  KEY: TDirectoryFile   DF_2397811916393952;1   DF_2397811916393952
  KEY: TDirectoryFile   DF_2397811916393984;1   DF_2397811916393984
  KEY: TMap     metaData;1      A (key,value) map
root [3] DF_2397811916393856->cd()
(bool) true
root [4] file->ls()
TFile**         AO2D_MC_promptJpsi_anch24.root
 TFile*         AO2D_MC_promptJpsi_anch24.root
  TDirectoryFile*               DF_2397811916393856     DF_2397811916393856
   KEY: TTree   O2ambiguousfwdtr;1      O2ambiguousfwdtr
   KEY: TTree   O2ambiguousmfttr;1      O2ambiguousmfttr
   KEY: TTree   O2ambiguoustrack;1      O2ambiguoustrack
   KEY: TTree   O2bc_001;1      O2bc_001
   KEY: TTree   O2bcflag;1      O2bcflag
   KEY: TTree   O2calo;1        O2calo
   KEY: TTree   O2calotrigger;1 O2calotrigger
   KEY: TTree   O2cascade_001;1 O2cascade_001
   KEY: TTree   O2collision_001;1       O2collision_001
   KEY: TTree   O2cpvcluster;1  O2cpvcluster
   KEY: TTree   O2decay3body;1  O2decay3body
   KEY: TTree   O2fdd_001;1     O2fdd_001
   KEY: TTree   O2fddextra;1    O2fddextra
   KEY: TTree   O2ft0;1 O2ft0
   KEY: TTree   O2ft0extra;1    O2ft0extra
   KEY: TTree   O2fv0a;1        O2fv0a
   KEY: TTree   O2fv0aextra;1   O2fv0aextra
   KEY: TTree   O2fwdtrack;1    O2fwdtrack
   KEY: TTree   O2fwdtrackcov;1 O2fwdtrackcov
   KEY: TTree   O2fwdtrkcl;1    O2fwdtrkcl
   KEY: TTree   O2hepmcheavyion;1       O2hepmcheavyion
   KEY: TTree   O2hepmcpdfinfo;1        O2hepmcpdfinfo
   KEY: TTree   O2hepmcxsection;1       O2hepmcxsection
   KEY: TTree   O2hmpid_001;1   O2hmpid_001
   KEY: TTree   O2mccalolabel_001;1     O2mccalolabel_001
   KEY: TTree   O2mccollision_001;1     O2mccollision_001
   KEY: TTree   O2mccollisionlabel;1    O2mccollisionlabel
   KEY: TTree   O2mcfwdtracklabel;1     O2mcfwdtracklabel
   KEY: TTree   O2mcmfttracklabel;1     O2mcmfttracklabel
   KEY: TTree   O2mcparticle_001;1      O2mcparticle_001
   KEY: TTree   O2mctracklabel;1        O2mctracklabel
   KEY: TTree   O2mfttrack_001;1        O2mfttrack_001
   KEY: TTree   O2mfttrackcov;1 O2mfttrackcov
   KEY: TTree   O2origin;1      O2origin
   KEY: TTree   O2track_iu;1    O2track_iu
   KEY: TTree   O2trackcov_iu;1 O2trackcov_iu
   KEY: TTree   O2tracked3body;1        O2tracked3body
   KEY: TTree   O2trackedcascade;1      O2trackedcascade
   KEY: TTree   O2trackedv0;1   O2trackedv0
   KEY: TTree   O2trackextra_002;1      O2trackextra_002
   KEY: TTree   O2trackqa_003;1 O2trackqa_003
   KEY: TTree   O2v0_002;1      O2v0_002
   KEY: TTree   O2zdc_001;1     O2zdc_001
  KEY: TDirectoryFile   DF_2397811916393856;1   DF_2397811916393856
  KEY: TDirectoryFile   DF_2397811916393888;1   DF_2397811916393888
  KEY: TDirectoryFile   DF_2397811916393920;1   DF_2397811916393920
  KEY: TDirectoryFile   DF_2397811916393952;1   DF_2397811916393952
  KEY: TDirectoryFile   DF_2397811916393984;1   DF_2397811916393984
  KEY: TMap     metaData;1      A (key,value) map
root [5] O2fwdtrack->Print()
******************************************************************************
*Tree    :O2fwdtrack: O2fwdtrack                                             *
*Entries :     3168 : Total =          257392 bytes  File  Size =     102102 *
*        :          : Tree compression factor =   2.44                       *
******************************************************************************
*Br    0 :fIndexCollisions : fIndexCollisions/I                              *
*Entries :     3168 : Total  Size=      13290 bytes  File Size  =        625 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  20.42     *
*............................................................................*
*Br    1 :fTrackType : fTrackType/b                                          *
*Entries :     3168 : Total  Size=       3750 bytes  File Size  =        423 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   7.69     *
*............................................................................*
*Br    2 :fX        : fX/F                                                   *
*Entries :     3168 : Total  Size=      13220 bytes  File Size  =      11890 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.07     *
*............................................................................*
*Br    3 :fY        : fY/F                                                   *
*Entries :     3168 : Total  Size=      13220 bytes  File Size  =      11809 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.08     *
*............................................................................*
*Br    4 :fZ        : fZ/F                                                   *
*Entries :     3168 : Total  Size=      13220 bytes  File Size  =       4227 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   3.02     *
*............................................................................*
*Br    5 :fPhi      : fPhi/F                                                 *
*Entries :     3168 : Total  Size=      13230 bytes  File Size  =      10997 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.16     *
*............................................................................*
*Br    6 :fTgl      : fTgl/F                                                 *
*Entries :     3168 : Total  Size=      13230 bytes  File Size  =       9318 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.37     *
*............................................................................*
*Br    7 :fSigned1Pt : fSigned1Pt/F                                          *
*Entries :     3168 : Total  Size=      13260 bytes  File Size  =       9412 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.36     *
*............................................................................*
*Br    8 :fNClusters : fNClusters/B                                          *
*Entries :     3168 : Total  Size=       3750 bytes  File Size  =        662 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   4.91     *
*............................................................................*
*Br    9 :fPDca     : fPDca/F                                                *
*Entries :     3168 : Total  Size=      13235 bytes  File Size  =       2938 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   4.34     *
*............................................................................*
*Br   10 :fRAtAbsorberEnd : fRAtAbsorberEnd/F                                *
*Entries :     3168 : Total  Size=      13285 bytes  File Size  =       2913 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   4.38     *
*............................................................................*
*Br   11 :fChi2     : fChi2/F                                                *
*Entries :     3168 : Total  Size=      13235 bytes  File Size  =       6833 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.87     *
*............................................................................*
*Br   12 :fChi2MatchMCHMID : fChi2MatchMCHMID/F                              *
*Entries :     3168 : Total  Size=      13290 bytes  File Size  =       2199 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   5.80     *
*............................................................................*
*Br   13 :fChi2MatchMCHMFT : fChi2MatchMCHMFT/F                              *
*Entries :     3168 : Total  Size=      13290 bytes  File Size  =       5921 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   2.16     *
*............................................................................*
*Br   14 :fMatchScoreMCHMFT : fMatchScoreMCHMFT/F                            *
*Entries :     3168 : Total  Size=      13295 bytes  File Size  =       5922 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   2.16     *
*............................................................................*
*Br   15 :fIndexMFTTracks : fIndexMFTTracks/I                                *
*Entries :     3168 : Total  Size=      13285 bytes  File Size  =       6672 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.91     *
*............................................................................*
*Br   16 :fIndexFwdTracks_MatchMCHTrack : fIndexFwdTracks_MatchMCHTrack/I    *
*Entries :     3168 : Total  Size=      13355 bytes  File Size  =       2308 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   5.53     *
*............................................................................*
*Br   17 :fMCHBitMap : fMCHBitMap/s                                          *
*Entries :     3168 : Total  Size=       6920 bytes  File Size  =        451 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  14.23     *
*............................................................................*
*Br   18 :fMIDBitMap : fMIDBitMap/b                                          *
*Entries :     3168 : Total  Size=       3750 bytes  File Size  =        563 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   5.77     *
*............................................................................*
*Br   19 :fMIDBoards : fMIDBoards/i                                          *
*Entries :     3168 : Total  Size=      13260 bytes  File Size  =       2352 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   5.42     *
*............................................................................*
*Br   20 :fTrackTime : fTrackTime/F                                          *
*Entries :     3168 : Total  Size=      13260 bytes  File Size  =       1875 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   6.80     *
*............................................................................*
*Br   21 :fTrackTimeRes : fTrackTimeRes/F                                    *
*Entries :     3168 : Total  Size=      13275 bytes  File Size  =        404 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=  31.58     *
*............................................................................*
root [6] O2fwdtrack->Show()
======> EVENT:-1
 fIndexCollisions = 0
 fTrackType      = 0
 fX              = 0
 fY              = 0
 fZ              = 0
 fPhi            = 0
 fTgl            = 0
 fSigned1Pt      = 0
 fNClusters      = 0
 fPDca           = 0
 fRAtAbsorberEnd = 0
 fChi2           = 0
 fChi2MatchMCHMID = 0
 fChi2MatchMCHMFT = 0
 fMatchScoreMCHMFT = 0
 fIndexMFTTracks = 0
 fIndexFwdTracks_MatchMCHTrack = 0
 fMCHBitMap      = 0
 fMIDBitMap      = 0
 fMIDBoards      = 0
 fTrackTime      = 0
 fTrackTimeRes   = 0
root [7] O2fwdtrack->Show(1)
======> EVENT:1
 fIndexCollisions = -1
 fTrackType      = 3
 fX              = 15.3936
 fY              = -19.385
 fZ              = -522.409
 fPhi            = -0.895863
 fTgl            = -21.7285
 fSigned1Pt      = 0.136963
 fNClusters      = 10
 fPDca           = 114.86
 fRAtAbsorberEnd = 23.9523
 fChi2           = 0.110352
 fChi2MatchMCHMID = 0.349609
 fChi2MatchMCHMFT = -1
 fMatchScoreMCHMFT = -1
 fIndexMFTTracks = -1
 fIndexFwdTracks_MatchMCHTrack = -1
 fMCHBitMap      = 1023
 fMIDBitMap      = 255
 fMIDBoards      = 50533119
 fTrackTime      = 37.4038
 fTrackTimeRes   = 12.4753
root [8] O2fwdtrack->Show(2)
======> EVENT:2
 fIndexCollisions = -1
 fTrackType      = 3
 fX              = -17.9127
 fY              = 9.51899
 fZ              = -522.409
 fPhi            = 2.64386
 fTgl            = -23.8511
 fSigned1Pt      = 0.450531
 fNClusters      = 11
 fPDca           = 85.4557
 fRAtAbsorberEnd = 19.555
 fChi2           = 0.0588379
 fChi2MatchMCHMID = 0.386719
 fChi2MatchMCHMFT = -1
 fMatchScoreMCHMFT = -1
 fIndexMFTTracks = -1
 fIndexFwdTracks_MatchMCHTrack = -1
 fMCHBitMap      = 1023
 fMIDBitMap      = 255
 fMIDBoards      = 53022975
 fTrackTime      = 37.4452
 fTrackTimeRes   = 12.4753
root [9] O2fwdtrack->Show(3)
======> EVENT:3
 fIndexCollisions = -1
 fTrackType      = 3
 fX              = -2.35123
 fY              = -22.9435
 fZ              = -529.909
 fPhi            = -1.63199
 fTgl            = -21.8525
 fSigned1Pt      = 0.697083
 fNClusters      = 10
 fPDca           = 52.7648
 fRAtAbsorberEnd = 21.9247
 fChi2           = 0.081543
 fChi2MatchMCHMID = 0.144531
 fChi2MatchMCHMFT = -1
 fMatchScoreMCHMFT = -1
 fIndexMFTTracks = -1
 fIndexFwdTracks_MatchMCHTrack = -1
 fMCHBitMap      = 1023
 fMIDBitMap      = 255
 fMIDBoards      = 52888319
 fTrackTime      = 112.279
 fTrackTimeRes   = 12.4753
root [10] O2fwdtrack->Show(50)
======> EVENT:50
 fIndexCollisions = 3
 fTrackType      = 0
 fX              = 5.47213
 fY              = -2.26133
 fZ              = -45.3501
 fPhi            = -0.40813
 fTgl            = -9.24243
 fSigned1Pt      = -0.764771
 fNClusters      = 10
 fPDca           = 62.1586
 fRAtAbsorberEnd = 67.0885
 fChi2           = 604
 fChi2MatchMCHMID = 0.886719
 fChi2MatchMCHMFT = 410
 fMatchScoreMCHMFT = 410
 fIndexMFTTracks = 86
 fIndexFwdTracks_MatchMCHTrack = 48
 fMCHBitMap      = 1023
 fMIDBitMap      = 221
 fMIDBoards      = 50553053
 fTrackTime      = 411.687
 fTrackTimeRes   = 12.4753
root [11] O2fwdtrack->Show(100)
======> EVENT:100
 fIndexCollisions = 29
 fTrackType      = 0
 fX              = -3.18538
 fY              = -1.40832
 fZ              = -45.324
 fPhi            = -2.73063
 fTgl            = -14.8477
 fSigned1Pt      = -0.543884
 fNClusters      = 10
 fPDca           = 45.6744
 fRAtAbsorberEnd = 34.6208
 fChi2           = 5.625
 fChi2MatchMCHMID = 0.847656
 fChi2MatchMCHMFT = 2.70312
 fMatchScoreMCHMFT = 2.70312
 fIndexMFTTracks = 406
 fIndexFwdTracks_MatchMCHTrack = 96
 fMCHBitMap      = 1023
 fMIDBitMap      = 255
 fMIDBoards      = 52896255
 fTrackTime      = 212.082
 fTrackTimeRes   = 12.4753
root [12]
```
# mcparticle_TTree

```bash
root [10] TDirectory* dir = (TDirectory*)file->get("DF_2397811916393856")
ROOT_prompt_10:1:38: error: no member named 'get' in 'TFile'
TDirectory* dir = (TDirectory*)file->get("DF_2397811916393856")
                               ~~~~  ^
root [11] TDirectory* dir = (TDirectory*)file->Get("DF_2397811916393856")
(TDirectory *) 0x1d14463daa0
root [12] dir->ls()
TDirectoryFile*         DF_2397811916393856     DF_2397811916393856
 KEY: TTree     O2ambiguousfwdtr;1      O2ambiguousfwdtr
 KEY: TTree     O2ambiguousmfttr;1      O2ambiguousmfttr
 KEY: TTree     O2ambiguoustrack;1      O2ambiguoustrack
 KEY: TTree     O2bc_001;1      O2bc_001
 KEY: TTree     O2bcflag;1      O2bcflag
 KEY: TTree     O2calo;1        O2calo
 KEY: TTree     O2calotrigger;1 O2calotrigger
 KEY: TTree     O2cascade_001;1 O2cascade_001
 KEY: TTree     O2collision_001;1       O2collision_001
 KEY: TTree     O2cpvcluster;1  O2cpvcluster
 KEY: TTree     O2decay3body;1  O2decay3body
 KEY: TTree     O2fdd_001;1     O2fdd_001
 KEY: TTree     O2fddextra;1    O2fddextra
 KEY: TTree     O2ft0;1 O2ft0
 KEY: TTree     O2ft0extra;1    O2ft0extra
 KEY: TTree     O2fv0a;1        O2fv0a
 KEY: TTree     O2fv0aextra;1   O2fv0aextra
 KEY: TTree     O2fwdtrack;1    O2fwdtrack
 KEY: TTree     O2fwdtrackcov;1 O2fwdtrackcov
 KEY: TTree     O2fwdtrkcl;1    O2fwdtrkcl
 KEY: TTree     O2hepmcheavyion;1       O2hepmcheavyion
 KEY: TTree     O2hepmcpdfinfo;1        O2hepmcpdfinfo
 KEY: TTree     O2hepmcxsection;1       O2hepmcxsection
 KEY: TTree     O2hmpid_001;1   O2hmpid_001
 KEY: TTree     O2mccalolabel_001;1     O2mccalolabel_001
 KEY: TTree     O2mccollision_001;1     O2mccollision_001
 KEY: TTree     O2mccollisionlabel;1    O2mccollisionlabel
 KEY: TTree     O2mcfwdtracklabel;1     O2mcfwdtracklabel
 KEY: TTree     O2mcmfttracklabel;1     O2mcmfttracklabel
 KEY: TTree     O2mcparticle_001;1      O2mcparticle_001
 KEY: TTree     O2mctracklabel;1        O2mctracklabel
 KEY: TTree     O2mfttrack_001;1        O2mfttrack_001
 KEY: TTree     O2mfttrackcov;1 O2mfttrackcov
 KEY: TTree     O2origin;1      O2origin
 KEY: TTree     O2track_iu;1    O2track_iu
 KEY: TTree     O2trackcov_iu;1 O2trackcov_iu
 KEY: TTree     O2tracked3body;1        O2tracked3body
 KEY: TTree     O2trackedcascade;1      O2trackedcascade
 KEY: TTree     O2trackedv0;1   O2trackedv0
 KEY: TTree     O2trackextra_002;1      O2trackextra_002
 KEY: TTree     O2trackqa_003;1 O2trackqa_003
 KEY: TTree     O2v0_002;1      O2v0_002
 KEY: TTree     O2zdc_001;1     O2zdc_001
root [13] dir->cd()
(bool) true
root [20] O2mcparticle_001->Show()
======> EVENT:-1
 fIndexMcCollisions = 0
 fPdgCode        = 0
 fStatusCode     = 0
 fFlags          = 0
 fIndexArray_Mothers_size = 0
 fIndexSlice_Daughters = 0,
                  3473455
 fWeight         = 0
 fPx             = 0
 fPy             = 0
 fPz             = 0
 fE              = 0
 fVx             = 0
 fVy             = 0
 fVz             = 0
 fVt             = 0
root [21] O2mcparticle_001->Show(1)
======> EVENT:1
 fIndexMcCollisions = 0
 fPdgCode        = 2212
 fStatusCode     = -1610094588
 fFlags          = 2
 fIndexArray_Mothers_size = 0
 fIndexSlice_Daughters = 2,
                  373
 fWeight         = 1
 fPx             = 0
 fPy             = 0
 fPz             = -6800
 fE              = 6800
 fVx             = -0.0506766
 fVy             = -0.0481419
 fVz             = -6.61708
 fVt             = 0
root [22] O2mcparticle_001->Show(2)
======> EVENT:2
 fIndexMcCollisions = 0
 fPdgCode        = 443
 fStatusCode     = -1610612725
 fFlags          = 2
 fIndexArray_Mothers_size = 2
 fIndexArray_Mothers = 0,
                  1
 fIndexSlice_Daughters = 1159,
                  1160
 fWeight         = 1
 fPx             = 0.520601
 fPy             = -5.87624
 fPz             = -242.838
 fE              = 242.929
 fVx             = -0.0506766
 fVy             = -0.0481419
 fVz             = -6.61708
 fVt             = 0
root [23] O2mcparticle_001->Show(3)
======> EVENT:3
 fIndexMcCollisions = 0
 fPdgCode        = 211
 fStatusCode     = -1610570239
 fFlags          = 6
 fIndexArray_Mothers_size = 2
 fIndexArray_Mothers = 0,
                  1
 fIndexSlice_Daughters = 1323,
                  1324
 fWeight         = 1
 fPx             = -0.480938
 fPy             = -0.195271
 fPz             = 69.4425
 fE              = 69.4446
 fVx             = -0.0506766
 fVy             = -0.0481419
 fVz             = -6.61708
 fVt             = 0
root [24] O2mcparticle_001->Print()
******************************************************************************
*Tree    :O2mcparticle_001: O2mcparticle_001                                       *
*Entries :  1889231 : Total =       132959168 bytes  File  Size =   55700579 *
*        :          : Tree compression factor =   2.39                       *
******************************************************************************
*Br    0 :fIndexMcCollisions : fIndexMcCollisions/I                          *
*Entries :  1889231 : Total  Size=    7557562 bytes  File Size  =       6587 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression= 1147.26     *
*............................................................................*
*Br    1 :fPdgCode  : fPdgCode/I                                             *
*Entries :  1889231 : Total  Size=    7557512 bytes  File Size  =    1143441 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   6.61     *
*............................................................................*
*Br    2 :fStatusCode : fStatusCode/I                                        *
*Entries :  1889231 : Total  Size=    7557527 bytes  File Size  =     623968 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=  12.11     *
*............................................................................*
*Br    3 :fFlags    : fFlags/b                                               *
*Entries :  1889231 : Total  Size=    1889803 bytes  File Size  =     105492 *
*Baskets :        1 : Basket Size=    1890255 bytes  Compression=  17.91     *
*............................................................................*
*Br    4 :fIndexArray_Mothers_size : fIndexArray_Mothers_size/I              *
*Entries :  1889231 : Total  Size=    7557592 bytes  File Size  =      15490 *
*Baskets :        1 : Basket Size=   15114872 bytes  Compression= 487.86     *
*............................................................................*
*Br    5 :fIndexArray_Mothers :                                              *
*         | fIndexArray_Mothers[fIndexArray_Mothers_size]/I                  *
*Entries :  1889231 : Total  Size=   17706901 bytes  File Size  =    6779214 *
*Baskets :        2 : Basket Size=   15114872 bytes  Compression=   2.61     *
*............................................................................*
*Br    6 :fIndexSlice_Daughters : fIndexSlice_Daughters[2]/I                 *
*Entries :  1889231 : Total  Size=   15114507 bytes  File Size  =    4665002 *
*Baskets :        1 : Basket Size=   15114872 bytes  Compression=   3.24     *
*............................................................................*
*Br    7 :fWeight   : fWeight/F                                              *
*Entries :  1889231 : Total  Size=    7557507 bytes  File Size  =        747 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression= 10116.48     *
*............................................................................*
*Br    8 :fPx       : fPx/F                                                  *
*Entries :  1889231 : Total  Size=    7557487 bytes  File Size  =    6777624 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   1.11     *
*............................................................................*
*Br    9 :fPy       : fPy/F                                                  *
*Entries :  1889231 : Total  Size=    7557487 bytes  File Size  =    6777906 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   1.11     *
*............................................................................*
*Br   10 :fPz       : fPz/F                                                  *
*Entries :  1889231 : Total  Size=    7557487 bytes  File Size  =    6848243 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   1.10     *
*............................................................................*
*Br   11 :fE        : fE/F                                                   *
*Entries :  1889231 : Total  Size=    7557482 bytes  File Size  =    6552742 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   1.15     *
*............................................................................*
*Br   12 :fVx       : fVx/F                                                  *
*Entries :  1889231 : Total  Size=    7557487 bytes  File Size  =    3785789 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   2.00     *
*............................................................................*
*Br   13 :fVy       : fVy/F                                                  *
*Entries :  1889231 : Total  Size=    7557487 bytes  File Size  =    3787570 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   2.00     *
*............................................................................*
*Br   14 :fVz       : fVz/F                                                  *
*Entries :  1889231 : Total  Size=    7557487 bytes  File Size  =    3768904 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   2.01     *
*............................................................................*
*Br   15 :fVt       : fVt/F                                                  *
*Entries :  1889231 : Total  Size=    7557487 bytes  File Size  =    4060644 *
*Baskets :        1 : Basket Size=    7557948 bytes  Compression=   1.86     *
*............................................................................*
root [25]

```




