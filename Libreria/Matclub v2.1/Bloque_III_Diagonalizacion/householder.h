// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.4
// Transformacion de Householder (forma de Hessenberg / tridiagonal)
// ============================================================================
// Reduccion a forma de Hessenberg superior (tridiagonal si la matriz es simetrica) por eliminacion y por reflexiones de Householder.
//
// Funciones (2): hessenberg_mat, hessenberg_householder_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_HOUSEHOLDER_H
#define MATCLUB_HOUSEHOLDER_H

// Forma de Hessenberg superior por transformaciones de similaridad (eliminacion)
// Descripción: Hace cero los elementos por debajo de la subdiagonal con B^-1*A*B (multiplicadores b_i = a_i,m-1 / a_m,m-1, como en la teoria).
// Si el elemento subdiagonal es cero se intercambian fila y columna con el de mayor magnitud (asi no cambian los autovalores). Devuelve una matriz nueva.
double** hessenberg_mat(double **A, int n);

// Forma de Hessenberg superior por reflexiones de Householder
// Descripción: Igual que hessenberg_mat pero con reflexiones P = I - 2*v*v^T/(v^T*v) (transformaciones ortogonales, mas estables numericamente).
// Mantiene los autovalores (P es ortogonal y simetrica: H = P*A*P). Si A es simetrica el resultado es tridiagonal.
double** hessenberg_householder_mat(double **A, int n);

#endif // MATCLUB_HOUSEHOLDER_H
