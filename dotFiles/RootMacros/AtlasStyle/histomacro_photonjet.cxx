//C++ Standardbibliotheken
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "assert.h"
#include "TMath.h"
#include "TPaveText.h"

//using namespace std;
/*
 void plot1(TH1F*,  const char*, double, double,double, double);
 void plot3(TH1F*, TH1F*,const char*, double, double,double, double);
 void plot3(TH1F*, TH1F*, TH1F*, const char*, double, double,double, double);
 void legende1(TH1F*, const char*, double, double, double, double);
 void legende2(TH1F*, TH1F*, const char*, const char*, double, double, double, double);
 void legende3(TH1F*, TH1F*, TH1F*, const char*, const char*, const char*, double, double, double, double);
 */

#include "histomacro_photonjet.h"

//==============================================================================================================================
//                                   	 Macro
//==============================================================================================================================

void histomacro_photonjet(std::string prong = "3P", TString dirname="../out")
{
  //gROOT->LoadMacro("../MyTools.C");
  
   // --- open file ---
    TFile fileZtautau(dirname+"/AnalyseCycle.mc.PythiaZtautau.root"); 
    // fileZtautau ist Variable fuer AnalyseCycle...root. Es wird nur mit Leserechten geoeffnet
    TFile fileData(dirname+"/AnalyseCycle.data.DataEgamma.root"); 
    TFile fileQCDJ1(dirname+"/AnalyseCycle.mc.QCDJ1.root");
    TFile fileQCDJ2(dirname+"/AnalyseCycle.mc.QCDJ2.root");
    TFile fileQCDJ3(dirname+"/AnalyseCycle.mc.QCDJ3.root");
    TFile fileQCDJ4(dirname+"/AnalyseCycle.mc.QCDJ4.root");
    TFile fileQCDJ5(dirname+"/AnalyseCycle.mc.QCDJ5.root");
    TFile fileQCDJ6(dirname+"/AnalyseCycle.mc.QCDJ6.root");
    TFile fileQCDJ7(dirname+"/AnalyseCycle.mc.QCDJ7.root");
  
  // --- declare pointers ---
    //pt
    TH1F* taupt = (TH1F*) fileZtautau.Get(Form("h_myTauPt_%s", prong.c_str()));
    TH1F* taupt_data = (TH1F*) fileData.Get(Form("h_all_%s_Pt", prong.c_str()));
    //TH1F* jetpt =  (TH1F*) fileZtautau.Get(Form("h_all_%s_Pt", prong.c_str()));
    //file.Get liefert TObject, durch (TH1F) wird es in ein Histogramm konvertiert
    TH1F* tauptJ1 = (TH1F*) fileQCDJ1.Get(Form("h_all_%s_Pt", prong.c_str()));
    TH1F* tauptJ2 = (TH1F*) fileQCDJ2.Get(Form("h_all_%s_Pt", prong.c_str()));
    TH1F* tauptJ3 = (TH1F*) fileQCDJ3.Get(Form("h_all_%s_Pt", prong.c_str()));
    TH1F* tauptJ4 = (TH1F*) fileQCDJ4.Get(Form("h_all_%s_Pt", prong.c_str()));
    TH1F* tauptJ5 = (TH1F*) fileQCDJ5.Get(Form("h_all_%s_Pt", prong.c_str()));
    TH1F* tauptJ6 = (TH1F*) fileQCDJ6.Get(Form("h_all_%s_Pt", prong.c_str()));
    TH1F* tauptJ7 = (TH1F*) fileQCDJ7.Get(Form("h_all_%s_Pt", prong.c_str()));
      std::vector<TH1F*> tauptvec; //Vector der die pt-Histogramme der QCDsamples enthaelt
      tauptvec.push_back(tauptJ1);
      tauptvec.push_back(tauptJ2);
      tauptvec.push_back(tauptJ3);
      tauptvec.push_back(tauptJ4);
      tauptvec.push_back(tauptJ5);
      tauptvec.push_back(tauptJ6);
      tauptvec.push_back(tauptJ7);
    
    //mit h_tau_pt_pre kann man sich pt vor dem cut angucken
    //im preselector def groessen: pt, eta, phi, anzahl tau pro event
    
    //eta
    TH1F* taueta = (TH1F*) fileZtautau.Get(Form("h_myTauEta_%s", prong.c_str()));
    TH1F* taueta_data = (TH1F*) fileData.Get(Form("h_all_%s_Eta", prong.c_str()));
    //TH1F* jeteta = (TH1F*) fileZtautau.Get(Form("h_all_%s_Eta", prong.c_str()));
    TH1F* tauetaJ1 = (TH1F*) fileQCDJ1.Get(Form("h_all_%s_Eta", prong.c_str()));
    TH1F* tauetaJ2 = (TH1F*) fileQCDJ2.Get(Form("h_all_%s_Eta", prong.c_str()));
    TH1F* tauetaJ3 = (TH1F*) fileQCDJ3.Get(Form("h_all_%s_Eta", prong.c_str()));
    TH1F* tauetaJ4 = (TH1F*) fileQCDJ4.Get(Form("h_all_%s_Eta", prong.c_str())); 
    TH1F* tauetaJ5 = (TH1F*) fileQCDJ5.Get(Form("h_all_%s_Eta", prong.c_str()));
    TH1F* tauetaJ6 = (TH1F*) fileQCDJ6.Get(Form("h_all_%s_Eta", prong.c_str()));
    TH1F* tauetaJ7 = (TH1F*) fileQCDJ7.Get(Form("h_all_%s_Eta", prong.c_str()));
      std::vector<TH1F*> tauetavec;
      tauetavec.push_back(tauetaJ1);
      tauetavec.push_back(tauetaJ2);
      tauetavec.push_back(tauetaJ3);
      tauetavec.push_back(tauetaJ4);
      tauetavec.push_back(tauetaJ5);
      tauetavec.push_back(tauetaJ6);
      tauetavec.push_back(tauetaJ7);

    //phi
    TH1F* tauphi = (TH1F*) fileZtautau.Get(Form("h_myTauPhi_%s", prong.c_str()));
    TH1F* tauphi_data = (TH1F*) fileData.Get(Form("h_myTauPhi_%s", prong.c_str()));
      //TH1F* jetphi = (TH1F*) fileZtautau.Get(Form("h_myJetPhi_%s", prong.c_str()));
    TH1F* tauphiJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauPhi_%s", prong.c_str()));
    TH1F* tauphiJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauPhi_%s", prong.c_str()));
    TH1F* tauphiJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauPhi_%s", prong.c_str()));
    TH1F* tauphiJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauPhi_%s", prong.c_str()));
    TH1F* tauphiJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauPhi_%s", prong.c_str()));
    TH1F* tauphiJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauPhi_%s", prong.c_str()));
    TH1F* tauphiJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauPhi_%s", prong.c_str()));
      std::vector<TH1F*> tauphivec;
      tauphivec.push_back(tauphiJ1);
      tauphivec.push_back(tauphiJ2);
      tauphivec.push_back(tauphiJ3);
      tauphivec.push_back(tauphiJ4);
      tauphivec.push_back(tauphiJ5);
      tauphivec.push_back(tauphiJ6);
      tauphivec.push_back(tauphiJ7);
    
    //Number of tau per event
//     TH1F* taunJ1 = (TH1F*) fileQCDJ1.Get("TauPreSelector/h_n");
//     TH1F* taunJ2 = (TH1F*) fileQCDJ2.Get("TauPreSelector/h_n");
//     TH1F* taunJ3 = (TH1F*) fileQCDJ3.Get("TauPreSelector/h_n");
//     TH1F* taunJ4 = (TH1F*) fileQCDJ4.Get("TauPreSelector/h_n");
//     TH1F* taunJ5 = (TH1F*) fileQCDJ5.Get("TauPreSelector/h_n");
//     TH1F* taunJ6 = (TH1F*) fileQCDJ6.Get("TauPreSelector/h_n");
//     TH1F* taunJ7 = (TH1F*) fileQCDJ7.Get("TauPreSelector/h_n");

    //seedCalo_centFrac
    TH1F* tauseedCalo_centFrac = (TH1F*) fileZtautau.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFrac_data = (TH1F*) fileData.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFracJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFracJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFracJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFracJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFracJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFracJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
    TH1F* tauseedCalo_centFracJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauSeedCalo_centFrac_%s",prong.c_str()));
      //Vector for QCD-samples
      std::vector<TH1F*> tauseedCalo_centFracvec;
      tauseedCalo_centFracvec.push_back(tauseedCalo_centFracJ1);
      tauseedCalo_centFracvec.push_back(tauseedCalo_centFracJ2);
      tauseedCalo_centFracvec.push_back(tauseedCalo_centFracJ3);
      tauseedCalo_centFracvec.push_back(tauseedCalo_centFracJ4);
      tauseedCalo_centFracvec.push_back(tauseedCalo_centFracJ5);
      tauseedCalo_centFracvec.push_back(tauseedCalo_centFracJ6);
      tauseedCalo_centFracvec.push_back(tauseedCalo_centFracJ7);

    //seedCalo_trkAvgDist
    TH1F* tauseedCalo_trkAvgDist = (TH1F*) fileZtautau.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDist_data = (TH1F*) fileData.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDistJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDistJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDistJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDistJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDistJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDistJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
    TH1F* tauseedCalo_trkAvgDistJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauSeedCalo_trkAvgDist_%s",prong.c_str())); 
      std::vector<TH1F*> tauseedCalo_trkAvgDistvec;
      tauseedCalo_trkAvgDistvec.push_back(tauseedCalo_trkAvgDistJ1);
      tauseedCalo_trkAvgDistvec.push_back(tauseedCalo_trkAvgDistJ2);
      tauseedCalo_trkAvgDistvec.push_back(tauseedCalo_trkAvgDistJ3);
      tauseedCalo_trkAvgDistvec.push_back(tauseedCalo_trkAvgDistJ4);
      tauseedCalo_trkAvgDistvec.push_back(tauseedCalo_trkAvgDistJ5);
      tauseedCalo_trkAvgDistvec.push_back(tauseedCalo_trkAvgDistJ6);
      tauseedCalo_trkAvgDistvec.push_back(tauseedCalo_trkAvgDistJ7);
    
      //calcVars_calRadius
      TH1F* taucalcVars_calRadius = (TH1F*) fileZtautau.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadius_data = (TH1F*) fileData.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadiusJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadiusJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadiusJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadiusJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadiusJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadiusJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));
      TH1F* taucalcVars_calRadiusJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauCalcVars_calRadius_%s",prong.c_str()));	
	std::vector<TH1F*> taucalcVars_calRadiusvec;
	taucalcVars_calRadiusvec.push_back(taucalcVars_calRadiusJ1);
	taucalcVars_calRadiusvec.push_back(taucalcVars_calRadiusJ2);
	taucalcVars_calRadiusvec.push_back(taucalcVars_calRadiusJ3);
	taucalcVars_calRadiusvec.push_back(taucalcVars_calRadiusJ4);
	taucalcVars_calRadiusvec.push_back(taucalcVars_calRadiusJ5);
	taucalcVars_calRadiusvec.push_back(taucalcVars_calRadiusJ6);
	taucalcVars_calRadiusvec.push_back(taucalcVars_calRadiusJ7);
       
      //seedCalo_nWideTrk
      TH1F* tauseedCalo_nWideTrk = (TH1F*) fileZtautau.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      assert(tauseedCalo_nWideTrk!=0);
      TH1F* tauseedCalo_nWideTrk_data = (TH1F*) fileData.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      TH1F* tauseedCalo_nWideTrkJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      assert(tauseedCalo_nWideTrkJ1 != 0);
      TH1F* tauseedCalo_nWideTrkJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      TH1F* tauseedCalo_nWideTrkJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      TH1F* tauseedCalo_nWideTrkJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      TH1F* tauseedCalo_nWideTrkJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      TH1F* tauseedCalo_nWideTrkJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
      TH1F* tauseedCalo_nWideTrkJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauSeedCalo_nWideTrk_%s",prong.c_str()));
	std::vector<TH1F*> tauseedCalo_nWideTrkvec;
	tauseedCalo_nWideTrkvec.push_back(tauseedCalo_nWideTrkJ1);
	tauseedCalo_nWideTrkvec.push_back(tauseedCalo_nWideTrkJ2);
	tauseedCalo_nWideTrkvec.push_back(tauseedCalo_nWideTrkJ3);
	tauseedCalo_nWideTrkvec.push_back(tauseedCalo_nWideTrkJ4);
	tauseedCalo_nWideTrkvec.push_back(tauseedCalo_nWideTrkJ5);
	tauseedCalo_nWideTrkvec.push_back(tauseedCalo_nWideTrkJ6);
	tauseedCalo_nWideTrkvec.push_back(tauseedCalo_nWideTrkJ7);
	
      //seedCalo_lead2ClusterEOverAllClusterE
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterE = (TH1F*) fileZtautau.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterE_data = (TH1F*) fileData.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));	
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
      assert(tauseedCalo_lead2ClusterEOverAllClusterEJ1 != 0);
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauSeedCalo_lead2ClusterEOverAllClusterE_%s",prong.c_str()));
	std::vector<TH1F*> tauseedCalo_lead2ClusterEOverAllClusterEvec;
	tauseedCalo_lead2ClusterEOverAllClusterEvec.push_back(tauseedCalo_lead2ClusterEOverAllClusterEJ1);
	tauseedCalo_lead2ClusterEOverAllClusterEvec.push_back(tauseedCalo_lead2ClusterEOverAllClusterEJ2);
	tauseedCalo_lead2ClusterEOverAllClusterEvec.push_back(tauseedCalo_lead2ClusterEOverAllClusterEJ3);
	tauseedCalo_lead2ClusterEOverAllClusterEvec.push_back(tauseedCalo_lead2ClusterEOverAllClusterEJ4);
	tauseedCalo_lead2ClusterEOverAllClusterEvec.push_back(tauseedCalo_lead2ClusterEOverAllClusterEJ5);
	tauseedCalo_lead2ClusterEOverAllClusterEvec.push_back(tauseedCalo_lead2ClusterEOverAllClusterEJ6);
	tauseedCalo_lead2ClusterEOverAllClusterEvec.push_back(tauseedCalo_lead2ClusterEOverAllClusterEJ7);

      //trFlightPathSig
      TH1F* tautrFlightPathSig = (TH1F*) fileZtautau.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSig_data = (TH1F*) fileData.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSigJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSigJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSigJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSigJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSigJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSigJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
      TH1F* tautrFlightPathSigJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauTrFlightPathSig_%s",prong.c_str()));
	std::vector<TH1F*> tautrFlightPathSigvec;
	tautrFlightPathSigvec.push_back(tautrFlightPathSigJ1);
	tautrFlightPathSigvec.push_back(tautrFlightPathSigJ2);
	tautrFlightPathSigvec.push_back(tautrFlightPathSigJ3);
	tautrFlightPathSigvec.push_back(tautrFlightPathSigJ4);
	tautrFlightPathSigvec.push_back(tautrFlightPathSigJ5);
	tautrFlightPathSigvec.push_back(tautrFlightPathSigJ6);
	tautrFlightPathSigvec.push_back(tautrFlightPathSigJ7);
    
      //massTrkSys
      TH1F* taumassTrkSys = (TH1F*) fileZtautau.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSys_data = (TH1F*) fileData.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSysJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSysJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSysJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSysJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSysJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSysJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
      TH1F* taumassTrkSysJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauMassTrkSys_%s",prong.c_str()));
	std::vector<TH1F*> taumassTrkSysvec;
	taumassTrkSysvec.push_back(taumassTrkSysJ1);
	taumassTrkSysvec.push_back(taumassTrkSysJ2);
	taumassTrkSysvec.push_back(taumassTrkSysJ3);
	taumassTrkSysvec.push_back(taumassTrkSysJ4);
	taumassTrkSysvec.push_back(taumassTrkSysJ5);
	taumassTrkSysvec.push_back(taumassTrkSysJ6);
	taumassTrkSysvec.push_back(taumassTrkSysJ7);

      
      //SeedCalo_dRmax
      TH1F* tauseedCalo_dRmax = (TH1F*) fileZtautau.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmax_data = (TH1F*) fileData.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmaxJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmaxJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmaxJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmaxJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmaxJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmaxJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
      TH1F* tauseedCalo_dRmaxJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauSeedCalo_dRmax_%s",prong.c_str()));
	std::vector<TH1F*> tauseedCalo_dRmaxvec;
	tauseedCalo_dRmaxvec.push_back(tauseedCalo_dRmaxJ1);
	tauseedCalo_dRmaxvec.push_back(tauseedCalo_dRmaxJ2);
	tauseedCalo_dRmaxvec.push_back(tauseedCalo_dRmaxJ3);
	tauseedCalo_dRmaxvec.push_back(tauseedCalo_dRmaxJ4);
	tauseedCalo_dRmaxvec.push_back(tauseedCalo_dRmaxJ5);
	tauseedCalo_dRmaxvec.push_back(tauseedCalo_dRmaxJ6);
	tauseedCalo_dRmaxvec.push_back(tauseedCalo_dRmaxJ7);
   // }; 
   
   //BDTJetScore
    TH1F* BDTJetScore = (TH1F*) fileZtautau.Get("h_myBDTJetScore");
    TH1F* BDTJetScoreJ1 = (TH1F*) fileQCDJ1.Get("h_myBDTJetScore");
    TH1F* BDTJetScoreJ2 = (TH1F*) fileQCDJ2.Get("h_myBDTJetScore");
    TH1F* BDTJetScoreJ3 = (TH1F*) fileQCDJ3.Get("h_myBDTJetScore");
    TH1F* BDTJetScoreJ4 = (TH1F*) fileQCDJ4.Get("h_myBDTJetScore");
    TH1F* BDTJetScoreJ5 = (TH1F*) fileQCDJ5.Get("h_myBDTJetScore");
    TH1F* BDTJetScoreJ6 = (TH1F*) fileQCDJ6.Get("h_myBDTJetScore");    
    TH1F* BDTJetScoreJ7 = (TH1F*) fileQCDJ7.Get("h_myBDTJetScore");
      std::vector<TH1F*> BDTJetScorevec;
      BDTJetScorevec.push_back(BDTJetScoreJ1);
      BDTJetScorevec.push_back(BDTJetScoreJ2);
      BDTJetScorevec.push_back(BDTJetScoreJ3);
      BDTJetScorevec.push_back(BDTJetScoreJ4);
      BDTJetScorevec.push_back(BDTJetScoreJ5);
      BDTJetScorevec.push_back(BDTJetScoreJ6);
      BDTJetScorevec.push_back(BDTJetScoreJ7);

    //JetBDTSigLoose
    TH1F* JetBDTSigLoose = (TH1F*) fileZtautau.Get("h_myJetBDTSigLoose");
    TH1F* JetBDTSigLooseJ1 = (TH1F*) fileQCDJ1.Get("h_myJetBDTSigLoose");
    TH1F* JetBDTSigLooseJ2 = (TH1F*) fileQCDJ2.Get("h_myJetBDTSigLoose");
    TH1F* JetBDTSigLooseJ3 = (TH1F*) fileQCDJ3.Get("h_myJetBDTSigLoose");
    TH1F* JetBDTSigLooseJ4 = (TH1F*) fileQCDJ4.Get("h_myJetBDTSigLoose");
    TH1F* JetBDTSigLooseJ5 = (TH1F*) fileQCDJ5.Get("h_myJetBDTSigLoose");
    TH1F* JetBDTSigLooseJ6 = (TH1F*) fileQCDJ6.Get("h_myJetBDTSigLoose");
    TH1F* JetBDTSigLooseJ7 = (TH1F*) fileQCDJ7.Get("h_myJetBDTSigLoose");
      std::vector<TH1F*> JetBDTSigLoosevec;
      JetBDTSigLoosevec.push_back(JetBDTSigLooseJ1);
      JetBDTSigLoosevec.push_back(JetBDTSigLooseJ2);
      JetBDTSigLoosevec.push_back(JetBDTSigLooseJ3);
      JetBDTSigLoosevec.push_back(JetBDTSigLooseJ4);
      JetBDTSigLoosevec.push_back(JetBDTSigLooseJ5);
      JetBDTSigLoosevec.push_back(JetBDTSigLooseJ6);
      JetBDTSigLoosevec.push_back(JetBDTSigLooseJ7);
      
    //JetBDTSigMedium
    TH1F* JetBDTSigMedium = (TH1F*) fileZtautau.Get("h_myJetBDTSigMedium");
    TH1F* JetBDTSigMediumJ1 = (TH1F*) fileQCDJ1.Get("h_myJetBDTSigMedium");
    TH1F* JetBDTSigMediumJ2 = (TH1F*) fileQCDJ2.Get("h_myJetBDTSigMedium");
    TH1F* JetBDTSigMediumJ3 = (TH1F*) fileQCDJ3.Get("h_myJetBDTSigMedium");
    TH1F* JetBDTSigMediumJ4 = (TH1F*) fileQCDJ4.Get("h_myJetBDTSigMedium");
    TH1F* JetBDTSigMediumJ5 = (TH1F*) fileQCDJ5.Get("h_myJetBDTSigMedium");
    TH1F* JetBDTSigMediumJ6 = (TH1F*) fileQCDJ6.Get("h_myJetBDTSigMedium");
    TH1F* JetBDTSigMediumJ7 = (TH1F*) fileQCDJ7.Get("h_myJetBDTSigMedium");
      std::vector<TH1F*> JetBDTSigMediumvec;
      JetBDTSigMediumvec.push_back(JetBDTSigMediumJ1);
      JetBDTSigMediumvec.push_back(JetBDTSigMediumJ2);
      JetBDTSigMediumvec.push_back(JetBDTSigMediumJ3);
      JetBDTSigMediumvec.push_back(JetBDTSigMediumJ4);
      JetBDTSigMediumvec.push_back(JetBDTSigMediumJ5);
      JetBDTSigMediumvec.push_back(JetBDTSigMediumJ6);
      JetBDTSigMediumvec.push_back(JetBDTSigMediumJ7);
      
    //JetBDTSigTight
    TH1F* JetBDTSigTight = (TH1F*) fileZtautau.Get("h_myJetBDTSigTight");
    TH1F* JetBDTSigTightJ1 = (TH1F*) fileQCDJ1.Get("h_myJetBDTSigTight");
    TH1F* JetBDTSigTightJ2 = (TH1F*) fileQCDJ2.Get("h_myJetBDTSigTight");
    TH1F* JetBDTSigTightJ3 = (TH1F*) fileQCDJ3.Get("h_myJetBDTSigTight");
    TH1F* JetBDTSigTightJ4 = (TH1F*) fileQCDJ4.Get("h_myJetBDTSigTight");
    TH1F* JetBDTSigTightJ5 = (TH1F*) fileQCDJ5.Get("h_myJetBDTSigTight");
    TH1F* JetBDTSigTightJ6 = (TH1F*) fileQCDJ6.Get("h_myJetBDTSigTight");
    TH1F* JetBDTSigTightJ7 = (TH1F*) fileQCDJ7.Get("h_myJetBDTSigTight");
      std::vector<TH1F*> JetBDTSigTightvec;
      JetBDTSigTightvec.push_back(JetBDTSigTightJ1);
      JetBDTSigTightvec.push_back(JetBDTSigTightJ2);
      JetBDTSigTightvec.push_back(JetBDTSigTightJ3);
      JetBDTSigTightvec.push_back(JetBDTSigTightJ4);
      JetBDTSigTightvec.push_back(JetBDTSigTightJ5);
      JetBDTSigTightvec.push_back(JetBDTSigTightJ6);
      JetBDTSigTightvec.push_back(JetBDTSigTightJ7);
      
      //likelihood
    TH1F* likelihood = (TH1F*) fileZtautau.Get("h_mylikelihood");
    TH1F* likelihoodJ1 = (TH1F*) fileQCDJ1.Get("h_mylikelihood");
    TH1F* likelihoodJ2 = (TH1F*) fileQCDJ2.Get("h_mylikelihood");
    TH1F* likelihoodJ3 = (TH1F*) fileQCDJ3.Get("h_mylikelihood");
    TH1F* likelihoodJ4 = (TH1F*) fileQCDJ4.Get("h_mylikelihood");
    TH1F* likelihoodJ5 = (TH1F*) fileQCDJ5.Get("h_mylikelihood");
    TH1F* likelihoodJ6 = (TH1F*) fileQCDJ6.Get("h_mylikelihood");
    TH1F* likelihoodJ7 = (TH1F*) fileQCDJ7.Get("h_mylikelihood");
      std::vector<TH1F*> likelihoodvec;
      likelihoodvec.push_back(likelihoodJ1);
      likelihoodvec.push_back(likelihoodJ2);
      likelihoodvec.push_back(likelihoodJ3);
      likelihoodvec.push_back(likelihoodJ4);
      likelihoodvec.push_back(likelihoodJ5);
      likelihoodvec.push_back(likelihoodJ6);
      likelihoodvec.push_back(likelihoodJ7);
      
      //tauLlhLoose
    TH1F* tauLlhLoose = (TH1F*) fileZtautau.Get("h_mytauLlhLoose");
    TH1F* tauLlhLooseJ1 = (TH1F*) fileQCDJ1.Get("h_mytauLlhLoose");
    TH1F* tauLlhLooseJ2 = (TH1F*) fileQCDJ2.Get("h_mytauLlhLoose");
    TH1F* tauLlhLooseJ3 = (TH1F*) fileQCDJ3.Get("h_mytauLlhLoose");
    TH1F* tauLlhLooseJ4 = (TH1F*) fileQCDJ4.Get("h_mytauLlhLoose");
    TH1F* tauLlhLooseJ5 = (TH1F*) fileQCDJ5.Get("h_mytauLlhLoose");
    TH1F* tauLlhLooseJ6 = (TH1F*) fileQCDJ6.Get("h_mytauLlhLoose");
    TH1F* tauLlhLooseJ7 = (TH1F*) fileQCDJ7.Get("h_mytauLlhLoose");
      std::vector<TH1F*> tauLlhLoosevec;
      tauLlhLoosevec.push_back(tauLlhLooseJ1);
      tauLlhLoosevec.push_back(tauLlhLooseJ2);
      tauLlhLoosevec.push_back(tauLlhLooseJ3);
      tauLlhLoosevec.push_back(tauLlhLooseJ4);
      tauLlhLoosevec.push_back(tauLlhLooseJ5);
      tauLlhLoosevec.push_back(tauLlhLooseJ6);
      tauLlhLoosevec.push_back(tauLlhLooseJ7);
      
      
      //tauLlhMedium
    TH1F* tauLlhMedium = (TH1F*) fileZtautau.Get("h_mytauLlhMedium");
    TH1F* tauLlhMediumJ1 = (TH1F*) fileQCDJ1.Get("h_mytauLlhMedium");
    TH1F* tauLlhMediumJ2 = (TH1F*) fileQCDJ2.Get("h_mytauLlhMedium");
    TH1F* tauLlhMediumJ3 = (TH1F*) fileQCDJ3.Get("h_mytauLlhMedium");
    TH1F* tauLlhMediumJ4 = (TH1F*) fileQCDJ4.Get("h_mytauLlhMedium");
    TH1F* tauLlhMediumJ5 = (TH1F*) fileQCDJ5.Get("h_mytauLlhMedium");
    TH1F* tauLlhMediumJ6 = (TH1F*) fileQCDJ6.Get("h_mytauLlhMedium");
    TH1F* tauLlhMediumJ7 = (TH1F*) fileQCDJ7.Get("h_mytauLlhMedium");
      std::vector<TH1F*> tauLlhMediumvec;
      tauLlhMediumvec.push_back(tauLlhMediumJ1);
      tauLlhMediumvec.push_back(tauLlhMediumJ2);
      tauLlhMediumvec.push_back(tauLlhMediumJ3);
      tauLlhMediumvec.push_back(tauLlhMediumJ4);
      tauLlhMediumvec.push_back(tauLlhMediumJ5);
      tauLlhMediumvec.push_back(tauLlhMediumJ6);
      tauLlhMediumvec.push_back(tauLlhMediumJ7);
      
      //tauLlhTight
    TH1F* tauLlhTight = (TH1F*) fileZtautau.Get("h_mytauLlhTight");
    TH1F* tauLlhTightJ1 = (TH1F*) fileQCDJ1.Get("h_mytauLlhTight");
    TH1F* tauLlhTightJ2 = (TH1F*) fileQCDJ2.Get("h_mytauLlhTight");
    TH1F* tauLlhTightJ3 = (TH1F*) fileQCDJ3.Get("h_mytauLlhTight");
    TH1F* tauLlhTightJ4 = (TH1F*) fileQCDJ4.Get("h_mytauLlhTight");
    TH1F* tauLlhTightJ5 = (TH1F*) fileQCDJ5.Get("h_mytauLlhTight");
    TH1F* tauLlhTightJ6 = (TH1F*) fileQCDJ6.Get("h_mytauLlhTight");
    TH1F* tauLlhTightJ7 = (TH1F*) fileQCDJ7.Get("h_mytauLlhTight");
      std::vector<TH1F*> tauLlhTightvec;
      tauLlhTightvec.push_back(tauLlhTightJ1);
      tauLlhTightvec.push_back(tauLlhTightJ2);
      tauLlhTightvec.push_back(tauLlhTightJ3);
      tauLlhTightvec.push_back(tauLlhTightJ4);
      tauLlhTightvec.push_back(tauLlhTightJ5);
      tauLlhTightvec.push_back(tauLlhTightJ6);
      tauLlhTightvec.push_back(tauLlhTightJ7);
      
      //TruthType
    TH1F* tauTruthType = (TH1F*) fileZtautau.Get(Form("h_myTauTruthType_%s",prong.c_str()));
    TH1F* tauTruthTypeJ1 = (TH1F*) fileQCDJ1.Get(Form("h_myTauTruthType_%s",prong.c_str()));
    TH1F* tauTruthTypeJ2 = (TH1F*) fileQCDJ2.Get(Form("h_myTauTruthType_%s",prong.c_str()));
    TH1F* tauTruthTypeJ3 = (TH1F*) fileQCDJ3.Get(Form("h_myTauTruthType_%s",prong.c_str()));
    TH1F* tauTruthTypeJ4 = (TH1F*) fileQCDJ4.Get(Form("h_myTauTruthType_%s",prong.c_str()));
    TH1F* tauTruthTypeJ5 = (TH1F*) fileQCDJ5.Get(Form("h_myTauTruthType_%s",prong.c_str()));
    TH1F* tauTruthTypeJ6 = (TH1F*) fileQCDJ6.Get(Form("h_myTauTruthType_%s",prong.c_str()));
    TH1F* tauTruthTypeJ7 = (TH1F*) fileQCDJ7.Get(Form("h_myTauTruthType_%s",prong.c_str()));
     std::vector<TH1F*> tauTruthTypevec;
      tauTruthTypevec.push_back(tauTruthTypeJ1);
      tauTruthTypevec.push_back(tauTruthTypeJ2);
      tauTruthTypevec.push_back(tauTruthTypeJ3);
      tauTruthTypevec.push_back(tauTruthTypeJ4);
      tauTruthTypevec.push_back(tauTruthTypeJ5);
      tauTruthTypevec.push_back(tauTruthTypeJ6);
      tauTruthTypevec.push_back(tauTruthTypeJ7);
     
      
