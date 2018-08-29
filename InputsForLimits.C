#include "TROOT.h"
#include "SearchBins.h"
//void GetErrorHist(TH1* sys, TH1* input_nominal);
void GetErrorHist(TH1* sys, TH1* input_nominal);
void accErrPropagation(TH1* sys, TH1* input_nominal);
void CorrectLowStatBins(TH1* sys, double ymin, double ymax);
void QCDToSearchBin(TH1* input, TH1* output); 
void takeDiffForSys(TH1* sys, TH1* input_nominal);
void reformat(TH1* input, TH1* output);
void reLabel(TH1* output);
using namespace std;

void InputsForLimits(bool Hadtau=false, bool LostLepton=false, bool LLPlusHadtau=false){
  if(Hadtau){
    char tempname[200];
    std::cout<<" hadatu running"<<endl;
  //    SearchBins_ = new SearchBins(false);
    //SearchBinsQCD_ = new SearchBins(true);
    //unsigned nSB = SearchBinsQCD_->GetNbins();

    TH1D * GenHist, * EstHist, * TFRefHist,* TFRefHist_copy,* TFRefWithBtagProbHist, *TFIDDnHist, *TFIsoDnHist, * TFTrackRecoDnHist, * TFScaleSysHist, * TFPDFSysHist,* TFMTDnHist;
    
    //    THStack * tempstack;
    int NSearchBinArray=174;
    double lumi=35.9;
    double lumiRef=3;
    //Data prediction
    sprintf(tempname,"Prediction_0_Data_MET_HadTau_binSFCorrected_withCSHist.root");
    TFile *DataEstFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname); 
    TH1D* searchBin_nominal = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("searchBin_nominal");
    //Data prediction error
    //TH1D* DataPredErr = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("DataPredErr");
    //GetErrorHist(DataPredErr,searchBin_nominal);
    //Reference TF
    sprintf(tempname,"TFHadTau_JECRef_binSFcorrected.root");
    TFile *RefTFFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TFRefHist=(TH1D*) RefTFFile->Get("h_0L1L_SF_SB")->Clone("TFRefHist");
    TFRefHist_copy=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("TFRefHist_copy");     
    TFRefHist_copy->Reset();
    TH1D* TFErrHist_input=(TH1D*) RefTFFile->Get("h_0L1L_SF_SB")->Clone("TFErrHist_input");
    GetErrorHist(TFErrHist_input,TFRefHist);
    TH1D *TFErrHist=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("TFErrHist");
    TFErrHist->Reset();

    //    TH1D * TFErrHist_input=TFErrHist->Clone("TFErrHist_input");
    //Reference TF with btag probability considered    
    sprintf(tempname,"TFHadTau_JECRefWithBtagProb_binSFcorrected.root");
    TFile *RefTFWithBtagProbFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TFRefWithBtagProbHist=(TH1D*) RefTFWithBtagProbFile->Get("h_0L1L_SF_SB")->Clone("TFRefWithBtagProbHist");

    //TFBtagSysDn with btag probability considered
    sprintf(tempname,"TFHadTau_BtagDnWithBtagProb_binSFcorrected.root");
    TFile * TFBtagSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_BMistagDn_input=(TH1D*) TFBtagSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_BMistagDn_input");//x axis[0.5,223.5]
    TH1D * searchBin_BMistagDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_BMistagDn");
    searchBin_BMistagDn->Reset(); //[0.5,223.5]

    //TFJECSysDn with btag probability considered 
    sprintf(tempname,"TFHadTau_JECDn_binSFcorrected.root");
    TFile * TFJECSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_JECSysDn_input=(TH1D*) TFJECSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_JECSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_JECSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_JECSysDn");
    searchBin_JECSysDn->Reset(); //[0.5,223.5]

    //TFMTSysDn with btag probability considered
    sprintf(tempname,"TFHadTau_MTDn_binSFcorrected.root");
    TFile * TFMTSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MTSysDn_input=(TH1D*) TFMTSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MTSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MTSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MTSysDn");
    searchBin_MTSysDn->Reset(); //[0.5,223.5]


    //TFPDFSysDn with btag probability considered
    sprintf(tempname,"TFHadTau_PDFSys_binSFcorrected.root");
    TFile * TFPDFSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_AccSysPDFRef_input=(TH1D*) TFPDFSysDnFile->Get("h_PDF_0L1L_SF_SB_0")->Clone("searchBin_AccSysPDFRef_input");
    TH1D * searchBin_AccSysPDFDn_input=(TH1D*) TFPDFSysDnFile->Get("h_PDF_0L1L_SF_SB_101")->Clone("searchBin_AccSysPDFDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_AccSysPDFDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_AccSysPDFDn");
    searchBin_AccSysPDFDn->Reset(); //[0.5,223.5]

    //TFScaleSysDn with btag probability considered
    sprintf(tempname,"TFHadTau_ScaleSys_binSFcorrected.root");
    TFile * TFScaleSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_AccSysScaleRef_input=(TH1D*) TFScaleSysDnFile->Get("h_scale_0L1L_SF_SB_0")->Clone("searchBin_AccSysScaleRef_input");//x axis[0.5,223.5]
    TH1D * searchBin_AccSysScaleDn_input=(TH1D*) TFScaleSysDnFile->Get("h_scale_0L1L_SF_SB_9")->Clone("searchBin_AccSysScaleDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_AccSysScaleDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_AccSysScaleDn");
    searchBin_AccSysScaleDn->Reset(); //[0.5,223.5]

    //MuonTrackRecoDn with btag probability considered
    sprintf(tempname,"TFHadTau_TrackRecoDn_binSFcorrected.root");
    TFile * TFTrackRecoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MuRecoSysDn_input=(TH1D*) TFTrackRecoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MuRecoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MuRecoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MuRecoSysDn");
    searchBin_MuRecoSysDn->Reset(); //[0.5,223.5]


    //MuonIsoSysDn with btag probability considered
    sprintf(tempname,"TFHadTau_IsoDn_binSFcorrected.root");
    TFile * TFIsoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MuIsoSysDn_input=(TH1D*) TFIsoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MuIsoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MuIsoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MuIsoSysDn");
    searchBin_MuIsoSysDn->Reset(); //[0.5,223.5]


    TH1D * closureRatio = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("closureRatio");
    closureRatio->Reset(); 
    //MC expectation
    sprintf(tempname,"ARElog115_GenInfo_HadTauEstimation_stacked.root");
    TFile * GenFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);  
    
    sprintf(tempname,"%s","searchH_b");
    THStack * tempstack=(THStack*)GenFile->Get(tempname)->Clone();
    GenHist=(TH1D*) tempstack->GetStack()->Last();
    GenHist->Scale(lumi/lumiRef);
    TH1D * GenHist_input=(TH1D*)GenHist->Clone("GenHist_input");
    reformat(GenHist_input,GenHist);
    // TH1D* GenHist_input =(TH1D*)GenHist->Clone("GenHist_input");
    
    
    //MC prediction
    sprintf(tempname,"Prediction_0_TTbarWJetST_WithoutSF_HadTauDirect_binSFcorrected.root");
    TFile *EstFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    
    sprintf(tempname,"h_Prediction");
    EstHist=(TH1D*) EstFile->Get(tempname);

    closureRatio->Divide(GenHist,EstHist,1,1,"");//[0.5,174.5] 
    
    TH1D* searchBin_one = (TH1D*)closureRatio->Clone("searchBin_one");
    searchBin_one->Reset();
    searchBin_one->SetFillColor(0);
    searchBin_one->SetLineColor(1);
    for (unsigned int ix=1; ix<=NSearchBinArray; ix++){
      searchBin_one->SetBinContent(ix,1.0);
      searchBin_one->SetBinError(ix, 0.0);
    }   
    
    TH1D *searchBin_closureUncertainty=(TH1D*)closureRatio->Clone("searchBin_closureUncertainty");
    searchBin_closureUncertainty->Reset();
    searchBin_closureUncertainty->SetFillColor(0);
    searchBin_one->SetLineColor(1);    
    
    
    for (int ibin=1;ibin<=closureRatio->GetNbinsX();ibin++){
      
      double FracErrorOnClosure;
      double ClosureUncertainty;
      if (closureRatio->GetBinContent(ibin)!=0.){
	FracErrorOnClosure= closureRatio->GetBinError(ibin)/closureRatio->GetBinContent(ibin);
      }
      ClosureUncertainty=TMath::Max(fabs(closureRatio->GetBinContent(ibin)-1.),FracErrorOnClosure);
      if(ClosureUncertainty>1)
	ClosureUncertainty=1;
      searchBin_closureUncertainty->SetBinContent(ibin,ClosureUncertainty);
      // searchBin_closureUncertainty->SetBinError(ibin,0);
      std::cout<<" closureRatio "<<" ibin "<<ibin<<" Gen_bincontent "<<GenHist->GetBinContent(ibin)<<" Est_bincontent "<<EstHist->GetBinContent(ibin)<<" ratio_bincontent-1 "<<closureRatio->GetBinContent(ibin)-1<<" ratio_binerr "<<closureRatio->GetBinError(ibin)<<" FracErrorOnClosure "<<FracErrorOnClosure<<"closureUncertainty_bincontent "<<searchBin_closureUncertainty->GetBinContent(ibin)<<" closureUncertainty_binerrr "<<searchBin_closureUncertainty->GetBinError(ibin)<<endl;
    }
    takeDiffForSys(searchBin_BMistagDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_BMistagDn_input,searchBin_BMistagDn);
    takeDiffForSys(searchBin_JECSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_JECSysDn_input,searchBin_JECSysDn);  
    takeDiffForSys(searchBin_MTSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_MTSysDn_input,searchBin_MTSysDn); 
    
    //Instead of using accErrPropagation(), we used takeDiffForSys() here for PDF and scale systematics. 
    //    accErrPropagation(searchBin_AccSysPDFDn_input,searchBin_AccSysPDFRef_input);
    takeDiffForSys(searchBin_AccSysPDFDn_input,searchBin_AccSysPDFRef_input);
    QCDToSearchBin(searchBin_AccSysPDFDn_input,searchBin_AccSysPDFDn);  
    std::cout<<" *****check seg vio "<<endl;

    //accErrPropagation(searchBin_AccSysScaleDn_input,searchBin_AccSysScaleRef_input);
    takeDiffForSys(searchBin_AccSysScaleDn_input,searchBin_AccSysScaleRef_input);
    QCDToSearchBin(searchBin_AccSysScaleDn_input,searchBin_AccSysScaleDn);  

    takeDiffForSys(searchBin_MuRecoSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_MuRecoSysDn_input,searchBin_MuRecoSysDn); 

    takeDiffForSys(searchBin_MuIsoSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_MuIsoSysDn_input,searchBin_MuIsoSysDn); 

    QCDToSearchBin(TFErrHist_input,TFErrHist);
    QCDToSearchBin(TFRefHist,TFRefHist_copy);
    /*--------------------------------------------------------
    //  Write output file 
    -----------------------------------------------*/


    sprintf(tempname,"InputsForLimits_data_formatted.root");
    TFile fileOut(tempname,"RECREATE");
    searchBin_nominal->Write();
    //    TH1D * searchBin_one_input=(TH1D*)searchBin_one->Clone("searchBin_one_input");
    //    reformat(searchBin_one_input,searchBin_one);
    searchBin_one->Write();
    closureRatio->Write();//[0.5,174.5]
    TH1D * searchBin_closureUncertainty_input=(TH1D*)searchBin_closureUncertainty->Clone("searchBin_closureUncertainty_input");
    //    reformat(searchBin_closureUncertainty_input,searchBin_closureUncertainty);
    searchBin_closureUncertainty->Add(searchBin_one);
    reLabel(searchBin_closureUncertainty);
    searchBin_closureUncertainty->Write();
    //reLabel(DataPredErr);
    //    DataPredErr->Write();
    reLabel(TFErrHist);
    TFErrHist->Write();
    reLabel(TFRefHist_copy);
    TFRefHist_copy->Write();
    searchBin_BMistagDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_BMistagDn,0.99,1.01);
    reLabel(searchBin_BMistagDn);
    searchBin_BMistagDn->Write();
    searchBin_JECSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_JECSysDn,0.95,1.05);
    reLabel(searchBin_JECSysDn);
    searchBin_JECSysDn->Write();
    searchBin_MTSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MTSysDn,0.997,1.003);
    reLabel(searchBin_MTSysDn);
    searchBin_MTSysDn->Write();
    searchBin_AccSysPDFDn->Add(searchBin_one); 
    CorrectLowStatBins(searchBin_AccSysPDFDn,1.00,1.05);
    reLabel(searchBin_AccSysPDFDn);
    searchBin_AccSysPDFDn->Write();
    searchBin_AccSysScaleDn->Add(searchBin_one); 
    CorrectLowStatBins(searchBin_AccSysScaleDn,1.00,1.02);
    reLabel(searchBin_AccSysScaleDn);
    searchBin_AccSysScaleDn->Write();

    searchBin_MuRecoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MuRecoSysDn,1.008,1.01);
    reLabel(searchBin_MuRecoSysDn);
    searchBin_MuRecoSysDn->Write();

    searchBin_MuIsoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MuIsoSysDn,1.006,1.011);
    reLabel(searchBin_MuIsoSysDn);
    searchBin_MuIsoSysDn->Write();

    fileOut.Close();
  }

  if(LostLepton){
    char tempname[200];
    //    SearchBins_ = new SearchBins(false);
    //SearchBinsQCD_ = new SearchBins(true);
    //unsigned nSB = SearchBinsQCD_->GetNbins();

    TH1D * GenHist, * EstHist, * TFRefHist, * LL_TFRefHist_copy,* TFRefWithBtagProbHist, *TFIDDnHist, *TFIsoDnHist, * TFTrackRecoDnHist, * TFScaleSysHist, * TFPDFSysHist,* TFMTDnHist;
    
    //    THStack * tempstack;
    int NSearchBinArray=174;
    double lumi=35.9;
    double lumiRef=3;
    //Data prediction
    sprintf(tempname,"Prediction_0_Data_MET_LL_binSFcorrected_withCSHist.root");
    TFile *DataEstFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D* DataCSStat = (TH1D*)DataEstFile->Get("h_CSStat")->Clone("DataCSStat"); 
    TH1D* totalPred_LL = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("totalPred_LL");
    //Data prediction error
    TH1D* DataCSStatErr = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("DataCSStatErr");
    GetErrorHist(DataCSStatErr,DataCSStat);

    //Reference TF
    sprintf(tempname,"TFLL_JECRef_binSFcorrected.root");
    TFile *RefTFFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TFRefHist=(TH1D*) RefTFFile->Get("h_0L1L_SF_SB")->Clone("TFRefHist");
    LL_TFRefHist_copy=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("LL_TFRefHist_copy");     
    LL_TFRefHist_copy->Reset();

    TH1D* LL_TFErrHist_input=(TH1D*) RefTFFile->Get("h_0L1L_SF_SB")->Clone("LL_TFErrHist_input");
    GetErrorHist(LL_TFErrHist_input,TFRefHist);

    TH1D *LL_TFErrHist=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("LL_TFErrHist");
    LL_TFErrHist->Reset();
    /*
    //Reference TF with btag probability considered    
    sprintf(tempname,"TFHadTau_JECRefWithBtagProb_binSFcorrected.root");
    TFile *RefTFWithBtagProbFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TFRefWithBtagProbHist=(TH1D*) RefTFWithBtagProbFile->Get("h_0L1L_SF_SB")->Clone("TFRefWithBtagProbHist");
*/
    //TFBtagSysDn with btag probability considered
    sprintf(tempname,"TFLL_BtagSysDn_binSFcorrected.root");
    TFile * TFBtagSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LL_BMistagDn_input=(TH1D*) TFBtagSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_LL_BMistagDn_input");//x axis[0.5,223.5]
    TH1D * searchBin_LL_BMistagDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LL_BMistagDn");
    searchBin_LL_BMistagDn->Reset(); //[0.5,223.5]

    //TFJECSysDn with btag probability considered 
    sprintf(tempname,"TFLL_JECDn_binSFcorrected.root");
    TFile * TFJECSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LL_JECSysDn_input=(TH1D*) TFJECSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_LL_JECSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_LL_JECSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LL_JECSysDn");
    searchBin_LL_JECSysDn->Reset(); //[0.5,223.5]

    //TFMTSysDn with btag probability considered
    sprintf(tempname,"TFLL_MTSysDn_binSFcorrected.root");
    TFile * TFMTSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MTSysDn_input=(TH1D*) TFMTSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MTSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MTSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MTSysDn");
    searchBin_MTSysDn->Reset(); //[0.5,223.5]


    //TFPDFSysDn with btag probability considered
    sprintf(tempname,"TFLL_PDFSys_binSFcorrected.root");
    TFile * TFPDFSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LL_AccSysPDFRef_input=(TH1D*) TFPDFSysDnFile->Get("h_PDF_0L1L_SF_SB_0")->Clone("searchBin_LL_AccSysPDFRef_input");
    TH1D * searchBin_LL_AccSysPDFDn_input=(TH1D*) TFPDFSysDnFile->Get("h_PDF_0L1L_SF_SB_101")->Clone("searchBin_LL_AccSysPDFDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_LL_AccSysPDFDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LL_AccSysPDFDn");
    searchBin_LL_AccSysPDFDn->Reset(); //[0.5,223.5]

    //TFScaleSysDn with btag probability considered
    sprintf(tempname,"TFLL_ScaleSys_binSFcorrected.root");
    TFile * TFScaleSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LL_AccSysScaleRef_input=(TH1D*) TFScaleSysDnFile->Get("h_scale_0L1L_SF_SB_0")->Clone("searchBin_LL_AccSysScaleRef_input");//x axis[0.5,223.5]
    TH1D * searchBin_LL_AccSysScaleDn_input=(TH1D*) TFScaleSysDnFile->Get("h_scale_0L1L_SF_SB_9")->Clone("searchBin_LL_AccSysScaleDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_LL_AccSysScaleDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LL_AccSysScaleDn");
    searchBin_LL_AccSysScaleDn->Reset(); //[0.5,223.5]

    //MuonTrackRecoDn with btag probability considered
    sprintf(tempname,"TFLL_TrackRecoSysDn_binSFcorrected.root");
    TFile * TFTrackRecoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MuRecoSysDn_input=(TH1D*) TFTrackRecoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MuRecoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MuRecoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MuRecoSysDn");
    searchBin_MuRecoSysDn->Reset(); //[0.5,223.5]


    //MuonIsoSysDn with btag probability considered
    sprintf(tempname,"TFLL_IsoSysDn_binSFcorrected.root");
    TFile * TFIsoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MuIsoSysDn_input=(TH1D*) TFIsoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MuIsoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MuIsoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MuIsoSysDn");
    searchBin_MuIsoSysDn->Reset(); //[0.5,223.5]


    TH1D * closureRatio = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("closureRatio");
    closureRatio->Reset(); 
    //MC expectation
    TDirectory *dExp = 0;
    
    sprintf(tempname,"LLPrediction_Moriond.root");
    TFile * GenFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);  
    dExp=(TDirectory*)GenFile->Get("Expectation");
    sprintf(tempname,"%s","totalExp_LL");
    /*
    THStack * tempstack=(THStack*)GenFile->Get(tempname)->Clone();
    GenHist=(TH1D*) tempstack->GetStack()->Last();
    GenHist->Scale(lumi/lumiRef);
*/
    TH1D * GenHist_input=(TH1D*)dExp->Get(tempname)->Clone("GenHist_input");
    GenHist=(TH1D*)dExp->Get(tempname)->Clone("GenHist");
    GenHist->Reset();
    reformat(GenHist_input,GenHist);
    // TH1D* GenHist_input =(TH1D*)GenHist->Clone("GenHist_input");
    
    TDirectory *dPre = 0;
    //MC prediction
    sprintf(tempname,"LLPrediction_Moriond.root");
    TFile *EstFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    dPre=(TDirectory*)EstFile->Get("Prediction_MC");
    sprintf(tempname,"totalPred_LL_MC");
    TH1D * EstHist_input=(TH1D*)dPre->Get(tempname)->Clone("EstHist_input");
    EstHist=(TH1D*)dPre->Get(tempname)->Clone("EstHist");
    EstHist->Reset();
    reformat(EstHist_input,EstHist);
    closureRatio->Divide(GenHist,EstHist,1,1,"");//[0.5,174.5] 
    
    TH1D* searchBin_one = (TH1D*)closureRatio->Clone("searchBin_one");
    searchBin_one->Reset();
    searchBin_one->SetFillColor(0);
    searchBin_one->SetLineColor(1);
    for (unsigned int ix=1; ix<=NSearchBinArray; ix++){
      searchBin_one->SetBinContent(ix,1.0);
      searchBin_one->SetBinError(ix, 0.0);
    }   
    
    TH1D *searchBin_LL_closureUncertainty=(TH1D*)closureRatio->Clone("searchBin_LL_closureUncertainty");
    searchBin_LL_closureUncertainty->Reset();
    searchBin_LL_closureUncertainty->SetFillColor(0);
    searchBin_one->SetLineColor(1);    
    
    
    for (int ibin=1;ibin<=closureRatio->GetNbinsX();ibin++){
      
      double FracErrorOnClosure;
      double ClosureUncertainty;
      if (closureRatio->GetBinContent(ibin)!=0.){
	FracErrorOnClosure= closureRatio->GetBinError(ibin)/closureRatio->GetBinContent(ibin);
      }
      ClosureUncertainty=TMath::Max(fabs(closureRatio->GetBinContent(ibin)-1.),FracErrorOnClosure);
      if(ClosureUncertainty>1)
	ClosureUncertainty=1;
      searchBin_LL_closureUncertainty->SetBinContent(ibin,ClosureUncertainty);
      // searchBin_LL_closureUncertainty->SetBinError(ibin,0);
      std::cout<<" closureRatio "<<" ibin "<<ibin<<" Gen_bincontent "<<GenHist->GetBinContent(ibin)<<" Est_bincontent "<<EstHist->GetBinContent(ibin)<<" ratio_bincontent-1 "<<closureRatio->GetBinContent(ibin)-1<<" ratio_binerr "<<closureRatio->GetBinError(ibin)<<" FracErrorOnClosure "<<FracErrorOnClosure<<"closureUncertainty_bincontent "<<searchBin_LL_closureUncertainty->GetBinContent(ibin)<<" closureUncertainty_binerrr "<<searchBin_LL_closureUncertainty->GetBinError(ibin)<<endl;
    }
    takeDiffForSys(searchBin_LL_BMistagDn_input,TFRefHist);
    QCDToSearchBin(searchBin_LL_BMistagDn_input,searchBin_LL_BMistagDn);
    takeDiffForSys(searchBin_LL_JECSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_LL_JECSysDn_input,searchBin_LL_JECSysDn);  
    takeDiffForSys(searchBin_MTSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_MTSysDn_input,searchBin_MTSysDn); 
    
    //Instead of using accErrPropagation(), we used takeDiffForSys() here for PDF and scale systematics. 
    //    accErrPropagation(searchBin_LL_AccSysPDFDn_input,searchBin_LL_AccSysPDFRef_input);
    takeDiffForSys(searchBin_LL_AccSysPDFDn_input,searchBin_LL_AccSysPDFRef_input);
    QCDToSearchBin(searchBin_LL_AccSysPDFDn_input,searchBin_LL_AccSysPDFDn);  
    std::cout<<" *****check seg vio "<<endl;

    //accErrPropagation(searchBin_LL_AccSysScaleDn_input,searchBin_LL_AccSysScaleRef_input);
    takeDiffForSys(searchBin_LL_AccSysScaleDn_input,searchBin_LL_AccSysScaleRef_input);
    QCDToSearchBin(searchBin_LL_AccSysScaleDn_input,searchBin_LL_AccSysScaleDn);  

    takeDiffForSys(searchBin_MuRecoSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_MuRecoSysDn_input,searchBin_MuRecoSysDn); 

    takeDiffForSys(searchBin_MuIsoSysDn_input,TFRefHist);
    QCDToSearchBin(searchBin_MuIsoSysDn_input,searchBin_MuIsoSysDn); 

    QCDToSearchBin(LL_TFErrHist_input,LL_TFErrHist);
    QCDToSearchBin(TFRefHist,LL_TFRefHist_copy);
    /*--------------------------------------------------------
    //  Write output file 
    -----------------------------------------------*/


    sprintf(tempname,"InputsForLimits_data_formatted_LL.root");
    TFile fileOut(tempname,"RECREATE");
    totalPred_LL->Write();
    reLabel(DataCSStat);
    DataCSStat->Write();
    //    TH1D * searchBin_one_input=(TH1D*)searchBin_one->Clone("searchBin_one_input");
    //    reformat(searchBin_one_input,searchBin_one);
    searchBin_one->Write();
    closureRatio->Write();//[0.5,174.5]
    TH1D * searchBin_LL_closureUncertainty_input=(TH1D*)searchBin_LL_closureUncertainty->Clone("searchBin_LL_closureUncertainty_input");
    //    reformat(searchBin_LL_closureUncertainty_input,searchBin_LL_closureUncertainty);
    reLabel(DataCSStatErr);
    DataCSStatErr->Write();

    reLabel(LL_TFErrHist);
    LL_TFErrHist->Write();
    reLabel(LL_TFRefHist_copy);
    LL_TFRefHist_copy->Write();   
    searchBin_LL_closureUncertainty->Add(searchBin_one);
    reLabel(searchBin_LL_closureUncertainty);
    searchBin_LL_closureUncertainty->Write();
    searchBin_LL_BMistagDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_LL_BMistagDn,0.998,1.005);
    reLabel(searchBin_LL_BMistagDn);
    searchBin_LL_BMistagDn->Write("totalPredBMistagDown_LL");
    searchBin_LL_JECSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_LL_JECSysDn,0.96,1.04);
    reLabel(searchBin_LL_JECSysDn);
    searchBin_LL_JECSysDn->Write("totalPred_JECSysDown_LL");
    searchBin_MTSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MTSysDn,0.998,1.000);
    reLabel(searchBin_MTSysDn);
    searchBin_MTSysDn->Write("totalPredMTWSysDown_LL");
    searchBin_LL_AccSysPDFDn->Add(searchBin_one); 
    CorrectLowStatBins(searchBin_LL_AccSysPDFDn,1.00,1.04);
    reLabel(searchBin_LL_AccSysPDFDn);
    searchBin_LL_AccSysPDFDn->Write("totalPredLepAccSysDown_LL");
    searchBin_LL_AccSysScaleDn->Add(searchBin_one); 
    CorrectLowStatBins(searchBin_LL_AccSysScaleDn,1,1.022);
    reLabel(searchBin_LL_AccSysScaleDn);
    searchBin_LL_AccSysScaleDn->Write("totalPredLepAccQsquareSysDown_LL");
    searchBin_MuRecoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MuRecoSysDn,1.02,1.04);
    reLabel(searchBin_MuRecoSysDn);
    searchBin_MuRecoSysDn->Write("totalPredMuRecoSysDown_LL");

    searchBin_MuIsoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MuIsoSysDn,1.015,1.028);
    reLabel(searchBin_MuIsoSysDn);
    searchBin_MuIsoSysDn->Write("totalPredMuIsoSysDown_LL");
    fileOut.Close();
  }


  if(LLPlusHadtau){
    char tempname[200];
    //    SearchBins_ = new SearchBins(false);
    //SearchBinsQCD_ = new SearchBins(true);
    //unsigned nSB = SearchBinsQCD_->GetNbins();

    TH1D * GenHist, * EstHist, * TFRefHist, * LLPlusHadTau_TFRefHist_copy,* TFRefWithBtagProbHist, *TFIDDnHist, *TFIsoDnHist, * TFTrackRecoDnHist, * TFScaleSysHist, * TFPDFSysHist,* TFMTDnHist;
    std::cout<<" LLPlusHadtau is true "<<endl;
    //    THStack * tempstack;
    int NSearchBinArray=174;
    double lumi=35.9;
    double lumiRef=3;
    //Data prediction
    sprintf(tempname,"Prediction_0_Data_MET_LLPlusHadTau_binSFCorrected_withCSHist.root");
    TFile *DataEstFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D* DataCSStat = (TH1D*)DataEstFile->Get("h_CSStat")->Clone("DataCSStat"); 
    TH1D* totalPred_LLPlusHadTau = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("totalPred_LLPlusHadTau");
    //Data prediction error
    TH1D* DataCSStatErr = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("DataCSStatErr");
    GetErrorHist(DataCSStatErr,DataCSStat);

    //Reference TF
    sprintf(tempname,"TFLLPlusHadTau_JECRef_binSFcorrected.root");
    TFile *RefTFFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TFRefHist=(TH1D*) RefTFFile->Get("h_0L1L_SF_SB")->Clone("TFRefHist");
    LLPlusHadTau_TFRefHist_copy=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("LLPlusHadTau_TFRefHist_copy");     
    LLPlusHadTau_TFRefHist_copy->Reset();

    
    //Reference TF with btag probability considered    
    sprintf(tempname,"TFLLPlusHadTau_JECRefWithBtagProb_binSFcorrected.root");
    TFile *RefTFWithBtagProbFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TFRefWithBtagProbHist=(TH1D*) RefTFWithBtagProbFile->Get("h_0L1L_SF_SB")->Clone("TFRefWithBtagProbHist");

    //223(QCD) bin error histogram
    TH1D* LLPlusHadTau_TFErrHist_input=(TH1D*) RefTFFile->Get("h_0L1L_SF_SB")->Clone("LLPlusHadTau_TFErrHist_input");
    GetErrorHist(LLPlusHadTau_TFErrHist_input,TFRefWithBtagProbHist);

    TH1D *LLPlusHadTau_TFErrHist=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("LLPlusHadTau_TFErrHist");
    LLPlusHadTau_TFErrHist->Reset();

    //TFBtagSysDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_BtagDnWithBtagProb_binSFcorrected.root");
    TFile * TFBtagSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LLPlusHadTau_BMistagDn_input=(TH1D*) TFBtagSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_LLPlusHadTau_BMistagDn_input");//x axis[0.5,223.5]
    TH1D * searchBin_LLPlusHadTau_BMistagDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LLPlusHadTau_BMistagDn");
    searchBin_LLPlusHadTau_BMistagDn->Reset(); //[0.5,223.5]

    //TFJECSysDn with btag probability considered 
    sprintf(tempname,"TFLLPlusHadTau_JECDn_CorrectedHadTauJECDn_binSFcorrected_btagProbforHadTau.root");
    TFile * TFJECSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LLPlusHadTau_JECSysDn_input=(TH1D*) TFJECSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_LLPlusHadTau_JECSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_LLPlusHadTau_JECSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LLPlusHadTau_JECSysDn");
    searchBin_LLPlusHadTau_JECSysDn->Reset(); //[0.5,223.5]

    //TFMTSysDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_MTDn_binSFcorrected_btagProbforHadTau.root");
    TFile * TFMTSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MTSysDn_input=(TH1D*) TFMTSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MTSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MTSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MTSysDn");
    searchBin_MTSysDn->Reset(); //[0.5,223.5]


    //TFPDFSysDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_PDFSys_binSFcorrected.root");
    TFile * TFPDFSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LLPlusHadTau_AccSysPDFRef_input=(TH1D*) TFPDFSysDnFile->Get("h_PDF_0L1L_SF_SB_0")->Clone("searchBin_LLPlusHadTau_AccSysPDFRef_input");
    TH1D * searchBin_LLPlusHadTau_AccSysPDFDn_input=(TH1D*) TFPDFSysDnFile->Get("h_PDF_0L1L_SF_SB_101")->Clone("searchBin_LLPlusHadTau_AccSysPDFDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_LLPlusHadTau_AccSysPDFDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LLPlusHadTau_AccSysPDFDn");
    searchBin_LLPlusHadTau_AccSysPDFDn->Reset(); //[0.5,223.5]

    //TFScaleSysDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_ScaleSys_binSFcorrected.root");
    TFile * TFScaleSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_LLPlusHadTau_AccSysScaleRef_input=(TH1D*) TFScaleSysDnFile->Get("h_scale_0L1L_SF_SB_0")->Clone("searchBin_LLPlusHadTau_AccSysScaleRef_input");//x axis[0.5,223.5]
    TH1D * searchBin_LLPlusHadTau_AccSysScaleDn_input=(TH1D*) TFScaleSysDnFile->Get("h_scale_0L1L_SF_SB_9")->Clone("searchBin_LLPlusHadTau_AccSysScaleDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_LLPlusHadTau_AccSysScaleDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_LLPlusHadTau_AccSysScaleDn");
    searchBin_LLPlusHadTau_AccSysScaleDn->Reset(); //[0.5,223.5]

    //MuonTrackRecoDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_MuTrkRecoDn_binSFcorrected.root");
    TFile * TFMuTrackRecoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MuRecoSysDn_input=(TH1D*) TFMuTrackRecoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MuRecoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MuRecoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MuRecoSysDn");
    searchBin_MuRecoSysDn->Reset(); //[0.5,223.5]

    //ElectronTrackRecoDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_EleTrkRecoDn_binSFcorrected.root");
    TFile * TFEleTrackRecoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_EleRecoSysDn_input=(TH1D*) TFEleTrackRecoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_EleRecoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_EleRecoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_EleRecoSysDn");
    searchBin_EleRecoSysDn->Reset(); //[0.5,223.5]


    //MuonIsoSysDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_MuIsoDn_binSFcorrected.root");
    TFile * TFMuIsoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_MuIsoSysDn_input=(TH1D*) TFMuIsoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_MuIsoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_MuIsoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_MuIsoSysDn");
    searchBin_MuIsoSysDn->Reset(); //[0.5,223.5]

    //ElectronIsoSysDn with btag probability considered
    sprintf(tempname,"TFLLPlusHadTau_EleIsoDn_binSFcorrected.root");
    TFile * TFEleIsoSysDnFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    TH1D * searchBin_EleIsoSysDn_input=(TH1D*) TFEleIsoSysDnFile->Get("h_0L1L_SF_SB")->Clone("searchBin_EleIsoSysDn_input");//x axis[0.5,223.5]
    TH1D *searchBin_EleIsoSysDn=(TH1D*) DataEstFile->Get("h_Prediction")->Clone("searchBin_EleIsoSysDn");
    searchBin_EleIsoSysDn->Reset(); //[0.5,223.5]


    TH1D * closureRatio = (TH1D*)DataEstFile->Get("h_Prediction")->Clone("closureRatio");
    closureRatio->Reset(); 
    //MC expectation
    TDirectory *dExp = 0;
    
    sprintf(tempname,"LLPrediction_Moriond.root");
    TFile * GenFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);  
    dExp=(TDirectory*)GenFile->Get("Expectation");
    sprintf(tempname,"%s","totalExp_LL");
    /*
    THStack * tempstack=(THStack*)GenFile->Get(tempname)->Clone();
    GenHist=(TH1D*) tempstack->GetStack()->Last();
    GenHist->Scale(lumi/lumiRef);
*/
    TH1D * GenHist_input=(TH1D*)dExp->Get(tempname)->Clone("GenHist_input");
    GenHist=(TH1D*)dExp->Get(tempname)->Clone("GenHist");
    GenHist->Reset();
    reformat(GenHist_input,GenHist);
    // TH1D* GenHist_input =(TH1D*)GenHist->Clone("GenHist_input");
    
    TDirectory *dPre = 0;
    //MC prediction
    sprintf(tempname,"LLPrediction_Moriond.root");
    TFile *EstFile = TFile::Open(tempname,"R");
    printf("Opened %s\n",tempname);
    dPre=(TDirectory*)EstFile->Get("Prediction_MC");
    sprintf(tempname,"totalPred_LL_MC");
    TH1D * EstHist_input=(TH1D*)dPre->Get(tempname)->Clone("EstHist_input");
    EstHist=(TH1D*)dPre->Get(tempname)->Clone("EstHist");
    EstHist->Reset();
    reformat(EstHist_input,EstHist);
    closureRatio->Divide(GenHist,EstHist,1,1,"");//[0.5,174.5] 
    
    TH1D* searchBin_one = (TH1D*)closureRatio->Clone("searchBin_one");
    searchBin_one->Reset();
    searchBin_one->SetFillColor(0);
    searchBin_one->SetLineColor(1);
    for (unsigned int ix=1; ix<=NSearchBinArray; ix++){
      searchBin_one->SetBinContent(ix,1.0);
      searchBin_one->SetBinError(ix, 0.0);
    }   
    
    TH1D *searchBin_LL_closureUncertainty=(TH1D*)closureRatio->Clone("searchBin_LL_closureUncertainty");
    searchBin_LL_closureUncertainty->Reset();
    searchBin_LL_closureUncertainty->SetFillColor(0);
    searchBin_one->SetLineColor(1);    
    
    
    for (int ibin=1;ibin<=closureRatio->GetNbinsX();ibin++){
      
      double FracErrorOnClosure;
      double ClosureUncertainty;
      if (closureRatio->GetBinContent(ibin)!=0.){
	FracErrorOnClosure= closureRatio->GetBinError(ibin)/closureRatio->GetBinContent(ibin);
      }
      ClosureUncertainty=TMath::Max(fabs(closureRatio->GetBinContent(ibin)-1.),FracErrorOnClosure);
      if(ClosureUncertainty>1)
	ClosureUncertainty=1;
      searchBin_LL_closureUncertainty->SetBinContent(ibin,ClosureUncertainty);
      // searchBin_LLPlusHadTau_closureUncertainty->SetBinError(ibin,0);
      //      std::cout<<" closureRatio "<<" ibin "<<ibin<<" Gen_bincontent "<<GenHist->GetBinContent(ibin)<<" Est_bincontent "<<EstHist->GetBinContent(ibin)<<" ratio_bincontent-1 "<<closureRatio->GetBinContent(ibin)-1<<" ratio_binerr "<<closureRatio->GetBinError(ibin)<<" FracErrorOnClosure "<<FracErrorOnClosure<<"closureUncertainty_bincontent "<<searchBin_LLPlusHadTau_closureUncertainty->GetBinContent(ibin)<<" closureUncertainty_binerrr "<<searchBin_LLPlusHadTau_closureUncertainty->GetBinError(ibin)<<endl;
    }
    takeDiffForSys(searchBin_LLPlusHadTau_BMistagDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_LLPlusHadTau_BMistagDn_input,searchBin_LLPlusHadTau_BMistagDn);
    takeDiffForSys(searchBin_LLPlusHadTau_JECSysDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_LLPlusHadTau_JECSysDn_input,searchBin_LLPlusHadTau_JECSysDn);  
    takeDiffForSys(searchBin_MTSysDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_MTSysDn_input,searchBin_MTSysDn); 
    
    //Instead of using accErrPropagation(), we used takeDiffForSys() here for PDF and scale systematics. 
    //    accErrPropagation(searchBin_LLPlusHadTau_AccSysPDFDn_input,searchBin_LLPlusHadTau_AccSysPDFRef_input);
    takeDiffForSys(searchBin_LLPlusHadTau_AccSysPDFDn_input,searchBin_LLPlusHadTau_AccSysPDFRef_input);
    QCDToSearchBin(searchBin_LLPlusHadTau_AccSysPDFDn_input,searchBin_LLPlusHadTau_AccSysPDFDn);  
    std::cout<<" *****check seg vio "<<endl;

    //accErrPropagation(searchBin_LLPlusHadTau_AccSysScaleDn_input,searchBin_LLPlusHadTau_AccSysScaleRef_input);
    takeDiffForSys(searchBin_LLPlusHadTau_AccSysScaleDn_input,searchBin_LLPlusHadTau_AccSysScaleRef_input);
    QCDToSearchBin(searchBin_LLPlusHadTau_AccSysScaleDn_input,searchBin_LLPlusHadTau_AccSysScaleDn);  

    takeDiffForSys(searchBin_MuRecoSysDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_MuRecoSysDn_input,searchBin_MuRecoSysDn); 

    takeDiffForSys(searchBin_EleRecoSysDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_EleRecoSysDn_input,searchBin_EleRecoSysDn); 

    takeDiffForSys(searchBin_MuIsoSysDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_MuIsoSysDn_input,searchBin_MuIsoSysDn); 

    takeDiffForSys(searchBin_EleIsoSysDn_input,TFRefWithBtagProbHist);
    QCDToSearchBin(searchBin_EleIsoSysDn_input,searchBin_EleIsoSysDn); 


    QCDToSearchBin(LLPlusHadTau_TFErrHist_input,LLPlusHadTau_TFErrHist);
    QCDToSearchBin(TFRefHist,LLPlusHadTau_TFRefHist_copy);
    /*--------------------------------------------------------
    //  Write output file 
    -----------------------------------------------*/


    sprintf(tempname,"InputsForLimits_data_formatted_LLPlusHadTau.root");
    TFile fileOut(tempname,"RECREATE");
    totalPred_LLPlusHadTau->Write();
    reLabel(DataCSStat);
    DataCSStat->Write();
    //    TH1D * searchBin_one_input=(TH1D*)searchBin_one->Clone("searchBin_one_input");
    //    reformat(searchBin_one_input,searchBin_one);
    searchBin_one->Write();
    closureRatio->Write();//[0.5,174.5]
    TH1D * searchBin_LL_closureUncertainty_input=(TH1D*)searchBin_LL_closureUncertainty->Clone("searchBin_LL_closureUncertainty_input");
    //    reformat(searchBin_LLPlusHadTau_closureUncertainty_input,searchBin_LLPlusHadTau_closureUncertainty);
    reLabel(DataCSStatErr);
    DataCSStatErr->Write();

    reLabel(LLPlusHadTau_TFErrHist);
    LLPlusHadTau_TFErrHist->Write();
    reLabel(LLPlusHadTau_TFRefHist_copy);
    LLPlusHadTau_TFRefHist_copy->Write();   
    searchBin_LL_closureUncertainty->Add(searchBin_one);
    reLabel(searchBin_LL_closureUncertainty);
    searchBin_LL_closureUncertainty->Write();
    searchBin_LLPlusHadTau_BMistagDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_LLPlusHadTau_BMistagDn,1.00,1.006);
    reLabel(searchBin_LLPlusHadTau_BMistagDn);
    searchBin_LLPlusHadTau_BMistagDn->Write("totalPredBMistagDown_LLPlusHadTau");
    searchBin_LLPlusHadTau_JECSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_LLPlusHadTau_JECSysDn,0.94,1.06);
    reLabel(searchBin_LLPlusHadTau_JECSysDn);
    searchBin_LLPlusHadTau_JECSysDn->Write("totalPred_JECSysDown_LLPlusHadTau");
    searchBin_MTSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MTSysDn,0.998,1.001);
    reLabel(searchBin_MTSysDn);
    searchBin_MTSysDn->Write("totalPredMTWSysDown_LLPlusHadTau");
    searchBin_LLPlusHadTau_AccSysPDFDn->Add(searchBin_one); 
    CorrectLowStatBins(searchBin_LLPlusHadTau_AccSysPDFDn,1.00,1.01);
    reLabel(searchBin_LLPlusHadTau_AccSysPDFDn);
    searchBin_LLPlusHadTau_AccSysPDFDn->Write("totalPredLepAccSysDown_LLPlusHadTau");
    searchBin_LLPlusHadTau_AccSysScaleDn->Add(searchBin_one); 
    CorrectLowStatBins(searchBin_LLPlusHadTau_AccSysScaleDn,1.000,1.006);
    reLabel(searchBin_LLPlusHadTau_AccSysScaleDn);
    searchBin_LLPlusHadTau_AccSysScaleDn->Write("totalPredLepAccQsquareSysDown_LLPlusHadTau");

    searchBin_MuRecoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MuRecoSysDn,1.008,1.012);
    reLabel(searchBin_MuRecoSysDn);
    searchBin_MuRecoSysDn->Write("totalPredMuRecoSysDown_LLPlusHadTau");

    searchBin_EleRecoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_EleRecoSysDn,1.005,1.008);
    reLabel(searchBin_EleRecoSysDn);
    searchBin_EleRecoSysDn->Write("totalPredEleRecoSysDown_LLPlusHadTau");

    searchBin_MuIsoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_MuIsoSysDn,1.01,1.018);
    reLabel(searchBin_MuIsoSysDn);
    searchBin_MuIsoSysDn->Write("totalPredMuIsoSysDown_LLPlusHadTau");

    searchBin_EleIsoSysDn->Add(searchBin_one);
    CorrectLowStatBins(searchBin_EleIsoSysDn,1.003,1.007);
    reLabel(searchBin_EleIsoSysDn);
    searchBin_EleIsoSysDn->Write("totalPredEleIsoSysDown_LLPlusHadTau");



    fileOut.Close();
  }
}

