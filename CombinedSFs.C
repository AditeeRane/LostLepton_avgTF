//void plot_Acceptance_forICHEP2016(std::string elogForPlot=""){
#include <stdio.h>
#include <string.h>


//* AR-180313--this is to evaluate SFSR as a function of search bins in PDF/scale acceptance case

void GetSFHistograms(char* WJetTTbarMC,char* SFHist, char* histOne,char *histTwo,char *histThree,int ArraySize){
  int size=ArraySize;
  std::cout<< " size "<<size<<endl;
  for (int j=0;j<size;j++){
    TFile *_file0 = TFile::Open(WJetTTbarMC);
    
    char SFhname[500];
    char Firsthname[500];
    char Secondhname[500];
    char Thirdhname[500];
    
    sprintf(SFhname,"%s_%i",SFHist,j);
    sprintf(Firsthname,"%s_%i",histOne,j);
    sprintf(Secondhname,"%s_%i",histTwo,j);
    sprintf(Thirdhname,"%s_%i",histThree,j);
    std::cout<<" SFhname "<<std::string(SFhname)<<" Secondhname "<<Secondhname<<endl;

    TH1D *h1 = (TH1D*)_file0->FindObjectAny(Firsthname);
    TH1D *h2 = (TH1D*)_file0->FindObjectAny(Secondhname);
    TH1D *h3 = (TH1D*)_file0->FindObjectAny(Thirdhname);
    h1->Scale(35862.351);
    h2->Scale(35862.351);  
    h3->Scale(35862.351);

    TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFhname);
    hOut->Reset();
    std::cout<<" add h1 "<<endl;
    hOut->Add(h1);
    hOut->Add(h2,-1);
    hOut->Divide(h3);

    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      hOut->SetBinError(nX, 0);
      if(hOut->GetBinContent(nX) < 1e-8)
	hOut->SetBinContent(nX,1);
      if(hOut->GetBinContent(nX) < 1)
	hOut->SetBinContent(nX,1);
    }
    std::string name = std::string(WJetTTbarMC);
    if(name.find(std::string("SFCR_0_TTbar")) != std::string::npos){
      TFile* xf = new TFile("SFCR_0.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_TTbar")) != std::string::npos){
      TFile* xf = new TFile("SFSR_0.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close();
    } 
    if(name.find(std::string("SFCR_0_WJet")) != std::string::npos){
      TFile* xf = new TFile("SFCR_1.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_WJet")) != std::string::npos){
      TFile* xf = new TFile("SFSR_1.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close(); 
    }
    if(name.find(std::string("SFCR_0_ST")) != std::string::npos){
      TFile* xf = new TFile("SFCR_2.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_ST")) != std::string::npos){
      TFile* xf = new TFile("SFSR_2.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close(); 
    }
    if(name.find(std::string("SFCR_0_Exotic")) != std::string::npos){
      TFile* xf = new TFile("SFCR_3.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_Exotic")) != std::string::npos){
      TFile* xf = new TFile("SFSR_3.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();
      h3->Write();
      xf->Close(); 
    }
    
  }
}
//* AR-180313--this is to evaluate SFSR as a function of search bins in nominal case
void GetSFHistograms(const char* WJetTTbarMC, const char* SFHist, const char* histOne,const char *histTwo,const char *histThree){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  TH1D *h3 = (TH1D*)_file0->FindObjectAny(histThree);
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  int ret_el; int ret_mu;
  hOut->Reset();
  std::cout<<" add h1 "<<endl;
  hOut->Add(h1);
  hOut->Add(h2,-1);
  hOut->Divide(h3);
  ret_el = strncmp(SFHist, "h_el_SFSR_SB", 15);
  ret_mu = strncmp(SFHist, "h_mu_SFSR_SB",15);


  if(ret_el==0 || ret_mu ==0){
    //  if(SFHist=="h_el_SFSR_SB" || SFHist=="h_mu_SFSR_SB"){
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      hOut->SetBinError(nX, 0);
      if(hOut->GetBinContent(nX) < 1e-8)
	hOut->SetBinContent(nX,1);
      if(hOut->GetBinContent(nX) < 1)
	hOut->SetBinContent(nX,1);
    }
  }
  std::string name = std::string(WJetTTbarMC);
  if(name.find(std::string("SFCR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFCR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFSR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close();
  } 
  if(name.find(std::string("SFCR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFCR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFSR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFCR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFSR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFCR_3.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFSR_3.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    xf->Close(); 
  }
  
}
//* AR-180313--this is to evaluate SFCR as a function of search bins in PDF/scale acceptance case. Here one extra argument bool Dilep has to be introduced to make it distinguishable from a function used in case of dilepton case.
void GetSFHistograms(char* WJetTTbarMC, char* SFHist, char* histOne,char *histTwo,int ArraySize,bool Dilep){
  int size=ArraySize;
  std::cout<< " ****size "<<size<<endl;
  for (int j=0;j<size;j++){
    TFile *_file0 = TFile::Open(WJetTTbarMC);

    char SFhname[500];
    char Firsthname[500];
    char Secondhname[500];

    sprintf(SFhname,"%s_%i",SFHist,j);
    sprintf(Firsthname,"%s_%i",histOne,j);
    sprintf(Secondhname,"%s_%i",histTwo,j);

    std::cout<<" SFhname "<<std::string(SFhname)<<" Secondhname "<<Secondhname<<endl;
    
    TH1D *h1 = (TH1D*)_file0->FindObjectAny(Firsthname);
    TH1D *h2 = (TH1D*)_file0->FindObjectAny(Secondhname);

    h1->Scale(35862.351);
    h2->Scale(35862.351);
    TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFhname);
    hOut->Reset();
    std::cout<<" divide two hists "<<endl;
    hOut->Divide(h1,h2);
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      hOut->SetBinError(nX, 0);
      if(hOut->GetBinContent(nX) < 1e-8)
	hOut->SetBinContent(nX,1);
      if(hOut->GetBinContent(nX) > 1)
	hOut->SetBinContent(nX,1);
    }
  
    std::string name = std::string(WJetTTbarMC);
    std::cout<<" name "<<name<<endl;
    if(name.find(std::string("SFCR_0_TTbar")) != std::string::npos){
      TFile* xf = new TFile("SFCR_0.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_TTbar")) != std::string::npos){
      TFile* xf = new TFile("SFSR_0.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close();
    } 
    if(name.find(std::string("SFCR_0_WJet")) != std::string::npos){
      TFile* xf = new TFile("SFCR_1.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_WJet")) != std::string::npos){
      TFile* xf = new TFile("SFSR_1.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close(); 
    }
    if(name.find(std::string("SFCR_0_ST")) != std::string::npos){
      TFile* xf = new TFile("SFCR_2.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_ST")) != std::string::npos){
      TFile* xf = new TFile("SFSR_2.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close(); 
    }
    if(name.find(std::string("SFCR_0_Exotic")) != std::string::npos){
      TFile* xf = new TFile("SFCR_3.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close(); 
    }
    if(name.find(std::string("SFSR_0_Exotic")) != std::string::npos){
      TFile* xf = new TFile("SFSR_3.root","UPDATE");
      hOut->Write();
      h1->Write();
      h2->Write();   
      xf->Close(); 
    }
  }

}



//* AR-180313--this is to evaluate SFCR as a function of search bins in nominal case
void GetSFHistograms(const char* WJetTTbarMC, const char* SFHist, const char* histOne,const char *histTwo){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  //  h1->Scale(35862.351);
  //  h2->Scale(35862.351);
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  int ret_el; int ret_mu;
  hOut->Reset();
  std::cout<<" divide two hists "<<endl;
  hOut->Divide(h1,h2);
  ret_el = strncmp(SFHist, "h_el_SFCR_SB", 15);
  ret_mu = strncmp(SFHist, "h_mu_SFCR_SB",15);


  if(ret_el==0 || ret_mu ==0){
    //  if(SFHist=="h_el_SFCR_SB" || SFHist=="h_mu_SFCR_SB"){
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      hOut->SetBinError(nX, 0);
      if(hOut->GetBinContent(nX) < 1e-8)
	hOut->SetBinContent(nX,1);
      if(hOut->GetBinContent(nX) > 1)
	hOut->SetBinContent(nX,1);
    }
  }
  std::string name = std::string(WJetTTbarMC);
  std::cout<<" name "<<name<<endl;
  if(name.find(std::string("SFCR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFCR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFSR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close();
  } 
  if(name.find(std::string("SFCR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFCR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFSR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFCR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFSR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFCR_3.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFSR_3.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }

}


void GetSFHistograms(char* WJetTTbarMC, char* SFHist, char* histOne,char *histTwo, int DiLept){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  h1->Scale(35862.351);
  h2->Scale(35862.351);
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  hOut->Reset();
  std::cout<<" get SF "<<endl;
  for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
    double SFCR_dilep = 1;
      if(h1->GetBinContent(nX)>0)
	SFCR_dilep=std::sqrt(h1->GetBinContent(nX)/h2->GetBinContent(nX));
      hOut->SetBinContent(nX,SFCR_dilep);      
      if(hOut->GetBinContent(nX) > 1)
	hOut->SetBinContent(nX,1);
  }
  
  std::string name = std::string(WJetTTbarMC);
  std::cout<<" name "<<name<<endl;
  
  if(name.find(std::string("SFCR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFCR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFSR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFCR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFSR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFCR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFSR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFCR_3.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFSR_3.root","UPDATE");
    hOut->Write(); 
    h1->Write();
    h2->Write();   
    xf->Close(); 
  }
  
}

void GetSFHistograms(char* WJetTTbarMC, char* SFHist, char* histOne,char *histTwo, char* histThree, char* histFour){
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TFile *_file0 = TFile::Open(WJetTTbarMC);
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  TH1D *h2 = (TH1D*)_file0->FindObjectAny(histTwo);
  TH1D *h3 = (TH1D*)_file0->FindObjectAny(histThree);
  TH1D *h4 = (TH1D*)_file0->FindObjectAny(histFour);
  h1->Scale(35862.351);
  h2->Scale(35862.351);
  h3->Scale(35862.351);
  h4->Scale(35862.351);
  TH1D *hOut = (TH1D*)_file0->FindObjectAny(SFHist);
  hOut->Reset();
  std::cout<<" get SF "<<endl;
  for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      double SFSR_dilep = 1;
      if(h2->GetBinContent(nX)>0 && (h1->GetBinContent(nX)-h2->GetBinContent(nX))<0 && (h4->GetBinContent(nX)>0 || h3->GetBinContent(nX)>0))
	SFSR_dilep=(2*(h1->GetBinContent(nX)-h2->GetBinContent(nX)))/(-h3->GetBinContent(nX)-std::sqrt(h3->GetBinContent(nX)*h3->GetBinContent(nX)-4*h4->GetBinContent(nX)*(h1->GetBinContent(nX)-h2->GetBinContent(nX))));
      hOut->SetBinContent(nX,SFSR_dilep);      
      if(hOut->GetBinContent(nX) < 1)
	hOut->SetBinContent(nX,1);
  }
  std::string name = std::string(WJetTTbarMC);
  std::cout<<" name "<<name<<endl;

  if(name.find(std::string("SFCR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFCR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_TTbar")) != std::string::npos){
    TFile* xf = new TFile("SFSR_0.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFCR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_WJet")) != std::string::npos){
    TFile* xf = new TFile("SFSR_1.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFCR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_ST")) != std::string::npos){
    TFile* xf = new TFile("SFSR_2.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFCR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFCR_3.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  if(name.find(std::string("SFSR_0_Exotic")) != std::string::npos){
    TFile* xf = new TFile("SFSR_3.root","UPDATE");
    hOut->Write();
    h1->Write();
    h2->Write();
    h3->Write();
    h4->Write();
    xf->Close(); 
  }
  
}


void CombinedSFs() {
  
  /*
    GetSFHistograms("SFCR_0_TTbar_.root","h_el_SFCR_etaPt","h_el_nFoundOnePrompt_SF_etaPt","h_el_nFoundOnePrompt_etaPt");
    GetSFHistograms("SFCR_0_TTbar_.root","h_mu_SFCR_etaPt","h_mu_nFoundOnePrompt_SF_etaPt","h_mu_nFoundOnePrompt_etaPt");
    GetSFHistograms("SFCR_0_TTbar_.root","h_el_SFCR_SB","h_el_nFoundOnePrompt_SF_SB","h_el_nFoundOnePrompt_SB");
    GetSFHistograms("SFCR_0_TTbar_.root","h_mu_SFCR_SB","h_mu_nFoundOnePrompt_SF_SB","h_mu_nFoundOnePrompt_SB");
  */
  /*
    GetSFHistograms("SFCR_0_WJet_.root","h_el_SFCR_etaPt","h_el_nFoundOnePrompt_SF_etaPt","h_el_nFoundOnePrompt_etaPt");
    GetSFHistograms("SFCR_0_WJet_.root","h_mu_SFCR_etaPt","h_mu_nFoundOnePrompt_SF_etaPt","h_mu_nFoundOnePrompt_etaPt");
    GetSFHistograms("SFCR_0_WJet_.root","h_el_SFCR_SB","h_el_nFoundOnePrompt_SF_SB","h_el_nFoundOnePrompt_SB");
    GetSFHistograms("SFCR_0_WJet_.root","h_mu_SFCR_SB","h_mu_nFoundOnePrompt_SF_SB","h_mu_nFoundOnePrompt_SB");

*/
    
    GetSFHistograms("SFCR_0_ST_.root","h_el_SFCR_etaPt","h_el_nFoundOnePrompt_SF_etaPt","h_el_nFoundOnePrompt_etaPt");
    GetSFHistograms("SFCR_0_ST_.root","h_mu_SFCR_etaPt","h_mu_nFoundOnePrompt_SF_etaPt","h_mu_nFoundOnePrompt_etaPt");
    GetSFHistograms("SFCR_0_ST_.root","h_el_SFCR_SB","h_el_nFoundOnePrompt_SF_SB","h_el_nFoundOnePrompt_SB");
    GetSFHistograms("SFCR_0_ST_.root","h_mu_SFCR_SB","h_mu_nFoundOnePrompt_SF_SB","h_mu_nFoundOnePrompt_SB");
    
  
  /*
  
  GetSFHistograms("SFSR_0_TTbar_.root","h_el_SFSR_etaPt","h_el_nOnePrompt_etaPt","h_el_nFoundOnePrompt_SF_etaPt","h_el_nLostOnePrompt_etaPt");
  GetSFHistograms("SFSR_0_TTbar_.root","h_mu_SFSR_etaPt","h_mu_nOnePrompt_etaPt","h_mu_nFoundOnePrompt_SF_etaPt","h_mu_nLostOnePrompt_etaPt");
  GetSFHistograms("SFSR_0_TTbar_.root","h_el_SFSR_SB","h_el_nOnePrompt_SB","h_el_nFoundOnePrompt_SF_SB","h_el_nLostOnePrompt_SB");
  GetSFHistograms("SFSR_0_TTbar_.root","h_mu_SFSR_SB","h_mu_nOnePrompt_SB","h_mu_nFoundOnePrompt_SF_SB","h_mu_nLostOnePrompt_SB");
*/
  /*  
  GetSFHistograms("SFSR_0_WJet_.root","h_el_SFSR_etaPt","h_el_nOnePrompt_etaPt","h_el_nFoundOnePrompt_SF_etaPt","h_el_nLostOnePrompt_etaPt");
  GetSFHistograms("SFSR_0_WJet_.root","h_mu_SFSR_etaPt","h_mu_nOnePrompt_etaPt","h_mu_nFoundOnePrompt_SF_etaPt","h_mu_nLostOnePrompt_etaPt");
  GetSFHistograms("SFSR_0_WJet_.root","h_el_SFSR_SB","h_el_nOnePrompt_SB","h_el_nFoundOnePrompt_SF_SB","h_el_nLostOnePrompt_SB");
  GetSFHistograms("SFSR_0_WJet_.root","h_mu_SFSR_SB","h_mu_nOnePrompt_SB","h_mu_nFoundOnePrompt_SF_SB","h_mu_nLostOnePrompt_SB");
*/  
  /*
  GetSFHistograms("SFSR_0_ST_.root","h_el_SFSR_etaPt","h_el_nOnePrompt_etaPt","h_el_nFoundOnePrompt_SF_etaPt","h_el_nLostOnePrompt_etaPt");
  GetSFHistograms("SFSR_0_ST_.root","h_mu_SFSR_etaPt","h_mu_nOnePrompt_etaPt","h_mu_nFoundOnePrompt_SF_etaPt","h_mu_nLostOnePrompt_etaPt");
  GetSFHistograms("SFSR_0_ST_.root","h_el_SFSR_SB","h_el_nOnePrompt_SB","h_el_nFoundOnePrompt_SF_SB","h_el_nLostOnePrompt_SB");
  GetSFHistograms("SFSR_0_ST_.root","h_mu_SFSR_SB","h_mu_nOnePrompt_SB","h_mu_nFoundOnePrompt_SF_SB","h_mu_nLostOnePrompt_SB");
*/

  /*
  GetSFHistograms("SFCR_0_WJet_.root","h_el_SFCR_etaPt","h_el_nFoundOnePrompt_SF_etaPt","h_el_nFoundOnePrompt_etaPt");
  GetSFHistograms("SFCR_0_WJet_.root","h_mu_SFCR_etaPt","h_mu_nFoundOnePrompt_SF_etaPt","h_mu_nFoundOnePrompt_etaPt");
  GetSFHistograms("SFCR_0_WJet_.root","h_el_SFCR_SB","h_el_nFoundOnePrompt_SF_SB","h_el_nFoundOnePrompt_SB");
  GetSFHistograms("SFCR_0_WJet_.root","h_mu_SFCR_SB","h_mu_nFoundOnePrompt_SF_SB","h_mu_nFoundOnePrompt_SB");
*/



}
