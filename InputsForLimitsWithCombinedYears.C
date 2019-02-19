//void plot_Acceptance_forICHEP2016(std::string elogForPlot=""){
#include <stdio.h>
#include <string.h>
#include "TMath.h"

//*AR:190211-TFErr histogram to represent stat error on MC
void InputsForLimitsWithCombinedYears(const char* TTbarMC,const char* TFMC,const char* histOne,const char* histTFMC,int type,bool yTTbar){

  std::cout<<" combining histograms from different years "<<endl;
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TH1D *h1;TH1D *h2;TH1D *h3;TH1D *h4;TH1D *h5;TH1D *h6;TH1D *hTF;TH1D *hTFMC;TH1D *hOut;
  TFile *_file0 = TFile::Open(TTbarMC);
  if(yTTbar){
    h1 = (TH1D*)_file0->FindObjectAny(histOne); 
  }
  TFile *_fileMC = TFile::Open(TFMC);
  hTFMC = (TH1D*)_fileMC->FindObjectAny(histTFMC);

  hOut =(TH1D *)h1->Clone();

  /*
  if(yTTbar)
    hOut =(TH1D *)h1->Clone();
  else if(yWJet)
    hOut =(TH1D *)h2->Clone();
  else
    hOut =(TH1D *)h3->Clone(); 
*/
  hOut->Reset();
  /*
  double scaleTTbar=LTTbar/(LTTbar+LWJet+LSt);
  double scaleWJet=LWJet/(LTTbar+LWJet+LSt);
  double scaleSt=LSt/(LTTbar+LWJet+LSt);

  double valTTbar=scaleTTbar;
  double valWJet=scaleWJet;
  double valSt=scaleSt;
*/
  //*AR:190130 TF Err read from MC TF histogram 
  if(type==5){
    double binVal;
    std::cout<<" Get TF error"<<endl;
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      binVal=1+hTFMC->GetBinError(nX)/hTFMC->GetBinContent(nX);
      std::cout<<" nX "<<nX<<" h1val "<<hTFMC->GetBinContent(nX)<<" h1err "<<hTFMC->GetBinError(nX)<<" binval "<<binVal<<endl;
      hOut->SetBinContent(nX,binVal);
    }
  }
  TFile* xf = new TFile("InputsForLimits_data_formatted_LLPlusHadTau_CombinedYears.root","UPDATE");
    hOut->Write();
    xf->Close();
  
}






