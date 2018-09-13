/* Cláudio Santos nº 42208
   MIEF - Modelação em Física e Engenharia
   Ex 7.1 - Gás de Lennard-Jones
   Novembro de 2016 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

using namespace std;

void cfp (double &sitio1, double &sitio0, double L){ // função que verifica condições de fronteira periódicas

 if(sitio1<0.0){ sitio1=sitio1+L; sitio0=sitio0+L;}

 if(sitio1>L){ sitio1=sitio1-L; sitio0=sitio0-L;}

}

void cfp_d (double &d, double L){	// funçao que calcula distancia (com sinal) entre particulas com cfp

 if(d>L/2.0) d-=L;
 if(d<-L/2.0) d+=L;
}

double V_LJ (double r){	// função que calcula potencial de Lennard-Jones
 
 double V=4.0*(1.0/pow(r,12)-1.0/pow(r,6));
 
 return V;
}

double forca_LJ(double r){	// função que calcula derivada do potencial de Lennard-Jones (força)
 
 double F=24.0*(2.0/pow(r,13)-1.0/pow(r,7));
 
 return F;
}

int main(){

 int N=50;	// numero de particulas
 double L=10;	// lado da caixa
 double X1[N],Y1[N],Z1[N];	// posições das particulas actual
 double X0[N],Y0[N],Z0[N];	// posiçoes das particulas passadas
 double Vx[N],Vy[N],Vz[N];	// velocidade das particulas
 double dx,dy,dz;	// distancia entre particulas x, y, z
 double r;	// distancia entre particulas
 double V,F;	// Potencial e força entre particulas
 double drx,dry,drz;	// derivada de r em ordem a x, y, z
 double Fx,Fy,Fz;	// força x, y, z
 double Vi;	// contador do potencial na particula y
 double Vel2;	// modulo velocidade ao quadrado
 double Ek,Ep,Em;	// energia cinetica, potencial, mecanica
 double step=1e-4;	// passo de integração
 double Rc=2.5;	// raio de corte

 /* Condições Iniciais */
 for(int i=0;i<N;i++){
 
  /* Posição inicial aleatoriamente*/ 
  X1[i]=L*drand48();
  Y1[i]=L*drand48();
  Z1[i]=L*drand48();
  
  /* Sentido da posição passada aleatoriamente */
  int wx=1+rand()%2;
  int wy=1+rand()%2;
  int wz=1+rand()%2;
  
  /* Posição Passada x com incremento aleatorio*/
  if(wx==1){ X0[i]=X1[i]-step*drand48(); }
  if(wx==2){ X0[i]=X1[i]+step*drand48(); }
  
  /* Posição Passada y com incremento aleatorio*/
  if(wy==1){ Y0[i]=Y1[i]-step*drand48(); }
  if(wy==2){ Y0[i]=Y1[i]+step*drand48(); }
  
  /* Posição Passada z com incremento aleatorio*/
  if(wz==1){ Z0[i]=Z1[i]-step*drand48(); }
  if(wz==2){ Z0[i]=Z1[i]+step*drand48(); }
  
  /* Verificar condições de fronteira periodica */
  cfp(X1[i],X0[i],L);
  cfp(Y1[i],Y0[i],L);
  cfp(Z1[i],Z0[i],L);
 }
  
 ofstream ok;
 ok.open("E.txt");
 
 //char nome[100];
 //ofstream bla;
  
 int tmax=1e5;	// tempo total de iterações
 int t=0;	// iteração
  
 while (t<=tmax){
  
  Ek=0;	// energia cinetica em cada iteração
  Ep=0;	// energia potencial em cada iteração
  Em=0;	// energia mecanica em cada iteraçao
  
  //sprintf(nome,"mexe%d.txt",t);
  //bla.open(nome);
  
  for(int i=0;i<N;i++){	// correr todas as particulas i
   
    //bla<<X1[i]<<'\t'<<Y1[i]<<'\t'<<Z1[i]<<endl;
   
   Fx=0;	// força x acumulada entre particula i e todas as outras
   Fy=0;	// força y acumulada entre particula i e todas as outras
   Fz=0;	// força z acumulada entre particula i e todas as outras
   
   Vi=0;	// potencial na particula i
     
   for(int j=0;j<N;j++){	// ver interações entre particulas i e j
    
    if(j!=i){	// excepto com ela propria
     
     dx=X1[i]-X1[j];	// distancia x entre particulas i e j
     dy=Y1[i]-Y1[j];	// distancia y entre particulas i e j
     dz=Z1[i]-Z1[j];	// distancia z entre particulas i e j
      
     /* Condições de fronteira periódicas no cálculo da distância */
     cfp_d(dx,L);
     cfp_d(dy,L);
     cfp_d(dz,L);
      
     r=sqrt(pow(dx,2)+pow(dy,2)+pow(dz,2));	// distancia entre particulas i e j
      
     if(r<Rc){	// se distancia menor que raio de corte, faz contas
      
      V=V_LJ(r)-V_LJ(Rc)+forca_LJ(Rc)*(r-Rc);	// potencial de Lennard-Jones
      F=forca_LJ(r)-forca_LJ(Rc);	// derivada do potencial de Lennard Jones (força)
      
      drx=dx/r;	// derivada de r em ordem a x
      dry=dy/r;	// derivada de r em ordem a y
      drz=dz/r;	// derivada de r em ordem a z
      
      Fx=Fx+F*drx;	// iterar força x na particula i
      Fy=Fy+F*dry;	// iterar força y na particula i
      Fz=Fz+F*drz;	// iterar força z na particula i
      
      Vi=Vi+V; // iterar potencial na particula i
     }
    }
   }
   
   double temp;	// variavel para guardar posiçao passada temporariamente
   
   temp=X0[i];	
   X0[i]=X1[i];	// actualizar posiçao x passada da particula i  
   X1[i]=2.0*X1[i]-temp+Fx*pow(step,2);	// actualizar posiçao x actual da particula i
   
   temp=X1[i]-temp;
   cfp_d(temp,L);	// condições periodicas
   Vx[i]=temp/(2.0*step);	// actualizar velocidade x da particula i
   cfp(X1[i],X0[i],L);	// verificar novamente condiçoes periódicas para x
      
   temp=Y0[i];  
   Y0[i]=Y1[i];	// actualizar posiçao y passada da particula i
   Y1[i]=2.0*Y1[i]-temp+Fy*pow(step,2);	// actualizar posição y actual da particula i

   temp=Y1[i]-temp;
   cfp_d(temp,L);	// condiçoes periodicas
   Vy[i]=temp/(2.0*step);	// actualizar velocidade y da particula i
   cfp(Y1[i],Y0[i],L);	// verificar novamente condiçoes periódicas para y
   
   temp=Z0[i];  
   Z0[i]=Z1[i];	// actualizar posiçao z passada da particula i
   Z1[i]=2.0*Z1[i]-temp+Fz*pow(step,2);	// actualizar posiçao z actual da particula i
   
   temp=Z1[i]-temp;
   cfp_d(temp,L);	// condiçoes periodicas
   Vz[i]=temp/(2.0*step);	// actualizar velocidade z da particula i
   cfp(Z1[i],Z0[i],L);	// verificar novamente condiçoes periódicas para z

   Vel2=pow(Vx[i],2)+pow(Vy[i],2)+pow(Vz[i],2);	// modulo da velocidade ao quadrado
   
   Ek=Ek+0.5*Vel2;	// energia cinetica acumulada de cada particula
   Ep=Ep+Vi;	// energia potencial acumulada de cada particula
  }
 
  //bla.close();  
 
  Ep=Ep/2.0;	// divide-se por 2 porque conta-se o potencial entre cada par duas vezes
   
  Em=Ek+Ep;	// energia mecanica
    
  ok<<t<<'\t'<<Ek<<'\t'<<Ep<<'\t'<<Em<<endl; 
  cout<<"Iteracao= "<<t<<" , Ek= "<<Ek<< " , Ep= "<<Ep<<" , Em= "<<Em<<endl;
  
  t=t+1; 
 }
 
 ok.close();
 
 return 0;
}
