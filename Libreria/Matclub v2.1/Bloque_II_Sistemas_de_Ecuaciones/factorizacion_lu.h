// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: factorizacion LU
// ============================================================================
// Factorizacion LU (Doolittle y Crout) y resolucion de sistemas con ella.
//
// Funciones (4): lu_forma1, lu_forma1_sol, lu_forma2, lu_forma2_sol
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_FACTORIZACION_LU_H
#define MATCLUB_FACTORIZACION_LU_H

// Factorización LU (Forma 1 - Descomposición de Doolittle)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma1(double **A, int n, double **L, double **U);

// Resuelve Ax = b usando LU Forma 1
double* lu_forma1_sol(double **A, double *b, int n);

// Factorización LU (Forma 2 - Alternando fila U y columna L)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma2(double **A, int n, double **L, double **U);

// Resuelve Ax = b usando LU Forma 2
double* lu_forma2_sol(double **A, double *b, int n);

#endif // MATCLUB_FACTORIZACION_LU_H
