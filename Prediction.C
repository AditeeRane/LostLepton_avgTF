#define Prediction_cxx

#include "Prediction.h"
#include <TH2.h>
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
  h_Prediction = new TH1D("h_Prediction", "h_Prediction", nSB, 0.5, nSB+0.5);
  h_CSStat = new TH1D("h_CSStat", "h_CSStat", nSB, 0.5, nSB+0.5);
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
  h_LepPhi_Exp=new TH1D("h_LepPhi_Exp","h_LepPhi_Exp",7,-3.5,3.5);
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

  h_HTv2Recipe_Exp =new TH1D("h_HTv2Recipe_Exp","h_HTv2Recipe_Exp",12,100,2500);
  h_HTforLowNJetv2Recipe_Exp =new TH1D("h_HTforLowNJetv2Recipe_Exp","h_HTforLowNJetv2Recipe_Exp",12,100,2500);
  h_HTforHighNJetv2Recipe_Exp =new TH1D("h_HTforHighNJetv2Recipe_Exp","h_HTforHighNJetv2Recipe_Exp",12,100,2500);

  h_HTvsMHTforLowNJetv2Recipe_Exp =new TH2D("h_HTvsMHTforLowNJetv2Recipe_Exp","h_HTvsMHTforLowNJetv2Recipe_Exp",12,100,2500,16,200,1000);
  h_HTvsMHTforHighNJetv2Recipe_Exp =new TH2D("h_HTvsMHTforHighNJetv2Recipe_Exp","h_HTvsMHTforHighNJetv2Recipe_Exp",12,100,2500,16,200,1000);

  h_HT5v2Recipe_Exp =new TH1D("h_HT5v2Recipe_Exp","h_HT5v2Recipe_Exp",12,100,2500);
  h_HTRatiov2Recipe_Exp =new TH1D("h_HTRatiov2Recipe_Exp","h_HTRatiov2Recipe_Exp",20,0,5);
  h_HTRatioforLowNJetv2Recipe_Exp =new TH1D("h_HTRatioforLowNJetv2Recipe_Exp","h_HTRatioforLowNJetv2Recipe_Exp",20,0,5);
  h_HTRatioforHighNJetv2Recipe_Exp =new TH1D("h_HTRatioforHighNJetv2Recipe_Exp","h_HTRatioforHighNJetv2Recipe_Exp",20,0,5);

  h_MHTv2Recipe_Exp =new TH1D("h_MHTv2Recipe_Exp","h_MHTv2Recipe_Exp",16,200,1000);
  h_MHTforLowNJetv2Recipe_Exp =new TH1D("h_MHTforLowNJetv2Recipe_Exp","h_MHTforLowNJetv2Recipe_Exp",16,200,1000);
  h_MHTforHighNJetv2Recipe_Exp =new TH1D("h_MHTforHighNJetv2Recipe_Exp","h_MHTforHighNJetv2Recipe_Exp",16,200,1000);

  h_MHTPhiv2Recipe_Exp=new TH1D("h_MHTPhiv2Recipe_Exp","h_MHTPhiv2Recipe_Exp",7,-3.5,3.5);
  h_MHTPhiforLowNJetv2Recipe_Exp=new TH1D("h_MHTPhiforLowNJetv2Recipe_Exp","h_MHTPhiforLowNJetv2Recipe_Exp",7,-3.5,3.5);
  h_MHTPhiforHighNJetv2Recipe_Exp=new TH1D("h_MHTPhiforHighNJetv2Recipe_Exp","h_MHTPhiforHighNJetv2Recipe_Exp",7,-3.5,3.5);

  h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp=new TH2D("h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp","h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp",70,-3.5,3.5,20,0,5);
  h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp=new TH2D("h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp","h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp",70,-3.5,3.5,20,0,5);

  h_NJetv2Recipe_Exp =new TH1D("h_NJetv2Recipe_Exp","h_NJetv2Recipe_Exp",10,2,12);
  h_NJetvsHTv2Recipe_Exp=new TH2D("h_NJetvsHTv2Recipe_Exp","h_NJetvsHTv2Recipe_Exp",10,2,12,12,100,2500);
  h_NJetvsMHTv2Recipe_Exp=new TH2D("h_NJetvsMHTv2Recipe_Exp","h_NJetvsMHTv2Recipe_Exp",10,2,12,16,200,1000);
  h_NJetvsMHTPhiv2Recipe_Exp=new TH2D("h_NJetvsMHTPhiv2Recipe_Exp","h_NJetvsMHTPhiv2Recipe_Exp",10,2,12,7,-3.5,3.5);

  h_NJetforMHTminusHTv2Recipe_Exp =new TH1D("h_NJetforMHTminusHTv2Recipe_Exp","h_NJetforMHTminusHTv2Recipe_Exp",12,0,12);
  h_NBtagv2Recipe_Exp =new TH1D("h_NBtagv2Recipe_Exp","h_NBtagv2Recipe_Exp",5,0,5);
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
  h_JetPhiforHTv2Recipe_Exp=new TH1D("h_JetPhiforHTv2Recipe_Exp","h_JetPhiforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtforLowNJetforHTv2Recipe_Exp=new TH1D("h_JetPtforLowNJetforHTv2Recipe_Exp","h_JetPtforLowNJetforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforLowNJetforHTv2Recipe_Exp=new TH1D("h_JetEtaforLowNJetforHTv2Recipe_Exp","h_JetEtaforLowNJetforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforLowNJetforHTv2Recipe_Exp=new TH1D("h_JetPhiforLowNJetforHTv2Recipe_Exp","h_JetPhiforLowNJetforHTv2Recipe_Exp",70,-3.5,3.5);
  h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp","h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp",20,0.0,1000.0,50,-2.5,2.5);
  h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp","h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp",50,-2.5,2.5,70,-3.5,3.5);
  h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp=new TH2D("h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp","h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp",20,0.0,1000.0,7,-3.5,3.5);

  h_JetPtforHighNJetforHTv2Recipe_Exp=new TH1D("h_JetPtforHighNJetforHTv2Recipe_Exp","h_JetPtforHighNJetforHTv2Recipe_Exp",20,0.0,1000.0);
  h_JetEtaforHighNJetforHTv2Recipe_Exp=new TH1D("h_JetEtaforHighNJetforHTv2Recipe_Exp","h_JetEtaforHighNJetforHTv2Recipe_Exp",50,-2.5,2.5);
  h_JetPhiforHighNJetforHTv2Recipe_Exp=new TH1D("h_JetPhiforHighNJetforHTv2Recipe_Exp","h_JetPhiforHighNJetforHTv2Recipe_Exp",70,-3.5,3.5);
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
  h_JetPtvsPhiforHTv2Recipe_Exp=new TH2D("h_JetPtvsPhiforHTv2Recipe_Exp","h_JetPtvsPhiforHTv2Recipe_Exp",20,0.0,1000.0,70,-3.5,3.5);
  h_JetPtvsDPhiforHTv2Recipe_Exp=new TH2D("h_JetPtvsDPhiforHTv2Recipe_Exp","h_JetPtvsDPhiforHTv2Recipe_Exp",20,0.0,1000.0,32,0,3.2);
  h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp","h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);

  h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp","h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp","h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);
  h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp","h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);
  h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp","h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);

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
  h_JetPhiforMHTminusHTv2Recipe_Exp=new TH1D("h_JetPhiforMHTminusHTv2Recipe_Exp","h_JetPhiforMHTminusHTv2Recipe_Exp",70,-3.5,3.5);

  h_DphiOneforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiOneforMHTminusHTv2Recipe_Exp","h_DphiOneforMHTminusHTv2Recipe_Exp",32,0,3.2);
  h_DphiTwoforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiTwoforMHTminusHTv2Recipe_Exp","h_DphiTwoforMHTminusHTv2Recipe_Exp",32,0,3.2);
  h_DphiThreeforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiThreeforMHTminusHTv2Recipe_Exp","h_DphiThreeforMHTminusHTv2Recipe_Exp",32,0,3.2);
  h_DphiFourforMHTminusHTv2Recipe_Exp =new TH1D("h_DphiFourforMHTminusHTv2Recipe_Exp","h_DphiFourforMHTminusHTv2Recipe_Exp",32,0,3.2);

  h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp=new TH2D("h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp","h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,100,-5.,5.);
  h_JetPtvsEtaforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsEtaforMHTminusHTv2Recipe_Exp","h_JetPtvsEtaforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,100,-5.,5.);
  h_JetEtavsPhiforMHTminusHTv2Recipe_Exp=new TH2D("h_JetEtavsPhiforMHTminusHTv2Recipe_Exp","h_JetEtavsPhiforMHTminusHTv2Recipe_Exp",100,-5.,5.,70,-3.5,3.5);
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
  h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,20,0,1);
  h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);
  h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);
  h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp=new TH2D("h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp","h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp",20,0.0,1000.0,200,0,100);

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
  h_MHT_Pre =new TH1D("h_MHT_Pre","h_MHT_Pre",16,200,1000);
  h_NJet_Pre =new TH1D("h_NJet_Pre","h_NJet_Pre",10,2,12);
  h_NBtag_Pre =new TH1D("h_NBtag_Pre","h_NBtag_Pre",5,0,5);


  GetOutputList()->Add(h_Prediction);
  GetOutputList()->Add(h_CSStat); //one lepton CS
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
  GetOutputList()->Add(h_LepPhi_Exp); 
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

  GetOutputList()->Add(h_HTv2Recipe_Exp);
  GetOutputList()->Add(h_HTforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTvsMHTforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTvsMHTforHighNJetv2Recipe_Exp);

  GetOutputList()->Add(h_HT5v2Recipe_Exp);
  GetOutputList()->Add(h_HTRatiov2Recipe_Exp);
  GetOutputList()->Add(h_HTRatioforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_HTRatioforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTv2Recipe_Exp);
  GetOutputList()->Add(h_MHTforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp);
  GetOutputList()->Add(h_NJetv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsHTv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsMHTv2Recipe_Exp);
  GetOutputList()->Add(h_NJetvsMHTPhiv2Recipe_Exp);

  GetOutputList()->Add(h_NBtagv2Recipe_Exp);
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
  GetOutputList()->Add(h_JetPhiforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtaforHighNJetforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPhiforHighNJetforHTv2Recipe_Exp);
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
  GetOutputList()->Add(h_neutralHadronEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralHadronMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_neutralMultiplicityforHTv2Recipe_Exp);
  GetOutputList()->Add(h_photonEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_photonMultiplicityforHTv2Recipe_Exp);
  //  GetOutputList()->Add(h_qgLikelihoodforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsEtaforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetEtavsPhiforHTv2Recipe_Exp);
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
  GetOutputList()->Add(h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp);
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
  GetOutputList()->Add(h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp);
  GetOutputList()->Add(h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp);
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

  std::cout<<"Run on Data: "<<runOnData<<std::endl;
  std::cout<<"Run on SM MC: "<<runOnStandardModelMC<<std::endl;
  std::cout<<"Run on Signal MC: "<<runOnSignalMC<<std::endl;
  std::cout<<"----------------"<<std::endl;
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
}

