// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.2
// Diagonalizacion de matrices simetricas: Metodo de Jacobi
// ============================================================================
// Rotaciones de Jacobi para obtener autovalores y autovectores de matrices simetricas, y ordenacion de los resultados.
//
// Funciones (2): jacobi_eig, sort_eig
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_JACOBI_H
#define MATCLUB_JACOBI_H

// Diagonalización de una matriz simétrica: Método de Jacobi
// Descripción: Aplica rotaciones planas R_ij(theta) que anulan en cada paso el mayor elemento fuera de la diagonal (ecs. [7] y [8] de la teoria)
// hasta que todos sean menores que 'tol'. Devuelve la matriz U (new[]) cuyas COLUMNAS son los autovectores; los autovalores se devuelven en L (new[]).
// 'n_rot' devuelve el numero de rotaciones realizadas. La matriz A no se modifica.
double** jacobi_eig(double **A, int n, double *&L, double tol, int max_iter, int &n_rot);

// Ordenar autovalores y autovectores
// Descripción: Ordena L en valor absoluto decreciente (como en la teoria: l1 = 4, l2 = -3, l3 = 2) y permuta las columnas de U en consecuencia.
void sort_eig(double *L, double **U, int n);

#endif // MATCLUB_JACOBI_H