//*AR:190211-TF=Pred/CSStat
void InputsForLimitsWithCombinedYears(const char* TTbarMC,const char* WJetMC,const char* STMC,const char* TFMC,double LTTbar,double LWJet,double LSt,const char* histTF,const char* histOne,const char* histTwo,const char* histTFMC,int type,bool yTTbar,bool yWJet,bool ySt){

  std::cout<<" combining histograms from different years "<<endl;
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TH1D *h1;TH1D *h2;TH1D *h3;TH1D *h4;TH1D *h5;TH1D *h6;TH1D *hTF;TH1D *hTFMC;TH1D *hOut;
  TFile *_file0 = TFile::Open(TTbarMC);
  if(yTTbar){
    h1 = (TH1D*)_file0->FindObjectAny(histOne); 
    h4 = (TH1D*)_file0->FindObjectAny(histTwo);
    hTF =(TH1D*)_file0->FindObjectAny(histTF);

  }
  TFile *_file1 = TFile::Open(WJetMC);
  if(yWJet){
    h2 = (TH1D*)_file1->FindObjectAny(histOne); 
    h5 = (TH1D*)_file1->FindObjectAny(histTwo);
  }
  TFile *_file2 = TFile::Open(STMC);
  if(ySt){
    h3 = (TH1D*)_file2->FindObjectAny(histOne);
    h6 = (TH1D*)_file2->FindObjectAny(histTwo);
  }
  TFile *_fileMC = TFile::Open(TFMC);
  hTFMC = (TH1D*)_fileMC->FindObjectAny(histTFMC);

  hOut =(TH1D *)hTF->Clone();

  /*
  if(yTTbar)
    hOut =(TH1D *)h1->Clone();
  else if(yWJet)
    hOut =(TH1D *)h2->Clone();
  else
    hOut =(TH1D *)h3->Clone(); 
*/
  hOut->Reset();

  double scaleTTbar=LTTbar/(LTTbar+LWJet+LSt);
  double scaleWJet=LWJet/(LTTbar+LWJet+LSt);
  double scaleSt=LSt/(LTTbar+LWJet+LSt);

  double valTTbar=scaleTTbar;
  double valWJet=scaleWJet;
  double valSt=scaleSt;

  //*AR:190130 TF--- simple add 
  if(type==4){
    std::cout<<" Get TF "<<endl;
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      double binVal=0;
      double GetMCTF=hTFMC->GetBinContent(nX);
      valTTbar=h1->GetBinContent(nX) + h2->GetBinContent(nX) + h3->GetBinContent(nX);
      valWJet=h4->GetBinContent(nX) + h5->GetBinContent(nX) + h6->GetBinContent(nX);
      if(valWJet>0)
	binVal=valTTbar/valWJet;
      else
	binVal=GetMCTF;
      std::cout<<" nX "<<nX<<" h1 "<<h1->GetBinContent(nX)<<" h2 "<<h2->GetBinContent(nX)<<" h3 "<<h3->GetBinContent(nX)<<" totPred "<<valTTbar<<" h4 "<<h4->GetBinContent(nX)<<" h5 "<<h5->GetBinContent(nX)<<" h6 "<<h6->GetBinContent(nX)<<" tot1L"<<valWJet<<" binval "<<binVal<<" GetMCTF "<<GetMCTF<<endl;
      hOut->SetBinContent(nX,binVal);
    }
  }
  TFile* xf = new TFile("InputsForLimits_data_formatted_LLPlusHadTau_CombinedYears.root","UPDATE");
  hOut->Write();
  xf->Close();
  
}





//*AR:190218-DataCSStatErr
void InputsForLimitsWithCombinedYears(const char* TTbarMC,const char* WJetMC,const char* STMC,double LTTbar,double LWJet,double LSt,const char* histTF,const char* histOne,int type,bool yTTbar,bool yWJet,bool ySt){

  std::cout<<" combining histograms from different years "<<endl;
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TH1D *h1;TH1D *h2;TH1D *h3;TH1D *h4;TH1D *h5;TH1D *h6;TH1D *hTF;TH1D *hTotal;TH1D *hOut;
  TFile *_file0 = TFile::Open(TTbarMC);
  if(yTTbar){
    h1 = (TH1D*)_file0->FindObjectAny(histOne); 
    hTF =(TH1D*)_file0->FindObjectAny(histTF);
    //    hTotal =(TH1D*)_file0->FindObjectAny(histOne);
  }
  TFile *_file1 = TFile::Open(WJetMC);
  if(yWJet){
    h2 = (TH1D*)_file1->FindObjectAny(histOne); 
  }
  TFile *_file2 = TFile::Open(STMC);
  if(ySt){
    h3 = (TH1D*)_file2->FindObjectAny(histOne);
  }

  hOut =(TH1D *)hTF->Clone();
  hTotal=(TH1D *)h1->Clone(); 
  /*
  if(yTTbar)
    hOut =(TH1D *)h1->Clone();
  else if(yWJet)
    hOut =(TH1D *)h2->Clone();
  else
    hOut =(TH1D *)h3->Clone(); 
*/
  hOut->Reset();
  //  hTotal->Reset();
  //  hTotal->Add(h2);
  //  hTotal->Add(h3);
  std::cout<<" org "<<hTotal->GetBinContent(1)<<endl;
  //  hTotal->Add(h1);
  //  std::cout<<" added h1 "<<hTotal->GetBinContent(1)<<endl;
  hTotal->Add(h2);
  std::cout<<" added h2 "<<hTotal->GetBinContent(1)<<endl;
  hTotal->Add(h3);
  std::cout<<" added h3 "<<hTotal->GetBinContent(1)<<endl;

  double scaleTTbar=LTTbar/(LTTbar+LWJet+LSt);
  double scaleWJet=LWJet/(LTTbar+LWJet+LSt);
  double scaleSt=LSt/(LTTbar+LWJet+LSt);

  double valTTbar=scaleTTbar;
  double valWJet=scaleWJet;
  double valSt=scaleSt;

  //*AR:190218 Add Data CSStat from three years 
  if(type==2){
    std::cout<<" Get Data CS Stat error "<<endl;
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      double binVal;
      //      binVal=h1->GetBinContent(nX)+h2->GetBinContent(nX);
      if(hTotal->GetBinContent(nX))
	binVal=1+hTotal->GetBinError(nX)/hTotal->GetBinContent(nX);
      else
	binVal=1+hTotal->GetBinError(nX);
      std::cout<<" nX "<<nX<<" h1 "<<h1->GetBinContent(nX)<<" h2 "<<h2->GetBinContent(nX)<<" h3 "<<h3->GetBinContent(nX)<<" totPred "<<hTotal->GetBinContent(nX)<<" binval "<<binVal<<endl;
      hOut->SetBinContent(nX,binVal);
    }
  }
  TFile* xf = new TFile("InputsForLimits_data_formatted_LLPlusHadTau_CombinedYears.root","UPDATE");
  hOut->Write();
  xf->Close();
  
}




