//=================================================================================================================================================
//				Zusaetzliche Funktionen
//=================================================================================================================================================

TLegend* leg =0;

//-------------------------------------------------------------------------------------------------------------------------------------------------

void weight(TH1F*& histnew,		//histogram to fill
	    std::vector<TH1F*> vec,	//histograms to fill histnew with
	    std::vector<double> scale 	//scalefactor
	    )
{
  histnew = (TH1F*) vec[0]->Clone("histnew1"); //new TH1F(*((TH1F*)vec[0]->Clone("histnew2"))); // needs a new name!
  histnew->SetDirectory(0);	
  histnew->Reset(); // delete everything 
   
    // add now the specific histogram from all QCD samples to the new one
      for (unsigned int i = 0; i < vec.size(); ++i)
      {
	histnew->Add(vec[i], scale[i]);
      }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

 void plot1(TH1F* hist,		//Pointer auf Historgramm
	   //double scale,	//Skalierungsfaktor  Histogramm
	   const char* xtitle, 	//Beschriftung X-Achse
	   double x2,		//Endwert X-Achse
	   double y2,		//Endwert Y-Achse
	   double x1,		//Startwert X-Achse
	   double y1		//Startwert Y-Achse
	  )
{
  double scale;
  
  //skale
  scale = 1./hist->Integral();
  hist->Scale(scale);
  if ( y2 == -1.)
  {
  y2 = hist->GetMaximum();
  y2 =  y2 +(0.05*y2);  
  };
  
  //draw
  hist->Draw("hist");
  hist->SetFillColor(kBlack);
  hist->SetFillStyle(3018);
  hist->GetXaxis()->SetRangeUser(x1,x2);
  hist->GetXaxis()->SetTitle(xtitle);
  hist->GetYaxis()->SetRangeUser(y1,y2);
  hist->GetYaxis()->SetTitleOffset(1.5);
  //hist->SetTitle("title");
  hist->SetStats(0);//entfernt Statistikbox (1-> wird gezeichnet)
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void plot2(TH1F* hist1,		//Pointer auf erstes Historgramm
	  TH1F* hist2, 		//Pointer auf zweites Histogramm
	  //double scale1, //=1.,	//Skalierungsfaktor 1. Histogramm
	  //double scale2, //=1.,	//Skalierungsfaktor 2. Histogramm
	  const char* xtitle, 	//Beschriftung X-Achse
	  double x2, //=10.,	//Endwert X-Achse
	  double y2,			//Endwert Y-Achse
	  double x1, //=0.,		//Startwert X-Achse
	  double y1 //=0.		//Startwert Y-Achse
	  )
{
   double scale2;
   double scale1;
   
   //skalieren
   scale1 = 1./hist1->Integral();
   hist1->Scale(scale1);
   scale2 = 1./hist2->Integral();
   hist2->Scale(scale2);
   
  if (y2 == -1. )
  {
  double a = hist1->GetMaximum();
  double b = hist2->GetMaximum();
  if (a < b) {y2 = b + (0.05*b);} else {y2 = a+(0.05*a);};
  };
  
  // 1. Histogramm
  hist1->Draw("hist");
  
  hist1->SetFillColor(kRed);
  hist1->SetFillStyle(3018);
  hist1->GetXaxis()->SetRangeUser(x1,x2);
  hist1->GetXaxis()->SetTitle(xtitle);
  hist1->GetYaxis()->SetRangeUser(y1,y2);
  hist1->GetYaxis()->SetTitleOffset(1.5);
  hist1->SetStats(0);//entfernt Statistikbox (1-> wird gezeichnet)
  
  //2. Histogramm
  hist2->SetLineColor(kBlack);
  hist2->Draw("same");//hist = als linie plotten
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void plot3(TH1F* hist1,		//Pointer auf erstes Historgramm
	  TH1F* hist2, 		//Pointer auf zweites Histogramm
	  TH1F* hist3, 		//Pointer auf drittes Histogramm
	 // double scale1, //=1.,	//Skalierungsfaktor 1. Histogramm
	 // double scale2, //=1.,	//Skalierungsfaktor 2. Histogramm
	 // double scale3, //=1.,	//Skalierungsfaktor 3. Histogramm
	  const char* xtitle, 		//Beschriftung X-Achse
	  double x2, //=10.,		//Endwert X-Achse
	  double y2,			//Endwert Y-Achse
	  double x1, //=0.,		//Startwert X-Achse
	  double y1 //=0.		//Startwert Y-Achse
	  )
{
  double scale1; //=1.,	//Skalierungsfaktor 1. Histogramm
  double scale2; //=1.,	//Skalierungsfaktor 2. Histogramm
  double scale3;
  
  //skalieren
  scale1 = 1./hist1->Integral();
  hist1->Scale(scale1);
  scale2 = 1./hist2->Integral();
  hist2->Scale(scale2);
  scale3 = 1./hist3->Integral();
  hist3->Scale(scale3);
  if (y2 == -1.)
  {
  y2 = TMath::Max(TMath::Max(hist1->GetMaximum(), hist2->GetMaximum()),hist3->GetMaximum());
  y2 = y2 +0.05*y2; 
  };
  
  //1. Histogramm
  hist1->Draw("hist");
  hist1->SetFillColor(kBlack);
  hist1->SetFillStyle(3018);
  hist1->GetXaxis()->SetRangeUser(x1,x2);
  hist1->GetXaxis()->SetTitle(xtitle);
  hist1->GetYaxis()->SetRangeUser(y1,y2);
  hist1->GetYaxis()->SetTitleOffset(1.5);
  hist1->SetStats(0);//entfernt Statistikbox (1-> wird gezeichnet)
  
  //2. Histogramm
  hist2->SetLineColor(kRed);
  hist2->SetFillColor(kRed);
  hist2->SetFillStyle(3019);
  hist2->Draw("hist same");
    
  //3. Histogramm
  hist3->SetLineColor(KBlack);
  hist3->Draw("same");//hist = als linie plotten
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

 // leg->SetMargin(0.5); stellt Abstand der Schrift von Rand ein
void legend1(TH1F* hist, 		//Pointer auf Histogramm
	     const char* label,		//Eintrag  Histogramm
	     double x1,			//Ecke unten links (x)
	     double y1,			//Ecke oben rechts (x)
	     double x2,			//Ecke unten link (y)
	     double y2	     		//Ecke oben rechts (y)
	   )
{
  leg= new TLegend(x1,y1,x2,y2);
  assert(leg !=0);
  leg->SetFillColor(4000);
  leg->SetBorderSize(0);
  leg->AddEntry(hist,label,"l"); // l=line, f=fill, p=point
  leg->SetTextSize(0.04);
  leg->Draw();
  //delete leg;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void legend2(TH1F* hist1, 		//erstes Histogramm
	     TH1F* hist2,		//zweites Histogramm
	     const char* label1,	//Eintrag erstes Histogramm
	     const char* label2,	//Eintrag zweites Histogramm
	     double x1,			//Ecke unten links (x)
	     double y1,			// Ecke oben rechts (x)
	     double x2,			//Ecke unten link (y)
	     double y2	     		//Ecke oben rechts (y)
	   )
{
  leg = new TLegend(x1,y1,x2,y2); //leg global definieren, nach dem anweden von legend1 resetten
  leg->SetFillColor(4000);
  leg->SetBorderSize(0);
  leg->AddEntry(hist1,label1,"f"); // l=line, f=fill, p=point
  leg->AddEntry(hist2,label2,"l");
  leg->SetTextSize(0.04);
  leg->Draw();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

void legend3(TH1F* hist1, 		//erstes Histogramm
	     TH1F* hist2,		//zweites Histogramm
	     TH1F* hist3,		//drittes Histogramm
	     const char* label1,	//Eintrag erstes Histogramm
	     const char* label2,	//Eintrag zweites Histogramm
	     const char* label3,	//Eintrag drittes Histogramm
	     double x1,			//Ecke unten links (x)
	     double y1,			// Ecke oben rechts (x)
	     double x2,			//Ecke unten link (y)
	     double y2	     		//Ecke oben rechts (y)
	   )
{
  leg = new TLegend(x1,y1,x2,y2);
  //leg->SetFillColor(4000); //transparent
  leg->SetFillColor(4000);
  //leg->SetFillStyle(3018);
  leg->SetBorderSize(0);
  leg->AddEntry(hist1,label1,"f"); // l=line, f=fill, p=point
  leg->AddEntry(hist2,label2,"f");
  leg->AddEntry(hist3,label3,"p");
  leg->SetTextSize(0.04);
  leg->Draw();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------

 double GetWeight(TFile& file,      // Referenz zur Root Datei in denen die Histogramme drin stehen, fuer die das Gewicht berechnet werden soll. 
		 double lumi=1.,   // Luminositaet auf die gewichtet werden soll (in pb-1)
		 TString id="",    // Falls Dateiname von "file" die Dataset-ID nicht enthaelt, kann man diese hier angeben
		 bool beQuit=true) // gibt informationen aus, wenn auf "false" gesetzt
{
  //assert(file);

  // if id not given, use filename as id
  if (id=="") id = file.GetName();
    
  // get raw cut flow before any skimming
  TH1F* hCutFlowRaw = (TH1F*) file.Get("SkimSelection/h_cut_flow_raw");
  assert(hCutFlowRaw);

  // original number of events saved it first bin
  double dEntries = hCutFlowRaw->GetBinContent(1);
  
  // get cross-section
  // silly hardcoded id<->xsec assignment
  // xsec given in pb
  double xsec=0.;
  if (id.Contains("106052") || id.Contains("PythiaZtautau")) xsec = 990.; // Pythia Ztautau NNLO 
  if (id.Contains("105009") || id.Contains("J0")) xsec = 1.2032E+10; // J0 dijet Pythia
  if (id.Contains("105010") || id.Contains("J1")) xsec = 8.0714E+08; // J1 dijet Pythia
  if (id.Contains("105011") || id.Contains("J2")) xsec = 4.8027E+07; // J2 dijet Pythia
  if (id.Contains("105012") || id.Contains("J3")) xsec = 2.5364E+06; // J3 dijet Pythia
  if (id.Contains("105013") || id.Contains("J4")) xsec = 9.9605E+04; // J4 dijet Pythia
  if (id.Contains("105014") || id.Contains("J5")) xsec = 2.5947E+03; // J5 dijet Pythia
  if (id.Contains("105015") || id.Contains("J6")) xsec = 3.5457E+01; // J6 dijet Pythia
  if (id.Contains("105016") || id.Contains("J7")) xsec = 1.3391E-01; // J7 dijet Pythia
  if (id.Contains("105017") || id.Contains("J8")) xsec = 5.6799E-06; // J8 dijet Pythia

  // calcuate weigt for given luminosity
  double weight = lumi * xsec / dEntries;
  
  // some print out if requested
  if (!beQuit) {
    cout << "* processing sample with id = "<< id << endl;
    cout << "  #entries = " << dEntries << ", xsec = " << xsec << ", weight (for " << lumi << "pb-1) = " << weight << endl;
  }

  // return the dataset weight
  return weight;
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
const char* doubtostr( double isDouble, 		// double to be converted
			    TString appendString	//final string
			    )
{
  std::ostringstream 	oss;
  std::string isString;
  
  oss << isDouble;
  isString = oss.str();
  
  return appendString.Append(isString);
}
