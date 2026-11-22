// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.3
// Minimizacion de funciones
// ============================================================================
// Descenso mas rapido (steepest descent) para sistemas y seccion aurea para funciones de una variable.
//
// Funciones (3): seccion_aurea, func_S_error, steepest_descent_sys
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_MINIMIZACION_H
#define MATCLUB_MINIMIZACION_H

// Minimo de una funcion unimodal por el metodo de la seccion aurea
// Descripcion: Reduce el intervalo [a,b] por el factor 1/PHI en cada paso, sin usar derivadas,
//              hasta que su longitud sea menor que 'tol'. Devuelve la posicion x del minimo.
double seccion_aurea(double (*f)(double), double a, double b, double tol);

// Helper: Calcula S(x) = sum(fi(x)^2) para convertir un sistema de ecuaciones en un problema de minimización
double func_S_error(double (*AF[])(double*, int), double *x, int n);

// 5. Descenso más rápido / Máxima pendiente (Steepest Descent)
// Descripción: Resuelve el sistema encontrando el mínimo global de la función escalar S(x) = sum(fi^2).
// Utiliza un factor de avance alfa dinámico (backtracking simple) para asegurar que S siempre disminuya.
double* steepest_descent_sys(double (*AF[])(double*, int), double *x_init, int n, double alpha_init, double tol, int max_iter);

#endif // MATCLUB_MINIMIZACION_H