void InputsForLimitsWithCombinedYears(const char* TTbarMC,const char* WJetMC,const char* STMC,double LTTbar,double LWJet,double LSt,const char* histOne,int type,bool yTTbar,bool yWJet,bool ySt){

  std::cout<<" combining histograms from different years "<<endl;
  std::cout<<"***"<<" histOne "<<histOne<<endl;
  TH1D *h1;TH1D *h2;TH1D *h3;TH1D *hOut;
  TFile *_file0 = TFile::Open(TTbarMC);
  if(yTTbar)
    h1 = (TH1D*)_file0->FindObjectAny(histOne); 
  TFile *_file1 = TFile::Open(WJetMC);
  if(yWJet)
    h2 = (TH1D*)_file1->FindObjectAny(histOne); 
  TFile *_file2 = TFile::Open(STMC);
  if(ySt)
    h3 = (TH1D*)_file2->FindObjectAny(histOne);

  //  TH1D *hOut = (TH1D*)_file0->FindObjectAny(histOne);
  if(yTTbar)
    hOut =(TH1D *)h1->Clone();
  else if(yWJet)
    hOut =(TH1D *)h2->Clone();
  else
    hOut =(TH1D *)h3->Clone(); 

  hOut->Reset();

  double scaleTTbar=LTTbar/(LTTbar+LWJet+LSt);
  double scaleWJet=LWJet/(LTTbar+LWJet+LSt);
  double scaleSt=LSt/(LTTbar+LWJet+LSt);

  double valTTbar=scaleTTbar;
  double valWJet=scaleWJet;
  double valSt=scaleSt;
  std::cout<<" scaleTTbar "<<scaleTTbar<<" scaleWJet "<<scaleWJet<<" scaleSt "<<scaleSt<<endl;
  //*AR:190130 If systematics is correlated across three years
  if(type==1){
    std::cout<<" systematics is correlated "<<endl;
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      if(yTTbar) valTTbar=scaleTTbar*h1->GetBinContent(nX);
      if(yWJet) valWJet=scaleWJet*h2->GetBinContent(nX);
      if(ySt) valSt=scaleSt*h3->GetBinContent(nX);

      double binVal=valTTbar+valWJet+valSt;
      //      std::cout<<" nX "<<nX<<" h1 "<<h1->GetBinContent(nX)<<" h2 "<<h2->GetBinContent(nX)<<" h3 "<<h3->GetBinContent(nX)<<" binval "<<binVal<<endl;
      //      std::cout<<" nX "<<nX<<" h1 "<<h1->GetBinContent(nX)<<" binval "<<binVal<<endl;

      hOut->SetBinContent(nX,binVal);
    }
  }

  //*AR:190130 If systematics is uncorrelated across three years 
  if(type==2){
    std::cout<<" systematics is uncorrelated "<<endl;
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      if(yTTbar) valTTbar=scaleTTbar*h1->GetBinContent(nX);
      if(yWJet) valWJet=scaleWJet*h2->GetBinContent(nX);
      if(ySt) valSt=scaleSt*h3->GetBinContent(nX);
      
      double binVal=sqrt( pow( valTTbar, 2 ) + pow( valWJet, 2 ) + pow( valSt, 2 ) );
      //      std::cout<<" nX "<<nX<<" h1 "<<h1->GetBinContent(nX)<<" h2 "<<h2->GetBinContent(nX)<<" h3 "<<h3->GetBinContent(nX)<<" binval "<<binVal<<endl;
      hOut->SetBinContent(nX,binVal);
    }
  }


  //*AR:190130 simple addition for Data CS stat and also for total Prediction 
  if(type==3){
    std::cout<<" Data CS stat / Prediction "<<endl;
    for(int nX = 1; nX <= hOut->GetXaxis()->GetNbins(); ++nX){
      if(yTTbar) valTTbar=h1->GetBinContent(nX);
      if(yWJet) valWJet=h2->GetBinContent(nX);
      if(ySt) valSt=h3->GetBinContent(nX);
      
      double binVal=valTTbar+valWJet+valSt;
      //std::cout<<" nX "<<nX<<" h1 "<<h1->GetBinContent(nX)<<" h2 "<<h2->GetBinContent(nX)<<" h3 "<<h3->GetBinContent(nX)<<" binval "<<binVal<<endl;
      hOut->SetBinContent(nX,binVal);
    }
  }


  TFile* xf = new TFile("InputsForLimits_data_formatted_LLPlusHadTau_CombinedYears.root","UPDATE");
  hOut->Write();
  xf->Close();

}





