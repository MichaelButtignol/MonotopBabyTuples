#include "MyMonotopSkim.h"
using namespace std;

#define DEBUG_MSG std::cout << "DEBUG (" << __FILE__ << ", l." << __LINE__ << ") "

// ----------------------------------------------------------------------------
// Default constructor
// ----------------------------------------------------------------------------

MyMonotopSkim::MyMonotopSkim ()
{
}

void MyMonotopSkim::doObjectSelection(bool runningOnData, short int JESvariation)
{

    // Clear selected object collections

    rawElectrons.clear();
    selectedElectrons.clear();

    rawMuons.clear();
    selectedMuons.clear();

    rawJets.clear();
    selectedJets.clear();
    selectedBJets.clear();

    // Raw / good objects

    rawElectrons      = *GetPointer2Electrons();
    rawMuons	      = *GetPointer2Muons();
    rawJets           = *GetPointer2Jets();

    // Selected objects

    selectedMuons     = doMonotopMuonsSelection();
    selectedElectrons = doMonotopElectronsSelection();
    selectedJets      = doMonotopJetsSelection (runningOnData);
    selectedBJets     = doMonotopBJetsSelection(runningOnData);

}

bool MyMonotopSkim::passEventSelection(bool runningOnData)
{

    // #####################
    // #  Object selection #
    // #####################

    doObjectSelection(runningOnData);

    // ##########################
    // #  Step 0        Filters #
    // ##########################

    if ((getRho() < 0.0) || (getRho() > 40.0)) return false;

    // ##########################
    // #  Step 1        Trigger #
    // ##########################

    bool trigger_singleElec = passTrigger("singleElec");
    bool trigger_singleMuon = passTrigger("singleMuon");

    if ( ((runningOnData) && (trigger_singleElec || trigger_singleMuon))|| (!runningOnData) )
    {

        // ######################
        // #  Step 2   1 Lepton #
        // ######################

        if ((selectedElectrons.size() == 1 && selectedMuons.size() == 0) || (selectedElectrons.size() == 0 && selectedMuons.size() == 1))
        {
            numberOfSelectedLeptons = selectedElectrons.size() + selectedMuons.size();

            // ##########################
            // #  Step 3     1 B-jets   #
            // ##########################

            if (selectedBJets.size() == 1) 
            {
                FillKinematicP4();
                return true;
            }
        } 
    } 

    return false;
}


void MyMonotopSkim::FillKinematicP4()
{

    theSelectedLepton_pdgid=-9999;

    // 1. The Lepton
    if (selectedMuons.size() == 1 && selectedElectrons.size() == 0)
    {
	theSelectedLepton       = selectedMuons[0].p4;
	theSelectedLepton_pdgid = selectedMuons[0].charge * (-13);
    }
    else if (selectedMuons.size() == 0 && selectedElectrons.size() == 1)
    {
	theSelectedLepton       = selectedElectrons[0].p4;
	theSelectedLepton_pdgid = selectedElectrons[0].charge * (-11);
    }
    else DEBUG_MSG << "There is a problem with the selected lepton!" << endl;

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
        path.push_back("HLT_IsoMu24_v*"); 
        path.push_back("HLT_IsoMu24_eta2p1_v*"); 
    }
    if (channel == "singleElec") 
    { 
        path.push_back("HLT_Ele27_WP80_v*"); 
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


// ##############################################################################
// #   _____      _           _           _                                     #
// #  /  ___|    | |         | |         | |                                    #
// #  \ `--.  ___| | ___  ___| |_ ___  __| |  _ __ ___  _   _  ___  _ __  ___   #
// #   `--. \/ _ \ |/ _ \/ __| __/ _ \/ _` | | '_ ` _ \| | | |/ _ \| '_ \/ __|  #
// #  /\__/ /  __/ |  __/ (__| ||  __/ (_| | | | | | | | |_| | (_) | | | \__ \  #
// #  \____/ \___|_|\___|\___|\__\___|\__,_| |_| |_| |_|\__,_|\___/|_| |_|___/  #
// #                                                                            # 
// ##############################################################################

std::vector<IPHCTree::NTMuon> MyMonotopSkim::doMonotopMuonsSelection() const
{

    // Container for output
    std::vector<IPHCTree::NTMuon> outputVector;

    // Get muons
    std::vector<IPHCTree::NTMuon> muons = rawMuons;

    // Loop over muons
    for(unsigned int i=0;i<muons.size();i++)
    {

        // Pt and Eta
        if (muons[i].p4.Pt()  < 30) continue;
        if (muons[i].p4.Eta() > 2.1) continue;

        // Reco - PF matching
        if (fabs(muons[i].bestMatch_pT - muons[i].p4.Pt()) >= 10) continue;

        // Absolute isolation
        float pfIsoCharged = muons[i].isolation["PF03Char"];
        float pfIsoNeutral = muons[i].isolation["PF03Neut"];
        float pfIsoPhoton  = muons[i].isolation["PF03Phot"];
        float pfIsoPU      = muons[i].isolation["PF03PU"];
        float absIso       = pfIsoCharged + max(0., pfIsoNeutral + pfIsoPhoton- 0.5*pfIsoPU); 
        if (absIso > 5) continue;

        outputVector.push_back(muons[i]);
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

    std::vector<IPHCTree::NTElectron> electrons = rawElectrons;

    for(unsigned int i=0;i<electrons.size();i++)
    {

        // Pt and Eta
        if (electrons[i].p4.Pt() < 30) continue;
        if (fabs(electrons[i].etaSuperCluster) >= 1.4442)     continue;

        // Absolute isolation
        float chargedIso = electrons[i].isolation["RA4Charg"];
        float photonIso = electrons[i].isolation["RA4Photo"];
        float neutralIso = electrons[i].isolation["RA4Neutr"];
        float rho_relIso = electrons[i].isolation["rho"];
        float Aeff_relIso = electrons[i].isolation["Aeff"];
        float absIso = chargedIso + max((float) 0.0,(float) (photonIso + neutralIso - rho_relIso * Aeff_relIso));
        if (absIso > 5) continue;

        // E/Pin
        if (electrons[i].eSuperClusterOverP > 4) continue;

        // PF - Reco matching
        if (fabs(electrons[i].bestMatch_pT - electrons[i].p4.Pt()) > 10) continue;

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

    for(unsigned int i=0;i<rawJets.size();i++)
    {
        
        // For sync sample only (had a bug with Tight <-> Loose)
        if (rawJets[i].ID["PU_IDLoose5x"] != 1.) continue;

        // Eta and Pt cuts
        if ((fabs(rawJets[i].p4.Eta()) >= 2.4) || (rawJets[i].p4.Pt()  < 30)) continue;

        outputVector.push_back(rawJets[i]);
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
        if (DataType == 1)
            discr = selectedJets[j].bTag["combinedSecondaryVertexBJetTags"];
        else
            discr = selectedJets[j].bTag["zz1combinedSecondaryVertexBJetTagsReshapeNominal"];

        // Apply CSV medium working point
        if (discr >= 0.679) bJets.push_back(selectedJets[j]);
    }

    return bJets;
}
