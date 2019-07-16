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
void GetOneDSRCRCombined(int hNum,char const * VarCS, char const * VarPre, char const * VarPreLL, char const * VarPreHadtau,char const * VarPreLLFailAcc, char const * VarPreLLFailIDIso,char const * Sample,char const * TTbarCR,char const * TTbarLL,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){
  
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
  float ymax_top = 2.;
  float ymin_top = 0.0;
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
  double dw_correction = 1.275; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
 
  // set pad size
  canvas_up->SetPad(0., 1 - up_height +0.095, 0.97, 1.);
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.10);
  canvas_up->SetRightMargin(0.03);
  canvas_up->SetBottomMargin(0);

  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.40);
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
  char hnameCS[500], htit[500];
  char hnamePre[500];
  char hnamePreLL[500];
  char hnamePreLLFailIDIso[500];
  char hnamePreLLFailAcc[500]; 
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
  sprintf(hnamePreLLFailIDIso,"%s",VarPreLLFailIDIso);
  sprintf(hnamePreLLFailAcc,"%s",VarPreLLFailAcc);
  //  sprintf(hnameRev,"h_%s_Pre",VarTwo);
  sprintf(RatioLabelX,"%s",xRatioLabel);
  sprintf(RatioLabelY,"%s",yRatioLabel);
  sprintf(cname,"h_%s_Exp",Sample);


  TFile *_fileTTbarCS = TFile::Open(TTbarCR); 

  TFile *_fileTTbarLL = TFile::Open(TTbarLL);
  //  TFile *_fileSTLL = TFile::Open(STLL);
  /*
  TFile *_fileTTbarHadtau = TFile::Open(TTbarHadtau); 
  TFile *_fileWJetHadtau = TFile::Open(WJetHadtau);
  TFile *_fileSTHadtau = TFile::Open(STHadtau);
*/

  //  TFile *_fileData = TFile::Open(DataPred);

  //  _fileTTbarLL->cd();
  TH1D *hTTbarCS = (TH1D*)_fileTTbarCS->FindObjectAny(hnameCS);
  TH1D *hTTbarCSClone = (TH1D*)_fileTTbarCS->FindObjectAny(hnameCS);

  TH1D *hTTbarPre = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePre);
  TH1D *hTTbarPreLL = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePreLL);
  TH1D *hTTbarPreLLFailIDIso = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePreLLFailIDIso);
  TH1D *hTTbarPreLLFailAcc = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePreLLFailAcc);
  TH1D *hTTbarPreHadtau = (TH1D*)_fileTTbarLL->FindObjectAny(hnamePreHadtau);

  TH1D *hTTbarTotalOrg=(TH1D *) hTTbarCS->Clone("hTTbarTotalOrg");
  hTTbarTotalOrg->Add(hTTbarPre,1);

  TH1D *hTTbarFracCSOrg=(TH1D *) hTTbarCS->Clone("hTTbarFracCSOrg");
  hTTbarFracCSOrg->Divide(hTTbarTotalOrg);

  TH1D *hTTbarFracPreOrg=(TH1D *) hTTbarPre->Clone("hTTbarFracPreOrg");
  hTTbarFracPreOrg->Divide(hTTbarTotalOrg);

  TH1D *hTTbarFracPreLLOrg=(TH1D *) hTTbarPreLL->Clone("hTTbarFracPreLLOrg");
  hTTbarFracPreLLOrg->Divide(hTTbarTotalOrg);

  TH1D *hTTbarFracPreLLFailIDIsoOrg=(TH1D *) hTTbarPreLLFailIDIso->Clone("hTTbarFracPreLLFailIDIsoOrg");
  hTTbarFracPreLLFailIDIsoOrg->Divide(hTTbarTotalOrg); 

  TH1D *hTTbarFracPreLLFailAccOrg=(TH1D *) hTTbarPreLLFailAcc->Clone("hTTbarFracPreLLFailAccOrg");
  hTTbarFracPreLLFailAccOrg->Divide(hTTbarTotalOrg); 

  TH1D * hTTbarFracPreHadtauOrg=(TH1D *) hTTbarPreHadtau->Clone("hTTbarFracPreHadtauOrg");
  hTTbarFracPreHadtauOrg->Divide(hTTbarTotalOrg);

  /*
  TH1D *hTTbarFracCS = (TH1D*) hTTbarCSClone->Clone("hTTbarFracCS");
  //  hTTbarFracCS->Reset();
  TH1D *hTTbarFracPre= (TH1D*) hTTbarCSClone->Clone("hTTbarFracPre");
  //  hTTbarFracPre->Reset();
  TH1D *hTTbarFracPreLL= (TH1D*) hTTbarCSClone->Clone("hTTbarFracPreLL");
  //  hTTbarFracPreLL->Reset();
  TH1D *hTTbarFracPreHadtau= (TH1D*) hTTbarCSClone->Clone("hTTbarFracPreHadtau");
  //  hTTbarFracPreHadtau->Reset();
  TH1D *hTTbarFracPreLLFailIDIso= (TH1D*) hTTbarCSClone->Clone("hTTbarFracPreLLFailIDIso");
  //  hTTbarFracPreLLFailIDIso->Reset();
  TH1D *hTTbarFracPreLLFailAcc= (TH1D*) hTTbarCSClone->Clone("hTTbarFracPreLLFailAcc");
  //  hTTbarFracPreLLFailAcc->Reset();
*/
 

  TH1D *hTTbarFracCS = new TH1D("hTTbarFracCS","hTTbarFracCS",19,0.5,19.5);
  TH1D *hTTbarFracPre = new TH1D("hTTbarFracPre","hTTbarFracPre",19,0.5,19.5);
  TH1D *hTTbarFracPreLL = new TH1D("hTTbarFracPreLL","hTTbarFracPreLL",19,0.5,19.5);
  TH1D *hTTbarFracPreLLFailIDIso = new TH1D("hTTbarFracPreLLFailIDIso","hTTbarFracPreLLFailIDIso",19,0.5,19.5);
  TH1D *hTTbarFracPreLLFailAcc = new TH1D("hTTbarFracPreLLFailAcc","hTTbarFracPreLLFailAcc",19,0.5,19.5);
  TH1D *hTTbarFracPreHadtau = new TH1D("hTTbarFracPreHadtau","hTTbarFracPreHadtau",19,0.5,19.5);
  TH1D *hCR = new TH1D("hCR","hCR",19,0.5,19.5);
  TH1D *hSR = new TH1D("hSR","hSR",19,0.5,19.5);



  double CRFrac,LLFailIDIsoFrac,LLFailAccFrac,HadtauFrac,total,CRval,SRval;
  

  for(int i=1;i<=19;i++){
    /*
    total=hTTbarCS->GetBinContent(i)+hTTbarPre->GetBinContent(i);
    CRFrac=hTTbarCS->GetBinContent(i)/total;
    LLFailIDIsoFrac=hTTbarPreLLFailIDIso->GetBinContent(i)/total;
    LLFailAccFrac=hTTbarPreLLFailAcc->GetBinContent(i)/total; 
    HadtauFrac=hTTbarPreHadtau->GetBinContent(i)/total;
    //TFval=hTTbarPre->GetBinContent(i)/hTTbarCS->GetBinContent(i);
*/


    hTTbarFracCS->SetBinContent(i,hTTbarFracCSOrg->GetBinContent(i));
    hTTbarFracCS->SetBinError(i,hTTbarFracCSOrg->GetBinError(i));

    hCR->SetBinContent(i,hTTbarCS->GetBinContent(i));
    hCR->SetBinError(i,hTTbarCS->GetBinError(i));

    hSR->SetBinContent(i,hTTbarPre->GetBinContent(i));
    hSR->SetBinError(i,hTTbarPre->GetBinError(i));


    hTTbarFracPreLLFailIDIso->SetBinContent(i,hTTbarFracPreLLFailIDIsoOrg->GetBinContent(i));
    hTTbarFracPreLLFailIDIso->SetBinError(i,hTTbarFracPreLLFailIDIsoOrg->GetBinError(i));

    hTTbarFracPreLLFailAcc->SetBinContent(i,hTTbarFracPreLLFailAccOrg->GetBinContent(i));
    hTTbarFracPreLLFailAcc->SetBinError(i,hTTbarFracPreLLFailAccOrg->GetBinError(i));

    hTTbarFracPreHadtau->SetBinContent(i,hTTbarFracPreHadtauOrg->GetBinContent(i));
    hTTbarFracPreHadtau->SetBinError(i,hTTbarFracPreHadtauOrg->GetBinError(i));

  }

  //  gStyle->SetHatchesLineWidth(2);
  hTTbarFracCS->SetLineColor(kRed+4);
  hTTbarFracCS->SetFillColor(kRed+4);

  hTTbarFracPreLLFailIDIso->SetLineColor(kBlue);
  hTTbarFracPreLLFailIDIso->SetFillColor(kBlue);
  hTTbarFracPreLLFailIDIso->SetFillStyle(3005);

  hTTbarFracPreHadtau->SetLineColor(96);
  hTTbarFracPreHadtau->SetFillColor(96);
  hTTbarFracPreHadtau->SetFillStyle(3013);


  hTTbarFracPreLLFailAcc->SetLineColor(kGreen+2);
  //  hTTbarFracPreLLFailAcc->SetLineWidth(2);
  hTTbarFracPreLLFailAcc->SetFillColor(kGreen+2);
  hTTbarFracPreLLFailAcc->SetFillStyle(3004);
  /*
  hWJetPreHadtau->SetLineColor(kGreen+1);
  hWJetPreHadtau->SetLineWidth(2);
  hWJetPreHadtau->SetFillColor(kGreen+1);
  hWJetPreHadtau->SetFillStyle(3013);
*/
  //  TH1D * hCR=(TH1D *)hTTbarCS->Clone("hCR");
  //  hCR->Add();

  //  TH1D * hSR=(TH1D *)hTTbarPre->Clone("hSR");
  //  hSR->Add(hWJetPre);

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
  hExp->Add(hTTbarFracCS);
  hExp->Add(hTTbarFracPreHadtau);
  hExp->Add(hTTbarFracPreLLFailIDIso);
  hExp->Add(hTTbarFracPreLLFailAcc);


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
  


  //  hExp->SetTextSize(0.044);
  //  hExp->SetTextFont(42);
   
  TH1D * hExpFinal=(TH1D*) hExp->GetStack()->Last();
  //  TCanvas *c = new TCanvas("c","c", 500, 500);
  //  canvas_up->SetLogy();

  if(logy)
    canvas_up->SetLogy();
  
  if(logx)
    canvas_up->SetLogx();
  std::cout<<" seg vio 1"<<endl;
  /*
    if(logy)
      hExp->SetMaximum(1.);
    //      hExp->SetMaximum(5*hExp->GetMaximum());
    else 
      hExp->SetMaximum(1);
*/
  hExp->SetMaximum(2);
  hExp->SetMinimum(0.001);
  std::cout<<" seg vio 2"<<endl;  
  //*AR:190104-If you get segmentation violation for arbitary plot due to SetMinimum() command then switch off "if" loops used to set minimum of histogram. Instead fix minimum to some fixed value. 
  //  hExp->SetMinimum(0.);
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
  //  hDataLLHadtau->Draw("esame");
  std::cout<<" seg vio 5"<<endl;  
  //  hTTbarFracCS->SetLabelSize(0.032);
  hTTbarFracCS->SetLabelFont(42);
  hTTbarFracCS->SetLabelSize(1.815,"XY");
  
  hExp->GetYaxis()->SetTitle("Fractions");

  hExp->GetYaxis()->SetTitleSize(0.05);
  hExp->GetYaxis()->SetLabelSize(0.05);
  hExp->GetYaxis()->SetLabelFont(42);
  hExp->GetYaxis()->SetLabelOffset(0.008);
  hExp->GetYaxis()->SetTitleOffset(0.88);

