#ifndef TFMaker_h
#define TFMaker_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH2.h>
#include <TH1.h>
#include <TProfile.h>
#include "TVector2.h"
#include <cmath>
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TKey.h"
#include "TLorentzVector.h"
#include <fstream>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>
#include "SearchBins.h"
#include "LLTools.h"
#include "isr/ISRCorrector.h"
#include "btag/BTagCorrector.h"


////////////////////////
//////// Options
//////// SET DEPENDING ON SAMPLE: data, MC, signal!
///////////////////////

// useDeltaPhiCut = 0: no deltaPhiCut
// useDeltaPhiCut = 1: deltaPhiCut
// useDeltaPhiCut = -1: inverted deltaPhiCut
const int useDeltaPhiCut = 1;  //<-check------------------------

bool RunFor2017=true;
bool RunFor2018=false;
bool RunFor2016=false;

const bool doBTagCorr = true;
const bool doPUreweighting = false; //true for fastsim signal in prediction code
const bool doISRcorr = false;  //true for fastsim signal in prediction code
const bool doTopPtReweighting = false; 
const bool applyFilters = true;
const bool useFilterData = true; // false for FastSim since not simulated
const bool LeptonSys=false;
const bool IsoMuSys=false;//false by default
const bool IsoEleSys=false;
const bool IDMuSys=false;//false by default
const bool IDEleSys=false;
const bool TrackRecoMuSys=false;
const bool TrackRecoEleSys=false;
const bool JECSys=false; //false by default
const bool ScaleAccSys=false;
const bool PDFAccSys=false;
const bool BtagSys=false;
const bool MTSys=false; //*AR, 180329: for MTSys SF files are same as JEC Ref as SFMaker does not include MTW.
const bool SysUp=false;
const bool SysDn=true; //*AR, 180327: no need to change this for any run
// Use TFs with/without SFs
double scaleFactorWeight = 59546.381;
bool GetNonPrefireProb=true; //<---true for 2016 and 2017 MC
bool AddHEMVeto=false; //<---true to get 2018 TF for HEM affected region
const bool ApplyHT5cut=true;

// Path to Skims for btag reweighting
const string path_toSkims("root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_SLm/");

// PU
const TString path_puHist("PU/PileupHistograms_0721_63mb_pm5.root");
// bTag corrections
string path_bTagCalib = "btag/DeepCSV_102XSF_V1_1018_190404.csv";   //*AR:190429:don't change here, yearwise change of file is made later
const string path_bTagCalibFastSim("btag/fastsim_csvv2_ttbar_26_1_2017.csv");
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ISR corrections
const TString path_ISRcorr("isr/ISRWeights.root");

// Isotrack uncertainty
const TString path_isoTrackunc("SFs_ICHEP/NJets_uncertainty.root");


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
double csvForBtag=0.4184; //*AR:190429:don't change here, yearwise change of file is made later

int Scalesize=9;
int PDFsize=102;
//vector<double> *Vec_SF;


class TFMaker : public TSelector {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  
  void PushHist(TH1* h, TH1* f);
  void SaveEff(TH1* h, TFile* oFile, bool xlog=false, bool ylog=false);
  bool FiltersPass();
  void resetValues();

  std::vector<TVector3>Order_the_Vec(std::vector<TVector3> vec);
  std::vector<double>Order_the_Vec(std::vector<TVector3> vec,std::vector<double> vecTwo);
  std::vector<int>Order_the_Vec(std::vector<TVector3> vec,std::vector<int> vecTwo);
  std::vector<bool>Order_the_Vec(std::vector<TVector3> vec,std::vector<bool> vecTwo);
  std::vector<TLorentzVector>Order_the_Vec(std::vector<TVector3> vec,std::vector<TLorentzVector> vecTwo);

vector<TH1*> Vec_scale_el_SFCR_SB,Vec_scale_el_SFSR_SB,Vec_scale_mu_SFCR_SB,Vec_scale_mu_SFSR_SB,Vec_scale_CR_SB_copy,Vec_scale_CR_SF_SB_copy,Vec_scale_SR_SB_copy,Vec_scale_SR_SF_SB_copy,Vec_scale_0L1L_SB,Vec_scale_0L1L_SF_SB;

vector<TH1*> Vec_PDF_el_SFCR_SB,Vec_PDF_el_SFSR_SB,Vec_PDF_mu_SFCR_SB,Vec_PDF_mu_SFSR_SB,Vec_PDF_CR_SB_copy,Vec_PDF_CR_SF_SB_copy,Vec_PDF_SR_SB_copy,Vec_PDF_SR_SF_SB_copy,Vec_PDF_0L1L_SB,Vec_PDF_0L1L_SF_SB;

