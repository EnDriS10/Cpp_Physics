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

int main() {
	int N_O = count_lines_file("OKLL.dat"); int N_C = count_lines_file("CKLL.dat") ; int N_N = count_lines_file("NKLL.dat"); int N_B = count_lines_file("BKLL.dat");
	double* x_O= zeros_vect(N_O); double* x_C= zeros_vect(N_C); double* x_N= zeros_vect(N_N); double* x_B= zeros_vect(N_B);
	double* y_O= zeros_vect(N_O); double* y_C= zeros_vect(N_C); double* y_N= zeros_vect(N_N); double* y_B= zeros_vect(N_B);
	double S_N = 1.218; double S_O=1.257; double S_C=0.614; double S_B=0.889;

	read_xy_file("OKLL.dat", x_O, y_O, N_O);  read_xy_file("CKLL.dat", x_C, y_C, N_C);  read_xy_file("NKLL.dat", x_N, y_N, N_N);  read_xy_file("BKLL.dat", x_B, y_B, N_B);
	
	double I_O= simpson13_vect(x_O,y_O,N_O); double I_C= simpson13_vect(x_C,y_C,N_C); double I_N= simpson13_vect(x_N,y_N,N_N); double I_B= simpson13_vect(x_B,y_B,N_B);
	
	double k_O = I_O/S_O; double k_N= I_N/S_N; double k_C = I_C/S_C; double k_B = I_B/S_B; double kT = k_O + k_B + k_C + k_N;
	double C_O = k_O/kT; double C_N = k_N/kT; double C_C = k_C/kT; double C_B = k_B/kT;
	
	cout<<"Las 'concentraciones' de O, C, N y B respectivamente son "<<C_O <<" , "<<C_C <<" , "<<C_N <<" ,y "<<C_B<<endl;
	//cout<<"Las estequiometria de O, C, N y B respectivamente son "<< 1/(C_C*C_N*C_B) <<" , "<< 1/(C_O*C_N*C_B) <<" , "<< 1/(C_C*C_O*C_B) <<" ,y "<<1/(C_C*C_N*C_O)<<endl;
	cout<<"Las estequiometria de C:O , N:O y B:O respectivamente son "<< C_C/C_O <<" , "<< C_N/C_O <<" ,y "<<C_B/C_O<<endl;
	cout<<"Las estequiometria de O:C , N:C y B:C respectivamente son "<< C_O/C_C <<" , "<< C_N/C_C <<" ,y "<<C_B/C_C<<endl;
	cout<<"Las estequiometria de O:N , C:N y B:N respectivamente son "<< C_O/C_N <<" , "<< C_C/C_N <<" ,y "<<C_B/C_N<<endl;
	
	cout<<"(O_"<<(3/C_N)*C_O<<")(C_"<<(3/C_N)*C_C<<")"<<"(N_"<<(3/C_N)*C_N<<")"<<"(B_"<<(3/C_N)*C_B<<"). Que es aproximadamente O5C6N3B4"<<endl;

	delete[] x_O; delete[] x_C;	delete[] x_N; delete[] x_B; delete[] y_O; delete[] y_C; delete[] y_N; delete[] y_B;			
	
	return 0;
}
