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
    Bool_t xtriggerMuon;                        // Muon cross-trigger  has been fired
    Bool_t triggerElec;                         // Single-Elec trigger has been fired
    
    Bool_t triggerDoubleElec;                   // Double-Elec trigger has been fired
    Bool_t triggerDoubleMuon;                   // Double-Muon trigger has been fired
    Bool_t triggerMuonElec;                     // Muon-Elec   trigger has been fired

    // ------------
    // Leptons info
    // ------------

    Short_t        numberOfLepton;              // Number of selected leptons
    TLorentzVector leadingLepton;               // p4 of the leading selected lepton
    Short_t        leadingLeptonPDGId;          // pdgid of the leading selected lepton
    TLorentzVector secondLepton;                // p4 of the second lepton
    Short_t        secondLeptonPDGId;           // pdgid of the second lepton

    Bool_t         isolatedTrackVeto;           // Event pass/fail the isolated track veto
    Bool_t         tauVeto;                     // Event pass/fail the tau veto
    
    // ------------
    // Jets info
    // ------------

    Short_t                nJets;               // Number of selected jets
    Short_t                nBTag;               // Number of selected jets b-tagged
    vector<TLorentzVector> jets;                // p4 of the selected jets
    vector<Float_t>        jets_CSV_raw;        // CSV value of the selected jets, before reshaping 
    vector<Float_t>        jets_CSV_reshaped;   // CSV value of the selected jets, after reshaping
    vector<Int_t>          jets_partonFlav;     // Parton flavour of the selected jets

    // ------------
    // "High-level" /BDT variables
    // ------------

    Float_t MET;                                // Type-1 + phi-corrected PF MET
    Float_t MT;                                 // transverse mass of leading lepton + MET
    Float_t deltaPhiMETJets;                    // DeltaPhi(MET,first two leading jets)
    Float_t hadronicChi2;                       // Hadronic Chi^2
    Float_t MT2W;                               // MT2W
    Float_t HT;                                 // HT
    Float_t HTRatio;                            // Fraction of HT in the same hemisphere as MET
    Float_t leadingBPt;                         // pT of the leading b-jet
    Float_t leadingLeptonPt;                    // pT of the leading lepton
    Float_t leadingJetPt;                       // pT of the leading jet
    Float_t Mlb;                                // invariant mass of leading lepton + jet with highest CSV
    Float_t Mlb_hemi;                           // invariant mass of leading lepton + b-jet closest to lepton
    Float_t M3b;                                // invariant mass of the 3jets dR-furthest from lepton
    Float_t deltaRLeptonLeadingB;               // DeltaR(leading lepton, leading b-jet)
    Float_t METoverSqrtHT;                      // MET/sqrt(HT)
    Float_t HTPlusLeptonPtPlusMET;              // HT + pT(leading lepton) + MET

    // ------------
    // W-tagging info
    // ------------

    Short_t nWTag;                              // Number of W-tagged jets
    Float_t leadingWjetPt;                      // pT of the leading W-tagged jet

    // ------------
    // Signal-specific infos
    // ------------

    Float_t mStop;                              // Stop mass
    Float_t mNeutralino;                        // Neutralino mass
    Float_t mCharginoParameter;                 // Chargino mass parameter for T2bw (0.25, 0.5 or 0.75)
 
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
    Float_t weightISRmodeling;                  // Weight for ISR modeling
    Float_t weightTopPt;                        // Weight for top Pt reweighting
    Float_t weightTriggerEfficiency;            // Weight for singleLepton trigger efficiency

    Float_t weightT2ttLeftHanded;               // Polarization reweighting
    Float_t weightT2ttRightHanded;              // Polarization reweighting
    Float_t weightT2bwPolarization_ss;          // Polarization reweighting
    Float_t weightT2bwPolarization_ls;          // Polarization reweighting
    Float_t weightT2bwPolarization_sl;          // Polarization reweighting
    Float_t weightT2bwPolarization_sr;          // Polarization reweighting
    Float_t weightT2bwPolarization_rs;          // Polarization reweighting
    Float_t weightT2bwPolarization_ll;          // Polarization reweighting
    Float_t weightT2bwPolarization_lr;          // Polarization reweighting
    Float_t weightT2bwPolarization_rl;          // Polarization reweighting
    Float_t weightT2bwPolarization_rr;          // Polarization reweighting

    // ------------
    // Infos for systematic effects
    // ------------

        // Jet energy scale

    Float_t MET_JESup;                          // Type-1 + phi-corrected PF MET                              (+1sigma JES applied)
    Float_t MT_JESup;                           // transverse mass of leading lepton + MET                    (+1sigma JES applied)
    Float_t deltaPhiMETJets_JESup;              // DeltaPhi(MET,first two leading jets)                       (+1sigma JES applied)
    Float_t hadronicChi2_JESup;                 // Hadronic Chi^2                                             (+1sigma JES applied)
    Float_t MT2W_JESup;                         // MT2W                                                       (+1sigma JES applied)
    Float_t HT_JESup;                           // HT                                                         (+1sigma JES applied)
    Float_t HTRatio_JESup;                      // Fraction of HT in the same hemisphere as MET               (+1sigma JES applied)
    Float_t leadingBPt_JESup;                   // pT of the leading b-jet                                    (+1sigma JES applied)
    Float_t leadingJetPt_JESup;                 // pT of the leading jet                                      (+1sigma JES applied)
    Float_t Mlb_JESup;                          // invariant mass of leading lepton + jet with highest CSV    (+1sigma JES applied)
    Float_t Mlb_hemi_JESup;                     // invariant mass of leading lepton + b-jet closest to lepton (+1sigma JES applied)
    Float_t M3b_JESup;                          // invariant mass of the 3jets dR-furthest from lepton        (+1sigma JES applied)
    Float_t deltaRLeptonLeadingB_JESup;         // DeltaR(leading lepton, leading b-jet)                      (+1sigma JES applied)
    Float_t METoverSqrtHT_JESup;                // MET/sqrt(HT)                                               (+1sigma JES applied)
    Float_t HTPlusLeptonPtPlusMET_JESup;        // HT + pT(leading lepton) + MET                              (+1sigma JES applied)
    Short_t nJets_JESup;                        // Jet multiplicity with                                      (+1sigma JES applied)
    Float_t weightTriggerEfficiency_JESup;      // Weight for singleLepton trigger efficiency                 (+1sigma JES applied)

    Float_t MET_JESdown;                        // Type-1 - phi-corrected PF MET                              (-1sigma JES applied)
    Float_t MT_JESdown;                         // transverse mass of leading lepton - MET                    (-1sigma JES applied)
    Float_t deltaPhiMETJets_JESdown;            // DeltaPhi(MET,first two leading jets)                       (-1sigma JES applied)
    Float_t hadronicChi2_JESdown;               // Hadronic Chi^2                                             (-1sigma JES applied)
    Float_t MT2W_JESdown;                       // MT2W                                                       (-1sigma JES applied)
    Float_t HT_JESdown;                         // HT                                                         (-1sigma JES applied)
    Float_t HTRatio_JESdown;                    // Fraction of HT in the same hemisphere as MET               (-1sigma JES applied)
    Float_t leadingBPt_JESdown;                 // pT of the leading b-jet                                    (-1sigma JES applied)
    Float_t leadingJetPt_JESdown;               // pT of the leading jet                                      (-1sigma JES applied)
    Float_t Mlb_JESdown;                        // invariant mass of leading lepton - jet with highest CSV    (-1sigma JES applied)
    Float_t Mlb_hemi_JESdown;                   // invariant mass of leading lepton - b-jet closest to lepton (-1sigma JES applied)
    Float_t M3b_JESdown;                        // invariant mass of the 3jets dR-furthest from lepton        (-1sigma JES applied)
    Float_t deltaRLeptonLeadingB_JESdown;       // DeltaR(leading lepton, leading b-jet)                      (-1sigma JES applied)
    Float_t METoverSqrtHT_JESdown;              // MET/sqrt(HT)                                               (-1sigma JES applied)
    Float_t HTPlusLeptonPtPlusMET_JESdown;      // HT - pT(leading lepton) - MET                              (-1sigma JES applied)
    Short_t nJets_JESdown;                      // Jet multiplicity with                                      (-1sigma JES applied)
    Float_t weightTriggerEfficiency_JESdown;    // Weight for singleLepton trigger efficiency                 (-1sigma JES applied)

        // CSV reshaping
        
    vector<Float_t> jets_CSV_reshapedUpBC;
    vector<Float_t> jets_CSV_reshapedDownBC;
    vector<Float_t> jets_CSV_reshapedUpLight;
    vector<Float_t> jets_CSV_reshapedDownLight;

        // Non-selected jets (with pT > 10, eta < 4.7)

    vector<TLorentzVector> nonSelectedJets;              // p4 of the non selected jets (with pT > 10, eta < 4.7)
    vector<Float_t>        nonSelectedJets_CSV_raw;      // CSV value of the non selected jets, before reshaping 
    vector<Float_t>        nonSelectedJets_CSV_reshaped; // CSV value of the non selected jets, after reshaping
    vector<Int_t>          nonSelectedJets_partonFlav;   // Parton flavour of the non selected jets

        // Non selected leptons (with pT > 10, eta < 2.4, and electron/muon ID applied)

    vector<TLorentzVector> nonSelectedLeptons;              // p4 of the non selected leptons
    vector<Short_t>        nonSelectedLeptonsPDGId;         // pdgid of the non selected leptons 

        // Raw MET (used as a cross check for when applying MET filters after production)

    Float_t rawPFMET;                           // Raw MET from PF-based algorithm 

        // Infos for PDF uncertainties
   
    Float_t x_firstIncomingParton;              // Momentum fraction carried by the first incoming parton
    Float_t x_secondIncomingParton;             // Momentum fraction carried by the second incoming parton
    Int_t   flavor_firstIncomingParton;         // PDGId of the first incoming parton
    Int_t   flavor_secondIncomingParton;        // PDGId of the second incoming parton
    Float_t scalePDF;                           // The PDF scale


} babyEvent;

