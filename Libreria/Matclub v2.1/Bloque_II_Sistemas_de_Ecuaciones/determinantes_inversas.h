// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Determinantes e inversas
// ============================================================================
// Determinante e inversa por Gauss, Gauss-Jordan y LU.
//
// Funciones (4): det_gauss, det_lu, inv_gj, inv_lu
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_DETERMINANTES_INVERSAS_H
#define MATCLUB_DETERMINANTES_INVERSAS_H

// 1A. Determinante usando Eliminación Gaussiana (con pivoteo)
double det_gauss(double **A, int n);

// 1B. Determinante usando Factorización LU (Doolittle)
double det_lu(double **A, int n);

// 2A. Inversa de una matriz usando Gauss-Jordan
double** inv_gj(double **A, int n);

// 2B. Inversa de una matriz usando Factorización LU
double** inv_lu(double **A, int n);

#endif // MATCLUB_DETERMINANTES_INVERSAS_H
