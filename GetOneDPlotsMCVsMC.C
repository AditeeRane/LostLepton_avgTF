#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>


//*AR: 181016: use this definition of function if histograms to be compared from two files have different names

void GetOneDPlotsMCVsMC(int hNum,char const * Var,char const * VarTwo,char const * Sample,char const * TTbarLL, char const * TTbarHadtau,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){

  //  TH1::SetDefaultSumw2();
//*AR: 181016: use this definition of function if histograms to be compared from two files have same name and comment unnecessry lines in code accordingly

//void GetOneDPlotsMCVsMC(int hNum,char const * Var,char const * Sample,char const * TTbarLL, char const * TTbarHadtau,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMax){
  
  //*AR:180831: Borrow cosmetics specific to RA2b style

  double lumi     = 36.35;
  double lumi_ref = 41.486; // normaliza to 3 (fb-1)

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
  //*AR: canvas_up:(0,0.21,0.97,1): original giving plots for paper
  //  canvas_up->SetPad(0., 1 - up_height +0.01, 0.97, 1.);
  //*AR:Due to overlap of up and down pad, here ymin is readjusted to recover low values in top plot, which used to be hidden due to above overlap.

  canvas_up->SetPad(0., 1 - up_height +0.095, 0.97, 1.);

  //*AR: canvas_dw:(0,0.04,0.97,0.3)
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.10);
  canvas_up->SetRightMargin(0.03);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.30);
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
  string var(Var);

  sprintf(header,"%s",LegHeader);
  sprintf(hname,"h_%s_Exp",Var);
  sprintf(RatioLabelX,"%s",xRatioLabel);
  sprintf(RatioLabelY,"%s",yRatioLabel);
  sprintf(cname,"h_%s_Pre_%s",Var,Sample);
  sprintf(hnameRev,"h_%s_Pre",VarTwo);
  //  if(var.find("MHTOrig")!=string::npos)
  //  sprintf(hnameRev,"h_%s_Pre",Var);
  TFile *_fileTTbarLL = TFile::Open(TTbarLL); 

  TFile *_fileTTbarHadtau = TFile::Open(TTbarHadtau); 

  //  TFile *_fileData = TFile::Open(DataPred);

  _fileTTbarLL->cd();
  //  TH1D *hTTbarLL = (TH1D*)_fileTTbarLL->FindObjectAny("h_NJetv2Recipe_Exp");
  //  TH1D *hTTbarLL = (TH1D*)_fileTTbarLL->FindObjectAny("h_MHTv2Recipe_Exp");
  //Use this line only for Njet, HT, MHT
  TH1D *hTTbarLL = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  //  hTTbarLL->Scale(137.06/118.77);


  // This block is needed only while comparing btags because MC expectation has btags>4 but not for MC prediction as we use btag prob for MC prediction. This is not the case for Data prediction.
  /*
  TH1D *hTTbarLLOrg = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  //hTTbarLLOrg->Scale(137.06/118.77);
  TH1D *hTTbarLL = new TH1D("hTTbarLL","hTTbarLL",4,0,4);
  //  hTTbarLL->Sumw2();
  int nbins=hTTbarLL->GetXaxis()->GetNbins();
  for(int i=1;i<=nbins;i++){
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
  */
  //*AR:B:E vs F
  //  hTTbarLL->Scale(13498.0/27987.0);
  //*AR:16 Vs 17
  //  hTTbarLL->Scale(35900.0/5000.0);
  hTTbarLL->SetLineColor(kRed);
  hTTbarLL->SetLineWidth(2);
  hTTbarLL->SetMarkerStyle(21);
  hTTbarLL->SetMarkerColor(kRed);
  double xmin=hTTbarLL->GetXaxis()->GetXmin();
  double xmax=hTTbarLL->GetXaxis()->GetXmax();
  double diff=xmax-xmin;  
  double ymaximum=hTTbarLL->GetYaxis()->GetXmax();
  std::cout<<" xmin "<<xmin<<" xmax "<<xmax<<" diff "<<diff<<" ymaximum "<<ymaximum<<endl;
  //hTTbarLL->GetYaxis()->SetRangeUser(0.001,ymax); 

  //  _fileData->cd();
  //  TH1D *hDataLLHadtau = (TH1D*)_fileData->FindObjectAny(hname);

  _fileTTbarHadtau->cd();
  //TH1D *hTTbarHadtau = (TH1D*)_fileTTbarHadtau->FindObjectAny("h_MHT_Exp");
  //  TH1D *hTTbarHadtau = (TH1D*)_fileTTbarHadtau->FindObjectAny("h_DphiOne_Exp");
  TH1D *hTTbarHadtau = (TH1D*)_fileTTbarHadtau->FindObjectAny(hnameRev);
  //hTTbarHadtau->Scale(137.06/118.77);

  // This block is needed only while comparing btags as Btag plot in prediction also has x-axis range 0-5 
  /*
  TH1D *hTTbarHadtauOrg = (TH1D*)_fileTTbarHadtau->FindObjectAny(hnameRev);
  //  hTTbarHadtauOrg->Scale(137.06/118.77);
  TH1D *hTTbarHadtau = new TH1D("hTTbarHadtau","hTTbarHadtau",4,0,4);
  //  hTTbarHadtau->Sumw2();
  nbins=hTTbarHadtau->GetXaxis()->GetNbins();
  for(int i=1;i<=nbins;i++){
    if(i<=3){
      double val=hTTbarHadtauOrg->GetBinContent(i);
      double err=hTTbarHadtauOrg->GetBinError(i);
      hTTbarHadtau->SetBinContent(i,val);
      hTTbarHadtau->SetBinError(i,err);
    }
    else{
      double val=hTTbarHadtauOrg->GetBinContent(i)+hTTbarHadtauOrg->GetBinContent(i+1);
      double err=sqrt(hTTbarHadtauOrg->GetBinError(i)*hTTbarHadtauOrg->GetBinError(i) + hTTbarHadtauOrg->GetBinError(i+1)*hTTbarHadtauOrg->GetBinError(i+1));
      hTTbarHadtau->SetBinContent(i,val);
      hTTbarHadtau->SetBinError(i,err);
    }
 }
  */

  //  hTTbarHadtau->Scale(35900.0/41486.0);
  hTTbarHadtau->SetLineColor(kBlue);
  hTTbarHadtau->SetMarkerColor(kBlue);
  hTTbarHadtau->SetLineWidth(2);
  hTTbarHadtau->SetMarkerStyle(24);
  //  hTTbarHadtau->SetMarkerSize(0.0001);
  //  hTTbarHadtau->SetFillStyle(3144);
  //  hTTbarHadtau->SetFillColor(kBlue);
  ////  TH1D *hTTbarLLHadtau=(TH1D *) hTTbarLL->Clone("hTTbarLLHadtau");
  //  hTTbarLLHadtau->Add(hTTbarHadtau);

  if(logy)
    canvas_up->SetLogy();
  
  if(logx)
    canvas_up->SetLogx();

  
  if(hTTbarHadtau->GetMaximum()>hTTbarLL->GetMaximum()){
    if(logy)
      hTTbarLL->SetMaximum(3*hTTbarHadtau->GetMaximum());
    else 
      hTTbarLL->SetMaximum(1.5*hTTbarHadtau->GetMaximum());
  }
  else{
    if(logy)
      hTTbarLL->SetMaximum(3*hTTbarLL->GetMaximum());
    else 
      hTTbarLL->SetMaximum(1.5*hTTbarLL->GetMaximum());
  }
  /*
  if(hTTbarHadtau->GetMinimum()<hTTbarLL->GetMinimum())
    hTTbarLL->SetMinimum(0.5*hTTbarHadtau->GetMinimum());
*/
  hTTbarLL->SetMinimum(9);
  if(!logy)
    hTTbarLL->SetMinimum(0);

  hTTbarLL->Draw("e");
  hTTbarHadtau->Draw("esame");
  //  hTTbarHadtau->GetYaxis()->SetRangeUser(0,ymax);
  
  //  TLegend *tl=new TLegend(0.57,0.7,0.87,0.87);
  //  TLegend *tl=new TLegend(0.77,0.78,0.89,0.89); 
  TLegend *tl=new TLegend(Legxmin,Legymin,Legxmax,Legymax);
  tl->SetHeader(header);
 
  //*AR:B:E vs F 
  //  tl->AddEntry(hTTbarHadtau, "2017(F)");
  //  tl->AddEntry(hTTbarLL, "2017(B:E)"); 


  //  tl->AddEntry(hTTbarHadtau, "Data17F:v1");
  //  tl->AddEntry(hTTbarLL, "Data17F:v2"); 

  tl->AddEntry(hTTbarHadtau, "MC Pred");
  tl->AddEntry(hTTbarLL, "MC Exp"); 

  //  tl->AddEntry(hTTbarHadtau, "Data17(F)");
  //  tl->AddEntry(hTTbarLL, "Data17(B:E)");
 

  tl->SetLineColor(kWhite);
  tl->Draw("same");
  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  //ttext->DrawLatex(GetRatioXmin , 1.1*ymax , "#bf{CMS} #it{Preliminary}");
  //  ttext->DrawLatex(xmin , 1*ymax , "#bf{CMS} #it{Preliminary}");
  ttext->DrawLatexNDC(0.15,0.91, "#bf{CMS} #it{Preliminary}");
  
  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  //  ttexlumi->DrawLatex(GetRatioXmax-10*binSize, ymaximum , "35.9fb^{-1} (13TeV)");

  //*AR:B:E vs F   
  //  ttexlumi->DrawLatex(xmin+0.65*diff, 1*ymax , "13.49fb^{-1} (13TeV)");
  //  ttexlumi->DrawLatex(xmin+0.65*diff, 1*ymax , "5.0fb^{-1} (13TeV)");
  ttexlumi->DrawLatexNDC(0.7, 0.91 , "59.546 fb^{-1} (13 TeV)");
  
  gPad->Modified();
  
  TH1D * cOne = new TH1D("Ratio","ratio plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram
  cOne=(TH1D *) hTTbarHadtau->Clone("Ratio");
  cOne->Divide(hTTbarLL);
  gStyle->SetPadBottomMargin(0.3);
  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(RatioLabelX);
  cOne->GetYaxis()->SetTitle(RatioLabelY);
  canvas_dw->cd();
  cOne->Draw("e");
  
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
  cOne->GetYaxis()->SetNdivisions(8);
  cOne->SetLabelSize(0.115,"XY");
  TLine *tline = new TLine(GetRatioXmin,1.,GetRatioXmax,1.);
  tline->SetLineStyle(2);  
  tline->Draw("same");  
  gPad->Update();
  gPad->Modified();
  char PrintName[500];
  sprintf(PrintName,"%i_%s.png",hNum,cname);
  canvas->Print(PrintName);
  sprintf(PrintName,"%i_%s.pdf",hNum,cname);
  canvas->Print(PrintName);




}



