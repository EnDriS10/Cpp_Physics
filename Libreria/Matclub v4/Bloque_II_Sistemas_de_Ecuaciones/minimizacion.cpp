// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.3
// Minimizacion de funciones
// ============================================================================
// Descenso mas rapido (steepest descent) para sistemas y seccion aurea para funciones de una variable.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "minimizacion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (3): seccion_aurea, func_S_error, steepest_descent_sys
// Dependencias copiadas (10): MC_NAN, print_error, print_warning, print_error_int, intercambiar_elem, PHI, copy_vect, pesos_deriv_lagrange, part_derv_c, part_derv
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_MINIMIZACION_CPP
#define MATCLUB_MINIMIZACION_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

// (constante global)
#ifndef MC_FN_MC_NAN
#define MC_FN_MC_NAN
const double MC_NAN = sqrt(-1.0);
#endif // MC_FN_MC_NAN

// (copiada de: mensajes)
#ifndef MC_FN_print_error
#define MC_FN_print_error
void print_error(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB ERROR]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_error

// (copiada de: mensajes)
#ifndef MC_FN_print_warning
#define MC_FN_print_warning
// Aviso: algo no fue perfecto pero el programa puede continuar
void print_warning(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB AVISO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_warning

// (copiada de: mensajes)
#ifndef MC_FN_print_error_int
#define MC_FN_print_error_int
// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}
#endif // MC_FN_print_error_int

// (copiada de: auxiliares)
#ifndef MC_FN_intercambiar_elem
#define MC_FN_intercambiar_elem
//Intercambia dos elementos
void intercambiar_elem(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}
#endif // MC_FN_intercambiar_elem

// (copiada de: auxiliares)
#ifndef MC_FN_PHI
#define MC_FN_PHI
// Devuelve el numero aureo (1+sqrt(5))/2 redondeado a 'n' decimales
// Descripcion: Igual que PI(n). Se usa en seccion_aurea (el factor de reduccion es 1/PHI = PHI-1).
double PHI(int n) {
    /*
    Ejemplo de uso:
        double fi = PHI(6); // Devuelve 1.618034
    */
    double base_phi = (1.0 + sqrt(5.0)) / 2.0;
    double factor = pow(10.0, n);
    return round(base_phi * factor) / factor;
}
#endif // MC_FN_PHI

// (copiada de: vectores)
#ifndef MC_FN_copy_vect
#define MC_FN_copy_vect
// Copia un vector
double* copy_vect(double *a, int n) {
    double *c = new double[n];
    for (int i = 0; i < n; i++) c[i] = a[i];
    return c;
}
#endif // MC_FN_copy_vect

// (copiada de: derivacion)
#ifndef MC_FN_pesos_deriv_lagrange
#define MC_FN_pesos_deriv_lagrange
// Pesos de derivación (derivada del polinomio de Lagrange)
// Descripción: Para los m nodos xs[0..m-1] calcula los pesos w[j] tales que f^(orden)(xt) ~ sum(w[j]*f(xs[j])), con orden = 1 o 2. Vale para nodos NO equiespaciados.
// Con nodos equiespaciados reproduce las formulas clasicas (centrales, progresivas y regresivas). 'w' debe tener m posiciones.
void pesos_deriv_lagrange(double *xs, int m, double xt, int orden, double *w) {
    /*
    Ejemplo de uso:
        double xs[] = {1.9, 2.0, 2.1}, w[3];
        pesos_deriv_lagrange(xs, 3, 2.0, 1, w);     // w = {-5, 0, 5}  (central: (f(x+h)-f(x-h))/(2h) con h = 0.1)
    */
    for (int j = 0; j < m; j++) {
        double D = 1.0;
        for (int k = 0; k < m; k++) if (k != j) D *= (xs[j] - xs[k]);
        double s = 0.0;
        for (int a = 0; a < m; a++) {
            if (a == j) continue;
            if (orden == 1) {
                double p = 1.0;
                for (int k = 0; k < m; k++) if (k != j && k != a) p *= (xt - xs[k]);
                s += p;
            } else {
                for (int l = 0; l < m; l++) {
                    if (l == j || l == a) continue;
                    double p = 1.0;
                    for (int k = 0; k < m; k++) if (k != j && k != a && k != l) p *= (xt - xs[k]);
                    s += p;
                }
            }
        }
        w[j] = s / D;
    }
}
#endif // MC_FN_pesos_deriv_lagrange

// (copiada de: derivacion)
#ifndef MC_FN_part_derv_c
#define MC_FN_part_derv_c
// Derivada parcial CENTRAL de alta precisión
// Descripción: Calcula df/dx_j con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9; error O(h^(puntos-1))). Mas puntos = mas precision pero mas evaluaciones de f (puntos-1).
// Si h <= 0 elige automaticamente el paso que equilibra truncamiento y redondeo: h = eps^(1/puntos) * max(1, |x_j|). f debe ser suave (derivable) en el entorno del punto.
double part_derv_c(double (*f)(double*, int), double *x, int n, int j, double h, int puntos) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0]*v[1] + sin(v[1]); }
        double punto[] = {2.0, 0.5};
        double dfdx = part_derv_c(mi_func, punto, 2, 0, 0.0, 5);   // 2*x*y = 2.0 (paso automatico, 5 puntos)
        double dfdy = part_derv_c(mi_func, punto, 2, 1, 1e-3, 7);  // x^2 + cos(y) = 4.8775826 (h = 1e-3, 7 puntos)
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("part_derv_c: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    if (j < 0 || j >= n) { print_error_int("part_derv_c: la variable j esta fuera de rango", j); return MC_NAN; }
    if (h <= 0.0) h = pow(2.220446049250313e-16, 1.0 / puntos) * ((fabs(x[j]) > 1.0) ? fabs(x[j]) : 1.0);
    int m = puntos / 2;
    double xs[9], w[9];
    for (int k = 0; k < puntos; k++) xs[k] = (double)(k - m);
    pesos_deriv_lagrange(xs, puntos, 0.0, 1, w);          // pesos centrales para paso unidad
    double *xh = copy_vect(x, n);
    double suma = 0.0;
    for (int k = 0; k < puntos; k++) {
        if (k == m) continue;                              // el peso central es 0
        xh[j] = x[j] + (k - m) * h;
        suma += w[k] * f(xh, n);
    }
    delete[] xh;
    return suma / h;
}
#endif // MC_FN_part_derv_c