//  cOne->SetLabelSize(0.149,"XY"); 
  TLegend *tl=new TLegend(Legxmin,Legymin,Legxmax,Legymax);
  //  tl->SetFillColor(10);
  //  tl->SetHeader("W+jets: Lost lepton, Single lepton fractions");
  //  tl->SetHeader("W+jets");
  tl->SetHeader("t#bar{t}");
  //  tl->AddEntry(hDataLLHadtau, "Data: LL+Had#tau");  //if 0L reg
  //  tl->SetNColumns(2);
  //  tl->AddEntry(hTTbarFracCS," W+jets(CR):1L");

  //  tl->AddEntry(hWJetPreHadtau,"W+jets(SR):#tau_{h}");

  //  tl->AddEntry(hWJetPreLL,"W+jets(SR):LL");

  tl->AddEntry(hTTbarFracPreLLFailAcc,"Lost lepton-fail acceptance","f");
  tl->AddEntry(hTTbarFracPreLLFailIDIso,"Lost lepton-fail ID,Iso","f");
  tl->AddEntry(hTTbarFracPreHadtau,"Lost lepton-#tau_{h}","f");
  tl->AddEntry(hTTbarFracCS,"Single lepton","f");

  /*

  TLegend *tlCS=new TLegend(Legxmin,0.32,Legxmax,0.57);
  tlCS->SetHeader("Single lepton");
  tlCS->AddEntry(hTTbarFracCS,"Lepton found","f");

*/


  //  tl->AddEntry(hWJetCS,"W+jets(CR):1L");

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
  ttext->SetTextSize(0.90*canvas_up->GetTopMargin());
  ttext->DrawLatexNDC(0.15,0.91, "#bf{CMS}");

  TLatex * ttextSup = new TLatex();
  ttextSup->SetTextFont(42);
  ttextSup->SetTextSize(0.50*canvas_up->GetTopMargin());
  ttextSup->DrawLatexNDC(0.29,0.91, "#it{Simulation Supplementary}");

  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  ttexlumi->SetTextSize(0.90*canvas_up->GetTopMargin());
  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  ttexlumi->DrawLatexNDC(0.72, 0.91 , "13 TeV");
  /*
  
  float ymax_top = 2000000.;
  float ymin_top = 0.015;
  */
  float ymax2_top = 1.6;
  float ymax3_top = 1.4;
  float ymax4_top = 1.2;
  float ymax5_top = 1.2;

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


  /*
  tl_njet->DrawLine(4,ymin_top,4,ymax_top); 
  tl_njet->DrawLine(8,ymin_top,8,ymax_top); 
  tl_njet->DrawLine(12,ymin_top,12,ymax_top); 
  tl_njet->DrawLine(16,ymin_top,16,ymax_top); 
*/
    // Njet labels
    TLatex * ttext_njet = new TLatex();
    ttext_njet->SetTextFont(42);
    ttext_njet->SetTextSize(0.0375);
    ttext_njet->SetTextAlign(22);

    ttext_njet->DrawLatex(2.2 , 2.03 , "2 #leq N_{#scale[0.2]{ }jet} #leq 3");
    ttext_njet->DrawLatex(5.5 , 2.03 , "4 #leq N_{#scale[0.2]{ }jet} #leq 5");
    ttext_njet->DrawLatex(9.5 , 2.03 , "6 #leq N_{#scale[0.2]{ }jet} #leq 7");
    ttext_njet->DrawLatex(13.5 , 2.03 , "8 #leq N_{#scale[0.2]{ }jet} #leq 9");
    ttext_njet->DrawLatex(17.5 , 2.03 , "N_{#scale[0.2]{ }jet} #geq 10");
    /*
    ttext_njet->DrawLatex(2.5 , 1.9 , "2 #leq N_{#scale[0.2]{ }jet} #leq 3");
    ttext_njet->DrawLatex(6 , 1.9 , "4 #leq N_{#scale[0.2]{ }jet} #leq 5");
    ttext_njet->DrawLatex(10 , 1.9 , "6 #leq N_{#scale[0.2]{ }jet} #leq 7");
    ttext_njet->DrawLatex(14 , 1.9 , "8 #leq N_{#scale[0.2]{ }jet} #leq 9");
    ttext_njet->DrawLatex(18 , 1.9 , "N_{#scale[0.2]{ }jet} #geq 10");
    */
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

    /*

    tl_nb->DrawLine(2,ymin_top,2,ymax2_top); 
    tl_nb->DrawLine(3,ymin_top,3,ymax2_top); 
    tl_nb->DrawLine(4,ymin_top,4,ymax2_top);
    tl_nb->DrawLine(5,ymin_top,5,ymax2_top);
    tl_nb->DrawLine(6,ymin_top,6,ymax2_top); 
    tl_nb->DrawLine(7,ymin_top,7,ymax2_top); 
    tl_nb->DrawLine(8,ymin_top,8,ymax2_top);
    tl_nb->DrawLine(9,ymin_top,9,ymax3_top);
    tl_nb->DrawLine(10,ymin_top,10,ymax3_top); 
    tl_nb->DrawLine(11,ymin_top,11,ymax3_top); 
    tl_nb->DrawLine(12,ymin_top,12,ymax3_top); 
    tl_nb->DrawLine(13,ymin_top,13,ymax4_top); 
    tl_nb->DrawLine(14,ymin_top,14,ymax4_top); 
    tl_nb->DrawLine(15,ymin_top,15,ymax4_top); 
    tl_nb->DrawLine(16,ymin_top,16,ymax4_top);
    tl_nb->DrawLine(17,ymin_top,17,ymax5_top);
    tl_nb->DrawLine(18,ymin_top,18,ymax5_top);
    tl_nb->DrawLine(19,ymin_top,19,ymax5_top);
    tl_nb->DrawLine(20,ymin_top,20,ymax5_top);

*/    
    // Nb labels
    TLatex * ttext_nb = new TLatex();
    ttext_nb->SetTextFont(42);
    ttext_nb->SetTextSize(0.0375);
    ttext_nb->SetTextAlign(22);
    
    ttext_nb->DrawLatex(2.0 , 1.93 , "N_{#scale[0.2]{ }b-jet}");
    ttext_nb->DrawLatex(1.0 , 1.832 , "0");
    ttext_nb->DrawLatex(2.0 , 1.832 , "1");
    ttext_nb->DrawLatex(3.0 , 1.832 , "#geq 2");
    ttext_nb->DrawLatex(4.0 , 1.832 , "0");
    ttext_nb->DrawLatex(5.0 , 1.832 , "1");
    ttext_nb->DrawLatex(6.0 , 1.832 , "2");
    ttext_nb->DrawLatex(7.0 , 1.832 , "#geq 3");

    tl->SetFillColor(kWhite);    
    tl->SetLineColor(kBlack);
    tl->Draw();
    /*
    tlCS->SetFillColor(kWhite);    
    tlCS->SetLineColor(kBlack);
    tlCS->Draw();
*/
    gPad->SetLeftMargin(0.16);
    gPad->SetBottomMargin(0.);
    
    gPad->Modified();
  std::cout<<" seg vio 6"<<endl;  
  
  //  TH1D * cOne = new TH1D("Ratio","ratio plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram
  TH1D *  cOne=(TH1D *) hSR->Clone("Ratio");
  cOne->Divide(hCR);
  gStyle->SetPadBottomMargin(0.3);
  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(RatioLabelX);
  cOne->GetYaxis()->SetTitle(RatioLabelY);
  canvas_dw->cd();
  cOne->SetMarkerStyle(20);cOne->SetLineColor(1);
  cOne->Draw("e");
  std::cout<<" seg vio 7"<<endl;  
  

  TLegend *tlbottom=new TLegend(Legxmin,Legymin,Legxmax,Legymax);
  //  tl->SetFillColor(10);
  tlbottom->SetHeader("Lost lepton");
  //  tl->AddEntry(hDataLLHadtau, "Data: LL+Had#tau");  //if 0L reg
  //  tl->SetNColumns(2);
  tlbottom->AddEntry(cOne," t#bar{t}","pe");


  cOne->GetXaxis()->SetTitleOffset(1.05);
  cOne->GetXaxis()->SetTitleSize(0.13);
  cOne->GetXaxis()->SetLabelSize(0.13);
  cOne->GetXaxis()->SetTitleFont(42);
  cOne->GetXaxis()->SetLabelOffset(0.008);

  cOne->GetYaxis()->SetRangeUser(RatioYmin,RatioYmax);
  cOne->GetYaxis()->SetTitleOffset(0.44);
  cOne->GetYaxis()->SetTitleSize(0.13);
  cOne->GetYaxis()->SetLabelSize(0.13);
  cOne->GetYaxis()->SetTitleFont(42);
  cOne->GetYaxis()->SetLabelOffset(0.008);

  gStyle->SetPadTickY(1);
  gStyle->SetErrorX(0);
  cOne->GetYaxis()->SetNdivisions(5);
  cOne->SetLabelSize(0.149,"XY");
  TLine *tline = new TLine(GetRatioXmin,1.,GetRatioXmax,1.);
  tline->SetLineStyle(2);  
  tline->Draw("same");  


    // Njet separation lines

  TLine *tlCS_njet = new TLine();
  tlCS_njet->SetLineStyle(2);
  tlCS_njet->DrawLine(3.5,ymin_top,3.5,2); 
  tlCS_njet->DrawLine(7.5,ymin_top,7.5,2); 
  tlCS_njet->DrawLine(11.5,ymin_top,11.5,2); 
  tlCS_njet->DrawLine(15.5,ymin_top,15.5,2); 


  /*

  TLine *tlb_njet = new TLine();
  tlb_njet->SetLineStyle(2);
  tlb_njet->DrawLine(4,ymin_top,4,ymax_top); 
  tlb_njet->DrawLine(8,ymin_top,8,ymax_top); 
  tlb_njet->DrawLine(12,ymin_top,12,ymax_top); 
  tlb_njet->DrawLine(16,ymin_top,16,ymax_top); 

*/    
    // Nb separation lines
    
    TLine *tlCS_nb = new TLine();
    tlCS_nb->SetLineStyle(3);
    tlCS_nb->DrawLine(1.5,ymin_top,1.5,2); 
    tlCS_nb->DrawLine(2.5,ymin_top,2.5,2); 
    tlCS_nb->DrawLine(3.5,ymin_top,3.5,2);
    tlCS_nb->DrawLine(4.5,ymin_top,4.50,2);
    tlCS_nb->DrawLine(5.5,ymin_top,5.5,2); 
    tlCS_nb->DrawLine(6.5,ymin_top,6.5,2); 
    tlCS_nb->DrawLine(7.5,ymin_top,7.5,2);
    tlCS_nb->DrawLine(8.5,ymin_top,8.5,2);
    tlCS_nb->DrawLine(9.5,ymin_top,9.5,2); 
    tlCS_nb->DrawLine(10.5,ymin_top,10.5,2); 
    tlCS_nb->DrawLine(11.5,ymin_top,11.5,2); 
    tlCS_nb->DrawLine(12.5,ymin_top,12.5,2); 
    tlCS_nb->DrawLine(13.5,ymin_top,13.5,2); 
    tlCS_nb->DrawLine(14.5,ymin_top,14.5,2); 
    tlCS_nb->DrawLine(15.5,ymin_top,15.5,2);
    tlCS_nb->DrawLine(16.5,ymin_top,16.5,2);
    tlCS_nb->DrawLine(17.5,ymin_top,17.5,2);
    tlCS_nb->DrawLine(18.5,ymin_top,18.5,2);
    tlCS_nb->DrawLine(19.5,ymin_top,19.5,2);


    /*

  TLine *tlb_nb = new TLine();
    tlb_nb->SetLineStyle(3);
    tlb_nb->DrawLine(2,ymin_top,2,ymax2_top); 
    tlb_nb->DrawLine(3,ymin_top,3,ymax2_top); 
    tlb_nb->DrawLine(4,ymin_top,4,ymax2_top);
    tlb_nb->DrawLine(5,ymin_top,5,ymax2_top);
    tlb_nb->DrawLine(6,ymin_top,6,ymax2_top); 
    tlb_nb->DrawLine(7,ymin_top,7,ymax2_top); 
    tlb_nb->DrawLine(8,ymin_top,8,ymax2_top);
    tlb_nb->DrawLine(9,ymin_top,9,ymax3_top);
    tlb_nb->DrawLine(10,ymin_top,10,ymax3_top); 
    tlb_nb->DrawLine(11,ymin_top,11,ymax3_top); 
    tlb_nb->DrawLine(12,ymin_top,12,ymax3_top); 
    tlb_nb->DrawLine(13,ymin_top,13,ymax4_top); 
    tlb_nb->DrawLine(14,ymin_top,14,ymax4_top); 
    tlb_nb->DrawLine(15,ymin_top,15,ymax4_top); 
    tlb_nb->DrawLine(16,ymin_top,16,ymax4_top);
    tlb_nb->DrawLine(17,ymin_top,17,ymax5_top);
    tlb_nb->DrawLine(18,ymin_top,18,ymax5_top);
    tlb_nb->DrawLine(19,ymin_top,19,ymax5_top);
    tlb_nb->DrawLine(20,ymin_top,20,ymax5_top);
*/
    

    //tlCS->SetFillColor(kWhite);    
    //    tlCS->SetLineColor(kBlack);
    //    tlCS->Draw();
    gPad->RedrawAxis();
    //    gPad->SetTicks(1,1);
    gPad->SetLeftMargin(0.16);
    //    gPad->SetBottomMargin(0);
    gPad->Modified();

    char PrintName[500];
    sprintf(PrintName,"%i_%s.png",hNum,cname);
    canvas->Print(PrintName);
    sprintf(PrintName,"%i_%s.pdf",hNum,cname);
    canvas->Print(PrintName);



}

