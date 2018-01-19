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

vector<string> input_Data;
vector<string> input_MC;
vector<string> folder;
vector<string> Cut;
vector<string> Histo;
vector<string> Histo2;
vector<string> legend;


void setTDRStyle(){
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  //  tdrStyle->SetCanvasDefH(600); //Height of canvas
  //  tdrStyle->SetCanvasDefW(600); //Width of canvas
  //  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  //  tdrStyle->SetCanvasDefY(0);
  // For the Pad:
  //  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  //  tdrStyle->SetPadGridX(false);
  //  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  //  tdrStyle->SetGridStyle(3);
  //  tdrStyle->SetGridWidth(1);
  // For the frame:
  //  tdrStyle->SetFrameBorderMode(0);
  //  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  //  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  //  tdrStyle->SetHistFillColor(0);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  //  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
//  tdrStyle->SetEndErrorSize(0);


//  tdrStyle->SetErrorX(0.);


//  tdrStyle->SetErrorMarker(20);

  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  //  tdrStyle->SetFitFormat("5.4g");
  //tdrStyle->SetFuncColor(1);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat("e"); // To display the mean and RMS:   SetOptStat("mr");
  //tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatColor(kGray);
  //  tdrStyle->SetStatFont(42);

  tdrStyle->SetTextSize(11);
  //  tdrStyle->SetTextAlign(11);

  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  //  tdrStyle->SetStatBorderSize(0);
  tdrStyle->SetStatX(1.); //Starting position on X axis
  tdrStyle->SetStatY(1.); //Starting position on Y axis
  //  tdrStyle->SetStatFontSize(0.025); //Vertical Size
  tdrStyle->SetStatW(0.25); //Horizontal size 
  // tdrStyle->SetStatStyle(Style_t style = 1001);

  // Margins:
  tdrStyle->SetPadTopMargin(0.095);
  tdrStyle->SetPadBottomMargin(0.125);
  tdrStyle->SetPadLeftMargin(0.14);
  tdrStyle->SetPadRightMargin(0.1);

  // For the Global title:

  //  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  //  tdrStyle->SetTitleFontSize(0.05);
  tdrStyle->SetTitleH(0.045); // Set the height of the title box
  //tdrStyle->SetTitleW(0); // Set the width of the title box
  tdrStyle->SetTitleX(0.15); // Set the position of the title box
  tdrStyle->SetTitleY(1.0); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  tdrStyle->SetTitleBorderSize(0);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");

  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  //  tdrStyle->SetTitleXOffset(0.9);
  //  tdrStyle->SetTitleYOffset(1.0);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  //tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  //  tdrStyle->SetLabelSize(0.03, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  //  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);
  // Postscript options:
  // tdrStyle->SetPaperSize(15.,15.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);
  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();
}

void fill(){

input_Data.push_back("/home/alejandro/CMS/data/data_plot/Tau/allData");

input_MC.push_back("/home/alejandro/CMS/data/data_plot/Tau/VV");
input_MC.push_back("/home/alejandro/CMS/data/data_plot/Tau/DY+Jets");
input_MC.push_back("/home/alejandro/CMS/data/data_plot/Tau/tt");

input_MC.push_back("/home/alejandro/CMS/data/data_plot/ETau/W+Jets");

  Cut.push_back("NRecoTriggers1");
  Cut.push_back("NRecoTau1");
  Cut.push_back("NRecoMuon1"); 
  Cut.push_back("METCut"); 

  Histo.push_back("Tau1Pt");
  Histo.push_back("Tau1MetMt");
  Histo.push_back("Met");
  
  Histo2.push_back("Muon1Pt");
  Histo2.push_back("Muon1MetMt");
  Histo2.push_back("Met");
 
  legend.push_back("VV");
  legend.push_back("DY+Jets");
  legend.push_back("t#bar{t}");
  legend.push_back("W+Jets");
  
    
}


