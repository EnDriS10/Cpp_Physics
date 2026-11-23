#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

double** KK(double *k ,int n) {
    double **M;
    M =  zeros_mat(n,n);
    for (int i = 0; i < n; i++) {
    	if (i > 0){ M[i][i-1] = -k[i];}
    		if (i < n-1){ M[i][i] = k[i+1]+k[i];
					M[i][i+1] = -k[i+1];}
        }
    return M;
}

// Metodo QR con acumulacion de transformacion ortogonal Q_acum:
// Devuelve T (triangular/Schur) y por referencia Q_acum tal que (Q_acum^T) * A * Q_acum ˜ T.
double** qr_triang_q_mat(double **A, int n, double tol, int max_iter, bool usar_hess,
                           double **&Q_acum, int &iter_out) {
    double **T = coppy_mat(A, n, n);
    Q_acum = eye_mat(n);

    if (usar_hess && n > 2) {
        double *v = new double[n];
        for (int k = 0; k < n - 2; k++) {
            double norma = 0.0;
            for (int i = k + 1; i < n; i++) norma += T[i][k] * T[i][k];
            norma = sqrt(norma);
            if (norma == 0.0) continue;

            double alfa = (T[k + 1][k] > 0.0) ? -norma : norma;
            for (int i = 0; i < n; i++) v[i] = 0.0;
            v[k + 1] = T[k + 1][k] - alfa;
            for (int i = k + 2; i < n; i++) v[i] = T[i][k];

            double vv = 0.0;
            for (int i = k + 1; i < n; i++) vv += v[i] * v[i];
            if (vv == 0.0) continue;

            // T = P * T * P (con P simetrica e involutiva: P^T = P, P^2 = I)
            for (int j = 0; j < n; j++) {
                double s = 0.0;
                for (int i = k + 1; i < n; i++) s += v[i] * T[i][j];
                for (int i = k + 1; i < n; i++) T[i][j] -= 2.0 * s * v[i] / vv;
            }
            for (int i = 0; i < n; i++) {
                double s = 0.0;
                for (int j = k + 1; j < n; j++) s += T[i][j] * v[j];
                for (int j = k + 1; j < n; j++) T[i][j] -= 2.0 * s * v[j] / vv;
            }
            for (int i = k + 2; i < n; i++) T[i][k] = 0.0;

            // Q_acum = Q_acum * P  =>  (Q_acum^T) * A * Q_acum se mantiene igual a T
            for (int i = 0; i < n; i++) {
                double s = 0.0;
                for (int j = k + 1; j < n; j++) s += Q_acum[i][j] * v[j];
                for (int j = k + 1; j < n; j++) Q_acum[i][j] -= 2.0 * s * v[j] / vv;
            }
        }
        delete[] v;
    }

    iter_out = 0;
    while (iter_out < max_iter) {
        double bajo = 0.0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++) bajo += fabs(T[i][j]);
        if (bajo < tol) break;

        double **Q, **R;
        qr_givens_mat(T, n, Q, R);
        del_mat(T, n);
        T = prod_mat(R, Q, n, n, n, n);

        double **Q_next = prod_mat(Q_acum, Q, n, n, n, n);
        del_mat(Q_acum, n);
        Q_acum = Q_next;

        del_mat(Q, n);
        del_mat(R, n);
        iter_out++;
    }

    if (iter_out >= max_iter) {
        print_warning("qr_triang_q_mat alcanzo max_iter (posibles autovalores complejos o convergencia lenta).");
    }
    return T;
}

// Autovalores (vector evals) y autovectores (matriz evecs de n x n, columna j = autovector de evals[j])
// para una matriz genérica A de n x n.
double* qr_eig_vec(double **A, int n, double tol, int max_iter, bool usar_hess,
                   double **&evecs, int &iter_out) {
    double **Q_acum = NULL;
    double **T = qr_triang_q_mat(A, n, tol, max_iter, usar_hess, Q_acum, iter_out);

    double *evals = new double[n];
    for (int i = 0; i < n; i++) evals[i] = T[i][i];

    double **V_T = zeros_mat(n, n);

    // Para cada autovalor lambda = T[k][k], resolvemos (T - lambda*I) * v = 0 por sustitucion regresiva
    for (int k = 0; k < n; k++) {
        double lambda = evals[k];
        double *v = new double[n];
        for (int i = 0; i < n; i++) v[i] = 0.0;

        v[k] = 1.0; // Componente libre para evitar la solucion trivial nula

        // Filas por encima de k: sum_{j=i+1}^{k} (T[i][j] - delta_ij*lambda) * v[j] = -(T[i][k] - delta_ik*lambda)*v[k]
        for (int i = k - 1; i >= 0; i--) {
            double rhs = -T[i][k] * v[k];
            for (int j = i + 1; j < k; j++) {
                rhs -= T[i][j] * v[j];
            }
            double diag = T[i][i] - lambda;
            if (fabs(diag) < 1e-13) {
                // Autovalor repetido o casi degenerado: fijamos v[i] = 1.0 y seguimos hacia arriba
                v[i] = 1.0;
            } else {
                v[i] = rhs / diag;
            }
        }

        // Normalizar v
        double nrm = 0.0;
        for (int i = 0; i < n; i++) nrm += v[i] * v[i];
        nrm = sqrt(nrm);
        if (nrm > 0.0) {
            for (int i = 0; i < n; i++) v[i] /= nrm;
        }

        for (int i = 0; i < n; i++) V_T[i][k] = v[i];
        delete[] v;
    }

    // Transformar autovectores de T a la base original de A: evecs = Q_acum * V_T
    evecs = prod_mat(Q_acum, V_T, n, n, n, n);

    // Normalizar cada columna de evecs
    for (int j = 0; j < n; j++) {
        double nrm = 0.0;
        for (int i = 0; i < n; i++) nrm += evecs[i][j] * evecs[i][j];
        nrm = sqrt(nrm);
        if (nrm > 0.0) {
            for (int i = 0; i < n; i++) evecs[i][j] /= nrm;
        }
    }

    del_mat(V_T, n);
    del_mat(Q_acum, n);
    del_mat(T, n);
    return evals;
}


int main() {
	int n=4;
	double **M = prod_esc_mat(eye_mat(n), 4e3, n, n) ; double **K = zeros_mat(n,n); double **Kr = ones_mat(n,n); double **U = zeros_mat(n,n);
	double *k = prod_esc_vect(ones_vect(n), 5e3 ,n);
	double *L = new double[n]; int iter = 0 ;
	
	K= KK(k ,n);
	Kr=prod_mat(inv_lu(M, n), K, n, n,n,n);
	
	L = qr_eig_vec(Kr, n, 1e-10, 2e3, true, U, iter);

    print_mat(K, n, n, "Kr ");               
	print_mat(U, n, n, "EigenVectors");
	print_vect(L, n, "eigenAguacates");

	del_mat(M, n); del_mat(K, n); del_mat(Kr, n); del_mat(U, n);
	delete[] k; delete[] L;
	
	return 0;
}
