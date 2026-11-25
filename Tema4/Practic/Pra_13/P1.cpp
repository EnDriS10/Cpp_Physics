#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

double* deriv_vect_(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *dy = deriv_vect_5p(x_O, y_O, 75);
    */
    if (n < 5) { print_error_int("deriv_vect_5p: se necesitan al menos 5 puntos", n); return NULL; }
    int m = n - 1;                        // numero de subintervalos
    double h = (x[m] - x[0]) / m;         // paso calculado automaticamente desde x

    for (int i = 0; i < m; i++) {
        if (fabs((x[i + 1] - x[i]) - h) > 1e-6 * fabs(h)) {
            print_warning("deriv_vect_5p: los puntos x no son equiespaciados.");
            break;
        }
    }

    double *d = new double[n];
    d[0] = (-25.0 * y[0] + 48.0 * y[1] - 36.0 * y[2] + 16.0 * y[3] - 3.0 * y[4]) / (12.0 * h);
    d[n - 1] = (25.0 * y[n - 1] - 48.0 * y[n - 2] + 36.0 * y[n - 3] - 16.0 * y[n - 4] + 3.0 * y[n - 5]) / (12.0 * h);
    d[1] = (y[2] - y[0]) / (2.0 * h);
    d[n - 2] = (y[n - 1] - y[n - 3]) / (2.0 * h);
    for (int i = 2; i < n - 2; i++) d[i] = (y[i - 2] - 8.0 * y[i - 1] + 8.0 * y[i + 1] - y[i + 2]) / (12.0 * h);
    return d;
}

double fs(double t){ return -70 + 7*t +70*exp(-t/10);}
double fv(double t){ return 7 - 7*exp(-t/10);}
double fa(double t){ return 0.7*exp(-t/10);}

int main() {
	int N=500; double* t = new double [N]; double* s = new double [N];
	double * v_num =zeros_vect(N); double * a_num =zeros_vect(N);
	double* v = new double [N];double* a = new double [N]; double* Err_v = new double [N]; double* Err_a = new double [N];
	
	read_xy_file("distancia.dat", t, s, N);
	v_num= deriv_vect_(t,s, 500); a_num= deriv_vect_(t,v_num, 500);
	
  	for ( int i = 0; i<N ; i++){
		v[i] = fv(t[i]);	a[i] = fa(t[i]);
		Err_v[i] = fabs( (v_num[i]-v[i])/(v_num[i]) );
		Err_a[i] = fabs( (a_num[i]-a[i])/(a_num[i]) );
		} 
	
	save_vector_file("Err_v.dat", Err_v, N);
	save_vector_file("Err_a.dat", Err_a, N);
	save_xy_file("Velocidad_num.dat", t, a_num, N);
	save_xy_file("Aceleracion_num.dat", t, a_num, N);
	
	delete[] t;		delete[] s;		delete[] v_num;    delete[] a_num;    delete[] v;    delete[] a;     delete[] Err_v;    delete[] Err_a;
	return 0;
}
