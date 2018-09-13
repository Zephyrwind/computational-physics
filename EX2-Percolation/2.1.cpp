/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 2.1 - Gerar configurações canonicas de percolaçao
   Outubro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <fstream>
#include "latticeview.h"
#include <stdlib.h>

using namespace std;

#define ImageWidth 1000  //image width
#define ImageHeight 1000 //image height

int main()
{
 /* Declaração de variaveis */
 int Lx=50;		// dimensao x
 int Ly=50;		// dimensao y
 double p=0.3;		// probabilidade
 int rede[Lx*Ly];	// rede quadrada
 double w;		// numero aleatorio
 srand48(137493);	//seed
 
 for(int i=0;i<Lx;i++){		// correr dimensao x
  for(int j=0;j<Ly;j++){	// correr dimensao y
   w=drand48();			// gerar numero
   if(w>1-p) rede[i+j*Lx]=1;	// numero maior que probabilidade, contar na posiçao
   else rede[i+j*Lx]=0;		// senao nao contar
  }
 }
 
 Print_lattice (rede, Lx, Ly, ImageWidth, ImageHeight, "p=0.3");	// guarda imagem

 /* p=0.5 */
 p=0.5;
 
 for(int i=0;i<Lx;i++){
  for(int j=0;j<Ly;j++){
   w=drand48();
   if(w>1-p) rede[i+j*Lx]=1;
   else rede[i+j*Lx]=0;
  }
 }
 
 Print_lattice (rede, Lx, Ly, ImageWidth, ImageHeight, "p=0.5");
 
 /* p=0.7 */
 p=0.7;
 
 for(int i=0;i<Lx;i++){
  for(int j=0;j<Ly;j++){
   w=drand48();
   if(w>1-p) rede[i+j*Lx]=1;
   else rede[i+j*Lx]=0;
  }
 }
 
 Print_lattice (rede, Lx, Ly, ImageWidth, ImageHeight, "p=0.7");
 
 return 0;
} 
