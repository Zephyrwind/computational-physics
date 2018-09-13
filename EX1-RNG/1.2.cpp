/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 1.2 -Gerar pontos uniformemente sobre um círculo
   Outubro de 2016 
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

# define M_PI           3.14159265358979323846  // pi

int main()
{
/* Declaração de Variáveis */
 int N=10000;		// número de pontos
 double A;		// área uniforme
 double r;		// distância "uniforme" do ponto no círculo
 double Y[N];		// coordenada y do círculo
 double X[N];		// coordernada x do círculo
 double teta[N];	// ângulo (em radianos) do ponto no círculo
 
 ofstream xy;
 xy.open("circulo.txt");

/* Gerar aleatoriamente coordenadas polares e converter para coordenadas cartesianas */
 for(int i=0;i<N;i++){
   teta[i]=(2*M_PI*rand())/RAND_MAX;
   A=rand()/(double)RAND_MAX;
   r=sqrt(A);
   X[i]=r*cos(teta[i]);
   Y[i]=r*sin(teta[i]);
   
   xy << X[i] << '\t' << Y[i] << endl;	// ficheiro .txt para vizualizar a distribuição uniforme 2D
  }
 xy.close();

 return 0;
}
