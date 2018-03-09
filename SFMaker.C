#define SFMaker_cxx

#include "SFMaker.h"

void SFMaker::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TH1::SetDefaultSumw2();
}

void SFMaker::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).
  std::cout<<"***SFMaker::SlaveBegin***"<<std::endl;
  
  SearchBins_ = new SearchBins(true);
  SearchBins_BTags_ = new SearchBins(true);
  
  bTagBins = {0, 0, 0, 0};
  
  // Initialize Histograms
  TH1::SetDefaultSumw2();
  unsigned nSB = SearchBins_->GetNbins();
    if(useCombinedBins) nSB = SearchBins_->GetNbinsCombined();
    h_el_nOnePrompt_etaPt = new TH2D("h_el_nOnePrompt_etaPt", "h_el_nOnePrompt_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_el_nOnePrompt_SB = new TH1D("h_el_nOnePrompt_SB", "h_el_nOnePrompt_SB", nSB, 0.5, nSB+0.5);    
    h_el_nFoundOnePrompt_etaPt = new TH2D("h_el_nFoundOnePrompt_etaPt", "h_el_nFoundOnePrompt_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_el_nFoundOnePrompt_SB = new TH1D("h_el_nFoundOnePrompt_SB", "h_el_nFoundOnePrompt_SB", nSB, 0.5, nSB+0.5);
    h_el_nFoundOnePrompt_SF_etaPt = new TH2D("h_el_nFoundOnePrompt_SF_etaPt", "h_el_nFoundOnePrompt_SF_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_el_nFoundOnePrompt_SF_SB = new TH1D("h_el_nFoundOnePrompt_SF_SB", "h_el_nFoundOnePrompt_SF_SB", nSB, 0.5, nSB+0.5);
    h_el_nLostOnePrompt_etaPt = new TH2D("h_el_nLostOnePrompt_etaPt", "h_el_nLostOnePrompt_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_el_nLostOnePrompt_SB = new TH1D("h_el_nLostOnePrompt_SB", "h_el_nLostOnePrompt_SB", nSB, 0.5, nSB+0.5);

    h_el_SFCR_etaPt = new TH2D("h_el_SFCR_etaPt", "h_el_SFCR_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_el_SFCR_SB = new TH1D("h_el_SFCR_SB", "h_el_SFCR_SB", nSB, 0.5, nSB+0.5);
    h_el_SFSR_etaPt = new TH2D("h_el_SFSR_etaPt", "h_el_SFSR_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_el_SFSR_SB = new TH1D("h_el_SFSR_SB", "h_el_SFSR_SB", nSB, 0.5, nSB+0.5);

    h_mu_nOnePrompt_etaPt = new TH2D("h_mu_nOnePrompt_etaPt", "h_mu_nOnePrompt_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_mu_nOnePrompt_SB = new TH1D("h_mu_nOnePrompt_SB", "h_mu_nOnePrompt_SB", nSB, 0.5, nSB+0.5);    
    h_mu_nFoundOnePrompt_etaPt = new TH2D("h_mu_nFoundOnePrompt_etaPt", "h_mu_nFoundOnePrompt_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_mu_nFoundOnePrompt_SB = new TH1D("h_mu_nFoundOnePrompt_SB", "h_mu_nFoundOnePrompt_SB", nSB, 0.5, nSB+0.5);
    h_mu_nFoundOnePrompt_SF_etaPt = new TH2D("h_mu_nFoundOnePrompt_SF_etaPt", "h_mu_nFoundOnePrompt_SF_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_mu_nFoundOnePrompt_SF_SB = new TH1D("h_mu_nFoundOnePrompt_SF_SB", "h_mu_nFoundOnePrompt_SF_SB", nSB, 0.5, nSB+0.5);
    h_mu_nLostOnePrompt_etaPt = new TH2D("h_mu_nLostOnePrompt_etaPt", "h_mu_nLostOnePrompt_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_mu_nLostOnePrompt_SB = new TH1D("h_mu_nLostOnePrompt_SB", "h_mu_nLostOnePrompt_SB", nSB, 0.5, nSB+0.5);

    h_mu_SFCR_etaPt = new TH2D("h_mu_SFCR_etaPt", "h_mu_SFCR_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_mu_SFCR_SB = new TH1D("h_mu_SFCR_SB", "h_mu_SFCR_SB", nSB, 0.5, nSB+0.5);
    h_mu_SFSR_etaPt = new TH2D("h_mu_SFSR_etaPt", "h_mu_SFSR_etaPt", nBins_etaElec-1, bins_etaElec, nBins_pT-1, bins_pT);
    h_mu_SFSR_SB = new TH1D("h_mu_SFSR_SB", "h_mu_SFSR_SB", nSB, 0.5, nSB+0.5);

    h_di_nTwoPrompt_SB = new TH1D("h_di_nTwoPrompt_SB", "h_di_nTwoPrompt_SB", nSB, 0.5, nSB+0.5);
    h_di_nOneFoundTwoPrompt_SB = new TH1D("h_di_nOneFoundTwoPrompt_SB", "h_di_nOneFoundTwoPrompt_SB", nSB, 0.5, nSB+0.5);
    h_di_nOneFoundTwoPrompt_SF_SB = new TH1D("h_di_nOneFoundTwoPrompt_SF_SB", "h_di_nOneFoundTwoPrompt_SF_SB", nSB, 0.5, nSB+0.5);
    h_di_nTwoFoundTwoPrompt_SB = new TH1D("h_di_nTwoFoundTwoPrompt_SB", "h_di_nTwoFoundTwoPrompt_SB", nSB, 0.5, nSB+0.5);
    h_di_nTwoFoundTwoPrompt_SF_SB = new TH1D("h_di_nTwoFoundTwoPrompt_SF_SB", "h_di_nTwoFoundTwoPrompt_SF_SB", nSB, 0.5, nSB+0.5);
    h_di_nLostTwoPrompt_SB = new TH1D("h_di_nLostTwoPrompt_SB", "h_di_nLostTwoPrompt_SB", nSB, 0.5, nSB+0.5);

    h_di_SFCR_SB = new TH1D("h_di_SFCR_SB", "h_di_SFCR_SB", nSB, 0.5, nSB+0.5);
    h_di_SFSR_SB = new TH1D("h_di_SFSR_SB", "h_di_SFSR_SB", nSB, 0.5, nSB+0.5);

    GetOutputList()->Add(h_el_nOnePrompt_etaPt);
    GetOutputList()->Add(h_el_nOnePrompt_SB);
    GetOutputList()->Add(h_el_nFoundOnePrompt_etaPt);
    GetOutputList()->Add(h_el_nFoundOnePrompt_SB);
    GetOutputList()->Add(h_el_nFoundOnePrompt_SF_etaPt);
    GetOutputList()->Add(h_el_nFoundOnePrompt_SF_SB);
    GetOutputList()->Add(h_el_nLostOnePrompt_etaPt);
    GetOutputList()->Add(h_el_nLostOnePrompt_SB);
    GetOutputList()->Add(h_el_SFCR_etaPt);
    GetOutputList()->Add(h_el_SFCR_SB);
    GetOutputList()->Add(h_el_SFSR_etaPt);
    GetOutputList()->Add(h_el_SFSR_SB);

    GetOutputList()->Add(h_mu_nOnePrompt_etaPt);
    GetOutputList()->Add(h_mu_nOnePrompt_SB);
    GetOutputList()->Add(h_mu_nFoundOnePrompt_etaPt);
    GetOutputList()->Add(h_mu_nFoundOnePrompt_SB);
    GetOutputList()->Add(h_mu_nFoundOnePrompt_SF_etaPt);
    GetOutputList()->Add(h_mu_nFoundOnePrompt_SF_SB);
    GetOutputList()->Add(h_mu_nLostOnePrompt_etaPt);
    GetOutputList()->Add(h_mu_nLostOnePrompt_SB);
    GetOutputList()->Add(h_mu_SFCR_etaPt);
    GetOutputList()->Add(h_mu_SFCR_SB);
    GetOutputList()->Add(h_mu_SFSR_etaPt);
    GetOutputList()->Add(h_mu_SFSR_SB);

    GetOutputList()->Add(h_di_nTwoPrompt_SB);
    GetOutputList()->Add(h_di_nOneFoundTwoPrompt_SB);
    GetOutputList()->Add(h_di_nOneFoundTwoPrompt_SF_SB);
    GetOutputList()->Add(h_di_nTwoFoundTwoPrompt_SB);
    GetOutputList()->Add(h_di_nTwoFoundTwoPrompt_SF_SB);
    GetOutputList()->Add(h_di_nLostTwoPrompt_SB);
    GetOutputList()->Add(h_di_SFCR_SB);
    GetOutputList()->Add(h_di_SFSR_SB);

    std::cout<<"----------------"<<std::endl;
    std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
    std::cout<<"----------------"<<std::endl;
}

Bool_t SFMaker::Process(Long64_t entry)
{
  //  std::cout<<"***SFMaker::Process***"<<" entry "<<entry<<" HT "<<HT<<" MHT "<<MHT<<" NJets "<<NJets<<std::endl;
  
    resetValues();

    fChain->GetTree()->GetEntry(entry);
    //*AR-180116-Only consider events passing filters
    if(applyFilters &&  !FiltersPass() ) return kTRUE;

    
    vector<TVector3> NewJets;
    vector<TVector3> HT3JetVec;
    vector<TVector3> MHT3JetVec;
    vector<TLorentzVector> MHT3JetLorentzVec;
    vector<double> HT3JetCSVvec;
    vector<double> MHT3JetCSVvec;
    vector<bool> HT3JetHTMaskvec;
    vector<bool> MHT3JetHTMaskvec;
    vector<int> HT3JetHadronFlavorvec;
    vector<int> MHT3JetHadronFlavorvec;
    TVector3 temp3Vec;
    TLorentzVector temp3LorentzVec;
    double newPt=-99;     
    double jetCSV=-99;
    bool jet_HTMask=false;
    int jet_hadronFlavor=-99;
    bool Print=false;
    double newHT=0,newMHT=0,newMHTPhi=0;
    TVector3 newMHT3Vec;
    int newNJets=-99;
    double newDphi1=99.,newDphi2=99.,newDphi3=99.,newDphi4=99.;
    int newBTags = 0;
  //*AR-180115-As in jet collection there are jets saved with pt>30 and eta<5, MHT3JetVec size remains same while HT3JetVec size reduces.
    if(JECSys){ 
      for(unsigned int i=0;i < Jets->size();i++){
	//std::cout<<" i "<<i<<" jet_pt(i) "<<Jets->at(i).Pt()<<" jec "<< Jets_jecUnc->at(i)<<" new pt "<< Jets->at(i).Pt()*(1+Jets_jecUnc->at(i))<<" csv "<< Jets_bDiscriminatorCSV->at(i)<<" HTMask "<< Jets_HTMask->at(i)<<" hadronFlavor "<<Jets_hadronFlavor->at(i)<<" eta "<< Jets->at(i).Eta()<<endl;
	if(SysUp) newPt=Jets->at(i).Pt()*(1+Jets_jecUnc->at(i));
	if(SysDn) newPt=Jets->at(i).Pt()*(1-Jets_jecUnc->at(i));
	jetCSV=Jets_bDiscriminatorCSV->at(i);
	jet_HTMask=Jets_HTMask->at(i);
	jet_hadronFlavor=Jets_hadronFlavor->at(i);
	temp3Vec.SetPtEtaPhi(newPt,Jets->at(i).Eta(),Jets->at(i).Phi());
	temp3LorentzVec.SetPtEtaPhiM(newPt,Jets->at(i).Eta(),Jets->at(i).Phi(),Jets->at(i).M());
	NewJets.push_back(temp3Vec);
	if(newPt>30. && fabs(Jets->at(i).Eta())<2.4){
	  HT3JetVec.push_back(temp3Vec);
	  HT3JetCSVvec.push_back(jetCSV);
	  HT3JetHTMaskvec.push_back(jet_HTMask);
	  HT3JetHadronFlavorvec.push_back(jet_hadronFlavor);
	}
	if(newPt>30. && fabs(Jets->at(i).Eta())<5.){
	  MHT3JetVec.push_back(temp3Vec);
	  MHT3JetLorentzVec.push_back(temp3LorentzVec);
	  MHT3JetCSVvec.push_back(jetCSV);
	  MHT3JetHTMaskvec.push_back(jet_HTMask);
	  MHT3JetHadronFlavorvec.push_back(jet_hadronFlavor);
	}
      } //end of for loop
      /*
	for(unsigned int i=0;i < SoftJets->size();i++){
	//std::cout<<" i "<<i<<" jet_pt(i) "<<Jets->at(i).Pt()<<" jec "<< Jets_jecUnc->at(i)<<" new pt "<< Jets->at(i).Pt()*(1+Jets_jecUnc->at(i))<<" csv "<< Jets_bDiscriminatorCSV->at(i)<<" HTMask "<< Jets_HTMask->at(i)<<" hadronFlavor "<<Jets_hadronFlavor->at(i)<<" eta "<< Jets->at(i).Eta()<<endl;
	if(SysUp) newPt=SoftJets->at(i).Pt()*(1+SoftJets_jecUnc->at(i));
	if(SysDn) newPt=SoftJets->at(i).Pt()*(1-SoftJets_jecUnc->at(i));
	jetCSV=SoftJets_bDiscriminatorCSV->at(i);
	jet_HTMask=SoftJets_HTMask->at(i);
	jet_hadronFlavor=SoftJets_hadronFlavor->at(i);
	temp3Vec.SetPtEtaPhi(newPt,SoftJets->at(i).Eta(),SoftJets->at(i).Phi());
	temp3LorentzVec.SetPtEtaPhiM(newPt,SoftJets->at(i).Eta(),SoftJets->at(i).Phi(),SoftJets->at(i).M());
	NewJets.push_back(temp3Vec);
	if(newPt>30. && fabs(SoftJets->at(i).Eta())<2.4){
	  HT3JetVec.push_back(temp3Vec);
	  HT3JetCSVvec.push_back(jetCSV);
	  HT3JetHTMaskvec.push_back(jet_HTMask);
	  HT3JetHadronFlavorvec.push_back(jet_hadronFlavor);
	}
	if(newPt>30. && fabs(SoftJets->at(i).Eta())<5.){
	  MHT3JetVec.push_back(temp3Vec);
	  MHT3JetLorentzVec.push_back(temp3LorentzVec);
	  MHT3JetCSVvec.push_back(jetCSV);
	  MHT3JetHTMaskvec.push_back(jet_HTMask);
	  MHT3JetHadronFlavorvec.push_back(jet_hadronFlavor);
	}
      } //end of for loop
      */
      //      if(Jets->size()!=MHT3JetVec.size()) 
      //std::cout<< " jet_size "<<Jets->size()<<" HT3 "<<HT3JetVec.size()<<" MHT3 "<<MHT3JetVec.size()<<endl;
      /*
      for(unsigned int i=1;i<MHT3JetVec.size();i++){
	if(MHT3JetVec[i-1].Pt()<MHT3JetVec[i].Pt()){
	  Print=true;
	  //  std::cout<<"*** vector before ordering ***"<<" i "<<i<<" jet_pt(i) "<< Jets->at(i).Pt()<<" MHT_pt(i) "<<MHT3JetVec[i].Pt()<<" MHT_csv(i) "<< MHT3JetCSVvec[i]<<" MHT_HTMask(i) "<< MHT3JetHTMaskvec[i]<<" MHT_JetHadronFlavor "<< MHT3JetHadronFlavorvec[i]<<" eta "<< MHT3JetVec[i].Eta()<<" MHT_Lor_pt(i) "<<MHT3JetLorentzVec[i].Pt()<<endl;
	}
      }
      
      */
      
      HT3JetCSVvec= Order_the_Vec(HT3JetVec,HT3JetCSVvec);   
      MHT3JetCSVvec= Order_the_Vec(MHT3JetVec,MHT3JetCSVvec);    
      HT3JetHTMaskvec= Order_the_Vec(HT3JetVec,HT3JetHTMaskvec);   
      MHT3JetHTMaskvec= Order_the_Vec(MHT3JetVec,MHT3JetHTMaskvec);    
      HT3JetHadronFlavorvec= Order_the_Vec(HT3JetVec,HT3JetHadronFlavorvec);   
      MHT3JetHadronFlavorvec= Order_the_Vec(MHT3JetVec,MHT3JetHadronFlavorvec);         MHT3JetLorentzVec= Order_the_Vec(MHT3JetVec,MHT3JetLorentzVec);
      HT3JetVec= Order_the_Vec(HT3JetVec);
      MHT3JetVec= Order_the_Vec(MHT3JetVec);      
      /*
      if(HT3JetCSVvec.size()!=HT3JetVec.size() || HT3JetHTMaskvec.size()!=HT3JetVec.size() || HT3JetHadronFlavorvec.size()!=HT3JetVec.size()) 
	std::cout<<" HT3 vectors not consistent in size "<<endl;

      if(MHT3JetCSVvec.size()!=MHT3JetVec.size() || MHT3JetHTMaskvec.size()!=MHT3JetVec.size() || MHT3JetHadronFlavorvec.size()!=MHT3JetVec.size()) 
	std::cout<<" MHT3 vectors not consistent in size "<<endl;
*/
      /*
      if(Print){
	for(unsigned int i=0;i<MHT3JetVec.size();i++){
	  std::cout<<"*** vector is ordered ***"<<" i "<<i<<" pt "<<MHT3JetVec[i].Pt()<<" csv "<<MHT3JetCSVvec[i]<<" HTMask "<<MHT3JetHTMaskvec[i]<<" HadronFlavor "<<MHT3JetHadronFlavorvec[i]<<" eta "<<MHT3JetVec[i].Eta()<<" MHT_Lor_pt(i) "<<MHT3JetLorentzVec[i].Pt()<<endl;
	}
      }
    */  

      for(unsigned int i=0;i<HT3JetVec.size();i++){
	newHT+=HT3JetVec[i].Pt();
      }
      for(unsigned int i=0;i<MHT3JetVec.size();i++){
	newMHT3Vec-=MHT3JetVec[i];
      }
      newMHT=newMHT3Vec.Pt();
      newMHTPhi=newMHT3Vec.Phi();
      
      newNJets = HT3JetVec.size();
      if(HT3JetVec.size()>0)
	newDphi1=fabs(TVector2::Phi_mpi_pi(HT3JetVec[0].Phi() - newMHTPhi));
      if(HT3JetVec.size()>1)
	newDphi2=fabs(TVector2::Phi_mpi_pi(HT3JetVec[1].Phi() - newMHTPhi));
      if(HT3JetVec.size()>2)
	newDphi3=fabs(TVector2::Phi_mpi_pi(HT3JetVec[2].Phi() - newMHTPhi));
      if(HT3JetVec.size()>3)
	newDphi4=fabs(TVector2::Phi_mpi_pi(HT3JetVec[3].Phi() - newMHTPhi));
      //      std::cout<<" jet_size "<<Jets->size()<<" HT3 "<< HT3JetVec.size()<<" Dphi1 "<<newDphi1<<" Dphi2 "<<newDphi2<<" Dphi3 "<<newDphi3<<"  Dphi4 "<<newDphi4<<endl;
      for(unsigned int i=0;i<HT3JetVec.size();i++){
	if(HT3JetCSVvec[i]>csvForBtag)
	  newBTags++;
      }
    }    

    //    if(Jets->size() !=MHT3JetVec.size())
    //std::cout<<" jets "<<Jets->size()<<" MHT3 "<<MHT3JetVec.size()<<" btags "<<BTags<<" newBTags "<<newBTags<<endl;
      //  if(entry % 3 != 0) return kTRUE;
      
    //if(HTgen_" vector is orderedcut > 0.01) if(madHT > HTgen_cut) return kTRUE;
    //*AR, 180101-minHT_=300,minMHT_=250,minNJets_=1.5,deltaPhi1_=0.5,deltaPhi2_=0.5,deltaPhi3_=0.3,deltaPhi4_=0.3
    //*AR, 180101-minMHT_=250 here as we are also deriving SFs for low MHT, 3 bins.
    if(JECSys){
      //      if(newNJets==2 && (newHT<minHT_ || newMHT< minMHT_ || newNJets < minNJets_  ))
      //std::cout<<" fail "<<" old jet "<<NJets<<" old HT "<< HT<<" new HT "<<newHT<<" old MHT "<<MHT<<" new MHT "<<newMHT<<endl;
      //if(newNJets==2 && !(newHT<minHT_ || newMHT< minMHT_ || newNJets < minNJets_  ))
	//	std::cout<<" **pass** "<<" old jet "<<NJets<<" old HT "<< HT<<" new HT "<<newHT<<" old MHT "<<MHT<<" new MHT "<<newMHT<<" dphi1 "<<newDphi1<<" dphi2 "<<newDphi2<<" dphi3 "<<newDphi3<<" dphi4 "<<newDphi4<<endl;
      if(newHT<minHT_ || newMHT< minMHT_ || newNJets < minNJets_  ) return kTRUE;
      if(useDeltaPhiCut == 1) if(newDphi1 < deltaPhi1_ || newDphi2 < deltaPhi2_ || newDphi3 < deltaPhi3_ || newDphi4 < deltaPhi4_) return kTRUE;
      if(useDeltaPhiCut == -1) if(!(newDphi1 < deltaPhi1_ || newDphi2 < deltaPhi2_ || newDphi3 < deltaPhi3_ || newDphi4 < deltaPhi4_)) return kTRUE;
    }
    else{
      if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
      if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
      if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
    }

    //if(newNJets==2)
    //std::cout<<" there are 2 jets "<<endl;

    GenMuonsNum_ = GenMuons->size();
    GenElectronsNum_ = GenElectrons->size();

    //*AR, 180101- Only consider events which have atleast one gen electron or one gen muon.
    if(GenMuonsNum_ + GenElectronsNum_ == 0) return kTRUE;

    if(JECSys){
      if(useCombinedBins){ //useCombinedBins=false
        Bin_ = SearchBins_->GetCombinedBinNumber(newHT,newMHT,newNJets);
      }else{ 
        Bin_ = SearchBins_->GetBinNumber(newHT,newMHT,newNJets,newBTags);
	//	if(newNJets==2)
	//std::cout<<" Bin_ "<<Bin_<<endl;
      }    
      if(Bin_ > 900) return kTRUE;
    }
    else{
      if(useCombinedBins){ //useCombinedBins=false
        Bin_ = SearchBins_->GetCombinedBinNumber(HT,MHT,NJets);
      }else{ 
        Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTags);
      }    
      if(Bin_ > 900) return kTRUE;
    }
    // TH1 cannot properly deal with negative bin contents
    // At most 1% difference in SFs expected (rare BGs only)
    //if(Weight < 0) return kTRUE;
    //* AR-20180115-As following loop is not executing, it is not modified to account for JECSys effect.
    if(doTopPtReweighting){ //doTopPtReweighting=false
      if(GenParticles->size() != GenParticles_PdgId->size()){
	std::cout << "Cannot do top-pT reweighting!"<< std::endl; 
      }else{
	for(unsigned iGen = 0; iGen < GenParticles->size(); iGen++){
	  if(std::abs(GenParticles_PdgId->at(iGen)) == 6){
	    topPt.push_back(GenParticles->at(iGen).Pt());
	  }
	} //* AR-180101--end of for loop
	
	// https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting#Example
	// Numbers outdated! Use latest numbers from twiki
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
      } //end of else of "if(GenParticles->size() != GenParticles_PdgId->size())"

        // Normalization tested on SingleLept and DiLept samples (varies from ~98.9x-99.0x)
      topPtSF /= 0.99;
      Weight *= topPtSF;
    } //end of "if(doTopPtReweighting)"
    double madHTcut=0.0;
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());
    //std::cout<<" survived event "<< " entry "<<entry<<" currentTree "<<currentTree<<endl;

    //treeName = " "
    //**AR-Nov3,2017-Loop below "if(currentTree != treeName)" only executes for every new tree in filelist and not for every event. So variables to be checked for every event should be outside this loop.
    if(currentTree != treeName){
        treeName = currentTree;
	//std::cout<<" treeName "<<treeName<<endl;
        TObjArray *optionArray = currentTree.Tokenize("/");
        currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
	currentFile = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
	//	std::cout<<" currFileName "<<currFileName<<endl;
	//
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

	sprintf(SkimFile,"root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_SLm/%s",skimName.c_str());
	//	std::cout<<" currFileName "<<currFileName<<" skimname "<<skimName<<endl;

	//* AR-20180115-As following loop is not executing, it is not modified to account for JECSys effect.
        if(doISRcorr){ //doISRcorr=false
	  h_njetsisr = (TH1*) fChain->GetCurrentFile()->Get("NJetsISR");
	  if(isrcorr!=0){
            delete isrcorr;
            isrcorr = 0;
	  }
	  isrcorr = new ISRCorrector();
	  isrcorr->SetWeights(h_isr,h_njetsisr);
        }
	
        if(doBTagCorr){
	  if(btagcorr!=0){
            delete btagcorr;
            btagcorr = 0;
	  }
	  //* AR-20180101- Creates an instance of class BTagCorrector for every new tree of the filelist     
	  btagcorr = new BTagCorrector();
	  //  std::cout<<"***Seg Vio***"<<std::endl;
	  
	  TFile *skimFile = TFile::Open(SkimFile, "READ");
	  btagcorr->SetEffs(skimFile);
	  //	    std::cout<<" skimFile "<<skimFile<<endl;
	  btagcorr->SetCalib(path_bTagCalib);        
	  //if(runOnSignalMC){
	  //  btagcorr->SetCalibFastSim(path_bTagCalibFastSim);
	  //  btagcorr->SetFastSim(true);
	  //}
	  //else
	  btagcorr->SetFastSim(false);
        }
	
        /*if(runOnSignalMC){
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
        }*/
    } // end of "if(currentTree != treeName)"

    /*if(runOnSignalMC){
        TH1F *nEventProc = (TH1F*)fChain->GetCurrentFile()->Get("nEventProc");
        TH1F *nEventNeg = (TH1F*)fChain->GetCurrentFile()->Get("nEventNeg");
        nEvtsTotal = nEventProc->GetBinContent(1) - 2*nEventNeg->GetBinContent(1);

        xsec = 0;
        for (std::vector<std::pair<double, double>>::iterator it = xsecs->begin() ; it != xsecs->end(); ++it){
            if(std::abs(SusyMotherMass - it->first) < 0.1){
            xsec = it->second;
            break;
            }
        }
        if(xsec < 1e-10){
            std::cout<<"No valid xsec found!"<<std::endl;
            return kTRUE;
        }

        Weight = xsec / nEvtsTotal;
        if(Weight < 0) Weight *= -1;
    }   
    */
    //*AR-Nov27,2017-following if loop was introduced to ignore negative weight events. After ignoring those, SFSR for exotic and single top samples are found to be better in agreement with Simon's results
    if(Weight < 0)
      return kTRUE;
    //      std::cout<<" entry "<<entry<<" negative event weight "<<endl;

    if(currentFile.find("TTJets_SingleLeptFromTbar")!=string::npos || currentFile.find("TTJets_SingleLeptFromT")!=string::npos || currentFile.find("DiLept")!=string::npos){
      madHTcut=600;
      if(madHT > madHTcut){
	//	std::cout<<" currentTree "<<currentTree<<" entry "<<entry<<" madHT "<<madHT<< " &&&not passed&&& "<<endl;
	return kTRUE;
      }
    }
    //    std::cout<<" passed "<<" entry "<<entry<<" madHT "<<madHT<<endl;
    //* AR-20180115-As following loop is not executing, it is not modified to account for JECSys effect.   
    if(doISRcorr){ //false
      w_isr = isrcorr->GetCorrection(NJetsISR);
      Weight *= w_isr;
    }
    
    if(doBTagCorr){
      if(JECSys)
	bTagProb = btagcorr->GetCorrections(MHT3JetLorentzVec,MHT3JetHadronFlavorvec,MHT3JetHTMaskvec);
      else
	bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
      if(useCombinedBins){
	bTagBins = {Bin_, Bin_, Bin_, Bin_};
      }
      else{
	if(JECSys)
	  bTagBins = {SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,0), SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,1), SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,2), newNJets < 3 ? 999 : SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,3)};
	else
	  bTagBins = {SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,0), SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,1), SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,2), NJets < 3 ? 999 : SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,3)};
      }  
    }
    else{
      bTagProb = {1, 0, 0, 0};
      bTagBins = {Bin_, 0, 0, 0};
    }
    
    //if(runOnSignalMC){
        //  //Account for efficiency of JetID since we cannot apply it on fastSim
        // Weight *= 0.99;
    //}

    //if(useTriggerEffWeight){
        //  if(runOnSignalMC){
        //    Weight *= GetSignalTriggerEffWeight(MHT);
        //  }else{
        //    Weight *= GetTriggerEffWeight(MHT);
        //  }
    //}

    if(doPUreweighting){ // doPUreweighting is false
        w_pu = puhist->GetBinContent(puhist->GetXaxis()->FindBin(min(TrueNumInteractions,puhist->GetBinLowEdge(puhist->GetNbinsX()+1))));
        Weight *= w_pu;
    }

    // We are only interested in the GenLeptons that pass the acceptance, including isotrk veto! (i.e. abs(eta)<2.5, pT>5)
    for(unsigned i=0; i< GenElectrons->size(); i++){
        if(GenElectrons->at(i).Pt() > 5. && std::abs(GenElectrons->at(i).Eta()) < 2.5){
	  GenElectronsAcc.push_back(GenElectrons->at(i));
        }
    }
    for(unsigned i=0; i< GenMuons->size(); i++){
        if(GenMuons->at(i).Pt() > 5. && std::abs(GenMuons->at(i).Eta()) < 2.5){
            GenMuonsAcc.push_back(GenMuons->at(i));
        }
    }
    /*  
    for(unsigned i=0; i< Electrons->size(); i++){
      std::cout<<" i_reco "<<i<<" pt "<<Electrons->at(i).Pt()<<" eta "<<Electrons->at(i).Eta()<<endl;
    }
    *//*
    for(unsigned i=0; i< Muons->size(); i++){
      std::cout<<" i_reco "<<i<<" pt "<<Muons->at(i).Pt()<<" eta "<<Muons->at(i).Eta()<<endl;
    }
    */
    /*
    for(unsigned i=0; i< GenElectrons->size(); i++){
      std::cout<<" i_gen "<<i<<" pt "<<GenElectrons->at(i).Pt()<<" eta "<<GenElectrons->at(i).Eta()<<endl;
    }
    
*/
    GenMuonsAccNum_ = GenMuonsAcc.size();
    GenElectronsAccNum_ = GenElectronsAcc.size();
    //*AR-180101---Skip the event if there is no electron and no muon with pT>5 and abs(eta)<2.5
    if(GenMuonsAccNum_ + GenElectronsAccNum_ == 0) return kTRUE;

    //*AR-180101---Call first two leading muons or electrons by special names
    //Define some helpful variables
    if(GenMuonsAccNum_ > 0){
        GenMuonsAccPt_ = GenMuonsAcc.at(0).Pt();
        GenMuonsAccEta_ = GenMuonsAcc.at(0).Eta();
        if(GenMuonsAccNum_ > 1){
            GenMuonsAccPt2_ = GenMuonsAcc.at(1).Pt();
            GenMuonsAccEta2_ = GenMuonsAcc.at(1).Eta();
        }
    }
    if(GenElectronsAccNum_ > 0){
        GenElectronsAccPt_ = GenElectronsAcc.at(0).Pt();
        GenElectronsAccEta_ = GenElectronsAcc.at(0).Eta();
        if(GenElectronsAccNum_ > 1){
            GenElectronsAccPt2_ = GenElectronsAcc.at(1).Pt();
            GenElectronsAccEta2_ = GenElectronsAcc.at(1).Eta();
        }
    }

    ElectronsNum_ = Electrons->size();
    MuonsNum_ = Muons->size();

    // get isoTrack collection from full TAP collection
    //*AR-180101---Skips event if number of isolated tracks obtained from TAP selection and those provided by isotrack collection in tree are not same 
    //*AR-180102---Q. isolated track needs track isolation<0.2 and mT<100 for electrons, muons and track isolation<0.1 and mT<100 for pions, why there is no pT cut >5 for leptonic track and >10 for hadronic track?
    isoTracksNum = isoMuonTracksNum + isoPionTracksNum + isoElectronTracksNum;

    for(unsigned i=0; i< TAPElectronTracks->size(); i++){
        if(TAPElectronTracks_trkiso->at(i) < 0.2 && TAPElectronTracks_mT->at(i) < 100){
            isoElectronTracks.push_back(TAPElectronTracks->at(i));
        }
    }
    if(isoElectronTracks.size() != (unsigned) isoElectronTracksNum){
        std::cout << "WARNING! Number of isoElectronTracks is not correct! Skipping event." << std::endl;
        return kTRUE;
    }

    for(unsigned i=0; i< TAPMuonTracks->size(); i++){
        if(TAPMuonTracks_trkiso->at(i) < 0.2 && TAPMuonTracks_mT->at(i) < 100){
            isoMuonTracks.push_back(TAPMuonTracks->at(i));
        }      
    }
    if(isoMuonTracks.size() != (unsigned) isoMuonTracksNum){
        std::cout << "WARNING! Number of isoMuonTracks is not correct! Skipping event." << std::endl;
        return kTRUE;
    }

    for(unsigned i=0; i< TAPPionTracks->size(); i++){
        if(TAPPionTracks_trkiso->at(i) < 0.1 && TAPPionTracks_mT->at(i) < 100){
            isoPionTracks.push_back(TAPPionTracks->at(i));
        }      
    }
    if(isoPionTracks.size() != (unsigned) isoPionTracksNum){
        std::cout << "WARNING! Number of isoPionTracks is not correct! Skipping event." << std::endl;
        return kTRUE;
    }

    // Match iso leptons/tracks to gen leptons
    // Apply SFs only to prompts
    // *AR-180101---Reco objects which match to gen obects within acceptane, call them by special names
    // *AR-180102---matching is done in terms of delta_pT/pT<0.1 and deltaR<0.03 for both isolated reco electrons and reco isolated tracks 
    for(unsigned i=0; i< GenElectronsAccNum_; i++){
      bool matched = false;
        for(unsigned j=0; j< ElectronsNum_; j++){
            if(std::abs(GenElectronsAcc.at(i).Pt() - Electrons->at(j).Pt()) / GenElectronsAcc.at(i).Pt() < 0.1
                && deltaR(GenElectronsAcc.at(i).Eta(), GenElectronsAcc.at(i).Phi(), Electrons->at(j).Eta(), Electrons->at(j).Phi()) < 0.03){
                if(ElectronsPromptNum_==0){
                    ElectronsPromptPt_ = GenElectronsAcc.at(i).Pt();
                    ElectronsPromptEta_ = GenElectronsAcc.at(i).Eta();
                    ElectronsPromptMatch_ = i;
                }else if(ElectronsPromptNum_==1){
                    ElectronsPromptPt2_ = GenElectronsAcc.at(i).Pt();
                    ElectronsPromptEta2_ = GenElectronsAcc.at(i).Eta();
                    ElectronsPromptMatch2_ = i;
                }
                matched = true;
                ElectronsPromptNum_++;
                break; //*AR if for a given gen object, a matching reco object is found, skip looping over remaining reco objects for match
            }// end of if(std::abs(GenElect...)
        } //end of loop over ElectronsNum_
        if(matched) continue; //* AR,180101---if a matching reco electron is found don't need to check for isoElectronTracks, hence skip rest of this loop and move to next gen electron 

        for(int j=0; j< isoElectronTracksNum; j++){
            if(std::abs(GenElectronsAcc.at(i).Pt() - isoElectronTracks.at(j).Pt()) / GenElectronsAcc.at(i).Pt() < 0.1
                && deltaR(GenElectronsAcc.at(i).Eta(), GenElectronsAcc.at(i).Phi(), isoElectronTracks.at(j).Eta(), isoElectronTracks.at(j).Phi()) < 0.03){
                if(ElectronTracksPromptNum_==0){
                    ElectronTracksPromptPt_ = GenElectronsAcc.at(i).Pt();
                    ElectronTracksPromptEta_ = GenElectronsAcc.at(i).Eta();
                    ElectronTracksPromptMatch_ = i;
                }else if(ElectronTracksPromptNum_==1){
                    ElectronTracksPromptPt2_ = GenElectronsAcc.at(i).Pt();
                    ElectronTracksPromptEta2_ = GenElectronsAcc.at(i).Eta();
                    ElectronTracksPromptMatch2_ = i;
                }
                ElectronTracksPromptNum_++;
                break;
            }
        }
    } //*AR-180101-end of loop over gen electrons
    //*AR-180101-For muons as well same procedure is repeated
    for(unsigned i=0; i< GenMuonsAccNum_; i++){
        bool matched = false;
        for(unsigned j=0; j< MuonsNum_; j++){
            if(std::abs(GenMuonsAcc.at(i).Pt() - Muons->at(j).Pt()) / GenMuonsAcc.at(i).Pt() < 0.1
                && deltaR(GenMuonsAcc.at(i).Eta(), GenMuonsAcc.at(i).Phi(), Muons->at(j).Eta(), Muons->at(j).Phi()) < 0.03){
                if(MuonsPromptNum_==0){
                    MuonsPromptPt_ = GenMuonsAcc.at(i).Pt();
                    MuonsPromptEta_ = GenMuonsAcc.at(i).Eta();
                    MuonsPromptMatch_ = i;
                }else if(MuonsPromptNum_==1){
                    MuonsPromptPt2_ = GenMuonsAcc.at(i).Pt();
                    MuonsPromptEta2_ = GenMuonsAcc.at(i).Eta();
                    MuonsPromptMatch2_ = i;
                }
                matched = true;
                MuonsPromptNum_++;
                break;
            }//end of if condition with deltaR matching
        } //end of loop over j
        if(matched) continue;

        for(int j=0; j< isoMuonTracksNum; j++){
            if(std::abs(GenMuonsAcc.at(i).Pt() - isoMuonTracks.at(j).Pt()) / GenMuonsAcc.at(i).Pt() < 0.1
                && deltaR(GenMuonsAcc.at(i).Eta(), GenMuonsAcc.at(i).Phi(), isoMuonTracks.at(j).Eta(), isoMuonTracks.at(j).Phi()) < 0.03){
                if(MuonTracksPromptNum_==0){
                    MuonTracksPromptPt_ = GenMuonsAcc.at(i).Pt();
                    MuonTracksPromptEta_ = GenMuonsAcc.at(i).Eta();
                    MuonTracksPromptMatch_ = i;
                }else if(MuonTracksPromptNum_==1){
                    MuonTracksPromptPt2_ = GenMuonsAcc.at(i).Pt();
                    MuonTracksPromptEta2_ = GenMuonsAcc.at(i).Eta();
                    MuonTracksPromptMatch2_ = i;
                }
                MuonTracksPromptNum_++;
                break;
            }
        }
    }

    if(GenMuonsAccNum_ < MuonsPromptNum_ + MuonTracksPromptNum_ || GenElectronsAccNum_ < ElectronsPromptNum_ + ElectronTracksPromptNum_){
        std::cout<<"Mu:"<<GenMuonsAccNum_<<"->"<<MuonsPromptNum_<<"+"<<MuonTracksPromptNum_<<std::endl;
        std::cout<<"El:"<<GenElectronsAccNum_<<"->"<<ElectronsPromptNum_<<"+"<<ElectronTracksPromptNum_<<std::endl;
        std::cout<<"Matching not successful. Skipping event."<<std::endl;
        return kTRUE;
    }

    int nLoops = 1;
    if(doBTagCorr){
      if(JECSys) 
	nLoops = (newNJets == 2 ? 3 : 4);
      else
	nLoops = (NJets == 2 ? 3 : 4);
    }
    for(int i = 0; i < nLoops; i++){
    	double WeightBtagProb = Weight*bTagProb.at(i);
    	unsigned bTagBin = bTagBins.at(i);
	
	//*AR, Nov20,2017- Checks if a gen muon is found and gen electron is not found
	//*AR, Nov20,2017- input histograms for deriving SF are only filled when there is electron /muon within acceptance pt>5 and |eta|<2.5
	if(GenMuonsAccNum_ == 1 && GenElectronsAccNum_ == 0){
	  h_mu_nOnePrompt_etaPt->Fill(GenMuonsAccEta_, GenMuonsAccPt_, WeightBtagProb);
	  h_mu_nOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	  if(IsoSys){
	    //std::cout<<" SF "<<GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))<<" SF Unc "<<GetSFUnc(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01)<<endl;
	    if(SysUp)
	      isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))+GetSFUnc(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	    if(SysDn)
	      isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))-GetSFUnc(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	  }
	  else
	    isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_));

	  if(IDSys){
	    //	    std::pair<double, double> MyPair;
	    //MyPair=EvalSF(h_muIDSF,GenMuonsAccPt_, std::abs(GenMuonsAccEta_));
	    //	    std::cout<<" pt "<<GenMuonsAccPt_<<" eta "<<GenMuonsAccEta_<<" MuPair_1 "<<MyPair.first<<" MuPair_2 "<<MyPair.second<<endl;
	    if(SysUp)
	      recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))+GetSFUnc(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	    if(SysDn)
	      recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))-GetSFUnc(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	  }
	  else
	    recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_));
	  
	  if(TrackRecoSys){
	    if(GenMuonsAccPt_ > 10){
	      if(SysUp)
		trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_)+GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta_,0.01);
	      
	      if(SysDn){
		//	std::pair<double, double> MyPair;
		//		MyPair=EvalSF(h_muTrkHighPtSF, GenMuonsAccEta_);
		//		std::cout<<" eta "<<GenMuonsAccEta_<<"MuPair_1 "<<MyPair.first<<" MuPair_2 "<<MyPair.second<<" totUnc "<<GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta_,0.01)<<endl;	
		trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_)-GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta_,0.01);
	      }
	    }
	    else{
	      if(SysUp)
		trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_)+GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta_,0.01);
	      if(SysDn)
		trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_)-GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta_,0.01);
	    }
	  }
	  else{
	    if(GenMuonsAccPt_ > 10)
	      trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_);
	    else
	      trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_);
	  }
	  
	  
	  //*AR, Nov20,2017-  three possible cases are considered here: 1] Reco level muon is found(applied isoSF,recoSF and trackingSF) 2] Reco level muon is not found but isotrack veto(when applied) counted one isolated muon track(applied only trackingSF) 3] Reco level muon is not found and also no isolated muon track was recorded either beacause isolated track veto was not applied so number of tracks were not counted or even after applying isolated track veto somehow no isolated muon track was recorded. (no SF is applied)
	  
	  //*AR, 20180102---A set of events with identified, isolated and reconstructed electrons/muons and a set of events with isolated electron/isolated muon tracks can be considered as two different subsets of total events with no overlap. Becuase the second subset is constructed out of events which do not fall in first subset. Hence for a reconstructed ele/muon three scale factors come into picture while for reconstructed tracks only one scale factor.
	  
	  //*AR, 20180102---Thus when isotrack veto is applied, lost e event is one which has reco electron=0 and isolated electron track=0. When isotrack veto is not applied,lost e event is one with reco electron=0 
	  if(MuonsPromptNum_ == 1){
	    double WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF;
	    
	    h_mu_nFoundOnePrompt_etaPt->Fill(GenMuonsAccEta_, GenMuonsAccPt_, WeightBtagProb);
	    h_mu_nFoundOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	    h_mu_nFoundOnePrompt_SF_etaPt->Fill(GenMuonsAccEta_, GenMuonsAccPt_, WeightCorr);
	    h_mu_nFoundOnePrompt_SF_SB->Fill(bTagBin, WeightCorr);
	  }else if(includeIsotrkVeto && MuonsPromptNum_ == 0 && MuonTracksPromptNum_ == 1){
	    double WeightCorr = WeightBtagProb * trackingSF;
	    
	    h_mu_nFoundOnePrompt_etaPt->Fill(GenMuonsAccEta_, GenMuonsAccPt_, WeightBtagProb);
	    h_mu_nFoundOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	    h_mu_nFoundOnePrompt_SF_etaPt->Fill(GenMuonsAccEta_, GenMuonsAccPt_, WeightCorr);
	    h_mu_nFoundOnePrompt_SF_SB->Fill(bTagBin, WeightCorr);
	  }else if(MuonsPromptNum_ == 0 && (!includeIsotrkVeto || MuonTracksPromptNum_ == 0)){
	    //*AR, 20180102- if IsotrkVeto is applied, following histograms filled only when there is no reco muon. If IsotrkVeto is not applied, following histograms filled when there is no muon and no isolated track
	    h_mu_nLostOnePrompt_etaPt->Fill(GenMuonsAccEta_, GenMuonsAccPt_, WeightBtagProb);
	    h_mu_nLostOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	  }else{
	    std::cout<<"SingleMu: "<<MuonsPromptNum_<<"+"<<MuonTracksPromptNum_<<std::endl;
	  }
    	} //end of if(GenMuonsAccNum_ == 1 && GenElectronsAccNum_ == 0)
	
    	if(GenMuonsAccNum_ == 0 && GenElectronsAccNum_ == 1){
	  h_el_nOnePrompt_etaPt->Fill(GenElectronsAccEta_, GenElectronsAccPt_, WeightBtagProb);
	  h_el_nOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	  //	  std::cout<<" h_el_nOnePrompt_SB filled "<<" WeightBtagProb "<<WeightBtagProb<<endl;
	  if(IsoSys){
	    if(SysUp)
	      isoSF = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))+GetSFUnc(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	    if(SysDn)
	      isoSF = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))-GetSFUnc(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	  }
	  else
	    isoSF = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_));

	  if(IDSys){
	    //	    std::pair<double, double> MyPair;
	    //MyPair=EvalSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_));
	    //std::cout<<" pt "<<GenElectronsAccPt_<<" eta "<<GenElectronsAccEta_<<" ElePair_1 "<<MyPair.first<<" ElePair_2 "<<MyPair.second<<endl;
	    
	    if(SysUp)
	      recoSF = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))+GetSFUnc(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	    if(SysDn)
	      recoSF = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))-GetSFUnc(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	  }
	  else
	    recoSF = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_));
	  //*AR-180306---According to lepton SF twiki, 1% systematics should be added on top for electrons with pt<20 or >80 GeV, as Scale factors are found to be flat with pT. Nevertheless the pT dependence is hard to verify below 20GeV and above 80 GeV.
	  if(TrackRecoSys){
	    if(GenElectronsAccPt_<20 || GenElectronsAccPt_>80){
	      if(SysUp)
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.01);
	      if(SysDn)
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.01);
	    }
	    else{
	      if(SysUp)
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.0);
	      if(SysDn){
		/*		
		std::pair<double, double> MyPair;
		MyPair=EvalSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_);
		std::cout<<" eta "<<GenElectronsAccEta_<<"ElecPair_1 "<<MyPair.first<<" ElecPair_2 "<<MyPair.second<<" totUnc "<<GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.0)<<endl;
*/
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.0);
	      }
	    }
	  }
	  else
	    trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_); 
	  
	  if(ElectronsPromptNum_ == 1){
	    double WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF;
	    
	    h_el_nFoundOnePrompt_etaPt->Fill(GenElectronsAccEta_, GenElectronsAccPt_, WeightBtagProb);
	    h_el_nFoundOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	    //std::cout<<" h_el_nFoundOnePrompt_SB filled "<<" WeightBtagProb "<<WeightBtagProb<<endl;
	    
	    h_el_nFoundOnePrompt_SF_etaPt->Fill(GenElectronsAccEta_, GenElectronsAccPt_, WeightCorr);
	    h_el_nFoundOnePrompt_SF_SB->Fill(bTagBin, WeightCorr);
	  }else if(includeIsotrkVeto && ElectronsPromptNum_ == 0 && ElectronTracksPromptNum_ == 1){
	    double WeightCorr = WeightBtagProb * trackingSF;
	    
	    h_el_nFoundOnePrompt_etaPt->Fill(GenElectronsAccEta_, GenElectronsAccPt_, WeightBtagProb);
	    h_el_nFoundOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	    h_el_nFoundOnePrompt_SF_etaPt->Fill(GenElectronsAccEta_, GenElectronsAccPt_, WeightCorr);
	    h_el_nFoundOnePrompt_SF_SB->Fill(bTagBin, WeightCorr);
	  }else if(ElectronsPromptNum_ == 0 && (!includeIsotrkVeto || ElectronTracksPromptNum_ == 0)){
	    h_el_nLostOnePrompt_etaPt->Fill(GenElectronsAccEta_, GenElectronsAccPt_, WeightBtagProb);
	    h_el_nLostOnePrompt_SB->Fill(bTagBin, WeightBtagProb);
	  }else{
	    std::cout<<"SingleElec: "<<ElectronsPromptNum_<<"+"<<ElectronTracksPromptNum_<<std::endl;
	  }	
    	}

        if(GenMuonsAccNum_ == 2 && GenElectronsAccNum_ == 0){
            h_di_nTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);

	    if(IsoSys){
	      if(SysUp)
		isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))+GetSFUnc(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	      if(SysDn)
		isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))-GetSFUnc(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	    }
	    else
	      isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_));
	    

	  if(IDSys){
	    if(SysUp)
	      recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))+GetSFUnc(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	    if(SysDn)
	      recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))-GetSFUnc(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	  }
	  else
	    recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_));


	  if(TrackRecoSys){
	    if(GenMuonsAccPt_ > 10){
	      if(SysUp)
		trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_)+GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta_,0.01);
	      if(SysDn)
		trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_)-GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta_,0.01);
	    }
	    else{
	      if(SysUp)
		trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_)+GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta_,0.01);
	      if(SysDn)
		trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_)-GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta_,0.01);
	    }
	  }
	  else{
	    if(GenMuonsAccPt_ > 10)
	      trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_);
	    else
	      trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_);
	  }
	  
	  if(IsoSys){
	    if(SysUp)
		isoSF2 = GetSF(h_muIsoSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_))+GetSFUnc(h_muIsoSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_),0.01);
	      if(SysDn)
		isoSF2 = GetSF(h_muIsoSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_))-GetSFUnc(h_muIsoSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_),0.01);
	    }
	    else
	      isoSF2 = GetSF(h_muIsoSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_));

	    if(IDSys){
	      if(SysUp)
		recoSF2 = GetSF(h_muIDSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_))+GetSFUnc(h_muIDSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_),0.01);
	      if(SysDn)
		recoSF2 = GetSF(h_muIDSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_))-GetSFUnc(h_muIDSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_),0.01);
	    }
	    else
	      recoSF2 = GetSF(h_muIDSF, GenMuonsAccPt2_, std::abs(GenMuonsAccEta2_));
	    
	    if(TrackRecoSys){
	      if(GenMuonsAccPt2_ > 10){
		if(SysUp)
		  trackingSF2 = GetSF(h_muTrkHighPtSF, GenMuonsAccEta2_)+GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta2_,0.01);
		if(SysDn)
		  trackingSF2 = GetSF(h_muTrkHighPtSF, GenMuonsAccEta2_)-GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta2_,0.01);
	      }
	      else{
		if(SysUp)
		  trackingSF2 = GetSF(h_muTrkLowPtSF, GenMuonsAccEta2_)+GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta2_,0.01);
		if(SysDn)
		  trackingSF2 = GetSF(h_muTrkLowPtSF, GenMuonsAccEta2_)-GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta2_,0.01);
	      }
	    }
	    else{
	      if(GenMuonsAccPt_ > 10)
		trackingSF2 = GetSF(h_muTrkHighPtSF, GenMuonsAccEta2_);
	      else
		trackingSF2 = GetSF(h_muTrkLowPtSF, GenMuonsAccEta2_);
	    }
	    
	    if(MuonsPromptNum_ == 2){
                double WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && MuonsPromptNum_ == 1 && MuonTracksPromptNum_ == 1){
                double WeightCorr = 1;
		//*AR, Nov20,2017-MuonsPromptMatch_ gives the index of a reco muon which is matched to gen muon.   
             if(MuonsPromptMatch_ == 0)  WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF * trackingSF2;
                else WeightCorr = WeightBtagProb * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && MuonsPromptNum_ == 0 && MuonTracksPromptNum_ == 2){
                double WeightCorr = WeightBtagProb * trackingSF * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(MuonsPromptNum_ == 1 && (!includeIsotrkVeto || MuonTracksPromptNum_ == 0)){
                double WeightCorr = 1;
                if(MuonsPromptMatch_ == 0)  WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF;
                else WeightCorr = WeightBtagProb * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nOneFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nOneFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && MuonsPromptNum_ == 0 && MuonTracksPromptNum_ == 1){
                double WeightCorr = 1;
                if(MuonsPromptMatch_ == 0)  WeightCorr = WeightBtagProb * trackingSF;
                else WeightCorr = WeightBtagProb * trackingSF2;

                h_di_nOneFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nOneFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(MuonsPromptNum_ == 0 && (!includeIsotrkVeto || MuonTracksPromptNum_ == 0)){
                h_di_nLostTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
            }else{
                std::cout<<"DiMu: "<<GenMuonsAccNum_<<"->"<<MuonsPromptNum_<<"+"<<MuonTracksPromptNum_<<std::endl;
            }       
        }

        if(GenMuonsAccNum_ == 0 && GenElectronsAccNum_ == 2){
	  h_di_nTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
	  
	  if(IsoSys){
	    if(SysUp)
	      isoSF = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))+GetSFUnc(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	    if(SysDn)
	      isoSF = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))-GetSFUnc(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	  }
	  else
	    isoSF = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_));


	  if(IDSys){
	    if(SysUp)
	      recoSF = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))+GetSFUnc(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	    if(SysDn)
	      recoSF = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))-GetSFUnc(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	  }
	  else
	    recoSF = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_));

	  if(TrackRecoSys){
	    if(GenElectronsAccPt_<20 || GenElectronsAccPt_>80){
	      if(SysUp)
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.01);
	      if(SysDn)
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.01);
	    }
	    else{
	      if(SysUp)
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.0);
	      if(SysDn)
		trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.0);
	    }
	  }
	  else
	    trackingSF = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_); 

 
	  if(IsoSys){
	    if(SysUp)
	      isoSF2 = GetSF(h_elecIsoSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_))+GetSFUnc(h_elecIsoSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_),0.0);
	    if(SysDn)
	      isoSF2 = GetSF(h_elecIsoSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_))-GetSFUnc(h_elecIsoSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_),0.0);
	  }
	  else
	    isoSF2 = GetSF(h_elecIsoSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_));


	  if(IDSys){
	    if(SysUp)
	      recoSF2 = GetSF(h_elecIDSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_))+GetSFUnc(h_elecIDSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_),0.0);
	    if(SysDn)
	      recoSF2 = GetSF(h_elecIDSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_))-GetSFUnc(h_elecIDSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_),0.0);
	  }
	  else
	    recoSF2 = GetSF(h_elecIDSF, GenElectronsAccPt2_, std::abs(GenElectronsAccEta2_));


	  if(TrackRecoSys){
	    if(GenElectronsAccPt2_<20 || GenElectronsAccPt2_>80){
	      if(SysUp)
		trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_,0.01);
	      if(SysDn)
		trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_,0.01);
	    }
	    else{
	      if(SysUp)
		trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_,0.0);
	      if(SysDn)
		trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_,0.0);
	    }
	  }
	  else
	    trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta2_, GenElectronsAccPt2_); 

	  
	  if(ElectronsPromptNum_ == 2){
                double WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && ElectronsPromptNum_ == 1 && ElectronTracksPromptNum_ == 1){
                double WeightCorr = 1;
                if(MuonsPromptMatch_ == 0)  WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF * trackingSF2;
                else WeightCorr = WeightBtagProb * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && ElectronsPromptNum_ == 0 && ElectronTracksPromptNum_ == 2){
                double WeightCorr = WeightBtagProb * trackingSF * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(ElectronsPromptNum_ == 1 && (!includeIsotrkVeto || ElectronTracksPromptNum_ == 0)){
                double WeightCorr = 1;
                if(MuonsPromptMatch_ == 0)  WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF;
                else WeightCorr = WeightBtagProb * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nOneFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nOneFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && ElectronsPromptNum_ == 0 && ElectronTracksPromptNum_ == 1){
                double WeightCorr = 1;
                if(MuonsPromptMatch_ == 0)  WeightCorr = WeightBtagProb * trackingSF;
                else WeightCorr = WeightBtagProb * trackingSF2;

                h_di_nOneFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nOneFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(ElectronsPromptNum_ == 0 && (!includeIsotrkVeto || ElectronTracksPromptNum_ == 0)){
                h_di_nLostTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
            }else{
                std::cout<<"DiElec: "<<GenElectronsAccNum_<<"->"<<ElectronsPromptNum_<<"+"<<ElectronTracksPromptNum_<<std::endl;
            }   
        }

        if(GenMuonsAccNum_ == 1 && GenElectronsAccNum_ == 1){
            h_di_nTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
	    if(IsoSys){
	      if(SysUp)
		isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))+GetSFUnc(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	      if(SysDn)
		isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))-GetSFUnc(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	    }
	    else
	      isoSF = GetSF(h_muIsoSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_));


	    if(IDSys){
	      if(SysUp)
		recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))+GetSFUnc(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	      if(SysDn)
		recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_))-GetSFUnc(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_),0.01);
	    }
	    else
	      recoSF = GetSF(h_muIDSF, GenMuonsAccPt_, std::abs(GenMuonsAccEta_));
	    
	    if(TrackRecoSys){
	      if(GenMuonsAccPt_ > 10){
		if(SysUp)
		  trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_)+GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta_,0.01);
		if(SysDn)
		  trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_)-GetSFUnc(h_muTrkHighPtSF, GenMuonsAccEta_,0.01);
	      }
	      else{
		if(SysUp)
		  trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_)+GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta_,0.01);
		if(SysDn)
		  trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_)-GetSFUnc(h_muTrkLowPtSF, GenMuonsAccEta_,0.01);
	      }
	    }
	    else{
	      if(GenMuonsAccPt_ > 10)
		trackingSF = GetSF(h_muTrkHighPtSF, GenMuonsAccEta_);
	      else
		trackingSF = GetSF(h_muTrkLowPtSF, GenMuonsAccEta_);
	    }
	    
	    if(IsoSys){
	      if(SysUp)
		isoSF2 = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))+GetSFUnc(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	      if(SysDn)
		isoSF2 = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))-GetSFUnc(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	    }
	    else
	      isoSF2 = GetSF(h_elecIsoSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_));

	    if(IDSys){
	      if(SysUp)
		recoSF2 = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))+GetSFUnc(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	      if(SysDn)
		recoSF2 = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_))-GetSFUnc(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_),0.0);
	    }
	    else
	      recoSF2 = GetSF(h_elecIDSF, GenElectronsAccPt_, std::abs(GenElectronsAccEta_));
	    
	    if(TrackRecoSys){
	      if(GenElectronsAccPt_<20 || GenElectronsAccPt_>80){
		if(SysUp)
		  trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.01);
		if(SysDn)
		  trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.01);
	      }
	      else{
		if(SysUp)
		  trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)+GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.0);
		if(SysDn)
		  trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_)-GetSFUnc(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_,0.0);
	      }
	    }
	    else
	      trackingSF2 = GetSF(h_elecTrkSF, GenElectronsAccEta_, GenElectronsAccPt_); 
	    

            if(ElectronsPromptNum_ == 1 && MuonsPromptNum_ == 1){
                double WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && ((MuonsPromptNum_ == 1 && ElectronTracksPromptNum_ == 1) || (ElectronsPromptNum_ == 1 && MuonTracksPromptNum_ == 1))){
                double WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF * trackingSF2;
                if(ElectronsPromptNum_ == 1) WeightCorr = WeightBtagProb * trackingSF * isoSF2 * recoSF2 * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && MuonsPromptNum_ == 0 && ElectronsPromptNum_ == 0 && MuonTracksPromptNum_ == 1 && ElectronTracksPromptNum_ == 1){
                double WeightCorr = WeightBtagProb * trackingSF * trackingSF2;

                h_di_nTwoFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nTwoFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if((MuonsPromptNum_ == 1 && ElectronsPromptNum_ == 0 && (!includeIsotrkVeto || ElectronTracksPromptNum_ == 0)) || (ElectronsPromptNum_ == 1 && MuonsPromptNum_ == 0 && (!includeIsotrkVeto || MuonTracksPromptNum_ == 0))){
                double WeightCorr = WeightBtagProb * isoSF * recoSF * trackingSF;
                if(ElectronsPromptNum_ == 1) WeightCorr = WeightBtagProb * isoSF2 * recoSF2 * trackingSF2;

                h_di_nOneFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nOneFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(includeIsotrkVeto && ((MuonsPromptNum_ == 0 && ElectronsPromptNum_ == 0 && ElectronTracksPromptNum_ == 0 && MuonTracksPromptNum_ == 1) || (MuonsPromptNum_ == 0 && ElectronsPromptNum_ == 0 && MuonTracksPromptNum_ == 0 && ElectronTracksPromptNum_ == 1))){
                double WeightCorr = WeightBtagProb * trackingSF;
                if(ElectronTracksPromptNum_ == 1) WeightCorr = WeightBtagProb * trackingSF2;

                h_di_nOneFoundTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
                h_di_nOneFoundTwoPrompt_SF_SB->Fill(bTagBin, WeightCorr);
            }else if(MuonsPromptNum_ == 0 && ElectronsPromptNum_ == 0 && (!includeIsotrkVeto || (MuonTracksPromptNum_ == 0 && ElectronTracksPromptNum_ == 0))){
                h_di_nLostTwoPrompt_SB->Fill(bTagBin, WeightBtagProb);
            }else{
                std::cout<<"DiMuEl: "<<GenMuonsAccNum_<<"/"<<GenElectronsAccNum_<<"->"<<MuonsPromptNum_<<"+"<<MuonTracksPromptNum_<<"/"<<ElectronsPromptNum_<<"+"<<ElectronTracksPromptNum_<<std::endl;
            }
        }
    }

    return kTRUE;
}

