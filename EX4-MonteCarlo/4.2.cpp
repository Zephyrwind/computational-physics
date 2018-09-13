/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 4.2 - Pontos numa caixa
   Novembro de 2016 
*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// devolve a distância média entre N particulas para K configurações 
double caixa(int N, int K){	

 double X[N],Y[N],Z[N];	// posições (x,y,z) de N partículas
 double dm[K]={0};	// distância média entre partículas
 double conta=0;	// conta
 
 for(int k=0;k<K;k++){	// soma sobre K configurações
  for(int i=0;i<N;i++){	// fixar partícula i
   for(int j=0;j<N;j++){	// ver as outras partículas j
    X[j]=drand48(); 
    Y[j]=drand48();
    Z[j]=drand48();    
  
   // calcular a distancia medida entre a partícula i e a particula j e somar para todos os pares
   // contabilizar cada distância apenas uma vez, por isso impoe se a condição j>i
   if(j>i) conta=sqrt(pow(X[i]-X[j],2)+pow(Y[i]-Y[j],2)+pow(Z[i]-Z[j],2))+conta;
   }
  }
  
  dm[k]=2*conta/((double)N*((double)N-1));
  conta=0;
  srand48(k);
 }
 
 conta=0;
 for(int k=0;k<K;k++){
  conta=dm[k]+conta;
 }
 
 conta=conta/(double)K;
 
 return conta;
}

int main(){

 int N=500;	// numero de particulas
 double dmm=0;	// distância media sobre configurações
 
 /* N fixo, K a variar */
 ofstream bla;
 bla.open("n fixo, k a variar.txt");
 
 for( int i=1;i<=100;i++){
  dmm=caixa(100,i)+dmm;	// soma sobre K=1,2,...,100 configurações de 100 particulas
  bla<< i<<'\t'<< dmm/(double)i<<endl;
 }
 bla.close();
 
 dmm=0;
 
 /* N a variar, K fixo */
 ofstream ok;
 ok.open("n variar, k fixo.txt");
 
 for(int i=2;i<N+1;i++){
  dmm=caixa(i,50)+dmm;	// soma sobre 50 configuraçoes de N=2,3,...,500 particulas
  ok<< i<< '\t'<< dmm/(double)i<< '\t'<<endl;
 }
 ok.close();
 
 return 0;
}