/*  double scalefactor_tauPt;
  double scalefactor_tauEta;
  double scalefactor_tauPhi;
  double scalefactor_tauseedCalo_centFrac;
  double scalefactor_tauseedCalo_trkAvgDist;
  double scalefactor_taucalcVars_calRadius;
  double scalefactor_tautrFlightPathSig;
  double scalefactor_tauseedCalo_nWideTrk;
  double scalefactor_tauseedCalo_lead2ClusterEOverAllClusterE;
  double scalefactor_taumassTrkSys;
  double scalefactor_tauseedCalo_dRmax;
  double scalefactor_jetPt; 
  double scalefactor_jetEta; 
  double scalefactor_jetPhi;
  double scalefactor_QCDpt;
  double scalefactor_QCDeta;
  double scalefactor_QCDphi;
  double scalefactor_QCDn;*/

  //how to get the weight for a data sample
  double scalefactor_QCDJ1=GetWeight(fileQCDJ1,5,"",true);
  double scalefactor_QCDJ2=GetWeight(fileQCDJ2,5,"",true);
  double scalefactor_QCDJ3=GetWeight(fileQCDJ3,5,"",true);
  double scalefactor_QCDJ4=GetWeight(fileQCDJ4,5,"",true);
  double scalefactor_QCDJ5=GetWeight(fileQCDJ5,5,"",true);
  double scalefactor_QCDJ6=GetWeight(fileQCDJ6,5,"",true);
  double scalefactor_QCDJ7=GetWeight(fileQCDJ7,5,"",true);
    std::vector<double> scale;
    scale.push_back(scalefactor_QCDJ1);
    scale.push_back(scalefactor_QCDJ2);
    scale.push_back(scalefactor_QCDJ3);
    scale.push_back(scalefactor_QCDJ4);
    scale.push_back(scalefactor_QCDJ5);
    scale.push_back(scalefactor_QCDJ6);
    scale.push_back(scalefactor_QCDJ7);
  

  TCanvas c1("canvas","Histogramm"); //c1(name,title)
  //c1.Divide(2,1);//2 Spalten, 1 Zeile
