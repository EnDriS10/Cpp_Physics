// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: eliminacion de Gauss y Gauss-Jordan
// ============================================================================
// Metodos directos de eliminacion, con deteccion de matrices singulares.
//
// Funciones (2): gauss_solve, gauss_jordan_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ELIMINACION_GAUSS_H
#define MATCLUB_ELIMINACION_GAUSS_H

// Eliminación de Gauss con pivoteo parcial
double* gauss_solve(double **A, double *b, int n);

// Método de Gauss-Jordan (Diagonal a 1, ceros arriba y abajo)
double* gauss_jordan_solve(double **A, double *b, int n);

#endif // MATCLUB_ELIMINACION_GAUSS_H
