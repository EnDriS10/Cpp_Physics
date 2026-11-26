// ============================================================================
// MATCLUB-CPP  |  BLOQUE V: EDOs  |  V.3
// EDO's con condiciones de frontera
// ============================================================================
// Metodo del disparo (con secante) y metodo de las diferencias finitas para problemas de valores de frontera.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "edo_frontera.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (3): ivp_rk4_2o, disparo_edo, dif_finitas_bvp
// Dependencias copiadas (3): print_warning, print_error_int, tridiag_vect_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_EDO_FRONTERA_CPP
#define MATCLUB_EDO_FRONTERA_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

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

// (copiada de: sistemas_tridiagonales)
#ifndef MC_FN_tridiag_vect_solve
#define MC_FN_tridiag_vect_solve
// Resolución de sistemas tridiagonales con las diagonales en vectores (Algoritmo de Thomas)
// Descripción: Resuelve A*x = f para una matriz tridiagonal de n x n SIN construirla: 'a' es la diagonal inferior (a[1..n-1], a[0] no se usa),
// 'b' la principal (b[0..n-1]) y 'c' la superior (c[0..n-2], c[n-1] no se usa). Es la funcion Tridiag de las practicas (factorizacion LU + sustitucion).
double* tridiag_vect_solve(double *a, double *b, double *c, double *f, int n) {
    /*
    Ejemplo de uso:
        // [2 -1 0; -1 2 -1; 0 -1 2] * x = [1 0 1]
        double a[] = {0, -1, -1}, b[] = {2, 2, 2}, c[] = {-1, -1, 0}, f[] = {1, 0, 1};
        double *x = tridiag_vect_solve(a, b, c, f, 3); // x = {1, 1, 1}
    */
    if (n < 1) { print_error_int("tridiag_vect_solve: n debe ser >= 1", n); return NULL; }
    double *beta = new double[n];
    double *z = new double[n];
    double *x = new double[n];

    // Paso 1: Factorización LU y sustitución progresiva (L*z = f)
    beta[0] = b[0];
    z[0] = f[0];
    for (int i = 1; i < n; i++) {
        if (beta[i - 1] == 0.0) print_warning("Cero en la diagonal durante el algoritmo de Thomas (posible division por cero).");
        double alpha = a[i] / beta[i - 1];
        beta[i] = b[i] - alpha * c[i - 1];
        z[i] = f[i] - alpha * z[i - 1];
    }
    // Paso 2: Sustitución regresiva (U*x = z)
    x[n - 1] = z[n - 1] / beta[n - 1];
    for (int i = n - 2; i >= 0; i--) x[i] = (z[i] - c[i] * x[i + 1]) / beta[i];

    delete[] beta; delete[] z;
    return x;
}
#endif // MC_FN_tridiag_vect_solve

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: EDO's con condiciones de frontera
// ----------------------------------------------------------------------------

#ifndef MC_FN_ivp_rk4_2o
#define MC_FN_ivp_rk4_2o
// Helper: resuelve el IVP y'' = f(t,y,y'), y(a) = alfa, y'(a) = p con RK4 y devuelve y(b).
// Si ys != NULL guarda la solucion en ys[0..n] (n pasos).
// Descripción: Funcion auxiliar del metodo del disparo: resuelve el problema de valores iniciales y'' = f(t,y,y'), y(a) = alfa, y'(a) = p con Runge-Kutta 4 (n pasos) y devuelve y(b).
// Si ys != NULL guarda tambien la solucion en ys[0..n].
double ivp_rk4_2o(double (*f)(double, double, double), double a, double b, double alfa, double p, int n, double *ys) {
    /*
    Ejemplo de uso:
        double f(double t, double y, double yp) { return -y; }          // y'' = -y
        double yb = ivp_rk4_2o(f, 0.0, 1.5707963267949, 0.0, 1.0, 100, NULL);
        // Resultado: yb = 1   (la solucion es y = sin(t), asi que y(pi/2) = 1)
    */
    double h = (b - a) / n, t = a, y = alfa, v = p;
    if (ys != NULL) ys[0] = y;
    for (int i = 0; i < n; i++) {
        double k1y = v,                 k1v = f(t, y, v);
        double k2y = v + 0.5*h*k1v,     k2v = f(t + 0.5*h, y + 0.5*h*k1y, v + 0.5*h*k1v);
        double k3y = v + 0.5*h*k2v,     k3v = f(t + 0.5*h, y + 0.5*h*k2y, v + 0.5*h*k2v);
        double k4y = v + h*k3v,         k4v = f(t + h, y + h*k3y, v + h*k3v);
        y += h / 6.0 * (k1y + 2.0*k2y + 2.0*k3y + k4y);
        v += h / 6.0 * (k1v + 2.0*k2v + 2.0*k3v + k4v);
        t = a + (i + 1) * h;
        if (ys != NULL) ys[i + 1] = y;
    }
    return y;
}
#endif // MC_FN_ivp_rk4_2o

