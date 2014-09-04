//+______________________________________________________________________________

// Generate weights based on two input distributions, intended and generated



#include <TF1.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>


void Reweight_Gen() {

 TH1F* PU_intended = new TH1F("PU_intended","Intended pileup distribution (i.e. Data)",25,-0.5,24.5);
 TH1F* PU_generated = new TH1F("PU_generated","Generated pileup distribution (i.e., MC)",25,-0.5,24.5);


  double x;

  // "Flat10+Tail distribution taken directly from MixingModule input


  Double_t Summer2012_S10[60] = {

             2.560E-06,
             5.239E-06,
             1.420E-05,
             5.005E-05,
             1.001E-04,
             2.705E-04,
             1.999E-03,
             6.097E-03,
             1.046E-02,
             1.383E-02,
             1.685E-02,
             2.055E-02,
             2.572E-02,
             3.262E-02,
             4.121E-02,
             4.977E-02,
             5.539E-02,
             5.725E-02,
             5.607E-02,
             5.312E-02,
             5.008E-02,
             4.763E-02,
             4.558E-02,
             4.363E-02,
             4.159E-02,
             3.933E-02,
             3.681E-02,
             3.406E-02,
             3.116E-02,
             2.818E-02,
             2.519E-02,
             2.226E-02,
             1.946E-02,
             1.682E-02,
             1.437E-02,
             1.215E-02,
             1.016E-02,
             8.400E-03,
             6.873E-03,
             5.564E-03,
             4.457E-03,
             3.533E-03,
             2.772E-03,
             2.154E-03,
             1.656E-03,
             1.261E-03,
             9.513E-04,
             7.107E-04,
             5.259E-04,
             3.856E-04,
             2.801E-04,
             2.017E-04,
             1.439E-04,
             1.017E-04,
             7.126E-05,
             4.948E-05,
             3.405E-05,
             2.322E-05,
             1.570E-05,
             5.005E-06
  };

  // PU distribution from pileupCalc.py for 2012 SingleMu Data files


  Double_t PileUpinData[60];

  for (i = 0; i < 60; i++)
  {
        PileUpinData[i]
  }

  //Fill PU weight histogram

  
  for (int i=1;i<26;i++) {
    PU_generated->SetBinContent(i,probdistFlat10[i-1]);
    PU_intended->SetBinContent(i,TrueDist2011[i-1]);
  }

  TCanvas *can1 = new TCanvas("can1,","can1",1200,800);
  can1->Divide(2,2);

  can1->cd(1);
  PU_generated->SetLineColor(kRed);
  PU_intended->SetLineColor(kBlue);

  PU_intended->Draw();
  PU_generated->Draw("Same");


  can1->cd(2);
  PU_generated->Draw();


  can1->cd(3);
  PU_intended->DrawNormalized();

  TCanvas *can2 = new TCanvas("can2,","can2",1200,800);

  TH1F* PUnorm = dynamic_cast<TH1F*>(PU_intended->DrawNormalized());

  TH1F* Quotient = PUnorm;

  Quotient->Divide(PUnorm,PU_generated,1.0,1.0);

  std::cout << "Bin Contents" << std::endl;

  for(int ibin=1; ibin<26; ibin++){

    x = Quotient->GetBinContent(ibin);

      std::cout << ibin-1 << " " << x << std::endl;
    //std::cout <<  " " << x << "," <<  std::endl;


  }

  Quotient->SetNameTitle("Computed Weights","Computed Weights");
  Quotient->Draw();

}
