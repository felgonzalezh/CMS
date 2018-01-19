#include "TFile.h"
 #include "TH1F.h"
 #include "TTreeReader.h"
 #include "TTreeReaderValue.h"

void treereader(){
	
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
  

auto f = new TFile("BDT_training.root");
auto T = (TTree*)f->Get("demo/tree");

   T->Draw("Muon_pt");
 // T->Draw("dpt_14", "dpt_14 > 0 && dpt_14 < 5"); 
 // T->Draw("dpt_48", "dpt_48 > 0 && dpt_48 < 5");
 // T->Draw("dpt_815", "dpt_815 > 0 && dpt_815 < 5");
 //T->Draw("dpt_1530", "dpt_1530 > 0 && dpt_1530 < 5");

 //Superponer
 //T->Draw("dpt_14", "dpt_14 > 0 && dpt_14 < 5");
 //T->Draw("dpt_48", "dpt_48 > 0 && dpt_48 < 5");  
 //T->Draw( "dpt_48"," ","same");
 //T->Draw( "dpt_815","dpt_48 ","same");

 //T->Print();
// T->Scan();

//Create Histogram
int xmin = -1;
int xmax = 2;
int bins = 40;

int station = 2;
bool digis = true; 

if(digis) {
xmin =  -10;
xmax = 20;
bins = 30;
}

TH1F *h1 = new TH1F("h1","hist from tree",bins, xmin, xmax);
TH1F *h2 = new TH1F("h2","hist from tree",bins, xmin, xmax);
TH1F *h3 = new TH1F("h3","hist from tree",bins, xmin, xmax);
TH1F *h4 = new TH1F("h4","hist from tree",bins, xmin, xmax);

  


if(station == 1){

T->Draw("dpt_14_1 >> h1");
T->Draw("dpt_48_1 >> h2");
T->Draw("dpt_815_1 >> h3");
T->Draw("dpt_1530_1 >> h4");

if(digis){
T->Draw("pt_14_1 >> h1");
T->Draw("pt_48_1 >> h2");
T->Draw("pt_815_1 >> h3");
T->Draw("pt_1530_1 >> h4");
}

}

if(station == 2) {


T->Draw("dpt_14_2 >> h1");
T->Draw("dpt_48_2 >> h2");
T->Draw("dpt_815_2 >> h3");
T->Draw("dpt_1530_2 >> h4");

if(digis){
T->Draw("pt_14_2 >> h1");
T->Draw("pt_48_2 >> h2");
T->Draw("pt_815_2 >> h3");
T->Draw("pt_1530_2 >> h4");
}


}


h1->SetLineColor(6);
h1->SetLineWidth(2);
h2->SetLineColor(2);
h2->SetLineWidth(2);
h3->SetLineColor(TColor::GetColor("#cccc31"));
h3->SetLineWidth(2);
h4->SetLineColor(3);
h4->SetLineWidth(2);

h4->SetTitle("");
h4->SetStats(kFALSE);
h4->GetXaxis()->SetTitle("#Delta #phi");

h4->Draw();
h3->Draw("same");
h2->Draw("same");
h1->Draw("same");

 TLegend *leg = new TLegend(0.5530504,0.7347826,0.9708223,0.9695652,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);

  leg->SetHeader("1.2 < |#eta| < 1.6", "c" );
  leg->AddEntry(h4, "15 < p_{T} < 30");
  leg->AddEntry(h3, "8 < p_{T} < 15"); 
  leg->AddEntry(h2, "4 < p_{T} < 8"); 
  leg->AddEntry(h1, "1 < p_{T} < 4");
  
    
 
   leg->Draw();
}
