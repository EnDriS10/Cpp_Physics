#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include "ceros_2.3.cpp"

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

  //Estudio de Solucion 3 para x0 = 2.3
  fstream f23; f23.open("Sol3_x0-2.3.txt",fstream::out);
    x0 = 2.3;
    x = newton_raphson(x0, eps, niter, f, Df,f23);
    cout<<"Solucion 3: "<<x<<endl;
    f23.close();
    
}
