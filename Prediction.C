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
  h_HT_Exp =new TH1D("h_HT_Exp","h_HT_Exp",12,100,2500);
  h_HT5_Exp =new TH1D("h_HT5_Exp","h_HT5_Exp",12,100,2500);

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
  h_MHTv2Recipe_Exp =new TH1D("h_MHTv2Recipe_Exp","h_MHTv2Recipe_Exp",16,200,1000);
  h_MHTPhiv2Recipe_Exp=new TH1D("h_MHTPhiv2Recipe_Exp","h_MHTPhiv2Recipe_Exp",7,-3.5,3.5);
  h_NJetv2Recipe_Exp =new TH1D("h_NJetv2Recipe_Exp","h_NJetv2Recipe_Exp",10,2,12);
  h_NBtagv2Recipe_Exp =new TH1D("h_NBtagv2Recipe_Exp","h_NBtagv2Recipe_Exp",5,0,5);

  h_DphiOnev2Recipe_Exp =new TH1D("h_DphiOnev2Recipe_Exp","h_DphiOnev2Recipe_Exp",32,0,3.2);
  h_DphiTwov2Recipe_Exp =new TH1D("h_DphiTwov2Recipe_Exp","h_DphiTwov2Recipe_Exp",32,0,3.2);
  h_DphiThreev2Recipe_Exp =new TH1D("h_DphiThreev2Recipe_Exp","h_DphiThreev2Recipe_Exp",32,0,3.2);
  h_DphiFourv2Recipe_Exp =new TH1D("h_DphiFourv2Recipe_Exp","h_DphiFourv2Recipe_Exp",32,0,3.2);


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

  GetOutputList()->Add(h_HT_Exp);
  GetOutputList()->Add(h_HT5_Exp);

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
  GetOutputList()->Add(h_MHTv2Recipe_Exp);
  GetOutputList()->Add(h_MHTPhiv2Recipe_Exp);
  GetOutputList()->Add(h_NJetv2Recipe_Exp);
  GetOutputList()->Add(h_NBtagv2Recipe_Exp);
  GetOutputList()->Add(h_DphiOnev2Recipe_Exp);
  GetOutputList()->Add(h_DphiTwov2Recipe_Exp);
  GetOutputList()->Add(h_DphiThreev2Recipe_Exp);
  GetOutputList()->Add(h_DphiFourv2Recipe_Exp);


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
  //  MuonsNum_ = Muons->size();
  //  ElectronsNum_ = Electrons->size();
  //*AR: 180917: NMuons and NElectrons are number of isolated electrons and muons
  MuonsNum_ = NMuons;
  ElectronsNum_ = NElectrons;
  double newGenHT=0;double newGenMHT=0;
  TVector3 temp3Vec;
  vector<TVector3>GenHT3JetVec,GenMHT3JetVec;
  TVector3 newGenMHT3Vec;
  int BTagsfrmCSV=0;

  vector<TVector3>Jetsv2Recipe;
  vector<double> JetsCSVv2Recipe;
  HTv2Recipe=-99.;
  MHTv2Recipe=-99.;
  MHTPhiv2Recipe=-99.;
  TVector3 MHT3Vecv2Recipe;
  int NJetv2Recipe=0;
  int NBtagv2Recipe=0;
  DeltaPhi1v2Recipe=-99.;
  DeltaPhi2v2Recipe=-99.;
  DeltaPhi3v2Recipe=-99.;
  DeltaPhi4v2Recipe=-99.;
  //  if(BTags>0)
  //std::cout<<" entry "<<" jets_size "<<Jets->size()<<" njets "<<NJets<<" btags "<<BTags<<endl;

  for(unsigned j = 0; j < Jets->size(); ++j){
    double jetCSV=Jets_bDiscriminatorCSV->at(j);
    if(jetCSV>csvForBtag && Jets->at(j).Pt() > 30 && fabs(Jets->at(j).Eta())<2.4)
      BTagsfrmCSV++;
  }

  for(unsigned j = 0; j < Jets->size(); ++j){
    double jetPtv2Recipe= Jets->at(j).Pt()/Jets_jecFactor->at(j);
    //std::cout<<" raw pt "<<jetPtv2Recipe<<" pt "<<Jets->at(j).Pt()<<" eta "<<Jets->at(j).Eta()<<" phi "<<Jets->at(j).Phi()<<endl;
    if(jetPtv2Recipe >50 && (fabs(Jets->at(j).Eta()) < 2.65 || fabs(Jets->at(j).Eta()) > 3.139)){
      temp3Vec.SetPtEtaPhi(Jets->at(j).Pt(),Jets->at(j).Eta(),Jets->at(j).Phi());
      Jetsv2Recipe.push_back(temp3Vec);
      JetsCSVv2Recipe.push_back(Jets_bDiscriminatorCSV->at(j));
    }
  }
  
  //  std::cout<<" jetPtv2Recipe.size "<<Jetsv2Recipe.size()<<endl;
  
  for(unsigned int i=0;i<Jetsv2Recipe.size();i++){
    if(Jetsv2Recipe[i].Pt()>30 && fabs(Jetsv2Recipe[i].Eta())<2.4){
      HTv2Recipe+=Jetsv2Recipe[i].Pt();
      NJetsv2Recipe++;
      if(JetsCSVv2Recipe[i]>csvForBtag)
	BTagsv2Recipe++;
    }
    if(Jetsv2Recipe[i].Pt()>30 && fabs(Jetsv2Recipe[i].Eta())<5.0){
      MHT3Vecv2Recipe-=Jetsv2Recipe[i];
    }
  }
  if(MHT3Vecv2Recipe.Pt()!=0){
    MHTv2Recipe=MHT3Vecv2Recipe.Pt(); 
    MHTPhiv2Recipe=MHT3Vecv2Recipe.Phi();
  }
  if(Jetsv2Recipe.size()>0){
    DeltaPhi1v2Recipe=Jetsv2Recipe[0].Phi()-MHTPhiv2Recipe;
    if(Jetsv2Recipe.size()>1)
      DeltaPhi2v2Recipe=Jetsv2Recipe[1].Phi()-MHTPhiv2Recipe;
    if(Jetsv2Recipe.size()>2)
      DeltaPhi3v2Recipe=Jetsv2Recipe[2].Phi()-MHTPhiv2Recipe;
    if(Jetsv2Recipe.size()>3)
      DeltaPhi4v2Recipe=Jetsv2Recipe[3].Phi()-MHTPhiv2Recipe;
  }
  //  std::cout<<" seg vio "<<endl;
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
  
  //only considers single isolated lepton events
  if(!GetSignalRegHists){
    if((MuonsNum_+ElectronsNum_) !=1) return kTRUE;

    if(MuonsNum_==1){
      for(unsigned int i=0;i<Muons->size();i++){
	if(Muons_passIso->at(i)){
	  LepPt=Muons->at(i).Pt();
	  LepEta=Muons->at(i).Eta();
	  LepPhi=Muons->at(i).Phi();
	}
      }
    }

    if(ElectronsNum_==1){
      for(unsigned int i=0;i<Electrons->size();i++){
	if(Electrons_passIso->at(i)){
	  LepPt=Electrons->at(i).Pt();
	  LepEta=Electrons->at(i).Eta();
	  LepPhi=Electrons->at(i).Phi();
	}
      }
    }

    if(LepPt<20 || fabs(LepEta)>2.1) 
      return kTRUE;
  } //end of if(!GetSignalRegHists)
  else
    if((MuonsNum_+ElectronsNum_) !=0) return kTRUE;
  
  //*AR: 180917- Only consider events with HT>300, MHT>250, Njet>1.5
  if(runOnSignalMC && useGenHTMHT){
    if(newGenHT<minHT_ || newGenMHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
  }
  else{
    if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
  }

  //*AR: 180917-for high dphi: only events with all dphis>(0.5,0.5,0.3,0.3)
  //for low dphi: only events with either of dphis<(0.5,0.5,0.3,0.3)
  if(useDeltaPhiCut == 1)  if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
  if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
  if(applyFilters &&  !FiltersPass() ) return kTRUE;
  //*AR-180606:Only consider events with one isolated lepton at reco level and mT<100(no pT, eta cuts)
  if(!GetSignalRegHists){
    if(MuonsNum_==1 && ElectronsNum_==0){
      mtw =  Muons_MTW->at(0);
      
      //std::cout<<" entry "<<entry<<" 1mu event "<<endl;
      
      //*AR: 180917- Gets skimfile for signal and standard model MC
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
  if(GetSignalRegHists){
    if(isoTracksNum !=0){
      std::cout<<" isotrack nonzero "<<endl;
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
  if(useTrigger) if(!TriggerPass->at(108) && !TriggerPass->at(110) &&!TriggerPass->at(114) && !TriggerPass->at(124) && !TriggerPass->at(126) && !TriggerPass->at(129)) return kTRUE;

  if(runOnSignalMC && useGenHTMHT){
    Bin_ = SearchBins_->GetBinNumber(newGenHT,newGenMHT,NJets,BTagsfrmCSV);
    BinQCD_ = SearchBinsQCD_->GetBinNumber(newGenHT,newGenMHT,NJets,BTagsfrmCSV);
  }
  else{
    Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTagsfrmCSV);
    BinQCD_ = SearchBinsQCD_->GetBinNumber(HT,MHT,NJets,BTagsfrmCSV);
  }
  if(Bin_ > 900 && BinQCD_ > 900) return kTRUE;
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
      std::cout<<" skip event "<<endl;
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

    std::cout<<" passed event "<<" evt "<<EvtNum<<" run "<<RunNum<<" lumi "<<LumiBlockNum<<endl;

  }


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
    //std::cout<<" i "<<i<<" bTagBin "<<bTagBin<<" *** Seg Vio3 *** "<<endl;
    //*AR: 180917- These histograms represent yield in CR as TF is not applied
    h_CSStat->Fill(bTagBin, WeightBtagProb);
    h_HT_Exp->Fill(HT,WeightBtagProb);
    h_HT5_Exp->Fill(HT5,WeightBtagProb);
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
    h_MHTv2Recipe_Exp->Fill(MHTv2Recipe,WeightBtagProb);
    h_MHTPhiv2Recipe_Exp->Fill(MHTPhiv2Recipe,WeightBtagProb);
    h_NJetv2Recipe_Exp->Fill(NJetsv2Recipe,WeightBtagProb);
    h_NBtagv2Recipe_Exp->Fill(BTagsv2Recipe,WeightBtagProb);
    h_DphiOnev2Recipe_Exp->Fill(DeltaPhi1v2Recipe,WeightBtagProb);
    h_DphiTwov2Recipe_Exp->Fill(DeltaPhi2v2Recipe,WeightBtagProb);
    h_DphiThreev2Recipe_Exp->Fill(DeltaPhi3v2Recipe,WeightBtagProb);
    h_DphiFourv2Recipe_Exp->Fill(DeltaPhi4v2Recipe,WeightBtagProb);


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
  h_HT_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT_Exp"));
  h_HT5_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_HT5_Exp"));
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
  h_MHTv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTv2Recipe_Exp"));
  h_MHTPhiv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MHTPhiv2Recipe_Exp"));
  h_NJetv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NJetv2Recipe_Exp"));
  h_NBtagv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_NBtagv2Recipe_Exp"));
  h_DphiOnev2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiOnev2Recipe_Exp"));
  h_DphiTwov2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiTwov2Recipe_Exp"));
  h_DphiThreev2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiThreev2Recipe_Exp"));
  h_DphiFourv2Recipe_Exp = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_DphiFourv2Recipe_Exp"));


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
  h_HT_Exp->Write();
  h_HT5_Exp->Write();  
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
  h_MHTv2Recipe_Exp->Write();
  h_MHTPhiv2Recipe_Exp->Write();
  h_NJetv2Recipe_Exp->Write();
  h_NBtagv2Recipe_Exp->Write();
  h_DphiOnev2Recipe_Exp->Write();
  h_DphiTwov2Recipe_Exp->Write();
  h_DphiThreev2Recipe_Exp->Write();
  h_DphiFourv2Recipe_Exp->Write(); 


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
