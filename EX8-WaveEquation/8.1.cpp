/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 8.1 - Resolução da Equação de Onda
   Novembro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(){
 
 /* Caso 1: b<1 */
 int Nx1=20;	// discretização espacial caso 1
 int Nt1=100;	// discretização temporal caso 1
 double dX1=1.0e-2;	// step espacial caso 2
 double dT1=1.0e-2;	// step temporal caso 2
 double vel1=0.4;	// velocidade onda caso 1
 double b1=pow((vel1*dT1)/dX1,2);	// coef b caso 1
 double u1[Nx1][Nt1];	// funçao onda caso 1
 
 /* Caso 2: b=1 */
 int Nx2=20;	// discretização espacial caso 2
 int Nt2=100;	// discretização temporal caso 2
 double dX2=1.0e-2;	// step espacial caso 2
 double dT2=1.0e-2;	// step temporal caso 2
 double vel2=1.0;	// velocidade onda caso 2
 double b2=pow((vel2*dT2)/dX2,2);	// coef b caso 2
 double u2[Nx2][Nt2];	// funçao onda caso 2 
 
 /* Caso 3: b>1 */
 int Nx3=20;	// discretização espacial caso 3
 int Nt3=50;	// discretização temporal caso 3
 double dX3=1.0e-4;	// step espacial caso 3
 double dT3=1.0e-2;	// step temporal caso 3
 double vel3=10.0;	// velocidade onda caso 3
 double b3=pow((vel3*dT2)/dX3,2);	// coef b caso 3
 double u3[Nx3][Nt3];	// funçao onda caso 3
  
 /* Condiçoes Iniciais */
 
 /* Caso 1 */
 for(int x=0;x<Nx1;x++){
 
  u1[x][0]=exp(-pow(x-vel1*dT1-10,2));	// condição instante passado caso 1
  u1[x][1]=exp(-pow(x-10,2));	// condição instante actual caso 1
 }
 
 /* Caso 2 */
 for(int x=0;x<Nx2;x++){
 
  u2[x][0]=exp(-pow(x-vel2*dT2-10,2));	// condição instante passado caso 2
  u2[x][1]=exp(-pow(x-10,2));	// condição instante actual caso 2
 }
 
 /* Caso 3 */
 for(int x=0;x<Nx3;x++){
  
  u3[x][0]=exp(-pow(x-vel3*dT3-10,2));	// condição instante passado caso 3
  u3[x][1]=exp(-pow(x-10,2));	// condição instante actual caso 3
 }
 
 /* Algoritmo das diferenças finitas numa malha com condiçoes fronteira periodicas*/
 
 /* Caso 1 */
 for(int t=1;t<Nt1-1;t++){
  for(int x=0;x<Nx1;x++){
   
   if(x==0) u1[0][t+1]=2.0*(1.0-b1)*u1[0][t]+b1*(u1[1][t]+u1[Nx1-1][t])-u1[0][t-1];
   
   else if(x==Nx1-1) u1[Nx1-1][t+1]=2.0*(1.0-b1)*u1[Nx1-1][t]+b1*(u1[0][t]+u1[Nx1-2][t])-u1[Nx1-1][t-1]; 
     
   else u1[x][t+1]=2.0*(1.0-b1)*u1[x][t]+b1*(u1[x+1][t]+u1[x-1][t])-u1[x][t-1];
  }
 }
 
 /* Caso 2 */
 for(int t=1;t<Nt2-1;t++){
  for(int x=0;x<Nx2;x++){
   
   if(x==0) u2[0][t+1]=2.0*(1.0-b2)*u2[0][t]+b2*(u2[1][t]+u2[Nx2-1][t])-u2[0][t-1];
   
   else if(x==Nx2-1) u2[Nx2-1][t+1]=2.0*(1.0-b2)*u2[Nx2-1][t]+b2*(u2[0][t]+u2[Nx2-2][t])-u2[Nx2-1][t-1];
    
   else u2[x][t+1]=2.0*(1.0-b2)*u2[x][t]+b2*(u2[x+1][t]+u2[x-1][t])-u2[x][t-1]; 
  }
 }
 
 /* Caso 3 */
 for(int t=1;t<Nt3-1;t++){
  for(int x=0;x<Nx3;x++){
   
   if(x==0) u3[0][t+1]=2.0*(1.0-b3)*u3[0][t]+b3*(u3[1][t]+u3[Nx3-1][t])-u3[0][t-1]; 
   
   else if(x==Nx3-1) u3[Nx3-1][t+1]=2.0*(1.0-b3)*u3[Nx3-1][t]+b3*(u3[0][t]+u3[Nx3-2][t])-u3[Nx3-1][t-1];
   
   else u3[x][t+1]=2.0*(1.0-b3)*u3[x][t]+b3*(u3[x+1][t]+u3[x-1][t])-u3[x][t-1];
  }
 }
 
 /* Guardar ficheiros de cada caso */
 
 /* Caso 1 */
 ofstream ok;
 ok.open("b<1.txt");
 
 for(int t=0;t<Nt1;t++){
  for(int x=0;x<Nx1;x++){
  
   cout<<"t= "<<t<<", X= "<<x<<" , u(x)= "<<u1[x][t]<<endl;
   ok<<t<<'\t'<<x<<'\t'<<u1[x][t]<<endl;
  }
 }
  
 ok.close();
 
 /* Caso 2 */ 
 ofstream bla;
 bla.open("b=1.txt");
 
 for(int t=0;t<Nt2;t++){
  for(int x=0;x<Nx2;x++){
  
   cout<<"t= "<<t<<", X= "<<x<<" , u(x)= "<<u2[x][t]<<endl;
   bla<<t<<'\t'<<x<<'\t'<<u2[x][t]<<endl;
  }
 }
 
 bla.close();
 
 /* Caso 3 */
 ofstream wow;
 wow.open("b>1.txt");
 
 for(int t=0;t<Nt3;t++){
  for(int x=0;x<Nx3;x++){
  
   cout<<"t= "<<t<<", X= "<<x<<" , u(x)= "<<u3[x][t]<<endl;
   wow<<t<<'\t'<<x<<'\t'<<u3[x][t]<<endl;
  }
 }
 
 wow.close(); 
  
 return 0;
} 
