// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.3
// Sistemas no lineales
// ============================================================================
// Sustituciones sucesivas (Jacobi y Gauss-Seidel no lineales) y Newton-Raphson para sistemas.
//
// Funciones (5): check_convergence_nolin, jacobi_nolin, gauss_seidel_nolin, newton_raphson_sys, newton_raphson_multi_sys
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_SISTEMAS_NO_LINEALES_H
#define MATCLUB_SISTEMAS_NO_LINEALES_H

// Comprobador de Condición de Convergencia
// Descripción: Verifica si la suma del valor absoluto de las derivadas parciales de cada función es <= 1.
bool check_convergence_nolin(double (*AF[])(double*, int), double *x, int n);

// 1. Jacobi para Sistemas No Lineales
// Descripción: Resuelve iterativamente un sistema reordenado xi = Fi(x1...xn) usando desplazamientos simultáneos.
double* jacobi_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter);

// 2. Gauss-Seidel para Sistemas No Lineales
// Descripción: Similar a Jacobi, pero usa los valores recién calculados (desplazamientos sucesivos).
double* gauss_seidel_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter);

// 3. Newton-Raphson Multivariable (Generalizado para n ecuaciones)
// Descripción: Resuelve el sistema F(x)=0 aproximando las derivadas por diferencias finitas (Jacobiano).
double* newton_raphson_sys(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter);

// 4. Newton-Raphson Array de Soluciones
// Descripción: Ejecuta Newton-Raphson sobre múltiples puntos de inicio. Devuelve una matriz de soluciones.
double** newton_raphson_multi_sys(double (*AF[])(double*, int), double **x_inits, int num_puntos, int n, double tol, int max_iter);

#endif // MATCLUB_SISTEMAS_NO_LINEALES_H
