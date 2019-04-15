//void plot_Acceptance_forICHEP2016(std::string elogForPlot=""){
#include <stdio.h>
#include <string.h>


//*AR-180529--LL TF in scale/PDF sys case 

void GetTFHistograms(const char* WJetTTbarMC, const char* SFHist, const char* histOne,const char *histTwo, int ArraySize){

  int size=ArraySize;
  std::cout<< " size "<<size<<endl;
  for (int j=0;j<=size;j++){
    TFile *_file0 = TFile::Open(WJetTTbarMC);
    if(j<size){    
      char SFhname[500];
      char Firsthname[500];
      char Secondhname[500];
      
      sprintf(SFhname,"%s_%i",SFHist,j);
      sprintf(Firsthname,"%s_%i",histOne,j);
      sprintf(Secondhname,"%s_%i",histTwo,j);
      
      TH1D *h1 = (TH1D*)_file0->FindObjectAny(Firsthname);
      TH1D *h2 = (TH1D*)_file0->FindObjectAny(Secondhname);
      
      TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFhname);
      hOut->Reset();
      hOut->Divide(h1,h2);
      
      for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
	if(hOut->GetBinContent(nX) < 0)
	  std::cout<<" nX "<<nX<< " negative value "<<std::endl;   
      }
      TFile* xf = new TFile("TFCombinedLLHadtau.root","UPDATE"); 
      hOut->Write();
      xf->Close(); 
    }
    
    else{
      char SFhname[500];
      char Firsthname[500];
      sprintf(SFhname,"%s_%i",SFHist,j);
      sprintf(Firsthname,"%s_%i",SFHist,0);
      std::cout<<" SFhname "<<SFhname<<" Firsthname "<<Firsthname<<endl;
      TFile *_file1 = TFile::Open("TFCombinedLLHadtau.root"); 
      TH1D *h1 = (TH1D*)_file1->FindObjectAny(Firsthname);
      TH1D *hOut = (TH1D*)h1->Clone(SFhname);
      hOut->Reset();
      TFile *fDistTF=new TFile("fDistTF.root","UPDATE");
      for(int binIndx=1;binIndx<=223;binIndx++){
	double MaxDiff=0.0;
	double tot=0.0;
	double avg=0;
	double valNominal=0;
	double valSys=0;
	valNominal=h1->GetBinContent(binIndx);
	double MaxSysBinContent=0;
	char hname[500];
	sprintf(hname,"%s_bin_%i",SFHist,binIndx);    
	TH1D * hDist =new TH1D(hname,hname,500,0,5);
	char cname[500];
	sprintf(cname,"C_%i",binIndx);
	for (int k=1;k<size;k++){
	  char Secondhname[500];
	  double tempTF;
	  sprintf(Secondhname,"%s_%i",SFHist,k);
	  TH1D *h2 = (TH1D*)_file1->FindObjectAny(Secondhname);
	  tempTF=h2->GetBinContent(binIndx);
	  std::cout<<" binIndx "<<binIndx<<" firstHist "<<Firsthname<<" secHist "<<Secondhname<<" tempTF "<<tempTF<<endl;
	  hDist->Fill(tempTF);
	  //std::cout<<" abs_diff "<<abs (Diff)<<" abs_MaxDiff "<<abs (MaxDiff)<<endl;
	  //	  if(abs (Diff)>abs (MaxDiff))
	  // MaxDiff=Diff;
	  //std::cout<<" Diff "<<Diff<<" MaxDiff "<<MaxDiff<<endl;
	}
	//TCanvas *C=new TCanvas(cname,cname,500,500);
	hDist->Write();
	MaxSysBinContent=hDist->GetRMS(1)/2;
	valSys=valNominal+MaxSysBinContent;
	std::cout<<"binIndx "<<binIndx<<" nominal "<<valNominal<<" rms "<<MaxSysBinContent<<endl;
	hOut->SetBinContent(binIndx,valSys);
	hOut->SetBinError(binIndx,h1->GetBinError(binIndx));
      }
      TFile* yf = new TFile("TFCombinedLLHadtau.root","UPDATE");
      hOut->Write();
      yf->Close();
    }

  }

}


