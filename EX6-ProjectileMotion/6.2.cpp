/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 6.2 - Lançamento com Resistência de Ar (Método Runge-Kutaa 4ºOrdem)
   Novembro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

# define M_PI           3.14159265358979323846  // pi

using namespace std;

double atrito_RK4(double step, double theta,double gama){
 
 /* Condições iniciais */
 double v0=20.0;	// velocidade inicial
 double g=9.8;	// aceleração gravítica
 
 /* Sistema de equações diferenciais */
 double dx=v0*cos(theta);	// derivada de x
 double dy=v0*sin(theta);	// derivada de y
 double dvx=-gama*dx*v0;	// derivada de vx
 double dvy=-g-gama*dy*v0;	// derivada de vy

 double x=0,y=0,vx=0,vy=0;	// variaveis a determinar
 int t=0;	// numero de iterações
 double k1x, k2x, k3x, k4x;	// Coef RK4 de x
 double k1y, k2y, k3y, k4y;	// Coef RK4 de y
 double k1vx, k2vx, k3vx, k4vx;	// Coef RK4 de vx
 double k1vy, k2vy, k3vy, k4vy;	// Coef RK4 de vy
 
 while(y>=0){	// enquanto projectil voar
  
  /* Declive no ponto inicial */
  k1x=dx;
  k1y=dy;
  k1vx=dvx;
  k1vy=dvy;
  
  /* Declive num ponto intermedio */
  k2x=dx+k1x*step/2.0;
  k2y=dy+k1y*step/2.0;
  k2vx=dvx+k1vx*step/2.0;
  k2vy=dvy+k2vy*step/2.0;
  
  /* Declive noutro ponto intermedio */
  k3x=dx+k2x*step/2.0;
  k3y=dy+k2y*step/2.0;
  k3vx=dvx+k2vx*step/2.0;
  k3vy=dvy+k2vy*step/2.0;
  
  /* Declive no ponto final */
  k4x=dx+k3x*step;
  k4y=dy+k3y*step;
  k4vx=dvx+k3vx*step;
  k4vy=dvy+k3vy*step;
  
  x=x+step*(k1x/6.0+k2x/3.0+k3x/3.0+k4x/6.0);	// valor x
  y=y+step*(k1y/6.0+k2y/3.0+k3y/3.0+k4y/6.0);	// valor y
  vx=dx+step*(k1vx/6.0+k2vx/3.0+k3vx/3.0+k4vx/6.0);	// valor vx
  vy=dy+step*(k1vy/6.0+k2vy/3.0+k3vy/3.0+k4vy/6.0);	// valor vy
  
  dx=vx;	// actualizar vx
  dy=vy;	// actualizar vy 
  t=t+1;	// somar iteração
 }
 
 return x;
}  
 
int main(){
 
 double step=1e-2;	// passo de integração
 double gama=1e-5;	// constante proporcional ao quadrado da velocidade
 double L;	// valor calculado do alcance do projectil
 double alfa;	// angulo de lançamento em graus
 double alfaMax;	// angulo correspondente ao alcance maximo
 double LMax;	// alcance maximo para um dado gama
 
 ofstream ok; 
 ok.open("gama.txt"); 
 
 for(double j=gama;j<=1.0;j=j+5*gama){	// variar gama
 
  LMax=0;
  alfaMax=0;   
 
  for(double i=M_PI/200.0;i<M_PI/2.0;i=i+M_PI/200.0){	// variar angulo de lançamento
  
   L=atrito_RK4(step,i,j);
   alfa=i*180.0/M_PI;

   if(L>LMax){
    LMax=L;
    alfaMax=alfa;
   }
  }
 
 cout<<"Gama= "<<j<<" , Alcance Máximo= "<<LMax<<" , Angulo Lançamento= "<<alfaMax<<endl;
 ok<<j<<'\t'<<LMax<<'\t'<<alfaMax<<endl;
 }
 
 ok.close(); 
 
 return 0;
}
