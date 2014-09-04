#define ProofSelectorMyCutFlow_cxx

//////////////////////////////////////////////////////////
//
// Example of TSelector implementation to do a Monte Carlo
// generation using Pythia8.
// See tutorials/proof/runProof.C, option "pythia8", for an
// example of how to run this selector.
//
//////////////////////////////////////////////////////////
 
#include <TCanvas.h>
#include <TFrame.h>
#include <TPaveText.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1F.h>
#include <TMath.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TParameter.h>
#include "TClonesArray.h"
#include "TParticle.h"
#include "TDatabasePDG.h"
 
#include "ProofSelectorMyCutFlow.h"

//_____________________________________________________________________________
ProofSelectorMyCutFlow::ProofSelectorMyCutFlow()
{
  // Constructor
  
  

  cout << "start proof constructor " << endl;
  fChain     = 0;
  branch     = 0;
  event      = 0;
  dataset    = 0;
  anaEL      = 0;
  verbosity  = 0;
  DataType   = 0;
  Luminosity = 0;
  //histos
  //fHist      = 0;
  
  nselevents_mumumu = 0;
  isTTbarMCatNLO = false;
  
  //------------------------// 
  //initialize the variables
  //------------------------// 
  //------------------------// 
  //for PU
  IReweight             = true;
  IReweight_puUp	= false;
  IReweight_puDown	= false;
  IReweight_pu	        = false;
  //------------------------// 
  //for JES uncertainties
  doJESuncert = false;
  upOrDown    = false;
  applyJES    = false; 
  applyJER    = false;
  ResFactor   = 0.1;
  //------------------------// 
  //for PDF unceratinties
  doPDF = false;
  //pdftype =0 ;
  pdftype =1  ;
  //------------------------// 
  //loose iso on W
  //for backgr studies
  useNonIsoWcand = true;
  looseIso = 0.3; //0.4
  themetcut = 30;
  //------------------------// 
  //tight iso for W cand.
  tightIso_e  = 0.12;
  tightIso_mu = 0.03;
  //------------------------// 
  applyTrigger     = true;
  applyTriggerUp   = false;
  applyTriggerDown = false;
  //------------------------// 
  applyLeptonSF      = false;
  applyLeptonSFUp    = false;
  applyLeptonSFDown  = false;
  //------------------------// 
  
  

  
  cout << "end proof constructor " << endl;

}

