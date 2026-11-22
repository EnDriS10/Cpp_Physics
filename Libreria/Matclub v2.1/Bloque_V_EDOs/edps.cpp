// ============================================================================
// MATCLUB-CPP  |  BLOQUE V (ampliacion): ECUACIONES EN DERIVADAS PARCIALES
// Ecuaciones en derivadas parciales
// ============================================================================
// Ecuacion del calor (explicita e implicita) y ecuacion de Laplace en una placa (Gauss-Seidel con sobrerrelajacion).
//
// Funciones (4): calor_explicito, calor_implicito, laplace_gs, laplace_placa
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Ecuación del calor: forma explícita (diferencias progresivas)
// Descripción: w[i][n+1] = lambda*w[i-1][n] + (1-2*lambda)*w[i][n] + lambda*w[i+1][n], con lambda = dtau/dX^2 y dX = 1/M. f0(X) es la condicion inicial y g0(tau), g1(tau)
// las condiciones de contorno en X = 0 y X = 1. Estable solo si lambda <= 1/2 (aviso si no se cumple). Devuelve una matriz (N+1) x (M+1), una fila por instante tau_n;
// N_out = numero de pasos de tiempo hasta tau_max. Liberar con del_mat(W, N_out+1).

double** calor_explicito(double (*f0)(double), double (*g0)(double), double (*g1)(double),
                         int M, double dtau, double tau_max, int &N_out) {
    /*
    Ejemplo de uso:
        double f0(double X) { return 0.0; }   double g(double tau) { return 1.0; }
        int N;
        double **W = calor_explicito(f0, g, g, 10, 0.004, 0.2, N);   // lambda = 0.4
    */
    if (M < 2 || dtau <= 0.0 || tau_max <= 0.0) { print_error("calor_explicito: M >= 2, dtau > 0 y tau_max > 0"); N_out = 0; return NULL; }
    double dX = 1.0 / M, lambda = dtau / (dX * dX);
    if (lambda > 0.5) print_warning("calor_explicito: lambda > 1/2, el metodo explicito es inestable (criterio de Von Neumann).");
    int N = (int)ceil(tau_max / dtau - 1e-12);
    N_out = N;
    double **W = zeros_mat(N + 1, M + 1);
    for (int i = 0; i <= M; i++) W[0][i] = f0(i * dX);
    for (int n = 0; n < N; n++) {
        double tau = (n + 1) * dtau;
        W[n + 1][0] = g0(tau);
        W[n + 1][M] = g1(tau);
        for (int i = 1; i < M; i++)
            W[n + 1][i] = lambda * W[n][i - 1] + (1.0 - 2.0 * lambda) * W[n][i] + lambda * W[n][i + 1];
    }
    return W;
}

// Ecuación del calor: forma implícita (diferencias regresivas)
// Descripción: -lambda*w[i-1][n+1] + (1+2*lambda)*w[i][n+1] - lambda*w[i+1][n+1] = w[i][n]. En cada instante se resuelve un sistema tridiagonal de M-1 ecuaciones con
// tridiag_vect_solve. Es estable para cualquier dtau y dX. Mismos argumentos y salida que calor_explicito.

double** calor_implicito(double (*f0)(double), double (*g0)(double), double (*g1)(double),
                         int M, double dtau, double tau_max, int &N_out) {
    /*
    Ejemplo de uso:
        int N;
        double **W = calor_implicito(f0, g, g, 10, 0.02, 0.2, N);   // lambda = 2, valido
    */
    if (M < 2 || dtau <= 0.0 || tau_max <= 0.0) { print_error("calor_implicito: M >= 2, dtau > 0 y tau_max > 0"); N_out = 0; return NULL; }
    double dX = 1.0 / M, lambda = dtau / (dX * dX);
    int N = (int)ceil(tau_max / dtau - 1e-12);
    N_out = N;
    double **W = zeros_mat(N + 1, M + 1);
    for (int i = 0; i <= M; i++) W[0][i] = f0(i * dX);
    int m = M - 1;                                       // puntos interiores
    double *a = new double[m], *b = new double[m], *c = new double[m], *d = new double[m];
    for (int i = 0; i < m; i++) { a[i] = -lambda; b[i] = 1.0 + 2.0 * lambda; c[i] = -lambda; }
    for (int n = 0; n < N; n++) {
        double tau = (n + 1) * dtau;
        W[n + 1][0] = g0(tau);
        W[n + 1][M] = g1(tau);
        for (int i = 0; i < m; i++) d[i] = W[n][i + 1];
        d[0]     += lambda * W[n + 1][0];
        d[m - 1] += lambda * W[n + 1][M];
        double *w = tridiag_vect_solve(a, b, c, d, m);
        for (int i = 0; i < m; i++) W[n + 1][i + 1] = w[i];
        delete[] w;
    }
    delete[] a; delete[] b; delete[] c; delete[] d;
    return W;
}

// Ecuación de Laplace 2D: Gauss-Seidel con sobrerrelajación
// Descripción: T es una matriz (n+1) x (n+1) con la frontera ya fijada y un valor inicial en el interior. Itera T_new = T_old + omega/4*(T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1] - 4*T_old)
// hasta que sum|T_new - T_old| < tol. omega = 1 es Gauss-Seidel puro; 1 < omega < 2 acelera la convergencia (omega ~ 1.94 para n = 100). Devuelve el numero de iteraciones.

int laplace_gs(double **T, int n, double tol, int max_iter, double omega) {
    /*
    Ejemplo de uso:
        int it = laplace_gs(T, 20, 1e-7, 50000, 1.5);   // T se modifica con la solucion
    */
    int iter = 0;
    double diferencia = tol + 1.0;
    while (diferencia > tol && iter < max_iter) {
        diferencia = 0.0;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                double viejo = T[i][j];
                double nuevo = viejo + omega / 4.0 * (T[i + 1][j] + T[i - 1][j] + T[i][j + 1] + T[i][j - 1] - 4.0 * viejo);
                T[i][j] = nuevo;
                diferencia += fabs(nuevo - viejo);
            }
        }
        iter++;
    }
    if (iter >= max_iter && diferencia > tol) print_warning("laplace_gs alcanzo max_iter sin converger plenamente.");
    return iter;
}

// Placa cuadrada con temperaturas constantes en los bordes
// Descripción: Crea la matriz (n+1) x (n+1) con T_sup (fila 0), T_inf (fila n), T_izq (columna 0) y T_der (columna n) constantes y el interior a 0, y resuelve Laplace con laplace_gs.
// 'iter_out' devuelve las iteraciones. Liberar con del_mat(T, n+1).

double** laplace_placa(int n, double T_sup, double T_inf, double T_izq, double T_der,
                       double tol, int max_iter, double omega, int &iter_out) {
    /*
    Ejemplo de uso:
        int it;
        double **T = laplace_placa(20, 0.0, 0.0, 100.0, 0.0, 1e-7, 50000, 1.5, it);   // un borde a 100 y los otros a 0
    */
    double **T = zeros_mat(n + 1, n + 1);
    for (int k = 0; k <= n; k++) {
        T[0][k] = T_sup; T[n][k] = T_inf;
        T[k][0] = T_izq; T[k][n] = T_der;
    }
    iter_out = laplace_gs(T, n, tol, max_iter, omega);
    return T;
}

