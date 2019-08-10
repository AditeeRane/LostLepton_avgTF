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
void GetPiChart2DBaselineHTMHT(int hNum){
  
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
  int H = 450;
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
  /*
  Float_t valHT1[] = {4.175e4,1.438e5,4228};
  Float_t valHT2[] = {3.303e4,5.597e4,2451};
  Float_t valHT3[] = {5962,9126,486.7};
  Float_t valHT4[] ={750.9,1395.3,86.164};
  

  Float_t valMHT1[] = {74623.9,131156.3,6005.05};
  Float_t valMHT2[] = {21055.7,29919.07,1225.029};
  Float_t valMHT3[] = {2377.289,10027.76,32.82};
  Float_t valMHT4[] ={223.6,1838.19,1.98};
  */



  Float_t valNJet10[] = {75031.8,195288.9,3127.2};
  Float_t valNJet11[] = {10258.5,21766.9,663.7};
  Float_t valNJet12[] = {1357,2120.9,107.1};

  Float_t valNJet20[] = {22718.7,41500.4,1852.2};
  Float_t valNJet21[] = {9796.5,8609.9,781.7};
  Float_t valNJet22[] = {4636.7,1558.9,239.4};

  Float_t valNJet30[] = {3683.1,4367.5,839.2};
  Float_t valNJet31[] = {3257.5,1440.5,303.9};
  Float_t valNJet32[] = {2391.6,429.2,105.1};

  Float_t valNJet40[] = {402.1,311.8,203.2};
  Float_t valNJet41[] = {542.3,183.3,87.4};
  Float_t valNJet42[] = {603.1,78.8,48.8};






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
  cpie->Divide(4,1);

  //
  // Define pads
  //
  //  TPad* pOne = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_1");
  TPad* pTwo = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_1");
  TPad* pThree = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_2");
  TPad* pFour = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_3");
  TPad* pFive = (TPad*) cpie->GetListOfPrimitives()->FindObject("cpie_4");
 
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
  /*
  pOne->SetPad(0.083,0.859,0.917,1.00);
  pTwo->SetPad(0.083,0.66,0.917,0.859);
  pThree->SetPad(0.083,0.46,0.917,0.66);
  pFour->SetPad(0.083,0.26,0.917,0.46);
  pFive->SetPad(0.083,0.0599,0.917,0.26);
*/
  // pOne->SetPad(0.083,0.859,0.917,1.00);
  
  pTwo->SetPad(0.083,0.777,0.917,1.00);
  pThree->SetPad(0.083,0.555,0.917,0.777);
  pFour->SetPad(0.083,0.333,0.917,0.555);
  pFive->SetPad(0.083,0.111,0.917,0.333);




  /*
  pTwo->SetPad(0.043,0.75,0.967,1.00);
  pThree->SetPad(0.043,0.55,0.967,0.75);
  pFour->SetPad(0.043,0.35,0.967,0.55);
  pFive->SetPad(0.043,0.15,0.967,0.35);
*/

  //  std::cout<<pOne->GetBorderSize()<<endl;




  
  pTwo->SetFrameFillColor(0);
  pTwo->SetLineColor(kGreen+2);
  pTwo->SetFillColor(0);
  //  pTwo->SetTopMargin(0.15);
  pTwo->SetTopMargin(0.15);

  pTwo->SetRightMargin(0.083);
  pTwo->SetLeftMargin(0.083);
  pTwo->SetBottomMargin(0);  

  pThree->SetFrameFillColor(0);
  pThree->SetLineColor(1);
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
  
  //pTwo->SetLineColor(1); 
  pTwo->Draw(); pThree->Draw(); pFour->Draw(); pFive->Draw();
  pTwo->SetLineColor(kGreen+2);


  pTwo->Divide(1,1);
  //pTwo->Divide(5,1);
  pThree->Divide(5,1);
  pFour->Divide(5,1);
  pFive->Divide(5,1);

  //  cpie->Divide(4,4);
  Int_t colors[] = {kBlue-4,2,kYellow};
  //HT chart
  /*
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
  /*
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
  */
  //MHT chart
  TPie *pieNJet10 = new TPie("pieNJet10","[2-3,0]",nvals,valNJet10,colors);
  TPie *pieNJet20 = new TPie("pieNJet20","[4-5,0]",nvals,valNJet20,colors);
  TPie *pieNJet30 = new TPie("pieNJet30","[6-7,0]",nvals,valNJet30,colors);
  TPie *pieNJet40 = new TPie("pieNJet40","[>=8,0]",nvals,valNJet40,colors);
  pThree->cd();
  TPaveLabel * tbox10=new TPaveLabel(0,0,1,1,"");
  //  ttextMHT->SetLabelSize(0.8);
  tbox10->SetFillColor(0);
  tbox10->SetFillStyle(0);
  tbox10->SetLineColor(1);
  tbox10->SetShadowColor(0);
  tbox10->Draw();


  pThree->cd(1);
  


  TLatex * ttext10=new TLatex(0.0002,0.6,"[N_{jet},0 b-jet]");
  ttext10->SetTextSize(0.165);
  ttext10->SetTextColor(1);
  ttext10->Draw("same");
  /*
  TLatex * tttext10=new TLatex(0.1,0.35,"[N_{jet},0]");
  tttext10->SetTextSize(0.2);
  tttext10->SetTextColor(1);
  tttext10->Draw("same");
*/

  pThree->cd(2);

  pieNJet10->SetCircle(.5,.43,.385);
  //  pieNJet1->SetRadius(.365);
  pieNJet10->SetLabelFormat(0);
  pieNJet10->Draw("nol < ");

  pThree->cd(3);
  pieNJet20->SetCircle(.5,.43,.385);
  pieNJet20->SetLabelFormat(0);
  pieNJet20->Draw("nol < ");

  pThree->cd(4);
  pieNJet30->SetCircle(.5,.43,.385);
  pieNJet30->SetLabelFormat(0);
  pieNJet30->Draw("nol < ");

  pThree->cd(5);
  pieNJet40->SetCircle(.5,.43,.385);
  pieNJet40->SetLabelFormat(0);
  pieNJet40->Draw("nol < ");





  TPie *pieNJet11 = new TPie("pieNJet11","[2-3,1]",nvals,valNJet11,colors);
  TPie *pieNJet21 = new TPie("pieNJet21","[4-5,1]",nvals,valNJet21,colors);
  TPie *pieNJet31 = new TPie("pieNJet31","[6-7,1]",nvals,valNJet31,colors);
  TPie *pieNJet41 = new TPie("pieNJet41","[>=8,1]",nvals,valNJet41,colors);
  pFour->cd();
  TPaveLabel * tbox11=new TPaveLabel(0,0,1,1,"");
  //  ttextMHT->SetLabelSize(0.8);
  tbox11->SetFillColor(0);
  tbox11->SetFillStyle(0);
  tbox11->SetLineColor(1);
  tbox11->SetShadowColor(0);
  tbox11->Draw();


  pFour->cd(1);
  


  TLatex * ttext11=new TLatex(0.0002,0.6,"[N_{jet},1 b-jet]");
  ttext11->SetTextSize(0.165);
  ttext11->SetTextColor(1);
  ttext11->Draw("same");


  pFour->cd(2);

  pieNJet11->SetCircle(.5,.43,.385);
  //  pieNJet1->SetRadius(.365);
  pieNJet11->SetLabelFormat(0);
  pieNJet11->Draw("nol < ");

  pFour->cd(3);
  pieNJet21->SetCircle(.5,.43,.385);
  pieNJet21->SetLabelFormat(0);
  pieNJet21->Draw("nol < ");

  pFour->cd(4);
  pieNJet31->SetCircle(.5,.43,.385);
  pieNJet31->SetLabelFormat(0);
  pieNJet31->Draw("nol < ");

  pFour->cd(5);
  pieNJet41->SetCircle(.5,.43,.385);
  pieNJet41->SetLabelFormat(0);
  pieNJet41->Draw("nol < ");


  TPie *pieNJet12 = new TPie("pieNJet12","[2-3,>=2]",nvals,valNJet12,colors);
  TPie *pieNJet22 = new TPie("pieNJet22","[4-5,>=2]",nvals,valNJet22,colors);
  TPie *pieNJet32 = new TPie("pieNJet32","[6-7,>=2]",nvals,valNJet32,colors);
  TPie *pieNJet42 = new TPie("pieNJet42","[>=8,>=2]",nvals,valNJet42,colors);
  pFive->cd();
  TPaveLabel * tbox12=new TPaveLabel(0,0,1,1,"");
  //  ttextMHT->SetLabelSize(0.8);
  tbox12->SetFillColor(0);
  tbox12->SetFillStyle(0);
  tbox12->SetLineColor(1);
  tbox12->SetShadowColor(0);
  tbox12->Draw();


  pFive->cd(1);
  


  TLatex * ttext12=new TLatex(0.0002,0.6,"[N_{jet},2+ b-jets]");
  ttext12->SetTextSize(0.165);
  ttext12->SetTextColor(1);
  ttext12->Draw("same");



  pFive->cd(2);

  pieNJet12->SetCircle(.5,.43,.385);
  //  pieNJet1->SetRadius(.365);
  pieNJet12->SetLabelFormat(0);
  pieNJet12->Draw("nol < ");

  pFive->cd(3);
  pieNJet22->SetCircle(.5,.43,.385);
  pieNJet22->SetLabelFormat(0);
  pieNJet22->Draw("nol < ");

  pFive->cd(4);
  pieNJet32->SetCircle(.5,.43,.385);
  pieNJet32->SetLabelFormat(0);
  pieNJet32->Draw("nol < ");

  pFive->cd(5);
  pieNJet42->SetCircle(.5,.43,.385);
  pieNJet42->SetLabelFormat(0);
  pieNJet42->Draw("nol < ");




  pTwo->cd();

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

  //  ttext->SetTextSize(0.99*pTwo->GetTopMargin());
  ttext->DrawLatexNDC(0.0,0.6, "#bf{CMS}");

  TLatex * ttextSupp = new TLatex();
  ttextSupp->SetTextFont(42);
  ttextSupp->SetTextSize(0.32);

  //  ttextSupp->SetTextSize(0.99*pTwo->GetTopMargin());
  ttextSupp->DrawLatexNDC(0.22,0.6, "#it{Supplementary}");



  TLatex * ttexlumi = new TLatex();
  ttexlumi->SetTextFont(42);
  ttexlumi->SetTextSize(0.52);
  //  double binSize=(GetRatioXmax-GetRatioXmin)/GetRatioNbins;
  //  ttexlumi->DrawLatexNDC(0.57, 0.72 , "137 fb^{-1} (13 TeV)");
  ttexlumi->DrawLatexNDC(0.68, 0.6 , "13 TeV");


  //  pTwo->cd(1);

  
  TPaveLabel * ttextTT=new TPaveLabel(0.01,0.04,0.06,0.5,"");
  ttextTT->SetFillColor(kBlue-4);
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
  TLatex * textTT=new TLatex(0.07,0.1,"Lost lepton");
  textTT->SetTextSize(0.30);
  textTT->SetTextColor(1);
  textTT->Draw();

  
  //  pTwo->cd(2);
  //  TPaveLabel * ttextWJet=new TPaveLabel(0.01,0.2,0.2,0.5,"");
  TPaveLabel * ttextWJet=new TPaveLabel(0.36,0.04,0.41,0.5,"");

  ttextWJet->SetFillColor(2);
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
  TLatex * textWJet=new TLatex(0.42,0.1,"Z#rightarrow#nu#bar{#nu}");
  textWJet->SetTextSize(0.30);
  textWJet->SetTextColor(1);
  textWJet->Draw();


  //pTwo->cd(3);


  TPaveLabel * ttextST=new TPaveLabel(0.57,0.04,0.62,0.5,"");
  ttextST->SetFillColor(kYellow);
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
  TLatex * textST=new TLatex(0.63,0.1,"QCD");
  textST->SetTextSize(0.30);
  textST->SetTextColor(1);
  textST->Draw();

  //  pTwo->cd(2);
  
  TLatex * textHT=new TLatex(0.75,0.35,"H_{T} > 300 GeV");
  textHT->SetTextSize(0.18);
  textHT->SetTextColor(1);
  textHT->Draw();

  TLatex * textMHT=new TLatex(0.75,0.1,"H_{T}^{miss} > 300 GeV");
  textMHT->SetTextSize(0.18);
  textMHT->SetTextColor(1);
  textMHT->Draw();
 



 /*


  TPaveText * textWJet=new TPaveText(0,0,0.1,1);
  TPaveText * ttextWJet=new TPaveText(0.2,0,0.85,1);
  ttextWJet->AddText("W + jets");
  textWJet->Fill(3);
  textWJet->Draw();
  ttextWJet->Draw();

  pTwo->cd(3);
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

  cpie->Print("PieChart2DBaselineHTMHTAllBkg_137.pdf");
  cpie->Print("PieChart2DBaselineHTMHTAllBkg_137.png");




}

void GetPiChart2DBaselineHTMHT(){
  
  GetPiChart2DBaselineHTMHT(1300);
  
}
