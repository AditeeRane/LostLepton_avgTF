//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Nov  4 01:48:45 2016 by ROOT version 6.06/01
// from TTree PreSelection/PreSelection
// found on file: root://cmseos.fnal.gov//store/user/vhegde/myProduction_V11/Spring16.WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_96_RA2AnalysisTree.root
//////////////////////////////////////////////////////////
#ifndef NtupleVariables_h
#define NtupleVariables_h

#include <TROOT.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

using namespace std;
class NtupleVariables : public TSelector {
 public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
  Int_t NMuons=-1;
  Int_t NElectrons=-1;

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

  Double_t        DeltaPhi1Orig;
  Double_t        DeltaPhi2Orig;
  Double_t        DeltaPhi3Orig;
  Double_t        DeltaPhi4Orig;


  Int_t           globalSuperTightHalo2016Filter;
  Int_t           EcalDeadCellTriggerPrimitiveFilter;
  Int_t           eeBadScFilter;
  //Bool_t           eeBadSc4Filter;
  std::vector<TLorentzVector> *GenElectrons=0;
  std::vector<bool>    *GenElectrons_fromTau=0;
  std::vector<TLorentzVector> *GenMuons=0;
  std::vector<bool>    *GenMuons_fromTau=0;
  std::vector<TLorentzVector> *GenTaus=0;
  std::vector<bool> *GenTaus_had=0;
  Int_t          HBHENoiseFilter;
  Int_t          HBHEIsoNoiseFilter;
  Double_t        HT;
  Double_t        HTclean;
  Double_t        HTv2Recipe; 
  Double_t        HT5v2Recipe;
  Double_t        HTRatiov2Recipe; 
  Double_t        RecHTRatiov2Recipe;
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
  std::vector<bool> *Muons_mediumID=0;
  std::vector<bool> *Muons_passIso=0;
  std::vector<bool> *Electrons_passIso=0;

  std::vector<TLorentzVector> *Jets=0;
  //  vector<bool>    *Jets_ID;

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
  std::vector<double>     *Jets_bJetTagDeepCSVprobb=0;
  std::vector<double>     *Jets_bJetTagDeepCSVprobbb=0;


  std::vector<double>     *Jets_jecFactor=0;
  
  std::vector<int>     *Jets_hadronFlavor=0;
  std::vector<double>     *Jets_chargedHadronEnergyFraction=0;

  std::vector<bool>    *Jets_HTMask=0;






  Double_t        METPhi;
  Double_t        MET;
  Double_t        NonPrefiringProb;
  Double_t        NonPrefiringProbUp;
  Double_t        NonPrefiringProbDown;

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
  Double_t        CrossSection;
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




  Double_t        DeltaPhi1_AK8;
  Double_t        DeltaPhi2_AK8;
  Double_t        DeltaPhiMin_AK8;


  std::vector<TLorentzVector> *GenJetsAK8=0; 
  std::vector<int> *GenJetsAK8_multiplicity=0;
  std::vector<double> *GenJetsAK8_prunedMass=0;
  std::vector<double> *GenJetsAK8_softDropMass=0;

  std::vector<TLorentzVector> *JetsAK8=0;
  std::vector<double> *JetsAK8_deepDoubleBDiscriminatorH=0;
  std::vector<double> *JetsAK8_deepDoubleBDiscriminatorQ=0;
  std::vector<double> *JetsAK8_doubleBDiscriminator=0;
  std::vector<double> *JetsAK8_hDiscriminatorDeep=0;
  std::vector<int> *JetsAK8_multiplicity=0; 

  std::vector<double> *JetsAK8_NsubjettinessTau1=0;
  std::vector<double> *JetsAK8_NsubjettinessTau2=0;
  std::vector<double> *JetsAK8_NsubjettinessTau3=0;

  std::vector<int> * JetsAK8_origIndex=0;
  std::vector<double> *JetsAK8_prunedMass=0;
  std::vector<double> *JetsAK8_softDropMass=0;  

