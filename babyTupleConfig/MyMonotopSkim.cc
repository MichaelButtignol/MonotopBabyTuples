#include "Selection/interface/MyMonotopSkim.h"
using namespace std;

#define DEBUG_MSG std::cout << "DEBUG (" << __FILE__ << ", l." << __LINE__ << ") "

// ----------------------------------------------------------------------------
// Default constructor
// ----------------------------------------------------------------------------

MyMonotopSkim::MyMonotopSkim ()
{
}

//void MyMonotopSkim::setBTagReshapingInput(string fileName)       { bTagReshapingInput      = fileName; }          
//void MyMonotopSkim::setMCJetCorrectionsInput(string fileName)    { jetCorrectionsMCInput   = fileName; }
//void MyMonotopSkim::setDataJetCorrectionsInput(string fileName)  { jetCorrectionsDataInput = fileName; }
void MyMonotopSkim::setPileUpReweightingInput(string fileName)        { pileUpReweightingInput  = fileName; }
void MyMonotopSkim::setPileUpReweightingInput_IPHC(string fileName)   { pileUpReweightingInput_IPHC  = fileName; }

void MyMonotopSkim::loadCorrections()
{
    // Load bTagReshaping input

//    BTagReshape_nominal   = new BTagShapeInterface(bTagReshapingInput, 0.0, 0.0);
//    BTagReshape_upBC      = new BTagShapeInterface(bTagReshapingInput, 1.0, 0.0);
//    BTagReshape_downBC    = new BTagShapeInterface(bTagReshapingInput,-1.0, 0.0);
//    BTagReshape_upLight   = new BTagShapeInterface(bTagReshapingInput, 0.0, 1.0);
//    BTagReshape_downLight = new BTagShapeInterface(bTagReshapingInput, 0.0,-1.0);

    // Load JEC/JES stuff

//    JESUncertainty_MC     = new JetCorrectionUncertainty(jetCorrectionsMCInput);
//    JESUncertainty_Data   = new JetCorrectionUncertainty(jetCorrectionsDataInput);

    // Load pile-up stuff

    TFile* pileUpReweightingFile = TFile::Open(pileUpReweightingInput.c_str());
    pileUpReweightingHisto = (TH1F*) pileUpReweightingFile->Get("puWeights");
    pileUpReweightingHisto->SetName("h_pu_wgt");

    TFile* pileUpReweightingFile_IPHC = TFile::Open(pileUpReweightingInput_IPHC.c_str());
    pileUpReweightingHisto_IPHC = (TH1D*) pileUpReweightingFile_IPHC->Get("pileup");

    PUWeights = new PUWeighting;
    PUWeights->initPUSummer12_S10(pileUpReweightingHisto_IPHC);
}

void MyMonotopSkim::doObjectSelection(bool runningOnData, short int JESvariation)
{

    // Clear selected object collections

    rawElectrons.clear();
    selectedElectrons.clear();
    selectedLooseElectrons.clear();

    rawMuons.clear();
    selectedMuons.clear();
    selectedLooseMuons.clear();

    rawJets.clear();
    selectedJets.clear();
    selectedBJets.clear();


    // Raw / good objects

    rawElectrons      = *GetPointer2Electrons();
    rawMuons          = *GetPointer2Muons();
    rawJets           = *GetPointer2Jets();
    rawMET            = *GetPointer2MET();
    theMET            = TLorentzVector(rawMET.p2.Px(),rawMET.p2.Py(),0.,rawMET.p2.Mod());

    // JES variations if asked

   // if (JESvariation ==  1) ApplyJESVariation(runningOnData,true);
   // if (JESvariation == -1) ApplyJESVariation(runningOnData,false);

    // Selected objects

    selectedLooseMuons     = doMonotopLooseMuonsSelection( true );
    selectedMuons          = doMonotopMuonsSelection( true );
    selectedLooseElectrons = doMonotopLooseElectronsSelection();
    selectedElectrons      = doMonotopElectronsSelection();
    selectedJets           = doMonotopJetsSelection (runningOnData);
    selectedBJets          = doMonotopBJetsSelection(runningOnData);

}

