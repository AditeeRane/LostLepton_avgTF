#ifndef Prediction_h
#define Prediction_h

#include "LLTools.h"
#include "SearchBins.h"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TProfile.h>
#include "TVector2.h"
#include <cmath>
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TKey.h"
#include "TLorentzVector.h"
#include <fstream>
#include "isr/ISRCorrector.h"
#include "btag/BTagCorrector.h"


////////////////////////
//////// Options
//////// SET DEPENDING ON SAMPLE: data, MC, signal!
///////////////////////

// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = -1;  //<-check------------------------

const bool runOnData = true;   //<-check:true only for data------------------------
const bool runOnStandardModelMC = false;  //<-check:true only for MC------------------------
const bool runOnSignalMC = false;  //<-check------------------------
bool GetSignalRegHists= true;
//*AR: To select events from given runs in data, which are allowed to unblind from 2017 in signal region.
bool RunSelectiveEvents= true;

// Use TFs with/without SFs
const bool applySFs = true; //check:true only for data
const double csvForBtag=0.8838;
// Use TFs with/without SFs
const double scaleFactorWeight = 35862.351;

// Only needed if running on full nTuples not on Skims (bTag reweighting)
// Does not matter for Data
const bool runOnNtuples = true;
const string path_toSkims("root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_SLm/");

// Useful for T2tt corridor studies
//*AR:180621-"true" only for genMHT version of signal contamination
const bool useGenHTMHT = false;

// Do top-pt reweightung
const bool topPTreweight = false;

// pu
const TString path_puHist("pu/PileupHistograms_0121_69p2mb_pm4p6.root");
// bTag corrections
const string path_bTagCalib("btag/CSVv2_Moriond17_B_H_mod.csv");
const string path_bTagCalibFastSim("btag/fastsim_csvv2_ttbar_26_1_2017.csv");
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const TString path_ISRcorr("isr/ISRWeights.root");
// Signal x-sec: "dict_xsec.txt" for gluino pair prod; "dict_xsec_T2.txt" for (anti)stop pair prod.
const string path_xsecT1T5("xsec/dict_xsec.txt");
const string path_xsecT2("xsec/dict_xsec_T2.txt");


////////////////////////
//////// Usually don't have to be changed
///////////////////////

const bool applyFilters=true;


////////////////////////
//////// Don't change anything below
///////////////////////

const double minHT_=300;
//const double minHT_=250;
const double minMHT_=250;
const double minNJets_=1.5;
const double deltaPhi1_=0.5;
const double deltaPhi2_=0.5;
const double deltaPhi3_=0.3;
const double deltaPhi4_=0.3;
const double minDeltaPhiN_=4.0;


class Prediction : public TSelector {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  void resetValues();
  bool FiltersPass();
  vector<string> skmInput(string mom);
  
  //Options
  bool useTrigger = false;
  bool useTriggerEffWeight = false;
  bool doPUreweighting = false;
  bool doBTagCorr = false;  //do not change this value here, later it is turned "true" for !data
  bool doISRcorr = false; 
  bool useFilterData = false;

  // output variables
  std::string fname; // for fetching file name
  TString fileName;
  Double_t HTgen_cut = 0;
  string currentFile;
  TFile* pufile = 0;
  TH1* puhist = 0;
  
  std::vector<std::pair<double, double>> xsecsT1T5;
  std::vector<std::pair<double, double>> xsecsT2;
  std::vector<std::pair<double, double>> *xsecs = 0;

  // Output
  TH1D* h_Prediction = 0;
  TH1D* h_YieldCutFlow=0;
  TH1D* h_CSStat = 0;
  TH1D* h_HT_Exp=0;
  TH1D* h_HT5_Exp=0;
  TH1D* h_HTRatio_Exp=0;
  TH1D* h_MHT_Exp=0;
  TH1D* h_MHTPhi_Exp=0;
  TH1D* h_MET_Exp=0;
  TH1D* h_METPhi_Exp=0;
  TH1D* h_mT_Exp=0;
  TH1D* h_NJet_Exp=0;
  TH1D* h_NBtag_Exp=0;
  TH1D* h_DphiOne_Exp=0;
  TH1D* h_DphiTwo_Exp=0;
  TH1D* h_DphiThree_Exp=0;
  TH1D* h_DphiFour_Exp=0;
  TH1D* h_LepPt_Exp=0;
  TH1D* h_LepEta_Exp=0;
  TH1D* h_LepPhi_Exp=0;
  TH1D* h_rawJetPtforHT_Exp=0;
  TH1D* h_rawJetPtforMHTminusHT_Exp=0; 
  TH2D* h_rawJetPtvsEtaforHT_Exp=0;
  TH2D* h_rawJetPtvsEtaforMHTminusHT_Exp=0; 
  TH1D* h_JetPtforHTLead_Exp=0;
  TH1D* h_JetEtaforHTLead_Exp=0;
  TH1D* h_JetPtforHTNotLead_Exp=0;
  TH1D* h_JetEtaforHTNotLead_Exp=0;
  TH1D* h_JetPtforHT_Exp=0;
  TH1D* h_JetEtaforHT_Exp=0;
  TH2D* h_JetPtvsHTRatioforHT_Exp=0;
  TH2D* h_JetPtvsEtaforHT_Exp=0;
  TH1D* h_JetPtforMHTminusHTLead_Exp=0;
  TH1D* h_JetEtaforMHTminusHTLead_Exp=0;
  TH1D* h_JetPtforMHTminusHTNotLead_Exp=0;
  TH1D* h_JetEtaforMHTminusHTNotLead_Exp=0;
  TH1D* h_JetPtforMHTminusHT_Exp=0;
  TH1D* h_JetEtaforMHTminusHT_Exp=0;

  TH2D* h_JetPtvsEtaforMHTminusHT_Exp=0;
  TH2D* h_JetPtvsHTRatioforMHTminusHT_Exp=0;

