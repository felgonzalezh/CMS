void null_vs_alternative_hypo_poisson(){
  gStyle->SetOptStat(0);
  TCanvas * c1 = new TCanvas("","",900,600);
  TH1F * h = new TH1F( "h_work",";Nev.;arbitrary", 60, 0, 30.);

  TF1* fga  = new TF1("fga","TMath::Poisson(x,[0])",0,30);
  TF1* falt = new TF1("falt","TMath::Poisson(x,[0])",0,30);
  fga->SetLineColor(3);
  fga->SetParameter( 0, 4.0);
  falt->SetLineColor(2);
  falt->SetParameter( 0, 15);
  h->SetMaximum(0.218);

  std::cout << "CL_s+b(x=7; lambda) = " << falt->Integral(-50,7) << std::endl;
  std::cout << "CL_b(x=7; lambda) = " << fga->Integral(7,50) << std::endl;
 
  cout<<"alpha:"<<fga->Integral(7, 50) 
      <<" total:"<<fga->Integral(0, 50) 
      <<" "<<fga->Integral(7, 50)/fga->Integral(0, 50)  <<endl; 
  cout<<"beta:"<<falt->Integral(0,7) 
      <<" total:"<<falt->Integral(0, 50) <<endl; 

   TLine line;
   line.SetLineWidth(4);

   TLatex text;
   text.SetTextSize(0.04);
   text.SetTextColor(1);

   TGraph * g = new TGraph(1);
   TGraph * a = new TGraph(1);
   for (int i=0; i<=100; ++i){
     g->SetPoint(i, 7+6.*(double)i/100., fga->Eval(7+6.*(double)i/100.));
     a->SetPoint(i, 7-7.*(double)i/100., falt->Eval(7-7.*(double)i/100.));
   }  
   g->SetPoint(101,11,0);
   g->SetPoint(102,7,0);
   g->SetFillColor(4);
   a->SetPoint(101,3,0);
   a->SetPoint(102,7,0);
   a->SetFillColor(5);

  h->Draw();
  text.SetTextSize(0.04);   
  text.SetTextColor( kGreen - 6);
  text.DrawLatex(5., 0.18, "Null-Hypothesis (background-only):  #lambda_{b} = 4");
  text.SetTextColor(1);
  text.DrawLatex(5.6,0.144, "Observation d = 7");   
  text.SetTextColor(4);
  text.SetTextSize(0.06);   
  text.DrawLatex(7.8,0.048, "#alpha");   
  g->Draw("lf,same");
  a->Draw("lf,same");
  fga->Draw("l,same");
  falt->Draw("l,same");

  text.SetTextColor(kOrange);
  text.DrawLatex(6,0.012, "#beta");
  text.SetTextColor(kRed);
  text.SetTextSize(0.04);   
  text.DrawLatex(10.8, 0.121, "Alternative hypothesis: #lambda_{s+b} = 15");
  text.DrawLatex(12, 0.11, "(signal + background)");
  line.DrawLine(7,0.14,7,0.0);
  gPad->RedrawAxis();
  c1->SaveAs("bgd_plus_s.pdf");

}

