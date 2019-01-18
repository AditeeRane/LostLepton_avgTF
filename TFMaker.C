#define TFMaker_cxx

#include "TFMaker.h"

void TFMaker::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TH1::SetDefaultSumw2();
}

void TFMaker::SlaveBegin(TTree * /*tree*/)
{ //*AR-180314: This loop runs for every new tree
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  std::cout<<"***TFMaker::SlaveBegin***"<<std::endl;
  SearchBins_ = new SearchBins(true);
  SearchBins_BTags_ = new SearchBins(true);

  bTagBins = {0, 0, 0, 0};
  BinforMTEff = {0, 0, 0, 0};
  // Initialize Histograms
  TH1::SetDefaultSumw2();
  unsigned nSB = SearchBins_->GetNbins();
  h_CR_SB = new TH1D("h_CR_SB", "h_CR_SB", nSB, 0.5, nSB+0.5);
  h_SR_SB = new TH1D("h_SR_SB", "h_SR_SB", nSB, 0.5, nSB+0.5);
  h_SR_LL_SB = new TH1D("h_SR_LL_SB", "h_SR_LL_SB", nSB, 0.5, nSB+0.5);
  h_SR_Hadtau_SB = new TH1D("h_SR_Hadtau_SB", "h_SR_Hadtau_SB", nSB, 0.5, nSB+0.5);

  h_0L1L_SB = new TH1D("h_0L1L_SB", "h_0L1L_SB", nSB, 0.5, nSB+0.5);
  h_0L1L_LL_SB = new TH1D("h_0L1L_LL_SB", "h_0L1L_LL_SB", nSB, 0.5, nSB+0.5);
  h_0L1L_Hadtau_SB = new TH1D("h_0L1L_Hadtau_SB", "h_0L1L_Hadtau_SB", nSB, 0.5, nSB+0.5);

  h_CR_SF_SB = new TH1D("h_CR_SF_SB", "h_CR_SF_SB", nSB, 0.5, nSB+0.5);
  h_SR_SF_SB = new TH1D("h_SR_SF_SB", "h_SR_SF_SB", nSB, 0.5, nSB+0.5);
  h_SR_SF_LL_SB = new TH1D("h_SR_SF_LL_SB", "h_SR_SF_LL_SB", nSB, 0.5, nSB+0.5);
  h_SR_SF_Hadtau_SB = new TH1D("h_SR_SF_Hadtau_SB", "h_SR_SF_Hadtau_SB", nSB, 0.5, nSB+0.5);

  h_0L1L_SF_SB = new TH1D("h_0L1L_SF_SB", "h_0L1L_SF_SB", nSB, 0.5, nSB+0.5);
  h_0L1L_SF_LL_SB = new TH1D("h_0L1L_SF_LL_SB", "h_0L1L_SF_LL_SB", nSB, 0.5, nSB+0.5);
  h_0L1L_SF_Hadtau_SB = new TH1D("h_0L1L_SF_Hadtau_SB", "h_0L1L_SF_Hadtau_SB", nSB, 0.5, nSB+0.5);

  // Use those histograms per sample. You don't want net negative weights
  h_CR_SB_copy = new TH1D("h_CR_SB_copy", "h_CR_SB_copy", nSB, 0.5, nSB+0.5);
  h_SR_SB_copy = new TH1D("h_SR_SB_copy", "h_SR_SB_copy", nSB, 0.5, nSB+0.5);
  h_SR_LL_SB_copy = new TH1D("h_SR_LL_SB_copy", "h_SR_LL_SB_copy", nSB, 0.5, nSB+0.5);
  h_SR_Hadtau_SB_copy = new TH1D("h_SR_Hadtau_SB_copy", "h_SR_Hadtau_SB_copy", nSB, 0.5, nSB+0.5);

  h_CR_SF_SB_copy = new TH1D("h_CR_SF_SB_copy", "h_CR_SF_SB_copy", nSB, 0.5, nSB+0.5);
  h_SR_SF_SB_copy = new TH1D("h_SR_SF_SB_copy", "h_SR_SF_SB_copy", nSB, 0.5, nSB+0.5);
  h_SR_SF_LL_SB_copy = new TH1D("h_SR_SF_LL_SB_copy", "h_SR_SF_LL_SB_copy", nSB, 0.5, nSB+0.5);
  h_SR_SF_Hadtau_SB_copy = new TH1D("h_SR_SF_Hadtau_SB_copy", "h_SR_SF_Hadtau_SB_copy", nSB, 0.5, nSB+0.5);

  h_CR_BeforeMT = new TH1D("h_CR_BeforeMT","h_CR_BeforeMT",nSB, 0.5, nSB+0.5);
  h_CR_AfterMT = new TH1D("h_CR_AfterMT","h_CR_AfterMT",nSB, 0.5, nSB+0.5);
  h_MTEff = new TH1D("h_MTEff","h_MTEff",nSB, 0.5, nSB+0.5);

  GetOutputList()->Add(h_CR_SB);
  GetOutputList()->Add(h_SR_SB);
  GetOutputList()->Add(h_SR_LL_SB);
  GetOutputList()->Add(h_SR_Hadtau_SB);

  GetOutputList()->Add(h_0L1L_SB);
  GetOutputList()->Add(h_0L1L_LL_SB);
  GetOutputList()->Add(h_0L1L_Hadtau_SB);

  GetOutputList()->Add(h_CR_SF_SB);
  GetOutputList()->Add(h_SR_SF_SB);
  GetOutputList()->Add(h_SR_SF_LL_SB);
  GetOutputList()->Add(h_SR_SF_Hadtau_SB);

  GetOutputList()->Add(h_0L1L_SF_SB);
  GetOutputList()->Add(h_0L1L_SF_LL_SB);
  GetOutputList()->Add(h_0L1L_SF_Hadtau_SB);

  GetOutputList()->Add(h_CR_SB_copy);
  GetOutputList()->Add(h_SR_SB_copy);
  GetOutputList()->Add(h_SR_LL_SB_copy);
  GetOutputList()->Add(h_SR_Hadtau_SB_copy);

  GetOutputList()->Add(h_CR_SF_SB_copy);
  GetOutputList()->Add(h_SR_SF_SB_copy);
  GetOutputList()->Add(h_SR_SF_LL_SB_copy);
  GetOutputList()->Add(h_SR_SF_Hadtau_SB_copy);


  GetOutputList()->Add(h_CR_BeforeMT);
  GetOutputList()->Add(h_CR_AfterMT);
  GetOutputList()->Add(h_MTEff);

  std::cout<<"----------------"<<std::endl;
  std::cout<<"DeltaPhi Cut: "<<useDeltaPhiCut<<std::endl;
  std::cout<<"----------------"<<std::endl;
  
  if(ScaleAccSys){
    char tempname[200];
    for(int iacc=0; iacc < Scalesize; iacc++){
      sprintf(tempname,"h_scale_CR_SB_%d",iacc);
      Vec_scale_CR_SB_copy.push_back(static_cast<TH1*>(h_CR_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_scale_SR_SB_%d",iacc);
      Vec_scale_SR_SB_copy.push_back(static_cast<TH1*>(h_SR_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_scale_0L1L_SB_%d",iacc);
      Vec_scale_0L1L_SB.push_back(static_cast<TH1*>(h_0L1L_SB->Clone(tempname)));
    
      sprintf(tempname,"h_scale_CR_SF_SB_%d",iacc);
      Vec_scale_CR_SF_SB_copy.push_back(static_cast<TH1*>(h_CR_SF_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_scale_SR_SF_SB_%d",iacc);
      Vec_scale_SR_SF_SB_copy.push_back(static_cast<TH1*>(h_SR_SF_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_scale_0L1L_SF_SB_%d",iacc);
      Vec_scale_0L1L_SF_SB.push_back(static_cast<TH1*>(h_0L1L_SF_SB->Clone(tempname)));
    }
    std::cout<<" first ScaleAcc**** "<<endl;
  }

  if(PDFAccSys){
    char tempname[200];
    for(int iacc=0; iacc < PDFsize; iacc++){
      sprintf(tempname,"h_PDF_CR_SB_%d",iacc);
      Vec_PDF_CR_SB_copy.push_back(static_cast<TH1*>(h_CR_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_PDF_SR_SB_%d",iacc);
      Vec_PDF_SR_SB_copy.push_back(static_cast<TH1*>(h_SR_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_PDF_0L1L_SB_%d",iacc);
      Vec_PDF_0L1L_SB.push_back(static_cast<TH1*>(h_0L1L_SB->Clone(tempname)));
    
      sprintf(tempname,"h_PDF_CR_SF_SB_%d",iacc);
      Vec_PDF_CR_SF_SB_copy.push_back(static_cast<TH1*>(h_CR_SF_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_PDF_SR_SF_SB_%d",iacc);
      Vec_PDF_SR_SF_SB_copy.push_back(static_cast<TH1*>(h_SR_SF_SB_copy->Clone(tempname)));
      sprintf(tempname,"h_PDF_0L1L_SF_SB_%d",iacc);
      Vec_PDF_0L1L_SF_SB.push_back(static_cast<TH1*>(h_0L1L_SF_SB->Clone(tempname)));
    }
    std::cout<<" first PDFAcc**** "<<endl;
  }
}

Bool_t TFMaker::Process(Long64_t entry)
{
  //*AR-180314: This loop runs for every new event
  //  std::cout<<"***TFMaker::Process***"<<" entry "<<entry<<std::endl;
    resetValues();

    fChain->GetTree()->GetEntry(entry);
    //*AR-180116-Only consider events passing filters
    if(applyFilters &&  !FiltersPass() ) return kTRUE;
    
    //  if(entry % 3 != 0) return kTRUE;

    //if(HTgen_cut > 0.01) if(madHT > HTgen_cut) return kTRUE;
    vector<int> MHTJetsIdxv2Recipe;
    vector<int> ElectronMatchJetIdxv2Recipe;

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
    double newHT=0,newHT5=0,newMHT=0,newMHTPhi=0;
    TVector3 newMHT3Vec;
    int newNJets=-99;
    double newDphi1=99.,newDphi2=99.,newDphi3=99.,newDphi4=99.;
    int newBTagsDeepCSV = 0;
    vector<double> Vec_SF;
    int MuonsNumPassIdIso_=0;
    int ElectronsNumPassIdIso_=0;
  //*AR-180115-As in jet collection there are jets saved with pt>30 and eta<5, MHT3JetVec size remains same while HT3JetVec size reduces.
    if(JECSys){ 
      for(unsigned int i=0;i < Jets->size();i++){
	//std::cout<<" i "<<i<<" jet_pt(i) "<<Jets->at(i).Pt()<<" jec "<< Jets_jecUnc->at(i)<<" new pt "<< Jets->at(i).Pt()*(1+Jets_jecUnc->at(i))<<" csv "<< Jets_bDiscriminatorCSV->at(i)<<" HTMask "<< Jets_HTMask->at(i)<<" hadronFlavor "<<Jets_hadronFlavor->at(i)<<" eta "<< Jets->at(i).Eta()<<endl;
	if(SysUp) newPt=Jets->at(i).Pt()*(1+Jets_jecUnc->at(i));
	if(SysDn) newPt=Jets->at(i).Pt()*(1-Jets_jecUnc->at(i));
	jetCSV=Jets_bJetTagDeepCSVprobb->at(i) + Jets_bJetTagDeepCSVprobbb->at(i);
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
      } /*//end of for loop
      
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
      MHT3JetHadronFlavorvec= Order_the_Vec(MHT3JetVec,MHT3JetHadronFlavorvec);          MHT3JetLorentzVec= Order_the_Vec(MHT3JetVec,MHT3JetLorentzVec);
      HT3JetVec= Order_the_Vec(HT3JetVec);
      MHT3JetVec= Order_the_Vec(MHT3JetVec);      
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
	newHT5+=MHT3JetVec[i].Pt();
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
      
      for(unsigned int i=0;i<HT3JetVec.size();i++){
	if(HT3JetCSVvec[i]>csvForBtag)
	  newBTagsDeepCSV++;
      }
    } //end of JECSys
    else{
      for(unsigned j = 0; j < Jets->size(); ++j){
	if(Jets->at(j).Pt()>30 && fabs(Jets->at(j).Eta()) < 5.0)
	  MHTJetsIdxv2Recipe.push_back(j);
      }
    }
    
      //    std::cout<<" btags "<<BTagsDeepCSV<<" newBTags "<<newBTagsDeepCSV<<endl;
      //  if(entry % 3 != 0) return kTRUE;
      
    //if(HTgen_" vector is orderedcut > 0.01) if(madHT > HTgen_cut) return kTRUE;
    //*AR, 180101-minHT_=300,minMHT_=250,minNJets_=1.5,deltaPhi1_=0.5,deltaPhi2_=0.5,deltaPhi3_=0.3,deltaPhi4_=0.3
    //*AR, 180101-minMHT_=250 here as we are also deriving SFs for low MHT, 3 bins.
    if(JECSys){
      if(newHT<minHT_ || newMHT< minMHT_ || newNJets < minNJets_  ) return kTRUE;
      if(useDeltaPhiCut == 1) if(newDphi1 < deltaPhi1_ || newDphi2 < deltaPhi2_ || newDphi3 < deltaPhi3_ || newDphi4 < deltaPhi4_) return kTRUE;
      if(useDeltaPhiCut == -1) if(!(newDphi1 < deltaPhi1_ || newDphi2 < deltaPhi2_ || newDphi3 < deltaPhi3_ || newDphi4 < deltaPhi4_)) return kTRUE;
      double getHT5Cut;
      getHT5Cut = 1.025*(newHT5/newHT)-0.5875;
      if(newDphi1 < getHT5Cut){
	//	std::cout<<" HT "<<HT<<" HT5 "<<HT5<<" getHT5Cut "<<getHT5Cut<<" DeltaPhi1 "<<DeltaPhi1<<endl;
	return kTRUE;
      }

    }
    else{
      if(HT<minHT_ || MHT< minMHT_ || NJets < minNJets_  ) return kTRUE;
      if(useDeltaPhiCut == 1) if(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_) return kTRUE;
      if(useDeltaPhiCut == -1) if(!(DeltaPhi1 < deltaPhi1_ || DeltaPhi2 < deltaPhi2_ || DeltaPhi3 < deltaPhi3_ || DeltaPhi4 < deltaPhi4_)) return kTRUE;
      double getHT5Cut;
      getHT5Cut = 1.025*(HT5/HT)-0.5875;
      if(DeltaPhi1 < getHT5Cut){
	//	std::cout<<" HT "<<HT<<" HT5 "<<HT5<<" getHT5Cut "<<getHT5Cut<<" DeltaPhi1 "<<DeltaPhi1<<endl;
	return kTRUE;
      }
    }


    GenMuonsNum_ = GenMuons->size();
    GenElectronsNum_ = GenElectrons->size();
    GenTausNum_ = GenTaus->size();
    MuonsNum_ = Muons->size();
    ElectronsNum_ = Electrons->size();
    //    std::cout<<" GenMuonsNum_ "<<GenMuonsNum_<<" GenElectronsNum_ "<<GenElectronsNum_<<" ElectronsNum_ "<<ElectronsNum_<<" MuonsNum_ "<<MuonsNum_<<endl;
    //Consider only events with atleast one lepton at gen level.
    //*AR-190111: This condition was removed when considering hadtau component contribution in signal region.
    //    if(GenMuonsNum_ + GenElectronsNum_ == 0) return kTRUE;

    if(JECSys)
      Bin_ = SearchBins_->GetBinNumber(newHT,newMHT,newNJets,newBTagsDeepCSV);
    else
      Bin_ = SearchBins_->GetBinNumber(HT,MHT,NJets,BTagsDeepCSV); //BTags are real btags read from ntuple 
    //    std::cout<<" HT "<<HT<<" MHT "<<MHT<<" NJets "<<NJets<<" BTags "<<BTagsDeepCSV<<" bin "<<Bin_<<endl;
    if(Bin_ > 900) return kTRUE;

    //* AR-20180115-As following loop is not executing, it is not modified to account for JECSys effect.
    if(doTopPtReweighting){
        if(GenParticles->size() != GenParticles_PdgId->size()){
            std::cout << "Cannot do top-pT reweighting!"<< std::endl; 
        }else{
            for(unsigned iGen = 0; iGen < GenParticles->size(); iGen++){
                if(std::abs(GenParticles_PdgId->at(iGen)) == 6){
                  topPt.push_back(GenParticles->at(iGen).Pt());
                }
            }//* AR-180123--end of for loop

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
        }

        // Normalization tested on SingleLept and DiLept samples (varies from ~98.9x-99.0x)
        topPtSF /= 0.99;
        Weight *= topPtSF;
    }//end of "if(doTopPtReweighting)"

    double madHTcut=0.0;
    TString currentTree = TString(fChain->GetCurrentFile()->GetName());
    //*AR-190110: This is skimfilepath irrespective of (GenElectronsNum_ + GenMuonsNum_) is zero or not
    SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm";
    if(GenElectronsNum_ > GenMuonsNum_)
      SkimFilePath="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLe";

    //*AR-180314-Name of skimfile won't change from event to event, so this loop has to be run only for every new tree
    if(currentTree != treeName  || SkimFilePath!=OldSkimFilePath){
        treeName = currentTree;
	OldSkimFilePath = SkimFilePath;
        TObjArray *optionArray = currentTree.Tokenize("/");
        currFileName = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
	currentFile = ((TObjString *)(optionArray->At(optionArray->GetEntries()-1)))->String();
	//	std::cout<<" currentFile "<<currentFile<<endl;

	string skimName="tree_TTJets_SingleLeptFromT_MC2017.root";
	char SkimFile[500];
	if(currentFile.find("TTJets_SingleLeptFromTbar")!=string::npos) skimName="tree_TTJets_SingleLeptFromTbar_MC2017.root"; 
	else if(currentFile.find("TTJets_SingleLeptFromT")!=string::npos) skimName="tree_TTJets_SingleLeptFromT_MC2017.root"; 
	else if(currentFile.find("DiLept")!=string::npos)skimName="tree_TTJets_DiLept_MC2017.root";
	else if(currentFile.find("TTJets_HT-600to800")!=string::npos)skimName="tree_TTJets_HT-600to800_MC2017.root";
	else if(currentFile.find("TTJets_HT-800to1200")!=string::npos)skimName="tree_TTJets_HT-800to1200_MC2017.root";
	else if(currentFile.find("TTJets_HT-1200to2500")!=string::npos)skimName="tree_TTJets_HT-1200to2500_MC2017.root";
	else if(currentFile.find("TTJets_HT-2500toInf")!=string::npos)skimName="tree_TTJets_HT-2500toInf_MC2017.root";
	else if(currentFile.find("Inclusive")!=string::npos)skimName="tree_TTJets_MC2017.root";
	else if(currentFile.find("WJetsToLNu_HT-100To200")!=string::npos)skimName="tree_WJetsToLNu_HT-100to200_MC2017.root";
	else if(currentFile.find("WJetsToLNu_HT-200To400")!=string::npos)skimName="tree_WJetsToLNu_HT-200to400_MC2017.root";
	else if(currentFile.find("WJetsToLNu_HT-400To600")!=string::npos)skimName="tree_WJetsToLNu_HT-400to600_MC2017.root";
	else if(currentFile.find("WJetsToLNu_HT-600To800")!=string::npos)skimName="tree_WJetsToLNu_HT-600to800_MC2017.root";
	else if(currentFile.find("WJetsToLNu_HT-800To1200")!=string::npos)skimName="tree_WJetsToLNu_HT-800to1200_MC2017.root";
	else if(currentFile.find("WJetsToLNu_HT-1200To2500")!=string::npos)skimName="tree_WJetsToLNu_HT-1200to2500_MC2017.root";
	else if(currentFile.find("WJetsToLNu_HT-2500ToInf")!=string::npos)skimName="tree_WJetsToLNu_HT-2500toInf_MC2017.root"; 
	else if(currentFile.find("tW_antitop")!=string::npos)skimName="tree_ST_tW_antitop_MC2017.root";
	else if(currentFile.find("tW_top")!=string::npos)skimName="tree_ST_tW_top_MC2017.root";
	else if(currentFile.find("t-channel_top")!=string::npos)skimName="tree_ST_t-channel_top_MC2017.root";
	else if(currentFile.find("t-channel_antitop")!=string::npos)skimName="tree_ST_t-channel_antitop_MC2017.root"; 
	else if(currentFile.find("s-channel")!=string::npos)skimName="tree_ST_s-channel_MC2017.root"; 
	else if(currentFile.find("ZZZ")!=string::npos)skimName="tree_ZZZ_MC2017.root"; 
	else if(currentFile.find("ZZTo2L2Q")!=string::npos)skimName="tree_ZZTo2L2Q_MC2017.root";
	else if(currentFile.find("WZZ")!=string::npos)skimName="tree_WZZ_MC2017.root";
	else if(currentFile.find("WZTo1L3Nu")!=string::npos)skimName="tree_WZTo1L3Nu_MC2017.root";
	else if(currentFile.find("WZTo1L1Nu2Q")!=string::npos)skimName="tree_WZTo1L1Nu2Q_MC2017.root";
	else if(currentFile.find("WWZ")!=string::npos)skimName="tree_WWZ_MC2017.root";
	else if(currentFile.find("WWTo2L2Nu")!=string::npos)skimName="tree_WWTo2L2Nu_MC2017.root";
	else if(currentFile.find("WWTo1L1Nu2Q")!=string::npos)skimName="tree_WWTo1L1Nu2Q_MC2017.root";
	else if(currentFile.find("TTZToQQ")!=string::npos)skimName="tree_TTZToQQ_MC2017.root";
	else if(currentFile.find("TTZToLLNuNu")!=string::npos)skimName="tree_TTZToLLNuNu_MC2017.root";
	else if(currentFile.find("TTWJetsToQQ")!=string::npos)skimName="tree_TTWJetsToQQ_MC2017.root";
	else if(currentFile.find("TTWJetsToLNu")!=string::npos)skimName="tree_TTWJetsToLNu_MC2017.root";
	else if(currentFile.find("TTTT")!=string::npos)skimName="tree_TTTT_MC2017.root";
	else if(currentFile.find("TTGJets")!=string::npos)skimName="tree_TTGJets_MC2017.root";
	sprintf(SkimFile,"%s/%s",SkimFilePath.c_str(),skimName.c_str());

	//std::cout<<" currFileName "<<currFileName<<" skimname "<<skimName<<endl;
        // Make sure you don't have negative number of events per sample
	//*AR-180314-Histograms h_CR_SB,h_SR_SB,h_CR_SF_SB,h_SR_SF_SB are written newly for every tree
	//*AR-180322-At this step, these are just empty, declared histograms.
        PushHist(h_CR_SB_copy, h_CR_SB);
        PushHist(h_SR_SB_copy, h_SR_SB);
        PushHist(h_SR_LL_SB_copy, h_SR_LL_SB);
        PushHist(h_SR_Hadtau_SB_copy, h_SR_Hadtau_SB);

        PushHist(h_CR_SF_SB_copy, h_CR_SF_SB);
        PushHist(h_SR_SF_SB_copy, h_SR_SF_SB);
        PushHist(h_SR_SF_LL_SB_copy, h_SR_SF_LL_SB);
        PushHist(h_SR_SF_Hadtau_SB_copy, h_SR_SF_Hadtau_SB);

	//*AR-180314-individual SF histograms and vector of SF histograms to be used need to be reset for every new tree( and not for event).
        // Open histograms for SFs
        if(SFCR_histFile!=0 || SFSR_histFile!=0){
            h_el_SFCR_etaPt = 0;
            h_el_SFCR_SB = 0;
            h_el_SFSR_etaPt = 0;
            h_el_SFSR_SB = 0;

            h_mu_SFCR_etaPt = 0;
            h_mu_SFCR_SB = 0;
            h_mu_SFSR_etaPt = 0;
            h_mu_SFSR_SB = 0;

            h_di_SFCR_SB = 0;
            h_di_SFSR_SB = 0;

	    //*AR-As we are using push_back for every new tree, we need to clear existing vector of SFs before pushing SF histograms corresponding to new tree. 
	    Vec_scale_el_SFSR_SB.clear();
	    Vec_scale_el_SFCR_SB.clear();
	    Vec_scale_mu_SFSR_SB.clear();
	    Vec_scale_mu_SFCR_SB.clear();
	    Vec_PDF_el_SFSR_SB.clear();
	    Vec_PDF_el_SFCR_SB.clear();
	    Vec_PDF_mu_SFSR_SB.clear();
	    Vec_PDF_mu_SFCR_SB.clear();

	    /*
	    for(int iacc=0; iacc < Vec_scale_el_SFCR_SB.size(); iacc++){
	      Vec_scale_el_SFSR_SB.at(iacc)->Reset(); 
	      Vec_scale_el_SFCR_SB.at(iacc)->Reset();
	      Vec_scale_mu_SFSR_SB.at(iacc)->Reset(); 
	      Vec_scale_mu_SFCR_SB.at(iacc)->Reset();
	    }
*/
            SFCR_histFile->Close();
            SFCR_histFile = 0;
            SFSR_histFile->Close();
            SFSR_histFile = 0;
	    
        }

        TString SFCR_histFile_path = "";
        TString SFSR_histFile_path = "";
	//*AR-180314-Selects appropriate SF file based on tree name. 
        if((std::string(currFileName.Data()).find(std::string("TTJets"))) != std::string::npos){
            SFCR_histFile_path = "SFCR_0.root";
            SFSR_histFile_path = "SFSR_0.root";
        }else if((std::string(currFileName.Data()).find(std::string("WJetsToLNu"))) != std::string::npos){
            SFCR_histFile_path = "SFCR_1.root";
            SFSR_histFile_path = "SFSR_1.root";
        }else if((std::string(currFileName.Data()).find(std::string("ST_"))) != std::string::npos){
            SFCR_histFile_path = "SFCR_2.root";
            SFSR_histFile_path = "SFSR_2.root";
        }else{
            SFCR_histFile_path = "SFCR_3.root";
            SFSR_histFile_path = "SFSR_3.root";
        }
	//*AR-180302-SF Histograms are read from respective SF files 
	//	std::cout<<" SFCR_histFile_path "<<SFCR_histFile_path<<endl;
        SFCR_histFile = TFile::Open(SFCR_histFile_path, "READ");
        SFSR_histFile = TFile::Open(SFSR_histFile_path, "READ");

	//	std::cout<<" read SF files "<<endl;
	//* AR 180314--For scale systematics we have vector of SF histograms to be read while for nominal case only one histogram of every type 
	if(ScaleAccSys){
	  char tempname[200];
	  for(int iacc=0; iacc < Scalesize; iacc++){
	    sprintf(tempname,"h_scale_el_SFCR_SB_%d",iacc);
	    h_el_SFCR_SB = (TH1D*)SFCR_histFile->FindObjectAny(tempname);
	    Vec_scale_el_SFCR_SB.push_back(h_el_SFCR_SB);

	    sprintf(tempname,"h_scale_el_SFSR_SB_%d",iacc);
	    h_el_SFSR_SB = (TH1D*)SFSR_histFile->FindObjectAny(tempname);
	    Vec_scale_el_SFSR_SB.push_back(h_el_SFSR_SB);

	    sprintf(tempname,"h_scale_mu_SFCR_SB_%d",iacc);
	    h_mu_SFCR_SB = (TH1D*)SFCR_histFile->FindObjectAny(tempname);
	    Vec_scale_mu_SFCR_SB.push_back(h_mu_SFCR_SB);

	    sprintf(tempname,"h_scale_mu_SFSR_SB_%d",iacc);
	    h_mu_SFSR_SB = (TH1D*)SFSR_histFile->FindObjectAny(tempname);
	    Vec_scale_mu_SFSR_SB.push_back(h_mu_SFSR_SB);
	  }
	  std::cout<<" second ScaleAcc**** "<<endl; 
	  std::cout<<" size "<<Vec_scale_mu_SFSR_SB.size()<<endl;
	}

	else if(PDFAccSys){
	  char tempname[200];
	  for(int iacc=0; iacc < PDFsize; iacc++){
	    sprintf(tempname,"h_PDF_el_SFCR_SB_%d",iacc);
	    h_el_SFCR_SB = (TH1D*)SFCR_histFile->FindObjectAny(tempname);
	    Vec_PDF_el_SFCR_SB.push_back(h_el_SFCR_SB);

	    sprintf(tempname,"h_PDF_el_SFSR_SB_%d",iacc);
	    h_el_SFSR_SB = (TH1D*)SFSR_histFile->FindObjectAny(tempname);
	    Vec_PDF_el_SFSR_SB.push_back(h_el_SFSR_SB);

	    sprintf(tempname,"h_PDF_mu_SFCR_SB_%d",iacc);
	    h_mu_SFCR_SB = (TH1D*)SFCR_histFile->FindObjectAny(tempname);
	    Vec_PDF_mu_SFCR_SB.push_back(h_mu_SFCR_SB);

	    sprintf(tempname,"h_PDF_mu_SFSR_SB_%d",iacc);
	    h_mu_SFSR_SB = (TH1D*)SFSR_histFile->FindObjectAny(tempname);
	    Vec_PDF_mu_SFSR_SB.push_back(h_mu_SFSR_SB);
	  }
	  std::cout<<" second PDFAcc**** "<<endl; 
	  std::cout<<" size "<<Vec_PDF_mu_SFSR_SB.size()<<endl;
	}
	  
	else{
	  //	  std::cout<<" segvio1**** "<<endl;
	  h_el_SFCR_etaPt = (TH2D*) SFCR_histFile->Get("h_el_SFCR_etaPt")->Clone();
	  h_el_SFCR_SB = (TH1D*) SFCR_histFile->Get("h_el_SFCR_SB")->Clone();
	  h_mu_SFCR_etaPt = (TH2D*) SFCR_histFile->Get("h_mu_SFCR_etaPt")->Clone();
	  h_mu_SFCR_SB = (TH1D*) SFCR_histFile->Get("h_mu_SFCR_SB")->Clone();
	  //	  h_di_SFCR_SB = (TH1D*) SFCR_histFile->Get("h_di_SFCR_SB")->Clone();
	  
	  h_el_SFSR_etaPt = (TH2D*) SFSR_histFile->Get("h_el_SFSR_etaPt")->Clone();
	  h_el_SFSR_SB = (TH1D*) SFSR_histFile->Get("h_el_SFSR_SB")->Clone();        
	  h_mu_SFSR_etaPt = (TH2D*) SFSR_histFile->Get("h_mu_SFSR_etaPt")->Clone();
	  h_mu_SFSR_SB = (TH1D*) SFSR_histFile->Get("h_mu_SFSR_SB")->Clone();
	  //	  h_di_SFSR_SB = (TH1D*) SFSR_histFile->Get("h_di_SFSR_SB")->Clone();
	  /*	  
	  if(h_di_SFCR_SB->GetNbinsX() < 100){
            useCombinedBinsCR = true;
            std::cout<<"Using combined bins in CR"<<std::endl;
	  }
	  if(h_di_SFSR_SB->GetNbinsX() < 100){
            useCombinedBinsSR = true;
            std::cout<<"Using combined bins in SR"<<std::endl;
	  }
*/
	}
	
	//* AR-20180115-As following loop is not executing, it is not modified to account for JECSys effect.
        if(doISRcorr){
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
            btagcorr = new BTagCorrector();

            TFile *skimFile = TFile::Open(SkimFile, "READ");
            btagcorr->SetEffs(skimFile);
	    
            btagcorr->SetCalib(path_bTagCalib);
	    if(BtagSys){
	      btagcorr->SetBtagSFunc(-1); 
	      btagcorr->SetCtagSFunc(-1);
	      btagcorr->SetMistagSFunc(-1);
	    }        
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
    } //end of currentTree != treeName

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
    //*AR-180314--Here onward execution happens for every event

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
    
    //    std::cout<<"correction for prefirewt done "<<" weight "<<Weight<<endl;







    if(Weight < 0)
      return kTRUE;

    if(currentFile.find("TTJets_SingleLeptFromTbar")!=string::npos || currentFile.find("TTJets_SingleLeptFromT")!=string::npos || currentFile.find("DiLept")!=string::npos){
      madHTcut=600;
      if(madHT > madHTcut){
	//std::cout<<" currentTree "<<currentTree<<" entry "<<entry<<" madHT "<<madHT<< " &&&not passed&&& "<<endl;
	return kTRUE;
      }
    }
    //* AR-20180123-As following loop is not executing, it is not modified to account for JECSys effect.   
    if(doISRcorr){
        w_isr = isrcorr->GetCorrection(NJetsISR);
        Weight *= w_isr;
    }

    if(doBTagCorr){
      BinforMTEff= {Bin_, 0, 0, 0};
      if(JECSys)
	bTagProb = btagcorr->GetCorrections(MHT3JetLorentzVec,MHT3JetHadronFlavorvec,MHT3JetHTMaskvec);
      else
	bTagProb = btagcorr->GetCorrections(Jets,Jets_hadronFlavor,Jets_HTMask);
      
	if(JECSys)
	  bTagBins = {SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,0), SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,1), SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,2), newNJets < 3 ? 999 : SearchBins_BTags_->GetBinNumber(newHT,newMHT,newNJets,3)};
	else
	  bTagBins = {SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,0), SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,1), SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,2), NJets < 3 ? 999 : SearchBins_BTags_->GetBinNumber(HT,MHT,NJets,3)};
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

    if(doPUreweighting){
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

    //*AR:190109- gen electrons/ muons with abs(eta)<2.5, pT>5
    GenMuonsAccNum_ = GenMuonsAcc.size();
    GenElectronsAccNum_ = GenElectronsAcc.size();
    //    std::cout<<" GenMuonsAccNum_ "<<GenMuonsAccNum_<<" GenElectronsAccNum_ "<<GenElectronsAccNum_<<endl;
    //*AR: Here note that unlike SFMaker.C, we do not skip events if there is no gen lepton with pT>5 and eta<2.5
    //Define some helpful variables

    //*AR:190109- get pT, eta of gen electrons/ muons with abs(eta)<2.5, pT>5 
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

    // get isoTrack collection from full TAP collection.
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
    
    //*AR:190109- If there are gen electrons/ muons with abs(eta)<2.5, pT>5, match iso leptons/tracks to gen leptons: ElectronsPromptNum_,ElectronTracksPromptNum_,MuonsPromptNum_, MuonTrcksPromptNum_: number of reco leptons(passing id, iso criteria) and tracks matching to gen electrons/muons with pT>5 and eta<2.5
    // Apply SFs only to prompts

    //*AR:190109- As per definition, MuonsNum_ = Muons->size() and ElectronsNum_ = Electrons->size();

    //*AR:190109-Get number of electrons, muons passing id, iso
    for(unsigned j=0; j< ElectronsNum_; j++){
      if(Electrons_passIso->at(j)){
	ElectronsNumPassIdIso_++;
      }
    }

    for(unsigned j=0; j< MuonsNum_; j++){
      if(Muons_passIso->at(j) && Muons_mediumID->at(j)){
	MuonsNumPassIdIso_++;
      }
    }
    //    std::cout<<" ElectronsNumPassIdIso_ "<<ElectronsNumPassIdIso_<<" MuonsNumPassIdIso_ "<<MuonsNumPassIdIso_<<endl;
    for(unsigned i=0; i< GenElectronsAccNum_; i++){
        bool matched = false;
        for(unsigned j=0; j< ElectronsNum_; j++){
	  if(Electrons_passIso->at(j)){
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
                break;
            }
	  } //end of passIso condition
        }
        if(matched) continue;

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
    }

    for(unsigned i=0; i< GenMuonsAccNum_; i++){
        bool matched = false;
        for(unsigned j=0; j< MuonsNum_; j++){
	  if(Muons_passIso->at(j) && Muons_mediumID->at(j)){
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
            }
	  } //end of passIso condition
        }
        if(matched) continue; //* AR,180101---if a matching reco muon is found don't need to check for isoMuonTracks, hence skip rest of this loop and move to next gen muon

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
    //*AR-180606:Skip event if cases of (matched lepton+matched tracks) exceed number of gen leptons(ele/muons withpT>5 and eta<2.5), that is avoids double counting.

    if(GenMuonsAccNum_ < MuonsPromptNum_ + MuonTracksPromptNum_ || GenElectronsAccNum_ < ElectronsPromptNum_ + ElectronTracksPromptNum_){
        std::cout<<"Mu:"<<GenMuonsAccNum_<<"->"<<MuonsPromptNum_<<"+"<<MuonTracksPromptNum_<<std::endl;
        std::cout<<"El:"<<GenElectronsAccNum_<<"->"<<ElectronsPromptNum_<<"+"<<ElectronTracksPromptNum_<<std::endl;
        std::cout<<"Matching not successful. Skipping event."<<std::endl;
        return kTRUE;
    }

    //*AR, 180101- Steps up to here are similar to those in SFMaker.C

    Weight *= scaleFactorWeight;
    //    std::cout<<" weight after scaling lumi "<<Weight<<endl;
    int nLoops = 1;
    if(doBTagCorr) nLoops = (NJets == 2 ? 3 : 4);
    for(int i = 0; i < nLoops; i++){
      double WeightBtagProb = Weight*bTagProb.at(i);
      unsigned bTagBin = bTagBins.at(i);
      unsigned GetBinforMTEff=BinforMTEff.at(i);
      //      std::cout<<" segvio2**** "<<endl;
      // CONTROL REGION: if there is electron at reco level(after checking iso or id criteria), get it's mT
      if(ElectronsNumPassIdIso_ + MuonsNumPassIdIso_ == 1){ //*AR-180322--these are just reco objects, not matched to gen objects yet
	double SF = 1;
	double binSF = bTagBin; //based on (HT,MHT,Njet,Nbtag_true)
	//	    double bTagBin = (double)bTagBins.at(i);
	
	if(useCombinedBinsCR){
	  //*AR-180302-JEC Sys is considered here as it leads to change in the search bins, hence to remain consistent with search bins of histograms used in evaluating SFs. 
	  if(JECSys)
	    binSF = SearchBins_->GetCombinedBinNumber(newHT,newMHT,newNJets);
	  else
	    binSF = SearchBins_->GetCombinedBinNumber(HT,MHT,NJets);
	}
	//*AR: 180606: Three caes are considered here
	//1] there is a reco electron and gen electron with pT>5 and eta<2.5: Use SF(binSF) 2] there is a reco electron but no gen electron with pT>5 and eta<2.5 (gen lepton out of acceptance): SF=1 3] there is a reco electron and gen electron with pT>5 and eta<2.5 but no matched reco electron to gen electron: failed matching: SF=1 
	//*AR: 190117- MTWCalculator is defined in LLTools.h.
	//MTWCalculator(double metPt,double  metPhi,double  lepPt,double  lepPhi, int scaleMet = 0). So here metPt and metPhi are directly after scaling MET with JEC uncertaintyand is not further scaled by 1.3 or 0.7 which would have been case if scaleMet != 0
	
	if(ElectronsNumPassIdIso_ == 1){
	  for(unsigned j=0; j< ElectronsNum_; j++){
	    if(Electrons_passIso->at(j)){
	      mtw = Electrons_MTW->at(j);
	      //*AR-180329--why METUp, METDown sizes are 7
	      /*	  for(unsigned int k=0;k<METUp->size();k++){
			  std::cout<<" k "<<k<<" met up"<<METUp->at(k)<<endl;
			  }
			  for(unsigned int k=0;k<METDown->size();k++){
			  std::cout<<" k "<<k<<" met down"<<METDown->at(k)<<endl;
			  }
	      */
	      //	  std::cout<<" up "<<METUp->size()<<" dn "<<METDown->size()<<endl;
	      //*AR--180329--MTSys has propagation of JEC uncertainties to MET, hence METUp need not be greater than MET and METDn need not be less than MET.
	      if(MTSys){
		if(SysUp)
		  mtw = MTWCalculator(METUp->at(1),METPhiUp->at(1), Electrons->at(j).Pt(), Electrons->at(j).Phi(), 0);
		if(SysDn)
		  mtw = MTWCalculator(METDown->at(1),METPhiDown->at(1), Electrons->at(j).Pt(), Electrons->at(j).Phi(), 0);
	      }
	      
	  //	 double  mtwCalc =  MTWCalculator(MET,METPhi, Electrons->at(0).Pt(), Electrons->at(0).Phi(), 0);
	 //	 std::cout<<" mtw "<<mtw<<" mtwCalc "<<mtwCalc<<endl;
	  //*AR-180101-here although scale factor is read from histogram file, if reco electron is not prompt(matching to gen electron), scale factor is reset to 1 later, which is expected as SF histograms are filled based on number of reco electrons/muons which are prompt.
	      if(GenElectronsAccNum_ == 1 && GenMuonsAccNum_ == 0){
		if(ScaleAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < Scalesize; iacc++){		  
		    Vec_SF.push_back(GetSF(Vec_scale_el_SFCR_SB.at(iacc), binSF));
		    //		      std::cout<<" btags "<<BTags<<" binSF "<<binSF<<" binSF_SF "<<GetSF(Vec_scale_el_SFCR_SB.at(iacc), binSF)<<" bTagBin "<<bTagBin<<" bTagBin_SF "<<GetSF(Vec_scale_el_SFCR_SB.at(iacc), binSF)<<endl;
		    //		std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" size_SF_1 "<< Vec_SF.size()<<endl;
		  }
		}
		else if(PDFAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < PDFsize; iacc++){		  
		    Vec_SF.push_back(GetSF(Vec_PDF_el_SFCR_SB.at(iacc), binSF));
		    //		      std::cout<<" btags "<<BTags<<" binSF "<<binSF<<" binSF_SF "<<GetSF(Vec_PDF_el_SFCR_SB.at(iacc), binSF)<<" bTagBin "<<bTagBin<<" bTagBin_SF "<<GetSF(Vec_PDF_el_SFCR_SB.at(iacc), binSF)<<endl;
		    //		std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" size_SF_1 "<< Vec_SF.size()<<endl;
		  }
		}
		else
		  SF = GetSF(h_el_SFCR_SB,binSF);  //as there was a reco electron passing id, iso and also gen electron passing pT>5 and eta<2.5, pick SF as a function of search bins
		//		std::cout<<"  el CR SF "<<SF<<endl;
	      } //end of if GenElectronsAccNum_ == 1, ie gen electron with pT>5 and eta<2.5
	      //else if((GenElectronsAccNum_ == 2 && GenMuonsAccNum_ == 0) || (GenElectronsAccNum_ == 1 && GenMuonsAccNum_ == 1)){
	      //  SF = GetSF(h_di_SFCR_SB, binSF)*GetSF(h_di_SFSR_SB, binSF);
	      //}
	      else{ //*AR-180321--there is reco electron but no gen electron with pt>5 and eta<2.5, i.e corresponding to fake, out of acceptance reconstructed electrons
		if(ScaleAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < Scalesize; iacc++){
		    Vec_SF.push_back(1);
		    //		std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" size_SF_2 "<< Vec_SF.size()<<endl;		      
		  }
		  std::cout<<" forth ScaleAcc**** "<<endl; 
		}
		else if(PDFAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < PDFsize; iacc++){
		    Vec_SF.push_back(1);
		    //std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" size_SF_2 "<< Vec_SF.size()<<endl;		      
		  }
		  std::cout<<" forth PDFAcc**** "<<endl; 
		}
		else
		  SF = 1; //as there was a reco electron passing id, iso but no gen electron passing pT>5 and eta<2.5, let SF=1
		//		std::cout<<"  no gen ele passing acceptance "<<SF<<endl;
	      } //end of else of "if(GenElectronsAccNum_ == 1 && GenMuonsAccNum_ == 0)"
	      
                // Don't correct for non-prompts
	      if(ElectronsPromptNum_==0){
		if(ScaleAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < Scalesize; iacc++){
		    Vec_SF.push_back(1);
		    //std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" size_SF_3 "<< Vec_SF.size()<<endl;
		  }
		}
		else if(PDFAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < PDFsize; iacc++){
		    Vec_SF.push_back(1);
		    //std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" size_SF_3 "<< Vec_SF.size()<<endl;
		  }
		}
		else
		  SF = 1; //as there was a reco electron passing id, iso but there was no electron matched to gen electron passing pT>5 and eta<2.5, let SF=1
		//		std::cout<<"  gen ele exists but not matched to reco "<<SF<<endl;

	      } //end of ElectronsPromptNum_==0
	    } //end of Electrons_passIso  
	  } //end of loop over ElectronsNum_
	} //end of ElectronsNumPassIdIso_ == 1
	    //Similar three cases as for electrons
	if(MuonsNumPassIdIso_ == 1){
	  for(unsigned j=0; j< MuonsNum_; j++){
	    if(Muons_passIso->at(j) && Muons_mediumID->at(j)){
	      mtw = Muons_MTW->at(j);
	      if( GenMuonsAccNum_ == 1 && Muons->at(j).Pt()>20 && abs(Muons->at(j).Eta())<2.1){
		//		std::cout<<" entry "<<entry<<" i "<<i<<"beforeMT.. "<<" MuonsNum_ "<<MuonsNum_<<" electronsNum_ "<<ElectronsNum_<<" mtw "<<mtw<<endl;
		h_CR_BeforeMT->Fill(GetBinforMTEff,Weight);
	      }
	  //std::cout<<" met "<<MET<<" up1 "<<METUp->at(1)<<" dn1 "<<METDown->at(1)<<endl;
	      if(MTSys){
		if(SysUp)
		  mtw = MTWCalculator(METUp->at(1),METPhiUp->at(1), Muons->at(j).Pt(), Muons->at(j).Phi(), 0);
		if(SysDn)
		  mtw = MTWCalculator(METDown->at(1),METPhiDown->at(1), Muons->at(j).Pt(), Muons->at(j).Phi(), 0);
	      }

	      if(GenElectronsAccNum_ == 0 && GenMuonsAccNum_ == 1){
		if(ScaleAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < Scalesize; iacc++){
		    Vec_SF.push_back(GetSF(Vec_scale_mu_SFCR_SB.at(iacc), binSF)); 
		  }
		}
		else if(PDFAccSys){ 
		  Vec_SF.clear();
		  for(int iacc=0; iacc < PDFsize; iacc++){
		    Vec_SF.push_back(GetSF(Vec_PDF_mu_SFCR_SB.at(iacc), binSF)); 
		  }
		}
		else
		  SF = GetSF(h_mu_SFCR_SB, binSF);  //as there was a reco muon passing id, iso and also gen muon passing pT>5 and eta<2.5, pick SF as a function of search bins
		//		std::cout<<"  mu CR SF "<<SF<<endl;
 
	      }
	      //else if((GenElectronsAccNum_ == 0 && GenMuonsAccNum_ == 2) || (GenElectronsAccNum_ == 1 && GenMuonsAccNum_ == 1)){
	      //  SF = GetSF(h_di_SFCR_SB, binSF)*GetSF(h_di_SFSR_SB, binSF);
	      //}
	      else{
		if(ScaleAccSys){
		  Vec_SF.clear(); 
		  for(int iacc=0; iacc < Scalesize; iacc++){
		    Vec_SF.push_back(1);
		  }
		}
		else if(PDFAccSys){
		  Vec_SF.clear(); 
		  for(int iacc=0; iacc < PDFsize; iacc++){
		    Vec_SF.push_back(1);
		  }
		}
		else
		  SF = 1; //as there was a reco electron passing id, iso but no gen electron passing pT>5 and eta<2.5, let SF=1
		//		std::cout<<"  no gen mu passing acceptance "<<SF<<endl;

	      }
	      
	      // Don't correct for non-prompts
	      if(MuonsPromptNum_==0){
		if(ScaleAccSys){
		  Vec_SF.clear(); 
		  for(int iacc=0; iacc < Scalesize; iacc++){
		    Vec_SF.push_back(1);
		  }
		}
		else if(PDFAccSys){
		  Vec_SF.clear(); 
		  for(int iacc=0; iacc < PDFsize; iacc++){
		    Vec_SF.push_back(1);
		  }
		}
		else
		  SF = 1; //as there was a reco muon passing id, iso but there was no muon matched to gen muon passing pT>5 and eta<2.5, let SF=1
		//		std::cout<<"  reco mu exists but not matched to gen "<<SF<<endl;

	      } //end of MuonsPromptNum_==0
	    } ////end of muons_passIso
	  }//end of loop over MuonsNum_
	}//end of MuonsNumPassIdIso_ == 1
	//*AR-180101-skips event if the electron/muon found at reco level has mT>100
	if(mtw > 100) return kTRUE;
	//	std::cout<<" entry "<<entry<<" i "<<i<<" MuonsNum_ "<<MuonsNum_<<" electronsNum_ "<<ElectronsNum_<<" mtw "<<mtw<<endl;
	/*	
		if(MuonsNum_ == 1 && GenMuonsAccNum_ == 1 && Muons->at(0).Pt()>20 && abs(Muons->at(0).Eta())<2.1){
		std::cout<<" entry "<<entry<<" i "<<i<<"now fill afterMT.. "<<" mtw "<<mtw<<" GetBinforMTEff "<<GetBinforMTEff<<endl;
		h_CR_AfterMT->Fill(GetBinforMTEff,Weight);
		}
	*/
	if(ScaleAccSys){
	  for(int iacc=0; iacc < Scalesize; iacc++){ 
	    Vec_scale_CR_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*ScaleWeights->at(iacc));
	    
	    Vec_scale_CR_SF_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*ScaleWeights->at(iacc)*Vec_SF.at(iacc));
	  }
	}
	else if(PDFAccSys){
	  for(int iacc=0; iacc < PDFsize; iacc++){ 
	    Vec_PDF_CR_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*PDFWeights->at(iacc));
	    //		if(iacc==0 && binSF==137)
	    //std::cout<<" evt "<<entry<<" loop "<<i<<" true b "<<BTags<<" sf "<< Vec_SF.at(iacc)<<endl;
	    //		if(iacc==9 && binSF==137)
	    //std::cout<<" evt "<<entry<<" loop "<<i<<" true b "<<BTags<<" Weight "<<Weight<<" bProb "<<bTagProb.at(i)<<" WeightBtagProb in CR "<<WeightBtagProb<< " PDF_9 "<<PDFWeights->at(iacc)<<" PDF_10 "<<PDFWeights->at(iacc+1)<<endl;
	    Vec_PDF_CR_SF_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*PDFWeights->at(iacc)*Vec_SF.at(iacc));
	  }
	}
	else{
	  h_CR_SB_copy->Fill(binSF, WeightBtagProb);
	  //if(binSF==137)
	  //std::cout<<" evt "<<entry<<" loop "<<i<<" true b "<<BTags<<" sf "<< SF<<endl;
	  h_CR_SF_SB_copy->Fill(binSF, WeightBtagProb*SF);
	}
      } //end of ElectronsNumPassIdIso_ + MuonsNumPassIdIso_ == 1
      
      // SIGNAL REGION
      if(ElectronsNumPassIdIso_ + MuonsNumPassIdIso_ == 0 && isoTracksNum == 0){
	  //Four cases possible here:
	  //1] No lepton at gen level: skip event as SR requires there is a lepton at gen level but no lepton at reco level 2] there was gen electron with pt>5 and eta<2.5: use ele_SF in SR 3] there was gen muon with pt>5 and eta<2.5: use muon_SF in SR 4] no gen electron/muon with pt>5 and eta<2.5(out of acceptance) : use SF=1
	double SF = 1;
	//            double binSF = Bin_;
	double binSF = bTagBin;
	
	if(useCombinedBinsSR){
	  if(JECSys)
	    binSF = SearchBins_->GetCombinedBinNumber(newHT,newMHT,newNJets);
	  else
	    binSF = SearchBins_->GetCombinedBinNumber(HT,MHT,NJets);
	}
	
	if(GenElectronsNum_ + GenMuonsNum_ == 0){
	  //	  std::cout<<" gen_taus "<<GenTaus->size()<<" gen taus had bool "<<GenTaus_had->size()<<endl;
	  if(GenTausNum_ > 0){ //gen taus size
	    int HadronicTaus=0;
	    for(unsigned i=0; i<GenTaus->size();i++){
	      if(GenTaus_had->at(i)==1){ //checks if tau is hadronic tau
		//	std::cout<<" it's a hadronic tau "<<endl;
		HadronicTaus++;
	      }
	    }
	    if(HadronicTaus >0){
	      if(ScaleAccSys){
		for(int iacc=0; iacc < Scalesize; iacc++){ 
		  Vec_scale_SR_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*ScaleWeights->at(iacc));
		  Vec_scale_SR_SF_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*ScaleWeights->at(iacc));
		}
	      }
	      else if(PDFAccSys){
		for(int iacc=0; iacc < PDFsize; iacc++){ 
		  //if(iacc==9 && binSF==137)
		  //std::cout<<" evt "<<entry<<" loop "<<i<<" true b "<<BTags<<" Weight "<<Weight<<" bProb "<<bTagProb.at(i)<<" WeightBtagProb in SR "<<WeightBtagProb<< " PDF_9 "<<PDFWeights->at(iacc)<<" PDF_10 "<<PDFWeights->at(iacc+1)<<endl;
		  
		  Vec_PDF_SR_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*PDFWeights->at(iacc));
		  Vec_PDF_SR_SF_SB_copy.at(iacc)->Fill(binSF,WeightBtagProb*PDFWeights->at(iacc));
		}
	      }
	      else{
		//	std::cout<<" filling tau histogram "<<endl;
		h_SR_Hadtau_SB_copy->Fill(binSF, WeightBtagProb);
		h_SR_SF_Hadtau_SB_copy->Fill(binSF, WeightBtagProb);
		
		h_SR_SB_copy->Fill(binSF, WeightBtagProb);
		h_SR_SF_SB_copy->Fill(binSF, WeightBtagProb);
	      }
	    }
	  }
	} //end of GenElectronsNum_ + GenMuonsNum_ == 0
	else{
	  if(GenElectronsAccNum_ == 1 && GenMuonsAccNum_ == 0){
	    if(ScaleAccSys){
	      Vec_SF.clear(); 
	      for(int iacc=0; iacc < Scalesize; iacc++){
		Vec_SF.push_back(GetSF(Vec_scale_el_SFSR_SB.at(iacc), binSF)); 
	      }
	    }
	    else if(PDFAccSys){
	      Vec_SF.clear(); 
	      for(int iacc=0; iacc < PDFsize; iacc++){
		Vec_SF.push_back(GetSF(Vec_PDF_el_SFSR_SB.at(iacc), binSF)); 
	      }
	    }
	    else
	      SF = GetSF(h_el_SFSR_SB,binSF);
	    //	    std::cout<<"  el SR SF "<<SF<<endl;
	    
	  } //end of GenElectronsAccNum_ == 1 && GenMuonsAccNum_ == 0
	  
	  else if(GenElectronsAccNum_ == 0 && GenMuonsAccNum_ == 1){
	    if(ScaleAccSys){ 
	      Vec_SF.clear();
	      for(int iacc=0; iacc < Scalesize; iacc++){
		//		  std::cout<<" ele "<<GenElectronsAccNum_<<" mu "<<GenMuonsAccNum_<<" third ScaleAcc**** "<<endl;
		//		  SF=GetSF(Vec_scale_mu_SFSR_SB.at(iacc), binSF); 
		Vec_SF.push_back(GetSF(Vec_scale_mu_SFSR_SB.at(iacc), binSF));
		//		  std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" scale "<<GetSF(Vec_scale_mu_SFSR_SB.at(iacc),binSF)<<endl;
		
		//		  Vec_SF.push_back(GetSF(Vec_scale_mu_SFSR_SB.at(iacc), binSF)); 
	      }
	    }
	    else if(PDFAccSys){ 
	      Vec_SF.clear();
	      for(int iacc=0; iacc < PDFsize; iacc++){
		//		  std::cout<<" ele "<<GenElectronsAccNum_<<" mu "<<GenMuonsAccNum_<<" third PDFAcc**** "<<endl;
		//		  SF=GetSF(Vec_PDF_mu_SFSR_SB.at(iacc), binSF); 
		Vec_SF.push_back(GetSF(Vec_PDF_mu_SFSR_SB.at(iacc), binSF));
		//		  std::cout<<" entry "<<entry<<" nloop "<<i<<" iacc "<<iacc<<" PDF "<<GetSF(Vec_PDF_mu_SFSR_SB.at(iacc),binSF)<<endl;
		
		//		  Vec_SF.push_back(GetSF(Vec_PDF_mu_SFSR_SB.at(iacc), binSF)); 
	      }
	      
	    }
	    else
	      SF = GetSF(h_mu_SFSR_SB, binSF); 
	    //	    std::cout<<"  mu SR SF "<<SF<<endl;
	  } //end of (GenElectronsAccNum_ == 0 && GenMuonsAccNum_ == 1)
	  //else if(GenElectronsAccNum_ + GenMuonsAccNum_ == 2){
	  //  SF = GetSF(h_di_SFSR_SB, binSF)*GetSF(h_di_SFSR_SB, binSF); 
	  //}
	  else{   //GenElectronsAccNum_ == 0 && GenMuonsAccNum_ == 0
	    if(ScaleAccSys){ 
	      Vec_SF.clear();
	      for(int iacc=0; iacc < Scalesize; iacc++){
		Vec_SF.push_back(1);
	      }
	    }
	    else if(PDFAccSys){ 
	      Vec_SF.clear();
	      for(int iacc=0; iacc < PDFsize; iacc++){
		Vec_SF.push_back(1);
	      }
	    }
	    else
	      SF = 1;
	  } //end of GenElectronsAccNum_ == 0 && GenMuonsAccNum_ == 0
	  
	  if(ScaleAccSys){
	    for(int iacc=0; iacc < Scalesize; iacc++){ 
	      Vec_scale_SR_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*ScaleWeights->at(iacc));
	      Vec_scale_SR_SF_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*ScaleWeights->at(iacc)*Vec_SF.at(iacc));
	    }
	  }
	  else if(PDFAccSys){
	    for(int iacc=0; iacc < PDFsize; iacc++){ 
	      //if(iacc==9 && binSF==137)
	      //std::cout<<" evt "<<entry<<" loop "<<i<<" true b "<<BTags<<" Weight "<<Weight<<" bProb "<<bTagProb.at(i)<<" WeightBtagProb in SR "<<WeightBtagProb<< " PDF_9 "<<PDFWeights->at(iacc)<<" PDF_10 "<<PDFWeights->at(iacc+1)<<endl;
	      
	      Vec_PDF_SR_SB_copy.at(iacc)->Fill(binSF, WeightBtagProb*PDFWeights->at(iacc));
	      Vec_PDF_SR_SF_SB_copy.at(iacc)->Fill(binSF,WeightBtagProb*PDFWeights->at(iacc)*Vec_SF.at(iacc));
	    }
	  }
	  
	  else{
	    //	    std::cout<<" filling lost lepton histogram "<<endl;
	    h_SR_LL_SB_copy->Fill(binSF, WeightBtagProb);
	    h_SR_SF_LL_SB_copy->Fill(binSF, WeightBtagProb*SF);


	    h_SR_SB_copy->Fill(binSF, WeightBtagProb);
	    h_SR_SF_SB_copy->Fill(binSF, WeightBtagProb*SF);
	  }
	} //end of GenElectronsNum_ + GenMuonsNum_ != 0
      } //end of ElectronsNumPassIdIso_ + MuonsNumPassIdIso_ == 0 && isoTracksNum == 0
      
    } //end over nLoops
    
    return kTRUE;
}

