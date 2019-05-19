#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>


//*AR: 181016: use this definition of function if histograms to be compared from two files have different names
void GetOneDPlots(int hNum,char const * Var,char const * VarTwo,char const * Sample,char const * TTbarLL,char const * WJetLL,char const * STLL,char const* DataPred,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){

//*AR: 181016: use this definition of function if histograms to be compared from two files have same name
//void GetOneDPlots(int hNum,char const * Var,char const * Sample,char const * TTbarLL,char const * WJetLL,char const * STLL,char const* DataPred,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){
  
  //*AR:180831: Borrow cosmetics specific to RA2b style

  double lumi     = 36.35;
  double lumi_ref = 3.0; // normaliza to 3 (fb-1)

  gROOT->LoadMacro("tdrstyle.C");
  void setTDRStyle();
  gROOT->LoadMacro("CMS_lumi.C");

  bool writeExtraText = true;
  char extraText[200]   = "CMS Supplementary (Simulation)                                        ";  // default extra text is "Preliminary"
  char lumi_8TeV[100]  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  char lumi_7TeV[100]  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  //char lumi_sqrtS[100] = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
  float cmsTextSize  = 0.60;
  float lumiTextSize = 0.52;

  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  int iPos=0;

  char line[100] = "";
  char tempname[200];
  sprintf(tempname,"%8.1f",lumi);
  strcat( line, tempname);
  //  line+=tempname;
  //line+=" fb^{-1} (13 TeV)";
  char lumiDetail[100]=" fb^{-1} (13 TeV)";
  strcat( line, lumiDetail);
  TString lumi_sqrtS = line;
  sprintf(tempname,"%s",extraText);
  strcat(extraText,line);

  int W = 600;
  int H = 600;
  int H_ref = 600;
  int W_ref = 800;
  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.08*W_ref;


  //
  // Various vertical line coordinates
  float ymax_top = 300000.;
  float ymin_top = 0.04;
  float ymax_bottom = 2.65;
  float ymin_bottom = 0.0;
  float ytext_top = 2000.;
  float x_legend = 10.;
  float y_legend = 4000.;
  float xtext_top;

  TLatex * toptext = new TLatex();
  toptext->SetTextSize(0.03);


  // Define legend 
  Float_t legendX1 = .40; //.50;
  Float_t legendX2 = .90; //.70;
  Float_t legendY1 = .62; //.65;
  Float_t legendY2 = .82;

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);

  catLeg1->SetTextSize(0.044);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);


  // Define canvas
  //
  TCanvas *canvas = new TCanvas("canvas","canvas",10,10,W,H);

  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetRightMargin( 0.2 );
  canvas->SetTopMargin( T/H );
  canvas->SetBottomMargin( B/H );

  canvas->Divide(1, 2);

  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
 
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.30; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
 
  // set pad size
  canvas_up->SetPad(0., 1 - up_height +0.095, 0.97, 1.);
  canvas_dw->SetPad(0., dw_height_offset, 0.97, 0.29);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.10);
  canvas_up->SetRightMargin(0.03);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.35);
  canvas_dw->SetRightMargin(0.03);
  canvas_up->SetBottomMargin(0);  
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0);


  canvas_up->cd();

  //======================================================================



  gStyle->SetOptTitle(0);
  //  gStyle->SetOptLabel(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  int col1 = kRed;
  int col2 = kBlack;
  int i=0;
  
  int GetRatioNbins=RatioNbins;
  double GetRatioXmin=RatioXmin;
  double GetRatioXmax=RatioXmax;
  double ymax=topMax;
  char hname[500], htit[500];
  char hnameRev[500];
  char tempWJet[500];
  char tempTTbar[500];
  char LabelX[500];
  char LabelY[500];
  char RatioLabelX[500];
  char RatioLabelY[500];
  char cname[500];
  char header[500];

  //*AR:181207-In 2016, LL+Hadtau data prediction in 0L region (i.e in file "Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root") is saved with "h_%s_Exp" (After applying TF) while in 2017 same (MC and Data) prediction saved with "h_%s_Pre" (After applying TF and met v2 recipe). MC Expectation in 0L region is saved with "h_%s_Exp" (if met v2 recipe not applied, example 2016) or with "h_%sv2recipe_Exp"(if met v2 recipe not applied, example 2017)  

  sprintf(header,"%s",LegHeader);
  sprintf(hname,"h_%s_Exp",Var);
  sprintf(hnameRev,"h_%s_Pre",VarTwo);
  sprintf(RatioLabelX,"%s",xRatioLabel);
  sprintf(RatioLabelY,"%s",yRatioLabel);
  sprintf(cname,"h_%s_Exp_%s",Var,Sample);


  TFile *_fileTTbarLL = TFile::Open(TTbarLL); 

  TFile *_fileWJetLL = TFile::Open(WJetLL);
  TFile *_fileSTLL = TFile::Open(STLL);
  /*
  TFile *_fileTTbarHadtau = TFile::Open(TTbarHadtau); 
  TFile *_fileWJetHadtau = TFile::Open(WJetHadtau);
  TFile *_fileSTHadtau = TFile::Open(STHadtau);
*/

  TFile *_fileData = TFile::Open(DataPred);

  _fileTTbarLL->cd();
  //TH1D *hTTbarLL = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  //  hTTbarLL->Scale(35900);
  TH1D *hTTbarLLOrg = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  _fileWJetLL->cd();
  //TH1D *hWJetLL = (TH1D*)_fileWJetLL->FindObjectAny(hname);
  //  hWJetLL->Scale(35900);
  
  TH1D *hWJetLLOrg = (TH1D*)_fileWJetLL->FindObjectAny(hname);
  _fileSTLL->cd();
  //TH1D *hSTLL = (TH1D*)_fileSTLL->FindObjectAny(hname);
  //  hSTLL->Scale(35900);
  
  TH1D *hSTLLOrg = (TH1D*)_fileSTLL->FindObjectAny(hname);
  _fileData->cd();

  TH1D *hDataLLHadtauOrg = (TH1D*)_fileData->FindObjectAny(hnameRev);

  TH1D * hTTbarLL = new TH1D("hTTbarLL", "hTTbarLL", GetRatioNbins, GetRatioXmin, GetRatioXmax);
  TH1D * hWJetLL = new TH1D("hWJetLL", "hWJetLL", GetRatioNbins, GetRatioXmin, GetRatioXmax);
  TH1D * hSTLL = new TH1D("hSTLL", "hSTLL", GetRatioNbins, GetRatioXmin, GetRatioXmax);

  TH1D * hDataLLHadtau = new TH1D("hDataLLHadtau", "hDataLLHadtau", GetRatioNbins, GetRatioXmin, GetRatioXmax);

  for(int i=0;i<=GetRatioNbins+1;i++){
    hTTbarLL->SetBinContent(i,hTTbarLLOrg->GetBinContent(i)); 
    hTTbarLL->SetBinError(i,hTTbarLLOrg->GetBinError(i)); 

    hWJetLL->SetBinContent(i,hWJetLLOrg->GetBinContent(i)); 
    hWJetLL->SetBinError(i,hWJetLLOrg->GetBinError(i)); 

    hSTLL->SetBinContent(i,hSTLLOrg->GetBinContent(i)); 
    hSTLL->SetBinError(i,hSTLLOrg->GetBinError(i)); 

    hDataLLHadtau->SetBinContent(i,hDataLLHadtauOrg->GetBinContent(i)); 
    hDataLLHadtau->SetBinError(i,hDataLLHadtauOrg->GetBinError(i)); 

    double val=hDataLLHadtauOrg->GetBinContent(i)+hDataLLHadtauOrg->GetBinContent(i+1);
    //    if(i==4)
    //hDataLLHadtau->SetBinContent(i,val);
    double err=sqrt(hDataLLHadtauOrg->GetBinError(i)*hDataLLHadtauOrg->GetBinError(i) + hDataLLHadtauOrg->GetBinError(i+1)*hDataLLHadtauOrg->GetBinError(i+1));
    //    if(i==4)
    //hDataLLHadtau->SetBinError(i,err); 


  }

  /*
  
  TH1D *hTTbarLLOrg = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  TH1D *hTTbarLL = new TH1D("hTTbarLL","hTTbarLL",4,0,4);
  //  hTTbarLL->Sumw2();
  int nbins=hTTbarLL->GetXaxis()->GetNbins();
  for(int i=1;i<=4;i++){
    if(i<=3){
      double val=hTTbarLLOrg->GetBinContent(i);
      hTTbarLL->SetBinContent(i,val);
      double err=hTTbarLLOrg->GetBinError(i);
      hTTbarLL->SetBinError(i,err);
    }
    else{
      double val=hTTbarLLOrg->GetBinContent(i)+hTTbarLLOrg->GetBinContent(i+1);
      hTTbarLL->SetBinContent(i,val);
      double err=sqrt(hTTbarLLOrg->GetBinError(i)*hTTbarLLOrg->GetBinError(i) + hTTbarLLOrg->GetBinError(i+1)*hTTbarLLOrg->GetBinError(i+1));
      hTTbarLL->SetBinError(i,err);
    }
  }

  _fileWJetLL->cd();
  //TH1D *hWJetLL = (TH1D*)_fileWJetLL->FindObjectAny(hname);
  //  hWJetLL->Scale(35900);
  
  TH1D *hWJetLLOrg = (TH1D*)_fileWJetLL->FindObjectAny(hname);
  TH1D *hWJetLL = new TH1D("hWJetLL","hWJetLL",4,0,4);
  //  hWJetLL->Sumw2();
  nbins=hWJetLL->GetXaxis()->GetNbins();
  for(int i=1;i<=4;i++){
    if(i<=3){
      double val=hWJetLLOrg->GetBinContent(i);
      hWJetLL->SetBinContent(i,val);
      double err=hWJetLLOrg->GetBinError(i);
      hWJetLL->SetBinError(i,err);
    }
    else{
      double val=hWJetLLOrg->GetBinContent(i)+hWJetLLOrg->GetBinContent(i+1);
      hWJetLL->SetBinContent(i,val);
      double err=sqrt(hWJetLLOrg->GetBinError(i)*hWJetLLOrg->GetBinError(i) + hWJetLLOrg->GetBinError(i+1)*hWJetLLOrg->GetBinError(i+1));
      hWJetLL->SetBinError(i,err);
    }
  }

  TH1D *hSTLL = new TH1D("hSTLL","hSTLL",4,0,4);
  //  hSTLL->Sumw2();
  nbins=hSTLL->GetXaxis()->GetNbins();
  for(int i=1;i<=4;i++){
    if(i<=3){
      double val=hSTLLOrg->GetBinContent(i);
      hSTLL->SetBinContent(i,val);
      double err=hSTLLOrg->GetBinError(i);
      hSTLL->SetBinError(i,err);
    }
    else{
      double val=hSTLLOrg->GetBinContent(i)+hSTLLOrg->GetBinContent(i+1);
      hSTLL->SetBinContent(i,val);
      double err=sqrt(hSTLLOrg->GetBinError(i)*hSTLLOrg->GetBinError(i) + hSTLLOrg->GetBinError(i+1)*hSTLLOrg->GetBinError(i+1));
      hSTLL->SetBinError(i,err);
    }
  }
  
  _fileData->cd();
  //  TH1D *hDataLLHadtau = (TH1D*)_fileData->FindObjectAny(hnameRev);
  //  std::cout<<" seg vio "<<endl;
  //  hDataLLHadtau->Scale(41486.328/59546.381);
  
  TH1D *hDataLLHadtauOrg = (TH1D*)_fileData->FindObjectAny(hnameRev);
  TH1D *hDataLLHadtau = new TH1D("hDataLLHadtau","hDataLLHadtau",4,0,4);
  //  hDataLLHadtau->Sumw2();
  //  nbins=hDataLLHadtau->GetXaxis()->GetNbins();
  
  for(int i=1;i<=4;i++){
    if(i<=3){
      double val=hDataLLHadtauOrg->GetBinContent(i);
      hDataLLHadtau->SetBinContent(i,val);
      double err=hDataLLHadtauOrg->GetBinError(i);
      hDataLLHadtau->SetBinError(i,err);

    }
    else{
      double val=hDataLLHadtauOrg->GetBinContent(i)+hDataLLHadtauOrg->GetBinContent(i+1);
      hDataLLHadtau->SetBinContent(i,val);
      double err=sqrt(hDataLLHadtauOrg->GetBinError(i)*hDataLLHadtauOrg->GetBinError(i) + hDataLLHadtauOrg->GetBinError(i+1)*hDataLLHadtauOrg->GetBinError(i+1));
      hDataLLHadtau->SetBinError(i,err);
    }
  }
*/
    /*
 hTTbarLL->Rebin(5);
  hWJetLL->Rebin(5);
  hSTLL->Rebin(5);
  hDataLLHadtau->Rebin(5);
*/
  hDataLLHadtau->SetMarkerStyle(20);
  hDataLLHadtau->SetMarkerSize(1.2);
  hDataLLHadtau->SetLineColor(1);

  double xmin=hDataLLHadtau->GetXaxis()->GetXmin();
  double xmax=hDataLLHadtau->GetXaxis()->GetXmax();
  double diff=xmax-xmin;  
  double ymaximum=hDataLLHadtau->GetYaxis()->GetXmax();
  std::cout<<" xmin "<<xmin<<" xmax "<<xmax<<" diff "<<diff<<" ymaximum "<<ymaximum<<endl;

  /*
  //  hDataLLHadtau->GetYaxis()->SetRangeUser(0.001,ymax); 
  _fileTTbarHadtau->cd();
  TH1D *hTTbarHadtau = (TH1D*)_fileTTbarHadtau->FindObjectAny(hname);
  hTTbarHadtau->Scale(35900);

  _fileWJetHadtau->cd();
  TH1D *hWJetHadtau = (TH1D*)_fileWJetHadtau->FindObjectAny(hname);
  hWJetHadtau->Scale(35900);

  _fileSTHadtau->cd();
  TH1D *hSTHadtau = (TH1D*)_fileSTHadtau->FindObjectAny(hname);
  hSTHadtau->Scale(35900);
*/
  TH1D *hTTbarLLHadtau=(TH1D *) hTTbarLL->Clone("hTTbarLLHadtau");
  //  hTTbarLLHadtau->Add(hTTbarHadtau);
  hTTbarLLHadtau->SetLineColor(kBlue);
  hTTbarLLHadtau->SetFillColor(kBlue);
  //  hTTbarLLHadtau->SetMarkerStyle(21);
  TH1D *hWJetLLHadtau=(TH1D *) hWJetLL->Clone("hWJetLLHadtau");
  //  hWJetLLHadtau->Add(hWJetHadtau);
  hWJetLLHadtau->SetLineColor(kGreen);
  hWJetLLHadtau->SetFillColor(kGreen);

  TH1D *hSTLLHadtau=(TH1D *) hSTLL->Clone("hSTLLHadtau");
  //  hSTLLHadtau->Add(hSTHadtau);
  hSTLLHadtau->SetLineColor(kRed);
  hSTLLHadtau->SetFillColor(kRed);



  THStack * hExp = new THStack("hExp","hExp");
  //  std::cout<<" ****** seg vio ******"<<endl;

  hExp->Add(hSTLLHadtau);
  hExp->Add(hWJetLLHadtau);
  hExp->Add(hTTbarLLHadtau);
   
  TH1D * hExpFinal=(TH1D*) hExp->GetStack()->Last();
  //  TCanvas *c = new TCanvas("c","c", 500, 500);
  //  canvas_up->SetLogy();

  if(logy)
    canvas_up->SetLogy();
  
  if(logx)
    canvas_up->SetLogx();
  std::cout<<" seg vio 1"<<endl;
  
  if(hDataLLHadtau->GetMaximum()>hExp->GetMaximum()){
    if(logy)
      hExp->SetMaximum(5*hDataLLHadtau->GetMaximum());
    else 
      hExp->SetMaximum(1.5*hDataLLHadtau->GetMaximum());
  }
  else{
    if(logy)
      hExp->SetMaximum(5*hExp->GetMaximum());
    else 
      hExp->SetMaximum(1.5*hExp->GetMaximum());
  }
  std::cout<<" seg vio 2"<<endl;  
  //*AR:190104-If you get segmentation violation for arbitary plot due to SetMinimum() command then switch off "if" loops used to set minimum of histogram. Instead fix minimum to some fixed value. 
  hExp->SetMinimum(9);
  /*
  if(hDataLLHadtau->GetMinimum()<hExp->GetMinimum()){
    hExp->SetMinimum(0.5*hDataLLHadtau->GetMinimum());
    std::cout<<" seg vio 3"<<endl;  
  }
  else{
    hExp->SetMinimum(0.5*hSTLLHadtau->GetMinimum());
    //hExp->SetMinimum(10);

    std::cout<<" seg vio 4"<<endl;  
  }
*/
  hExp->Draw("hist e");
  hDataLLHadtau->Draw("esame");
  std::cout<<" seg vio 5"<<endl;  
  hExp->GetYaxis()->SetTitle("Events");

  hExp->GetYaxis()->SetLabelSize(0.055*1.15);
  hExp->GetYaxis()->SetTitleSize(0.06*1.15);
  hExp->GetYaxis()->SetTitleOffset(0.9);
  hExp->GetYaxis()->SetTitleFont(42);

  TLegend *tl=new TLegend(Legxmin,Legymin,Legxmax,Legymax);
  //  tl->SetHeader(header);
  tl->SetTextSize(0.044);
  tl->SetTextFont(42);
  tl->SetFillColor(0);
  tl->SetLineColor(0);
  tl->SetBorderSize(0);

  //  tl->AddEntry(hDataLLHadtau, "Data: LL+Had#tau");  //if 0L reg
  tl->AddEntry(hDataLLHadtau, "Data:Lost-lepton prediction","pe"); 
  tl->AddEntry(hSTLLHadtau, "MC: Single top");
  tl->AddEntry(hWJetLLHadtau, "MC: W+jets");
  tl->AddEntry(hTTbarLLHadtau, "MC: t#bar{t}");
  tl->SetLineColor(kWhite);
  tl->Draw("same");
  gPad->RedrawAxis();

  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.8*canvas_up->GetTopMargin());
  ttext->DrawLatexNDC(0.15,0.91, "#bf{CMS} #it{Preliminary}");

  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);

  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  ttexlumi->SetTextSize(0.8*canvas_up->GetTopMargin());
  ttexlumi->DrawLatexNDC(0.6, 0.91 , "137 fb^{-1} (13 TeV)");

  gPad->SetLeftMargin(0.16);
  gPad->SetTicks(1,1);
  gPad->Modified();
  std::cout<<" seg vio 6"<<endl;  
  
  //  TH1D * cOne = new TH1D("Ratio","ratio plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram
  TH1D *  cOne=(TH1D *) hDataLLHadtau->Clone("Ratio");
  cOne->Divide(hExpFinal);
  gStyle->SetPadBottomMargin(0.3);
  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(RatioLabelX);
  cOne->GetYaxis()->SetTitle(RatioLabelY);
  canvas_dw->cd();
  cOne->Draw("e");
  std::cout<<" seg vio 7"<<endl;  
  cOne->GetXaxis()->SetLabelSize(0.20*0.045/0.06);
  cOne->GetXaxis()->SetTitleOffset(0.9);
  cOne->GetXaxis()->SetTitleSize(0.16);
  cOne->GetXaxis()->SetTitleFont(42);
  cOne->GetXaxis()->SetLabelOffset(0.008);

  cOne->GetYaxis()->SetRangeUser(RatioYmin,RatioYmax);
  cOne->GetYaxis()->SetTitleOffset(0.40);
  cOne->GetYaxis()->SetTitleSize(0.18);
  cOne->GetYaxis()->SetTitleFont(42);
  cOne->GetYaxis()->SetNdivisions(505);
  cOne->GetYaxis()->SetLabelSize(0.20*0.045/0.06);
  cOne->GetYaxis()->SetLabelOffset(0.008);

  gStyle->SetPadTickY(1);
  cOne->GetYaxis()->SetNdivisions(5);
  //  cOne->SetLabelSize(0.115,"XY");
  TLine *tline = new TLine(GetRatioXmin,1.,GetRatioXmax,1.);
  tline->SetLineStyle(2);  
  tline->Draw("same");  
  gPad->Update();
  gPad->SetLeftMargin(0.16);
  gPad->SetTicks(1,1);
  gPad->Modified();
  char PrintName[500];
  sprintf(PrintName,"%i_%s.png",hNum,cname);
  canvas->Print(PrintName);
  sprintf(PrintName,"%i_%s.pdf",hNum,cname);
  canvas->Print(PrintName);



}

