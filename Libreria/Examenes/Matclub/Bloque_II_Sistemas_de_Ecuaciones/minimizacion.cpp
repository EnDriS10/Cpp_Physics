// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.3
// Minimizacion de funciones
// ============================================================================
// Descenso mas rapido (steepest descent) para sistemas y seccion aurea para funciones de una variable.
//
// Funciones (3): seccion_aurea, func_S_error, steepest_descent_sys
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Minimo de una funcion unimodal por el metodo de la seccion aurea
// Descripcion: Reduce el intervalo [a,b] por el factor 1/PHI en cada paso, sin usar derivadas,
//              hasta que su longitud sea menor que 'tol'. Devuelve la posicion x del minimo.

double seccion_aurea(double (*f)(double), double a, double b, double tol) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return (x - 2.0) * (x - 2.0) + 1.0; }
        double xmin = seccion_aurea(mi_func, -10.0, 10.0, 1e-8); // Devuelve ~2.0
    */
    if (tol <= 0.0) { print_error("seccion_aurea: tol debe ser > 0"); return MC_NAN; }
    if (a > b) intercambiar_elem(a, b);
    const double r = 1.0 / PHI(15);
    double c = b - r * (b - a), d = a + r * (b - a);
    double fc = f(c), fd = f(d);
    while (fabs(b - a) > tol) {
        if (fc < fd) { b = d; d = c; fd = fc; c = b - r * (b - a); fc = f(c); }
        else         { a = c; c = d; fc = fd; d = a + r * (b - a); fd = f(d); }
    }
    return 0.5 * (a + b);
}

// Helper: Calcula S(x) = sum(fi(x)^2) para convertir un sistema de ecuaciones en un problema de minimización

double func_S_error(double (*AF[])(double*, int), double *x, int n) {
    double S = 0.0;
    for (int i = 0; i < n; i++) {
        double val = AF[i](x, n);
        S += val * val;
    }
    return S;
}

// 5. Descenso más rápido / Máxima pendiente (Steepest Descent)
// Descripción: Resuelve el sistema encontrando el mínimo global de la función escalar S(x) = sum(fi^2).
// Utiliza un factor de avance alfa dinámico (backtracking simple) para asegurar que S siempre disminuya.

double* steepest_descent_sys(double (*AF[])(double*, int), double *x_init, int n, double alpha_init, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        // Sist debe contener funciones igualadas a cero. alpha_init = 0.1 o 1.0 suele ser un buen punto de partida.
        double (*Sist[2])(double*, int) = {f1, f2};
        double p0[] = {0.6, 3.0};
        double *sol = steepest_descent_sys(Sist, p0, 2, 0.5, 1e-6, 500);
    */
    double *x_old = copy_vect(x_init, n);
    double *x_new = new double[n];
    double *grad_S = new double[n];
    
    int iter = 0;
    double S_actual = func_S_error(AF, x_old, n);
    
    while (S_actual > tol && iter < max_iter) {
        // 1. Calcular el gradiente de S(x) manualmente usando la regla de la cadena: dS/dxj = 2 * sum( fi * dfi/dxj )
        for (int j = 0; j < n; j++) {
            grad_S[j] = 0.0;
            for (int i = 0; i < n; i++) {
                grad_S[j] += 2.0 * AF[i](x_old, n) * part_derv(AF[i], x_old, n, j);
            }
        }
        
        // 2. Moviéndonos en la dirección negativa del gradiente iterativamente
        double alpha = alpha_init;
        bool mejorado = false;
        
        // Búsqueda lineal simplificada (backtracking): reduce alpha a la mitad si la aproximación no mejora a S(x)
        while (alpha > 1e-8) {
            for (int i = 0; i < n; i++) {
                x_new[i] = x_old[i] - alpha * grad_S[i];
            }
            double S_nuevo = func_S_error(AF, x_new, n);
            
            if (S_nuevo < S_actual) {
                S_actual = S_nuevo;
                mejorado = true;
                break;
            }
            alpha /= 2.0; // Achicamos el paso
        }
        
        if (!mejorado) {
            print_warning("Steepest Descent se atasco en un minimo local o valle plano.");
            break;
        }

        for (int i = 0; i < n; i++) x_old[i] = x_new[i];
        iter++;
    }
    
    if (iter == max_iter) print_warning("Steepest Descent alcanzo max_iter sin converger plenamente.");
    
    delete[] grad_S;
    delete[] x_old;
    return x_new;
}