#endif
  


// ###################################################
// #     This function is called by the proof        #
// #   job - this is where you fill the microtuple   #
// ###################################################
#ifdef isCompilingTheBabyTupler

TH2F* mapT2tt;
TH2F* mapT2bw025;
TH2F* mapT2bw050;
TH2F* mapT2bw075;

void ProofJob::LoadCorrectionFiles()
{

    sel.setBTagReshapingInput(     anaEL->GetInfo("Analysis","Corrections","bTagReshaping")          );
    sel.setMCJetCorrectionsInput(  anaEL->GetInfo("Analysis","Corrections","jetEnergyCorrectionMC")  );
    sel.setDataJetCorrectionsInput(anaEL->GetInfo("Analysis","Corrections","jetEnergyCorrectionData"));
    sel.setPileUpReweightingInput( anaEL->GetInfo("Analysis","Corrections","pileUp")                 );

    sel.loadCorrections();
    

    TFile* fileMapT2tt    = new TFile("/opt/sbg/data/data4/cms/aaubin/analysisStudy_July13/CMSSW_5_3_2_patch4/src/NTuple/NTupleAnalysis/macros/TTbarMET/babyTupling/../inputs/signalInitialNumberOfEventsMap/mapT2tt.root");
    TFile* fileMapT2bw025 = new TFile("/opt/sbg/data/data4/cms/aaubin/analysisStudy_July13/CMSSW_5_3_2_patch4/src/NTuple/NTupleAnalysis/macros/TTbarMET/babyTupling/../inputs/signalInitialNumberOfEventsMap/mapT2bw-025.root");
    TFile* fileMapT2bw050 = new TFile("/opt/sbg/data/data4/cms/aaubin/analysisStudy_July13/CMSSW_5_3_2_patch4/src/NTuple/NTupleAnalysis/macros/TTbarMET/babyTupling/../inputs/signalInitialNumberOfEventsMap/mapT2bw-050.root");
    TFile* fileMapT2bw075 = new TFile("/opt/sbg/data/data4/cms/aaubin/analysisStudy_July13/CMSSW_5_3_2_patch4/src/NTuple/NTupleAnalysis/macros/TTbarMET/babyTupling/../inputs/signalInitialNumberOfEventsMap/mapT2bw-075.root");

    fileMapT2tt   ->GetObject("mStopVSmNeutralino",mapT2tt   );
    fileMapT2bw025->GetObject("mStopVSmNeutralino",mapT2bw025);
    fileMapT2bw050->GetObject("mStopVSmNeutralino",mapT2bw050);
    fileMapT2bw075->GetObject("mStopVSmNeutralino",mapT2bw075);
}

