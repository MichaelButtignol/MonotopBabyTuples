#ifndef babyFormat
#define babyFormat

typedef struct 
{
    // ------------
    // General info
    // ------------

    Int_t run;                                  // Run number
    Int_t lumi;                                 // Lumiblock number
    Int_t event;                                // Event number

    // ------------
    // Trigger info
    // ------------
    
    Bool_t triggerMuon;                         // Single-Muon trigger has been fired
    Bool_t triggerElec;                         // Single-Elec trigger has been fired
    Bool_t triggerLeptonBtag;                   // Lepton-Btag trigger has been fired

    // ------------
    // Leptons info
    // ------------

    Short_t        numberOfLepton;              // Number of selected leptons
    TLorentzVector selectedLepton;              // p4 of the leading selected lepton
    Float_t        selectedLeptonEta;           // Eta of the leading selected lepton
    Short_t        selectedLeptonPDGId;         // pdgid of the leading selected lepton
    Short_t        nLooseMuons;                 // Number of selected loose muons
    Short_t        nMuons;                      // Number of selected muons
    Short_t        nElectrons;                  // Number of selected electrons
    Short_t        nLooseElectrons;             // Number of selected loose electrons
    Float_t        selectedLeptonIsolation;     // Isolation of the lepton after the cut 

    // ------------
    // Jets info
    // ------------

    Short_t                nJets;               // Number of selected jets
    Short_t                nBTag;               // Number of selected jets b-tagged
    vector<TLorentzVector> jets;                // p4 of the selected jets
    vector<TLorentzVector> bjets;               // p4 of the selected bjets
    //vector<TLorentzVector> leptons;           // p4 of the selected leptons
    //vector<TLorentzVector> leadingJet;        // p4 of the leading jet
    vector<Float_t>        jets_CSV_raw;        // CSV value of the selected jets, before reshaping
    vector<Float_t>        jets_CSV_reshaped;   // CSV value of the selected jets, after reshaping

    // ------------
    // "High-level" /BDT variables
    // ------------

    Float_t MET;                                // Type-1 + phi-corrected PF MET
    Float_t MTw;                                // Transvers mass of the W boson
    Float_t leadingJetPt;                       // pT of the leading jet
    Float_t leadingJetEta;                      // Eta of the leading jet
    Float_t DeltaR_leadJet_lep;                 // DletaR between the lepton and the leading jet

    // ------------
    // Signal-specific infos
    // ------------

    Float_t mResonant;                          // Resonant mass
    Float_t mInvisible;                         // Invisible mass
 
    // ------------
    // Generator-level infos
    // ------------
   
    Int_t   numberOfGenLepton;                  // Number of MC leptons (e/mu/tau, leptons from tau decay are not taken into account)

    vector<TLorentzVector> genParticles;        // p4 of status=3 particles
    vector<Int_t>          genParticlesPDGId;   // PDG of status=3 particles
    vector<Int_t>          genParticlesMother;  // Mother index of the status=3 particles

    // ------------
    // Weights and infos related to weights
    // ------------

    Int_t   numberOfInitialEvents;              // Number of events for the given dataset or signal mass point, before any skimming/selection applied
    Float_t crossSection;                       // Cross section for the given dataset or signal mass point
    Int_t   numberOfTruePU;                     // Number of true pile-up (MC, used in weightPileup)
    Int_t   numberOfPrimaryVertices;            // Number of primary vertices, used to check pile-up data/MC aggreement

    Float_t weightCrossSection;                 // = (crossSection / numberOfInitialEvents) ; user should multiply this weight by the desired lumi
    Float_t weightPileUp;                       // Weight for PU-reweighting
    Float_t weightPileUp_IPHC;                  // Weight for PU-reweighting
    Float_t weightISRmodeling;                  // Weight for ISR modeling
    Float_t weightTopPt;                        // Weight for top Pt reweighting
    Float_t weightTriggerEfficiency;            // Weight for singleLepton trigger efficiency

        // CSV reshaping

    vector<Float_t> jets_CSV_reshapedUpBC;
    vector<Float_t> jets_CSV_reshapedDownBC;
    vector<Float_t> jets_CSV_reshapedUpLight;
    vector<Float_t> jets_CSV_reshapedDownLight;

        // Raw MET (used as a cross check for when applying MET filters after production)

    Float_t rawPFMET;                           // Raw MET from PF-based algorithm 



} babyEvent;