  TH1D* h_HTclean_Exp=0;
  TH1D* h_HT5clean_Exp=0;
  TH1D* h_MHTclean_Exp=0;
  TH1D* h_MHTPhiclean_Exp=0;
  TH1D* h_METclean_Exp=0;
  TH1D* h_METPhiclean_Exp=0;
  TH1D* h_mTclean_Exp=0;
  TH1D* h_NJetclean_Exp=0;
  TH1D* h_NBtagclean_Exp=0;
  TH1D* h_DphiOneclean_Exp=0;
  TH1D* h_DphiTwoclean_Exp=0;
  TH1D* h_DphiThreeclean_Exp=0;
  TH1D* h_DphiFourclean_Exp=0;
  TH1D* h_LepPtclean_Exp=0;
  TH1D* h_LepEtaclean_Exp=0;
  TH1D* h_LepPhiclean_Exp=0;

  TH1D* h_HTv2Recipe_Exp=0;
  TH1D* h_HT5v2Recipe_Exp=0;
  TH1D* h_HTRatiov2Recipe_Exp=0;
  TH1D* h_MHTv2Recipe_Exp=0;
  TH1D* h_MHTPhiv2Recipe_Exp=0;
  TH1D* h_NJetv2Recipe_Exp=0;
  TH1D* h_NJetforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_NBtagv2Recipe_Exp=0;




  TH1D* h_rawJetPtforHTv2Recipe_Exp=0;
  TH1D* h_rawJetPtforMHTminusHTv2Recipe_Exp=0; 
  TH2D* h_rawJetPtvsEtaforHTv2Recipe_Exp=0;
  TH2D* h_rawJetPtvsEtaforMHTminusHTv2Recipe_Exp=0; 

  TH1D* h_JetPtforHTv2RecipeLead_Exp=0;
  TH1D* h_JetEtaforHTv2RecipeLead_Exp=0;
  TH1D* h_JetPhiforHTv2RecipeLead_Exp=0;
  TH1D* h_JetPtforHTv2RecipeNotLead_Exp=0;
  TH1D* h_JetEtaforHTv2RecipeNotLead_Exp=0;
  TH1D* h_JetPhiforHTv2RecipeNotLead_Exp=0;
  TH1D* h_JetPtforHTv2Recipe_Exp=0;
  TH1D* h_JetEtaforHTv2Recipe_Exp=0;
  TH1D* h_JetPhiforHTv2Recipe_Exp=0;
  TH1D* h_DphiOneforHTv2Recipe_Exp=0;
  TH1D* h_DphiTwoforHTv2Recipe_Exp=0;
  TH1D* h_DphiThreeforHTv2Recipe_Exp=0;
  TH1D* h_DphiFourforHTv2Recipe_Exp=0;
  TH1D* h_chargedEmEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_chargedHadronEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_chargedHadronMultiplicityforHTv2Recipe_Exp=0;  
  TH1D* h_chargedMultiplicityforHTv2Recipe_Exp=0;
  TH1D* h_electronEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_electronMultiplicityforHTv2Recipe_Exp=0;
  TH1D* h_hadronFlavorforHTv2Recipe_Exp=0; 
  TH1D* h_hfEMEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_hfHadronEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_multiplicityforHTv2Recipe_Exp=0; 
  TH1D* h_muonEnergyFractionforHTv2Recipe_Exp=0; 
  TH1D* h_muonMultiplicityforHTv2Recipe_Exp=0; 
  TH1D* h_neutralEmEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_neutralHadronEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_neutralHadronMultiplicityforHTv2Recipe_Exp=0; 
  TH1D* h_neutralMultiplicityforHTv2Recipe_Exp=0;
  TH1D* h_photonEnergyFractionforHTv2Recipe_Exp=0;
  TH1D* h_photonMultiplicityforHTv2Recipe_Exp=0;
  TH1D* h_qgLikelihoodforHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsEtaforHTv2Recipe_Exp=0;
  TH2D* h_JetIdxvsEtaforHTv2Recipe_Exp=0;
  TH2D* h_JetMultvsEtaforHTv2Recipe_Exp=0;

  TH2D* h_JetPtvsHTRatioforHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsPhiforHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsDPhiforHTv2Recipe_Exp=0;
  TH2D* h_JetPtvschargedEmEnergyFractionforHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsneutralEmEnergyFractionforHTv2Recipe_Exp=0;
  TH2D* h_JetPtvschargedHadronEnergyFractionforHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsneutralHadronEnergyFractionforHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsPhiforHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsDPhiforHTv2Recipe_Exp=0;
  TH2D* h_JetEtavschargedEmEnergyFractionforHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsneutralEmEnergyFractionforHTv2Recipe_Exp=0;
  TH2D* h_JetEtavschargedHadronEnergyFractionforHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsneutralHadronEnergyFractionforHTv2Recipe_Exp=0;

  TH1D* h_JetPtforMHTminusHTv2RecipeLead_Exp=0;
  TH1D* h_JetEtaforMHTminusHTv2RecipeLead_Exp=0;
  TH1D* h_JetPhiforMHTminusHTv2RecipeLead_Exp=0;
  TH1D* h_JetPtforMHTminusHTv2RecipeNotLead_Exp=0;
  TH1D* h_JetEtaforMHTminusHTv2RecipeNotLead_Exp=0;
  TH1D* h_JetPhiforMHTminusHTv2RecipeNotLead_Exp=0;
  TH1D* h_JetPtforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_JetEtaforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_JetPhiforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_DphiOneforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_DphiTwoforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_DphiThreeforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_DphiFourforMHTminusHTv2Recipe_Exp=0;
      
