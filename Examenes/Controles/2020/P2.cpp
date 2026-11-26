#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;

double* gauss_seidel_solve_p2(double **A, double *b, double *x_lu, double *x_0,int n, double tol, int &iter);
double* jacobi_solve_p2(double **A, double *b, double *x_lu, double *x_0,int n, double tol, int &iter);

int main() {
	int dim= 5;	  int iter;	  double **A=gen_mat(A,dim,dim);	double *b= new double[dim]; double *x_0= new double[dim];
	
	double b_aux[dim] = { -1, 21,  43, 32, 55};
	double A_aux[dim][dim] = {
    { 12, -2,  1,  4, -0.5},
    {-1,  15, 4,  6, 7},
    { 9, 0.5,  12, 3, 1},
    { -3,  -6, 9,  24, 1},
    { 1,  -1, 3,  2, 8}};
	
	for (int i = 0; i < dim; i++){
		b[i] = b_aux[i]; x_0[i]=0;
    	for (int j = 0; j < dim; j++){
        	A[i][j] = A_aux[i][j];
        }
	}
	double *x_lu= lu_forma1_sol(A, b, dim);
	double *tol_arr = new double[dim];double *logtol_arr = new double[dim]; double *iter1_arr = new double[dim]; double *iter2_arr = new double[dim];
	
	for (int i = 0; i < dim; i++){
		tol_arr[i] = 1e-3*pow(0.1,i);
		double *x_jacobi= jacobi_solve_p2(A, b, x_lu, x_0,dim,  tol_arr[i], iter);			iter1_arr[i]=iter;
		double *x_gauss= gauss_seidel_solve_p2(A, b, x_lu, x_0,dim,  tol_arr[i], iter);		iter2_arr[i]=iter;
		logtol_arr[i]= log10(tol_arr[i]);
	}
	
	save_xy_file("iter1_v_log.dat", logtol_arr, iter1_arr, dim);
	save_xy_file("iter1_v_log.dat", logtol_arr, iter2_arr, dim);
	
	//print_vect(x_lu,dim,"LU");
	//print_vect(x_jacobi,dim,"Jacobi");
	//print_vect(x_gauss,dim,"GaussSeidel");
	
	return 0;
}

double* jacobi_solve_p2(double **A, double *b, double *x_lu, double *x_0,int n, double tol, int &iter) {
    // 1. Trabajamos con copias para no destruir las matrices originales del main
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    // 2. Intentar hacer la matriz diagonalmente dominante
    reorder_diagonals(M, vb, n);
	
	double *oldx = new double[n];
    double *newx = new double[n];
    
    // 3. Aproximación inicial: x_i^(0) = b_i / A_ii
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Jacobi no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = x_0[i];
    }

    double error = tol + 1.0;

    // 4. Bucle principal de Jacobi
    while (error > tol ) {
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
        double *rest = resta_vect(newx, x_lu, n);
        error = mod_vect(rest, n);
        delete[] rest;

        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        iter++;
    }
    
    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}

double* gauss_seidel_solve_p2(double **A, double *b, double *x_lu, double *x_0,int n, double tol, int &iter) {
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

        double *rest = resta_vect(newx, x_lu, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}
