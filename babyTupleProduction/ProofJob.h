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

// Monotop-analysis specific headers
#include "Selection/interface/MyMonotopSkim.h"
#include "Selection/interface/MonotopMCinfo.h"

// Baby Tuple format definition
#include "ProofFormat.h"

#define SELECTION_TYPE MyMonotopSkim

class ProofJob : public TSelector 
{

 public :
  
  TTree* fChain;
  TBranch* branch;
  IPHCTree::NTEvent* event;
  TFile            *fFile;
  TProofOutputFile *fProofFile; 
  AnalysisEnvironmentLoader* anaEL; 
  PUWeighting* LumiWeights; 
  vector<Dataset> datasets;
  Dataset* dataset;
  vector<string> CutName;
  vector<string> ChannelName;
  vector<string> VecChannelName;
  float Luminosity;
  int verbosity;
  int DataType;
  TH1D* hCutFlow;

// To stock some infos before and after the quality cuts
  TH1D* hnleptons_beforeCut;
  TH1D* hnleptons_afterCut;
  TH1D* hnjets_beforeCut;
  TH1D* hnjets_afterCut;
  TH1D* hnBjets_beforeCut;
  TH1D* hnBjets_afterCut;
  TH1D* hMuonIso_beforeCut;
  

  float LumiError ;
  string PUWeightFileName;
  
  string datasetName ;
  
  //------------------------------------
  // Additionnal info for Monotop
  //------------------------------------
  SELECTION_TYPE sel;
  SELECTION_TYPE Void;
  MonotopMCinfo* monotopMCinfo;

  TTree* theTree;
  TTree* theCutFlowTree;

  babyEvent  myEvent;
  CutFlows   myCutFlowEvent;

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

  virtual void InitializeBranches(TTree* theTree, TTree* theCutFlowTree, babyEvent* pointerToEvent, CutFlows* pointerToCutFlowEvent);
  virtual void LoadCorrectionFiles();
  
  ClassDef(ProofJob,0);
};



#endif