  TH1D* h_chargedEmEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_chargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_chargedHadronMultiplicityforMHTminusHTv2Recipe_Exp=0;  
  TH1D* h_chargedMultiplicityforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_electronEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_electronMultiplicityforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_hadronFlavorforMHTminusHTv2Recipe_Exp=0; 
  TH1D* h_hfEMEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_hfHadronEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_multiplicityforMHTminusHTv2Recipe_Exp=0; 
  TH1D* h_muonEnergyFractionforMHTminusHTv2Recipe_Exp=0; 
  TH1D* h_muonMultiplicityforMHTminusHTv2Recipe_Exp=0; 
  TH1D* h_neutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_neutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_neutralHadronMultiplicityforMHTminusHTv2Recipe_Exp=0; 
  TH1D* h_neutralMultiplicityforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_photonEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_photonMultiplicityforMHTminusHTv2Recipe_Exp=0;
  TH1D* h_qgLikelihoodforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsEtaforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetIdxvsEtaforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetMultvsEtaforMHTminusHTv2Recipe_Exp=0;

  TH2D* h_JetPtvsHTRatioforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsPhiforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsDPhiforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetPtvschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetPtvschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetPtvsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsPhiforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsDPhiforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetEtavschargedEmEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsneutralEmEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetEtavschargedHadronEnergyFractionforMHTminusHTv2Recipe_Exp=0;
  TH2D* h_JetEtavsneutralHadronEnergyFractionforMHTminusHTv2Recipe_Exp=0;


  TH1D* h_MHTOrig_Exp=0;
  TH1D* h_MHTPhiOrig_Exp=0;
  TH1D* h_METOrig_Exp=0;
  TH1D* h_METPhiOrig_Exp=0;
  TH1D* h_DphiOneOrig_Exp=0;
  TH1D* h_DphiTwoOrig_Exp=0;
  TH1D* h_DphiThreeOrig_Exp=0;
  TH1D* h_DphiFourOrig_Exp=0;


  TH1D* h_HT_Pre=0;
  TH1D* h_MHT_Pre=0;
  TH1D* h_NJet_Pre=0;
  TH1D* h_NBtag_Pre=0;


  // TFs
  TH1D* h_0L1L_SB = 0;
  TH1D* h_0L1L_SF_SB = 0;

  //open skim file as skimfile
  TH1* h_njetsisr = 0;
  double nEvtsTotal;
  Double_t xsec;
  ISRCorrector *isrcorr = 0;
  TFile* isrfile = 0;
  TH1* h_isr = 0;
  Double_t w_isr;
  Double_t w_pu;
  BTagCorrector *btagcorr = 0;
  std::vector<double> bTagProb;
  std::vector<unsigned int> bTagBins;
  std::vector<unsigned int> bTagBinsQCD;
  Double_t		  topPtSF;
  std::vector<double> topPt;

  TString treeName = " ";
  string SkimFilePath=" ";
  string OldSkimFilePath=" ";

  SearchBins *SearchBins_ =0;
  SearchBins *SearchBinsQCD_ =0;
  SearchBins *SearchBins_BTags_ =0;
  SearchBins *SearchBinsQCD_BTags_ =0;

  Int_t           isoTracksNum;
  UShort_t JetsNum_;
  UShort_t MuonsNoIsoNum_, MuonsNum_;
  UShort_t ElectronsNoIsoNum_, ElectronsNum_;
  Float_t MuonsPt_, MuonsEta_;
  Float_t ElectronsPt_, ElectronsEta_;
  Float_t mtw;
  
  UShort_t Bin_, BinQCD_;

  Int_t NMuons=-1;
  Int_t NElectrons=-1;
  // Declaration of leaf types
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  ULong64_t       EvtNum;
  Bool_t           BadChargedCandidateFilter;
  Bool_t           BadPFMuonFilter;
  Int_t           BTags;
  Int_t           BTagsclean;
  Int_t           BTagsv2Recipe;
  Int_t          CSCTightHaloFilter;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        DeltaPhi4;
  Double_t        DeltaPhi1clean;
  Double_t        DeltaPhi2clean;
  Double_t        DeltaPhi3clean;
  Double_t        DeltaPhi4clean;
  Double_t        DeltaPhi1v2Recipe;
  Double_t        DeltaPhi2v2Recipe;
  Double_t        DeltaPhi3v2Recipe;
  Double_t        DeltaPhi4v2Recipe;

  Double_t        HTDeltaPhi1v2Recipe;
  Double_t        HTDeltaPhi2v2Recipe;
  Double_t        HTDeltaPhi3v2Recipe;
  Double_t        HTDeltaPhi4v2Recipe;

  Double_t        MHTminusHTDeltaPhi1v2Recipe;
  Double_t        MHTminusHTDeltaPhi2v2Recipe;
  Double_t        MHTminusHTDeltaPhi3v2Recipe;
  Double_t        MHTminusHTDeltaPhi4v2Recipe;

  Double_t        MHTminusHTPt1v2Recipe;
  Double_t        MHTminusHTPt2v2Recipe;
  Double_t        MHTminusHTPt3v2Recipe;
  Double_t        MHTminusHTPt4v2Recipe;

  Double_t        MHTminusHTEta1v2Recipe;
  Double_t        MHTminusHTEta2v2Recipe;
  Double_t        MHTminusHTEta3v2Recipe;
  Double_t        MHTminusHTEta4v2Recipe;

  Double_t        MHTminusHTPhi1v2Recipe;
  Double_t        MHTminusHTPhi2v2Recipe;
  Double_t        MHTminusHTPhi3v2Recipe;
  Double_t        MHTminusHTPhi4v2Recipe;

  Double_t        DeltaPhi1Orig;
  Double_t        DeltaPhi2Orig;
  Double_t        DeltaPhi3Orig;
  Double_t        DeltaPhi4Orig;


  Int_t           globalTightHalo2016Filter;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  //Bool_t           eeBadSc4Filter;
  std::vector<TLorentzVector> *GenElectrons=0;
  std::vector<TLorentzVector> *GenMuons=0;
  Int_t          HBHENoiseFilter;
  Int_t          HBHEIsoNoiseFilter;
  Double_t        HT;
  Double_t        HTclean;
  Double_t        HTv2Recipe; 
  Double_t        HT5v2Recipe;
  Double_t        HTRatiov2Recipe; 
  Double_t        HT5;
  Double_t        HTRatio;
  Double_t        HT5clean;

