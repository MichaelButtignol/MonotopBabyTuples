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
    WtoLNU_.clear();
    ZtoLL_.clear();
//    lepton_.clear();
//    neutrino_.clear();
}

void MonotopMCinfo::LoadEvent(IPHCTree::NTEvent* evt)
{
    Reset();
    event_ = evt;

    // looking for Tops
    for (unsigned int ip = 0; ip< event_->mc.topAndDecays.size(); ip++)
    {
       top_.push_back(&event_->mc.topAndDecays[ip]);
    }

    // looking for Ws
    for (unsigned int ip = 0; ip< event_->mc.wAndDecays.size(); ip++)
    {
        if( (abs(event_->mc.wAndDecays[ip].mcLepId)==11 || abs(event_->mc.wAndDecays[ip].mcLepId)==13 || abs(event_->mc.wAndDecays[ip].mcLepId)==15) && (abs(event_->mc.wAndDecays[ip].mcMotherId) == 6) )
        { 
           WtoLNU_.push_back(&event_->mc.wAndDecays[ip]);
        }
    }

    // looking for Zs
    for (unsigned int ip = 0; ip< event_->mc.zAndDecays.size(); ip++)
    {
        if( (abs(event_->mc.zAndDecays[ip].Lep1_pdgID)==11 || abs(event_->mc.zAndDecays[ip].Lep1_pdgID)==13 || abs(event_->mc.zAndDecays[ip].Lep1_pdgID)==15) && (abs(event_->mc.zAndDecays[ip].Lep2_pdgID)==11 || abs(event_->mc.zAndDecays[ip].Lep2_pdgID)==13 || abs(event_->mc.zAndDecays[ip].Lep2_pdgID)==15) )
        {
           ZtoLL_.push_back(&event_->mc.zAndDecays[ip]);
        }
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