void GetOneDSRCRCombined(){
  
  //*AR-181211-Here files "Prediction_0_haddTTbar_AppliedPrefireMap_NewCodeconsistentwithOldCode_1L.root" is copied to "Prediction_0_haddTTbar_0L_.root" and so on.

  /*
    GetOneDPlots(1200,"LepEtafor50","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

    GetOneDPlots(1200,"LepEtafor100","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);

    GetOneDPlots(1200,"LepEtafor200","DataVsMCRemovedExcessDeepCSV_1L_HighDphi_NotAppliedAsElectronPrefireMapNoAcceptanceOnMC","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"Lepton #eta","Data/MC",0,0,10,-2.5,2.5,0,2.49,50000);
*/



  
  GetOneDSRCRCombined(1300,"h_CSStat_NJetvsNBtag_1D","h_CSStat_SR_NJetvsNBtag_1D","h_CSStat_LL_NJetvsNBtag_1D","h_CSStat_Hadtau_NJetvsNBtag_1D","h_CSStat_LL_FailAcc_NJetvsNBtag_1D","h_CSStat_LL_FailIDIso_NJetvsNBtag_1D","2017_CRSR_forSupplimentary","Prediction_0_haddTTbar_1L_.root","Prediction_0_haddTTbar_0L_.root","SR+CR",0.47,0.5,0.962,0.83,"N_{jet}, N_{b-jet} bin index","#frac{Lost lepton}{Single lepton}",0,0,19,0.5,19.5,0,1.9,200000);
  
  /*
  GetOneDPlots(1000,"MHTv2Recipe","2017_Final_1L_NewPrefire","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"MHT","Data/MC",1,0,16,200,1000,0,2.49,70000);

  GetOneDPlots(1100,"HTv2Recipe","2017_Final_1L_NewPrefire","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"HT","Data/MC",1,0,12,100,2500,0,2.49,90000);

  GetOneDPlots(1200,"NJetv2Recipe","2017_Final_1L_NewPrefire","Prediction_0_haddTTbar_0L_.root","Prediction_0_haddWJet_0L_.root","Prediction_0_haddST_0L_.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L CR",0.57,0.6,0.87,0.87,"NJet","Data/MC",1,0,10,2,12,0,2.49,50000);



  */

}
