// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.1
// Busqueda de ceros de una funcion
// ============================================================================
// Biseccion, secante y Newton (con version para buscar varias raices en un intervalo).
//
// Funciones (5): biseccion, biseccion_multi, secante, newton, newton_multi
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_CEROS_FUNCION_H
#define MATCLUB_CEROS_FUNCION_H

// Método de la Biseccion (Una sola raiz)
double biseccion(double (*f)(double), double x1, double x2, double tol1, double tol2, int max_iter);

// Biseccion Multiple: Busca multiples raices en un intervalo [a, b]
double* biseccion_multi(double (*f)(double), double a, double b, int subintervalos, double tol, int &num_raices);

// Método de la Secante (Una sola raiz)
double secante(double (*f)(double), double x0, double x1, double tol1, double tol2, int max_iter);

// Método de Newton (Una sola raiz)
double newton(double (*f)(double), double (*df)(double), double x0, double tol1, double tol2, int max_iter);

// Newton Multiple: Busca multiples raices lanzando Newton desde varios puntos
double* newton_multi(double (*f)(double), double (*df)(double), double a, double b, int puntos_inicio, double tol, int &num_raices);

#endif // MATCLUB_CEROS_FUNCION_H
