// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.3
// Metodo QR
// ============================================================================
// Factorizacion QR (Gram-Schmidt y rotaciones de Givens) e iteracion QR para obtener autovalores.
//
// Funciones (4): qr_gs_mat, qr_givens_mat, qr_triang_mat, qr_eig
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_QR_H
#define MATCLUB_QR_H

// Factorización QR por Gram-Schmidt modificado
// Descripción: Descompone A = Q*R con Q ortogonal (columnas ortonormales) y R triangular superior. Q y R se devuelven por referencia (new[]).
// Necesita que las columnas de A sean linealmente independientes (A invertible).
void qr_gs_mat(double **A, int n, double **&Q, double **&R);

// Factorización QR por rotaciones (Givens)
// Descripción: Hace cero los elementos por debajo de la diagonal uno a uno con rotaciones P_k (c = a_jj/d, s = a_ij/d, d = sqrt(a_jj^2 + a_ij^2)).
// R = P_m*...*P_1*A y Q = P_1^T*...*P_m^T, de modo que A = Q*R. Q y R se devuelven por referencia (new[]). Funciona para cualquier A (no necesita ser invertible).
void qr_givens_mat(double **A, int n, double **&Q, double **&R);

// Método QR: matriz triangular superior semejante a A
// Descripción: Itera A(i) = Q(i)*R(i) -> A(i+1) = R(i)*Q(i) (misma traza y autovalores) hasta que la suma de |elementos bajo la diagonal| sea < tol.
// Si 'usar_hess' es true se aplica antes la transformacion de Hessenberg (converge con menos trabajo por iteracion). Devuelve la matriz (new[]) e 'iter_out' iteraciones.
// Con autovalores complejos no converge a triangular (quedan bloques 2x2).
double** qr_triang_mat(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out);

// Autovalores de una matriz genérica: Método QR
// Descripción: Devuelve (new[]) los autovalores de A, que son los elementos diagonales de la matriz triangular obtenida con qr_triang_mat.
double* qr_eig(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out);

#endif // MATCLUB_QR_H