void GetOneDPlotsMCVsMC(){
  /*
  
  GetOneDPlotsMCVsMC(1000,"MHT","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","17(F)/17(B:E)",1,0,16,200,1000,0.5,1.5,25000);
  
  GetOneDPlotsMCVsMC(1100,"HT","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"HT","17(F)/17(B:E)",1,0,12,100,2500,0.5,1.5,22000);

  GetOneDPlotsMCVsMC(1200,"NJet","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NJet","17(F)/17(B:E)",1,0,10,2,12,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1300,"NBtag","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NBtag","17(F)/17(B:E)",1,0,5,0,5,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1400,"DphiOne","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","17(F)/17(B:E)",1,0,32,0,3.2,0.5,1.5,15000);


  GetOneDPlotsMCVsMC(1500,"DphiTwo","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","17(F)/17(B:E)",1,0,32,0,3.2,0.5,1.5,4500);

  GetOneDPlotsMCVsMC(1600,"DphiThree","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","17(F)/17(B:E)",1,0,32,0,3.2,0.5,1.5,4000);

  GetOneDPlotsMCVsMC(1700,"DphiFour","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","17(F)/17(B:E)",1,0,32,0,3.2,0.5,1.5,2000);

  GetOneDPlotsMCVsMC(1800,"LepPt","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","17(F)/17(B:E)",1,0,20,0,1000,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1900,"LepEta","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","17(F)/17(B:E)",0,0,10,-2.5,2.5,0.5,1.5,3500);

  GetOneDPlotsMCVsMC(2000,"LepPhi","BCDEVsF_HighDphi","Prediction_0_Data_MET_V15bcde_.root","Prediction_0_Data_MET_V15f_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","17(F)/17(B:E)",0,0,7,-3.5,3.5,0.5,1.5,3600);
   
  
  GetOneDPlotsMCVsMC(1310,"NBtag","BCDEVsF_HighDphiMu","Prediction_0_Data_MET_V15bcdeMu_.root","Prediction_0_Data_MET_V15fMu_.root","#mu CS",0.57,0.7,0.87,0.87,"NBtag","17(F)/17(B:E)",1,0,5,0,5,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1410,"DphiOne","BCDEVsF_HighDphiMu","Prediction_0_Data_MET_V15bcdeMu_.root","Prediction_0_Data_MET_V15fMu_.root","#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","17(F)/17(B:E)",1,0,32,0,3.2,0.5,1.5,8000);

  GetOneDPlotsMCVsMC(1810,"LepPt","BCDEVsF_HighDphiMu","Prediction_0_Data_MET_V15bcdeMu_.root","Prediction_0_Data_MET_V15fMu_.root","#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","17(F)/17(B:E)",1,0,20,0,1000,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1910,"LepEta","BCDEVsF_HighDphiMu","Prediction_0_Data_MET_V15bcdeMu_.root","Prediction_0_Data_MET_V15fMu_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","17(F)/17(B:E)",0,0,10,-2.5,2.5,0.5,1.5,1900);

  GetOneDPlotsMCVsMC(2010,"LepPhi","BCDEVsF_HighDphiMu","Prediction_0_Data_MET_V15bcdeMu_.root","Prediction_0_Data_MET_V15fMu_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","17(F)/17(B:E)",0,0,7,-3.5,3.5,0.5,1.5,2020);


  GetOneDPlotsMCVsMC(1320,"NBtag","BCDEVsF_HighDphiEle","Prediction_0_Data_MET_V15bcdeEle_.root","Prediction_0_Data_MET_V15fEle_.root","e CS",0.57,0.7,0.87,0.87,"NBtag","17(F)/17(B:E)",1,0,5,0,5,0.5,1.5,20000);

    GetOneDPlotsMCVsMC(1420,"DphiOne","BCDEVsF_HighDphiEle","Prediction_0_Data_MET_V15bcdeEle_.root","Prediction_0_Data_MET_V15fEle_.root","e CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","17(F)/17(B:E)",1,0,32,0,3.2,0.5,1.5,8000);

  GetOneDPlotsMCVsMC(1820,"LepPt","BCDEVsF_HighDphiEle","Prediction_0_Data_MET_V15bcdeEle_.root","Prediction_0_Data_MET_V15fEle_.root","e CS",0.57,0.7,0.87,0.87,"Lep_pT","17(F)/17(B:E)",1,0,20,0,1000,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1920,"LepEta","BCDEVsF_HighDphiEle","Prediction_0_Data_MET_V15bcdeEle_.root","Prediction_0_Data_MET_V15fEle_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#eta","17(F)/17(B:E)",0,0,10,-2.5,2.5,0.5,1.5,1650);

  GetOneDPlotsMCVsMC(2020,"LepPhi","BCDEVsF_HighDphiEle","Prediction_0_Data_MET_V15bcdeEle_.root","Prediction_0_Data_MET_V15fEle_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#phi","17(F)/17(B:E)",0,0,7,-3.5,3.5,0.5,1.5,1650);
*/
  /*
  
  GetOneDPlotsMCVsMC(1000,"MHT","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","Data16/Data17",1,0,16,200,1000,0.5,1.5,80000);

  GetOneDPlotsMCVsMC(1100,"HT","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","Data16/Data17",1,0,12,100,2500,0.5,1.5,50000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NJet","Data16/Data17",1,0,10,2,12,0.5,1.5,40000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,100000);

  GetOneDPlotsMCVsMC(1310,"NBtag","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,60000);

  GetOneDPlotsMCVsMC(1320,"NBtag","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1400,"DphiOne","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,50000);

  GetOneDPlotsMCVsMC(1410,"DphiOne","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1420,"DphiOne","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1500,"DphiTwo","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,25000);
  
    GetOneDPlotsMCVsMC(1600,"DphiThree","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,15000);
  
  GetOneDPlotsMCVsMC(1700,"DphiFour","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,6200);

  GetOneDPlotsMCVsMC(1800,"LepPt","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,50000);
  
  GetOneDPlotsMCVsMC(1810,"LepPt","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1820,"LepPt","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,25000);
  
  GetOneDPlotsMCVsMC(1900,"LepEta","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,13000);
  
    GetOneDPlotsMCVsMC(1910,"LepEta","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,7200);

    GetOneDPlotsMCVsMC(1920,"LepEta","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,5800);

  GetOneDPlotsMCVsMC(2000,"LepPhi","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,12800);

  GetOneDPlotsMCVsMC(2010,"LepPhi","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,7000);

  GetOneDPlotsMCVsMC(2020,"LepPhi","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,5600);

*/
  /*
  
  GetOneDPlotsMCVsMC(1000,"MHT","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","Data16/Data17",1,0,16,200,1000,0.5,1.5,60000);

  GetOneDPlotsMCVsMC(1100,"HT","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"HT","Data16/Data17",1,0,12,100,2500,0.5,1.5,60000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NJet","Data16/Data17",1,0,10,2,12,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,80000);


  GetOneDPlotsMCVsMC(1310,"NBtag","Data1LHighDphiMu","Prediction_0_Data_MET_Sep18Mu_V15_.root","Prediction_0_Data_MET_Sep19Mu_V12_.root","#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,40000);

  GetOneDPlotsMCVsMC(1320,"NBtag","Data1LHighDphiEle","Prediction_0_Data_MET_Sep18Ele_V15_.root","Prediction_0_Data_MET_Sep19Ele_V12_.root","e CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1400,"DphiOne","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,32000);

  GetOneDPlotsMCVsMC(1410,"DphiOne","Data1LHighDphiMu","Prediction_0_Data_MET_Sep18Mu_V15_.root","Prediction_0_Data_MET_Sep19Mu_V12_.root","#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1420,"DphiOne","Data1LHighDphiEle","Prediction_0_Data_MET_Sep18Ele_V15_.root","Prediction_0_Data_MET_Sep19Ele_V12_.root","e CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1500,"DphiTwo","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,12000);

  GetOneDPlotsMCVsMC(1600,"DphiThree","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,9000);

  GetOneDPlotsMCVsMC(1700,"DphiFour","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,4000);

  GetOneDPlotsMCVsMC(1800,"LepPt","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,70000);

  GetOneDPlotsMCVsMC(1810,"LepPt","Data1LHighDphiMu","Prediction_0_Data_MET_Sep18Mu_V15_.root","Prediction_0_Data_MET_Sep19Mu_V12_.root","#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,40000);

  GetOneDPlotsMCVsMC(1820,"LepPt","Data1LHighDphiEle","Prediction_0_Data_MET_Sep18Ele_V15_.root","Prediction_0_Data_MET_Sep19Ele_V12_.root","e CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1900,"LepEta","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,9000);

  GetOneDPlotsMCVsMC(1910,"LepEta","Data1LHighDphiMu","Prediction_0_Data_MET_Sep18Mu_V15_.root","Prediction_0_Data_MET_Sep19Mu_V12_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,5000);

  GetOneDPlotsMCVsMC(1920,"LepEta","Data1LHighDphiEle","Prediction_0_Data_MET_Sep18Ele_V15_.root","Prediction_0_Data_MET_Sep19Ele_V12_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,4200);

  GetOneDPlotsMCVsMC(2000,"LepPhi","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,9200);
  
  GetOneDPlotsMCVsMC(2010,"LepPhi","Data1LHighDphiMu","Prediction_0_Data_MET_Sep18Mu_V15_.root","Prediction_0_Data_MET_Sep19Mu_V12_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,5200);

  GetOneDPlotsMCVsMC(2020,"LepPhi","Data1LHighDphiEle","Prediction_0_Data_MET_Sep18Ele_V15_.root","Prediction_0_Data_MET_Sep19Ele_V12_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,4200);



  GetOneDPlotsMCVsMC(2120,"MHTPhi","Data1LHighDphiEle","Prediction_0_Data_MET_Sep27Ele_V15_.root","Prediction_0_Data_MET_Sep27Ele_V12_.root","e CS",0.47,0.3,0.77,0.47,"#phi(MHT)","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,4100);

  GetOneDPlotsMCVsMC(2220,"METPhi","Data1LHighDphiEle","Prediction_0_Data_MET_Sep27Ele_V15_.root","Prediction_0_Data_MET_Sep27Ele_V12_.root","e CS",0.47,0.3,0.77,0.47,"#phi(MET)","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,4050);

  GetOneDPlotsMCVsMC(2320,"MET","Data1LHighDphiEle","Prediction_0_Data_MET_Sep27Ele_V15_.root","Prediction_0_Data_MET_Sep27Ele_V12_.root","e CS",0.57,0.7,0.87,0.87,"MET","Data16/Data17",1,0,16,200,1000,0.5,1.5,9000);

  GetOneDPlotsMCVsMC(2420,"mT","Data1LHighDphiEle","Prediction_0_Data_MET_Sep27Ele_V15_.root","Prediction_0_Data_MET_Sep27Ele_V12_.root","e CS",0.47,0.3,0.77,0.47,"mT","Data16/Data17",1,0,20,0,100,0.5,1.5,2500);
  
  GetOneDPlotsMCVsMC(2520,"NBtagclean","Data1LHighDphiEle","Prediction_0_Data_MET_Sep27Ele_V15_.root","Prediction_0_Data_MET_Sep27Ele_V12_.root","e CS",0.57,0.7,0.87,0.87,"NBtagclean","Data16/Data17",1,0,5,0,5,0.5,1.5,30000);
  */
  /*
  GetOneDPlotsMCVsMC(2120,"MHTPhi","Data1LLowDphiEle","Prediction_0_Data_MET_Sep27LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep27LowDphiEle_V12_.root","e CS",0.47,0.3,0.77,0.47,"#phi(MHT)","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,5700);

  GetOneDPlotsMCVsMC(2220,"METPhi","Data1LLowDphiEle","Prediction_0_Data_MET_Sep27LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep27LowDphiEle_V12_.root","e CS",0.47,0.3,0.77,0.47,"#phi(MET)","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,5700);

  GetOneDPlotsMCVsMC(2320,"MET","Data1LLowDphiEle","Prediction_0_Data_MET_Sep27LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep27LowDphiEle_V12_.root","e CS",0.57,0.7,0.87,0.87,"MET","Data16/Data17",1,0,16,200,1000,0.5,1.5,10000);

  GetOneDPlotsMCVsMC(2420,"mT","Data1LLowDphiEle","Prediction_0_Data_MET_Sep27LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep27LowDphiEle_V12_.root","e CS",0.47,0.3,0.77,0.47,"mT","Data16/Data17",1,0,20,0,100,0.5,1.5,6000);
  
  GetOneDPlotsMCVsMC(2520,"NBtagclean","Data1LLowDphiEle","Prediction_0_Data_MET_Sep27LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep27LowDphiEle_V12_.root","e CS",0.57,0.7,0.87,0.87,"NBtagclean","Data16/Data17",1,0,5,0,5,0.5,1.5,30000);
*/

  /*
  GetOneDPlotsMCVsMC(1300,"NBtag","Data1LHighDphi","Prediction_0_Data_MET_Sep28CorrectedBtagPtEta_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,80000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data1LLowDphi","Prediction_0_Data_MET_Sep28LowDphiCorrectedBtagPtEta_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,120000);
*/
  /*
  GetOneDPlotsMCVsMC(1000,"MHT","MHT","DataPredHighDphi_17Vs16","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TF.root","LL+Had#tau",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",1,0,16,200,1000,0.5,1.5,30000);
  
  GetOneDPlotsMCVsMC(1100,"HT","HT","DataPredHighDphi_17Vs16","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TF.root","LL+Had#tau",0.57,0.7,0.87,0.87,"HT","Data17/Data16",1,0,12,100,2500,0.5,1.5,41000);

  GetOneDPlotsMCVsMC(1200,"NJet","NJet","DataPredHighDphi_17Vs16","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TF.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NJet","Data17/Data16",1,0,10,2,12,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1300,"NBtag","NBtag","DataPredHighDphi_17Vs16","Prediction_0_Data_MET_afterhadd_180830_With1DPredHists.root","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TF.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NBtag","Data17/Data16",1,0,5,0,5,0.5,1.5,50000);

*/



  //*AR:181106: 2017BE vs 2016 in 0L
 /*
    
  GetOneDPlotsMCVsMC(1000,"MHT","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",1,0,16,200,1000,0.5,1.5,30000);
  
  GetOneDPlotsMCVsMC(1100,"HT","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"HT","Data17/Data16",1,0,12,100,2500,0.5,1.5,41000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","Data17/Data16",1,0,10,2,12,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(2100,"MHTPhi","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5400);

  GetOneDPlotsMCVsMC(2200,"METPhi","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MET)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5500);

  GetOneDPlotsMCVsMC(2300,"MET","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MET","Data17/Data16",1,0,16,200,1000,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","Data17/Data16",1,0,5,0,5,0.5,1.5,50000);

  GetOneDPlotsMCVsMC(1400,"DphiOne","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,18000);

  GetOneDPlotsMCVsMC(1500,"DphiTwo","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.3,0.87,0.47,"#delta#phi(j_{2},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,4000);

  GetOneDPlotsMCVsMC(1600,"DphiThree","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.3,0.87,0.47,"#delta#phi(j_{3},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,2000);

  GetOneDPlotsMCVsMC(1700,"DphiFour","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,1000);
*/

  /*
  GetOneDPlotsMCVsMC(1010,"MHTOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",1,0,16,200,1000,0.5,1.5,30000);
  
  GetOneDPlotsMCVsMC(2110,"MHTPhiOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5400);

  GetOneDPlotsMCVsMC(2210,"METPhiOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MET)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5500);

  GetOneDPlotsMCVsMC(2310,"METOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MET","Data17/Data16",1,0,16,200,1000,0.5,1.5,7000);

  GetOneDPlotsMCVsMC(1410,"DphiOneOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,18000);

  GetOneDPlotsMCVsMC(1510,"DphiTwoOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.2,0.87,0.37,"#delta#phi(j_{2},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,4000);

  GetOneDPlotsMCVsMC(1610,"DphiThreeOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.6,0.87,0.77,"#delta#phi(j_{3},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,2000);

  GetOneDPlotsMCVsMC(1710,"DphiFourOrig","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.6,0.87,0.77,"#delta#phi(j_{4},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,1000);
*/

  /*

  GetOneDPlotsMCVsMC(1020,"MHTv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",1,0,16,200,1000,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1120,"HTv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"HT","Data17/Data16",1,0,12,100,2500,0.5,1.5,41000);

  GetOneDPlotsMCVsMC(1220,"NJetv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","Data17/Data16",1,0,10,2,12,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(2120,"MHTPhiv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5400);
*/
  //  GetOneDPlotsMCVsMC(2220,"METPhiv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MET)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5500);

  //  GetOneDPlotsMCVsMC(2320,"METv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MET","Data17/Data16",1,0,16,200,1000,0.5,1.5,7000);
  /*
  GetOneDPlotsMCVsMC(1320,"NBtagv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","Data17/Data16",1,0,5,0,5,0.5,1.5,50000);

  GetOneDPlotsMCVsMC(1420,"DphiOnev2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,18000);

  GetOneDPlotsMCVsMC(1520,"DphiTwov2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.2,0.87,0.37,"#delta#phi(j_{2},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,4000);

  GetOneDPlotsMCVsMC(1620,"DphiThreev2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.6,0.87,0.77,"#delta#phi(j_{3},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,2000);

  GetOneDPlotsMCVsMC(1720,"DphiFourv2Recipe","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.6,0.87,0.77,"#delta#phi(j_{4},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,1000);

*/
  
  

  /*
  GetOneDPlotsMCVsMC(1000,"MHT","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","F/B:E",1,0,16,200,1000,0.5,1.5,15000);

  GetOneDPlotsMCVsMC(1100,"HT","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HT","F/B:E",1,0,12,100,2500,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","F/B:E",1,0,10,2,12,0.5,1.5,22000);

  GetOneDPlotsMCVsMC(2100,"MHTPhi","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5400);

  GetOneDPlotsMCVsMC(2200,"METPhi","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MET)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5500);

  GetOneDPlotsMCVsMC(2300,"MET","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MET","F/B:E",1,0,16,200,1000,0.5,1.5,10000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","F/B:E",1,0,5,0,5,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1400,"DphiOne","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,9000);

  GetOneDPlotsMCVsMC(1500,"DphiTwo","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,2100);

  GetOneDPlotsMCVsMC(1600,"DphiThree","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,1300);

  GetOneDPlotsMCVsMC(1700,"DphiFour","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,520);
  


*/

  /*  
  //B:E vs F- MET-v1

  
  GetOneDPlotsMCVsMC(1000,"MHT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","F/B:E",1,0,16,200,1000,0.5,1.5,15000);

  GetOneDPlotsMCVsMC(1100,"HT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HT","F/B:E",1,0,12,100,2500,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","F/B:E",1,0,10,2,12,0.5,1.5,22000);

  GetOneDPlotsMCVsMC(1300,"MHTPhi","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5400);

  GetOneDPlotsMCVsMC(1400,"METPhi","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MET)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5500);

  GetOneDPlotsMCVsMC(1500,"MET","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MET","F/B:E",1,0,16,200,1000,0.5,1.5,10000);

  GetOneDPlotsMCVsMC(1600,"NBtag","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","F/B:E",1,0,5,0,5,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1700,"DphiOne","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,9000);

  GetOneDPlotsMCVsMC(1800,"DphiTwo","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.3,0.87,0.47,"#delta#phi(j_{2},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,2100);

  GetOneDPlotsMCVsMC(1900,"DphiThree","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.3,0.87,0.47,"#delta#phi(j_{3},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,1300);

  GetOneDPlotsMCVsMC(2000,"DphiFour","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.3,0.87,0.47,"#delta#phi(j_{4},MHT)","F/B:E",1,0,32,0,3.2,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2100,"JetEtaforHT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2200,"JetPtforHT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2101,"JetEtaforHTLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2201,"JetPtforHTLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2102,"JetEtaforHTNotLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2202,"JetPtforHTNotLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2300,"rawJetPtforHT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2400,"JetEtaforMHTminusHT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,100,-5.,5.,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2500,"JetPtforMHTminusHT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2401,"JetEtaforMHTminusHTLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,100,-5.,5.,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2501,"JetPtforMHTminusHTLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2402,"JetEtaforMHTminusHTNotLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,100,-5.,5.,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2502,"JetPtforMHTminusHTNotLead","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2600,"rawJetPtforMHTminusHT","Data0LHighDphi_BEVsF_v1","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  */
  


    
  
  
  //B:E vs F- MET-v2  

  /*    
  GetOneDPlotsMCVsMC(1050,"MHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","F/B:E",1,0,16,200,1000,0.5,1.5,15000);

  GetOneDPlotsMCVsMC(1058,"MHTforLowNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","F/B:E",1,0,16,200,1000,0.5,1.5,15000);

  GetOneDPlotsMCVsMC(1059,"MHTforHighNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","F/B:E",1,0,16,200,1000,0.5,1.5,15000);

  GetOneDPlotsMCVsMC(1150,"HTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HT","F/B:E",1,0,12,100,2500,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1158,"HTforLowNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HT","F/B:E",1,0,12,100,2500,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1159,"HTforHighNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HT","F/B:E",1,0,12,100,2500,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(11150,"HTRatiov2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HTRatio","F/B:E",1,0,20,0,5,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(11158,"HTRatioforLowNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HTRatio","F/B:E",1,0,20,0,5,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(11159,"HTRatioforHighNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HTRatio","F/B:E",1,0,20,0,5,0.5,1.5,25000);
  
  GetOneDPlotsMCVsMC(1250,"NJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","F/B:E",1,0,10,2,12,0.5,1.5,22000);

  GetOneDPlotsMCVsMC(1251,"NJetforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","F/B:E",1,0,12,0,12,0.5,1.5,22000);
  
  GetOneDPlotsMCVsMC(1350,"MHTPhiv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi(MHT)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5400);

  GetOneDPlotsMCVsMC(1358,"MHTPhiforLowNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi(MHT)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5400);
  
  GetOneDPlotsMCVsMC(1359,"MHTPhiforHighNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi(MHT)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5400);

  //  GetOneDPlotsMCVsMC(1450,"METPhiv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MET)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5500);

  //GetOneDPlotsMCVsMC(1550,"METv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MET","F/B:E",1,0,16,200,1000,0.5,1.5,10000);
  
  GetOneDPlotsMCVsMC(1650,"NBtagv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","F/B:E",1,0,5,0,5,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1658,"NBtagforLowNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","F/B:E",1,0,5,0,5,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1659,"NBtagforHighNJetv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","F/B:E",1,0,5,0,5,0.5,1.5,30000);
  

  GetOneDPlotsMCVsMC(1750,"DphiOneforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,9000);

  GetOneDPlotsMCVsMC(1850,"DphiTwoforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{2},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,2100);

  GetOneDPlotsMCVsMC(1950,"DphiThreeforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{3},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,1300);

  GetOneDPlotsMCVsMC(2050,"DphiFourforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.27,0.7,0.57,0.87,"#delta#phi(j_{4},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2150,"JetEtaforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2250,"JetPtforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2350,"JetPhiforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  
  GetOneDPlotsMCVsMC(1057,"MHTforTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","F/B:E",1,0,16,200,1000,0.5,1.5,15000);

  GetOneDPlotsMCVsMC(1157,"HTforTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HT","F/B:E",1,0,12,100,2500,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1357,"MHTPhiforTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi(MHT)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5400);

  GetOneDPlotsMCVsMC(11157,"HTRatioforTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HTRatio","F/B:E",1,0,20,0,5,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1257,"NJetforTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","F/B:E",1,0,10,2,12,0.5,1.5,22000);

  GetOneDPlotsMCVsMC(1057,"MHTforNotTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","F/B:E",1,0,16,200,1000,0.5,1.5,15000);

  GetOneDPlotsMCVsMC(1157,"HTforNotTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HT","F/B:E",1,0,12,100,2500,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1357,"MHTPhiforNotTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi(MHT)","F/B:E",0,0,7,-3.5,3.5,0.5,1.5,5400);

  GetOneDPlotsMCVsMC(11157,"HTRatioforNotTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"HTRatio","F/B:E",1,0,20,0,5,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1257,"NJetforNotTwoNbv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","F/B:E",1,0,10,2,12,0.5,1.5,22000);


  
  GetOneDPlotsMCVsMC(2157,"JetEtaforTwoNbforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2257,"JetPtforTwoNbforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2357,"JetPhiforTwoNbforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2157,"JetEtaforNotTwoNbforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2257,"JetPtforNotTwoNbforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2357,"JetPhiforNotTwoNbforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  
  GetOneDPlotsMCVsMC(2158,"JetEtaforLowNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforLowNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforLowNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);
  
  GetOneDPlotsMCVsMC(2158,"JetEtaforLowNJetfor0bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforLowNJetfor0bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforLowNJetfor0bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2158,"JetEtaforLowNJetfor1bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforLowNJetfor1bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforLowNJetfor1bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2158,"JetEtaforLowNJetfor2bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforLowNJetfor2bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforLowNJetfor2bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2158,"JetEtaforLowNJetfor3bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforLowNJetfor3bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforLowNJetfor3bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);
  
  
  GetOneDPlotsMCVsMC(2159,"JetEtaforHighNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2259,"JetPtforHighNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2359,"JetPhiforHighNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);
  
  GetOneDPlotsMCVsMC(2159,"JetEtaforHighNJetLeadforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2259,"JetPtforHighNJetLeadforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2359,"JetPhiforHighNJetLeadforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2159,"JetEtaforHighNJetNotLeadforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2259,"JetPtforHighNJetNotLeadforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2359,"JetPhiforHighNJetNotLeadforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);


  //  GetOneDPlotsMCVsMC(2259,"JetCSVforHighNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"CSV_{jet}","F/B:E",1,0,100,0.0,1.0,0.5,1.5,520);

  //  GetOneDPlotsMCVsMC(2650,"neutralEmEnergyFractionforLowNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuEmFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  //  GetOneDPlotsMCVsMC(2650,"neutralEmEnergyFractionforHighNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuEmFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  //  GetOneDPlotsMCVsMC(2650,"neutralEmEnergyFractionforLowPtforHighNJetforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuEmFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(3050,"photonMultiplicityforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"PhotonMultiplicity_{jet}","F/B:E",1,0,100,0.0,100.0,0.5,1.5,520);

  
  GetOneDPlotsMCVsMC(2158,"JetEtaforHighNJetfor0bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforHighNJetfor0bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforHighNJetfor0bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2158,"JetEtaforHighNJetfor1bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforHighNJetfor1bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforHighNJetfor1bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2158,"JetEtaforHighNJetfor2bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforHighNJetfor2bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforHighNJetfor2bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2158,"JetEtaforHighNJetfor3bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2258,"JetPtforHighNJetfor3bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2358,"JetPhiforHighNJetfor3bforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  
  GetOneDPlotsMCVsMC(2151,"JetEtaforHTv2RecipeLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2251,"JetPtforHTv2RecipeLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2351,"JetPhiforHTv2RecipeLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.27,0.2,0.57,0.37,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2152,"JetEtaforHTv2RecipeNotLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#eta_{jet}","F/B:E",0,0,50,-2.5,2.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2252,"JetPtforHTv2RecipeNotLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2352,"JetPhiforHTv2RecipeNotLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2450,"rawJetPtforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2550,"chargedEmEnergyFractionforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"ChaEmFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2650,"neutralEmEnergyFractionforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuEmFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2750,"chargedHadronEnergyFractionforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"ChaHadFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2850,"neutralHadronEnergyFractionforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuHadFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2950,"chargedHadronMultiplicityforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"ChaHadMultiplicity_{jet}","F/B:E",1,0,100,0.0,100.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(3050,"neutralHadronMultiplicityforHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuHadMultiplicity_{jet}","F/B:E",1,0,20,0.0,20.0,0.5,1.5,520);



  GetOneDPlotsMCVsMC(1750,"DphiOneforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,9000);

  GetOneDPlotsMCVsMC(1850,"DphiTwoforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{2},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,2100);

  GetOneDPlotsMCVsMC(1950,"DphiThreeforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{3},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,1300);

  GetOneDPlotsMCVsMC(2050,"DphiFourforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.27,0.7,0.57,0.87,"#delta#phi(j_{4},MHT)","F/B:E",0,0,32,0,3.2,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2150,"JetEtaforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,100,-5,5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2250,"JetPtforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2350,"JetPhiforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2151,"JetEtaforMHTminusHTv2RecipeLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,100,-5.,5.,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2251,"JetPtforMHTminusHTv2RecipeLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2351,"JetPhiforMHTminusHTv2RecipeLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2152,"JetEtaforMHTminusHTv2RecipeNotLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.37,0.3,0.67,0.47,"#eta_{jet}","F/B:E",0,0,100,-5.,5.,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2252,"JetPtforMHTminusHTv2RecipeNotLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2352,"JetPhiforMHTminusHTv2RecipeNotLead","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.2,0.87,0.37,"#phi_{jet}","F/B:E",0,0,70,-3.5,3.5,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2450,"rawJetPtforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"pT_{jet}","F/B:E",1,0,20,0.0,1000.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2550,"chargedEmEnergyFractionforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"CharEmFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2650,"neutralEmEnergyFractionforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuEmFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2750,"chargedHadronEnergyFractionforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"CharHadFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2850,"neutralHadronEnergyFractionforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuHadFraction_{jet}","F/B:E",1,0,20,0.0,1.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(2950,"chargedHadronMultiplicityforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"CharHadMultiplicity_{jet}","F/B:E",1,0,100,0.0,100.0,0.5,1.5,520);

  GetOneDPlotsMCVsMC(3050,"neutralHadronMultiplicityforMHTminusHTv2Recipe","Data0LHighDphi_BEVsF","Prediction_0_Data_MET_Oct02_bcdehadd_.root ","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"NeuHadMultiplicity_{jet}","F/B:E",1,0,20,0.0,20.0,0.5,1.5,520);

*/





  /* 

  GetOneDPlotsMCVsMC(1000,"MHT","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",1,0,16,200,1000,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1100,"HT","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"HT","Data17/Data16",1,0,12,100,2500,0.5,1.5,45000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","Data17/Data16",1,0,10,2,12,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(2100,"MHTPhi","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5600);

  GetOneDPlotsMCVsMC(2200,"METPhi","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.2,0.77,0.37,"#phi(MET)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5900);

  GetOneDPlotsMCVsMC(2300,"MET","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MET","Data17/Data16",1,0,16,200,1000,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","Data17/Data16",1,0,5,0,5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1400,"DphiOne","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1500,"DphiTwo","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,4200);

  GetOneDPlotsMCVsMC(1600,"DphiThree","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,2200);

  GetOneDPlotsMCVsMC(1700,"DphiFour","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root ","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,1200);

  //  GetOneDPlotsMCVsMC(1000,"MHT","Data0LHighDphi_BEVs16","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",1,0,16,200,1000,0.5,1.5,200000);

*/
  /*
  GetOneDPlotsMCVsMC(1010,"MHTOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",0,0,16,200,1000,0.5,1.5,30000);

  //  GetOneDPlotsMCVsMC(1110,"HTOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"HT","Data17/Data16",1,0,12,100,2500,0.5,1.5,45000);

  //  GetOneDPlotsMCVsMC(1210,"NJetOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","Data17/Data16",1,0,10,2,12,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(2110,"MHTPhiOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5600);

  GetOneDPlotsMCVsMC(2210,"METPhiOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.2,0.77,0.37,"#phi(MET)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5900);

  GetOneDPlotsMCVsMC(2310,"METOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MET","Data17/Data16",1,0,16,200,1000,0.5,1.5,20000);

  //  GetOneDPlotsMCVsMC(1310,"NBtagOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","Data17/Data16",1,0,5,0,5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1410,"DphiOneOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1510,"DphiTwoOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","Data17/Data16",0,0,32,0,3.2,0.5,1.5,4200);

  GetOneDPlotsMCVsMC(1610,"DphiThreeOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","Data17/Data16",0,0,32,0,3.2,0.5,1.5,2200);

  GetOneDPlotsMCVsMC(1710,"DphiFourOrig","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root ","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","Data17/Data16",0,0,32,0,3.2,0.5,1.5,1200);
*/
  /*
 
  GetOneDPlotsMCVsMC(1020,"MHTv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MHT","Data17/Data16",0,0,16,200,1000,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1120,"HTv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"HT","Data17/Data16",1,0,12,100,2500,0.5,1.5,45000);

  GetOneDPlotsMCVsMC(1220,"NJetv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NJet","Data17/Data16",1,0,10,2,12,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(2120,"MHTPhiv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5600);

  //GetOneDPlotsMCVsMC(2220,"METPhiv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.47,0.2,0.77,0.37,"#phi(MET)","Data17/Data16",0,0,7,-3.5,3.5,0.5,1.5,5900);

  //GetOneDPlotsMCVsMC(2320,"METv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"MET","Data17/Data16",1,0,16,200,1000,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1320,"NBtagv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","Data17/Data16",1,0,5,0,5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1420,"DphiOnev2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data17/Data16",1,0,32,0,3.2,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1520,"DphiTwov2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","Data17/Data16",0,0,32,0,3.2,0.5,1.5,4200);

  GetOneDPlotsMCVsMC(1620,"DphiThreev2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","Data17/Data16",0,0,32,0,3.2,0.5,1.5,2200);

  GetOneDPlotsMCVsMC(1720,"DphiFourv2Recipe","Data0LHighDphi_FVs16","Prediction_0_Data_MET_Oct02_fhadd_.root ","Prediction_0_Data_MET_0L_Oct03_V12_.root","0L Region",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","Data17/Data16",0,0,32,0,3.2,0.5,1.5,1200);
  
  */

  /*
  //v2Vsv1: F

  GetOneDPlotsMCVsMC(1020,"MHTv2Recipe","MHT","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"MHT","v2/v1",0,0,16,200,1000,0.5,1.5,30000);
  
  GetOneDPlotsMCVsMC(1120,"HTv2Recipe","HT","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"HT","v2/v1",1,0,12,100,2500,0.5,1.5,45000);

  GetOneDPlotsMCVsMC(1220,"NJetv2Recipe","NJet","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"NJet","v2/v1",1,0,10,2,12,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(2120,"MHTPhiv2Recipe","MHTPhi","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","v2/v1",0,0,7,-3.5,3.5,0.5,1.5,5600);

  //GetOneDPlotsMCVsMC(2220,"METPhiv2Recipe","METPhi","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.47,0.2,0.77,0.37,"#phi(MET)","v2/v1",0,0,7,-3.5,3.5,0.5,1.5,5900);

  //GetOneDPlotsMCVsMC(2320,"METv2Recipe","MET","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"MET","v2/v1",1,0,16,200,1000,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1320,"NBtagv2Recipe","NBtag","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","v2/v1",1,0,5,0,5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1420,"DphiOnev2Recipe","DphiOne","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","v2/v1",1,0,32,0,3.2,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1520,"DphiTwov2Recipe","DphiTwo","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{2},MHT)","v2/v1",0,0,32,0,3.2,0.5,1.5,4200);

  GetOneDPlotsMCVsMC(1620,"DphiThreev2Recipe","DphiThree","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{3},MHT)","v2/v1",0,0,32,0,3.2,0.5,1.5,2200);

  GetOneDPlotsMCVsMC(1720,"DphiFourv2Recipe","DphiFour","Data0LHighDphi_v2Vsv1_f","Prediction_0_Data_MET_Oct16f_V15f_v2Baseline.root ","Prediction_0_Data_MET_Oct16f_V15f_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{4},MHT)","v2/v1",0,0,32,0,3.2,0.5,1.5,1200);
*/

  //*AR: 1L reg Data 2017 V15 vs V16
  /*
  GetOneDPlotsMCVsMC(1020,"MHTv2Recipe","Data1LHighDphi_v16Vsv15","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TFAndV15Ntuples.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L Region",0.57,0.7,0.87,0.87,"MHT","v16/v15",0,0,16,200,1000,0.5,1.5,30000);
  
  GetOneDPlotsMCVsMC(1120,"HTv2Recipe","Data1LHighDphi_v16Vsv15","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TFAndV15Ntuples.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L Region",0.57,0.7,0.87,0.87,"HT","v16/v15",1,0,12,100,2500,0.5,1.5,45000);

  GetOneDPlotsMCVsMC(1220,"NJetv2Recipe","Data1LHighDphi_v16Vsv15","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TFAndV15Ntuples.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L Region",0.57,0.7,0.87,0.87,"NJet","v16/v15",1,0,10,2,12,0.5,1.5,25000);
  

  GetOneDPlotsMCVsMC(1320,"NBtagv2Recipe","Data1LHighDphi_v16Vsv15","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TFAndV15Ntuples.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L Region",0.57,0.7,0.87,0.87,"NBtag","v16/v15",1,0,5,0,5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1320,"LepEta","Data1LHighDphi_v16Vsv15","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TFAndV15Ntuples.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L Region",0.57,0.7,0.87,0.87,"#eta","v16/v15",0,0,10,-2.5,2.5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1320,"LepPhi","Data1LHighDphi_v16Vsv15","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TFAndV15Ntuples.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L Region",0.57,0.7,0.87,0.87,"#phi","v16/v15",0,0,7,-3.5,3.5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1320,"LepPt","Data1LHighDphi_v16Vsv15","Prediction_0_Data_MET_Nov20bcdef_2017PredwithV12TFAndV15Ntuples.root","Prediction_0_haddData_MET_BeforePrefire_NoBtagProb_1L.root","1L Region",0.57,0.7,0.87,0.87,"pT","v16/v15",1,0,20,0,1000,0.5,1.5,50500);

  */


  //*AR: 1L reg MC2017(V16) vs MC2016(V12)
  /*  
  GetOneDPlotsMCVsMC(1020,"MHTv2Recipe","MC_RemovedExcess_1LHighDphi_v16for2017Vsv12for2016","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","1L Region",0.57,0.7,0.87,0.87,"MHT","v16/v12",0,0,16,200,1000,0.5,1.5,30000);
  
  GetOneDPlotsMCVsMC(1120,"HTv2Recipe","MC_RemovedExcess_1LHighDphi_v16for2017Vsv12for2016","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","1L Region",0.57,0.7,0.87,0.87,"HT","v16/v12",1,0,12,100,2500,0.5,1.5,45000);

  GetOneDPlotsMCVsMC(1220,"NJetv2Recipe","MC_RemovedExcess_1LHighDphi_v16for2017Vsv12for2016","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","1L Region",0.57,0.7,0.87,0.87,"NJet","v16/v12",1,0,10,2,12,0.5,1.5,25000);
  

  GetOneDPlotsMCVsMC(1320,"NBtagv2Recipe","MC_RemovedExcess_1LHighDphi_v16for2017Vsv12for2016","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","1L Region",0.57,0.7,0.87,0.87,"NBtag","v16/v12",1,0,5,0,5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1320,"LepEta","MC_RemovedExcess_1LHighDphi_v16for2017Vsv12for2016","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","1L Region",0.57,0.7,0.87,0.87,"#eta","v16/v12",0,0,10,-2.5,2.5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1320,"LepPhi","MC_RemovedExcess_1LHighDphi_v16for2017Vsv12for2016","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","1L Region",0.57,0.7,0.87,0.87,"#phi","v16/v12",0,0,7,-3.5,3.5,0.5,1.5,50500);

  GetOneDPlotsMCVsMC(1320,"LepPt","MC_RemovedExcess_1LHighDphi_v16for2017Vsv12for2016","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","1L Region",0.57,0.7,0.87,0.87,"pT","v16/v12",1,0,20,0,1000,0.5,1.5,50500);

  */



  
  GetOneDPlotsMCVsMC(2320,"MHTv2Recipe","MHT","LLPlusHadtau_2018","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","LL+Had#tau",0.57,0.7,0.87,0.87,"MHT","Pred/Exp",1,0,16,200,1000,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(2320,"HTv2Recipe","HT","LLPlusHadtau_2018","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","LL+Had#tau",0.57,0.7,0.87,0.87,"HT","Pred/Exp",1,0,12,100,2500,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(2320,"NJetv2Recipe","NJet","LLPlusHadtau_2018","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NJet","Pred/Exp",1,0,10,2,12,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(2320,"NBtagv2Recipe","NBtag","LLPlusHadtau_2018","Prediction_0_Data_MET_Oct02_bcdehadd_.root","Prediction_0_Data_MET_Oct02_fhadd_.root","LL+Had#tau",0.57,0.7,0.87,0.87,"NBtag","Pred/Exp",1,0,5,0,5,0.5,1.5,20000);









  //v2Vsv1: B:E


  

  //  GetOneDPlotsMCVsMC(1020,"MHTv2Recipe","MHT","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"MHT","v2/v1",0,0,16,200,1000,0.5,1.5,30000);
  
  //  GetOneDPlotsMCVsMC(1120,"HTv2Recipe","HT","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"HT","v2/v1",1,0,12,100,2500,0.5,1.5,45000);

  //  GetOneDPlotsMCVsMC(1220,"NJetv2Recipe","NJet","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"NJet","v2/v1",1,0,10,2,12,0.5,1.5,25000);

  //GetOneDPlotsMCVsMC(2120,"MHTPhiv2Recipe","MHTPhi","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.47,0.3,0.77,0.47,"#phi(MHT)","v2/v1",0,0,7,-3.5,3.5,0.5,1.5,5600);

  //GetOneDPlotsMCVsMC(2220,"METPhiv2Recipe","METPhi","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.47,0.2,0.77,0.37,"#phi(MET)","v2/v1",0,0,7,-3.5,3.5,0.5,1.5,5900);

  //GetOneDPlotsMCVsMC(2320,"METv2Recipe","MET","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"MET","v2/v1",1,0,16,200,1000,0.5,1.5,20000);

  //  GetOneDPlotsMCVsMC(1320,"NBtagv2Recipe","NBtag","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.57,0.7,0.87,0.87,"NBtag","v2/v1",1,0,5,0,5,0.5,1.5,50500);
  /*
  GetOneDPlotsMCVsMC(1420,"DphiOnev2Recipe","DphiOne","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","v2/v1",1,0,32,0,3.2,0.5,1.5,20000);

  GetOneDPlotsMCVsMC(1520,"DphiTwov2Recipe","DphiTwo","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{2},MHT)","v2/v1",0,0,32,0,3.2,0.5,1.5,4200);

  GetOneDPlotsMCVsMC(1620,"DphiThreev2Recipe","DphiThree","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{3},MHT)","v2/v1",0,0,32,0,3.2,0.5,1.5,2200);

  GetOneDPlotsMCVsMC(1720,"DphiFourv2Recipe","DphiFour","Data0LHighDphi_v2Vsv1_be","Prediction_0_Data_MET_Oct16be_V15bcde_v2Baseline.root ","Prediction_0_Data_MET_Oct16be_V15bcde_DefaultBaseline.root","0L Region",0.37,0.7,0.67,0.87,"#delta#phi(j_{4},MHT)","v2/v1",0,0,32,0,3.2,0.5,1.5,1200);
*/
}
