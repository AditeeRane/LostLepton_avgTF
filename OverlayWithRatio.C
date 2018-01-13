//void plot_Acceptance_forICHEP2016(std::string elogForPlot=""){



void OverlayWithRatio() {
  //  OverlayWithRatio("TFLL_WithoutDiLep_Nov30_12.25.root","TF_Simon.root","h_0L1L_SB","h_0L1L_SB","Search Bins","TF",0,0,0);
  //  OverlayWithRatio("TFLL_WithoutDiLep_Nov30_12.25.root","TF_Simon.root","h_0L1L_SF_SB","h_0L1L_SF_SB","Search Bins","TF",0,0,0);
  //  OverlayWithRatio("Prediction_0_Total_NoSF_NoDilep_Nov30.root","Prediction_noSF_noDilep_Simon.root","h_Prediction","h_Prediction","Search Bins","Prediction",0,0,0);
  //  OverlayWithRatio("Prediction_0_Total_WithSF_NoDilep_Nov30.root","Prediction_SF_noDilep_Simon.root","h_Prediction","h_Prediction","Search Bins","Prediction",0,0,0);
  OverlayWithRatio("Prediction_0_Total_WithSF_NoDilep_Nov30.root","Prediction_SF_noDilep_Simon.root","h_Prediction","h_Prediction","Search Bins","Prediction",1,0,0);

}

void OverlayWithRatio(char* WJetTTbarMC,char* Wgun,char *histOne,char* histTwo,char *xLabel,char *yLabel, bool logy, bool logx,bool normalized){
  gStyle->SetOptTitle(0);
  int col1 = kRed;
  int col2 = kBlue;
  int i=0;
    
  char hname[500], htit[500];
  char tempWJet[500];
  char LabelX[500];
  char LabelY[500];
  sprintf(tempWJet,histOne);
  sprintf(LabelX,xLabel);
  sprintf(LabelY,yLabel);
  TFile *_file0 = TFile::Open(WJetTTbarMC); 
  TFile *_file1 = TFile::Open(Wgun);
  _file0->cd();
  TH1D *h1 = (TH1D*)_file0->FindObjectAny(histOne);
  _file1->cd();
  TH1D *h2 = (TH1D*)_file1->FindObjectAny(histTwo);

  h1->SetName(tempWJet);
  h1->GetXaxis()->SetTitle(LabelX);
  h1->GetYaxis()->SetTitle(LabelY); 
  h1->SetTitle(tempWJet);
  char cname[500];

  h1->SetLineColor(col1);
  h2->SetLineColor(col2);
  h2->SetLineStyle(2);
  h2->SetLineWidth(2);

  sprintf(cname, "c_%s", histOne);
    
  TCanvas *c = new TCanvas(cname, cname, 500, 500);
  c->Range(0,0,1,1);	
  TPad *pOne = new TPad ("p1", "", 0, 0.3, 1, 1);
  pOne->Draw();
  pOne->cd();
  if(logy)
    c->SetLogy();
  
  if(logx)
    c->SetLogx();
  
  if(normalized){
     h1->Scale(1.0/h1->GetSumOfWeights());
     h2->Scale(1.0/h2->GetSumOfWeights()); 
  }
  h1->Draw();
  h2->Draw("sames");

  // h1->Draw("colz");
  gPad->Update();
  
  TPaveStats *st1 = (TPaveStats*)h1->FindObject("stats");  
  st1->SetLineColor(col1);
  st1->SetX1NDC(0.6);
  st1->SetX2NDC(0.9); 
  st1->SetY1NDC(0.6);
  st1->SetY2NDC(0.9);
  st1->SetTextColor(col1);

  TPaveStats *st2 = (TPaveStats*)h2->FindObject("stats");  
  st2->SetLineColor(col2);
  st2->SetX1NDC(0.6);
  st2->SetX2NDC(0.9); 
  st2->SetY1NDC(0.3);
  st2->SetY2NDC(0.6);
  st2->SetTextColor(col2);
  
  gPad->Modified();
  
  //  TH1D * cOne = new TH1D("Ratio","ratio plot",220, 0.,220.0);
  TH1D * cOne = new TH1D("Ratio","ratio plot",174, 0.,174);

  cOne->SetTitle(0);
  cOne->GetXaxis()->SetTitle(LabelX);
  //  cOne->GetYaxis()->SetTitle("AditeeTF_Red/SimonTF_Blue");
  cOne->GetYaxis()->SetTitle("AditeePrediction_Red/SimonPrediction_Blue");

  int bin=1;
  int nbins=h1->GetSize();
  double zOne=0;
  while(bin<nbins-1){ 
    double xOne=h1->GetBinContent(bin);
    double yOne=h2->GetBinContent(bin); 
    if(yOne!=0)
      zOne=xOne/yOne;
    cOne->SetBinContent(bin,zOne);
    bin++;
  }
  c->cd();
  TPad *pTwo = new TPad ("p2", "", 0, 0, 1, 0.3);
  pTwo->Draw();
  pTwo->cd();
  cOne->Draw();
  gPad->Update();
  cOne->SetLabelSize(0.04,"XY");
  gStyle->SetOptStat(0);
  gPad->Modified();
  
}