void GetErrorHist(TH1* sys, TH1* input_nominal){
  sys->Reset();
  sys->SetLineColor(1);
  sys->SetFillColor(0);

  Float_t diff;
  for (int ibin=0;ibin<sys->GetNbinsX();ibin++){
    if (input_nominal->GetBinContent(ibin+1))
      diff =1+(input_nominal->GetBinError(ibin+1)/input_nominal->GetBinContent(ibin+1));
    else
      diff =1+input_nominal->GetBinError(ibin+1);
    sys->SetBinContent(ibin+1,diff);
    std::cout<<" ibin "<<ibin<<" err "<<diff<<endl;
  }
}

void accErrPropagation(TH1* sys, TH1* input_nominal){

  TH1* input_sys = (TH1*)sys->Clone("input_sys");
  sys->Reset();
  sys->SetLineColor(1);
  sys->SetFillColor(0);

  Float_t diff;
  for (int ibin=0;ibin<sys->GetNbinsX();ibin++){
    if (input_nominal->GetBinContent(ibin+1)){
      /* */
      diff = (input_nominal->GetBinContent(ibin+1)) /
	(input_nominal->GetBinContent(ibin+1) + input_sys->GetBinContent(ibin+1));
      /* */
      //diff=input_sys->GetBinContent(ibin+1);
      sys->SetBinContent(ibin+1,diff);
    }
  }
  
}

