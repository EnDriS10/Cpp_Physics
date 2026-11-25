#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

int n=100;

double** tridiag_mat(int n) {
    double **M;
    M = zeros_mat(n,n);
    for (int i = 0; i < n; i++) {  
			if (i>1 && i<n-1) {M[i][i-1] = -1.0;}
			if (i>0 && i<n-2) {M[i][i+1] = -1.0;}
			
			if (i==0 || i==n-1) {M[i][i] = 1.0;}
			else M[i][i] = 2.0;
	}
    return M;
}

int jacobi_eig_iters(double **A, int n, double *&L, double **&U, bool calc_autoval, bool calc_autovec, bool ordenar, double tol, int max_iter, double *Trz, int &Num) {

    L = NULL;
    U = NULL;
    if (!calc_autoval && !calc_autovec) {
        print_warning("jacobi_eig: no se pidieron ni autovalores ni autovectores, no hay nada que calcular.");
        return 0;
    }
    if (!is_symmetric_mat(A, n, 1e-10)) {
        print_error("jacobi_eig: la matriz debe ser simetrica");
        return -1;
    }
    double **B = coppy_mat(A, n, n);
    double **V = calc_autovec ? eye_mat(n) : NULL;
    int n_rot = 0; Num =0;

    while (n > 1) {
        // Paso 3: maximo (en valor absoluto) por encima de la diagonal
        int i = 0, j = 1;
        double mx = 0.0;
        for (int ib = 0; ib < n; ib++)
            for (int jb = ib + 1; jb < n; jb++)
                if (fabs(B[ib][jb]) > mx) { mx = fabs(B[ib][jb]); i = ib; j = jb; }
        if (mx < tol) break;
        if (n_rot >= max_iter) { print_warning("jacobi_eig alcanzo max_iter sin converger plenamente."); break; }

        // Paso 4: angulo theta (ec. [8])
        double theta;
        if (fabs(B[i][i] - B[j][j]) < 1e-14 * (fabs(B[i][i]) + fabs(B[j][j])) + 1e-300) theta = atan(1.0);  // pi/4
        else theta = 0.5 * atan(2.0 * B[i][j] / (B[i][i] - B[j][j]));
        double si = sin(theta), co = cos(theta);

        // Paso 5: V = V*R (sin construir R), solo si se piden los autovectores
        if (V != NULL) {
            for (int k = 0; k < n; k++) {
                double vki = V[k][i];
                V[k][i] = vki * co + V[k][j] * si;
                V[k][j] = -vki * si + V[k][j] * co;
            }
        }
        if ( n_rot%100 == 0 ) { double *TT=get_diag_mat(B,n); Trz[Num] = sum_elems(TT, n);Num++; delete [] TT;}
        
        // Paso 6: B = R^T * B * R (ecs. [7b] a [7e])
        for (int k = 0; k < n; k++) {
            if (k != i && k != j) {
                double bki = B[k][i];
                B[k][i] = bki * co + B[k][j] * si;
                B[k][j] = -bki * si + B[k][j] * co;
                B[i][k] = B[k][i];
                B[j][k] = B[k][j];
            }
        }
        
        
        double aii = B[i][i], ajj = B[j][j], aij = B[i][j];
        B[i][i] = aii * co * co + ajj * si * si + 2.0 * aij * si * co;
        B[j][j] = aii * si * si + ajj * co * co - 2.0 * aij * si * co;
        B[i][j] = 0.0;
        B[j][i] = 0.0;
		n_rot++;
	}
    double *Ld = get_diag_mat(B, n);       
	del_mat(B, n);
    if (ordenar) sort_eig(Ld, V, n);
    U = V;
    if (calc_autoval) L = Ld; else delete[] Ld;
    return n_rot;
}
int main() {
	int max_iter = 1e5;
	double** M =tridiag_mat(n); double *L;double *Trz = new double [max_iter/n]; double **U; int NUM;
    int n_rot= jacobi_eig_iters(M, n, L, U, true, true, false, 1e-10, max_iter,Trz,NUM);
 	double* w=sqrt_vect(L, n);
 	
        //print_mat(M, n, n, "Matriz M");
        //print_vect(L, n, "Autovalores");
        print_vect(w, n, "Modos de Vibracion");
        //print_vect(Trz, NUM, "Traza");
        
        //print_mat(U, n, n, "Autovectores (columnas)");
 		//cout<<endl<<n_rot<<endl;
 		//cout<<endl<<NUM<<endl;
 		double *x =new double[NUM]; for ( int i = 0; i<NUM ; i++){ x[i] = 100*i;} 
 		save_xy_file("Traza.dat", x, Trz, NUM);
 		
 	delete [] L; delete [] Trz; delete [] w; delete [] x;
 	del_mat(M,n); del_mat(U,n);
 	
 		
	return 0;
}
