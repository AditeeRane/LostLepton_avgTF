#define Prediction_cxx

#include "Prediction.h"
#include <TH2.h>
#include "TGraphAsymmErrors.h"
#include <TStyle.h>
#include <iostream>

void Prediction::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

}

void Prediction::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  std::cout<<"***Prediction::SlaveBegin***"<<std::endl;  

  SearchBins_ = new SearchBins(false);
  SearchBinsQCD_ = new SearchBins(true);
  SearchBins_BTags_ = new SearchBins(false);
  SearchBinsQCD_BTags_ = new SearchBins(true);

  bTagBins = {0, 0, 0, 0};
  bTagBinsQCD = {0, 0, 0, 0};

  // Initialize Histograms
  TH1::SetDefaultSumw2();
  unsigned nSB = SearchBins_->GetNbins();
  Float_t MHTbins[5]= { 300, 350, 600, 850, 2000 };
  Float_t Nbtagbins[5]= { 0, 1, 2, 3, 20 };

  h_Prediction = new TH1D("h_Prediction", "h_Prediction", nSB, 0.5, nSB+0.5);
  h_CSStat = new TH1D("h_CSStat", "h_CSStat", nSB, 0.5, nSB+0.5);
  h_CSStat_MHTVsNbjet=new TH2D("h_CSStat_MHTVsNbjet","h_CSStat_MHTVsNbjet",4,MHTbins,4,Nbtagbins);
  h_Prediction_MHTVsNbjet=new TH2D("h_Prediction_MHTVsNbjet","h_Prediction_MHTVsNbjet",4,MHTbins,4,Nbtagbins);

  h_CutFlow = new TH1D("h_CutFlow", "h_CutFlow", 30, 0, 30);
  h_CutFlow->GetXaxis()->SetBinLabel(1,"all");
  h_CutFlow->GetXaxis()->SetBinLabel(2,"HTgen_cut");
  if(GetSignalRegHists)
    h_CutFlow->GetXaxis()->SetBinLabel(3,"0L");
  else
    h_CutFlow->GetXaxis()->SetBinLabel(3,"1L");
  h_CutFlow->GetXaxis()->SetBinLabel(4,"Base-HT,MHT,NJet");
  h_CutFlow->GetXaxis()->SetBinLabel(5,"Base-dPhi");
  h_CutFlow->GetXaxis()->SetBinLabel(6,"HBHENoise");
  h_CutFlow->GetXaxis()->SetBinLabel(7,"HBHEIsoNoise");
  h_CutFlow->GetXaxis()->SetBinLabel(8,"EcalDeadCell");
  h_CutFlow->GetXaxis()->SetBinLabel(9,"BadPFMuon");
  h_CutFlow->GetXaxis()->SetBinLabel(10,"globalSuperTightHalo");
  h_CutFlow->GetXaxis()->SetBinLabel(11,"JetID");
  h_CutFlow->GetXaxis()->SetBinLabel(12,"PFCaloMETRatio");
  h_CutFlow->GetXaxis()->SetBinLabel(13,"BadMuonJet");
  h_CutFlow->GetXaxis()->SetBinLabel(14,"BadJet");
  if(GetSignalRegHists)
    h_CutFlow->GetXaxis()->SetBinLabel(15,"NoIsoTrack");
  else
    h_CutFlow->GetXaxis()->SetBinLabel(15,"MT-cut");
  h_CutFlow->GetXaxis()->SetBinLabel(16,"QCDBin");
  h_CutFlow->GetXaxis()->SetBinLabel(17,"NegWt");
  h_CutFlow->GetXaxis()->SetBinLabel(18,"madHT");
  h_CutFlow->GetXaxis()->SetBinLabel(19,"1e");
  h_CutFlow->GetXaxis()->SetBinLabel(20,"1mu");
  h_CutFlow->GetXaxis()->SetBinLabel(21,"1L-gen");
  h_CutFlow->GetXaxis()->SetBinLabel(22,"Hadtaus");
  h_CutFlow->GetXaxis()->SetBinLabel(23,"ecalBadCalibReduced");
  h_CutFlow->GetXaxis()->SetBinLabel(24,"ecalBadCalibReducedExtra");
  h_CutFlow->GetXaxis()->SetBinLabel(25,"eeBadSc");
  h_CutFlow->GetXaxis()->SetBinLabel(26,"Nvtx");
  h_CutFlow->GetXaxis()->SetBinLabel(27,"HTMHTNJetOrg"); 
  h_YieldCutFlow = new TH1D("h_YieldCutFlow", "h_YieldCutFlow", 2, 0, 2);

  h_HT_Exp =new TH1D("h_HT_Exp","h_HT_Exp",12,100,2500);
  h_HT5_Exp =new TH1D("h_HT5_Exp","h_HT5_Exp",12,100,2500);
  h_HTRatio_Exp =new TH1D("h_HTRatio_Exp","h_HTRatio_Exp",20,0,5);
  h_MHT_Exp =new TH1D("h_MHT_Exp","h_MHT_Exp",16,200,1000);
  h_MET_Exp =new TH1D("h_MET_Exp","h_MET_Exp",16,200,1000);
  h_MHTPhi_Exp=new TH1D("h_MHTPhi_Exp","h_MHTPhi_Exp",7,-3.5,3.5);
  h_METPhi_Exp=new TH1D("h_METPhi_Exp","h_METPhi_Exp",7,-3.5,3.5);
  h_mT_Exp=new TH1D("h_mT_Exp","h_mT_Exp",20,0,100);
  h_NJet_Exp =new TH1D("h_NJet_Exp","h_NJet_Exp",10,2,12);
  h_NBtag_Exp =new TH1D("h_NBtag_Exp","h_NBtag_Exp",5,0,5);

  h_DphiOne_Exp =new TH1D("h_DphiOne_Exp","h_DphiOne_Exp",32,0,3.2);
  h_DphiTwo_Exp =new TH1D("h_DphiTwo_Exp","h_DphiTwo_Exp",32,0,3.2);
  h_DphiThree_Exp =new TH1D("h_DphiThree_Exp","h_DphiThree_Exp",32,0,3.2);
  h_DphiFour_Exp =new TH1D("h_DphiFour_Exp","h_DphiFour_Exp",32,0,3.2);
  h_LepPt_Exp=new TH1D("h_LepPt_Exp","h_LepPt_Exp",20,0.0,1000.0);
  h_LepEta_Exp=new TH1D("h_LepEta_Exp","h_LepEta_Exp",10,-2.5,2.5);
  h_LepEtafor50_Exp=new TH1D("h_LepEtafor50_Exp","h_LepEtafor50_Exp",10,-2.5,2.5);
  h_LepEtafor100_Exp=new TH1D("h_LepEtafor100_Exp","h_LepEtafor100_Exp",10,-2.5,2.5);
  h_LepEtafor200_Exp=new TH1D("h_LepEtafor200_Exp","h_LepEtafor200_Exp",10,-2.5,2.5);


  h_LepPhi_Exp=new TH1D("h_LepPhi_Exp","h_LepPhi_Exp",7,-3.5,3.5);

  h_ElePt_Exp=new TH1D("h_ElePt_Exp","h_ElePt_Exp",20,0.0,1000.0);
  h_EleEta_Exp=new TH1D("h_EleEta_Exp","h_EleEta_Exp",10,-2.5,2.5);
  h_ElePhi_Exp=new TH1D("h_ElePhi_Exp","h_ElePhi_Exp",7,-3.5,3.5);

  h_EleEtavsPt_Exp=new TH2D("h_EleEtavsPt_Exp","h_EleEtavsPt_Exp",28,-3.5,3.5,20,0.0,1000.0);
  h_EleEtavsPhi_Exp=new TH2D("h_EleEtavsPhi_Exp","h_EleEtavsPhi_Exp",28,-3.5,3.5,7,-3.5,3.5);
  h_EleEtavsMT_Exp=new TH2D("h_EleEtavsMT_Exp","h_EleEtavsMT_Exp",28,-3.5,3.5,20,0,100);
  h_EleEtavsHT_Exp=new TH2D("h_EleEtavsHT_Exp","h_EleEtavsHT_Exp",28,-3.5,3.5,12,100,2500);
  h_EleEtavsMHT_Exp=new TH2D("h_EleEtavsMHT_Exp","h_EleEtavsMHT_Exp",28,-3.5,3.5,16,200,1000);
  h_EleEtavsNJet_Exp=new TH2D("h_EleEtavsNJet_Exp","h_EleEtavsNJet_Exp",28,-3.5,3.5,10,2,12);
  h_EleEtavsNBtag_Exp=new TH2D("h_EleEtavsNBtag_Exp","h_EleEtavsNBtag_Exp",28,-3.5,3.5,5,0,5);
  h_EleMTvsPt_Exp=new TH2D("h_EleMTvsPt_Exp","h_EleMTvsPt_Exp",20,0,100,20,0.0,1000.0);
  h_EleMTvsMET_Exp=new TH2D("h_EleMTvsMET_Exp","h_EleMTvsMET_Exp",20,0,100,16,200,1000);
  h_EleMTvsDphi_Exp=new TH2D("h_EleMTvsDphi_Exp","h_EleMTvsDphi_Exp",20,0,100,14,0,3.5);

  h_HEMEleEtavsPt_Exp=new TH2D("h_HEMEleEtavsPt_Exp","h_HEMEleEtavsPt_Exp",28,-3.5,3.5,20,0.0,1000.0);
  h_HEMEleEtavsPhi_Exp=new TH2D("h_HEMEleEtavsPhi_Exp","h_HEMEleEtavsPhi_Exp",28,-3.5,3.5,7,-3.5,3.5);
  h_HEMEleEtavsMT_Exp=new TH2D("h_HEMEleEtavsMT_Exp","h_HEMEleEtavsMT_Exp",28,-3.5,3.5,20,0,100);
  h_HEMEleEtavsHT_Exp=new TH2D("h_HEMEleEtavsHT_Exp","h_HEMEleEtavsHT_Exp",28,-3.5,3.5,12,100,2500);
  h_HEMEleEtavsMHT_Exp=new TH2D("h_HEMEleEtavsMHT_Exp","h_HEMEleEtavsMHT_Exp",28,-3.5,3.5,16,200,1000);
  h_HEMEleEtavsNJet_Exp=new TH2D("h_HEMEleEtavsNJet_Exp","h_HEMEleEtavsNJet_Exp",28,-3.5,3.5,10,2,12);
  h_HEMEleEtavsNBtag_Exp=new TH2D("h_HEMEleEtavsNBtag_Exp","h_HEMEleEtavsNBtag_Exp",28,-3.5,3.5,5,0,5);
  h_HEMEleMTvsPt_Exp=new TH2D("h_HEMEleMTvsPt_Exp","h_HEMEleMTvsPt_Exp",20,0,100,20,0.0,1000.0);
  h_HEMEleMTvsMET_Exp=new TH2D("h_HEMEleMTvsMET_Exp","h_HEMEleMTvsMET_Exp",20,0,100,16,200,1000);
  h_HEMEleMTvsDphi_Exp=new TH2D("h_HEMEleMTvsDphi_Exp","h_HEMEleMTvsDphi_Exp",20,0,100,14,0,3.5);

  h_MuPt_Exp=new TH1D("h_MuPt_Exp","h_MuPt_Exp",20,0.0,1000.0);
  h_MuEta_Exp=new TH1D("h_MuEta_Exp","h_MuEta_Exp",10,-2.5,2.5);
  h_MuPhi_Exp=new TH1D("h_MuPhi_Exp","h_MuPhi_Exp",7,-3.5,3.5);

  h_rawJetPtforHT_Exp=new TH1D("h_rawJetPtforHT_Exp","h_rawJetPtforHT_Exp",20,0.0,1000.0);
  h_JetPtforHTLead_Exp=new TH1D("h_JetPtforHTLead_Exp","h_JetPtforHTLead_Exp",20,0.0,1000.0);
  h_JetEtaforHTLead_Exp=new TH1D("h_JetEtaforHTLead_Exp","h_JetEtaforHTLead_Exp",50,-2.5,2.5);
  h_JetPtforHTNotLead_Exp=new TH1D("h_JetPtforHTNotLead_Exp","h_JetPtforHTNotLead_Exp",20,0.0,1000.0);
  h_JetEtaforHTNotLead_Exp=new TH1D("h_JetEtaforHTNotLead_Exp","h_JetEtaforHTNotLead_Exp",50,-2.5,2.5);
  h_JetPtforHT_Exp=new TH1D("h_JetPtforHT_Exp","h_JetPtforHT_Exp",20,0.0,1000.0);
  h_JetEtaforHT_Exp=new TH1D("h_JetEtaforHT_Exp","h_JetEtaforHT_Exp",50,-2.5,2.5);

  h_JetPtvsEtaforHT_Exp=new TH2D("h_JetPtvsEtaforHT_Exp","h_JetPtvsEtaforHT_Exp",20,0.0,1000.0,50,-2.5,2.5);
  h_JetPtvsHTRatioforHT_Exp=new TH2D("h_JetPtvsHTRatioforHT_Exp","h_JetPtvsHTRatioforHT_Exp",20,0.0,1000.0,20,0,5);

  h_rawJetPtvsEtaforHT_Exp=new TH2D("h_rawJetPtvsEtaforHT_Exp","h_rawJetPtvsEtaforHT_Exp",20,0.0,1000.0,50,-2.5,2.5);

  h_rawJetPtforMHTminusHT_Exp=new TH1D("h_rawJetPtforMHTminusHT_Exp","h_rawJetPtforMHTminusHT_Exp",20,0.0,1000.0);
  h_JetPtforMHTminusHTLead_Exp=new TH1D("h_JetPtforMHTminusHTLead_Exp","h_JetPtforMHTminusHTLead_Exp",20,0.0,1000.0);
  h_JetEtaforMHTminusHTLead_Exp=new TH1D("h_JetEtaforMHTminusHTLead_Exp","h_JetEtaforMHTminusHTLead_Exp",100,-5.,5.);
  h_JetPtforMHTminusHTNotLead_Exp=new TH1D("h_JetPtforMHTminusHTNotLead_Exp","h_JetPtforMHTminusHTNotLead_Exp",20,0.0,1000.0);
  h_JetEtaforMHTminusHTNotLead_Exp=new TH1D("h_JetEtaforMHTminusHTNotLead_Exp","h_JetEtaforMHTminusHTNotLead_Exp",100,-5.,5.);
  h_JetPtforMHTminusHT_Exp=new TH1D("h_JetPtforMHTminusHT_Exp","h_JetPtforMHTminusHT_Exp",20,0.0,1000.0);
  h_JetEtaforMHTminusHT_Exp=new TH1D("h_JetEtaforMHTminusHT_Exp","h_JetEtaforMHTminusHT_Exp",100,-5.,5.);

  h_JetPtvsEtaforMHTminusHT_Exp=new TH2D("h_JetPtvsEtaforMHTminusHT_Exp","h_JetPtvsEtaforMHTminusHT_Exp",20,0.0,1000.0,100,-5.,5.);

  h_JetPtvsHTRatioforMHTminusHT_Exp=new TH2D("h_JetPtvsHTRatioforMHTminusHT_Exp","h_JetPtvsHTRatioforMHTminusHT_Exp",20,0.0,1000.0,20,0,5);

  h_rawJetPtvsEtaforMHTminusHT_Exp=new TH2D("h_rawJetPtvsEtaforMHTminusHT_Exp","h_rawJetPtvsEtaforMHTminusHT_Exp",20,0.0,1000.0,100,-5.,5.);

  h_HTclean_Exp =new TH1D("h_HTclean_Exp","h_HTclean_Exp",12,100,2500);
  h_HT5clean_Exp =new TH1D("h_HT5clean_Exp","h_HT5clean_Exp",12,100,2500);
  h_MHTclean_Exp =new TH1D("h_MHTclean_Exp","h_MHTclean_Exp",16,200,1000);
  h_METclean_Exp =new TH1D("h_METclean_Exp","h_METclean_Exp",16,200,1000);
  h_MHTPhiclean_Exp=new TH1D("h_MHTPhiclean_Exp","h_MHTPhiclean_Exp",7,-3.5,3.5);
  h_METPhiclean_Exp=new TH1D("h_METPhiclean_Exp","h_METPhiclean_Exp",7,-3.5,3.5);
  h_mTclean_Exp=new TH1D("h_mTclean_Exp","h_mTclean_Exp",20,0,100);
  h_NJetclean_Exp =new TH1D("h_NJetclean_Exp","h_NJetclean_Exp",10,2,12);
  h_NBtagclean_Exp =new TH1D("h_NBtagclean_Exp","h_NBtagclean_Exp",5,0,5);

  h_DphiOneclean_Exp =new TH1D("h_DphiOneclean_Exp","h_DphiOneclean_Exp",32,0,3.2);
  h_DphiTwoclean_Exp =new TH1D("h_DphiTwoclean_Exp","h_DphiTwoclean_Exp",32,0,3.2);
  h_DphiThreeclean_Exp =new TH1D("h_DphiThreeclean_Exp","h_DphiThreeclean_Exp",32,0,3.2);
  h_DphiFourclean_Exp =new TH1D("h_DphiFourclean_Exp","h_DphiFourclean_Exp",32,0,3.2);
  h_LepPtclean_Exp=new TH1D("h_LepPtclean_Exp","h_LepPtclean_Exp",20,0.0,1000.0);
  h_LepEtaclean_Exp=new TH1D("h_LepEtaclean_Exp","h_LepEtaclean_Exp",10,-2.5,2.5);
  h_LepPhiclean_Exp=new TH1D("h_LepPhiclean_Exp","h_LepPhiclean_Exp",7,-3.5,3.5);
  h_Weight_Exp =new TH1D("h_Weight_Exp","h_Weight_Exp",200,-5.,5.);
  h_GenHT_Exp =new TH1D("h_GenHT_Exp","h_GenHT_Exp",100,0.,1000.);

  h_WeightBeforeScalePrefire_Exp =new TH1D("h_WeightBeforeScalePrefire_Exp","h_WeightBeforeScalePrefire_Exp",200,-5.,5.);
  h_WeightBeforeScalePrefirevsGenHT_Exp =new TH2D("h_WeightBeforeScalePrefirevsGenHT_Exp","h_WeightBeforeScalePrefirevsGenHT_Exp",100,0,1000.0,200,-5.,5.);
  h_WeightBeforeScalePrefirevsRecoHT_Exp =new TH2D("h_WeightBeforeScalePrefirevsRecoHT_Exp","h_WeightBeforeScalePrefirevsRecoHT_Exp",100,0,1000.0,200,-5.,5.);

  h_HTv2Recipe_Exp =new TH1D("h_HTv2Recipe_Exp","h_HTv2Recipe_Exp",12,100,2500);
  h_HTv2Recipe_forQCD_Exp =new TH1D("h_HTv2Recipe_forQCD_Exp","h_HTv2Recipe_forQCD_Exp",50,0,2500);

  h_HTforLowNJetv2Recipe_Exp =new TH1D("h_HTforLowNJetv2Recipe_Exp","h_HTforLowNJetv2Recipe_Exp",12,100,2500);
  h_HTforHighNJetv2Recipe_Exp =new TH1D("h_HTforHighNJetv2Recipe_Exp","h_HTforHighNJetv2Recipe_Exp",12,100,2500);
  h_HTforTwoNbv2Recipe_Exp =new TH1D("h_HTforTwoNbv2Recipe_Exp","h_HTforTwoNbv2Recipe_Exp",12,100,2500);
  h_HTforNotTwoNbv2Recipe_Exp =new TH1D("h_HTforNotTwoNbv2Recipe_Exp","h_HTforNotTwoNbv2Recipe_Exp",12,100,2500);

  h_HTvsMHTforLowNJetv2Recipe_Exp =new TH2D("h_HTvsMHTforLowNJetv2Recipe_Exp","h_HTvsMHTforLowNJetv2Recipe_Exp",12,100,2500,16,200,1000);
  h_HTvsMHTforHighNJetv2Recipe_Exp =new TH2D("h_HTvsMHTforHighNJetv2Recipe_Exp","h_HTvsMHTforHighNJetv2Recipe_Exp",12,100,2500,16,200,1000);

  h_HT5v2Recipe_Exp =new TH1D("h_HT5v2Recipe_Exp","h_HT5v2Recipe_Exp",12,100,2500);
  h_HTRatiov2Recipe_Exp =new TH1D("h_HTRatiov2Recipe_Exp","h_HTRatiov2Recipe_Exp",20,0,5);
  h_HTRatioforLowNJetv2Recipe_Exp =new TH1D("h_HTRatioforLowNJetv2Recipe_Exp","h_HTRatioforLowNJetv2Recipe_Exp",20,0,5);
  h_HTRatioforHighNJetv2Recipe_Exp =new TH1D("h_HTRatioforHighNJetv2Recipe_Exp","h_HTRatioforHighNJetv2Recipe_Exp",20,0,5);
  h_HTRatioforTwoNbv2Recipe_Exp =new TH1D("h_HTRatioforTwoNbv2Recipe_Exp","h_HTRatioforTwoNbv2Recipe_Exp",20,0,5);
  h_HTRatioforNotTwoNbv2Recipe_Exp =new TH1D("h_HTRatioforNotTwoNbv2Recipe_Exp","h_HTRatioforNotTwoNbv2Recipe_Exp",20,0,5);

  h_MHTv2Recipe_Exp =new TH1D("h_MHTv2Recipe_Exp","h_MHTv2Recipe_Exp",16,200,1000);
  h_MHTv2Recipe_forQCD_Exp =new TH1D("h_MHTv2Recipe_forQCD_Exp","h_MHTv2Recipe_forQCD_Exp",40,0,2000);

  h_MHTforTwoNbv2Recipe_Exp =new TH1D("h_MHTforTwoNbv2Recipe_Exp","h_MHTforTwoNbv2Recipe_Exp",16,200,1000);
  h_MHTforNotTwoNbv2Recipe_Exp =new TH1D("h_MHTforNotTwoNbv2Recipe_Exp","h_MHTforNotTwoNbv2Recipe_Exp",16,200,1000);

  h_MHTforLowNJetv2Recipe_Exp =new TH1D("h_MHTforLowNJetv2Recipe_Exp","h_MHTforLowNJetv2Recipe_Exp",16,200,1000);
  h_MHTforHighNJetv2Recipe_Exp =new TH1D("h_MHTforHighNJetv2Recipe_Exp","h_MHTforHighNJetv2Recipe_Exp",16,200,1000);

  h_MHTPhiv2Recipe_Exp=new TH1D("h_MHTPhiv2Recipe_Exp","h_MHTPhiv2Recipe_Exp",7,-3.5,3.5);
  h_MHTPhiforLowNJetv2Recipe_Exp=new TH1D("h_MHTPhiforLowNJetv2Recipe_Exp","h_MHTPhiforLowNJetv2Recipe_Exp",7,-3.5,3.5);
  h_MHTPhiforHighNJetv2Recipe_Exp=new TH1D("h_MHTPhiforHighNJetv2Recipe_Exp","h_MHTPhiforHighNJetv2Recipe_Exp",7,-3.5,3.5);
  h_MHTPhiforTwoNbv2Recipe_Exp =new TH1D("h_MHTPhiforTwoNbv2Recipe_Exp","h_MHTPhiforTwoNbv2Recipe_Exp",7,-3.5,3.5);
  h_MHTPhiforNotTwoNbv2Recipe_Exp =new TH1D("h_MHTPhiforNotTwoNbv2Recipe_Exp","h_MHTPhiforNotTwoNbv2Recipe_Exp",7,-3.5,3.5);

  h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp=new TH2D("h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp","h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp",70,-3.5,3.5,20,0,5);
  h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp=new TH2D("h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp","h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp",70,-3.5,3.5,20,0,5);
  h_NJetv2Recipe_Exp =new TH1D("h_NJetv2Recipe_Exp","h_NJetv2Recipe_Exp",10,2,12);
  h_NJetv2Recipe_forQCD_Exp =new TH1D("h_NJetv2Recipe_forQCD_Exp","h_NJetv2Recipe_forQCD_Exp",14,0,14);

  h_NJetforTwoNbv2Recipe_Exp =new TH1D("h_NJetforTwoNbv2Recipe_Exp","h_NJetforTwoNbv2Recipe_Exp",10,2,12);
  h_NJetforNotTwoNbv2Recipe_Exp =new TH1D("h_NJetforNotTwoNbv2Recipe_Exp","h_NJetforNotTwoNbv2Recipe_Exp",10,2,12);

  h_NJetvsHTv2Recipe_Exp=new TH2D("h_NJetvsHTv2Recipe_Exp","h_NJetvsHTv2Recipe_Exp",10,2,12,12,100,2500);
  h_NJetvsMHTv2Recipe_Exp=new TH2D("h_NJetvsMHTv2Recipe_Exp","h_NJetvsMHTv2Recipe_Exp",10,2,12,16,200,1000);
  h_NJetvsMHTPhiv2Recipe_Exp=new TH2D("h_NJetvsMHTPhiv2Recipe_Exp","h_NJetvsMHTPhiv2Recipe_Exp",10,2,12,7,-3.5,3.5);
  h_NJetvsNBtagv2Recipe_Exp=new TH2D("h_NJetvsNBtagv2Recipe_Exp","h_NJetvsNBtagv2Recipe_Exp",10,2,12,5,0,5);
  h_NJetvsNBFracv2Recipe_Exp=new TH2D("h_NJetvsNBFracv2Recipe_Exp","h_NJetvsNBFracv2Recipe_Exp",10,2,12,50,0,1);

  h_NJetforMHTminusHTv2Recipe_Exp =new TH1D("h_NJetforMHTminusHTv2Recipe_Exp","h_NJetforMHTminusHTv2Recipe_Exp",12,0,12);
  h_NBtagv2Recipe_Exp =new TH1D("h_NBtagv2Recipe_Exp","h_NBtagv2Recipe_Exp",5,0,5);
  h_NBtagv2Recipe_forQCD_Exp =new TH1D("h_NBtagv2Recipe_forQCD_Exp","h_NBtagv2Recipe_forQCD_Exp",7,0,7);

  h_NBtagforLowNJetv2Recipe_Exp =new TH1D("h_NBtagforLowNJetv2Recipe_Exp","h_NBtagforLowNJetv2Recipe_Exp",5,0,5);
  h_NBtagforHighNJetv2Recipe_Exp =new TH1D("h_NBtagforHighNJetv2Recipe_Exp","h_NBtagforHighNJetv2Recipe_Exp",5,0,5);

  h_rawJetPtforHTv2Recipe_Exp=new TH1D("h_rawJetPtforHTv2Recipe_Exp","h_rawJetPtforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetPtforHTv2RecipeLead_Exp=new TH1D("h_JetPtforHTv2RecipeLead_Exp","h_JetPtforHTv2RecipeLead_Exp",20,0.0,1000.0);
  h_JetEtaforHTv2RecipeLead_Exp=new TH1D("h_JetEtaforHTv2RecipeLead_Exp","h_JetEtaforHTv2RecipeLead_Exp",50,-2.5,2.5);
  h_JetPhiforHTv2RecipeLead_Exp=new TH1D("h_JetPhiforHTv2RecipeLead_Exp","h_JetPhiforHTv2RecipeLead_Exp",70,-3.5,3.5);

  h_JetPtforHTv2RecipeNotLead_Exp=new TH1D("h_JetPtforHTv2RecipeNotLead_Exp","h_JetPtforHTv2RecipeNotLead_Exp",20,0.0,1000.0);
  h_JetEtaforHTv2RecipeNotLead_Exp=new TH1D("h_JetEtaforHTv2RecipeNotLead_Exp","h_JetEtaforHTv2RecipeNotLead_Exp",50,-2.5,2.5);
  h_JetPhiforHTv2RecipeNotLead_Exp=new TH1D("h_JetPhiforHTv2RecipeNotLead_Exp","h_JetPhiforHTv2RecipeNotLead_Exp",70,-3.5,3.5);

  h_JetPtforHTv2Recipe_Exp=new TH1D("h_JetPtforHTv2Recipe_Exp","h_JetPtforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHTv2Recipe_Exp=new TH1D("h_JetEtaforHTv2Recipe_Exp","h_JetEtaforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetEtafor50forHTv2Recipe_Exp=new TH1D("h_JetEtafor50forHTv2Recipe_Exp","h_JetEtafor50forHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetEtafor100forHTv2Recipe_Exp=new TH1D("h_JetEtafor100forHTv2Recipe_Exp","h_JetEtafor100forHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetEtafor200forHTv2Recipe_Exp=new TH1D("h_JetEtafor200forHTv2Recipe_Exp","h_JetEtafor200forHTv2Recipe_Exp",50,-2.5,2.5);

  h_JetPhiforHTv2Recipe_Exp=new TH1D("h_JetPhiforHTv2Recipe_Exp","h_JetPhiforHTv2Recipe_Exp",70,-3.5,3.5);

  h_JetPtforTwoNbforHTv2Recipe_Exp=new TH1D("h_JetPtforTwoNbforHTv2Recipe_Exp","h_JetPtforTwoNbforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforTwoNbforHTv2Recipe_Exp=new TH1D("h_JetEtaforTwoNbforHTv2Recipe_Exp","h_JetEtaforTwoNbforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforTwoNbforHTv2Recipe_Exp=new TH1D("h_JetPhiforTwoNbforHTv2Recipe_Exp","h_JetPhiforTwoNbforHTv2Recipe_Exp",70,-3.5,3.5);

  h_JetPtforNotTwoNbforHTv2Recipe_Exp=new TH1D("h_JetPtforNotTwoNbforHTv2Recipe_Exp","h_JetPtforNotTwoNbforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforNotTwoNbforHTv2Recipe_Exp=new TH1D("h_JetEtaforNotTwoNbforHTv2Recipe_Exp","h_JetEtaforNotTwoNbforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforNotTwoNbforHTv2Recipe_Exp=new TH1D("h_JetPhiforNotTwoNbforHTv2Recipe_Exp","h_JetPhiforNotTwoNbforHTv2Recipe_Exp",70,-3.5,3.5);

  h_JetPtforLowNJetforHTv2Recipe_Exp=new TH1D("h_JetPtforLowNJetforHTv2Recipe_Exp","h_JetPtforLowNJetforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforLowNJetforHTv2Recipe_Exp=new TH1D("h_JetEtaforLowNJetforHTv2Recipe_Exp","h_JetEtaforLowNJetforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforLowNJetforHTv2Recipe_Exp=new TH1D("h_JetPhiforLowNJetforHTv2Recipe_Exp","h_JetPhiforLowNJetforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp","h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp",50,-2.5,2.5,70,-3.5,3.5);

  h_JetPtforLowNJetfor0bforHTv2Recipe_Exp=new TH1D("h_JetPtforLowNJetfor0bforHTv2Recipe_Exp","h_JetPtforLowNJetfor0bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp=new TH1D("h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp","h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp=new TH1D("h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp","h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforLowNJetfor1bforHTv2Recipe_Exp=new TH1D("h_JetPtforLowNJetfor1bforHTv2Recipe_Exp","h_JetPtforLowNJetfor1bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp=new TH1D("h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp","h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp=new TH1D("h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp","h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforLowNJetfor2bforHTv2Recipe_Exp=new TH1D("h_JetPtforLowNJetfor2bforHTv2Recipe_Exp","h_JetPtforLowNJetfor2bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp=new TH1D("h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp","h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp=new TH1D("h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp","h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforLowNJetfor3bforHTv2Recipe_Exp=new TH1D("h_JetPtforLowNJetfor3bforHTv2Recipe_Exp","h_JetPtforLowNJetfor3bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp=new TH1D("h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp","h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp=new TH1D("h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp","h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp",70,-3.5,3.5);


  h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp","h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp",20,0.0,1000.0,50,-2.5,2.5);
  h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp","h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp",50,-2.5,2.5,70,-3.5,3.5);
  h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp","h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp",20,0.0,1000.0,7,-3.5,3.5);
  h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp","h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp",20,0.0,1000.0,32,0.,3.2);
  h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp","h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp",20,0.0,1000.0,32,0.,3.2);
  h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp=new TH2D("h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp","h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp",35,-3.5,3.5,32,0.,3.2);
  h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp=new TH2D("h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp","h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp",35,-3.5,3.5,32,0.,3.2);

  h_JetPtforHighNJetforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetforHTv2Recipe_Exp","h_JetPtforHighNJetforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetforHTv2Recipe_Exp","h_JetEtaforHighNJetforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetforHTv2Recipe_Exp","h_JetPhiforHighNJetforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp","h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp",50,-2.5,2.5,70,-3.5,3.5);

  h_JetCSVforHighNJetforHTv2Recipe_Exp=new TH1D("h_JetCSVforHighNJetforHTv2Recipe_Exp","h_JetCSVforHighNJetforHTv2Recipe_Exp",100,0.0,1.0);
  h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp","h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp",20,0.0,1000.0,100,0.0,1.0);
  h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp","h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp",50,-2.5,2.5,100,0.0,1.0);
  h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp","h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp",70,-3.5,3.5,100,0.0,1.0);

  h_JetPtforHighNJetLeadforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetLeadforHTv2Recipe_Exp","h_JetPtforHighNJetLeadforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetLeadforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetLeadforHTv2Recipe_Exp","h_JetEtaforHighNJetLeadforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetLeadforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetLeadforHTv2Recipe_Exp","h_JetPhiforHighNJetLeadforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp","h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp","h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp","h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp",70,-3.5,3.5);

  h_JetPtforHighNJetfor0bforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetfor0bforHTv2Recipe_Exp","h_JetPtforHighNJetfor0bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp","h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp","h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforHighNJetfor1bforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetfor1bforHTv2Recipe_Exp","h_JetPtforHighNJetfor1bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp","h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp","h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforHighNJetfor2bforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetfor2bforHTv2Recipe_Exp","h_JetPtforHighNJetfor2bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp","h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp","h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforHighNJetfor3bforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetfor3bforHTv2Recipe_Exp","h_JetPtforHighNJetfor3bforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp","h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp","h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp",70,-3.5,3.5);


  h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp","h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp",20,0.0,1000.0,50,-2.5,2.5);
  h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp","h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp",50,-2.5,2.5,70,-3.5,3.5);

  h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp","h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp",20,0.0,1000.0,7,-3.5,3.5);

  h_DphiOneforHTv2Recipe_Exp =new TH1D("h_DphiOneforHTv2Recipe_Exp","h_DphiOneforHTv2Recipe_Exp",32,0,3.2);
  h_DphiTwoforHTv2Recipe_Exp =new TH1D("h_DphiTwoforHTv2Recipe_Exp","h_DphiTwoforHTv2Recipe_Exp",32,0,3.2);
  h_DphiThreeforHTv2Recipe_Exp =new TH1D("h_DphiThreeforHTv2Recipe_Exp","h_DphiThreeforHTv2Recipe_Exp",32,0,3.2);
  h_DphiFourforHTv2Recipe_Exp =new TH1D("h_DphiFourforHTv2Recipe_Exp","h_DphiFourforHTv2Recipe_Exp",32,0,3.2);

  h_rawJetPtvsEtaforHTv2Recipe_Exp=new TH2D("h_rawJetPtvsEtaforHTv2Recipe_Exp","h_rawJetPtvsEtaforHTv2Recipe_Exp",20,0.0,1000.0,50,-2.5,2.5);
  h_JetPtvsEtaforHTv2Recipe_Exp=new TH2D("h_JetPtvsEtaforHTv2Recipe_Exp","h_JetPtvsEtaforHTv2Recipe_Exp",20,0.0,1000.0,50,-2.5,2.5);
  h_JetEtavsPhiforHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforHTv2Recipe_Exp","h_JetEtavsPhiforHTv2Recipe_Exp",50,-2.5,2.5,70,-3.5,3.5);
  h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp","h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp",50,-2.5,2.5,70,-3.5,3.5);

  h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp=new TH2D("h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp","h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp",50,-2.5,2.5,70,-3.5,3.5);
  h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp=new TH2D("h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp","h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp",50,-2.5,2.5,70,-3.5,3.5);
  h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp=new TH2D("h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp","h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp",50,-2.5,2.5,32,0,3.2);
  h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp=new TH2D("h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp","h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp",50,-2.5,2.5,32,0,3.2);
  h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp=new TH1D("h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp","h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp",20,0,1);
  h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp=new TH1D("h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp","h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp",20,0,1);
  h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp=new TH1D("h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp","h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp",20,0,1);
  h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp=new TH1D("h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp","h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp",20,0,1);

  h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp=new TH2D("h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp","h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp",50,-2.5,2.5,210,-0.5,20.5);
  h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp=new TH2D("h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp","h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp",50,-2.5,2.5,210,-0.5,20.5);

  h_JetIdxvsEtaforHTv2Recipe_Exp=new TH2D("h_JetIdxvsEtaforHTv2Recipe_Exp","h_JetIdxvsEtaforHTv2Recipe_Exp",12,0,12,50,-2.5,2.5);
  h_JetMultvsEtaforHTv2Recipe_Exp=new TH2D("h_JetMultvsEtaforHTv2Recipe_Exp","h_JetMultvsEtaforHTv2Recipe_Exp",12,0,12,50,-2.5,2.5);

  h_JetPtvsHTRatioforHTv2Recipe_Exp=new TH2D("h_JetPtvsHTRatioforHTv2Recipe_Exp","h_JetPtvsHTRatioforHTv2Recipe_Exp",20,0.0,1000.0,20,0,5);
  h_JetEtavsHTRatioforHTv2Recipe_Exp=new TH2D("h_JetEtavsHTRatioforHTv2Recipe_Exp","h_JetEtavsHTRatioforHTv2Recipe_Exp",50,-2.5,2.5,20,0,5);
  h_JetPhivsHTRatioforHTv2Recipe_Exp=new TH2D("h_JetPhivsHTRatioforHTv2Recipe_Exp","h_JetPhivsHTRatioforHTv2Recipe_Exp",70,-3.5,3.5,20,0,5);
  h_JetPhivsDPhiLeadforHTv2Recipe_Exp=new TH2D("h_JetPhivsDPhiLeadforHTv2Recipe_Exp","h_JetPhivsDPhiLeadforHTv2Recipe_Exp",70,-3.5,3.5,32,0,3.2);
  h_MHTPhivsJetPhiforHTv2Recipe_Exp=new TH2D("h_MHTPhivsJetPhiforHTv2Recipe_Exp","h_MHTPhivsJetPhiforHTv2Recipe_Exp",70,-3.5,3.5,70,-3.5,3.5);
  h_RecHTRatiovsDPhiforHTv2Recipe_Exp=new TH2D("h_RecHTRatiovsDPhiforHTv2Recipe_Exp","h_RecHTRatiovsDPhiforHTv2Recipe_Exp",110,0,1.1,32,0,3.2);
  h_RecHTRatiovsDPhiforAllv2Recipe_Exp=new TH2D("h_RecHTRatiovsDPhiforAllv2Recipe_Exp","h_RecHTRatiovsDPhiforAllv2Recipe_Exp",110,0,1.1,32,0,3.2);

  h_chargedEmEnergyFractionforHTv2Recipe_Exp =new TH1D("h_chargedEmEnergyFractionforHTv2Recipe_Exp","h_chargedEmEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_chargedHadronEnergyFractionforHTv2Recipe_Exp =new TH1D("h_chargedHadronEnergyFractionforHTv2Recipe_Exp","h_chargedHadronEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_electronEnergyFractionforHTv2Recipe_Exp =new TH1D("h_electronEnergyFractionforHTv2Recipe_Exp","h_electronEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_hfEMEnergyFractionforHTv2Recipe_Exp =new TH1D("h_hfEMEnergyFractionforHTv2Recipe_Exp","h_hfEMEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_hfHadronEnergyFractionforHTv2Recipe_Exp =new TH1D("h_hfHadronEnergyFractionforHTv2Recipe_Exp","h_hfHadronEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_muonEnergyFractionforHTv2Recipe_Exp =new TH1D("h_muonEnergyFractionforHTv2Recipe_Exp","h_muonEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_neutralEmEnergyFractionforHTv2Recipe_Exp =new TH1D("h_neutralEmEnergyFractionforHTv2Recipe_Exp","h_neutralEmEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp =new TH1D("h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp","h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp",20,0,1);
  h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp =new TH1D("h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp","h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp",20,0,1);
  h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp =new TH1D("h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp","h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp",20,0,1);

  h_neutralHadronEnergyFractionforHTv2Recipe_Exp =new TH1D("h_neutralHadronEnergyFractionforHTv2Recipe_Exp","h_neutralHadronEnergyFractionforHTv2Recipe_Exp",20,0,1);
  h_photonEnergyFractionforHTv2Recipe_Exp =new TH1D("h_photonEnergyFractionforHTv2Recipe_Exp","h_photonEnergyFractionforHTv2Recipe_Exp",20,0,1);
  //  h_qgLikelihoodforHTv2Recipe_Exp =new TH1D("h_qgLikelihoodforHTv2Recipe_Exp",20,0,1);
  h_chargedHadronMultiplicityforHTv2Recipe_Exp =new TH1D("h_chargedHadronMultiplicityforHTv2Recipe_Exp","h_chargedHadronMultiplicityforHTv2Recipe_Exp",100,0,100);
  h_chargedMultiplicityforHTv2Recipe_Exp =new TH1D("h_chargedMultiplicityforHTv2Recipe_Exp","h_chargedMultiplicityforHTv2Recipe_Exp",100,0,100);
  h_electronMultiplicityforHTv2Recipe_Exp =new TH1D("h_electronMultiplicityforHTv2Recipe_Exp","h_electronMultiplicityforHTv2Recipe_Exp",100,0,100);
  h_multiplicityforHTv2Recipe_Exp =new TH1D("h_multiplicityforHTv2Recipe_Exp","h_multiplicityforHTv2Recipe_Exp",100,0,100);
  h_muonMultiplicityforHTv2Recipe_Exp =new TH1D("h_muonMultiplicityforHTv2Recipe_Exp","h_muonMultiplicityforHTv2Recipe_Exp",100,0,100);
  h_neutralHadronMultiplicityforHTv2Recipe_Exp =new TH1D("h_neutralHadronMultiplicityforHTv2Recipe_Exp","h_neutralHadronMultiplicityforHTv2Recipe_Exp",20,0,20);
  h_neutralMultiplicityforHTv2Recipe_Exp =new TH1D("h_neutralMultiplicityforHTv2Recipe_Exp","h_neutralMultiplicityforHTv2Recipe_Exp",100,0,100);
  h_photonMultiplicityforHTv2Recipe_Exp =new TH1D("h_photonMultiplicityforHTv2Recipe_Exp","h_photonMultiplicityforHTv2Recipe_Exp",100,0,100);
  h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp=new TH2D("h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp","h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp",20,0.0,1000.0,100,0,100);
  h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp=new TH2D("h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp","h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp",50,-2.5,2.5,100,0,100);
  h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp=new TH2D("h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp","h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp",70,-3.5,3.5,100,0,100);
  h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp","h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp",20,0.0,1000.0,100,0,100);
  h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp","h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp",50,-2.5,2.5,100,0,100);
  h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp=new TH2D("h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp","h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp",70,-3.5,3.5,100,0,100);


  h_JetPtvsPhiforHTv2Recipe_Exp=new TH2D("h_JetPtvsPhiforHTv2Recipe_Exp","h_JetPtvsPhiforHTv2Recipe_Exp",20,0.0,1000.0,70,-3.5,3.5);
  h_JetPtvsDPhiforHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforHTv2Recipe_Exp","h_JetPtvsDPhiforHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);
  h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp","h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);
  h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp","h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);

  h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp","h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);

  h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp","h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);

  h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp","h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp","h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp",20,0.0,1000.0,50,0,10);
  h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp","h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);
  h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp","h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);
  h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp","h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp",50,-2.5,2.5,50,0,10);
  h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp","h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp",50,-2.5,2.5,200,0,100);
  h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp","h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp",50,-2.5,2.5,200,0,100);

  h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp","h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp",50,-2.5,2.5,20,0,1);
  h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp","h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp",70,-3.5,3.5,20,0,1);

  h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp","h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp","h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp","h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp",50,-2.5,2.5,20,0,1);
  h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp","h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp",70,-3.5,3.5,20,0,1);





  h_rawJetPtforMHTminusHTv2Recipe_Exp=new TH1D("h_rawJetPtforMHTminusHTv2Recipe_Exp","h_rawJetPtforMHTminusHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetPtforMHTminusHTv2RecipeLead_Exp=new TH1D("h_JetPtforMHTminusHTv2RecipeLead_Exp","h_JetPtforMHTminusHTv2RecipeLead_Exp",20,0.0,1000.0);
  h_JetEtaforMHTminusHTv2RecipeLead_Exp=new TH1D("h_JetEtaforMHTminusHTv2RecipeLead_Exp","h_JetEtaforMHTminusHTv2RecipeLead_Exp",100,-5.,5.);
  h_JetPhiforMHTminusHTv2RecipeLead_Exp=new TH1D("h_JetPhiforMHTminusHTv2RecipeLead_Exp","h_JetPhiforMHTminusHTv2RecipeLead_Exp",70,-3.5,3.5);

  h_JetPtforMHTminusHTv2RecipeNotLead_Exp=new TH1D("h_JetPtforMHTminusHTv2RecipeNotLead_Exp","h_JetPtforMHTminusHTv2RecipeNotLead_Exp",20,0.0,1000.0);
  h_JetEtaforMHTminusHTv2RecipeNotLead_Exp=new TH1D("h_JetEtaforMHTminusHTv2RecipeNotLead_Exp","h_JetEtaforMHTminusHTv2RecipeNotLead_Exp",100,-5.,5.);
  h_JetPhiforMHTminusHTv2RecipeNotLead_Exp=new TH1D("h_JetPhiforMHTminusHTv2RecipeNotLead_Exp","h_JetPhiforMHTminusHTv2RecipeNotLead_Exp",70,-3.5,3.5);

  h_JetPtforMHTminusHTv2Recipe_Exp=new TH1D("h_JetPtforMHTminusHTv2Recipe_Exp","h_JetPtforMHTminusHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforMHTminusHTv2Recipe_Exp=new TH1D("h_JetEtaforMHTminusHTv2Recipe_Exp","h_JetEtaforMHTminusHTv2Recipe_Exp",100,-5.,5.);
  h_JetEtafor50forMHTminusHTv2Recipe_Exp=new TH1D("h_JetEtafor50forMHTminusHTv2Recipe_Exp","h_JetEtafor50forMHTminusHTv2Recipe_Exp",100,-5.,5.);
  h_JetEtafor100forMHTminusHTv2Recipe_Exp=new TH1D("h_JetEtafor100forMHTminusHTv2Recipe_Exp","h_JetEtafor100forMHTminusHTv2Recipe_Exp",100,-5.,5.);
  h_JetEtafor200forMHTminusHTv2Recipe_Exp=new TH1D("h_JetEtafor200forMHTminusHTv2Recipe_Exp","h_JetEtafor200forMHTminusHTv2Recipe_Exp",100,-5.,5.);

  h_JetPhiforMHTminusHTv2Recipe_Exp=new TH1D("h_JetPhiforMHTminusHTv2Recipe_Exp","h_JetPhiforMHTminusHTv2Recipe_Exp",70,-3.5,3.5);

  h_DphiOneforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiOneforMHTminusHTv2Recipe_Exp","h_DphiOneforMHTminusHTv2Recipe_Exp",32,0,3.2);
  h_DphiTwoforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiTwoforMHTminusHTv2Recipe_Exp","h_DphiTwoforMHTminusHTv2Recipe_Exp",32,0,3.2);
  h_DphiThreeforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiThreeforMHTminusHTv2Recipe_Exp","h_DphiThreeforMHTminusHTv2Recipe_Exp",32,0,3.2);
  h_DphiFourforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiFourforMHTminusHTv2Recipe_Exp","h_DphiFourforMHTminusHTv2Recipe_Exp",32,0,3.2);

  h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp=new TH2D("h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp","h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,100,-5.,5.);
  h_JetPtvsEtaforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsEtaforMHTminusHTv2Recipe_Exp","h_JetPtvsEtaforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,100,-5.,5.);
  h_JetEtavsPhiforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforMHTminusHTv2Recipe_Exp","h_JetEtavsPhiforMHTminusHTv2Recipe_Exp",100,-5.,5.,70,-3.5,3.5);
  h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp","h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp",100,-5.,5.,70,-3.5,3.5);


  h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp","h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp",100,-5.,5.,70,-3.5,3.5);

  h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp=new TH2D("h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp","h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp",12,0,12,100,-5.,5.);
  h_JetMultvsEtaforMHTminusHTv2Recipe_Exp=new TH2D("h_JetMultvsEtaforMHTminusHTv2Recipe_Exp","h_JetMultvsEtaforMHTminusHTv2Recipe_Exp",12,0,12,100,-5.,5.);
  h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp","h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,20,0,5);
  h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp","h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp",100,-5.,5.,20,0,5);
  h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp","h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp",70,-3.5,3.5,20,0,5);
  h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp","h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp",70,-3.5,3.5,32,0,3.2);
  h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp=new TH2D("h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp","h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp",70,-3.5,3.5,70,-3.5,3.5);
  h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp=new TH2D("h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp","h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp",110,0,1.1,32,0,3.2);



  h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp","h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_electronEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_electronEnergyFractionforMHTminusHTv2Recipe_Exp","h_electronEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp","h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp","h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_muonEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_muonEnergyFractionforMHTminusHTv2Recipe_Exp","h_muonEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp","h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  h_photonEnergyFractionforMHTminusHTv2Recipe_Exp =new TH1D("h_photonEnergyFractionforMHTminusHTv2Recipe_Exp","h_photonEnergyFractionforMHTminusHTv2Recipe_Exp",20,0,1);
  //  h_qgLikelihoodforMHTminusHTv2Recipe_Exp =new TH1D("h_qgLikelihoodforMHTminusHTv2Recipe_Exp",20,0,1);
  h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp","h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp",100,0,100);
  h_chargedMultiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_chargedMultiplicityforMHTminusHTv2Recipe_Exp","h_chargedMultiplicityforMHTminusHTv2Recipe_Exp",100,0,100);
  h_electronMultiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_electronMultiplicityforMHTminusHTv2Recipe_Exp","h_electronMultiplicityforMHTminusHTv2Recipe_Exp",100,0,100);
  h_multiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_multiplicityforMHTminusHTv2Recipe_Exp","h_multiplicityforMHTminusHTv2Recipe_Exp",100,0,100);
  h_muonMultiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_muonMultiplicityforMHTminusHTv2Recipe_Exp","h_muonMultiplicityforMHTminusHTv2Recipe_Exp",100,0,100);
  h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp","h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp",20,0,20);
  h_neutralMultiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_neutralMultiplicityforMHTminusHTv2Recipe_Exp","h_neutralMultiplicityforMHTminusHTv2Recipe_Exp",100,0,100);
  h_photonMultiplicityforMHTminusHTv2Recipe_Exp =new TH1D("h_photonMultiplicityforMHTminusHTv2Recipe_Exp","h_photonMultiplicityforMHTminusHTv2Recipe_Exp",100,0,100);
  h_JetPtvsPhiforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsPhiforMHTminusHTv2Recipe_Exp","h_JetPtvsPhiforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,70,-3.5,3.5);
  h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp","h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);
  h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp","h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);
  h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp","h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);

  h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp","h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);

  h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,50,0,10);
  h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);
  h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);

  h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp","h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp",100,-5,5,50,0,10);
  h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp","h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp",100,-5,5,200,0,100);
  h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp","h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp",100,-5,5,200,0,100);

  h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp",100,-5,5,20,0,1);
  h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp",70,-3.5,3.5,20,0,1);

  h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp",100,-5,5,20,0,1);
  h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp",70,-3.5,3.5,20,0,1);



  h_MHTOrig_Exp =new TH1D("h_MHTOrig_Exp","h_MHTOrig_Exp",16,200,1000);
  h_METOrig_Exp =new TH1D("h_METOrig_Exp","h_METOrig_Exp",16,200,1000);
  h_MHTPhiOrig_Exp=new TH1D("h_MHTPhiOrig_Exp","h_MHTPhiOrig_Exp",7,-3.5,3.5);
  h_METPhiOrig_Exp=new TH1D("h_METPhiOrig_Exp","h_METPhiOrig_Exp",7,-3.5,3.5);

  h_DphiOneOrig_Exp =new TH1D("h_DphiOneOrig_Exp","h_DphiOneOrig_Exp",32,0,3.2);
  h_DphiTwoOrig_Exp =new TH1D("h_DphiTwoOrig_Exp","h_DphiTwoOrig_Exp",32,0,3.2);
  h_DphiThreeOrig_Exp =new TH1D("h_DphiThreeOrig_Exp","h_DphiThreeOrig_Exp",32,0,3.2);
  h_DphiFourOrig_Exp =new TH1D("h_DphiFourOrig_Exp","h_DphiFourOrig_Exp",32,0,3.2);


  h_HT_Pre =new TH1D("h_HT_Pre","h_HT_Pre",12,100,2500);
  h_HT_forQCD_Pre =new TH1D("h_HT_forQCD_Pre","h_HT_forQCD_Pre",50,0,2500);

  h_MHT_Pre =new TH1D("h_MHT_Pre","h_MHT_Pre",16,200,1000);
  h_MHT_forQCD_Pre =new TH1D("h_MHT_forQCD_Pre","h_MHT_forQCD_Pre",40,0,2000);

  h_NJet_Pre =new TH1D("h_NJet_Pre","h_NJet_Pre",10,2,12);
  h_NJet_forQCD_Pre =new TH1D("h_NJet_forQCD_Pre","h_NJet_forQCD_Pre",14,0,14);

  h_NBtag_Pre =new TH1D("h_NBtag_Pre","h_NBtag_Pre",5,0,5);
  h_NBtag_forQCD_Pre =new TH1D("h_NBtag_forQCD_Pre","h_NBtag_forQCD_Pre",7,0,7);


  GetOutputList()->Add(h_Prediction);
  GetOutputList()->Add(h_CSStat); //one lepton CS
  GetOutputList()->Add(h_CutFlow); //one lepton CS
  GetOutputList()->Add(h_CSStat_MHTVsNbjet);
  GetOutputList()->Add(h_Prediction_MHTVsNbjet);
  GetOutputList()->Add(h_YieldCutFlow);
  GetOutputList()->Add(h_HT_Exp);
  GetOutputList()->Add(h_HT5_Exp);
  GetOutputList()->Add(h_HTRatio_Exp);
  GetOutputList()->Add(h_MHT_Exp);
  GetOutputList()->Add(h_MET_Exp);
  GetOutputList()->Add(h_METPhi_Exp);
  GetOutputList()->Add(h_MHTPhi_Exp);
  GetOutputList()->Add(h_mT_Exp);
  GetOutputList()->Add(h_NJet_Exp);
  GetOutputList()->Add(h_NBtag_Exp);
  GetOutputList()->Add(h_DphiOne_Exp);
  GetOutputList()->Add(h_DphiTwo_Exp);
  GetOutputList()->Add(h_DphiThree_Exp);
  GetOutputList()->Add(h_DphiFour_Exp);

  GetOutputList()->Add(h_LepPt_Exp);
  GetOutputList()->Add(h_LepEta_Exp);
  GetOutputList()->Add(h_LepEtafor50_Exp);
  GetOutputList()->Add(h_LepEtafor100_Exp);
  GetOutputList()->Add(h_LepEtafor200_Exp);

  GetOutputList()->Add(h_LepPhi_Exp); 

  GetOutputList()->Add(h_ElePt_Exp);
  GetOutputList()->Add(h_EleEta_Exp);
  GetOutputList()->Add(h_ElePhi_Exp); 
  GetOutputList()->Add(h_EleEtavsPt_Exp);
  GetOutputList()->Add(h_EleEtavsPhi_Exp);
  GetOutputList()->Add(h_EleEtavsMT_Exp);
  GetOutputList()->Add(h_EleEtavsHT_Exp);
  GetOutputList()->Add(h_EleEtavsMHT_Exp);
  GetOutputList()->Add(h_EleEtavsNJet_Exp);
  GetOutputList()->Add(h_EleEtavsNBtag_Exp);
  GetOutputList()->Add(h_EleMTvsPt_Exp);
  GetOutputList()->Add(h_EleMTvsMET_Exp);
  GetOutputList()->Add(h_EleMTvsDphi_Exp);

  GetOutputList()->Add(h_HEMEleEtavsPt_Exp);
  GetOutputList()->Add(h_HEMEleEtavsPhi_Exp);
  GetOutputList()->Add(h_HEMEleEtavsMT_Exp);
  GetOutputList()->Add(h_HEMEleEtavsHT_Exp);
  GetOutputList()->Add(h_HEMEleEtavsMHT_Exp);
  GetOutputList()->Add(h_HEMEleEtavsNJet_Exp);
  GetOutputList()->Add(h_HEMEleEtavsNBtag_Exp);
  GetOutputList()->Add(h_HEMEleMTvsPt_Exp);
  GetOutputList()->Add(h_HEMEleMTvsMET_Exp);
  GetOutputList()->Add(h_HEMEleMTvsDphi_Exp);

  GetOutputList()->Add(h_MuPt_Exp);
  GetOutputList()->Add(h_MuEta_Exp);
  GetOutputList()->Add(h_MuPhi_Exp); 


  GetOutputList()->Add(h_JetPtforHTLead_Exp);
  GetOutputList()->Add(h_JetEtaforHTLead_Exp);
  //  GetOutputList()->Add(h_JetPhiforHTLead_Exp);
  GetOutputList()->Add(h_JetPtforHTNotLead_Exp);
  GetOutputList()->Add(h_JetEtaforHTNotLead_Exp);
  //  GetOutputList()->Add(h_JetPhiforHTNotLead_Exp);
  GetOutputList()->Add(h_JetPtforHT_Exp);
  GetOutputList()->Add(h_JetEtaforHT_Exp);
  //  GetOutputList()->Add(h_JetPhiforHT_Exp);
  GetOutputList()->Add(h_JetPtvsEtaforHT_Exp);
  GetOutputList()->Add(h_JetPtvsHTRatioforHT_Exp);

  GetOutputList()->Add(h_JetPtforMHTminusHTLead_Exp);
  GetOutputList()->Add(h_JetEtaforMHTminusHTLead_Exp);
  //  GetOutputList()->Add(h_JetPhiforMHTminusHTLead_Exp);
  GetOutputList()->Add(h_JetPtforMHTminusHTNotLead_Exp);
  GetOutputList()->Add(h_JetEtaforMHTminusHTNotLead_Exp);
  //  GetOutputList()->Add(h_JetPhiforMHTminusHTNotLead_Exp);
  GetOutputList()->Add(h_JetPtforMHTminusHT_Exp);
  GetOutputList()->Add(h_JetEtaforMHTminusHT_Exp);
  //  GetOutputList()->Add(h_JetPhiforMHTminusHT_Exp);
  GetOutputList()->Add(h_JetPtvsEtaforMHTminusHT_Exp);
  GetOutputList()->Add(h_JetPtvsHTRatioforMHTminusHT_Exp);
  GetOutputList()->Add(h_rawJetPtforHT_Exp);
  GetOutputList()->Add(h_rawJetPtforMHTminusHT_Exp);
  GetOutputList()->Add(h_rawJetPtvsEtaforHT_Exp);
  GetOutputList()->Add(h_rawJetPtvsEtaforMHTminusHT_Exp);

  GetOutputList()->Add(h_HTclean_Exp);
  GetOutputList()->Add(h_HT5clean_Exp);
  GetOutputList()->Add(h_MHTclean_Exp);
  GetOutputList()->Add(h_METclean_Exp);
  GetOutputList()->Add(h_METPhiclean_Exp);
  GetOutputList()->Add(h_MHTPhiclean_Exp);
  GetOutputList()->Add(h_mTclean_Exp);
  GetOutputList()->Add(h_NJetclean_Exp);
  GetOutputList()->Add(h_NBtagclean_Exp);
  GetOutputList()->Add(h_DphiOneclean_Exp);
  GetOutputList()->Add(h_DphiTwoclean_Exp);
  GetOutputList()->Add(h_DphiThreeclean_Exp);
  GetOutputList()->Add(h_DphiFourclean_Exp);
  GetOutputList()->Add(h_LepPtclean_Exp);
  GetOutputList()->Add(h_LepEtaclean_Exp);
  GetOutputList()->Add(h_LepPhiclean_Exp); 

  GetOutputList()->Add(h_Weight_Exp);
  GetOutputList()->Add(h_GenHT_Exp);
  GetOutputList()->Add(h_WeightBeforeScalePrefire_Exp);
  GetOutputList()->Add(h_WeightBeforeScalePrefirevsGenHT_Exp);
  GetOutputList()->Add(h_WeightBeforeScalePrefirevsRecoHT_Exp);

  GetOutputList()->Add(h_HTv2Recipe_Exp);
  GetOutputList()->Add(h_HTv2Recipe_forQCD_Exp);

  GetOutputList()->Add(h_HTforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTforTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_HTforNotTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_HTvsMHTforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTvsMHTforHighNJetv2Recipe_Exp);

  GetOutputList()->Add(h_HT5v2Recipe_Exp);
  GetOutputList()->Add(h_HTRatiov2Recipe_Exp);
  GetOutputList()->Add(h_HTRatioforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTRatioforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTRatioforTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_HTRatioforNotTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_MHTv2Recipe_Exp);
  GetOutputList()->Add(h_MHTv2Recipe_forQCD_Exp);

  GetOutputList()->Add(h_MHTforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTforTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_MHTforNotTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiforTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiforNotTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_NJetv2Recipe_Exp);
  GetOutputList()->Add(h_NJetv2Recipe_forQCD_Exp);

  GetOutputList()->Add(h_NJetforTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_NJetforNotTwoNbv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsHTv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsMHTv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsMHTPhiv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsNBtagv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsNBFracv2Recipe_Exp);
  GetOutputList()->Add(h_NBtagv2Recipe_Exp);
  GetOutputList()->Add(h_NBtagv2Recipe_forQCD_Exp);

  GetOutputList()->Add(h_NBtagforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_NBtagforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_NJetforMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtforHTv2RecipeLead_Exp);
  GetOutputList()->Add(h_JetEtaforHTv2RecipeLead_Exp);
  GetOutputList()->Add(h_JetPhiforHTv2RecipeLead_Exp);
  GetOutputList()->Add(h_JetPtforHTv2RecipeNotLead_Exp);
  GetOutputList()->Add(h_JetEtaforHTv2RecipeNotLead_Exp);
  GetOutputList()->Add(h_JetPhiforHTv2RecipeNotLead_Exp);
  GetOutputList()->Add(h_JetPtforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtafor50forHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtafor100forHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtafor200forHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPhiforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforNotTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforNotTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforNotTwoNbforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforLowNJetfor0bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforLowNJetfor1bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforLowNJetfor2bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforLowNJetfor3bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetCSVforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtforHighNJetLeadforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetLeadforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetLeadforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtforHighNJetfor0bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforHighNJetfor1bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforHighNJetfor2bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforHighNJetfor3bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiOneforHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiTwoforHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiThreeforHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiFourforHTv2Recipe_Exp);
  GetOutputList()->Add(h_chargedEmEnergyFractionforHTv2Recipe_Exp);
                       
  GetOutputList()->Add(h_chargedHadronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_chargedHadronMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_chargedMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_electronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_electronMultiplicityforHTv2Recipe_Exp);
  //  GetOutputList()->Add(h_hadronFlavorforHTv2Recipe_Exp);
  GetOutputList()->Add(h_hfEMEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_hfHadronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_multiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_muonEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_muonMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralEmEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralHadronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralHadronMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_photonEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_photonMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp);

  //  GetOutputList()->Add(h_qgLikelihoodforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsEtaforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp);
  GetOutputList()->Add(h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp);
  GetOutputList()->Add(h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp);
  GetOutputList()->Add(h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp);
  GetOutputList()->Add(h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp);
  GetOutputList()->Add(h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp);
  GetOutputList()->Add(h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp);

  GetOutputList()->Add(h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp);
  GetOutputList()->Add(h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp);

  GetOutputList()->Add(h_JetIdxvsEtaforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetMultvsEtaforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsHTRatioforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsHTRatioforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsHTRatioforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsDPhiLeadforHTv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhivsJetPhiforHTv2Recipe_Exp);
  GetOutputList()->Add(h_RecHTRatiovsDPhiforHTv2Recipe_Exp);
  GetOutputList()->Add(h_RecHTRatiovsDPhiforAllv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsPhiforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtforMHTminusHTv2RecipeLead_Exp);
  GetOutputList()->Add(h_JetEtaforMHTminusHTv2RecipeLead_Exp);
  GetOutputList()->Add(h_JetPhiforMHTminusHTv2RecipeLead_Exp);
  GetOutputList()->Add(h_JetPtforMHTminusHTv2RecipeNotLead_Exp);
  GetOutputList()->Add(h_JetEtaforMHTminusHTv2RecipeNotLead_Exp);
  GetOutputList()->Add(h_JetPhiforMHTminusHTv2RecipeNotLead_Exp);
  GetOutputList()->Add(h_JetPtforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtafor50forMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtafor100forMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtafor200forMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPhiforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiOneforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiTwoforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiThreeforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_DphiFourforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_chargedMultiplicityforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_electronEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_electronMultiplicityforMHTminusHTv2Recipe_Exp);
  //  GetOutputList()->Add(h_hadronFlavorforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_multiplicityforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_muonEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_muonMultiplicityforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralMultiplicityforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_photonEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_photonMultiplicityforMHTminusHTv2Recipe_Exp);
  //  GetOutputList()->Add(h_qgLikelihoodforMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvsEtaforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetMultvsEtaforMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsPhiforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp);

  GetOutputList()->Add(h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp);


  GetOutputList()->Add(h_rawJetPtforHTv2Recipe_Exp);
  GetOutputList()->Add(h_rawJetPtforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_rawJetPtvsEtaforHTv2Recipe_Exp);
  GetOutputList()->Add(h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp);


  GetOutputList()->Add(h_MHTOrig_Exp);
  GetOutputList()->Add(h_METOrig_Exp);
  GetOutputList()->Add(h_METPhiOrig_Exp);
  GetOutputList()->Add(h_MHTPhiOrig_Exp);
  GetOutputList()->Add(h_DphiOneOrig_Exp);
  GetOutputList()->Add(h_DphiTwoOrig_Exp);
  GetOutputList()->Add(h_DphiThreeOrig_Exp);
  GetOutputList()->Add(h_DphiFourOrig_Exp);


  GetOutputList()->Add(h_HT_Pre);
  GetOutputList()->Add(h_MHT_Pre);
  GetOutputList()->Add(h_NJet_Pre);
  GetOutputList()->Add(h_NBtag_Pre);
  GetOutputList()->Add(h_HT_forQCD_Pre);
  GetOutputList()->Add(h_MHT_forQCD_Pre);
  GetOutputList()->Add(h_NJet_forQCD_Pre);
  GetOutputList()->Add(h_NBtag_forQCD_Pre);

  std::cout<<"Run on Data: "<<runOnData<<std::endl;
  std::cout<<"Run on SM MC: "<<runOnStandardModelMC<<std::endl;
  std::cout<<"Run on Signal MC: "<<runOnSignalMC<<std::endl;
  std::cout<<"----------------"<<std::endl;
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
}

Bool_t Prediction::Process(Long64_t entry)
{ //*AR-180619: Runs for every event
  //  std::cout<<"***Prediction::Process***"<<" entry "<<entry<<" jetid "<<JetID<<std::endl;
  h_CutFlow->Fill(0);
  resetValues();
  fChain->GetTree()->GetEntry(entry);
  //*AR:180917-HTgen_cut=0, hence this if condition has no role
  if(HTgen_cut > 0.01) if(madHT > HTgen_cut) return kTRUE;
  h_CutFlow->Fill(1);
  
  //  MuonsNum_ = Muons->size();
  //  ElectronsNum_ = Electrons->size();
  //*AR: 180917: NMuons and NElectrons are number of isolated electrons and muons(passing medium id)
  MuonsNum_ = NMuons;
  ElectronsNum_ = NElectrons;
  double newGenHT=0;double newGenMHT=0;
  TVector3 temp3Vec;
  vector<TVector3>GenHT3JetVec,GenMHT3JetVec;
  TVector3 newGenMHT3Vec;
  int BTagsfrmCSV=0;
  bool CheckPhi=false;
  bool CheckEta=false;

  bool CheckJetPhi=false;
  bool CheckJetEta=false;

  vector<TVector3>Jetsv2Recipe;
  vector<int> HTJetsIdxv2Recipe;
  vector<int> MHTJetsIdxv2Recipe;
  vector<int> MHTminusHTJetsIdxv2Recipe;
  vector<int> ElectronMatchJetIdxv2Recipe;
  vector<double> JetsCSVv2Recipe;
  vector<double> JetsJECv2Recipe;
  vector<double> JetschargedEmEnergyFractionv2Recipe;
  vector<double> JetschargedHadronEnergyFractionv2Recipe;
  vector<int> JetschargedHadronMultiplicityv2Recipe;
  vector<int> JetschargedMultiplicityv2Recipe;
  vector<double> JetselectronEnergyFractionv2Recipe;
  vector<int> JetselectronMultiplicityv2Recipe;
  //  vector<int> JetshadronFlavorv2Recipe;
  vector<double> JetshfEMEnergyFractionv2Recipe;
  vector<double> JetshfHadronEnergyFractionv2Recipe;
  vector<int> Jetsmultiplicityv2Recipe;
  vector<double> JetsmuonEnergyFractionv2Recipe;
  vector<int> JetsmuonMultiplicityv2Recipe;
  vector<double> JetsneutralEmEnergyFractionv2Recipe;
  vector<double> JetsneutralHadronEnergyFractionv2Recipe;
  vector<int> JetsneutralHadronMultiplicityv2Recipe;
  vector<int> JetsneutralMultiplicityv2Recipe;
  vector<double> JetsphotonEnergyFractionv2Recipe;
  vector<int> JetsphotonMultiplicityv2Recipe;
  //  vector<double> JetsqgLikelihoodv2Recipe;
  
  vector<TVector3>HTJetsv2Recipe;
  vector<double> HTJetsCSVv2Recipe;
  vector<double> HTJetsJECv2Recipe;

  vector<TVector3>MHTJetsv2Recipe;
  vector<double> MHTJetsCSVv2Recipe;
  vector<double> MHTJetsJECv2Recipe;

  vector<TVector3>MHTminusHTJetsv2Recipe;
  vector<double> MHTminusHTJetsCSVv2Recipe;
  vector<double> MHTminusHTJetsJECv2Recipe;

  HTv2Recipe=0.;
  HT5v2Recipe=0.; 
  HTRatiov2Recipe=0.;
  RecHTRatiov2Recipe=0.;
  MHTv2Recipe=0.;
  MHTPhiv2Recipe=-99.;
  TVector3 MHT3Vecv2Recipe;
  NJetsv2Recipe=0;
  NJetsforMHTminusHTv2Recipe=0;
  BTagsv2Recipe=0;
  DeltaPhi1v2Recipe=-99;
  HTDeltaPhi1v2Recipe=-99.;
  HTDeltaPhi2v2Recipe=-99.;
  HTDeltaPhi3v2Recipe=-99.;
  HTDeltaPhi4v2Recipe=-99.;


  MHTminusHTDeltaPhi1v2Recipe=-99.;
  MHTminusHTDeltaPhi2v2Recipe=-99.;
  MHTminusHTDeltaPhi3v2Recipe=-99.;
  MHTminusHTDeltaPhi4v2Recipe=-99.;


  int HTJetsDefault=0;
  int HTJetsv2=0;
  double PhiLeadJet=-99;

  //  std::cout<<" runnum1 "<<RunNum<<endl;

  //  if(runOnData && RunNum>=319077)
  //return kTRUE;
  AllEve++;
  
  //  std::cout<<" AllEve "<<AllEve<<endl;
  if(runOnData && GetSignalRegHists){
    /*
    if(!(RunNum>=320673 && RunNum<=321396))
      return kTRUE;
    
    */
    if(!(RunNum>=315257 && RunNum<=316202)){
      std::cout<<" skip run "<<RunNum<<endl;
      return kTRUE;
    }
    
  }      
  //std::cout<<" runnum "<<RunNum<<endl;
  //if(runOnData)
  //std::cout<<" run "<<RunNum<<" entry "<<entry<<" no HEM jet "<<endl;

  //  if(BTags>0)
  //std::cout<<" entry "<<" jets_size "<<Jets->size()<<" njets "<<NJets<<" btags "<<BTags<<endl;
  //*AR:181016: btags based on csv value instead of using value saved in ntuple
  for(unsigned j = 0; j < Jets->size(); ++j){
    // std::cout<<" j "<<j<<" pT "<<Jets->at(j).Pt()<<endl;
    double jetCSV=Jets_bJetTagDeepCSVprobb->at(j) + Jets_bJetTagDeepCSVprobbb->at(j);
    if(jetCSV>csvForBtag && Jets->at(j).Pt() > 30 && fabs(Jets->at(j).Eta())<2.4)
      BTagsfrmCSV++;
  }

  //*AR-181016: Recalculation of search variables after applying MET v2-recipe
  for(unsigned j = 0; j < Jets->size(); ++j){
    double jetPtv2Recipe= Jets->at(j).Pt()/Jets_jecFactor->at(j);
    //    if(jetPtv2Recipe >50 || (fabs(Jets->at(j).Eta()) < 2.65 || fabs(Jets->at(j).Eta()) > 3.139)){
    if(PhiLeadJet==-99.) 
      PhiLeadJet=Jets->at(j).Phi();
    //  std::cout<<" j "<<j<<" pt "<<Jets->at(j).Pt()<<" eta "<<fabs(Jets->at(j).Eta())<<endl;
    
    //      std::cout<<" j "<<j<<" passed v2 "<<" PhiLeadJet "<<PhiLeadJet<<endl;
    if(Jets->at(j).Pt()>30 && fabs(Jets->at(j).Eta()) < 2.4)
      HTJetsIdxv2Recipe.push_back(j);
    if(Jets->at(j).Pt()>30 && fabs(Jets->at(j).Eta()) < 5.0)
      MHTJetsIdxv2Recipe.push_back(j);
    if(Jets->at(j).Pt()>30 && fabs(Jets->at(j).Eta()) > 2.4 && fabs(Jets->at(j).Eta()) < 5.0)
      MHTminusHTJetsIdxv2Recipe.push_back(j); 
    //    } //end of METv2 recipe
  } //end of loop over jets
  NJetsforMHTminusHTv2Recipe=MHTminusHTJetsIdxv2Recipe.size();  
  for(unsigned int i=0;i<HTJetsIdxv2Recipe.size();i++){
    int jetIdx=HTJetsIdxv2Recipe[i];
    HTv2Recipe+=Jets->at(jetIdx).Pt();
    NJetsv2Recipe++;
    double deepCSV=Jets_bJetTagDeepCSVprobb->at(jetIdx) + Jets_bJetTagDeepCSVprobbb->at(jetIdx);
    if(deepCSV>csvForBtag)
      BTagsv2Recipe++;
  }

  for(unsigned int i=0;i<MHTJetsIdxv2Recipe.size();i++){
    int jetIdx=MHTJetsIdxv2Recipe[i];
    temp3Vec.SetPtEtaPhi(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
    MHT3Vecv2Recipe-=temp3Vec;
    HT5v2Recipe+=Jets->at(jetIdx).Pt();
  }

  if(BTagsv2Recipe != BTagsDeepCSV || BTagsfrmCSV != BTagsDeepCSV)
    std::cout<<" Btags calculated not equal to Btags from tree "<<" BTagsv2Recipe "<<BTagsv2Recipe<<" BTagsfrmCSV "<<BTagsfrmCSV<<" BTagsDeepCSV "<<BTagsDeepCSV<<endl; 

  /*
  for(unsigned int i=0;i<Jetsv2Recipe.size();i++){
    if(Jetsv2Recipe[i].Pt()>30 && fabs(Jetsv2Recipe[i].Eta())<2.4){
      HTv2Recipe+=Jetsv2Recipe[i].Pt();
      NJetsv2Recipe++;
      if(JetsCSVv2Recipe[i]>csvForBtag)
	BTagsv2Recipe++;
    }
    if(Jetsv2Recipe[i].Pt()>30 && fabs(Jetsv2Recipe[i].Eta())<5.0){
      MHT3Vecv2Recipe-=Jetsv2Recipe[i];
      HT5v2Recipe+=Jetsv2Recipe[i].Pt();
    }
  }
  */

  MHTv2Recipe=MHT3Vecv2Recipe.Pt(); 
  MHTPhiv2Recipe=MHT3Vecv2Recipe.Phi();
  
  if(AddHEMVeto){
    if(runOnData && RunNum>=319077){
      bool JetInHEMArea=false;
      for(unsigned j = 0; j < Jets->size(); ++j){
	CheckJetPhi=Jets->at(j).Pt() > 30 && Jets->at(j).Phi() < -0.67 && Jets->at(j).Phi() > -1.77;
	CheckJetEta=Jets->at(j).Pt() > 30 && Jets->at(j).Eta() < -1.2 && Jets->at(j).Eta() > -3.2;
	double DphiHEMJetMHT=fabs(TVector2::Phi_mpi_pi(Jets->at(j).Phi() - MHTPhiv2Recipe ));
	if(CheckJetPhi && CheckJetEta && (DphiHEMJetMHT<0.5)){
	  //if(CheckJetPhi && CheckJetEta){
	  HEMEve++;
	  //std::cout<<" run "<<RunNum<<" entry "<<entry<<" HEM jet "<<" j "<<j<<" pt "<<Jets->at(j).Pt()<<" eta "<<Jets->at(j).Eta()<<" phi "<<Jets->at(j).Phi()<<" dphi "<<DphiHEMJetMHT<<endl;
	  JetInHEMArea=true;
	  break;
	}
      }
      if(JetInHEMArea)
	return kTRUE;  
    }
  }

  //  std::cout<<" run "<<RunNum<<" entry "<<entry<<" passed event "<<endl;

  /*
    if(NJets ==2){
    std::cout<<" njets "<<NJets<<" njets-v2 "<<NJetsv2Recipe<<" ht-v2 "<<HTJetsv2Recipe.size()<<" HT old "<<HT<<" HT "<<HTv2Recipe<<" MHT old "<<MHT<<" MHT "<<MHTv2Recipe<<endl;
    
    std::cout<<" mht-v2 "<<MHTJetsv2Recipe.size()<<endl;
    
    std::cout<<" (mht-ht)-v2 "<<MHTminusHTJetsv2Recipe.size()<<endl;
    }
*/
  if(PhiLeadJet!=-99.)
    DeltaPhi1v2Recipe=fabs(TVector2::Phi_mpi_pi(PhiLeadJet- MHTPhiv2Recipe ));
  //  std::cout<<" PhiLeadJet "<<PhiLeadJet<<" MHTPhiv2Recipe "<<MHTPhiv2Recipe<<" DeltaPhi1v2Recipe "<<DeltaPhi1v2Recipe<<endl;
  //*AR-181017: get Dphi for leading 4 HT jets
  if(HTJetsIdxv2Recipe.size()>0)
    HTDeltaPhi1v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(HTJetsIdxv2Recipe[0]).Phi() - MHTPhiv2Recipe ));
  if(HTJetsIdxv2Recipe.size()>1)
    HTDeltaPhi2v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(HTJetsIdxv2Recipe[1]).Phi() - MHTPhiv2Recipe ));
  if(HTJetsIdxv2Recipe.size()>2)
    HTDeltaPhi3v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(HTJetsIdxv2Recipe[2]).Phi() - MHTPhiv2Recipe ));
  if(HTJetsIdxv2Recipe.size()>3)
    HTDeltaPhi4v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(HTJetsIdxv2Recipe[3]).Phi() - MHTPhiv2Recipe ));

  //*AR-181017: get Dphi for leading 4 (MHT-HT) jets

  if(MHTminusHTJetsIdxv2Recipe.size()>0)
    MHTminusHTDeltaPhi1v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(MHTminusHTJetsIdxv2Recipe[0]).Phi() - MHTPhiv2Recipe ));
  if(MHTminusHTJetsIdxv2Recipe.size()>1)
    MHTminusHTDeltaPhi2v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(MHTminusHTJetsIdxv2Recipe[1]).Phi() - MHTPhiv2Recipe ));
  if(MHTminusHTJetsIdxv2Recipe.size()>2)
    MHTminusHTDeltaPhi3v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(MHTminusHTJetsIdxv2Recipe[2]).Phi() - MHTPhiv2Recipe ));
  if(MHTminusHTJetsIdxv2Recipe.size()>3)
    MHTminusHTDeltaPhi4v2Recipe=fabs(TVector2::Phi_mpi_pi(Jets->at(MHTminusHTJetsIdxv2Recipe[3]).Phi() - MHTPhiv2Recipe ));
  /*
  if(HTDeltaPhi1v2Recipe!=DeltaPhi1v2Recipe){
    if(MHTminusHTDeltaPhi1v2Recipe!=DeltaPhi1v2Recipe){
  std::cout<<" HTDeltaPhi1v2Recipe "<<HTDeltaPhi1v2Recipe<<" MHTminusHTDeltaPhi1v2Recipe "<< MHTminusHTDeltaPhi1v2Recipe<<" DeltaPhi1v2Recipe "<<DeltaPhi1v2Recipe<<endl;
    }
  }
*/
  //END OF Recalculation of search variables


	   







  //*AR: 180917- only for signal
  if(runOnSignalMC && useGenHTMHT){
    for(unsigned j = 0; j < GenJets->size(); ++j){
      temp3Vec.SetPtEtaPhi(GenJets->at(j).Pt(),GenJets->at(j).Eta(),GenJets->at(j).Phi());
      if(GenJets->at(j).Pt() > 30 && fabs(GenJets->at(j).Eta())<2.4)
	GenHT3JetVec.push_back(temp3Vec);
      if(GenJets->at(j).Pt() > 30 && fabs(GenJets->at(j).Eta())<5)
	GenMHT3JetVec.push_back(temp3Vec);
    }
    for(unsigned int i=0;i<GenHT3JetVec.size();i++){
      newGenHT+=GenHT3JetVec[i].Pt();
    }  
    for(unsigned int i=0;i<GenMHT3JetVec.size();i++){
      newGenMHT3Vec-=GenMHT3JetVec[i]; 
    }  
    newGenMHT=newGenMHT3Vec.Pt();
  } //end of runOnSignalMC

  double LepPt=-99.0;
  double LepEta=-99.0;
  double LepPhi=-99.0;

  double ElePt=-99.0;
  double EleEta=-99.0;
  double ElePhi=-99.0;
  
  double MuPt=-99.0;
  double MuEta=-99.0;
  double MuPhi=-99.0;
  /*
  if(GenElectrons->size() + GenMuons->size() >= 1)
    h_CutFlow->Fill(20);


  if(GenTaus->size() > 0 && GenElectrons->size()==0 && GenMuons->size()==0){
    int HadronicTaus=0;
    for(unsigned i=0; i<GenTaus->size();i++){
      if(GenTaus_had->at(i)==1){
	HadronicTaus++;
      }
    }
    if(HadronicTaus >0)
      h_CutFlow->Fill(21);
  }
*/


  if(AddHEMVeto){
    //*AR-190207: HEM electron veto
    if(runOnData && RunNum>=319077){
      for(unsigned j=0; j< ElectronsNum_; j++){
	if(Electrons_passIso->at(j)){
	  double LepPhi=Electrons->at(j).Phi();
	  double LepEta=Electrons->at(j).Eta();
	  
	  CheckPhi=LepPhi < -0.87 && LepPhi > -1.57;
	  CheckEta=LepEta < -1.4 && LepEta > -3.0;
	  if(CheckPhi && CheckEta){
	    HEMEve++;
	    //	    std::cout<<" run "<<RunNum<<" entry "<<entry<<" HEM electron "<<" j "<<j<<" eta "<<LepEta<<" phi "<<LepPhi<<endl;
	    break;
	  }
	}
      }
      if(CheckPhi && CheckEta)
	return kTRUE;
    }
  }

  NonHEMEve++;

  //  std::cout<<" AllEve "<<AllEve<<" HEMeve "<<HEMEve<<" NonHEMEve "<<NonHEMEve<<endl;
  //  if(runOnData)
  //std::cout<<" run "<<RunNum<<" entry "<<entry<<" no HEM electron "<<endl;
  //*AR-181016: only considers single isolated lepton events(pT>20, eta<2.1) for CR and 0L events for signal region
  //pT>20 cut can be removed as MET triggers used for CR selection don't have any lepton pT threshold
  if(!GetSignalRegHists){
    if((MuonsNum_+ElectronsNum_) !=1) return kTRUE;
    h_CutFlow->Fill(2);
    if(MuonsNum_==1){
      h_CutFlow->Fill(19);
      for(unsigned int i=0;i<Muons->size();i++){
	if(Muons_passIso->at(i) && Muons_mediumID->at(i)){
	  LepPt=Muons->at(i).Pt();
	  LepEta=Muons->at(i).Eta();
	  LepPhi=Muons->at(i).Phi();

	  MuPt=Muons->at(i).Pt();
	  MuEta=Muons->at(i).Eta();
	  MuPhi=Muons->at(i).Phi();

	}
      }
    }

    if(ElectronsNum_==1){
      h_CutFlow->Fill(18);
      for(unsigned int i=0;i<Electrons->size();i++){
	if(Electrons_passIso->at(i)){
	  LepPt=Electrons->at(i).Pt();
	  LepEta=Electrons->at(i).Eta();
	  LepPhi=Electrons->at(i).Phi();

	  ElePt=Electrons->at(i).Pt();
	  EleEta=Electrons->at(i).Eta();
	  ElePhi=Electrons->at(i).Phi();
	}
      }
    }
    if(ElectronsNum_==1){
      CheckPhi=LepPhi < -0.87 && LepPhi > -1.57;
      CheckEta=LepEta < -1.4 && LepEta > -3.0;
      //    if(LepPt<20 || fabs(LepEta)>2.1)
      //if(CheckPhi && CheckEta)
      //return kTRUE;
    }
  } //end of if(!GetSignalRegHists)
  else{
    if((MuonsNum_+ElectronsNum_) !=0)
      return kTRUE;
    h_CutFlow->Fill(2);
  }
  //    std::cout<<"MHTdiff "<<MHTdiff<<" ht "<<HT<<" htv2 "<<HTv2Recipe<<" mht "<<MHT<<" mhtv2 "<<MHTv2Recipe<<" njets "<<NJets<<" njetv2 "<<NJetsv2Recipe<<" dphi1 "<<DeltaPhi1<<" dphiv2 "<<DeltaPhi1v2Recipe<<" dphi2 "<<DeltaPhi2<<" dphi2v2 "<<DeltaPhi2v2Recipe<<" dphi3 "<<DeltaPhi3<<"  dphi3v2 "<<DeltaPhi3v2Recipe<<" dphi4 "<<DeltaPhi4<< " dphi4v2 "<<DeltaPhi4v2Recipe<<endl;
  //*AR: 180917- Only consider events with HT>300, MHT>250, Njet>1.5
  if(runOnSignalMC && useGenHTMHT){
    if(newGenHT<minHT_ || newGenMHT< minMHT_ || NJetsv2Recipe < minNJets_  ) return kTRUE;
  }
  else{
    if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
    h_CutFlow->Fill(26);
    if(HTv2Recipe<minHT_ || MHTv2Recipe< minMHT_ || NJetsv2Recipe < minNJets_  ) return kTRUE;
    h_CutFlow->Fill(3);
  }

  //*AR: 180917-for high dphi: only events with all dphis>(0.5,0.5,0.3,0.3)
  //for low dphi: only events with either of dphis<(0.5,0.5,0.3,0.3)
  if(NJetsv2Recipe>=4){
    if(useDeltaPhiCut == 1)if(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_ || HTDeltaPhi4v2Recipe < deltaPhi4_) return kTRUE;
    if(useDeltaPhiCut == -1) if(!(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_ || HTDeltaPhi4v2Recipe < deltaPhi4_)) return kTRUE;

    if(ApplyHT5cut){
      double getHT5Cut;
      getHT5Cut = 5.3*(HT5v2Recipe/HTv2Recipe)-4.78;
      if(!(HTDeltaPhi1v2Recipe >= getHT5Cut || HT5v2Recipe/HTv2Recipe < 1.2)){
	//	std::cout<<" HTv2Recipe "<<HTv2Recipe<<" HT5v2Recipe "<<HT5v2Recipe<<" getHT5Cut "<<getHT5Cut<<" HTDeltaPhi1v2Recipe "<<HTDeltaPhi1v2Recipe<<endl;
	return kTRUE;
      }
    }
  }
  else if(NJetsv2Recipe==3){
    if(useDeltaPhiCut == 1)if(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_) return kTRUE;
    if(useDeltaPhiCut == -1) if(!(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_)) return kTRUE;
   
    if(ApplyHT5cut){
      double getHT5Cut;
      getHT5Cut = 5.3*(HT5v2Recipe/HTv2Recipe)-4.78;
      if(!(HTDeltaPhi1v2Recipe >= getHT5Cut || HT5v2Recipe/HTv2Recipe < 1.2)){
	//std::cout<<" HTv2Recipe "<<HTv2Recipe<<" HT5v2Recipe "<<HT5v2Recipe<<" getHT5Cut "<<getHT5Cut<<" HTDeltaPhi1v2Recipe "<<HTDeltaPhi1v2Recipe<<endl;
	return kTRUE;
      }
    }
  }
  else if(NJetsv2Recipe==2){
    if(useDeltaPhiCut == 1)if(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_) return kTRUE;
    if(useDeltaPhiCut == -1) if(!(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_)) return kTRUE;
  
    if(ApplyHT5cut){
      double getHT5Cut;
      getHT5Cut = 5.3*(HT5v2Recipe/HTv2Recipe)-4.78;
      if(!(HTDeltaPhi1v2Recipe >= getHT5Cut || HT5v2Recipe/HTv2Recipe < 1.2)){
	//	std::cout<<" HTv2Recipe "<<HTv2Recipe<<" HT5v2Recipe "<<HT5v2Recipe<<" getHT5Cut "<<getHT5Cut<<" HTDeltaPhi1v2Recipe "<<HTDeltaPhi1v2Recipe<<endl;
	return kTRUE;
      }
    }
    
  }
  else
    return kTRUE;
  h_CutFlow->Fill(4);
  //  if(useDeltaPhiCut == 1)  if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
  //  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
  
  if(applyFilters &&  !FiltersPass() ) return kTRUE;
  //*AR-180606:Only consider events with one isolated lepton at reco level and mT<100(no pT, eta cuts)
  if(runOnSignalMC)
    SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV17/scan/tree_SLm";
  if(runOnStandardModelMC)
    SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV17/tree_SLm";

  if(!GetSignalRegHists){
    if(MuonsNum_==1 && ElectronsNum_==0){
      for(unsigned int i=0;i<Muons->size();i++){
	if(Muons_passIso->at(i) && Muons_mediumID->at(i)){
	  mtw =  Muons_MTW->at(i);
	  //	  std::cout<<" muon_i "<<i<<" iso "<<Muons_passIso->at(i)<<" ID "<<Muons_mediumID->at(i)<<" mtw "<<Muons_MTW->at(i)<<endl;
	}
      }
      //std::cout<<" entry "<<entry<<" 1mu event "<<endl;
      
      //*AR: 180917- Gets skimfile for signal and standard model MC. No skimFile for data 
      //      if(runOnSignalMC)
      //SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_SLm";
      //      if(runOnStandardModelMC)
      //SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm";
    }else if(MuonsNum_==0 && ElectronsNum_==1){
      for(unsigned int i=0;i<Electrons->size();i++){
	if(Electrons_passIso->at(i))
	  mtw =  Electrons_MTW->at(i);
      }
      //std::cout<<" entry "<<entry<<" 1e event "<<endl;
      //      if(runOnSignalMC)
      //SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_SLe";
      //      if(runOnStandardModelMC)
      //SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLe";
    }
    //do not consider event if mT>100 
    if(mtw > 100) return kTRUE;
    h_CutFlow->Fill(14);
  }//end of if(!GetSignalRegHists)