  // Histograms
  TFile *SFCR_histFile = 0;
  TFile *SFSR_histFile = 0;

  TH2D* h_el_SFCR_etaPt = 0;
  TH1D* h_el_SFCR_SB = 0;
  TH1D* h_el_SFCR_SB_Track = 0;
  TH1D* h_el_SFCR_SB_ID = 0;
  TH1D* h_el_SFCR_SB_Iso = 0;
  TH2D* h_el_SFSR_etaPt = 0;
  TH1D* h_el_SFSR_SB = 0;
  TH1D* h_el_SFSR_SB_Track = 0;
  TH1D* h_el_SFSR_SB_ID = 0;
  TH1D* h_el_SFSR_SB_Iso = 0;

  TH2D* h_mu_SFCR_etaPt = 0;
  TH1D* h_mu_SFCR_SB = 0;
  TH1D* h_mu_SFCR_SB_Track = 0;
  TH1D* h_mu_SFCR_SB_ID = 0;
  TH1D* h_mu_SFCR_SB_Iso = 0;

  TH2D* h_mu_SFSR_etaPt = 0;
  TH1D* h_mu_SFSR_SB = 0;
  TH1D* h_mu_SFSR_SB_Track = 0;
  TH1D* h_mu_SFSR_SB_ID = 0;
  TH1D* h_mu_SFSR_SB_Iso = 0;

  TH1D* h_di_SFCR_SB = 0;
  TH1D* h_di_SFSR_SB = 0;

  TH1D* h_CR_SB = 0;
  TH1D* h_SR_SB = 0;
  TH1D* h_SR_LL_SB = 0;
  TH1D* h_SR_Hadtau_SB = 0;

  TH1D* h_0L1L_SB = 0;
  TH1D* h_0L1L_LL_SB = 0;
  TH1D* h_0L1L_Hadtau_SB = 0;


  TH1D* h_CR_SF_SB = 0;
  TH1D* h_CR_SF_SB_el_Track = 0;
  TH1D* h_CR_SF_SB_el_ID = 0;
  TH1D* h_CR_SF_SB_el_Iso = 0;
  TH1D* h_CR_SF_SB_mu_Track = 0;
  TH1D* h_CR_SF_SB_mu_ID = 0;
  TH1D* h_CR_SF_SB_mu_Iso = 0;

  TH1D* h_SR_SF_SB = 0;
  TH1D* h_SR_SF_SB_el_Track = 0;
  TH1D* h_SR_SF_SB_el_ID = 0;
  TH1D* h_SR_SF_SB_el_Iso = 0;
  TH1D* h_SR_SF_SB_mu_Track = 0;
  TH1D* h_SR_SF_SB_mu_ID = 0;
  TH1D* h_SR_SF_SB_mu_Iso = 0;

  TH1D* h_SR_SF_LL_SB = 0;
  TH1D* h_SR_SF_Hadtau_SB = 0;

  TH1D* h_0L1L_SF_SB = 0;
  TH1D* h_0L1L_SF_SB_el_Track = 0;
  TH1D* h_0L1L_SF_SB_el_ID = 0;
  TH1D* h_0L1L_SF_SB_el_Iso = 0;
  TH1D* h_0L1L_SF_SB_mu_Track = 0;
  TH1D* h_0L1L_SF_SB_mu_ID = 0;
  TH1D* h_0L1L_SF_SB_mu_Iso = 0;

  TH1D* h_0L1L_SF_LL_SB = 0;
  TH1D* h_0L1L_SF_Hadtau_SB = 0;

  TH1D* h_CR_SB_copy = 0;
  TH1D* h_SR_SB_copy = 0;
  TH1D* h_SR_LL_SB_copy = 0;
  TH1D* h_SR_Hadtau_SB_copy = 0;

  TH1D* h_CR_SF_SB_copy = 0;
  TH1D* h_CR_SF_SB_el_Track_copy = 0;
  TH1D* h_CR_SF_SB_el_ID_copy = 0;
  TH1D* h_CR_SF_SB_el_Iso_copy = 0;
  TH1D* h_CR_SF_SB_mu_Track_copy = 0;
  TH1D* h_CR_SF_SB_mu_ID_copy = 0;
  TH1D* h_CR_SF_SB_mu_Iso_copy = 0;

