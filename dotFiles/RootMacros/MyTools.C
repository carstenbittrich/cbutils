#include <assert.h>
#include "TFile.h"
#include "TString.h"
#include "TH1F.h"

//LUMI in pb-1 !

double GetWeight(TFile& file,      // Referenz zur Root Datei in denen die Histogramme drin stehen, fuer die das Gewicht berechnet werden soll. 
		 double lumi=1.,   // Luminositaet auf die gewichtet werden soll (in pb-1)
		 TString id="",    // Falls Dateiname von "file" die Dataset-ID nicht enthaelt, kann man diese hier angeben
		 bool beQuit=true) // gibt informationen aus, wenn auf "false" gesetzt
{
  assert(file);

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
