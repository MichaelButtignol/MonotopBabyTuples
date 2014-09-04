#ifndef MyMonotopSkim_h
#define MyMonotopSkim_h

// IPHC headers
#include "Selection/interface/Selection.h"
#include "Selection/interface/SelectionTable.h"
#include "Tools/interface/Dataset.h"

#include "EventReco/interface/Resolution.h"
#include "BTagReshaping/interface/BTagReshaping.h"

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


        // #####################################
        // #   Accessors to selected objects   #
        // #####################################

        //! Accessor to selected jets
        const std::vector<IPHCTree::NTJet>& GetSelectedJets() const { return selectedJets; }

        //! Accessor to selected b-jets
        const std::vector<IPHCTree::NTJet>& GetSelectedBJets() const { return selectedBJets; }


        // Accessors to selected leptons

        TLorentzVector getTheSelectedLepton()      { return theSelectedLepton; };
        int            getTheSelectedLeptonPDGId() { return theSelectedLepton_pdgid; };


        int getTheNumberOfSelectedLeptons() { return numberOfSelectedLeptons; }

        // #################################
        // #   Selection-related methods   #
        // #################################

        // Apply object selection on event
        void doObjectSelection(bool runningOnData, short int JESvariation = 0);

        // Return true if the event pass the selection
        bool passEventSelection(bool runningOnData);

        // Apply JES +/- 1sigma variation on a given jet collection
        void ApplyJESVariation(bool runningOnData, bool upOrDown);

        void FillKinematicP4();

        // Selected muons
        std::vector<IPHCTree::NTMuon> doMonotopMuonsSelection() const;

        // Selected electrons
        std::vector<IPHCTree::NTElectron> doMonotopElectronsSelection() const;
        
        // Selected jets
        std::vector<IPHCTree::NTJet> doMonotopJetsSelection(int DataType) const;

        // Selected b-jets
        std::vector<IPHCTree::NTJet> doMonotopBJetsSelection(int DataType) const; 

        // Check if a given trigger path has been trigerred
        bool checkPathHasBeenFired(string path);

        // Check if a given set of trigger (single electron, double muon, ...) contains a path that has been fired
        bool passTrigger(string channel);




        // -------------------------------------------------------------
        //                        data members
        // -------------------------------------------------------------
    private:

        // Raw objects

        std::vector<IPHCTree::NTElectron> rawElectrons;
        std::vector<IPHCTree::NTMuon>     rawMuons;
        std::vector<IPHCTree::NTJet>      rawJets;

        // Objects for analysis

        int numberOfSelectedLeptons;
        TLorentzVector theSelectedLepton;
        int theSelectedLepton_pdgid;

        std::vector<IPHCTree::NTElectron> selectedElectrons;
        std::vector<IPHCTree::NTMuon>     selectedMuons;
        std::vector<IPHCTree::NTJet>      selectedJets;
        std::vector<IPHCTree::NTJet>      selectedBJets;

};

#endif
