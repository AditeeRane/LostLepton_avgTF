#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>
#include <THStack.h>

//*AR: 181016: use this definition of function if histograms to be compared from two files have different names
//void GetOneDPlots(int hNum,char const * Var,char const * VarTwo,char const * Sample,char const * TTbarLL,char const * WJetLL,char const * STLL,char const* DataPred,ochar const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){

//*AR: 181016: use this definition of function if histograms to be compared from two files have same name
void GetOneDTFLLPlusHadtauPlots(int hNum,char const * VarCS, char const * VarPre, char const * VarPreLL, char const * VarPreHadtau,char const * Sample,char const * TTbarLL,char const * WJetLL,char const * STLL,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){
  
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
  float ymax_top = 2500000.;
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

  canvas->Divide(1, 3);

  //
  // Define pads
  //
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
  TPad* canvas_dwdw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_3");
 
  // define the size
  double up_height     = 0.8;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.275; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
 
  //1 - up_height +0.095=0.295
  //dw_height_offset=0.04
  //dw_height+dw_height_offset=(0.2*1.275) + 0.04= 0.255+0.04=0.295
  // set pad size
  //  canvas_up->SetPad(0., 1 - up_height +0.095, 0.97, 1.);
  //  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);

  //  canvas_up->SetPad(0.,0.6, 0.97, 1.);
  //  canvas_dw->SetPad(0.,0.295, 0.97, 0.6);
  //  canvas_dwdw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);

  canvas_up->SetPad(0.,0.55, 0.97, 1.); //0.42
  canvas_dw->SetPad(0.,0.275, 0.97, 0.55); //0.275
  canvas_dwdw->SetPad(0., dw_height_offset, 0.97, 0.275); //0.245


  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.12);
  canvas_up->SetRightMargin(0.03);
  canvas_up->SetBottomMargin(0);  

  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetTopMargin(0.0);
  canvas_dw->SetRightMargin(0.03);
  canvas_dw->SetBottomMargin(0);  

  canvas_dwdw->SetFillColor(0);
  canvas_dwdw->SetFrameFillColor(0);
  canvas_dwdw->SetBottomMargin(0.4);
  canvas_dwdw->SetRightMargin(0.03);
  canvas_dwdw->SetTopMargin(0);


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
  char hnameCS[500], htit[500];
  char hnamePre[500];
  char hnamePreLL[500];
  char hnamePreHadtau[500]; 
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
  sprintf(hnameCS,"%s",VarCS);
  sprintf(hnamePre,"%s",VarPre);
  sprintf(hnamePreLL,"%s",VarPreLL);
  sprintf(hnamePreHadtau,"%s",VarPreHadtau);
  //  sprintf(hnameRev,"h_%s_Pre",VarTwo);
  sprintf(RatioLabelX,"%s",xRatioLabel);
  sprintf(RatioLabelY,"%s",yRatioLabel);
  sprintf(cname,"h_%s_Exp",Sample);


  TFile *_fileTTbarLL = TFile::Open(TTbarLL); 

  TFile *_fileWJetLL = TFile::Open(WJetLL);
  TFile *_fileSTLL = TFile::Open(STLL);
  /*
  TFile *_fileTTbarHadtau = TFile::Open(TTbarHadtau); 
  TFile *_fileWJetHadtau = TFile::Open(WJetHadtau);
  TFile *_fileSTHadtau = TFile::Open(STHadtau);
*/

  //  TFile *_fileData = TFile::Open(DataPred);
  TH1::SetDefaultSumw2();
  //  _fileTTbarLL->cd();
  TH1D *hOrgTTbarCS = (TH1D*)_fileTTbarLL->FindObjectAny(hnameCS);
  TH1D *hOrgTTbarPre = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePre);
  TH1D *hOrgTTbarPreLL = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePreLL);
  TH1D *hOrgTTbarPreHadtau = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePreHadtau);

  TH1D *hOrgWJetCS = (TH1D*)_fileWJetLL->FindObjectAny(hnameCS);
  TH1D *hOrgWJetPre = (TH1D*)_fileWJetLL->FindObjectAny(hnamePre);
  TH1D *hOrgWJetPreLL = (TH1D*)_fileWJetLL->FindObjectAny(hnamePreLL);
  TH1D *hOrgWJetPreHadtau = (TH1D*)_fileWJetLL->FindObjectAny(hnamePreHadtau);

  TH1D *hOrgSTCS = (TH1D*)_fileSTLL->FindObjectAny(hnameCS);
  TH1D *hOrgSTPre = (TH1D*)_fileSTLL->FindObjectAny(hnamePre);


  TH1D* hTTbarCS = new TH1D("hTTbarCS","hTTbarCS",19,0.5,19.5);
  TH1D* hWJetCS = new TH1D("hWJetCS","hWJetCS",19,0.5,19.5);
  TH1D* hSTCS = new TH1D("hSTCS","hSTCS",19,0.5,19.5);

  TH1D* hTTbarPre = new TH1D("hTTbarPre","hTTbarPre",19,0.5,19.5);
  TH1D* hWJetPre = new TH1D("hWJetPre","hWJetPre",19,0.5,19.5);
  TH1D* hSTPre = new TH1D("hSTPre","hSTPre",19,0.5,19.5);

  for(int i=1;i<=19;i++){
    hTTbarCS->SetBinContent(i,hOrgTTbarCS->GetBinContent(i));
    hTTbarCS->SetBinError(i,hOrgTTbarCS->GetBinError(i));

    hWJetCS->SetBinContent(i,hOrgWJetCS->GetBinContent(i));
    hWJetCS->SetBinError(i,hOrgWJetCS->GetBinError(i));

    hSTCS->SetBinContent(i,hOrgSTCS->GetBinContent(i));
    hSTCS->SetBinError(i,hOrgSTCS->GetBinError(i));

    hTTbarPre->SetBinContent(i,hOrgTTbarPre->GetBinContent(i));
    hTTbarPre->SetBinError(i,hOrgTTbarPre->GetBinError(i));

    hWJetPre->SetBinContent(i,hOrgWJetPre->GetBinContent(i));
    hWJetPre->SetBinError(i,hOrgWJetPre->GetBinError(i));

    hSTPre->SetBinContent(i,hOrgSTPre->GetBinContent(i));
    hSTPre->SetBinError(i,hOrgSTPre->GetBinError(i));

  }




  hTTbarCS->Scale(137/41.486);
  hTTbarPre->Scale(137/41.486);

  //  hTTbarPreLL->Scale(137/41.486);
  //  hTTbarPreHadtau->Scale(137/41.486);

  hWJetCS->Scale(137/41.486);
  hWJetPre->Scale(137/41.486);
  //  hWJetPreLL->Scale(137/41.486);
  //  hWJetPreHadtau->Scale(137/41.486);
  hSTCS->Scale(137/41.486);
  hSTPre->Scale(137/41.486);



  //  gStyle->SetHatchesLineWidth(2);
  hTTbarCS->SetLineColor(kGreen+2);
  hTTbarCS->SetFillColor(kGreen+2);

  hTTbarPre->SetLineColor(kGreen+2);
  hTTbarPre->SetFillColor(kGreen+2);
  hTTbarPre->SetFillStyle(3013);

  hWJetCS->SetLineColor(kBlue);
  hWJetCS->SetFillColor(kBlue);

  hWJetPre->SetLineColor(kBlue);
  //  hWJetPre->SetLineWidth(2);
  hWJetPre->SetFillColor(kBlue);
  hWJetPre->SetFillStyle(3013);


  hSTCS->SetLineColor(96);
  hSTCS->SetFillColor(96);

  hSTPre->SetLineColor(96);
  //  hSTPre->SetLineWidth(2);
  hSTPre->SetFillColor(96);
  hSTPre->SetFillStyle(3013);

  /*
  hWJetPreLL->SetLineColor(kGreen+1);
  hWJetPreLL->SetLineWidth(2);
  hWJetPreLL->SetFillColor(kGreen+1);
  hWJetPreLL->SetFillStyle(3008);

  hWJetPreHadtau->SetLineColor(kGreen+1);
  hWJetPreHadtau->SetLineWidth(2);
  hWJetPreHadtau->SetFillColor(kGreen+1);
  hWJetPreHadtau->SetFillStyle(3013);
*/



  TH1D * hCR=(TH1D *)hTTbarCS->Clone("hCR");
  hCR->Add(hWJetCS);
  hCR->Add(hSTCS);

  TH1D * hSR=(TH1D *)hTTbarPre->Clone("hSR");
  hSR->Add(hWJetPre);
  hSR->Add(hSTPre);

  hSR->SetMarkerStyle(20);
  hSR->SetMarkerSize(1.2);
  hSR->SetLineColor(1);

  /*

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
*/

  THStack * hExp = new THStack("hExp","hExp");
  //  std::cout<<" ****** seg vio ******"<<endl;
  hExp->Add(hSTPre);
  hExp->Add(hWJetPre);
  hExp->Add(hTTbarPre);

  THStack * hExpCS = new THStack("hExpCS","hExpCS");
  hExpCS->Add(hSTCS);
  hExpCS->Add(hWJetCS);
  hExpCS->Add(hTTbarCS);

  /*
  hExp->Add(hWJetCS);
  hExp->Add(hTTbarCS);

  hExp->Add(hWJetPreLL);
  hExp->Add(hTTbarPreLL);

  hExp->Add(hWJetPreHadtau);
  hExp->Add(hTTbarPreHadtau);
*/

  //  hWJetCS->SetLabelSize(0.032);
  //  hWJetCS->SetLabelFont(42);
  
  //  hExp->GetYaxis()->SetTitle(hname);
  //  hExp->SetTextSize(0.064);
  //  hExp->SetTextFont(42);
   
  TH1D * hExpFinal=(TH1D*) hExp->GetStack()->Last();
  TH1D * hExpCSFinal=(TH1D*) hExpCS->GetStack()->Last();

  //  TCanvas *c = new TCanvas("c","c", 500, 500);
  //  canvas_up->SetLogy();

  if(logy){
    canvas_up->SetLogy();
    canvas_dw->SetLogy();
  }


  std::cout<<" seg vio 2"<<endl;  
  //*AR:190104-If you get segmentation violation for arbitary plot due to SetMinimum() command then switch off "if" loops used to set minimum of histogram. Instead fix minimum to some fixed value. 
  hExp->SetMinimum(9);
  hExpCS->SetMinimum(9);

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

  //*AR-Label and Title are properties of axis and not of THStack
  hExp->Draw("hist e");
  hExp->GetYaxis()->SetTitle("Events");

  if(logx)
    canvas_up->SetLogx();
  std::cout<<" seg vio 1"<<endl;
  
  if(logy){
    hExp->SetMaximum(2500000.);
    //    hExpCS->GetYaxis()->SetRange(9,900000.);
  }
  //      hExp->SetMaximum(5*hExp->GetMaximum());
  else{ 
    hExp->SetMaximum(1.5*hExpCS->GetMaximum());
    //    hExpCS->SetMaximum(1.5*hExpCS->GetMaximum());
  }
  std::cout<<" max "<<hExpCS->GetMaximum()<<" *1.5 "<<1.5*hExpCS->GetMaximum()<<endl;


  hExp->GetYaxis()->SetTitleSize(0.08);
  hExp->GetYaxis()->SetLabelSize(0.08);
  hExp->GetYaxis()->SetLabelFont(42);
  hExp->GetYaxis()->SetTitleOffset(0.80);
  //  hDataLLHadtau->Draw("esame");
  std::cout<<" seg vio 5"<<endl;  

  TLegend *tl=new TLegend(Legxmin,Legymin,Legxmax,Legymax);
  //  tl->SetFillColor(10);
  tl->SetHeader("Lost lepton");
  //  tl->AddEntry(hDataLLHadtau, "Data: LL+Had#tau");  //if 0L reg
  //  tl->SetNColumns(2);
  tl->AddEntry(hTTbarPre," t#bar{t}","f");
  tl->AddEntry(hWJetPre,"W+jets","f");
  tl->AddEntry(hSTPre,"Single top","f");

  TLegend *tlCS=new TLegend(Legxmin,0.62,Legxmax,0.97);
  tlCS->SetHeader("Single lepton");
  tlCS->AddEntry(hTTbarCS," t#bar{t}","f");
  tlCS->AddEntry(hWJetCS,"W+jets","f");
  tlCS->AddEntry(hSTCS,"Single top","f");


  /*

  tl->AddEntry(hWJetCS,"W + jets(1L)");
  tl->AddEntry(hTTbarCS," t#bar{t}(1L)");

  tl->AddEntry(hWJetPreLL,"W + jets(0L):LL");
  tl->AddEntry(hTTbarPreLL," t#bar{t}(0L):LL");

  tl->AddEntry(hWJetPreHadtau,"W + jets(0L):Hadtau");
  tl->AddEntry(hTTbarPreHadtau," t#bar{t}(0L):Hadtau");
*/

  /*

  tl->AddEntry(hDataLLHadtau, "Data"); 
  tl->AddEntry(hSTLLHadtau, "MC: single top");
  tl->AddEntry(hWJetLLHadtau, "MC: W+jets");
  tl->AddEntry(hTTbarLLHadtau, "MC: TTbar");
*/
  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.85*canvas_up->GetTopMargin());
  ttext->DrawLatexNDC(0.16,0.91, "#bf{CMS} #it{Simulation}");

  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  ttexlumi->SetTextSize(0.85*canvas_up->GetTopMargin());
  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  ttexlumi->DrawLatexNDC(0.65, 0.91 , "137 fb^{-1} (13 TeV)");
  /*
  
  float ymax_top = 2000000.;
  float ymin_top = 0.015;
  */
  float ymax2_top = 100000.;
  float ymax3_top = 30000.;
  float ymax4_top = 10000.;
  float ymax5_top = 1000;

  //float ymax_bottom = 1.19;
  //float ymin_bottom = 0.81;
  /*
  float ymax_bottom = 1.99;
  float ymin_bottom = 0.01;
  */
  float ymax2_bottom = 2.15;
  float ymax3_bottom = 2.15;
  float ymax4_bottom = 2.15;

    // Njet separation lines
  TLine *tl_njet = new TLine();
  tl_njet->SetLineStyle(2);
  tl_njet->DrawLine(3.5,ymin_top,3.5,ymax_top); 
  tl_njet->DrawLine(7.5,ymin_top,7.5,ymax_top); 
  tl_njet->DrawLine(11.5,ymin_top,11.5,ymax_top); 
  tl_njet->DrawLine(15.5,ymin_top,15.5,ymax_top); 

    // Njet labels
    TLatex * ttext_njet = new TLatex();
    ttext_njet->SetTextFont(42);
    ttext_njet->SetTextSize(0.0525);
    ttext_njet->SetTextAlign(22);
    ttext_njet->DrawLatex(2.2 , 2000000 , "2 #leq N_{#scale[0.2]{ }jet} #leq 3");
    ttext_njet->DrawLatex(5.5 , 2000000 , "4 #leq N_{#scale[0.2]{ }jet} #leq 5");
    ttext_njet->DrawLatex(9.5 , 2000000 , "6 #leq N_{#scale[0.2]{ }jet} #leq 7");
    ttext_njet->DrawLatex(13.5 , 2000000 , "8 #leq N_{#scale[0.2]{ }jet} #leq 9");
    ttext_njet->DrawLatex(17.5 , 2000000 , "N_{#scale[0.2]{ }jet} #geq 10");
    
    // Nb separation lines
    TLine *tl_nb = new TLine();
    tl_nb->SetLineStyle(3);
    tl_nb->DrawLine(1.5,ymin_top,1.5,ymax2_top); 
    tl_nb->DrawLine(2.5,ymin_top,2.5,ymax2_top); 
    tl_nb->DrawLine(3.5,ymin_top,3.5,ymax2_top);
    tl_nb->DrawLine(4.5,ymin_top,4.50,ymax2_top);
    tl_nb->DrawLine(5.5,ymin_top,5.5,ymax2_top); 
    tl_nb->DrawLine(6.5,ymin_top,6.5,ymax2_top); 
    tl_nb->DrawLine(7.5,ymin_top,7.5,ymax2_top);
    tl_nb->DrawLine(8.5,ymin_top,8.5,ymax3_top);
    tl_nb->DrawLine(9.5,ymin_top,9.5,ymax3_top); 
    tl_nb->DrawLine(10.5,ymin_top,10.5,ymax3_top); 
    tl_nb->DrawLine(11.5,ymin_top,11.5,ymax3_top); 
    tl_nb->DrawLine(12.5,ymin_top,12.5,ymax4_top); 
    tl_nb->DrawLine(13.5,ymin_top,13.5,ymax4_top); 
    tl_nb->DrawLine(14.5,ymin_top,14.5,ymax4_top); 
    tl_nb->DrawLine(15.5,ymin_top,15.5,ymax4_top);
    tl_nb->DrawLine(16.5,ymin_top,16.5,ymax5_top);
    tl_nb->DrawLine(17.5,ymin_top,17.5,ymax5_top);
    tl_nb->DrawLine(18.5,ymin_top,18.5,ymax5_top);
    tl_nb->DrawLine(19.5,ymin_top,19.5,ymax5_top);

    
    // Nb labels
    TLatex * ttext_nb = new TLatex();
    ttext_nb->SetTextFont(42);
    ttext_nb->SetTextSize(0.0525);
    ttext_nb->SetTextAlign(22);
    
    ttext_nb->DrawLatex(2.0 , 800000 , "N_{#scale[0.2]{ }b-jet}");
    ttext_nb->DrawLatex(1.0 , 300000 , "0");
    ttext_nb->DrawLatex(2.0 , 300000 , "1");
    ttext_nb->DrawLatex(3.0 , 300000 , "#geq 2");
    ttext_nb->DrawLatex(4.0 , 300000 , "0");
    ttext_nb->DrawLatex(5.0 , 300000 , "1");
    ttext_nb->DrawLatex(6.0 , 300000 , "2");
    ttext_nb->DrawLatex(7.0 , 300000 , "#geq 3");

    tl->SetFillColor(kWhite);    
    tl->SetLineColor(kBlack);
    tl->Draw();
    gPad->SetLeftMargin(0.16);
    gPad->SetBottomMargin(0.);
    gPad->Modified();


    canvas_dw->cd();
    hExpCS->Draw("hist e");


    if(logy){
      //      hExp->GetYaxis()->SetRange(9,2500000.);
      hExpCS->GetYaxis()->SetRange(9,900000.);
    }
    //      hExp->SetMaximum(5*hExp->GetMaximum());
    else{ 
      // hExp->SetMaximum(1.5*hExpCS->GetMaximum());
      hExpCS->SetMaximum(1.5*hExpCS->GetMaximum());
    }



    hExpCS->GetYaxis()->SetTitle("Events");

    hExpCS->GetYaxis()->SetTitleSize(0.12);
    hExpCS->GetYaxis()->SetLabelSize(0.12);
    hExpCS->GetYaxis()->SetLabelFont(42);
    hExpCS->GetYaxis()->SetTitleOffset(0.50);
    

    // Njet separation lines
  TLine *tlCS_njet = new TLine();
  tlCS_njet->SetLineStyle(2);
  tlCS_njet->DrawLine(3.5,ymin_top,3.5,ymax_top); 
  tlCS_njet->DrawLine(7.5,ymin_top,7.5,ymax_top); 
  tlCS_njet->DrawLine(11.5,ymin_top,11.5,ymax_top); 
  tlCS_njet->DrawLine(15.5,ymin_top,15.5,ymax_top); 
    // Nb separation lines
    TLine *tlCS_nb = new TLine();
    tlCS_nb->SetLineStyle(3);
    tlCS_nb->DrawLine(1.5,ymin_top,1.5,ymax2_top); 
    tlCS_nb->DrawLine(2.5,ymin_top,2.5,ymax2_top); 
    tlCS_nb->DrawLine(3.5,ymin_top,3.5,ymax2_top);
    tlCS_nb->DrawLine(4.5,ymin_top,4.50,ymax2_top);
    tlCS_nb->DrawLine(5.5,ymin_top,5.5,ymax2_top); 
    tlCS_nb->DrawLine(6.5,ymin_top,6.5,ymax2_top); 
    tlCS_nb->DrawLine(7.5,ymin_top,7.5,ymax2_top);
    tlCS_nb->DrawLine(8.5,ymin_top,8.5,ymax3_top);
    tlCS_nb->DrawLine(9.5,ymin_top,9.5,ymax3_top); 
    tlCS_nb->DrawLine(10.5,ymin_top,10.5,ymax3_top); 
    tlCS_nb->DrawLine(11.5,ymin_top,11.5,ymax3_top); 
    tlCS_nb->DrawLine(12.5,ymin_top,12.5,ymax4_top); 
    tlCS_nb->DrawLine(13.5,ymin_top,13.5,ymax4_top); 
    tlCS_nb->DrawLine(14.5,ymin_top,14.5,ymax4_top); 
    tlCS_nb->DrawLine(15.5,ymin_top,15.5,ymax4_top);
    tlCS_nb->DrawLine(16.5,ymin_top,16.5,ymax5_top);
    tlCS_nb->DrawLine(17.5,ymin_top,17.5,ymax5_top);
    tlCS_nb->DrawLine(18.5,ymin_top,18.5,ymax5_top);
    tlCS_nb->DrawLine(19.5,ymin_top,19.5,ymax5_top);
    

    tlCS->SetFillColor(kWhite);    
    tlCS->SetLineColor(kBlack);
    tlCS->Draw();
    gPad->RedrawAxis();
    //    gPad->SetTicks(1,1);
    gPad->SetLeftMargin(0.16);
    gPad->SetBottomMargin(0);
    gPad->Modified();











    std::cout<<" seg vio 6"<<endl;  
    //  TH1D * cOne = new TH1D("Ratio","ratio plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram
  TH1D *  cOne=(TH1D *) hSR->Clone("Ratio");
  cOne->Divide(hCR);
  for(int i=1;i<=19;i++){
    std::cout<<" CR_v "<<hCR->GetBinContent(i)<<" CR_e "<<hCR->GetBinError(i)<<" SR_v "<<hSR->GetBinContent(i)<<" SR_e "<<hSR->GetBinError(i)<<" cone-v "<<cOne->GetBinContent(i)<<" cone_e "<<cOne->GetBinError(i)<<endl;    
  }
  
  gStyle->SetPadBottomMargin(0.3);
  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(RatioLabelX);
  cOne->GetYaxis()->SetTitle(RatioLabelY);
  canvas_dwdw->cd();
  cOne->SetMarkerStyle(20);
  cOne->SetMarkerSize(1.2);
  cOne->SetLineColor(1);
  cOne->Draw("e");
  std::cout<<" seg vio 7"<<endl;  
  
  cOne->GetXaxis()->SetTitleOffset(0.98);
  cOne->GetXaxis()->SetTitleSize(0.15);
  cOne->GetXaxis()->SetTitleFont(42);
  cOne->GetXaxis()->SetLabelOffset(0.008);

  cOne->GetYaxis()->SetRangeUser(RatioYmin,RatioYmax);
  cOne->GetYaxis()->SetTitleOffset(0.37);
  cOne->GetYaxis()->SetTitleSize(0.145);
  cOne->GetYaxis()->SetTitleFont(42);
  cOne->GetYaxis()->SetLabelOffset(0.008);

  gStyle->SetPadTickY(1);
  gStyle->SetErrorX(0);
  cOne->GetYaxis()->SetNdivisions(5);
  cOne->SetLabelSize(0.149,"XY");


  TLegend *tlbottom=new TLegend(Legxmin,Legymin,Legxmax,Legymax);
  //  tl->SetFillColor(10);
  tlbottom->SetHeader("Lost lepton");
  //  tl->AddEntry(hDataLLHadtau, "Data: LL+Had#tau");  //if 0L reg
  //  tl->SetNColumns(2);
  tlbottom->AddEntry(cOne," t#bar{t}","pe");




  TLine *tline = new TLine(GetRatioXmin,1.,GetRatioXmax,1.);
  tline->SetLineStyle(2);  
  tline->Draw("same");  


    // Njet separation lines
  TLine *tlb_njet = new TLine();
  tlb_njet->SetLineStyle(2);

  tlb_njet->DrawLine(3.5,ymin_top,3.5,ymax_top); 
  tlb_njet->DrawLine(7.5,ymin_top,7.5,ymax_top); 
  tlb_njet->DrawLine(11.5,ymin_top,11.5,ymax_top); 
  tlb_njet->DrawLine(15.5,ymin_top,15.5,ymax_top); 

    
    // Nb separation lines
    TLine *tlb_nb = new TLine();
    tlb_nb->SetLineStyle(3);
    tlb_nb->DrawLine(1.5,ymin_top,1.5,ymax2_top); 
    tlb_nb->DrawLine(2.5,ymin_top,2.5,ymax2_top); 
    tlb_nb->DrawLine(3.5,ymin_top,3.5,ymax2_top);
    tlb_nb->DrawLine(4.5,ymin_top,4.50,ymax2_top);
    tlb_nb->DrawLine(5.5,ymin_top,5.5,ymax2_top); 
    tlb_nb->DrawLine(6.5,ymin_top,6.5,ymax2_top); 
    tlb_nb->DrawLine(7.5,ymin_top,7.5,ymax2_top);
    tlb_nb->DrawLine(8.5,ymin_top,8.5,ymax3_top);
    tlb_nb->DrawLine(9.5,ymin_top,9.5,ymax3_top); 
    tlb_nb->DrawLine(10.5,ymin_top,10.5,ymax3_top); 
    tlb_nb->DrawLine(11.5,ymin_top,11.5,ymax3_top); 
    tlb_nb->DrawLine(12.5,ymin_top,12.5,ymax4_top); 
    tlb_nb->DrawLine(13.5,ymin_top,13.5,ymax4_top); 
    tlb_nb->DrawLine(14.5,ymin_top,14.5,ymax4_top); 
    tlb_nb->DrawLine(15.5,ymin_top,15.5,ymax4_top);
    tlb_nb->DrawLine(16.5,ymin_top,16.5,ymax5_top);
    tlb_nb->DrawLine(17.5,ymin_top,17.5,ymax5_top);
    tlb_nb->DrawLine(18.5,ymin_top,18.5,ymax5_top);
    tlb_nb->DrawLine(19.5,ymin_top,19.5,ymax5_top);


  gPad->Update();
  gPad->SetLeftMargin(0.16);
  gPad->Modified();
  char PrintName[500];
  sprintf(PrintName,"%i_%s.png",hNum,cname);
  canvas->Print(PrintName);
  sprintf(PrintName,"%i_%s.pdf",hNum,cname);
  canvas->Print(PrintName);



}

void GetOneDTFLLPlusHadtauPlots(){
  

  
  GetOneDTFLLPlusHadtauPlots(1300,"h_CSStat_NJetvsNBtag_1D","h_Prediction_NJetvsNBtag_1D","h_PredictionLL_NJetvsNBtag_1D","h_PredictionHadtau_NJetvsNBtag_1D","TFLLPlusHadtauCombined_BillFinalSuggestion","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","SR+CR",0.75,0.55,0.95,0.77,"N_{jet}, N_{b-jet} bin index","#frac{Lost lepton}{Single lepton}",1,0,19,0.5,19.5,0,2.19,200000);
  
}
