/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 3.1 - Dimensão fractal de agregado percolativo
   3.1.1 - Método do Ensemble
   Outubro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>

using namespace std;

/* Metodo do ensemble: isola agregado percolativo de tamanho L, em pc e calcula numero medio de sitios */
double ensemble (int L){
 
 int rede[L*L];
 double pc=0.592746;	
 double w;			
 int conta=0;
 int config=250;
 int sitios[config]={0};

 for(int k=0;k<config;k++){	// Geração de k agregados com diferentes seeds em pc
  for(int i=0;i<L;i++){
   for(int j=0;j<L;j++){
    w=drand48();
    if(w>1-pc) rede[i+j*L]=1;
   else rede[i+j*L]=0;
   }
  }
 
  /* Metodo queima de baixo para cima (ex. 2.2) */
  for(int i=0;i<L;i++){
   if(rede[i]==1) {
    rede[i]=2;
    conta=conta+1;
   }
  }
  
  while(conta != 0){
   for(int i=0;i<L;i++){
    for(int j=0;j<L;j++){
     if(rede[i+j*L]==1){
      if(rede[i+(j-1)*L]==2 && j!=0) rede[i+j*L]=3;
      if(rede[i+j*L-1]==2 && i !=0) rede[i+j*L]=3;
      if(rede[i+j*L+1]==2 && i !=L-1) rede[i+j*L]=3;
      if(rede[i+(j+1)*L]==2 && j!=L-1) rede[i+j*L]=3;
     }
    }
   }
   for(int i=0;i<L;i++){
    for(int j=0;j<L;j++){
     if(rede[i+j*L]==2){
      rede[i+j*L]=4;
      conta=conta-1;
     }
     if(rede[i+j*L]==3){
      rede[i+j*L]=2;
      conta=conta+1;
     }
    }
   } 
  }
  
  /* Metodo da queima de cima para baixo para isolar agregado */
  conta=0;
  for(int i=L-1;i>=0;i--){
   for(int j=L-1;j>=0;j--){
    if(rede[i+j*L]==1){
     rede[i+j*L]=0;
    }
    if(rede[i+j*L]==4){
     rede[i+j*L]=1;
     conta=conta+1;
    }
   }
  }
  sitios[k]=conta;
  conta=0;
  srand48(k);
 }

 /* Médio do numero de sitios dos k agregados */
 double sitiosm=0;
 for(int k=0;k<config;k++){
  sitiosm=sitiosm+sitios[k];
 }
 sitiosm=sitiosm/(double)config;
 
 cout<< "Rede "<< L<< " x "<< L<< " com número médio de sítios= "<< sitiosm<<endl;
 
 return sitiosm;
}

int main(){

 int L=2;
 double M;
 
 ofstream ok;
 ok.open("ensemble.txt");
 
 for(int i=1;i<=7;i++){	// L=2^n, n=1,2,...,7 (Lmax=2^7=128)
  M=ensemble(pow(L,i));
  ok<< log(pow(L,i))<< '\t'<< log(M)<<endl;
 }
 
 ok.close();
 
 return 0;
}
