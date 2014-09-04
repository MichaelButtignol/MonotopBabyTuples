#include <TApplication.h>
#include <TGClient.h>
#include <TProof.h>
#include <TChain.h>
#include <TFileCollection.h>
#include <TDrawFeedback.h>

#include "../../Tools/interface/Dataset.h"
#include "../../Tools/interface/AnalysisEnvironmentLoader.h"

using namespace std;


int main(int argc, char* argv[])
{
  
  //This line could be commented if you don't want display while running, by example using screen.
  //TApplication theApp("App",&argc,argv);
  
  //---------------------------------------//
  // Global variables: could be give as argument later
  //---------------------------------------//
  
  int nwnodes = 1; //8 to 10 is the optimal
  string macroName = "ProofSelectorMyCutFlow.C+"; //"+" should be put at the end to use ACLIC complication - This macro should inherit from TSelector 
  //In order to allow the node to access the xml, the name should be given with the full path
  string xmlFileName = getenv( "CMSSW_BASE" )+string("/src/IPHCAnalysis/NTuple/Monotop/MyConfig.xml");
  
  string outputFileName = "proof_test.root";
  
  //---------------------------------------//
  //	Declaration of TProof
  //---------------------------------------//
  
  //to be done before calling TProof
  system("../GeneralExamples/./clean_proof.sh ; echo 'Wait few seconds ... ' ; sleep 6");
  system("rm -r $HOME/.proof");
  
  TProof *proof = TProof::Open("");
  proof->SetParallel(nwnodes); 
  //you should not have any package yet
  proof->ShowPackages();
  //proof->ClearPackages();
  //Loading package related to NTupleAnalysis
  cout<<" ## Upload package NTAna.par: ";
  proof->UploadPackage("../NTAna.par");
  cout<<" DONE [don't worry with symlink error - do rm NTAna if you change NTAna.par in the meanwhile !] "<<endl;
  proof->EnablePackage("NTAna");
  //Adding histograms for feedback: must exist in the TSelector !
  //proof->AddFeedback("fHist"); //give the "name" of the histogram and not the name of the variable TH1F* (could be the same !)
  
  //This line is required to display histograms during the process
  //TDrawFeedback fb(proof);
  
  
  //---------------------------------------//
  // Xml Loading  & Dataset registration
  //---------------------------------------//
  
  vector < Dataset > datasets;
  AnalysisEnvironmentLoader anaEL (xmlFileName);
  anaEL.LoadSamples (datasets); // now the list of datasets written in the xml file is known
  
  cout << " #------------------------------------# " << endl;
  cout << " PROOF DATASETS SUMMARY [normaly 0]" << endl;
  proof->ShowDataSets();
  cout << " #------------------------------------# " << endl;
  cout << " # Registring dataset ... " << endl;
  cout << " Don't be worry with the checksum error message [at least I'm not ;-) ]" << endl;
  cout << " #------------------------------------# " << endl;
  //Create datasets in proof format
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
  
  //summarize the list of datasets
  cout << " #------------------------------------# " << endl;
  cout << " PROOF DATASETS SUMMARY" << endl;
  proof->ShowDataSets();
  cout << " #------------------------------------# " << endl;
  
  //---------------------------------------//
  // 	Processing of the datasets
  //---------------------------------------//
  
  string outputFileNameModif = outputFileName.substr(0,outputFileName.size()-5);
  //string MergingCommand = "hadd "+outputFileNameModif+"_merged.root "+outputFileNameModif+"_*.root  ";


  
  
  // ####################################
  // #   Start loop over the datasets   #
  // ####################################  


  for(unsigned int i=0;i<datasets.size();i++)
  {
    //---------------------------------------//
    // 	Loading of the xml file
    //---------------------------------------//
    //Possibility to give float ... ex:
    //Double_t f = 3.14;
    //proof->SetParameter("IN_FLOAT",f);
    string outputnameSample = "proof_"+datasets[i].Name();
    
    proof->AddInput(new TNamed("PROOF_DATASETNAME", datasets[i].Name()));   
    proof->AddInput(new TNamed("PROOF_XMLFILENAME", xmlFileName));
    //proof->AddInput(new TNamed("PROOF_OUTPUTFILE", outputFileName));
    proof->AddInput(new TNamed("PROOF_OUTPUTFILE", outputnameSample));
    
    cout << "#------------------------------------# " << endl;
    cout << "PROOF PARAMETERS SUMMARY" << endl;
    proof->ShowParameters();
    cout << "#------------------------------------# " << endl;
    
    
    cout << "################################################################" << endl;
    cout << "########### Processing the dataset " << datasets[i].Name() << endl;
    cout << "################################################################" << endl;


    cout << "start  proof process " << endl;
    proof->Process(datasets[i].Name().c_str(),macroName.c_str());
    string newFileName = outputFileNameModif+"_"+datasets[i].Name()+".root";
    system("sleep 10");

    proof->ClearInput();
    //system("sleep 10");
    
    
  }
  
  //cout<<"## Merging of all the dataset into one single file with hadd: "<<outputFileName<<endl;
  //system(MergingCommand.c_str());
  cout << "start backuping proof root files " << endl;
  system("mkdir backup_outputProof`date +\"%d-%m-%y_%H-%M\"`;mv proof*.root  backup_outputProof`date +\"%d-%m-%y_%H-%M\"`/.");
  
  cout << "###############################################################" << endl;
  cout << "################ 	   May your job 	##############" << endl;
  cout << "################      Live long and prosper	##############" << endl;
  cout << "###############################################################" << endl;
  cout << "  							      " << endl;
  cout << "  			     _  			      " << endl;
  cout << "  			  .-T |   _			      " << endl;
  cout << "  			  | | |  / |			      " << endl;
  cout << "  			  | | | / /`|			      " << endl;
  cout << "  		       _  | | |/ / /			      " << endl;
  cout << "  		       \\`\\| \'.\' / / 		      " << endl;
  cout << "  			\\ \\`-. \'--|  		      " << endl;
  cout << "  			 \\    \'   |			      " << endl;
  cout << "  			  \\ \\  .` /			      " << endl;
  cout << "  			    |	 |			      " << endl;
  cout << "  							      " << endl;
  cout << "  							      " << endl;
  cout << "###############################################################"<<endl;
  cout << "###############################################################"<<endl;
  
  
  
  //delete proof; 
  
  for(unsigned int i=0;i<datasets.size();i++)
  {
  	delete fileCollec[i];
  }

  delete fileCollec;
  
  
  return (0);
  
}