short int MyMonotopSkim::passEventSelection(bool runningOnData, string datasetName)
{


    // #####################
    // #  Object selection #
    // #####################

    doObjectSelection(runningOnData);

    // ##########################
    // #  Step 1        Trigger #
    // ##########################

    short int passCuts = 0;

    bool trigger_singleElec = passTrigger("singleElec");
    bool trigger_singleMuon = passTrigger("singleMuon");
    bool trigger_leptonBtag = passTrigger("leptonBtag");
    if (trigger_singleMuon)
        // if ((trigger_singleElec || trigger_singleMuon))
        //if (runningOnData == false)
    {
        passCuts = 1;

        // ######################
        // #  Step 2   1 Lepton #
        // ######################
        //cout << "Number of electrons= " << selectedElectrons.size() << " and Number of muons= " << selectedMuons.size() << endl;
        //if (selectedLooseMuons.size() == 1 && selectedLooseElectrons.size() == 0 && selectedMuons.size() == 1)
        if (selectedMuons.size() == 1)
        {
            passCuts = 2;

            numberOfSelectedLeptons = selectedMuons.size() + selectedElectrons.size();
            // ################################
            // #  Step 3     At least 1 Jet   #
            // ################################

            //if (selectedJets.size() >= 1 && getLeadingJet().Pt() < 70)
            //if (selectedJets.size() >= 1)
            //{
                passCuts = 3;
                // ########################
                // #  Step 3     1 BJet   #
                // ########################
                //if (rawMET.p2.Mod() > 20)        
                //if (selectedBJets.size() == 1) 
                //{
                        passCuts = 4;
                        FillKinematicP4();
                //}
            //} 
        } 
   } 
   
  return passCuts;

}


void MyMonotopSkim::FillKinematicP4()
{

    selectedLepton_pdgid=-9999;

    // 1. The Lepton
    if (selectedMuons.size() == 1 &&  selectedLooseMuons.size() == 1 && selectedLooseElectrons.size() == 0)
    {
        selectedLepton       = selectedMuons[0].p4;
        selectedLepton_pdgid = selectedMuons[0].charge * (-13);
        cout << "Selected_muon_pT= " << selectedLepton.Pt() << endl;
        cout << "Selected_muon_pdgid= " << selectedLepton_pdgid << endl;
    }
    else if (selectedLooseMuons.size() == 0 && selectedLooseElectrons.size() == 1 && selectedElectrons.size() == 1)
    {
        selectedLepton       = selectedElectrons[0].p4;
        selectedLepton_pdgid = selectedElectrons[0].charge * (-11);
        cout << "Selected_electron_pT= " << selectedLepton.Pt() << endl;
        cout << "Selected_electron_pdgid= " << selectedLepton_pdgid << endl;
    }
    else 
    {
         DEBUG_MSG << "There is a problem with the selected lepton!" << endl;
         DEBUG_MSG << "There is: " << selectedMuons.size() << " muons on " << selectedLooseMuons.size() << "loose muons" << endl;
         DEBUG_MSG << "There is: " << selectedElectrons.size() << " electrons on " << selectedLooseElectrons.size() << "loose electrons" << endl;
    }

}

// ############################################
// #   _____    _                             #
// #  |_   _|  (_)                            #
// #    | |_ __ _  __ _  __ _  ___ _ __ ___   #
// #    | | '__| |/ _` |/ _` |/ _ \ '__/ __|  #
// #    | | |  | | (_| | (_| |  __/ |  \__ \  #
// #    \_/_|  |_|\__, |\__, |\___|_|  |___/  #
// #               __/ | __/ |                #
// #              |___/ |___/                 #
// #                                          #
// ############################################