//*AR-180529--LL TF in nominal case  
void GetTFHistograms(const char* WJetTTbarMC, const char* SFHist, const char* histOne,const char *histTwo){
  std::cout<<" getting combined and separate TFs for LL+Hadtau "<<endl;
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  int ret_el; int ret_mu;

  hOut->Reset();
  std::cout<<" h1/h2 "<<endl;
  hOut->Divide(h1,h2);
  
  for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
    std::cout<<" nX "<<nX<<" h1_val "<<h1->GetBinContent(nX)<<" h1_err "<<h1->GetBinError(nX)<<" h2_val "<<h2->GetBinContent(nX)<<" h2_err "<<h2->GetBinError(nX)<<" hOut_val "<<hOut->GetBinContent(nX)<<" hOut_err "<<hOut->GetBinError(nX)<<endl;
    
    if(hOut->GetBinContent(nX) < 0)
      std::cout<<" nX "<<nX<< " negative value "<<std::endl;   
  }
  std::string name = std::string(WJetTTbarMC);
  TFile* xf = new TFile("TFCombinedLLHadtau.root","UPDATE");
  hOut->Write();
  xf->Close(); 

}

//*AR-180529--LL+Hadtau TF in scale/PDF sys case 
//Now as LL+Hadtau contribution is derived together, we don't need functions below anymore.
void GetTFHistograms(char* WJetTTbarMC,char* Wgun,char* SFHist, char* histOne,char *histTwo,char* histThree,int ArraySize){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  int size=ArraySize; 
  std::cout<< " size "<<size<<endl;
  TH1::SetDefaultSumw2();  
  for (int j=0;j<=size;j++){
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TFile *_file1 = TFile::Open(Wgun);
  if(j<size){
    char SFhname[500];
    char Firsthname[500];
    char Secondhname[500];
    char Genhname[500];

    sprintf(SFhname,"%s_%i",SFHist,j);
    sprintf(Firsthname,"%s_%i",histOne,j); 
    sprintf(Secondhname,"%s_%i",histTwo,j); 
    sprintf(Genhname,"%s_%i",histThree,j);

    TH1D *h1 = (TH1D*)_file0->FindObjectAny(Firsthname);
    TH1D *h2 = (TH1D*)_file0->FindObjectAny(Secondhname);
    TH1D *h3 = (TH1D*)_file1->FindObjectAny(Genhname);
    
    TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFhname);
    hOut->Reset();
    hOut->Add(h3,35900);
    hOut->Add(h1);
    hOut->Divide(h2);

    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      if(j==0)
	std::cout<<" nX "<<nX<<" h1_val "<<h1->GetBinContent(nX)<<" h1_err "<<h1->GetBinError(nX)<<" h2_val "<<h2->GetBinContent(nX)<<" h2_err "<<h2->GetBinError(nX)<<" h3_val "<<h3->GetBinContent(nX)<<" h3_err "<<h3->GetBinError(nX)<<" hOut_val "<<hOut->GetBinContent(nX)<<" hOut_err "<<hOut->GetBinError(nX)<<endl;
      if(hOut->GetBinContent(nX) < 0)
	std::cout<<" nX "<<nX<< " negative value "<<std::endl;   
    }

    TFile* xf = new TFile("TFLLPlusHadTau.root","UPDATE");
    hOut->Write();
    xf->Close(); 
  }
  else{
    char SFhname[500];
    char Firsthname[500];
    sprintf(SFhname,"%s_%i",SFHist,j);
    sprintf(Firsthname,"%s_%i",SFHist,0);
    std::cout<<" SFhname "<<SFhname<<" Firsthname "<<Firsthname<<endl;
    TFile *_file1 = TFile::Open("TFLLPlusHadTau.root"); 
    TH1D *h1 = (TH1D*)_file1->FindObjectAny(Firsthname);
    TH1D *hOut = (TH1D*)h1->Clone(SFhname);
    hOut->Reset();
    TFile *fDistTF=new TFile("fDistTF.root","UPDATE");
    for(int binIndx=1;binIndx<=223;binIndx++){
      double MaxDiff=0.0;
      double tot=0.0;
      double avg=0;
      double valNominal=0;
      double valSys=0;
      valNominal=h1->GetBinContent(binIndx);
      double MaxSysBinContent=0;
      char hname[500];
      sprintf(hname,"%s_bin_%i",SFHist,binIndx);    
      TH1D * hDist =new TH1D(hname,hname,500,0,5);
      char cname[500];
      sprintf(cname,"C_%i",binIndx);
      for (int k=1;k<size;k++){
	char Secondhname[500];
	double tempTF;
	sprintf(Secondhname,"%s_%i",SFHist,k);
	TH1D *h2 = (TH1D*)_file1->FindObjectAny(Secondhname);
	tempTF=h2->GetBinContent(binIndx);
	std::cout<<" binIndx "<<binIndx<<" firstHist "<<Firsthname<<" secHist "<<Secondhname<<" tempTF "<<tempTF<<endl;
	hDist->Fill(tempTF);
	//std::cout<<" abs_diff "<<abs (Diff)<<" abs_MaxDiff "<<abs (MaxDiff)<<endl;
	//	  if(abs (Diff)>abs (MaxDiff))
	// MaxDiff=Diff;
	//std::cout<<" Diff "<<Diff<<" MaxDiff "<<MaxDiff<<endl;
      }
	//TCanvas *C=new TCanvas(cname,cname,500,500);
      hDist->Write();
      MaxSysBinContent=hDist->GetRMS(1)/2;
      valSys=valNominal+MaxSysBinContent;
      std::cout<<"binIndx "<<binIndx<<" nominal "<<valNominal<<" rms "<<MaxSysBinContent<<endl;
      hOut->SetBinContent(binIndx,valSys);
      hOut->SetBinError(binIndx,h1->GetBinError(binIndx));
    }
    TFile* yf = new TFile("TFLLPlusHadTau.root","UPDATE");
    hOut->Write();
    yf->Close();
  }
  }
}





