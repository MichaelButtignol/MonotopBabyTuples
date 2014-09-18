
#define DEBUG_MSG cout << "DEBUG (" << __FILE__ << ", l." << __LINE__ << ") "


#include "ProofJob.h"

#define isCompilingTheBabyTupler
// Baby Tuple format definition
#include "ProofFormat.h"



//_____________________________________________________________________________
ProofJob::ProofJob()
{
  // Constructor
    
  fChain        = 0;
  branch        = 0;
  event         = 0;
  dataset       = 0;
  anaEL         = 0;
  LumiWeights   = 0;
  verbosity     = 0;
  DataType      = 0;
  Luminosity    = 0; 
  theTree       = 0;
  theCutFlowTree= 0;
  fFile         = 0;
  fProofFile    = 0;
// To stock the yield of each cut
  hCutFlow	= new TH1D("hCutFlow", "hCutFlow", 5, -0.5, 4.5);
// To stock some infos before and after the quality cuts
  hnleptons_beforeCut = new TH1D("hnleptons_beforeCut", "hnleptons_beforeCut", 5  , -0.5 , 4.5 );
  hnleptons_afterCut  = new TH1D("hnleptons_afterCut" , "hnleptons_afterCut" , 5  , -0.5 , 4.5 );
  hnjets_beforeCut    = new TH1D("hnjets_beforeCut"   , "hnjets_beforeCut"   , 10 , -0.5 , 9.5 );
  hnjets_afterCut     = new TH1D("hnjets_afterCut"    , "hnjets_afterCut"    , 10 , -0.5 , 9.5 );
  hnBjets_beforeCut   = new TH1D("hnBjets_beforeCut"  , "hnBjets_beforeCut"  , 5  , -0.5 , 4.5 );
  hnBjets_afterCut    = new TH1D("hnBjets_afterCut"   , "hnBjets_afterCut"   , 5  , -0.5 , 4.5 );
  hMuonIso_beforeCut  = new TH1D("hMuonIso_beforeCut" , "hMuonIso_beforeCut" , 21, -0.005, 0.0205);

  monotopMCinfo = new MonotopMCinfo();
}

//_____________________________________________________________________________
ProofJob::~ProofJob() {}

//_____________________________________________________________________________
void ProofJob::Init(TTree *tree)
{
  cout << "Initializing the tree... " << endl;
  fChain = tree;

  // Find the relevant branch and link the NTEvent to it
  branch = (TBranch *) tree->GetBranch("NTEvent");
  event = new IPHCTree::NTEvent();
  branch->SetAddress(&event);

}

//_____________________________________________________________________________
void ProofJob::Begin(TTree * /*tree*/)
{
}

//_____________________________________________________________________________
void ProofJob::SlaveBegin(TTree * /*tree*/)
{

  cout << "      Starting babyTupler job     " << endl;
  
  // ############################
  // #   Get input from PROOF   #
  // ############################

    // Dataset name
    TNamed *dsname = (TNamed *) fInput->FindObject("PROOF_DATASETNAME"); 
    datasetName = dsname->GetTitle();
  
    cout << "     > Dataset : " << datasetName << endl;

    // XML config
    TNamed *xfname = (TNamed *) fInput->FindObject("PROOF_XMLFILENAME");
    string xmlFileName = xfname->GetTitle();
  
    // Output file
    TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE");
    fProofFile = new TProofOutputFile(out->GetTitle());
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("UPDATE");
    if (fFile && fFile->IsZombie()) SafeDelete(fFile);
    savedir->cd();

  // #######################
  // #   Load the config   #
  // #######################

    sel = Void;
    anaEL = new AnalysisEnvironmentLoader(xmlFileName.c_str());
    anaEL->LoadSamples(datasets, datasetName); 
    anaEL->LoadSelection(sel);  
    anaEL->LoadGeneralInfo(DataType, Luminosity, LumiError, verbosity);

    LoadCorrectionFiles();

    // Retrieve the current dataset according to its name
    for(unsigned int d=0;d<datasets.size();d++)
      if (datasets[d].Name() == datasetName) dataset = &datasets[d];

  // #############################
  // #   Initialise the TTree    #
  // #############################

    theTree=new TTree("babyTuple","babyTuple");
    theCutFlowTree=new TTree("CutFlows","CutFlows");
    theTree->SetDirectory(fFile);
    theCutFlowTree->SetDirectory(fFile);

    InitializeBranches(theTree,theCutFlowTree,&myEvent,&myCutFlowEvent);
  
}

//_____________________________________________________________________________
void ProofJob::SlaveTerminate()
{

  if (fFile) 
  {
    fFile->cd();

    hCutFlow->GetXaxis()->SetBinLabel(1, "No sel");
    hCutFlow->GetXaxis()->SetBinLabel(2, "Trigger");
    hCutFlow->GetXaxis()->SetBinLabel(3, "Nlepton == 1");
    hCutFlow->GetXaxis()->SetBinLabel(4, "Njets >= 1");
    hCutFlow->GetXaxis()->SetBinLabel(5, "NBjets == 1");
    hCutFlow->Write(0, TObject::kOverwrite);

    hnleptons_beforeCut->GetXaxis()->SetTitle("number Of leptons before lepton-cut");
    hnleptons_beforeCut->Write(0, TObject::kOverwrite);
    hnleptons_afterCut->GetXaxis()->SetTitle("number Of leptons after lepton-cut");
    hnleptons_afterCut->Write(0, TObject::kOverwrite);
    hnjets_beforeCut->GetXaxis()->SetTitle("number Of jets before jet-cut");
    hnjets_beforeCut->Write(0, TObject::kOverwrite);
    hnjets_afterCut->GetXaxis()->SetTitle("number Of jets after jet-cut");
    hnjets_afterCut->Write(0, TObject::kOverwrite);
    hnBjets_beforeCut->GetXaxis()->SetTitle("number Of Bjets after Bjet-cut");
    hnBjets_beforeCut->Write(0, TObject::kOverwrite);
    hnBjets_afterCut->GetXaxis()->SetTitle("number Of Bjets after Bjet-cut");
    hnBjets_afterCut->Write(0, TObject::kOverwrite);

    hMuonIso_beforeCut->GetXaxis()->SetTitle("isolation of the muon before isoCut at 0.12");
    hMuonIso_beforeCut->Write(0, TObject::kOverwrite);

    theTree->Print();
    theCutFlowTree->Print();
    theTree->Write(0, TObject::kOverwrite); 
    theCutFlowTree->Write(0, TObject::kOverwrite); 

    fProofFile->Print();
    fOutput->Add(fProofFile);

    fFile->Close("R");
  }

  delete anaEL;
  delete monotopMCinfo;

  cout << endl;
  cout << "      Terminating babyTupler job     " << endl;
  cout << endl;

}


//_____________________________________________________________________________
void ProofJob::Terminate()
{
  sel=Void;
  datasets.clear();
  delete fFile;
  delete event;
  delete branch;
  delete fChain;
  delete dataset;
  delete gDirectory;
  delete fProofFile;
}
