```root [3] TFile* file = TFile::Open("AO2D_MC_promptJpsi_anch24_merged.root")
(TFile *) 0x625cf62b7020
root [4] file->ls()
TFile**         AO2D_MC_promptJpsi_anch24_merged.root
 TFile*         AO2D_MC_promptJpsi_anch24_merged.root
  KEY: TDirectoryFile   DF_2397811916393856;1   DF_2397811916393856
  KEY: TMap     metaData;1      A (key,value) map
root [5] DF_2397811916393856->cd()
(bool) true
root [6] file->ls()
TFile**         AO2D_MC_promptJpsi_anch24_merged.root
 TFile*         AO2D_MC_promptJpsi_anch24_merged.root
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
  KEY: TMap     metaData;1      A (key,value) map
root [7] O2mfttrack_001->Print()
******************************************************************************
*Tree    :O2mfttrack_001: O2mfttrack_001                                         *
*Entries :   108041 : Total =         5196640 bytes  File  Size =    2603556 *
*        :          : Tree compression factor =   1.99                       *
******************************************************************************
*Br    0 :fIndexCollisions : fIndexCollisions/I                              *
*Entries :   108041 : Total  Size=     433158 bytes  File Size  =       6368 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=  67.94     *
*............................................................................*
*Br    1 :fX        : fX/F                                                   *
*Entries :   108041 : Total  Size=     433032 bytes  File Size  =     397774 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   1.09     *
*............................................................................*
*Br    2 :fY        : fY/F                                                   *
*Entries :   108041 : Total  Size=     433032 bytes  File Size  =     395226 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   1.09     *
*............................................................................*
*Br    3 :fZ        : fZ/F                                                   *
*Entries :   108041 : Total  Size=     433032 bytes  File Size  =     146276 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   2.96     *
*............................................................................*
*Br    4 :fPhi      : fPhi/F                                                 *
*Entries :   108041 : Total  Size=     433050 bytes  File Size  =     369398 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   1.17     *
*............................................................................*
*Br    5 :fTgl      : fTgl/F                                                 *
*Entries :   108041 : Total  Size=     433050 bytes  File Size  =     302055 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   1.43     *
*............................................................................*
*Br    6 :fSigned1Pt : fSigned1Pt/F                                          *
*Entries :   108041 : Total  Size=     433104 bytes  File Size  =     310551 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   1.39     *
*............................................................................*
*Br    7 :fMFTClusterSizesAndTrackFlags : fMFTClusterSizesAndTrackFlags/l    *
*Entries :   108041 : Total  Size=     865447 bytes  File Size  =     487250 *
*Baskets :        5 : Basket Size=     173296 bytes  Compression=   1.77     *
*............................................................................*
*Br    8 :fChi2     : fChi2/F                                                *
*Entries :   108041 : Total  Size=     433059 bytes  File Size  =     172452 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   2.51     *
*............................................................................*
*Br    9 :fTrackTime : fTrackTime/F                                          *
*Entries :   108041 : Total  Size=     433104 bytes  File Size  =      14298 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=  30.26     *
*............................................................................*
*Br   10 :fTrackTimeRes : fTrackTimeRes/F                                    *
*Entries :   108041 : Total  Size=     433131 bytes  File Size  =        615 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression= 703.44     *
*............................................................................*

O2mfttrack_001->show(0)
~~~~~~~~~~~~~~  ^
root [9] O2mfttrack_001->Show(0)
======> EVENT:0
 fIndexCollisions = -1
 fX              = -0.397844
 fY              = 4.10788
 fZ              = -45.3427
 fPhi            = 1.66471
 fTgl            = -11.1716
 fSigned1Pt      = -1.19482
 fMFTClusterSizesAndTrackFlags = 72066396574974084
 fChi2           = 4.5
 fTrackTime      = -2145.75
 fTrackTimeRes   = 2470.12
root [10] O2mfttrack_001->Show(1)
======> EVENT:1
 fIndexCollisions = -1
 fX              = -3.55252
 fY              = 3.4014
 fZ              = -45.3449
 fPhi            = 2.35321
 fTgl            = -10.0022
 fSigned1Pt      = 3.81934
 fMFTClusterSizesAndTrackFlags = 72070995410694339
 fChi2           = 2.90625
 fTrackTime      = -2145.75
 fTrackTimeRes   = 2470.12
root [11] O2mfttrack_001->Show(2)
======> EVENT:2
 fIndexCollisions = -1
 fX              = 3.54477
 fY              = -5.83217
 fZ              = -45.3403
 fPhi            = -1.01808
 fTgl            = -6.78882
 fSigned1Pt      = 1.92822
 fMFTClusterSizesAndTrackFlags = 109238889696997508
 fChi2           = 5
 fTrackTime      = -2145.75
 fTrackTimeRes   = 2470.12
root [12] O2mfttrack_001->Show(3)
======> EVENT:3
 fIndexCollisions = -1
 fX              = -4.19459
 fY              = 2.21909
 fZ              = -45.3346
 fPhi            = 2.60919
 fTgl            = -9.9209
 fSigned1Pt      = 5.37354
 fMFTClusterSizesAndTrackFlags = 55169372594913539
 fChi2           = 6.96875
 fTrackTime      = -2145.75
 fTrackTimeRes   = 2470.12
root [13] O2mfttrack_001->Show(4)
======> EVENT:4
 fIndexCollisions = -1
 fX              = -2.04179
 fY              = -2.32439
 fZ              = -45.3182
 fPhi            = -2.3165
 fTgl            = -15.0105
 fSigned1Pt      = 11.584
 fMFTClusterSizesAndTrackFlags = 74045785972424707
 fChi2           = 3.29688
 fTrackTime      = -2145.75
 fTrackTimeRes   = 2470.12
root [14] O2mfttrackcov->Print()
******************************************************************************
*Tree    :O2mfttrackcov: O2mfttrackcov                                          *
*Entries :    14126 : Total =          490554 bytes  File  Size =     337122 *
*        :          : Tree compression factor =   1.43                       *
******************************************************************************
*Br    0 :fIndexMFTTracks : fIndexMFTTracks/I                                *
*Entries :    14126 : Total  Size=      57211 bytes  File Size  =      35616 *
*Baskets :        2 : Basket Size=      32000 bytes  Compression=   1.59     *
*............................................................................*
*Br    1 :fSigmaX   : fSigmaX/F                                              *
*Entries :    14126 : Total  Size=      57163 bytes  File Size  =      37727 *
*Baskets :        2 : Basket Size=      32000 bytes  Compression=   1.50     *
*............................................................................*
*Br    2 :fSigmaY   : fSigmaY/F                                              *
*Entries :    14126 : Total  Size=      57163 bytes  File Size  =      37724 *
*Baskets :        2 : Basket Size=      32000 bytes  Compression=   1.50     *
*............................................................................*
*Br    3 :fSigmaPhi : fSigmaPhi/F                                            *
*Entries :    14126 : Total  Size=      57175 bytes  File Size  =      39955 *
*Baskets :        2 : Basket Size=      32000 bytes  Compression=   1.42     *
*............................................................................*
*Br    4 :fSigmaTgl : fSigmaTgl/F                                            *
*Entries :    14126 : Total  Size=      57175 bytes  File Size  =      40515 *
*Baskets :        2 : Basket Size=      32000 bytes  Compression=   1.40     *
*............................................................................*
*Br    5 :fSigma1Pt : fSigma1Pt/F                                            *
*Entries :    14126 : Total  Size=      57175 bytes  File Size  =      40002 *
*Baskets :        2 : Basket Size=      32000 bytes  Compression=   1.42     *
*............................................................................*
*Br    6 :fRhoXY    : fRhoXY/B                                               *
*Entries :    14126 : Total  Size=      14691 bytes  File Size  =       4812 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   2.95     *
*............................................................................*
*Br    7 :fRhoPhiX  : fRhoPhiX/B                                             *
*Entries :    14126 : Total  Size=      14701 bytes  File Size  =      13660 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.04     *
*............................................................................*
*Br    8 :fRhoPhiY  : fRhoPhiY/B                                             *
*Entries :    14126 : Total  Size=      14701 bytes  File Size  =      14210 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    9 :fRhoTglX  : fRhoTglX/B                                             *
*Entries :    14126 : Total  Size=      14701 bytes  File Size  =      13696 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.04     *
*............................................................................*
*Br   10 :fRhoTglY  : fRhoTglY/B                                             *
*Entries :    14126 : Total  Size=      14701 bytes  File Size  =      13695 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.04     *
*............................................................................*
*Br   11 :fRhoTglPhi : fRhoTglPhi/B                                          *
*Entries :    14126 : Total  Size=      14711 bytes  File Size  =       9022 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.58     *
*............................................................................*
*Br   12 :fRho1PtX  : fRho1PtX/B                                             *
*Entries :    14126 : Total  Size=      14701 bytes  File Size  =      10369 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.37     *
*............................................................................*
*Br   13 :fRho1PtY  : fRho1PtY/B                                             *
*Entries :    14126 : Total  Size=      14701 bytes  File Size  =      10235 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.39     *
*............................................................................*
*Br   14 :fRho1PtPhi : fRho1PtPhi/B                                          *
*Entries :    14126 : Total  Size=      14711 bytes  File Size  =      10818 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   1.31     *
*............................................................................*
*Br   15 :fRho1PtTgl : fRho1PtTgl/B                                          *
*Entries :    14126 : Total  Size=      14711 bytes  File Size  =       4020 *
*Baskets :        1 : Basket Size=      32000 bytes  Compression=   3.54     *
*............................................................................*
root [15] O2mfttrackcov->Show()
======> EVENT:-1
 fIndexMFTTracks = 0
 fSigmaX         = 0
 fSigmaY         = 0
 fSigmaPhi       = 0
 fSigmaTgl       = 0
 fSigma1Pt       = 0
 fRhoXY          = 0
 fRhoPhiX        = 0
 fRhoPhiY        = 0
 fRhoTglX        = 0
 fRhoTglY        = 0
 fRhoTglPhi      = 0
 fRho1PtX        = 0
 fRho1PtY        = 0
 fRho1PtPhi      = 0
 fRho1PtTgl      = 0
root [16] O2mfttrackcov->Show(0)
======> EVENT:0
 fIndexMFTTracks = 12489
 fSigmaX         = 0.000461996
 fSigmaY         = 0.000515953
 fSigmaPhi       = 0.00258219
 fSigmaTgl       = 0.0364752
 fSigma1Pt       = 1.40381
 fRhoXY          = -1
 fRhoPhiX        = -58
 fRhoPhiY        = 69
 fRhoTglX        = 69
 fRhoTglY        = 57
 fRhoTglPhi      = 6
 fRho1PtX        = -11
 fRho1PtY        = 13
 fRho1PtPhi      = 34
 fRho1PtTgl      = 1
root [17] O2mfttrackcov->Show(1)
======> EVENT:1
 fIndexMFTTracks = 12490
 fSigmaX         = 0.000514537
 fSigmaY         = 0.000554189
 fSigmaPhi       = 0.00314081
 fSigmaTgl       = 0.0424585
 fSigma1Pt       = 2.40137
 fRhoXY          = 0
 fRhoPhiX        = -66
 fRhoPhiY        = 70
 fRhoTglX        = 70
 fRhoTglY        = 66
 fRhoTglPhi      = -6
 fRho1PtX        = -4
 fRho1PtY        = 4
 fRho1PtPhi      = 24
 fRho1PtTgl      = 0
root [18] O2mfttrackcov->Show(2)
======> EVENT:2
 fIndexMFTTracks = 8210
 fSigmaX         = 0.0004289
 fSigmaY         = 0.000467055
 fSigmaPhi       = 0.00111583
 fSigmaTgl       = 0.00726819
 fSigma1Pt       = 0.3302
 fRhoXY          = -1
 fRhoPhiX        = 33
 fRhoPhiY        = -68
 fRhoTglX        = -65
 fRhoTglY        = -33
 fRhoTglPhi      = 3
 fRho1PtX        = 9
 fRho1PtY        = -20
 fRho1PtPhi      = 26
 fRho1PtTgl      = 1
root [19] O2mfttrackcov->Show(3)
======> EVENT:3
 fIndexMFTTracks = 12553
 fSigmaX         = 0.000349529
 fSigmaY         = 0.000377037
 fSigmaPhi       = 0.000978321
 fSigmaTgl       = 0.00802708
 fSigma1Pt       = 0.597412
 fRhoXY          = -5
 fRhoPhiX        = -88
 fRhoPhiY        = 16
 fRhoTglX        = 9
 fRhoTglY        = 74
 fRhoTglPhi      = 1
 fRho1PtX        = -67
 fRho1PtY        = 11
 fRho1PtPhi      = 111
 fRho1PtTgl      = 0
root [20] O2mcmfttracklabel->Print()
******************************************************************************
*Tree    :O2mcmfttracklabel: O2mcmfttracklabel                                      *
*Entries :   108041 : Total =          542459 bytes  File  Size =     358319 *
*        :          : Tree compression factor =   1.51                       *
******************************************************************************
*Br    0 :fIndexMcParticles : fIndexMcParticles/I                            *
*Entries :   108041 : Total  Size=     433182 bytes  File Size  =     351990 *
*Baskets :        5 : Basket Size=      87160 bytes  Compression=   1.23     *
*............................................................................*
*Br    1 :fMcMask   : fMcMask/b                                              *
*Entries :   108041 : Total  Size=     108876 bytes  File Size  =       5740 *
*Baskets :        4 : Basket Size=      32000 bytes  Compression=  18.88     *
*............................................................................*
root [21] O2mcmfttracklabel->Show()
======> EVENT:-1
 fIndexMcParticles = 0
 fMcMask         = 0
root [22] O2mcmfttracklabel->Show(0)
======> EVENT:0
 fIndexMcParticles = 1879328
 fMcMask         = 0
root [23] O2mcmfttracklabel->Show(1)
======> EVENT:1
 fIndexMcParticles = 1879005
 fMcMask         = 0
root [24] O2mcmfttracklabel->Show(2)
======> EVENT:2
 fIndexMcParticles = 1879448
 fMcMask         = 0
root [25] O2mcmfttracklabel->Show(3)
======> EVENT:3
 fIndexMcParticles = 1879689
 fMcMask         = 0
root [26] O2mcmfttracklabel->Show(4)
======> EVENT:4
 fIndexMcParticles = 1879513
 fMcMask         = 0
root [27] O2mcmfttracklabel->Show(50)
======> EVENT:50
 fIndexMcParticles = 9865
 fMcMask         = 0
root [28]bash




```