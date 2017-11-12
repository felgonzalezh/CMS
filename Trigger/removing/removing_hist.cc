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



void  removing_hist(){
  

  TFile *f1 = TFile::Open("data/Data.root","UPDATE");
  TFile *f2 = TFile::Open("data/DY+Jets.root","READ");
  TFile *f3 = TFile::Open("data/ttbar.root","READ");
  TFile *f4 = TFile::Open("data/VV.root","READ");
  

 
  TH1F *NumeratorS = (TH1F*)f1->Get("METCut/Met");
  TH1F *DenominatorS = (TH1F*)f1->Get("NRecoTriggers2/Met");
  
  TH1F *NumeratorDY = (TH1F*)f2->Get("METCut/Met");
  TH1F *DenominatorDY = (TH1F*)f2->Get("NRecoTriggers2/Met");
  
  TH1F *Numeratortt = (TH1F*)f3->Get("METCut/Met");
  TH1F *Denominatortt = (TH1F*)f3->Get("NRecoTriggers2/Met");

  TH1F *NumeratorVV = (TH1F*)f4->Get("METCut/Met");
  TH1F *DenominatorVV = (TH1F*)f4->Get("NRecoTriggers2/Met");
 
  NumeratorS->Add(NumeratorS, NumeratorDY, 1, -1);
  NumeratorS->Add(NumeratorS, Numeratortt, 1, -1);
  NumeratorS->Add(NumeratorS, NumeratorVV, 1, -1); 

  DenominatorS->Add(DenominatorS, DenominatorDY, 1, -1);
  DenominatorS->Add(DenominatorS, Denominatortt, 1, -1);
  DenominatorS->Add(DenominatorS, DenominatorVV, 1, -1); 
  
  f1->Write("",TObject::kOverwrite);    
  f1->Close();
}  
 