//std::cout<<" passed mT cut "<<endl;
  isoTracksNum = isoElectronTracksNum + isoMuonTracksNum + isoPionTracksNum;
  //*AR: for 0L signal region, there should not be any isolated track
  if(GetSignalRegHists){
    if(isoTracksNum !=0)
      //  std::cout<<" isotrack nonzero "<<endl;
      return kTRUE;
    h_CutFlow->Fill(14);
  }
  /*
  for(unsigned i=0;i<TriggerNames->size();i++){
    std::cout<<" entry "<<entry<<" i "<<i<<" name "<< TriggerNames->at(i)<<endl;
  }
  */
//  std::cout<<" 108 "<<TriggerNames->at(108)<<" 110 "<<TriggerNames->at(110)<<" 114 "<<TriggerNames->at(114)<<" 124 "<<TriggerNames->at(124)<<" 126 "<<TriggerNames->at(126)<<" 129 "<<TriggerNames->at(129)<<endl;
  // Signal region MET triggers applied only for data

  if(useTrigger) if(!TriggerPass->at(109) && !TriggerPass->at(110) && !TriggerPass->at(111) && !TriggerPass->at(112) && !TriggerPass->at(113) && !TriggerPass->at(114) && !TriggerPass->at(115) && !TriggerPass->at(116) && !TriggerPass->at(117) && !TriggerPass->at(118) && !TriggerPass->at(119) && !TriggerPass->at(120) && !TriggerPass->at(124) && !TriggerPass->at(125) && !TriggerPass->at(126) && !TriggerPass->at(127) && !TriggerPass->at(128) && !TriggerPass->at(129) && !TriggerPass->at(130) && !TriggerPass->at(131) && !TriggerPass->at(132) && !TriggerPass->at(133)&& !TriggerPass->at(134) && !TriggerPass->at(135) && !TriggerPass->at(136)) return kTRUE;
  
  if(runOnSignalMC && useGenHTMHT){
    Bin_ = SearchBins_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,BTagsv2Recipe);
    BinQCD_ = SearchBinsQCD_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,BTagsv2Recipe);
  }
  else{
    //  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTagsfrmCSV);
    //    BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTagsfrmCSV);

    Bin_ = SearchBins_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,BTagsv2Recipe);
    BinQCD_ = SearchBinsQCD_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,BTagsv2Recipe);
  }
  //std::cout<<" entry "<<entry<<" Bin_ "<<Bin_<<" BinQCD_ "<<BinQCD_<<endl;
  //*AR-181016: Use only events falling into either of QCD search bins. Note that this includes events which fall inone of 223 bins but not any of 174 search bins. So integral of 1D plots in search variables might not be same as (slightly higher) than 174 search bin histogram integral.

  if(Bin_ > 900 && BinQCD_ > 900) return kTRUE;
  h_CutFlow->Fill(15);
  /*
  if(Bin_ > 900 && BinQCD_ < 900 && MHTv2Recipe>300)
    std::cout<<" entry of passed event "<<entry<<" Bin_ "<<Bin_<<" BinQCD_ "<<BinQCD_<<" HT "<<HTv2Recipe<<" MHT "<<MHTv2Recipe<<" NJet "<<NJetsv2Recipe<<" Btag "<<BTagsv2Recipe<<endl;
*/
  
  h_YieldCutFlow->Fill(0);

  if(EENoiseCutbyAditee){
    if((MHTminusHTJetsIdxv2Recipe.size()>0 && Jets->at(MHTminusHTJetsIdxv2Recipe[0]).Pt()>250 && (MHTminusHTDeltaPhi1v2Recipe>2.6 || MHTminusHTDeltaPhi1v2Recipe<0.1))|| (MHTminusHTJetsIdxv2Recipe.size()>1 && Jets->at(MHTminusHTJetsIdxv2Recipe[1]).Pt()>250 && (MHTminusHTDeltaPhi2v2Recipe>2.6 || MHTminusHTDeltaPhi2v2Recipe<0.1))){
      //      std::cout<<" pt1 "<< Jets->at(MHTminusHTJetsIdxv2Recipe[0]).Pt() <<" pt2 "<<Jets->at(MHTminusHTJetsIdxv2Recipe[1]).Pt()<<" dphi1 "<<MHTminusHTDeltaPhi1v2Recipe<<" dphi2 "<<MHTminusHTDeltaPhi2v2Recipe<<endl;
      return kTRUE;
    }
  }

  //*AR: 181107: check following condition if Dphi cut to be applied

  /*
  TFile *RatioBEvsFPhotonMultExcessfile = TFile::Open("btag/hFprime_Above2BelowPt5.root", "READ");
  h_RatioBEvsF = (TH2D*)RatioBEvsFPhotonMultExcessfile->Get("hFprime");
  bool ApplyPhotonMCut=false;

  
  for(unsigned int i=0;i<HTJetsIdxv2Recipe.size();i++){
    int binX=1+Jets->at(HTJetsIdxv2Recipe[i]).Pt()/50.0;
    int binY=1+Jets_photonMultiplicity->at(HTJetsIdxv2Recipe[i]);
    double getRatio=h_RatioBEvsF->GetBinContent(binX,binY);
    //    std::cout<<" pt "<<Jets->at(HTJetsIdxv2Recipe[i]).Pt()<<" photon "<<Jets_photonMultiplicity->at(HTJetsIdxv2Recipe[i])<<" binx "<<binX<<" biny "<<binY<<" ratio "<<getRatio<<endl;
    if(getRatio>2.0 || getRatio<0.5){
      ApplyPhotonMCut=true;
      //std::cout<<" event to be skipped"<<endl;
      break;
    }
  }
  if(ApplyPhotonMCut)
    return kTRUE;
*/




  h_YieldCutFlow->Fill(1);
  
  //  std::cout<<" evt falling in search bin "<<endl;
  //*AR: 180917- Initialization of vectors
  bTagProb = {1, 0, 0, 0};
  bTagBins = {Bin_, 0, 0, 0};
  bTagBinsQCD = {BinQCD_, 0, 0, 0};

  //  std::cout<<" *** Seg Vio1 *** "<<endl;
  if(topPTreweight){ //false
    if(GenParticles->size() != GenParticles_PdgId->size()){
      std::cout << "Cannot do top-pT reweighting!"<< std::endl; 
    }else{
      for(unsigned iGen = 0; iGen < GenParticles->size(); iGen++){
        if(std::abs(GenParticles_PdgId->at(iGen)) == 6){
          topPt.push_back(GenParticles->at(iGen).Pt());
        }
      }
      
      // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#Example
      if(topPt.size() == 2){
        // dilept
        if(GenElectrons->size() + GenMuons->size() == 2){
          topPtSF = std::sqrt(std::exp(0.148-0.00129*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.148-0.00129*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
	  // singlelept
        }else if(GenElectrons->size() + GenMuons->size() == 1){
          topPtSF = std::sqrt(std::exp(0.159-0.00141*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.159-0.00141*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
	  //had
        }else{
          // Usually non-promt (in hadTau evts): use average SF
          topPtSF = std::sqrt(std::exp(0.156-0.00137*(topPt.at(0) < 400. ? topPt.at(0) : 400.))*std::exp(0.156-0.00137*(topPt.at(1) < 400. ? topPt.at(1) : 400.)));
          //std::cout << "Cannot do top-pT reweighting! No leptonic top found."<< std::endl; 
        }
      }else{
        topPtSF = -1;
        std::cout << "Cannot do top-pT reweighting! More/Less than 2 tops found."<< std::endl; 
      }

    }

    // Normalization tested on SingleLept and DiLept samples (varies from ~98.9x-99.0x)
    topPtSF /= 0.99;
  } //end of if(topPTreweight)
  //std::cout<<" entry "<<entry<<" *** Seg Vio2 *** "<<endl;
  double madHTcut=0.0;
  //char SkimFile[500];
  if(runOnData){
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());
    TObjArray *optionArray = currentTree.Tokenize("/");
    TString currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
    currentFile = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
    //    std::cout<<" currentFile "<<currentFile<<endl;
  }


  if(!runOnData){
    //    string GetFastSimSkim=Skmname.c_str();
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());
    //    std::cout<<" currentTree "<<currentTree<<endl;
    //*AR- Only runs for every new tree
    if(currentTree != treeName){ //treeName = " "
      //  std::cout<<" new tree or new skimfile "<<endl;
      treeName = currentTree;
      OldSkimFilePath = SkimFilePath;
      TObjArray *optionArray = currentTree.Tokenize("/");
      TString currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
      currentFile = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
      string skimName="tree_TTJets_SingleLeptFromT_MC2018.root";
      char SkimFile[500];
      if(currentFile.find("TTJets_SingleLeptFromTbar")!=string::npos) skimName="tree_TTJets_SingleLeptFromTbar_MC2018.root"; 
      else if(currentFile.find("TTJets_SingleLeptFromT")!=string::npos) skimName="tree_TTJets_SingleLeptFromT_MC2018.root"; 
      else if(currentFile.find("DiLept")!=string::npos)skimName="tree_TTJets_DiLept_MC2018.root";
      else if(currentFile.find("TTJets_HT-600to800")!=string::npos)skimName="tree_TTJets_HT-600to800_MC2018.root";
      else if(currentFile.find("TTJets_HT-800to1200")!=string::npos)skimName="tree_TTJets_HT-800to1200_MC2018.root";
      else if(currentFile.find("TTJets_HT-1200to2500")!=string::npos)skimName="tree_TTJets_HT-1200to2500_MC2018.root";
      else if(currentFile.find("TTJets_HT-2500toInf")!=string::npos)skimName="tree_TTJets_HT-2500toInf_MC2018.root";
      else if(currentFile.find("Inclusive")!=string::npos)skimName="tree_TTJets_MC2018.root";
      else if(currentFile.find("WJetsToLNu_HT-100To200")!=string::npos)skimName="tree_WJetsToLNu_HT-100to200_MC2018.root";
      else if(currentFile.find("WJetsToLNu_HT-200To400")!=string::npos)skimName="tree_WJetsToLNu_HT-200to400_MC2018.root";
      else if(currentFile.find("WJetsToLNu_HT-400To600")!=string::npos)skimName="tree_WJetsToLNu_HT-400to600_MC2018.root";
      else if(currentFile.find("WJetsToLNu_HT-600To800")!=string::npos)skimName="tree_WJetsToLNu_HT-600to800_MC2018.root";
      else if(currentFile.find("WJetsToLNu_HT-800To1200")!=string::npos)skimName="tree_WJetsToLNu_HT-800to1200_MC2018.root";
      else if(currentFile.find("WJetsToLNu_HT-1200To2500")!=string::npos)skimName="tree_WJetsToLNu_HT-1200to2500_MC2018.root";
      else if(currentFile.find("WJetsToLNu_HT-2500ToInf")!=string::npos)skimName="tree_WJetsToLNu_HT-2500toInf_MC2018.root"; 
      else if(currentFile.find("tW_antitop")!=string::npos)skimName="tree_ST_tW_antitop_MC2018.root";
      else if(currentFile.find("tW_top")!=string::npos)skimName="tree_ST_tW_top_MC2018.root";
      else if(currentFile.find("t-channel_top")!=string::npos)skimName="tree_ST_t-channel_top_MC2018.root";
      else if(currentFile.find("t-channel_antitop")!=string::npos)skimName="tree_ST_t-channel_antitop_MC2018.root"; 
      else if(currentFile.find("s-channel")!=string::npos)skimName="tree_ST_s-channel_MC2018.root"; 
      else if(currentFile.find("ZZZ")!=string::npos)skimName="tree_ZZZ.root"; 
      else if(currentFile.find("ZZTo2L2Q")!=string::npos)skimName="tree_ZZTo2L2Q.root";
      else if(currentFile.find("WZZ")!=string::npos)skimName="tree_WZZ.root";
      else if(currentFile.find("WZTo1L3Nu")!=string::npos)skimName="tree_WZTo1L3Nu.root";
      else if(currentFile.find("WZTo1L1Nu2Q")!=string::npos)skimName="tree_WZTo1L1Nu2Q.root";
      else if(currentFile.find("WWZ")!=string::npos)skimName="tree_WWZ.root";
      else if(currentFile.find("WWTo2L2Nu")!=string::npos)skimName="tree_WWTo2L2Nu.root";
      else if(currentFile.find("WWTo1L1Nu2Q")!=string::npos)skimName="tree_WWTo1L1Nu2Q.root";
      else if(currentFile.find("TTZToQQ")!=string::npos)skimName="tree_TTZToQQ.root";
      else if(currentFile.find("TTZToLLNuNu")!=string::npos)skimName="tree_TTZToLLNuNu.root";
      else if(currentFile.find("TTWJetsToQQ")!=string::npos)skimName="tree_TTWJetsToQQ.root";
      else if(currentFile.find("TTWJetsToLNu")!=string::npos)skimName="tree_TTWJetsToLNu.root";
      else if(currentFile.find("TTTT")!=string::npos)skimName="tree_TTTT.root";
      else if(currentFile.find("TTGJets")!=string::npos)skimName="tree_TTGJets.root";

      //*AR: 180619-Gets skim file name for a new tree

      //std::cout<<" subSampleKey "<<subSampleKey<<endl;
      if(runOnSignalMC){
	vector<string> skimInput = skmInput(string(currFileName));
	//	std::cout<<" 0 "<<skimInput[0]<<" 1 "<<skimInput[1]<<" 2 "<<skimInput[2]<<" 3 "<<skimInput[3]<<" 4 "<<skimInput[4]<<endl;
	sprintf(SkimFile,"%s/tree_%s_%s_%s_fast.root",SkimFilePath.c_str(),skimInput[0].c_str(),skimInput[2].c_str(),skimInput[4].c_str());
      }
      else
	sprintf(SkimFile,"%s/%s",SkimFilePath.c_str(),skimName.c_str());

      //std::cout<<" currFileName "<<currFileName<<" skimFile "<<SkimFile<<endl;
      TFile *skimFile = TFile::Open(SkimFile, "READ");	

      //*AR: 180619-Sets attributes of isrcorr and btagcorr for a new tree 
      if(doISRcorr){//true only for signal MC
	TFile *skimFile = TFile::Open(SkimFile, "READ");
	h_njetsisr = (TH1*)skimFile->Get("NJetsISR");
	//        h_njetsisr = (TH1*) fChain->GetCurrentFile()->Get("NJetsISR");
	//isrfile = TFile::Open(path_ISRcorr, "READ");
	//h_isr = (TH1*)isrfile->Get("isr_weights_central");
	//	bool ISRcheck = false;
	//if(isrcorr!=0) ISRcheck=true;
	//	std::cout<<" ISRcheck "<<ISRcheck<<endl;
	//	std::cout<<" h_isr_1 "<<h_isr->GetBinContent(1)<<" h_isr_2 "<<h_isr->GetBinContent(2)<<endl;
	//	std::cout<<" h_njetisr_1 "<<h_njetsisr->GetBinContent(1)<<" h_njetisr_2 "<<h_njetsisr->GetBinContent(2)<<endl;

	if(isrcorr!=0){
          delete isrcorr;
          isrcorr = 0;
        }
        isrcorr = new ISRCorrector();
	//		isrcorr->SetWeights(h_njetsisr,h_njetsisr);

	isrcorr->SetWeights(h_isr,h_njetsisr);

      }
      
      if(doBTagCorr){ //true only for signal and standard model mc
        if(btagcorr!=0){
          delete btagcorr;
          btagcorr = 0;
        }

        btagcorr = new BTagCorrector();
	//runOnNtuples is true
        if(!runOnNtuples) btagcorr->SetEffs(fChain->GetCurrentFile());
        else{
	  TFile *skimFile = TFile::Open(SkimFile, "READ");
	  btagcorr->SetEffs(skimFile);
        }
	
        btagcorr->SetCalib(path_bTagCalib);        
        if(runOnSignalMC){
          btagcorr->SetCalibFastSim(path_bTagCalibFastSim);
          btagcorr->SetFastSim(true);
        }
        else btagcorr->SetFastSim(false);
      } //end of if(doBTagCorr)
      
      //*AR- Get a vector of pairs (susymothermass, xsec) based on name of new tree
      if(runOnSignalMC){ //false for SM MC
	//*AR-180618:xsecsT1T5, xsecsT2 are vector of pairs like (220,2259.15) 
        if((std::string(currentTree.Data()).find(std::string("T1"))) != std::string::npos || (std::string(currentTree.Data()).find(std::string("T5"))) != std::string::npos){
          xsecs = &xsecsT1T5;
          //std::cout<<"Using xsecs for gluino pair production!"<<std::endl;
        }else if((std::string(currentTree.Data()).find(std::string("T2"))) != std::string::npos){
          xsecs = &xsecsT2;
          //std::cout<<"Using xsecs for stop pair production!"<<std::endl;
        }else{
          std::cout<<"No valid dictionary with xsecs found!"<<std::endl;
          return kTRUE;
        }
      } //end of runOnSignalMC

      //*AR- Get relative weight of susy signal event based on mother mass for every new tree
      if(runOnSignalMC){
	TFile *skimFile = TFile::Open(SkimFile, "READ");
	TH1 *nEventProc = (TH1*)skimFile->Get("nEventProc");
	TH1 * nEventNeg = (TH1*)skimFile->Get("nEventNeg");
	//      TH1F *nEventProc = (TH1F*)fChain->GetCurrentFile()->Get("nEventProc");
	//TH1F *nEventNeg = (TH1F*)fChain->GetCurrentFile()->Get("nEventNeg");
	//*AR:180619-nEvtsTotal=fChain->GetEntries()
	nEvtsTotal = nEventProc->GetBinContent(1) - 2*nEventNeg->GetBinContent(1);
	//std::cout<<" nEventProc "<<nEventProc->GetBinContent(1)<<" nEventNeg "<<nEventNeg->GetBinContent(1)<<endl;
	//	std::cout<<" nEvtsTotal "<<nEvtsTotal<<" total "<<fChain->GetEntries()<<endl;
	xsec = 0;
	//*AR:180618--xsec is a vector of pair like (220,2259.15)
	//Once susy mother mass is found, get corresponding xsec and break the loop over susymasses in xsec vector
	for (std::vector<std::pair<double, double>>::iterator it = xsecs->begin() ; it != xsecs->end(); ++it){
	  if(std::abs(SusyMotherMass - it->first) < 0.1){
	    xsec = it->second;
	    break;
	  }
	}
	//*AR-180618: If no xsec is found for given susy mass, just skip the event
	if(xsec < 1e-10){
	  std::cout<<"No valid xsec found!"<<std::endl;
	  return kTRUE;
	}
	
      } //end of runOnSignalMC        
      
    }// end of if(currentTree != treeName)
    if(runOnSignalMC){
      Weight = xsec / nEvtsTotal;
      std::cout<<" weight_xsec "<<Weight<<endl;
      if(Weight < 0) Weight *= -1;
    }

    //*AR:180917:skip negative wt events
    if(Weight < 0)
      return kTRUE;
    h_CutFlow->Fill(16);

    if(currentFile.find("TTJets_SingleLeptFromTbar")!=string::npos || currentFile.find("TTJets_SingleLeptFromT")!=string::npos || currentFile.find("DiLept")!=string::npos){
      madHTcut=600;
      if(madHT > madHTcut){
	//	std::cout<<" currentTree "<<currentTree<<" entry "<<entry<<" madHT "<<madHT<< " &&&not passed&&& "<<endl;
	return kTRUE;
      }
      h_CutFlow->Fill(17);
    }

   
    if(doISRcorr){ //true for signal mc
      w_isr = isrcorr->GetCorrection(NJetsISR);
      Weight *= w_isr;
      //std::cout<<" weight_afterISRcorr "<<Weight<<endl;
    }

    if(doBTagCorr){ //true for signal and standard model mc
      bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
      if(runOnSignalMC && useGenHTMHT){
	bTagBins = {SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,0), SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,1), SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,2), NJetsv2Recipe < 3 ? 999 : SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,3)};  
	bTagBinsQCD = {SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,0), SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,1), SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,2), NJetsv2Recipe < 3 ? 999 : SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJetsv2Recipe,3)};
      }   
      else{
	bTagBins = {SearchBins_BTags_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,0), SearchBins_BTags_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,1), SearchBins_BTags_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,2), NJets < 3 ? 999 : SearchBins_BTags_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,3)};  
	bTagBinsQCD = {SearchBinsQCD_BTags_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,0), SearchBinsQCD_BTags_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,1), SearchBinsQCD_BTags_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,2), NJetsv2Recipe < 3 ? 999 : SearchBinsQCD_BTags_->GetBinNumber(HT,MHTv2Recipe,NJetsv2Recipe,3)};  }
      
    }
  } //end of if(!runOnData)
  
  if(runOnData && RunSelectiveEvents){
    //std::cout<<" RunSelectiveEvents before unblinding "<<endl;
    vector<int> RunBCDE;
    //    ifstream ifile("2017BCDE.json");
    bool MatchRun=false;      

    //   vector<int> RunF;
    if(currentFile.find("Run2017B")!=string::npos || currentFile.find("Run2017C")!=string::npos || currentFile.find("Run2017D")!=string::npos || currentFile.find("Run2017E")!=string::npos){
      //std::cout<<" bcde file "<<endl;
      ifstream ifile("2017BCDE.json");

      char filenames[500];
      //      char[500] filenames;
      while(ifile.getline(filenames, 500) )
	{
	  //	  RunBCDE.clear();
	  char *p;
	  const char s[2] = " ";
	  //int itrr=-1;
	  
	  p = strtok (filenames,s);
	  //   std::cout<<" eventN "<<eventN<<" p"<<p<<" ****** seg vio****** "<<endl;
	  
	  unsigned int CheckRunNum=atoi(p);
	  //  std::cout<<" EvtNum "<<EvtNum<<" p "<<p<<" checkRun "<<CheckRunNum<<" runtrue "<<RunNum<<endl;
	  if(CheckRunNum != RunNum)
	    continue;
	  else{
	    MatchRun=true;
	    break;
	  }
	}
      ifile.close();
      
    }
    if(currentFile.find("Run2017F")!=string::npos){
      //      std::cout<<" f file "<<endl;
      ifstream ifile("2017F.json");
      char filenames[500];
      //      char[500] filenames;
      while(ifile.getline(filenames, 500) )
	{
	  //	  RunBCDE.clear();
	  char *p;
	  const char s[2] = " ";
	  //int itrr=-1;
	  
	  p = strtok (filenames,s);
	  //   std::cout<<" eventN "<<eventN<<" p"<<p<<" ****** seg vio****** "<<endl;
	  
	  unsigned int CheckRunNum=atoi(p);
	  //	  std::cout<<" EvtNum "<<EvtNum<<" p "<<p<<" checkRun "<<CheckRunNum<<" runtrue "<<RunNum<<endl;
	  if(CheckRunNum != RunNum)
	    continue;
	  else{
	    MatchRun=true;
	    break;
	  }
	}
      ifile.close();

    }
    
    if(!MatchRun){
      //      std::cout<<" EvtNum "<<EvtNum<<" runtrue "<<RunNum<<" no match found in json "<<endl;
      return kTRUE;
    }
    
    if(RunNum == 299370 && LumiBlockNum>442){
      //      std::cout<<" skip event "<<endl;
      return kTRUE;
    }
    if(RunNum == 305178 && LumiBlockNum==75){
      //      std::cout<<" skip event "<<endl;
      return kTRUE;
    }
    if(RunNum == 305365 && LumiBlockNum>273){
      //      std::cout<<" skip event "<<endl;
      return kTRUE;
    }
    
    //    std::cout<<" passed event "<<" evt "<<EvtNum<<" run "<<RunNum<<" lumi "<<LumiBlockNum<<endl;

  } //end of if(runOnData && RunSelectiveEvents)


  if(runOnSignalMC){
    //Account for efficiency of JetID since we cannot apply it on fastSim
    Weight *= 0.99;
    //std::cout<<" weight_afterJetID "<<Weight<<endl;
  }
  //*AR: true only for signal MC and useGenHTMHT=false, as signal MC should account for trigger efficiency in data 
  if(useTriggerEffWeight){ // false for SM MC
    //GetSignalTriggerEffWeight and GetTriggerEffWeight are methods defined in LLTools.h and values are given as function of MHT.
    if(runOnSignalMC){
      Weight *= GetSignalTriggerEffWeight(HTv2Recipe,MHTv2Recipe);
      //std::cout<<" weight_afterTrigEff "<<Weight<<endl;
    }else{
      Weight *= GetTriggerEffWeight(MHTv2Recipe);
    }
  }

  if(doPUreweighting){ //true only for signal mc
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
    //std::cout<<" weight_afterpu "<<Weight<<endl;
    
  }
  
  if(runOnData){
    Weight = 1.;
    h_WeightBeforeScalePrefire_Exp->Fill(Weight,Weight);
    h_WeightBeforeScalePrefirevsGenHT_Exp->Fill(GenHT,Weight,Weight);
    h_WeightBeforeScalePrefirevsRecoHT_Exp->Fill(HTv2Recipe,Weight,Weight);

  }
  else{
    //*AR:180619: As /uscms_data/d3/arane/work/RA2bInterpretation/CMSSW_7_4_7/src/SCRA2BLE/DatacardBuilder/GenMHTCorrection.py scales signal contamination by lumi in /pb, here signal histograms are saved at 1/pb scale.
    if(!runOnSignalMC){
      h_WeightBeforeScalePrefire_Exp->Fill(Weight,Weight);
      h_WeightBeforeScalePrefirevsGenHT_Exp->Fill(GenHT,Weight,Weight);
      h_WeightBeforeScalePrefirevsRecoHT_Exp->Fill(HTv2Recipe,Weight,Weight);
      
      Weight *= scaleFactorWeight;
    }
  }
  //  std::cout<<" weight_afterlumiscale "<<Weight<<endl;

  if(GetNonPrefireProb){
    
    for(unsigned int i=0;i<MHTJetsIdxv2Recipe.size();i++){
      double NonPrefireWt=1.0;
      double NonPrefireJetWt=1.0;
      double NonPrefireMatchElectronWt=1.0;
      int jetIdx=MHTJetsIdxv2Recipe[i];
      double jPt=Jets->at(jetIdx).Pt();
      double jEta=Jets->at(jetIdx).Eta();
      double jPhi=Jets->at(jetIdx).Phi();
      int binX=jMap->GetXaxis()->FindBin(jEta);
      int binY=jMap->GetYaxis()->FindBin(jPt);
      NonPrefireJetWt=1-jMap->GetBinContent(binX,binY);
      //std::cout<<" jetidx "<<i<<" jPt "<<jPt<<" jEta "<<jEta<<" binX "<<binX<<" binY "<<binY<<" preWt "<<jMap->GetBinContent(binX,binY)<<" NonPrefireJetWt "<<NonPrefireJetWt<<endl;
      for(unsigned j = 0; j < Electrons->size(); ++j){
	if(Electrons_passIso->at(j)){
	  double pPt=Electrons->at(j).Pt();
	  double pEta=Electrons->at(j).Eta();
	  int binpX=pMap->GetXaxis()->FindBin(pEta);
	  int binpY=pMap->GetYaxis()->FindBin(pPt);
	  double PreElectronWt=pMap->GetBinContent(binpX,binpY);
	  //std::cout<<" photonidx "<<j<<" pPt "<<pPt<<" pEta "<<pEta<<" binpX "<<binpX<<" binpY "<<binpY<<" preWt "<<pMap->GetBinContent(binpX,binpY)<<" 1-prewt "<<1-pMap->GetBinContent(binpX,binpY)<<endl;
	    
	  double dEtaJetElectron=Electrons->at(j).Eta()-jEta;
	  double dPhiJetElectron=TVector2::Phi_mpi_pi(Electrons->at(j).Phi()-jPhi);
	  double dRJetElectron=sqrt(dEtaJetElectron * dEtaJetElectron + dPhiJetElectron * dPhiJetElectron);
	  if(dRJetElectron<0.4){
	    //std::cout<<" dRJetElectron "<<dRJetElectron<<endl;
	    NonPrefireMatchElectronWt *= (1-pMap->GetBinContent(binpX,binpY));
	    ElectronMatchJetIdxv2Recipe.push_back(j);
	  } //end of dRJetElectron
	    //	std::cout<<" electron "<<j<<" NonPrefireMatchElectronWt "<<NonPrefireMatchElectronWt<<endl;
	}//end of Electrons_passIso
      } //end of loop over electrons
      if(NonPrefireJetWt<NonPrefireMatchElectronWt)
	Weight *= NonPrefireJetWt;
      else
	Weight *= NonPrefireMatchElectronWt;
    } //end of loop over MHT jets
      //      std::cout<<"weight_afterjet "<<i<<" is "<<Weight<<endl;
    
      //    std::cout<<" weight_afterAllJets "<<Weight<<endl;
    for(unsigned j = 0; j < Electrons->size(); ++j){
      if(Electrons_passIso->at(j)){
	bool MatchedtoJet=false;
	double pPt=Electrons->at(j).Pt();
	double pEta=Electrons->at(j).Eta();
	int binpX=pMap->GetXaxis()->FindBin(pEta);
	int binpY=pMap->GetYaxis()->FindBin(pPt);
	double PreElectronWt=pMap->GetBinContent(binpX,binpY);
	//      std::cout<<" pPt "<<pPt<<" pEta "<<pEta<<" binpX "<<binpX<<" binpY "<<binpY<<" preWt "<<pMap->GetBinContent(binpX,binpY)<<" 1-prewt "<<1-pMap->GetBinContent(binpX,binpY)<<endl;
	  
	for(unsigned k = 0; k <ElectronMatchJetIdxv2Recipe.size();k++){
	  unsigned int electronIdx=ElectronMatchJetIdxv2Recipe[k];
	  if(j != electronIdx)
	    continue;
	  else{
	    MatchedtoJet=true;
	    break;
	  }
	} //end of loop over ElectronMatchJetIdxv2Recipe
	if(!MatchedtoJet){
	  Weight *= (1-pMap->GetBinContent(binpX,binpY));
	  //std::cout<<" weight after nonmatchedelectron "<<j<<" is "<<Weight<<endl;
	}
      } //end of Electrons_passIso
    } //end of loop over electrons
      //    std::cout<<" weight_afterAllElectrons "<<Weight<<endl;
  } // end of GetNonPrefireProb

    
    //*AR:181016-jet pT, eta distribution of those contributing to HT and excess ones contributing to  MHT in default case
  double LeadHTJetPt=-99;
  double LeadMHTminusHTJetPt=-99;
  bool foundLeadHTJet=false;
  bool foundLeadMHTminusHTJet=false;
  for(unsigned j = 0; j < Jets->size(); ++j){
    if(Jets->at(j).Pt()>30 && fabs(Jets->at(j).Eta()) <2.4){
      double rawPt=Jets->at(j).Pt()/Jets_jecFactor->at(j);
      if(!foundLeadHTJet){
	LeadHTJetPt=Jets->at(j).Pt();
	foundLeadHTJet=true;
      }
      h_rawJetPtforHT_Exp->Fill(rawPt);
      h_rawJetPtvsEtaforHT_Exp->Fill(rawPt,Jets->at(j).Eta());
      if(j<=3){
	h_JetPtforHTLead_Exp->Fill(Jets->at(j).Pt());
	h_JetEtaforHTLead_Exp->Fill(Jets->at(j).Eta());
      }
      else{
	h_JetPtforHTNotLead_Exp->Fill(Jets->at(j).Pt());
	h_JetEtaforHTNotLead_Exp->Fill(Jets->at(j).Eta());
      }
      
      h_JetPtforHT_Exp->Fill(Jets->at(j).Pt());
      h_JetEtaforHT_Exp->Fill(Jets->at(j).Eta());
      h_JetPtvsEtaforHT_Exp->Fill(Jets->at(j).Pt(),Jets->at(j).Eta());
    }

    if(Jets->at(j).Pt()>30 && fabs(Jets->at(j).Eta()) >2.4 && fabs(Jets->at(j).Eta()) <5.0){
      double rawPt=Jets->at(j).Pt()/Jets_jecFactor->at(j);
      if(!foundLeadMHTminusHTJet){
	LeadMHTminusHTJetPt=Jets->at(j).Pt();
	foundLeadMHTminusHTJet=true;
      }
      h_rawJetPtforMHTminusHT_Exp->Fill(rawPt);
      h_rawJetPtvsEtaforMHTminusHT_Exp->Fill(rawPt,Jets->at(j).Eta());
      if(j<=3){
	h_JetPtforMHTminusHTLead_Exp->Fill(Jets->at(j).Pt());
	h_JetEtaforMHTminusHTLead_Exp->Fill(Jets->at(j).Eta());
      }
      else{
	h_JetPtforMHTminusHTNotLead_Exp->Fill(Jets->at(j).Pt());
	  h_JetEtaforMHTminusHTNotLead_Exp->Fill(Jets->at(j).Eta());
      }
      h_JetPtforMHTminusHT_Exp->Fill(Jets->at(j).Pt());
      h_JetEtaforMHTminusHT_Exp->Fill(Jets->at(j).Eta());
      h_JetPtvsEtaforMHTminusHT_Exp->Fill(Jets->at(j).Pt(),Jets->at(j).Eta());
    }
  }  //end of jet pT, eta distribution in default case
    
  
  //*AR:181016-jet pT, eta distribution of those contributing to HT and excess ones contributing to  MHT after applying MET-v2 recipe
  double LeadHTJetv2RecipePt=-99;
  double LeadMHTminusHTJetv2RecipePt=-99;
  double LeadHTJetv2RecipeEta=-99;
  double LeadMHTminusHTJetv2RecipeEta=-99;
  double LeadHTJetv2RecipePhi=-99;
  double LeadMHTminusHTJetv2RecipePhi=-99;

  bool foundLeadHTJetv2Recipe=false;
  bool foundLeadMHTminusHTJetv2Recipe=false;
  
  for(unsigned int i=0;i<HTJetsIdxv2Recipe.size();i++){
    int jetIdx=HTJetsIdxv2Recipe[i]; 
    double DphiJetMHT=fabs(TVector2::Phi_mpi_pi(Jets->at(jetIdx).Phi() - MHTPhiv2Recipe ));
    h_JetPtvsDPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
    h_JetEtavsPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());

    if(i<=1){
      h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
      h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      if(Jets->at(jetIdx).Eta()>-1.0 && Jets->at(jetIdx).Eta()<1.0 && Jets->at(jetIdx).Phi()>1.3 && Jets->at(jetIdx).Phi()<2.6)
	h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
      if(Jets->at(jetIdx).Eta()>-2.4 && Jets->at(jetIdx).Eta()<-1.2 && Jets->at(jetIdx).Phi()>-1.8 && Jets->at(jetIdx).Phi()<-0.5)
	h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
    }

    /*  
    double rawPt=Jets->at(jetIdx).Pt()/Jets_jecFactor->at(jetIdx);
    if(!foundLeadHTJetv2Recipe){
      LeadHTJetv2RecipePt=Jets->at(jetIdx).Pt();
      LeadHTJetv2RecipeEta=Jets->at(jetIdx).Eta();
      LeadHTJetv2RecipePhi=Jets->at(jetIdx).Phi();
      foundLeadHTJetv2Recipe=true;
    }
    h_rawJetPtforHTv2Recipe_Exp->Fill(rawPt);
    h_rawJetPtvsEtaforHTv2Recipe_Exp->Fill(rawPt,Jets->at(jetIdx).Eta());
      
    h_chargedEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets_chargedEmEnergyFraction->at(jetIdx));
    h_chargedHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets_chargedHadronEnergyFraction->at(jetIdx));
    h_chargedHadronMultiplicityforHTv2Recipe_Exp->Fill(Jets_chargedHadronMultiplicity->at(jetIdx));  
    h_chargedMultiplicityforHTv2Recipe_Exp->Fill(Jets_chargedMultiplicity->at(jetIdx));
    h_electronEnergyFractionforHTv2Recipe_Exp->Fill(Jets_electronEnergyFraction->at(jetIdx));
    h_electronMultiplicityforHTv2Recipe_Exp->Fill(Jets_electronMultiplicity->at(jetIdx));
    //      h_hadronFlavorforHTv2Recipe_Exp->Fill(Jets_hadronFlavor->at(jetIdx)); 
    h_hfEMEnergyFractionforHTv2Recipe_Exp->Fill(Jets_hfEMEnergyFraction->at(jetIdx));
    h_hfHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets_hfHadronEnergyFraction->at(jetIdx));
    h_multiplicityforHTv2Recipe_Exp->Fill(Jets_multiplicity->at(jetIdx)); 
    h_muonEnergyFractionforHTv2Recipe_Exp->Fill(Jets_muonEnergyFraction->at(jetIdx)); 
    h_muonMultiplicityforHTv2Recipe_Exp->Fill(Jets_muonMultiplicity->at(jetIdx)); 
    h_neutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
    h_neutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_neutralHadronMultiplicityforHTv2Recipe_Exp->Fill(Jets_neutralHadronMultiplicity->at(jetIdx)); 
    h_neutralMultiplicityforHTv2Recipe_Exp->Fill(Jets_neutralMultiplicity->at(jetIdx));
    h_photonEnergyFractionforHTv2Recipe_Exp->Fill(Jets_photonEnergyFraction->at(jetIdx));
    h_photonMultiplicityforHTv2Recipe_Exp->Fill(Jets_photonMultiplicity->at(jetIdx));
    h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_photonMultiplicity->at(jetIdx));
    h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_photonMultiplicity->at(jetIdx));
    h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_photonMultiplicity->at(jetIdx));



     //  h_qgLikelihoodforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i]);
    
    if(i<=3){
      h_JetPtforHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Phi());
      if(i==0){
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi1v2Recipe);
	if(NJetsv2Recipe>=6 && BTagsv2Recipe==2){
	  h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),HTDeltaPhi1v2Recipe);
	  h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),HTDeltaPhi1v2Recipe);
	}
	if(NJetsv2Recipe>=6 && BTagsv2Recipe!=2){
	  h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),HTDeltaPhi1v2Recipe);
	  h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),HTDeltaPhi1v2Recipe);
	}
      }
      if(i==1){
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi2v2Recipe);
	if(NJetsv2Recipe>=6 && BTagsv2Recipe==2){
	  h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),HTDeltaPhi2v2Recipe);
	  h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),HTDeltaPhi2v2Recipe);
	}
	if(NJetsv2Recipe>=6 && BTagsv2Recipe!=2){
	  h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),HTDeltaPhi2v2Recipe);
	  h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),HTDeltaPhi2v2Recipe);
	}
      }
      if(i==2){
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi3v2Recipe);
      }
      if(i==3){
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi4v2Recipe);
      }
         
    }
    else{
	h_JetPtforHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Phi());
    }

*/
    h_JetPtforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Weight);
    h_JetEtaforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);
    if(Jets->at(jetIdx).Pt()>50)
      h_JetEtafor50forHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);
    if(Jets->at(jetIdx).Pt()>100)
      h_JetEtafor100forHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);
    if(Jets->at(jetIdx).Pt()>200)
      h_JetEtafor200forHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);

    h_JetPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Weight);
    /*
    if(BTagsv2Recipe==2){
      h_JetPtforTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
    }
    else{
      h_JetPtforNotTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforNotTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforNotTwoNbforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
    }

    if(NJetsv2Recipe<6){
      h_JetPtforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
      if(Jets->at(jetIdx).Pt()<500)
	h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());

      if(BTagsv2Recipe==0){
	h_JetPtforLowNJetfor0bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      if(BTagsv2Recipe==1){
	h_JetPtforLowNJetfor1bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      if(BTagsv2Recipe==2){
	h_JetPtforLowNJetfor2bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      if(BTagsv2Recipe>=3){
	h_JetPtforLowNJetfor3bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta());
      h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      if(i==0)
	h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),MHTPhiv2Recipe);
    }
    if(NJetsv2Recipe>=6){
      h_JetPtforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
      h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_photonMultiplicity->at(jetIdx));
      h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_photonMultiplicity->at(jetIdx));
      h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_photonMultiplicity->at(jetIdx));

      if(Jets->at(jetIdx).Pt()<500){
	h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
      }
      h_JetCSVforHighNJetforHTv2Recipe_Exp->Fill(Jets_bDiscriminatorCSV->at(jetIdx));
      h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_bDiscriminatorCSV->at(jetIdx));
      h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_bDiscriminatorCSV->at(jetIdx));
      h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_bDiscriminatorCSV->at(jetIdx));

      if(i<=3){
	h_JetPtforHighNJetLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHighNJetLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHighNJetLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      if(i>3){
	h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }

      if(BTagsv2Recipe==0){
	h_JetPtforHighNJetfor0bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      if(BTagsv2Recipe==1){
	h_JetPtforHighNJetfor1bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      if(BTagsv2Recipe==2){
	h_JetPtforHighNJetfor2bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }
      if(BTagsv2Recipe>=3){
	h_JetPtforHighNJetfor3bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      }    
      h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta());
      h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      if(i==0)
	h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),MHTPhiv2Recipe);
    }
    h_JetIdxvsEtaforHTv2Recipe_Exp->Fill(i,Jets->at(jetIdx).Eta());
    h_JetMultvsEtaforHTv2Recipe_Exp->Fill(HTJetsIdxv2Recipe.size(),Jets->at(jetIdx).Eta());
    h_JetPtvsEtaforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta());
    h_JetEtavsPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
    double DphiJetMHT=fabs(TVector2::Phi_mpi_pi(Jets->at(jetIdx).Phi() - MHTPhiv2Recipe ));
    double ChHadronToPhoton=-0.2;
    if(Jets_neutralHadronMultiplicity->at(jetIdx)!=0)
      ChHadronToPhoton=double(Jets_photonMultiplicity->at(jetIdx))/double(Jets_neutralHadronMultiplicity->at(jetIdx));
    //    std::cout<<" ch "<<Jets_neutralHadronMultiplicity->at(jetIdx)<<" pho "<<Jets_photonMultiplicity->at(jetIdx)<<" ChHadronToPhoton "<<ChHadronToPhoton<<endl;
    int binX=1+Jets->at(jetIdx).Pt()/50.0;
    int binY=1+Jets_photonMultiplicity->at(jetIdx);
    double getRatio=h_RatioBEvsF->GetBinContent(binX,binY);
      //    std::cout<<" pt "<<Jets->at(HTJetsIdxv2Recipe[i]).Pt()<<" photon "<<Jets_photonMultiplicity->at(HTJetsIdxv2Recipe[i])<<" binx "<<binX<<" biny "<<binY<<" ratio "<<getRatio<<endl;
    if(getRatio>2.0 || getRatio<0.5){
      h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp->Fill(Jets->at(jetIdx).Eta(),DphiJetMHT);
      h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp->Fill(Jets->at(jetIdx).Eta(),ChHadronToPhoton);
      h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp->Fill(Jets_chargedEmEnergyFraction->at(jetIdx));
      h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
    }
    else{
      h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp->Fill(Jets->at(HTJetsIdxv2Recipe[i]).Eta(),Jets->at(HTJetsIdxv2Recipe[i]).Phi());  
      h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp->Fill(Jets->at(HTJetsIdxv2Recipe[i]).Eta(),DphiJetMHT);  
      h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp->Fill(Jets->at(jetIdx).Eta(),ChHadronToPhoton);
      h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp->Fill(Jets_chargedEmEnergyFraction->at(jetIdx));
      h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
 
    }  
    h_JetPtvsPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Phi());
    
    double neutralEMbyphoton=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_photonEnergyFraction->at(jetIdx);
    double neutralEMbyneutralHadron=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_neutralHadronEnergyFraction->at(jetIdx);
    double neutralEMbychargedEM=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_chargedEmEnergyFraction->at(jetIdx);

    h_JetPtvsDPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
    h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_chargedEmEnergyFraction->at(jetIdx));
    h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_neutralEmEnergyFraction->at(jetIdx));
    /*  h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyphoton);
    h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyneutralHadron);
    h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbychargedEM);
    h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),neutralEMbyphoton);
    h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),neutralEMbyneutralHadron);
    h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),neutralEMbychargedEM);

    h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralEmEnergyFraction->at(jetIdx));
    h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralEmEnergyFraction->at(jetIdx));

    h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_chargedHadronEnergyFraction->at(jetIdx));
    h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    */
  }




  
  for(unsigned int i=0;i<MHTminusHTJetsIdxv2Recipe.size();i++){
    int jetIdx=MHTminusHTJetsIdxv2Recipe[i]; 
    double DphiJetMHT=fabs(TVector2::Phi_mpi_pi(Jets->at(jetIdx).Phi() - MHTPhiv2Recipe ));
    h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
    if(i<=1){
      h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
      h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      if((Jets->at(jetIdx).Eta()>2.4 && Jets->at(jetIdx).Eta()<2.6 && Jets->at(jetIdx).Phi()>2.2 && Jets->at(jetIdx).Phi()<2.4) || (Jets->at(jetIdx).Eta()>2.7 && Jets->at(jetIdx).Eta()<2.8 && Jets->at(jetIdx).Phi()>1.2 && Jets->at(jetIdx).Phi()<1.6) || (Jets->at(jetIdx).Eta()>2.8 && Jets->at(jetIdx).Eta()<2.9 && Jets->at(jetIdx).Phi()>-2.8 && Jets->at(jetIdx).Phi()<-2.7))
	h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
      
      if(Jets->at(jetIdx).Eta()>-3.2 && Jets->at(jetIdx).Eta()<-2.4 && Jets->at(jetIdx).Phi()>-1.8 && Jets->at(jetIdx).Phi()<-0.5)
	h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
    }
    /*
    double rawPt=Jets->at(jetIdx).Pt()/Jets_jecFactor->at(jetIdx);
    if(!foundLeadMHTminusHTJetv2Recipe){
      LeadMHTminusHTJetv2RecipePt=Jets->at(jetIdx).Pt();
      LeadMHTminusHTJetv2RecipeEta=Jets->at(jetIdx).Eta();
      LeadMHTminusHTJetv2RecipePhi=Jets->at(jetIdx).Phi();
      foundLeadMHTminusHTJetv2Recipe=true;
    }

    h_rawJetPtforMHTminusHTv2Recipe_Exp->Fill(rawPt);
    h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp->Fill(rawPt,Jets->at(jetIdx).Eta());
      
    h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_chargedEmEnergyFraction->at(jetIdx));
    h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_chargedHadronEnergyFraction->at(jetIdx));
    h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_chargedHadronMultiplicity->at(jetIdx));  
    h_chargedMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_chargedMultiplicity->at(jetIdx));
    h_electronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_electronEnergyFraction->at(jetIdx));
    h_electronMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_electronMultiplicity->at(jetIdx));
    //      h_hadronFlavorforMHTminusHTv2Recipe_Exp->Fill(Jets_hadronFlavor->at(jetIdx)); 
    h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_hfEMEnergyFraction->at(jetIdx));
    h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_hfHadronEnergyFraction->at(jetIdx));
    h_multiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_multiplicity->at(jetIdx)); 
    h_muonEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_muonEnergyFraction->at(jetIdx)); 
    h_muonMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_muonMultiplicity->at(jetIdx)); 
    h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
    h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_neutralHadronMultiplicity->at(jetIdx)); 
    h_neutralMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_neutralMultiplicity->at(jetIdx));
    h_photonEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_photonEnergyFraction->at(jetIdx));
    h_photonMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_photonMultiplicity->at(jetIdx));
     //  h_qgLikelihoodforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i]);
    
    if(i<=3){
      h_JetPtforMHTminusHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforMHTminusHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforMHTminusHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Phi());
      if(i==0)
	h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),MHTminusHTDeltaPhi1v2Recipe);
      if(i==1)
	h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),MHTminusHTDeltaPhi2v2Recipe);
      if(i==2)
	h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),MHTminusHTDeltaPhi3v2Recipe);
      if(i==3)
	h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),MHTminusHTDeltaPhi4v2Recipe);
    }
    else{
	h_JetPtforMHTminusHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforMHTminusHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforMHTminusHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Phi());
    }
*/
    h_JetPtforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Weight);
    h_JetEtaforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);
    if(Jets->at(jetIdx).Pt()>50)
      h_JetEtafor50forMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);
    if(Jets->at(jetIdx).Pt()>100)
      h_JetEtafor100forMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);
    if(Jets->at(jetIdx).Pt()>200)
      h_JetEtafor200forMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Weight);
    
    h_JetPhiforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Weight);
    /*
    h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp->Fill(i,Jets->at(jetIdx).Eta());
    h_JetMultvsEtaforMHTminusHTv2Recipe_Exp->Fill(MHTminusHTJetsIdxv2Recipe.size(),Jets->at(jetIdx).Eta());
    h_JetPtvsEtaforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta());
    h_JetEtavsPhiforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
    if(Jets->at(jetIdx).Pt()>400)
      h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());

    h_JetPtvsPhiforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Phi());
    
    double DphiJetMHT=fabs(TVector2::Phi_mpi_pi(Jets->at(jetIdx).Phi() - MHTPhiv2Recipe ));
    double neutralEMbyphoton=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_photonEnergyFraction->at(jetIdx);
    double neutralEMbyneutralHadron=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_neutralHadronEnergyFraction->at(jetIdx);
    double neutralEMbychargedEM=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_chargedEmEnergyFraction->at(jetIdx);

    h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
    h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_chargedEmEnergyFraction->at(jetIdx));
    h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_neutralEmEnergyFraction->at(jetIdx));
    /*
    h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyphoton);
    h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyneutralHadron);
        h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbychargedEM);
    h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),neutralEMbyphoton);
    h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),neutralEMbyneutralHadron);
    h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),neutralEMbychargedEM);

    h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralEmEnergyFraction->at(jetIdx));
    h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralEmEnergyFraction->at(jetIdx));

    h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_chargedHadronEnergyFraction->at(jetIdx));
    h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    */
  }
  