// (copiada de: derivacion)
#ifndef MC_FN_part_derv
#define MC_FN_part_derv
// Derivada parcial numérica CENTRAL de 5 puntos (error O(h^4)).
// Descripción: Calcula df/dx_j con diferencias centrales de 5 puntos y paso automatico (eps^(1/5)*max(1,|x_j|)). Para elegir el paso o el nº de puntos (3, 5, 7, 9) usa part_derv_c.
double part_derv(double (*f)(double*, int), double *x, int n, int j) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0] + sin(v[1]); }
        double punto[] = {2.0, 3.14};
        double df_dy = part_derv(mi_func, punto, 2, 1);
    */
    return part_derv_c(f, x, n, j, 0.0, 5);
}
#endif // MC_FN_part_derv

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Minimizacion de funciones
// ----------------------------------------------------------------------------

#ifndef MC_FN_seccion_aurea
#define MC_FN_seccion_aurea
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
#endif // MC_FN_seccion_aurea

#ifndef MC_FN_func_S_error
#define MC_FN_func_S_error
// Helper: Calcula S(x) = sum(fi(x)^2) para convertir un sistema de ecuaciones en un problema de minimización
// Descripción: Convierte un sistema de ecuaciones f_i(x) = 0 en un problema de minimizacion: devuelve S(x) = suma de f_i(x)^2, que vale 0 solo en una solucion del sistema. La usan los metodos de minimizacion (descenso mas rapido).
double func_S_error(double (*AF[])(double*, int), double *x, int n) {
    /*
    Ejemplo de uso:
        double f1(double *x, int n) { return x[0]*x[0] + x[1]*x[1] - 4; }
        double f2(double *x, int n) { return x[0] - x[1]; }
        double (*AF[2])(double*, int) = {f1, f2};
        double x[2] = {1.0, 1.0};
        double S = func_S_error(AF, x, 2);
        // Resultado: S = 4   ((1+1-4)^2 + 0^2)
    */
    double S = 0.0;
    for (int i = 0; i < n; i++) {
        double val = AF[i](x, n);
        S += val * val;
    }
    return S;
}
#endif // MC_FN_func_S_error

#ifndef MC_FN_steepest_descent_sys
#define MC_FN_steepest_descent_sys
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
#endif // MC_FN_steepest_descent_sys

#endif // MATCLUB_MINIMIZACION_CPP