//*AR-180529--LL+Hadtau TF in nominal case 

void GetTFHistograms(char* WJetTTbarMC,char* Wgun,char* SFHist, char* histOne,char *histTwo,char* histThree){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TFile *_file1 = TFile::Open(Wgun);
  THStack *tempstack;
  char tempname[200]; 
  //  TH1D * GenHist;
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  sprintf(tempname,"%s",histThree);
  //  tempstack=(THStack*)_file1->Get(tempname)->Clone();
  //GenHist=(TH1D*) tempstack->GetStack()->Last();
  TH1D *GenHist=(TH1D*)_file1->FindObjectAny(tempname); 
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist); //if GenHist is not stacked
  hOut->Reset();
  hOut->Add(h1);
  std::cout<<" SR_bin_val "<<hOut->GetBinContent(1)<<" SR_bin_err "<<hOut->GetBinError(1)<<endl;
  hOut->Add(GenHist,35900);
  //  hOut->Add(GenHist,35.9/3);
  std::cout<<" h1_val "<<h1->GetBinContent(1)<<" h1_err "<<h1->GetBinError(1)<<"genhist_val "<<GenHist->GetBinContent(1)<<" bin_val_afterScale "<<hOut->GetBinContent(1)<<" genhist_err "<<GenHist->GetBinError(1)<<" bin_err_afterscale "<<hOut->GetBinError(1)<<endl;

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
//*AR-180328--hadtau TF in scale/PDF sys case
/*
void GetTFHistograms(char* WJetTTbarMC,char* Wgun,char* SFHist, char* histOne,char *histTwo,int ArraySize){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  int size=ArraySize; 
  std::cout<< " size "<<size<<endl;
  TH1::SetDefaultSumw2();  
  for (int j=0;j<=size;j++){
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TFile *_file1 = TFile::Open(Wgun);
  if(j<size){
    char SFhname[500];
    char Firsthname[500];
    char Secondhname[500];

    sprintf(SFhname,"%s_%i",SFHist,j);
    sprintf(Firsthname,"%s_%i",histOne,j); 
    sprintf(Secondhname,"%s_%i",histTwo,j); 

    TH1D *h1 = (TH1D*)_file0->FindObjectAny(Firsthname);
    TH1D *h2 = (TH1D*)_file1->FindObjectAny(Secondhname);
    
    TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFhname);
    hOut->Reset();
    hOut->Add(h2,35900);
    hOut->Divide(h1);

    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      if(j==0)
	std::cout<<" nX "<<nX<<" h1_val "<<h1->GetBinContent(nX)<<" h1_err "<<h1->GetBinError(nX)<<" h2_val "<<h2->GetBinContent(nX)<<" h2_err "<<h2->GetBinError(nX)<<" hOut_val "<<hOut->GetBinContent(nX)<<" hOut_err "<<hOut->GetBinError(nX)<<endl;
      if(hOut->GetBinContent(nX) < 0)
	std::cout<<" nX "<<nX<< " negative value "<<std::endl;   
    }

    TFile* xf = new TFile("TFHadTau.root","UPDATE");
    hOut->Write();
    xf->Close(); 
  }
  else{
    char SFhname[500];
    char Firsthname[500];
    sprintf(SFhname,"%s_%i",SFHist,j);
    sprintf(Firsthname,"%s_%i",SFHist,0);
    std::cout<<" SFhname "<<SFhname<<" Firsthname "<<Firsthname<<endl;
    TFile *_file1 = TFile::Open("TFHadTau.root"); 
    TH1D *h1 = (TH1D*)_file1->FindObjectAny(Firsthname);
    TH1D *hOut = (TH1D*)h1->Clone(SFhname);
    hOut->Reset();
    TFile *fDistTF=new TFile("fDistTF.root","UPDATE");
    for(int binIndx=1;binIndx<=223;binIndx++){
      double MaxDiff=0.0;
      double tot=0.0;
      double avg=0;
      double valNominal=0;
      double valSys=0;
      valNominal=h1->GetBinContent(binIndx);
      double MaxSysBinContent=0;
      char hname[500];
      sprintf(hname,"%s_bin_%i",SFHist,binIndx);    
      TH1D * hDist =new TH1D(hname,hname,500,0,5);
      char cname[500];
      sprintf(cname,"C_%i",binIndx);
      for (int k=1;k<size;k++){
	char Secondhname[500];
	double tempTF;
	sprintf(Secondhname,"%s_%i",SFHist,k);
	TH1D *h2 = (TH1D*)_file1->FindObjectAny(Secondhname);
	tempTF=h2->GetBinContent(binIndx);
	std::cout<<" binIndx "<<binIndx<<" firstHist "<<Firsthname<<" secHist "<<Secondhname<<" tempTF "<<tempTF<<endl;
	hDist->Fill(tempTF);
	//std::cout<<" abs_diff "<<abs (Diff)<<" abs_MaxDiff "<<abs (MaxDiff)<<endl;
	//	  if(abs (Diff)>abs (MaxDiff))
	// MaxDiff=Diff;
	//std::cout<<" Diff "<<Diff<<" MaxDiff "<<MaxDiff<<endl;
      }
	//TCanvas *C=new TCanvas(cname,cname,500,500);
      hDist->Write();
      MaxSysBinContent=hDist->GetRMS(1)/2;
      valSys=valNominal+MaxSysBinContent;
      std::cout<<"binIndx "<<binIndx<<" nominal "<<valNominal<<" rms "<<MaxSysBinContent<<endl;
      hOut->SetBinContent(binIndx,valSys);
      hOut->SetBinError(binIndx,h1->GetBinError(binIndx));
    }
    TFile* yf = new TFile("TFHadTau.root","UPDATE");
    hOut->Write();
    yf->Close();
  }
  }
}
*/
/*
   char SFhname[500];  
    char Firsthname[500]; 
    sprintf(SFhname,"%s_%i",SFHist,j);
    sprintf(Firsthname,"%s_%i",SFHist,0);
    std::cout<<" SFhname "<<SFhname<<" Firsthname "<<Firsthname<<endl;
    TFile *_file1 = TFile::Open("TFHadTau.root");
    TH1D *h1 = (TH1D*)_file1->FindObjectAny(Firsthname);
    TH1D *hOut = (TH1D*)h1->Clone(SFhname);
    hOut->Reset();
    for(int binIndx=1;binIndx<=223;binIndx++){
	double MaxDiff=0.0;
	double Diff=0.0;
	double MaxSysBinContent=0.0;
	for (int k=1;k<size;k++){
	  char Secondhname[500];
	  sprintf(Secondhname,"%s_%i",SFHist,k);
	  TH1D *h2 = (TH1D*)_file1->FindObjectAny(Secondhname);
	  std::cout<<" binIndx "<<binIndx<<" firstHist "<<Firsthname<<" secHist "<<Secondhname<<endl;
	  Diff=h1->GetBinContent(binIndx)-h2->GetBinContent(binIndx);
	  //std::cout<<" abs_diff "<<abs (Diff)<<" abs_MaxDiff "<<abs (MaxDiff)<<endl;
	  if(abs (Diff)>abs (MaxDiff))
	    MaxDiff=Diff;
	  std::cout<<" Diff "<<Diff<<" MaxDiff "<<MaxDiff<<endl;
	}
	MaxSysBinContent=h1->GetBinContent(binIndx)-MaxDiff;
	std::cout<<" FinalMaxDiff "<<MaxDiff<<" h0 "<<h1->GetBinContent(binIndx)<<" MaxSysBinContent "<<MaxSysBinContent<<endl;
	hOut->SetBinContent(binIndx,MaxSysBinContent);
	hOut->SetBinError(binIndx,h1->GetBinError(binIndx));
      }
      TFile* yf = new TFile("TFHadTau.root","UPDATE");
      hOut->Write();
      yf->Close();
  }
  }
}

*/