//end of jet pT, eta, phi distribution after v2 recipe


  int nLoops = 1;
  if(doBTagCorr) nLoops = (NJets == 2 ? 3 : 4);
  //*AR-180530: if(!runOnData),then bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);bTagBins=bTagBinsQCD = {(HT,MHT,NJet,0),(HT,MHT,NJet,1),(HT,MHT,NJet,2),(HT,MHT,NJet,3)}; else bTagProb = {1, 0, 0, 0} and bTagBins=bTagBinsQCD ={(HT,MHT,NJets,BTagsfrmCSV),0,0,0}.
  // This is because we do not know jet flavours in case of data hence can not calculate btag probability. There is jets_flavour branch saved also for data, but it has zero content.  
  /*
    for(int i=0;i<Jets->size();i++){
    std::cout<<" flavour "<<abs(Jets_flavor->at(i))<<endl;
    }
  */
  for(int i = 0; i < nLoops; i++){
    double WeightBtagProb = Weight*bTagProb.at(i);
    unsigned bTagBin = bTagBins.at(i);
    unsigned bTagBinQCD = bTagBinsQCD.at(i);
    //std::cout<<" WeightBtagProb "<<WeightBtagProb<<endl;
    double TF = -1;

    if(AddHEMVeto && runOnData && RunNum>=319077){
      //      std::cout<<" TF_RmHEMEleJet "<<endl;
      if(applySFs){ //true for data
	TF = h_0L1L_RmHEMEleJet_SF_SB->GetBinContent(bTagBinQCD);
	if(TF < 0) TF = h_0L1L_RmHEMEleJet_SB->GetBinContent(bTagBinQCD);
      }else{ //true for SM and signal MC
	TF = h_0L1L_RmHEMEleJet_SB->GetBinContent(bTagBinQCD);
      }
    }
    else{
      //      std::cout<<" TF "<<endl;
      if(applySFs){ //true for data
	TF = h_0L1L_SF_SB->GetBinContent(bTagBinQCD);
	if(TF < 0) TF = h_0L1L_SB->GetBinContent(bTagBinQCD);
      }else{ //true for SM and signal MC
	TF = h_0L1L_SB->GetBinContent(bTagBinQCD);
      }
    }


    HTRatio=HT5/HT;
    HTRatiov2Recipe=HT5v2Recipe/HTv2Recipe;
    RecHTRatiov2Recipe=1/HTRatiov2Recipe;    
    //    std::cout<<" i "<<i<<" bTagBin "<<bTagBin<<" bTagBinQCD "<<bTagBinQCD<<" *** Seg Vio3 *** "<<endl;
    //*AR: 180917- These histograms represent yield in CR as TF is not applied
    h_CSStat->Fill(bTagBin, WeightBtagProb);
    h_CSStat_MHTVsNbjet->Fill(MHTv2Recipe,BTagsfrmCSV,WeightBtagProb);
    h_HT_Exp->Fill(HT,WeightBtagProb);
    h_HT5_Exp->Fill(HT5,WeightBtagProb);
    h_HTRatio_Exp->Fill(HTRatio,WeightBtagProb);
    h_MHT_Exp->Fill(MHT,WeightBtagProb);
    h_MET_Exp->Fill(MET,WeightBtagProb);
    h_MHTPhi_Exp->Fill(MHTPhi,WeightBtagProb);
    h_METPhi_Exp->Fill(METPhi,WeightBtagProb);
    h_mT_Exp->Fill(mtw,WeightBtagProb);
    h_NJet_Exp->Fill(NJets,WeightBtagProb);
    h_NBtag_Exp->Fill(BTagsfrmCSV,WeightBtagProb);
    h_DphiOne_Exp->Fill(DeltaPhi1,WeightBtagProb);
    h_DphiTwo_Exp->Fill(DeltaPhi2,WeightBtagProb);
    h_DphiThree_Exp->Fill(DeltaPhi3,WeightBtagProb);
    h_DphiFour_Exp->Fill(DeltaPhi4,WeightBtagProb);
    h_LepPt_Exp->Fill(LepPt,WeightBtagProb);
    h_LepEta_Exp->Fill(LepEta,WeightBtagProb);
    if(LepPt>50)
      h_LepEtafor50_Exp->Fill(LepEta,WeightBtagProb);
    if(LepPt>100)
      h_LepEtafor100_Exp->Fill(LepEta,WeightBtagProb);
    if(LepPt>200)
      h_LepEtafor200_Exp->Fill(LepEta,WeightBtagProb);

    h_LepPhi_Exp->Fill(LepPhi,WeightBtagProb);

    if(ElePt>0.0){
      double LepMETDphi=fabs(TVector2::Phi_mpi_pi(ElePhi- METPhi));
      h_ElePt_Exp->Fill(ElePt,WeightBtagProb);
      h_EleEta_Exp->Fill(EleEta,WeightBtagProb);
      h_ElePhi_Exp->Fill(ElePhi,WeightBtagProb);
      h_EleEtavsPt_Exp->Fill(EleEta,ElePt,WeightBtagProb);
      h_EleEtavsPhi_Exp->Fill(EleEta,ElePhi,WeightBtagProb);
      h_EleEtavsMT_Exp->Fill(EleEta,mtw,WeightBtagProb);
      h_EleEtavsHT_Exp->Fill(EleEta,HTv2Recipe,WeightBtagProb);
      h_EleEtavsMHT_Exp->Fill(EleEta,MHTv2Recipe,WeightBtagProb);
      h_EleEtavsNJet_Exp->Fill(EleEta,NJetsv2Recipe,WeightBtagProb);
      h_EleEtavsNBtag_Exp->Fill(EleEta,BTagsfrmCSV,WeightBtagProb);
      h_EleMTvsPt_Exp->Fill(mtw,ElePt,WeightBtagProb);
      h_EleMTvsMET_Exp->Fill(mtw,MET,WeightBtagProb);
      h_EleMTvsDphi_Exp->Fill(mtw,LepMETDphi,WeightBtagProb);
      /*
      bool CheckJetEle=(CheckEta && CheckPhi) || (CheckJetPhi && CheckJetEta);
      //      std::cout<<" entry "<<entry<<" electron evt "<<" CheckEta "<<CheckEta<<" CheckPhi "<<CheckPhi<<" CheckJetPhi "<<CheckJetPhi<<" CheckJetEta "<<CheckJetEta<<" CheckJetEle "<<CheckJetEle<<endl; 

      if(CheckJetEle){
	//	std::cout<<" entry "<<entry<< " HEM veto "<<endl;
	h_HEMEleEtavsPt_Exp->Fill(EleEta,ElePt,WeightBtagProb);
	h_HEMEleEtavsPhi_Exp->Fill(EleEta,ElePhi,WeightBtagProb);
	h_HEMEleEtavsMT_Exp->Fill(EleEta,mtw,WeightBtagProb);
	h_HEMEleEtavsHT_Exp->Fill(EleEta,HTv2Recipe,WeightBtagProb);
	h_HEMEleEtavsMHT_Exp->Fill(EleEta,MHTv2Recipe,WeightBtagProb);
	h_HEMEleEtavsNJet_Exp->Fill(EleEta,NJetsv2Recipe,WeightBtagProb);
	h_HEMEleEtavsNBtag_Exp->Fill(EleEta,BTagsfrmCSV,WeightBtagProb);
	h_HEMEleMTvsPt_Exp->Fill(mtw,ElePt,WeightBtagProb);
	h_HEMEleMTvsMET_Exp->Fill(mtw,MET,WeightBtagProb);
	h_HEMEleMTvsDphi_Exp->Fill(mtw,LepMETDphi,WeightBtagProb);
	
      }
*/
    }

    if(MuPt>0.0){
      double LepMETDphi=fabs(TVector2::Phi_mpi_pi(MuPhi- METPhi));
      h_MuPt_Exp->Fill(MuPt,WeightBtagProb);
      h_MuEta_Exp->Fill(MuEta,WeightBtagProb);
      h_MuPhi_Exp->Fill(MuPhi,WeightBtagProb);

      h_EleEtavsPt_Exp->Fill(MuEta,MuPt,WeightBtagProb);
      h_EleEtavsPhi_Exp->Fill(MuEta,MuPhi,WeightBtagProb);
      h_EleEtavsMT_Exp->Fill(MuEta,mtw,WeightBtagProb);
      h_EleEtavsHT_Exp->Fill(MuEta,HTv2Recipe,WeightBtagProb);
      h_EleEtavsMHT_Exp->Fill(MuEta,MHTv2Recipe,WeightBtagProb);
      h_EleEtavsNJet_Exp->Fill(MuEta,NJetsv2Recipe,WeightBtagProb);
      h_EleEtavsNBtag_Exp->Fill(MuEta,BTagsfrmCSV,WeightBtagProb);
      h_EleMTvsPt_Exp->Fill(mtw,MuPt,WeightBtagProb);
      h_EleMTvsMET_Exp->Fill(mtw,MET,WeightBtagProb);
      h_EleMTvsDphi_Exp->Fill(mtw,LepMETDphi,WeightBtagProb);
      /*  
	  bool CheckJetEle=(CheckEta && CheckPhi) || (CheckJetPhi && CheckJetEta);
      //      std::cout<<" entry "<<entry<<" muon evt "<<" CheckEta "<<CheckEta<<" CheckPhi "<<CheckPhi<<" CheckJetPhi "<<CheckJetPhi<<" CheckJetEta "<<CheckJetEta<<" CheckJetEle "<<CheckJetEle<<endl; 

      if(CheckJetEle){
	//std::cout<<" entry "<<entry<< " HEM veto "<<endl;

	h_HEMEleEtavsPt_Exp->Fill(MuEta,MuPt,WeightBtagProb);
	h_HEMEleEtavsPhi_Exp->Fill(MuEta,MuPhi,WeightBtagProb);
	h_HEMEleEtavsMT_Exp->Fill(MuEta,mtw,WeightBtagProb);
	h_HEMEleEtavsHT_Exp->Fill(MuEta,HTv2Recipe,WeightBtagProb);
	h_HEMEleEtavsMHT_Exp->Fill(MuEta,MHTv2Recipe,WeightBtagProb);
	h_HEMEleEtavsNJet_Exp->Fill(MuEta,NJetsv2Recipe,WeightBtagProb);
	h_HEMEleEtavsNBtag_Exp->Fill(MuEta,BTagsfrmCSV,WeightBtagProb);
	h_HEMEleMTvsPt_Exp->Fill(mtw,MuPt,WeightBtagProb);
	h_HEMEleMTvsMET_Exp->Fill(mtw,MET,WeightBtagProb);
	h_HEMEleMTvsDphi_Exp->Fill(mtw,LepMETDphi,WeightBtagProb);
	
      }
*/

    }

    h_HTclean_Exp->Fill(HTclean,WeightBtagProb);
    h_HT5clean_Exp->Fill(HT5clean,WeightBtagProb);   
    h_MHTclean_Exp->Fill(MHTclean,WeightBtagProb);
    h_METclean_Exp->Fill(METclean,WeightBtagProb);
    h_MHTPhiclean_Exp->Fill(MHTPhiclean,WeightBtagProb);
    h_METPhiclean_Exp->Fill(METPhiclean,WeightBtagProb);
    h_mTclean_Exp->Fill(mtw,WeightBtagProb);
    h_NJetclean_Exp->Fill(NJetsclean,WeightBtagProb);
    h_NBtagclean_Exp->Fill(BTagsfrmCSV,WeightBtagProb);
    h_DphiOneclean_Exp->Fill(DeltaPhi1clean,WeightBtagProb);
    h_DphiTwoclean_Exp->Fill(DeltaPhi2clean,WeightBtagProb);
    h_DphiThreeclean_Exp->Fill(DeltaPhi3clean,WeightBtagProb);
    h_DphiFourclean_Exp->Fill(DeltaPhi4clean,WeightBtagProb);
    h_LepPtclean_Exp->Fill(LepPt,WeightBtagProb);
    h_LepEtaclean_Exp->Fill(LepEta,WeightBtagProb);
    h_LepPhiclean_Exp->Fill(LepPhi,WeightBtagProb);

    h_Weight_Exp->Fill(WeightBtagProb,WeightBtagProb);
    h_GenHT_Exp->Fill(GenHT,WeightBtagProb);

    h_HTv2Recipe_Exp->Fill(HTv2Recipe,WeightBtagProb);
    if(MHTv2Recipe>250 && MHTv2Recipe<300)
      h_HTv2Recipe_forQCD_Exp->Fill(HTv2Recipe,WeightBtagProb);

    if(BTagsv2Recipe==2){
      h_HTforTwoNbv2Recipe_Exp->Fill(HTv2Recipe,WeightBtagProb);
      h_HTRatioforTwoNbv2Recipe_Exp->Fill(HTRatiov2Recipe,WeightBtagProb);
      h_MHTforTwoNbv2Recipe_Exp->Fill(MHTv2Recipe,WeightBtagProb);
      h_MHTPhiforTwoNbv2Recipe_Exp->Fill(MHTPhiv2Recipe,WeightBtagProb);
      h_NJetforTwoNbv2Recipe_Exp->Fill(NJetsv2Recipe,WeightBtagProb);
    }
    else{
      h_HTforNotTwoNbv2Recipe_Exp->Fill(HTv2Recipe,WeightBtagProb);
      h_HTRatioforNotTwoNbv2Recipe_Exp->Fill(HTRatiov2Recipe,WeightBtagProb);
      h_MHTforNotTwoNbv2Recipe_Exp->Fill(MHTv2Recipe,WeightBtagProb);
      h_MHTPhiforNotTwoNbv2Recipe_Exp->Fill(MHTPhiv2Recipe,WeightBtagProb);
      h_NJetforNotTwoNbv2Recipe_Exp->Fill(NJetsv2Recipe,WeightBtagProb);
    }

    if(NJetsv2Recipe<6){
      h_HTvsMHTforLowNJetv2Recipe_Exp->Fill(HTv2Recipe,MHTv2Recipe);
      h_HTforLowNJetv2Recipe_Exp->Fill(HTv2Recipe,WeightBtagProb);
      h_MHTforLowNJetv2Recipe_Exp->Fill(MHTv2Recipe,WeightBtagProb);
      h_HTRatioforLowNJetv2Recipe_Exp->Fill(HTRatiov2Recipe,WeightBtagProb);
      h_NBtagforLowNJetv2Recipe_Exp->Fill(BTagsv2Recipe,WeightBtagProb);
    }
    if(NJetsv2Recipe>=6){
      h_HTvsMHTforHighNJetv2Recipe_Exp->Fill(HTv2Recipe,MHTv2Recipe);
      h_HTforHighNJetv2Recipe_Exp->Fill(HTv2Recipe,WeightBtagProb);
      h_MHTforHighNJetv2Recipe_Exp->Fill(MHTv2Recipe,WeightBtagProb);
      h_HTRatioforHighNJetv2Recipe_Exp->Fill(HTRatiov2Recipe,WeightBtagProb);
      h_NBtagforHighNJetv2Recipe_Exp->Fill(BTagsv2Recipe,WeightBtagProb);
    }

    h_HT5v2Recipe_Exp->Fill(HT5v2Recipe,WeightBtagProb);
    h_HTRatiov2Recipe_Exp->Fill(HTRatiov2Recipe,WeightBtagProb);
    h_MHTv2Recipe_Exp->Fill(MHTv2Recipe,WeightBtagProb);
    h_MHTv2Recipe_forQCD_Exp->Fill(MHTv2Recipe,WeightBtagProb);

    h_MHTPhiv2Recipe_Exp->Fill(MHTPhiv2Recipe,WeightBtagProb);

    if(NJetsv2Recipe<6){
      h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp->Fill(MHTPhiv2Recipe,HTRatiov2Recipe);
      h_MHTPhiforLowNJetv2Recipe_Exp->Fill(MHTPhiv2Recipe,WeightBtagProb);
    }
    if(NJetsv2Recipe>=6){
      h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp->Fill(MHTPhiv2Recipe,HTRatiov2Recipe);
      h_MHTPhiforHighNJetv2Recipe_Exp->Fill(MHTPhiv2Recipe,WeightBtagProb);
    }
    h_NJetv2Recipe_Exp->Fill(NJetsv2Recipe,WeightBtagProb);
    if(MHTv2Recipe>250 && MHTv2Recipe<300)
      h_NJetv2Recipe_forQCD_Exp->Fill(NJetsv2Recipe,WeightBtagProb);

    h_NJetvsHTv2Recipe_Exp->Fill(NJetsv2Recipe,HTv2Recipe);
    h_NJetvsMHTv2Recipe_Exp->Fill(NJetsv2Recipe,MHTv2Recipe);
    h_NJetvsMHTPhiv2Recipe_Exp->Fill(NJetsv2Recipe,MHTPhiv2Recipe);
    h_NJetvsNBtagv2Recipe_Exp->Fill(NJetsv2Recipe,BTagsv2Recipe);
    double BTagFrac=BTagsv2Recipe/NJetsv2Recipe;
    h_NJetvsNBFracv2Recipe_Exp->Fill(NJetsv2Recipe,BTagFrac);

    h_NJetforMHTminusHTv2Recipe_Exp->Fill(NJetsforMHTminusHTv2Recipe,WeightBtagProb);

    h_NBtagv2Recipe_Exp->Fill(BTagsv2Recipe,WeightBtagProb);
    if(MHTv2Recipe>250 && MHTv2Recipe<300)
      h_NBtagv2Recipe_forQCD_Exp->Fill(BTagsv2Recipe,WeightBtagProb);

    h_DphiOneforHTv2Recipe_Exp->Fill(HTDeltaPhi1v2Recipe,WeightBtagProb);
    h_DphiTwoforHTv2Recipe_Exp->Fill(HTDeltaPhi2v2Recipe,WeightBtagProb);
    h_DphiThreeforHTv2Recipe_Exp->Fill(HTDeltaPhi3v2Recipe,WeightBtagProb);
    h_DphiFourforHTv2Recipe_Exp->Fill(HTDeltaPhi4v2Recipe,WeightBtagProb);
    h_JetPtvsHTRatioforHTv2Recipe_Exp->Fill(LeadHTJetv2RecipePt,HTRatiov2Recipe);
    h_JetEtavsHTRatioforHTv2Recipe_Exp->Fill(LeadHTJetv2RecipeEta,HTRatiov2Recipe);
    h_JetPhivsHTRatioforHTv2Recipe_Exp->Fill(LeadHTJetv2RecipePhi,HTRatiov2Recipe);
    h_MHTPhivsJetPhiforHTv2Recipe_Exp->Fill(MHTPhiv2Recipe,LeadHTJetv2RecipePhi);
    // if(RecHTRatiov2Recipe>1.0 || HTDeltaPhi1v2Recipe>3.2 || HTDeltaPhi1v2Recipe<0)
    h_RecHTRatiovsDPhiforHTv2Recipe_Exp->Fill(RecHTRatiov2Recipe,HTDeltaPhi1v2Recipe);
    h_RecHTRatiovsDPhiforAllv2Recipe_Exp->Fill(RecHTRatiov2Recipe,DeltaPhi1v2Recipe);

    h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp->Fill(LeadMHTminusHTJetv2RecipePt,HTRatiov2Recipe);
    h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp->Fill(LeadMHTminusHTJetv2RecipeEta,HTRatiov2Recipe);
    h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp->Fill(LeadMHTminusHTJetv2RecipePhi,HTRatiov2Recipe);
    h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp->Fill(MHTPhiv2Recipe,LeadMHTminusHTJetv2RecipePhi);

    h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp->Fill(RecHTRatiov2Recipe,MHTminusHTDeltaPhi1v2Recipe);

    h_DphiOneforMHTminusHTv2Recipe_Exp->Fill(MHTminusHTDeltaPhi1v2Recipe,WeightBtagProb);
    h_DphiTwoforMHTminusHTv2Recipe_Exp->Fill(MHTminusHTDeltaPhi2v2Recipe,WeightBtagProb);
    h_DphiThreeforMHTminusHTv2Recipe_Exp->Fill(MHTminusHTDeltaPhi3v2Recipe,WeightBtagProb);
    h_DphiFourforMHTminusHTv2Recipe_Exp->Fill(MHTminusHTDeltaPhi4v2Recipe,WeightBtagProb);


    h_MHTOrig_Exp->Fill(MHTOrig,WeightBtagProb);
    h_METOrig_Exp->Fill(METOrig,WeightBtagProb);
    h_MHTPhiOrig_Exp->Fill(MHTPhiOrig,WeightBtagProb);
    h_METPhiOrig_Exp->Fill(METPhiOrig,WeightBtagProb);
    h_DphiOneOrig_Exp->Fill(DeltaPhi1Orig,WeightBtagProb);
    h_DphiTwoOrig_Exp->Fill(DeltaPhi2Orig,WeightBtagProb);
    h_DphiThreeOrig_Exp->Fill(DeltaPhi3Orig,WeightBtagProb);
    h_DphiFourOrig_Exp->Fill(DeltaPhi4Orig,WeightBtagProb);
    
    //*AR: 180917- These histograms represent yield in SR as TF is applied
    h_HT_Pre->Fill(HTv2Recipe,WeightBtagProb*TF);
    h_MHT_Pre->Fill(MHTv2Recipe,WeightBtagProb*TF);
    h_NJet_Pre->Fill(NJetsv2Recipe,WeightBtagProb*TF);
    if(doBTagCorr) //true for signal and SM MC
      h_NBtag_Pre->Fill(BTagsv2Recipe,WeightBtagProb*TF);
    else //true for data
      h_NBtag_Pre->Fill(BTagsv2Recipe,WeightBtagProb*TF);

    if(MHTv2Recipe>250 && MHTv2Recipe<300)
      h_HT_forQCD_Pre->Fill(HTv2Recipe,WeightBtagProb*TF);
    h_MHT_forQCD_Pre->Fill(MHTv2Recipe,WeightBtagProb*TF);
    if(MHTv2Recipe>250 && MHTv2Recipe<300)
      h_NJet_forQCD_Pre->Fill(NJetsv2Recipe,WeightBtagProb*TF);
    if(doBTagCorr){ //true for signal and SM MC
      if(MHTv2Recipe>250 && MHTv2Recipe<300)
	h_NBtag_forQCD_Pre->Fill(BTagsv2Recipe,WeightBtagProb*TF);
    }
    else{ //true for data
      if(MHTv2Recipe>250 && MHTv2Recipe<300)
	h_NBtag_forQCD_Pre->Fill(BTagsv2Recipe,WeightBtagProb*TF);
    }
    h_Prediction_MHTVsNbjet->Fill(MHTv2Recipe,BTagsfrmCSV,WeightBtagProb*TF);

    h_Prediction->Fill(bTagBin, WeightBtagProb*TF);
    //    std::cout<<" ** hist filled "<<" WeightBtagProb "<<WeightBtagProb<<endl;
    /*  
  if(bTagBin==2)
      std::cout<<" entry "<<entry<<" nLoops "<<i<<" bin "<<bTagBin<<" binQCD "<<bTagBinQCD<<" weight "<<Weight<<" BtagProb "<<bTagProb.at(i)<<" final wt "<<WeightBtagProb<<" h_CSStat "<<h_CSStat->GetBinContent(2)<<" h_Prediction "<<h_Prediction->GetBinContent(2)<<endl;
*/
  } //end of loop over nLoops

  return kTRUE;
}

