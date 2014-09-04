#include "../interface/MonotopMCinfo.h"


MonotopMCinfo::MonotopMCinfo()
{
  Reset();
}

void MonotopMCinfo::Reset()
{
    mResonant_  = -9999;
    mInvisible_ = -9999;
    event_ = 0;
    resonant_.clear();
    invisible_.clear();
    top_.clear();
    HadronicTop_.clear();
    W_.clear();
    HadronicW_.clear();
    lepton_.clear();
    neutrino_.clear();
    hadronicTau_.clear();
    TauDecay_.clear();
}

void MonotopMCinfo::LoadEvent(IPHCTree::NTEvent* evt)
{
    Reset();
    event_ = evt;
    // loop other variables
    for (unsigned int ip = 0; ip< event_->mc.genParticles.size(); ip++)
    {
        //loop for Monotops
        if(( abs(event_->mc.genParticles[ip].id) == 9000001 || abs(event_->mc.genParticles[ip].id) == 9000002 || abs(event_->mc.genParticles[ip].id) == 9000003) && event_->mc.genParticles[ip].isStatus3)
        {
            invisible_.push_back(&event_->mc.genParticles[ip]);
            mInvisible_ = event_->mc.genParticles[ip].p4.M();
        }
        if(( abs(event_->mc.genParticles[ip].id) == 9000004 || abs(event_->mc.genParticles[ip].id) == 9000005) && event_->mc.genParticles[ip].isStatus3)
        {
            resonant_.push_back(&event_->mc.genParticles[ip]);
            mResonant_ = event_->mc.genParticles[ip].p4.M();
        }

        if( abs(event_->mc.genParticles[ip].id) == 6 && event_->mc.genParticles[ip].isStatus3)
        {
            top_.push_back(&event_->mc.genParticles[ip]);
        }
        if(abs(event_->mc.genParticles[ip].id) == 24 && event_->mc.genParticles[ip].isStatus3 )
        {
            W_.push_back(&event_->mc.genParticles[ip]);
        }
        //looking for a lepton coming from a W
        if( (abs(event_->mc.genParticles[ip].id)==11 || abs(event_->mc.genParticles[ip].id)==13 || abs(event_->mc.genParticles[ip].id)==15) &&
            (event_->mc.genParticles[ip].motherIndex_ >=0 && event_->mc.genParticles[ip].isStatus3 && abs(event_->mc.genParticles[event_->mc.genParticles[ip].motherIndex_].id) == 24))
        {
            lepton_.push_back(&event_->mc.genParticles[ip]);
        }
        //looking for a lepton coming from a W
        if( (abs(event_->mc.genParticles[ip].id)==12 || abs(event_->mc.genParticles[ip].id)==14 || abs(event_->mc.genParticles[ip].id)==16) &&
            (event_->mc.genParticles[ip].motherIndex_ >=0 && event_->mc.genParticles[ip].isStatus3 && abs(event_->mc.genParticles[event_->mc.genParticles[ip].motherIndex_].id) == 24))
        {
            lepton_.push_back(&event_->mc.genParticles[ip]);
        }
        //looking for a TauDecay coming from a W
        if( (abs(event_->mc.genParticles[ip].id)==11 || abs(event_->mc.genParticles[ip].id)==13 || abs(event_->mc.genParticles[ip].id)==15) &&
            (event_->mc.genParticles[ip].motherIndex_ >=0 && event_->mc.genParticles[ip].isStatus3 && abs(event_->mc.genParticles[event_->mc.genParticles[ip].motherIndex_].id) == 15) &&
            (event_->mc.genParticles[event_->mc.genParticles[ip].motherIndex_].motherIndex_ >=0) &&
            abs(event_->mc.genParticles[event_->mc.genParticles[event_->mc.genParticles[ip].motherIndex_].motherIndex_].id) == 24)
        {
            TauDecay_.push_back(&event_->mc.genParticles[ip]);
        }
    }
    // End of loop over particles

        // Filling hadronicTau
    hadronicTau_ = lepton_;
    for(unsigned int i=0;i<TauDecay_.size();i++)
    {
        for(unsigned int j=hadronicTau_.size();j>0;j--)
        {
            if(&(event_->mc.genParticles[TauDecay_[i]->motherIndex_]) == hadronicTau_[j])
                hadronicTau_.erase(hadronicTau_.begin()+j);
        }
    }

    
    //Looking for hadronic W
    HadronicW_ = W_;
    for(unsigned int i=0;i<lepton_.size();i++)
    {
        for(unsigned int j=0;j<HadronicW_.size();j++){
            if(&(event_->mc.genParticles[lepton_[i]->motherIndex_]) == HadronicW_[j])
            HadronicW_.erase(HadronicW_.begin()+j);
            break;
        }
            
    }

    //Looking for hadronic top
    for(unsigned int i=0;i<HadronicW_.size();i++)
    {
        if(abs(event_->mc.genParticles[HadronicW_[i]->motherIndex_].id) == 6)
            HadronicTop_.push_back(&(event_->mc.genParticles[HadronicW_[i]->motherIndex_]));
    }
}


std::string MonotopMCinfo::Bool2Text(const bool& value) const{
    if(value) return string(" True ");
    else return string(" False ");
}


void MonotopMCinfo::Print() const{
    cout<<"#############################"<<endl;
    cout<<"#   MonotopMCinfo::Print       #"<<endl;
    cout<<"#############################"<<endl;
    cout<<"# m(resonant) = "<<mResonant_<<" m(invisible) = "<<mInvisible_<<endl;
    cout<<"#############################"<<endl;
}


