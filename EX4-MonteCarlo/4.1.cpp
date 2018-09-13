/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 4.1 - Calcular o valor de pi 
   Novembro de 2016 
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

# define M_PI           3.14159265358979323846  // pi

double long calcpi (int N){	// função que calcula valor de pi com N pontos aleatorios

 double r;	// distância da origem ao ponto gerado
 double Y;	// coordenada y do ponto
 double X;	// coordenada x do ponto	
 double conta=0;// contador

 for(int i=0;i<N;i++){	
  X=drand48();	// gerar aleatoriamente coordenadas x
  Y=drand48();	// gerar aleatoriamente coordenadas y
  r=sqrt(pow(X,2)+pow(Y,2));
  
  if(r<1) conta=conta+1;	// calha dentro do quarto circulo, contar
 }
 
 double long pi=4*(conta/N);	// pi=4*quarto de circulo*fracção do contador sobre todos os pontos gerados

 return pi;
}
int main(){

 double long pi; // valor de pi calculado
 int N=10;	// número de pontos gerados
 double long delta;	// desvio entre valor calculado e teórico
 
 ofstream ok;
 ok.open("pi.txt");
 
 for(int k=1;k<=pow(N,4);k++){
  pi=calcpi(N*k);
  delta=M_PI-pi;
  ok<< (N*k)<<'\t'<<pi <<'\t'<< delta<<endl;
  if((N*k)==pow(N,4)) cout<<"N= "<<(N*k)<<" , PI= "<<pi<<" +- "<<delta<<endl;
 }
 
 ok.close();

 return 0;
}
