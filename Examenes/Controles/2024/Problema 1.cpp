#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
const double PI = 4.0*atan(1.0);
const double e = 0.9672671; 
const double T = 75.9600;     //años
const double t0 = 1986.1113;  //años
const double dt = T/100.;
double f(double x, double t);
double df(double x);
double newton(double (*f) (double,double), double (*fprima) (double), double x0, double t, double tolerancia);

int main(){
  cout << setprecision(12);
  double raiz;
  double tolerancia=1E-8;
  double t = 1986.2491;
  // Elegimos E0 en el apartado (a) representando la función f(E)=E-e*sin(E)-M(t=t0)
  double E0 = 0.25;
  cout << "E(t="<< t << ") = " << newton(f,df,E0,t,tolerancia)<< endl;
  ofstream fsalida("resultados.dat");
	if (!fsalida)
    	{cout << "No se puede abrir el archivo";
    return 1;}
    fsalida << setprecision(12); 
    cout << "t, E(t)" << endl;
    fsalida << "t, E(t)" << endl;
    t=t0;
    E0=0;
    raiz=E0;
    int i = 0;
    do{
      E0 = raiz;
      raiz=newton(f,df,E0,t,tolerancia);
      cout << t << " " << raiz << endl;
      fsalida << t << " " << raiz << endl;
      ++i;
      t = t0 + i*dt;
    }while (t<=t0+T);

    fsalida.close(); 
 
  return 0;
}

double f(double x, double t){return x - e*sin(x) - 2*PI*(t-t0)/T;}

double df(double x){return (1 - e*cos(x));}

double newton(double (*f) (double,double), double (*fprima) (double), double x0, double t, double tolerancia)
{
double x1;
int contador=0;
do { 	
   if ((f(x0,t) !=0) && ( fprima(x0) !=0)) {
        x1 = x0 -(f(x0,t)/fprima(x0));
        x0 = x1; 
       	contador=contador+1;
	}
		else
			break;
} while (fabs(f(x1,t)) > tolerancia);
return x1;
}
