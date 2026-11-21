#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;
// const int n=2; // numero de EDOs de primer orden del sistema de ecuaciones diferenciales
double f1(double t,double y1,double y2);
double f2(double t,double y1,double y2);
// y1=V y y2=dV/dt
// no agrupamos y1 e y2 en un vector
// Tampoco agrupamos f1 y f2 en un array de punteros a funciones
void RK4(double *t, double *y1, double *y2, double h, int n);
//Se podrian haber pasado tambi?n como argumentos de la funci?nn RK4 las funciones f1 y f2
// pero para este caso particular no haria falta. Son funciones accesibles desde RK4
int main()
{ 
double *t,*y1,*y2;  
double t0=0, tf=0.03, h=0.0001;
int n=(tf-t0)/h+1;
t=new double[n+1];
y1=new double[n+1];
y2=new double[n+1];
t[0]=0;
y1[0]=10;
y2[0]=0; // condiciones iniciales
h=0.0001;
cout << setprecision(10);
for(int i=1; i<=n ;i++){t[i]=t[0]+h*i; }
ofstream fsalida("resultados-forma1.dat");
fsalida << setprecision(10);
RK4(t,y1,y2,h,n); // llamada a la funcion RK4
for(int i=0; i<=n-1 ;i++){
cout<<t[i]<< " " << y1[i] << " "<<y2[i]<<endl;
fsalida << t[i]<< " " << y1[i] << " "<<y2[i]<<endl;}
fsalida.close();
system("PAUSE");
return 0;
}
void RK4(double *t, double *y1, double *y2, double h, int n)
{
double k11,k21,k31,k41,k12,k22,k32,k42;
for(int i=0; i<n-1 ;i++)
{   k11= h*f1(t[i],y1[i],y2[i]);
	k12= h*f2(t[i], y1[i], y2[i]);
	k21= h*f1(t[i]+0.5*h, y1[i] +0.5*k11, y2[i] +0.5*k12);
	k22= h*f2(t[i]+0.5*h, y1[i] +0.5*k11, y2[i] +0.5*k12);
	k31= h*f1(t[i]+0.5*h, y1[i] +0.5*k21, y2[i] +0.5*k22);
	k32= h*f2(t[i]+0.5*h, y1[i] +0.5*k21, y2[i] +0.5*k22);
	k41= h*f1(t[i]+h, y1[i]+k31, y2[i]+k32);
	k42= h*f2(t[i]+h, y1[i]+k31, y2[i]+k32);
    y1[i+1]=y1[i]+(k11+2.0*k21+2.0*k31+k41)/6.0; 
    y2[i+1]=y2[i]+(k12+2.0*k22+2.0*k32+k42)/6.0;} 
    } 

double f1(double t, double y1,double y2)
{ return y2;}

double f2(double t, double y1, double y2)
{ double R=100, C=2E-6, L=0.5;
return (-(R/L)*y2-(1.0/(L*C))*y1);}

