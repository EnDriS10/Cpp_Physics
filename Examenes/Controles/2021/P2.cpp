#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;
double* jacobi_solve_iter(double **A, double *b, double *x_0, int n, double tol, int &iter);
double* gauss_seidel_solve_iter(double **A, double *b, double *x_0, int n, double tol, int &iter );


int main() {
	cout << setprecision(7);
	int dim =10; 	double **A = gen_mat(A, dim, dim);	double *b = new double[dim]; double *x0 = new double[dim];
	int iter1; int iter2 ; double *tol = new double[dim];  double *logtol = new double[dim];
	
    for (int i = 0; i < dim; i++) {
    	b[i]= i; x0[i] = 0; tol[i]=  1e-3*pow(0.1,i);  logtol[i]=log10(tol[i]);
        for (int j = 0; j < dim; j++) {
            if (i == j) A[i][j] = 100*(dim-i)*(dim-j) + i+j ;
            	else A[i][j] = i+j;
        }
    }
    
    //print_mat(A,dim,dim,"A");
    //print_vect(b,dim, "b");
    
    double *x_lu = lu_forma1_sol(A, b, dim);
    //print_vect(x_lu,dim, "Sol_LU");
    
    double *iter1_arr = new double[dim];	double *iter2_arr = new double[dim];
    //print_vect(tol,dim, "Tol");
    for (int i=0; i< dim; i++){
		double *x_jacobi = jacobi_solve_iter(A, b, x0,dim, tol[i] , iter1);
		double *x_gauss = gauss_seidel_solve_iter(A, b, x0,dim, tol[i] , iter2);
		iter1_arr[i]=iter1; iter2_arr[i]=iter2;
	}
    //print_vect(iter1_arr,dim,"iter1_arr");
    //print_vect(iter2_arr,dim,"iter2_arr");
    
    save_xy_file("iter1_arr.dat", logtol, iter1_arr, dim);
    save_xy_file("iter2_arr.dat", logtol, iter2_arr, dim);
    
	return 0;
}

double* jacobi_solve_iter(double **A, double *b, double *x_0, int n, double tol, int &iter) {
    // 1. Trabajamos con copias para no destruir las matrices originales del main
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    // 2. Intentar hacer la matriz diagonalmente dominante
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    // 3. Aproximación inicial
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Jacobi no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] =  x_0[i];
    }

    iter = 0;
    double error = tol + 1.0;

    // 4. Bucle principal de Jacobi
    while (error > tol) {
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Jacobi usa exclusivamente los valores de la iteración anterior oldx[j]
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * oldx[j];
                }
            }
        }

        // Calculamos error evaluando la norma euclidiana de la diferencia
        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;

        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        iter++;
    }

    
    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}

double* gauss_seidel_solve_iter(double **A, double *b, double *x_0, int n, double tol, int &iter ) {
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
        oldx[i] = x_0[i];
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
