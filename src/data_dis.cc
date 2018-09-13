#include <iostream> 
#include <vector> 
#include <stdlib.h> 
#include <utility> 

#include <boost/optional.hpp> 
#include <TFile.h> 
#include <TChain.h> 
#include <TH1.h> 
#include <TLorentzVector.h>

//#include "Higgs2diphoton.hh" 

using namespace std; 
//Higgs2diphoton Hdecay; 
bool sort_pt (TLorentzVector i, TLorentzVector j){return (i.Pt()>j.Pt());}

int main(){
  //======================================
  //Open Datafile
  TChain chain("mini"); 
  
  chain.Add("$TMPDIR/data15.root");
  chain.Add("$TMPDIR/data16_DS1.root"); 
  chain.Add("$TMPDIR/data16_DS2.root"); 
  chain.Add("$TMPDIR/data16_DS3.root"); 
  chain.Add("$TMPDIR/data16_DS4.root"); 
  //======================================
  //Set Variables 
  Float_t s, yydr, y1dr, y2dr, ptratio, y1y, y2y;
  Float_t jety,yydy,y1E, y2E, yyE, jetE;
  Float_t y1pt, y2pt, yypt, yyy, costhet; 
  //=====================================
  //Set Trees
  constexpr size_t max = 10; 
  Int_t photon_n, jet_n; 
  Float_t photon_m[max], photon_eta[max], photon_phi[max], photon_pt[max];
  Float_t jet_m[max], jet_eta[max], jet_phi[max], jet_pt[max];

  chain.SetBranchAddress("photon_n", &photon_n);
  chain.SetBranchAddress("photon_m", photon_m);
  chain.SetBranchAddress("photon_eta", photon_eta);
  chain.SetBranchAddress("photon_phi", photon_phi);
  chain.SetBranchAddress("photon_pt", photon_pt);

  chain.SetBranchAddress("jet_n", &jet_n);
  chain.SetBranchAddress("jet_m", jet_m);
  chain.SetBranchAddress("jet_eta", jet_eta);
  chain.SetBranchAddress("jet_phi", jet_phi);
  chain.SetBranchAddress("jet_pt", jet_pt);
  
  //====================================
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

  //====================================
  for (int i=0; i<9; ++i){
    //Make each file
    TString outname = "real_dis_" + num[i] +".root";
    TFile* out = TFile::Open(outname, "RECREATE"); 
    cout<<outname<<", writing....."<<endl; 
    //======================================
    //Each histogram
    int nbins = 100.; 
    if (i==6 or i==5){
      nbins = 40;
    } 
    if (i==7 or i==8){
      nbins = 20; 
    }

    //Signal Region
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
    TH1D* h_s_bl = new TH1D("Left__s_" + num[i], "#sqrt{s}", nbins,0.,2500.); 
    TH1D* h_yydr_bl = new TH1D("Left__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8); 
    TH1D* h_y1dr_bl = new TH1D("Left__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7); 
    TH1D* h_y2dr_bl = new TH1D("Left__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7); 
    TH1D* h_ptratio_bl = new TH1D("Left__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20); 
    TH1D* h_y1y_bl = new TH1D("Left__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5); 
    TH1D* h_y2y_bl = new TH1D("Left__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5); 
    TH1D* h_jety_bl = new TH1D("Left__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5); 
    TH1D* h_yydy_bl = new TH1D("Left__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6); 
    TH1D* h_y1E_bl = new TH1D("Left__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200); 
    TH1D* h_y2E_bl = new TH1D("Left__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_bl = new TH1D("Left__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750); 
    TH1D* h_jetE_bl = new TH1D("Left__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500); 
    TH1D* h_y1pt_bl = new TH1D("Left__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600); 
    TH1D* h_y2pt_bl = new TH1D("Left__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_bl = new TH1D("Left__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700); 
    
    TH1D* h_yyy_bl = new TH1D("Left__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3); 
    TH1D* h_costhet_bl = new TH1D("Left__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);  

    TH1D* h_s_br = new TH1D("Right__s_" + num[i], "#sqrt{s}", nbins,0.,2500.); 
    TH1D* h_yydr_br = new TH1D("Right__yydr_" + num[i], "Diphoton #DeltaR",nbins, 0, 8); 
    TH1D* h_y1dr_br = new TH1D("Right__y1dr_"+ num[i], "#gamma_{1} #DeltaR",nbins,1.5, 7); 
    TH1D* h_y2dr_br = new TH1D("Right__y2dr_" + num[i], "#gamma_{2} #DeltaR", nbins, 0, 7); 
    TH1D* h_ptratio_br = new TH1D("Right__ptratio_"+num[i], "p_{T}^{#gamma_{1}} / p_{T}^{#gamma_{2}}", nbins, 1, 20); 
    TH1D* h_y1y_br = new TH1D("Right__y1y_"+num[i], "#gamma_{1} Rapidity", nbins, 0, 2.5); 
    TH1D* h_y2y_br = new TH1D("Right__y2y_"+num[i],"#gamma_{2} Rapidity", nbins, 0, 2.5); 
    TH1D* h_jety_br = new TH1D("Right__jety_"+num[i],"Leading Jet Rapidity", nbins,0, 4.5); 
    TH1D* h_yydy_br = new TH1D("Right__yydy_"+num[i],"Diphoton #DeltaY", nbins, 0, 2.6); 
    TH1D* h_y1E_br = new TH1D("Right__y1E_"+num[i], "#gamma_{1} Energy", nbins, 0, 1200); 
    TH1D* h_y2E_br = new TH1D("Right__y2E_"+num[i], "#gamma_{2} Energy", nbins, 0, 600);
    TH1D* h_yyE_br = new TH1D("Right__yyE_"+num[i], "Diphoton Energy", nbins, 0, 1750); 
    TH1D* h_jetE_br = new TH1D("Right__jetE_"+num[i], "Leading Jet Energy", nbins, 0, 2500); 
    TH1D* h_y1pt_br = new TH1D("Right__y1pt_"+num[i], "#gamma_{1} p_{T}", nbins, 0, 600); 
    TH1D* h_y2pt_br = new TH1D("Right__y2pt_"+num[i], "#gamma_{2} p_{T}", nbins, 0, 250);
    TH1D* h_yypt_br = new TH1D("Right__yypt_"+num[i], "Diphoton p_{T}", nbins, 0, 700); 
    
    TH1D* h_yyy_br = new TH1D("Right__yyy_"+num[i], "Diphoton Rapidity", nbins, 0, 3); 
    TH1D* h_costhet_br = new TH1D("Right__costhet_"+num[i], "|cos #theta*|", nbins,0, 1.2);  
    //====================================
    int n_sig = 0; 
    int n_bg_r = 0; 
    int n_bg_l = 0; 
    //=====================================
    //Go through each event
    const Long64_t entries = chain.GetEntries(); 
    for (long k=0; k<entries; ++k){
      chain.GetEntry(k); 
      //Assign Particles 
      TLorentzVector yy, y1, y2, jet, photons, jets; 
      vector<TLorentzVector> t_y, t_jet; 

      for (int j=0; j<photon_n; ++j){
        photons.SetPtEtaPhiM(photon_pt[j], photon_eta[j], photon_phi[j], photon_m[j]); 
        t_y.emplace_back(photons); 
      }
      if (jet_n!=0){
        for (int j=0; j<jet_n; ++j){
          jets.SetPtEtaPhiM(jet_pt[j], jet_eta[j], jet_phi[j], jet_m[j]); 
          t_jet.emplace_back(jets); 
        }
      }
      else{
        jets.SetPtEtaPhiM(0,0,0,0); 
        t_jet.emplace_back(jets);  
      }

      //Sort by pT
      sort(t_jet.begin(), t_jet.end(), sort_pt); 
      sort(t_y.begin(), t_y.end(), sort_pt); 
      
      jet = t_jet[0]; 
      y1 = t_y[0]; 
      y2 = t_y[1]; 
      yy = y1+y2; 

      //Cuts
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

      //Diphoton Pt cuts                                                        
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
        //Calcuate each variable
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

        //Make sig and sideband cut
        bool sig = ((yy.M()>121.)&&(yy.M()<129.)); 
        bool left = ((yy.M()>105.)&&(yy.M()<121.)); 
        bool right = ((yy.M()>129.)&&(yy.M()<160.)); 

        if (sig){
          //Fill signal hist
          h_s_s->Fill(s); 
          h_yydr_s->Fill(yydr); 
          h_y1dr_s->Fill(y1dr); 
          h_y2dr_s->Fill(y2dr); 
          h_ptratio_s->Fill(ptratio); 
          h_y1y_s->Fill(y1y); 
          h_y2y_s->Fill(y2y); 
          h_jety_s->Fill(jety); 
          h_yydy_s->Fill(yydy); 

          h_yyE_s->Fill(yyE); 
          h_y1E_s->Fill(y1E); 
          h_y2E_s->Fill(y2E); 
          h_jetE_s->Fill(jetE);

          h_yypt_s->Fill(yypt);  
          h_y1pt_s->Fill(y1pt);  
          h_y2pt_s->Fill(y2pt); 
          
          h_yyy_s->Fill(yyy); 
          h_costhet_s->Fill(costhet); 
        
          n_sig+=1; 
        }

        if (left){
          //Fill sideband hist
          h_s_bl->Fill(s); 
          h_yydr_bl->Fill(yydr); 
          h_y1dr_bl->Fill(y1dr); 
          h_y2dr_bl->Fill(y2dr); 
          h_ptratio_bl->Fill(ptratio); 
          h_y1y_bl->Fill(y1y); 
          h_y2y_bl->Fill(y2y); 
          h_jety_bl->Fill(jety); 
          h_yydy_bl->Fill(yydy); 

          h_yyE_bl->Fill(yyE); 
          h_y1E_bl->Fill(y1E); 
          h_y2E_bl->Fill(y2E); 
          h_jetE_bl->Fill(jetE);

          h_yypt_bl->Fill(yypt);  
          h_y1pt_bl->Fill(y1pt);  
          h_y2pt_bl->Fill(y2pt); 
          
          h_yyy_bl->Fill(yyy); 
          h_costhet_bl->Fill(costhet); 
        
          n_bg_l+=1; 
        }

        if (right){
          //Fill sideband hist
          h_s_br->Fill(s); 
          h_yydr_br->Fill(yydr); 
          h_y1dr_br->Fill(y1dr); 
          h_y2dr_br->Fill(y2dr); 
          h_ptratio_br->Fill(ptratio); 
          h_y1y_br->Fill(y1y); 
          h_y2y_br->Fill(y2y); 
          h_jety_br->Fill(jety); 
          h_yydy_br->Fill(yydy); 

          h_yyE_br->Fill(yyE); 
          h_y1E_br->Fill(y1E); 
          h_y2E_br->Fill(y2E); 
          h_jetE_br->Fill(jetE);

          h_yypt_br->Fill(yypt);  
          h_y1pt_br->Fill(y1pt);  
          h_y2pt_br->Fill(y2pt); 
          
          h_yyy_br->Fill(yyy); 
          h_costhet_br->Fill(costhet); 
        
          n_bg_r+=1; 
        }   
      }
    }
    
    cout<<"Wrote "<<out->GetName()<<endl; 
    cout<<"Signal Count "<<n_sig<<endl; 
    cout<<"Right Bkground Count "<<n_bg_r<<endl;
    cout<<"Left Bkground Count "<<n_bg_l<<endl;
    cout<<""<<endl; 

    out->Write(); 
    out->Close(); 
  }
} 