//  
 // --- TruthType ---
 /*   TH1F* tauTruthTypeQCD = 0;
    
    weight(tauTruthTypeQCD, tauTruthTypevec, scale);
    plot3(tauTruthType, tauTruthTypeQCD, "ParticleID", 220.,0.7,0.,0.);
    legend3(tauTruthType, tauTruthTypeQCD, "ParticleID for #tau", "ParticleID for QCD samples", 0.2 , 0.75 , 0.5 , 0.92);
    //plot1(tauTruthType, "ParticleID", 30.,-1,-30.,0.);
    
    
    TPaveText *pt = 0;
    
    if (prong == "3P")
    {
    pt = new TPaveText(-150,0.1,-50,0.25);
    pt->AddText("#pm 24 #Rightarrow W^{#pm}");
    pt->AddText("#pm 16 #Rightarrow #nu_{#tau}, #bar{#nu_{#tau}}");
    pt->AddText("#pm 15 #Rightarrow #tau^{#pm}");
    pt->AddText("#pm 211/213 #Rightarrow #pi^{#pm}/#rho^{#pm}");
    pt->AddText("22 #Rightarrow Photon");
    pt->SetFillColor(4000);
    pt->SetBorderSize(0);
    }
    else
    {
     pt = new TPaveText(-150,0.1,-50,0.25);
    pt->AddText("#pm 24 #Rightarrow W^{#pm}");
    pt->AddText("#pm 15 #Rightarrow #tau^{#pm}");
    pt->AddText("#pm 211/213 #Rightarrow #pi^{#pm}/#rho^{#pm}");;
    pt->AddText("22 #Rightarrow Photon");
    pt->AddText("#pm 211/213 #Rightarrow #pi/#rho, #bar{#pi}/#bar{#rho}");
    pt->SetFillColor(4000);
    pt->SetBorderSize(0);
    }
    pt->Draw();
    
    //c1.WaitPrimitive();

    c1.Print(Form("ParticleID_tau_withoutPt_large_%s.png",prong.c_str()));
    delete leg;
    delete pt;
    leg = 0;
    c1.Clear();
 
  // --- BDTJetScore ---
     TH1F* BDTJetScoreQCD = 0;
    
    weight(BDTJetScoreQCD, BDTJetScorevec, scale);
    plot3(BDTJetScore,BDTJetScoreQCD, "BDTJetScore", 1.,0.75,0.,0.);
    legend3(BDTJetScore,BDTJetScoreQCD, "BDTJetScore_{#tau}", "BDTJetScore_{QCD}", 0.2 , 0.75 , 0.5 , 0.92);
    
    //c1.WaitPrimitive();

    c1.Print(Form("BDTJetScore_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();
    
  // --- JetBDTSigLoose ---
     TH1F* JetBDTSigLooseQCD = 0;
    weight(JetBDTSigLooseQCD, JetBDTSigLoosevec, scale);
    plot3(JetBDTSigLoose,JetBDTSigLooseQCD, "JetBDTSigLoose", 1.5,1.,-0.5,0.);
    legend3(JetBDTSigLoose,JetBDTSigLooseQCD, "JetBDTSigLoose_{#tau}", "JetBDTSigLoose_{QCD}", 0.3 , 0.7 , 0.5 , 0.89);
    
    //c1.WaitPrimitive();

    c1.Print(Form("JetBDTSigLoose_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();
    
  // --- JetBDTSigMedium ---
     TH1F* JetBDTSigMediumQCD = 0;
    weight(JetBDTSigMediumQCD, JetBDTSigMediumvec, scale);
    plot3(JetBDTSigMedium,JetBDTSigMediumQCD, "JetBDTSigMedium", 1.5,-1.,0.,0.);
    legend3(JetBDTSigMedium,JetBDTSigMediumQCD, "JetBDTSigMedium_{#tau}", "JetBDTSigMedium_{QCD}", 0.3 , 0.7 , 0.5 , 0.89);
    
    //c1.WaitPrimitive();

    c1.Print(Form("JetBDTSigMedium_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();
 
  // --- JetBDTSigTight ---
     TH1F* JetBDTSigTightQCD = 0;
    weight(JetBDTSigTightQCD, JetBDTSigTightvec, scale);
    plot3(JetBDTSigTight,JetBDTSigTightQCD, "JetBDTSigTight", 1.5,-1.,0.,0.);
    legend3(JetBDTSigTight,JetBDTSigTightQCD, "JetBDTSigTight_{#tau}", "JetBDTSigTight_{QCD}", 0.3 , 0.7 , 0.5 , 0.89);
    
    //c1.WaitPrimitive();

    c1.Print(Form("JetBDTSigTight_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();
    
  // --- likelihood ---
     TH1F* likelihoodQCD = 0;
    weight(likelihoodQCD, likelihoodvec, scale);
    plot3(likelihood,likelihoodQCD, "likelihood", 20.,-1.,-20.,0.);
    legend3(likelihood,likelihoodQCD, "likelihood_{#tau}", "likelihood_{QCD}", 0.2 , 0.73 , 0.4 , 0.89);
    
    //c1.WaitPrimitive();

    c1.Print(Form("likelihood_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();
    
   // --- tauLlhLoose ---
     TH1F* tauLlhLooseQCD = 0;
    weight(tauLlhLooseQCD, tauLlhLoosevec, scale);
    plot3(tauLlhLoose,tauLlhLooseQCD, "tauLlhLoose", 1.5,-1.,0.,0.);
    legend3(tauLlhLoose,tauLlhLooseQCD, "tauLlhLoose_{#tau}", "tauLlhLoose_{QCD}",0.3 , 0.7 , 0.5 , 0.89);
    
    //c1.WaitPrimitive();

    c1.Print(Form("tauLlhLoose_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();   
    
  // --- tauLlhMedium ---
     TH1F* tauLlhMediumQCD = 0;
    weight(tauLlhMediumQCD, tauLlhMediumvec, scale);
    plot3(tauLlhMedium,tauLlhMediumQCD, "tauLlhMedium", 1.5,-1.,0.,0.);
    legend3(tauLlhMedium,tauLlhMediumQCD, "tauLlhMedium_{#tau}", "tauLlhMedium_{QCD}", 0.3 , 0.7 , 0.5 , 0.89);
    
    //c1.WaitPrimitive();

    c1.Print(Form("tauLlhMedium_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();  
    
  // --- tauLlhTight ---
     TH1F* tauLlhTightQCD = 0; 
    weight(tauLlhTightQCD, tauLlhTightvec, scale);
    plot3(tauLlhTight,tauLlhTightQCD, "tauLlhTight", 1.5,-1.,0.,0.);
    legend3(tauLlhTight,tauLlhTightQCD, "tauLlhTight_{#tau}", "tauLlhTight_{QCD}", 0.3 , 0.7 , 0.5 , 0.89);
    
    //c1.WaitPrimitive();

    c1.Print(Form("tauLlhTight_8mar_mitTM_dijet_%s.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear(); 
    
 */


  // --- seedCalo_centFrac ---
    TH1F* tauseedCalo_centFracQCD = 0;     
    weight(tauseedCalo_centFracQCD, tauseedCalo_centFracvec, scale); 
    assert(tauseedCalo_centFracQCD != 0);
    plot3(tauseedCalo_centFrac,tauseedCalo_centFracQCD,tauseedCalo_centFrac_data, "f_{core}", 1.,-1.,0.,0.);
    legend3(tauseedCalo_centFrac,tauseedCalo_centFracQCD,tauseedCalo_centFrac_data, "f_{core,#tau}", "f_{core,QCD}", "f_{core,data}", 0.2 , 0.8 , 0.4 , 0.9);
    
    //c1.WaitPrimitive();

    c1.Print(Form("f_core_%s_pj_Vergleich.png",prong.c_str()));
    delete leg;
    leg = 0;
    c1.Clear();
  
  // --- seedCalo_trkAvgDist ---
    TH1F* tauseedCalo_trkAvgDistQCD = 0;
    weight(tauseedCalo_trkAvgDistQCD, tauseedCalo_trkAvgDistvec, scale);
    plot3(tauseedCalo_trkAvgDist, tauseedCalo_trkAvgDistQCD,tauseedCalo_trkAvgDist_data,  "R_{track}", 0.35,-1.,0.,0.);
    legend3(tauseedCalo_trkAvgDist, tauseedCalo_trkAvgDistQCD,tauseedCalo_trkAvgDist_data,  "R_{track,#tau}", "R_{track,QCD}",  "R_{track,data}",0.48,0.67,.73,0.81); 
    
    //c1.WaitPrimitive();

    c1.Print(Form("R_track_%s_pj_Vergleich.png",prong.c_str()));
    delete leg; //free(leg);//
    leg = 0;
    c1.Clear();
   
 //====================== 1prong histograms =================================================================================
  if (prong == "1P")
  {  
    // --- calcVars_calRadius ---
      TH1F* taucalcVars_calRadiusQCD = 0;
      weight(taucalcVars_calRadiusQCD, taucalcVars_calRadiusvec, scale);
      plot3(taucalcVars_calRadius, taucalcVars_calRadiusQCD, taucalcVars_calRadius_data, "R_{calo}", 0.3,-1.,0.,0.);
      legend3(taucalcVars_calRadius, taucalcVars_calRadiusQCD, taucalcVars_calRadius_data, "R_{calo,#tau}", "R_{calo,QCD}", "R_{calo,data}", 0.7,0.67,.83,0.81); 
      
      //c1.WaitPrimitive();

      c1.Print(Form("R_calo_%s_pj_Vergleich.png",prong.c_str()));
      delete leg;
      leg = 0;
      c1.Clear();
      
    // --- seedCalo_nWideTrk ---
      TH1F* tauseedCalo_nWideTrkQCD = 0;
      weight(tauseedCalo_nWideTrkQCD, tauseedCalo_nWideTrkvec, scale);
      plot3(tauseedCalo_nWideTrk, tauseedCalo_nWideTrkQCD, tauseedCalo_nWideTrk_data, "#sum N_{trk}^{iso}", 6.,-1.,0.,0.);
      legend3(tauseedCalo_nWideTrk, tauseedCalo_nWideTrkQCD, tauseedCalo_nWideTrk_data, "#sum N_{trk,#tau}^{iso}", "#sum N_{trk,QCD}^{iso}", "#sum N_{trk,data}^{iso}",0.38,0.67,.73,0.81); 
      
      //c1.WaitPrimitive();

      c1.Print(Form("nWideTrk_%s_pj_Vergleich.png",prong.c_str()));
      delete leg;
      leg = 0;
      c1.Clear();
      
    // --- seedCalo_lead2ClusterEOverAllClusterE ---
      TH1F* tauseedCalo_lead2ClusterEOverAllClusterEQCD = 0;
      weight(tauseedCalo_lead2ClusterEOverAllClusterEQCD, tauseedCalo_lead2ClusterEOverAllClusterEvec, scale);
      plot3(tauseedCalo_lead2ClusterEOverAllClusterE, tauseedCalo_lead2ClusterEOverAllClusterEQCD, tauseedCalo_lead2ClusterEOverAllClusterE_data,"f_{2 lead clusters}", 1.1,-1.,0.,0.);
      legend3(tauseedCalo_lead2ClusterEOverAllClusterE, tauseedCalo_lead2ClusterEOverAllClusterEQCD,tauseedCalo_lead2ClusterEOverAllClusterE_data, "f_{2 lead clusters,#tau}", "f_{2 lead clusters,QCD}","f_{2 lead clusters,data}", 0.18,0.77,.46,0.91); 
      
      //c1.WaitPrimitive();

      c1.Print(Form("lead2ClusterE_%s_pj_Vergleich.png",prong.c_str()));
      delete leg;
      leg = 0;
      c1.Clear(); 
  };
  
