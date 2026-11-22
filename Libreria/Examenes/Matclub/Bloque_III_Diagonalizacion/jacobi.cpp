// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.2
// Diagonalizacion de matrices simetricas: Metodo de Jacobi
// ============================================================================
// Rotaciones de Jacobi para obtener autovalores y autovectores de matrices simetricas, y ordenacion de los resultados.
//
// Funciones (2): jacobi_eig, sort_eig
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Diagonalización de una matriz simétrica: Método de Jacobi
// Descripción: Aplica rotaciones planas R_ij(theta) que anulan en cada paso el mayor elemento fuera de la diagonal (ecs. [7] y [8] de la teoria)
// hasta que todos sean menores que 'tol'. Devuelve la matriz U (new[]) cuyas COLUMNAS son los autovectores; los autovalores se devuelven en L (new[]).
// 'n_rot' devuelve el numero de rotaciones realizadas. La matriz A no se modifica.

double** jacobi_eig(double **A, int n, double *&L, double tol, int max_iter, int &n_rot) {
    /*
    Ejemplo de uso:
        double *L; int rot;
        double **U = jacobi_eig(A, n, L, 1e-10, 1000, rot);   // U' * A * U = diag(L)
        print_vect(L, n, "Autovalores");
        print_mat(U, n, n, "Autovectores (columnas)");
    */
    n_rot = 0;
    if (!is_symmetric_mat(A, n, 1e-10)) {
        print_error("jacobi_eig: la matriz debe ser simetrica");
        L = NULL;
        return NULL;
    }
    double **B = coppy_mat(A, n, n);
    double **U = eye_mat(n);

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

        // Paso 5: U = U*R (sin construir R)
        for (int k = 0; k < n; k++) {
            double uki = U[k][i];
            U[k][i] = uki * co + U[k][j] * si;
            U[k][j] = -uki * si + U[k][j] * co;
        }
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
    L = get_diag_mat(B, n);
    del_mat(B, n);
    return U;
}

// Ordenar autovalores y autovectores
// Descripción: Ordena L en valor absoluto decreciente (como en la teoria: l1 = 4, l2 = -3, l3 = 2) y permuta las columnas de U en consecuencia.

void sort_eig(double *L, double **U, int n) {
    /*
    Ejemplo de uso:
        sort_eig(L, U, n);   // tras jacobi_eig
    */
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (fabs(L[j]) > fabs(L[m])) m = j;
        if (m != i) {
            intercambiar_elem(L[i], L[m]);
            for (int k = 0; k < n; k++) intercambiar_elem(U[k][i], U[k][m]);
        }
    }
}