  Double_t        GenHT;
  Double_t        GenMHT;
  std::vector<TLorentzVector> *GenJets=0;
  Int_t           isoElectronTracksNum;
  Int_t           isoMuonTracksNum;
  Int_t           isoPionTracksNum;
  Bool_t          JetID;
  std::vector<bool> *Muons_passIso=0;
  std::vector<bool> *Electrons_passIso=0;

  std::vector<TLorentzVector> *Jets=0;
  std::vector<double>     *Jets_chargedEmEnergyFraction=0;
  std::vector<int>     *Jets_chargedHadronMultiplicity=0;
  std::vector<int>     *Jets_chargedMultiplicity=0;
  std::vector<double>     *Jets_electronEnergyFraction=0;
  std::vector<int>     *Jets_electronMultiplicity=0;
  std::vector<double>     *Jets_hfEMEnergyFraction=0;
  std::vector<double>     *Jets_hfHadronEnergyFraction=0;
  std::vector<int>     *Jets_multiplicity=0;
  std::vector<int>     *Jets_muonMultiplicity=0;
  std::vector<double>     *Jets_neutralEmEnergyFraction=0;
  std::vector<double>     *Jets_neutralHadronEnergyFraction=0;
  std::vector<int>     *Jets_neutralHadronMultiplicity=0;
  std::vector<int>     *Jets_neutralMultiplicity=0;
  std::vector<double>     *Jets_photonEnergyFraction=0;
  std::vector<int>     *Jets_photonMultiplicity=0;
  std::vector<double>     *Jets_muonEnergyFraction=0;
  std::vector<double>     *Jets_bDiscriminatorCSV=0;
  std::vector<double>     *Jets_jecFactor=0;
  
  std::vector<int>     *Jets_hadronFlavor=0;
  std::vector<double>     *Jets_chargedHadronEnergyFraction=0;
  std::vector<bool>    *Jets_HTMask=0;
  Double_t        METPhi;
  Double_t        MET;
  Double_t        METPhiclean;
  Double_t        METclean;
  Double_t        METPhiOrig;
  Double_t        METOrig;

  Double_t        PFCaloMETRatio;
  Double_t        MHT;
  Double_t        MHTPhi;
  Double_t        MHTclean;
  Double_t        MHTPhiclean;
  Double_t        MHTv2Recipe;
  Double_t        MHTPhiv2Recipe;

  Double_t        MHTOrig;
  Double_t        MHTPhiOrig;

  Int_t           NJets;
  Int_t           NJetsclean;
  Int_t           NJetsv2Recipe;
  Int_t           NJetsforMHTminusHTv2Recipe;
  Int_t           NVtx;
  std::vector<TLorentzVector> *ElectronsNoIso=0;
  std::vector<TLorentzVector> *Electrons=0;
  std::vector<TLorentzVector> *Muons=0;
  std::vector<TLorentzVector> *MuonsNoIso=0;
  std::vector<string>  *TriggerNames=0;
  std::vector<int>    *TriggerPass=0;
  std::vector<int>     *TriggerPrescales=0;
  Double_t        Weight;
  Double_t        puWeight;
  Double_t        madHT;
  Double_t        SusyLSPMass;
  Double_t        SusyMotherMass;
  Double_t        TrueNumInteractions;
  std::vector<double>  *ElectronsNoIso_MT2Activity=0;
  std::vector<double>  *Electrons_MT2Activity=0;
  std::vector<double>  *MuonsNoIso_MT2Activity=0;
  std::vector<double>  *Muons_MT2Activity=0;
  Int_t           NJetsISR;
  vector<TLorentzVector> *GenParticles = 0;
  vector<int>     *GenParticles_PdgId = 0;
  std::vector<double>  *Muons_MTW=0;
  std::vector<double>  *Electrons_MTW=0;
  vector<bool>    *Muons_tightID=0;
  vector<bool>    *Electrons_mediumID=0;
  vector<bool>    *Electrons_tightID=0;



  // List of branches
  TBranch        *b_RunNum=0;   //!
  TBranch        *b_LumiBlockNum=0;   //!
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_BTagsclean=0; 
  TBranch        *b_BadChargedCandidateFilter=0;   //!
  TBranch        *b_BadPFMuonFilter=0;   //!
  TBranch        *b_CSCTightHaloFilter=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
  TBranch        *b_DeltaPhi4=0;   //!

  TBranch        *b_DeltaPhi1clean=0;   //!
  TBranch        *b_DeltaPhi2clean=0;   //!
  TBranch        *b_DeltaPhi3clean=0;   //!
  TBranch        *b_DeltaPhi4clean=0;   //!

  TBranch        *b_DeltaPhi1Orig=0;   //!
  TBranch        *b_DeltaPhi2Orig=0;   //!
  TBranch        *b_DeltaPhi3Orig=0;   //!
  TBranch        *b_DeltaPhi4Orig=0;   //!

  TBranch        *b_globalTightHalo2016Filter=0;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter=0;   //!
  TBranch        *b_eeBadScFilter=0;   //!
  //TBranch        *b_eeBadSc4Filter=0;   //!
  TBranch        *b_GenElectrons=0;   //!
  TBranch        *b_GenMuons=0;   //!
  TBranch        *b_HBHENoiseFilter=0;   //!
  TBranch        *b_HBHEIsoNoiseFilter=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_HTclean=0;   //!
  TBranch        *b_HT5=0;   //!
  TBranch        *b_HT5clean=0;   //!