//=============================== 3prong histograms =======================================================================================

  if (prong == "3P")
  {
    // --- trFlightPathSig ---
      TH1F* tautrFlightPathSigQCD = 0;
      weight(tautrFlightPathSigQCD, tautrFlightPathSigvec, scale);
      plot3(tautrFlightPathSig, tautrFlightPathSigQCD, tautrFlightPathSig_data, "S_{T}^{flight}", 15.,-1.,-15.,0.);
      legend3(tautrFlightPathSig, tautrFlightPathSigQCD, tautrFlightPathSig_data, "S_{T,#tau}^{flight}", "S_{T,QCD}^{flight}", "S_{T,data}^{flight}", 0.48,0.67,.73,0.81); 
      
      //c1.WaitPrimitive();

      c1.Print(Form("transflightsig_%s_pj_Vergleich.png",prong.c_str()));
      delete leg;
      leg = 0;
      c1.Clear();
      
    //massTrkSys
      TH1F* taumassTrkSysQCD = 0;
      weight(taumassTrkSysQCD, taumassTrkSysvec, scale);
      plot3( taumassTrkSys, taumassTrkSysQCD, taumassTrkSys_data, "m_{tracks}[Gev]", 7.,-1.,0.,0.);
      legend3( taumassTrkSys, taumassTrkSysQCD, taumassTrkSys_data, "m_{tracks,#tau}", "m_{tracks,QCD}", "m_{tracks,data}",0.48,0.67,.73,0.81); 
      
      //c1.WaitPrimitive();

      c1.Print(Form("massTrkSys_%s_pj_Vergleich.png",prong.c_str()));
      delete leg;
      leg = 0;
      c1.Clear();
   
    // --- seedCalo_dRmax ---
      TH1F* tauseedCalo_dRmaxQCD = 0;
      weight(tauseedCalo_dRmaxQCD, tauseedCalo_dRmaxvec, scale);
      plot3( tauseedCalo_dRmax, tauseedCalo_dRmaxQCD,tauseedCalo_dRmax_data,  "#Delta R_{max}", 0.2,0.095,0.,0.);
      legend3( tauseedCalo_dRmax, tauseedCalo_dRmaxQCD, tauseedCalo_dRmax_data,doubtostr(tauseedCalo_dRmax->GetEntries(), "#Delta R_{max,#tau}, #Entries: "), 
	       doubtostr(tauseedCalo_dRmaxQCD->GetEntries(), "#Delta R_{max,QCD}, #Entries: "),  
	       doubtostr(tauseedCalo_dRmax_data->GetEntries(), "#Delta R_{max,data}, #Entries: "),0.68,0.7,.85,0.89); 
      
      //c1.WaitPrimitive();

      c1.Print(Form("dRmax_%s_pj_Vergleich.png",prong.c_str()));
      delete leg;
      leg = 0;
      c1.Clear();
  }; 

  // ============== general kinematic variables =====================================================
 //--- pt ---
    std::cout << "=== PT ===" << std::endl;
    TH1F* tauptQCD =0;
    weight(tauptQCD, tauptvec, scale);
    plot3(taupt, tauptQCD,taupt_data,  "p_{T}", 110.,-1.,0.,0.);
    legend3(taupt,tauptQCD, taupt_data,doubtostr(taupt->GetEntries(), "p_{T,#tau}, #Entries: "),
	    doubtostr(tauptQCD->GetEntries(),  "p_{T,QCD}, #Entries: "),
	    doubtostr(taupt_data->GetEntries(),  "p_{T,data}, #Entries: "), 0.42,0.74,0.89,0.89);  
    c1.Update();
    //c1.WaitPrimitive();

    c1.Print("pt_pj_Vergleich.png");
    delete leg;
    c1.Clear();


   // --- eta ---
    // c1.cd(2);
    std::cout << "=== ETA ===" << std::endl;
    TH1F* tauetaQCD = 0;    
    weight(tauetaQCD, tauetavec, scale);
    plot3(taueta, tauetaQCD, taueta_data,"#eta", 3.,-1,-3.,0.);
    legend3(taueta,tauetaQCD, taueta_data,doubtostr(taueta->GetEntries(),"#eta_{#tau} #Entries: "), 
					doubtostr(tauetaQCD->GetEntries(),"#eta_{QCD} #Entries: "),
	    doubtostr(taueta_data->GetEntries(),"#eta_{data} #Entries: "), 0.45,0.25,0.69,0.43);
  
    c1.Update();
    //c1.WaitPrimitive();

    c1.Print("eta_pj_Vergleich.png");
    delete leg;
    c1.Clear();
  
    
  // --- phi ---
    std::cout << "=== PHI ===" << std::endl;
    TH1F* tauphiQCD =  0;
    weight(tauphiQCD, tauphivec, scale);
    plot3(tauphi, tauphiQCD, tauphi_data,"#Phi", 5.,-1.,-5.,0.);
    legend3(tauphi,tauphiQCD, tauphi_data,doubtostr(taueta->GetEntries(),"#Phi_{#tau}, #Entries: "),
	    doubtostr(taueta->GetEntries(),"#Phi_{QCD}, #Entries: "),
	    doubtostr(taueta->GetEntries(),"#Phi_{data}, #Entries: "), 0.45,0.25,0.69,0.43);
  
    c1.Update();
    //c1.WaitPrimitive();

    c1.Print("phi_pj_Vergleich.png"); 
    delete leg;
    c1.Clear(); 
}

