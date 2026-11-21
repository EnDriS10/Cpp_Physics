#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "ceros.cpp"

double f(double x){
  return exp(x) - x*(x+5) -2;
}

double Df(double x){
  return exp(x) - 2*x - 5;
}

int main(){

  double eps = 1.0E-4, delta = 0.1;
  cout<<setprecision(4); cout<<fixed;
  int niter; double x0;  // x0 = valor inicial

  //Soluciones
  double x; // x = cero de Newton-Raphson
  bool sol1 = true, sol2 = true, sol3 = true;
  
  //Valores de x0 con mismo cero
  fstream f1,f2,f3;
  f1.open("cero1_vs_x0.txt",fstream::out);
  f2.open("cero2_vs_x0.txt",fstream::out);
  f3.open("cero3_vs_x0.txt",fstream::out);

  //Para cada cero, iteraciones en funcion de x0
  fstream fi1,fi2,fi3;
  fi1.open("cero1_iter_vs_x0.txt",fstream::out);
  fi2.open("cero2_iter_vs_x0.txt",fstream::out);
  fi3.open("cero3_iter_vs_x0.txt",fstream::out);

  /*Represento la funcion para ver donde caen los ceros aproximadamente y veo que hay tres ceros
  cero1 en x>-6 && x<-3
  cero2 en x>-2 && x<1
  cero3 en x>2 && x<5
  */
  
  x0 = -6;
  while(x0<5){

    x = newton_raphson(x0, eps, niter, f, Df);

    if(x>-6 && x<-3){

      if (sol1){cout<<"Solucion 1: "<<x<<endl; sol1=false;}
      f1<<x0<<"   "<<x<<endl;
      fi1<<x0<<"   "<<niter<<endl;
      
    } else if(x>-2 && x<1){

      if (sol2){cout<<"Solucion 2: "<<x<<endl; sol2=false;}
      f2<<x0<<"   "<<x<<endl;
      fi2<<x0<<"   "<<niter<<endl;
      
    } else if(x>2 && x<5) {

      if (sol3){cout<<"Solucion 3: "<<x<<endl; sol3=false;}
      f3<<x0<<"   "<<x<<endl;
      fi3<<x0<<"   "<<niter<<endl;
      
    }
    x0 = x0 + delta;
  }

  //Estudio de Solucion 3 para x0 = 2.3 (ver ex1_2.3.cpp)

}