void Prediction::SlaveTerminate()
{
  std::cout<<"***Prediction::SlaveTerminate***"<<std::endl;
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

  //std::cout<<"--- QCD binning ---"<<std::endl;
  //SearchBinsQCD_->PrintUsed();

  std::cout<<"--- Search bins ---"<<std::endl;
  SearchBins_->PrintUsed();  
}

void Prediction::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  std::cout<<"***Prediction::Terminate***"<<std::endl;
  h_Prediction = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_Prediction"));
  h_CSStat = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CSStat"));
  h_CSStat_MHTVsNbjet = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_CSStat_MHTVsNbjet"));
  h_Prediction_MHTVsNbjet = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_Prediction_MHTVsNbjet"));
  h_CutFlow = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CutFlow"));

  h_YieldCutFlow = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_YieldCutFlow"));
  h_HT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT_Exp"));
  h_HT5_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT5_Exp"));
  h_HTRatio_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatio_Exp"));
  h_MHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHT_Exp"));
  h_MET_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MET_Exp"));
  h_MHTPhi_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhi_Exp"));
  h_METPhi_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_METPhi_Exp"));
  h_mT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mT_Exp"));
  h_NJet_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJet_Exp"));
  h_NBtag_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtag_Exp"));
  h_DphiOne_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiOne_Exp"));
  h_DphiTwo_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiTwo_Exp"));
  h_DphiThree_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiThree_Exp"));
  h_DphiFour_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiFour_Exp"));
  h_LepPt_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepPt_Exp"));
  h_LepEta_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepEta_Exp"));
  h_LepEtafor50_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepEtafor50_Exp"));
 h_LepEtafor100_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepEtafor100_Exp"));
 h_LepEtafor200_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepEtafor200_Exp"));

  h_LepPhi_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepPhi_Exp"));

  h_ElePt_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_ElePt_Exp"));
  h_EleEta_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_EleEta_Exp"));
  h_ElePhi_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_ElePhi_Exp"));

  h_EleEtavsPt_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleEtavsPt_Exp"));
  h_EleEtavsPhi_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleEtavsPhi_Exp"));
  h_EleEtavsMT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleEtavsMT_Exp"));
  h_EleEtavsHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleEtavsHT_Exp"));
  h_EleEtavsMHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleEtavsMHT_Exp"));
  h_EleEtavsNJet_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleEtavsNJet_Exp"));
  h_EleEtavsNBtag_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleEtavsNBtag_Exp"));
  h_EleMTvsPt_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleMTvsPt_Exp"));
  h_EleMTvsMET_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleMTvsMET_Exp"));
  h_EleMTvsDphi_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EleMTvsDphi_Exp"));


  h_HEMEleEtavsPt_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleEtavsPt_Exp"));
  h_HEMEleEtavsPhi_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleEtavsPhi_Exp"));
  h_HEMEleEtavsMT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleEtavsMT_Exp"));
  h_HEMEleEtavsHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleEtavsHT_Exp"));
  h_HEMEleEtavsMHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleEtavsMHT_Exp"));
  h_HEMEleEtavsNJet_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleEtavsNJet_Exp"));
  h_HEMEleEtavsNBtag_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleEtavsNBtag_Exp"));
 h_HEMEleMTvsPt_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleMTvsPt_Exp"));
 h_HEMEleMTvsMET_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleMTvsMET_Exp"));
 h_HEMEleMTvsDphi_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HEMEleMTvsDphi_Exp"));



  h_MuPt_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MuPt_Exp"));
  h_MuEta_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MuEta_Exp"));
  h_MuPhi_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MuPhi_Exp"));

  h_rawJetPtforHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_rawJetPtforHT_Exp"));
  h_JetPtforHTLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHTLead_Exp"));
  h_JetEtaforHTLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHTLead_Exp"));
  h_JetPtforHTNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHTNotLead_Exp"));
  h_JetEtaforHTNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHTNotLead_Exp"));
  h_JetPtforHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHT_Exp"));
  h_JetEtaforHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHT_Exp"));

  h_rawJetPtvsEtaforHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_rawJetPtvsEtaforHT_Exp"));
  h_JetPtvsEtaforHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforHT_Exp"));
  h_JetPtvsHTRatioforHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsHTRatioforHT_Exp"));

  h_JetPtvsPhiforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsPhiforHTv2Recipe_Exp"));
  h_JetPtvsDPhiforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforHTv2Recipe_Exp"));
  h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp"));
  h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp"));

  h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp"));

  h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp"));

  h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp"));
  h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp"));
  h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp"));

  h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp"));
  h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp"));

  h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp"));
  h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp"));
  h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp"));






  h_rawJetPtforMHTminusHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_rawJetPtforMHTminusHT_Exp"));
  h_JetPtforMHTminusHTLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforMHTminusHTLead_Exp"));
  h_JetEtaforMHTminusHTLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforMHTminusHTLead_Exp"));
  h_JetPtforMHTminusHTNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforMHTminusHTNotLead_Exp"));
  h_JetEtaforMHTminusHTNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforMHTminusHTNotLead_Exp"));
  h_JetPtforMHTminusHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforMHTminusHT_Exp"));
  h_JetEtaforMHTminusHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforMHTminusHT_Exp"));

  h_rawJetPtvsEtaforMHTminusHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_rawJetPtvsEtaforMHTminusHT_Exp"));
  h_JetPtvsEtaforMHTminusHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforMHTminusHT_Exp"));
  h_JetPtvsHTRatioforMHTminusHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsHTRatioforMHTminusHT_Exp"));



  h_HTclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTclean_Exp"));
  h_HT5clean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT5clean_Exp"));
  h_MHTclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTclean_Exp"));
  h_METclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_METclean_Exp"));
  h_MHTPhiclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiclean_Exp"));
  h_METPhiclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_METPhiclean_Exp"));
  h_mTclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mTclean_Exp"));
  h_NJetclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetclean_Exp"));
  h_NBtagclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtagclean_Exp"));
  h_DphiOneclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiOneclean_Exp"));
  h_DphiTwoclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiTwoclean_Exp"));
  h_DphiThreeclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiThreeclean_Exp"));
  h_DphiFourclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiFourclean_Exp"));
  h_LepPtclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepPtclean_Exp"));
  h_LepEtaclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepEtaclean_Exp"));
  h_LepPhiclean_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepPhiclean_Exp"));


  h_Weight_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_Weight_Exp"));
  h_GenHT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_GenHT_Exp"));

  h_WeightBeforeScalePrefire_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_WeightBeforeScalePrefire_Exp"));
  h_WeightBeforeScalePrefirevsGenHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_WeightBeforeScalePrefirevsGenHT_Exp"));
  h_WeightBeforeScalePrefirevsRecoHT_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_WeightBeforeScalePrefirevsRecoHT_Exp"));

  h_HTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTv2Recipe_Exp"));
  h_HTv2Recipe_forQCD_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTv2Recipe_forQCD_Exp"));

  h_HTforTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTforTwoNbv2Recipe_Exp"));
  h_HTforNotTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTforNotTwoNbv2Recipe_Exp"));

  h_HTforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTforLowNJetv2Recipe_Exp"));
  h_HTforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTforHighNJetv2Recipe_Exp"));

  h_HTvsMHTforLowNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HTvsMHTforLowNJetv2Recipe_Exp"));
  h_HTvsMHTforHighNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HTvsMHTforHighNJetv2Recipe_Exp"));
  h_HT5v2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT5v2Recipe_Exp"));
  h_HTRatiov2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatiov2Recipe_Exp"));
  h_HTRatioforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatioforLowNJetv2Recipe_Exp"));
  h_HTRatioforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatioforHighNJetv2Recipe_Exp"));
  h_HTRatioforTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatioforTwoNbv2Recipe_Exp"));
  h_HTRatioforNotTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatioforNotTwoNbv2Recipe_Exp"));

  h_MHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTv2Recipe_Exp"));
  h_MHTv2Recipe_forQCD_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTv2Recipe_forQCD_Exp"));

  h_MHTforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTforLowNJetv2Recipe_Exp"));
  h_MHTforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTforHighNJetv2Recipe_Exp"));
  h_MHTforTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTforTwoNbv2Recipe_Exp"));
  h_MHTforNotTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTforNotTwoNbv2Recipe_Exp"));

  h_MHTPhiv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiv2Recipe_Exp"));
  h_MHTPhiforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiforLowNJetv2Recipe_Exp"));
  h_MHTPhiforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiforHighNJetv2Recipe_Exp"));
  h_MHTPhiforTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiforTwoNbv2Recipe_Exp"));
  h_MHTPhiforNotTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiforNotTwoNbv2Recipe_Exp"));

  h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp"));
  h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp"));
  h_NJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetv2Recipe_Exp"));
  h_NJetv2Recipe_forQCD_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetv2Recipe_forQCD_Exp"));

  h_NJetforTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetforTwoNbv2Recipe_Exp"));
  h_NJetforNotTwoNbv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetforNotTwoNbv2Recipe_Exp"));

  h_NJetvsHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsHTv2Recipe_Exp"));
  h_NJetvsMHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsMHTv2Recipe_Exp"));
  h_NJetvsMHTPhiv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsMHTPhiv2Recipe_Exp"));
  h_NJetvsNBtagv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsNBtagv2Recipe_Exp"));
  h_NJetvsNBFracv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsNBFracv2Recipe_Exp"));

  h_NJetforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetforMHTminusHTv2Recipe_Exp"));
  h_NBtagv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtagv2Recipe_Exp"));
  h_NBtagv2Recipe_forQCD_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtagv2Recipe_forQCD_Exp"));

  h_NBtagforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtagforLowNJetv2Recipe_Exp"));
  h_NBtagforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtagforHighNJetv2Recipe_Exp"));

  h_DphiOneforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiOneforHTv2Recipe_Exp"));
  h_DphiTwoforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiTwoforHTv2Recipe_Exp"));
  h_DphiThreeforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiThreeforHTv2Recipe_Exp"));
  h_DphiFourforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiFourforHTv2Recipe_Exp"));
  h_DphiOneforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiOneforMHTminusHTv2Recipe_Exp"));
  h_DphiTwoforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiTwoforMHTminusHTv2Recipe_Exp"));
  h_DphiThreeforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiThreeforMHTminusHTv2Recipe_Exp"));
  h_DphiFourforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiFourforMHTminusHTv2Recipe_Exp"));

  h_rawJetPtforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_rawJetPtforHTv2Recipe_Exp"));
  h_JetPtforHTv2RecipeLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHTv2RecipeLead_Exp"));
  h_JetEtaforHTv2RecipeLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHTv2RecipeLead_Exp"));
  h_JetPhiforHTv2RecipeLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHTv2RecipeLead_Exp"));

  h_JetPtforHTv2RecipeNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHTv2RecipeNotLead_Exp"));
  h_JetEtaforHTv2RecipeNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHTv2RecipeNotLead_Exp"));
  h_JetPhiforHTv2RecipeNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHTv2RecipeNotLead_Exp"));

  h_JetPtforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHTv2Recipe_Exp"));
  h_JetEtaforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHTv2Recipe_Exp"));
  h_JetEtafor50forHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtafor50forHTv2Recipe_Exp"));
  h_JetEtafor100forHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtafor100forHTv2Recipe_Exp"));
  h_JetEtafor200forHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtafor200forHTv2Recipe_Exp"));

  h_JetPhiforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHTv2Recipe_Exp"));

  h_JetPtforTwoNbforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforTwoNbforHTv2Recipe_Exp"));
  h_JetEtaforTwoNbforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforTwoNbforHTv2Recipe_Exp"));
  h_JetPhiforTwoNbforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforTwoNbforHTv2Recipe_Exp"));

  h_JetPtforNotTwoNbforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforNotTwoNbforHTv2Recipe_Exp"));
  h_JetEtaforNotTwoNbforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforNotTwoNbforHTv2Recipe_Exp"));
  h_JetPhiforNotTwoNbforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforNotTwoNbforHTv2Recipe_Exp"));

  h_JetPtforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforLowNJetforHTv2Recipe_Exp"));
  h_JetEtaforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforLowNJetforHTv2Recipe_Exp"));
  h_JetPhiforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforLowNJetforHTv2Recipe_Exp"));
  h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp"));

  h_JetPtforLowNJetfor0bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforLowNJetfor0bforHTv2Recipe_Exp"));
  h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp"));
  h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp"));

  h_JetPtforLowNJetfor1bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforLowNJetfor1bforHTv2Recipe_Exp"));
  h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp"));
  h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp"));

  h_JetPtforLowNJetfor2bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforLowNJetfor2bforHTv2Recipe_Exp"));
  h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp"));
  h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp"));

  h_JetPtforLowNJetfor3bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforLowNJetfor3bforHTv2Recipe_Exp"));
  h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp"));
  h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp"));

  h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp"));
  h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp"));

  h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp"));

  h_JetPtforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetforHTv2Recipe_Exp"));
  h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp"));
  h_JetCSVforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetCSVforHighNJetforHTv2Recipe_Exp"));
  h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp"));
  h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp"));
  h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp"));

  h_JetPtforHighNJetLeadforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetLeadforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetLeadforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetLeadforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetLeadforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetLeadforHTv2Recipe_Exp"));
  h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp"));

  h_JetPtforHighNJetfor0bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetfor0bforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp"));

  h_JetPtforHighNJetfor1bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetfor1bforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp"));

  h_JetPtforHighNJetfor2bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetfor2bforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp"));

  h_JetPtforHighNJetfor3bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetfor3bforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp"));

  h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp"));
  h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp"));
  h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp"));

  h_rawJetPtvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_rawJetPtvsEtaforHTv2Recipe_Exp"));
  h_JetIdxvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetIdxvsEtaforHTv2Recipe_Exp")); 
  h_JetMultvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetMultvsEtaforHTv2Recipe_Exp"));
  h_JetPtvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforHTv2Recipe_Exp"));
  h_JetEtavsPhiforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHTv2Recipe_Exp"));
  h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp"));

  h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp"));
  h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp"));
  h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp"));
  h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp"));
  h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp"));
  h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp"));
  h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp"));
  h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp"));

  h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp"));
  h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp"));
  
 h_JetPtvsHTRatioforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsHTRatioforHTv2Recipe_Exp"));
  h_JetEtavsHTRatioforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsHTRatioforHTv2Recipe_Exp"));
  h_JetPhivsHTRatioforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsHTRatioforHTv2Recipe_Exp"));
  h_JetPhivsDPhiLeadforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsDPhiLeadforHTv2Recipe_Exp"));
  h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp"));
  h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp"));
  h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp"));
  h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp"));

  h_MHTPhivsJetPhiforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_MHTPhivsJetPhiforHTv2Recipe_Exp"));
  h_RecHTRatiovsDPhiforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_RecHTRatiovsDPhiforHTv2Recipe_Exp"));
  h_RecHTRatiovsDPhiforAllv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_RecHTRatiovsDPhiforAllv2Recipe_Exp"));

  h_chargedEmEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedEmEnergyFractionforHTv2Recipe_Exp"));
           
  h_chargedHadronEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedHadronEnergyFractionforHTv2Recipe_Exp"));
  h_chargedHadronMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedHadronMultiplicityforHTv2Recipe_Exp"));  
  h_chargedMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedMultiplicityforHTv2Recipe_Exp"));
  h_electronEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_electronEnergyFractionforHTv2Recipe_Exp"));
  h_electronMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_electronMultiplicityforHTv2Recipe_Exp"));
  std::cout<<" seg vio1 "<<endl;

  //  h_hadronFlavorforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_hadronFlavorforHTv2Recipe_Exp")); 
  h_hfEMEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_hfEMEnergyFractionforHTv2Recipe_Exp"));
  h_hfHadronEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_hfHadronEnergyFractionforHTv2Recipe_Exp"));
  h_multiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_multiplicityforHTv2Recipe_Exp")); 
  h_muonEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_muonEnergyFractionforHTv2Recipe_Exp")); 
  h_muonMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_muonMultiplicityforHTv2Recipe_Exp")); 
  h_neutralEmEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralEmEnergyFractionforHTv2Recipe_Exp"));
  h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp"));
  h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp"));
  h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp"));

  h_neutralHadronEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralHadronEnergyFractionforHTv2Recipe_Exp"));
  h_neutralHadronMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralHadronMultiplicityforHTv2Recipe_Exp")); 
  h_neutralMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralMultiplicityforHTv2Recipe_Exp"));
  h_photonEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_photonEnergyFractionforHTv2Recipe_Exp"));
  h_photonMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_photonMultiplicityforHTv2Recipe_Exp"));
  h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp"));
  h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp"));
  h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp"));
  h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp=dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp"));
  h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp=dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp"));
  h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp=dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp"));
  
  //  h_qgLikelihoodforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject(""));


  std::cout<<" seg vio2 "<<endl;




  h_rawJetPtforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_rawJetPtforMHTminusHTv2Recipe_Exp"));
  h_JetPtforMHTminusHTv2RecipeLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforMHTminusHTv2RecipeLead_Exp"));
  h_JetEtaforMHTminusHTv2RecipeLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforMHTminusHTv2RecipeLead_Exp"));
  h_JetPhiforMHTminusHTv2RecipeLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforMHTminusHTv2RecipeLead_Exp"));


  h_JetPtforMHTminusHTv2RecipeNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforMHTminusHTv2RecipeNotLead_Exp"));
  h_JetEtaforMHTminusHTv2RecipeNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforMHTminusHTv2RecipeNotLead_Exp"));
  h_JetPhiforMHTminusHTv2RecipeNotLead_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforMHTminusHTv2RecipeNotLead_Exp"));
  std::cout<<" seg vio3 "<<endl;

  h_JetPtforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforMHTminusHTv2Recipe_Exp"));
  h_JetEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforMHTminusHTv2Recipe_Exp"));
  h_JetEtafor50forMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtafor50forMHTminusHTv2Recipe_Exp"));
  h_JetEtafor100forMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtafor100forMHTminusHTv2Recipe_Exp"));
  h_JetEtafor200forMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtafor200forMHTminusHTv2Recipe_Exp"));

  h_JetPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforMHTminusHTv2Recipe_Exp"));

  h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp"));
  h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp")); 
  h_JetMultvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetMultvsEtaforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp"));

  h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp"));

  h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp"));
  h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp"));
  h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp"));

  h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp"));
  h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp"));

  h_JetPtvsPhiforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsPhiforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp"));

  h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp"));

  h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp"));

  h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp"));

  h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp"));

  h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp"));  
  h_chargedMultiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_chargedMultiplicityforMHTminusHTv2Recipe_Exp"));
  h_electronEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_electronEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_electronMultiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_electronMultiplicityforMHTminusHTv2Recipe_Exp"));
  //  h_hadronFlavorforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_hadronFlavorforMHTminusHTv2Recipe_Exp")); 
  std::cout<<" seg vio4 "<<endl;

  h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_multiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_multiplicityforMHTminusHTv2Recipe_Exp")); 
  h_muonEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_muonEnergyFractionforMHTminusHTv2Recipe_Exp")); 
  h_muonMultiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_muonMultiplicityforMHTminusHTv2Recipe_Exp")); 
  h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp")); 
  h_neutralMultiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralMultiplicityforMHTminusHTv2Recipe_Exp"));
  h_photonEnergyFractionforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_photonEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_photonMultiplicityforMHTminusHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_photonMultiplicityforMHTminusHTv2Recipe_Exp"));

  std::cout<<" seg vio5 "<<endl;


  h_MHTOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTOrig_Exp"));
  h_METOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_METOrig_Exp"));
  h_MHTPhiOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiOrig_Exp"));
  h_METPhiOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_METPhiOrig_Exp"));
  h_DphiOneOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiOneOrig_Exp"));
  h_DphiTwoOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiTwoOrig_Exp"));
  h_DphiThreeOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiThreeOrig_Exp"));
  h_DphiFourOrig_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiFourOrig_Exp"));




  h_HT_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT_Pre"));
  h_MHT_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHT_Pre"));
  h_NJet_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJet_Pre"));
  h_NBtag_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtag_Pre"));
  h_HT_forQCD_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT_forQCD_Pre"));
  h_MHT_forQCD_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHT_forQCD_Pre"));
  h_NJet_forQCD_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJet_forQCD_Pre"));
  h_NBtag_forQCD_Pre = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtag_forQCD_Pre"));

  TFile *outPutFile = new TFile(fileName,"RECREATE"); ;
  outPutFile->cd();
  /*
  for(unsigned int i=1; i<=174;i++){
    std::cout<<" i "<<i<<" binVal "<<h_Prediction->GetBinContent(i)<<endl;
  }
*/
  h_Prediction->Write();
  h_CSStat->Write();
  h_CSStat_MHTVsNbjet->Write();
  h_Prediction_MHTVsNbjet->Write();
  h_CutFlow->Write();
  h_YieldCutFlow->Write();
  h_HT_Exp->Write();
  h_HT5_Exp->Write();  
  h_HTRatio_Exp->Write();
  h_MHT_Exp->Write();
  h_MHTPhi_Exp->Write();
  h_MET_Exp->Write();
  h_METPhi_Exp->Write();
  h_mT_Exp->Write();
  h_NJet_Exp->Write();
  h_NBtag_Exp->Write();
  h_DphiOne_Exp->Write();
  h_DphiTwo_Exp->Write();
  h_DphiThree_Exp->Write();
  h_DphiFour_Exp->Write(); 
  h_LepPt_Exp->Write(); 
  h_LepEta_Exp->Write(); 
  h_LepEtafor50_Exp->Write(); 
  h_LepEtafor100_Exp->Write(); 
  h_LepEtafor200_Exp->Write(); 

  h_LepPhi_Exp->Write(); 

  h_ElePt_Exp->Write(); 
  h_EleEta_Exp->Write(); 
  h_ElePhi_Exp->Write(); 

  h_EleEtavsPt_Exp->Write();
  h_EleEtavsPhi_Exp->Write();
  h_EleEtavsMT_Exp->Write();
  h_EleEtavsHT_Exp->Write();
  h_EleEtavsMHT_Exp->Write();
  h_EleEtavsNJet_Exp->Write();
  h_EleEtavsNBtag_Exp->Write();
  h_EleMTvsPt_Exp->Write();
  h_EleMTvsMET_Exp->Write();
  h_EleMTvsDphi_Exp->Write();

  h_HEMEleEtavsPt_Exp->Write();
  h_HEMEleEtavsPhi_Exp->Write();
  h_HEMEleEtavsMT_Exp->Write();
  h_HEMEleEtavsHT_Exp->Write();
  h_HEMEleEtavsMHT_Exp->Write();
  h_HEMEleEtavsNJet_Exp->Write();
  h_HEMEleEtavsNBtag_Exp->Write();
  h_HEMEleMTvsPt_Exp->Write();
  h_HEMEleMTvsMET_Exp->Write();
  h_HEMEleMTvsDphi_Exp->Write();

  h_MuPt_Exp->Write(); 
  h_MuEta_Exp->Write(); 
  h_MuPhi_Exp->Write(); 

  h_rawJetPtforHT_Exp->Write();
  h_JetPtforHTLead_Exp->Write();
  h_JetEtaforHTLead_Exp->Write();
  h_JetPtforHTNotLead_Exp->Write();
  h_JetEtaforHTNotLead_Exp->Write();
  h_JetPtforHT_Exp->Write();
  h_JetEtaforHT_Exp->Write();

  h_rawJetPtvsEtaforHT_Exp->Write();
  h_JetPtvsEtaforHT_Exp->Write();
  h_JetPtvsHTRatioforHT_Exp->Write();
  h_rawJetPtforMHTminusHT_Exp->Write();
  h_JetPtforMHTminusHTLead_Exp->Write();
  h_JetEtaforMHTminusHTLead_Exp->Write();
  h_JetPtforMHTminusHTNotLead_Exp->Write();
  h_JetEtaforMHTminusHTNotLead_Exp->Write();
  h_JetPtforMHTminusHT_Exp->Write();
  h_JetEtaforMHTminusHT_Exp->Write();

  h_JetPtvsEtaforMHTminusHT_Exp->Write();
  h_JetPtvsHTRatioforMHTminusHT_Exp->Write();
  h_rawJetPtvsEtaforMHTminusHT_Exp->Write();

  h_HTclean_Exp->Write();
  h_HT5clean_Exp->Write();
  h_MHTclean_Exp->Write();
  h_MHTPhiclean_Exp->Write();
  h_METclean_Exp->Write();
  h_METPhiclean_Exp->Write();
  h_mTclean_Exp->Write();
  h_NJetclean_Exp->Write();
  h_NBtagclean_Exp->Write();
  h_DphiOneclean_Exp->Write();
  h_DphiTwoclean_Exp->Write();
  h_DphiThreeclean_Exp->Write();
  h_DphiFourclean_Exp->Write(); 
  h_LepPtclean_Exp->Write(); 
  h_LepEtaclean_Exp->Write(); 
  h_LepPhiclean_Exp->Write(); 

  h_Weight_Exp->Write();
  h_GenHT_Exp->Write();

  h_WeightBeforeScalePrefire_Exp->Write();
  h_WeightBeforeScalePrefirevsGenHT_Exp->Write();
  h_WeightBeforeScalePrefirevsRecoHT_Exp->Write();

  h_HTv2Recipe_Exp->Write();
  h_HTv2Recipe_forQCD_Exp->Write();

  h_HTforLowNJetv2Recipe_Exp->Write();
  h_HTforHighNJetv2Recipe_Exp->Write();
  h_HTforTwoNbv2Recipe_Exp->Write();
  h_HTforNotTwoNbv2Recipe_Exp->Write();
  h_HTvsMHTforLowNJetv2Recipe_Exp->Write();
  h_HTvsMHTforHighNJetv2Recipe_Exp->Write();
  h_HT5v2Recipe_Exp->Write();
  h_HTRatiov2Recipe_Exp->Write();
  h_HTRatioforLowNJetv2Recipe_Exp->Write();
  h_HTRatioforHighNJetv2Recipe_Exp->Write();
  h_HTRatioforTwoNbv2Recipe_Exp->Write();
  h_HTRatioforNotTwoNbv2Recipe_Exp->Write();
  h_MHTv2Recipe_Exp->Write();
  h_MHTv2Recipe_forQCD_Exp->Write();
  h_MHTforLowNJetv2Recipe_Exp->Write();
  h_MHTforHighNJetv2Recipe_Exp->Write();
  h_MHTforTwoNbv2Recipe_Exp->Write();
  h_MHTforNotTwoNbv2Recipe_Exp->Write();
  h_MHTPhiv2Recipe_Exp->Write();
  h_MHTPhiforLowNJetv2Recipe_Exp->Write();
  h_MHTPhiforHighNJetv2Recipe_Exp->Write();
  h_MHTPhiforTwoNbv2Recipe_Exp->Write();
  h_MHTPhiforNotTwoNbv2Recipe_Exp->Write();
  h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp->Write();
  h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp->Write();
  h_NJetv2Recipe_Exp->Write();
  h_NJetv2Recipe_forQCD_Exp->Write();
  
  h_NJetforTwoNbv2Recipe_Exp->Write();
  h_NJetforNotTwoNbv2Recipe_Exp->Write();
  h_NJetvsHTv2Recipe_Exp->Write();
  h_NJetvsMHTv2Recipe_Exp->Write();
  h_NJetvsMHTPhiv2Recipe_Exp->Write();
  h_NJetvsNBtagv2Recipe_Exp->Write();
  h_NJetvsNBFracv2Recipe_Exp->Write();
  h_NJetforMHTminusHTv2Recipe_Exp->Write();
  h_NBtagv2Recipe_Exp->Write();
  h_NBtagv2Recipe_forQCD_Exp->Write();

  h_NBtagforLowNJetv2Recipe_Exp->Write();
  h_NBtagforHighNJetv2Recipe_Exp->Write();

  h_DphiOneforHTv2Recipe_Exp->Write();
  h_DphiTwoforHTv2Recipe_Exp->Write();
  h_DphiThreeforHTv2Recipe_Exp->Write();
  h_DphiFourforHTv2Recipe_Exp->Write(); 

  h_DphiOneforMHTminusHTv2Recipe_Exp->Write();
  h_DphiTwoforMHTminusHTv2Recipe_Exp->Write();
  h_DphiThreeforMHTminusHTv2Recipe_Exp->Write();
  h_DphiFourforMHTminusHTv2Recipe_Exp->Write(); 

  h_rawJetPtforHTv2Recipe_Exp->Write();
  h_JetPtforHTv2RecipeLead_Exp->Write();
  h_JetEtaforHTv2RecipeLead_Exp->Write();
  h_JetPhiforHTv2RecipeLead_Exp->Write();
  h_JetPtforHTv2RecipeNotLead_Exp->Write();
  h_JetEtaforHTv2RecipeNotLead_Exp->Write();
  h_JetPhiforHTv2RecipeNotLead_Exp->Write();
  h_JetPtforHTv2Recipe_Exp->Write();
  h_JetEtaforHTv2Recipe_Exp->Write();
  h_JetEtafor50forHTv2Recipe_Exp->Write();
  h_JetEtafor100forHTv2Recipe_Exp->Write();
  h_JetEtafor200forHTv2Recipe_Exp->Write();

  h_JetPhiforHTv2Recipe_Exp->Write();

  h_JetPtforTwoNbforHTv2Recipe_Exp->Write();
  h_JetEtaforTwoNbforHTv2Recipe_Exp->Write();
  h_JetPhiforTwoNbforHTv2Recipe_Exp->Write();

  h_JetPtforNotTwoNbforHTv2Recipe_Exp->Write();
  h_JetEtaforNotTwoNbforHTv2Recipe_Exp->Write();
  h_JetPhiforNotTwoNbforHTv2Recipe_Exp->Write();


  h_JetPtforLowNJetforHTv2Recipe_Exp->Write();
  h_JetEtaforLowNJetforHTv2Recipe_Exp->Write();
  h_JetPhiforLowNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforLowPtforLowNJetforHTv2Recipe_Exp->Write();

  h_JetPtforLowNJetfor0bforHTv2Recipe_Exp->Write();
  h_JetEtaforLowNJetfor0bforHTv2Recipe_Exp->Write();
  h_JetPhiforLowNJetfor0bforHTv2Recipe_Exp->Write();

  h_JetPtforLowNJetfor1bforHTv2Recipe_Exp->Write();
  h_JetEtaforLowNJetfor1bforHTv2Recipe_Exp->Write();
  h_JetPhiforLowNJetfor1bforHTv2Recipe_Exp->Write();

  h_JetPtforLowNJetfor2bforHTv2Recipe_Exp->Write();
  h_JetEtaforLowNJetfor2bforHTv2Recipe_Exp->Write();
  h_JetPhiforLowNJetfor2bforHTv2Recipe_Exp->Write();

  h_JetPtforLowNJetfor3bforHTv2Recipe_Exp->Write();
  h_JetEtaforLowNJetfor3bforHTv2Recipe_Exp->Write();
  h_JetPhiforLowNJetfor3bforHTv2Recipe_Exp->Write();

  h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp->Write();
  h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp->Write();
  h_JetPtforHighNJetforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforLowPtforHighNJetforHTv2Recipe_Exp->Write();
  h_JetCSVforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPtvsCSVforHighNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsCSVforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPhivsCSVforHighNJetforHTv2Recipe_Exp->Write();

  h_JetPtforHighNJetLeadforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetLeadforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetLeadforHTv2Recipe_Exp->Write();
  h_JetPtforHighNJetNotLeadforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetNotLeadforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetNotLeadforHTv2Recipe_Exp->Write();

  h_JetPtforHighNJetfor0bforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetfor0bforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetfor0bforHTv2Recipe_Exp->Write();

  h_JetPtforHighNJetfor1bforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetfor1bforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetfor1bforHTv2Recipe_Exp->Write();

  h_JetPtforHighNJetfor2bforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetfor2bforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetfor2bforHTv2Recipe_Exp->Write();

  h_JetPtforHighNJetfor3bforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetfor3bforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetfor3bforHTv2Recipe_Exp->Write();


  h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp->Write();
  h_rawJetPtvsEtaforHTv2Recipe_Exp->Write();
  h_JetIdxvsEtaforHTv2Recipe_Exp->Write();
  h_JetMultvsEtaforHTv2Recipe_Exp->Write();
  h_JetPtvsEtaforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforLeadingTwoforHTv2Recipe_Exp->Write();

  h_JetEtavsPhiforHTv2RecipePassPhotonCut_Exp->Write();
  h_JetEtavsPhiforHTv2RecipeFailPhotonCut_Exp->Write();
  h_JetEtavsDPhiforHTv2RecipePassPhotonCut_Exp->Write();
  h_JetEtavsDPhiforHTv2RecipeFailPhotonCut_Exp->Write();
  h_chargedEmEnergyFractionforHTv2RecipePassPhotonCut_Exp->Write();
  h_chargedEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp->Write();
  h_neutralEmEnergyFractionforHTv2RecipePassPhotonCut_Exp->Write();
  h_neutralEmEnergyFractionforHTv2RecipeFailPhotonCut_Exp->Write();

  h_EtavsRatioMultiplicityforHTv2RecipePassPhotonCut_Exp->Write();
  h_EtavsRatioMultiplicityforHTv2RecipeFailPhotonCut_Exp->Write();

  h_JetPtvsHTRatioforHTv2Recipe_Exp->Write();
  h_JetEtavsHTRatioforHTv2Recipe_Exp->Write();
  h_JetPhivsHTRatioforHTv2Recipe_Exp->Write();
  h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforTwoNbforHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforNotTwoNbforHTv2Recipe_Exp->Write();
  h_JetEtavsDPhiforTwoNbforHTv2Recipe_Exp->Write();
  h_JetEtavsDPhiforNotTwoNbforHTv2Recipe_Exp->Write();

  h_MHTPhivsJetPhiforHTv2Recipe_Exp->Write();
  h_RecHTRatiovsDPhiforHTv2Recipe_Exp->Write();
  h_RecHTRatiovsDPhiforAllv2Recipe_Exp->Write(); 
  h_JetPtvsPhiforHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforLeadingTwoforHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforRedSpotsLeadingTwoforHTv2Recipe_Exp->Write();

  h_JetPtvsDPhiforHEMcloseLeadingTwoforHTv2Recipe_Exp->Write();

  h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp->Write();

  h_JetEtavsneutralEMbyphotonFractionforHTv2Recipe_Exp->Write();
  h_JetEtavsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp->Write();
  h_JetEtavsneutralEMbychargedEMFractionforHTv2Recipe_Exp->Write();

  h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp->Write();

  h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp->Write();


  h_chargedEmEnergyFractionforHTv2Recipe_Exp->Write();
  h_chargedHadronEnergyFractionforHTv2Recipe_Exp->Write();
  h_chargedHadronMultiplicityforHTv2Recipe_Exp->Write();  
  h_chargedMultiplicityforHTv2Recipe_Exp->Write();
  h_electronEnergyFractionforHTv2Recipe_Exp->Write();
  h_electronMultiplicityforHTv2Recipe_Exp->Write();

  std::cout<<" seg vio51 "<<endl;

  //  h_hadronFlavorforHTv2Recipe_Exp->Write(); 
  h_hfEMEnergyFractionforHTv2Recipe_Exp->Write();
  h_hfHadronEnergyFractionforHTv2Recipe_Exp->Write();
  std::cout<<" seg vio52 "<<endl;

  h_multiplicityforHTv2Recipe_Exp->Write(); 
  h_muonEnergyFractionforHTv2Recipe_Exp->Write(); 
  h_muonMultiplicityforHTv2Recipe_Exp->Write(); 
  std::cout<<" seg vio53 "<<endl;

  h_neutralEmEnergyFractionforHTv2Recipe_Exp->Write();
  h_neutralEmEnergyFractionforLowNJetforHTv2Recipe_Exp->Write();
  h_neutralEmEnergyFractionforHighNJetforHTv2Recipe_Exp->Write();
  h_neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe_Exp->Write();

  h_neutralHadronEnergyFractionforHTv2Recipe_Exp->Write();
  h_neutralHadronMultiplicityforHTv2Recipe_Exp->Write(); 
  std::cout<<" seg vio54 "<<endl;

  h_neutralMultiplicityforHTv2Recipe_Exp->Write();
  std::cout<<" seg vio55 "<<endl;

  h_photonEnergyFractionforHTv2Recipe_Exp->Write();
  std::cout<<" seg vio56 "<<endl;

  h_photonMultiplicityforHTv2Recipe_Exp->Write();
  h_JetPtvsphotonMultiplicityforHTv2Recipe_Exp->Write();
  h_JetEtavsphotonMultiplicityforHTv2Recipe_Exp->Write();
  h_JetPhivsphotonMultiplicityforHTv2Recipe_Exp->Write();
  h_JetPtvsphotonMultiplicityforHighNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsphotonMultiplicityforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPhivsphotonMultiplicityforHighNJetforHTv2Recipe_Exp->Write();

  std::cout<<" seg vio6 "<<endl;




  h_JetPtforMHTminusHTv2RecipeLead_Exp->Write();
  h_JetEtaforMHTminusHTv2RecipeLead_Exp->Write();
  h_JetPhiforMHTminusHTv2RecipeLead_Exp->Write();
  h_JetPtforMHTminusHTv2RecipeNotLead_Exp->Write();
  h_JetEtaforMHTminusHTv2RecipeNotLead_Exp->Write();
  h_JetPhiforMHTminusHTv2RecipeNotLead_Exp->Write();
  h_JetPtforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtafor50forMHTminusHTv2Recipe_Exp->Write();
  h_JetEtafor100forMHTminusHTv2Recipe_Exp->Write();
  h_JetEtafor200forMHTminusHTv2Recipe_Exp->Write();

  h_JetPhiforMHTminusHTv2Recipe_Exp->Write();
  h_rawJetPtforMHTminusHTv2Recipe_Exp->Write();

  h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetMultvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforLeadingTwoforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp->Write();

  h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp->Write();
  h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp->Write();
  h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp->Write();

  h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp->Write();
  h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp->Write();

  h_JetPtvsPhiforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforLeadingTwoforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforRedSpotsLeadingTwoforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforHEMcloseLeadingTwoforMHTminusHTv2Recipe_Exp->Write();

  h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp->Write();

  h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();

  h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();

  std::cout<<" seg vio61 "<<endl;

  
  h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  std::cout<<" seg vio611 "<<endl;
  h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  std::cout<<" seg vio62 "<<endl;

  h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp->Write();  
  h_chargedMultiplicityforMHTminusHTv2Recipe_Exp->Write();
  std::cout<<" seg vio63 "<<endl;

  h_electronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_electronMultiplicityforMHTminusHTv2Recipe_Exp->Write();
  //  h_hadronFlavorforMHTminusHTv2Recipe_Exp->Write(); 
  std::cout<<" seg vio64 "<<endl;

  h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_multiplicityforMHTminusHTv2Recipe_Exp->Write(); 
  h_muonEnergyFractionforMHTminusHTv2Recipe_Exp->Write(); 
  h_muonMultiplicityforMHTminusHTv2Recipe_Exp->Write(); 
  h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp->Write(); 
  h_neutralMultiplicityforMHTminusHTv2Recipe_Exp->Write();
  h_photonEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_photonMultiplicityforMHTminusHTv2Recipe_Exp->Write();

  std::cout<<" seg vio7 "<<endl;



  h_MHTOrig_Exp->Write();
  h_MHTPhiOrig_Exp->Write();
  h_METOrig_Exp->Write();
  h_METPhiOrig_Exp->Write();
  h_DphiOneOrig_Exp->Write();
  h_DphiTwoOrig_Exp->Write();
  h_DphiThreeOrig_Exp->Write();
  h_DphiFourOrig_Exp->Write(); 

  h_HT_Pre->Write();
  h_MHT_Pre->Write();
  h_NJet_Pre->Write();
  h_NBtag_Pre->Write();
  h_HT_forQCD_Pre->Write();
  h_MHT_forQCD_Pre->Write();
  h_NJet_forQCD_Pre->Write();
  h_NBtag_forQCD_Pre->Write();


  outPutFile->Close();

  cout << "Saved output to " << fileName << endl;
  
}