Bool_t Prediction::Process(Long64_t entry)
{ //*AR-180619: Runs for every event
  //  std::cout<<"***Prediction::Process***"<<" entry "<<entry<<std::endl;

  resetValues();
  fChain->GetTree()->GetEntry(entry);
  //*AR:180917-HTgen_cut=0, hence this if condition has no role
  if(HTgen_cut > 0.01) if(madHT > HTgen_cut) return kTRUE;
  MuonsNum_ = Muons->size();
  ElectronsNum_ = Electrons->size();
  //*AR: 180917: NMuons and NElectrons are number of isolated electrons and muons
  //MuonsNum_ = NMuons;
  //ElectronsNum_ = NElectrons;
  double newGenHT=0;double newGenMHT=0;
  TVector3 temp3Vec;
  vector<TVector3>GenHT3JetVec,GenMHT3JetVec;
  TVector3 newGenMHT3Vec;
  int BTagsfrmCSV=0;

  vector<TVector3>Jetsv2Recipe;
  vector<int> HTJetsIdxv2Recipe;
  vector<int> MHTJetsIdxv2Recipe;
  vector<int> MHTminusHTJetsIdxv2Recipe;
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
  //  if(BTags>0)
  //std::cout<<" entry "<<" jets_size "<<Jets->size()<<" njets "<<NJets<<" btags "<<BTags<<endl;
  //*AR:181016: btags based on csv value instead of using value saved in ntuple
  for(unsigned j = 0; j < Jets->size(); ++j){
    double jetCSV=Jets_bDiscriminatorCSV->at(j);
    if(jetCSV>csvForBtag && Jets->at(j).Pt() > 30 && fabs(Jets->at(j).Eta())<2.4)
      BTagsfrmCSV++;
  }
  //*AR-181016: Recalculation of search variables after applying MET v2-recipe
  for(unsigned j = 0; j < Jets->size(); ++j){
    double jetPtv2Recipe= Jets->at(j).Pt()/Jets_jecFactor->at(j);
    if(jetPtv2Recipe >50 || (fabs(Jets->at(j).Eta()) < 2.65 || fabs(Jets->at(j).Eta()) > 3.139)){
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
    } //end of METv2 recipe
  } //end of loop over jets
  NJetsforMHTminusHTv2Recipe=MHTminusHTJetsIdxv2Recipe.size();  
  for(unsigned int i=0;i<HTJetsIdxv2Recipe.size();i++){
    int jetIdx=HTJetsIdxv2Recipe[i];
    HTv2Recipe+=Jets->at(jetIdx).Pt();
    NJetsv2Recipe++;
    if(Jets_bDiscriminatorCSV->at(jetIdx)>csvForBtag)
      BTagsv2Recipe++;
  }

  for(unsigned int i=0;i<MHTJetsIdxv2Recipe.size();i++){
    int jetIdx=MHTJetsIdxv2Recipe[i];
    temp3Vec.SetPtEtaPhi(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
    MHT3Vecv2Recipe-=temp3Vec;
    HT5v2Recipe+=Jets->at(jetIdx).Pt();
  }

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
  
  //*AR-181016: only considers single isolated lepton events(pT>20, eta<2.1) for CR and 0L events for signal region
  //pT>20 cut can be removed as MET triggers used for CR selection don't have any lepton pT threshold
  if(!GetSignalRegHists){
    if((MuonsNum_+ElectronsNum_) !=1) return kTRUE;

    if(MuonsNum_==1){
      for(unsigned int i=0;i<Muons->size();i++){
	//if(Muons_passIso->at(i)){
	  LepPt=Muons->at(i).Pt();
	  LepEta=Muons->at(i).Eta();
	  LepPhi=Muons->at(i).Phi();
	  //}
      }
    }

    if(ElectronsNum_==1){
      for(unsigned int i=0;i<Electrons->size();i++){
	//if(Electrons_passIso->at(i)){
	  LepPt=Electrons->at(i).Pt();
	  LepEta=Electrons->at(i).Eta();
	  LepPhi=Electrons->at(i).Phi();
	  //}
      }
    }

    if(LepPt<20 || fabs(LepEta)>2.1) 
      return kTRUE;
  } //end of if(!GetSignalRegHists)
  else
    if((MuonsNum_+ElectronsNum_) !=0) return kTRUE;

  //   std::cout<<" ht "<<HT<<" htv2 "<<HTv2Recipe<<" mht "<<MHT<<" mhtv2 "<<MHTv2Recipe<<" njets "<<NJets<<" njetv2 "<<NJetsv2Recipe<<" dphi1 "<<DeltaPhi1<<" dphiv2 "<<DeltaPhi1v2Recipe<<" dphi2 "<<DeltaPhi2<<" dphi2v2 "<<DeltaPhi2v2Recipe<<" dphi3 "<<DeltaPhi3<<"  dphi3v2 "<<DeltaPhi3v2Recipe<<" dphi4 "<<DeltaPhi4<< " dphi4v2 "<<DeltaPhi4v2Recipe<<endl;
  //*AR: 180917- Only consider events with HT>300, MHT>250, Njet>1.5
  if(runOnSignalMC && useGenHTMHT){
    if(newGenHT<minHT_ || newGenMHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
  }
  else{
    //    if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
    if(HTv2Recipe<minHT_ || MHTv2Recipe< minMHT_ || NJetsv2Recipe < minNJets_  ) return kTRUE;

  }

  //*AR: 180917-for high dphi: only events with all dphis>(0.5,0.5,0.3,0.3)
  //for low dphi: only events with either of dphis<(0.5,0.5,0.3,0.3)
  if(NJetsv2Recipe>=4){
    if(useDeltaPhiCut == 1)if(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_ || HTDeltaPhi4v2Recipe < deltaPhi4_) return kTRUE;
    if(useDeltaPhiCut == -1) if(!(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_ || HTDeltaPhi4v2Recipe < deltaPhi4_)) return kTRUE;
  }
  else if(NJetsv2Recipe==3){
    if(useDeltaPhiCut == 1)if(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_) return kTRUE;
    if(useDeltaPhiCut == -1) if(!(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_ || HTDeltaPhi3v2Recipe < deltaPhi3_)) return kTRUE;
  }
  else if(NJetsv2Recipe==2){
    if(useDeltaPhiCut == 1)if(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_) return kTRUE;
    if(useDeltaPhiCut == -1) if(!(HTDeltaPhi1v2Recipe < deltaPhi1_ || HTDeltaPhi2v2Recipe < deltaPhi2_)) return kTRUE;
  }
  else
    return kTRUE;
  
  //  if(useDeltaPhiCut == 1)  if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
  //  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
  
  if(applyFilters &&  !FiltersPass() ) return kTRUE;
  //*AR-180606:Only consider events with one isolated lepton at reco level and mT<100(no pT, eta cuts)
  
  if(!GetSignalRegHists){
    if(MuonsNum_==1 && ElectronsNum_==0){
      mtw =  Muons_MTW->at(0);
      
      //std::cout<<" entry "<<entry<<" 1mu event "<<endl;
      
      //*AR: 180917- Gets skimfile for signal and standard model MC. No skimFile for data 
      if(runOnSignalMC)
	SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_SLm";
      if(runOnStandardModelMC)
	SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_SLm";
    }else if(MuonsNum_==0 && ElectronsNum_==1){
      mtw =  Electrons_MTW->at(0);
      //std::cout<<" entry "<<entry<<" 1e event "<<endl;
      if(runOnSignalMC)
	SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_SLe";
      if(runOnStandardModelMC)
	SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_SLe";
    }
    //do not consider event if mT>100 
    if(mtw > 100) return kTRUE;
  }//end of if(!GetSignalRegHists)
//std::cout<<" passed mT cut "<<endl;
  isoTracksNum = isoElectronTracksNum + isoMuonTracksNum + isoPionTracksNum;
  //*AR: for 0L signal region, there should not be any isolated track
  if(GetSignalRegHists){
    if(isoTracksNum !=0){
      //  std::cout<<" isotrack nonzero "<<endl;
      return kTRUE;
    }
  }
/*
  for(unsigned i=0;i<TriggerNames->size();i++){
    std::cout<<" entry "<<entry<<" i "<<i<<" name "<< TriggerNames->at(i)<<endl;
  }
*/  
//  std::cout<<" 108 "<<TriggerNames->at(108)<<" 110 "<<TriggerNames->at(110)<<" 114 "<<TriggerNames->at(114)<<" 124 "<<TriggerNames->at(124)<<" 126 "<<TriggerNames->at(126)<<" 129 "<<TriggerNames->at(129)<<endl;
  // Signal region MET triggers applied only for data
  if(useTrigger) if(!TriggerPass->at(42) && !TriggerPass->at(43) &&!TriggerPass->at(44) && !TriggerPass->at(46) && !TriggerPass->at(47) && !TriggerPass->at(48)) return kTRUE;

  //  if(useTrigger) if(!TriggerPass->at(108) && !TriggerPass->at(110) &&!TriggerPass->at(114) && !TriggerPass->at(124) && !TriggerPass->at(126) && !TriggerPass->at(129)) return kTRUE;

  if(runOnSignalMC && useGenHTMHT){
    Bin_ = SearchBins_->GetBinNumber(newGenHT,newGenMHT,NJets,BTagsfrmCSV);
    BinQCD_ = SearchBinsQCD_->GetBinNumber(newGenHT,newGenMHT,NJets,BTagsfrmCSV);
  }
  else{
    //  Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTagsfrmCSV);
    //    BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTagsfrmCSV);

    Bin_ = SearchBins_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,BTagsv2Recipe);
    BinQCD_ = SearchBinsQCD_->GetBinNumber(HTv2Recipe,MHTv2Recipe,NJetsv2Recipe,BTagsv2Recipe);
  }
  //*AR-181016: Use only events falling into search bins
  if(Bin_ > 900 && BinQCD_ > 900) return kTRUE;

  h_YieldCutFlow->Fill(0);
  //*AR: 181107: check following condition if Dphi cut to be applied

  //  if((MHTminusHTJetsIdxv2Recipe.size()>0 && Jets->at(MHTminusHTJetsIdxv2Recipe[0]).Pt()>250 && (MHTminusHTDeltaPhi1v2Recipe>2.6 || MHTminusHTDeltaPhi1v2Recipe<0.1)) || (MHTminusHTJetsIdxv2Recipe.size()>1 && Jets->at(MHTminusHTJetsIdxv2Recipe[1]).Pt()>250 && (MHTminusHTDeltaPhi2v2Recipe>2.6 || MHTminusHTDeltaPhi2v2Recipe<0.1)))
  //return kTRUE;
  h_YieldCutFlow->Fill(1);
  //  std::cout<<" seg vio "<<endl;
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
    if(currentTree != treeName || SkimFilePath!=OldSkimFilePath){ //treeName = " "
      //  std::cout<<" new tree or new skimfile "<<endl;
      treeName = currentTree;
      OldSkimFilePath = SkimFilePath;
      TObjArray *optionArray = currentTree.Tokenize("/");
      TString currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
      currentFile = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
      string skimName="tree_TTJets_SingleLeptFromT.root";
      char SkimFile[500];
      if(currentFile.find("TTJets_SingleLeptFromTbar")!=string::npos) skimName="tree_TTJets_SingleLeptFromTbar.root"; 
      else if(currentFile.find("TTJets_SingleLeptFromT")!=string::npos) skimName="tree_TTJets_SingleLeptFromT.root"; 
      else if(currentFile.find("DiLept")!=string::npos)skimName="tree_TTJets_DiLept.root";
      else if(currentFile.find("TTJets_HT-600to800")!=string::npos)skimName="tree_TTJets_HT-600to800.root";
      else if(currentFile.find("TTJets_HT-800to1200")!=string::npos)skimName="tree_TTJets_HT-800to1200.root";
      else if(currentFile.find("TTJets_HT-1200to2500")!=string::npos)skimName="tree_TTJets_HT-1200to2500.root";
      else if(currentFile.find("TTJets_HT-2500toInf")!=string::npos)skimName="tree_TTJets_HT-2500toInf.root";
      else if(currentFile.find("Inclusive")!=string::npos)skimName="tree_TTJets.root";
      else if(currentFile.find("WJetsToLNu_HT-100To200")!=string::npos)skimName="tree_WJetsToLNu_HT-100to200.root";
      else if(currentFile.find("WJetsToLNu_HT-200To400")!=string::npos)skimName="tree_WJetsToLNu_HT-200to400.root";
      else if(currentFile.find("WJetsToLNu_HT-400To600")!=string::npos)skimName="tree_WJetsToLNu_HT-400to600.root";
      else if(currentFile.find("WJetsToLNu_HT-600To800")!=string::npos)skimName="tree_WJetsToLNu_HT-600to800.root";
      else if(currentFile.find("WJetsToLNu_HT-800To1200")!=string::npos)skimName="tree_WJetsToLNu_HT-800to1200.root";
      else if(currentFile.find("WJetsToLNu_HT-1200To2500")!=string::npos)skimName="tree_WJetsToLNu_HT-1200to2500.root";
      else if(currentFile.find("WJetsToLNu_HT-2500ToInf")!=string::npos)skimName="tree_WJetsToLNu_HT-2500toInf.root"; 
      else if(currentFile.find("tW_antitop")!=string::npos)skimName="tree_ST_tW_antitop.root";
      else if(currentFile.find("tW_top")!=string::npos)skimName="tree_ST_tW_top.root";
      else if(currentFile.find("t-channel_top")!=string::npos)skimName="tree_ST_t-channel_top.root";
      else if(currentFile.find("t-channel_antitop")!=string::npos)skimName="tree_ST_t-channel_antitop.root"; 
      else if(currentFile.find("s-channel")!=string::npos)skimName="tree_ST_s-channel.root"; 
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
    
    if(currentFile.find("TTJets_SingleLeptFromTbar")!=string::npos || currentFile.find("TTJets_SingleLeptFromT")!=string::npos || currentFile.find("DiLept")!=string::npos){
      madHTcut=600;
      if(madHT > madHTcut){
	//	std::cout<<" currentTree "<<currentTree<<" entry "<<entry<<" madHT "<<madHT<< " &&&not passed&&& "<<endl;
	return kTRUE;
      }
    }

   
    if(doISRcorr){ //true for signal mc
      w_isr = isrcorr->GetCorrection(NJetsISR);
      Weight *= w_isr;
      //std::cout<<" weight_afterISRcorr "<<Weight<<endl;
    }

    if(doBTagCorr){ //true for signal and standard model mc
      bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
      if(runOnSignalMC && useGenHTMHT){
	bTagBins = {SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,0), SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,1), SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,2), NJets < 3 ? 999 : SearchBins_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,3)};  
	bTagBinsQCD = {SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,0), SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,1), SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,2), NJets < 3 ? 999 : SearchBinsQCD_BTags_->GetBinNumber(newGenHT,newGenMHT,NJets,3)};
      }   
      else{
	bTagBins = {SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,0), SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,1), SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,2), NJets < 3 ? 999 : SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,3)};  
	bTagBinsQCD = {SearchBinsQCD_BTags_->GetBinNumber(HT,MHT,NJets,0), SearchBinsQCD_BTags_->GetBinNumber(HT,MHT,NJets,1), SearchBinsQCD_BTags_->GetBinNumber(HT,MHT,NJets,2), NJets < 3 ? 999 : SearchBinsQCD_BTags_->GetBinNumber(HT,MHT,NJets,3)};  }
      
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
  //*AR: true only for signal MC and useGenHTMHT=false
  if(useTriggerEffWeight){ // false for SM MC
    //GetSignalTriggerEffWeight and GetTriggerEffWeight are methods defined in LLTools.h and values are given as function of MHT.
    if(runOnSignalMC){
      Weight *= GetSignalTriggerEffWeight(HT,MHT);
      //std::cout<<" weight_afterTrigEff "<<Weight<<endl;
    }else{
      Weight *= GetTriggerEffWeight(MHT);
    }
  }

  if(doPUreweighting){ //true only for signal mc
    w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
    Weight *= w_pu;
    //std::cout<<" weight_afterpu "<<Weight<<endl;
    
  }
  
  if(runOnData) Weight = 1.;
  else{
    //*AR:180619: As /uscms_data/d3/arane/work/RA2bInterpretation/CMSSW_7_4_7/src/SCRA2BLE/DatacardBuilder/GenMHTCorrection.py scales signal contamination by lumi in /pb, here signal histograms are saved at 1/pb scale.
    if(!runOnSignalMC)
      Weight *= scaleFactorWeight;
  }
  //  std::cout<<" weight_afterlumiscale "<<Weight<<endl;


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
    //    h_electronEnergyFractionforHTv2Recipe_Exp->Fill(Jets_electronEnergyFraction->at(jetIdx));
    h_electronMultiplicityforHTv2Recipe_Exp->Fill(Jets_electronMultiplicity->at(jetIdx));
    //      h_hadronFlavorforHTv2Recipe_Exp->Fill(Jets_hadronFlavor->at(jetIdx)); 
    //    h_hfEMEnergyFractionforHTv2Recipe_Exp->Fill(Jets_hfEMEnergyFraction->at(jetIdx));
    //    h_hfHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets_hfHadronEnergyFraction->at(jetIdx));
    //    h_multiplicityforHTv2Recipe_Exp->Fill(Jets_multiplicity->at(jetIdx)); 
    h_muonEnergyFractionforHTv2Recipe_Exp->Fill(Jets_muonEnergyFraction->at(jetIdx)); 
    h_muonMultiplicityforHTv2Recipe_Exp->Fill(Jets_muonMultiplicity->at(jetIdx)); 
    h_neutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets_neutralEmEnergyFraction->at(jetIdx));
    h_neutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_neutralHadronMultiplicityforHTv2Recipe_Exp->Fill(Jets_neutralHadronMultiplicity->at(jetIdx)); 
    h_neutralMultiplicityforHTv2Recipe_Exp->Fill(Jets_neutralMultiplicity->at(jetIdx));
    h_photonEnergyFractionforHTv2Recipe_Exp->Fill(Jets_photonEnergyFraction->at(jetIdx));
    h_photonMultiplicityforHTv2Recipe_Exp->Fill(Jets_photonMultiplicity->at(jetIdx));
     //  h_qgLikelihoodforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i]);
    
    if(i<=3){
      h_JetPtforHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforHTv2RecipeLead_Exp->Fill(Jets->at(jetIdx).Phi());
      if(i==0)
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi1v2Recipe);
      if(i==1)
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi2v2Recipe);
      if(i==2)
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi3v2Recipe);
      if(i==3)
	h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),HTDeltaPhi4v2Recipe);
    
    }
    else{
	h_JetPtforHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Pt());
	h_JetEtaforHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Eta());
	h_JetPhiforHTv2RecipeNotLead_Exp->Fill(Jets->at(jetIdx).Phi());
    }
    h_JetPtforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
    h_JetEtaforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
    h_JetPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
    if(NJetsv2Recipe<6){
      h_JetPtforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta());
      h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      if(i==0)
	h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),MHTPhiv2Recipe);

    }
    if(NJetsv2Recipe>=6){
      h_JetPtforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
      h_JetEtaforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
      h_JetPhiforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
      h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta());
      h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());
      if(i==0)
	h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),MHTPhiv2Recipe);
    }
    h_JetIdxvsEtaforHTv2Recipe_Exp->Fill(i,Jets->at(jetIdx).Eta());
    h_JetMultvsEtaforHTv2Recipe_Exp->Fill(HTJetsIdxv2Recipe.size(),Jets->at(jetIdx).Eta());
    h_JetPtvsEtaforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Eta());
    h_JetEtavsPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets->at(jetIdx).Phi());

    h_JetPtvsPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets->at(jetIdx).Phi());
    
    double DphiJetMHT=fabs(TVector2::Phi_mpi_pi(Jets->at(jetIdx).Phi() - MHTPhiv2Recipe ));
    double neutralEMbyphoton=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_photonEnergyFraction->at(jetIdx);
    double neutralEMbyneutralHadron=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_neutralHadronEnergyFraction->at(jetIdx);
    double neutralEMbychargedEM=Jets_neutralEmEnergyFraction->at(jetIdx)/Jets_chargedEmEnergyFraction->at(jetIdx);

    h_JetPtvsDPhiforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),DphiJetMHT);
    h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_chargedEmEnergyFraction->at(jetIdx));
    h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_neutralEmEnergyFraction->at(jetIdx));
    h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyphoton);
    h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyneutralHadron);
    h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbychargedEM);
    h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralEmEnergyFraction->at(jetIdx));
    h_JetPhivsneutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralEmEnergyFraction->at(jetIdx));

    h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_chargedHadronEnergyFraction->at(jetIdx));
    h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetPhivsneutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralHadronEnergyFraction->at(jetIdx));

  }





  for(unsigned int i=0;i<MHTminusHTJetsIdxv2Recipe.size();i++){
    int jetIdx=MHTminusHTJetsIdxv2Recipe[i]; 
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
    //    h_electronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_electronEnergyFraction->at(jetIdx));
    h_electronMultiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_electronMultiplicity->at(jetIdx));
    //      h_hadronFlavorforMHTminusHTv2Recipe_Exp->Fill(Jets_hadronFlavor->at(jetIdx)); 
    //    h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_hfEMEnergyFraction->at(jetIdx));
    //    h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets_hfHadronEnergyFraction->at(jetIdx));
    //    h_multiplicityforMHTminusHTv2Recipe_Exp->Fill(Jets_multiplicity->at(jetIdx)); 
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
    h_JetPtforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt());
    h_JetEtaforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta());
    h_JetPhiforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi());
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
    h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyphoton);
    h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbyneutralHadron);
    h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),neutralEMbychargedEM);

    h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralEmEnergyFraction->at(jetIdx));
    h_JetPhivsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralEmEnergyFraction->at(jetIdx));

    h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_chargedHadronEnergyFraction->at(jetIdx));
    h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Pt(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Eta(),Jets_neutralHadronEnergyFraction->at(jetIdx));
    h_JetPhivsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jets->at(jetIdx).Phi(),Jets_neutralHadronEnergyFraction->at(jetIdx));

  }
  
  /*


  for(unsigned int i=0;i<Jetsv2Recipe.size();i++){
   if(Jetsv2Recipe[i].Pt()>30 && fabs(Jetsv2Recipe[i].Eta())<2.4){
     double rawPt=Jetsv2Recipe[i].Pt()/JetsJECv2Recipe[i];
     h_rawJetPtforHTv2Recipe_Exp->Fill(rawPt);
     h_rawJetPtvsEtaforHTv2Recipe_Exp->Fill(rawPt,Jetsv2Recipe[i].Eta());
      
      h_chargedEmEnergyFractionforHTv2Recipe_Exp->Fill(JetschargedEmEnergyFractionv2Recipe[i]);
      h_chargedHadronEnergyFractionforHTv2Recipe_Exp->Fill(JetschargedHadronEnergyFractionv2Recipe[i]);
      h_chargedHadronMultiplicityforHTv2Recipe_Exp->Fill(JetschargedHadronMultiplicityv2Recipe[i]);  
      h_chargedMultiplicityforHTv2Recipe_Exp->Fill(JetschargedMultiplicityv2Recipe[i]);
      h_electronEnergyFractionforHTv2Recipe_Exp->Fill(JetselectronEnergyFractionv2Recipe[i]);
      h_electronMultiplicityforHTv2Recipe_Exp->Fill(JetselectronMultiplicityv2Recipe[i]);
      //      h_hadronFlavorforHTv2Recipe_Exp->Fill(JetshadronFlavorv2Recipe[i]); 
      h_hfEMEnergyFractionforHTv2Recipe_Exp->Fill(JetshfEMEnergyFractionv2Recipe[i]);
      h_hfHadronEnergyFractionforHTv2Recipe_Exp->Fill(JetshfHadronEnergyFractionv2Recipe[i]);
      h_multiplicityforHTv2Recipe_Exp->Fill(Jetsmultiplicityv2Recipe[i]); 
      h_muonEnergyFractionforHTv2Recipe_Exp->Fill(JetsmuonEnergyFractionv2Recipe[i]); 
      h_muonMultiplicityforHTv2Recipe_Exp->Fill(JetsmuonMultiplicityv2Recipe[i]); 
      h_neutralEmEnergyFractionforHTv2Recipe_Exp->Fill(JetsneutralEmEnergyFractionv2Recipe[i]);
      h_neutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(JetsneutralHadronEnergyFractionv2Recipe[i]);
      h_neutralHadronMultiplicityforHTv2Recipe_Exp->Fill(JetsneutralHadronMultiplicityv2Recipe[i]); 
      h_neutralMultiplicityforHTv2Recipe_Exp->Fill(JetsneutralMultiplicityv2Recipe[i]);
      h_photonEnergyFractionforHTv2Recipe_Exp->Fill(JetsphotonEnergyFractionv2Recipe[i]);
      h_photonMultiplicityforHTv2Recipe_Exp->Fill(JetsphotonMultiplicityv2Recipe[i]);
  //  h_qgLikelihoodforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i]);

      if(i<=3){
	h_JetPtforHTv2RecipeLead_Exp->Fill(Jetsv2Recipe[i].Pt());
	h_JetEtaforHTv2RecipeLead_Exp->Fill(Jetsv2Recipe[i].Eta());
	h_JetPhiforHTv2RecipeLead_Exp->Fill(Jetsv2Recipe[i].Phi());
      }
      else{
	h_JetPtforHTv2RecipeNotLead_Exp->Fill(Jetsv2Recipe[i].Pt());
	h_JetEtaforHTv2RecipeNotLead_Exp->Fill(Jetsv2Recipe[i].Eta());
	h_JetPhiforHTv2RecipeNotLead_Exp->Fill(Jetsv2Recipe[i].Phi());
      }
      h_JetPtforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt());
      h_JetEtaforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Eta());
      h_JetPhiforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Phi());
      h_JetPtvsEtaforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),Jetsv2Recipe[i].Eta());
      h_JetPtvsPhiforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),Jetsv2Recipe[i].Phi());

      double DphiJetMHT=fabs(TVector2::Phi_mpi_pi(Jetsv2Recipe[i].Phi() - MHTPhiv2Recipe ));
      h_JetPtvsDPhiforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),DphiJetMHT);
      h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetschargedEmEnergyFractionv2Recipe[i]);
      h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetsneutralEmEnergyFractionv2Recipe[i]);
      h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetschargedHadronEnergyFractionv2Recipe[i]);
      h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetsneutralHadronEnergyFractionv2Recipe[i]);
   }
   
   if(Jetsv2Recipe[i].Pt()>30 && fabs(Jetsv2Recipe[i].Eta())>2.4 && fabs(Jetsv2Recipe[i].Eta())<5.0){
      double rawPt=Jetsv2Recipe[i].Pt()/JetsJECv2Recipe[i];    
      //      std::cout<<" v2 jets "<<" i "<<i<< "raw pt "<<rawPt<<" eta "<<Jetsv2Recipe[i].Eta()<<endl;
      h_rawJetPtforMHTminusHTv2Recipe_Exp->Fill(rawPt);
      h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp->Fill(rawPt,Jetsv2Recipe[i].Eta());

      h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetschargedEmEnergyFractionv2Recipe[i]);
      h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetschargedHadronEnergyFractionv2Recipe[i]);
      h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp->Fill(JetschargedHadronMultiplicityv2Recipe[i]);  
      h_chargedMultiplicityforMHTminusHTv2Recipe_Exp->Fill(JetschargedMultiplicityv2Recipe[i]);
      h_electronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetselectronEnergyFractionv2Recipe[i]);
      h_electronMultiplicityforMHTminusHTv2Recipe_Exp->Fill(JetselectronMultiplicityv2Recipe[i]);
      //      h_hadronFlavorforMHTminusHTv2Recipe_Exp->Fill(JetshadronFlavorv2Recipe[i]); 
      h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetshfEMEnergyFractionv2Recipe[i]);
      h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetshfHadronEnergyFractionv2Recipe[i]);
      h_multiplicityforMHTminusHTv2Recipe_Exp->Fill(Jetsmultiplicityv2Recipe[i]); 
      h_muonEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetsmuonEnergyFractionv2Recipe[i]); 
      h_muonMultiplicityforMHTminusHTv2Recipe_Exp->Fill(JetsmuonMultiplicityv2Recipe[i]); 
      h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetsneutralEmEnergyFractionv2Recipe[i]);
      h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetsneutralHadronEnergyFractionv2Recipe[i]);
      h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp->Fill(JetsneutralHadronMultiplicityv2Recipe[i]); 
      h_neutralMultiplicityforMHTminusHTv2Recipe_Exp->Fill(JetsneutralMultiplicityv2Recipe[i]);
      h_photonEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(JetsphotonEnergyFractionv2Recipe[i]);
      h_photonMultiplicityforMHTminusHTv2Recipe_Exp->Fill(JetsphotonMultiplicityv2Recipe[i]);



      if(i<=3){
	h_JetPtforMHTminusHTv2RecipeLead_Exp->Fill(Jetsv2Recipe[i].Pt());
	h_JetEtaforMHTminusHTv2RecipeLead_Exp->Fill(Jetsv2Recipe[i].Eta());
	h_JetPhiforMHTminusHTv2RecipeLead_Exp->Fill(Jetsv2Recipe[i].Phi());
      }
      else{
	h_JetPtforMHTminusHTv2RecipeNotLead_Exp->Fill(Jetsv2Recipe[i].Pt());
	h_JetEtaforMHTminusHTv2RecipeNotLead_Exp->Fill(Jetsv2Recipe[i].Eta());
	h_JetPhiforMHTminusHTv2RecipeNotLead_Exp->Fill(Jetsv2Recipe[i].Phi());
      }
      h_JetPtforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt());
      h_JetEtaforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Eta());
      h_JetPhiforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Phi());
      h_JetPtvsEtaforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),Jetsv2Recipe[i].Eta());
      h_JetPtvsPhiforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),Jetsv2Recipe[i].Phi());

      double DphiJetMHT=fabs(TVector2::Phi_mpi_pi(Jetsv2Recipe[i].Phi() - MHTPhiv2Recipe ));
      h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),DphiJetMHT);
      h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetschargedEmEnergyFractionv2Recipe[i]);
      h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetsneutralEmEnergyFractionv2Recipe[i]);
      h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetschargedHadronEnergyFractionv2Recipe[i]);
      h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp->Fill(Jetsv2Recipe[i].Pt(),JetsneutralHadronEnergyFractionv2Recipe[i]);


    }
    
  } 

*/



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
    if(applySFs){ //true for data
      TF = h_0L1L_SF_SB->GetBinContent(bTagBinQCD);
      if(TF < 0) TF = h_0L1L_SB->GetBinContent(bTagBinQCD);
    }else{ //true for SM and signal MC
      TF = h_0L1L_SB->GetBinContent(bTagBinQCD);
    }
    HTRatio=HT5/HT;
    HTRatiov2Recipe=HT5v2Recipe/HTv2Recipe;
    RecHTRatiov2Recipe=1/HTRatiov2Recipe;    
