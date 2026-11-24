#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

double simpson13_vect(double *x, double *y, int n_puntos) {
    /*
    Ejemplo de uso:
        double I = simpson13_comp_vect(x_O, y_O, 75);   // 74 subintervalos
    */
    if (n_puntos < 2) { print_error_int("simpson13_comp_vect: se necesitan al menos 2 puntos", n_puntos); return MC_NAN; }
    int m = n_puntos - 1;                 // numero de subintervalos
    double h = (x[m] - x[0]) / m;         // paso calculado automaticamente desde x

    for (int i = 0; i < m; i++) {
        if (fabs((x[i + 1] - x[i]) - h) > 1e-6 * fabs(h)) {
            print_warning("simpson13_comp_vect: los puntos x no son equiespaciados.");
            break;
        }
    }

    int ms = m - (m % 2);                 // subintervalos tratados con Simpson
    double res = 0.0;
    if (ms > 0) {
        double suma = y[0] + y[ms];
        for (int i = 1; i < ms; i++) suma += ((i % 2 == 0) ? 2.0 : 4.0) * y[i];
        res = h / 3.0 * suma;
    }
    if (m % 2 == 1) res += (x[m] - x[m - 1]) * (y[m - 1] + y[m]) / 2.0;
    return res;
}

double trapecio_comp_vect(double *x, double *y, int n_puntos) {
    /*
    Ejemplo de uso:
        double I = trapecio_comp_vect(x_O, y_O, 75);   // 74 subintervalos
    */
    if (n_puntos < 2) { print_error_int("trapecio_comp_vect: se necesitan al menos 2 puntos", n_puntos); return MC_NAN; }
    int m = n_puntos - 1;                 // numero de subintervalos
    double h = (x[m] - x[0]) / m;         // paso calculado automaticamente desde x

    for (int i = 0; i < m; i++) {
        if (fabs((x[i + 1] - x[i]) - h) > 1e-6 * fabs(h)) {
            print_warning("trapecio_comp_vect: los puntos x no son equiespaciados.");
            break;
        }
    }

    double suma = 0.5 * (y[0] + y[m]);
    for (int i = 1; i < m; i++) suma += y[i];
    return h * suma;
}

int main() {
	int N_O = count_lines_file("O1s.dat"); int N_Al = count_lines_file("Al2p.dat") ; int N_C = count_lines_file("C1s.dat");
	double* x_O= zeros_vect(N_O); double* x_Al= zeros_vect(N_Al); double* x_C= zeros_vect(N_C);
	double* y_O= zeros_vect(N_O); double* y_Al= zeros_vect(N_Al); double* y_C= zeros_vect(N_C);
	double S_Al = 0.193; double S_O=0.711; double S_C=0.296;
	
	read_xy_file("O1s.dat", x_O, y_O, N_O);		read_xy_file("Al2p.dat", x_Al, y_Al, N_Al);		read_xy_file("C1s.dat", x_C, y_C, N_C);
	
	double I_O= simpson13_vect(x_O,y_O,N_O); double I_Al= simpson13_vect(x_Al,y_Al,N_Al); double I_C= simpson13_vect(x_C,y_C,N_C);
	
	double I_O_trapecio= trapecio_comp_vect(x_O,y_O,N_O); 
	double I_Al_trapecio= trapecio_comp_vect(x_Al,y_Al,N_Al); 
	double I_C_trapecio= trapecio_comp_vect(x_C,y_C,N_C);
	
	double k_O = I_O/S_O; double k_Al= I_Al/S_Al; double k_C = I_C/S_C; double kT = k_O + k_Al + k_C;
	double C_O = k_O/kT; double C_Al = k_Al/kT; double C_C = k_C/kT;
	
	cout<<"Las 'concentraciones' de O, Al, y C respectivamente son "<<C_O <<" , "<<C_Al <<" ,y "<<C_C<<endl;
	cout<<"(Al_"<<C_Al<<")(O_"<<C_O<<"). Por tanto "<<"AlO_"<<C_O/C_Al<<" Que es aproximadamente Al2O3"<<endl;
	
	return 0;
}