  std::vector<vector<TLorentzVector> > *JetsAK8_subjets=0;
  std::vector<vector<double> > *JetsAK8_subjets_bDiscriminatorCSV=0;
  std::vector<vector<int> > *JetsAK8_subjets_multiplicity=0;
  std::vector<double> *JetsAK8_tDiscriminatorDeep=0;
  std::vector<double> *JetsAK8_tDiscriminatorDeepDecorrel=0;
  std::vector<double> *JetsAK8_wDiscriminatorDeep=0;
  std::vector<double> *JetsAK8_wDiscriminatorDeepDecorrel=0;
  std::vector<double> *JetsAK8_zDiscriminatorDeep=0;
  std::vector<double> *JetsAK8_zDiscriminatorDeepDecorrel=0;



   // List of branches

  TBranch        *b_RunNum=0;   //!
  TBranch        *b_LumiBlockNum=0;   //!
  TBranch        *b_EvtNum=0;   //!
  TBranch        *b_BTags=0;   //!
  TBranch        *b_BTagsDeepCSV=0;   //!
  TBranch        *b_BTagsclean=0; 
  TBranch        *b_BadChargedCandidateFilter=0;   //!
  TBranch        *b_BadPFMuonFilter=0;   //!
  TBranch        *b_CrossSection=0;   //!
  TBranch        *b_ecalBadCalibFilter=0;
  TBranch        *b_ecalBadCalibReducedFilter=0; 
  TBranch        *b_ecalBadCalibReducedExtraFilter=0; 
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

  TBranch        *b_globalSuperTightHalo2016Filter=0;   //!
  TBranch        *b_EcalDeadCellTriggerPrimitiveFilter=0;   //!
  TBranch        *b_eeBadScFilter=0;   //!
  //TBranch        *b_eeBadSc4Filter=0;   //!
  TBranch        *b_GenElectrons=0;   //!
  TBranch        *b_GenElectrons_fromTau=0;   //!
  TBranch        *b_GenMuons=0;   //!
  TBranch        *b_GenMuons_fromTau=0;   //! 
  TBranch        *b_GenTaus=0;   //!
  TBranch        *b_GenTaus_had=0;   //!
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
  TBranch        *b_Muons_mediumID=0;
  TBranch        *b_Muons_passIso=0;
  TBranch        *b_Electrons_passIso=0;

  TBranch        *b_JetID=0;   //!
  TBranch        *b_Jets=0;   //!
  //  TBranch        *b_Jets_ID;   //!

  TBranch        *b_Jets_muonEnergyFraction=0;   //!
  TBranch        *b_Jets_bDiscriminatorCSV=0;   //!
  TBranch        *b_Jets_bJetTagDeepCSVprobb=0;   //!
  TBranch        *b_Jets_bJetTagDeepCSVprobbb=0;   //!

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
  TBranch        *b_NonPrefiringProb=0;   //!
  TBranch        *b_NonPrefiringProbUp=0;   //!
  TBranch        *b_NonPrefiringProbDown=0;   //!

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

  TBranch        *b_DeltaPhi1_AK8=0;
  TBranch        *b_DeltaPhi2_AK8=0;
  TBranch        *b_DeltaPhiMin_AK8=0;


  TBranch        *b_GenJetsAK8=0; 
  TBranch        *b_GenJetsAK8_multiplicity=0;
  TBranch        *b_GenJetsAK8_prunedMass=0;
  TBranch        *b_GenJetsAK8_softDropMass=0;

  TBranch        *b_JetsAK8=0;
  TBranch        *b_JetsAK8_deepDoubleBDiscriminatorH=0;
  TBranch        *b_JetsAK8_deepDoubleBDiscriminatorQ=0;
  TBranch        *b_JetsAK8_doubleBDiscriminator=0;
  TBranch        *b_JetsAK8_hDiscriminatorDeep=0;
  TBranch        *b_JetsAK8_multiplicity=0; 

  TBranch        *b_JetsAK8_NsubjettinessTau1=0;
  TBranch        *b_JetsAK8_NsubjettinessTau2=0;
  TBranch        *b_JetsAK8_NsubjettinessTau3=0;