  TH1D* h_SR_SF_SB_copy = 0;
  TH1D* h_SR_SF_SB_el_Track_copy = 0;
  TH1D* h_SR_SF_SB_el_ID_copy = 0;
  TH1D* h_SR_SF_SB_el_Iso_copy = 0;
  TH1D* h_SR_SF_SB_mu_Track_copy = 0;
  TH1D* h_SR_SF_SB_mu_ID_copy = 0;
  TH1D* h_SR_SF_SB_mu_Iso_copy = 0;

  TH1D* h_SR_SF_LL_SB_copy = 0;
  TH1D* h_SR_SF_Hadtau_SB_copy = 0;

  //Stuff
  std::string fname; // for fetching file name
  TString fileName;
  TString currFileName;
  string currentFile;
  TFile* pufile = 0;
  TH1* puhist = 0;

  //open skim file as skimfile
  bool useCombinedBinsCR = false;
  bool useCombinedBinsSR = false;
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
  std::vector<unsigned int> BinforMTEff;
  Double_t		  topPtSF;
  std::vector<double> topPt;
  string SkimFilePath=" ";
  string OldSkimFilePath=" ";


   TFile *JetPrefireMap = TFile::Open("btag/L1prefiring_jetpt_2017BtoF.root", "READ");
   TH2F * jMap = (TH2F*) JetPrefireMap->Get("L1prefiring_jetpt_2017BtoF");
   TFile *PhotonPrefireMap = TFile::Open("btag/L1prefiring_photonpt_2017BtoF.root", "READ");
   TH2F * pMap = (TH2F*)PhotonPrefireMap->Get("L1prefiring_photonpt_2017BtoF");


  TH1D* h_muIsoTrack_NJetsunc = 0;
  TH1D* h_elecIsoTrack_NJetsunc = 0;
  TH1D* h_pionIsoTrack_NJetsunc = 0;
  TH1D* h_CR_AfterMT=0;
  TH1D* h_CR_BeforeMT=0;
  TH1D*  h_MTEff=0;
  TString treeName = " ";


  SearchBins *SearchBins_ =0;
  SearchBins *SearchBins_BTags_ =0;

  Int_t           isoTracksNum;
  UShort_t JetsNum_;
  Float_t mtw;
  UShort_t Bin_;
  UShort_t BinCombined_;
  Int_t NMuons=-1;
  Int_t NElectrons=-1;
  UShort_t MuonsNoIsoNum_, MuonsNum_;
  UShort_t ElectronsNoIsoNum_, ElectronsNum_;
  UShort_t GenElectronsNum_, GenMuonsNum_;
  UShort_t GenTausNum_;
  UShort_t GenTausHadNum_;
  UShort_t ElectronsPromptNum_, MuonsPromptNum_;
  UShort_t MuonsPromptMatch_, ElectronsPromptMatch_;
  UShort_t MuonsPromptMatch2_, ElectronsPromptMatch2_;
  Float_t MuonsPromptPt_, MuonsPromptEta_;
  Float_t ElectronsPromptPt_, ElectronsPromptEta_;
  Float_t MuonsPromptPt2_, MuonsPromptEta2_;
  Float_t ElectronsPromptPt2_, ElectronsPromptEta2_;

  UShort_t ElectronTracksPromptNum_, MuonTracksPromptNum_;
  UShort_t MuonTracksPromptMatch_, ElectronTracksPromptMatch_;
  UShort_t MuonTracksPromptMatch2_, ElectronTracksPromptMatch2_;
  Float_t MuonTracksPromptPt_, MuonTracksPromptEta_;
  Float_t ElectronTracksPromptPt_, ElectronTracksPromptEta_;
  Float_t MuonTracksPromptPt2_, MuonTracksPromptEta2_;
  Float_t ElectronTracksPromptPt2_, ElectronTracksPromptEta2_;

  std::vector<TLorentzVector> GenElectronsAcc;
  std::vector<TLorentzVector> GenMuonsAcc;
  UShort_t GenMuonsAccNum_, GenElectronsAccNum_;
  Float_t GenMuonsAccPt_, GenMuonsAccEta_;
  Float_t GenElectronsAccPt_, GenElectronsAccEta_;
  Float_t GenMuonsAccPt2_, GenMuonsAccEta2_;
  Float_t GenElectronsAccPt2_, GenElectronsAccEta2_;