bool MyMonotopSkim::passTrigger(string channel)
{
    vector<string> path;

    if (channel == "singleMuon") 
    { 
        //path.push_back("HLT Mu15 eta2p1_v*");
        //path.push_back("HLT_IsoMu24_v*"); 
        path.push_back("HLT_IsoMu24_eta2p1_v*"); 
    }
    if (channel == "singleElec") 
    { 
        //path.push_back("HLT Ele22 CaloIdL CaloIsoVL_v*");
        path.push_back("HLT_Ele27_WP80_v*"); 
    }
    if (channel == "leptonBtag") 
    { 
        path.push_back("HLT_IsoMu17_eta2p1_CentralPFNoPUJet30_BTagIPIter_v1");//Muon + Btag
        //path.push_back("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFNoPUJet30_BTagIPIter_v6");//Electron+Btag 
    }
    
    for (unsigned int i = 0 ; i < path.size() ; i++)
    {
        if (checkPathHasBeenFired(path[i])) return true;
    }

    return false;

}

bool MyMonotopSkim::checkPathHasBeenFired(string path)
{
    std::vector<IPHCTree::NTTriggerPathType> myPaths;
    GetPointer2Trigger()->GetSubTable(path.c_str(),myPaths);
    for (unsigned int i=0;i<myPaths.size();i++) 
    {
        if (myPaths[i].fired==1) 
        {
            if (myPaths[i].prescale>1) cout << " warning TRIGGER " << myPaths[i].name 
                << " is PRESCALED with a factor " << myPaths[i].prescale 
                    << endl;

            return true;
        }
    }

    return false;

}

// ######################################################################################################
// #   _____      _           _           _   _                                                          #
// #  /  ___|    | |         | |         | | | |                                                        #
// #  \ `--.  ___| | ___  ___| |_ ___  __| | | | ___  ___  ___  ___   _ __ ___  _   _  ___  _ __  ___  # 
// #   `--. \/ _ \ |/ _ \/ __| __/ _ \/ _` | | || _ || _ |/ __|/ _ \ | '_ ` _ \| | | |/ _ \| '_ \/ __| #
// #  /\__/ /  __/ |  __/ (__| ||  __/ (_| | | |||_||||_||\__ \  __/ | | | | | | |_| | (_) | | | \__ \ #
// #  \____/ \___|_|\___|\___|\__\___|\__,_| |_||___||___||___/\___| |_| |_| |_|\__,_|\___/|_| |_|___/ # 
// #                                                                                                    #
// ######################################################################################################

std::vector<IPHCTree::NTMuon> MyMonotopSkim::doMonotopLooseMuonsSelection( bool doCutOnIsolation = true ) const
{
    // Container for output
    std::vector<IPHCTree::NTMuon> outputVector;

    // Get electrons
    std::vector<IPHCTree::NTMuon> muons = rawMuons;

    // Loop over muons
    for(unsigned int i=0;i<muons.size();i++)
    {
        if (!muons[i].isPFMuon)                                             continue;
        if (!(muons[i].isTrackerMuon || muons[i].isGlobalMuon))             continue;
        if (fabs(muons[i].p4.Eta()) > 2.5 )                                 continue;
        if (muons[i].p4.Pt() < 10)                                          continue;
        //if (static_cast<double>(RelIso04PFDeltaBeta(muons[i])) >= 0.2)    continue;
        if(doCutOnIsolation)
        {
                if (getMuonIsolation(muons[i]) >= 0.2)                      continue;
        }
              outputVector.push_back(muons[i]);
    }
    
    std::sort(outputVector.begin(),outputVector.end(),HighestPt());
    return outputVector;
}



// ##############################################################################
// #   _____      _           _           _                                     #
// #  /  ___|    | |         | |         | |                                    #
// #  \ `--.  ___| | ___  ___| |_ ___  __| |  _ __ ___  _   _  ___  _ __  ___   #
// #   `--. \/ _ \ |/ _ \/ __| __/ _ \/ _` | | '_ ` _ \| | | |/ _ \| '_ \/ __|  #
// #  /\__/ /  __/ |  __/ (__| ||  __/ (_| | | | | | | | |_| | (_) | | | \__ \  #
// #  \____/ \___|_|\___|\___|\__\___|\__,_| |_| |_| |_|\__,_|\___/|_| |_|___/  #
// #                                                                            # 
// ##############################################################################

