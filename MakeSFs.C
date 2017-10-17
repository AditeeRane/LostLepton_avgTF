#include <TChain.h>
#include <vector>
#include "TProofServ.h"
#include "TProof.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include <iostream>
#include<stdio.h>
#include <fstream>
#include <string>
#include <sstream>
using std::vector;
using namespace std;

//needed to write vector<TLorentzVector> to tree
#ifdef __CINT__
#pragma link C++ class std::vector<TLorentzVector>+;
#endif
void MakeSFs(char* InputTxtFile)
{
  gSystem->Load("libPhysics.so");
  gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

  gROOT->ProcessLine(".L SFMaker.C+");
  vector<string> filesVec;
  char filenames[500]; 
  char TxtFilename[500];
  int numFiles=1;
  //const string TxtFilename = argv[1];
  sprintf(TxtFilename,"%s",InputTxtFile);
  //  ifstream fin(InRootList.c_str());
  ifstream fin(TxtFilename);
  while(fin.getline(filenames, 500) ){filesVec.push_back(filenames);}

  const int nChains = 1;
  TChain *Effchain[nChains];
  for(Int_t i=0; i<nChains; i++){
    Effchain[i] = new TChain("TreeMaker2/PreSelection");
  }
  for(unsigned int in=0; in<filesVec.size(); in++){
    Effchain[0]->Add(filesVec.at(in).c_str());
  }
  /*
  // genHT cut of those samples already performed when skimming!
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTJets_SingleLeptFromT.root");
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTJets_SingleLeptFromTbar.root");
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTJets_DiLept.root");
  
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTJets_HT-600to800.root");
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTJets_HT-800to1200.root");
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTJets_HT-1200to2500.root");
  Effchain[0]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTJets_HT-2500toInf.root");

  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WJetsToLNu_HT-100to200.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WJetsToLNu_HT-200to400.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WJetsToLNu_HT-400to600.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WJetsToLNu_HT-600to800.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WJetsToLNu_HT-800to1200.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WJetsToLNu_HT-1200to2500.root");
  Effchain[1]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WJetsToLNu_HT-2500toInf.root");

  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/ST_s-channel.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/ST_t-channel_antitop.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/ST_t-channel_top.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/ST_tW_antitop.root");
  Effchain[2]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/ST_tW_top.root");

  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTGJets.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTTT.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTWJetsToLNu.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTWJetsToQQ.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTZToLLNuNu.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/TTZToQQ.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WWTo1L1Nu2Q.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WWTo2L2Nu.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WWZ.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WZTo1L1Nu2Q.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WZTo1L3Nu.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/WZZ.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/ZZTo2L2Q.root");
  Effchain[3]->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/mc_v12_baseline/ZZZ.root");

*/
  for(Int_t i=0; i<nChains; i++){ //i<nChains i>2
    std::cout<<"Processing Tree: "<<i<<std::endl;
        Effchain[i]->Process("SFMaker", TString::Format("SFSR_%d.root",i));
  }
}