void Plotter_1(){
cout << "working" << endl;
fill();
//setTDRStyle();

  TFile *Data = TFile::Open((input_Data[0]+".root").c_str(),"READ");
  TFile *Mc[10];
  for(int i = 0; i < input_MC.size(); i++){
  TFile* f = TFile::Open((input_MC[i]+".root").c_str(),"READ");
  Mc[i] = f;
  }

  int j = 3;  //cut
  int k = 1;  //histo
 
 
  TH1F *h1 = (TH1F*)Data->Get((Cut[j]+"/"+Histo[k]).c_str()); 
  h1->GetXaxis()->SetRangeUser(15., 250.);
  h1->Sumw2();

  TH1F* Mc_histos[100];
  for(int i = 0; i < input_MC.size(); i++){
  TH1F* h;
  if(i!=3) h = (TH1F*)Mc[i]->Get((Cut[j]+"/"+Histo[k]).c_str()); 
  else h = (TH1F*)Mc[i]->Get((Cut[j]+"/"+Histo2[k]).c_str()); 
  h->SetLineColor(i+3);
  h->SetFillColor(i+3);
  h->GetXaxis()->SetRangeUser(15., 250.);
  h->Sumw2();
  Mc_histos[i] = h;
  }
   
  THStack *hs = new THStack("hs","CMS Preliminary 35.9 fb^{-1} (13 TeV)");
  for(int i = 0; i < input_MC.size(); i++){
  hs->Add(Mc_histos[i]);
  }

  TH1F *background  = (TH1F*)Mc_histos[0]->Clone("brackground");
  background->Sumw2();

  for(int i = 1; i < input_MC.size(); i++){
  background->Add(Mc_histos[i]);
  } 
 
  TH1F *Data_1  = (TH1F*)h1->Clone("Data_1");
  Data_1->Divide(background);

//Drawing part


TCanvas* c1 = new TCanvas("c1","c1",200,200,800,700);
gStyle->SetOptStat(0);

TPad *pad1 = new TPad("pad1", "pad1",0.0,0.3,1.0,1.0);

  pad1->Draw();
  pad1->cd();
//  pad1->SetLogy();
  pad1->SetTickx();
  pad1->SetTicky();


hs->Draw("HIST");
hs->GetYaxis()->SetTitle("Events");

 h1->GetXaxis()->SetRangeUser(15., 250.);
 h1->SetLineColor(1);
 h1->SetMarkerStyle(20);
 h1->SetMarkerSize(1.1);

h1->Draw("Same");

TLegend *leg_massZprime = new TLegend(0.57, 0.68, 0.69, 0.88);

  //  leg_massZprime->SetHeader("Samples");
  //  c1->SetLegendFillColor(0);
  leg_massZprime->SetFillColor(0);
  leg_massZprime->SetBorderSize(1);
  leg_massZprime->SetTextSize(0.025);
  leg_massZprime->SetBorderSize(0);
  leg_massZprime->SetTextSize(0.025);
  leg_massZprime->Draw();
   
  leg_massZprime->AddEntry(h1,"Data","L");
  for(int i = 0; i < input_MC.size(); i++){
  leg_massZprime->AddEntry(Mc_histos[i],legend[i].c_str(),"f");
  }

  c1->cd();   
  

 TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.3);
  pad2->Draw();
  pad2->cd();
  pad2->SetGridy();
  pad2->SetTickx();
  pad2->SetTicky();
  pad2->SetTopMargin(0.02077151);
  pad2->SetBottomMargin(0.1829871);

 Data_1->SetTitle("");

 Data_1->GetXaxis()->SetTitleOffset(0.75);
 Data_1->GetXaxis()->SetTitleSize(0.1);  
 Data_1->GetXaxis()->SetLabelSize(0.07);
 Data_1->GetXaxis()->SetTitle("M_{T}[GeV]"); 

 Data_1->GetYaxis()->SetTitleOffset(0.5);
 Data_1->GetYaxis()->SetTitleSize(0.08);
 Data_1->GetYaxis()->SetLabelSize(0.1);  
 Data_1->GetYaxis()->SetTitle("#frac{DATA}{MC}");
 
 Data_1->SetLineColor(1);
 Data_1->SetMarkerStyle(20);
 Data_1->SetMarkerSize(1.1);

 Data_1->SetMaximum(2.);
 Data_1->SetMinimum(0.);

 Data_1->Draw();
 
  TLine *line1 = new TLine(15, 1.0, 250, 1.0);
  line1->SetLineColor(kRed);
  line1->SetLineWidth(1.4);
  line1->SetLineStyle(1);
  line1->Draw();
  c1->cd();

return 0;
}