void Prediction::resetValues()
{
  mtw = 0;
}

vector<string> Prediction::skmInput(string mom){
  vector<string> vecStr;
  bool underline =false;
  bool dash=false;
  while(mom.find("_")!=string::npos || mom.find("-")!=string::npos){
    if(mom.find("_")!=string::npos){
      vecStr.push_back(mom.substr(0,mom.find("_")));
      mom=mom.substr(mom.find("_")+1);
    }
    if(mom.find("-")!=string::npos){
      vecStr.push_back(mom.substr(0,mom.find("-")));
      mom=mom.substr(mom.find("-")+1);
    }

  }
  vecStr.push_back(mom);
  return vecStr;
}

bool Prediction::FiltersPass()
{

  bool result=true;
  if(useFilterData){
    if(HBHENoiseFilter!=1){
      result=false;
      //      std::cout<<" failed HBHE "<<endl;
    }
    if(result) h_CutFlow->Fill(5);

    if(HBHEIsoNoiseFilter!=1){
      result=false;
      //      std::cout<<" failed HBHEIso "<<endl;
    }
    if(result) h_CutFlow->Fill(6);
    if(EcalDeadCellTriggerPrimitiveFilter!=1){
      result=false;    
      //      std::cout<<" failed EcalDeadCell "<<endl;
    }

    if(result) h_CutFlow->Fill(7);
    /*
    if(eeBadScFilter!=1){
      result=false;
      //      std::cout<<" failed eeBadSc "<<endl;
    }
*/
    if(BadPFMuonFilter!=1) result=false;
      
    if(result) h_CutFlow->Fill(8);
    //    if(BadChargedCandidateFilter!=1) result=false;

    if(!runOnSignalMC){
      if(globalSuperTightHalo2016Filter!=1) result=false;
    }
    if(result) h_CutFlow->Fill(9);
    //std::cout<<" ecalBadCalib "<<ecalBadCalibFilter<<" ecalBadCalibReducedFilter "<<ecalBadCalibReducedFilter<<" ecalBadCalibReducedExtraFilter "<<ecalBadCalibReducedExtraFilter<<endl;
    if(!ecalBadCalibReducedFilter) result=false;
    if(result) h_CutFlow->Fill(22);
    if(!ecalBadCalibReducedExtraFilter) result=false;
    if(result) h_CutFlow->Fill(23);

    if(runOnData){
      if(eeBadScFilter!=1) result=false;
      // if(globalSuperTightHalo2016Filter!=1) result=false;
    }    
    if(result) h_CutFlow->Fill(24);
  }
  if(NVtx<=0){
    result=false;
    //    std::cout<<" failed nvtx "<<endl;
  }
  if(result) h_CutFlow->Fill(25);

  // Do not apply on fastSim samples!
  if(!runOnSignalMC) if(!JetID){
      result=false;
      //      std::cout<<"failed jetID "<<endl;
  }

  if(result) h_CutFlow->Fill(10);
  // Preliminary filters
  if(PFCaloMETRatio>5) result=false;
  if(result) h_CutFlow->Fill(11);
  // Check efficiency of filter
  //  std::cout<<" PFCaloMETRatio "<<PFCaloMETRatio<<endl;
  if(result)
    for(unsigned j = 0; j < Jets->size(); j++){
      if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
      if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
	//std::cout<<"found bad muon jet"<<std::endl;
	result=false;
      }
    }
  if(result) h_CutFlow->Fill(12);

  //*AR-190406---filter devided to take care of anomalous jets affecting QCD control region
  if(result)
    for(unsigned j = 0; j < Jets->size(); j++){
      if(j==0){
	if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
	if(Jets_neutralEmEnergyFraction->at(j)<0.03 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
	  //	  std::cout<<"found bad QCD CR jet"<<std::endl;
	  result=false;
	}
      }
    }
	  
	  
  //reject events with any jet pt>20, |eta|<2.5 NOT matched to a GenJet (w/in DeltaR<0.3) and chfrac < 0.1
  if(result && runOnSignalMC)
    for(unsigned j = 0; j < Jets->size(); ++j){
      if(Jets->at(j).Pt() <= 20 || fabs(Jets->at(j).Eta())>=2.5) continue;
      bool genMatched = false;
      for(unsigned g = 0; g < GenJets->size(); ++g){
	if(GenJets->at(g).DeltaR(Jets->at(j)) < 0.3) {
	  genMatched = true;
	  break;
	}
      }
      if(!genMatched && Jets_chargedHadronEnergyFraction->at(j) < 0.1){
	result = false;
	break;
      }
    }
  if(result) h_CutFlow->Fill(13);


  return result;













  /*

  bool result=true;
  if(useFilterData){
    if(HBHENoiseFilter!=1){
      result=false;
      //      std::cout<<" failed HBHE "<<endl;
    }
    if(result) h_CutFlow->Fill(5);
    if(HBHEIsoNoiseFilter!=1){
      result=false;
      //      std::cout<<" failed HBHEIso "<<endl;
    }

    if(result) h_CutFlow->Fill(6);
    if(EcalDeadCellTriggerPrimitiveFilter!=1){
      result=false;    
      //      std::cout<<" failed EcalDeadCell "<<endl;
    }

    if(result) h_CutFlow->Fill(7);
    /*
    if(eeBadScFilter!=1){
      result=false;
      //      std::cout<<" failed eeBadSc "<<endl;
    }
*/
  /*
    if(BadPFMuonFilter!=1) result=false;
    if(result) h_CutFlow->Fill(8);
    std::cout<<" passed Bad PF muon "<<endl;
    if(!runOnSignalMC){
      if(globalSuperTightHalo2016Filter!=1) result=false;
    }

    if(result) h_CutFlow->Fill(9);
    //if(result) h_CutFlow->Fill(8);
    if(BadChargedCandidateFilter!=1) result=false;
    //if(ecalBadCalibFilter!=1) result=false;
    if(runOnData){
      if(eeBadScFilter!=1) result=false;
      //if(!BadChargedCandidateFilter) result=false;
      //  if(!BadPFMuonFilter) result=false;
      //      if(globalSuperTightHalo2016Filter!=1) result=false;
    }    
  }
  if(NVtx<=0){
    result=false;
    std::cout<<" failed nvtx "<<endl;
  }
  std::cout<<" passed nvtx "<<endl;

  //  if(result) h_CutFlow->Fill(9);
  //  if(result) h_CutFlow->Fill(9);
  // Do not apply on fastSim samples!
  if(!runOnSignalMC) if(!JetID){
      result=false;
      std::cout<<" failed jetID "<<endl;
  }
  std::cout<<" passed jetID "<<endl;
  if(result) h_CutFlow->Fill(10);
  // Preliminary filters
  if(PFCaloMETRatio>5) result=false;
  if(result) h_CutFlow->Fill(11);
  // Check efficiency of filter
  
  if(result)
    for(unsigned j = 0; j < Jets->size(); j++){
      if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
      if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
	//std::cout<<"found bad muon jet"<<std::endl;
	result=false;
      }
    }
  if(result) h_CutFlow->Fill(12);
  std::cout<<" passed bad muon jet "<<endl;

  //reject events with any jet pt>20, |eta|<2.5 NOT matched to a GenJet (w/in DeltaR<0.3) and chfrac < 0.1
  if(result && runOnSignalMC)
    for(unsigned j = 0; j < Jets->size(); ++j){
      if(Jets->at(j).Pt() <= 20 || fabs(Jets->at(j).Eta())>=2.5) continue;
      bool genMatched = false;
      for(unsigned g = 0; g < GenJets->size(); ++g){
	if(GenJets->at(g).DeltaR(Jets->at(j)) < 0.3) {
	  genMatched = true;
	  break;
	}
      }
      if(!genMatched && Jets_chargedHadronEnergyFraction->at(j) < 0.1){
	result = false;
	break;
      }
    }
  if(result) h_CutFlow->Fill(13);
  std::cout<<" not a bad jet "<<endl;


  return result;
*/
}
