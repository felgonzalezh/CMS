
//To run this code:
// root [0] .L graph-separate-data-v2.C
// root [1] makePlots()

// .q (quit)



TGraph * readTypeFour( const char * fname) 
{

ifstream in;
in.open(fname); //
  
double en, flux;
  
TGraph * graphT4 = new TGraph(); 

int i = 0;
  
while ( in.good() ) 
{
    
 in >> en >> flux; //we read 2 columns of data
    
 graphT4->SetPoint( i , en, flux);
    
 ++i;
    
 }

std::cout << "Total points read: " << i << std::endl; 
    
in.close();
  
return graphT4;
  
}


void makePlots() {

  //. Plots of separate data and different data formats
  //.
  //. The available data formats and their matching Graph objects are:
  //. 6 columns data (x,y, x1, x2, y1, y2) == TGraphAsymmErrors
  //. 4 columns data (x,y, xerr, yerr) == TGraphErrors
  //. 3 columns data (x,y, yerr) == TGraphErros ( xerr = 0.0)
  //. 2 columns data (x,y) == TGraph
  //.
  //.... 
    

  int ndataset = 0;
  TList * allgraphs = new TList(); //this is a ROOT container. It will store all of your Graphs
  



  
  
  
  // 1. 2 columns data
  
  TGraph * graphT4 = readTypeFour("grafico-root-prueba.txt");
  // allgraphs->Add( graphT4 ); //Append to your List this Graph
  // ndataset++;

  TF1 *myfit = new TF1("myfit","[1]*x + [0]", 0., 2500.);//para hacer el ajuste
  
  graphT4 = readTypeFour("grafico-root-prueba.txt");
   allgraphs->Add( graphT4 ); //Append to your List this Graph
  ndataset++;

  graphT4 = readTypeFour("grafico-root-prueba.txt");
  //allgraphs->Add( graphT4 ); //Append to your List this Graph
  //ndataset++;
  
  std::cout << "Total dataset read " << ndataset << " " << std::endl;

  //. End of reading and creating Graphs from data files
  //.
  ////////////////////////////////////////////////////////////////////////////////////
  //. 
  //. Plot each Dataset on a sigle Canvas (all combined)
  
  TCanvas * canvas = new TCanvas("Plot1", "Canvas for plot 1", 94, 262,700, 502 );
  canvas->SetFillColor(10);
   TCanvas * canvas1 = new TCanvas("Plot2", "Canvas for plot 1", 94, 262,700, 502 );
 
  
  //If you need log scale on both axis - uncomment the following lines
  //canvas->SetLogx();
  //canvas->SetLogy();
  
  //Set the minimum and maximum for the whole graph
  //Min a max for Axis
  float xmin =  0.0;
  float xmax =  2500.0;
  float ymin = 0.0;
  float ymax =  1000.0;
  
  //Datasets options (Markers: style, color, size) : You can also do it by hand using the interactive Editor
  int style[15];
  int color[15];
  float size[15];
  
  //For dataset No1
  style[0] = 25;
  color[0] = 2;
  size[0]  = 1.0;
  
  //For dataset No2
  style[1] = 26;
  color[1] = 4;
  size[1]  = 1.0;
  
  //For dataset No3
  style[2] = 24;
  color[2] = 38;
  size[2]  = 1.0;
  
  //For dataset No4
  style[3] = 20;
  color[3] = 4;
  size[3]  = 0.5;

  //For dataset No5
  style[4] = 24;
  color[4] = 6;
  size[4]  = 0.8;

  //For dataset No6
  style[5] = 26;
  color[5] = 2;
  size[5]  = 0.8;

  //For dataset No7
  style[6] = 7;
  color[6] = 2;
  size[6]  = 1.0;
  
  //For dataset No8
  style[7] = 25;
  color[7] = 38;
  size[7]  = 1.0;

  //For dataset No9
  style[8] = 26;
  color[8] = 7;
  size[8]  = 1.0;

  //For dataset No10
  style[9] = 1;
  color[9] = 1;
  size[9]  = 1.0;

  // Loop over all Graphs and draw them in the Canvas
  // Min,Max for X and Y axis are set on the first Graph that is plotted

  ndataset = allgraphs->GetSize(); //Get the ndatasets from the size of the List
    
  // Loop now over the List using the index k
  canvas->cd();
  
  for(int k=0; k < ndataset-1; ++k) {
    
    if( k == 0 ) {
      //this is our first graph and it is special (to define axis min,max)
      ((TGraph*)allgraphs->At(k))->SetMinimum(ymin);
      ((TGraph*)allgraphs->At(k))->SetMaximum(ymax);
      ((TGraph*)allgraphs->At(k))->Draw("AP");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLimits(xmin, xmax);
      //set the color options
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      ((TGraph*)allgraphs->At(k))->Draw("AP"); // Draw option AP A=draw axis P=draw a marker for the data
       myfit->SetParameter(0, 8.0);
       myfit->SetParameter(1, 0.5);
      ((TGraph*)allgraphs->At(k))->Fit("myfit");
    }
    else {
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
       myfit->SetParameter(0, 8.0);
       myfit->SetParameter(1, 0.5);
      ((TGraph*)allgraphs->At(k))->Fit("myfit");
      
      ((TGraph*)allgraphs->At(k))->Draw("P"); // since we have already plotted the axis on the first graph we only need option P
      if( k == 9 ){
        ((TGraph*)allgraphs->At(k))->SetLineWidth(2);
        ((TGraph*)allgraphs->At(k))->Draw("C");
      }
      
    }
    
  }

   canvas1->cd();

   for(int k=0; k < ndataset; ++k) {
     if(k==1)
       {
        ((TGraph*)allgraphs->At(k))->Draw("P");
	((TGraph*)allgraphs->At(k))->SetMarkerSize();
       }
    if( k == 0 || k==1) {
      //this is our first graph and it is special (to define axis min,max)
      ((TGraph*)allgraphs->At(k))->SetMinimum(ymin);
      ((TGraph*)allgraphs->At(k))->SetMaximum(ymax);
      ((TGraph*)allgraphs->At(k))->Draw("AP");
      ((TGraph*)allgraphs->At(k))->GetXaxis()->SetLimits(xmin, xmax);
      //set the color options
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
      ((TGraph*)allgraphs->At(k))->Draw("AP"); // Draw option AP A=draw axis P=draw a marker for the data
        myfit->SetParameter(0, 8.0);
       myfit->SetParameter(1, 0.5);
       ((TGraph*)allgraphs->At(1))->Fit("myfit");
    }
    else {
      ((TGraph*)allgraphs->At(k))->SetMarkerStyle( style[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerSize( size[k] );
      ((TGraph*)allgraphs->At(k))->SetMarkerColor( color[k] );
      ((TGraph*)allgraphs->At(k))->SetLineColor( color[k] );
       myfit->SetParameter(0, 8.0);
       myfit->SetParameter(1, 0.5);
       ((TGraph*)allgraphs->At(2))->Fit("myfit");
      
      ((TGraph*)allgraphs->At(k))->Draw("P"); // since we have already plotted the axis on the first graph we only need option P
      if( k == 9 ){
        ((TGraph*)allgraphs->At(k))->SetLineWidth(2);
        ((TGraph*)allgraphs->At(k))->Draw("C");
      }
      
    }
    
  }
  
  /// All done!
  
}