void CorrectLowStatBins(TH1* sys, double ymin, double ymax){
  TH1* input_sys=(TH1*)sys->Clone("input_sys");
  sys->Reset();
  sys->SetLineColor(1);
  sys->SetFillColor(0);
  for (int ibin=1;ibin<=sys->GetNbinsX();ibin++){
    double binVal=input_sys->GetBinContent(ibin); 
    if(binVal<ymin)
      sys->SetBinContent(ibin,ymin);
    else if(binVal>ymax)
      sys->SetBinContent(ibin,ymax);  
    else
      sys->SetBinContent(ibin,binVal);
  }
}
/*
void CorrectLowStatBins(TH1* sys, double ymin, double ymax){
  TH1* input_sys=(TH1*)sys->Clone("input_sys");
  double avg;
  sys->Reset();
  sys->SetLineColor(1);
  sys->SetFillColor(0);
  for (int ibin=1;ibin<=sys->GetNbinsX();ibin++){
    double binVal=input_sys->GetBinContent(ibin);
    if(ibin==sys->GetNbinsX())
      avg=input_sys->GetBinContent(ibin-1);
    else if(ibin==1)
      avg=input_sys->GetBinContent(ibin+1);
    else
      avg=(input_sys->GetBinContent(ibin-1)+input_sys->GetBinContent(ibin+1))/2;
    double ratio=binVal/avg;
    if(ratio>1.01 || ratio<0.99)
      sys->SetBinContent(ibin,avg); 
    else
      sys->SetBinContent(ibin,binVal);
  }
}
*/
void QCDToSearchBin(TH1* input, TH1* output){
  SearchBins * SearchBins_ = new SearchBins(false); //returns array with indx[0,173]
  SearchBins * SearchBinsQCD_ = new SearchBins(true); //returns array with indx[0,222]
  unsigned nSB = SearchBinsQCD_->GetNbins();
  for (int ibin=0;ibin<nSB;ibin++){
    vector<double> InVector;
    int SBin=-999;
    InVector= SearchBinsQCD_->GetBinMedian(ibin);
    SBin=SearchBins_->GetBinNumber(InVector[0],InVector[1],InVector[2],InVector[3]); //SBin=ibin+1
    std::cout<<" QCDbin "<<ibin+1<<" searchBin "<<SBin<<" HT "<<InVector[0]<<" MHT "<<InVector[1]<<" Njet "<<InVector[2]<<" Nbtag "<<InVector[3]<<endl;
    if(SBin>=0)
      output->SetBinContent(SBin,input->GetBinContent(ibin+1));
    else
      continue;
  }
}