  vector<TLorentzVector> isoElectronTracks;
  vector<TLorentzVector> isoMuonTracks;
  vector<TLorentzVector> isoPionTracks;


  
  // Declaration of leaf types
  UInt_t          RunNum;
  UInt_t          LumiBlockNum;
  ULong64_t       EvtNum;
  Bool_t           BadChargedCandidateFilter;
  Bool_t           BadPFMuonFilter;
  Bool_t           ecalBadCalibFilter;
  Bool_t           ecalBadCalibReducedFilter;
  Bool_t           ecalBadCalibReducedExtraFilter;

  Int_t           BTags;
  Int_t           BTagsDeepCSV;

  Int_t          CSCTightHaloFilter;
  Double_t        DeltaPhi1;
  Double_t        DeltaPhi2;
  Double_t        DeltaPhi3;
  Double_t        DeltaPhi4;
  Int_t           globalSuperTightHalo2016Filter;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  std::vector<TLorentzVector> *GenElectrons=0;
  std::vector<TLorentzVector> *GenMuons=0;
  std::vector<TLorentzVector> *GenTaus=0;
  std::vector<bool> *GenTaus_had=0;

  Int_t          HBHENoiseFilter;
  Int_t          HBHEIsoNoiseFilter;
  Double_t        HT;
  Double_t        GenHT;
  Double_t        GenMHT;
  std::vector<TLorentzVector> *GenJets=0;
  Int_t           isoElectronTracksNum;
  Int_t           isoMuonTracksNum;
  Int_t           isoPionTracksNum;
  Bool_t          JetID;

  std::vector<double> *Muons_MiniIso=0;
  std::vector<bool> *Muons_mediumID=0;
  std::vector<bool> *Muons_passIso=0;
  std::vector<bool> *Electrons_passIso=0;


  std::vector<TLorentzVector> *Jets=0;
  std::vector<double>     *Jets_muonEnergyFraction=0;
  std::vector<double>     *Jets_neutralEmEnergyFraction=0;

  std::vector<double>     *Jets_bDiscriminatorCSV=0;
  std::vector<double>     *Jets_bJetTagDeepCSVprobb=0;
  std::vector<double>     *Jets_bJetTagDeepCSVprobbb=0;

  std::vector<int>     *Jets_hadronFlavor=0;
  std::vector<int>     *Jets_chargedHadronEnergyFraction=0;
  std::vector<bool>    *Jets_HTMask=0;
  std::vector<double>  *Jets_jecUnc=0;

  Double_t        METPhi;
  Double_t        MET;
  Double_t        NonPrefiringProb;
  Double_t        NonPrefiringProbUp;
  Double_t        NonPrefiringProbDown;

  std::vector<double> *METUp=0;
  std::vector<double> *METDown=0;
  std::vector<double> *METPhiUp=0;
  std::vector<double> *METPhiDown=0;
  Double_t        PFCaloMETRatio;
  Double_t        MHT;
  Double_t        MHTPhi;
  Double_t        HT5;

  Int_t           NJets;
  Int_t           NVtx;
  std::vector<TLorentzVector> *ElectronsNoIso=0;
  std::vector<TLorentzVector> *Electrons=0;
  std::vector<TLorentzVector> *Muons=0;
  std::vector<TLorentzVector> *MuonsNoIso=0;
  std::vector<string>  *TriggerNames=0;
  std::vector<int>    *TriggerPass=0;
  std::vector<int>     *TriggerPrescales=0;
  std::vector<double> *ScaleWeights=0;
  std::vector<double> *PDFWeights=0;

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
  vector<TLorentzVector> *TAPElectronTracks = 0;
  vector<double>  *TAPElectronTracks_activity = 0;
  vector<int>     *TAPElectronTracks_charge = 0;
  vector<double>  *TAPElectronTracks_mT = 0;
  vector<double>  *TAPElectronTracks_trkiso = 0;
  vector<TLorentzVector> *TAPMuonTracks = 0;
  vector<double>  *TAPMuonTracks_activity = 0;
  vector<int>     *TAPMuonTracks_charge = 0;
  vector<double>  *TAPMuonTracks_mT = 0;
  vector<double>  *TAPMuonTracks_trkiso = 0;
  vector<TLorentzVector> *TAPPionTracks = 0;
  vector<double>  *TAPPionTracks_activity = 0;
  vector<int>     *TAPPionTracks_charge = 0;
  vector<double>  *TAPPionTracks_mT = 0;
  vector<double>  *TAPPionTracks_trkiso = 0;



  // List of branches
  TBranch        *b_RunNum=0;   //!
  TBranch        *b_LumiBlockNum=0;   //!
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_BTagsDeepCSV=0;   //!
  TBranch        *b_BadChargedCandidateFilter=0;   //!
  TBranch        *b_BadPFMuonFilter=0;   //!
  TBranch        *b_ecalBadCalibFilter=0;
  TBranch        *b_ecalBadCalibReducedFilter=0;
  TBranch        *b_ecalBadCalibReducedExtraFilter=0;

