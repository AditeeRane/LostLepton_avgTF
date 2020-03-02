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
void GetPiChart(int hNum){
  
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
  int H = 500;
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

  Float_t valHT1[] = {4.175e4,1.438e5,4228};
  Float_t valHT2[] = {3.303e4,5.597e4,2451};
  Float_t valHT3[] = {5962,9126,486.7};
  Float_t valHT4[] ={750.9,1395.3,86.164};

  Float_t valMHT1[] = {1.96e4,5.63e4,1800};
  Float_t valMHT2[] = {1.234e4,4.347e4,1245};
  Float_t valMHT3[] = {1298,7547,169.9};
  Float_t valMHT4[] ={67.354,866.2,14.496};

  Float_t valNJet1[] = {1.851e4,1.523e5,3186};
  Float_t valNJet2[] = {4.171e4,5.068e4,3098};
  Float_t valNJet3[] = {1.772e4,6840,841};
  Float_t valNJet4[] ={3542.84,568.547,127.06};

  Float_t valNbtag1[] = {1.545e4,1.894e5,1955};
  Float_t valNbtag2[] = {3.886e4,1.91e4,3669};
  Float_t valNbtag3[] = {2.41e4,1763,1477};
  Float_t valNbtag4[] ={3082.06,95.65,150.5};
  gStyle->SetTitleFontSize(0.15);
  gStyle->SetTitle(0);
  Int_t nvals = 3;

  // Define canvas
  //
  TCanvas *cpie = new TCanvas("cpie","cpie",10,10,W,H);

  cpie->SetFillColor(0);
  cpie->SetLineColor(1);
  cpie->SetBorderMode(1);
  cpie->SetFrameFillStyle(0);
  cpie->SetFrameBorderMode(1);
  /*
  cpie->SetLeftMargin( L/W );
  cpie->SetRightMargin( R/W );
  cpie->SetRightMargin( 0.2 );
  cpie->SetTopMargin( T/H );
  cpie->SetBottomMargin( B/H );
*/
  cpie->Divide(5,1);

  //
  // Define pads
  //
  TPad* pOne = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_1");
  TPad* pTwo = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_2");
  TPad* pThree = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_3");
  TPad* pFour = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_4");
  TPad* pFive = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_5");
 
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
  /*
  pOne->SetPad(0.083,0.9529,0.917,1);
  pTwo->SetPad(0.083,0.71489,0.917,0.9529);
  pThree->SetPad(0.083,0.47689,0.917,0.71489);
  pFour->SetPad(0.083,0.2388,0.917,0.47689);
  pFive->SetPad(0.083,dw_height_offset,0.917,0.2388);

  pOne->SetPad(0.083,0.8166,0.917,1.00);
  pTwo->SetPad(0.083,0.65,0.917,0.8166);
  pThree->SetPad(0.083,0.4833,0.917,0.65);
  pFour->SetPad(0.083,0.3166,0.917,0.4833);
  pFive->SetPad(0.083,0.1499,0.917,0.3166);
  

  pOne->SetPad(0.083,0.75,0.917,1.00);
  pTwo->SetPad(0.083,0.5833,0.917,0.75);
  pThree->SetPad(0.083,0.4166,0.917,0.5833);
  pFour->SetPad(0.083,0.25,0.917,0.4166);
  pFive->SetPad(0.083,0.0833,0.917,0.25);
*/

  pOne->SetPad(0.083,0.859,0.917,1.00);
  pTwo->SetPad(0.083,0.66,0.917,0.859);
  pThree->SetPad(0.083,0.46,0.917,0.66);
  pFour->SetPad(0.083,0.26,0.917,0.46);
  pFive->SetPad(0.083,0.0599,0.917,0.26);


  std::cout<<pOne->GetBorderSize()<<endl;




  
  pOne->SetFrameFillColor(0);
  pOne->SetLineColor(kGreen+2);
  pOne->SetFillColor(0);
  //  pOne->SetTopMargin(0.15);
  pOne->SetTopMargin(0.15);

  pOne->SetRightMargin(0.083);
  pOne->SetLeftMargin(0.083);
  pOne->SetBottomMargin(0);  

  pTwo->SetFrameFillColor(0);
  pOne->SetLineColor(1);
  pTwo->SetFillColor(0);
  pTwo->SetTopMargin(0.0);
  pTwo->SetRightMargin(0.083);
  pTwo->SetLeftMargin(0.083);
  pTwo->SetBottomMargin(0);  

  pThree->SetFrameFillColor(0);
  pThree->SetFillColor(0);
  pThree->SetTopMargin(0.0);
  pThree->SetRightMargin(0.083);
  pThree->SetLeftMargin(0.083);
  pThree->SetBottomMargin(0);  

  pFour->GetFrame()->SetBorderMode(1);
  pFour->GetFrame()->SetBorderSize(5);
  pFour->SetFrameFillColor(3);
  pFour->SetFrameLineColor(5);
  //  pFour->SetBorderColor(7);
  pFour->SetBorderSize(2);
  pFour->SetFillColor(0);
  pFour->SetTopMargin(0.0);
  pFour->SetRightMargin(0.083);
  pFour->SetLeftMargin(0.083);
  pFour->SetBottomMargin(0);  

  pFive->SetFillColor(0);
  pFive->SetFrameFillColor(0);
  //  pFive->SetBottomMargin(0.15);
  pFive->SetBottomMargin(0.0599);

  pFive->SetRightMargin(0.083);
  pFive->SetLeftMargin(0.083);
  pFive->SetTopMargin(0);
  
  //pOne->SetLineColor(1); 
  pOne->Draw(); pTwo->Draw(); pThree->Draw(); pFour->Draw(); pFive->Draw();
  pOne->SetLineColor(kGreen+2);


  pOne->Divide(1,1);
  pTwo->Divide(5,1);
  pThree->Divide(5,1);
  pFour->Divide(5,1);
  pFive->Divide(5,1);

  //  cpie->Divide(4,4);
  Int_t colors[] = {4,3,2};
  //HT chart

  TPie *pieHT1 = new TPie("pieHT1","[300-500]",nvals,valHT1,colors);
  TPie *pieHT2 = new TPie("pieHT2","[500-900]",nvals,valHT2,colors);
  TPie *pieHT3 = new TPie("pieHT3","[900-1500]",nvals,valHT3,colors);
  TPie *pieHT4 = new TPie("pieHT4","[>=1500]",nvals,valHT4,colors);
  pTwo->cd();
  TPaveLabel * tboxHT=new TPaveLabel(0,0,1,1,"");
  //  ttextHT->SetLabelSize(0.8);
  tboxHT->SetFillColor(0);
  tboxHT->SetFillStyle(0);
  tboxHT->SetLineColor(1);
  tboxHT->SetShadowColor(0);
  tboxHT->Draw();


  pTwo->cd(1);
  /*
  TPaveLabel * ttextHT=new TPaveLabel(0,0,1,1,"H_{T}");
  ttextHT->SetFillColor(0);
  ttextHT->SetLineColor(0);
  ttextHT->SetShadowColor(0);
  ttextHT->Draw();
*/
  TLatex * ttextHT=new TLatex(0.1,0.5,"H_{T}");
  ttextHT->SetTextSize(0.3);
  ttextHT->SetTextColor(1);
  ttextHT->Draw();


  pTwo->cd(2);
  pieHT1->SetCircle(.5,.43,.385);
  //  pieHT1->SetRadius(.365);
  pieHT1->SetLabelFormat(0);
  pieHT1->Draw("nol < ");

  pTwo->cd(3);
  pieHT2->SetCircle(.5,.43,.385);
  //  pieHT2->SetRadius(.365);
  pieHT2->SetLabelFormat(0);
  pieHT2->Draw("nol < ");

  pTwo->cd(4);
  pieHT3->SetCircle(.5,.43,.385);
  //  pieHT3->SetRadius(.365);
  pieHT3->SetLabelFormat(0);
  pieHT3->Draw("nol < ");

  pTwo->cd(5);
  pieHT4->SetCircle(.5,.43,.385);
  //  pieHT4->SetRadius(.365);
  pieHT4->SetLabelFormat(0);
  pieHT4->Draw("nol < ");
  
  //MHT chart
  TPie *pieMHT1 = new TPie("pieMHT1","[300-350]",nvals,valMHT1,colors);
  TPie *pieMHT2 = new TPie("pieMHT2","[350-500]",nvals,valMHT2,colors);
  TPie *pieMHT3 = new TPie("pieMHT3","[500-750]",nvals,valMHT3,colors);
  TPie *pieMHT4 = new TPie("pieMHT4","[>=750]",nvals,valMHT4,colors);
  pThree->cd();
  TPaveLabel * tboxMHT=new TPaveLabel(0,0,1,1,"");
  //  ttextMHT->SetLabelSize(0.8);
  tboxMHT->SetFillColor(0);
  tboxMHT->SetFillStyle(0);
  tboxMHT->SetLineColor(1);
  tboxMHT->SetShadowColor(0);
  tboxMHT->Draw();


  pThree->cd(1);
  


  TLatex * ttextMHT=new TLatex(0.1,0.5,"H_{T}^{miss}");
  ttextMHT->SetTextSize(0.3);
  ttextMHT->SetTextColor(1);
  ttextMHT->Draw("same");

  /*
  TPaveLabel * ttextMHT=new TPaveLabel(0,0,1,1,"H_{T}^{miss}");
  //  ttextMHT->SetLabelSize(0.8);
  ttextMHT->SetFillColor(0);
  ttextMHT->SetLineColor(0);
  ttextMHT->SetShadowColor(0);
  ttextMHT->Draw();
*/

  pThree->cd(2);
  pieMHT1->SetCircle(.5,.43,.385);
  //  pieMHT1->SetRadius(.365);
  pieMHT1->SetLabelFormat(0);
  pieMHT1->Draw("nol < ");

  pThree->cd(3);
  pieMHT2->SetCircle(.5,.43,.385);
  pieMHT2->SetLabelFormat(0);
  pieMHT2->Draw("nol < ");

  pThree->cd(4);
  pieMHT3->SetCircle(.5,.43,.385);
  pieMHT3->SetLabelFormat(0);
  pieMHT3->Draw("nol < ");

  pThree->cd(5);
  pieMHT4->SetCircle(.5,.43,.385);
  pieMHT4->SetLabelFormat(0);
  pieMHT4->Draw("nol < ");


  //NJet chart
  TPie *pieNJet1 = new TPie("pieNJet1","[2-3]",nvals,valNJet1,colors);
  TPie *pieNJet2 = new TPie("pieNJet2","[4-5]",nvals,valNJet2,colors);
  TPie *pieNJet3 = new TPie("pieNJet3","[6-7]",nvals,valNJet3,colors);
  TPie *pieNJet4 = new TPie("pieNJet4","[>=8]",nvals,valNJet4,colors);
  pFour->cd();
  TPaveLabel * tboxNJet=new TPaveLabel(0,0,1,1,"");
  //  ttextNJet->SetLabelSize(0.8);
  tboxNJet->SetFillColor(0);
  tboxNJet->SetFillStyle(0);
  tboxNJet->SetLineColor(1);
  tboxNJet->SetShadowColor(0);
  tboxNJet->Draw();


  pFour->cd(1);

  TLatex * ttextNJet=new TLatex(0.1,0.5,"N_{jet}");
  ttextNJet->SetTextSize(0.3);
  ttextNJet->SetTextColor(1);
  ttextNJet->Draw();

  /*

  TPaveLabel * ttextNJet=new TPaveLabel(0,0,1,1,"N_{jet}");
  ttextNJet->SetFillColor(0);
  ttextNJet->SetLineColor(0);
  ttextNJet->SetShadowColor(0);
  ttextNJet->Draw();
*/
  pFour->cd(2);
  pieNJet1->SetCircle(.5,.43,.385);
  pieNJet1->SetLabelFormat(0);
  pieNJet1->Draw("nol < ");

  pFour->cd(3);
  pieNJet2->SetCircle(.5,.43,.385);
  pieNJet2->SetLabelFormat(0);
  pieNJet2->Draw("nol < ");

  pFour->cd(4);
  pieNJet3->SetCircle(.5,.43,.385);
  pieNJet3->SetLabelFormat(0);
  pieNJet3->Draw("nol < ");

  pFour->cd(5);
  pieNJet4->SetCircle(.5,.43,.385);
  pieNJet4->SetTextSize(0.8);
  pieNJet4->SetLabelFormat(0);
  pieNJet4->Draw("nol < ");

  //Nbtag chart
  TPie *pieNbtag1 = new TPie("pieNbtag1","[0]",nvals,valNbtag1,colors);
  TPie *pieNbtag2 = new TPie("pieNbtag2","[1]",nvals,valNbtag2,colors);
  TPie *pieNbtag3 = new TPie("pieNbtag3","[2]",nvals,valNbtag3,colors);
  TPie *pieNbtag4 = new TPie("pieNbtag4","[>=3]",nvals,valNbtag4,colors);

  pFive->cd();
  TPaveLabel * tboxNbtag=new TPaveLabel(0,0,1,1,"");
  //  ttextNbtag->SetLabelSize(0.8);
  tboxNbtag->SetFillColor(0);
  tboxNbtag->SetFillStyle(0);
  tboxNbtag->SetLineColor(1);
  tboxNbtag->SetShadowColor(0);
  tboxNbtag->Draw();



  pFive->cd(1);
  /*
  TPaveLabel * ttextNbtag=new TPaveLabel(0,0,1,1,"N_{b-jet}");
  ttextNbtag->SetFillColor(0);
  ttextNbtag->SetLineColor(0);
  ttextNbtag->SetShadowColor(0);
  ttextNbtag->Draw();
*/
  TLatex * ttextNbtag=new TLatex(0.1,0.5,"N_{b-jet}");
  ttextNbtag->SetTextSize(0.3);
  ttextNbtag->SetTextColor(1);
  ttextNbtag->Draw();


  TLatex * textArxiv=new TLatex(0.001,0.03,"#it{arXiv:1908.04722}");
  textArxiv->SetTextSize(0.12);
  textArxiv->SetTextColor(kBlue);
  textArxiv->Draw();


  pFive->cd(2);
  pieNbtag1->SetCircle(.5,.43,.385);
  pieNbtag1->SetLabelFormat(0);
  pieNbtag1->Draw("nol < ");

  pFive->cd(3);
  pieNbtag2->SetCircle(.5,.43,.385);
  pieNbtag2->SetLabelFormat(0);
  pieNbtag2->Draw("nol < ");

  pFive->cd(4);
  pieNbtag3->SetCircle(.5,.43,.385);
  pieNbtag3->SetLabelFormat(0);
  pieNbtag3->Draw("nol < ");

  pFive->cd(5);
  pieNbtag4->SetCircle(.5,.43,.385);
  pieNbtag4->SetLabelFormat(0);
  pieNbtag4->Draw("nol < ");

  pOne->cd();

  TPaveLabel * tboxLeg=new TPaveLabel(0,0,1,0.55,"");
  //  ttextLeg->SetLabelSize(0.8);
  tboxLeg->SetFillColor(0);
  tboxLeg->SetFillStyle(0);
  tboxLeg->SetLineColor(1);
  tboxLeg->SetShadowColor(0);
  tboxLeg->Draw();


  TLatex * ttext = new TLatex();
  ttext->SetTextFont(42);
  ttext->SetTextSize(0.52);

  //  ttext->SetTextSize(0.99*pOne->GetTopMargin());
  ttext->DrawLatexNDC(0.0,0.6, "#bf{CMS}");

  TLatex * ttextSupp = new TLatex();
  ttextSupp->SetTextFont(42);
  ttextSupp->SetTextSize(0.32);

  //  ttextSupp->SetTextSize(0.99*pOne->GetTopMargin());
  ttextSupp->DrawLatexNDC(0.15,0.6, "#it{Simulation Supplementary}");



  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  ttexlumi->SetTextSize(0.52);
  //  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  //  ttexlumi->DrawLatexNDC(0.57, 0.72 , "137 fb^{-1} (13 TeV)");
  ttexlumi->DrawLatexNDC(0.73, 0.6 , "13 TeV");


  //  pOne->cd(1);

  
  TPaveLabel * ttextTT=new TPaveLabel(0.01,0.03,0.06,0.5,"");
  ttextTT->SetFillColor(4);
  ttextTT->SetLineColor(0);
  ttextTT->SetShadowColor(0);
  ttextTT->Draw();
  /*
  TPaveLabel * textTT=new TPaveLabel(0.35,0.2,0.7,0.5,"t#bar{t}");
  textTT->SetFillColor(0);
  textTT->SetLineColor(0);
  textTT->SetShadowColor(0);
  textTT->Draw();
  */
  TLatex * textTT=new TLatex(0.08,0.1,"t#bar{t}");
  textTT->SetTextSize(0.38);
  textTT->SetTextColor(1);
  textTT->Draw();

  
  //  pOne->cd(2);
  //  TPaveLabel * ttextWJet=new TPaveLabel(0.01,0.2,0.2,0.5,"");
  TPaveLabel * ttextWJet=new TPaveLabel(0.29,0.03,0.34,0.5,"");

  ttextWJet->SetFillColor(3);
  ttextWJet->SetLineColor(0);
  ttextWJet->SetShadowColor(0);
  ttextWJet->Draw();
  /*
  TPaveLabel * textWJet=new TPaveLabel(0.35,0.2,0.7,0.5,"W + jets");
  textWJet->SetFillColor(0);
  textWJet->SetLineColor(0);
  textWJet->SetShadowColor(0);
  textWJet->Draw();
*/
  TLatex * textWJet=new TLatex(0.35,0.1,"W + jets");
  textWJet->SetTextSize(0.38);
  textWJet->SetTextColor(1);
  textWJet->Draw();


  pOne->cd(3);


  TPaveLabel * ttextST=new TPaveLabel(0.64,0.03,0.69,0.5,"");
  ttextST->SetFillColor(2);
  ttextST->SetLineColor(0);
  ttextST->SetShadowColor(0);
  ttextST->Draw();

  /*
  TPaveLabel * textST=new TPaveLabel(0.35,0.2,0.7,0.5,"Single top");
  textST->SetFillColor(0);
  textST->SetLineColor(0);
  textST->SetShadowColor(0);
  textST->Draw();
*/
  TLatex * textST=new TLatex(0.71,0.1,"Single top");
  textST->SetTextSize(0.38);
  textST->SetTextColor(1);
  textST->Draw();


  /*


  TPaveText * textWJet=new TPaveText(0,0,0.1,1);
  TPaveText * ttextWJet=new TPaveText(0.2,0,0.85,1);
  ttextWJet->AddText("W + jets");
  textWJet->Fill(3);
  textWJet->Draw();
  ttextWJet->Draw();

  pOne->cd(3);
  TPaveText * textST=new TPaveText(0,0,0.1,1);
  TPaveText * ttextST=new TPaveText(0.2,0,0.85,1);
  ttextST->AddText("single top");
  ttextST->Fill(4);
  textST->Draw();
  ttextST->Draw();

*/
  /*

  TPaveText * textWJet=new TPaveText(0.1,0.55,0.2,0.7);
  TPaveText * textST=new TPaveText(0.1,0.35,0.2,0.5);

  TPaveText * ttextWJet=new TPaveText(0.25,0.55,0.85,0.7);
  TPaveText * ttextST=new TPaveText(0.25,0.35,0.85,0.5);
  

  ttextWJet->AddText("W+jets");
  ttextST->AddText("single top");

  //  textTT->Fill(2);
  textTT->Draw();
  textWJet->Draw();
  textST->Draw();

  ttextTT->Draw();
  ttextWJet->Draw();
  ttextST->Draw();
*/
  gPad->Update();
  gPad->Modified();

  cpie->Print("PieChartHTWithSupplementary_withArxiv_137.pdf");
  cpie->Print("PieChartHTWithSupplementary_withArxiv_137.png");




}

void GetPiChart(){
  
  GetPiChart(1300);
  
}
