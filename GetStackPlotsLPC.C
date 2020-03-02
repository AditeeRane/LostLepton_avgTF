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
void GetStackPlotsLPC(int hNum){
  
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


  Float_t TTbarCutFlow[] = {181.137e6,3.9e6,1.64e6,656832,644241,407296,405392};
  Float_t WJetCutFlow[] = {91.42e6,4.11e6,1.96e6,889783,874816,601422,599942};
  Float_t STCutFlow[] = {129.49e6,259503,114618,61312,59986,36685,36468};
  Float_t ZJetCutFlow[] = {60e6,3.3e6,3.28e6,2.49e6,2.48e6,2.43e6,2.42e6};
  Float_t QCDCutFlow[] = {252.25e6,340741,337181,7600,5802,5396,5389};
  TH1::SetDefaultSumw2();

  TH1D * hSurvive=new TH1D("hSurvive","hSurvive",5,1,6);
  TH1D * hRejNoBin=new TH1D("hRejNoBin","hRejNoBin",5,1,6);

  TH1D * hRejIsotrk=new TH1D("hRejIsotrk","hRejIsotrk",5,1,6);
  TH1D * hRejMETfilters=new TH1D("hRejMETfilters","hRejMETfilters",5,1,6);
  TH1D * hRejDphiCut=new TH1D("hRejDphiCut","hRejDphiCut",5,1,6);
  TH1D * hRejLepton=new TH1D("hRejLepton","hRejLepton",5,1,6);
  TH1D * hRejHTMHTNjetBaseline=new TH1D("hRejHTMHTNjetBaseline","hRejHTMHTNjetBaseline",5,1,6);

  double fracTTbar=TTbarCutFlow[6]/TTbarCutFlow[0];
  double fracWJet=WJetCutFlow[6]/WJetCutFlow[0];
  double fracST=STCutFlow[6]/STCutFlow[0];
  double fracZJet=ZJetCutFlow[6]/ZJetCutFlow[0];
  double fracQCD=QCDCutFlow[6]/QCDCutFlow[0];


  hSurvive->Fill(1,100*fracTTbar);
  hSurvive->Fill(2,100*fracWJet);
  hSurvive->Fill(3,100*fracST);
  hSurvive->Fill(4,100*fracZJet);
  hSurvive->Fill(5,100*fracQCD);

  fracTTbar=(TTbarCutFlow[5]-TTbarCutFlow[6])/TTbarCutFlow[0];
  fracWJet=(WJetCutFlow[5] - WJetCutFlow[6])/WJetCutFlow[0];
  fracST=(STCutFlow[5] - STCutFlow[6])/STCutFlow[0];
  fracZJet=(ZJetCutFlow[5] - ZJetCutFlow[6])/ZJetCutFlow[0];
  fracQCD=(QCDCutFlow[5] - QCDCutFlow[6])/QCDCutFlow[0];

  hRejNoBin->Fill(1,100*fracTTbar);
  hRejNoBin->Fill(2,100*fracWJet);
  hRejNoBin->Fill(3,100*fracST);
  hRejNoBin->Fill(4,100*fracZJet);
  hRejNoBin->Fill(5,100*fracQCD);

  fracTTbar=(TTbarCutFlow[4]-TTbarCutFlow[5])/TTbarCutFlow[0];
  fracWJet=(WJetCutFlow[4] - WJetCutFlow[5])/WJetCutFlow[0];
  fracST=(STCutFlow[4] - STCutFlow[5])/STCutFlow[0];
  fracZJet=(ZJetCutFlow[4] - ZJetCutFlow[5])/ZJetCutFlow[0];
  fracQCD=(QCDCutFlow[4] - QCDCutFlow[5])/QCDCutFlow[0];

  hRejIsotrk->Fill(1,100*fracTTbar);
  hRejIsotrk->Fill(2,100*fracWJet);
  hRejIsotrk->Fill(3,100*fracST);
  hRejIsotrk->Fill(4,100*fracZJet);
  hRejIsotrk->Fill(5,100*fracQCD);

  fracTTbar=(TTbarCutFlow[3]-TTbarCutFlow[4])/TTbarCutFlow[0];
  fracWJet=(WJetCutFlow[3] - WJetCutFlow[4])/WJetCutFlow[0];
  fracST=(STCutFlow[3] - STCutFlow[4])/STCutFlow[0];
  fracZJet=(ZJetCutFlow[3] - ZJetCutFlow[4])/ZJetCutFlow[0];
  fracQCD=(QCDCutFlow[3] - QCDCutFlow[4])/QCDCutFlow[0];

  hRejMETfilters->Fill(1,100*fracTTbar);
  hRejMETfilters->Fill(2,100*fracWJet);
  hRejMETfilters->Fill(3,100*fracST);
  hRejMETfilters->Fill(4,100*fracZJet);
  hRejMETfilters->Fill(5,100*fracQCD);

  fracTTbar=(TTbarCutFlow[2]-TTbarCutFlow[3])/TTbarCutFlow[0];
  fracWJet=(WJetCutFlow[2] - WJetCutFlow[3])/WJetCutFlow[0];
  fracST=(STCutFlow[2] - STCutFlow[3])/STCutFlow[0];
  fracZJet=(ZJetCutFlow[2] - ZJetCutFlow[3])/ZJetCutFlow[0];
  fracQCD=(QCDCutFlow[2] - QCDCutFlow[3])/QCDCutFlow[0];

  hRejDphiCut->Fill(1,100*fracTTbar);
  hRejDphiCut->Fill(2,100*fracWJet);
  hRejDphiCut->Fill(3,100*fracST);
  hRejDphiCut->Fill(4,100*fracZJet);
  hRejDphiCut->Fill(5,100*fracQCD);

  fracTTbar=(TTbarCutFlow[1]-TTbarCutFlow[2])/TTbarCutFlow[0];
  fracWJet=(WJetCutFlow[1] - WJetCutFlow[2])/WJetCutFlow[0];
  fracST=(STCutFlow[1] - STCutFlow[2])/STCutFlow[0];
  fracZJet=(ZJetCutFlow[1] - ZJetCutFlow[2])/ZJetCutFlow[0];
  fracQCD=(QCDCutFlow[1] - QCDCutFlow[2])/QCDCutFlow[0];


  hRejLepton->Fill(1,100*fracTTbar);
  hRejLepton->Fill(2,100*fracWJet);
  hRejLepton->Fill(3,100*fracST);
  hRejLepton->Fill(4,100*fracZJet);
  hRejLepton->Fill(5,100*fracQCD);

  fracTTbar=(TTbarCutFlow[0]-TTbarCutFlow[1])/TTbarCutFlow[0];
  fracWJet=(WJetCutFlow[0] - WJetCutFlow[1])/WJetCutFlow[0];
  fracST=(STCutFlow[0] - STCutFlow[1])/STCutFlow[0];
  fracZJet=(ZJetCutFlow[0] - ZJetCutFlow[1])/ZJetCutFlow[0];
  fracQCD=(QCDCutFlow[0] - QCDCutFlow[1])/QCDCutFlow[0];

  hRejHTMHTNjetBaseline->Fill(1,100*fracTTbar);
  hRejHTMHTNjetBaseline->Fill(2,100*fracWJet);
  hRejHTMHTNjetBaseline->Fill(3,100*fracST);
  hRejHTMHTNjetBaseline->Fill(4,100*fracZJet);
  hRejHTMHTNjetBaseline->Fill(5,100*fracQCD);

  gStyle->SetTitleFontSize(0.15);
  gStyle->SetTitle(0);
  //  Int_t nvals = 3;

  gStyle->SetHatchesLineWidth(2.0);
  //  hSurvive->SetLineColor(3);
  hSurvive->SetFillColor(2);

  hRejNoBin->SetFillColor(28);
  //  hRejNoBin->SetFillStyle(3008);

  //  hSurvive->SetFillStyle(3144);

  //  hRejIsotrk->SetLineColor(7);
  //  hRejIsotrk->SetLineWidth(2); 
  hRejIsotrk->SetFillColor(6);
  //  hRejIsotrk->SetFillStyle(3008);

  //  hRejMETfilters->SetLineColor(28);
  hRejMETfilters->SetFillColor(3);
  //  hRejMETfilters->SetFillStyle(3008);

  //  hRejDphiCut->SetLineColor(6);
  hRejDphiCut->SetFillColor(4);
  //  hRejDphiCut->SetFillStyle(3008);

  //  hRejLepton->SetLineColor(2);
  hRejLepton->SetFillColor(7);
  //  hRejLepton->SetFillStyle(3008);

  //  hRejHTMHTNjetBaseline->SetLineColor(4);
  hRejHTMHTNjetBaseline->SetFillColor(5);
  //  hRejHTMHTNjetBaseline->SetFillStyle(3008);
  hRejNoBin->GetXaxis()->SetBinLabel(1,"t#bar{t}");
  hRejNoBin->GetXaxis()->SetBinLabel(2,"W + jets");
  hRejNoBin->GetXaxis()->SetBinLabel(3,"Single top");
  hRejNoBin->GetXaxis()->SetBinLabel(4,"Z + jets");
  hRejNoBin->GetXaxis()->SetBinLabel(5,"QCD");

  hRejNoBin->GetXaxis()->SetTitleOffset(0.98);
  hRejNoBin->GetXaxis()->SetTitleSize(0.15);
  hRejNoBin->GetXaxis()->SetTitleFont(42);
  hRejNoBin->GetXaxis()->SetLabelOffset(0.008);

  THStack * hExp = new THStack("hExp","hExp");
  hExp->Add(hRejNoBin);
  hExp->Add(hRejMETfilters);
  hExp->Add(hRejIsotrk);
  hExp->Add(hRejLepton);
  hExp->Add(hRejDphiCut);
  hExp->Add(hRejHTMHTNjetBaseline);

  THStack * hSur = new THStack("hSur","hSur");
  hSur->Add(hSurvive);




  // Define canvas
  //




  // Define canvas
  //
  TCanvas *canvas = new TCanvas("canvas","canvas",10,10,W,H);
  /*
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L/W );
  canvas->SetRightMargin( R/W );
  canvas->SetRightMargin( 0.2 );
  canvas->SetTopMargin( T/H );
  canvas->SetBottomMargin( B/H );
*/
  canvas->Divide(1,2);
  //  TCanvas *cpie = new TCanvas("cpie","cpie",10,10,W,H);
  TPad* canvas_up = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_1");
  TPad* canvas_dw = (TPad*) canvas->GetListOfPrimitives()->FindObject("canvas_2");
  // define the size
  double up_height     = 0.5;  // please tune so that the upper figures size will meet your requirement
  double dw_correction = 1.275; // please tune so that the smaller canvas size will work in your environment
  double font_size_dw  = 0.1;  // please tune the font size parameter for bottom figure
  double dw_height    = (1. - up_height) * dw_correction;
  double dw_height_offset = 0.040; // KH, added to put the bottom one closer to the top panel
  /*
  //  canvas_up->SetPad(0., dw_height_offset, 0.97, 1.);
  canvas_up->SetPad(0., 0.06, 0.97, 1.);

  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.10);
  canvas_up->SetRightMargin(0.03);
  canvas_up->SetBottomMargin(0.06);  
*/



  canvas_up->SetPad(0., 1 - up_height +0.095, 0.97, 1.);

  //*AR: canvas_dw:(0,0.04,0.97,0.3)
  canvas_dw->SetPad(0., dw_height_offset, 0.97, dw_height+dw_height_offset);
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_up->SetTopMargin(0.15);
  canvas_up->SetRightMargin(0.03);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  canvas_dw->SetBottomMargin(0.1);
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

  canvas_up->SetLogy();
  hSur->Draw("hist e");
  hSur->SetMaximum(12000.);
  hSur->SetMinimum(0.000000065);

  hSur->GetYaxis()->SetTitle("Survival(%)");
  hSur->GetYaxis()->SetTitleSize(0.068);
  hSur->GetYaxis()->SetLabelSize(0.068);
  hSur->GetYaxis()->SetLabelFont(42);
  hSur->GetYaxis()->SetTitleOffset(0.7);

  hSur->GetXaxis()->SetTitleSize(0.04);
  hSur->GetXaxis()->SetLabelSize(0.065);
  hSur->GetXaxis()->SetLabelFont(42);
  hSur->GetXaxis()->SetTitleOffset(0.8);

  TLegend *tlS=new TLegend(0.68,0.68,0.94,0.80);
  //  tlS->SetHeader("Survived fraction");
  tlS->AddEntry(hSurvive,"SM Background","f");
  tlS->SetFillColor(kWhite);    
  tlS->SetLineColor(0);
  tlS->Draw();

  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.95*canvas_up->GetTopMargin());
  ttext->DrawLatexNDC(0.10,0.86, "#bf{CMS} #it{Simulation}");
  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  ttexlumi->SetTextSize(0.95*canvas_up->GetTopMargin());
  //  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  ttexlumi->DrawLatexNDC(0.77, 0.86 , "13 TeV");
  gPad->RedrawAxis();

  canvas_dw->cd();

  //======================================================================



  gStyle->SetOptTitle(0);
  //  gStyle->SetOptLabel(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  //  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  canvas_dw->SetLogy();


  hExp->Draw("hist e");
  hExp->SetMaximum(15000000.);
  hExp->SetMinimum(0.00000008);

  hExp->GetYaxis()->SetTitle("Rejection(%)");
  hExp->GetYaxis()->SetTitleSize(0.05);
  hExp->GetYaxis()->SetLabelSize(0.05);
  hExp->GetYaxis()->SetLabelFont(42);
  hExp->GetYaxis()->SetTitleOffset(1.0);

  hExp->GetXaxis()->SetTitleSize(0.065);
  hExp->GetXaxis()->SetLabelSize(0.095);
  hExp->GetXaxis()->SetLabelFont(42);
  hExp->GetXaxis()->SetTitleOffset(0.8);
  //  hExp->GetXaxis()->SetLabelOffset(0.08);

  TLegend *tlCS=new TLegend(0.52,0.70,0.94,0.99);
  tlCS->SetNColumns(2);
  //  tlCS->SetHeader("Rejected fractions");
  tlCS->AddEntry(hRejNoBin," H_{T}^{miss} < H_{T} cut","f");
  tlCS->AddEntry(hRejMETfilters,"MET filters","f");
  tlCS->AddEntry(hRejIsotrk,"Isotrack veto","f");
  tlCS->AddEntry(hRejLepton,"Lepton veto","f");
  tlCS->AddEntry(hRejDphiCut,"#Delta#phi cut","f");
  tlCS->AddEntry(hRejHTMHTNjetBaseline,"H_{T}, H_{T}^{miss}, N_{jet} cuts","f");


  tlCS->SetFillColor(kWhite);    
  tlCS->SetLineColor(0);
  tlCS->Draw();
  gPad->RedrawAxis();

  /*

  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.52);

  //  ttext->SetTextSize(0.99*pOne->GetTopMargin());
  ttext->DrawLatexNDC(0.0,0.6, "#bf{CMS} #it{Simulation}");

  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  ttexlumi->SetTextSize(0.52);
  //  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  //  ttexlumi->DrawLatexNDC(0.57, 0.72 , "137 fb^{-1} (13 TeV)");
  ttexlumi->DrawLatexNDC(0.73, 0.6 , "(13 TeV)");

*/
  gPad->Update();
  gPad->Modified();

  canvas->Print("StackedFractions_190828.pdf");
  canvas->Print("StackedFractions_190828.png");

}

void GetStackPlotsLPC(){
  
  GetStackPlotsLPC(1300);
  
}
