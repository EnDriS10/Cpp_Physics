// ============================================================================
// MATCLUB-CPP  |  BLOQUE V: EDOs  |  V.1
// EDO's con valores iniciales
// ============================================================================
// Serie de Taylor, Euler, Euler mejorado, Runge-Kutta de 2o y 4o orden y Runge-Kutta-Fehlberg adaptativo.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "edo_valores_iniciales.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (8): err_max_vect, taylor_eval, euler_edo, euler_mejorado_edo, rk2_edo, rk4_edo, rkf45_paso, rkf45_edo
// Dependencias copiadas (3): print_error, print_warning, print_error_int
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_EDO_VALORES_INICIALES_CPP
#define MATCLUB_EDO_VALORES_INICIALES_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: EDO's con valores iniciales
// ----------------------------------------------------------------------------

#ifndef MC_FN_err_max_vect
#define MC_FN_err_max_vect
// Error máximo entre dos vectores
// Descripción: Devuelve max|a[i]-b[i]|. Util para comparar la solucion numerica con la analitica.
double err_max_vect(double *a, double *b, int n) {
    /*
    Ejemplo de uso:
        double e = err_max_vect(y_num, y_exacta, n + 1);
    */
    double mx = 0.0;
    for (int i = 0; i < n; i++) if (fabs(a[i] - b[i]) > mx) mx = fabs(a[i] - b[i]);
    return mx;
}
#endif // MC_FN_err_max_vect

#ifndef MC_FN_taylor_eval
#define MC_FN_taylor_eval
// Método de la serie de Taylor
// Descripción: Evalua y(x0+h) = sum_k y^(k)(x0)*h^k/k! a partir de las 'n' derivadas conocidas derivs[k] = y^(k)(x0), k = 0..n-1.
double taylor_eval(double *derivs, int n, double h) {
    /*
    Ejemplo de uso:
        // y' = -2x - y, y(0) = -1  ->  derivadas en 0: -1, 1, -3, 3, -3
        double d[] = {-1, 1, -3, 3, -3};
        double y = taylor_eval(d, 5, 0.1);   // -0.91451
    */
    double suma = 0.0, termino = 1.0;
    for (int k = 0; k < n; k++) {
        suma += derivs[k] * termino;
        termino *= h / (k + 1.0);
    }
    return suma;
}
#endif // MC_FN_taylor_eval

#ifndef MC_FN_euler_edo
#define MC_FN_euler_edo
// Método de Euler
// Descripción: y_(n+1) = y_n + h*f(x_n,y_n) con 'n' pasos entre x0 y xf. Devuelve y[0..n] y los puntos x en x_out (ambos new[]). Error global O(h).
double* euler_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out) {
    /*
    Ejemplo de uso:
        double f(double x, double y) { return -2*x - y; }
        double *x, *y = euler_edo(f, 0.0, -1.0, 0.5, 5, x);   // h = 0.1
    */
    if (n < 1) { print_error_int("euler_edo: n debe ser >= 1", n); x_out = NULL; return NULL; }
    double h = (xf - x0) / n;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        y[i + 1] = y[i] + h * f(x_out[i], y[i]);
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}
#endif // MC_FN_euler_edo

#ifndef MC_FN_euler_mejorado_edo
#define MC_FN_euler_mejorado_edo
// Método de Euler mejorado (predictor-corrector)
// Descripción: Predice y_p = y_n + h*f(x_n,y_n) y corrige y_c = y_n + h*(f(x_n,y_n) + f(x_n+h,y_p))/2. 'n_corr' es el numero de correcciones (1 = metodo de Heun).
// Error local O(h^3) y global O(h^2).
double* euler_mejorado_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out, int n_corr) {
    /*
    Ejemplo de uso:
        double *x, *y = euler_mejorado_edo(f, 0.0, -1.0, 0.5, 5, x, 1);
    */
    if (n < 1 || n_corr < 1) { print_error("euler_mejorado_edo: n y n_corr deben ser >= 1"); x_out = NULL; return NULL; }
    double h = (xf - x0) / n;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        double f0 = f(x_out[i], y[i]);
        double yp = y[i] + h * f0;                     // prediccion (Euler)
        for (int c = 0; c < n_corr; c++) yp = y[i] + h * (f0 + f(x_out[i] + h, yp)) / 2.0;   // correccion
        y[i + 1] = yp;
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}
#endif // MC_FN_euler_mejorado_edo

#ifndef MC_FN_rk2_edo
#define MC_FN_rk2_edo
// Método de Runge-Kutta de segundo orden (familia de un parametro)
// Descripción: y_(n+1) = y_n + a*k1 + b*k2 con b = 1-a, k1 = h*f(x,y), k2 = h*f(x+alfa*h, y+beta*k1) y alfa = beta = 1/(2b). 0 <= a < 1.
// a = 1/2 es Euler mejorado (Heun), a = 0 es el metodo del punto medio, a = 1/3 es Ralston.
double* rk2_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out, double a) {
    /*
    Ejemplo de uso:
        double *x, *y = rk2_edo(f, 0.0, -1.0, 0.5, 5, x, 0.5);   // = Heun
    */
    if (n < 1 || a < 0.0 || a >= 1.0) { print_error("rk2_edo: n >= 1 y 0 <= a < 1"); x_out = NULL; return NULL; }
    double h = (xf - x0) / n, b = 1.0 - a, alfa = 1.0 / (2.0 * b);
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        double k1 = h * f(x_out[i], y[i]);
        double k2 = h * f(x_out[i] + alfa * h, y[i] + alfa * k1);
        y[i + 1] = y[i] + a * k1 + b * k2;
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}
#endif // MC_FN_rk2_edo

