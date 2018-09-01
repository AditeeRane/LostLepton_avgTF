#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>



void GetOneDPlots(char const * Var,char const * TTbarLL,char const * WJetLL,char const * STLL,char const * TTbarHadtau,char const * WJetHadtau,char const* STHadtau,char const* DataPred,char const *xRatioLabel,char const *yRatioLabel,int RatioNbins,double RatioXmin,double RatioXmax,double topMax){
  
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
  canvas_up->SetPad(0., 1 - up_height +0.01, 0.97, 1.);
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.10);
  canvas_up->SetRightMargin(0.03);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.30);
  canvas_dw->SetRightMargin(0.03);
  
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
  char tempWJet[500];
  char tempTTbar[500];
  char LabelX[500];
  char LabelY[500];
  char RatioLabelX[500];
  char RatioLabelY[500];
  
  sprintf(hname,"h_%s_Exp",Var);
  sprintf(RatioLabelX,"%s",xRatioLabel);
  sprintf(RatioLabelY,"%s",yRatioLabel);


  TFile *_fileTTbarLL = TFile::Open(TTbarLL); 

  TFile *_fileWJetLL = TFile::Open(WJetLL);
  TFile *_fileSTLL = TFile::Open(STLL);

  TFile *_fileTTbarHadtau = TFile::Open(TTbarHadtau); 
  TFile *_fileWJetHadtau = TFile::Open(WJetHadtau);
  TFile *_fileSTHadtau = TFile::Open(STHadtau);

  TFile *_fileData = TFile::Open(DataPred);

  _fileTTbarLL->cd();
  TH1D *hTTbarLL = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  hTTbarLL->Scale(35900);

  _fileWJetLL->cd();
  TH1D *hWJetLL = (TH1D*)_fileWJetLL->FindObjectAny(hname);
  hWJetLL->Scale(35900);

  _fileSTLL->cd();
  TH1D *hSTLL = (TH1D*)_fileSTLL->FindObjectAny(hname);
  hSTLL->Scale(35900);

  _fileData->cd();
  TH1D *hDataLLHadtau = (TH1D*)_fileData->FindObjectAny(hname);
  hDataLLHadtau->SetLineColor(kBlack);
  hDataLLHadtau->SetLineWidth(2);
  hDataLLHadtau->SetMarkerStyle(21);
  hDataLLHadtau->SetMarkerColor(kBlack);
  hDataLLHadtau->GetYaxis()->SetRangeUser(0.001,ymax); 
  _fileTTbarHadtau->cd();
  TH1D *hTTbarHadtau = (TH1D*)_fileTTbarHadtau->FindObjectAny(hname);
  hTTbarHadtau->Scale(35900);

  _fileWJetHadtau->cd();
  TH1D *hWJetHadtau = (TH1D*)_fileWJetHadtau->FindObjectAny(hname);
  hWJetHadtau->Scale(35900);

  _fileSTHadtau->cd();
  TH1D *hSTHadtau = (TH1D*)_fileSTHadtau->FindObjectAny(hname);
  hSTHadtau->Scale(35900);

  TH1D *hTTbarLLHadtau=(TH1D *) hTTbarLL->Clone("hTTbarLLHadtau");
  hTTbarLLHadtau->Add(hTTbarHadtau);
  hTTbarLLHadtau->SetLineColor(kBlue);
  hTTbarLLHadtau->SetFillColor(kBlue);
  //  hTTbarLLHadtau->SetMarkerStyle(21);
  TH1D *hWJetLLHadtau=(TH1D *) hWJetLL->Clone("hWJetLLHadtau");
  hWJetLLHadtau->Add(hWJetHadtau);
  hWJetLLHadtau->SetLineColor(kGreen);
  hWJetLLHadtau->SetFillColor(kGreen);

  TH1D *hSTLLHadtau=(TH1D *) hSTLL->Clone("hSTLLHadtau");
  hSTLLHadtau->Add(hSTHadtau);
  hSTLLHadtau->SetLineColor(kRed);
  hSTLLHadtau->SetFillColor(kRed);


  THStack * hExp = new THStack("hExp","hExp");
  //  std::cout<<" ****** seg vio ******"<<endl;

  hExp->Add(hSTLLHadtau);
  hExp->Add(hWJetLLHadtau);
  hExp->Add(hTTbarLLHadtau);
   
  TH1D * hExpFinal=(TH1D*) hExp->GetStack()->Last();
  //  TCanvas *c = new TCanvas("c","c", 500, 500);
  canvas_up->SetLogy();
  hExp->Draw("hist");
  hDataLLHadtau->Draw("same");

  TLegend *tl=new TLegend(0.57,0.7,0.87,0.87);
  tl->AddEntry(hSTLLHadtau, "MC: single top");
  tl->AddEntry(hWJetLLHadtau, "MC: W+jets");
  tl->AddEntry(hTTbarLLHadtau, "MC: TTbar");
  tl->AddEntry(hDataLLHadtau, "Data: LL+Hadtau"); 
  tl->SetLineColor(kWhite);
  tl->Draw("same");
  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  ttext->DrawLatex(GetRatioXmin , ymax , "#bf{CMS} #it{Preliminary}");

  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  ttexlumi->DrawLatex(GetRatioXmax-2*binSize, ymax , "35.9fb^{-1} (13TeV)");

  
  gPad->Modified();
  
  TH1D * cOne = new TH1D("Ratio","ratio plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram
  cOne=(TH1D *) hDataLLHadtau->Clone("Ratio");
  cOne->Divide(hExpFinal);
  gStyle->SetPadBottomMargin(0.3);
  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(RatioLabelX);
  cOne->GetYaxis()->SetTitle(RatioLabelY);
  canvas_dw->cd();
  cOne->Draw();
  
  cOne->GetXaxis()->SetTitleOffset(0.8);
  cOne->GetXaxis()->SetTitleSize(0.12);
  cOne->GetXaxis()->SetTitleFont(42);
  cOne->GetXaxis()->SetLabelOffset(0.007);

  cOne->GetYaxis()->SetRangeUser(0,2.499);
  cOne->GetYaxis()->SetTitleOffset(0.35);
  cOne->GetYaxis()->SetTitleSize(0.12);
  cOne->GetYaxis()->SetTitleFont(42);
  gStyle->SetPadTickY(1);
  cOne->GetYaxis()->SetNdivisions(8);
  cOne->SetLabelSize(0.10,"XY");
  TLine *tline = new TLine(GetRatioXmin,1.,GetRatioXmax,1.);
  tline->SetLineStyle(2);  
  tline->Draw("same");  
  gPad->Update();
  gPad->Modified();
  char PrintName[500];
  sprintf(PrintName,"%s.png",hname);
  canvas->Print(PrintName);
  sprintf(PrintName,"%s.pdf",hname);
  canvas->Print(PrintName);




}


