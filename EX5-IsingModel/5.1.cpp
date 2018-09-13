/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 5.1 - Simulaçoes de Monte Carlo. Modelo de Ising
   Novembro de 2016
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "latticeview.h"
#include <stdlib.h>
#include <cmath>

using namespace std;

#define ImageWidth 1000  //image width
#define ImageHeight 1000 //image height

void ising (int Lx, int Ly, int step, double T){
 
 int rede[Lx*Ly];	// sistema
 double J=1.0;	// interação de troca
 double E=0;	// energia
 double M=Lx*Ly; // magnetização
 
 for(int k=0;k<Lx*Ly;k++) rede[k]=1;	// sistema começa com spins todos '1'
 
 /* Energia inicial do sistema, correndo todos os pares vizinhos com condições de fronteira periodicas */
 for(int x=0;x<Lx;x++){
  for(int y=0;y<Ly;y++){
    
   if(x!=Lx-1) E=rede[x+y*Ly]*rede[x+1+y*Ly]+E;	// direita
   else E=rede[x+y*Ly]*rede[0+y*Ly]+E;
  
   if(x!=0) E=rede[x+y*Ly]*rede[x-1+y*Lx]+E;	// esquerda
   else E=rede[x+y*Ly]*rede[Lx-1+y*Lx]+E;
  
   if(y!=Ly-1) E=rede[x+y*Ly]*rede[x+(y+1)*Lx]+E;	// cima
   else E=rede[x+y*Ly]*rede[x+0*Lx]+E;
  
   if(y!=0) E=rede[x+y*Ly]*rede[x+(y-1)*Lx]+E;	// baixo
   else E=rede[x+y*Ly]*rede[x+(Ly-1)*Lx]+E;
  }
 }
 
 E=-(J*E)/2.0;	// Divide-se por dois pois conta-se cada par 2 vezes
 
 cout<<"Energial Inicial= "<<E<<endl;
 
 double dE;
 double kb=1.0;	// constante de boltzman
 
 for(int i=1;i<=step;i++){	// Monte Carlo step
 
  dE=0;
  int x=Lx*drand48();	// posição x spin
  int y=Ly*drand48();	// posição i spin
  
  /* Condições de Fronteira periódicas */
  if(x!=Lx-1) dE=rede[x+1+y*Ly]+dE;	// direita
  else dE=rede[y*Ly]+dE;
  
  if(x!=0) dE=rede[x-1+y*Lx]+dE;	// esquerda
  else dE=rede[Lx-1+y*Lx]+dE;
  
  if(y!=Ly-1) dE=rede[x+(y+1)*Lx]+dE;	// cima
  else dE=rede[x]+dE;
  
  if(y!=0) dE=rede[x+(y-1)*Lx]+dE;	// baixo
  else dE=rede[x+(Ly-1)*Lx]+dE;

  dE=2.0*J*rede[x+y*Lx]*dE;		// variação de energia
   
  if(dE<=0){	// variação negativa
   rede[x+y*Lx]=-rede[x+y*Lx];	// inverte spin
   E=E+dE;	// energia actualizada
   if(rede[x+y*Lx]==-1) M=M-2; // 1 para -1, M diminui 
   if(rede[x+y*Lx]==1) M=M+2;	// -1 para 1, M aumenta
  }
  
  if(dE>0){	// variação positiva
     
   double pr=exp(-dE/(kb*T));	// probabilidade de inverter
   double w=drand48();  // numero aleatorio
   
   if(w<pr){	// comparar com numero aleatorio, maior inverte (analogo a dE<=0)
    rede[x+y*Lx]=-rede[x+y*Lx];
    E=E+dE;
    if(rede[x+y*Lx]==-1) M=M-2;
    if(rede[x+y*Lx]==1) M=M+2;
   }  
  }
 }
 
 cout<<"Rede= "<<Lx<<" x "<<Ly<<" , T= "<<T<<" , Step= "<<step<<" , E= "<<E<<" , M= "<<M<<endl;
 
 char nome[100];
 sprintf(nome,"ising eq T=%0.1f.ppm",T);
 
 Print_lattice (rede, Lx, Ly, ImageWidth, ImageHeight, nome);
 
 return;
}

int main(){
 
 int Lx=200;	// tamanho x do sistema
 int Ly=200;	// tamanho y do sistema
 int step=1e6;	// número de steps de Monte Carlo

 for(double i=1.0;i<=10.0;i=i+1.0){	// variar a temperatura de 1.0<T<10.0
  ising(Lx,Ly,step,i);
 }
 
 return 0;
}
