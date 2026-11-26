#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;

double* gauss_seidel_solve_p2(double **A, double *b, double *x_lu, double *x_0,int n, double tol, int &iter);
double* jacobi_solve_p2(double **A, double *b, double *x_lu, double *x_0,int n, double tol, int &iter);

int main() {
    int dim= 18; double **M=gen_mat(M,dim,dim); double *b= new double[dim]; double *x0= new double[dim];  int iter;
	
	for (int i = 0; i < dim; i++) {
		b[i]=i; x0[i]=0;
        for (int j = 0; j < dim; j++) {
            if (i == j) {M[i][j] = 18.0;} 
            else M[i][j] = 1.0;
        }
    }
    double *x_lu = lu_forma1_sol(M, b, dim);
    
    int mm= 10;
    double *tol_arr = new double[mm];double *logtol_arr = new double[mm]; double *iter1_arr = new double[mm]; double *iter2_arr = new double[mm];
	
	for (int i = 0; i < mm; i++){
		tol_arr[i] = 1e-3*pow(0.1,i);
		double *x_jacobi= jacobi_solve_p2(M, b, x_lu, x0,dim,  tol_arr[i], iter);			iter1_arr[i]=iter;
		double *x_gauss= gauss_seidel_solve_p2(M, b, x_lu, x0,dim,  tol_arr[i], iter);		iter2_arr[i]=iter;
		logtol_arr[i]= log10(tol_arr[i]);
	}
	
	save_xy_file("iter1_v_log.dat", logtol_arr, iter1_arr, mm);
	save_xy_file("iter2_v_log.dat", logtol_arr, iter2_arr, mm);
	
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