#ifndef MC_FN_disparo_edo
#define MC_FN_disparo_edo
// Método del disparo (con secante)
// Descripción: Resuelve el BVP y'' = f(t,y,y'), y(a) = alfa, y(b) = beta. Busca la pendiente inicial p* tal que E(p) = y_p(b) - beta = 0 con el metodo de la secante,
// resolviendo cada IVP con RK4 y 'n' pasos. Arranque: p0 = (beta-alfa)/(b-a); p1 = p0/2 si p0*E0 > 0, 2*p0 si p0*E0 < 0 (si p0 = 0: p1 = -1 si E0 > 0, +1 si E0 < 0).
// Devuelve y[0..n] (new[]), x_out con las abscisas y p_out con la pendiente final. Si el BVP es lineal converge en una sola iteracion de la secante.
double* disparo_edo(double (*f)(double, double, double), double a, double b, double alfa, double beta,
                    int n, double tol, int max_iter, double *&x_out, double &p_out) {
    /*
    Ejemplo de uso:
        // y'' = -(2/t)y' + (2/t^2)y + sin(ln t)/t^2, y(1) = 1, y(2) = 2   (p* = 0.917621...)
        double f(double t, double y, double yp) { return -2.0/t*yp + 2.0/(t*t)*y + sin(log(t))/(t*t); }
        double *x, p;
        double *y = disparo_edo(f, 1.0, 2.0, 1.0, 2.0, 100, 1e-10, 50, x, p);
    */
    if (n < 1) { print_error_int("disparo_edo: n debe ser >= 1", n); x_out = NULL; return NULL; }
    double p0 = (beta - alfa) / (b - a);
    double E0 = ivp_rk4_2o(f, a, b, alfa, p0, n, NULL) - beta;
    double p1;
    if (p0 == 0.0)        p1 = (E0 > 0.0) ? -1.0 : 1.0;
    else if (p0 * E0 > 0.0) p1 = p0 / 2.0;
    else                  p1 = 2.0 * p0;
    double E1 = ivp_rk4_2o(f, a, b, alfa, p1, n, NULL) - beta;
    double p2 = p1, E2 = E1;
    if (fabs(E0) < tol) { p2 = p0; E2 = E0; }
    else {
        int it = 0;
        while (fabs(E1) >= tol && it < max_iter) {
            if (E1 == E0) { print_warning("disparo_edo: E(p0) = E(p1), la secante no puede continuar."); break; }
            p2 = p1 - E1 * (p1 - p0) / (E1 - E0);
            E2 = ivp_rk4_2o(f, a, b, alfa, p2, n, NULL) - beta;
            p0 = p1; E0 = E1;
            p1 = p2; E1 = E2;
            it++;
        }
        if (fabs(E1) >= tol && it >= max_iter) print_warning("disparo_edo alcanzo max_iter sin converger plenamente.");
        p2 = p1;
    }
    p_out = p2;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    ivp_rk4_2o(f, a, b, alfa, p2, n, y);
    double h = (b - a) / n;
    for (int i = 0; i <= n; i++) x_out[i] = a + i * h;
    return y;
}
#endif // MC_FN_disparo_edo

#ifndef MC_FN_dif_finitas_bvp
#define MC_FN_dif_finitas_bvp
// Método de las diferencias finitas para un BVP lineal
// Descripción: Resuelve y'' = p(t)*y' + q(t)*y + r(t), y(a) = alfa, y(b) = beta con 'N' puntos interiores (h = (b-a)/(N+1)). Sustituye las derivadas por diferencias
// centrales y resuelve el sistema tridiagonal resultante con tridiag_vect_solve. Devuelve w[0..N+1] (incluye los dos extremos) y x_out con los puntos.
double* dif_finitas_bvp(double (*p)(double), double (*q)(double), double (*r)(double), double a, double b,
                        double alfa, double beta, int N, double *&x_out) {
    /*
    Ejemplo de uso:
        double p(double t) { return -2.0/t; }
        double q(double t) { return 2.0/(t*t); }
        double r(double t) { return sin(log(t))/(t*t); }
        double *x, *w = dif_finitas_bvp(p, q, r, 1.0, 2.0, 1.0, 2.0, 99, x);
    */
    if (N < 1) { print_error_int("dif_finitas_bvp: N debe ser >= 1", N); x_out = NULL; return NULL; }
    double h = (b - a) / (N + 1);
    double *ai = new double[N], *bi = new double[N], *ci = new double[N], *fi = new double[N];
    x_out = new double[N + 2];
    for (int i = 0; i <= N + 1; i++) x_out[i] = a + i * h;
    for (int i = 1; i <= N; i++) {
        double t = x_out[i];
        ai[i - 1] = -(1.0 / (h * h) + p(t) / (2.0 * h));
        bi[i - 1] = 2.0 / (h * h) + q(t);
        ci[i - 1] = -(1.0 / (h * h) - p(t) / (2.0 * h));
        fi[i - 1] = -r(t);
    }
    fi[0]     -= ai[0] * alfa;          // a_1 y c_N pasan al termino independiente
    fi[N - 1] -= ci[N - 1] * beta;
    double *w_int = tridiag_vect_solve(ai, bi, ci, fi, N);
    double *w = new double[N + 2];
    w[0] = alfa; w[N + 1] = beta;
    for (int i = 0; i < N; i++) w[i + 1] = w_int[i];
    delete[] ai; delete[] bi; delete[] ci; delete[] fi; delete[] w_int;
    return w;
}
#endif // MC_FN_dif_finitas_bvp

#endif // MATCLUB_EDO_FRONTERA_CPP
