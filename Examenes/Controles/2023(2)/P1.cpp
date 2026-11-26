#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;

double a_CO2= 0.401; double b_CO2= 42.7e-6; double N_CO2= 1e3;
double T=300; double P =3.5e7; double k = 1.3806503e-23;

double f1(double V){return ( P + a_CO2*pow( (N_CO2/V) ,2) )*( V - N_CO2*b_CO2 ) - k*N_CO2*T;}
double* gauss_seidel_solve_p2(double **A, double *b, double *x0, int n, double tol, int &iter );

int main() {
	double V = biseccion(f1, 0, 1 , 1e-12, 1e-12 , 1e6);
	cout<<"El Volumen que toma CO2 es "<<V<<" m^3"<<endl;
	
	int dim=3; double **A = gen_mat(A,dim,dim); double *b= new double[dim]; double *x0 = new double[dim];
	int iter;	double b_aux[dim]={ 0, 1260,  756};
	double A_aux[dim][dim] = {
    {1.05,    -1.0,    0.00},
    {0.1667, 0.6667, 0.3333},
    {0.3333, 0.1667, 0.6667}};
    
	for (int i = 0; i < dim; i++){
		b[i]=b_aux[i]; x0[i]=1000;
    	for (int j = 0; j < dim; j++){
        	A[i][j] = A_aux[i][j];
    	}
	}
	
	double* X_r = gauss_seidel_solve_p2(A, b, x0,dim, 1e-4, iter );
	cout<<"El numero de juguetes rojos, azules y amarillos respectivamente es";
	print_vect(X_r,dim," "); X_r = round_vect(X_r, dim); cout<<"O sea aproximadamente "; print_vect(X_r,dim," ");
	cout<<endl;
	return 0;
}

double* gauss_seidel_solve_p2(double **A, double *b, double *x0, int n, double tol, int &iter ) {
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Gauss-Seidel no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = x0[i];
        newx[i] = oldx[i];
    }

    iter = 0;
    double error = tol + 1.0;

    while (error > tol) {
        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Gauss-Seidel usa newx[j] porque el valor se actualiza inmediatamente
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * newx[j]; 
                }
            }
        }

        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}