void SFMaker::SlaveTerminate()
{
  std::cout<<"***SFMaker::SlaveTerminate***"<<std::endl;
  
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.

    //std::cout<<"--- QCD binning ---"<<std::endl;
    //SearchBinsQCD_->PrintUsed();

    std::cout<<"--- Search bins ---"<<std::endl;
    if(useCombinedBins){
        SearchBins_->PrintUsedCombined();  
    }else{
        SearchBins_->PrintUsed();  
    }
}

void SFMaker::Terminate()
{std::cout<<"***SFMaker::Terminate***"<<std::endl;
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.

    // Draw Options
    gStyle->SetPaintTextFormat("5.2f");
    gStyle->SetStatW(0.1);
    gStyle->SetStatH(0.1);
    gStyle->SetStatY(202);
    gStyle->SetTitleYOffset(1.3);

    gStyle->SetPalette(87);
    gStyle->SetMarkerSize(1.3);

    TFile *outPutFile = new TFile(fileName,"RECREATE");

    h_el_nOnePrompt_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_el_nOnePrompt_etaPt"));
    h_el_nOnePrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_el_nOnePrompt_SB"));
    h_el_nFoundOnePrompt_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_el_nFoundOnePrompt_etaPt"));
    h_el_nFoundOnePrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_el_nFoundOnePrompt_SB"));
    h_el_nFoundOnePrompt_SF_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_el_nFoundOnePrompt_SF_etaPt"));
    h_el_nFoundOnePrompt_SF_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_el_nFoundOnePrompt_SF_SB"));
    h_el_nLostOnePrompt_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_el_nLostOnePrompt_etaPt"));
    h_el_nLostOnePrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_el_nLostOnePrompt_SB"));

    h_el_SFCR_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_el_SFCR_etaPt"));
    h_el_SFCR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_el_SFCR_SB"));

    h_mu_nOnePrompt_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_mu_nOnePrompt_etaPt"));
    h_mu_nOnePrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mu_nOnePrompt_SB"));
    h_mu_nFoundOnePrompt_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_mu_nFoundOnePrompt_etaPt"));
    h_mu_nFoundOnePrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mu_nFoundOnePrompt_SB"));
    h_mu_nFoundOnePrompt_SF_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_mu_nFoundOnePrompt_SF_etaPt"));
    h_mu_nFoundOnePrompt_SF_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mu_nFoundOnePrompt_SF_SB"));
    h_mu_nLostOnePrompt_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_mu_nLostOnePrompt_etaPt"));
    h_mu_nLostOnePrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mu_nLostOnePrompt_SB"));

    h_mu_SFCR_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_mu_SFCR_etaPt"));
    h_mu_SFCR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mu_SFCR_SB"));

    h_el_SFSR_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_el_SFSR_etaPt"));
    h_el_SFSR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_el_SFSR_SB"));
    h_mu_SFSR_etaPt = dynamic_cast<TH2D*>(GetOutputList()->FindObject("h_mu_SFSR_etaPt"));
    h_mu_SFSR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_mu_SFSR_SB"));

    h_di_nTwoPrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_nTwoPrompt_SB"));
	h_di_nOneFoundTwoPrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_nOneFoundTwoPrompt_SB"));
	h_di_nOneFoundTwoPrompt_SF_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_nOneFoundTwoPrompt_SF_SB"));
	h_di_nTwoFoundTwoPrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_nTwoFoundTwoPrompt_SB"));
	h_di_nTwoFoundTwoPrompt_SF_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_nTwoFoundTwoPrompt_SF_SB"));
	h_di_nLostTwoPrompt_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_nLostTwoPrompt_SB"));

	h_di_SFCR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_SFCR_SB"));
	h_di_SFSR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_di_SFSR_SB"));

    for(int nX = 1; nX <= h_el_nOnePrompt_SB->GetXaxis()->GetNbins(); ++nX){
      if(h_el_nOnePrompt_SB->GetBinContent(nX) < 0){
	h_el_nOnePrompt_SB->SetBinContent(nX, 0);
	std::cout<<"h_el_nOnePrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_el_nFoundOnePrompt_SB->GetBinContent(nX) < 0){
	h_el_nFoundOnePrompt_SB->SetBinContent(nX, 0);
	std::cout<<"h_el_nFoundOnePrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_el_nFoundOnePrompt_SF_SB->GetBinContent(nX) < 0){
	h_el_nFoundOnePrompt_SF_SB->SetBinContent(nX, 0);
	std::cout<<"h_el_nFoundOnePrompt_SF_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_el_nLostOnePrompt_SB->GetBinContent(nX) < 0){
            h_el_nLostOnePrompt_SB->SetBinContent(nX, 0);
            std::cout<<"h_el_nLostOnePrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_mu_nOnePrompt_SB->GetBinContent(nX) < 0){
	h_mu_nOnePrompt_SB->SetBinContent(nX, 0);
	std::cout<<"h_mu_nOnePrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
        }
      if(h_mu_nFoundOnePrompt_SB->GetBinContent(nX) < 0){
	h_mu_nFoundOnePrompt_SB->SetBinContent(nX, 0);
	std::cout<<"h_mu_nFoundOnePrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_mu_nFoundOnePrompt_SF_SB->GetBinContent(nX) < 0){
	h_mu_nFoundOnePrompt_SF_SB->SetBinContent(nX, 0);
	std::cout<<"h_mu_nFoundOnePrompt_SF_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_mu_nLostOnePrompt_SB->GetBinContent(nX) < 0){
            h_mu_nLostOnePrompt_SB->SetBinContent(nX, 0);
            std::cout<<"h_mu_nLostOnePrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
      }        
      if(h_di_nTwoPrompt_SB->GetBinContent(nX) < 0){
	h_di_nTwoPrompt_SB->SetBinContent(nX, 0);
	std::cout<<"h_di_nTwoPrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_di_nOneFoundTwoPrompt_SB->GetBinContent(nX) < 0){
	h_di_nOneFoundTwoPrompt_SB->SetBinContent(nX, 0);
	std::cout<<"h_di_nOneFoundTwoPrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
        }
      if(h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX) < 0){
	h_di_nOneFoundTwoPrompt_SF_SB->SetBinContent(nX, 0);
	std::cout<<"h_di_nOneFoundTwoPrompt_SF_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
      if(h_di_nTwoFoundTwoPrompt_SB->GetBinContent(nX) < 0){
	h_di_nTwoFoundTwoPrompt_SB->SetBinContent(nX, 0);
	std::cout<<"h_di_nTwoFoundTwoPrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
      }
        if(h_di_nTwoFoundTwoPrompt_SF_SB->GetBinContent(nX) < 0){
            h_di_nTwoFoundTwoPrompt_SF_SB->SetBinContent(nX, 0);
            std::cout<<"h_di_nTwoFoundTwoPrompt_SF_SB (Bin "<<nX<<") negative value"<<std::endl;
        }
        if(h_di_nLostTwoPrompt_SB->GetBinContent(nX) < 0){
            h_di_nLostTwoPrompt_SB->SetBinContent(nX, 0);
            std::cout<<"h_di_nLostTwoPrompt_SB (Bin "<<nX<<") negative value"<<std::endl;
        }
    }



    ///////////////
    /// Singleleptonic
    ////////////

    // Without SFs:
    // nOnePrompt = nFoundOnePrompt + nLostOnePrompt
    // nOnePrompt is constant (only depends on xsec)

    // With SFs:
    // nOnePrompt = SFCR * nFoundOnePrompt + SFSR * nLostOnePrompt

    // Solve for SFSR:
    // SFSR = (nOnePrompt - SFCR * nFoundOnePrompt) / nLostOnePrompt

    h_el_SFSR_etaPt->Reset();
    h_el_SFSR_etaPt->Add(h_el_nOnePrompt_etaPt);
    h_el_SFSR_etaPt->Add(h_el_nFoundOnePrompt_SF_etaPt, -1);
    h_el_SFSR_etaPt->Divide(h_el_nLostOnePrompt_etaPt);

    h_el_SFSR_SB->Reset();
    h_el_SFSR_SB->Add(h_el_nOnePrompt_SB);
    h_el_SFSR_SB->Add(h_el_nFoundOnePrompt_SF_SB, -1);
    h_el_SFSR_SB->Divide(h_el_nLostOnePrompt_SB);

    h_mu_SFSR_etaPt->Reset();
    h_mu_SFSR_etaPt->Add(h_mu_nOnePrompt_etaPt);
    h_mu_SFSR_etaPt->Add(h_mu_nFoundOnePrompt_SF_etaPt, -1);
    h_mu_SFSR_etaPt->Divide(h_mu_nLostOnePrompt_etaPt);

    h_mu_SFSR_SB->Reset();
    h_mu_SFSR_SB->Add(h_mu_nOnePrompt_SB);
    h_mu_SFSR_SB->Add(h_mu_nFoundOnePrompt_SF_SB, -1);
    h_mu_SFSR_SB->Divide(h_mu_nLostOnePrompt_SB);


    // SF for CRs
    h_mu_SFCR_etaPt->Divide(h_mu_nFoundOnePrompt_SF_etaPt, h_mu_nFoundOnePrompt_etaPt);
	h_mu_SFCR_SB->Divide(h_mu_nFoundOnePrompt_SF_SB, h_mu_nFoundOnePrompt_SB);

	h_el_SFCR_etaPt->Divide(h_el_nFoundOnePrompt_SF_etaPt, h_el_nFoundOnePrompt_etaPt);
	h_el_SFCR_SB->Divide(h_el_nFoundOnePrompt_SF_SB, h_el_nFoundOnePrompt_SB);


    // Save histograms
	h_el_nOnePrompt_etaPt->Write();
	h_el_nOnePrompt_SB->Write();
	h_el_nFoundOnePrompt_etaPt->Write();
	h_el_nFoundOnePrompt_SB->Write();
	h_el_nFoundOnePrompt_SF_etaPt->Write();
	h_el_nFoundOnePrompt_SF_SB->Write();
	h_el_nLostOnePrompt_etaPt->Write();
	h_el_nLostOnePrompt_SB->Write();
	/*
    SaveEff(h_el_nOnePrompt_etaPt, outPutFile, false, true);
    SaveEff(h_el_nOnePrompt_SB, outPutFile);
    h_el_nFoundOnePrompt_etaPt->Divide(h_el_nOnePrompt_etaPt);
    SaveEff(h_el_nFoundOnePrompt_etaPt, outPutFile, false, true);
    h_el_nFoundOnePrompt_SB->Divide(h_el_nOnePrompt_SB);
    SaveEff(h_el_nFoundOnePrompt_SB, outPutFile);
    h_el_nFoundOnePrompt_SF_etaPt->Divide(h_el_nOnePrompt_etaPt);
    SaveEff(h_el_nFoundOnePrompt_SF_etaPt, outPutFile, false, true);
    h_el_nFoundOnePrompt_SF_SB->Divide(h_el_nOnePrompt_SB);
    SaveEff(h_el_nFoundOnePrompt_SF_SB, outPutFile);
    h_el_nLostOnePrompt_etaPt->Divide(h_el_nOnePrompt_etaPt);
    SaveEff(h_el_nLostOnePrompt_etaPt, outPutFile, false, true);
    h_el_nLostOnePrompt_SB->Divide(h_el_nOnePrompt_SB);
    SaveEff(h_el_nLostOnePrompt_SB, outPutFile);
*/
    for(int nX = 1; nX <= h_el_SFCR_SB->GetXaxis()->GetNbins(); ++nX){
        h_el_SFCR_SB->SetBinError(nX, 0);
        h_el_SFSR_SB->SetBinError(nX, 0);

        if(h_el_SFCR_SB->GetBinContent(nX) < 1e-8) h_el_SFCR_SB->SetBinContent(nX, 1);
        if(h_el_SFSR_SB->GetBinContent(nX) < 1e-8) h_el_SFSR_SB->SetBinContent(nX, 1);

        // Fix for sample with negative weights
        if(h_el_SFCR_SB->GetBinContent(nX) > 1) h_el_SFCR_SB->SetBinContent(nX, 1);
        if(h_el_SFSR_SB->GetBinContent(nX) < 1) h_el_SFSR_SB->SetBinContent(nX, 1);
    }

    SaveEff(h_el_SFCR_etaPt, outPutFile, false, true);
    SaveEff(h_el_SFCR_SB, outPutFile);

    SaveEff(h_el_SFSR_etaPt, outPutFile, false, true);
    SaveEff(h_el_SFSR_SB, outPutFile);

    h_mu_nOnePrompt_etaPt->Write();
    h_mu_nOnePrompt_SB->Write();
    h_mu_nFoundOnePrompt_etaPt->Write();
    h_mu_nFoundOnePrompt_SB->Write();
    h_mu_nFoundOnePrompt_SF_etaPt->Write();
    h_mu_nFoundOnePrompt_SF_SB->Write();
    h_mu_nLostOnePrompt_etaPt->Write();
    h_mu_nLostOnePrompt_SB->Write();
    /*  
    SaveEff(h_mu_nOnePrompt_etaPt, outPutFile, false, true);
    SaveEff(h_mu_nOnePrompt_SB, outPutFile);
    h_mu_nFoundOnePrompt_etaPt->Divide(h_mu_nOnePrompt_etaPt);
    SaveEff(h_mu_nFoundOnePrompt_etaPt, outPutFile, false, true);
    h_mu_nFoundOnePrompt_SB->Divide(h_mu_nOnePrompt_SB);
    SaveEff(h_mu_nFoundOnePrompt_SB, outPutFile);
    h_mu_nFoundOnePrompt_SF_etaPt->Divide(h_mu_nOnePrompt_etaPt);
    SaveEff(h_mu_nFoundOnePrompt_SF_etaPt, outPutFile, false, true);
    h_mu_nFoundOnePrompt_SF_SB->Divide(h_mu_nOnePrompt_SB);
    SaveEff(h_mu_nFoundOnePrompt_SF_SB, outPutFile);
    h_mu_nLostOnePrompt_etaPt->Divide(h_mu_nOnePrompt_etaPt);
    SaveEff(h_mu_nLostOnePrompt_etaPt, outPutFile, false, true);
    h_mu_nLostOnePrompt_SB->Divide(h_mu_nOnePrompt_SB);
    SaveEff(h_mu_nLostOnePrompt_SB, outPutFile);
*/
    for(int nX = 1; nX <= h_mu_SFCR_SB->GetXaxis()->GetNbins(); ++nX){
        h_mu_SFCR_SB->SetBinError(nX, 0);
        h_mu_SFSR_SB->SetBinError(nX, 0);
        
        if(h_mu_SFCR_SB->GetBinContent(nX) < 1e-8) h_mu_SFCR_SB->SetBinContent(nX, 1);
        if(h_mu_SFSR_SB->GetBinContent(nX) < 1e-8) h_mu_SFSR_SB->SetBinContent(nX, 1);

        // Fix for sample with negative weights
        if(h_mu_SFCR_SB->GetBinContent(nX) > 1) h_mu_SFCR_SB->SetBinContent(nX, 1);
        if(h_mu_SFSR_SB->GetBinContent(nX) < 1) h_mu_SFSR_SB->SetBinContent(nX, 1);
    }

    SaveEff(h_mu_SFCR_etaPt, outPutFile, false, true);
    SaveEff(h_mu_SFCR_SB, outPutFile);

    SaveEff(h_mu_SFSR_etaPt, outPutFile, false, true);
    SaveEff(h_mu_SFSR_SB, outPutFile);


    ///////////////
    /// Dileptonic
    ////////////

    // Similar as singleleptonic case
    // With SFs:
    // nTwoPrompt = SFCR^2 * nTwoFoundTwoPrompt + SFCR * SFSR * nOneFoundTwoPrompt + SFSR^2 * nLostTwoPrompt
    // => 0 = SFSR^2 * nLostTwoPrompt + SFSR * (SFCR * nOneFoundTwoPrompt) + ((SFCR^2 * nTwoFoundTwoPrompt) - nTwoPrompt)

    // Solve for SFSR: (quadratic equation with only 1 positive solution)
    // SFSR = (-nOneFoundTwoPrompt + sqrt((nOneFoundTwoPrompt)^2 - 4 * nLostTwoPrompt * (nTwoFoundTwoPrompt - nTwoPrompt))) /  (2 * nLostTwoPrompt)
    // Better: Use Muller's method (smaller rounding errors)
    // x = 2c / (-b - sqrt(b^2 - 4ac))
    // SFSR = 2 * (nTwoFoundTwoPrompt - nTwoPrompt) / (-nOneFoundTwoPrompt - sqrt(nOneFoundTwoPrompt^2 - 4 * nLostTwoPrompt * (nTwoFoundTwoPrompt - nTwoPrompt)))

	for(int nX = 1; nX <= h_di_SFSR_SB->GetXaxis()->GetNbins(); ++nX){
		double SFSR_dilep = 1;
        if(h_di_nTwoPrompt_SB->GetBinContent(nX) > 0 && h_di_nTwoFoundTwoPrompt_SF_SB->GetBinContent(nX) - h_di_nTwoPrompt_SB->GetBinContent(nX) < 0 && (h_di_nLostTwoPrompt_SB->GetBinContent(nX) > 0 || h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX) > 0))
            SFSR_dilep = (2. * (h_di_nTwoFoundTwoPrompt_SF_SB->GetBinContent(nX) - h_di_nTwoPrompt_SB->GetBinContent(nX))) / (-h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX) - std::sqrt(h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX)*h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX) - 4. * h_di_nLostTwoPrompt_SB->GetBinContent(nX) * (h_di_nTwoFoundTwoPrompt_SF_SB->GetBinContent(nX) - h_di_nTwoPrompt_SB->GetBinContent(nX))));
		//else if(h_di_nLostTwoPrompt_SB->GetBinContent(nX) > 0)
        //SFSR_dilep = (-h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX) + std::sqrt(h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX)*h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX) - 4. * h_di_nLostTwoPrompt_SB->GetBinContent(nX) * (h_di_nTwoFoundTwoPrompt_SF_SB->GetBinContent(nX) - h_di_nTwoPrompt_SB->GetBinContent(nX)))) / (2. * h_di_nLostTwoPrompt_SB->GetBinContent(nX));
		h_di_SFSR_SB->SetBinContent(nX, SFSR_dilep);

        //std::cout<<SFSR_dilep<<"   "<<h_di_nTwoPrompt_SB->GetBinContent(nX)<<"  "<<h_di_nTwoFoundTwoPrompt_SF_SB->GetBinContent(nX)<<"/"<<h_di_nTwoFoundTwoPrompt_SB->GetBinContent(nX)<<"  "<<h_di_nOneFoundTwoPrompt_SF_SB->GetBinContent(nX)<<"/"<<h_di_nOneFoundTwoPrompt_SB->GetBinContent(nX)<<"    "<<h_di_nLostTwoPrompt_SB->GetBinContent(nX)<<std::endl;

		double SFCR_dilep = 1;
		if(h_di_nTwoFoundTwoPrompt_SB->GetBinContent(nX) > 0) SFCR_dilep = std::sqrt(h_di_nTwoFoundTwoPrompt_SF_SB->GetBinContent(nX)/h_di_nTwoFoundTwoPrompt_SB->GetBinContent(nX));
		h_di_SFCR_SB->SetBinContent(nX, SFCR_dilep);

        // Fix for sample with negative weights
        if(h_di_SFCR_SB->GetBinContent(nX) > 1) h_di_SFCR_SB->SetBinContent(nX, 1);
        if(h_di_SFSR_SB->GetBinContent(nX) < 1) h_di_SFSR_SB->SetBinContent(nX, 1);
	}

	h_di_nTwoPrompt_SB->Write();
	h_di_nTwoFoundTwoPrompt_SB->Write();
	h_di_nOneFoundTwoPrompt_SB->Write();
	h_di_nTwoFoundTwoPrompt_SF_SB->Write();
	h_di_nOneFoundTwoPrompt_SF_SB->Write();
	h_di_nLostTwoPrompt_SB->Write();
	/*
	h_di_nTwoFoundTwoPrompt_SB->Divide(h_di_nTwoPrompt_SB);
	SaveEff(h_di_nTwoFoundTwoPrompt_SB, outPutFile);
	h_di_nOneFoundTwoPrompt_SB->Divide(h_di_nTwoPrompt_SB);
	SaveEff(h_di_nOneFoundTwoPrompt_SB, outPutFile);
	h_di_nTwoFoundTwoPrompt_SF_SB->Divide(h_di_nTwoPrompt_SB);
	SaveEff(h_di_nTwoFoundTwoPrompt_SF_SB, outPutFile);
	h_di_nOneFoundTwoPrompt_SF_SB->Divide(h_di_nTwoPrompt_SB);
	SaveEff(h_di_nOneFoundTwoPrompt_SF_SB, outPutFile);
	h_di_nLostTwoPrompt_SB->Divide(h_di_nTwoPrompt_SB);
	SaveEff(h_di_nLostTwoPrompt_SB, outPutFile);
*/	
    SaveEff(h_di_SFCR_SB, outPutFile);
    SaveEff(h_di_SFSR_SB, outPutFile);

    outPutFile->Close();

    cout << "Saved output to " << fileName << endl;

}