//_____________________________________________________________________________
ProofSelectorMyCutFlow::~ProofSelectorMyCutFlow()
{
  // Destructor
  cout << "in destructor " << endl;
  //SafeDelete(fHist);
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses of the tree
  // will be set. It is normaly not necessary to make changes to the
  // generated code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running with PROOF.
  
  //fChain point to the loading tree 
  fChain = tree;
  
  
  cout << "start init tree " << endl;
  // Set branch addresses
  //tree->cd("MyModule);
  
  if(!tree) cout << "tree with null pointer " << endl;
  cout << "	GetNbranches " << tree->GetNbranches() << endl;
  branch = (TBranch *) tree->GetBranch("NTEvent");
  //branch = (TBranch *) tree->GetBranch("NTSampleInfo");
  
  event = new IPHCTree::NTEvent();
  
  if(!branch) cout << "get branch failed " << endl;
  branch->SetAddress(&event);
  
   //event is now retrieved and could be used in Process
   cout << "end init tree " << endl;
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  cout << "start Begin " << endl;
  TString option = GetOption();
  cout << "end  Begin" << endl;
  
  
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::SlaveBegin(TTree * tree)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  
  cout << "start SlaveBegin " << endl;
  TString option = GetOption();
  //--------------------------------------//
  //       Loading the xml file
  //--------------------------------------//
  TNamed *dsname = (TNamed *) fInput->FindObject("PROOF_DATASETNAME"); 
  datasetName = dsname->GetTitle();
  cout << "dataset name " << datasetName << endl;
  
  
  TNamed *xfname = (TNamed *) fInput->FindObject("PROOF_XMLFILENAME");
  string xmlFileName = xfname->GetTitle();
  anaEL = new AnalysisEnvironmentLoader(xmlFileName.c_str());
  
  
  
  anaEL->LoadSamples (datasets, datasetName); // now the list of datasets written in the xml file is known
  
  
  
  //retrieve the current dataset according to its name
  for(unsigned int d=0;d<datasets.size();d++){
    cout << "datasets.size() " << datasets.size()<< "  datasets[d].Name()" << datasets[d].Name()  << " datasetName "
	 <<datasetName  << endl;
    if(datasets[d].Name()==datasetName)dataset = &datasets[d];
  }
  cout << "load datasets "  << endl;
  anaEL->LoadDiLeptonSelection (sel); // now the parameters for the selection are given to the selection
  cout << "datasets loaded "  << endl;
  anaEL->LoadGeneralInfo(DataType, Luminosity, LumiError, PUWeightFileName, verbosity );
   
  anaEL->LoadWeight (sel); // now the parameters for SFBweight are initialized (for b-tag!)
  
  
  //--------------------------------------//
  //   retrive datasets	
  //--------------------------------------//
  
  
  for(unsigned int d=0;d<datasets.size();d++){
    cout << "datasets.size() " << datasets.size()<< "  datasets[d].Name()" << datasets[d].Name()  << " datasetName "
	 <<datasetName  << endl;
    if(datasets[d].Name()==datasetName)dataset = &datasets[d];
  }
  
  
  //--------------------------------------//
  //   Fill cuts and channels  	
  //--------------------------------------//
  CutName.push_back("Cut1");
  
  
  //--------------------------------------//
  //   Determine is dataset or MC samples 	
  //--------------------------------------//
  bool isData_sample = false;    
  if(datasetName=="DataSingleMu") isData_sample = true;
  
    
  
  //--------------------------------------//
  //   Managing histos  	
  //--------------------------------------//
  MyhistoManager.LoadDatasets(datasets);   
  MyhistoManager.LoadSelectionSteps(CutName);
  MyhistoManager.LoadChannels(TheChannelName);
  
  ITypeMC = -1 ;
  
  
  
  createTheHisto(&MyhistoManager);
  
   

   
   //--------------------------------------//
   //   Initialize PU reweighting for 8 TeV 	
   //--------------------------------------//
  
  string PUdatafilename;
  TH1D * dataPUhisto;
  if( !isData_sample && IReweight_pu) {
    if( !IReweight_puDown && !IReweight_puUp ) PUdatafilename = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/PileupHistogram2012_MuEG.root");
    if( IReweight_puDown )                     PUdatafilename = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/");
    if( IReweight_puUp )                       PUdatafilename = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/");
  }
  else {
    if( !IReweight_puDown && !IReweight_puUp ) PUdatafilename = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/PileupHistogram2012_MuEG.root");
    if( IReweight_puDown )                     PUdatafilename = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/");
    if( IReweight_puUp )                       PUdatafilename = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/");
  }
  fexists(PUdatafilename, true);
  
  TFile* pufile = new TFile(PUdatafilename.c_str() );
  dataPUhisto = (TH1D*) pufile->Get( "pileup" );
  LumiWeights = new  PUWeighting( );
  LumiWeights->initPUSummer12_S10(&*dataPUhisto);
  
  
  
  //--------------------------------------//
  //   For JET uncertainties 	
  //--------------------------------------//
  
  
  //cout << " isData_sample  " << isData_sample << endl;
  string jesuncertcalibpath = "";
  if(isData_sample){
    jesuncertcalibpath = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/Summer13_V5_DATA_UncertaintySources_AK5PFchs.txt");
    JetCorrectorParameters *pjetparam = new JetCorrectorParameters( jesuncertcalibpath.c_str(), "Total");
    theJESuncertainty = new JetCorrectionUncertainty( *pjetparam );
  }
  else{
    jesuncertcalibpath = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/macros/data/Fall12_V7_MC_Uncertainty_AK5PFchs.txt");
    theJESuncertainty = new JetCorrectionUncertainty( jesuncertcalibpath.c_str() );    
  }
  
  
  
  //--------------------------------------//
  //   for PDF uncertainties	
  //--------------------------------------//
  
  
  if(doPDF) pdf.Initialize();
  
 
 //--------------------------------------//
  //   Output file 	
  //--------------------------------------//
  //retrieve info from the input:
  TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE");
  //this file will be THE file which will contains all the histograms
  fProofFile = new TProofOutputFile(out->GetTitle());
  // Open the file
  TDirectory *savedir = gDirectory;
  fFile = fProofFile->OpenFile("UPDATE");
  //fFile = fProofFile->OpenFile("NEW");
  if (fFile && fFile->IsZombie()) SafeDelete(fFile);
  savedir->cd();
  

  
  
  
  //this file is very important !!!
  fFile->Write();
  //It is required to add in fOutput the histos you want to feedback
  //fOutput->Add(fHist);
  fOutput->Add(fFile);
  cout << "end SlaveBegin " << endl;
}