  TBranch        *b_GenHT=0;   //!
  TBranch        *b_GenMHT=0;   //!
  TBranch        *b_GenJets=0;   //!
  TBranch        *b_isoElectronTracksNum=0;   //!
  TBranch        *b_isoMuonTracksNum=0;   //!
  TBranch        *b_isoPionTracksNum=0;   //!
  TBranch        *b_Muons_passIso=0;
  TBranch        *b_Electrons_passIso=0;

  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_muonEnergyFraction=0;   //!
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
  TBranch        *b_Jets_jecFactor=0;   //!
  TBranch        *b_Jets_chargedEmEnergyFraction=0;
  TBranch        *b_Jets_chargedHadronMultiplicity=0;
  TBranch        *b_Jets_chargedMultiplicity=0;
  TBranch        *b_Jets_electronEnergyFraction=0;
  TBranch        *b_Jets_electronMultiplicity=0;
  TBranch        *b_Jets_hfEMEnergyFraction=0;
  TBranch        *b_Jets_hfHadronEnergyFraction=0;
  TBranch        *b_Jets_multiplicity=0;
  TBranch        *b_Jets_muonMultiplicity=0;
  TBranch        *b_Jets_neutralEmEnergyFraction=0;
  TBranch        *b_Jets_neutralHadronEnergyFraction=0;
  TBranch        *b_Jets_neutralHadronMultiplicity=0;
  TBranch        *b_Jets_neutralMultiplicity=0;
  TBranch        *b_Jets_photonEnergyFraction=0;
  TBranch        *b_Jets_photonMultiplicity=0;
  TBranch        *b_Jets_qgLikelihood=0;

  TBranch        *b_Jets_hadronFlavor=0;   //!
  TBranch        *b_Jets_chargedHadronEnergyFraction=0;   //!
  TBranch        *b_Jets_HTMask=0;   //!
  TBranch        *b_METPhi=0;   //!
  TBranch        *b_MET=0;   //!
  TBranch        *b_METPhiclean=0;   //!
  TBranch        *b_METclean=0;   //!
  TBranch        *b_METPhiOrig=0;   //!
  TBranch        *b_METOrig=0;   //!

  TBranch        *b_PFCaloMETRatio=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_MHTPhi=0;   //!
  TBranch        *b_MHTclean=0;   //!
  TBranch        *b_MHTPhiclean=0;   //!
  TBranch        *b_MHTOrig=0;   //!
  TBranch        *b_MHTPhiOrig=0;   //!

  TBranch        *b_NJets=0;   //!
  TBranch        *b_NJetsclean=0;   //!

  TBranch        *b_NVtx=0;   //!
  TBranch        *b_ElectronsNoIso=0;   //!
  TBranch        *b_Electrons=0;   //!
  TBranch        *b_Muons=0;   //!
  TBranch        *b_MuonsNoIso=0;   //!
  TBranch        *b_TriggerNames=0;   //!
  TBranch        *b_TriggerPass=0;   //!
  TBranch        *b_TriggerPrescales=0;   //!
  TBranch        *b_Weight=0;   //!
  TBranch        *b_puWeight=0;   //!
  TBranch        *b_madHT=0;
  TBranch        *b_NMuons=0;
  TBranch        *b_NElectrons=0;
  TBranch        *b_SusyLSPMass=0;
  TBranch        *b_SusyMotherMass=0;
  TBranch        *b_TrueNumInteractions=0;
  TBranch        *b_ElectronsNoIso_MT2Activity=0;   //!
  TBranch        *b_Electrons_MT2Activity=0;   //!
  TBranch        *b_Muons_MT2Activity=0;   //!
  TBranch        *b_MuonsNoIso_MT2Activity=0;   //!
  TBranch        *b_NJetsISR=0;
  TBranch        *b_GenParticles=0;
  TBranch        *b_GenParticles_PdgId=0;
  TBranch        *b_Muons_MTW=0;
  TBranch        *b_Electrons_MTW=0;
  TBranch        *b_Muons_tightID=0;   //!
  TBranch        *b_Electrons_mediumID=0;   //!
  TBranch        *b_Electrons_tightID=0;   //!


  
 Prediction(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~Prediction() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  
  ClassDef(Prediction,0);
};

#endif

#ifdef Prediction_cxx
void Prediction::Init(TTree *tree)
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
  fChain->SetMakeClass(1);


  ////////////////////////
  //////// Options
  ///////////////////////

  if(!((runOnData && !runOnStandardModelMC && !runOnSignalMC) || (!runOnData && runOnStandardModelMC && !runOnSignalMC) || (!runOnData && !runOnStandardModelMC && runOnSignalMC))){
    fprintf(stderr, "CHECK OPTIONS! EITHER RUN ON DATA, MC, OR SIGNAL!!!");
    return;
  }

  // Seta data specific options, e.g. Trigger
  // Apply trigger
  if(runOnData) useTrigger = true;
  // Apply weights if trigger not simulated
  //if(runOnStandardModelMC) useTriggerEffWeight = true; // not derived yet
  if(runOnSignalMC && !useGenHTMHT) useTriggerEffWeight = true;

  // Do PU reweighting. true for signal scan
  if(runOnSignalMC) doPUreweighting = true;
  //if(runOnStandardModelMC) doPUreweighting = true;
  // bTag corrections. Use for signal scan
  if(!runOnData) doBTagCorr = true;
  // ISR corrections.
  if(runOnSignalMC) doISRcorr = true; //<-check---------------------------------------

  // useFilterData = true; unless you want to run without MET filters
  // useFilterData = false; For FastSim Samples, e.g. Signal Scans! Met filters not simulated
  if(runOnStandardModelMC || runOnData) useFilterData = true;



  ////////////////////////
  //////// End Options
  ///////////////////////

  // Open histograms with TFs
  TFile *TF_histFile = TFile::Open("TF.root", "READ");
  h_0L1L_SB = (TH1D*) TF_histFile->Get("h_0L1L_SB")->Clone();
  h_0L1L_SF_SB = (TH1D*) TF_histFile->Get("h_0L1L_SF_SB")->Clone();