  TBranch        *b_JetsAK8_origIndex=0;
  TBranch        *b_JetsAK8_prunedMass=0;
  TBranch        *b_JetsAK8_softDropMass=0;  

  TBranch        *b_JetsAK8_subjets=0;
  TBranch        *b_JetsAK8_subjets_bDiscriminatorCSV=0;
  TBranch        *b_JetsAK8_subjets_multiplicity=0;
  TBranch        *b_JetsAK8_tDiscriminatorDeep=0;
  TBranch        *b_JetsAK8_tDiscriminatorDeepDecorrel=0;
  TBranch        *b_JetsAK8_wDiscriminatorDeep=0;
  TBranch        *b_JetsAK8_wDiscriminatorDeepDecorrel=0;
  TBranch        *b_JetsAK8_zDiscriminatorDeep=0;
  TBranch        *b_JetsAK8_zDiscriminatorDeepDecorrel=0;




   
 NtupleVariables(TTree * /*tree*/ =0) : fChain(0) { }
   ~NtupleVariables() { }
   void    Init(TTree *tree, string);
   Bool_t  Notify();
   Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   double  DeltaPhi(double, double);
   double  DeltaR(double eta1, double phi1, double eta2, double phi2);
   
};

#endif
#ifdef NtupleVariables_cxx
void NtupleVariables::Init(TTree *tree, string nameData)
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

   // Set object pointer
  //   Electrons = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   fChain->SetBranchStatus("*",0);

  fChain->SetBranchStatus("RunNum", 1);

  fChain->SetBranchStatus("LumiBlockNum", 1);
  fChain->SetBranchStatus("EvtNum", 1);

  fChain->SetBranchStatus("CSCTightHaloFilter", 1);
  fChain->SetBranchStatus("EcalDeadCellTriggerPrimitiveFilter", 1);
  fChain->SetBranchStatus("eeBadScFilter", 1);
  //fChain->SetBranchStatus("eeBadSc4Filter", 1);    
  fChain->SetBranchStatus("HBHENoiseFilter", 1);
  fChain->SetBranchStatus("HBHEIsoNoiseFilter", 1);
  fChain->SetBranchStatus("ecalBadCalibFilter", 1); 
  fChain->SetBranchStatus("ecalBadCalibReducedFilter", 1);
  fChain->SetBranchStatus("ecalBadCalibReducedExtraFilter", 1);
  fChain->SetBranchStatus("globalSuperTightHalo2016Filter", 1);
  fChain->SetBranchStatus("BadChargedCandidateFilter", 1);
  fChain->SetBranchStatus("BadPFMuonFilter", 1);
  

  fChain->SetBranchStatus("BTags", 1);
  fChain->SetBranchStatus("BTagsDeepCSV", 1);
   fChain->SetBranchStatus("CrossSection",1);


  //fChain->SetBranchStatus("BTagsclean", 1);
  fChain->SetBranchStatus("DeltaPhi1", 1);
  fChain->SetBranchStatus("DeltaPhi2", 1);
  fChain->SetBranchStatus("DeltaPhi3", 1);
  fChain->SetBranchStatus("DeltaPhi4", 1);
  
  fChain->SetBranchStatus("Electrons", 1);
  fChain->SetBranchStatus("Electrons_passIso",1);
  fChain->SetBranchStatus("Electrons_MTW",1);
  fChain->SetBranchStatus("GenElectrons",1);
  fChain->SetBranchStatus("GenElectrons_fromTau",1);
  fChain->SetBranchStatus("GenJets",1);
  fChain->SetBranchStatus("GenMuons",1);
  fChain->SetBranchStatus("GenMuons_fromTau",1);
  fChain->SetBranchStatus("GenTaus",1);
  fChain->SetBranchStatus("GenTaus_had",1);

  fChain->SetBranchStatus("HT", 1);
  fChain->SetBranchStatus("HT5", 1);

  fChain->SetBranchStatus("isoElectronTracks", 1);
  fChain->SetBranchStatus("isoMuonTracks", 1);
  fChain->SetBranchStatus("isoPionTracks", 1);
  fChain->SetBranchStatus("JetID", 1);
  fChain->SetBranchStatus("Jets", 1);
  fChain->SetBranchStatus("Jets_bDiscriminatorCSV",1);
  fChain->SetBranchStatus("Jets_bJetTagDeepCSVprobb", 1);
  fChain->SetBranchStatus("Jets_bJetTagDeepCSVprobbb", 1);
  fChain->SetBranchStatus("Jets_chargedHadronEnergyFraction",1);
   fChain->SetBranchStatus("Jets_hadronFlavor",1);
   fChain->SetBranchStatus("Jets_neutralEmEnergyFraction",1);
   fChain->SetBranchStatus("Jets_HTMask",1);
   //   fChain->SetBranchStatus("Jets_ID",1);
   fChain->SetBranchStatus("Jets_muonEnergyFraction",1);   
   fChain->SetBranchStatus("madHT",1);
   fChain->SetBranchStatus("SusyLSPMass", 1);
   fChain->SetBranchStatus("SusyMotherMass", 1);
   fChain->SetBranchStatus("MET",1);
   fChain->SetBranchStatus("METPhi",1);
   fChain->SetBranchStatus("MHT",1);
   fChain->SetBranchStatus("MHTPhi",1);
   fChain->SetBranchStatus("Muons",1);
   fChain->SetBranchStatus("Muons_mediumID",1);
   fChain->SetBranchStatus("Muons_passIso",1);
   fChain->SetBranchStatus("Muons_MTW",1);
   fChain->SetBranchStatus("NJets",1);
   fChain->SetBranchStatus("NJetsISR",1);
   fChain->SetBranchStatus("NVtx",1);
   fChain->SetBranchStatus("NMuons",1);
   fChain->SetBranchStatus("NElectrons",1); 
   fChain->SetBranchStatus("NonPrefiringProb", 1);
   fChain->SetBranchStatus("PFCaloMETRatio",1);
   fChain->SetBranchStatus("puWeight",1);
   fChain->SetBranchStatus("TriggerNames",1);
   fChain->SetBranchStatus("TriggerPass",1);
   fChain->SetBranchStatus("TriggerPrescales", 1);
   fChain->SetBranchStatus("TrueNumInteractions",1);
   fChain->SetBranchStatus("Weight",1);


  fChain->SetBranchStatus("DeltaPhi1_AK8",1);
  fChain->SetBranchStatus("DeltaPhi2_AK8",1);
  fChain->SetBranchStatus("DeltaPhiMin_AK8",1);


  fChain->SetBranchStatus("GenJetsAK8",1); 
  fChain->SetBranchStatus("GenJetsAK8_multiplicity",1);
  fChain->SetBranchStatus("GenJetsAK8_prunedMass",1);
  fChain->SetBranchStatus("GenJetsAK8_softDropMass",1);

  fChain->SetBranchStatus("JetsAK8",1);
  fChain->SetBranchStatus("JetsAK8_deepDoubleBDiscriminatorH",1);
  fChain->SetBranchStatus("JetsAK8_deepDoubleBDiscriminatorQ",1);
  fChain->SetBranchStatus("JetsAK8_doubleBDiscriminator",1);
  fChain->SetBranchStatus("JetsAK8_hDiscriminatorDeep",1);
  fChain->SetBranchStatus("JetsAK8_multiplicity",1); 

  fChain->SetBranchStatus("JetsAK8_NsubjettinessTau1",1);
  fChain->SetBranchStatus("JetsAK8_NsubjettinessTau2",1);
  fChain->SetBranchStatus("JetsAK8_NsubjettinessTau3",1);

  fChain->SetBranchStatus("JetsAK8_origIndex",1);
  fChain->SetBranchStatus("JetsAK8_prunedMass",1);
  fChain->SetBranchStatus("JetsAK8_softDropMass",1);  

  fChain->SetBranchStatus("JetsAK8_subjets",1);
  fChain->SetBranchStatus("JetsAK8_subjets_bDiscriminatorCSV",1);
  fChain->SetBranchStatus("JetsAK8_subjets_multiplicity",1);
  fChain->SetBranchStatus("JetsAK8_tDiscriminatorDeep",1);
  fChain->SetBranchStatus("JetsAK8_tDiscriminatorDeepDecorrel",1);
  fChain->SetBranchStatus("JetsAK8_wDiscriminatorDeep",1);
  fChain->SetBranchStatus("JetsAK8_wDiscriminatorDeepDecorrel",1);
  fChain->SetBranchStatus("JetsAK8_zDiscriminatorDeep",1);
  fChain->SetBranchStatus("JetsAK8_zDiscriminatorDeepDecorrel",1);


   fChain->SetBranchAddress("CrossSection", &CrossSection, &b_CrossSection);
   fChain->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum, &b_LumiBlockNum);

  fChain->SetBranchAddress("NMuons", &NMuons, &b_NMuons);
  fChain->SetBranchAddress("NElectrons", &NElectrons, &b_NElectrons);
  fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
  fChain->SetBranchAddress("BTags", &BTags, &b_BTags);
  fChain->SetBranchAddress("BTagsDeepCSV", &BTagsDeepCSV, &b_BTagsDeepCSV);

  fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1, &b_DeltaPhi1);
  fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2, &b_DeltaPhi2);
  fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3, &b_DeltaPhi3);
  fChain->SetBranchAddress("DeltaPhi4", &DeltaPhi4, &b_DeltaPhi4);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("HT5", &HT5, &b_HT5);
  fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
  fChain->SetBranchAddress("MET", &MET, &b_MET);
  fChain->SetBranchAddress("NonPrefiringProb",&NonPrefiringProb, &b_NonPrefiringProb);
  fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
  fChain->SetBranchAddress("MHTPhi", &MHTPhi, &b_MHTPhi);
  fChain->SetBranchAddress("NJets", &NJets, &b_NJets);

  fChain->SetBranchAddress("PFCaloMETRatio", &PFCaloMETRatio, &b_PFCaloMETRatio);

    fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
    fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
    fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
    //fChain->SetBranchAddress("eeBadSc4Filter", &eeBadSc4Filter, &b_eeBadSc4Filter);    
    fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
    fChain->SetBranchAddress("HBHEIsoNoiseFilter", &HBHEIsoNoiseFilter, &b_HBHEIsoNoiseFilter);
      fChain->SetBranchAddress("ecalBadCalibFilter", &ecalBadCalibFilter, &b_ecalBadCalibFilter);
      fChain->SetBranchAddress("ecalBadCalibReducedFilter", &ecalBadCalibReducedFilter, &b_ecalBadCalibReducedFilter);
      fChain->SetBranchAddress("ecalBadCalibReducedExtraFilter", &ecalBadCalibReducedExtraFilter, &b_ecalBadCalibReducedExtraFilter);

      fChain->SetBranchAddress("globalSuperTightHalo2016Filter", &globalSuperTightHalo2016Filter, &b_globalSuperTightHalo2016Filter);
      fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
      fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
  fChain->SetBranchAddress("globalSuperTightHalo2016Filter", &globalSuperTightHalo2016Filter, &b_globalSuperTightHalo2016Filter);
  fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
  fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);

  fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracksNum, &b_isoElectronTracksNum);
  fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracksNum, &b_isoMuonTracksNum);
  fChain->SetBranchAddress("isoPionTracks", &isoPionTracksNum, &b_isoPionTracksNum);
  fChain->SetBranchAddress("JetID", &JetID, &b_JetID);
  //  fChain->SetBranchAddress("Jets_ID", &Jets_ID, &b_Jets_ID);

  fChain->SetBranchAddress("Jets", &Jets, &b_Jets);
  fChain->SetBranchAddress("Jets_HTMask", &Jets_HTMask, &b_Jets_HTMask);

  fChain->SetBranchAddress("NVtx", &NVtx, &b_NVtx);
  fChain->SetBranchAddress("Electrons", &Electrons, &b_Electrons);
  fChain->SetBranchAddress("Muons", &Muons, &b_Muons);
  fChain->SetBranchAddress("TriggerNames", &TriggerNames, &b_TriggerNames);
  fChain->SetBranchAddress("TriggerPass", &TriggerPass, &b_TriggerPass);
  fChain->SetBranchAddress("TriggerPrescales", &TriggerPrescales, &b_TriggerPrescales);
  fChain->SetBranchAddress("Muons_mediumID", &Muons_mediumID, &b_Muons_mediumID);
  fChain->SetBranchAddress("Muons_passIso", &Muons_passIso, &b_Muons_passIso);
  fChain->SetBranchAddress("Electrons_passIso", &Electrons_passIso, &b_Electrons_passIso);

  fChain->SetBranchAddress("Jets_muonEnergyFraction", &Jets_muonEnergyFraction, &b_Jets_muonEnergyFraction);
  fChain->SetBranchAddress("Jets_bDiscriminatorCSV", &Jets_bDiscriminatorCSV, &b_Jets_bDiscriminatorCSV);

  fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobb", &Jets_bJetTagDeepCSVprobb, &b_Jets_bJetTagDeepCSVprobb);
  fChain->SetBranchAddress("Jets_bJetTagDeepCSVprobbb", &Jets_bJetTagDeepCSVprobbb, &b_Jets_bJetTagDeepCSVprobbb);


  fChain->SetBranchAddress("GenElectrons", &GenElectrons, &b_GenElectrons);
  fChain->SetBranchAddress("GenElectrons_fromTau", &GenElectrons_fromTau, &b_GenElectrons_fromTau);
  fChain->SetBranchAddress("GenMuons", &GenMuons, &b_GenMuons);
  fChain->SetBranchAddress("GenMuons_fromTau", &GenMuons_fromTau, &b_GenMuons_fromTau);

  fChain->SetBranchAddress("GenTaus", &GenTaus, &b_GenTaus);
  fChain->SetBranchAddress("GenTaus_had", &GenTaus_had, &b_GenTaus_had);
  
  fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
  fChain->SetBranchAddress("Jets_hadronFlavor", &Jets_hadronFlavor, &b_Jets_hadronFlavor);
  fChain->SetBranchAddress("madHT", &madHT, &b_madHT);
  fChain->SetBranchAddress("TrueNumInteractions", &TrueNumInteractions, &b_TrueNumInteractions);
  fChain->SetBranchAddress("SusyLSPMass", &SusyLSPMass, &b_SusyLSPMass);
  fChain->SetBranchAddress("SusyMotherMass", &SusyMotherMass, &b_SusyMotherMass);
  fChain->SetBranchAddress("NJetsISR", &NJetsISR, &b_NJetsISR);
  fChain->SetBranchAddress("GenJets", &GenJets, &b_GenJets);
  fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
  fChain->SetBranchAddress("Jets_chargedHadronEnergyFraction", &Jets_chargedHadronEnergyFraction, &b_Jets_chargedHadronEnergyFraction);
  fChain->SetBranchAddress("Jets_neutralEmEnergyFraction", &Jets_neutralEmEnergyFraction, &b_Jets_neutralEmEnergyFraction);

  fChain->SetBranchAddress("Muons_MTW", &Muons_MTW, &b_Muons_MTW);
  fChain->SetBranchAddress("Electrons_MTW", &Electrons_MTW, &b_Electrons_MTW);

  fChain->SetBranchAddress("DeltaPhi1_AK8",&DeltaPhi1_AK8,&b_DeltaPhi1_AK8);
  fChain->SetBranchAddress("DeltaPhi2_AK8",&DeltaPhi2_AK8,&b_DeltaPhi2_AK8);
  fChain->SetBranchAddress("DeltaPhiMin_AK8",&DeltaPhiMin_AK8,&b_DeltaPhiMin_AK8);


  fChain->SetBranchAddress("GenJetsAK8",&GenJetsAK8,&b_GenJetsAK8); 
  fChain->SetBranchAddress("GenJetsAK8_multiplicity",&GenJetsAK8_multiplicity,&b_GenJetsAK8_multiplicity);
  fChain->SetBranchAddress("GenJetsAK8_prunedMass",&GenJetsAK8_prunedMass,&b_GenJetsAK8_prunedMass);
  fChain->SetBranchAddress("GenJetsAK8_softDropMass",&GenJetsAK8_softDropMass,&b_GenJetsAK8_softDropMass);

  fChain->SetBranchAddress("JetsAK8",&JetsAK8,&b_JetsAK8);
  fChain->SetBranchAddress("JetsAK8_deepDoubleBDiscriminatorH",&JetsAK8_deepDoubleBDiscriminatorH,&b_JetsAK8_deepDoubleBDiscriminatorH);
  fChain->SetBranchAddress("JetsAK8_deepDoubleBDiscriminatorQ",&JetsAK8_deepDoubleBDiscriminatorQ,&b_JetsAK8_deepDoubleBDiscriminatorQ);
  fChain->SetBranchAddress("JetsAK8_doubleBDiscriminator",&JetsAK8_doubleBDiscriminator,&b_JetsAK8_doubleBDiscriminator);
  fChain->SetBranchAddress("JetsAK8_hDiscriminatorDeep",&JetsAK8_hDiscriminatorDeep,&b_JetsAK8_hDiscriminatorDeep);
  fChain->SetBranchAddress("JetsAK8_multiplicity",&JetsAK8_multiplicity,&b_JetsAK8_multiplicity); 

  fChain->SetBranchAddress("JetsAK8_NsubjettinessTau1",&JetsAK8_NsubjettinessTau1,&b_JetsAK8_NsubjettinessTau1);
  fChain->SetBranchAddress("JetsAK8_NsubjettinessTau2",&JetsAK8_NsubjettinessTau2,&b_JetsAK8_NsubjettinessTau2);
  fChain->SetBranchAddress("JetsAK8_NsubjettinessTau3",&JetsAK8_NsubjettinessTau3,&b_JetsAK8_NsubjettinessTau3);

  fChain->SetBranchAddress("JetsAK8_origIndex",&JetsAK8_origIndex,&b_JetsAK8_origIndex);
  fChain->SetBranchAddress("JetsAK8_prunedMass",&JetsAK8_prunedMass,&b_JetsAK8_prunedMass);
  fChain->SetBranchAddress("JetsAK8_softDropMass",&JetsAK8_softDropMass,&b_JetsAK8_softDropMass);  

  fChain->SetBranchAddress("JetsAK8_subjets",&JetsAK8_subjets,&b_JetsAK8_subjets);
  fChain->SetBranchAddress("JetsAK8_subjets_bDiscriminatorCSV",&JetsAK8_subjets_bDiscriminatorCSV,&b_JetsAK8_subjets_bDiscriminatorCSV);
  fChain->SetBranchAddress("JetsAK8_subjets_multiplicity",&JetsAK8_subjets_multiplicity,&b_JetsAK8_subjets_multiplicity);
  fChain->SetBranchAddress("JetsAK8_tDiscriminatorDeep",&JetsAK8_tDiscriminatorDeep,&b_JetsAK8_tDiscriminatorDeep);
  fChain->SetBranchAddress("JetsAK8_tDiscriminatorDeepDecorrel",&JetsAK8_tDiscriminatorDeepDecorrel,&b_JetsAK8_tDiscriminatorDeepDecorrel);
  fChain->SetBranchAddress("JetsAK8_wDiscriminatorDeep",&JetsAK8_wDiscriminatorDeep,&b_JetsAK8_wDiscriminatorDeep);
  fChain->SetBranchAddress("JetsAK8_wDiscriminatorDeepDecorrel",&JetsAK8_wDiscriminatorDeepDecorrel,&b_JetsAK8_wDiscriminatorDeepDecorrel);
  fChain->SetBranchAddress("JetsAK8_zDiscriminatorDeep",&JetsAK8_zDiscriminatorDeep,&b_JetsAK8_zDiscriminatorDeep);
  fChain->SetBranchAddress("JetsAK8_zDiscriminatorDeepDecorrel",&JetsAK8_zDiscriminatorDeepDecorrel,&b_JetsAK8_zDiscriminatorDeepDecorrel);

   Notify();
}

Bool_t NtupleVariables::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef temp_cxx
