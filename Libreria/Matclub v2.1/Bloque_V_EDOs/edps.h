// ============================================================================
// MATCLUB-CPP  |  BLOQUE V (ampliacion): ECUACIONES EN DERIVADAS PARCIALES
// Ecuaciones en derivadas parciales
// ============================================================================
// Ecuacion del calor (explicita e implicita) y ecuacion de Laplace en una placa (Gauss-Seidel con sobrerrelajacion).
//
// Funciones (4): calor_explicito, calor_implicito, laplace_gs, laplace_placa
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_EDPS_H
#define MATCLUB_EDPS_H

// Ecuación del calor: forma explícita (diferencias progresivas)
// Descripción: w[i][n+1] = lambda*w[i-1][n] + (1-2*lambda)*w[i][n] + lambda*w[i+1][n], con lambda = dtau/dX^2 y dX = 1/M. f0(X) es la condicion inicial y g0(tau), g1(tau)
// las condiciones de contorno en X = 0 y X = 1. Estable solo si lambda <= 1/2 (aviso si no se cumple). Devuelve una matriz (N+1) x (M+1), una fila por instante tau_n;
// N_out = numero de pasos de tiempo hasta tau_max. Liberar con del_mat(W, N_out+1).
double** calor_explicito(double (*f0)(double), double (*g0)(double), double (*g1)(double), int M, double dtau, double tau_max, int &N_out);

// Ecuación del calor: forma implícita (diferencias regresivas)
// Descripción: -lambda*w[i-1][n+1] + (1+2*lambda)*w[i][n+1] - lambda*w[i+1][n+1] = w[i][n]. En cada instante se resuelve un sistema tridiagonal de M-1 ecuaciones con
// tridiag_vect_solve. Es estable para cualquier dtau y dX. Mismos argumentos y salida que calor_explicito.
double** calor_implicito(double (*f0)(double), double (*g0)(double), double (*g1)(double), int M, double dtau, double tau_max, int &N_out);

// Ecuación de Laplace 2D: Gauss-Seidel con sobrerrelajación
// Descripción: T es una matriz (n+1) x (n+1) con la frontera ya fijada y un valor inicial en el interior. Itera T_new = T_old + omega/4*(T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1] - 4*T_old)
// hasta que sum|T_new - T_old| < tol. omega = 1 es Gauss-Seidel puro; 1 < omega < 2 acelera la convergencia (omega ~ 1.94 para n = 100). Devuelve el numero de iteraciones.
int laplace_gs(double **T, int n, double tol, int max_iter, double omega);

// Placa cuadrada con temperaturas constantes en los bordes
// Descripción: Crea la matriz (n+1) x (n+1) con T_sup (fila 0), T_inf (fila n), T_izq (columna 0) y T_der (columna n) constantes y el interior a 0, y resuelve Laplace con laplace_gs.
// 'iter_out' devuelve las iteraciones. Liberar con del_mat(T, n+1).
double** laplace_placa(int n, double T_sup, double T_inf, double T_izq, double T_der, double tol, int max_iter, double omega, int &iter_out);

#endif // MATCLUB_EDPS_H