//_____________________________________________________________________________
Bool_t ProofSelectorMyCutFlow::Process(Long64_t entry)
{
  
  //---------------------------------------------------//
  // Main event loop: get entry
  //---------------------------------------------------//
  fChain->GetTree()->GetEntry(entry); 
  branch->GetEntry(entry);
  
  IPHCTree::NTTransient::InitializeAfterReading(event);
  
  
  bool isData = false;    
  if(datasetName=="DataSingleMu") isData = true;
  
  
  
  //---------------------------------
  //load events 
  //---------------------------------
  sel.LoadEvent(event);
  
  
  

  //---------------------------------
  //get collections from events 
  //---------------------------------
  double rho = event->pileup.rho_PUUE_dens;
  
  //Collection of selected objects
  vector<NTVertex>   selVertices        = sel.GetSelectedVertex();
  vector<NTElectron> selElectrons       = sel.GetSelectedElectronsRhoIso(20, 2.5, 0.15, 0, 0, 0, 0, rho); 
  vector<NTMuon>     selMuons           = sel.GetSelectedMuonsDeltaBetaIso();
  vector<NTElectron> selElectronsNonIso = sel.GetSelectedElectronsNoIso();
  vector<NTMuon>     selMuonsNonIso     = sel.GetSelectedMuonsNoIso();
  NTMET met   = sel.GetSelectedMET(applyJES, &*theJESuncertainty, upOrDown , applyJER, ResFactor);  
  
 


  //---------------------------------
  //initialize MC weights 
  //---------------------------------
  double Dweight[101];
  for(int k1=0; k1<101; k1++) {
    Dweight[k1] = 0.;
  }
  
  double weightITypeMC_save = Luminosity*dataset->Xsection()/dataset->getNSkimmedEvent();
  double weightITypeMC=0;
  
  
  
  
  //*****************************************************************
  // calcul the MC weights
  //*****************************************************************
  //to do : use isData parameter
  if ( !isData ) { 
    if(IReweight ){
      weightITypeMC = weightITypeMC_save*LumiWeights->weight_Summer12_S10(event->pileup.Tnpv);
    }
    else weightITypeMC = weightITypeMC_save;
  }
  else weightITypeMC = 1;
  
  
  //*****************************************************************
  // determine top decay channel
  //*****************************************************************    
  bool IsSignal      = false;
  
    
  //*****************************************************************
  // determine MC event weight
  //*****************************************************************
  double WeightForBranchingRatio = 1;
  std::vector< double > thereweight = determineWeights(datasetName, weightITypeMC, WeightForBranchingRatio);
  ITypeMC                           = thereweight[0];
  Dweight[ITypeMC]                  = thereweight[1];
  double EventYieldWeightError      = thereweight[2];
  if(thereweight[3] > 0) IsSignal = true; else IsSignal = false;
  
  
  //*****************************************************************
  // pass trigger selection
  //*****************************************************************
  
  bool passtrigger_mujets = false;
  
     
  
  //implemented la selection trigger
  passtrigger_mujets  = sel.passTriggerSelection8TeV ( dataset, "mumu");
  
  
  
  
  
  
  
  
  
  
  
  
  return kTRUE;
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
  if(fProofFile) fProofFile->Print();
  cout << "SlaveTerminate " << fFile << endl;
  if (fFile) {
    //Bool_t cleanup = kFALSE;
    //TDirectory *savedir = gDirectory;
    fFile->cd();
    
    
    
    
    
    
    WriteTheHisto(&*fFile, &MyhistoManager);
    fFile->cd();
  
  
   //The following line is mandatory to copy everything in a common RootFile
    fOutput->Add(fProofFile);

    cleanHistoVector();
    
    //delete fProofFile;
    fFile->Close("R");
    
  }
}





