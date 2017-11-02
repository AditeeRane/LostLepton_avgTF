//void plot_Acceptance_forICHEP2016(std::string elogForPlot=""){



void CombinedTF() {
  //  GetSFHistograms("SFCR_0_TTbar_.root","h_di_SFSR_SB","h_di_nTwoFoundTwoPrompt_SF_SB","h_di_nTwoPrompt_SB","h_di_nOneFoundTwoPrompt_SF_SB","h_di_nLostTwoPrompt_SB");
  /*
  GetTFHistograms("TF_0.root","h_0L1L_SB","h_SR_SB","h_CR_SB");
  GetTFHistograms("TF_0.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB");
*/
  GetTFHistograms("TF_0.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SB","h_SR_SB","h_CR_SB","QCD_Up");
  GetTFHistograms("TF_0.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB","QCD_Up");

}

void GetTFHistograms(char* WJetTTbarMC, char* SFHist, char* histOne,char *histTwo){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  hOut->Reset();
  std::cout<<" h1/h2 "<<endl;
  hOut->Divide(h1,h2);
  
  for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
    if(hOut->GetBinContent(nX) < 0)
      std::cout<<" nX "<<nX<< " negative value "<<std::endl;   
  }
  std::string name = std::string(WJetTTbarMC);
  TFile* xf = new TFile("TFLL.root","UPDATE");
  hOut->Write();
  xf->Close(); 
}

void GetTFHistograms(char* WJetTTbarMC,char* Wgun,char* SFHist, char* histOne,char *histTwo,char* histThree){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TFile *_file1 = TFile::Open(Wgun);
  THStack *tempstack;
  char tempname[200]; 
  TH1D * GenHist;
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  sprintf(tempname,"%s",histThree);
  tempstack=(THStack*)_file1->Get(tempname)->Clone();
  GenHist=(TH1D*) tempstack->GetStack()->Last();
  
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  hOut->Reset();
  hOut->Add(h1);
  hOut->Add(GenHist,1);
  hOut->Divide(h2);

  for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
    if(hOut->GetBinContent(nX) < 0)
      std::cout<<" nX "<<nX<< " negative value "<<std::endl;   
  }
  std::string name = std::string(WJetTTbarMC);
  TFile* xf = new TFile("TFLLPlusHadTau.root","UPDATE");
  hOut->Write();
  xf->Close(); 
}

