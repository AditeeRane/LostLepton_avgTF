void GetPiChart(){
  Float_t valHT1[] = {13340,45200,1554};
  Float_t valHT2[] = {10140,17070,812.8};
  Float_t valHT3[] = {1790,2719,155.1};
  Float_t valHT4[] ={236.18,414.18,28.379};

  Float_t valMHT1[] = {6140,17390,615};
  Float_t valMHT2[] = {3825,13350,427.4};
  Float_t valMHT3[] = {399.1,2377,60.66};
  Float_t valMHT4[] ={20.721,270.71,4.3111};

  Float_t valNJet1[] = {5708,47500,1172};
  Float_t valNJet2[] = {13110,15670,1052};
  Float_t valNJet3[] = {5616,2067,289.5};
  Float_t valNJet4[] ={1073.27,158.592,36.585};

  Float_t valNbtag1[] = {4753,59450,696.5};
  Float_t valNbtag2[] = {12240,5424,1296};
  Float_t valNbtag3[] = {7592,502,507.5};
  Float_t valNbtag4[] ={905.563,24.386,49.884};
  gStyle->SetTitleFontSize(0.1);

  Int_t nvals = 3;
  TCanvas *cpie = new TCanvas("cpie","TPie test",700,700);
  cpie->Divide(5,4);
  Int_t colors[] = {4,3,2};
  //HT chart

  TPie *pieHT1 = new TPie("pieHT1","HT:[300-500]",nvals,valHT1,colors);
  TPie *pieHT2 = new TPie("pieHT2","HT:[500-900]",nvals,valHT2,colors);
  TPie *pieHT3 = new TPie("pieHT3","HT:[900-1500]",nvals,valHT3,colors);
  TPie *pieHT4 = new TPie("pieHT4","HT:[>=1500]",nvals,valHT4,colors);
  cpie->cd(1);
  pieHT1->SetRadius(.24);
  pieHT1->SetLabelFormat(0);
  pieHT1->Draw("nol <");

  cpie->cd(2);
  pieHT2->SetRadius(.24);
  pieHT2->SetLabelFormat(0);
  pieHT2->Draw("nol <");

  cpie->cd(3);
  pieHT3->SetRadius(.24);
  pieHT3->SetLabelFormat(0);
  pieHT3->Draw("nol <");

  cpie->cd(4);
  pieHT4->SetRadius(.24);
  pieHT4->SetLabelFormat(0);
  pieHT4->Draw("nol <");

  //MHT chart
  TPie *pieMHT1 = new TPie("pieMHT1","MHT:[300-350]",nvals,valMHT1,colors);
  TPie *pieMHT2 = new TPie("pieMHT2","MHT:[350-500]",nvals,valMHT2,colors);
  TPie *pieMHT3 = new TPie("pieMHT3","MHT:[500-750]",nvals,valMHT3,colors);
  TPie *pieMHT4 = new TPie("pieMHT4","MHT:[>=750]",nvals,valMHT4,colors);
  cpie->cd(6);
  pieMHT1->SetRadius(.24);
  pieMHT1->SetLabelFormat(0);
  pieMHT1->Draw("nol <");

  cpie->cd(7);
  pieMHT2->SetRadius(.24);
  pieMHT2->SetLabelFormat(0);
  pieMHT2->Draw("nol <");

  cpie->cd(8);
  pieMHT3->SetRadius(.24);
  pieMHT3->SetLabelFormat(0);
  pieMHT3->Draw("nol <");

  cpie->cd(9);
  pieMHT4->SetRadius(.24);
  pieMHT4->SetLabelFormat(0);
  pieMHT4->Draw("nol <");


  //NJet chart
  TPie *pieNJet1 = new TPie("pieNJet1","NJet:[2-3]",nvals,valNJet1,colors);
  TPie *pieNJet2 = new TPie("pieNJet2","NJet:[4-5]",nvals,valNJet2,colors);
  TPie *pieNJet3 = new TPie("pieNJet3","NJet:[6-7]",nvals,valNJet3,colors);
  TPie *pieNJet4 = new TPie("pieNJet4","NJet:[>=8]",nvals,valNJet4,colors);
  cpie->cd(11);
  pieNJet1->SetRadius(.24);
  pieNJet1->SetLabelFormat(0);
  pieNJet1->Draw("nol <");

  cpie->cd(12);
  pieNJet2->SetRadius(.24);
  pieNJet2->SetLabelFormat(0);
  pieNJet2->Draw("nol <");

  cpie->cd(13);
  pieNJet3->SetRadius(.24);
  pieNJet3->SetLabelFormat(0);
  pieNJet3->Draw("nol <");

  cpie->cd(14);
  pieNJet4->SetRadius(.24);
  pieNJet4->SetLabelFormat(0);
  pieNJet4->Draw("nol <");

  //Nbtag chart
  TPie *pieNbtag1 = new TPie("pieNbtag1","Nbtag:[0]",nvals,valNbtag1,colors);
  TPie *pieNbtag2 = new TPie("pieNbtag2","Nbtag:[1]",nvals,valNbtag2,colors);
  TPie *pieNbtag3 = new TPie("pieNbtag3","Nbtag:[2]",nvals,valNbtag3,colors);
  TPie *pieNbtag4 = new TPie("pieNbtag4","Nbtag:[>=3]",nvals,valNbtag4,colors);
  cpie->cd(16);
  pieNbtag1->SetRadius(.24);
  pieNbtag1->SetLabelFormat(0);
  pieNbtag1->Draw("nol <");

  cpie->cd(17);
  pieNbtag2->SetRadius(.24);
  pieNbtag2->SetLabelFormat(0);
  pieNbtag2->Draw("nol <");

  cpie->cd(18);
  pieNbtag3->SetRadius(.24);
  pieNbtag3->SetLabelFormat(0);
  pieNbtag3->Draw("nol <");

  cpie->cd(19);
  pieNbtag4->SetRadius(.24);
  pieNbtag4->SetLabelFormat(0);
  pieNbtag4->Draw("nol <");

  cpie->cd(5);
  TPaveText * textTT=new TPaveText(0.1,0.75,0.2,0.9);
  TPaveText * textWJet=new TPaveText(0.1,0.55,0.2,0.7);
  TPaveText * textST=new TPaveText(0.1,0.35,0.2,0.5);

  TPaveText * ttextTT=new TPaveText(0.25,0.75,0.85,0.9);
  TPaveText * ttextWJet=new TPaveText(0.25,0.55,0.85,0.7);
  TPaveText * ttextST=new TPaveText(0.25,0.35,0.85,0.5);


  ttextTT->AddText("ttbar");
  ttextWJet->AddText("W+jets");
  ttextST->AddText("single top");

  //  textTT->Fill(2);
  textTT->Draw();
  textWJet->Draw();
  textST->Draw();

  ttextTT->Draw();
  ttextWJet->Draw();
  ttextST->Draw();

  gPad->Update();
  gPad->Modified();

  //  cpie->Print("PieChartHT.pdf");
}
