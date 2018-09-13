/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 2.2 - Método da Queima
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

int main(){

/* 0-> estado vazio 
   1-> estado ocupado
   2-> estado "a queimar"
   3-> estado que vai queimar na próxima iteração
   4-> estado queimado
*/

/* Geração de uconfigurações de percolação como no ex. 2.1 */
 int Lx=10;		
 int Ly=10;		
 double p=0.7;		
 int rede[Lx*Ly];	
 double w;		
 srand48(137493);	
 
 for(int i=0;i<Lx;i++){
  for(int j=0;j<Ly;j++){
   w=drand48();
   if(w>1-p) rede[i+j*Lx]=1;
   else rede[i+j*Lx]=0;
  }
 }
 
 Print_lattice (rede, Lx, Ly, ImageWidth, ImageHeight, "2.2 pre queima");
 
 int ite=0;	// iterações do método da queima
 int conta=0;	// número de estados 2
 int curto=0;	// caminho mais curto
 
 for(int i=0;i<Lx;i++){	// inicializar método com primeira linha a arder
  if(rede[i]==1) {	// 1->2 e soma valor um em conta
   rede[i]=2;
   conta=conta+1;
  }
 }
 
 while(conta != 0){	// enquanto houver estados para queimar
  ite=ite+1;		// somar iteração do ciclo
  for(int i=0;i<Lx;i++){
   for(int j=0;j<Ly;j++){
    if(rede[i+j*Lx]==1){
     if(rede[i+(j-1)*Lx]==2 && j!=0) rede[i+j*Lx]=3;	// vizinho de baixo a queimar, 1->3
     if(rede[i+j*Lx-1]==2 && i !=0) rede[i+j*Lx]=3;	// vizinho da esquerda a queimar, 1->3
     if(rede[i+j*Lx+1]==2 && i !=Lx-1) rede[i+j*Lx]=3; 	// vizinho da direita a queimar, 1->3
     if(rede[i+(j+1)*Lx]==2 && j!=Ly-1) rede[i+j*Lx]=3;	// vizinho de cima a queimar, 1->3
    }
   }
  }
  
  for(int i=0;i<Lx;i++){
   for(int j=0;j<Ly;j++){
    if(rede[i+j*Lx]==2){
     rede[i+j*Lx]=4;	// estado fica queimado, 2->4
     conta=conta-1;	// diminuir conta
    }
    if(rede[i+j*Lx]==3){
     rede[i+j*Lx]=2;	// estado fica a arder, 3->2
     conta=conta+1;	// aumentar conta
    }
   }
   if(rede[i+(Ly-1)*Lx]==4 && curto==0) curto=ite;	// primeiro estado 4, caminho mais curto
  } 
 }
 
 Print_lattice (rede, Lx, Ly, ImageWidth, ImageHeight, "2.2 pos queima");
 
 if(curto !=0) cout<< "Há agregado percolativo!" << '\n' << "Caminho mais curto= " << curto <<'\n'<< "Número total de passos= " << ite <<endl;
 
 if(curto==0) cout<< "Não há agregado percolativo!" << '\n' << "Número total de passos= " << ite <<endl;
 
 return 0;
}