//std::cout<<" i "<<i<<" bTagBin "<<bTagBin<<" *** Seg Vio3 *** "<<endl;
    //*AR: 180917- These histograms represent yield in CR as TF is not applied
    h_CSStat->Fill(bTagBin, WeightBtagProb);
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
    h_LepPhi_Exp->Fill(LepPhi,WeightBtagProb);


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

    h_HTv2Recipe_Exp->Fill(HTv2Recipe,WeightBtagProb);
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
    h_NJetvsHTv2Recipe_Exp->Fill(NJetsv2Recipe,HTv2Recipe);
    h_NJetvsMHTv2Recipe_Exp->Fill(NJetsv2Recipe,MHTv2Recipe);
    h_NJetvsMHTPhiv2Recipe_Exp->Fill(NJetsv2Recipe,MHTPhiv2Recipe);
    h_NJetforMHTminusHTv2Recipe_Exp->Fill(NJetsforMHTminusHTv2Recipe,WeightBtagProb);

    h_NBtagv2Recipe_Exp->Fill(BTagsv2Recipe,WeightBtagProb);
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
    h_HT_Pre->Fill(HT,WeightBtagProb*TF);
    h_MHT_Pre->Fill(MHT,WeightBtagProb*TF);
    h_NJet_Pre->Fill(NJets,WeightBtagProb*TF);
    if(doBTagCorr) //true for signal and SM MC
      h_NBtag_Pre->Fill(i,WeightBtagProb*TF);
    else //true for data
      h_NBtag_Pre->Fill(BTagsfrmCSV,WeightBtagProb*TF);
    
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
  h_LepPhi_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_LepPhi_Exp"));

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
  h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp"));

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


  h_HTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTv2Recipe_Exp"));
  h_HTforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTforLowNJetv2Recipe_Exp"));
  h_HTforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTforHighNJetv2Recipe_Exp"));

  h_HTvsMHTforLowNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HTvsMHTforLowNJetv2Recipe_Exp"));
  h_HTvsMHTforHighNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_HTvsMHTforHighNJetv2Recipe_Exp"));
  h_HT5v2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT5v2Recipe_Exp"));
  h_HTRatiov2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatiov2Recipe_Exp"));
  h_HTRatioforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatioforLowNJetv2Recipe_Exp"));
  h_HTRatioforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HTRatioforHighNJetv2Recipe_Exp"));

  h_MHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTv2Recipe_Exp"));
  h_MHTforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTforLowNJetv2Recipe_Exp"));
  h_MHTforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTforHighNJetv2Recipe_Exp"));

  h_MHTPhiv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiv2Recipe_Exp"));
  h_MHTPhiforLowNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiforLowNJetv2Recipe_Exp"));
  h_MHTPhiforHighNJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiforHighNJetv2Recipe_Exp"));

  h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp"));
  h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp"));
  h_NJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetv2Recipe_Exp"));
  h_NJetvsHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsHTv2Recipe_Exp"));
  h_NJetvsMHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsMHTv2Recipe_Exp"));
  h_NJetvsMHTPhiv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_NJetvsMHTPhiv2Recipe_Exp"));

  h_NJetforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetforMHTminusHTv2Recipe_Exp"));
  h_NBtagv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtagv2Recipe_Exp"));
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
  h_JetPhiforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHTv2Recipe_Exp"));
  h_JetPtforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforLowNJetforHTv2Recipe_Exp"));
  h_JetEtaforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforLowNJetforHTv2Recipe_Exp"));
  h_JetPhiforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforLowNJetforHTv2Recipe_Exp"));
  h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp"));
  h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp"));

  h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp"));

  h_JetPtforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPtforHighNJetforHTv2Recipe_Exp"));
  h_JetEtaforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetEtaforHighNJetforHTv2Recipe_Exp"));
  h_JetPhiforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforHighNJetforHTv2Recipe_Exp"));
  h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp"));
  h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp"));
  h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp"));

  h_rawJetPtvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_rawJetPtvsEtaforHTv2Recipe_Exp"));
  h_JetIdxvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetIdxvsEtaforHTv2Recipe_Exp")); 
  h_JetMultvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetMultvsEtaforHTv2Recipe_Exp"));
  h_JetPtvsEtaforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforHTv2Recipe_Exp"));
  h_JetEtavsPhiforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHTv2Recipe_Exp"));
  h_JetPtvsHTRatioforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsHTRatioforHTv2Recipe_Exp"));
  h_JetEtavsHTRatioforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsHTRatioforHTv2Recipe_Exp"));
  h_JetPhivsHTRatioforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsHTRatioforHTv2Recipe_Exp"));
  h_JetPhivsDPhiLeadforHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsDPhiLeadforHTv2Recipe_Exp"));
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
  h_neutralHadronEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralHadronEnergyFractionforHTv2Recipe_Exp"));
  h_neutralHadronMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralHadronMultiplicityforHTv2Recipe_Exp")); 
  h_neutralMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_neutralMultiplicityforHTv2Recipe_Exp"));
  h_photonEnergyFractionforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_photonEnergyFractionforHTv2Recipe_Exp"));
  h_photonMultiplicityforHTv2Recipe_Exp=dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_photonMultiplicityforHTv2Recipe_Exp"));
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
  h_JetPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_JetPhiforMHTminusHTv2Recipe_Exp"));

  h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp"));
  h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp")); 
  h_JetMultvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetMultvsEtaforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsEtaforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsEtaforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp"));

  h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp"));
  h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp"));
  h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp"));
  h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp"));

  h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp"));
  h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp"));

  h_JetPtvsPhiforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsPhiforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp"));
  h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp"));
  h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp= dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp"));

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

  TFile *outPutFile = new TFile(fileName,"RECREATE"); ;
  outPutFile->cd();
  /*
  for(unsigned int i=1; i<=174;i++){
    std::cout<<" i "<<i<<" binVal "<<h_Prediction->GetBinContent(i)<<endl;
  }
*/
  h_Prediction->Write();
  h_CSStat->Write();
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
  h_LepPhi_Exp->Write(); 

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


  h_HTv2Recipe_Exp->Write();
  h_HTforLowNJetv2Recipe_Exp->Write();
  h_HTforHighNJetv2Recipe_Exp->Write();
  h_HTvsMHTforLowNJetv2Recipe_Exp->Write();
  h_HTvsMHTforHighNJetv2Recipe_Exp->Write();
  h_HT5v2Recipe_Exp->Write();
  h_HTRatiov2Recipe_Exp->Write();
  h_HTRatioforLowNJetv2Recipe_Exp->Write();
  h_HTRatioforHighNJetv2Recipe_Exp->Write();

  h_MHTv2Recipe_Exp->Write();
  h_MHTforLowNJetv2Recipe_Exp->Write();
  h_MHTforHighNJetv2Recipe_Exp->Write();

  h_MHTPhiv2Recipe_Exp->Write();
  h_MHTPhiforLowNJetv2Recipe_Exp->Write();
  h_MHTPhiforHighNJetv2Recipe_Exp->Write();
  h_MHTPhivsHTRatioforLowNJetv2Recipe_Exp->Write();
  h_MHTPhivsHTRatioforHighNJetv2Recipe_Exp->Write();
  h_NJetv2Recipe_Exp->Write();
  h_NJetvsHTv2Recipe_Exp->Write();
  h_NJetvsMHTv2Recipe_Exp->Write();
  h_NJetvsMHTPhiv2Recipe_Exp->Write();
  h_NJetforMHTminusHTv2Recipe_Exp->Write();
  h_NBtagv2Recipe_Exp->Write();
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
  h_JetPhiforHTv2Recipe_Exp->Write();
  h_JetPtforLowNJetforHTv2Recipe_Exp->Write();
  h_JetEtaforLowNJetforHTv2Recipe_Exp->Write();
  h_JetPhiforLowNJetforHTv2Recipe_Exp->Write();
  h_JetPtvsEtaforLowNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforLowNJetforHTv2Recipe_Exp->Write();
  h_JetPtvsMHTPhiforLowNJetforHTv2Recipe_Exp->Write();
  h_JetPtforHighNJetforHTv2Recipe_Exp->Write();
  h_JetEtaforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPhiforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPtvsEtaforHighNJetforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforHighNJetforHTv2Recipe_Exp->Write();
  h_JetPtvsMHTPhiforHighNJetforHTv2Recipe_Exp->Write();
  h_rawJetPtvsEtaforHTv2Recipe_Exp->Write();
  h_JetIdxvsEtaforHTv2Recipe_Exp->Write();
  h_JetMultvsEtaforHTv2Recipe_Exp->Write();
  h_JetPtvsEtaforHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforHTv2Recipe_Exp->Write();
  h_JetPtvsHTRatioforHTv2Recipe_Exp->Write();
  h_JetEtavsHTRatioforHTv2Recipe_Exp->Write();
  h_JetPhivsHTRatioforHTv2Recipe_Exp->Write();
  h_JetPhivsDPhiLeadforHTv2Recipe_Exp->Write();
  h_MHTPhivsJetPhiforHTv2Recipe_Exp->Write();
  h_RecHTRatiovsDPhiforHTv2Recipe_Exp->Write();
  h_RecHTRatiovsDPhiforAllv2Recipe_Exp->Write(); 
  h_JetPtvsPhiforHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforHTv2Recipe_Exp->Write();
  h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyphotonFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyneutralHadronFractionforHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbychargedEMFractionforHTv2Recipe_Exp->Write();
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
  h_neutralHadronEnergyFractionforHTv2Recipe_Exp->Write();
  h_neutralHadronMultiplicityforHTv2Recipe_Exp->Write(); 
  std::cout<<" seg vio54 "<<endl;

  h_neutralMultiplicityforHTv2Recipe_Exp->Write();
  std::cout<<" seg vio55 "<<endl;

  h_photonEnergyFractionforHTv2Recipe_Exp->Write();
  std::cout<<" seg vio56 "<<endl;

  h_photonMultiplicityforHTv2Recipe_Exp->Write();

  std::cout<<" seg vio6 "<<endl;




  h_JetPtforMHTminusHTv2RecipeLead_Exp->Write();
  h_JetEtaforMHTminusHTv2RecipeLead_Exp->Write();
  h_JetPhiforMHTminusHTv2RecipeLead_Exp->Write();
  h_JetPtforMHTminusHTv2RecipeNotLead_Exp->Write();
  h_JetEtaforMHTminusHTv2RecipeNotLead_Exp->Write();
  h_JetPhiforMHTminusHTv2RecipeNotLead_Exp->Write();
  h_JetPtforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetPhiforMHTminusHTv2Recipe_Exp->Write();
  h_rawJetPtforMHTminusHTv2Recipe_Exp->Write();

  h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetMultvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsEtaforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsPhiforHighPtforMHTminusHTv2Recipe_Exp->Write();

  h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp->Write();
  h_JetEtavsHTRatioforMHTminusHTv2Recipe_Exp->Write();
  h_JetPhivsHTRatioforMHTminusHTv2Recipe_Exp->Write();
  h_JetPhivsDPhiLeadforMHTminusHTv2Recipe_Exp->Write();

  h_MHTPhivsJetPhiforMHTminusHTv2Recipe_Exp->Write();
  h_RecHTRatiovsDPhiforMHTminusHTv2Recipe_Exp->Write();

  h_JetPtvsPhiforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyphotonFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbyneutralHadronFractionforMHTminusHTv2Recipe_Exp->Write();
  h_JetPtvsneutralEMbychargedEMFractionforMHTminusHTv2Recipe_Exp->Write();

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
    if(HBHENoiseFilter!=1) result=false;
    if(HBHEIsoNoiseFilter!=1) result=false;
    if(EcalDeadCellTriggerPrimitiveFilter!=1) result=false;    
    if(eeBadScFilter!=1) result=false;
    //    if(ecalBadCalibFilter!=1) result=false;
    if(runOnData){
      if(!BadChargedCandidateFilter) result=false;
      if(!BadPFMuonFilter) result=false;
      if(globalTightHalo2016Filter!=1) result=false;
    }    
  }
  if(NVtx<=0) result=false;

  // Do not apply on fastSim samples!
  if(!runOnSignalMC) if(!JetID) result=false;

  // Preliminary filters
  if(PFCaloMETRatio>5) result=false;

  // Check efficiency of filter
  
  if(result)
    for(unsigned j = 0; j < Jets->size(); j++){
      if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
      if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
	//std::cout<<"found bad muon jet"<<std::endl;
	result=false;
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

  return result;
}
