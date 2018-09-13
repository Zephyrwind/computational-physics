/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 5.2 - Estatistica
   Novembro de 2016 
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <cmath>

using namespace std;

void ising_est (int Lx, int Ly, int step, int sweep, double Ti,double Tf,double dT){
 
 int rede[Lx*Ly];	// rede quadrada
 double J=1;	// interação de troca
 
 char nome[100];
 sprintf(nome,"TME(L%d).txt",Lx);
 
 ofstream ok;
 ok.open(nome,fstream::app);
 
 for(int k=0;k<Lx*Ly;k++) rede[k]=1;	// sistema começa com spins todos '1'
 
 for(double T=Ti;T<=Tf;T=T+dT){	// variar temperatura
  
  int M=0;	// magnetização sistema
  double E=0;	// energia sistema
  double Ms=0;	// magnetização a cada 3 sweep
  double Es=0;	// energia a cada 3 sweep
  int counter=0;	// contador que itera a cada 3 sweep
 
  /* Energia inicial do sistema para uma dada temperatura, com condições de fronteira periodicas */
  for(int x=0;x<Lx;x++){
   for(int y=0;y<Ly;y++){
    
    M=M+rede[x+y*Lx];
    
    if(x!=Lx-1) E=rede[x+y*Ly]*rede[x+1+y*Ly]+E;	// direita
    else E=rede[x+y*Ly]*rede[y*Ly]+E;
  
    if(x!=0) E=rede[x+y*Ly]*rede[x-1+y*Lx]+E;	// esquerda
    else E=rede[x+y*Ly]*rede[Lx-1+y*Lx]+E;
  
    if(y!=Ly-1) E=rede[x+y*Ly]*rede[x+(y+1)*Lx]+E;	// cima
    else E=rede[x+y*Ly]*rede[x]+E;
  
    if(y!=0) E=rede[x+y*Ly]*rede[x+(y-1)*Lx]+E;	// baixo
    else E=rede[x+y*Ly]*rede[x+(Ly-1)*Lx]+E;
   }
  }
 
  E=-(J*E)/2.0; // Divide-se por dois pois conta-se cada par 2 vezes
 
  double kb=1.0;
  
  for(int i=1;i<=step;i++){	// Monte Carlo step
    
   double dE=0;	// variação energia
   int sx=Lx*drand48();	// posição x spin
   int sy=Ly*drand48();	// posição i spin
  
   /* Condições de Fronteira periódicas, ver primeiros vizinhos */
   if(sx!=Lx-1) dE=rede[sx+1+sy*Ly]+dE;	// direita
   else dE=rede[0+sy*Ly]+dE;
  
   if(sx!=0) dE=rede[sx-1+sy*Lx]+dE;	// esquerda
   else dE=rede[Lx-1+sy*Lx]+dE;
  
   if(sy!=Ly-1) dE=rede[sx+(sy+1)*Lx]+dE;	// cima
   else dE=rede[sx+0*Lx]+dE;
  
   if(sy!=0) dE=rede[sx+(sy-1)*Lx]+dE;	// baixo
   else dE=rede[sx+(Ly-1)*Lx]+dE;

   dE=2.0*J*rede[sx+sy*Lx]*dE;		// variação de energia
   
   if(dE<=0){	// variação negativa
    rede[sx+sy*Lx]=-rede[sx+sy*Lx];	// inverte spin
    E=E+dE;	// energia actualizada
    if(rede[sx+sy*Lx]==-1) M=M-2; // 1 para -1, M diminui 
    if(rede[sx+sy*Lx]==1) M=M+2;	// -1 para 1, M aumenta
   }
  
   else {	// variação positiva
     
    double pr=exp(-dE/(kb*T));	// probabilidade de inverter
    double w=drand48();  // numero aleatorio
    
    if(w<pr){	// comparar com numero aleatorio, maior inverte
     rede[sx+sy*Lx]=-rede[sx+sy*Lx];
     E=E+dE;
     if(rede[sx+sy*Lx]==-1) M=M-2;
     if(rede[sx+sy*Lx]==1) M=M+2;
    }  
   }
   
   if(i%sweep==0){	// conta energia e magnetização a cada 3 sweep
    Es=E+Es;
    Ms=M+Ms;
    counter=counter+1;
   }
  }
  
  Es=Es/(double)counter;	// energia media por 3 sweep 
  Ms=Ms/(double)counter;	// magnetização média por 
  
  cout<<"Rede= "<<Lx<<" x "<<Ly<<" , T= "<<T<<" , Iterações= "<<step<<" , Sweep= "<<sweep<<" , M= "<<Ms<<" , E= "<<Es<<endl;
  
  ok<<T<<'\t'<<Ms<<'\t'<<Es<<endl;
 }
   
 ok.close();
 
 return;
}

int main(){

 int step=1e6;	// número de steps de Monte Carlo
 double Ti=1.0;	// temperatura inicial
 double Tf=5.0;	// temperatura final
 double dT=0.01;	// incremento de temperatura
 
 for(int i=10;i<=pow(10,2);i=i*3){	// variar a tamanho
 
  int media=3*i*i;	// conta energia e magnetização a cada 3 sweeps de Monte Carlo
  ising_est(i,i,step,media,Ti,Tf,dT);
 }
 
 return 0;
}
