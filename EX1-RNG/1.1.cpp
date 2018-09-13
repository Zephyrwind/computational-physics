/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 1.1 - Implementação de um gerador linear congruente
   Outubro de 2016 
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main()
{

 /* Método Congruente Linear */
 int X0=333331;				// seed
 int c=3;				// multiplicador do gerador
 int a=5;				// desvio do gerador
 int p=31;				// maior número possível de ser gerado
 int Y[100];				// variável no método congruente
 int X[100];				// array com os números aleatórios gerados

 ofstream xyz;
 xyz.open("rng.txt");

 for(int i=0;i<100;i++){
  if(i==0){
   Y[0]=X0;
   X[0]=(c*Y[0]+a)%p;
  }
  if(i>=1){
   Y[i]=X[i-1];
   X[i]=(c*Y[i]+a)%p;
   xyz << i << '\t' << X[i] << '\t' << Y[i] << endl; // ficheiro .txt para o teste do cubo
  }
 }
 xyz.close();

 /* Parametros da aula */
 c=16807;
 a=0;
 
 ofstream xyz2;
 xyz2.open("rngaula.txt");

 for(int i=0;i<100;i++){
  if(i==0){
   Y[0]=X0;
   X[0]=(c*Y[0]+a)%p;
  }
  if(i>=1){
   Y[i]=X[i-1];
   X[i]=(c*Y[i]+a)%p;
   xyz2 << i << '\t' << X[i] << '\t' << Y[i] << endl;
  }
 }
 xyz2.close();
 
 /* Função rand() */
 ofstream xyz3;
 xyz3.open("rngrand.txt");

 for(int i=0;i<100;i++){
   X[i]=rand();
   if(i>=1){
    xyz3 << i << '\t' << X[i] << '\t' << X[i-1] << endl;
  }
 }
 xyz3.close();
 
 /* Função drand48() */
 ofstream xyz4;
 xyz4.open("rngdrand48.txt");

 for(int i=0;i<100;i++){
   X[i]=100*drand48();
   if(i>=1){
    xyz4 << i << '\t' << X[i] << '\t' << X[i-1] << endl;
  }
 }
 xyz4.close();
 
 return 0;
}
