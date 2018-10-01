#include <TH1D.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TList.h>
#include <TStyle.h>
#include <vector>
#include <cstdio>



void GetSearchBinPlotMCVsMC(int hNum,char const * Var,char const * Sample,char const * TTbarLL, char const * TTbarHadtau,char const * LegHeader,double Legxmin,double Legymin,double Legxmax,double Legymax,char const *xRatioLabel,char const *yRatioLabel,bool logy, bool logx,int RatioNbins,double RatioXmin,double RatioXmax,double RatioYmin,double RatioYmax,double topMin,double topMax){
  
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



  // Canvas size

  int W = 1200;
  int H = 740;
  int H_ref = 740;
  int W_ref = 800;

  float T = 0.08*H_ref;
  float B = 0.12*H_ref;
  float L = 0.12*W_ref;
  float R = 0.08*W_ref;

  //
  // Various vertical line coordinates
  float ymax_top = 100000.;
  float ymin_top = 0.11;
  //float ymin_top = 0.002;

  float ymax2_top = 1000.;
  float ymax3_top = 200.;
  float ymax4_top = 30.;

  float ymax_bottom = 2.65;
  float ymin_bottom = 0.;

  float ymax2_bottom = 2.15;
  float ymax3_bottom = 2.15;
  float ymax4_bottom = 2.15;


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
  //  int col1 = kRed;
  //  int col2 = kBlack;
  int i=0;
  
  int GetRatioNbins=RatioNbins;
  double GetRatioXmin=RatioXmin;
  double GetRatioXmax=RatioXmax;
  double ymax=topMax;
  double ymin=topMin;
  char hname[500], htit[500];
  char tempWJet[500];
  char tempTTbar[500];
  char LabelX[500];
  char LabelY[500];
  char RatioLabelX[500];
  char RatioLabelY[500];
  char cname[500];
  char header[500];
  sprintf(header,"%s",LegHeader);
  sprintf(hname,"h_%s",Var);
  sprintf(RatioLabelX,"%s",xRatioLabel);
  sprintf(RatioLabelY,"%s",yRatioLabel);
  sprintf(cname,"h_%s_%s",Var,Sample);

  TFile *_fileTTbarLL = TFile::Open(TTbarLL); 

  TFile *_fileTTbarHadtau = TFile::Open(TTbarHadtau); 

  //  TFile *_fileData = TFile::Open(DataPred);

  _fileTTbarLL->cd();
  TH1D *hTTbarLL = (TH1D*)_fileTTbarLL->FindObjectAny(hname);
  hTTbarLL->Scale(35900.0/41486.0);
  hTTbarLL->SetLineColor(kRed);
  hTTbarLL->SetLineWidth(2);
  hTTbarLL->SetMarkerStyle(22);
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
  TH1D *hTTbarHadtau = (TH1D*)_fileTTbarHadtau->FindObjectAny(hname);
  //  hTTbarHadtau->Scale(35900);

  //  hTTbarHadtau->SetFillStyle(3144);
  hTTbarHadtau->SetLineColor(kBlue);
  hTTbarHadtau->SetLineWidth(2);
  hTTbarHadtau->SetMarkerStyle(24);
  hTTbarHadtau->SetMarkerColor(kBlue);

  /*
  hTTbarHadtau->SetLineColor(kBlue);
  hTTbarHadtau->SetMarkerStyle(21);
  hTTbarHadtau->SetMarkerSize(0.0001);
*/
  ////  TH1D *hTTbarLLHadtau=(TH1D *) hTTbarLL->Clone("hTTbarLLHadtau");
  //  hTTbarLLHadtau->Add(hTTbarHadtau);

  if(logy)
    canvas_up->SetLogy();
  
  if(logx)
    canvas_up->SetLogx();
  hTTbarLL->SetMaximum(ymax);
  hTTbarLL->SetMinimum(ymin);
  hTTbarLL->Draw("e");
  hTTbarHadtau->Draw("e same");
  //  hTTbarHadtau->GetYaxis()->SetRangeUser(0,ymax);
  
  //  TLegend *tl=new TLegend(0.57,0.7,0.87,0.87);
  //  TLegend *tl=new TLegend(0.77,0.78,0.89,0.89); 
  TLegend *tl=new TLegend(Legxmin,Legymin,Legxmax,Legymax);

  tl->SetTextSize(0.032);
  tl->SetTextFont(42);

  tl->SetTextSize(0.035);
  tl->SetTextFont(42);
  tl->SetFillColor(0);
  tl->SetLineColor(0);
  tl->SetBorderSize(0);

  tl->SetHeader(header);
  tl->AddEntry(hTTbarHadtau, "Data_16");
  tl->AddEntry(hTTbarLL, "Data_17"); 
  tl->SetLineColor(kWhite);
  tl->Draw("same");
  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  //ttext->DrawLatex(GetRatioXmin , 1.1*ymax , "#bf{CMS} #it{Preliminary}");
  ttext->DrawLatex(xmin , 1*ymax , "#bf{CMS} #it{Preliminary}");
  
  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  //  ttexlumi->DrawLatex(GetRatioXmax-10*binSize, ymaximum , "35.9fb^{-1} (13TeV)");
  ttexlumi->DrawLatex(xmin+0.65*diff, 1*ymax , "35.9fb^{-1} (13TeV)");
  
  //-----------------------------------------------------------
  // Putting lines and labels explaining search region definitions
  //-----------------------------------------------------------
  
  // Njet separation lines
  
  TLine *tl_njet = new TLine();
  tl_njet->SetLineStyle(2);
  tl_njet->DrawLine(31.-0.5,ymin_top,31.-0.5,ymax); 
  tl_njet->DrawLine(71.-0.5,ymin_top,71.-0.5,ymax);
  tl_njet->DrawLine(111.-0.5,ymin_top,111.-0.5,ymax);
  tl_njet->DrawLine(143.-0.5,ymin_top,143.-0.5,ymax);
  tl_njet->DrawLine(175.-0.5,ymin_top,175.-0.5,ymax);
  // Njet labels
  TLatex * ttext_njet = new TLatex();
  ttext_njet->SetTextFont(42);
  //ttext_njet->SetTextSize(0.060);
  ttext_njet->SetTextSize(0.040);
  ttext_njet->SetTextAlign(22);
    
  ttext_njet->DrawLatex(16.-0.5 , ymax/4. , "N_{#scale[0.2]{ }jet} = 2");
  ttext_njet->DrawLatex(51.-0.5 , ymax/4. , "3 #leq N_{#scale[0.2]{ }jet} #leq 4");
  ttext_njet->DrawLatex(91.-0.5 , ymax/4. , "5 #leq N_{#scale[0.2]{ }jet} #leq 6");
  ttext_njet->DrawLatex(127.-0.5 , ymax/4. , "7 #leq N_{#scale[0.2]{ }jet} #leq 8");
  ttext_njet->DrawLatex(159.-0.5 , ymax/4. , "N_{#scale[0.2]{ }jet} #geq 9");
  // Nb separation lines
  TLine *tl_nb = new TLine();
  tl_nb->SetLineStyle(3);
  tl_nb->DrawLine(11.-0.5,ymin_top,11.-0.5,ymax/24); 
  tl_nb->DrawLine(21.-0.5,ymin_top,21.-0.5,ymax/24); 
  tl_nb->DrawLine(41.-0.5,ymin_top,41.-0.5,ymax/24); 
  tl_nb->DrawLine(51.-0.5,ymin_top,51.-0.5,ymax/24); 
  tl_nb->DrawLine(61.-0.5,ymin_top,61.-0.5,ymax/24); 
  tl_nb->DrawLine(81.-0.5,ymin_top,81.-0.5,ymax/24); 
  tl_nb->DrawLine(91.-0.5,ymin_top,91.-0.5,ymax/24); 
  tl_nb->DrawLine(101.-0.5,ymin_top,101.-0.5,ymax/24); 
  tl_nb->DrawLine(119.-0.5,ymin_top,119.-0.5,ymax/24); 
  tl_nb->DrawLine(127.-0.5,ymin_top,127.-0.5,ymax/24);
  tl_nb->DrawLine(135.-0.5,ymin_top,135.-0.5,ymax/24);
  tl_nb->DrawLine(151.-0.5,ymin_top,151.-0.5,ymax/24);
  tl_nb->DrawLine(159.-0.5,ymin_top,159.-0.5,ymax/24);
  tl_nb->DrawLine(167.-0.5,ymin_top,167.-0.5,ymax/24);
  // Nb labels
  TLatex * ttext_nb = new TLatex();
  ttext_nb->SetTextFont(42);
  //ttext_nb->SetTextSize(0.060);
  ttext_nb->SetTextSize(0.040);
  ttext_nb->SetTextAlign(22);
    
  ttext_nb->DrawLatex( 8.-0.5 , ymax/12. , "N_{#scale[0.2]{ }b-jet}");
    
  ttext_nb->DrawLatex( 6.-0.5 , ymax/20. , "0");
  ttext_nb->DrawLatex(16.-0.5 , ymax/20. , "1");
  ttext_nb->DrawLatex(26.-0.5 , ymax/20. , "2");
    
  ttext_nb->DrawLatex(36.-0.5 , ymax/20. , "0");
  ttext_nb->DrawLatex(46.-0.5 , ymax/20. , "1");
  ttext_nb->DrawLatex(56.-0.5 , ymax/20. , "2");
  ttext_nb->DrawLatex(66.-0.5 , ymax/20. , "#geq 3");

  ttext_nb->DrawLatex(76.-0.5 , ymax/20. , "0");
  ttext_nb->DrawLatex(86.-0.5 , ymax/20. , "1");
  ttext_nb->DrawLatex(96.-0.5 , ymax/20. , "2");
  ttext_nb->DrawLatex(106.-0.5 , ymax/20. , "#geq 3");

  ttext_nb->DrawLatex(115.-0.5 , ymax/20. , "0");
  ttext_nb->DrawLatex(123.-0.5 , ymax/20. , "1");
  ttext_nb->DrawLatex(131.-0.5 , ymax/20. , "2");
  ttext_nb->DrawLatex(139.-0.5 , ymax/20. , "#geq 3");

  ttext_nb->DrawLatex(147.-0.5 , ymax/20. , "0");
  ttext_nb->DrawLatex(155.-0.5 , ymax/20. , "1");
  ttext_nb->DrawLatex(163.-0.5 , ymax/20. , "2");
  ttext_nb->DrawLatex(171.-0.5 , ymax/20. , "#geq 3");

  
  gPad->Modified();
  
  TH1D * cOne = new TH1D("Ratio","ratio plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram
  TH1D * cTwo = new TH1D("RatioTwo","ratioTwo plot",GetRatioNbins,GetRatioXmin,GetRatioXmax); //For SF and TF histogram


  cOne=(TH1D *) hTTbarHadtau->Clone("Ratio");
  cTwo=(TH1D *) hTTbarLL->Clone("RatioTwo");

  TH1D * cTwoNoErr= (TH1D *)cTwo->Clone("cTwoNoErr");
  for (int ibin=0; ibin<cTwoNoErr->GetNbinsX()+2; ibin++){
    cTwoNoErr->SetBinError(ibin,0.);
  }
 
  cOne->Divide(hTTbarHadtau,cTwoNoErr,1,1,"");
  cTwo->Divide(hTTbarLL,cTwoNoErr,1,1,"");

  gStyle->SetPadBottomMargin(0.3);
  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(RatioLabelX);
  cOne->GetYaxis()->SetTitle(RatioLabelY);
  canvas_dw->cd();
  cOne->Draw("e");
  cTwo->Draw("e same");
  
  // Njet separation lines
  TLine *tlBottom_njet = new TLine();
  tlBottom_njet->SetLineStyle(2);

    
  tlBottom_njet->DrawLine(31.-0.5,RatioYmin,31.-0.5,RatioYmax);
  tlBottom_njet->DrawLine(71.-0.5,RatioYmin,71.-0.5,RatioYmax);
  tlBottom_njet->DrawLine(111.-0.5,RatioYmin,111.-0.5,RatioYmax);
  tlBottom_njet->DrawLine(143.-0.5,RatioYmin,143.-0.5,RatioYmax);
  tlBottom_njet->DrawLine(175.-0.5,RatioYmin,175.-0.5,RatioYmax);

  // Nb separation lines
  TLine *tlBottom_nb = new TLine();
  tlBottom_nb->SetLineStyle(3);
  tlBottom_nb->DrawLine(11.-0.5,RatioYmin,11.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(21.-0.5,RatioYmin,21.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(31.-0.5,RatioYmin,31.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(51.-0.5,RatioYmin,51.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(61.-0.5,RatioYmin,61.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(81.-0.5,RatioYmin,81.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(91.-0.5,RatioYmin,91.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(101.-0.5,RatioYmin,101.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(119.-0.5,RatioYmin,119.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(127.-0.5,RatioYmin,127.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(135.-0.5,RatioYmin,135.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(151.-0.5,RatioYmin,151.-0.5,RatioYmax); 
  tlBottom_nb->DrawLine(159.-0.5,RatioYmin,159.-0.5,RatioYmax);
  tlBottom_nb->DrawLine(167.-0.5,RatioYmin,167.-0.5,RatioYmax); 



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


void GetSearchBinPlotMCVsMC(){

  //GetSearchBinPlotMCVsMC(5000,"CSStat","DataCSStat","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","1L CR Stat",0.58,0.55,0.90,0.65,"Search Bins","Data16/Data17",1,0,174,0,174,0,1.9,0.01,10000000);

  GetSearchBinPlotMCVsMC(5100,"CSStat","DataCSStat_LowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","1L CR Stat",0.58,0.55,0.90,0.65,"Search Bins","Data16/Data17",1,0,174,0,174,0,1.9,0.01,10000000);

  //  GetSearchBinPlotMCVsMC(5100,"Prediction","Prediction_HighDphi","Prediction_0_Data_MET_LLPlusHadTau_binSFCorrected_withCSHist_Sep21_V15_00.root","Prediction_0_Data_MET_LLPlusHadTau_binSFCorrected_withCSHist.root","LLPlusHadtau",0.58,0.55,0.90,0.65,"Search Bins","Data16/Data17",1,0,174,0,174,0,1.9,0.01,10000000);

  /*
  GetOneDPlotsMCVsMC(1000,"MHT","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","Data16/Data17",1,0,16,200,1000,0.5,1.5,80000);

  GetOneDPlotsMCVsMC(1100,"HT","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","Data16/Data17",1,0,12,100,2500,0.5,1.5,50000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NJet","Data16/Data17",1,0,10,2,12,0.5,1.5,40000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,100000);

  GetOneDPlotsMCVsMC(1310,"NBtag","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,60000);

  GetOneDPlotsMCVsMC(1320,"NBtag","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,50000);

  GetOneDPlotsMCVsMC(1400,"DphiOne","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,50000);

  GetOneDPlotsMCVsMC(1410,"DphiOne","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1420,"DphiOne","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.37,0.7,0.67,0.87,"#delta#phi(j_{1},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1500,"DphiTwo","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{2},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,25000);
  */
  //  GetOneDPlotsMCVsMC(1600,"DphiThree","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{3},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,15000);
  /*
  GetOneDPlotsMCVsMC(1700,"DphiFour","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"#delta#phi(j_{4},MHT)","Data16/Data17",1,0,32,0,3.2,0.5,1.5,6000);

  GetOneDPlotsMCVsMC(1800,"LepPt","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,50000);
  
  GetOneDPlotsMCVsMC(1810,"LepPt","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1820,"LepPt","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.57,0.7,0.87,0.87,"Lep_pT","Data16/Data17",1,0,20,0,1000,0.5,1.5,25000);

  GetOneDPlotsMCVsMC(1900,"LepEta","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,13000);
  */
  //  GetOneDPlotsMCVsMC(1910,"LepEta","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,7200);

  //  GetOneDPlotsMCVsMC(1920,"LepEta","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#eta","Data16/Data17",0,0,10,-2.5,2.5,0.5,1.5,6200);

  //GetOneDPlotsMCVsMC(2000,"LepPhi","Data1LLowDphi","Prediction_0_Data_MET_Sep19LowDphi_V15_.root","Prediction_0_Data_MET_Sep19LowDphi_V12_.root","e+#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,12800);

  //GetOneDPlotsMCVsMC(2010,"LepPhi","Data1LLowDphiMu","Prediction_0_Data_MET_Sep20LowDphiMu_V15_.root","Prediction_0_Data_MET_Sep20LowDphiMu_V12_.root","#mu CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,7000);

  //GetOneDPlotsMCVsMC(2020,"LepPhi","Data1LLowDphiEle","Prediction_0_Data_MET_Sep20LowDphiEle_V15_.root","Prediction_0_Data_MET_Sep20LowDphiEle_V12_.root","e CS",0.47,0.3,0.77,0.47,"Lep_#phi","Data16/Data17",0,0,7,-3.5,3.5,0.5,1.5,5800);







  /*


  
  
  GetOneDPlotsMCVsMC(1000,"MHT","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","Data16/Data17",1,0,16,200,1000,0.5,1.5,60000);

  GetOneDPlotsMCVsMC(1100,"HT","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"MHT","Data16/Data17",1,0,12,100,2500,0.5,1.5,60000);

  GetOneDPlotsMCVsMC(1200,"NJet","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NJet","Data16/Data17",1,0,10,2,12,0.5,1.5,30000);

  GetOneDPlotsMCVsMC(1300,"NBtag","Data1LHighDphi","Prediction_0_Data_MET_Sep18_V15_.root","Prediction_0_Data_MET_Sep18_V12_.root","e+#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,80000);


  GetOneDPlotsMCVsMC(1310,"NBtag","Data1LHighDphiMu","Prediction_0_Data_MET_Sep18Mu_V15_.root","Prediction_0_Data_MET_Sep19Mu_V12_.root","#mu CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,40000);

  GetOneDPlotsMCVsMC(1320,"NBtag","Data1LHighDphiEle","Prediction_0_Data_MET_Sep18Ele_V15_.root","Prediction_0_Data_MET_Sep19Ele_V12_.root","e CS",0.57,0.7,0.87,0.87,"NBtag","Data16/Data17",1,0,5,0,5,0.5,1.5,32000);

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

*/



}
