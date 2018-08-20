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
                              
int main(){                                                               
  //===============================================                         
  TChain chain_s("t3"); 
  TChain chain_b("t3"); 

  chain_s.Add("$TMPDIR/H1.0j_GGFHT_B_6500_pt25.0_eta4.5_r100_100.root",0); 
  //chain_s.Add("/msu/data/t3work4/luisonig/H1jets_ggf/NTuplesFiles/H1.0j_GGFHT_B_6500_pt25.0_eta4.5_r100_100.root",0); 
  //chain_b.Add("$TMPDIR/born6.root",0); 
  chain_b.Add("$TMPDIR/born7.root",0); 
  chain_b.Add("$TMPDIR/born8.root",0); 
  chain_b.Add("$TMPDIR/born9.root",0); 
  //chain_b.Add("/msu/data/t3work4/gosam_diphoton_jet/born/born9.root",0); 
  cout<<"Read in files"<<endl; 
  
  //===============================================                            
  constexpr size_t max = 10;                                                    
  Float_t px_s[max], py_s[max], pz_s[max], E_s[max];                            
  Int_t nparticle_s, kf_s[max];                                                 
  Double_t weight_s;                                                            
                                                                                
  Float_t px_b[max], py_b[max], pz_b[max], E_b[max];                            
  Int_t nparticle_b, kf_b[max];                                                 
  Double_t weight_b;                                                            
  //===============================================
  chain_s.SetBranchAddress("nparticle",&nparticle_s);                          
  chain_s.SetBranchAddress("kf",kf_s);                                         
  chain_s.SetBranchAddress("px",px_s);                                         
  chain_s.SetBranchAddress("py",py_s);                                         
  chain_s.SetBranchAddress("pz",pz_s);                                         
  chain_s.SetBranchAddress("E",E_s);                                           
  chain_s.SetBranchAddress("weight2",&weight_s);                               
 
  chain_b.SetBranchAddress("nparticle",&nparticle_b);                          
  chain_b.SetBranchAddress("kf",kf_b);                                         
  chain_b.SetBranchAddress("px",px_b);                                         
  chain_b.SetBranchAddress("py",py_b);                                         
  chain_b.SetBranchAddress("pz",pz_b);                                         
  chain_b.SetBranchAddress("E",E_b);                                           
  chain_b.SetBranchAddress("weight2",&weight_b);                               
  //==============================================                              
  //ALL THE TREES                                                               
  Float_t s, yydr, y1dr, y2dr, ptratio, y1y, y2y,jety, yydy;                    
  Float_t y1E, y1pt, y2E, y2pt, yyE, yypt, jetE, jetpt, yyy, costhet;                         
  Float_t weights;                                                              
  //===============================================                             
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

  for (int i=0; i<9; ++i){
    TString outname = "mc_dis_" + num[i] + ".root"; 
    TFile* out = TFile::Open(outname, "RECREATE"); 
    cout<<"Writing "<<outname<<"....."<<endl; 

    //===============================================                             
    //Ouputs
    int nbins = 100.;
    if (i==6){
      nbins = 60; 
    }
    if (i==8 or i==7){
      nbins = 40;
    }    
    //Signal
    TH1D* h_s_s = new TH1D("Signal__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);    
    TH1D* h_yydr_s = new TH1D("Signal__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_s = new TH1D("Signal__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_s = new TH1D("Signal__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_s = new TH1D("Signal__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_s = new TH1D("Signal__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_s = new TH1D("Signal__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_s = new TH1D("Signal__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_s = new TH1D("Signal__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_s = new TH1D("Signal__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_s = new TH1D("Signal__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_s = new TH1D("Signal__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_s = new TH1D("Signal__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_s = new TH1D("Signal__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_s = new TH1D("Signal__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_s = new TH1D("Signal__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
                                                                                
    TH1D* h_yyy_s = new TH1D("Signal__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_s = new TH1D("Signal__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
                                                                                
    //Sideband                                                                  
    TH1D* h_s_b = new TH1D("Background__s_" + num[i], "#sqrt{s}", nbins,0.,2500.);
    TH1D* h_yydr_b = new TH1D("Background__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8);
    TH1D* h_y1dr_b = new TH1D("Background__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7);
    TH1D* h_y2dr_b = new TH1D("Background__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7);
    TH1D* h_ptratio_b = new TH1D("Background__ptratio_"+num[i], "p_{T}^{#gamma_{1}} /p_{T}^{#gamma_{2}}", nbins, 1, 20);
    TH1D* h_y1y_b = new TH1D("Background__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5);
    TH1D* h_y2y_b = new TH1D("Background__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5);
    TH1D* h_jety_b = new TH1D("Background__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5);
    TH1D* h_yydy_b = new TH1D("Background__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6);
    TH1D* h_y1E_b = new TH1D("Background__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200);
    TH1D* h_y2E_b = new TH1D("Background__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_b = new TH1D("Background__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750);
    TH1D* h_jetE_b = new TH1D("Background__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500);
    TH1D* h_y1pt_b = new TH1D("Background__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600);
    TH1D* h_y2pt_b = new TH1D("Background__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_b = new TH1D("Background__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700);
                                                                                
    TH1D* h_yyy_b = new TH1D("Background__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3);
    TH1D* h_costhet_b = new TH1D("Background__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);
                                                                
    //==============================================                              
    const Long64_t entries_s = chain_s.GetEntries();                             
    int n_sig = 0; 
    //=============================================== 
    //Signal                                                                      
    for (long j=0; j<entries_s; ++j){                                             
      chain_s.GetEntry(j);                                                       
      TLorentzVector yy, y1, y2, jet;                                
      vector<TLorentzVector> jets;                                                
      for (long i=0; i<nparticle_s; ++i){                                         
        if (kf_s[i]==25){                                                         
          yy.SetPxPyPzE(px_s[i],py_s[i],pz_s[i],E_s[i]);                       
        }                                                                         
        else{                                                                     
          jets.emplace_back(px_s[i],py_s[i],pz_s[i],E_s[i]);                      
        }                                                                         
      }                                                                           
                                                                                  
      //Decay yy                                                               
      pair<TLorentzVector, TLorentzVector> diphoton = Hdecay(yy);              
                                                                                  
      //Sort Photons                                                                            
      if (diphoton.first.Pt()>diphoton.second.Pt()){                              
        y1 = diphoton.first;                                                 
        y2 = diphoton.second;                                                
      }                                                                           
      else{                                                                       
        y1 = diphoton.second;                                                
        y2 = diphoton.first;                                                 
      }                                                                           
                                                                                  
      jet=jets[0]; 
      
      //Cuts
      //Mass Cut                                                                  
      bool select = ((yy.M()>121.)&&(yy.M()<129.));                         
      //Rapidity Cut                                                              
      select &= (abs(y2.Rapidity())<2.4);                                    
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
      select &= (y2.DeltaR(jet)>.4);   
      //Jet Cuts                            
      select &= (jet.Pt()>30);              
      select &= (jet.Rapidity()<4.4);       
     
  
        //Diy Pt cuts 
      if (i==0){select &= (yy.Pt()<50.);}
      if (i==1){select &= (yy.Pt()>50. && yy.Pt()<100.);}
      if (i==2){select &= (yy.Pt()>100. && yy.Pt()<150);}
      if (i==3){select &= (yy.Pt()>150. && yy.Pt()<200);}
      if (i==4){select &= (yy.Pt()>200. && yy.Pt()<250);}                       
      if (i==5){select &= (yy.Pt()>250. && yy.Pt()<300.);}                      
      if (i==6){select &= (yy.Pt()>300. && yy.Pt()<350);}                       
      if (i==7){select &= (yy.Pt()>350. && yy.Pt()<400);}                       
      if (i==8){select &= (yy.Pt()>400.);} 
      
      if (select){ 
        n_sig+=1; 

        s = (abs((yy+jet).M()));                                               
        yydr = (abs(y1.DeltaR(y2)));                                          
        y1dr = (abs(y1.DeltaR(jet)));                                        
        y2dr = (abs(y2.DeltaR(jet)));                                        
        ptratio = (abs(y1.Pt())/abs(y2.Pt()));                          
        y1y = (abs(y1.Rapidity()));                                          
        y2y = (abs(y2.Rapidity()));                                          
        jety = (abs(jet.Rapidity()));                                             
        yydy = (abs(y1.Rapidity()-y2.Rapidity()));                      
                                                                                  
        yyE = (abs(yy.E()));                                                   
        y1E = (abs(y1.E()));                                                 
        y2E = (abs(y2.E()));                                                 
        jetE = (abs(jet.E()));                                                    
                                                                                  
        yypt = (abs(yy.Pt()));                                                 
        y1pt = abs(y1.Pt());                                                 
        y2pt = abs(y2.Pt());                                                 
        jetpt = abs(jet.Pt());                                                    
        
        yyy = abs(yy.Rapidity()); 
        costhet = (sinh(abs(y1.PseudoRapidity()-y2.PseudoRapidity()))*2*y1.Pt()*y2.Pt())/(sqrt(1.+pow((yy.Pt()/yy.M()),2.))*pow((yy.M()),2.));
                                       

        h_s_s->Fill(s,weight_s);                                                       
        h_yydr_s->Fill(yydr,weight_s);                                                 
        h_y1dr_s->Fill(y1dr,weight_s);                                                 
        h_y2dr_s->Fill(y2dr,weight_s);                                                 
        h_ptratio_s->Fill(ptratio, weight_s);                                           
        h_y1y_s->Fill(y1y,weight_s);                                                   
        h_y2y_s->Fill(y2y,weight_s);                                                   
        h_jety_s->Fill(jety,weight_s);                                                 
        h_yydy_s->Fill(yydy,weight_s);                                                 
                                                                              
        h_yyE_s->Fill(yyE,weight_s);                                                   
        h_y1E_s->Fill(y1E,weight_s);                                                   
        h_y2E_s->Fill(y2E,weight_s);                                                   
        h_jetE_s->Fill(jetE,weight_s);                                                 
                                                                              
        h_yypt_s->Fill(yypt,weight_s);                                                 
        h_y1pt_s->Fill(y1pt,weight_s);                                                 
        h_y2pt_s->Fill(y2pt,weight_s);                                                 
                                                                              
        h_yyy_s->Fill(yyy,weight_s);                                                   
        h_costhet_s->Fill(costhet,weight_s);                                           
                                                                      
      }       
    }
    //Background 
    //=============================================
    const Long64_t entries_b = chain_b.GetEntries(); 
    int n_bg = 0; 
    //=============================================
    for (long k=0; k<entries_b; ++k){
      chain_b.GetEntry(k); 

      vector<TLorentzVector> photons;                                           
      TLorentzVector y1, y2, jet;                                               
      photons.clear();                                                          
                                                                                
      //Assign particles                                                           
      for (long j=0; j<nparticle_b; ++j){                                       
        //if photon                                                                
        if (kf_b[j]== 22){                                                      
          photons.emplace_back(px_b[j], py_b[j], pz_b[j], E_b[j]);              
        }                                                                       
        //if jet                                                                   
        else{                                                                   
          jet.SetPxPyPzE(px_b[j], py_b[j], pz_b[j], E_b[j]);                    
        }                                                                       
      }                                                                         
      //Setting photons                                                            
      //Sort by pt                                                                 
      if (photons[0].Pt()>photons[1].Pt()){                                     
        y1 = photons[0];                                                        
        y2 = photons[1];                                                        
      }                                                                         
      else{                                                                     
        y1 = photons[1];                                                        
        y2 = photons[0];                                                        
      }                                                                         
      TLorentzVector yy = y1 + y2;  
      
      //Cuts
      //Mass Cut                                                                  
      bool select = ((yy.M()>121.)&&(yy.M()<129.));                         
      //Rapidity Cut                                                              
      select &= (abs(y2.Rapidity())<2.4);                                    
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
      select &= (y2.DeltaR(jet)>.4);   
      //Jet Cuts                            
      select &= (jet.Pt()>30);              
      select &= (jet.Rapidity()<4.4);       
     
  
        //Diy Pt cuts 
      if (i==0){select &= (yy.Pt()<50.);}
      if (i==1){select &= (yy.Pt()>50. && yy.Pt()<100.);}
      if (i==2){select &= (yy.Pt()>100. && yy.Pt()<150);}
      if (i==3){select &= (yy.Pt()>150. && yy.Pt()<200);}
      if (i==4){select &= (yy.Pt()>200. && yy.Pt()<250);}                       
      if (i==5){select &= (yy.Pt()>250. && yy.Pt()<300.);}                      
      if (i==6){select &= (yy.Pt()>300. && yy.Pt()<350);}                       
      if (i==7){select &= (yy.Pt()>350. && yy.Pt()<400);}                       
      if (i==8){select &= (yy.Pt()>400.);} 
      
      if (select){ 
        n_bg+=1; 

        s = (abs((yy+jet).M()));                                               
        yydr = (abs(y1.DeltaR(y2)));                                          
        y1dr = (abs(y1.DeltaR(jet)));                                        
        y2dr = (abs(y2.DeltaR(jet)));                                        
        ptratio = (abs(y1.Pt())/abs(y2.Pt()));                          
        y1y = (abs(y1.Rapidity()));                                          
        y2y = (abs(y2.Rapidity()));                                          
        jety = (abs(jet.Rapidity()));                                             
        yydy = (abs(y1.Rapidity()-y2.Rapidity()));                      
                                                                                  
        yyE = (abs(yy.E()));                                                   
        y1E = (abs(y1.E()));                                                 
        y2E = (abs(y2.E()));                                                 
        jetE = (abs(jet.E()));                                                    
                                                                                  
        yypt = (abs(yy.Pt()));                                                 
        y1pt = abs(y1.Pt());                                                 
        y2pt = abs(y2.Pt());                                                 
        jetpt = abs(jet.Pt());                                                    
        
        yyy = abs(yy.Rapidity()); 
        costhet = (sinh(abs(y1.PseudoRapidity()-y2.PseudoRapidity()))*2*y1.Pt()*y2.Pt())/(sqrt(1.+pow((yy.Pt()/yy.M()),2.))*pow((yy.M()),2.));
                                       

        h_s_b->Fill(s,weight_b);                                                       
        h_yydr_b->Fill(yydr,weight_b);                                                 
        h_y1dr_b->Fill(y1dr,weight_b);                                                 
        h_y2dr_b->Fill(y2dr,weight_b);                                                 
        h_ptratio_b->Fill(ptratio, weight_b);                                           
        h_y1y_b->Fill(y1y,weight_b);                                                   
        h_y2y_b->Fill(y2y,weight_b);                                                   
        h_jety_b->Fill(jety,weight_b);                                                 
        h_yydy_b->Fill(yydy,weight_b);                                                 
                                                                              
        h_yyE_b->Fill(yyE,weight_b);                                                   
        h_y1E_b->Fill(y1E,weight_b);                                                   
        h_y2E_b->Fill(y2E,weight_b);                                                   
        h_jetE_b->Fill(jetE,weight_b);                                                 
                                                                              
        h_yypt_b->Fill(yypt,weight_b);                                                 
        h_y1pt_b->Fill(y1pt,weight_b);                                                 
        h_y2pt_b->Fill(y2pt,weight_b);                                                 
                                                                              
        h_yyy_b->Fill(yyy,weight_b);                                                   
        h_costhet_b->Fill(costhet,weight_b);                                           
      }
    } 
    cout<<outname<<" written"<<endl; 
    
    cout<<"signal events: "<<n_sig<<endl; 
    cout<<"bkground events: "<<n_bg<<endl; 
    cout<<""<<endl; 

    out->Write(); 
    out->Close(); 
  }
}
