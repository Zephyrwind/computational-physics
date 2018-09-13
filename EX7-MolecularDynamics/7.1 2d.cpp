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

void cfp (double &sitio, double &sitioa, int L){ // função que verifica condições de fronteira periódicas

 if(sitio<0.0){
  sitio=sitio+L; 
  sitioa=sitioa+L;
 }
 if(sitio>L){
  sitio=sitio-L; 
  sitioa-=L;
 }
}

double cfp_d (double d, int L){	// funçao que calcula distancia entre particulas com cfp

 if(d>L/2.0) d=d-L;
 if(d<-L/2.0) d=d+L;
 
 return d;
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

 int N=2;	// numero de particulas
 double L=10;	// lado da caixa
 double X1[N],Y1[N],Z1[N];	// posições das particulas actual
 double X0[N],Y0[N],Z0[N];	// posiçoes das particulas passadas
 double Vx[N],Vy[N],Vz[N];	// velocidade das particulas
 double step=1e-5;	// passo de integração
 double Rc=10.0;	// raio de corte
 
 X1[0]=1.5;
 Y1[0]=2.0;
 X1[1]=3.5;
 Y1[1]=2.0;
 
 X0[0]=1.5-step;
 X0[1]=3.5+step;
 Y0[0]=2.0;
 Y0[1]=2.0;
 
 /* Condições Iniciais */
 //for(int i=0;i<N;i++){
 
  /* Posição inicial */ 
  //X1[i]=L*drand48();
  //Y1[i]=L*drand48();
  //Z1[i]=L*drand48();
  
  /* Posição Passada */
  //X0[i]=X1[i]-step;
  //Y0[i]=Y1[i]-step;
  //Z0[i]=Z1[i]-2.0*step;
  
  /* Condições de Fronteira periodica */
  //X0[i]=cfp(X0[i],L);
  //Y0[i]=cfp(Y0[i],L);
  //Z0[i]=cfp(Z0[i],L);
  
  /* Velocidade inicial */
  //Vx[i]=(X1[i]-X0[i])/(2.0*step);
  //Vy[i]=(Y1[i]-Y0[i])/(2.0*step);
  //Vz[i]=(Z1[i]-Z0[i])/(2.0*step);
 //}
  
 ofstream ok;
 ok.open("Ek.txt");
 
 ofstream bla;
 bla.open("Ep.txt");
 
 ofstream doh;
 doh.open("Em.txt");
  
 int tmax=1e5;	// tempo total de iterações
 int t=0;	// iteração
  
 while (t<=tmax){
 
  double Ekt=0;	// energia cinetica em cada iteração
  double Ept=0;	// energia potencial em cada iteração
  
  for(int i=0;i<N;i++){	// correr todas as particulas i
   
   double Fx=0;	// força x acumulada entre particula i e todas as outras
   double Fy=0;	// força y acumulada entre particula i e todas as outras
   //double Fz=0;	// força z acumulada entre particula i e todas as outras
   
   double Vit=0;	// potencial na particula i
     
   for(int j=0;j<N;j++){	// ver interações entre particulas i e j
    
    if(j!=i){	// excepto com ela propria
     
     double dx=X1[i]-X1[j];	// distancia x entre particulas i e j
     double dy=Y1[i]-Y1[j];	// distancia y entre particulas i e j
     //double dz=Z1[i]-Z1[j];	// distancia z entre particulas i e j
      
     /* Condições de fronteira periódicas no cálculo da distância */
     dx=cfp_d(dx,L);
     dy=cfp_d(dy,L);
     //dz=cfp_d(dz,L);
      
     double r=sqrt(pow(dx,2)+pow(dy,2));/*+pow(dz,2));*/	// distancia entre particulas i e j
      
     if(r<Rc){	// se distancia menor que raio de corte, faz contas
      
      double V=V_LJ(r)-V_LJ(Rc)+forca_LJ(Rc)*(r-Rc);	// potencial de Lennard-Jones
      double F=forca_LJ(r)-forca_LJ(Rc);	// derivada do potencial de Lennard Jones (força)
      
      double drx=dx/r;	// derivada de r em ordem a x
      double dry=dy/r;	// derivada de r em ordem a y
      //drz=dz/r;	// derivada de r em ordem a z
      
      Fx=Fx+F*drx;	// iterar força x na particula i
      Fy=Fy+F*dry;	// iterar força y na particula i
      //Fz=Fz+dVr*drz;	// iterar força z na particula i
      
      Vit=Vit+V; // iterar potencial na particula i
     }
    }
   }
    
   double temp;	// variavel temporaria para guardar posiçao passada
   
   temp=X0[i];	
   X0[i]=X1[i];	// actualizar posiçao x passada da particula i  
   X1[i]=2.0*X1[i]-temp+Fx*pow(step,2);	// actualizar posiçao x actual da particula i
   Vx[i]=(X1[i]-temp)/(2.0*step);	// actualizar velocidade x da particula i
   cfp(X1[i],X0[i],L);	// verificar novamente condiçoes periódicas para x
   
   temp=Y0[i];  
   Y0[i]=Y1[i];	// actualizar posiçao y passada da particula i
   Y1[i]=2.0*Y1[i]-temp+Fy*pow(step,2);	// actualizar posição y actual da particula i
   Vy[i]=(Y1[i]-temp)/(2.0*step);	// actualizar velocidade y da particula i
   cfp(Y1[i],Y0[i],L);	// verificar novamente condiçoes periódicas para y
   
  
   //temp=Z0[i];  
   //Z0[i]=Z1[i];	// actualizar posiçao z passada da particula i
   //Z1[i]=2.0*Z1[i]-temp+Fz*pow(step,2);	// actualizar posiçao z actual da particula i
   //Vz[i]=(Z1[i]-temp)/(2.0*step);	// actualizar velocidade z da particula i
   //Z1[i]=cfp(Z1[i],Z0[i],L);

   double V2=pow(Vx[i],2)+pow(Vy[i],2);//+pow(Vz[i],2);	// modulo da velocidade ao quadrado
   
   Ekt=Ekt+0.5*V2;	// energia cinetica acumulada de cada particula
   Ept=Ept+Vit;	// energia potencial acumulada de cada particula
  }
 
  Ept=Ept/2.0;	// divide-se por 2 porque conta-se o potencial entre cada par duas vezes
   
  double Em=Ekt+Ept;	// energia mecanica
 
  if (t%10==0){	// guardar a cada 10 iterações
 
   ok<<t<<'\t'<<Ekt<<endl;
   bla<<t<<'\t'<<Ept<<endl;
   doh<<t<<'\t'<<Em<<endl;
   
   cout<<"Iteracao= "<<t<<" , Ek= "<<Ekt<< " , Ep= "<<Ept<<" , Em= "<<Em<<endl;
  }
  
  t=t+1; 
 }
 
 ok.close();
 bla.close();
 doh.close();
 
 return 0;
}