std::vector<IPHCTree::NTMuon> MyMonotopSkim::doMonotopMuonsSelection( bool doCutOnIsolation = true ) const
{

    // Container for output
    std::vector<IPHCTree::NTMuon> outputVector;

    // Get muons
    std::vector<IPHCTree::NTMuon> muons = selectedLooseMuons;

    // Loop over muons
    for(unsigned int i=0;i<muons.size();i++)
    {

        // Requirements
        //if (!muons[i].isPFMuon)                                   continue;
        //if (!muons[i].isTrackerMuon)                              continue;
        if (!muons[i].isGlobalMuon)                                 continue;
        if (muons[i].p4.Pt()  < 26)                                 continue;
        if (muons[i].p4.Eta() > 2.1)                                continue;
        if (doCutOnIsolation)
        {
                if (getMuonIsolation(muons[i]) >= 0.12)             continue;
        }
        if (muons[i].Chi2 > 10 || muons[i].Chi2 < 0)                continue;
        if (muons[i].NValidHits <= 0)                               continue;
        if (muons[i].numMatchedStations <= 1)                       continue;   
        if (muons[i].pixelHits <= 0)                                continue;
        if (muons[i].numTrackerLayersWithMeasurement <= 5)          continue;
        if (muons[i].dxy_vertex >= 0.2)                             continue;
        if (muons[i].dz_vertex >= 0.5)                              continue;
        if (fabs(muons[i].D0Inner)  >= 0.02)                        continue;
        
        //if (static_cast<double>(RelIso04PFDeltaBeta(muons[i])) >0.12)        continue;
        // SelectedVertex is not coded yet. See Selection.cc 'GetSelectedVertex'.
        //if (fabs(muons[i].vertex.Z() - GetSelectedVertex()[0].p3.Z() ) >= 0.5 ) continue;

        outputVector.push_back(muons[i]);
    }

    std::sort(outputVector.begin(),outputVector.end(),HighestPt());
    return outputVector;
}

float MyMonotopSkim::getMuonIsolation(IPHCTree::NTMuon &muon) const
{
        float pfIsoCharged = muon.isolation["PF03Char"];
        float pfIsoNeutral = muon.isolation["PF03Neut"];
        float pfIsoPhoton  = muon.isolation["PF03Phot"];
        float pfIsoPU      = muon.isolation["PF03PU"];

        float relIso =  ( pfIsoCharged + max((float) 0.0,(float) (pfIsoNeutral + pfIsoPhoton- 0.5*pfIsoPU )) ) / muon.p4.Pt();        
        return relIso;
}


// ###############################################################################################################
// #   _____      _           _           _   _                             _           _                         #
// #  /  ___|    | |         | |         | | | |                          | |         | |                        #
// #  \ `--.  ___| | ___  ___| |_ ___  __| | | | ___  ___  ___  ___    ___| | ___  ___| |_ _ __ ___  _ __  ___   #
// #   `--. \/ _ \ |/ _ \/ __| __/ _ \/ _` | | || _ || _ |/ __|/ _ \  / _ \ |/ _ \/ __| __| '__/ _ \| '_ \/ __|  #
// #  /\__/ /  __/ |  __/ (__| ||  __/ (_| | | |||_||||_||\__ \  __/ |  __/ |  __/ (__| |_| | | (_) | | | \__ \  #
// #  \____/ \___|_|\___|\___|\__\___|\__,_| |_||___||___||___/\___|  \___|_|\___|\___|\__|_|  \___/|_| |_|___/  #
// #                                                                                                              #
// ###############################################################################################################