void takeDiffForSys(TH1* sys, TH1* input_nominal){

  TH1* input_sys = (TH1*)sys->Clone("input_sys");
  sys->Reset();
  sys->SetLineColor(1);
  sys->SetFillColor(0);

  Float_t diff;
  for (int ibin=1;ibin<=sys->GetNbinsX();ibin++){
    if (input_nominal->GetBinContent(ibin+1)){
      diff = float((input_sys->GetBinContent(ibin+1)-input_nominal->GetBinContent(ibin+1))
		   /input_nominal->GetBinContent(ibin+1));
      sys->SetBinContent(ibin+1,diff);
    }
  }
  
}

void reformat(TH1* input, TH1* output){

  char tempname[200];  
  //string histname;
  //char hname[500];
  //std::cout << input->GetBinLowEdge(1) << std::endl;
  if (input->GetBinLowEdge(1)==1) {
    output->SetBins(input->GetNbinsX(),input->GetBinLowEdge(1)-0.5,input->GetBinLowEdge(input->GetNbinsX()+1)-0.5);
  }
  /*
  else {
    output->SetBins(input->GetNbinsX(),input->GetBinLowEdge(1)+0.5,input->GetBinLowEdge(input->GetNbinsX()+1)+0.5);
  }
*/
  for (int ibin=1;ibin<=input->GetNbinsX();ibin++){    
    output->SetBinContent(ibin,input->GetBinContent(ibin));    
    output->SetBinError(ibin,input->GetBinError(ibin));    

  }
  //histname=output->GetName();
  // Search Binning

  // QCD Binning
  
};


