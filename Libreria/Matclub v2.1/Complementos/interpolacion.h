// ============================================================================
// MATCLUB-CPP  |  COMPLEMENTOS (fuera de los 5 bloques)
// Interpolacion numerica
// ============================================================================
// Splines, Newton (diferencias divididas y progresivas), Lagrange, Vandermonde y estimacion del error de interpolacion.
//
// Funciones (15): spline_coef, spline_eval, spline_interp, newton_coef, newton_eval, lagrange_coef, lagrange_val, vandermonde_mat, poly_interp_coef, dif_divididas_mat, newton_error_sig, interp_error_cota, dif_progresivas_mat, newton_prog_eval, newton_prog_error_sig
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_INTERPOLACION_H
#define MATCLUB_INTERPOLACION_H

// 7. ---------------- SPLINE CUBICA NATURAL ----------------
// Devuelve las segundas derivadas M[0..n-1] (M[0]=M[n-1]=0). Liberar con del_vect.
double* spline_coef(double *x, double *y, int n);

// x debe estar ordenado de menor a mayor. Fuera de [x0, xn-1] extrapola con el tramo extremo.
double spline_eval(double *x, double *y, double *M, int n, double xi);

double spline_interp(double *x, double *y, int n, double xi);

// 8. ---------------- NEWTON (diferencias divididas) ----------------
// Devuelve c[0..n-1] = f[x0], f[x0,x1], ... Liberar con del_vect.
double* newton_coef(double *x, double *y, int n);

// Evalua el polinomio de Newton en xi (forma anidada tipo Horner)
double newton_eval(double *x, double *c, int n, double xi);

// 9. ---------------- LAGRANGE (forma baricentrica) ----------------
// Devuelve los pesos w[i] = 1 / prod_{j!=i} (x[i]-x[j]). Liberar con del_vect.
double* lagrange_coef(double *x, int n);

// Evalua el polinomio de Lagrange en xi con los pesos w (O(n) por punto)
double lagrange_val(double *x, double *y, double *w, int n, double xi);

// 10. ---------------- POLINOMIO DE INTERPOLACION POR EL SISTEMA DE VANDERMONDE ----------------
// Matriz de Vandermonde
// Descripción: Devuelve la matriz V (n x n) con V[i][j] = x[i]^j (potencias crecientes). Resolver V*a = y da los coeficientes del polinomio interpolador.
double** vandermonde_mat(double *x, int n);

// Coeficientes del polinomio interpolador (resolviendo el sistema de Vandermonde)
// Descripción: Devuelve los n coeficientes del unico polinomio de grado n-1 que pasa por los n puntos, con potencias DECRECIENTES (listo para 'polyval').
// Es el metodo mas directo pero esta mal condicionado si n es grande; para evaluar conviene newton_eval o lagrange_val.
double* poly_interp_coef(double *x, double *y, int n);

// 11. ---------------- TABLA DE DIFERENCIAS DIVIDIDAS (NEWTON) ----------------
// Tabla completa de diferencias divididas
// Descripción: T[i][j] = f[x_i, ..., x_{i+j}] (la columna j=0 es y). Los coeficientes del polinomio de Newton son la primera fila T[0][j].
// Los elementos por debajo de la diagonal secundaria valen 0. Liberar con del_mat(T, n).
double** dif_divididas_mat(double *x, double *y, int n);

// 12. ---------------- ERROR DE INTERPOLACION ----------------
// Error de interpolación de Newton: regla del término siguiente
// Descripción: Estima E(xi) ~ f[x0,...,xn] * prod(xi - x_i) usando el siguiente termino que se sumaria al polinomio.
// El polinomio usa 'n' puntos (x[0..n-1]) y 'c' son los coeficientes de Newton calculados con UN punto mas (c[0..n], es decir n+1 coeficientes).
double newton_error_sig(double *x, double *c, int n, double xi);

// Cota del error de interpolación (Lagrange o Newton)
// Descripción: |E(xi)| <= M/n! * prod|xi - x_i|, donde n es el numero de puntos del polinomio y M una cota de |f^(n)| en el intervalo.
double interp_error_cota(double *x, int n, double xi, double M_deriv);

// 13. ---------------- PUNTOS EQUIESPACIADOS: DIFERENCIAS PROGRESIVAS ----------------
// Tabla de diferencias progresivas
// Descripción: D[i][k] = (Delta^k f)(x_i) para datos equiespaciados. La columna k=0 es y. Liberar con del_mat(D, n).
// Relacion con las diferencias divididas: f[x0,...,xk] = Delta^k f0 / (k! * h^k).
double** dif_progresivas_mat(double *y, int n);

// Polinomio de interpolación de Newton con diferencias progresivas
// Descripción: Evalua P(xi) = sum_k C(s,k) * Delta^k f0 con s = (xi - x0)/h, usando 'n' diferencias dif0[0..n-1] = Delta^k f(x0).
// Para centrar el polinomio, tomar como x0 el nodo adecuado y como dif0 la fila correspondiente de dif_progresivas_mat (D[i0]).
double newton_prog_eval(double x0, double h, double *dif0, int n, double xi);

// Error de Newton progresivo: regla del término siguiente
// Descripción: E ~ C(s,n) * Delta^n f0, donde el polinomio usa 'n' puntos y dif0[n] es la primera diferencia NO usada en el polinomio.
double newton_prog_error_sig(double x0, double h, double *dif0, int n, double xi);

#endif // MATCLUB_INTERPOLACION_H
