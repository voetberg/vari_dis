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
  TChain chain_mc("t3"); 
  TChain chain_data("mini"); 
  //==============================================
  
  //All MC files
  chain_mc.Add("$TMPDIR/H1.0j_GGFHT_B_6500_pt25.0_eta4.5_r100_100.root",0); 
  chain_mc.Add("$TMPDIR/H1.0j_GGFHT_B_6500_pt25.0_eta4.5_r100_101.root",0); 
  
  chain_mc.Add("$TMPDIR/born7.root",0); 
  chain_mc.Add("$TMPDIR/born6.root",0); 
  chain_mc.Add("$TMPDIR/born8.root",0); 

  //All Data files
  chain_data.Add("$TMPDIR/data15.root",0); 
  chain_data.Add("$TMPDIR/data16_DS1.root",0); 
  chain_data.Add("$TMPDIR/data16_DS2.root",0); 
  chain_data.Add("$TMPDIR/data16_DS3.root",0); 
  //==============================================
  Float_t ptratio; 
  //==============================================
  //Trees
  constexpr size_t max = 10;                                                    
  
  //MC 
  Float_t px[max], py[max], pz[max], E[max];                            
  Int_t nparticle, kf[max];                                                 
  Double_t weight; 
  
  chain_mc.SetBranchAddress("nparticle",&nparticle);
  chain_mc.SetBranchAddress("kf",kf);
  chain_mc.SetBranchAddress("px",px);
  chain_mc.SetBranchAddress("py",py);
  chain_mc.SetBranchAddress("pz",pz);
  chain_mc.SetBranchAddress("E",E);                                            
  chain_mc.SetBranchAddress("weight2",&weight); 
  
  //Data
  Int_t photon_n,jet_n;                                                        
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
  //Make a file 
  TString outname = "pt_ratio_dis.root"; 
  TFile* out = TFile::Open(outname, "RECREATE"); 
  
  int nbins = 100; 
  
  //MC
  TH1D* h_ptratio_s_mc[9]={
     new TH1D("Signal__mc__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__mc__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__mc__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__mc__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__mc__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__mc__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
     new TH1D("Signal__mc__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
     new TH1D("Signal__mc__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
     new TH1D("Signal__mc__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20)
  }; 
  TH1D* h_ptratio_bl_mc[9] = {
    new TH1D("Left__mc__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__mc__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__mc__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__mc__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__mc__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__mc__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Left__mc__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Left__mc__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
    new TH1D("Left__mc__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20)
  };
  TH1D* h_ptratio_br_mc[9] = {
    new TH1D("Right__mc__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__mc__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__mc__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__mc__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__mc__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__mc__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Right__mc__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Right__mc__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
    new TH1D("Right__mc__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20)
  }; 
  TH1D* h_ptratio_bg_mc[9] = {
    new TH1D("Bckground__mc__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__mc__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__mc__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__mc__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__mc__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__mc__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Bckground__mc__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Bckground__mc__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
    new TH1D("Bckground__mc__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20), 
  };

  //Data   
  TH1D* h_ptratio_s_data[9]={
     new TH1D("Signal__data__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__data__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__data__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__data__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__data__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
     new TH1D("Signal__data__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
     new TH1D("Signal__data__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
     new TH1D("Signal__data__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
     new TH1D("Signal__data__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20)
  };
  TH1D* h_ptratio_bl_data[9] = {
    new TH1D("Left__data__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__data__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__data__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__data__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__data__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Left__data__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Left__data__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Left__data__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
    new TH1D("Left__data__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20)
  };
  TH1D* h_ptratio_br_data[9] = {
    new TH1D("Right__data__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__data__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__data__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__data__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__data__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Right__data__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Right__data__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Right__data__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
    new TH1D("Right__data__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20)
  }; 
  TH1D* h_ptratio_bg_data[9] = {
    new TH1D("Bckground__data__ptratio_50","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__data__ptratio_100","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__data__ptratio_150","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__data__ptratio_200","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__data__ptratio_250","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 2, 20),
    new TH1D("Bckground__data__ptratio_300","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Bckground__data__ptratio_350","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-50, 2, 20),
    new TH1D("Bckground__data__ptratio_400","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20),
    new TH1D("Bckground__data__ptratio_400p","p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins-80, 2, 20) 
  };


  //============================================
  //Iteraion over the list 
  for (int i=0; i<9; ++i){
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
        ptratio = abs(y1.Pt())/abs(y2.Pt());    

        //Cuts for signal and sideband 
        bool sig = ((yy.M()>121.) && (yy.M()<129.)); 
        bool left = ((yy.M()>105.)&&(yy.M()<121.));
        bool right = ((yy.M()>129.)&&(yy.M()<160.)); 
        bool bg = right + left;         
        
        if (sig){h_ptratio_s_data[i]->Fill(ptratio);}
        if (bg){h_ptratio_bg_data[i]->Fill(ptratio);}
        if (right){h_ptratio_br_data[i]->Fill(ptratio);}
        if (left){h_ptratio_bl_data[i]->Fill(ptratio);} 
      }
    }
    cout<<outname<<" data written"<<endl; 
    cout<<""<<endl; 

    //========================================
    //Iterate through MC   
    entries = chain_mc.GetEntries(); 
    for (long j=0; j<entries; ++j){
      
      chain_mc.GetEntry(j); 
      TLorentzVector yy, y1, y2, jet; 
      vector <TLorentzVector> photons; 
      bool higgs_event = false; 

      for (int i=0; i<nparticle; ++i){
        if (kf[i]==25){
          higgs_event = true; 
          yy.SetPxPyPzE(px[i], py[i], pz[i],E[i]); 
        }
        if (kf[i]==22){
          higgs_event = false; 
          photons.emplace_back(px[i], py[i], pz[i], E[i]); 
        }
        else{
          jet.SetPxPyPzE(px[i], py[i], pz[i],E[i]); 
        }
      }
      if (higgs_event==false){
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
      }
      if (higgs_event==true){
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
        ptratio = abs(y1.Pt())/abs(y2.Pt());    
        //Cuts for signal and sideband 
        bool sig = higgs_event; 
        bool left = ((yy.M()>105.)&&(yy.M()<121.)); 
        bool right = ((yy.M()>129.)&&(yy.M()<160.)); 
        bool bg = right + left;         
        
        if (sig){h_ptratio_s_mc[i]->Fill(ptratio,weight);}
        if (bg){h_ptratio_bg_mc[i]->Fill(ptratio,weight);}
        if (right){h_ptratio_br_mc[i]->Fill(ptratio,weight);}
        if (left){h_ptratio_bl_mc[i]->Fill(ptratio,weight);} 
      }
    }    
  }
  out->Write(); 
  out->Close(); 
}
