
#include <TSelector.h>

#include "ProofLauncher.h"

void printBoxedMessage(string message);

int main(int argc, char* argv[])
{
  
  printBoxedMessage("Launching PROOF");

  // #######################################
  // #   Cleaning existing/previous jobs   #
  // #######################################
 
  cout << "  > Cleaning existing workers..." << endl << endl;
  system("pkill -9 proofserv.exe 2>/dev/null");
  system("sleep 1");
  cout << "  > Cleaning proof box ..." << endl << endl;
  system((string("rm -r ")+OUTPUT_BOX).c_str());  

  // ################################################
  // #   Setting up proofbox and cCreating workers  #
  // ################################################
  
  gEnv->SetValue("ProofLite.Sandbox",OUTPUT_BOX);
  
  cout << "  > Starting PROOF with " << NUMBER_OF_NODES << " workers " << endl << endl;
  TProof *proof = TProof::Open("");
  proof->SetParallel(NUMBER_OF_NODES);

  // Set the feedback period to 5 seconds
  proof->SetParameter("PROOF_FeedbackPeriod", (Long_t) 5000);

  // #####################
  // #   Load packages   #
  // #####################
 
  cout << "  > Loading NTuple Analysis package (don't worry about the symlink error)" << endl;
  proof->UploadPackage("/opt/sbg/data/data1/cms/mbuttign/THESE/Monotop/Analysis/CMSSW_5_3_11/src/IPHCAnalysis/NTuple/macros/NTAna.par");
  proof->EnablePackage("NTAna");
  
  // ##############################
  // #   Load XML configuration   #
  // ##############################
  
  string xmlFileName = string("/opt/sbg/data/data1/cms/mbuttign/THESE/Monotop/Analysis/CMSSW_5_3_11/src/IPHCAnalysis/NTuple/")+XML_CONFIG;
  AnalysisEnvironmentLoader anaEL(xmlFileName);
  
  vector<Dataset> datasets;
  anaEL.LoadSamples(datasets);
 
  // #######################################
  // #   Create datasets in proof format   #
  // #######################################

  TFileCollection** fileCollec = new TFileCollection*[datasets.size()];
  for(unsigned int i=0;i<datasets.size();i++)
  {
    fileCollec[i]  = new TFileCollection(datasets[i].Name().c_str(),"");
    for(unsigned int j=0;j<datasets[i].Filenames().size();j++)
    {
      fileCollec[i]->Add(datasets[i].Filenames()[j].c_str());
    }

    //register dataset in proof
    proof->RegisterDataSet(datasets[i].Name().c_str(),fileCollec[i]);
    proof->VerifyDataSet(datasets[i].Name().c_str());
    proof->SetDataSetTreeName( datasets[i].Name().c_str(), "MyModule/Event");
  }

  // ############################
  // #   Process the datasets   #
  // ############################
  
  string macroName = MACRO_NAME;
  system("mkdir -p proofOutput");
  
  for(unsigned int i=0;i<datasets.size();i++)
  {
      printBoxedMessage("Processing "+datasets[i].Name());

      proof->AddInput(new TNamed("PROOF_DATASETNAME", datasets[i].Name()));
      proof->AddInput(new TNamed("PROOF_XMLFILENAME", xmlFileName));
      proof->AddInput(new TNamed("PROOF_OUTPUTFILE",  "output.root"));
      proof->Process(datasets[i].Name().c_str(),macroName.c_str(),"",datasets[i].NofEvtsToRunOver());
      system("sleep 5");

      string newFileName = "proofOutput/"+datasets[i].Name()+".root";
      cout << "  > Moving output to " << newFileName << endl;
      string command = "mv output.root "+newFileName;
      system(command.c_str());
      proof->ClearInput();
  }
 
  // ##################
  // #   Show stats   #
  // ##################
 
  printBoxedMessage("Job done, here are a few stats");

  proof->Print();
    
  printBoxedMessage("May your job live long and prosper");
  cout << "                                                 " << endl;
  cout << "                   _                             " << endl;
  cout << "                .-T |   _                        " << endl;
  cout << "                | | |  / |                       " << endl;
  cout << "                | | | / /`|                      " << endl;
  cout << "             _  | | |/ / /                       " << endl;
  cout << "             \\`\\| \'.\' / /                    " << endl;
  cout << "              \\ \\`-. \'--|                     " << endl;
  cout << "               \\    \'   |                      " << endl;
  cout << "                \\ \\  .` /                      " << endl;
  cout << "                  |     |                        " << endl;
  cout << "                                                 " << endl;
  cout << "                                                 " << endl;
  
  return (0);
}

void printBoxedMessage(string message)
{
    cout << endl;

    cout << "   ┌──";
    for(unsigned int i = 0 ; i <= message.size() ; i++) cout << "─";
    cout << "─┐  " << endl;

    cout << "   │  " << message << "  │  " << endl;
    
    cout << "   └──";
    for(unsigned int i = 0 ; i <= message.size() ; i++) cout << "─";
    cout << "─┘  " << endl; 
 
    cout << endl;

}