  TChain* temp = (TChain*)fChain;
  std::string infname=temp->GetFile()->GetName();

  TFile* skimfile = temp->GetFile();

  std::string baseName(infname);
  size_t pos=baseName.rfind("/");
  if(pos!=std::string::npos){
    if(pos!=baseName.size()-1){
      baseName.erase(0,pos+1);
    }
  }
  pos=baseName.rfind(".root");
  if(pos!=std::string::npos){
    if(pos!=baseName.size()-1){
      baseName.erase(pos);
    }
  }
 
  fname = baseName+"_Exp.root";

  TString option = GetOption();
  TObjArray *optionArray = option.Tokenize(",");
  fileName = fname.c_str();

  TString fileNameString = "";
  TString HTcutString = "";

  if(!optionArray->IsEmpty()){
    fileNameString = ((TObjString *)(optionArray->At(0)))->String();
    if(optionArray->GetEntries() > 1) HTcutString = ((TObjString *)(optionArray->At(1)))->String();
  }

  fileNameString = fileNameString.Strip(TString::kBoth, ' ').String();
  HTcutString = HTcutString.Strip(TString::kBoth, ' ').String();

  if(fileNameString!="*" && fileNameString!="") fileName = fileNameString;
  if(HTcutString!="" && HTcutString.IsFloat()) HTgen_cut = HTcutString.Atof();

  std::cout << "madHT cut: " << HTgen_cut << std::endl;

  std::cout << "Saving file to: " << fileName << std::endl;

  std::ifstream signal_xsecT1T5(path_xsecT1T5);
  std::string str_xsecT1T5;
  while (std::getline(signal_xsecT1T5, str_xsecT1T5))
  {
    //TObjArray * TString::Tokenize ( const TString &  delim)
    // This function is used to isolate sequential tokens in a TString.
    //These tokens are separated in the string by at least one of the characters in delim. 
    TObjArray *tokens = TString(str_xsecT1T5).Tokenize(",");
    //std::cout<<((TObjString *)(tokens->At(0)))->String()<<"; "<<((TObjString *)(tokens->At(1)))->String()<<";"<<std::endl;
    //makes vector of pair like: (220,2259.15):(mass,xsec)
    xsecsT1T5.push_back(std::make_pair(std::atof(((TObjString *)(tokens->At(0)))->String()), std::atof(((TObjString *)(tokens->At(1)))->String())));
  }
  //AR-180618- Ex. :ifstream  userstream(“file1.txt”); The userstream is the name of the object and file1.txt is the name of the file. When the object is created file is automatically open. There is no need of explicitly opening the file.
  std::ifstream signal_xsecT2(path_xsecT2);
  std::string str_xsecT2;
  //AR-180618- New line is saved under str_xsecT2
  while (std::getline(signal_xsecT2, str_xsecT2))
    {
      
    TObjArray *tokens = TString(str_xsecT2).Tokenize(",");
    //std::cout<<((TObjString *)(tokens->At(0)))->String()<<"; "<<((TObjString *)(tokens->At(1)))->String()<<";"<<std::endl;
    
    xsecsT2.push_back(std::make_pair(std::atof(((TObjString *)(tokens->At(0)))->String()), std::atof(((TObjString *)(tokens->At(1)))->String())));
  }
  
  if(runOnSignalMC){
    // ISR setup
    isrfile = TFile::Open(path_ISRcorr, "READ");
    h_isr = (TH1*)isrfile->Get("isr_weights_central");
  }

  if(doPUreweighting){
    pufile = TFile::Open(path_puHist,"READ");
    puhist = (TH1*)pufile->Get("pu_weights_down");
  }

  fChain->SetBranchStatus("*",0);

  fChain->SetBranchStatus("RunNum", 1);
  fChain->SetBranchStatus("LumiBlockNum", 1);
  fChain->SetBranchStatus("EvtNum", 1);
  fChain->SetBranchStatus("BTags", 1);
  fChain->SetBranchStatus("BTagsclean", 1);

  fChain->SetBranchStatus("DeltaPhi1", 1);
  fChain->SetBranchStatus("DeltaPhi2", 1);
  fChain->SetBranchStatus("DeltaPhi3", 1);
  fChain->SetBranchStatus("DeltaPhi4", 1);
  fChain->SetBranchStatus("DeltaPhi1clean", 1);
  fChain->SetBranchStatus("DeltaPhi2clean", 1);
  fChain->SetBranchStatus("DeltaPhi3clean", 1);
  fChain->SetBranchStatus("DeltaPhi4clean", 1);
  fChain->SetBranchStatus("DeltaPhi1Orig", 1);
  fChain->SetBranchStatus("DeltaPhi2Orig", 1);
  fChain->SetBranchStatus("DeltaPhi3Orig", 1);
  fChain->SetBranchStatus("DeltaPhi4Orig", 1);

  if(!runOnSignalMC){
    //fChain->SetBranchStatus("CSCTightHaloFilter", 1);
    fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
    fChain->SetBranchStatus("eeBadScFilter", 1);
    //fChain->SetBranchStatus("eeBadSc4Filter", 1);    
    fChain->SetBranchStatus("HBHENoiseFilter", 1);
    fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
    if(runOnData){
      fChain->SetBranchStatus("globalTightHalo2016Filter", 1);
      fChain->SetBranchStatus("BadChargedCandidateFilter", 1);
      fChain->SetBranchStatus("BadPFMuonFilter", 1);
    }
  }
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("HTclean", 1);
  fChain->SetBranchStatus("HT5", 1);
  fChain->SetBranchStatus("HT5clean", 1);

  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("Jets_HTMask", 1);
  fChain->SetBranchStatus("PFCaloMETRatio", 1);

  fChain->SetBranchStatus("METPhiclean", 1);
  fChain->SetBranchStatus("METclean", 1);
  fChain->SetBranchStatus("MHTclean", 1);
  fChain->SetBranchStatus("MHTPhiclean", 1);
  fChain->SetBranchStatus("NJetsclean", 1);