void SFMaker::SaveEff(TH1* h, TFile* oFile, bool xlog, bool ylog)
{
    oFile->cd();

    //h->SetTitle(TString("Simulation, L=3 fb^{-1}, #sqrt{s}=13 TeV ") + TString(title));
    h->SetMarkerSize(2.0);
    h->UseCurrentStyle();

    gROOT->SetBatch(true);    
    TCanvas *c1 = new TCanvas("c1","c1",1);
    c1->cd();
    if(xlog){
      c1->SetLogx();
      h->GetXaxis()->SetRangeUser(0.001, h->GetXaxis()->GetBinLowEdge(h->GetNbinsX()+1));
    }
    if(ylog){
    	c1->SetLogy();
    	h->GetYaxis()->SetRangeUser(0.001, h->GetYaxis()->GetBinLowEdge(h->GetNbinsY()+1));
   	}

    std::string name = std::string(h->GetName());
    if(name.find(std::string("SFCR")) != std::string::npos || name.find(std::string("SFSR")) != std::string::npos){
    	if(name.find(std::string("SB")) != std::string::npos) h->GetYaxis()->SetRangeUser(0.79, 1.31);
    	if(name.find(std::string("etaPt")) != std::string::npos){
            h->GetYaxis()->SetRangeUser(5., 500.);
            h->GetZaxis()->SetRangeUser(0.79, 1.31);
        }
    }else{
    	if(name.find(std::string("SB")) != std::string::npos) h->GetYaxis()->SetRangeUser(0.01, 1.01);
    	if(name.find(std::string("etaPt")) != std::string::npos){
            h->GetYaxis()->SetRangeUser(5., 500.);
            h->GetZaxis()->SetRangeUser(0.01, 1.01);
        }
    }
    
    h->Draw("ColZ,Text");

    //if(name.find(std::string("SFCR")) != std::string::npos || name.find(std::string("SFSR")) != std::string::npos){
    	TObjArray *optionArray = currFileName.Tokenize("_.");
    	TString currTreeName = ((TObjString *)(optionArray->At(0)))->String();
    	c1->SaveAs("SFs/"+currTreeName+"_"+TString(name)+".pdf");
	//}

    delete c1;
    gROOT->SetBatch(false);

    h->Write();
}

