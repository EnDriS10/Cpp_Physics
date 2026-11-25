#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;

double e = 0.9672671; double T= 75.9600; double t0 = 1986.1113; double tr= 1986.2491;
double Err = 1e-10; int N=1e3;

double f1(double E){return ((2*PI(10)*(tr-t0))/ T) - E +e*sin(E);}
double df1(double E){return deriv_cent_5p(f1, E, Err);}

int main() {
	cout << setprecision(7);
	
	// =============== INCISO A ================
	double r= newton(f1, df1,0, Err, Err,1e3);
	// =============== INCISO B ================
	double* E_arr = zeros_vect(N); double *t = new double [N]; t[0]=t0;
    for ( int i = 1; i<N+1 ; i++){
		t[i] = t0 + (i * T)/N;
		tr = t[i];
		E_arr[i]= newton(f1, df1,E_arr[i-1], Err, Err,1e3);
		}   
	
	save_xy_file("E(t).dat", t, E_arr, N);
	delete [] E_arr; delete [] t;
	
	return 0;
}
