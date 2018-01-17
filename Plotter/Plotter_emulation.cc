#include "TFile.h"
#include "TTree.h"

#include "TH1F.h"

#include "THStack.h"
#include "TLegend.h"
#include "TColor.h"
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
using namespace std;

void setTDRStyle();
void Plotter_error_600(){

  TCanvas* c1 = new TCanvas("c1","c1",200,200,800,700);

  gStyle->SetOptStat(0);
  /*
  int nb = 10;
  float BINS[12] = {200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 750.0, 900.0,1200.0, 1500.0, 2000.0};  
  double BINNER[12] = {200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 750.0, 900.0,1200.0, 1500.0, 2000.0};  
  */
    
  int nb = 7;
  float BINS[8] = {200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 900.0};  
  double BINNER[8] = {200.0, 225.0, 250.0, 300.0, 350.0, 450.0, 600.0, 900.0};  
  
  Int_t cVV = 17561; // color index                                                                                                                                   
  TColor *colorVV = new TColor(cVV, 222.0/255.0,  90.0/255.0, 106.0/255.0 );
  Int_t cWJet = 17562; // color index                                                                                                                                   
  TColor *colorWJet = new TColor(cWJet, 100.0/255.0, 182.0/255.0, 232.0/255.0 );
  Int_t cTT = 17563; // color index                                                                                                                                   
  TColor *colorTT = new TColor(cTT, 155.0/255.0, 152.0/255.0, 204.0/255.0 );
  Int_t cQCD = 17564; // color index                                                                                                  
  TColor *colorQCD = new TColor(cQCD, 250.0/255.0, 202.0/255.0, 255.0/255.0);
  Int_t cDY = 17565; // color index                                                                                                                                 
  TColor *colorDY = new TColor(cDY, 248.0/255.0, 206.0/255.0, 104.0/255.0);

  cout << "working" << endl;

  //  setTDRStyle();

  TFile *f1 = TFile::Open("CR_C/QCD.root","READ");
  if (f1 == 0) {
    printf("Error: cannot open QCD \n");
    return;
    }
  TH1D *Mass_QCD = (TH1D*)f1->Get("NDiTauCombinations/DiTauReconstructableMass");
  Mass_QCD->Scale(1.34);
  
  TFile *f3 = TFile::Open("SR/DY+Jets.root","READ");
  if (f3 == 0) {
    printf("Error: cannot open DY \n");
    return;
    }
  TH1D *Mass_DY = (TH1D*)f3->Get("NDiTauCombinations/DiTauReconstructableMass");


  TFile *f4 = TFile::Open("SR/VV.root","READ");
  if (f4 == 0) {
    printf("Error: cannot open DiBoson \n");
    return;
    }
  TH1D *Mass_DiBoson = (TH1D*)f4->Get("NDiTauCombinations/DiTauReconstructableMass");

  TFile *f6 = TFile::Open("SR/W+Jets.root","READ");
  if (f6 == 0) {
    printf("Error: cannot open WJets \n");
    return;
    }
  TH1D *Mass_WJets = (TH1D*)f6->Get("NDiTauCombinations/DiTauReconstructableMass");

  TFile *f5 = TFile::Open("SR/tbar{t}.root","READ");
  if (f5 == 0) {
    printf("Error: cannot open TTbar \n");
    return;
    }
  TH1D *Mass_TTbar = (TH1D*)f5->Get("NDiTauCombinations/DiTauReconstructableMass");

  TFile *f2 = TFile::Open("SR/Zprime3000.root","READ");
  if (f2 == 0) {
    printf("Error: cannot open Zprime3000 \n");
    return;
    }
  TH1D *Mass_3000 = (TH1D*)f2->Get("NDiTauCombinations/DiTauReconstructableMass");


  TH1D *error = new TH1D("error", "error", Mass_3000->GetXaxis()->GetNbins(), Mass_3000->GetXaxis()->GetXmin(), Mass_3000->GetXaxis()->GetXmax() );
  error->Add(Mass_DiBoson);
  error->Add(Mass_TTbar);
  error->Add(Mass_WJets);
  error->Add(Mass_DY);
  error->Add(Mass_QCD);



  TH1D *H_Mass_3000 = new TH1D("h_3000", "h_3000", nb, BINS);

  TH1D *H_Mass_DY = new TH1D("h_DY", "h_DY", nb, BINS);
  TH1D *H_Mass_QCD = new TH1D("h_QCD", "h_QCD", nb, BINS);
  TH1D *H_Mass_DiBoson = new TH1D("h_VV", "h_VV", nb, BINS);
  TH1D *H_Mass_WJets = new TH1D("h_WJets", "h_WJets", nb, BINS);
  TH1D *H_Mass_TTbar = new TH1D("h_TT", "h_TT", nb, BINS);

  TH1D *H_error = new TH1D("h_error", "h_error", nb, BINS);
  TH1D *ERROR = new TH1D("Error", "Error", nb, BINS);

  TH1D *H_Sig = new TH1D("h_Sig", "h_Sig", nb, BINS);

  H_error = (TH1D*)error->Rebin(nb, "error_rebin", BINNER);
  //  error = (TH1D*)error->Rebin(nb, "error_rebin", BINS);

  Int_t nbins   = Mass_3000->GetXaxis()->GetNbins(); 

  for (int b = 1; b <= nbins; b++ ){
    Mass_3000->SetBinError(b,0);
    Mass_QCD->SetBinError(b,0);
    Mass_DY->SetBinError(b,0);
    Mass_WJets->SetBinError(b,0);
    Mass_DiBoson->SetBinError(b,0);
    Mass_TTbar->SetBinError(b,0);
    // cout << " b " << b << "  " << error->GetXaxis()->GetBinLowEdge(b) << "-" << error->GetXaxis()->GetBinLowEdge(b) + error->GetXaxis()->GetBinWidth(b) << " BinContent " << error->GetBinContent(b) << " Error " << error->GetBinError(b) << endl;
    
  }
//  double max3000=0,MAX=0; 

  cout << "i " << Mass_3000->GetXaxis()->GetNbins() << endl; 
  cout << "b " << H_Mass_3000->GetXaxis()->GetNbins() << endl; 

  for (int b = 1; b <= H_Mass_3000->GetXaxis()->GetNbins(); b++ ){
    double num_DY = 0; 
    double num_QCD = 0;
    double num_DiBoson = 0;
    double num_WJets = 0;
    double num_TTbar = 0;
    double num_3000 = 0;

    double num_error = 0;
    double num_error_error = 0;

    double num_DY_width = 0; 
    double num_QCD_width = 0;
    double num_DiBoson_width = 0;
    double num_WJets_width = 0;
    double num_TTbar_width = 0;
    double num_3000_width = 0;

    double num_error_width = 0;
    double num_error_error_width = 0;


    for (int i = 1; i <= nbins; i++ ){
      if(((( Mass_3000->GetXaxis()->GetBinLowEdge(i)) + (Mass_3000->GetXaxis()->GetBinWidth(i))) <= ((H_Mass_3000->GetXaxis()->GetBinLowEdge(b))+ (H_Mass_3000->GetXaxis()->GetBinWidth(b)))) && ((( Mass_3000->GetXaxis()->GetBinLowEdge(i))+ (Mass_3000->GetXaxis()->GetBinWidth(i))) > ((H_Mass_3000->GetXaxis()->GetBinLowEdge(b))))){
	
	num_3000 += Mass_3000->GetBinContent(i);
	num_DY += Mass_DY->GetBinContent(i);
	num_QCD += Mass_QCD->GetBinContent(i);
	num_DiBoson += Mass_DiBoson->GetBinContent(i);
	num_TTbar += Mass_TTbar->GetBinContent(i);
	num_WJets += Mass_WJets->GetBinContent(i);

	num_error += error->GetBinContent(i);
	//	num_error_error += error->GetBinError(i);
	
      }else if( ( Mass_3000->GetXaxis()->GetBinLowEdge(i)) >= (H_Mass_3000->GetXaxis()->GetBinLowEdge(nb)+ (H_Mass_3000->GetXaxis()->GetBinWidth(nb))) && b==nb){//---- ELSE ES SOLO PARA EL OVERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)

	num_3000 += Mass_3000->GetBinContent(i);
	num_DY += Mass_DY->GetBinContent(i);
	num_QCD += Mass_QCD->GetBinContent(i);
	num_DiBoson += Mass_DiBoson->GetBinContent(i);
	num_TTbar += Mass_TTbar->GetBinContent(i);
	num_WJets += Mass_WJets->GetBinContent(i);
	num_error += error->GetBinContent(i);
	//	num_error_error += abs(error->GetBinError(i));

      }else if( ( Mass_3000->GetXaxis()->GetBinLowEdge(i)) < (H_Mass_3000->GetXaxis()->GetBinLowEdge(1)+ (H_Mass_3000->GetXaxis()->GetBinWidth(1))) && b==1){//---- ELSE ES SOLO PARA EL UNDERFLOW... SI SE NO QUIERE OVERFLOW (QUITAR ESTE ELSE)
	num_3000 += Mass_3000->GetBinContent(i);
	num_DY += Mass_DY->GetBinContent(i);
	num_QCD += Mass_QCD->GetBinContent(i);
	num_DiBoson += Mass_DiBoson->GetBinContent(i);
	num_TTbar += Mass_TTbar->GetBinContent(i);
	num_WJets += Mass_WJets->GetBinContent(i);
	num_error += error->GetBinContent(i);
	//	num_error_error += abs(error->GetBinError(i));
		
      }else{
	continue;
      }

      num_3000_width = num_3000 / (H_Mass_3000->GetXaxis()->GetBinWidth(b));
      num_DY_width = num_DY / (H_Mass_DY->GetXaxis()->GetBinWidth(b));
      num_QCD_width = num_QCD / (H_Mass_QCD->GetXaxis()->GetBinWidth(b));
      num_DiBoson_width = num_DiBoson / (H_Mass_DiBoson->GetXaxis()->GetBinWidth(b));
      num_WJets_width = num_WJets / (H_Mass_WJets->GetXaxis()->GetBinWidth(b));
      num_TTbar_width = num_TTbar / (H_Mass_TTbar->GetXaxis()->GetBinWidth(b));
      
      num_error_width = num_error / H_error->GetXaxis()->GetBinWidth(b);
      num_error_error_width =  H_error->GetBinError(b) / H_error->GetXaxis()->GetBinWidth(b);
      
      H_Mass_3000->SetBinContent(b, num_3000);
      H_Mass_DY->SetBinContent(b, num_DY);
      H_Mass_QCD->SetBinContent(b, num_QCD);
      H_Mass_DiBoson->SetBinContent(b, num_DiBoson);
      H_Mass_WJets->SetBinContent(b, num_WJets);
      H_Mass_TTbar->SetBinContent(b, num_TTbar);

      H_Mass_3000->SetBinError(b,0);
      H_Mass_QCD->SetBinError(b,0);
      H_Mass_DY->SetBinError(b,0);
      H_Mass_WJets->SetBinError(b,0);
      H_Mass_DiBoson->SetBinError(b,0);
      H_Mass_TTbar->SetBinError(b,0);
      /*
      H_error->SetBinContent(b, num_error );
      H_error->GetBinError(b);
      */

      //      ERROR->SetBinContent(b, num_error_width);
      //      ERROR->SetBinError(b, H_error->GetBinError(b) / H_error->GetXaxis()->GetBinWidth(b));


      ERROR->SetBinContent(b, num_error);
      ERROR->SetBinError(b, H_error->GetBinError(b));

    }
  }
  /*
  for (int b = 1; b <= H_error->GetXaxis()->GetNbins(); b++ ){
    cout << " b " << b << "  " << H_error->GetXaxis()->GetBinLowEdge(b) << "-" << H_error->GetXaxis()->GetBinLowEdge(b) + H_error->GetXaxis()->GetBinWidth(b) << " BinContent " << H_error->GetBinContent(b) << " Error " << H_error->GetBinError(b) << endl;
  }

  cout << " ============== " << endl;
  cout << "  BINNED ERROR " << endl;
  cout << " ============== " << endl;

  for (int b = 1; b <= ERROR->GetXaxis()->GetNbins(); b++ ){
    cout << " b " << b << "  " << ERROR->GetXaxis()->GetBinLowEdge(b) << "-" << ERROR->GetXaxis()->GetBinLowEdge(b) + ERROR->GetXaxis()->GetBinWidth(b) << " BinContent " << ERROR->GetBinContent(b) << " Error " << ERROR->GetBinError(b) << endl;
  }
  */
  int errorbins =  ERROR->GetXaxis()->GetNbins();
  Double_t* mcX = new Double_t[errorbins];
  Double_t* mcY = new Double_t[errorbins];
  Double_t* mcErrorX = new Double_t[errorbins];
  Double_t* mcErrorY = new Double_t[errorbins];

  for(int bin=0; bin < ERROR->GetXaxis()->GetNbins(); bin++) {
    mcY[bin] = ERROR->GetBinContent(bin+1);
    mcErrorY[bin] = ERROR->GetBinError(bin+1);
    mcX[bin] = ERROR->GetBinCenter(bin+1);
    mcErrorX[bin] = ERROR->GetBinWidth(bin+1) * 0.5;
  }

  TGraphErrors *mcError = new TGraphErrors(ERROR->GetXaxis()->GetNbins(),mcX,mcY,mcErrorX,mcErrorY);
  mcError->SetLineWidth(1);
  mcError->SetFillColor(1);
  mcError->SetFillStyle(3002);
  
  delete[] mcX;
  delete[] mcY;
  delete[] mcErrorX;
  delete[] mcErrorY;

  double maxQCD=0,max3000=0,maxDY=0,maxDiBoson=0,maxTTbar=0,MAX=0; 
  maxQCD = H_Mass_QCD->GetMaximum();
  max3000 = H_Mass_3000->GetMaximum();
  maxDY = H_Mass_DY->GetMaximum();
  maxTTbar = H_Mass_TTbar->GetMaximum();
  maxDiBoson = H_Mass_DiBoson->GetMaximum();
  
  cout << "max      QCD " << maxQCD << endl;
  cout << "max     3000 " << max3000 << endl;
  cout << "max       DY " << maxDY << endl;
  cout << "max    TTbar " << maxTTbar << endl;
  cout << "max  DiBoson " << maxDiBoson << endl;


  if(maxQCD > max3000 && maxQCD > maxDY && maxQCD > maxTTbar && maxQCD > maxDiBoson){MAX = maxQCD*1.05;}
  if(max3000 > maxQCD && max3000 > maxDY && max3000 > maxTTbar && max3000 > maxDiBoson){MAX = max3000*1.05;}
  if(maxDY > maxQCD && maxDY > max3000 && maxDY > maxTTbar && maxDY > maxDiBoson){MAX = maxDY*1.05;}
  if(maxTTbar > maxQCD && maxTTbar > max3000 && maxTTbar > maxDY && maxTTbar > maxDiBoson){MAX = maxTTbar*1.05;}
  if(maxDiBoson > maxQCD && maxDiBoson > max3000 && maxDiBoson > maxTTbar && maxDiBoson > maxDY){MAX = maxDiBoson*1.05;}
  

  H_Mass_DY->SetLineColor(1);
  H_Mass_DY->SetFillColor(cDY);

  H_Mass_QCD->SetLineColor(1);
  H_Mass_QCD->SetFillColor(cQCD);

  H_Mass_DiBoson->SetLineColor(1);
  H_Mass_DiBoson->SetFillColor(cVV);

  H_Mass_WJets->SetLineColor(1);
  H_Mass_WJets->SetFillColor(cWJet);

  H_Mass_TTbar->SetLineColor(1);
  H_Mass_TTbar->SetFillColor(cTT);

  H_Mass_3000->SetLineColor(4);
  H_Mass_3000->SetLineWidth(3);
  H_Mass_3000->SetLineStyle(2);

  cout << "3000 normal (Events) " << Mass_3000->Integral() << endl;
  cout << "3000 binned (Events/GeV) " << H_Mass_3000->Integral() << endl;


  //  setTDRStyle();

  TPad *pad1 = new TPad("pad1", "pad1",0.0,0.3,1.0,1.0);

  pad1->Draw();
  pad1->cd();
  pad1->SetLogy();
  pad1->SetTickx();
  pad1->SetTicky();

  //--------------FIRSTPAD
  THStack *hs = new THStack("hs","CMS Preliminary 35.9 fb^{-1} (13 TeV)");
  hs->Add(H_Mass_DiBoson);
  hs->Add(H_Mass_TTbar);
  hs->Add(H_Mass_WJets);
  hs->Add(H_Mass_DY);
  hs->Add(H_Mass_QCD);

  THStack* hsdraw = hs;
  hsdraw->Draw("");

  hsdraw->GetYaxis()->SetTitle("Events");
  //  hsdraw->GetXaxis()->SetTitle("m(#tau, #tau, #slash{E}_{T})");
  //  hsdraw->SetMaximum(1.07*hs->GetMaximum());
  hsdraw->SetMaximum(500);
  hsdraw->SetMinimum(0.004);
  //  hsdraw->GetBinError(3);



  TH1D *background = (TH1D*)hs->Clone("background");
  TH1D *signal = (TH1D*)H_Mass_3000->Clone("sig");

  H_Mass_3000->Scale(100);
  H_Mass_3000->Draw("same");
  mcError->Draw("2");

  //  TLegend *leg_massZprime = new TLegend(0.12, 0.68, 0.24, 0.88);
  TLegend *leg_massZprime = new TLegend(0.57, 0.68, 0.69, 0.88);

  //  leg_massZprime->SetHeader("Samples");
  //  c1->SetLegendFillColor(0);
  leg_massZprime->SetFillColor(0);
  leg_massZprime->SetBorderSize(1);
  leg_massZprime->SetTextSize(0.025);
  leg_massZprime->SetBorderSize(0);
  leg_massZprime->SetTextSize(0.025);
  leg_massZprime->AddEntry(H_Mass_TTbar,"t#bar{t}","f");
  leg_massZprime->AddEntry(H_Mass_DiBoson,"VV, H","f");
  leg_massZprime->AddEntry(H_Mass_QCD,"QCD","f");
  leg_massZprime->AddEntry(H_Mass_WJets,"W+Jets","f");
  leg_massZprime->AddEntry(H_Mass_DY,"DY+Jets","f");
  leg_massZprime->AddEntry(H_Mass_3000,"Z' (3000 GeV) x 100","L");

  leg_massZprime->Draw();

  c1->cd();   
  
   
  TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.3);
  pad2->Draw();
  pad2->cd();
  pad2->SetGridy();
  pad2->SetTickx();
  pad2->SetTicky();
  pad2->SetTopMargin(0.02077151);
  pad2->SetBottomMargin(0.1829871);

  double sig=0;
  double significance=0;
  for (int b = 1; b <= H_Mass_3000->GetXaxis()->GetNbins(); b++ ){
    double s =0;
    double bkg =0;
    s=signal->GetBinContent(b);
    bkg=H_Mass_DY->GetBinContent(b)+H_Mass_QCD->GetBinContent(b)+H_Mass_DiBoson->GetBinContent(b)+H_Mass_WJets->GetBinContent(b)+H_Mass_TTbar->GetBinContent(b);
    
    sig=s/sqrt(s+bkg);
    H_Sig->SetBinContent(b,sig);
    cout << "Significance " << BINS[b-1] << "-" << BINS[b] << " = " << sig << endl;
  }


  H_Sig->SetStats(0);      // No statistics on lower plot
  H_Sig->Sumw2();

  double ratiomax =0, ratiomin=0;
  ratiomax = H_Sig->GetMaximum();
  ratiomin = H_Sig->GetMinimum();
  H_Sig->SetMinimum(-0.005);  // Define Y ..
  H_Sig->SetMaximum(1.05*ratiomax); // .. range

  H_Sig->GetYaxis()->SetTitleSize(0.09) ;
  H_Sig->GetYaxis()->SetLabelSize(0.08) ;
  H_Sig->GetYaxis()->SetTitleOffset(0.4);

  H_Sig->GetXaxis()->SetTitleSize(0.1) ;
  H_Sig->GetXaxis()->SetLabelSize(0.09) ;
  H_Sig->GetXaxis()->SetTitleOffset(0.7);

  //  H_Sig->SetTitleXFont(32,"t");
  H_Sig->SetTitle("");
  H_Sig->GetYaxis()->SetTitle("#frac{s}{#sqrt{s+b}}");
  H_Sig->GetXaxis()->SetTitle("m(#tau, #tau, #slash{E}_{T})");

  H_Sig->SetLineColor(4);
  H_Sig->SetLineWidth(3);
  H_Sig->SetLineStyle(2);
  //  H_Sig->SetMarkerStyle(21);
  H_Sig->Draw("HIST");    



  return;
}  

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