bool SFMaker::FiltersPass()
{
    bool result=true;
    //*AR-180101- useFilterData true for other than FastSim
    if(useFilterData){
        if(HBHENoiseFilter!=1) result=false;
        if(HBHEIsoNoiseFilter!=1) result=false;
        if(EcalDeadCellTriggerPrimitiveFilter!=1) result=false;    
        if(eeBadScFilter!=1) result=false;

        //if(runOnData){
        //    if(!BadChargedCandidateFilter) result=false;
        //    if(!BadPFMuonFilter) result=false;
        //    if(globalTightHalo2016Filter!=1) result=false;
        //}    
    }
    if(NVtx<=0) result=false;

    // Preliminary filters
    if(PFCaloMETRatio>5) result=false;

    for(unsigned j = 0; j < Jets->size(); j++){
      //*AR-180101- return std::isnan(x)----> A non-zero value (true) if x is a NaN value; and zero (false) otherwise.
        if(TMath::IsNaN(Jets->at(j).Phi()-METPhi)) result=false;
        if(Jets->at(j).Pt()>200 && Jets_muonEnergyFraction->at(j)>0.5 && (TVector2::Phi_mpi_pi(Jets->at(j).Phi()-METPhi)>(TMath::Pi()-0.4))){
            //std::cout<<"found bad muon jet"<<std::endl;
            result=false;
            break;
        }
    }

    //reject events with any jet pt>20, |eta|<2.5 NOT matched to a GenJet (w/in DeltaR<0.3) and chfrac < 0.1
    /*if (runOnSignalMC)
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
    */
    // Do not apply on fastSim samples!
    //if(!runOnSignalMC) if(!JetID) result=false;
    return result;
}
/*
std::pair<vector<TVector3>,vector<int>> SFMaker::Order_the_Vec(vector<TVector3> vec)
{
  vector<TVector3> vecjvec=vec;
  vector<int> vecIndex;
  for(int i=0; i<((int)vecjvec.size()-1);i++){
    int OrgIndex=-1;
    for(int j=i+1; j<((int)vecjvec.size()-1);j++){
      if(vecjvec[j].Pt()>vecjvec[i].Pt()){
	OrgIndex=j;
	swap(vecjvec[i],vecjvec[j]);
      }
    }
    vecIndex.push_back(OrgIndex);
  }
  return std::make_pair(vecjvec,vecIndex);
}
*/

