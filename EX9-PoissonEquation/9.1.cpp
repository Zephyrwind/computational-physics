/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 9.1 - Resolução da Equação de Poisson
   Dezembro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(){
 
 int L=100;
 double delta=1e-5;
 double rho1[L][L],rho2[L][L],rho3[L][L];
 double u1[L][L],u2[L][L],u3[L][L];
 
 /* Condiçoes Iniciais */
 for(int j=0;j<L;j++){
  for(int l=0;l<L;l++){
  
   /* Caso 3 - N cargas */  
   if((j!=0 && j%20==0) || (l!=0 && l%20==0)) rho3[j][l]=1;
   else rho3[j][l]=0;
   
   /* Inicializar tudo com densidade carga nula */
   rho1[j][l]=0;
   rho2[j][l]=0;
   
   /* Inicializar potencial a zero */
   u1[j][l]=0;
   u2[j][l]=0;
   u3[j][l]=0;
  }
 }
 
 /* Caso 1 - Carga pontual no centro */
 rho1[int(L/2)][int(L/2)]=1;
 
 /* Caso 2 - 2 Cargas à mesma distância do centro do sistema */
 rho2[int(L/3+6)][int(L/3+6)]=1;
 rho2[int(2*L/3-6)][int(2*L/3-6)]=1;
 
 int t=1;	// iteração
 int tmax=1e3;	// tempo total de iteração
 
 while (t<=tmax){
 
  /* Método de Gauss-Seidel */
  for(int j=1;j<L-1;j++){
   for(int l=1;l<L-1;l++){
    
    /* Caso 1*/
    u1[j][l]=0.25*(u1[j+1][l]+u1[j-1][l]+u1[j][l+1]+u1[j][l-1])-0.25*pow(delta,2)*rho1[j][l];
    
    /* Caso 2*/
    u2[j][l]=0.25*(u2[j+1][l]+u2[j-1][l]+u2[j][l+1]+u2[j][l-1])-0.25*pow(delta,2)*rho2[j][l];
    
    /* Caso 3*/
    u3[j][l]=0.25*(u3[j+1][l]+u3[j-1][l]+u3[j][l+1]+u3[j][l-1])-0.25*pow(delta,2)*rho3[j][l];
   }
  }
  
  cout<<"Iteração= "<<t<<endl;
   
  t=t+1;	// incrementar iteração
 }
 
 ofstream ok;
 ok.open("1carga.txt");		// Caso 1
 
 ofstream bla;
 bla.open("2carga.txt");	// Caso 2
 
 ofstream wow;
 wow.open("Ncarga.txt");	// Caso 3
 
 for(int j=0;j<L;j++){
  for(int l=0;l<L;l++){
  
   ok<<j<<'\t'<<l<<'\t'<<u1[j][l]<<endl;	// Caso 1
   bla<<j<<'\t'<<l<<'\t'<<u2[j][l]<<endl;	// Caso 2
   wow<<j<<'\t'<<l<<'\t'<<u3[j][l]<<endl;	// Caso 3
  } 
 }
 
 ok.close();
 bla.close();
 wow.close();
 
 return 0;
} 