typedef struct
{
    vector<TLorentzVector> jets_beforecut;               // p4 of the selected jets
    vector<TLorentzVector> jets_aftercut;                // p4 of the selected jets
    vector<TLorentzVector> bjets_beforecut;              // p4 of the selected bjets
    vector<TLorentzVector> bjets_aftercut;               // p4 of the selected bjets
    vector<TLorentzVector> leptons_beforecut;            // p4 of the selected leptons
    vector<TLorentzVector> leptons_aftercut;             // p4 of the selected leptons


} CutFlows;

#endif
  


// ###################################################
// #     This function is called by the proof        #
// #   job - this is where you fill the microtuple   #
// ###################################################
#ifdef isCompilingTheBabyTupler

void ProofJob::LoadCorrectionFiles()
{

    //sel.setBTagReshapingInput(     anaEL->GetInfo("Analysis","Corrections","bTagReshaping")          );
    //sel.setMCJetCorrectionsInput(  anaEL->GetInfo("Analysis","Corrections","jetEnergyCorrectionMC")  );
    //sel.setDataJetCorrectionsInput(anaEL->GetInfo("Analysis","Corrections","jetEnergyCorrectionData"));
    sel.setPileUpReweightingInput( anaEL->GetInfo("Analysis","Corrections","pileUp")                   );
    sel.setPileUpReweightingInput_IPHC( anaEL->GetInfo("Analysis","Corrections","pileUp_IPHC")         );

    sel.loadCorrections();

}

void ProofJob::InitializeBranches(TTree* theTree, TTree* theCutFlowTree, babyEvent* myEvent ,CutFlows* myCutFlowEvent)
{
    theTree->Branch("run",                                          &(myEvent->run));
    theTree->Branch("lumi",                                         &(myEvent->lumi));
    theTree->Branch("event",                                        &(myEvent->event));
    
    theTree->Branch("triggerMuon",                                  &(myEvent->triggerMuon));
    theTree->Branch("triggerElec",                                  &(myEvent->triggerElec));
    theTree->Branch("triggerLeptonBtag",                            &(myEvent->triggerLeptonBtag));

    theTree->Branch("numberOfLepton",                               &(myEvent->numberOfLepton));
    theTree->Branch("selectedLepton","TLorentzVector",              &(myEvent->selectedLepton));
    theTree->Branch("selectedLeptonEta",                            &(myEvent->selectedLeptonEta));
    theTree->Branch("selectedLeptonPDGId",                          &(myEvent->selectedLeptonPDGId));
    theTree->Branch("nLooseMuons",                                  &(myEvent->nLooseMuons));
    theTree->Branch("nMuons",                                       &(myEvent->nMuons));
    theTree->Branch("nLooseElectrons",                              &(myEvent->nLooseElectrons));
    theTree->Branch("nElectrons",                                   &(myEvent->nElectrons));
    theTree->Branch("selectedLeptonIsolation",                       &(myEvent->selectedLeptonIsolation));

    theTree->Branch("nJets",                                        &(myEvent->nJets));
    //theTree->Branch("leadingJet","TLorentzVector",                &(myEvent->leadingJet));
    theTree->Branch("nBTag",                                        &(myEvent->nBTag));
    theTree->Branch("jets","std::vector<TLorentzVector>",           &(myEvent->jets));
    theTree->Branch("bjets","std::vector<TLorentzVector>",          &(myEvent->bjets));
    //theTree->Branch("leptons","std::vector<TLorentzVector>",      &(myEvent->leptons));
    theTree->Branch("jets_CSV_raw",     "std::vector<Float_t>",     &(myEvent->jets_CSV_raw));
    theTree->Branch("jets_CSV_reshaped","std::vector<Float_t>",     &(myEvent->jets_CSV_reshaped));


    theTree->Branch("MET",                                          &(myEvent->MET));
    theTree->Branch("MTw",                                          &(myEvent->MTw));
    theTree->Branch("leadingJetPt",                                 &(myEvent->leadingJetPt));
    theTree->Branch("leadingJetEta",                                &(myEvent->leadingJetEta));
    theTree->Branch("DeltaR_leadJet_lep",                           &(myEvent->DeltaR_leadJet_lep));

    theTree->Branch("numberOfGenLepton",                            &(myEvent->numberOfGenLepton));
    theTree->Branch("genParticles","std::vector<TLorentzVector>",   &(myEvent->genParticles));
    theTree->Branch("genParticlesPDGId","std::vector<Int_t>",       &(myEvent->genParticlesPDGId));
    theTree->Branch("genParticlesMother","std::vector<Int_t>",      &(myEvent->genParticlesMother));
    
    theTree->Branch("numberOfInitialEvents",                        &(myEvent->numberOfInitialEvents));
    theTree->Branch("crossSection",                                 &(myEvent->crossSection));
    theTree->Branch("numberOfTruePU",                               &(myEvent->numberOfTruePU));
    theTree->Branch("numberOfPrimaryVertices",                      &(myEvent->numberOfPrimaryVertices));
    theTree->Branch("weightCrossSection",                           &(myEvent->weightCrossSection));
    theTree->Branch("weightPileUp",                                 &(myEvent->weightPileUp));
    theTree->Branch("weightPileUp_IPHC",                            &(myEvent->weightPileUp_IPHC));

    //theTree->Branch("jets_CSV_reshapedUpBC",       "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedUpBC));
    //theTree->Branch("jets_CSV_reshapedDownBC",     "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedDownBC));
    //theTree->Branch("jets_CSV_reshapedUpLight",    "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedUpLight));
    //theTree->Branch("jets_CSV_reshapedDownLight",  "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedDownLight));

    theTree->Branch("rawPFMET",			                    &(myEvent->rawPFMET));

    theCutFlowTree->Branch("leptonsBeforeCut","std::vector<TLorentzVector>",  &(myCutFlowEvent->leptons_beforecut));
    theCutFlowTree->Branch("leptonsAfterCut","TLorentzVector",                &(myEvent->selectedLepton));
    theCutFlowTree->Branch("jetsBeforeCut","std::vector<TLorentzVector>",     &(myCutFlowEvent->jets_beforecut));
    theCutFlowTree->Branch("jetsAfterCut","std::vector<TLorentzVector>",      &(myCutFlowEvent->jets_aftercut));
    theCutFlowTree->Branch("bjetsBeforeCut","std::vector<TLorentzVector>",    &(myCutFlowEvent->bjets_beforecut));
    theCutFlowTree->Branch("bjetsAfterCut","std::vector<TLorentzVector>",     &(myCutFlowEvent->bjets_aftercut));
}


