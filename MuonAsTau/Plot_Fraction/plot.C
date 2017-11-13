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

vector<string> in_put; 
vector<string> folder;
std::vector<string> Histo;


void fill(){
  
  in_put.push_back("Tau_Inf.root");
   
  folder.push_back("WJetsToLNu_HT-70To100"); 
  folder.push_back("WJetsToLNu_HT-100To200");
  folder.push_back("WJetsToLNu_HT-200To400");
  folder.push_back("WJetsToLNu_HT-400To600");
  folder.push_back("WJetsToLNu_HT-600To800");
  folder.push_back("WJetsToLNu_HT-800To1200");
  folder.push_back("WJetsToLNu_HT-1200To2500");
  folder.push_back("WJetsToLNu_HT-2500ToInf"); 
  
  Histo.push_back("GenTauFraction");
  Histo.push_back("GenTauResolution");
  Histo.push_back("GenTauFractionR1");
  Histo.push_back("GenTauFractionR2");
  Histo.push_back("GenTauFractionR3");
  Histo.push_back("GenTauFractionR4");
  Histo.push_back("GenTauFractionR5");
  Histo.push_back("GenTauIDRecoPt");
//  Histo.push_back("GenTauIDPt");
  Histo.push_back("GenTauMatchedPt");
//  Histo.push_back("GenHadTauPt"); 
  

}


void plot(){

  cout << "working" << endl;
  fill();


  TCanvas *c1 = new TCanvas("c1", "c1",245,158,756,727);
  c1->Range(-20.38653,-0.005764521,153.3666,0.04198848);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.1173305);
  c1->SetRightMargin(0.01937567);
  c1->SetTopMargin(0.01937407);
  c1->SetBottomMargin(0.1207154);
  c1->SetFrameBorderMode(0);
  c1->SetFrameBorderMode(0);

   TFile* file1 = TFile::Open(in_put[0].c_str(), "READ");
  
    
  for (int i = 0 ; i < 9; i++ ){
   TH1F *h0 = (TH1F*)file1->Get((folder[0]+"/"+Histo[i]).c_str());
   TH1F *h1 = (TH1F*)file1->Get((folder[1]+"/"+Histo[i]).c_str());
   TH1F *h2 = (TH1F*)file1->Get((folder[2]+"/"+Histo[i]).c_str());
   TH1F *h3 = (TH1F*)file1->Get((folder[3]+"/"+Histo[i]).c_str());
   TH1F *h4 = (TH1F*)file1->Get((folder[4]+"/"+Histo[i]).c_str());
   TH1F *h5 = (TH1F*)file1->Get((folder[5]+"/"+Histo[i]).c_str());
   TH1F *h6 = (TH1F*)file1->Get((folder[6]+"/"+Histo[i]).c_str());
   TH1F *h7 = (TH1F*)file1->Get((folder[7]+"/"+Histo[i]).c_str());
 
   h0->SetLineColor(1);
   h1->SetLineColor(2);
   h2->SetLineColor(3);
   h3->SetLineColor(4);
   h4->SetLineColor(5);
   h5->SetLineColor(6);
   h6->SetLineColor(7);
   h7->SetLineColor(8);
 
   h0->Draw();
   h0->SetTitle("");
   h0->SetStats(kFALSE);

    h0->GetYaxis()->SetTitle("a.u.");
   if(i==0)   h0->GetXaxis()->SetTitle("p_{T}(#tau_{h}^{gen})/p_{T}(#tau^{gen}) [GeV]");
   else if(i==1) h0->GetXaxis()->SetTitle("(p_{T}(#tau_{Reco})-p_{T}(#tau_{h}^{gen}))/p_{T}(#tau_{h}^{gen}) [GeV]");
   else if (i==7){ 
   h0->GetXaxis()->SetRangeUser(0. ,500.);
   h0->GetXaxis()->SetTitle("ID efficiency");
   h0->GetYaxis()->SetRangeUser(0.8 ,1.1); 
   h0->GetYaxis()->SetTitle("");
   }
   else if (i==8) {
   h0->GetXaxis()->SetTitle("Matching efficiency");
   h0->GetXaxis()->SetRangeUser(0. ,500.);
   h0->GetYaxis()->SetRangeUser(0.7 ,1.1); 
   h0->GetYaxis()->SetTitle("");   
   }
   else h0->GetXaxis()->SetTitle("p_{T}(#tau_{Reco})/p_{T}(#tau^{gen}) [GeV]");
 
   h0->GetXaxis()->SetTitleOffset(1);
   h0->GetXaxis()->SetTitleSize(0.06); 
   h0->GetYaxis()->SetTitleOffset(1.0);
   h0->GetYaxis()->SetTitleSize(0.06);
   h1->Draw("same");
   h2->Draw("same");
   h3->Draw("same");
   h4->Draw("same");
   h5->Draw("same");
   h6->Draw("same");
   h7->Draw("same");

  TLegend *leg = new TLegend(0.729443,0.1405797,0.969496,0.3913043,NULL,"brNDC");
  leg->SetBorderSize(1);
  leg->SetTextFont(62);
  leg->SetTextSize(0.04);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->AddEntry(h0, "HT 70-100");
  leg->AddEntry(h1, "HT 100-200");
  leg->AddEntry(h2, "HT 200-400");
  leg->AddEntry(h3, "HT 400-600");
  leg->AddEntry(h4, "HT 600-800");
  leg->AddEntry(h5, "HT 800-1200");
  leg->AddEntry(h6, "HT 1200-2500");
  leg->AddEntry(h7, "HT 2500-Inf");
  leg->Draw();
 
  c1->SaveAs(("templates/"+Histo[i]+".pdf").c_str());
  }
 
}
