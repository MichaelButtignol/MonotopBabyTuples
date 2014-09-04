#ifndef MyMonotopSkim_h
#define MyMonotopSkim_h

// IPHC headers
#include "Selection/interface/Selection.h"
#include "Selection/interface/SelectionTable.h"
#include "Tools/interface/Dataset.h"

#include "EventReco/interface/Resolution.h"
#include "BTagReshaping/interface/BTagReshaping.h"
#include "Tools/interface/PUWeighting.h"

#include "JetCorrections/interface/JetCorrectionUncertainty.h"

// system include files
#include <memory>
#include <vector>
#include <sstream>

class MyMonotopSkim: public Selection
{

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
    public:

        //! Constructor without argument
        MyMonotopSkim();

        //! Copy constructor
        MyMonotopSkim(const MyMonotopSkim &);

        //! Destructor
        ~MyMonotopSkim()
        { }

        //! LoadEvent 
        bool LoadEvent(const NTEvent * event) 
        { 
            return Event::LoadEvent(event); 
        }

        void setBTagReshapingInput(string fileName);     
        void setMCJetCorrectionsInput(string fileName);  
        void setDataJetCorrectionsInput(string fileName);
        void setPileUpReweightingInput(string fileName); 
        void setPileUpReweightingInput_IPHC(string fileName); 
        void loadCorrections();

        // #####################################
        // #   Accessors to selected objects   #
        // #####################################

        //! Accessor to selected jets
        const std::vector<IPHCTree::NTJet>& getSelectedJets() const { return selectedJets; }

        //! Accessor to selected b-jets
        const std::vector<IPHCTree::NTJet>& getSelectedBJets() const { return selectedBJets; }


        // Accessors to selected leptons
        TLorentzVector getSelectedLepton()      { return selectedLepton; };
        int            getSelectedLeptonPDGId() { return selectedLepton_pdgid; };

        int getNumberOfSelectedLeptons() { return numberOfSelectedLeptons; }


        // #################################
        // #   Selection-related methods   #
        // #################################

        // Apply object selection on event
        void doObjectSelection(bool runningOnData, short int JESvariation = 0);

        // Return true if the event pass the selection
        short int passEventSelection(bool runningOnData, string datasetName);

        // Apply JES +/- 1sigma variation on a given jet collection
        void ApplyJESVariation(bool runningOnData, bool upOrDown);

        void FillKinematicP4();

        // Selected muons
        std::vector<IPHCTree::NTMuon> doMonotopMuonsSelection( bool doCutOnIsolation ) const;

	// Selected loose muons
        std::vector<IPHCTree::NTMuon> doMonotopLooseMuonsSelection( bool doCutOnIsolation ) const;

        // Get the isolation of the muon whether it is rejected or not (flag)
        float getMuonIsolation(IPHCTree::NTMuon &muon) const;

        // Selected electrons
        std::vector<IPHCTree::NTElectron> doMonotopElectronsSelection() const;

        // Selected loose electrons
        std::vector<IPHCTree::NTElectron> doMonotopLooseElectronsSelection() const;
        
        // Selected jets
        std::vector<IPHCTree::NTJet> doMonotopJetsSelection(int DataType) const;

        // Selected b-jets
        std::vector<IPHCTree::NTJet> doMonotopBJetsSelection(int DataType) const; 

        // Check if a given trigger path has been trigerred
        bool checkPathHasBeenFired(string path);

        // Check if a given set of trigger (single electron, double muon, ...) contains a path that has been fired
        bool passTrigger(string channel);

        // Compute the transverse mass of the W
        float MTw() const   { return sqrt( 2.* selectedLepton.Pt() * theMET.Pt() *(1. - cos( selectedLepton.Phi() - theMET.Phi()) )) ;}

	//Get the MET
	float Met() const            { return rawMET.p2.Mod(); }

	// Get the leading jet	
        TLorentzVector getLeadingJet()
        {
            TLorentzVector leadingJet = 0.0;

            for (unsigned int i = 0 ; i < selectedJets.size() ; i++)
            {
                if (leadingJet.Pt() < selectedJets[i].p4.Pt())
                    leadingJet      = selectedJets[i].p4;
            }

            return leadingJet;
        }

	
        TLorentzVector getLeadingJetByCSV(bool runningOnData)
        {
            TLorentzVector leadingCSVJet = 0.0;
            float maxDiscr = -1.0;

            string discrName;
            if (runningOnData) discrName = "combinedSecondaryVertexBJetTags";
            else               discrName = "zz1combinedSecondaryVertexBJetTagsReshapeNominal";

            for (unsigned int i = 0 ; i < selectedJets.size() ; i++)
            {
                if (maxDiscr < selectedJets[i].bTag[discrName])
                {
                    maxDiscr = selectedJets[i].bTag[discrName];
                    leadingCSVJet = selectedJets[i].p4;
                }
            }

            return leadingCSVJet;
        }

        float getPileUpWeightFromHistoRatio( int nvtx, bool runningOnData )
        {
            if( runningOnData ) return 1;

            if( nvtx > pileUpReweightingHisto->GetNbinsX() )
                nvtx = pileUpReweightingHisto->GetNbinsX();

            float weight = 0;
            weight = pileUpReweightingHisto->GetBinContent( pileUpReweightingHisto->FindBin(nvtx) );

            //we don't want to kill events bc they have no weight
            if( weight <= 0 ) weight = 1.;
            return weight;
        }
            
        float getPileUpWeightFromHistoData( int nvtx, bool runningOnData )
        {
            if( runningOnData ) return 1;

            float weight = 0;
            weight = PUWeights->weight_Summer12_S10(nvtx);
            
            //we don't want to kill events bc they have no weight
            if( weight <= 0 ) weight = 1.;
            return weight;
        }


        // -------------------------------------------------------------
        //                        data members
        // -------------------------------------------------------------
    private:

        // Raw objects

        std::vector<IPHCTree::NTElectron> rawElectrons;
        std::vector<IPHCTree::NTMuon>     rawMuons;
        std::vector<IPHCTree::NTJet>      rawJets;
	NTMET			          rawMET;
	TLorentzVector      		  theMET;

        // Objects for analysis

        int numberOfSelectedLeptons;
        TLorentzVector selectedLepton;
        int selectedLepton_pdgid;

        std::vector<IPHCTree::NTElectron> selectedElectrons;
        std::vector<IPHCTree::NTElectron> selectedLooseElectrons;
        std::vector<IPHCTree::NTMuon>     selectedMuons;
        std::vector<IPHCTree::NTMuon>     selectedLooseMuons;
        std::vector<IPHCTree::NTJet>      selectedJets;
        std::vector<IPHCTree::NTJet>      selectedBJets;

        // Corrections managers

//        string bTagReshapingInput;
//        string jetCorrectionsMCInput;
//        string jetCorrectionsDataInput;
        string pileUpReweightingInput;
        string pileUpReweightingInput_IPHC;

        PUWeighting* PUWeights; 
        TH1F* pileUpReweightingHisto;
        TH1D* pileUpReweightingHisto_IPHC;
//        JetCorrectionUncertainty* JESUncertainty_MC;
//        JetCorrectionUncertainty* JESUncertainty_Data;

//        BTagShapeInterface* BTagReshape_nominal;
//        BTagShapeInterface* BTagReshape_upBC;
//        BTagShapeInterface* BTagReshape_downBC;
//        BTagShapeInterface* BTagReshape_upLight;
//        BTagShapeInterface* BTagReshape_downLight;

};

#endif
