#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <cstdio>

using namespace std;


double f(double phi, double tht){
	double k= sin(0.5*tht);
	return (2 / PI(10) ) * 1/ sqrt( 1- pow( k*sin(phi) ,2) );}
	

double I_trapecio(double (*f)(double, double), double a, double b, double tht) {
    return (b - a) / 2.0 * (f(a,tht) + f(b,tht));
}

double I_simpson13(double (*f)(double,double), double a, double b, double tht) {
    double h = (b - a) / 2.0;
    return h / 3.0 * (f(a,tht) + 4.0 * f(a + h,tht) + f(b,tht));
}

double I_simpson38(double (*f)(double,double), double a, double b, double x) {
    double h = (b - a) / 3.0;
    return 3.0 * h / 8.0 * (f(a,x) + 3.0 * f(a + h,x) + 3.0 * f(a + 2.0 * h,x) + f(b,x));
}

double I_trapecio_comp(double (*f)(double,double), double a, double b, int n, double x) {
    if (n < 1) { print_error_int("trapecio_comp_func: n debe ser >= 1", n); return MC_NAN; }
    double h = (b - a) / n;
    double suma = 0.5 * (f(a,x) + f(b,x));
    for (int i = 1; i < n; i++) suma += f(a + i * h,x);
    return h * suma;
}

double I_simpson13_comp(double (*f)(double,double), double a, double b, int n, double x) {
    if (n < 2) n = 2;
    if (n % 2 != 0) n++;
    double h = (b - a) / n;
    double suma = f(a,x) + f(b,x);
    for (int i = 1; i < n; i++) suma += ((i % 2 == 0) ? 2.0 : 4.0) * f(a + i * h,x);
    return h / 3.0 * suma;
}

double I_simpson38_comp(double (*f)(double,double), double a, double b, int n, double x) {
    if (n < 3) n = 3;
    if (n % 3 != 0) n += 3 - (n % 3);
    double h = (b - a) / n;
    double suma = f(a,x) + f(b,x);
    for (int i = 1; i < n; i++) suma += ((i % 3 == 0) ? 2.0 : 3.0) * f(a + i * h,x);
    return 3.0 * h / 8.0 * suma;
}

double I_gauss_legendre(double (*f)(double,double), double a, double b, int n, double th) {
    if (n < 1) { print_error_int("gauss_legendre_func: n debe ser >= 1", n); return MC_NAN; }
    double *x, *w;
    gauss_legendre_nodos(n, x, w);
    double mitad = (b - a) / 2.0, centro = (b + a) / 2.0, suma = 0.0;
    for (int i = 0; i < n; i++) suma += w[i] * f(mitad * x[i] + centro,th);
    delete[] x; delete[] w;
    return mitad * suma;
}
	

int main() {
	double* theta = linspace(0, deg2rad(150), 30); double I[10];	char nombre[30];

	for (int i=0; i<30; i++) {
	
	I[0]=I_trapecio(f, 0, 0.5*PI(10), theta[i]);
	I[1]=I_simpson13(f, 0, 0.5*PI(10), theta[i]);
	I[2]=I_simpson38(f, 0,0.5*PI(10), theta[i]);
	I[3]=I_trapecio_comp(f,  0,0.5*PI(10), 1e2 ,theta[i]);
	I[4]=I_simpson13_comp(f,  0,0.5*PI(10), 1e2 ,theta[i]);
	I[5]=I_simpson38_comp(f,  0,0.5*PI(10), 1e2 ,theta[i]);
	
	for (int j=0; j<=3; j++) {
		I[6+j]=I_gauss_legendre(f,0,0.5*PI(10), 3+i,theta[i]);
	}
	
	cout << "I =[Trapecio, Simpson13, Simpson38, Trapecio Comp, Simpson13 Comp, Simpson38 Comp, Gauss n=3 ,4 , 5, 6 ] "<<endl;
	print_vect(I, 9, "I");
	sprintf(nombre, "I_run_%d.dat", i);
	save_vector_file(nombre, I, 10);
	cout << " "<<endl;
	} 	
	

	return 0;
}