vector<TVector3>SFMaker::Order_the_Vec(vector<TVector3> vec)
{
  vector<TVector3> vecjvec=vec;
  vector<int> vecIndex;
  for(unsigned int i=0; i<vecjvec.size();i++){
    for(unsigned int j=i+1; j<vecjvec.size();j++){
      if(vecjvec[j].Pt()>vecjvec[i].Pt()){
	swap(vecjvec[i],vecjvec[j]);
      }
    }
  }
  return vecjvec;
}

vector<double>SFMaker::Order_the_Vec(vector<TVector3> vec,vector<double> vecTwo)
{
  vector<TVector3> vecjvec=vec;
  vector<double> vecjTwovec=vecTwo;
  for(unsigned int i=0; i<vecjvec.size();i++){
    for(unsigned int j=i+1; j<vecjvec.size();j++){
      if(vecjvec[j].Pt()>vecjvec[i].Pt()){
	swap(vecjvec[i],vecjvec[j]);
	swap(vecjTwovec[i],vecjTwovec[j]);
      }
    }
  }
  return vecjTwovec;
}

vector<bool>SFMaker::Order_the_Vec(vector<TVector3> vec,vector<bool> vecTwo)
{
  vector<TVector3> vecjvec=vec;
  vector<bool> vecjTwovec=vecTwo;
  for(unsigned int i=0; i<vecjvec.size();i++){
    for(unsigned int j=i+1; j<vecjvec.size();j++){
      if(vecjvec[j].Pt()>vecjvec[i].Pt()){
	swap(vecjvec[i],vecjvec[j]);
	swap(vecjTwovec[i],vecjTwovec[j]);
      }
    }
  }
  return vecjTwovec;
}