  fChain->SetBranchStatus("METPhiOrig", 1);
  fChain->SetBranchStatus("METOrig", 1);
  fChain->SetBranchStatus("MHTOrig", 1);
  fChain->SetBranchStatus("MHTPhiOrig", 1);

  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("NVtx", 1);
  fChain->SetBranchStatus("ElectronsNoIso", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("MuonsNoIso", 1);
  fChain->SetBranchStatus("TriggerNames", 1);
  fChain->SetBranchStatus("TriggerPass", 1);
  fChain->SetBranchStatus("TriggerPrescales", 1);
  fChain->SetBranchStatus("Jets_muonEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorCSV", 1);
  fChain->SetBranchStatus("Jets_jecFactor", 1);
  fChain->SetBranchStatus("Jets_chargedEmEnergyFraction", 1); 
  fChain->SetBranchStatus("Jets_chargedHadronMultiplicity", 1);
  fChain->SetBranchStatus("Jets_chargedMultiplicity", 1);
  fChain->SetBranchStatus("Jets_electronEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_electronMultiplicity", 1);
  fChain->SetBranchStatus("Jets_hfEMEnergyFraction", 1); 
  fChain->SetBranchStatus("Jets_hfHadronEnergyFraction", 1); 
  fChain->SetBranchStatus("Jets_multiplicity", 1);
  fChain->SetBranchStatus("Jets_muonMultiplicity", 1); 
  fChain->SetBranchStatus("Jets_neutralEmEnergyFraction", 1); 
  fChain->SetBranchStatus("Jets_neutralHadronEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_neutralHadronMultiplicity", 1);
  fChain->SetBranchStatus("Jets_neutralMultiplicity", 1);
  fChain->SetBranchStatus("Jets_photonEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_photonMultiplicity",1);
  fChain->SetBranchStatus("Muons_passIso",1);
  fChain->SetBranchStatus("Electrons_passIso",1);
  if(topPTreweight){
    fChain->SetBranchStatus("GenParticles", 1);
    fChain->SetBranchStatus("GenParticles_PdgId", 1);
    fChain->SetBranchStatus("GenElectrons", 1);
    fChain->SetBranchStatus("GenMuons", 1);
  }  
  

  if(!runOnData){
    fChain->SetBranchStatus("Weight", 1);
    fChain->SetBranchStatus("Jets_hadronFlavor", 1);
    fChain->SetBranchStatus("madHT", 1);
    fChain->SetBranchStatus("TrueNumInteractions", 1);
  } 
  if(runOnSignalMC){
    fChain->SetBranchStatus("SusyLSPMass", 1);
    fChain->SetBranchStatus("SusyMotherMass", 1);
    fChain->SetBranchStatus("NJetsISR", 1);
    fChain->SetBranchStatus("GenJets", 1);
    fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction", 1);
  }
  fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction", 1);
  //if(useGenHTMHT){
  //  fChain->SetBranchStatus("GenHT", 1);
  //  fChain->SetBranchStatus("GenMHT", 1);
  //}

  fChain->SetBranchStatus("ElectronsNoIso_MT2Activity",1);
  fChain->SetBranchStatus("Electrons_MT2Activity", 1);
  fChain->SetBranchStatus("Muons_MT2Activity",1);
  fChain->SetBranchStatus("MuonsNoIso_MT2Activity", 1);
  fChain->SetBranchStatus("Muons_MTW", 1);
  fChain->SetBranchStatus("Electrons_MTW", 1);
  fChain->SetBranchStatus("Muons_tightID", 1);
  fChain->SetBranchStatus("Electrons_mediumID", 1);
  fChain->SetBranchStatus("Electrons_tightID", 1);
  fChain->SetBranchStatus("NMuons",1);
  fChain->SetBranchStatus("NElectrons",1); 
  fChain->SetBranchAddress("NMuons", &NMuons, &b_NMuons);
  fChain->SetBranchAddress("NElectrons", &NElectrons, &b_NElectrons);
  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
  fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("HTclean", &HTclean, &b_HTclean);
  fChain->SetBranchAddress("HT5", &HT5, &b_HT5);
  fChain->SetBranchAddress("HT5clean", &HT5clean, &b_HT5clean);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("MET", &MET, &b_MET);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("BTagsclean", &BTagsclean, &b_BTagsclean);
  fChain->SetBranchAddress("DeltaPhi1clean", &DeltaPhi1clean, &b_DeltaPhi1clean);
  fChain->SetBranchAddress("DeltaPhi2clean", &DeltaPhi2clean, &b_DeltaPhi2clean);
  fChain->SetBranchAddress("DeltaPhi3clean", &DeltaPhi3clean, &b_DeltaPhi3clean);
  fChain->SetBranchAddress("DeltaPhi4clean", &DeltaPhi4clean, &b_DeltaPhi4clean);
  fChain->SetBranchAddress("METPhiclean", &METPhiclean, &b_METPhiclean);
  fChain->SetBranchAddress("METclean", &METclean, &b_METclean);
  fChain->SetBranchAddress("MHTclean", &MHTclean, &b_MHTclean);
  fChain->SetBranchAddress("MHTPhiclean", &MHTPhiclean, &b_MHTPhiclean);
  fChain->SetBranchAddress("NJetsclean", &NJetsclean, &b_NJetsclean);

  fChain->SetBranchAddress("DeltaPhi1Orig", &DeltaPhi1Orig, &b_DeltaPhi1Orig);
  fChain->SetBranchAddress("DeltaPhi2Orig", &DeltaPhi2Orig, &b_DeltaPhi2Orig);
  fChain->SetBranchAddress("DeltaPhi3Orig", &DeltaPhi3Orig, &b_DeltaPhi3Orig);
  fChain->SetBranchAddress("DeltaPhi4Orig", &DeltaPhi4Orig, &b_DeltaPhi4Orig);
  fChain->SetBranchAddress("METPhiOrig", &METPhiOrig, &b_METPhiOrig);
  fChain->SetBranchAddress("METOrig", &METOrig, &b_METOrig);
  fChain->SetBranchAddress("MHTOrig", &MHTOrig, &b_MHTOrig);
  fChain->SetBranchAddress("MHTPhiOrig", &MHTPhiOrig, &b_MHTPhiOrig);

  fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);