void GetOneDPlots(){
  
  //*AR-181211-Here files "Prediction_0_haddTTbar_AppliedPrefireMap_NewCodeconsistentwithOldCode_1L.root" is copied to "Prediction_0_haddTTbar_0L_.root" and so on.

  /*
    GetOneDPlots(1200,"LepEtafor50","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

    GetOneDPlots(1200,"LepEtafor100","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

    GetOneDPlots(1200,"LepEtafor200","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);
*/
  /*
    GetOneDPlots(1200,"JetEtafor50forHTv2Recipe","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Jet #eta","Data/MC",0,0,5,-2.5,2.5,0,2.49,50000);

    GetOneDPlots(1200,"JetEtafor100forHTv2Recipe","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Jet #eta","Data/MC",0,0,5,-2.5,2.5,0,2.49,50000);

    GetOneDPlots(1200,"JetEtafor200forHTv2Recipe","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Jet #eta","Data/MC",0,0,5,-2.5,2.5,0,2.49,50000);
  
        
    GetOneDPlots(1200,"JetEtafor50forMHTminusHTv2Recipe","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Jet #eta","Data/MC",0,0,10,-5.,5.,0,2.49,50000);

    GetOneDPlots(1200,"JetEtafor100forMHTminusHTv2Recipe","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Jet #eta","Data/MC",0,0,10,-5.,5.,0,2.49,50000);

    GetOneDPlots(1200,"JetEtafor200forMHTminusHTv2Recipe","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Jet #eta","Data/MC",0,0,10,-5.,5.,0,2.49,50000);

*/    

  
  /*
  GetOneDPlots(1300,"NBtagv2Recipe","NBtag","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"NBtag","Data/MC",1,0,5,0,5,0,2.49,200000);
  
  GetOneDPlots(1000,"MHTv2Recipe","MHT","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"MHT","Data/MC",1,0,16,200,1000,0,2.49,70000);

  GetOneDPlots(1100,"HTv2Recipe","HT","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"HT","Data/MC",1,0,12,100,2500,0,2.49,90000);

  GetOneDPlots(1200,"NJetv2Recipe","NJet","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"NJet","Data/MC",1,0,10,2,12,0,2.49,50000);
*/

  
  //  GetOneDPlots(1200,"LepPt","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton pT","Data/MC",1,0,20,0,1000,0,2.49,50000);
  
  //GetOneDPlots(1200,"LepEta","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);



  //GetOneDPlots(1200,"LepPhi","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #phi","Data/MC",0,0,7,-3.5,3.5,0,2.49,50000);
  /*
  GetOneDPlots(1300,"NBtagv2Recipe","NBtag","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"NBtag","Data/MC",1,0,5,0,5,0,2.49,200000);
  
  GetOneDPlots(1000,"MHTv2Recipe","MHT","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"MHT","Data/MC",1,0,16,200,1000,0,2.49,70000);

  GetOneDPlots(1100,"HTv2Recipe","HT","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"HT","Data/MC",1,0,12,100,2500,0,2.49,90000);

  GetOneDPlots(1200,"NJetv2Recipe","NJet","DataPredVsMCExpWithBtagProb","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.57,0.6,0.87,0.87,"NJet","Data/MC",1,0,10,2,12,0,2.49,50000);
*/



  
  //  GetOneDPlots(1300,"NBtagv2Recipe","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"NBtag","Data/MC",1,0,4,0,4,0,2.49,200000);
  
  /*
  GetOneDPlots(1000,"MHTv2Recipe","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"MHT","Data/MC",1,0,16,200,1000,0,2.49,70000);

  GetOneDPlots(1100,"HTv2Recipe","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"HT","Data/MC",1,0,12,100,2500,0,2.49,90000);

  GetOneDPlots(1200,"NJetv2Recipe","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"NJet","Data/MC",1,0,10,2,12,0,2.49,50000);



  
  GetOneDPlots(1200,"ElePt","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.6,0.87,0.87,"Eletron pT","Data/MC",1,0,20,0,1000,0,2.49,50000);
  
  GetOneDPlots(1200,"EleEta","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.6,0.87,0.87,"Electron #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"ElePhi","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.6,0.87,0.87,"Electron #phi","Data/MC",0,0,7,-3.5,3.5,0,2.49,50000);

  GetOneDPlots(1200,"MuPt","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.6,0.87,0.87,"Muon pT","Data/MC",1,0,20,0,1000,0,2.49,50000);
  
  GetOneDPlots(1200,"MuEta","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.6,0.87,0.87,"Muon #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"MuPhi","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.6,0.87,0.87,"Muon #phi","Data/MC",0,0,7,-3.5,3.5,0,2.49,50000);



  GetOneDPlots(1200,"LepPt","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton pT","Data/MC",1,0,20,0,1000,0,2.49,50000);
  
  GetOneDPlots(1200,"LepEta","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepPhi","2016_1L_Check","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #phi","Data/MC",0,0,7,-3.5,3.5,0,2.49,50000);
*/


  //  GetOneDPlots(1300,"NBtagv2Recipe","NBtag","Data_FinalV17_16Plus17Plus18","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.52,0.6,0.87,0.87,"N_{b}","Data/MC",1,0,4,-0.5,3.5,0,2.49,200000);
  
    GetOneDPlots(1000,"MHTv2Recipe","MHT","Data_FinalV17_16Plus17Plus18","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.52,0.6,0.87,0.87,"H_{T}^{miss}","Data/MC",1,0,16,200,1000,0,2.49,70000);

    GetOneDPlots(1100,"HTv2Recipe","HT","Data_FinalV17_16Plus17Plus18","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.52,0.6,0.87,0.87,"H_{T}","Data/MC",1,0,12,100,2500,0,2.49,90000);

    GetOneDPlots(1200,"NJetv2Recipe","NJet","Data_FinalV17_16Plus17Plus18","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","0L SR",0.52,0.6,0.87,0.87,"N_{jet}","Data/MC",1,0,10,1.5,11.5,0,2.49,50000);











































  
  //  GetOneDPlots(1200,"JetPtforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"pT","Data/MC",1,0,20,0,1000,0,2.49,50000);
  
  /*
  GetOneDPlots(1200,"JetEtaforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50forHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100forHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200forHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);
*/
  /*
  GetOneDPlots(1200,"JetEtaNjet2To3forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50Njet2To3forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100Njet2To3forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200Njet2To3forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);


  GetOneDPlots(1200,"JetEtaNjet4To6forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50Njet4To6forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100Njet4To6forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200Njet4To6forHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEtaNjet7ToAboveforHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50Njet7ToAboveforHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100Njet7ToAboveforHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200Njet7ToAboveforHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

*/

  /*
  GetOneDPlots(1200,"JetEtaInEleforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50InEleforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100InEleforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200InEleforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);


  GetOneDPlots(1200,"JetEtaInMuforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50InMuforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100InMuforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200InMuforHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"#eta","Data/MC",0,0,50,-2.5,2.5,0,2.49,50000);
*/


  /*

  GetOneDPlots(1200,"JetPhiforHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#phi","Data/MC",0,0,70,-3.5,3.5,0,2.49,50000);

  GetOneDPlots(1200,"JetPtforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"pT","Data/MC",1,0,20,0,1000,0,2.49,50000);
*/
  /*
  GetOneDPlots(1200,"JetEtaforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);
*/
  /*
  GetOneDPlots(1200,"JetEtaNjet2To3forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50Njet2To3forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100Njet2To3forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200Njet2To3forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);


  GetOneDPlots(1200,"JetEtaNjet4To6forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50Njet4To6forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100Njet4To6forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200Njet4To6forMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);


  GetOneDPlots(1200,"JetEtaNjet7ToAboveforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50Njet7ToAboveforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100Njet7ToAboveforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200Njet7ToAboveforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);
*/


  /*
  GetOneDPlots(1200,"JetEtaInEleforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50InEleforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100InEleforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200InEleforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEtaInMuforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta50InMuforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta100InMuforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);

  GetOneDPlots(1200,"JetEta200InMuforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.37,0.5,0.67,0.67,"#eta","Data/MC",0,0,100,-5,5,0,2.49,50000);
*/
  /*
  GetOneDPlots(1200,"LepEta","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta50","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta100","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta200","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);


  GetOneDPlots(1200,"LepEtaInEle","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta50InEle","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta100InEle","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta200InEle","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1e CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEtaInMu","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta50InMu","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta100InMu","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta200InMu","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1#mu CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);
*/



  /*


  GetOneDPlots(1200,"JetPhiforMHTminusHTv2Recipe","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"#phi","Data/MC",0,0,70,-3.5,3.5,0,2.49,50000);
  
  //GetOneDPlots(1200,"LepPt","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep pT","Data/MC",1,0,20,0,1000,0,2.49,50000);
    
  GetOneDPlots(1200,"LepEta","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta50","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta100","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  GetOneDPlots(1200,"LepEta200","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

  
    GetOneDPlots(1200,"LepPhi","DataVsMC_1L_HighDphi_AppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.7,0.87,0.87,"Lep #phi","Data/MC",0,0,7,-3.5,3.5,0,2.49,50000);
  
*/


  /*
  GetOneDPlots(1300,"NBtag","DataVsMCCorrr_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NBtag","Data/MC",1,0,5,0,5,0,2.49,200000);
  
  GetOneDPlots(1000,"MHT","DataVsMCCorrr_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"MHT","Data/MC",1,0,16,200,1000,0,2.49,70000);

  GetOneDPlots(1100,"HT","DataVsMCCorrr_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"HT","Data/MC",1,0,12,100,2500,0,2.49,90000);

  GetOneDPlots(1200,"NJet","DataVsMCCorrr_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NJet","Data/MC",1,0,10,2,12,0,2.49,50000);
*/  
  /*
  //*AR: Obtained plots with prefire map applied on MC
  GetOneDPlots(1300,"NBtag","DataVsAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddWJet_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddST_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NBtag","Data/MC",1,0,5,0,5,0,2.5,200000);
  
  GetOneDPlots(1000,"MHT","DataVsAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddWJet_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddST_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"MHT","Data/MC",1,0,16,200,1000,0,2.5,70000);

  GetOneDPlots(1100,"HT","DataVsAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddWJet_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddST_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"HT","Data/MC",1,0,12,100,2500,0,2.5,90000);

  GetOneDPlots(1200,"NJet","DataVsAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddWJet_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_haddST_181206_AppliedNonPrefireProbMapforJetsAndPhotons_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NJet","Data/MC",1,0,10,2,12,0,2.5,50000);
*/
  /*
  //*AR: Obtained plots with no prefire map applied on MC
  GetOneDPlots(1300,"NBtag","DataVsNotAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_BeforePrefireCase_0L.root","Prediction_0_haddWJet_BeforePrefireCase_0L.root","Prediction_0_haddST_BeforePrefireCase_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NBtag","Data/MC",1,0,5,0,5,0,2.5,200000);
  
  GetOneDPlots(1000,"MHT","DataVsNotAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_BeforePrefireCase_0L.root","Prediction_0_haddWJet_BeforePrefireCase_0L.root","Prediction_0_haddST_BeforePrefireCase_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"MHT","Data/MC",1,0,16,200,1000,0,2.5,70000);

  GetOneDPlots(1100,"HT","DataVsNotAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_BeforePrefireCase_0L.root","Prediction_0_haddWJet_BeforePrefireCase_0L.root","Prediction_0_haddST_BeforePrefireCase_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"HT","Data/MC",1,0,12,100,2500,0,2.5,90000);

  GetOneDPlots(1200,"NJet","DataVsNotAppliedPrefireMapOnMC_LLPlusHadtau_HighDphi","Prediction_0_haddTTbar_BeforePrefireCase_0L.root","Prediction_0_haddWJet_BeforePrefireCase_0L.root","Prediction_0_haddST_BeforePrefireCase_0L.root","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NJet","Data/MC",1,0,10,2,12,0,2.5,50000);
*/

}
