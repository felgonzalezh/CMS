// example of CrystalBall Function and its distribution (pdf and cdf)

void CrystalBall()  {

   auto c1 = new TCanvas();
   c1->Divide(1,3);

   // crystal ball function
   c1->cd(1);
   
   TH1F *h1 = new TH1F("h1", "h1 title", 10, 0, 1);
      
   TF1 *gauss = new TF1("gauss","ROOT::Math::normal_cdf(x, 1, 0)",-15.0,15.0);
   TRandom3 *random = new TRandom3();
   random->SetSeed(0);
   
   for(double i=-15; i<=15; i=i+0.01){
   double ran_number = random->Uniform(-15.0,15.0);
   double integral=gauss->Eval(ran_number);
   h1->Fill(integral);
   }
   c1->cd(1);
   gauss->SetLineColor(kRed);
   gauss->Draw();
   c1->cd(2);
   h1->Draw();
   
}

 