void InputsForLimitsWithCombinedYears() {

  //*AR: 190116- TF in nominal case  
  /*
  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredBMistagDown_LLPlusHadTau",1,1,1,1);
  
  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPred_JECSysDown_LLPlusHadTau",1,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredLepAccSysDown_LLPlusHadTau",1,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredLepAccQsquareSysDown_LLPlusHadTau",1,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredMuRecoSysDown_LLPlusHadTau",1,1,0,0);
  
  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredMTWSysDown_LLPlusHadTau",1,1,1,1);
  

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredMuIDSysDown_LLPlusHadTau",1,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredMuIsoSysDown_LLPlusHadTau",1,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredEleRecoSysDown_LLPlusHadTau",1,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredEleIsoSysDown_LLPlusHadTau",1,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018.root",35.815,41.486,59.777,"totalPredEleIDSysDown_LLPlusHadTau",1,1,1,1);
*/
  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","TFFromMC_AfterTF174.root","LLPlusHadTauTFErr","TF_174",5,1);


  /////    InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018_PredRmHEMEleJet.root",35.815,41.486,59.777,"LLPlusHadTauTFErr",5,1,1,1);

  //  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018_PredRmHEMEleJet.root",35.815,41.486,59.777,"DataCSStatErr","DataCSStatistics",2,1,1,1);
  /*
  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018_PredRmHEMEleJet.root",35.815,41.486,59.777,"DataCSStatistics",3,1,1,1);

  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018_PredRmHEMEleJet.root",35.815,41.486,59.777,"totalPred_LLPlusHadTau",3,1,1,1);



  InputsForLimitsWithCombinedYears("InputsForLimits_data_formatted_LLPlusHadTau_2016.root","InputsForLimits_data_formatted_LLPlusHadTau_2017.root","InputsForLimits_data_formatted_LLPlusHadTau_2018_PredRmHEMEleJet.root","TFFromMC_AfterTF174.root",35.815,41.486,59.777,"LLPlusHadTauTF","totalPred_LLPlusHadTau","DataCSStatistics","TF_174",4,1,1,1);
  */

}
