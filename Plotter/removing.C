#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TTreePlayer.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>

#include <vector>
#include "math.h"

#include <TMultiGraph.h>

using namespace std;



void  removing(){
  

  TFile *f1 = TFile::Open("allData.root","UPDATE");
  TFile *f2 = TFile::Open("DY+Jets.root","READ");
  TFile *f3 = TFile::Open("tt.root","READ");
  TFile *f4 = TFile::Open("VV.root","READ");
  

 
  TH1F *NumeratorS = (TH1F*)f1->Get("METCut/Tau1MetMt");
  
  TH1F *NumeratorDY = (TH1F*)f2->Get("METCut/Tau1MetMt");
  
  TH1F *Numeratortt = (TH1F*)f3->Get("METCut/Tau1MetMt");
  
  TH1F *NumeratorVV = (TH1F*)f4->Get("METCut/Tau1MetMt");
 
 
  NumeratorS->Add(NumeratorS, NumeratorDY, 1, -1);
  NumeratorS->Add(NumeratorS, Numeratortt, 1, -1);
  NumeratorS->Add(NumeratorS, NumeratorVV, 1, -1); 

  
  f1->Write("",TObject::kOverwrite);    
  f1->Close();


  TFile *f6 = TFile::Open("allData.root","READ");
  TH1F *WJets = (TH1F*)f6->Get("METCut/Tau1MetMt");
  double integral_1 = WJets->Integral();
  cout << "Expected integral: " << integral_1 << endl;

  TFile *f5 = TFile::Open("W+Jets.root","READ");
  TH1F *NumeratorW = (TH1F*)f5->Get("METCut/Muon1MetMt");
  double integral = NumeratorW->Integral();
  cout << "Emulated integral: " << integral << endl;

  cout << "Scale Factor: " << integral_1/integral << endl; 

}  
