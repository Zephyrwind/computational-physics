/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 1.3 - Teste do Qui-Quadrado
   Outubro de 2016 
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main()
{
 /* Declaraçao de variaveis */
 int X0=333331;			// seed
 int c=3;			// multiplicador do gerador
 int a=5;			// desvio do gerador
 double Nmax=31;		// maior número possível de ser gerado
 int n=50;			// numero de numeros aleatorios gerados
 int range=10;			// intervalo de 0-10
 double pi=1.0/(double)range;	// probabilidade de cada intervalo
 double Y[n];			// variavel para calcular numero aleatorio
 double X[n];			// array com os numeros aleatorios gerados
 int N[range]={0};		// array que conta o numero de numeros aleatorios gerados
 int conta=0;			// contador
 double qui2=0;			// qui-quadrado

 /* Gerador de n numeros aleatorios entre 0-10  usando metodo congruente com os valores do ex. 1.1 */
 for(int i=0;i<n;i++){
  if(i==0){
   Y[0]=X0;
   X[0]=range*fmod(c*Y[0]+a,Nmax)/Nmax;
  }
  if(i>=1){
   Y[i]=X[i-1];
   X[i]=range*fmod(c*Y[i]+a,Nmax)/Nmax;
  }
 }
 
 /* Contagem do numero de numeros aleatorios em cada intervalo */
 for(int j=0;j<n;j++){
  for(int k=0;k<range;k++){
   if(k<X[j]<k+1){
    conta=conta+1;
    N[k]=conta;
   }
  }
  conta=0;
 }
 
 /* Implementaçao do Qui-quadrado */
 for(int k=0;k<range;k++){
  qui2=qui2+(N[k]-(double)n*pi)*(N[k]-(double)n*pi)/((double)n*pi);
 }
 
 cout << "(Metodo Congruente) Qui-Quadrado= " << qui2 << endl;
 
 /* Comparação do teste do qui quadrado usando funçao rand */
 double Xr[n];
 int Nr[range]={0};
 double qui2r;
 
 for(int i=0;i<n;i++){
  Xr[i]=range*(rand()/(double) RAND_MAX);
 }
 
 for(int j=0;j<n;j++){
  for(int k=0;k<range;k++){
   if(k<Xr[j]<k+1){
    conta=conta+1;
    Nr[k]=conta;
   }
  }
  conta=0;
 }
 
 for(int k=0;k<range;k++){
  qui2r=qui2r+(Nr[k]-(double)n*pi)*(Nr[k]-(double)n*pi)/((double)n*pi);
 }
 
 cout << "(Função Rand) Qui-Quadrado= " << qui2r << endl;
 
 return 0;
}
