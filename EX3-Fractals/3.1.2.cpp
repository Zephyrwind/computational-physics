/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 3.1 - Dimensão fractal de agregado percolativo
   3.1.2 - Método de Box Counting
   Outubro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>

using namespace std;

void box_counting(int L){
 
 int rede[L*L];
 double pc=0.592746;	
 double w;			
 int conta=0;
 
 for(int i=0;i<L;i++){
  for(int j=0;j<L;j++){
   w=drand48();
   if(w>1-pc) rede[i+j*L]=1;
   else rede[i+j*L]=0;
  }
 }

 /* Metodo queima de baixo para cima (ex. 2.2) */
 for(int i=0;i<L;i++){
  if(rede[i]==1) {
   rede[i]=2;
   conta=conta+1;
  }
 }
  
 while(conta != 0){
  for(int i=0;i<L;i++){
   for(int j=0;j<L;j++){
    if(rede[i+j*L]==1){
     if(rede[i+(j-1)*L]==2 && j!=0) rede[i+j*L]=3;
     if(rede[i+j*L-1]==2 && i !=0) rede[i+j*L]=3;
     if(rede[i+j*L+1]==2 && i !=L-1) rede[i+j*L]=3;
     if(rede[i+(j+1)*L]==2 && j!=L-1) rede[i+j*L]=3;
    }
   }
  }
  for(int i=0;i<L;i++){
   for(int j=0;j<L;j++){
    if(rede[i+j*L]==2){
     rede[i+j*L]=4;
     conta=conta-1;
    }
    if(rede[i+j*L]==3){
     rede[i+j*L]=2;
     conta=conta+1;
    }
   }
  } 
 }
 
 /* Metodo da queima de cima para baixo para isolar agregado */
 for(int i=L-1;i>=0;i--){
  for(int j=L-1;j>=0;j--){
   if(rede[i+j*L]==1){
    rede[i+j*L]=0;
   }
   if(rede[i+j*L]==4){
    rede[i+j*L]=1;
   }
  }
 }
 
 int *box;
 int x,y;
 
 cout<<"Rede de tamanho "<<L<<" x "<<L<<endl;
 
 for(int l=1;l<L;l++){
  conta=0;
  if(L%l==0 && l!=1){
   box=new int[(L/l)*(L/l)];
   
   for(int i=0;i<L;i++){
    for(int j=0;j<L;j++){
     if(rede[i+j*L]==1){
      x=int (i/l);
      y=int (j/l);
      box[x+y*(L/l)]=1;
     }
    }
   }  
  for(int k=0;k<L/l;k++){
   for(int r=0;r<L/l;r++){
    if(box[k+r*(L/l)]=1) conta=conta+1;
   }
  }
  
  cout<<"Caixas de tamanho "<<l<<" x "<<l<<" com número de sítios igual= "<<conta<<endl;
  
  ofstream ok;
  ok.open("box counting.txt",fstream::app);
 
  ok<< log(conta)<< '\t'<< log(L/l)<<endl;
 
  delete [] box;
  }
 }
 
 return;      
} 

int main(){

 int L= pow(2,7);
 
 ofstream ok;
 ok.open("box counting.txt");
 
 box_counting(L);
 
 ok.close();
 
 return 0;
}
