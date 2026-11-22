// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.3
// Metodo QR
// ============================================================================
// Factorizacion QR (Gram-Schmidt y rotaciones de Givens) e iteracion QR para obtener autovalores.
//
// Funciones (4): qr_gs_mat, qr_givens_mat, qr_triang_mat, qr_eig
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Factorización QR por Gram-Schmidt modificado
// Descripción: Descompone A = Q*R con Q ortogonal (columnas ortonormales) y R triangular superior. Q y R se devuelven por referencia (new[]).
// Necesita que las columnas de A sean linealmente independientes (A invertible).

void qr_gs_mat(double **A, int n, double **&Q, double **&R) {
    /*
    Ejemplo de uso:
        double **Q, **R;
        qr_gs_mat(A, n, Q, R);   // A = Q*R
    */
    Q = zeros_mat(n, n);
    R = zeros_mat(n, n);
    double *v = new double[n];
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) v[k] = A[k][j];
        for (int i = 0; i < j; i++) {
            double r = 0.0;
            for (int k = 0; k < n; k++) r += Q[k][i] * v[k];
            R[i][j] = r;
            for (int k = 0; k < n; k++) v[k] -= r * Q[k][i];
        }
        double nrm = 0.0;
        for (int k = 0; k < n; k++) nrm += v[k] * v[k];
        nrm = sqrt(nrm);
        if (nrm < 1e-14) {
            print_error("qr_gs_mat: columnas linealmente dependientes");
            del_mat(Q, n); del_mat(R, n); delete[] v;
            Q = NULL; R = NULL;
            return;
        }
        R[j][j] = nrm;
        for (int k = 0; k < n; k++) Q[k][j] = v[k] / nrm;
    }
    delete[] v;
}

// Factorización QR por rotaciones (Givens)
// Descripción: Hace cero los elementos por debajo de la diagonal uno a uno con rotaciones P_k (c = a_jj/d, s = a_ij/d, d = sqrt(a_jj^2 + a_ij^2)).
// R = P_m*...*P_1*A y Q = P_1^T*...*P_m^T, de modo que A = Q*R. Q y R se devuelven por referencia (new[]). Funciona para cualquier A (no necesita ser invertible).

void qr_givens_mat(double **A, int n, double **&Q, double **&R) {
    /*
    Ejemplo de uso:
        double **Q, **R;
        qr_givens_mat(A, n, Q, R);   // A = Q*R
    */
    R = coppy_mat(A, n, n);
    Q = eye_mat(n);
    for (int j = 0; j < n - 1; j++) {
        for (int i = j + 1; i < n; i++) {
            if (R[i][j] == 0.0) continue;
            double d = sqrt(R[j][j] * R[j][j] + R[i][j] * R[i][j]);
            double c = R[j][j] / d, s = R[i][j] / d;
            for (int k = 0; k < n; k++) {                  // filas j e i de R
                double rj = R[j][k], ri = R[i][k];
                R[j][k] = c * rj + s * ri;
                R[i][k] = -s * rj + c * ri;
            }
            for (int k = 0; k < n; k++) {                  // columnas j e i de Q
                double qj = Q[k][j], qi = Q[k][i];
                Q[k][j] = c * qj + s * qi;
                Q[k][i] = -s * qj + c * qi;
            }
            R[i][j] = 0.0;
        }
    }
}

// Método QR: matriz triangular superior semejante a A
// Descripción: Itera A(i) = Q(i)*R(i) -> A(i+1) = R(i)*Q(i) (misma traza y autovalores) hasta que la suma de |elementos bajo la diagonal| sea < tol.
// Si 'usar_hess' es true se aplica antes la transformacion de Hessenberg (converge con menos trabajo por iteracion). Devuelve la matriz (new[]) e 'iter_out' iteraciones.
// Con autovalores complejos no converge a triangular (quedan bloques 2x2).

double** qr_triang_mat(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out) {
    /*
    Ejemplo de uso:
        int it;
        double **T = qr_triang_mat(A, n, 1e-12, 1000, true, it);   // diagonal de T = autovalores
    */
    double **T = usar_hess ? hessenberg_householder_mat(A, n) : coppy_mat(A, n, n);
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
        del_mat(Q, n); del_mat(R, n);
        iter_out++;
    }
    if (iter_out >= max_iter) print_warning("qr_triang_mat alcanzo max_iter (posibles autovalores complejos o poca convergencia).");
    return T;
}

// Autovalores de una matriz genérica: Método QR
// Descripción: Devuelve (new[]) los autovalores de A, que son los elementos diagonales de la matriz triangular obtenida con qr_triang_mat.

double* qr_eig(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out) {
    /*
    Ejemplo de uso:
        // A = [7 8 6 6; 1 6 -1 -2; 1 -2 5 -2; 3 4 3 4]  -> autovalores 10, 7, 4, 1
        int it;
        double *L = qr_eig(A, 4, 1e-12, 1000, true, it);
        print_vect(L, 4, "Autovalores");
    */
    double **T = qr_triang_mat(A, n, tol, max_iter, usar_hess, iter_out);
    double *L = get_diag_mat(T, n);
    del_mat(T, n);
    return L;
}

