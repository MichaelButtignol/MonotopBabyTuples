#ifndef ProofJob_h
#define ProofJob_h

// C headers
#include <iostream>
#include <algorithm>

// Root headers
#include <TSelector.h>
#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TRandom.h>
#include <TH1.h>
#include <TH2.h> 
#include <TH3.h>
#include <TLorentzVector.h>

// IPHC headers
#include "NTFormat/interface/NTEvent.h"
#include "NTFormat/interface/NTGenParticle.h"
#include "Tools/interface/Dataset.h"
#include "Tools/interface/AnalysisEnvironmentLoader.h"

// Stop-analysis specific headers
#include "Selection/interface/combined1LeptonStopSelection.h"
#include "Selection/interface/StopMCinfo.h"
#include "Plots/interface/StopMCCharacterization.h"
#include "EventReco/interface/StopAnaReco.h"
#include "EventReco/interface/Resolution.h"
#include "EventReco/interface/Mt2Com_bisect.h"

// Baby Tuple format definition
#include "ProofFormat.h"

#define SELECTION_TYPE combined1LeptonStopSelection

class ProofJob : public TSelector 
{

 public :
  
  TTree* fChain;
  TBranch* branch;
  IPHCTree::NTEvent* event;
  TFile            *fFile;
  TProofOutputFile *fProofFile; 
  AnalysisEnvironmentLoader* anaEL; 
  vector<Dataset> datasets;
  Dataset* dataset;
  vector<string> CutName;
  vector<string> ChannelName;
  vector<string> VecChannelName;
  float Luminosity;
  int verbosity;
  int DataType;
  
  float LumiError ;
  string PUWeightFileName;
  
  string datasetName ;
  
  //------------------------------------
  // Additionnal info for Stop
  //------------------------------------
  SELECTION_TYPE sel;
  SELECTION_TYPE Void;
  StopMCinfo* stopMCinfo;

  TTree* theTree;

  babyEvent  myEvent;

  //------------------------------------
  // definition of member functions
  //------------------------------------
  ProofJob();
  virtual ~ProofJob();
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual Bool_t  Process(Long64_t entry);
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();

  virtual void InitializeBranches(TTree* theTree, babyEvent* pointerToEvent);
  virtual void LoadCorrectionFiles(); 

  
  ClassDef(ProofJob,0);
};



#endif