#ifndef MC_FN_rk4_edo
#define MC_FN_rk4_edo
// Método de Runge-Kutta de cuarto orden
// Descripción: y_(n+1) = y_n + (k1 + 2k2 + 2k3 + k4)/6. Error local O(h^5) y global O(h^4).
double* rk4_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out) {
    /*
    Ejemplo de uso:
        double *x, *y = rk4_edo(f, 0.0, -1.0, 0.5, 5, x);   // y(0.5) = -0.81959 (exacto hasta 5 cifras)
    */
    if (n < 1) { print_error_int("rk4_edo: n debe ser >= 1", n); x_out = NULL; return NULL; }
    double h = (xf - x0) / n;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        double xi = x_out[i], yi = y[i];
        double k1 = h * f(xi, yi);
        double k2 = h * f(xi + 0.5 * h, yi + 0.5 * k1);
        double k3 = h * f(xi + 0.5 * h, yi + 0.5 * k2);
        double k4 = h * f(xi + h, yi + k3);
        y[i + 1] = yi + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}
#endif // MC_FN_rk4_edo

#ifndef MC_FN_rkf45_paso
#define MC_FN_rkf45_paso
// Paso de Runge-Kutta-Fehlberg (4o y 5o orden)
// Descripción: Avanza un paso h desde (x,y) con 6 evaluaciones de f. Devuelve el valor de 5o orden y, en 'err', la estimacion del error
// y5 - y4 = k1/360 - 128k3/4275 - 2197k4/75240 + k5/50 + 2k6/55.
double rkf45_paso(double (*f)(double, double), double x, double y, double h, double &err) {
    /*
    Ejemplo de uso:
        double e, y1 = rkf45_paso(f, 0.0, -1.0, 0.1, e);   // y(0.1) = -0.914512251, e ~ -4e-8
    */
    double k1 = h * f(x, y);
    double k2 = h * f(x + h / 4.0, y + k1 / 4.0);
    double k3 = h * f(x + 3.0 * h / 8.0, y + 3.0 * k1 / 32.0 + 9.0 * k2 / 32.0);
    double k4 = h * f(x + 12.0 * h / 13.0, y + 1932.0 * k1 / 2197.0 - 7200.0 * k2 / 2197.0 + 7296.0 * k3 / 2197.0);
    double k5 = h * f(x + h, y + 439.0 * k1 / 216.0 - 8.0 * k2 + 3680.0 * k3 / 513.0 - 845.0 * k4 / 4104.0);
    double k6 = h * f(x + h / 2.0, y - 8.0 * k1 / 27.0 + 2.0 * k2 - 3544.0 * k3 / 2565.0 + 1859.0 * k4 / 4104.0 - 11.0 * k5 / 40.0);
    double y4 = y + 25.0 * k1 / 216.0 + 1408.0 * k3 / 2565.0 + 2197.0 * k4 / 4104.0 - k5 / 5.0;
    double y5 = y + 16.0 * k1 / 135.0 + 6656.0 * k3 / 12825.0 + 28561.0 * k4 / 56430.0 - 9.0 * k5 / 50.0 + 2.0 * k6 / 55.0;
    err = y5 - y4;
    return y5;
}
#endif // MC_FN_rkf45_paso

#ifndef MC_FN_rkf45_edo
#define MC_FN_rkf45_edo
// Método de Runge-Kutta-Fehlberg con paso adaptativo
// Descripción: Parte del paso h0 y lo ajusta en cada iteracion (h_nuevo = 0.9*h*(tol/|err|)^(1/5)) para que el error por paso sea menor que 'tol'.
// Devuelve los valores y (new[]) en los puntos aceptados, x_out con las abscisas y n_out = numero de puntos. max_pasos limita el trabajo total.
double* rkf45_edo(double (*f)(double, double), double x0, double y0, double xf, double h0, double tol,
                  int max_pasos, double *&x_out, int &n_out) {
    /*
    Ejemplo de uso:
        double *x; int n;
        double *y = rkf45_edo(f, 0.0, -1.0, 0.5, 0.1, 1e-8, 10000, x, n);
    */
    int cap = 64;
    double *y = new double[cap];
    x_out = new double[cap];
    n_out = 1;
    x_out[0] = x0; y[0] = y0;
    double h = h0;
    double sentido = (xf >= x0) ? 1.0 : -1.0;
    h = fabs(h) * sentido;
    int pasos = 0;
    while ((xf - x_out[n_out - 1]) * sentido > 1e-14 * fabs(xf - x0) && pasos < max_pasos) {
        double x = x_out[n_out - 1];
        if ((x + h - xf) * sentido > 0.0) h = xf - x;          // no pasarse de xf
        double err;
        double ynew = rkf45_paso(f, x, y[n_out - 1], h, err);
        double e = fabs(err);
        if (e <= tol || fabs(h) < 1e-14) {                      // paso aceptado
            if (n_out >= cap) {
                int ncap = 2 * cap;
                double *ty = new double[ncap], *tx = new double[ncap];
                for (int i = 0; i < n_out; i++) { ty[i] = y[i]; tx[i] = x_out[i]; }
                delete[] y; delete[] x_out;
                y = ty; x_out = tx; cap = ncap;
            }
            y[n_out] = ynew;
            x_out[n_out] = x + h;
            n_out++;
        }
        double factor = (e == 0.0) ? 5.0 : 0.9 * pow(tol / e, 0.2);
        if (factor > 5.0) factor = 5.0;
        if (factor < 0.1) factor = 0.1;
        h *= factor;
        pasos++;
    }
    if (pasos >= max_pasos) print_warning("rkf45_edo alcanzo max_pasos antes de llegar a xf.");
    return y;
}
#endif // MC_FN_rkf45_edo

#endif // MATCLUB_EDO_VALORES_INICIALES_CPP