/*
//*AR-hadtau TF in nominal case
void GetTFHistograms(char* WJetTTbarMC,char* Wgun,char* SFHist, char* histOne,char *histTwo){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TFile *_file1 = TFile::Open(Wgun);
  THStack *tempstack;
  char tempname[200]; 
  TH1D * GenHist;
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  //TH1D *h2 = (TH1D*)_file1->FindObjectAny(histTwo);
  sprintf(tempname,"%s",histTwo);
  tempstack=(THStack*)_file1->Get(tempname)->Clone();
  GenHist=(TH1D*) tempstack->GetStack()->Last();
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  hOut->Reset();
  //hOut->Add(h2,35900); //*AR--180327--As eventweight, was scaled to 1pb, hence during stack we scale by 3000 and then while plotting by 35.9/3.so totally we need to scale by 35900, if file used is not stacked.
  hOut->Add(GenHist,35.9/3);
  hOut->Divide(h1);

  for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
    std::cout<<" nX "<<nX<<" h1_val "<<h1->GetBinContent(nX)<<" h1_err "<<h1->GetBinError(nX)<<" h2_val "<<h2->GetBinContent(nX)<<" h2_err "<<h2->GetBinError(nX)<<" hOut_val "<<hOut->GetBinContent(nX)<<" hOut_err "<<hOut->GetBinError(nX)<<endl;
    
    if(hOut->GetBinContent(nX) < 0)
      std::cout<<" nX "<<nX<< " negative value "<<std::endl;   
  }
  std::string name = std::string(WJetTTbarMC);
  TFile* xf = new TFile("TFHadTau.root","UPDATE");
  hOut->Write();
  xf->Close(); 
}
*/


