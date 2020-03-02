#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>


//*AR: 181016: use this definition of function if histograms to be compared from two files have same name
void OverlaySigBack(int hNum,char const * Var,char const * Sample,char const * TTbarLL,char const * WJetLL,char const * STLL,char const * ZJetLL,char const * QCDLL,char const* T1ttttCom,char const * T1ttttUnCom,char const * T2ttCom,char const * T2ttUnCom,char const * T5qqqqVVCom,char const * T5qqqqVVUnCom,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){
  
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

  int W = 800;
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
  
  canvas->Divide(1, 1);

  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  //  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
 
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.275; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
 
  // set pad size
  canvas_up->SetPad(0., dw_height_offset, 0.97, 1.);
  //  canvas_up->SetPad(0., 1 - up_height +0.095, 0.97, 1.);
  //  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.10);
  canvas_up->SetRightMargin(0.04);

  //  canvas_dw->SetFillColor(0);
  //  canvas_dw->SetFrameFillColor(0);
  //  canvas_dw->SetBottomMargin(0.30);
  //  canvas_dw->SetRightMargin(0.03);

  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  //*AR: for HT, MHT, Njet, Nbtag , margin was 0.06, for dphi plots as there is subscript, it is changed to 0.08
  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

  canvas_up->SetBottomMargin(0.13);  
  // set top margin 0 for bottom figure
  //  canvas_dw->SetTopMargin(0);


  canvas_up->cd();

  //======================================================================



  gStyle->SetOptTitle(0);
  //  gStyle->SetTitleColor(2);
  //  gStyle->SetOptLabel(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.10);
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
  //  sprintf(hnameRev,"h_%s_Pre",VarTwo);
  sprintf(RatioLabelX,"%s",xRatioLabel);
  sprintf(RatioLabelY,"%s",yRatioLabel);
  sprintf(cname,"h_%s_Exp_%s",Var,Sample);


  TFile *_fileTTbarLL = TFile::Open(TTbarLL); 
  TFile *_fileWJetLL = TFile::Open(WJetLL);
  TFile *_fileSTLL = TFile::Open(STLL);
  TFile *_fileZJetLL = TFile::Open(ZJetLL);
  TFile *_fileQCDLL = TFile::Open(QCDLL);
  /*
  TFile *_fileTTbarHadtau = TFile::Open(TTbarHadtau); 
  TFile *_fileWJetHadtau = TFile::Open(WJetHadtau);
  TFile *_fileSTHadtau = TFile::Open(STHadtau);
  */

  TFile *_fileT1ttttCom = TFile::Open(T1ttttCom);
  TFile *_fileT1ttttUnCom = TFile::Open(T1ttttUnCom);
  TFile *_fileT2ttCom = TFile::Open(T2ttCom);
  TFile *_fileT2ttUnCom = TFile::Open(T2ttUnCom);
  TFile *_fileT5qqqqVVCom = TFile::Open(T5qqqqVVCom);
  TFile *_fileT5qqqqVVUnCom = TFile::Open(T5qqqqVVUnCom);

  _fileTTbarLL->cd();
  TH1D *hTTbarLL = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  _fileWJetLL->cd();
  TH1D *hWJetLL = (TH1D*)_fileWJetLL->FindObjectAny(hname);
  _fileSTLL->cd();
  TH1D *hSTLL = (TH1D*)_fileSTLL->FindObjectAny(hname);
  _fileZJetLL->cd();
  TH1D *hZJetLL = (TH1D*)_fileZJetLL->FindObjectAny(hname);
  _fileQCDLL->cd();
  TH1D *hQCDLL = (TH1D*)_fileQCDLL->FindObjectAny(hname);

  _fileT1ttttCom->cd();
  TH1D *hT1ttttCom = (TH1D*)_fileT1ttttCom->FindObjectAny(hname);
  _fileT1ttttUnCom->cd();
  TH1D *hT1ttttUnCom = (TH1D*)_fileT1ttttUnCom->FindObjectAny(hname);

  _fileT2ttCom->cd();
  TH1D *hT2ttCom = (TH1D*)_fileT2ttCom->FindObjectAny(hname);
  _fileT2ttUnCom->cd();
  TH1D *hT2ttUnCom = (TH1D*)_fileT2ttUnCom->FindObjectAny(hname);

  _fileT5qqqqVVCom->cd();
  TH1D *hT5qqqqVVCom = (TH1D*)_fileT5qqqqVVCom->FindObjectAny(hname);
  _fileT5qqqqVVUnCom->cd();
  TH1D *hT5qqqqVVUnCom = (TH1D*)_fileT5qqqqVVUnCom->FindObjectAny(hname);

  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  //*AR: After baseline plots were not scaled to 35/fb but correspond to 1/pb, so did scaling here. But Before Baseline plots are already scaled to lumi in Prediction script, so no need of scaling here.
  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  /*
  hT1ttttCom->Scale(35862.351);
  hT1ttttUnCom->Scale(35862.351);

  hT2ttCom->Scale(35862.351);
  hT2ttUnCom->Scale(35862.351);

  hT5qqqqVVCom->Scale(35862.351);
  hT5qqqqVVUnCom->Scale(35862.351);
*/
  hT1ttttCom->SetLineColor(kBlack);
  hT1ttttCom->SetLineWidth(1);
  //  hT1ttttCom->SetMarkerStyle(21);
  //  hT1ttttCom->SetMarkerColor(kGreen);

  hT1ttttUnCom->SetLineColor(kBlack);
  hT1ttttUnCom->SetLineWidth(3);
  hT1ttttUnCom->SetLineStyle(2);
  //  hT1ttttUnCom->SetMarkerStyle(21);
  //  hT1ttttUnCom->SetMarkerColor(kGreen-3);

  hT2ttCom->SetLineColor(kMagenta);
  hT2ttCom->SetLineWidth(1);
  //  hT2ttCom->SetMarkerStyle(21);
  //  hT2ttCom->SetMarkerColor(kBlue);

  hT2ttUnCom->SetLineColor(kMagenta);
  hT2ttUnCom->SetLineWidth(3);
  hT2ttUnCom->SetLineStyle(2);

  //  hT2ttUnCom->SetMarkerStyle(21);
  //  hT2ttUnCom->SetMarkerColor(kBlue-3);

  hT5qqqqVVCom->SetLineColor(kCyan+2);
  hT5qqqqVVCom->SetLineWidth(1);
  //  hT5qqqqVVCom->SetMarkerStyle(21);
  //  hT5qqqqVVCom->SetMarkerColor(kRed);

  hT5qqqqVVUnCom->SetLineColor(kCyan+2);
  hT5qqqqVVUnCom->SetLineWidth(3);
  hT5qqqqVVUnCom->SetLineStyle(2);

  //  hT5qqqqVVUnCom->SetMarkerStyle(21);
  //  hT5qqqqVVUnCom->SetMarkerColor(kRed-3);




  double xmin=hT2ttCom->GetXaxis()->GetXmin();
  double xmax=hT2ttCom->GetXaxis()->GetXmax();
  double diff=xmax-xmin;  
  double ymaximum=hT2ttCom->GetYaxis()->GetXmax();
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

  TH1D *hZJetLLHadtau=(TH1D *) hZJetLL->Clone("hZJetLLHadtau");
  //  hZJetLLHadtau->Add(hZJetHadtau);
  hZJetLLHadtau->SetLineColor(kRed-2);
  hZJetLLHadtau->SetFillColor(kRed-2);

  TH1D *hQCDLLHadtau=(TH1D *) hQCDLL->Clone("hQCDLLHadtau");
  //  hQCDLLHadtau->Add(hQCDHadtau);
  hQCDLLHadtau->SetLineColor(kYellow);
  hQCDLLHadtau->SetFillColor(kYellow);


  THStack * hExp = new THStack("hExp","hExp");
  //  std::cout<<" ****** seg vio ******"<<endl;
  /*
  //*AR: sequence after baseline
  hExp->Add(hSTLLHadtau);
  hExp->Add(hQCDLLHadtau);
  hExp->Add(hWJetLLHadtau);
  hExp->Add(hTTbarLLHadtau);
  hExp->Add(hZJetLLHadtau);
*/
  //*AR: sequence before baseline
  hExp->Add(hSTLLHadtau);
  hExp->Add(hWJetLLHadtau);
  hExp->Add(hTTbarLLHadtau);
  hExp->Add(hZJetLLHadtau);
  hExp->Add(hQCDLLHadtau);



   
  TH1D * hExpFinal=(TH1D*) hExp->GetStack()->Last();
  //  TCanvas *c = new TCanvas("c","c", 500, 500);
  canvas_up->SetLogy();
  //canvas->SetLogy();
  /*
  if(logy)
    canvas_up->SetLogy();
  
  if(logx)
    canvas_up->SetLogx();
    std::cout<<" seg vio 1"<<endl;
  */
  double GetMaxVal=hExp->GetMaximum();
  if(hT2ttCom->GetMaximum() > GetMaxVal)
    GetMaxVal=hT2ttCom->GetMaximum();
  if(hT2ttUnCom->GetMaximum() > GetMaxVal)
    GetMaxVal=hT2ttUnCom->GetMaximum();

  if(hT5qqqqVVCom->GetMaximum() > GetMaxVal)
    GetMaxVal=hT5qqqqVVCom->GetMaximum();
  if(hT5qqqqVVUnCom->GetMaximum() > GetMaxVal)
    GetMaxVal=hT5qqqqVVUnCom->GetMaximum();

  if(hT1ttttCom->GetMaximum() > GetMaxVal)
    GetMaxVal=hT1ttttCom->GetMaximum();
  if(hT1ttttUnCom->GetMaximum() > GetMaxVal)
    GetMaxVal=hT1ttttUnCom->GetMaximum();



  double GetMinVal=hExp->GetMinimum();
  if(hT2ttCom->GetMinimum() < GetMinVal)
    GetMinVal=hT2ttCom->GetMinimum();
  if(hT2ttUnCom->GetMinimum() < GetMinVal)
    GetMinVal=hT2ttUnCom->GetMinimum();

  if(hT5qqqqVVCom->GetMinimum() < GetMinVal)
    GetMinVal=hT5qqqqVVCom->GetMinimum();
  if(hT5qqqqVVUnCom->GetMinimum() < GetMinVal)
    GetMinVal=hT5qqqqVVUnCom->GetMinimum();

  if(hT1ttttCom->GetMinimum() < GetMinVal)
    GetMinVal=hT1ttttCom->GetMinimum();
  if(hT1ttttUnCom->GetMinimum() < GetMinVal)
    GetMinVal=hT1ttttUnCom->GetMinimum();

  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  //*AR: After baseline: maximum-2000*GetMaxVal
  //  Before baseline: maximum-20000*GetMaxVal
  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  
  if(GetMaxVal>hExp->GetMaximum()){
    if(logy)
      hExp->SetMaximum(120000*GetMaxVal);
    else 
      hExp->SetMaximum(20*GetMaxVal);
  }
  else{
    if(logy)
      hExp->SetMaximum(12000*hExp->GetMaximum());
    else 
      hExp->SetMaximum(20*hExp->GetMaximum());
  }

  std::cout<<" seg vio 2"<<endl;  
  //*AR:190104-If you get segmentation violation for arbitary plot due to SetMinimum() command then switch off "if" loops used to set minimum of histogram. Instead fix minimum to some fixed value. 
  //hExp->SetMinimum(9);
  
  if(GetMinVal<hExp->GetMinimum()){
    //    hExp->SetMinimum(0.5*GetMinVal);
    std::cout<<" seg vio 3"<<endl;  
    hExp->SetMinimum(10);

  }
  else{
    //hExp->SetMinimum(0.5*hSTLLHadtau->GetMinimum());
    hExp->SetMinimum(10);

    std::cout<<" seg vio 4"<<endl;  
  }

  hExp->Draw("hist e");

  hExp->GetXaxis()->SetTitle(RatioLabelX);
  //hExp->GetYaxis()->SetTitle(RatioLabelY);
  hExp->GetXaxis()->SetTitleOffset(0.99);
  hExp->GetXaxis()->SetTitleSize(0.05);
  hExp->GetXaxis()->SetLabelSize(0.05);
  hExp->GetYaxis()->SetTitleSize(0.05);
  hExp->GetYaxis()->SetLabelSize(0.05);

  hExp->GetXaxis()->SetTitleFont(42);
  hExp->GetXaxis()->SetLabelOffset(0.008);
  //hExp->GetYaxis()->SetTitleOffset(0.9);
  //hExp->GetYaxis()->SetTitleSize(0.03);
  //hExp->GetYaxis()->SetTitleFont(42);
  hExp->GetYaxis()->SetLabelOffset(0.008);

  hT2ttCom->Draw("hist same");
  hT2ttUnCom->Draw("hist same");

  hT1ttttCom->Draw("hist same");
  hT1ttttUnCom->Draw("hist same");

  hT5qqqqVVCom->Draw("hist same");
  hT5qqqqVVUnCom->Draw("hist same");

  std::cout<<" seg vio 5"<<endl;  

  //  TLegend *tl=new TLegend(Legxmin,Legymin,Legxmax,Legymax);
  TLegend *tl=new TLegend(0.55,0.55,0.92,0.87);

  tl->AddEntry(hT2ttCom, "T2tt[M(#tilde{t}):300,M(#tilde{#chi}_{1}^{0}):213]");
  tl->AddEntry(hT2ttUnCom, "T2tt[M(#tilde{t}):300,M(#tilde{#chi}_{1}^{0}):1]");

  tl->AddEntry(hT1ttttCom, "T1tttt[M(#tilde{g}):600,M(#tilde{#chi}_{1}^{0}):375]");
  tl->AddEntry(hT1ttttUnCom, "T1tttt[M(#tilde{g}):600,M(#tilde{#chi}_{1}^{0}):1]");

  tl->AddEntry(hT5qqqqVVCom, "T5qqqqVV[M(#tilde{g}):600,M(#tilde{#chi}_{1}^{0}):475]");
  tl->AddEntry(hT5qqqqVVUnCom, "T5qqqqVV[M(#tilde{g}):600,M(#tilde{#chi}_{1}^{0}):1]");
  tl->SetLineColor(kWhite);
  tl->Draw("same");

  TLegend *tlx=new TLegend(0.2,0.65,0.47,0.87);
  //*AR:before baseline
  tlx->AddEntry(hQCDLLHadtau, "QCD");
  tlx->AddEntry(hZJetLLHadtau, "Z#nu#nu+jets");
  tlx->AddEntry(hTTbarLLHadtau, "t#bar{t}");
  tlx->AddEntry(hWJetLLHadtau, "W+jets");
  tlx->AddEntry(hSTLLHadtau, "single top");

  //*AR:after baseline
  /*
  tlx->AddEntry(hZJetLLHadtau, "Z#nu#nu+jets");
  tlx->AddEntry(hTTbarLLHadtau, "t#bar{t}");
  tlx->AddEntry(hWJetLLHadtau, "W+jets");
  tlx->AddEntry(hQCDLLHadtau, "QCD");
  tlx->AddEntry(hSTLLHadtau, "single top");
*/
  tlx->SetLineColor(kWhite);
  tlx->Draw("same");

  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.80*canvas_up->GetTopMargin());

  //  ttext->DrawLatexNDC(0.12,0.91, "#bf{CMS} #it{Simulation}");
  //  ttext->DrawLatexNDC(0.14,0.91, "#it{Simulation}");
  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  ttexlumi->SetTextSize(0.80*canvas_up->GetTopMargin());

  ttexlumi->DrawLatexNDC(0.55, 0.91 , "35.9 fb^{-1} (13 TeV)");

  Color_t xc=gStyle->GetTitleColor("X");
  std::cout<<" x color "<<xc<<endl;

  gStyle->SetTitleTextColor(1);
  gStyle->SetLabelColor(1);
  gPad->Update();  
  gPad->Modified();
  std::cout<<" seg vio 6"<<endl;  
  
  //  TH1D * cOne = new TH1D("Ratio","ratio plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram
  /*
  TH1D *  cOne=(TH1D *) hDataLLHadtau->Clone("Ratio");
  cOne->Divide(hExpFinal);
  gStyle->SetPadBottomMargin(0.3);
  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(RatioLabelX);
  cOne->GetYaxis()->SetTitle(RatioLabelY);
  canvas_dw->cd();
  cOne->Draw("e");
  std::cout<<" seg vio 7"<<endl;  
  
  cOne->GetXaxis()->SetTitleOffset(0.9);
  cOne->GetXaxis()->SetTitleSize(0.13);
  cOne->GetXaxis()->SetTitleFont(42);
  cOne->GetXaxis()->SetLabelOffset(0.008);

  cOne->GetYaxis()->SetRangeUser(RatioYmin,RatioYmax);
  cOne->GetYaxis()->SetTitleOffset(0.35);
  cOne->GetYaxis()->SetTitleSize(0.13);
  cOne->GetYaxis()->SetTitleFont(42);
  cOne->GetYaxis()->SetLabelOffset(0.008);

  gStyle->SetPadTickY(1);
  cOne->GetYaxis()->SetNdivisions(5);
  cOne->SetLabelSize(0.115,"XY");
  TLine *tline = new TLine(GetRatioXmin,1.,GetRatioXmax,1.);
  tline->SetLineStyle(2);  
  tline->Draw("same");  
  */
  gStyle->SetLabelColor(1,"xyz");
  gPad->Update();
  gPad->Modified();
  Color_t xcb=gStyle->GetTitleColor("X");
  std::cout<<" x updated color "<<xcb<<endl;

  char PrintName[500];
  //  sprintf(PrintName,"%i_%s.png",hNum,cname);
  //  canvas->SaveAs(PrintName);
  sprintf(PrintName,"%i_%s_190921.pdf",hNum,cname);
  canvas->SaveAs(PrintName);


}

