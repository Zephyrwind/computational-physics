/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 3.2 - Agregação Limitada pela Difusão (DLA)
   Outubro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include "latticeview.h"

using namespace std;

#define ImageWidth 1000  //image width
#define ImageHeight 1000 //image height
#define M_PI 3.14159265358979323846  // pi

int main(){

 int L=100;	// tamanho do sistema
 int rede[L*L]={0};	// rede quadrada
 int N=pow(10,5);	// numero de particulas
 int r=10;	// raio de largada
 double angulo;	// angulo de largada
 int x,y;	// coordenadas da particula
 double l;	// random walk
 bool livre=false;	// true- particula livre; false- particula colada ao cluster */
 
 rede[(L/2)+(L/2)*L]=1;	/* seed do DLA no meio da rede */
 
 for(int k=1;k<=N;k++){	// gera walker
 
  /* coordenadas do walker numa circuferencia centrada na seed do dla */ 
  angulo=2*M_PI*drand48();
  x=r*cos(angulo)+L/2;
  y=r*sin(angulo)+L/2;
 
  if(rede[x+y*L]!=1){ rede[x+y*L]=2; livre=true; } 
  
  while(livre){	// enquanto particula nao encontrar cluster
  
   l=rand()/(double) RAND_MAX;	// random walk
   
   if(0<l<0.25){ rede[x+y*L]=0; y++; rede[x+y*L]=2; }	// cima
   if(0.25<l<0.5){ rede[x+y*L]=0; x++; rede[x+y*L]=2; }	// direita
   if(0.5<l<0.75){ rede[x+y*L]=0; y--; rede[x+y*L]=2; }	// baixo
   if(0.75<l<1){ rede[x+y*L]=0; x--; rede[x+y*L]=2; }	// esquerda
   
   /* primeiros vizinhos ocupados, encontrou cluster, fica ocupado */
   if(rede[x+y*L]==2&&(rede[x-1+y*L]==1||rede[x+1+y*L]==1||rede[x+(y+1)*L]==1||rede[x+(y-1)*L]==1)){
    rede[x+y*L]=1;
    livre=false;
   }
   /* se particula fugir muito do raio de escape, destruir particula */
   if(sqrt(pow(x,2)+pow(y,2))>2*(r+L/2)){rede[x+y*L]=0; livre=false;}
  }
  
 if(k%300==0 && r<L/2) r=r+1; /* incrementar raio de escape a medida que cluster cresce */
 
 /* seeds dos geradores aleatorios */
 srand48(k);
 srand(k);
 }
 
 Print_lattice (rede, L, L, ImageWidth, ImageHeight, "dla");	// imagem do dla

 return 0;
}