//_____________________________________________________________________________
void ProofSelectorMyCutFlow::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  cout << "stat terminate " << endl;
  //Possibility to retrieve information from the merged file and perform some calculation or plotting tasks
  delete event ;
  
  cout << "event deleted " << endl;
}





//_____________________________________________________________________________
std::vector<double> ProofSelectorMyCutFlow::determineWeights(TString thedatasetName, double weightITypeMC, double WeightForBranchingRatio){
  
  
  
  //------------------------------------
  //to calculate the event weight
  //returns a vector of double,
  //containing the infor for reweighting
  //------------------------------------

   //fixme mettre   ITypeMC en int et pas en double    
    double ITypeMC = 0;
    double Dweight = 0 ;
    double EventYieldWeightError = 0 ;
    double IsSignal = -1 ;
    
    Dweight= weightITypeMC * WeightForBranchingRatio;
    EventYieldWeightError = Dweight*Dweight;
    
    //fixme update (remove ?)  
    if ( thedatasetName=="TTbar" ) {
      ITypeMC = -1;
      Dweight= weightITypeMC * WeightForBranchingRatio;
      EventYieldWeightError = Dweight*Dweight;
    }
    else {
      IsSignal = -1;
      Dweight= weightITypeMC;
      EventYieldWeightError = Dweight*Dweight;
      if ( thedatasetName=="Zjets" || thedatasetName=="DYToLL_M10-50") ITypeMC = 2;
      else if ( thedatasetName=="Wjets" ) ITypeMC = 3;
      else if ( thedatasetName=="SingleToptW" || thedatasetName=="TtW" || thedatasetName=="TbartW"
		|| thedatasetName=="TtWScaleUp" || thedatasetName=="TtWScaleDown"
		|| thedatasetName=="TbartWScaleUp" || thedatasetName=="TbartWScaleDown") ITypeMC = 4;
      else if ( thedatasetName=="WZ" || thedatasetName=="WW" || thedatasetName=="ZZ" 
             || thedatasetName=="WZ_scaleup"|| thedatasetName=="WZ_scaledown"  
             || thedatasetName=="WZ_matchup"|| thedatasetName=="WZ_matchdown" ) ITypeMC = 5;
      else if(thedatasetName=="tZq") ITypeMC = 7;
      else if(thedatasetName=="TT" ) ITypeMC = 8;
      else if(thedatasetName=="TTW" )ITypeMC = 9;
      else if(thedatasetName=="TTZ" )ITypeMC = 10;
   }
  
  if ( thedatasetName=="DataSingleMu") {
     ITypeMC = 100;
     Dweight= weightITypeMC;
     EventYieldWeightError = Dweight*Dweight;
  }




  
  std::vector< double > thereturn;
  thereturn.push_back(ITypeMC);
  thereturn.push_back(Dweight);
  thereturn.push_back(EventYieldWeightError);
  thereturn.push_back(IsSignal);
  
  
  return thereturn;
}








void ProofSelectorMyCutFlow::createTheHisto(HistoManager *thehistomanag){
  
  
   
  thehistomanag->CreateHisto(CutFlow_mujets,  "CutFlow_mujets" ,datasetName,"CutFlow","Entries",15,-0.5,14.5);
  thehistomanag->CreateHisto(ErrCutFlow_mujets,  "ErrCutFlow_mujets"  ,datasetName,"ErrCutFlow","Entries",15,-0.5,14.5);


}
 





void  ProofSelectorMyCutFlow::WriteTheHisto(TFile* theoutputfile, HistoManager *thehistomanag){
  
  
  theoutputfile->cd();
  
  thehistomanag->WriteMyHisto(CutFlow_mujets, "all" );
  thehistomanag->WriteMyHisto(ErrCutFlow_mujets,  "all");


}



void ProofSelectorMyCutFlow::cleanHistoVector(){
  
  
  
  CutFlow_mujets.clear();
  ErrCutFlow_mujets.clear();
  
  
}