void TFMaker::SlaveTerminate()
{
  std::cout<<"***TFMaker::SlaveTerminate***"<<std::endl;
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.

    //std::cout<<"--- QCD binning ---"<<std::endl;
    //SearchBinsQCD_->PrintUsed();

    std::cout<<"--- Search bins ---"<<std::endl;
    //SearchBins_->PrintUsedCombined();  
    SearchBins_->PrintUsed();  
}

void TFMaker::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
  std::cout<<"***TFMaker::Terminate***"<<std::endl;
    // Draw Options
    gStyle->SetPaintTextFormat("5.2f");
    gStyle->SetStatW(0.1);
    gStyle->SetStatH(0.1);
    gStyle->SetStatY(202);
    gStyle->SetTitleYOffset(1.3);

    gStyle->SetPalette(87);
    gStyle->SetMarkerSize(1.3);

    TFile *outPutFile = new TFile(fileName,"RECREATE");

    h_CR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CR_SB"));
    h_CR_SF_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CR_SF_SB"));
    h_SR_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SB"));
    h_SR_SF_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SF_SB"));
    h_SR_LL_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_LL_SB"));
    h_SR_SF_LL_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SF_LL_SB"));
    h_SR_Hadtau_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_Hadtau_SB"));
    h_SR_SF_Hadtau_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SF_Hadtau_SB"));
   
    h_0L1L_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_0L1L_SB"));
    h_0L1L_SF_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_0L1L_SF_SB"));
    h_0L1L_LL_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_0L1L_LL_SB"));
    h_0L1L_SF_LL_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_0L1L_SF_LL_SB"));
    h_0L1L_Hadtau_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_0L1L_Hadtau_SB"));
    h_0L1L_SF_Hadtau_SB = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_0L1L_SF_Hadtau_SB"));

    h_CR_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CR_SB_copy"));
    h_CR_SF_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CR_SF_SB_copy"));
    h_SR_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SB_copy"));
    h_SR_SF_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SF_SB_copy"));
    h_SR_LL_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_LL_SB_copy"));
    h_SR_SF_LL_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SF_LL_SB_copy"));
    h_SR_Hadtau_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_Hadtau_SB_copy"));
    h_SR_SF_Hadtau_SB_copy = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_SR_SF_Hadtau_SB_copy"));

    h_CR_BeforeMT = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CR_BeforeMT"));
    h_CR_AfterMT = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_CR_AfterMT"));
    h_MTEff = dynamic_cast<TH1D*>(GetOutputList()->FindObject("h_MTEff"));
    std::cout<<" seg vio1 "<<endl;
    PushHist(h_CR_SB_copy, h_CR_SB);
    PushHist(h_SR_SB_copy, h_SR_SB);
    PushHist(h_SR_LL_SB_copy, h_SR_LL_SB);
    PushHist(h_SR_Hadtau_SB_copy, h_SR_Hadtau_SB);

    PushHist(h_CR_SF_SB_copy, h_CR_SF_SB);
    PushHist(h_SR_SF_SB_copy, h_SR_SF_SB);
    PushHist(h_SR_SF_LL_SB_copy, h_SR_SF_LL_SB);
    PushHist(h_SR_SF_Hadtau_SB_copy, h_SR_SF_Hadtau_SB);
    
    if(ScaleAccSys){
      for(int iacc=0; iacc < Scalesize; iacc++){
	Vec_scale_0L1L_SB.at(iacc)->Reset();
	Vec_scale_0L1L_SF_SB.at(iacc)->Reset();
	Vec_scale_0L1L_SB.at(iacc)->Divide(Vec_scale_SR_SB_copy.at(iacc),Vec_scale_CR_SB_copy.at(iacc));
	Vec_scale_0L1L_SF_SB.at(iacc)->Divide(Vec_scale_SR_SF_SB_copy.at(iacc),Vec_scale_CR_SF_SB_copy.at(iacc));
      }
    }
    else if(PDFAccSys){
      for(int iacc=0; iacc < PDFsize; iacc++){
	Vec_PDF_0L1L_SB.at(iacc)->Reset();
	Vec_PDF_0L1L_SF_SB.at(iacc)->Reset();
	Vec_PDF_0L1L_SB.at(iacc)->Divide(Vec_PDF_SR_SB_copy.at(iacc),Vec_PDF_CR_SB_copy.at(iacc));
	Vec_PDF_0L1L_SF_SB.at(iacc)->Divide(Vec_PDF_SR_SF_SB_copy.at(iacc),Vec_PDF_CR_SF_SB_copy.at(iacc));
      }
    }
    else{
      h_0L1L_SB->Reset();
      h_0L1L_SB->Divide(h_SR_SB, h_CR_SB);
      h_0L1L_LL_SB->Reset();
      h_0L1L_LL_SB->Divide(h_SR_LL_SB, h_CR_SB);
      h_0L1L_Hadtau_SB->Reset();
      h_0L1L_Hadtau_SB->Divide(h_SR_Hadtau_SB, h_CR_SB);

      h_0L1L_SF_SB->Reset();
      h_0L1L_SF_SB->Divide(h_SR_SF_SB, h_CR_SF_SB);
      h_0L1L_SF_LL_SB->Reset();
      h_0L1L_SF_LL_SB->Divide(h_SR_SF_LL_SB, h_CR_SF_SB);
      h_0L1L_SF_Hadtau_SB->Reset();
      h_0L1L_SF_Hadtau_SB->Divide(h_SR_SF_Hadtau_SB, h_CR_SF_SB);

      h_MTEff->Reset();
      h_MTEff->Add(h_CR_AfterMT);
      h_MTEff->Divide(h_CR_BeforeMT);
      
    }

    for(int nX = 1; nX <= h_0L1L_SB->GetXaxis()->GetNbins(); ++nX){
	if(ScaleAccSys){
	  for(int iacc=0; iacc < Scalesize; iacc++){
	    if(Vec_scale_0L1L_SB.at(iacc)->GetBinContent(nX) < 0)std::cout<<"Vec_scale_0L1L_SB iacc "<<iacc<<" Bin "<<nX<<std::endl;
	    if(Vec_scale_0L1L_SF_SB.at(iacc)->GetBinContent(nX) < 0)std::cout<<"Vec_scale_0L1L_SF_SB iacc "<<iacc<<" Bin "<<nX<<std::endl;
	  }
	}
	else if(PDFAccSys){
	  for(int iacc=0; iacc < PDFsize; iacc++){
	    if(Vec_PDF_0L1L_SB.at(iacc)->GetBinContent(nX) < 0)std::cout<<"Vec_PDF_0L1L_SB iacc "<<iacc<<" Bin "<<nX<<std::endl;
	    if(Vec_PDF_0L1L_SF_SB.at(iacc)->GetBinContent(nX) < 0)std::cout<<"Vec_PDF_0L1L_SF_SB iacc "<<iacc<<" Bin "<<nX<<std::endl;
	  }
	}
	else{
	  if(h_0L1L_SB->GetBinContent(nX) < 0) std::cout<<"h_0L1L_SB (Bin "<<nX<<") negative value"<<std::endl;
	  if(h_0L1L_SF_SB->GetBinContent(nX) < 0) std::cout<<"h_0L1L_SF_SB (Bin "<<nX<<") negative value"<<std::endl;
	}
    }
    
    if(ScaleAccSys){
      for(int iacc=0; iacc < Scalesize; iacc++){
	Vec_scale_CR_SB_copy.at(iacc)->Write();
	Vec_scale_SR_SB_copy.at(iacc)->Write();
	Vec_scale_CR_SF_SB_copy.at(iacc)->Write();
	Vec_scale_SR_SF_SB_copy.at(iacc)->Write();
	Vec_scale_0L1L_SB.at(iacc)->Write();
	Vec_scale_0L1L_SF_SB.at(iacc)->Write();
      }
    }
    else if(PDFAccSys){
      for(int iacc=0; iacc < PDFsize; iacc++){
	Vec_PDF_CR_SB_copy.at(iacc)->Write();
	Vec_PDF_SR_SB_copy.at(iacc)->Write();
	Vec_PDF_CR_SF_SB_copy.at(iacc)->Write();
	Vec_PDF_SR_SF_SB_copy.at(iacc)->Write();
	Vec_PDF_0L1L_SB.at(iacc)->Write();
	Vec_PDF_0L1L_SF_SB.at(iacc)->Write();
      }
    }
    else{
      h_CR_SB->Write();
      h_CR_SF_SB->Write();
      h_SR_SB->Write();
      h_SR_SF_SB->Write();
      h_SR_LL_SB->Write();
      h_SR_SF_LL_SB->Write();
      h_SR_Hadtau_SB->Write();
      h_SR_SF_Hadtau_SB->Write();

      h_0L1L_SB->Write();
      h_0L1L_SF_SB->Write();
      h_0L1L_LL_SB->Write();
      h_0L1L_SF_LL_SB->Write();
      h_0L1L_Hadtau_SB->Write();
      h_0L1L_SF_Hadtau_SB->Write();

      h_CR_BeforeMT->Write(); 
      h_CR_AfterMT->Write(); 
      h_MTEff->Write();
    }
    /*
    SaveEff(h_CR_SB, outPutFile);
    SaveEff(h_CR_SF_SB, outPutFile);
    SaveEff(h_SR_SB, outPutFile);
    SaveEff(h_SR_SF_SB, outPutFile);
    SaveEff(h_0L1L_SB, outPutFile);
    SaveEff(h_0L1L_SF_SB, outPutFile);    
*/
    outPutFile->Close();

    cout << "Saved output to " << fileName << endl;

}

