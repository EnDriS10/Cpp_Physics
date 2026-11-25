#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

double k1= 10; double k2 = 20; double L1 = 1; double L2= 1; double D=1;
double m=0.1; double g=9.81;
	
double E(double* r, int n){
return 0.5*k1*pow( ( sqrt(r[0]*r[0] +r[1]*r[1]) - L1 ) ,2) + 0.5*k2*pow(( sqrt( (r[0]-D)*(r[0]-D) + r[1]*r[1]) - L2 ) ,2) - m*g*r[1];
}

double Fx(double* r, int n){return part_derv(E, r, n, 0);}
double Fy(double* r, int n){return part_derv(E, r, n, 1);}

int main() {
	int m= 2; double r0[] = {2, -2}; double (*Sist[m])(double*, int) = {Fx, Fy};
	
	int N; double* km = arange(0, 2, 20, N); double** A =gen_mat(A, N, 3);
	
	for (int i=0; i<N; i++) {
	k2= km[i]; 
	double *sol = newton_raphson_sys(Sist, r0, 2, 1e-10, 100);
	cout << i << "   ";
	print_vect(sol,m,"r_eq");
	cout<<endl;
	A[i][0] = k2; A[i][1] = sol[0] ;A[i][2] = sol[1];
	delete [] sol;
	} 
    
    save_mat_file("Posicion.dat", A, N, 3);
    delete [] km; del_mat(A, N);  
	return 0;
}