void OverlaySigBack(){
  //*AR: After baseline plots-  

  //  OverlaySigBack(1000,"MHTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}^{miss}","Events",1,0,16,200,1000,0,2.49,70000);
 
  //  OverlaySigBack(1000,"NJetv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{jet}","Events",1,0,10,2,12,0,2.49,50000);

  //  OverlaySigBack(1000,"HTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}","Events",1,0,12,100,2500,0,2.49,90000);
  
  //  OverlaySigBack(1000,"NBtagv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{b-jet}","Events",1,0,5,0,5,0,2.49,200000);

  //  OverlaySigBack(1000,"MHTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}^{miss}","Events",1,0,16,200,1000,0,2.49,70000);
 
  //  OverlaySigBack(1000,"NJetv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{jet}","Events",1,0,10,2,12,0,2.49,50000);

  //  OverlaySigBack(1000,"HTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}","Events",1,0,12,100,2500,0,2.49,90000);
  
  //  OverlaySigBack(1000,"NBtagv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{b-jet}","Events",1,0,5,0,5,0,2.49,200000);

  
  //  OverlaySigBack(1000,"DphiOneforHTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{1},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);

  //  OverlaySigBack(1000,"DphiTwoforHTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{2},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);

  //  OverlaySigBack(1000,"DphiThreeforHTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{3},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);

  //  OverlaySigBack(1000,"DphiFourforHTv2Recipe","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{4},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);


  //*AR: Before baseline plots-

  
  //  OverlaySigBack(1000,"DphiOnev2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{1},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);

  //  OverlaySigBack(1000,"DphiTwov2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{2},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);

  //  OverlaySigBack(1000,"DphiThreev2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{3},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);

  //  OverlaySigBack(1000,"DphiFourv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"#delta#phi(j_{4},MHT)","Events",1,0,32,0,3.2,0,2.49,200000);




  
  OverlaySigBack(1000,"NJetv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{jet}","Events",1,0,10,2,12,0,2.49,50000);

  OverlaySigBack(1000,"HTv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}","Events",1,0,12,100,2500,0,2.49,90000);
  
  OverlaySigBack(1000,"NBtagv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{b-jet}","Events",1,0,5,0,5,0,2.49,200000);

  OverlaySigBack(1000,"MHTv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}^{miss}","Events",1,0,16,200,1000,0,2.49,200000);

  OverlaySigBack(1000,"NJetv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{jet}","Events",1,0,10,2,12,0,2.49,50000);

  OverlaySigBack(1000,"HTv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}","Events",1,0,12,100,2500,0,2.49,90000);
  
  OverlaySigBack(1000,"NBtagv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"N_{b-jet}","Events",1,0,5,0,5,0,2.49,200000);

  OverlaySigBack(1000,"MHTv2Recipe_BeforeBaseline","MC","Prediction_0_haddTTbar_skim_0L.root","Prediction_0_haddWJet_skim_0L.root","Prediction_0_haddST_skim_0L.root","Prediction_0_haddZJet_skim_0L.root","Prediction_0_haddQCD_skim_0L.root","Prediction_0_signal_T1tttt_600_375_0L.root","Prediction_0_signal_T1tttt_600_1_0L.root","Prediction_0_signal_T2tt_300_213_0L.root","Prediction_0_signal_T2tt_300_1_0L.root","Prediction_0_signal_T5qqqqVV_600_475_0L.root","Prediction_0_signal_T5qqqqVV_600_1_0L.root","0L SR",0.5,0.65,0.87,0.87,"H_{T}^{miss}","Events",1,0,16,200,1000,0,2.49,200000);
 

}