void ProofJob::InitializeBranches(TTree* theTree, babyEvent* myEvent)
{
    theTree->Branch("run",                                          &(myEvent->run));
    theTree->Branch("lumi",                                         &(myEvent->lumi));
    theTree->Branch("event",                                        &(myEvent->event));
    
    theTree->Branch("triggerMuon",                                  &(myEvent->triggerMuon));
    theTree->Branch("xtriggerMuon",                                 &(myEvent->xtriggerMuon));
    theTree->Branch("triggerElec",                                  &(myEvent->triggerElec));
    theTree->Branch("triggerDoubleElec",                            &(myEvent->triggerDoubleElec));
    theTree->Branch("triggerDoubleMuon",                            &(myEvent->triggerDoubleMuon));
    theTree->Branch("triggerMuonElec",                              &(myEvent->triggerMuonElec));
    
    theTree->Branch("numberOfLepton",                               &(myEvent->numberOfLepton));
    theTree->Branch("leadingLepton","TLorentzVector",               &(myEvent->leadingLepton));
    theTree->Branch("leadingLeptonPDGId",                           &(myEvent->leadingLeptonPDGId));
    theTree->Branch("secondLepton","TLorentzVector",                &(myEvent->secondLepton));
    theTree->Branch("secondLeptonPDGId",                            &(myEvent->secondLeptonPDGId));
    theTree->Branch("isolatedTrackVeto",                            &(myEvent->isolatedTrackVeto));
    theTree->Branch("tauVeto",                                      &(myEvent->tauVeto));
    
    theTree->Branch("nJets",                                        &(myEvent->nJets));
    theTree->Branch("nBTag",                                        &(myEvent->nBTag));
    theTree->Branch("jets","std::vector<TLorentzVector>",           &(myEvent->jets));
    theTree->Branch("jets_CSV_raw",     "std::vector<Float_t>",     &(myEvent->jets_CSV_raw));
    theTree->Branch("jets_CSV_reshaped","std::vector<Float_t>",     &(myEvent->jets_CSV_reshaped));
    theTree->Branch("jets_partonFlav",  "std::vector<Int_t>",       &(myEvent->jets_partonFlav));

    theTree->Branch("MET",                                          &(myEvent->MET));
    theTree->Branch("MT",                                           &(myEvent->MT));
    theTree->Branch("deltaPhiMETJets",                              &(myEvent->deltaPhiMETJets));
    theTree->Branch("hadronicChi2",                                 &(myEvent->hadronicChi2));
    theTree->Branch("MT2W",                                         &(myEvent->MT2W));
    theTree->Branch("HT",                                           &(myEvent->HT));
    theTree->Branch("HTRatio",                                      &(myEvent->HTRatio));
    theTree->Branch("leadingBPt",                                   &(myEvent->leadingBPt));
    theTree->Branch("leadingLeptonPt",                              &(myEvent->leadingLeptonPt));
    theTree->Branch("leadingJetPt",                                 &(myEvent->leadingJetPt));
    theTree->Branch("Mlb",                                          &(myEvent->Mlb));
    theTree->Branch("Mlb_hemi",                                     &(myEvent->Mlb_hemi));
    theTree->Branch("M3b",                                          &(myEvent->M3b));
    theTree->Branch("deltaRLeptonLeadingB",                         &(myEvent->deltaRLeptonLeadingB));
    theTree->Branch("METoverSqrtHT",                                &(myEvent->METoverSqrtHT));
    theTree->Branch("HTPlusLeptonPtPlusMET",                        &(myEvent->HTPlusLeptonPtPlusMET));
    
    theTree->Branch("nWTag",                                        &(myEvent->nWTag));
    theTree->Branch("leadingWjetPt",                                &(myEvent->leadingWjetPt));
    
    theTree->Branch("mStop",                                        &(myEvent->mStop));
    theTree->Branch("mNeutralino",                                  &(myEvent->mNeutralino));
    theTree->Branch("mCharginoParameter",                           &(myEvent->mCharginoParameter));
    
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
    theTree->Branch("weightISRmodeling",                            &(myEvent->weightISRmodeling));
    theTree->Branch("weightTopPt",                                  &(myEvent->weightTopPt));
    theTree->Branch("weightTriggerEfficiency",                      &(myEvent->weightTriggerEfficiency));
    theTree->Branch("weightT2ttLeftHanded",                         &(myEvent->weightT2ttLeftHanded));
    theTree->Branch("weightT2ttRightHanded",                        &(myEvent->weightT2ttRightHanded));
    theTree->Branch("weightT2bwPolarization_ss",                    &(myEvent->weightT2bwPolarization_ss));
    theTree->Branch("weightT2bwPolarization_ls",                    &(myEvent->weightT2bwPolarization_ss));
    theTree->Branch("weightT2bwPolarization_sl",                    &(myEvent->weightT2bwPolarization_ss));
    theTree->Branch("weightT2bwPolarization_sr",                    &(myEvent->weightT2bwPolarization_ss));
    theTree->Branch("weightT2bwPolarization_rs",                    &(myEvent->weightT2bwPolarization_ss));
    theTree->Branch("weightT2bwPolarization_ll",                    &(myEvent->weightT2bwPolarization_ll));
    theTree->Branch("weightT2bwPolarization_lr",                    &(myEvent->weightT2bwPolarization_lr));
    theTree->Branch("weightT2bwPolarization_rl",                    &(myEvent->weightT2bwPolarization_rl));
    theTree->Branch("weightT2bwPolarization_rr",                    &(myEvent->weightT2bwPolarization_rr));
   
    theTree->Branch("MET_JESup",                                    &(myEvent->MET_JESup));
    theTree->Branch("MT_JESup",                                     &(myEvent->MT_JESup));
    theTree->Branch("deltaPhiMETJets_JESup",                        &(myEvent->deltaPhiMETJets_JESup));
    theTree->Branch("hadronicChi2_JESup",                           &(myEvent->hadronicChi2_JESup));
    theTree->Branch("MT2W_JESup",                                   &(myEvent->MT2W_JESup));
    theTree->Branch("HT_JESup",                                     &(myEvent->HT_JESup));
    theTree->Branch("HTRatio_JESup",                                &(myEvent->HTRatio_JESup));
    theTree->Branch("leadingBPt_JESup",                             &(myEvent->leadingBPt_JESup));
    theTree->Branch("leadingJetPt_JESup",                           &(myEvent->leadingJetPt_JESup));
    theTree->Branch("Mlb_JESup",                                    &(myEvent->Mlb_JESup));
    theTree->Branch("Mlb_hemi_JESup",                               &(myEvent->Mlb_hemi_JESup));
    theTree->Branch("M3b_JESup",                                    &(myEvent->M3b_JESup));
    theTree->Branch("deltaRLeptonLeadingB_JESup",                   &(myEvent->deltaRLeptonLeadingB_JESup));
    theTree->Branch("METoverSqrtHT_JESup",                          &(myEvent->METoverSqrtHT_JESup));
    theTree->Branch("HTPlusLeptonPtPlusMET_JESup",                  &(myEvent->HTPlusLeptonPtPlusMET_JESup));
    theTree->Branch("nJets_JESup",                                  &(myEvent->nJets_JESup));
    theTree->Branch("weightTriggerEfficiency_JESup",                &(myEvent->weightTriggerEfficiency_JESup));
    
    theTree->Branch("MET_JESdown",                                  &(myEvent->MET_JESdown));
    theTree->Branch("MT_JESdown",                                   &(myEvent->MT_JESdown));
    theTree->Branch("deltaPhiMETJets_JESdown",                      &(myEvent->deltaPhiMETJets_JESdown));
    theTree->Branch("hadronicChi2_JESdown",                         &(myEvent->hadronicChi2_JESdown));
    theTree->Branch("MT2W_JESdown",                                 &(myEvent->MT2W_JESdown));
    theTree->Branch("HT_JESdown",                                   &(myEvent->HT_JESdown));
    theTree->Branch("HTRatio_JESdown",                              &(myEvent->HTRatio_JESdown));
    theTree->Branch("leadingBPt_JESdown",                           &(myEvent->leadingBPt_JESdown));
    theTree->Branch("leadingJetPt_JESdown",                         &(myEvent->leadingJetPt_JESdown));
    theTree->Branch("Mlb_JESdown",                                  &(myEvent->Mlb_JESdown));
    theTree->Branch("Mlb_hemi_JESdown",                             &(myEvent->Mlb_hemi_JESdown));
    theTree->Branch("M3b_JESdown",                                  &(myEvent->M3b_JESdown));
    theTree->Branch("deltaRLeptonLeadingB_JESdown",                 &(myEvent->deltaRLeptonLeadingB_JESdown));
    theTree->Branch("METoverSqrtHT_JESdown",                        &(myEvent->METoverSqrtHT_JESdown));
    theTree->Branch("HTPlusLeptonPtPlusMET_JESdown",                &(myEvent->HTPlusLeptonPtPlusMET_JESdown));
    theTree->Branch("nJets_JESdown",                                &(myEvent->nJets_JESdown));
    theTree->Branch("weightTriggerEfficiency_JESdown",              &(myEvent->weightTriggerEfficiency_JESdown));

    theTree->Branch("jets_CSV_reshapedUpBC",       "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedUpBC));
    theTree->Branch("jets_CSV_reshapedDownBC",     "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedDownBC));
    theTree->Branch("jets_CSV_reshapedUpLight",    "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedUpLight));
    theTree->Branch("jets_CSV_reshapedDownLight",  "std::vector<Float_t>",          &(myEvent->jets_CSV_reshapedDownLight));

    theTree->Branch("nonSelectedJets",             "std::vector<TLorentzVector>",   &(myEvent->nonSelectedJets));
    theTree->Branch("nonSelectedJets_CSV_raw",     "std::vector<Float_t>",          &(myEvent->nonSelectedJets_CSV_raw));
    theTree->Branch("nonSelectedJets_CSV_reshaped","std::vector<Float_t>",          &(myEvent->nonSelectedJets_CSV_reshaped));
    theTree->Branch("nonSelectedJets_partonFlav",  "std::vector<Int_t>",            &(myEvent->nonSelectedJets_partonFlav));
    
    theTree->Branch("nonSelectedLeptons",          "std::vector<TLorentzVector>",   &(myEvent->nonSelectedLeptons));
    theTree->Branch("nonSelectedLeptonsPDGId",     "std::vector<Short_t>",          &(myEvent->nonSelectedLeptonsPDGId));
    
    theTree->Branch("rawPFMET",                     &(myEvent->rawPFMET));

    theTree->Branch("x_firstIncomingParton",        &(myEvent->x_firstIncomingParton));       
    theTree->Branch("x_secondIncomingParton",       &(myEvent->x_secondIncomingParton));      
    theTree->Branch("flavor_firstIncomingParton",   &(myEvent->flavor_firstIncomingParton));  
    theTree->Branch("flavor_secondIncomingParton",  &(myEvent->flavor_secondIncomingParton)); 
    theTree->Branch("scalePDF",                     &(myEvent->scalePDF));                   

}

#define PI 3.141592653
#include "../inputs/polarizationReweighting.h"
#include "../inputs/triggerEfficiencyReweighting.h"
#include "../inputs/stopCrossSections.h"

bool badSignalEventFilter(string datasetName,StopMCinfo* stopMCinfo);

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
        stopMCinfo->LoadEvent(event);
    }

    // ###############################
    // #  Filter bad signal events   #
    // ###############################
  
    if (badSignalEventFilter(datasetName,stopMCinfo) == false) return false;

    // ######################
    // #  Apply selection   #
    // ######################
    
    if (sel.passEventSelection(runningOnData) == false) return false;

    // #####################
    // #   General infos   #
    // #####################

    myEvent.run   = event->general.runNb;  
    myEvent.lumi  = event->general.lumiblock;
    myEvent.event = event->general.eventNb;

    // #####################
    // #   Trigger infos   #
    // #####################

    myEvent.triggerMuon       = sel.passTrigger("singleMuon");
    myEvent.triggerElec       = sel.passTrigger("singleElec");
    myEvent.xtriggerMuon      = sel.passTrigger("crossMuon" );
    myEvent.triggerDoubleMuon = sel.passTrigger("doubleMuon");
    myEvent.triggerDoubleElec = sel.passTrigger("doubleElec");
    myEvent.triggerMuonElec   = sel.passTrigger("muonElec"  );  

    // #####################
    // #   Leptons infos   #
    // #####################

    myEvent.numberOfLepton          = sel.getTheNumberOfSelectedLeptons();
    myEvent.leadingLepton           = sel.getTheLeadingLepton();
    myEvent.leadingLeptonPDGId      = sel.getTheLeadingLeptonPDGId();
    myEvent.secondLepton            = sel.getTheSecondLepton();
    myEvent.secondLeptonPDGId       = sel.getTheSecondLeptonPDGId();
    float leptonCharge;
    if (myEvent.leadingLeptonPDGId > 0) leptonCharge = -1.0;
    else                                leptonCharge = +1.0;
    myEvent.isolatedTrackVeto       = sel.GetSUSYstopIsolatedTrackVeto(myEvent.leadingLepton,leptonCharge);
    myEvent.tauVeto                 = sel.GetSUSYstopTauVeto(myEvent.leadingLepton,leptonCharge);

    // ####################
    // #  Fill jets info  #
    // ####################

    myEvent.nJets        = sel.GetJetsForAna().size();
    myEvent.nBTag        = sel.GetBJetsForAna().size();

    myEvent.jets.clear();
    myEvent.jets_partonFlav.clear();
    myEvent.jets_CSV_raw.clear();
    myEvent.jets_CSV_reshaped.clear();
    myEvent.jets_CSV_reshapedUpBC.clear();
    myEvent.jets_CSV_reshapedDownBC.clear();
    myEvent.jets_CSV_reshapedUpLight.clear();
    myEvent.jets_CSV_reshapedDownLight.clear();

    std::vector<IPHCTree::NTJet> jets = sel.GetJetsForAna();
    for (unsigned int i = 0 ; i < jets.size() ; i++)
    {
        myEvent.jets.push_back(jets[i].p4);
        myEvent.jets_partonFlav.push_back(jets[i].partonFlavour);

        myEvent.jets_CSV_raw.push_back(              jets[i].bTag["combinedSecondaryVertexBJetTags"]                 );
        myEvent.jets_CSV_reshaped.push_back(         jets[i].bTag["zz1combinedSecondaryVertexBJetTagsReshapeNominal"]  );
        myEvent.jets_CSV_reshapedUpBC.push_back(     jets[i].bTag["zz2combinedSecondaryVertexBJetTagsReshapeUpBC"]     );
        myEvent.jets_CSV_reshapedDownBC.push_back(   jets[i].bTag["zz3combinedSecondaryVertexBJetTagsReshapeDownBC"]   );
        myEvent.jets_CSV_reshapedUpLight.push_back(  jets[i].bTag["zz4combinedSecondaryVertexBJetTagsReshapeUpLight"]  );
        myEvent.jets_CSV_reshapedDownLight.push_back(jets[i].bTag["zz5combinedSecondaryVertexBJetTagsReshapeDownLight"]);
    }

    // #############################
    // #  "High-level" variables   #
    // #############################

    myEvent.MET                   = sel.Met();
    myEvent.MT                    = sel.MT_wleptonic();
    myEvent.deltaPhiMETJets       = sel.DPhi_MET_leadingJets();
    myEvent.hadronicChi2          = sel.HadronicChi2(runningOnData);
    myEvent.MT2W                  = sel.MT2W();
    myEvent.HTRatio               = sel.HT_ratio();
    myEvent.HT                    = sel.HT();
    myEvent.METoverSqrtHT         = myEvent.MET / sqrt(myEvent.HT);
    myEvent.leadingLeptonPt       = myEvent.leadingLepton.Pt();
    myEvent.HTPlusLeptonPtPlusMET = myEvent.HT + myEvent.leadingLeptonPt + myEvent.MET;
    TLorentzVector leadingBJet    = sel.leadingBJet();
    myEvent.leadingBPt            = leadingBJet.Pt();
    myEvent.deltaRLeptonLeadingB  = leadingBJet.DeltaR(myEvent.leadingLepton);
    myEvent.leadingJetPt          = sel.leadingJet().P();
    myEvent.M3b                   = sel.M3b();
    myEvent.Mlb                   = (myEvent.leadingLepton + sel.leadingJetByCSV(runningOnData)).M();
    myEvent.Mlb_hemi              = (myEvent.leadingLepton + sel.bJetClosestToLeadingLepton()).M();

    // ####################
    // #   Signal infos   #
    // ####################

    if ((datasetName.find("T2tt") != string::npos) 
    ||  (datasetName.find("T2bw")  != string::npos)) 
    {
        myEvent.mStop       = stopMCinfo->GetStopMass();
        myEvent.mNeutralino = stopMCinfo->GetNeutralinoMass();

        if (datasetName.find("T2tt") != string::npos)           myEvent.mCharginoParameter = -1.0;
        else if (datasetName.find("T2bw-025") != string::npos)  myEvent.mCharginoParameter = 0.25;
        else if (datasetName.find("T2bw-050") != string::npos)  myEvent.mCharginoParameter = 0.50; 
        else if (datasetName.find("T2bw-075") != string::npos)  myEvent.mCharginoParameter = 0.75;
    }
    else
    {
        myEvent.mStop              = -1.0;
        myEvent.mNeutralino        = -1.0;
        myEvent.mCharginoParameter = -1.0;
    }

    // ################################################
    // #  Weights and weighting-related informations  #
    // ################################################

    // Cross section

    if ((datasetName.find("T2tt") != string::npos) 
     || (datasetName.find("T2bw") != string::npos))
    {
        myEvent.crossSection          = stopCrossSection(myEvent.mStop).first;

        TH2F* signalMap = 0;

        if (datasetName.find("T2tt") != string::npos)          signalMap = mapT2tt; 
        else if (datasetName.find("T2bw-025") != string::npos) signalMap = mapT2bw025;
        else if (datasetName.find("T2bw-050") != string::npos) signalMap = mapT2bw050;
        else if (datasetName.find("T2bw-075") != string::npos) signalMap = mapT2bw075;
       
        myEvent.numberOfInitialEvents = signalMap->GetBinContent(signalMap->FindBin(myEvent.mStop,myEvent.mNeutralino));
    }
    else
    {
        myEvent.crossSection          = dataset->Xsection();
        myEvent.numberOfInitialEvents = dataset->getNumberOfEventsBeforeMTSkimmer();
    }
    
    myEvent.weightCrossSection = myEvent.crossSection / myEvent.numberOfInitialEvents;

    // Pile-up

    // Don't take PU weight into account for data
    if (runningOnData)
    {
        myEvent.numberOfTruePU = 1.0;
        myEvent.weightPileUp = 1.0;
    }
    else
    {

        myEvent.numberOfTruePU = sel.getTnpv();
        myEvent.weightPileUp = sel.getPileUpWeight(myEvent.numberOfTruePU,runningOnData);
    }

    myEvent.numberOfPrimaryVertices = sel.GetVertex().size();;

    // ISR

    float ISRboost = 0.0;
    if ((datasetName.find("T2tt") != string::npos) 
     || (datasetName.find("T2bw") != string::npos))
    {
        TLorentzVector StopStopBar;
        for (unsigned int i = 0 ; i < MCParticles.size() ; i++)  
            if (abs(MCParticles[i].id) == 1000006) StopStopBar += MCParticles[i].p4;
        ISRboost = StopStopBar.Pt();
    }
    else if ((datasetName == "ttbar"                      )
          || (datasetName == "ttbar_madgraph_1l"          )
          || (datasetName == "ttbar_madgraph_2l"          )
          || (datasetName == "ttbar_madgraph_mass166-5"   )
          || (datasetName == "ttbar_madgraph_mass178-5"   )
          || (datasetName == "ttbar_madgraph_matchingdown")
          || (datasetName == "ttbar_madgraph_matchingup"  )
          || (datasetName == "ttbar_madgraph_scaledown"   )
          || (datasetName == "ttbar_madgraph_scaleup"     ))
    {
        TLorentzVector TopTopBar;
        for (unsigned int i = 0 ; i < MCParticles.size() ; i++)  
            if (abs(MCParticles[i].id) == 6) TopTopBar += MCParticles[i].p4;
        ISRboost = TopTopBar.Pt();
    }

    myEvent.weightISRmodeling = 1.0;
    if ((ISRboost > 120.0) && (ISRboost < 150.0)) myEvent.weightISRmodeling = 0.95;
    if ((ISRboost > 150.0) && (ISRboost < 250.0)) myEvent.weightISRmodeling = 0.90;
    if  (ISRboost > 250.0)                        myEvent.weightISRmodeling = 0.80;

    // Top Pt weight
    
    myEvent.weightTopPt = 1.0;
    if ((datasetName == "ttbar"                      )
     || (datasetName == "ttbar_madgraph_1l"          )
     || (datasetName == "ttbar_madgraph_2l"          )
     || (datasetName == "ttbar_madgraph_mass166-5"   )
     || (datasetName == "ttbar_madgraph_mass178-5"   )
     || (datasetName == "ttbar_madgraph_matchingdown")
     || (datasetName == "ttbar_madgraph_matchingup"  )
     || (datasetName == "ttbar_madgraph_scaledown"   )
     || (datasetName == "ttbar_madgraph_scaleup"     ))
    {
        float TopPt = 0.0;
        for (unsigned int i = 0 ; i < MCParticles.size() ; i++)  
            if (MCParticles[i].id == 6) { TopPt = MCParticles[i].p4.Pt(); break; }

        myEvent.weightTopPt = exp(0.156 - 0.00137 * TopPt); 
    }
    
    // Trigger efficiency weight

    if (abs(myEvent.leadingLeptonPDGId) == 11) 
        myEvent.weightTriggerEfficiency = singleLeptonTriggerWeight(11,myEvent.leadingLepton.Pt(),
                                                                       myEvent.leadingLepton.Eta());
    else if ((abs(myEvent.leadingLeptonPDGId) == 13) && (myEvent.leadingLepton.Pt() > 26))
        myEvent.weightTriggerEfficiency = singleLeptonTriggerWeight(13,myEvent.leadingLepton.Pt(),
                                                                       myEvent.leadingLepton.Eta());
    else if (myEvent.nJets >= 4)
        myEvent.weightTriggerEfficiency = crossTriggerWeight(myEvent.leadingLepton.Pt(),
                                                             myEvent.leadingLepton.Eta(),
                                                             myEvent.jets[3].Pt());
    else
        myEvent.weightTriggerEfficiency = -1.0;

    // Signal polarization

    if (datasetName.find("T2tt") != string::npos) 
    {
        myEvent.weightT2ttLeftHanded  = Reweight_Stop_to_TopChi0(MCParticles, 0., -1);
        myEvent.weightT2ttRightHanded = Reweight_Stop_to_TopChi0(MCParticles, 0.,  1);
    }
    else
    {
        myEvent.weightT2ttLeftHanded  = 1.0;
        myEvent.weightT2ttRightHanded = 1.0; 
    }

    if (datasetName.find("T2bw") != string::npos)
    {
        myEvent.weightT2bwPolarization_lr = Reweight_T2bW( 0      , 0      , MCParticles );
        myEvent.weightT2bwPolarization_ls = Reweight_T2bW( 0      , PI/4.0 , MCParticles );
        myEvent.weightT2bwPolarization_ll = Reweight_T2bW( 0      , PI/2.0 , MCParticles );
        myEvent.weightT2bwPolarization_sr = Reweight_T2bW( PI/4.0 , 0      , MCParticles );
        myEvent.weightT2bwPolarization_ss = Reweight_T2bW( PI/4.0 , PI/4.0 , MCParticles );
        myEvent.weightT2bwPolarization_sl = Reweight_T2bW( PI/4.0 , PI/2.0 , MCParticles );
        myEvent.weightT2bwPolarization_rr = Reweight_T2bW( PI/2.0 , 0      , MCParticles );
        myEvent.weightT2bwPolarization_rs = Reweight_T2bW( PI/2.0 , PI/4.0 , MCParticles );
        myEvent.weightT2bwPolarization_rl = Reweight_T2bW( PI/2.0 , PI/2.0 , MCParticles );
    }
    else
    {
        myEvent.weightT2bwPolarization_lr = 1.0; 
        myEvent.weightT2bwPolarization_ls = 1.0;
        myEvent.weightT2bwPolarization_ll = 1.0;
        myEvent.weightT2bwPolarization_sr = 1.0;
        myEvent.weightT2bwPolarization_ss = 1.0;
        myEvent.weightT2bwPolarization_sl = 1.0;
        myEvent.weightT2bwPolarization_rr = 1.0;
        myEvent.weightT2bwPolarization_rs = 1.0;
        myEvent.weightT2bwPolarization_rl = 1.0;
    }

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

    // ################
    // #  Fill W-tag  #
    // ################         

    myEvent.nWTag = 0;
    myEvent.leadingWjetPt = -1.0;
    std::vector<IPHCTree::NTJet> WCand = sel.GetHeavyTagJets();
    for (unsigned int i = 0 ; i < WCand.size() ; i++)
    {
        // Pt
        if (WCand[i].p4.Pt() < 200) continue;

        // Mass window
        if ((WCand[i].p4.M() < 60) || (WCand[i].p4.M() > 100)) continue;

        // Lepton overlap removal
        if (WCand[i].p4.DeltaR(myEvent.leadingLepton) < 0.6) continue; 

        // B-jet overlap removal
        float minDeltaRBJet = 99.0;
        for (int j = 0 ; j < myEvent.nBTag ; j++)
        {
            if (minDeltaRBJet > WCand[i].p4.DeltaR(sel.GetBJetsForAna()[j].p4));
            minDeltaRBJet = WCand[i].p4.DeltaR(sel.GetBJetsForAna()[j].p4);
        }
        if (minDeltaRBJet > 0.6)
        {
            myEvent.nWTag = 1.0;
            if (myEvent.leadingWjetPt < WCand[i].p4.Pt())
                myEvent.leadingWjetPt = WCand[i].p4.Pt();
        }

    }
    // #####################################
    // #  Info for studies of systematics  #
    // #####################################

        // Non selected jets

    myEvent.nonSelectedJets.clear();     
    myEvent.nonSelectedJets_CSV_raw.clear();    
    myEvent.nonSelectedJets_CSV_reshaped.clear(); 
    myEvent.nonSelectedJets_partonFlav.clear();

    std::vector<IPHCTree::NTJet> goodJets = sel.GetGoodJets();
    for (unsigned int i = 0 ; i < goodJets.size() ; i++)
    {
        bool goodJetIsSelected = false;
        for (unsigned int j = 0 ; j < jets.size() ; j++)
        {
            if (jets[j].p4.Pt() == goodJets[i].p4.Pt()) goodJetIsSelected = true;
        }

        if (goodJetIsSelected) continue;

        myEvent.nonSelectedJets.push_back(goodJets[i].p4);
        myEvent.nonSelectedJets_CSV_raw.push_back(goodJets[i].bTag["combinedSecondaryVertexBJetTags"]);
        myEvent.nonSelectedJets_CSV_reshaped.push_back(goodJets[i].bTag["zz1combinedSecondaryVertexBJetTagsReshapeNominal"]); 
        myEvent.nonSelectedJets_partonFlav.push_back(goodJets[i].partonFlavour);
    }

        // Non selected leptons
DEBUG_MSG << endl;
    myEvent.nonSelectedLeptons.clear();
    myEvent.nonSelectedLeptonsPDGId.clear();
DEBUG_MSG << endl;

    std::vector<IPHCTree::NTElectron> goodElectrons = sel.GetGoodElectrons();
    std::vector<IPHCTree::NTMuon>     goodMuons = sel.GetGoodMuons();
DEBUG_MSG << endl;

    for (unsigned i = 0 ; i < goodElectrons.size() ; i++)
    {
DEBUG_MSG << endl;
        bool goodElectronIsSelected = false;
        if (goodElectrons[i].p4.Pt() == myEvent.leadingLepton.Pt()) goodElectronIsSelected = true; 
        if (goodElectrons[i].p4.Pt() == myEvent.secondLepton.Pt()) goodElectronIsSelected = true;

        if (goodElectronIsSelected) continue;
DEBUG_MSG << endl;

        myEvent.nonSelectedLeptons.push_back(goodElectrons[i].p4);
        myEvent.nonSelectedLeptonsPDGId.push_back(goodElectrons[i].charge * (-11));
DEBUG_MSG << endl;
    }

    for (unsigned i = 0 ; i < goodMuons.size() ; i++)
    {
        bool goodMuonIsSelected = false;
        if (goodMuons[i].p4.Pt() == myEvent.leadingLepton.Pt()) goodMuonIsSelected = true; 
        if (goodMuons[i].p4.Pt() == myEvent.secondLepton.Pt()) goodMuonIsSelected = true;

        if (goodMuonIsSelected) continue;

        myEvent.nonSelectedLeptons.push_back(goodMuons[i].p4);
        myEvent.nonSelectedLeptonsPDGId.push_back(goodMuons[i].charge * (-13));
    }

        // Raw MET
        
    myEvent.rawPFMET = sel.rawMet();

        // PDF infos

    if (runningOnData == false)
    {
        myEvent.x_firstIncomingParton       = mcInfo.x.first;
        myEvent.x_secondIncomingParton      = mcInfo.x.second;
        myEvent.flavor_firstIncomingParton  = mcInfo.partonFlavor.first;
        myEvent.flavor_secondIncomingParton = mcInfo.partonFlavor.second;
        myEvent.scalePDF                    = mcInfo.Q_scale;
    }

    sel.doObjectSelection(runningOnData,1);
    sel.FillKinematicP4();
   
    myEvent.MET_JESup                       = sel.Met();
    myEvent.MT_JESup                        = sel.MT_wleptonic();
    myEvent.deltaPhiMETJets_JESup           = sel.DPhi_MET_leadingJets();
    myEvent.hadronicChi2_JESup              = sel.HadronicChi2(runningOnData);
    myEvent.MT2W_JESup                      = sel.MT2W();
    myEvent.HTRatio_JESup                   = sel.HT_ratio();
    myEvent.HT_JESup                        = sel.HT();
    myEvent.METoverSqrtHT_JESup             = myEvent.MET_JESup / sqrt(myEvent.HT_JESup);
    leadingBJet = sel.leadingBJet();
    myEvent.leadingBPt_JESup                = leadingBJet.Pt();
    myEvent.deltaRLeptonLeadingB_JESup = leadingBJet.DeltaR(myEvent.leadingLepton);
    myEvent.leadingJetPt_JESup              = sel.leadingJet().P();
    myEvent.M3b_JESup                       = sel.M3b();
    myEvent.Mlb_JESup                       = (myEvent.leadingLepton + sel.leadingJetByCSV(runningOnData)).M();
    myEvent.Mlb_hemi_JESup                  = (myEvent.leadingLepton + sel.bJetClosestToLeadingLepton()).M();
    myEvent.HTPlusLeptonPtPlusMET_JESup     = myEvent.HT_JESup + myEvent.leadingLeptonPt + myEvent.MET_JESup;
    myEvent.nJets_JESup                     = sel.GetJetsForAna().size();

    if (abs(myEvent.leadingLeptonPDGId) == 11) 
        myEvent.weightTriggerEfficiency_JESup = singleLeptonTriggerWeight(11,myEvent.leadingLepton.Pt(),
                                                                             myEvent.leadingLepton.Eta());
    else if ((abs(myEvent.leadingLeptonPDGId) == 13) && (myEvent.leadingLepton.Pt() > 26))
        myEvent.weightTriggerEfficiency_JESup = singleLeptonTriggerWeight(13,myEvent.leadingLepton.Pt(),
                                                                             myEvent.leadingLepton.Eta());
    else if (myEvent.nJets_JESup >= 4)
        myEvent.weightTriggerEfficiency_JESup = crossTriggerWeight(myEvent.leadingLepton.Pt(),
                                                                   myEvent.leadingLepton.Eta(),
                                                                   myEvent.jets[3].Pt());
    else
        myEvent.weightTriggerEfficiency_JESup = -1.0;

    sel.doObjectSelection(runningOnData,-1);
    sel.FillKinematicP4();
    
    myEvent.MET_JESdown                     = sel.Met();
    myEvent.MT_JESdown                      = sel.MT_wleptonic();
    myEvent.deltaPhiMETJets_JESdown         = sel.DPhi_MET_leadingJets();
    myEvent.hadronicChi2_JESdown            = sel.HadronicChi2(runningOnData);
    myEvent.MT2W_JESdown                    = sel.MT2W();
    myEvent.HTRatio_JESdown                 = sel.HT_ratio();
    myEvent.HT_JESdown                      = sel.HT();
    myEvent.METoverSqrtHT_JESdown           = myEvent.MET_JESdown / sqrt(myEvent.HT_JESdown);
    leadingBJet = sel.leadingBJet();
    myEvent.leadingBPt_JESdown              = leadingBJet.Pt();
    myEvent.deltaRLeptonLeadingB_JESdown = leadingBJet.DeltaR(myEvent.leadingLepton);
    myEvent.leadingJetPt_JESdown            = sel.leadingJet().P();
    myEvent.M3b_JESdown                     = sel.M3b();
    myEvent.Mlb_JESdown                     = (myEvent.leadingLepton + sel.leadingJetByCSV(runningOnData)).M();
    myEvent.Mlb_hemi_JESdown                = (myEvent.leadingLepton + sel.bJetClosestToLeadingLepton()).M();
    myEvent.HTPlusLeptonPtPlusMET_JESdown   = myEvent.HT_JESdown + myEvent.leadingLeptonPt + myEvent.MET_JESdown;
    myEvent.nJets_JESdown                   = sel.GetJetsForAna().size();

    if (abs(myEvent.leadingLeptonPDGId) == 11) 
        myEvent.weightTriggerEfficiency_JESdown = singleLeptonTriggerWeight(11,myEvent.leadingLepton.Pt(),
                                                                               myEvent.leadingLepton.Eta());
    else if ((abs(myEvent.leadingLeptonPDGId) == 13) && (myEvent.leadingLepton.Pt() > 26))
        myEvent.weightTriggerEfficiency_JESdown = singleLeptonTriggerWeight(13,myEvent.leadingLepton.Pt(),
                                                                               myEvent.leadingLepton.Eta());
    else if (myEvent.nJets_JESdown >= 4)
        myEvent.weightTriggerEfficiency_JESdown = crossTriggerWeight(myEvent.leadingLepton.Pt(),
                                                                     myEvent.leadingLepton.Eta(),
                                                                     myEvent.jets[3].Pt());
    else
        myEvent.weightTriggerEfficiency_JESdown = -1.0;

    // ###############################
    // #  Add the event to the tree  #
    // ###############################

    theTree->Fill();

    return true;
}

bool badSignalEventFilter(string datasetName,StopMCinfo* stopMCinfo)
{

    if ((datasetName.find("T2tt") != string::npos)
     || (datasetName.find("T2bw") != string::npos))
    {
        if ((datasetName.find("withLSP0")  != string::npos)
         || (datasetName.find("LSP0to700") != string::npos))
        {
            float mStop       = stopMCinfo->GetStopMass();
            float mNeutralino = stopMCinfo->GetNeutralinoMass();

            if (mNeutralino - int(mNeutralino) > 0.000001) return false;
            if (mStop       - int(mStop)       > 0.000001) return false;
            if (int(mNeutralino) % 25 != 0) return false;
            if (int(mStop)       % 25 != 0) return false;

            if ((datasetName.find("withLSP0") != string::npos) && (mNeutralino == 500)) return false;
        }

    }

    return true;
}



#endif

