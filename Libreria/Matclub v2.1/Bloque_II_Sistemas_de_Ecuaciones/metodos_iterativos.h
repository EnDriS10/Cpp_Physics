// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: metodos iterativos
// ============================================================================
// Comprobacion de dominancia diagonal, Jacobi, Gauss-Seidel y sobrerrelajacion (SOR).
//
// Funciones (5): check_dominancia, reorder_diagonals, jacobi_solve, gauss_seidel_solve, sor_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_METODOS_ITERATIVOS_H
#define MATCLUB_METODOS_ITERATIVOS_H

/// Función Auxiliar: Comprueba estrictamente si una matriz es diagonalmente dominante
bool check_dominancia(double **A, int n);

// Función Auxiliar: Reordena las filas (A y b) solo si la matriz no es dominante de entrada
bool reorder_diagonals(double **A, double *b, int n);

// Método Iterativo de Jacobi (Desplazamientos simultáneos)
double* jacobi_solve(double **A, double *b, int n, double tol, int max_iter);

// Método Iterativo de Gauss-Seidel (Desplazamientos sucesivos)
double* gauss_seidel_solve(double **A, double *b, int n, double tol, int max_iter );

// Método de Sobrerrelajación (SOR) - Extensión de Gauss-Seidel
// El valor óptimo de w está entre 1 y 2. Para w=1 es idéntico a Gauss-Seidel.
double* sor_solve(double **A, double *b, int n, double w, double tol, int max_iter);

#endif // MATCLUB_METODOS_ITERATIVOS_H