void CombinedTF() {

  //*AR: 190116- TF in nominal case  
  
  GetTFHistograms("TF_0.root","h_0L1L_SB","h_SR_SB","h_CR_SB");
  GetTFHistograms("TF_0.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB");

  GetTFHistograms("TF_0.root","h_0L1L_LL_SB","h_SR_LL_SB","h_CR_SB");
  GetTFHistograms("TF_0.root","h_0L1L_SF_LL_SB","h_SR_SF_LL_SB","h_CR_SF_SB");

  GetTFHistograms("TF_0.root","h_0L1L_Hadtau_SB","h_SR_Hadtau_SB","h_CR_SB");
  GetTFHistograms("TF_0.root","h_0L1L_SF_Hadtau_SB","h_SR_SF_Hadtau_SB","h_CR_SF_SB");


  //*AR: 190116- TF in scale sys case

  //  GetTFHistograms("TF_0.root","h_scale_0L1L_SB","h_scale_SR_SB","h_scale_CR_SB",9);
  //  GetTFHistograms("TF_0.root","h_scale_0L1L_SF_SB","h_scale_SR_SF_SB","h_scale_CR_SF_SB",9);

  //*AR: 190116- TF in PDF sys case

  //  GetTFHistograms("TF_0.root","h_PDF_0L1L_SB","h_PDF_SR_SB","h_PDF_CR_SB",101);
  //  GetTFHistograms("TF_0.root","h_PDF_0L1L_SF_SB","h_PDF_SR_SF_SB","h_PDF_CR_SF_SB",101);

  //GetTFHistograms("TF_0_NoExotic.root","h_0L1L_SB","h_SR_SB","h_CR_SB");
  //GetTFHistograms("TF_0_NoExotic.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB");
  //  GetTFHistograms("TF_0.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SB","h_SR_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB","QCD_Up");

  //  GetTFHistograms("TF_WithoutExotic.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_WithoutExotic.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SF_SB","h_CR_SF_SB","QCD_Up");
  //    GetTFHistograms("TF_0_NoExotic.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SB","h_SR_SB","h_CR_SB","QCD_Up");
  //  GetTFHistograms("TF_0_NoExotic.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB","QCD_Up");

  //  GetTFHistograms("TF_0.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","ARElog115_GenInfo_HadTauEstimation_stacked.root","h_0L1L_SF_SB","h_CR_SF_SB","QCD_Up");

  //  GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECDn_haddTTbarWJetST.root","h_0L1L_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECDn_haddTTbarWJetST.root","h_0L1L_SF_SB","h_CR_SF_SB","QCD_Up");

  //  GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECDn_haddTTbarWJetST.root","h_0L1L_SB","h_SR_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECDn_haddTTbarWJetST.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB","QCD_Up");

  //  GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECRefWithbtagProb_haddTTbarWJetST.root","h_0L1L_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECRefWithbtagProb_haddTTbarWJetST.root","h_0L1L_SF_SB","h_CR_SF_SB","QCD_Up");

  //    GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECDnWithbtagProb_haddTTbarWJetST.root","h_0L1L_SB","h_SR_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_JECDnWithbtagProb_haddTTbarWJetST.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB","QCD_Up");

  //    GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_BtagSysWithbtagProb_haddTTbarWJetST.root","h_0L1L_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_BtagSysWithbtagProb_haddTTbarWJetST.root","h_0L1L_SF_SB","h_CR_SF_SB","QCD_Up");

  //  GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_BtagSysWithbtagProb_haddTTbarWJetST.root","h_0L1L_SB","h_SR_SB","h_CR_SB","QCD_Up");
  //GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_BtagSysWithbtagProb_haddTTbarWJetST.root","h_0L1L_SF_SB","h_SR_SF_SB","h_CR_SF_SB","QCD_Up");

  //GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_ScaleSys_haddTTbarWJet.root","h_scale_0L1L_SF_SB","h_scale_CR_SF_SB","QCD_Up_Scale",9);

  //  GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_PDFSys_haddTTbarWJet.root","h_PDF_0L1L_SF_SB","h_PDF_CR_SF_SB","QCD_Up_PDF",101);

  //  GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_ScaleSys_haddTTbarWJet.root","h_scale_0L1L_SF_SB","h_scale_SR_SF_SB","h_scale_CR_SF_SB","QCD_Up_Scale",9);

  //  GetTFHistograms("TF_0.root","GenInfo_HadTauEstimation_PDFSys_haddTTbarWJet.root","h_PDF_0L1L_SF_SB","h_PDF_SR_SF_SB","h_PDF_CR_SF_SB","QCD_Up_PDF",101);

}
