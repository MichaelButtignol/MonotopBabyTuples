// C++ headers
#include <iomanip>
#include <iostream>
#include <time.h>
using namespace std;

// ROOT headers
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>

// IPHC headers
#include "NTFormat/interface/NTEvent.h"
using namespace IPHCTree;
#include "MyMonotopSkim.cc"
#include "Tools/interface/Dataset.h"
#include "Tools/interface/AnalysisEnvironmentLoader.h"

#include "common.h"

// #########################################################################""
// #########################################################################""
// #########################################################################""

int main (int argc, char *argv[])
{
  
  printBoxedMessage("Starting test");

  // ############################
  // #  Initializing variables  #
  // ############################

  string xmlFileName("MyConfig.xml");
  int verbosity = 3;
  vector < Dataset > datasets;
  MyMonotopSkim sel;
  IPHCTree::NTEvent * event = 0;
  
  // #############################
  // #   Loading configuration   #
  // #############################

  cout << endl;
  INFO_MSG << "Loading configuration..." << endl;
  cout << "        (config : " << xmlFileName << ")" << endl;
  
  AnalysisEnvironmentLoader anaEL (xmlFileName);
  anaEL.LoadSamples (datasets); // now the list of datasets written in the xml file is known
  anaEL.LoadSelection (sel);    // now the parameters for the selection are given to the selection // no specific TTbarMET parameters


  // ####################################
  // #   Start loop over the datasets   #
  // ####################################

  if (verbosity > 0) printBoxedMessage("Starting loop over datasets");

  for (unsigned int datasetId = 0; datasetId < datasets.size (); datasetId++) 
  {

    // ########################
    // #   Load the dataset   #
    // ########################
   
    INFO_MSG << "Loading next dataset..." << endl;

    datasets[datasetId].eventTree()->SetBranchAddress ("NTEvent", &event);

    if (verbosity > 2)
    {
        cout << endl;
        cout << "         [ Dataset n°" << datasetId+1 << " ]" << endl;
        cout << "         " << datasets[datasetId].Name() << endl;
        cout << endl;
        INFO_MSG << "   NEvents total    : " << static_cast<unsigned int>(datasets[datasetId].eventTree()->GetEntries ()) << endl;
        INFO_MSG << "NEvents to run over : " << datasets[datasetId].NofEvtsToRunOver() << endl;
        cout << endl;
    }
    
    bool runningOnData = datasets[datasetId].isData();

    // ############################
    // #   Loop over the events   #
    // ############################
              
    if (verbosity > 0) printBoxedMessage("Starting loop over events");

    for (int ievt = 0; ievt < datasets[datasetId].NofEvtsToRunOver(); ievt++)
    {

        if (ievt % 10 == 0) printProgressBar(ievt,datasets[datasetId].NofEvtsToRunOver());

        // Load the event

        datasets[datasetId].eventTree()->GetEntry(ievt);
        IPHCTree::NTTransient::InitializeAfterReading(event);
        int eventId = event->general.eventNb;
        sel.LoadEvent(event);

        cout    << "run   = " << event->general.runNb
             << " ; lumi  = " << event->general.lumiblock
             << " ; event = " << event->general.eventNb << endl;

        // Apply selection
        if (sel.passEventSelection(runningOnData) == false) continue;

        TLorentzVector selectedLepton      = sel.getTheSelectedLepton();
        Short_t        selectedLeptonPDGId = sel.getTheSelectedLeptonPDGId();       

    }   // End event loop
  }     // End dataset loop


  printBoxedMessage("Program completed");
  return (0);
}
