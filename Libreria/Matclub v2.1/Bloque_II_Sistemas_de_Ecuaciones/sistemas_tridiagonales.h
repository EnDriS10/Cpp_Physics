// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: matrices tridiagonales
// ============================================================================
// Algoritmo de Thomas (LU para sistemas tridiagonales), con la matriz completa o solo con las tres diagonales.
//
// Funciones (2): tridiag_solve, tridiag_vect_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_SISTEMAS_TRIDIAGONALES_H
#define MATCLUB_SISTEMAS_TRIDIAGONALES_H

// Algoritmo de Thomas (Sistemas Tridiagonales)
// Los vectores a, b, c son las diagonales (inferior, principal, superior)
// Se le pasa la matriz completa A y el vector independiente f.
// La funcion extrae las diagonales automaticamente.
double* tridiag_solve(double **A, double *f, int n);

// Resolución de sistemas tridiagonales con las diagonales en vectores (Algoritmo de Thomas)
// Descripción: Resuelve A*x = f para una matriz tridiagonal de n x n SIN construirla: 'a' es la diagonal inferior (a[1..n-1], a[0] no se usa),
// 'b' la principal (b[0..n-1]) y 'c' la superior (c[0..n-2], c[n-1] no se usa). Es la funcion Tridiag de las practicas (factorizacion LU + sustitucion).
double* tridiag_vect_solve(double *a, double *b, double *c, double *f, int n);

#endif // MATCLUB_SISTEMAS_TRIDIAGONALES_H
