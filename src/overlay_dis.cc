#include <iostream>      
#include <vector>        
#include <stdlib.h>      
#include <utility>       
#include <chrono>        
                         
#include <boost/optional.hpp>                       
#include <TFile.h>                               
#include <TChain.h>                              
#include <TH1.h>                                 
#include <TLorentzVector.h>                      
#include <TTree.h>                               
#include <TRandom3.h>                            
                                                 
#include "Higgs2diphoton.hh"

using namespace std; 

Higgs2diphoton Hdecay; 
bool sort_pt (TLorentzVector i, TLorentzVector j){return (i.Pt()>j.Pt());}

int main(){
  //==============================================
  TChain chain_mc_b("t3"); 
  TChain chain_mc_s("t3"); 
  TChain chain_data("mini"); 
  //==============================================
  
  //All MC files
  chain_mc_s.Add("$TMPDIR/H1.0j_GGFHT_B_6500_pt25.0_eta4.5_r100_100.root",0); 
  chain_mc_s.Add("$TMPDIR/H1.0j_GGFHT_B_6500_pt25.0_eta4.5_r100_101.root",0); 
  
  chain_mc_b.Add("$TMPDIR/born7.root",0); 
  chain_mc_b.Add("$TMPDIR/born6.root",0); 
  chain_mc_b.Add("$TMPDIR/born8.root",0); 

  //All Data files
  chain_data.Add("$TMPDIR/data15.root",0); 
  chain_data.Add("$TMPDIR/data16_DS1.root",0); 
  chain_data.Add("$TMPDIR/data16_DS2.root",0); 
  chain_data.Add("$TMPDIR/data16_DS3.root",0); 
  //==============================================
  //Variables 
  Float_t s, yydr, y1dr, y2dr, ptratio, y1y, y2y, jety, yydy; 
  Float_t y2E, y1E, jetE, yyE, y1pt, y2pt, yypt, yyy, costhet; 
  //==============================================
  //Trees
  constexpr size_t max = 10;                                                    
  
  //MC 
  Float_t px[max], py[max], pz[max], E[max];                            
  Int_t nparticle, kf[max];                                                 
  Double_t weight; 
  
  chain_mc_s.SetBranchAddress("nparticle",&nparticle);
  chain_mc_s.SetBranchAddress("kf",kf);
  chain_mc_s.SetBranchAddress("px",px);
  chain_mc_s.SetBranchAddress("py",py);
  chain_mc_s.SetBranchAddress("pz",pz);
  chain_mc_s.SetBranchAddress("E",E);                                            
  chain_mc_s.SetBranchAddress("weight2",&weight); 
  
  chain_mc_b.SetBranchAddress("nparticle",&nparticle);
  chain_mc_b.SetBranchAddress("kf",kf);
  chain_mc_b.SetBranchAddress("px",px);
  chain_mc_b.SetBranchAddress("py",py);
  chain_mc_b.SetBranchAddress("pz",pz);
  chain_mc_b.SetBranchAddress("E",E);                                            
  chain_mc_b.SetBranchAddress("weight2",&weight); 
  
  //Data
  Int_t photon_n, jet_n;                                                        
  Float_t photon_m[max], photon_eta[max], photon_phi[max], photon_pt[max];      
  Float_t jet_m[max], jet_eta[max], jet_phi[max], jet_pt[max];                  
                                                                              
  chain_data.SetBranchAddress("photon_n", &photon_n);                                
  chain_data.SetBranchAddress("photon_m", photon_m);                                 
  chain_data.SetBranchAddress("photon_eta", photon_eta);                             
  chain_data.SetBranchAddress("photon_phi", photon_phi);                             
  chain_data.SetBranchAddress("photon_pt", photon_pt);                               
                                                                              
  chain_data.SetBranchAddress("jet_n", &jet_n);                                      
  chain_data.SetBranchAddress("jet_m", jet_m);                                       
  chain_data.SetBranchAddress("jet_eta", jet_eta);                                   
  chain_data.SetBranchAddress("jet_phi", jet_phi);                                   
  chain_data.SetBranchAddress("jet_pt", jet_pt); 

  //============================================
  //List of pts to iterate over
  vector<TString>num;                                                           
  num.emplace_back("50");                                                       
  num.emplace_back("100");                                                      
  num.emplace_back("150");                                                      
  num.emplace_back("200");                                                      
  num.emplace_back("250");                                                      
  num.emplace_back("300");                                                      
  num.emplace_back("350");                                                      
  num.emplace_back("400");                                                      
  num.emplace_back("400p");   

  //============================================
  //Iteraion over the list 
  for (int i=0; i<9; ++i){
    //Make each file
    TString outname = "Variable_Dist_pt"+num[i]+".root"; 
    TFile* out = TFile::Open(outname, "RECREATE"); 
    cout<<"Writing "<<outname<<" ..."<<endl; 
    //=========================================
    //Variable binning 
    int nbins = 100; 
    if (i==6 or i==5){nbins = 40;} 
    if (i==5 or i==8){nbins = 29;} 

    //Making each histogram 
    //MC
    TH1D* h_s_s_mc = new TH1D("Signal__mc__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_s_mc = new TH1D("Signal__mc__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_s_mc = new TH1D("Signal__mc__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_s_mc = new TH1D("Signal__mc__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_s_mc = new TH1D("Signal__mc__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_s_mc = new TH1D("Signal__mc__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_s_mc = new TH1D("Signal__mc__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_s_mc = new TH1D("Signal__mc__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_s_mc = new TH1D("Signal__mc__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_s_mc = new TH1D("Signal__mc__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_s_mc = new TH1D("Signal__mc__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_s_mc = new TH1D("Signal__mc__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_s_mc = new TH1D("Signal__mc__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_s_mc = new TH1D("Signal__mc__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_s_mc = new TH1D("Signal__mc__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_s_mc = new TH1D("Signal__mc__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_s_mc = new TH1D("Signal__mc__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_s_mc = new TH1D("Signal__mc__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
    //Left
    TH1D* h_s_bl_mc = new TH1D("Left__mc__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_bl_mc = new TH1D("Left__mc__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_bl_mc = new TH1D("Left__mc__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_bl_mc = new TH1D("Left__mc__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_bl_mc = new TH1D("Left__mc__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_bl_mc = new TH1D("Left__mc__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_bl_mc = new TH1D("Left__mc__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_bl_mc = new TH1D("Left__mc__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_bl_mc = new TH1D("Left__mc__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_bl_mc = new TH1D("Left__mc__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_bl_mc = new TH1D("Left__mc__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_bl_mc = new TH1D("Left__mc__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_bl_mc = new TH1D("Left__mc__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_bl_mc = new TH1D("Left__mc__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_bl_mc = new TH1D("Left__mc__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_bl_mc = new TH1D("Left__mc__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_bl_mc = new TH1D("Left__mc__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_bl_mc = new TH1D("Left__mc__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
    //Right 
    TH1D* h_s_br_mc = new TH1D("Right__mc__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_br_mc = new TH1D("Right__mc__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_br_mc = new TH1D("Right__mc__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_br_mc = new TH1D("Right__mc__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_br_mc = new TH1D("Right__mc__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_br_mc = new TH1D("Right__mc__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_br_mc = new TH1D("Right__mc__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_br_mc = new TH1D("Right__mc__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_br_mc = new TH1D("Right__mc__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_br_mc = new TH1D("Right__mc__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_br_mc = new TH1D("Right__mc__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_br_mc = new TH1D("Right__mc__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_br_mc = new TH1D("Right__mc__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_br_mc = new TH1D("Right__mc__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_br_mc = new TH1D("Right__mc__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_br_mc = new TH1D("Right__mc__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_br_mc = new TH1D("Right__mc__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_br_mc = new TH1D("Right__mc__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
    //Both
    TH1D* h_s_bg_mc = new TH1D("Bckground__mc__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_bg_mc = new TH1D("Bckground__mc__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_bg_mc = new TH1D("Bckground__mc__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_bg_mc = new TH1D("Bckground__mc__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_bg_mc = new TH1D("Bckground__mc__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_bg_mc = new TH1D("Bckground__mc__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_bg_mc = new TH1D("Bckground__mc__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_bg_mc = new TH1D("Bckground__mc__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_bg_mc = new TH1D("Bckground__mc__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_bg_mc = new TH1D("Bckground__mc__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_bg_mc = new TH1D("Bckground__mc__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_bg_mc = new TH1D("Bckground__mc__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_bg_mc = new TH1D("Bckground__mc__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_bg_mc = new TH1D("Bckground__mc__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_bg_mc = new TH1D("Bckground__mc__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_bg_mc = new TH1D("Bckground__mc__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_bg_mc = new TH1D("Bckground__mc__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_bg_mc = new TH1D("Bckground__mc__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
     
    //Data
    //Signal
    TH1D* h_s_s_data = new TH1D("Signal__data__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_s_data = new TH1D("Signal__data__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_s_data = new TH1D("Signal__data__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_s_data = new TH1D("Signal__data__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_s_data = new TH1D("Signal__data__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_s_data = new TH1D("Signal__data__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_s_data = new TH1D("Signal__data__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_s_data = new TH1D("Signal__data__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_s_data = new TH1D("Signal__data__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_s_data = new TH1D("Signal__data__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_s_data = new TH1D("Signal__data__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_s_data = new TH1D("Signal__data__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_s_data = new TH1D("Signal__data__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_s_data = new TH1D("Signal__data__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_s_data = new TH1D("Signal__data__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_s_data = new TH1D("Signal__data__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_s_data = new TH1D("Signal__data__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_s_data = new TH1D("Signal__data__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
    //Left
    TH1D* h_s_bl_data = new TH1D("Left__data__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_bl_data = new TH1D("Left__data__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_bl_data = new TH1D("Left__data__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_bl_data = new TH1D("Left__data__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_bl_data = new TH1D("Left__data__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_bl_data = new TH1D("Left__data__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_bl_data = new TH1D("Left__data__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_bl_data = new TH1D("Left__data__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_bl_data = new TH1D("Left__data__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_bl_data = new TH1D("Left__data__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_bl_data = new TH1D("Left__data__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_bl_data = new TH1D("Left__data__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_bl_data = new TH1D("Left__data__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_bl_data = new TH1D("Left__data__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_bl_data = new TH1D("Left__data__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_bl_data = new TH1D("Left__data__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_bl_data = new TH1D("Left__data__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_bl_data = new TH1D("Left__data__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
    //Right 
    TH1D* h_s_br_data = new TH1D("Right__data__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_br_data = new TH1D("Right__data__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_br_data = new TH1D("Right__data__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_br_data = new TH1D("Right__data__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_br_data = new TH1D("Right__data__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_br_data = new TH1D("Right__data__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_br_data = new TH1D("Right__data__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_br_data = new TH1D("Right__data__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_br_data = new TH1D("Right__data__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_br_data = new TH1D("Right__data__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_br_data = new TH1D("Right__data__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_br_data = new TH1D("Right__data__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_br_data = new TH1D("Right__data__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_br_data = new TH1D("Right__data__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_br_data = new TH1D("Right__data__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_br_data = new TH1D("Right__data__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_br_data = new TH1D("Right__data__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_br_data = new TH1D("Right__data__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
    //Both
    TH1D* h_s_bg_data = new TH1D("Bckground__data__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);  
    TH1D* h_yydr_bg_data = new TH1D("Bckground__data__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_bg_data = new TH1D("Bckground__data__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_bg_data = new TH1D("Bckground__data__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_bg_data = new TH1D("Bckground__data__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_bg_data = new TH1D("Bckground__data__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_bg_data = new TH1D("Bckground__data__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_bg_data = new TH1D("Bckground__data__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_bg_data = new TH1D("Bckground__data__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_bg_data = new TH1D("Bckground__data__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_bg_data = new TH1D("Bckground__data__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_bg_data = new TH1D("Bckground__data__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_bg_data = new TH1D("Bckground__data__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_bg_data = new TH1D("Bckground__data__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_bg_data = new TH1D("Bckground__data__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_bg_data = new TH1D("Bckground__data__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
    TH1D* h_yyy_bg_data = new TH1D("Bckground__data__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_bg_data = new TH1D("Bckground__data__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
    
    //=========================================
    //Iterate through data
    Long64_t entries = chain_data.GetEntries(); 
    for (long k=0; k<entries; ++k){ 
      chain_data.GetEntry(k); 
      TLorentzVector yy, y1, y2, jet, photons, jets; 
      vector<TLorentzVector> t_y, t_jet; 

      //Assign Particles 
      //Photons
      for (int j=0; j<photon_n; ++j){
        photons.SetPtEtaPhiM(photon_pt[j], photon_eta[j], photon_phi[j], photon_m[j]);
        t_y.emplace_back(photons); 
      }
      //Jets
      if (jet_n!=0){
        for (int j=0; j<jet_n; ++j){
          jets.SetPtEtaPhiM(jet_pt[j], jet_eta[j], jet_phi[j], jet_m[j]);
          t_jet.emplace_back(jets); 
        }
      }
      else{
        continue; 
      }
    
      //Sorting by pT
      sort(t_jet.begin(), t_jet.end(), sort_pt); 
      sort(t_y.begin(), t_y.end(), sort_pt); 

      jet = t_jet[0]; 
      y1 = t_y[0]; 
      y2 = t_y[1]; 
      yy = y1 + y2; 
 

      //All These Cuts 
      //Rapidity Cut                                                               
      bool select = (abs(y2.Rapidity())<2.4);                                   
      select &= (abs(y1.Rapidity())<2.4);                                       
      //PseudoRapidity Cut                                                         
      select &= (abs(y1.PseudoRapidity())<2.37);                                
      select &= !(1.37<abs(y1.PseudoRapidity()) && abs(y1.PseudoRapidity())<1.52);
      select &= (abs(y2.PseudoRapidity())<2.37);                                
      select &= !(1.37<abs(y2.PseudoRapidity()) && abs(y2.PseudoRapidity())<1.52);
      //Pt Cut                                                                     
      select &= (y1.Pt()>.35*yy.M());                                           
      select &= (y2.Pt()>.25*yy.M());                                           
      //Delta R                                                                    
      select &= (y1.DeltaR(jet)>.4);                                            
      select &= (y2.DeltaR(jet)>.4);                                            
      //Jet Cuts                                                                
      for (int i=0; i<jet_n; ++i){                                              
        select &= (t_jet[i].Pt()>30);                                           
        select &= (t_jet[i].Rapidity()<4.4);                                    
      } 
      
      //Diphoton Pt, variable 
      if (i==0){select &= (yy.Pt()<50.);}                
      if (i==1){select &= (yy.Pt()>50. && yy.Pt()<100.);}
      if (i==2){select &= (yy.Pt()>100. && yy.Pt()<150);}
      if (i==3){select &= (yy.Pt()>150. && yy.Pt()<200);}
      if (i==4){select &= (yy.Pt()>200. && yy.Pt()<250);}
      if (i==5){select &= (yy.Pt()>250. && yy.Pt()<300);}
      if (i==6){select &= (yy.Pt()>300. && yy.Pt()<350);}
      if (i==7){select &= (yy.Pt()>350. && yy.Pt()<400);}
      if (i==8){select &= (yy.Pt()>400);}
    
      if (select){
        s = (yy+jet).M();                       
        yydr = abs(y1.DeltaR(y2));              
        y1dr = abs(y1.DeltaR(jet));             
        y2dr = abs(y2.DeltaR(jet));             
        ptratio = abs(y1.Pt())/abs(y2.Pt());    
        y1y = abs(y1.Rapidity());               
        y2y = abs(y2.Rapidity());               
        jety = abs(jet.Rapidity());             
        yydy = abs(y1.Rapidity()-y2.Rapidity());                      
        yyE = abs(yy.E());  
        y1E = abs(y1.E());  
        y2E = abs(y2.E());  
        jetE = abs(jet.E());
        yypt = abs(yy.Pt());
        y1pt = abs(y1.Pt());
        y2pt = abs(y2.Pt());
        yyy = abs(yy.Rapidity());               
        //Cos theta star in Collins Soper       
        costhet = (sinh(abs(y1.PseudoRapidity()-y2.PseudoRapidity()))*2*y1.Pt()*y2.Pt())/(sqrt(1.+pow((yy.Pt()/yy.M()),2.))*pow((yy.M()),2.));

        //Cuts for signal and sideband 
        bool sig = ((yy.M()>121.) && (yy.M()<129.)); 
        bool left = ((yy.M()>105.)&&(yy.M()<121.));
        bool right = ((yy.M()>129.)&&(yy.M()<160.)); 
        bool bg = right + left;         
        
        if (sig){
          h_s_s_data->Fill(s);                                                      
          h_yydr_s_data->Fill(yydr);                                                
          h_y1dr_s_data->Fill(y1dr);                                                
          h_y2dr_s_data->Fill(y2dr);                                                
          h_ptratio_s_data->Fill(ptratio);                                          
          h_y1y_s_data->Fill(y1y);                                                  
          h_y2y_s_data->Fill(y2y);                                                  
          h_jety_s_data->Fill(jety);                                                
          h_yydy_s_data->Fill(yydy);                                                
                                                                                
          h_yyE_s_data->Fill(yyE);                                                  
          h_y1E_s_data->Fill(y1E);                                                  
          h_y2E_s_data->Fill(y2E);                                                  
          h_jetE_s_data->Fill(jetE);                                                
                                                                                
          h_yypt_s_data->Fill(yypt);                                                
          h_y1pt_s_data->Fill(y1pt);                                                
          h_y2pt_s_data->Fill(y2pt);                                                
                                                                                
          h_yyy_s_data->Fill(yyy);                                                  
          h_costhet_s_data->Fill(costhet);       
        }
        if (bg){  
          h_s_bg_data->Fill(s);                                                      
          h_yydr_bg_data->Fill(yydr);                                                
          h_y1dr_bg_data->Fill(y1dr);                                                
          h_y2dr_bg_data->Fill(y2dr);                                                
          h_ptratio_bg_data->Fill(ptratio);                                          
          h_y1y_bg_data->Fill(y1y);                                                  
          h_y2y_bg_data->Fill(y2y);                                                  
          h_jety_bg_data->Fill(jety);                                                
          h_yydy_bg_data->Fill(yydy);                                                
                                                                                
          h_yyE_bg_data->Fill(yyE);                                                  
          h_y1E_bg_data->Fill(y1E);                                                  
          h_y2E_bg_data->Fill(y2E);                                                  
          h_jetE_bg_data->Fill(jetE);                                                
                                                                                
          h_yypt_bg_data->Fill(yypt);                                                
          h_y1pt_bg_data->Fill(y1pt);                                                
          h_y2pt_bg_data->Fill(y2pt);                                                
                                                                                
          h_yyy_bg_data->Fill(yyy);                                                  
          h_costhet_bg_data->Fill(costhet);       
        }
        if (right){
          h_s_br_data->Fill(s);                                                      
          h_yydr_br_data->Fill(yydr);                                                
          h_y1dr_br_data->Fill(y1dr);                                                
          h_y2dr_br_data->Fill(y2dr);                                                
          h_ptratio_br_data->Fill(ptratio);                                          
          h_y1y_br_data->Fill(y1y);                                                  
          h_y2y_br_data->Fill(y2y);                                                  
          h_jety_br_data->Fill(jety);                                                
          h_yydy_br_data->Fill(yydy);                                                
                                                                                
          h_yyE_br_data->Fill(yyE);                                                  
          h_y1E_br_data->Fill(y1E);                                                  
          h_y2E_br_data->Fill(y2E);                                                  
          h_jetE_br_data->Fill(jetE);                                                
                                                                                
          h_yypt_br_data->Fill(yypt);                                                
          h_y1pt_br_data->Fill(y1pt);                                                
          h_y2pt_br_data->Fill(y2pt);                                                
                                                                                
          h_yyy_br_data->Fill(yyy);                                                  
          h_costhet_br_data->Fill(costhet);       
        }
        if (left){
          h_s_bl_data->Fill(s);                                                      
          h_yydr_bl_data->Fill(yydr);                                                
          h_y1dr_bl_data->Fill(y1dr);                                                
          h_y2dr_bl_data->Fill(y2dr);                                                
          h_ptratio_bl_data->Fill(ptratio);                                          
          h_y1y_bl_data->Fill(y1y);                                                  
          h_y2y_bl_data->Fill(y2y);                                                  
          h_jety_bl_data->Fill(jety);                                                
          h_yydy_bl_data->Fill(yydy);                                                
                                                                                
          h_yyE_bl_data->Fill(yyE);                                                  
          h_y1E_bl_data->Fill(y1E);                                                  
          h_y2E_bl_data->Fill(y2E);                                                  
          h_jetE_bl_data->Fill(jetE);                                                
                                                                                
          h_yypt_bl_data->Fill(yypt);                                                
          h_y1pt_bl_data->Fill(y1pt);                                                
          h_y2pt_bl_data->Fill(y2pt);                                                
                                                                                
          h_yyy_bl_data->Fill(yyy);                                                  
          h_costhet_bl_data->Fill(costhet);       
        } 
      }
    }
    cout<<outname<<" data written"<<endl; 
    cout<<""<<endl; 

    //========================================
    //Iterate through MC  
   //Signal  
    entries = chain_mc_s.GetEntries(); 
    for (long j=0; j<entries; ++j){
      
      chain_mc_s.GetEntry(j); 
      TLorentzVector yy, y1, y2, jet; 
      vector <TLorentzVector> photons; 

      for (int i=0; i<nparticle; ++i){
        if (kf[i]==25){
          yy.SetPxPyPzE(px[i], py[i], pz[i],E[i]); 
        }
        else{
          jet.SetPxPyPzE(px[i], py[i], pz[i],E[i]); 
        }
      }
      
      pair<TLorentzVector, TLorentzVector> diphoton = Hdecay(yy); 
      //Sort
      if (diphoton.first.Pt()>diphoton.second.Pt()){
        y1 = diphoton.first; 
        y2 = diphoton.second; 
      }
      else{
        y1 = diphoton.second; 
        y2 = diphoton.first; 
      }
  

      //All These Cuts 
      //Rapidity Cut                                                               
      bool select = (abs(y2.Rapidity())<2.4);                                   
      select &= (abs(y1.Rapidity())<2.4);                                       
      //PseudoRapidity Cut                                                         
      select &= (abs(y1.PseudoRapidity())<2.37);                                
      select &= !(1.37<abs(y1.PseudoRapidity()) && abs(y1.PseudoRapidity())<1.52);
      select &= (abs(y2.PseudoRapidity())<2.37);                                
      select &= !(1.37<abs(y2.PseudoRapidity()) && abs(y2.PseudoRapidity())<1.52);
      //Pt Cut                                                                     
      select &= (y1.Pt()>.35*yy.M());                                           
      select &= (y2.Pt()>.25*yy.M());                                           
      //Delta R                                                                    
      select &= (y1.DeltaR(jet)>.4);                                            
      select &= (y2.DeltaR(jet)>.4);                                            
      //Jet Cuts                                                                
      select &= (jet.Pt()>30);                                           
      select &= (jet.Rapidity()<4.4); 
      
      //Diphoton Pt, variable 
      if (i==0){select &= (yy.Pt()<50.);}                
      if (i==1){select &= (yy.Pt()>50. && yy.Pt()<100.);}
      if (i==2){select &= (yy.Pt()>100. && yy.Pt()<150);}
      if (i==3){select &= (yy.Pt()>150. && yy.Pt()<200);}
      if (i==4){select &= (yy.Pt()>200. && yy.Pt()<250);}
      if (i==5){select &= (yy.Pt()>250. && yy.Pt()<300);}
      if (i==6){select &= (yy.Pt()>300. && yy.Pt()<350);}
      if (i==7){select &= (yy.Pt()>350. && yy.Pt()<400);}
      if (i==8){select &= (yy.Pt()>400);}
    
      if (select){
        s = (yy+jet).M();                       
        yydr = abs(y1.DeltaR(y2));              
        y1dr = abs(y1.DeltaR(jet));             
        y2dr = abs(y2.DeltaR(jet));             
        ptratio = abs(y1.Pt())/abs(y2.Pt());    
        y1y = abs(y1.Rapidity());               
        y2y = abs(y2.Rapidity());               
        jety = abs(jet.Rapidity());             
        yydy = abs(y1.Rapidity()-y2.Rapidity());                      
        yyE = abs(yy.E());  
        y1E = abs(y1.E());  
        y2E = abs(y2.E());  
        jetE = abs(jet.E());
        yypt = abs(yy.Pt());
        y1pt = abs(y1.Pt());
        y2pt = abs(y2.Pt());
        yyy = abs(yy.Rapidity());               
        //Cos theta star in Collins Soper       
        costhet = (sinh(abs(y1.PseudoRapidity()-y2.PseudoRapidity()))*2*y1.Pt()*y2.Pt())/(sqrt(1.+pow((yy.Pt()/yy.M()),2.))*pow((yy.M()),2.));

        
        h_s_s_mc->Fill(s,weight);                                                      
        h_yydr_s_mc->Fill(yydr,weight);                                                
        h_y1dr_s_mc->Fill(y1dr,weight);                                                
        h_y2dr_s_mc->Fill(y2dr,weight);                                                
        h_ptratio_s_mc->Fill(ptratio,weight);                                          
        h_y1y_s_mc->Fill(y1y,weight);                                                  
        h_y2y_s_mc->Fill(y2y,weight);                                                  
        h_jety_s_mc->Fill(jety,weight);                                                
        h_yydy_s_mc->Fill(yydy,weight);                                                
                                                                                
        h_yyE_s_mc->Fill(yyE,weight);                                                  
        h_y1E_s_mc->Fill(y1E,weight);                                                  
        h_y2E_s_mc->Fill(y2E,weight);                                                  
        h_jetE_s_mc->Fill(jetE,weight);                                                
                                                                                
        h_yypt_s_mc->Fill(yypt,weight);                                                
        h_y1pt_s_mc->Fill(y1pt,weight);                                                
        h_y2pt_s_mc->Fill(y2pt,weight);                                                
                                                                                
        h_yyy_s_mc->Fill(yyy,weight);                                                  
        h_costhet_s_mc->Fill(costhet,weight);       
      }
    }
    cout<<outname<<" mc signal written"<<endl; 
    cout<<""<<endl; 
    //Background
    entries = chain_mc_b.GetEntries(); 
    for (long j=0; j<entries; ++j){
      
      chain_mc_b.GetEntry(j); 
      TLorentzVector yy, y1, y2, jet; 
      vector <TLorentzVector> photons; 

      for (int i=0; i<nparticle; ++i){
        if (kf[i]==22){
          photons.emplace_back(px[i], py[i], pz[i], E[i]); 
        }
        else{
          jet.SetPxPyPzE(px[i], py[i], pz[i],E[i]); 
        }
      }
      //Sort Photons
      if (photons[0].Pt()>photons[1].Pt()){
        y1 = photons[0]; 
        y2 = photons[1]; 
      }
      else{
        y1 = photons[1]; 
        y2 = photons[0]; 
      }
      yy = y1 + y2; 

      //All These Cuts 
      //Rapidity Cut                                                               
      bool select = (abs(y2.Rapidity())<2.4);                                   
      select &= (abs(y1.Rapidity())<2.4);                                       
      //PseudoRapidity Cut                                                         
      select &= (abs(y1.PseudoRapidity())<2.37);                                
      select &= !(1.37<abs(y1.PseudoRapidity()) && abs(y1.PseudoRapidity())<1.52);
      select &= (abs(y2.PseudoRapidity())<2.37);                                
      select &= !(1.37<abs(y2.PseudoRapidity()) && abs(y2.PseudoRapidity())<1.52);
      //Pt Cut                                                                     
      select &= (y1.Pt()>.35*yy.M());                                           
      select &= (y2.Pt()>.25*yy.M());                                           
      //Delta R                                                                    
      select &= (y1.DeltaR(jet)>.4);                                            
      select &= (y2.DeltaR(jet)>.4);                                            
      //Jet Cuts                                                                
      select &= (jet.Pt()>30);                                           
      select &= (jet.Rapidity()<4.4); 
      
      //Diphoton Pt, variable 
      if (i==0){select &= (yy.Pt()<50.);}                
      if (i==1){select &= (yy.Pt()>50. && yy.Pt()<100.);}
      if (i==2){select &= (yy.Pt()>100. && yy.Pt()<150);}
      if (i==3){select &= (yy.Pt()>150. && yy.Pt()<200);}
      if (i==4){select &= (yy.Pt()>200. && yy.Pt()<250);}
      if (i==5){select &= (yy.Pt()>250. && yy.Pt()<300);}
      if (i==6){select &= (yy.Pt()>300. && yy.Pt()<350);}
      if (i==7){select &= (yy.Pt()>350. && yy.Pt()<400);}
      if (i==8){select &= (yy.Pt()>400);}
    
      if (select){
        s = (yy+jet).M();                       
        yydr = abs(y1.DeltaR(y2));              
        y1dr = abs(y1.DeltaR(jet));             
        y2dr = abs(y2.DeltaR(jet));             
        ptratio = abs(y1.Pt())/abs(y2.Pt());    
        y1y = abs(y1.Rapidity());               
        y2y = abs(y2.Rapidity());               
        jety = abs(jet.Rapidity());             
        yydy = abs(y1.Rapidity()-y2.Rapidity());                      
        yyE = abs(yy.E());  
        y1E = abs(y1.E());  
        y2E = abs(y2.E());  
        jetE = abs(jet.E());
        yypt = abs(yy.Pt());
        y1pt = abs(y1.Pt());
        y2pt = abs(y2.Pt());
        yyy = abs(yy.Rapidity());               
        //Cos theta star in Collins Soper       
        costhet = (sinh(abs(y1.PseudoRapidity()-y2.PseudoRapidity()))*2*y1.Pt()*y2.Pt())/(sqrt(1.+pow((yy.Pt()/yy.M()),2.))*pow((yy.M()),2.));

        //Cuts for signal and sideband 
        bool left = ((yy.M()>105.)&&(yy.M()<121.)); 
        bool right = ((yy.M()>129.)&&(yy.M()<160.)); 
        bool bg = right + left;         
        
        if (bg){
          h_s_bg_mc->Fill(s,weight);                                                      
          h_yydr_bg_mc->Fill(yydr,weight);                                                
          h_y1dr_bg_mc->Fill(y1dr,weight);                                                
          h_y2dr_bg_mc->Fill(y2dr,weight);                                                
          h_ptratio_bg_mc->Fill(ptratio,weight);                                          
          h_y1y_bg_mc->Fill(y1y,weight);                                                  
          h_y2y_bg_mc->Fill(y2y,weight);                                                  
          h_jety_bg_mc->Fill(jety,weight);                                                
          h_yydy_bg_mc->Fill(yydy,weight);                                                
                                                                                
          h_yyE_bg_mc->Fill(yyE,weight);                                                  
          h_y1E_bg_mc->Fill(y1E,weight);                                                  
          h_y2E_bg_mc->Fill(y2E,weight);                                                  
          h_jetE_bg_mc->Fill(jetE,weight);                                                
                                                                                
          h_yypt_bg_mc->Fill(yypt,weight);                                                
          h_y1pt_bg_mc->Fill(y1pt,weight);                                                
          h_y2pt_bg_mc->Fill(y2pt,weight);                                                
                                                                                
          h_yyy_bg_mc->Fill(yyy,weight);                                                  
          h_costhet_bg_mc->Fill(costhet,weight);       
        }
        if (right){
          h_s_br_mc->Fill(s,weight);                                                      
          h_yydr_br_mc->Fill(yydr,weight);                                                
          h_y1dr_br_mc->Fill(y1dr,weight);                                                
          h_y2dr_br_mc->Fill(y2dr,weight);                                                
          h_ptratio_br_mc->Fill(ptratio,weight);                                          
          h_y1y_br_mc->Fill(y1y,weight);                                                  
          h_y2y_br_mc->Fill(y2y,weight);                                                  
          h_jety_br_mc->Fill(jety,weight);                                                
          h_yydy_br_mc->Fill(yydy,weight);                                                
                                                                                
          h_yyE_br_mc->Fill(yyE,weight);                                                  
          h_y1E_br_mc->Fill(y1E,weight);                                                  
          h_y2E_br_mc->Fill(y2E,weight);                                                  
          h_jetE_br_mc->Fill(jetE,weight);                                                
                                                                                
          h_yypt_br_mc->Fill(yypt,weight);                                                
          h_y1pt_br_mc->Fill(y1pt,weight);                                                
          h_y2pt_br_mc->Fill(y2pt,weight);                                                
                                                                                
          h_yyy_br_mc->Fill(yyy,weight);                                                  
          h_costhet_br_mc->Fill(costhet,weight);       
        }
        if (left){
          h_s_bl_mc->Fill(s,weight);                                                      
          h_yydr_bl_mc->Fill(yydr,weight);                                                
          h_y1dr_bl_mc->Fill(y1dr,weight);                                                
          h_y2dr_bl_mc->Fill(y2dr,weight);                                                
          h_ptratio_bl_mc->Fill(ptratio,weight);                                          
          h_y1y_bl_mc->Fill(y1y,weight);                                                  
          h_y2y_bl_mc->Fill(y2y,weight);                                                  
          h_jety_bl_mc->Fill(jety,weight);                                                
          h_yydy_bl_mc->Fill(yydy,weight);                                                
                                                                                
          h_yyE_bl_mc->Fill(yyE,weight);                                                  
          h_y1E_bl_mc->Fill(y1E,weight);                                                  
          h_y2E_bl_mc->Fill(y2E,weight);                                                  
          h_jetE_bl_mc->Fill(jetE,weight);                                                
                                                                                
          h_yypt_bl_mc->Fill(yypt,weight);                                                
          h_y1pt_bl_mc->Fill(y1pt,weight);                                                
          h_y2pt_bl_mc->Fill(y2pt,weight);                                                
                                                                                
          h_yyy_bl_mc->Fill(yyy,weight);                                                  
          h_costhet_bl_mc->Fill(costhet,weight);       
        } 
      }
    }
    cout<<outname<<" mc bg written"<<endl; 
    cout<<""<<endl; 

    out->Write(); 
    out->Close(); 
  }
}
