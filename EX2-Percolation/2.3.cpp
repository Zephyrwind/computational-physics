/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 2.3 - Estatística
   Outubro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <fstream>
#include "latticeview.h"
#include <stdlib.h>

using namespace std;

#define ImageWidth 1000  //image width
#define ImageHeight 1000 //image height

void rede_est (double p,int Lx,int Ly){
 
 int rede[Lx*Ly];	
 double w;			
 int ite=0;
 int conta=0;
 int config=1000;
 int curto[config]={0};
 int passos[config];
 
 for(int k=0;k<config;k++){
  for(int i=0;i<Lx;i++){
   for(int j=0;j<Ly;j++){
    w=drand48();
    if(w>1-p) rede[i+j*Lx]=1;
   else rede[i+j*Lx]=0;
   }
  }
 
  for(int i=0;i<Lx;i++){
   if(rede[i]==1) {
    rede[i]=2;
    conta=conta+1;
   }
  }
  
  while(conta != 0){
   ite=ite+1;
   for(int i=0;i<Lx;i++){
    for(int j=0;j<Ly;j++){
     if(rede[i+j*Lx]==1){
      if(rede[i+(j-1)*Lx]==2 && j!=0) rede[i+j*Lx]=3;
      if(rede[i+j*Lx-1]==2 && i !=0) rede[i+j*Lx]=3;
      if(rede[i+j*Lx+1]==2 && i !=Lx-1) rede[i+j*Lx]=3;
      if(rede[i+(j+1)*Lx]==2 && j!=Ly-1) rede[i+j*Lx]=3;
     }
    }
   }
  
   for(int i=0;i<Lx;i++){
    for(int j=0;j<Ly;j++){
     if(rede[i+j*Lx]==2){
      rede[i+j*Lx]=4;
      conta=conta-1;
     }
     if(rede[i+j*Lx]==3){
      rede[i+j*Lx]=2;
      conta=conta+1;
     }
    }
    if(rede[i+(Ly-1)*Lx]==4 && curto[k]==0) curto[k]=ite;
   } 
  }
  passos[k]=ite;
  ite=0;
  conta=0;
  srand48(k); 
 }
 
 int passosm=0;
 int curtom=0;
 double frac=0;
 
 for(int k=0;k<config;k++){
  if(curto[k]!=0){
   curtom=curtom+curto[k];
   passosm=passosm+passos[k];
   frac=frac+1;
  }
 }
 
 curtom=(double)curtom/frac;
 passosm=(double)passosm/frac;
 frac=frac/(double)config;
 
 ofstream ok;
 ok.open("data.txt",fstream::app);

 cout<< "Fracção de agregado percolativo = "<< frac <<endl;

 if(frac!=0){
  cout<< "Caminho Curto médio = "<< curtom<< '\n'<< "Tempo de queima médio= "<< passosm <<endl;
  ok<< p<<'\t'<<frac<< '\t'<< curtom<< '\t'<< passosm <<endl;
 }
 
 return;
} 

int main(){

 double pr=0.9;
 int L=10;
 
 ofstream ok;
 ok.open("data.txt");
 
 for(int i;i<16;i++){
  rede_est(pr-0.05*i,L,L);
 }
 
 ok.close();
 
 return 0;
}
