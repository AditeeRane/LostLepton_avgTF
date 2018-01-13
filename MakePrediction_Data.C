#include <TChain.h>
#include "TProofServ.h"
#include "TProof.h"
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

void MakePrediction_Data(const char *InputTxtFile,const char * subSampleKey, const char * Outdir, const char * inputnumber,const char * verbosity)
{
	gSystem->Load("libPhysics.so");
  	gInterpreter->GenerateDictionary("vector<TLorentzVector>","TLorentzVector.h;vector");

	bool useTProof = false;
	gROOT->ProcessLine(".L Prediction.C+");
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
	
	for(Int_t i=0; i<nChains; i++){ //i<nChains i>2
	  std::cout<<"Processing Tree: "<<i<<std::endl;
	  Effchain[i]->Process("Prediction", TString::Format("%s/Prediction_%d_%s_%s.root",Outdir,i,subSampleKey,inputnumber));
	}
	
	
	
//	TChain *Effchain = new TChain("TreeMaker2/PreSelection");
//	Effchain->Add("/nfs/dust/cms/user/kurzsimo/LostLepton/data_v12/Run2016*.root");

	TProof *proof = NULL;
	//*AR, Dec25, 2017-useTProof is false here
	/*
    if(useTProof){
    	proof = TProof::Open("workers=10");
    	Effchain->SetProof();     	
    }
    delete proof;
*/
}