void reLabel(TH1* output){
  
  char tempname[200];  
  string histname;
  //char hname[500];
  //std::cout << input->GetBinLowEdge(1) << std::endl;
  
  histname=output->GetName();
  std::cout<<" histname "<<histname<<" nbins "<<output->GetNbinsX()<<endl;
  // Search Binning
  if(output->GetNbinsX()==174){
    std::cout<<"***********searchbin labels"<<endl;
    int MaxNb=0;
    int MaxHTMHT=0;
    int bi=0;
    char hname[100];
    for(int nji = 0; nji<5; ++nji){
      if(nji==0)
	MaxNb=3;
      else
	MaxNb=4;
      if(nji>2)
	MaxHTMHT=8;
      else
	MaxHTMHT=10;
      for(int nbi = 0; nbi<MaxNb; ++nbi){
	for(int hti = 0; hti<MaxHTMHT; ++hti){
	  int mhti =0;
	  bi++;
	  if(MaxHTMHT==10){
	    if(hti >=0 && hti <=2) mhti = 0;
	    else if(hti >=3 && hti <=5) mhti = 1;
	    else if(hti >=6 && hti <=7) mhti = 2;
	    else mhti = 3;
	  }
	  if(MaxHTMHT==8){
	    if(hti >=0 && hti <=1) mhti = 0;
	    else if(hti >=2 && hti <=3) mhti = 1;
	    else if(hti >=4 && hti <=5) mhti = 2;
	    else mhti = 3;
	  }
	  
	  char binlabel[100];
	  //int bi = (nji) * 30 + nbi * MaxHTMHT + hti + 1;
	  //	  sprintf(binlabel, "nJet%d-nB%d-MHT%d-HT%d", nji, nbi, mhti, hti);
	  //sprintf(binlabel, "NJets%d_BTags%d_MHT%d_HT%d", nji, nbi, mhti, hti);
	  //if(histname.find("Sys")!=string::npos){
	  //sprintf(hname,"%s_%s","htau",histname.c_str());
	  if(histname.find("nominal")!=string::npos){
	    sprintf(binlabel, "NJets%d_BTags%d_MHT%d_HT%d", nji, nbi, mhti, hti);
	    sprintf(hname,"totalPred_LL");
	  }
	  else if(histname.find("DataCSStatErr")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","DataCSStatErr",nji,nbi, mhti,hti);
	    sprintf(hname,"DataCSStatErr");
	  }
	  else if(histname.find("DataCSStat")!=string::npos){
	    sprintf(binlabel, "CSStat_NJets%d_BTags%d_MHT%d_HT%d", nji, nbi, mhti, hti);
	    sprintf(hname,"DataCSStatistics");
	  }

	  else if(histname.find("StatUncertainties")!=string::npos){
	    sprintf(binlabel, "%sNJets%d_BTags%d_MHT%d_HT%d","HadTauClosure", nji, nbi, mhti, hti);
	    sprintf(hname,"totalPredControlStat_LL");
	  }
	  else if(histname.find("closureUncertainty_adhoc")!=string::npos){
	    sprintf(binlabel, "%s_NJets%d_BTags%d","HadTauCorr", nji, nbi);
	    sprintf(hname,"totalPredAdhoc_HadTau");
	  }
	  else if(histname.find("LL_closureUncertainty")!=string::npos){
	    sprintf(binlabel, "%sNJets%d_BTags%d_MHT%d_HT%d","LLClosure", nji, nbi, mhti, hti);
	    sprintf(hname,"totalPredNonClosure_LL");
	  }

	  else if(histname.find("closureUncertainty")!=string::npos){
	    sprintf(binlabel, "%sNJets%d_BTags%d_MHT%d_HT%d","HadTauClosure", nji, nbi, mhti, hti);
	    sprintf(hname,"totalPredNonClosure_HadTau");
	  }
	  else if(histname.find("LLPlusHadTau_BMistag")!=string::npos){
	    sprintf(binlabel, "LLPlusHadTauBMistag");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredBMistagUp_LLPlusHadTau");
	    else
	      sprintf(hname,"totalPredBMistagDown_LLPlusHadTau");
	  }

	  else if(histname.find("LL_BMistag")!=string::npos){
	    sprintf(binlabel, "LLBMistag");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredBMistagUp_LL");
	    else
	      sprintf(hname,"totalPredBMistagDown_LL");
	  }

	  else if(histname.find("BMistag")!=string::npos){
	    sprintf(binlabel, "HadTauBMistag");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredBMistagUp_HadTau");
	    else
	      sprintf(hname,"totalPredBMistagDown_HadTau");
	  }
	  else if(histname.find("LLPlusHadTau_TFErrHist")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","LLPlusHadTauTFErr",nji,nbi, mhti,hti);
	    sprintf(hname,"LLPlusHadTauTFErr");
	  }
	  else if(histname.find("LL_TFErrHist")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","LLTFErr",nji,nbi, mhti,hti);
	    sprintf(hname,"LLTFErr");
	  }
	  else if(histname.find("TFErrHist")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","TFErr",nji,nbi, mhti,hti);
	    sprintf(hname,"HadTauTFErr");
	  }
	  else if(histname.find("LLPlusHadTau_TFRefHist_copy")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","LLPlusHadTauTF",nji,nbi, mhti,hti);
	    sprintf(hname,"LLPlusHadTauTF");
	  }
	  else if(histname.find("LL_TFRefHist_copy")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","LLTF",nji,nbi, mhti,hti);
	    sprintf(hname,"LLTF");
	  }
	  else if(histname.find("TFRefHist_copy")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","HadTauTF",nji,nbi, mhti,hti);
	    sprintf(hname,"HadTauTF");
	  }

	  /*
	  else if(histname.find("LL_MuRecoSys")!=string::npos){
	    sprintf(binlabel, "LL_muRecoSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredMuRecoSysUp_LL");
	    else
	      sprintf(hname,"totalPredMuRecoSysDown_LL");
	  }
*/
	  else if(histname.find("MuRecoSys")!=string::npos){
	    sprintf(binlabel, "LL_muRecoSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredMuRecoSysUp_LL");
	    else
	      sprintf(hname,"totalPredMuRecoSysDown_LL");
	  }

	  else if(histname.find("EleRecoSys")!=string::npos){
	    sprintf(binlabel, "LL_eleRecoSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredEleRecoSysUp_LL");
	    else
	      sprintf(hname,"totalPredEleRecoSysDown_LL");
	  }

	  /*
	  else if(histname.find("LL_MuIsoSys")!=string::npos){
	    sprintf(binlabel, "LL_muIsoSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredMuIsoSysUp_LL");
	    else
	      sprintf(hname,"totalPredMuIsoSysDown_LL");
	  }
*/
	  else if(histname.find("MuIsoSys")!=string::npos){
	    sprintf(binlabel, "LL_muIsoSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredMuIsoSysUp_LL");
	    else
	      sprintf(hname,"totalPredMuIsoSysDown_LL");
	  }
	  else if(histname.find("EleIsoSys")!=string::npos){
	    sprintf(binlabel, "LL_eleIsoSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredEleIsoSysUp_LL");
	    else
	      sprintf(hname,"totalPredEleIsoSysDown_LL");
	  }
	  else if(histname.find("MuRecoIso")!=string::npos){
	    sprintf(binlabel, "llp_muRecoStat");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredMuRecoStatUp_LL");
	    else
	      sprintf(hname,"totalPredMuRecoStatDown_LL");

	  }
	  else if(histname.find("LLPlusHadTau_JEC")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","LLPlusHadTauEScale",nji,nbi, mhti,hti);
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredJECSysUp_LLPlusHadTau");
	    else
	      sprintf(hname,"totalPredJECSysDown_LLPlusHadTau");
	  }

	  else if(histname.find("LL_JEC")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","LLEScale",nji,nbi, mhti,hti);
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredJECSysUp_LL");
	    else
	      sprintf(hname,"totalPredJECSysDown_LL");
	  }

	  else if(histname.find("JEC")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","HadTauEScale",nji,nbi, mhti,hti);
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredJECSysUp_HadTau");
	    else
	      sprintf(hname,"totalPredJECSysDown_HadTau");
	  }
	  else if(histname.find("MTSys")!=string::npos){
	    sprintf(binlabel,"%s_NJets%d_BTags%d_MHT%d_HT%d","MTSys",nji,nbi, mhti,hti);
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredMTSysUp_LL");
	    else
	      sprintf(hname,"totalPredMTSysDown_LL");
	  }
	  else if(histname.find("MtEffStat")!=string::npos){
	    sprintf(binlabel, "NJets%d_BTags%d_MHT%d_HT%d", nji, nbi, mhti, hti);
	    sprintf(hname,"totalPredMtEffStat_HadTau");
	  }
	  else if(histname.find("IsoTrkVetoEffUncertaintyStat")!=string::npos){
	    sprintf(binlabel, "NJets%d_BTags%d_MHT%d_HT%d", nji, nbi, mhti, hti);
	    sprintf(binlabel, "llp_muIsoStat");
	    sprintf(hname,"totalPredIsoTrackStat_LL");
	  }
	  else if(histname.find("IsoTrkVetoEffUncertaintySys")!=string::npos){
	    sprintf(binlabel, "NJets%d_BTags%d_MHT%d_HT%d", nji, nbi, mhti, hti);
	    sprintf(hname,"totalPredIsoTrackSys_LL");
	  }
	  else if(histname.find("AccStat")!=string::npos){
	    sprintf(binlabel, "%s_%s_NJets%d_BTags%d_MHT%d_HT%d","llp","muAccStat", nji, nbi, mhti, hti);
	    sprintf(hname,"totalPredLepAccStat_LL");
	  }

	  else if(histname.find("searchBin_LLPlusHadTau_AccSysPDFDn")!=string::npos){
	    sprintf(binlabel, "%s_%s","LLPlusHadTau","muAccSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredPDFUp_LLPlusHadTau");
	    else
	      sprintf(hname,"totalPredPDFDown_LLPlusHadTau");
	  }

	  else if(histname.find("searchBin_LL_AccSysPDFDn")!=string::npos){
	    sprintf(binlabel, "%s_%s","LL","muAccSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredPDFUp_LL");
	    else
	      sprintf(hname,"totalPredPDFDown_LL");
	  }

	  else if(histname.find("searchBin_AccSysPDFDn")!=string::npos){
	    sprintf(binlabel, "%s_%s","HadTau","muAccSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredPDFUp_HadTau");
	    else
	      sprintf(hname,"totalPredPDFDown_HadTau");
	  }
	  else if(histname.find("LLPlusHadTau_AccSysScale")!=string::npos){
	    sprintf(binlabel, "%s_%s","LLPlusHadTau","muAccQsquareSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredScaleUp_LLPlusHadTau");
	    else
	      sprintf(hname,"totalPredScaleDown_LLPlusHadTau");
	  }
	  else if(histname.find("LL_AccSysScale")!=string::npos){
	    sprintf(binlabel, "%s_%s","LL","muAccQsquareSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredScaleUp_LL");
	    else
	      sprintf(hname,"totalPredScaleDown_LL");
	  }
	  else if(histname.find("AccSysScale")!=string::npos){
	    sprintf(binlabel, "%s_%s","HadTau","muAccQsquareSys");
	    if(histname.find("Up")!=string::npos)
	      sprintf(hname,"totalPredScaleUp_HadTau");
	    else
	      sprintf(hname,"totalPredScaleDown_HadTau");
	  }
	  else if(histname.find("MuFromTauStat")!=string::npos){
	    sprintf(binlabel, "HadtauMuFromTau");
	    sprintf(hname,"totalPredMuFromTauStat_HadTau");
	  }
	  else if(histname.find("Dilepton")!=string::npos){
	    sprintf(binlabel,"HadTauDilep");
	    sprintf(hname,"totalPredDilep_HadTau");
	  }
	  else if(histname.find("TrigEff")!=string::npos){
	    sprintf(binlabel, "HadTauTrigSyst");
	    sprintf(hname,"totalPredTrigSyst_HadTau");
	  }

	  //}
	  output -> GetXaxis() -> SetBinLabel(bi, binlabel);
	  output ->SetName(hname);
	  std::cout<<" bin "<<bi<<" label "<<binlabel<<endl;
	
	}
      }
    }
  }


  // QCD Binning
  if(output->GetNbinsX()==223){
    std::cout<<"***********QCD labels"<<endl;
    int MaxNb=0;
    int MaxHTMHT=0;
    int bi=0;
    int mhti =0;
    for(int nji = 0; nji<5; ++nji){
      if(nji==0)
	MaxNb=3;
      else
	MaxNb=4;
      if(nji>2)
	MaxHTMHT=10;
      else
	MaxHTMHT=13;
      for(int nbi = 0; nbi<MaxNb; ++nbi){
	for(int hti = 0; hti<MaxHTMHT; ++hti){
	  bi++;
	  if(MaxHTMHT==13){
	    if(hti >=0 && hti <=2) mhti = -1;
	    else if(hti >=3 && hti <=5) mhti = 0;
	    else if(hti >=6 && hti <=8) mhti = 1;
	    else if(hti >=9 && hti <=10) mhti = 2;
	    else mhti = 3;
	  }
	  if(MaxHTMHT==10){
	    if(hti >=0 && hti <=1) mhti = -1;
	    else if(hti >=2 && hti <=3) mhti = 0;
	    else if(hti >=4 && hti <=5) mhti = 1;
	    else if(hti >=6 && hti <=7) mhti = 2;
	    else mhti = 3;
	  }
	  
	  char binlabel[100];
	  //int bi = (nji) * 30 + nbi * MaxHTMHT + hti + 1;
	  //sprintf(binlabel, "nJet%d-nB%d-MHT%d-HT%d", nji, nbi, mhti, hti);
	  //sprintf(binlabel, "NJets%d_BTags%d_MHT%d_HT%d", nji, nbi, mhti, hti);
	  //if(histname.find("Sys")!=string::npos){
	  sprintf(binlabel, "%s_%s_NJets%d_BTags%d_MHT%d_HT%d","htau",histname.c_str(), nji, nbi, mhti, hti);
	  //sprintf(hname,"%s_%s","htau",histname.c_str());
	  //sprintf(binlabel, "%s_NJets%d-BTags%d-MHT%d-HT%d",hname, nji, nbi, mhti, hti);
	  //}
	  output -> GetXaxis() -> SetBinLabel(bi, binlabel);
	  std::cout<<" bin "<<bi<<" label "<<binlabel<<endl;
	}
      }
    }
  }

  
  output -> GetXaxis() -> LabelsOption("v");
  
};