void TFMaker::PushHist(TH1* h, TH1* f){
    for(int nX = 1; nX <= h->GetXaxis()->GetNbins(); ++nX){
        if(h->GetBinContent(nX) < 0){
            h->SetBinContent(nX, 0);
            h->SetBinError(nX, 0);
        }
    }

    f->Add(h);
    h->Reset();
}

void TFMaker::SaveEff(TH1* h, TFile* oFile, bool xlog, bool ylog)
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

    //h->GetYaxis()->SetRangeUser(0.79, 1.31);
    
    h->Draw("ColZ,Text");

    std::string name = std::string(h->GetName());
    //if(name.find(std::string("SFCR")) != std::string::npos || name.find(std::string("SFSR")) != std::string::npos){
        //TObjArray *optionArray = currFileName.Tokenize("_.");
        //TString currTreeName = ((TObjString *)(optionArray->At(0)))->String();
        TString currTreeName("all_noNeg");
        c1->SaveAs("TFs/"+currTreeName+"_"+TString(name)+".pdf");
    //}

    delete c1;
    gROOT->SetBatch(false);

    h->Write();
}

bool TFMaker::FiltersPass()
{
    bool result=true;
    if(useFilterData){
        if(HBHENoiseFilter!=1) result=false;
        if(HBHEIsoNoiseFilter!=1) result=false;
        if(EcalDeadCellTriggerPrimitiveFilter!=1) result=false;    
        if(eeBadScFilter!=1) result=false;
	//	if(ecalBadCalibFilter!=1) result=false;
        //if(runOnData){
        //    if(!BadChargedCandidateFilter) result=false;
        //    if(!BadPFMuonFilter) result=false;
        //    if(globalSuperTightHalo2016Filter!=1) result=false;
        //}    
    }
    if(NVtx<=0) result=false;

    // Preliminary filters
    if(PFCaloMETRatio>5) result=false;

    for(unsigned j = 0; j < Jets->size(); j++){
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
    //if(!runOnSignalMC)
    if(!JetID) result=false;
    return result;
}

vector<TVector3>TFMaker::Order_the_Vec(vector<TVector3> vec)
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

vector<double>TFMaker::Order_the_Vec(vector<TVector3> vec,vector<double> vecTwo)
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

vector<bool>TFMaker::Order_the_Vec(vector<TVector3> vec,vector<bool> vecTwo)
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

vector<int>TFMaker::Order_the_Vec(vector<TVector3> vec,vector<int> vecTwo)
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

vector<TLorentzVector>TFMaker::Order_the_Vec(vector<TVector3> vec,vector<TLorentzVector> vecTwo)
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

void TFMaker::resetValues()
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