  TBranch        *b_CSCTightHaloFilter=0;   //!
  TBranch        *b_DeltaPhi1=0;   //!
  TBranch        *b_DeltaPhi2=0;   //!
  TBranch        *b_DeltaPhi3=0;   //!
  TBranch        *b_DeltaPhi4=0;   //!
  TBranch        *b_globalSuperTightHalo2016Filter=0;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter=0;   //!
  TBranch        *b_eeBadScFilter=0;   //!
  TBranch        *b_GenElectrons=0;   //!
  TBranch        *b_GenMuons=0;   //!
  TBranch        *b_GenTaus=0;   //!
  TBranch        *b_GenTaus_had=0;   //!

  TBranch        *b_HBHENoiseFilter=0;   //!
  TBranch        *b_HBHEIsoNoiseFilter=0;   //!
  TBranch        *b_HT=0;   //!
  TBranch        *b_GenHT=0;   //!
  TBranch        *b_GenMHT=0;   //!
  TBranch        *b_GenJets=0;   //!
  TBranch        *b_isoElectronTracksNum=0;   //!
  TBranch        *b_isoMuonTracksNum=0;   //!
  TBranch        *b_isoPionTracksNum=0;   //!
  TBranch        *b_Muons_passIso=0;
  TBranch        *b_Muons_mediumID=0;
  TBranch        *b_Muons_MiniIso=0;
  TBranch        *b_Electrons_passIso=0;


  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  TBranch        *b_Jets_jecUnc=0;
  TBranch        *b_Jets_muonEnergyFraction=0;   //!
  TBranch        *b_Jets_neutralEmEnergyFraction=0;
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
  TBranch        *b_Jets_bJetTagDeepCSVprobb=0;   //!
  TBranch        *b_Jets_bJetTagDeepCSVprobbb=0;   //!

  TBranch        *b_Jets_hadronFlavor=0;   //!
  TBranch        *b_Jets_chargedHadronEnergyFraction=0;   //!
  TBranch        *b_Jets_HTMask=0;   //!
  TBranch        *b_METPhi=0;   //!
  TBranch        *b_MET=0;   //!
  TBranch *b_METUp=0; //!
  TBranch *b_METDown=0; //!
  TBranch *b_METPhiUp=0; //!
  TBranch *b_METPhiDown=0; //!
  TBranch        *b_NonPrefiringProb=0;   //!
  TBranch        *b_NonPrefiringProbUp=0;   //!
  TBranch        *b_NonPrefiringProbDown=0;   //!

  TBranch        *b_PFCaloMETRatio=0;   //!
  TBranch        *b_MHT=0;   //!
  TBranch        *b_MHTPhi=0;   //!
  TBranch        *b_HT5=0;   //!
  TBranch        *b_NJets=0;   //!
  TBranch        *b_NVtx=0;   //!
  TBranch        *b_ElectronsNoIso=0;   //!
  TBranch        *b_Electrons=0;   //!
  TBranch        *b_Muons=0;   //!
  TBranch        *b_MuonsNoIso=0;   //!
  TBranch        *b_TriggerNames=0;   //!
  TBranch        *b_TriggerPass=0;   //!
  TBranch        *b_TriggerPrescales=0;   //!
  TBranch        *b_ScaleWeights=0;
  TBranch        *b_PDFWeights=0;
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
  TBranch        *b_TAPElectronTracks=0;   //!
  TBranch        *b_TAPElectronTracks_activity=0;   //!
  TBranch        *b_TAPElectronTracks_charge=0;   //!
  TBranch        *b_TAPElectronTracks_mT=0;   //!
  TBranch        *b_TAPElectronTracks_trkiso=0;   //!
  TBranch        *b_TAPMuonTracks=0;   //!
  TBranch        *b_TAPMuonTracks_activity=0;   //!
  TBranch        *b_TAPMuonTracks_charge=0;   //!
  TBranch        *b_TAPMuonTracks_mT=0;   //!
  TBranch        *b_TAPMuonTracks_trkiso=0;   //!
  TBranch        *b_TAPPionTracks=0;   //!
  TBranch        *b_TAPPionTracks_activity=0;   //!
  TBranch        *b_TAPPionTracks_charge=0;   //!
  TBranch        *b_TAPPionTracks_mT=0;   //!
  TBranch        *b_TAPPionTracks_trkiso=0;   //!


  
 TFMaker(TTree * /*tree*/ =0) : fChain(0) { }
  virtual ~TFMaker() { }
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
  
