#ifndef ProofBabyTupler_h
#define ProofBabyTupler_h

// C headers
#include <iostream>
#include <string>
using namespace std;

// ROOT headers
#include <TApplication.h>
#include <TGClient.h>
#include <TProof.h>
#include <TEnv.h>
#include <TChain.h>
#include <TFileCollection.h>
#include <TDrawFeedback.h>

// IPHC headers
#include "Tools/interface/Dataset.h"
#include "Tools/interface/AnalysisEnvironmentLoader.h"

// ###################
// Proof configuration
// ###################

// Number of nodes to be used
#define NUMBER_OF_NODES 12 

// Name of the macro to be run
#define MACRO_NAME "ProofJob.C+"

// XML configuration to load
#define XML_CONFIG "macros/Monotop/babyTupleProduction/MyConfig.xml"

// Sandbox for PROOF
// NB : the content of this folder will be deleted each time you launch proof !
#define OUTPUT_BOX "/opt/sbg/data/data1/cms/mbuttign/proofBox/"

// Name for the final output
#define OUTPUT_NAME "proof.root"

#endif
