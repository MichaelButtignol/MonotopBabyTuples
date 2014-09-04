
//////////////////////////////////////////////////////////
//
// Example of TSelector implementation to do a Monte Carlo
// generation using Pythia8.
// See tutorials/proof/runProof.C, option "pythia8", for an
// example of how to run this selector.
//
//////////////////////////////////////////////////////////

#ifndef ProofSelectorMyCutFlow_h
#define ProofSelectorMyCutFlow_h

#include <TSelector.h>
#include <TTree.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TRandom.h>

#include "NTFormat/interface/NTEvent.h"
#include "Plots/interface/HistoManager.h"



#include "Tools/interface/Dataset.h"
#include "Tools/interface/AnalysisEnvironmentLoader.h"
#include "Selection/interface/DiLeptonSelection.h"
#include "Plots/interface/DiLepAnaHistoManager.h"
#include "Tools/interface/PUWeighting.h"
#include "Tools/interface/LumiReweightingStandAlone.h"
#include "Tools/interface/JetCorrector.h"
#include "Tools/interface/BtagHardcodedConditions.h"


#include "Tools/interface/PDFReweighter.h"
#include "Tools/interface/PUWeighting.h"


#include "JetCorrections/interface/JetCorrectionUncertainty.h"


#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1.h>
#include <TH2.h> 
#include <TH3.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TLorentzVector.h>
//#include <iostream>

class TH1F;
class TBranch;
class TTree;

class AnalysisEnvironmentLoader;
class DiLeptonSelection;

class ProofSelectorMyCutFlow : public TSelector {
 public :
  
  // Specific members
  //Access to the tree and outputs
  TTree* fChain;
  TBranch* branch;
  IPHCTree::NTEvent* event;
  TFile            *fFile;
  TProofOutputFile *fProofFile; // For optimized merging of the ntuple
  //Pointer on results from xml file  reading
  AnalysisEnvironmentLoader* anaEL; 
  //Minimimal info
  vector<Dataset> datasets;
  Dataset* dataset;
  vector<string> CutName;
  vector<string> TheChannelName;
  vector<string> VecChannelName;
  DiLeptonSelection sel; 
  float Luminosity;
  int verbosity;
  // 0: MC - 1: Data - 2 Data & MC
  int DataType;
  //Info analysis macro specific 
  
  
  int nselevents_mumumu;
  
  string datasetName ;
  //------------------------------------
  //For JES uncerainties
  //------------------------------------
  
  JetCorrectionUncertainty *theJESuncertainty;
  bool  doJESuncert;
  bool  upOrDown;
  bool  applyJES;
  bool  applyJER;
  float ResFactor;
  
  //------------------------------------
  //For PU reweighting
  //------------------------------------
  PUWeighting *LumiWeights;
  float LumiError ;
  string PUWeightFileName;
  bool IReweight;
  bool IReweight_puUp  ;
  bool IReweight_puDown;
  bool IReweight_pu;
  
   
   
  //------------------------------------
  //For PDF reweighting
  //------------------------------------
  bool doPDF ;
  int pdftype ;
  PDFReweighter pdf; 
  
 
  //------------------------------------
  //Definition of the various histograms
  //------------------------------------
  HistoManager MyhistoManager;
  int ITypeMC ;
  bool isTTbarMCatNLO;
    
  //------------------------------------
  //loose isolation on W cand
  //for background estimations
  //------------------------------------
  bool useNonIsoWcand;
  float looseIso;
  float themetcut;
   
  //------------------------------------
  //tight isolation on W cand
  //------------------------------------
  float tightIso_e;
  float tightIso_mu;
  
  
  //------------------------------------
  //Trigger scale factors
  //------------------------------------
  
  bool applyTrigger ;
  bool applyTriggerUp ;
  bool applyTriggerDown ;
  
  //------------------------------------
  //Lepton scale factors
  //------------------------------------
  
  bool applyLeptonSF;
  bool applyLeptonSFUp;
  bool applyLeptonSFDown;
  
  
  //------------------------------------
  //background scale factors
  //------------------------------------
  bool applyFakescale ;
  std::vector <double > SF_Fake;
  
  
  
  std::vector<TH1F> CutFlow_mujets;
  std::vector<TH1F> ErrCutFlow_mujets;
  
  
  
  //------------------------------------
  //definition of member functions
  //------------------------------------
  ProofSelectorMyCutFlow();
  virtual ~ProofSelectorMyCutFlow();
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
  
  ClassDef(ProofSelectorMyCutFlow,0);
  
  //to determine the MC event weight
  std::vector< double > determineWeights(TString, double , double);
  
  void createTheHisto(HistoManager *thehistomanag);
  void WriteTheHisto(TFile* theoutputfile, HistoManager *thehistomanag);
  void cleanHistoVector();
  
  
  
};

#endif