  ClassDef(TFMaker,0);
};

#endif

#ifdef TFMaker_cxx
void TFMaker::Init(TTree *tree)
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

  if(RunFor2018)
    csvForBtag=0.4184;
  if(RunFor2017)
    csvForBtag=0.4941;

  
  if(RunFor2018)
    scaleFactorWeight = 59546.381; //not used for data
  if(RunFor2017)
    scaleFactorWeight = 41486.136;

  if(RunFor2018)
    path_bTagCalib = "btag/DeepCSV_102XSF_V1_1018_190404.csv";
  if(RunFor2017)
    path_bTagCalib = "btag/DeepCSV_2017_94XSF_V4_B_F_190404.csv";

  ////////////////////////
  //////// End Options
  ///////////////////////


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
  //if(HTcutString!="" && HTcutString.IsFloat()) HTgen_cut = HTcutString.Atof();

  // std::cout << "madHT cut: " << HTgen_cut << std::endl;

  std::cout << "Saving file to: " << fileName << std::endl;

  if(doISRcorr){
    // ISR setup
    isrfile = TFile::Open(path_ISRcorr, "READ");
    h_isr = (TH1*)isrfile->Get("isr_weights_central");
  }

  if(doPUreweighting){
    pufile = TFile::Open(path_puHist,"READ");
    puhist = (TH1*)pufile->Get("pu_weights_central");
  }

  fChain->SetBranchStatus("*",0);

  fChain->SetBranchStatus("RunNum", 1);
  fChain->SetBranchStatus("LumiBlockNum", 1);
  fChain->SetBranchStatus("EvtNum", 1);
  fChain->SetBranchStatus("BTags", 1);
  fChain->SetBranchStatus("BTagsDeepCSV", 1);
  fChain->SetBranchStatus("DeltaPhi1", 1);
  fChain->SetBranchStatus("DeltaPhi2", 1);
  fChain->SetBranchStatus("DeltaPhi3", 1);
  fChain->SetBranchStatus("DeltaPhi4", 1);
  //if(!runOnSignalMC){
  fChain->SetBranchStatus("CSCTightHaloFilter", 1);
    fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
    fChain->SetBranchStatus("eeBadScFilter", 1);
    fChain->SetBranchStatus("HBHENoiseFilter", 1);
    fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
    fChain->SetBranchStatus("ecalBadCalibFilter", 1);
    fChain->SetBranchStatus("ecalBadCalibReducedFilter", 1);
    fChain->SetBranchStatus("ecalBadCalibReducedExtraFilter", 1);

    //if(runOnData){
      fChain->SetBranchStatus("globalSuperTightHalo2016Filter", 1);
      fChain->SetBranchStatus("BadChargedCandidateFilter", 1);
      fChain->SetBranchStatus("BadPFMuonFilter", 1);
    //}
  //}
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("Jets_HTMask", 1);
  fChain->SetBranchStatus("METPhi", 1);
  fChain->SetBranchStatus("MET", 1);
  fChain->SetBranchStatus("METUp", 1);
  fChain->SetBranchStatus("METDown", 1);
  fChain->SetBranchStatus("METPhiUp", 1);
  fChain->SetBranchStatus("METPhiDown", 1);
  fChain->SetBranchStatus("NonPrefiringProb", 1);
  fChain->SetBranchStatus("NonPrefiringProbUp", 1);
  fChain->SetBranchStatus("NonPrefiringProbDown", 1);

  fChain->SetBranchStatus("PFCaloMETRatio", 1);
  fChain->SetBranchStatus("MHT", 1);
  fChain->SetBranchStatus("MHTPhi", 1);
  fChain->SetBranchStatus("HT5", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("NJets", 1);
  fChain->SetBranchStatus("NVtx", 1);
  fChain->SetBranchStatus("ElectronsNoIso", 1);
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("Muons", 1);
  fChain->SetBranchStatus("MuonsNoIso", 1);
  fChain->SetBranchStatus("GenElectrons", 1);
  fChain->SetBranchStatus("GenMuons", 1);
  fChain->SetBranchStatus("GenTaus", 1);
  fChain->SetBranchStatus("GenTaus_had", 1);

  fChain->SetBranchStatus("TriggerNames", 1);
  fChain->SetBranchStatus("TriggerPass", 1);
  fChain->SetBranchStatus("TriggerPrescales", 1);
  fChain->SetBranchStatus("Jets_jecUnc" , 1);
  fChain->SetBranchStatus("Jets_muonEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_neutralEmEnergyFraction", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorCSV", 1);
  fChain->SetBranchStatus("Jets_bJetTagDeepCSVprobb", 1);
  fChain->SetBranchStatus("Jets_bJetTagDeepCSVprobbb", 1);

  fChain->SetBranchStatus("Muons_passIso",1);
  fChain->SetBranchStatus("Muons_mediumID",1);
  fChain->SetBranchStatus("Muons_MiniIso",1);

  fChain->SetBranchStatus("Electrons_passIso",1);


  if(doTopPtReweighting){
    fChain->SetBranchStatus("GenParticles", 1);
    fChain->SetBranchStatus("GenParticles_PdgId", 1);
  }  
  

  //if(!runOnData){

    fChain->SetBranchStatus("Weight", 1);
    fChain->SetBranchStatus("Jets_hadronFlavor", 1);
    fChain->SetBranchStatus("madHT", 1);
    fChain->SetBranchStatus("TrueNumInteractions", 1);
    fChain->SetBranchStatus("ScaleWeights",1);
    fChain->SetBranchStatus("PDFweights",1);

  //} 
  //if(runOnSignalMC){
  //  fChain->SetBranchStatus("SusyLSPMass", 1);
  //  fChain->SetBranchStatus("SusyMotherMass", 1);
  //  fChain->SetBranchStatus("NJetsISR", 1);
  //  fChain->SetBranchStatus("GenJets", 1);
  //  fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction", 1);
  //}

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

  fChain->SetBranchStatus("TAPElectronTracks", 1);
  fChain->SetBranchStatus("TAPElectronTracks_activity", 1);
  fChain->SetBranchStatus("TAPElectronTracks_charge", 1);
  fChain->SetBranchStatus("TAPElectronTracks_mT", 1);
  fChain->SetBranchStatus("TAPElectronTracks_trkiso", 1);
  fChain->SetBranchStatus("TAPMuonTracks", 1);
  fChain->SetBranchStatus("TAPMuonTracks_activity", 1);
  fChain->SetBranchStatus("TAPMuonTracks_charge", 1);
  fChain->SetBranchStatus("TAPMuonTracks_mT", 1);
  fChain->SetBranchStatus("TAPMuonTracks_trkiso", 1);
  fChain->SetBranchStatus("TAPPionTracks", 1);
  fChain->SetBranchStatus("TAPPionTracks_activity", 1);
  fChain->SetBranchStatus("TAPPionTracks_charge", 1);
  fChain->SetBranchStatus("TAPPionTracks_mT", 1);
  fChain->SetBranchStatus("TAPPionTracks_trkiso", 1);

  fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
  fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);

  fChain->SetBranchAddress("BTagsDeepCSV", &BTagsDeepCSV, &b_BTagsDeepCSV);

  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
  //if(!runOnSignalMC){
    fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);

    fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
    fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
    fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
    fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
    fChain->SetBranchAddress("ecalBadCalibFilter", &ecalBadCalibFilter, &b_ecalBadCalibFilter);
    fChain->SetBranchAddress("ecalBadCalibReducedFilter", &ecalBadCalibReducedFilter, &b_ecalBadCalibReducedFilter);
    fChain->SetBranchAddress("ecalBadCalibReducedExtraFilter", &ecalBadCalibReducedExtraFilter, &b_ecalBadCalibReducedExtraFilter);
    fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);


    //if(runOnData){
    fChain->SetBranchAddress("globalSuperTightHalo2016Filter", &globalSuperTightHalo2016Filter, &b_globalSuperTightHalo2016Filter);
    fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
    fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
    //}
  //}
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracksNum, &b_isoElectronTracksNum);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracksNum, &b_isoMuonTracksNum);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracksNum, &b_isoPionTracksNum);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("MET", &MET, &b_MET);
  fChain->SetBranchAddress("METUp", &METUp, &b_METUp);
  fChain->SetBranchAddress("METDown", &METDown, &b_METDown);
  fChain->SetBranchAddress("METPhiUp", &METPhiUp, &b_METPhiUp);
  fChain->SetBranchAddress("METPhiDown", &METPhiDown, &b_METPhiDown);
  fChain->SetBranchAddress("NonPrefiringProb",&NonPrefiringProb, &b_NonPrefiringProb);
  fChain->SetBranchAddress("NonPrefiringProbUp",&NonPrefiringProbUp, &b_NonPrefiringProbUp);
  fChain->SetBranchAddress("NonPrefiringProbDown",&NonPrefiringProbDown, &b_NonPrefiringProbDown);

  fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
  fChain->SetBranchAddress("HT5", &HT5, &b_HT5);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);
  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("ElectronsNoIso", &ElectronsNoIso, &b_ElectronsNoIso);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("MuonsNoIso", &MuonsNoIso, &b_MuonsNoIso);
  fChain->SetBranchAddress("GenElectrons", &GenElectrons, &b_GenElectrons);
  fChain->SetBranchAddress("GenMuons", &GenMuons, &b_GenMuons);
  fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
  fChain->SetBranchAddress("GenTaus_had", &GenTaus_had, &b_GenTaus_had);

  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  fChain->SetBranchAddress("Muons_mediumID", &Muons_mediumID, &b_Muons_mediumID);
  fChain->SetBranchAddress("Muons_MiniIso", &Muons_MiniIso, &b_Muons_MiniIso);

  fChain->SetBranchAddress("Muons_passIso", &Muons_passIso, &b_Muons_passIso);
  fChain->SetBranchAddress("Electrons_passIso", &Electrons_passIso, &b_Electrons_passIso);


  fChain->SetBranchAddress("Jets_jecUnc", &Jets_jecUnc, &b_Jets_jecUnc);
  fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
  fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);
  fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobb", &Jets_bJetTagDeepCSVprobb, &b_Jets_bJetTagDeepCSVprobb);
  fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobbb", &Jets_bJetTagDeepCSVprobbb, &b_Jets_bJetTagDeepCSVprobbb);

  if(doTopPtReweighting){
    fChain->SetBranchAddress("GenParticles", &GenParticles, &b_GenParticles);
    fChain->SetBranchAddress("GenParticles_PdgId", &GenParticles_PdgId, &b_GenParticles_PdgId);
  }  
  //if(!runOnData){
    fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
    fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
    fChain->SetBranchAddress("PDFweights", &PDFWeights, &b_PDFWeights);
    fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
    fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
    fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
  //}
  //if(runOnSignalMC){
  //  fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
  //  fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
  //  fChain->SetBranchAddress("NJetsISR", &NJetsISR, &b_NJetsISR);
  //  fChain->SetBranchAddress("GenJets", &GenJets, &b_GenJets);
  //  fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
  //}

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
  fChain->SetBranchAddress("TAPElectronTracks", &TAPElectronTracks, &b_TAPElectronTracks);
  fChain->SetBranchAddress("TAPElectronTracks_activity", &TAPElectronTracks_activity, &b_TAPElectronTracks_activity);
  fChain->SetBranchAddress("TAPElectronTracks_charge", &TAPElectronTracks_charge, &b_TAPElectronTracks_charge);
  fChain->SetBranchAddress("TAPElectronTracks_mT", &TAPElectronTracks_mT, &b_TAPElectronTracks_mT);
  fChain->SetBranchAddress("TAPElectronTracks_trkiso", &TAPElectronTracks_trkiso, &b_TAPElectronTracks_trkiso);
  fChain->SetBranchAddress("TAPMuonTracks", &TAPMuonTracks, &b_TAPMuonTracks);
  fChain->SetBranchAddress("TAPMuonTracks_activity", &TAPMuonTracks_activity, &b_TAPMuonTracks_activity);
  fChain->SetBranchAddress("TAPMuonTracks_charge", &TAPMuonTracks_charge, &b_TAPMuonTracks_charge);
  fChain->SetBranchAddress("TAPMuonTracks_mT", &TAPMuonTracks_mT, &b_TAPMuonTracks_mT);
  fChain->SetBranchAddress("TAPMuonTracks_trkiso", &TAPMuonTracks_trkiso, &b_TAPMuonTracks_trkiso);
  fChain->SetBranchAddress("TAPPionTracks", &TAPPionTracks, &b_TAPPionTracks);
  fChain->SetBranchAddress("TAPPionTracks_activity", &TAPPionTracks_activity, &b_TAPPionTracks_activity);
  fChain->SetBranchAddress("TAPPionTracks_charge", &TAPPionTracks_charge, &b_TAPPionTracks_charge);
  fChain->SetBranchAddress("TAPPionTracks_mT", &TAPPionTracks_mT, &b_TAPPionTracks_mT);
  fChain->SetBranchAddress("TAPPionTracks_trkiso", &TAPPionTracks_trkiso, &b_TAPPionTracks_trkiso);
}


Bool_t TFMaker::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

#endif // #ifdef TFMaker_cxx
