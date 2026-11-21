#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "matrix_2.h"
using namespace math;

#include "LU.cpp"
#include "leq_modificado.cpp"

int main(){
  cout<<setprecision(12); cout<<fixed;
  const int n = 5;
  matrix<double> A(n,n), b(n,1), x(n,1), x0(n,1);
  fstream Af, bf;
  Af.open("A.txt",fstream::in);
  bf.open("b.txt",fstream::in);
  Af>>A; bf>>b; Af.close(); bf.close();

  cout<<"Comprobacion. Solucion exacta \n";
  x = (!A)*b;
  cout<<x<<endl;
  cout<<"Solucion LU \n";
  matrix<double> x_LU(n,1);
  x_LU = LU(A,b);
  cout<<x_LU<<endl;


  fstream fJiter; fJiter.open("J_iter.txt",fstream::out);
  fstream fJlog; fJlog.open("J_log.txt",fstream::out);
  double epsilon = 1.0E-3, factor = 10, eps_min=1E-12; int niteraciones;
  x0.Null();
  while(epsilon >= eps_min){
    x = Jacobi(A,b,x0,epsilon,niteraciones);
    fJiter<<epsilon<<"  "<<niteraciones<<endl;
    fJlog<<log10(epsilon)<<"  "<<niteraciones<<endl;
    epsilon = epsilon/factor;
  }
  fJiter.close();
  fJlog.close();

  fJiter.open("GS_iter.txt",fstream::out);
  fJlog.open("GS_log.txt",fstream::out);
  epsilon = 1.0E-3; factor = 10; eps_min=1E-12;
  x0.Null();
  while(epsilon >= eps_min){
    x = GS(A,b,x0,epsilon,niteraciones);
    fJiter<<epsilon<<"  "<<niteraciones<<endl;
    fJlog<<log10(epsilon)<<"  "<<niteraciones<<endl;
    epsilon = epsilon/factor;
  }
  fJiter.close();
  fJlog.close();

  fJiter.open("J_LU_iter.txt",fstream::out);
  fJlog.open("J_LU_log.txt",fstream::out);
  epsilon = 1.0E-3; factor = 10; eps_min=1E-12;
  x0.Null();
  while(epsilon >= eps_min){
    x = JacobiLU(A,b,x0,epsilon,niteraciones,x_LU);
    fJiter<<epsilon<<"  "<<niteraciones<<endl;
    fJlog<<log10(epsilon)<<"  "<<niteraciones<<endl;
    epsilon = epsilon/factor;
  }
  fJiter.close();
  fJlog.close();

  fJiter.open("GS_LU_iter.txt",fstream::out);
  fJlog.open("GS_LU_log.txt",fstream::out);
  epsilon = 1.0E-3; factor = 10; eps_min=1E-12;
  x0.Null();
  while(epsilon >= eps_min){
    x = GSLU(A,b,x0,epsilon,niteraciones,x_LU);
    fJiter<<epsilon<<"  "<<niteraciones<<endl;
    fJlog<<log10(epsilon)<<"  "<<niteraciones<<endl;
    epsilon = epsilon/factor;
  }
  fJiter.close();
  fJlog.close();

  //Metodo de Jacobi
  cout<<"Metodo de Jacobi \n";
  x = Jacobi(A,b,x0,epsilon,niteraciones);
  cout<<"x = \n"<<x<<"\n\n  Num itera = "<<niteraciones<<endl;

  //Metodo de GS
  cout<<"Metodo de GS \n";
  x = GS(A,b,x0,epsilon,niteraciones);
  cout<<"x = \n"<<x<<"\n\n  Num itera = "<<niteraciones<<endl;

}