Bool_t ProofJob::Process(Long64_t entry)
{
    // ########################################
    // #  Load the event from the input tree  #
    // ########################################
    fChain->GetTree()->GetEntry(entry); 
    branch->GetEntry(entry);
    IPHCTree::NTTransient::InitializeAfterReading(event);
    sel.LoadEvent(event);
    string datasetName(dataset->Name());

    // ####################
    // #   Get MC infos   #
    // ####################

    bool runningOnData = dataset->isData();

    IPHCTree::NTMonteCarlo mcInfo;
    vector<IPHCTree::NTGenParticle> MCParticles;
    if (!runningOnData)
    {
        mcInfo = *((sel).GetPointer2MC());    
        MCParticles = mcInfo.genParticles;
        monotopMCinfo->LoadEvent(event);
    }    

    // ######################
    // #  Apply selection   #
    // ######################

    short int flag = sel.passEventSelection(runningOnData, datasetName);

    myCutFlowEvent.leptons_beforecut.clear();
    myCutFlowEvent.leptons_aftercut.clear();
    myCutFlowEvent.bjets_beforecut.clear();
    myCutFlowEvent.bjets_aftercut.clear();
    myCutFlowEvent.jets_beforecut.clear();
    myCutFlowEvent.jets_aftercut.clear();

    if (flag >= 0) 
    {
        hCutFlow->Fill(0.);   // Initial
        if(flag == 0) return false;
    }

    if (flag >= 1)
    {
        hCutFlow->Fill(1.);   // Pass Trigger

        std::vector<IPHCTree::NTMuon> muons = sel.doMonotopLooseMuonsSelection( true );
        for (unsigned int i = 0 ; i < muons.size() ; i++)
        {
            myCutFlowEvent.leptons_beforecut.push_back(muons[i].p4);
        }

//        std::vector<IPHCTree::NTElectron> electrons = sel.doMonotopLooseElectronsSelection();
//        for (unsigned int i = 0 ; i < electrons.size() ; i++)
//        {
//            myCutFlowEvent.leptons_beforecut.push_back(electrons[i].p4);
//        }

        hnleptons_beforeCut->Fill(myEvent.nLooseMuons);   // Number of loose muons before lepton cut

        if(flag == 1) return false;      
    }

    if (flag >= 2)
    {
        hCutFlow->Fill(2.);   // Exactly 1 lepton

        // Fill the isolation of the lepton before the cut
        bool doCutOnIsolation = false;
        hMuonIso_beforeCut->Fill( sel.getMuonIsolation( sel.doMonotopMuonsSelection( doCutOnIsolation )[0] ) );
        doCutOnIsolation = true;

        myEvent.selectedLepton           = sel.getSelectedLepton();

        std::vector<IPHCTree::NTJet> seljets = sel.getSelectedJets();
        for (unsigned int i = 0 ; i < seljets.size() ; i++)
        {
            myCutFlowEvent.jets_beforecut.push_back(seljets[i].p4);
        }

        hnleptons_afterCut->Fill(1);        // Number of loose muons before lepton cut
        hnjets_beforeCut->Fill(myCutFlowEvent.jets_beforecut.size());   // Number of jets before jets cut

        if(flag == 2) return false;
    }

    if (flag >= 3) 
    {
        hCutFlow->Fill(3.);   // At least 1 jet

        std::vector<IPHCTree::NTJet> seljets_2 = sel.getSelectedJets();
        for (unsigned int i = 0 ; i < seljets_2.size() ; i++)
        {
            myCutFlowEvent.jets_aftercut.push_back(seljets_2[i].p4);
        }

        std::vector<IPHCTree::NTJet> bjets = sel.getSelectedBJets();
        for (unsigned int i = 0 ; i < bjets.size() ; i++)
        {
            myCutFlowEvent.bjets_beforecut.push_back(bjets[i].p4);
        }

        hnjets_afterCut->Fill(myCutFlowEvent.jets_aftercut.size());                     // Number of jets before jets cut
        hnBjets_beforeCut->Fill(myCutFlowEvent.bjets_beforecut.size());                   // Number of jets before jets cut

        if(flag == 3) return false;
    }

    if (flag >= 4)
    {
        hCutFlow->Fill(4.);   // Exactly 1 bjet

        std::vector<IPHCTree::NTJet> bjets_2 = sel.getSelectedBJets();
        for (unsigned int i = 0 ; i < bjets_2.size() ; i++)
        {
            myCutFlowEvent.bjets_aftercut.push_back(bjets_2[i].p4);
        }

        hnBjets_afterCut->Fill(myCutFlowEvent.bjets_aftercut.size());                    // Number of jets before jets cut

    }


    // #####################
    // #   General infos   #
    // #####################

    myEvent.run   = event->general.runNb;  
    myEvent.lumi  = event->general.lumiblock;
    myEvent.event = event->general.eventNb;

    myEvent.numberOfInitialEvents = dataset->getNSkimmedEvent();
    myEvent.crossSection          = dataset->Xsection();
    myEvent.weightCrossSection    = myEvent.crossSection / myEvent.numberOfInitialEvents;

    // #####################
    // #     Pile-up       #
    // #####################

    // Don't take PU weight into account for data
    if (runningOnData)
    {
        myEvent.numberOfTruePU = 1.0;
        myEvent.weightPileUp = 1.0;
        myEvent.weightPileUp_IPHC = 1.0;
    }
    else
    {

        myEvent.numberOfTruePU = sel.getTnpv();
        myEvent.weightPileUp      = sel.getPileUpWeightFromHistoRatio(myEvent.numberOfTruePU,runningOnData);
        myEvent.weightPileUp_IPHC = sel.getPileUpWeightFromHistoData(myEvent.numberOfTruePU,runningOnData);
    }


    // #####################
    // #   Trigger infos   #
    // #####################

    myEvent.triggerMuon       = sel.passTrigger("singleMuon");
    myEvent.triggerElec       = sel.passTrigger("singleElec");
    myEvent.triggerLeptonBtag = sel.passTrigger("leptonBtag");

    // #####################
    // #   Leptons infos   #
    // #####################

    myEvent.nLooseMuons              = sel.doMonotopLooseMuonsSelection(true).size();
    myEvent.nMuons                   = sel.doMonotopMuonsSelection(true).size();
    myEvent.nLooseElectrons          = sel.doMonotopLooseElectronsSelection().size();
    myEvent.nElectrons               = sel.doMonotopElectronsSelection().size();

    myEvent.numberOfLepton           = sel.getNumberOfSelectedLeptons();
    myEvent.selectedLepton           = sel.getSelectedLepton();
    myEvent.selectedLeptonPDGId      = sel.getSelectedLeptonPDGId();

    // Because of the fact that at this stage, only one lepton should be here
    myEvent.selectedLeptonIsolation  = sel.getMuonIsolation( sel.doMonotopMuonsSelection(true)[0] );

    float leptonCharge;
    if (myEvent.selectedLeptonPDGId > 0) leptonCharge = -1.0;
    else                                leptonCharge = +1.0;

    // ####################
    // #  Fill jets info  #
    // ####################

    myEvent.nJets        = sel.getSelectedJets().size();
    myEvent.nBTag        = sel.getSelectedBJets().size();

    myEvent.jets.clear();
    myEvent.bjets.clear();
    myEvent.jets_CSV_raw.clear();

    //myEvent.jets_CSV_reshaped.clear();
    //myEvent.jets_CSV_reshapedUpBC.clear();
    //myEvent.jets_CSV_reshapedDownBC.clear();
    //myEvent.jets_CSV_reshapedUpLight.clear();
    //myEvent.jets_CSV_reshapedDownLight.clear();

    std::vector<IPHCTree::NTJet> jets = sel.getSelectedJets();
    for (unsigned int i = 0 ; i < jets.size() ; i++)
    {
        myEvent.jets.push_back(jets[i].p4);

        myEvent.jets_CSV_raw.push_back(              jets[i].bTag["combinedSecondaryVertexBJetTags"]                 );
        //myEvent.jets_CSV_reshaped.push_back(         jets[i].bTag["zz1combinedSecondaryVertexBJetTagsReshapeNominal"]  );
        //myEvent.jets_CSV_reshapedUpBC.push_back(     jets[i].bTag["zz2combinedSecondaryVertexBJetTagsReshapeUpBC"]     );
        //myEvent.jets_CSV_reshapedDownBC.push_back(   jets[i].bTag["zz3combinedSecondaryVertexBJetTagsReshapeDownBC"]   );
        //myEvent.jets_CSV_reshapedUpLight.push_back(  jets[i].bTag["zz4combinedSecondaryVertexBJetTagsReshapeUpLight"]  );
        //myEvent.jets_CSV_reshapedDownLight.push_back(jets[i].bTag["zz5combinedSecondaryVertexBJetTagsReshapeDownLight"]);


    }
        








    // #############################
    // #  "High-level" variables   #
    // #############################

    myEvent.MET                   = sel.Met();
    myEvent.MTw                   = sel.MTw();
    myEvent.leadingJetPt          = sel.getLeadingJet().Pt();
    myEvent.leadingJetEta         = abs(sel.getLeadingJet().Eta());
    myEvent.selectedLeptonEta     = abs(sel.getSelectedLepton().Eta());
    if(sel.getSelectedJets().size() == 0) myEvent.DeltaR_leadJet_lep  = -1;
    else                                  myEvent.DeltaR_leadJet_lep  = (sel.getLeadingJet()).DeltaR(sel.getSelectedLepton());
    if(abs(myEvent.DeltaR_leadJet_lep) >= 100) myEvent.DeltaR_leadJet_lep  = -1;
    if(abs(myEvent.DeltaR_leadJet_lep) <= 0.001)
    {
       cout << "WARNING:::::::::::::::::::LeadingJetEta= " << sel.getLeadingJet().Eta() << endl;
       cout << "WARNING:::::::::::::::::::SelectedLeptonEta= " << sel.getSelectedLepton().Eta() << endl;
       cout << "WARNING:::::::::::::::::::DeltaR= " << (sel.getLeadingJet()).DeltaR(sel.getSelectedLepton()) << endl;
    }

    myEvent.numberOfPrimaryVertices = sel.GetVertex().size();
    sel.doObjectSelection(runningOnData,-1);
    sel.FillKinematicP4();


    // ####################
    // #   Signal infos   #
    // ####################

    myEvent.mResonant   = monotopMCinfo->GetResonantMass();
    myEvent.mInvisible  = monotopMCinfo->GetInvisibleMass();


    // ###################################
    // #   Generator-level information   #
    // ###################################

    myEvent.genParticles.clear();
    myEvent.genParticlesPDGId.clear();
    myEvent.genParticlesMother.clear();

    if (runningOnData)
    {
        myEvent.numberOfGenLepton = -1;
    }
    else
    {

        // TMEME decoding
        int TMEME = mcInfo.TMEME; 
        int  MEME = TMEME % 10000; 
        int   EME =  MEME % 1000; 
        int    ME =   EME % 100; 
        int     E =    ME % 10;

        myEvent.numberOfGenLepton = TMEME/10000 + ME/10 + E/1;

        for (unsigned int i = 0 ; i < MCParticles.size() ; i++)  
        {
            myEvent.genParticles.push_back(MCParticles[i].p4);
            myEvent.genParticlesPDGId.push_back(MCParticles[i].id);
            myEvent.genParticlesMother.push_back(MCParticles[i].motherIndex_);
        }
    }



    // ###############################
    // #  Add the event to the tree  #
    // ###############################

    theTree->Fill();
    theCutFlowTree->Fill();
    return true;
}

#endif

