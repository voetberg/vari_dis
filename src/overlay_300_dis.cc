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
  //==============================================
  
  //All MC files
  chain_mc_s.Add("/msu/data/t3work4/luisonig/H1jets_ggf/NTuplesFiles/H1.0j_GGFHT_B_6500_pt25.0_eta4.5_r100_100.root",0); 
  
  chain_mc_b.Add("/msu/data/t3work4/gosam_diphoton_jet/born/born7.root",0); 

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
  //========================================
  //Iterate through MC  
  //Signal
  long entries;   
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
    
    //Diphoton Pt
    select &= (yy.Pt()>250. && yy.Pt()<300);
  
    if (select){ 
      //Printing out a few 
      TRandom3 *r = new TRandom3(std::chrono::system_clock::now().time_since_epoch().count()); 
      double ran = r->Rndm(); 
      const bool split = (ran < .00005); 
      if (split){
        cout<<"Sig Photon 1: "<<endl; 
        y1.Print(); 
      
        cout<<"Sig Photon 2: "<<endl;
        y2.Print(); 

        cout<<"Sig Jet: "<<endl;
        jet.Print();
        cout<<" "<<endl;
      }
    }
  }
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
    select &= (yy.Pt()>250. && yy.Pt()<300);
  
    if (select){
      //A few 4 vectors   
      TRandom3 *r = new TRandom3(std::chrono::system_clock::now().time_since_epoch().count()); 
      double ran = r->Rndm(); 
      const bool split = (ran < .0005); 
      if (split){
        

        cout<<"Bg Photon 1: "<<endl; 
        y1.Print(); 
        cout<<"Bg Photon 2: "<<endl;
        y2.Print(); 
        cout<<"Bg Jet: "<<endl;
        jet.Print();
        cout<<" "<<endl;   
      }
    }
  }
}
