/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 6.1 - Lançamento sem Resistência de Ar (Método Euler)
   Novembro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

# define M_PI           3.14159265358979323846  // pi

using namespace std;

double euler(double step){	// alcance simulado para um dado passo de Euler
 
 /* Condições iniciais */
 double v0=10.0;	// velocidade inicial
 double theta=M_PI/4.0;	// angulo de lançamento
 double g=9.8;	// aceleração gravítica
 
 /* Sistema de equações diferenciais */
 double dx=v0*cos(theta);	// derivada de x
 double dy=v0*sin(theta);	// derivada de y
 double dvx=0;	// derivada de vx
 double dvy=-g;	// derivada de vy

 double x=0,y=0,vx=0,vy=0;	// variaveis a determinar
 int t=0;	// numero de iterações
 
 char nome[100];
 sprintf(nome,"traj(step=%0.3f).txt",step);
 
 ofstream bla;
 bla.open(nome);
 
 while(y>=0){	// enquanto projectil voar
  
  bla<<x<<'\t'<<y<<endl;
  
  x=x+dx*step;	// aproximação linear em x
  y=y+dy*step;	// aproximação linear em y
  vx=dx+dvx*step;	// aproximação linear em vx
  vy=dy+dvy*step;	// aproximação linear em vy
  
  dx=vx;	// actualizar vx
  dy=vy;	// actualizar vy
  t=t+1;	// somar iteração
 }

 bla.close();
 
 return x;
}  

int main(){
 
 /* Calculo analitico do alcance máximo */
 double v0=10;	// modulo da velocidade inicial de lançamento
 double theta=M_PI/4.0;	// angulo de lançamento
 double g=9.8;	// aceleração gravitica
 double vx=v0*cos(theta);	// velocidade inicial vx
 double vy=v0*sin(theta);	// velocidade inicial vy
 double tvoo=(2.0*vy)/g;	// tempo de voo
 double alcance=vx*tvoo;	// alcance analitico
 
 double step=1e-3;	// iteração de Euler
 double L;	// valor calculado do alcance do projectil
 double erro;	// erro entre alcance simulado e o alcance analitico
 
 ofstream ok;
 ok.open("euler.txt");
 
 for(double i=step;i<=1.0;i=i*10){	// variar passo de Euler
 
  L=euler(i);	// alcance simulado
  erro=abs(L-alcance);	// erro absoluto
  
  cout<<"Alcance Máximo= "<<L<<" , Erro Absoluto= "<<erro<<endl;
  ok<<i<<'\t'<<L<<'\t'<<erro<<endl;
 }
 
 ok.close();
 
 cout<<"Alcance Máximo teorico= "<<alcance<<endl;
 
 return 0;
 
}