  if(!runOnSignalMC){
    //fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
    fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
    fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
    //fChain->SetBranchAddress("eeBadSc4Filter", &eeBadSc4Filter, &b_eeBadSc4Filter);    
    fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
    fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
    if(runOnData){
      fChain->SetBranchAddress("globalTightHalo2016Filter", &globalTightHalo2016Filter, &b_globalTightHalo2016Filter);
      fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
      fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
    }
  }
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracksNum, &b_isoElectronTracksNum);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracksNum, &b_isoMuonTracksNum);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracksNum, &b_isoPionTracksNum);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);

  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("ElectronsNoIso", &ElectronsNoIso, &b_ElectronsNoIso);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("MuonsNoIso", &MuonsNoIso, &b_MuonsNoIso);
  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  fChain->SetBranchAddress("Muons_passIso", &Muons_passIso, &b_Muons_passIso);
  fChain->SetBranchAddress("Electrons_passIso", &Electrons_passIso, &b_Electrons_passIso);

  fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
  fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
  fChain->SetBranchAddress("Jets_jecFactor", &Jets_jecFactor, &b_Jets_jecFactor);
  fChain->SetBranchAddress("Jets_chargedEmEnergyFraction", &Jets_chargedEmEnergyFraction, &b_Jets_chargedEmEnergyFraction);
  fChain->SetBranchAddress("Jets_chargedHadronMultiplicity", &Jets_chargedHadronMultiplicity, &b_Jets_chargedHadronMultiplicity);
  fChain->SetBranchAddress("Jets_chargedMultiplicity", &Jets_chargedMultiplicity, &b_Jets_chargedMultiplicity);
  fChain->SetBranchAddress("Jets_electronEnergyFraction", &Jets_electronEnergyFraction, &b_Jets_electronEnergyFraction);
  fChain->SetBranchAddress("Jets_electronMultiplicity", &Jets_electronMultiplicity, &b_Jets_electronMultiplicity);
  fChain->SetBranchAddress("Jets_hfEMEnergyFraction", &Jets_hfEMEnergyFraction, &b_Jets_hfEMEnergyFraction);
  fChain->SetBranchAddress("Jets_hfHadronEnergyFraction", &Jets_hfHadronEnergyFraction, &b_Jets_hfHadronEnergyFraction);
  fChain->SetBranchAddress("Jets_multiplicity", &Jets_multiplicity, &b_Jets_multiplicity);
  fChain->SetBranchAddress("Jets_muonMultiplicity", &Jets_muonMultiplicity, &b_Jets_muonMultiplicity);
  fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);
  fChain->SetBranchAddress("Jets_neutralHadronEnergyFraction", &Jets_neutralHadronEnergyFraction, &b_Jets_neutralHadronEnergyFraction);
  fChain->SetBranchAddress("Jets_neutralHadronMultiplicity", &Jets_neutralHadronMultiplicity, &b_Jets_neutralHadronMultiplicity);
  fChain->SetBranchAddress("Jets_neutralMultiplicity", &Jets_neutralMultiplicity, &b_Jets_neutralMultiplicity);
  fChain->SetBranchAddress("Jets_photonEnergyFraction", &Jets_photonEnergyFraction, &b_Jets_photonEnergyFraction);
  fChain->SetBranchAddress("Jets_photonMultiplicity", &Jets_photonMultiplicity, &b_Jets_photonMultiplicity);

  if(topPTreweight){
    fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
    fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
    fChain->SetBranchAddress("GenElectrons", &GenElectrons, &b_GenElectrons);
    fChain->SetBranchAddress("GenMuons", &GenMuons, &b_GenMuons);
  }  
  if(!runOnData){
    fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
    fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
    fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
    fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
  }
  if(runOnSignalMC){
    fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
    fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
    fChain->SetBranchAddress("NJetsISR", &NJetsISR, &b_NJetsISR);
    fChain->SetBranchAddress("GenJets", &GenJets, &b_GenJets);
    fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
  }
  fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);

  //if(useGenHTMHT){
  //  fChain->SetBranchAddress("GenHT", &GenHT, &b_GenHT);
  //  fChain->SetBranchAddress("GenMHT", &GenMHT, &b_GenMHT);
  //}

  fChain->SetBranchAddress("ElectronsNoIso_MT2Activity", &ElectronsNoIso_MT2Activity, &b_ElectronsNoIso_MT2Activity);
  fChain->SetBranchAddress("Electrons_MT2Activity", &Electrons_MT2Activity, &b_Electrons_MT2Activity);
  fChain->SetBranchAddress("Muons_MT2Activity", &Muons_MT2Activity, &b_Muons_MT2Activity);
  fChain->SetBranchAddress("MuonsNoIso_MT2Activity", &MuonsNoIso_MT2Activity, &b_MuonsNoIso_MT2Activity);
  fChain->SetBranchAddress("Muons_MTW", &Muons_MTW, &b_Muons_MTW);
  fChain->SetBranchAddress("Electrons_MTW", &Electrons_MTW, &b_Electrons_MTW);
  fChain->SetBranchAddress("Muons_tightID", &Muons_tightID, &b_Muons_tightID);
  fChain->SetBranchAddress("Electrons_mediumID", &Electrons_mediumID, &b_Electrons_mediumID);
  fChain->SetBranchAddress("Electrons_tightID", &Electrons_tightID, &b_Electrons_tightID);
}


Bool_t Prediction::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

#endif // #ifdef Prediction_cxx