vector<int>SFMaker::Order_the_Vec(vector<TVector3> vec,vector<int> vecTwo)
{
  vector<TVector3> vecjvec=vec;
  vector<int> vecjTwovec=vecTwo;
  for(unsigned int i=0; i<vecjvec.size();i++){
    for(unsigned int j=i+1; j<vecjvec.size();j++){
      if(vecjvec[j].Pt()>vecjvec[i].Pt()){
	swap(vecjvec[i],vecjvec[j]);
	swap(vecjTwovec[i],vecjTwovec[j]);
      }
    }
  }
  return vecjTwovec;
}

vector<TLorentzVector>SFMaker::Order_the_Vec(vector<TVector3> vec,vector<TLorentzVector> vecTwo)
{
  vector<TVector3> vecjvec=vec;
  vector<TLorentzVector> vecjTwovec=vecTwo;
  for(unsigned int i=0; i<vecjvec.size();i++){
    for(unsigned int j=i+1; j<vecjvec.size();j++){
      if(vecjvec[j].Pt()>vecjvec[i].Pt()){
	swap(vecjvec[i],vecjvec[j]);
	swap(vecjTwovec[i],vecjTwovec[j]);
      }
    }
  }
  return vecjTwovec;
}


void SFMaker::resetValues()
{
    GenMuonsAccPt_=0;
    GenMuonsAccEta_=0;
    GenElectronsAccPt_=0;
    GenElectronsAccEta_=0;
    GenMuonsAccPt2_=0;
    GenMuonsAccEta2_=0;
    GenElectronsAccPt2_=0;
    GenElectronsAccEta2_=0;

    MuonsPromptNum_=0;
    ElectronsPromptNum_=0;
    MuonTracksPromptNum_=0;
    ElectronTracksPromptNum_=0;

    MuonsPromptPt_=0;
    MuonsPromptEta_=0;
    ElectronsPromptPt_=0;
    ElectronsPromptEta_=0;

    MuonsPromptPt2_=0;
    MuonsPromptEta2_=0;
    ElectronsPromptPt2_=0;
    ElectronsPromptEta2_=0;

    MuonTracksPromptPt_=0;
    MuonTracksPromptEta_=0;
    ElectronTracksPromptPt_=0;
    ElectronTracksPromptEta_=0;

    MuonTracksPromptPt2_=0;
    MuonTracksPromptEta2_=0;
    ElectronTracksPromptPt2_=0;
    ElectronTracksPromptEta2_=0;

    MuonsPromptMatch_=-1;
    ElectronsPromptMatch_=-1;
    MuonsPromptMatch2_=-1;
    ElectronsPromptMatch2_=-1;

    MuonTracksPromptMatch_=-1;
    ElectronTracksPromptMatch_=-1;
    MuonTracksPromptMatch2_=-1;
    ElectronTracksPromptMatch2_=-1;

    GenElectronsAcc.clear();
    GenMuonsAcc.clear();

    mtw = 0;

    isoElectronTracks.clear();
    isoMuonTracks.clear();
    isoPionTracks.clear();
}