std::vector<IPHCTree::NTElectron> MyMonotopSkim::doMonotopLooseElectronsSelection() const
{
    // Container for output
    std::vector<IPHCTree::NTElectron> outputVector;

    // Get electrons
    std::vector<IPHCTree::NTElectron> electrons = rawElectrons;

    // Loop over electrons
    for(unsigned int i=0;i<electrons.size();i++)
    {
        if (!electrons[i].isGsfElectron)                                      continue; //when using before 5_3_X
        if (fabs(electrons[i].p4.Eta()) > 2.5 )                         continue;
        if (electrons[i].p4.Pt() < 20)                                        continue;
        if (electrons[i].ID["mvaTrigV0"] < 0.0)                                continue; 
        if (electrons[i].ID["mvaTrigV0"] > 1.0)                                continue; 
        if (static_cast<double>(RelIso03PF(electrons[i])) >= 0.15)        continue;
        
        //float chargedIso  = electrons[i].isolation["RA3Charg"];
        //float photonIso   = electrons[i].isolation["RA3Photo"];
        //float neutralIso  = electrons[i].isolation["RA3Neutr"];
        //float rho_relIso  = electrons[i].isolation["rho"];
        //float Aeff_relIso = electrons[i].isolation["Aeff"];
        //float relIso = (chargedIso + max((float) 0.0, (float) (photonIso + neutralIso - rho_relIso * Aeff_relIso)))/electrons[i].p4.Pt();
            
        //if (relIso >= 0.15)                                 continue;

              outputVector.push_back(electrons[i]);
    }
    
    std::sort(outputVector.begin(),outputVector.end(),HighestPt());
    return outputVector;
}


// #######################################################################################
// #   _____      _           _           _        _           _                         #
// #  /  ___|    | |         | |         | |      | |         | |                        #
// #  \ `--.  ___| | ___  ___| |_ ___  __| |   ___| | ___  ___| |_ _ __ ___  _ __  ___   #
// #   `--. \/ _ \ |/ _ \/ __| __/ _ \/ _` |  / _ \ |/ _ \/ __| __| '__/ _ \| '_ \/ __|  #
// #  /\__/ /  __/ |  __/ (__| ||  __/ (_| | |  __/ |  __/ (__| |_| | | (_) | | | \__ \  #
// #  \____/ \___|_|\___|\___|\__\___|\__,_|  \___|_|\___|\___|\__|_|  \___/|_| |_|___/  #
// #                                                                                     #
// #######################################################################################
std::vector<IPHCTree::NTElectron> MyMonotopSkim::doMonotopElectronsSelection() const
{
    std::vector<IPHCTree::NTElectron> outputVector;

    std::vector<IPHCTree::NTElectron> electrons = selectedLooseElectrons;

    for(unsigned int i=0;i<electrons.size();i++)
    {

        // Requirements
        //if (!electrons[i].isPFElectron)                                          continue; //because using 5_3_X
        if (!electrons[i].isGsfElectron)                                               continue; //when using before 5_3_X
        if (electrons[i].p4.Pt() < 30)                                                 continue;
        if (electrons[i].p4.Eta() > 2.5)                                         continue;
        //if (fabs(electrons[i].etaSuperCluster) < 1.4442)                         continue; //to exclude EB-EE transition region

        if (fabs(electrons[i].etaSuperCluster) > 1.5660)                         continue; //to exclude EB-EE transition region 
        if (electrons[i].dxy_vertex > 0.02)                                         continue; //transverse IP wrt the first OPV (cm) 


        if (electrons[i].passConversionVeto == false)                                 continue;
        if (electrons[i].ID["mvaTrigV0"] < 0.5)                                        continue; 
        if (electrons[i].missingHits > 0)                                        continue; //to veto photon reco. as electron
        if (static_cast<double>(RelIso03PF(electrons[i])) > 0.1)                continue;
        
        //float chargedIso  = electrons[i].isolation["RA3Charg"];
        //float photonIso   = electrons[i].isolation["RA3Photo"];
        //float neutralIso  = electrons[i].isolation["RA3Neutr"];
        //float rho_relIso  = electrons[i].isolation["rho"];
        //float Aeff_relIso = electrons[i].isolation["Aeff"];
        //float relIso = (chargedIso + max((float) 0.0, (float) (photonIso + neutralIso - rho_relIso * Aeff_relIso)))/electrons[i].p4.Pt();
            
        //if (relIso >= 0.1)                                 continue;
        outputVector.push_back(electrons[i]);
    }

    std::sort(outputVector.begin(),outputVector.end(),HighestPt());
    return outputVector;
}




