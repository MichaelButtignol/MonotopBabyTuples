#ifndef MonotopMCInfo_h
#define MonotopMCInfo_h

// IPHC headers
#include "NTFormat/interface/NTEvent.h"

#include <vector>
#include <string>

class MonotopMCinfo 
{

 public:

  MonotopMCinfo(); 
  ~MonotopMCinfo(){;}

 void LoadEvent(IPHCTree::NTEvent* event);
 void Reset();

 //Output
 std::string Bool2Text(const bool& value) const;
 void Print() const;

 //Access to masses
 Float_t GetInvisibleMass()const {return mInvisible_;}
 Float_t GetResonantMass()const {return mResonant_;}

 //Add accessors to the objects
 vector<IPHCTree::NTGenParticle*> GetInvisibles() { return invisible_; }
 vector<IPHCTree::NTGenParticle*> GetResonants() { return resonant_; }
 vector<IPHCTree::NTGenParticle*> GetWs() { return W_; }
 vector<IPHCTree::NTGenParticle*> GetHadronicWs() { return HadronicW_; }
 vector<IPHCTree::NTGenParticle*> GetTops() { return top_; }
 vector<IPHCTree::NTGenParticle*> GetHadronicTops() { return HadronicTop_; }
 vector<IPHCTree::NTGenParticle*> GetLeptonsFromW() { return lepton_; }
 vector<IPHCTree::NTGenParticle*> GetNeutrinosFromW() { return neutrino_; }
 vector<IPHCTree::NTGenParticle*> GetHadronicTauFromW() { return hadronicTau_; }
 vector<IPHCTree::NTGenParticle*> GetLeptonicTauDecay() { return TauDecay_; }

 private:

  // Masses
  Float_t mResonant_;
  Float_t mInvisible_;


  // Pointer to event
  IPHCTree::NTEvent* event_;

  // List of particles
  vector<IPHCTree::NTGenParticle*> invisible_;
  vector<IPHCTree::NTGenParticle*> resonant_;
  vector<IPHCTree::NTGenParticle*> top_;
  vector<IPHCTree::NTGenParticle*> HadronicTop_;
  vector<IPHCTree::NTGenParticle*> W_;
  vector<IPHCTree::NTGenParticle*> HadronicW_;
  vector<IPHCTree::NTGenParticle*> lepton_;
  vector<IPHCTree::NTGenParticle*> neutrino_;
  vector<IPHCTree::NTGenParticle*> hadronicTau_;
  vector<IPHCTree::NTGenParticle*> TauDecay_;


};

#endif
