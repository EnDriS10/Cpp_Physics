#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;
const int n=2; // numero de EDOs de primer orden del sistema de ecuaciones diferenciales
double f1 (double t, double y[n]);
double f2 (double t, double y[n]);
double (*Af[n]) (double t, double y[n])={f1, f2}; // array de punteros a funciones 
void RK4(double (*Af[n])(double t, double y[n]), double t0, double tf, double h, double y[n], int n);
// y1 e y2 se agrupan en un vector y[], tal que y[0]=y1 e y[1]=y2
// Las funciones f1 y f2 se agrupan en un array de punteros a funciones Af que ahora lo pasamos como argumento a la funcion RK4
// Ojo. Ahora n no es el numero de puntos calculados

int main()
{   
double t0=0, tf=0.03, h=0.0001;
double y[n];
y[0]=10;
y[1]=0; // condiciones iniciales
cout << setprecision(10);
RK4(Af,t0,tf, h,y,n); // llamada a la funcion RK4
system("PAUSE");
return 0;
}

double f1(double t, double y[n])
{ return y[1];}


double f2(double t, double y[n])
{ double R=100, C=2E-6, L=0.5;
return (-(R/L)*y[1]-(1.0/(L*C))*y[0]);}

void RK4(double (*Af[n])(double t, double y[n]), double t0, double tf, double h, double y[n], int n)
{
  int j;
  // Hay que abrir el flujo en la funcion
  ofstream fsalida("resultados-forma2.dat");
  if (!fsalida)
    {cout << "No se puede abrir el archivo";
     system("PAUSE"); }
  double t=t0, k1[n], k2[n], k3[n], k4[n], yy[n];
  cout << t;
  fsalida << t;
    for (j=0; j<n; j++) 
    { cout << "   " << y[j];
      fsalida << "   " << y[j];
    }
    cout << endl;
    fsalida << endl;
   do {
    for (j=0; j<n; j++)    { k1[j]=h*Af[j](t,y);}
    for (j=0; j<n; j++)    { yy[j]=y[j]+0.5*k1[j];}
    for (j=0; j<n; j++)    { k2[j]=h*Af[j](t+0.5*h,yy);}
    for (j=0; j<n; j++)    { yy[j]=y[j]+0.5*k2[j];}
    for (j=0; j<n; j++)    { k3[j]=h*Af[j](t+0.5*h,yy); }
    for (j=0; j<n; j++)    { yy[j]=y[j]+k3[j];}
    for (j=0; j<n; j++)    { k4[j]=h*Af[j](t+h,yy);}
    // nueva aproximaci?n
    for (j=0; j<n; j++) 
    { y[j]=y[j] + (1.0/6.0)*(k1[j] + 2.0*k2[j] + 2.0*k3[j] + k4[j]);}
    t=t+h;
    cout << t;
    fsalida << t;
    for (j=0; j<n; j++) 
    { cout << "   " << y[j];
      fsalida << "   " << y[j];}
    cout << endl;
    fsalida << endl;
    } while (t<=(tf-h));
   fsalida.close();
}