// ###############################################################
// #   _____      _           _           _     _      _         #
// #  /  ___|    | |         | |         | |   (_)    | |        #
// #  \ `--.  ___| | ___  ___| |_ ___  __| |    _  ___| |_ ___   #
// #   `--. \/ _ \ |/ _ \/ __| __/ _ \/ _` |   | |/ _ \ __/ __|  #
// #  /\__/ /  __/ |  __/ (__| ||  __/ (_| |   | |  __/ |_\__ \  #
// #  \____/ \___|_|\___|\___|\__\___|\__,_|   | |\___|\__|___/  #
// #                                          _/ |               #
// #                                         |__/                #
// ###############################################################

std::vector<IPHCTree::NTJet> MyMonotopSkim::doMonotopJetsSelection(
        int DataType) const
{
    // Container for output
    std::vector<IPHCTree::NTJet> outputVector;

    // Get muons
    std::vector<IPHCTree::NTMuon> muon_cand = selectedLooseMuons;

    // Get electrons
    std::vector<IPHCTree::NTElectron> elec_cand = selectedLooseElectrons;


    for(unsigned int i=0;i<rawJets.size();i++)
    {
        
        // Eta and Pt cuts
        if ((fabs(rawJets[i].p4.Eta()) >= 2.4) || (rawJets[i].p4.Pt()  < 30)) continue;
    
        double deltaRmu = 10000;
        double deltaRel = 10000;

        for(unsigned int imu=0; imu< muon_cand.size(); imu++)
        {
           double deltaR = rawJets[i].p4.DeltaR(muon_cand[imu].p4);
           if(deltaR < deltaRmu) deltaRmu = deltaR;
        }
/*
        for(unsigned int iel=0; iel< elec_cand.size(); iel++)
        {
           double deltaR = rawJets[i].p4.DeltaR(elec_cand[iel].p4Gsf);
           if(deltaR < deltaRel) deltaRel = deltaR;
        }

        if( deltaRmu > 0.5  && deltaRel > 0.5)  outputVector.push_back(rawJets[i]);
*/      if( deltaRmu > 0.5 )  outputVector.push_back(rawJets[i]);

    }


    std::sort(outputVector.begin(),outputVector.end(),HighestPt());
    return outputVector;
}

// #######################################################################
// #   _____      _           _           _     _       _      _         #
// #  /  ___|    | |         | |         | |   | |     (_)    | |        #
// #  \ `--.  ___| | ___  ___| |_ ___  __| |   | |__    _  ___| |_ ___   #
// #   `--. \/ _ \ |/ _ \/ __| __/ _ \/ _` |   | '_ \  | |/ _ \ __/ __|  #
// #  /\__/ /  __/ |  __/ (__| ||  __/ (_| |   | |_) | | |  __/ |_\__ \  #
// #  \____/ \___|_|\___|\___|\__\___|\__,_|   |_.__/  | |\___|\__|___/  #
// #                                                  _/ |               #
// #                                                 |__/                #
// #######################################################################
std::vector<IPHCTree::NTJet> MyMonotopSkim::doMonotopBJetsSelection(
        int DataType) const
{
    std::vector<IPHCTree::NTJet> bJets;

    for (unsigned int j = 0; j < selectedJets.size (); j++)
    {
        // Get discriminant
        float discr;
        discr = selectedJets[j].bTag["combinedSecondaryVertexBJetTags"];

        // Apply CSV medium working point
        //if (discr >= 0.679) bJets.push_back(selectedJets[j]);
        // Apply CSV loose working point
        if (discr >= 0.244) bJets.push_back(selectedJets[j]);
    }

    return bJets;
}
