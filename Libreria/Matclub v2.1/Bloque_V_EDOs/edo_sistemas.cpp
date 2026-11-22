// ============================================================================
// MATCLUB-CPP  |  BLOQUE V: EDOs  |  V.2
// Sistemas de EDO's y EDO's de orden superior
// ============================================================================
// Euler, Euler mejorado, Runge-Kutta 4 y Runge-Kutta-Fehlberg para sistemas, y EDO's de orden n.
//
// Funciones (7): eval_sys, euler_sys, euler_mejorado_sys, rk4_sys, rkf45_paso_sys, rkf45_sys, rk4_orden_n
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Helper: evalua el vector de derivadas dy_i/dt = AF[i](t, y, n)

void eval_sys(double (*AF[])(double, double*, int), double t, double *y, int n, double *dy) {
    for (int i = 0; i < n; i++) dy[i] = AF[i](t, y, n);
}

// Método de Euler para sistemas de EDO's
// Descripción: Resuelve y_i' = AF[i](t, y) con 'n' ecuaciones y condiciones iniciales y0[0..n-1]. Devuelve una matriz (pasos+1) x n (una fila por instante);
// t_out contiene los tiempos (new[]). Liberar la matriz con del_mat(Y, pasos+1).

double** euler_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, int pasos, double *&t_out) {
    /*
    Ejemplo de uso:
        double f1(double t, double *y, int n) { return y[1]; }          // y' = v
        double f2(double t, double *y, int n) { return -y[0]; }         // v' = -y
        double (*AF[2])(double, double*, int) = {f1, f2};
        double y0[] = {1.0, 0.0}, *t;
        double **Y = euler_sys(AF, 0.0, y0, 2, 10.0, 1000, t);
    */
    if (pasos < 1 || n < 1) { print_error("euler_sys: pasos y n deben ser >= 1"); t_out = NULL; return NULL; }
    double h = (tf - t0) / pasos;
    double **Y = zeros_mat(pasos + 1, n);
    t_out = new double[pasos + 1];
    double *dy = new double[n];
    t_out[0] = t0;
    for (int j = 0; j < n; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        eval_sys(AF, t_out[i], Y[i], n, dy);
        for (int j = 0; j < n; j++) Y[i + 1][j] = Y[i][j] + h * dy[j];
        t_out[i + 1] = t0 + (i + 1) * h;
    }
    delete[] dy;
    return Y;
}

// Método de Euler mejorado para sistemas de EDO's
// Descripción: Predictor-corrector aplicado a todas las ecuaciones a la vez ('n_corr' correcciones; 1 = Heun). Mismos argumentos y salida que euler_sys.

double** euler_mejorado_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf,
                            int pasos, double *&t_out, int n_corr) {
    /*
    Ejemplo de uso:
        double **Y = euler_mejorado_sys(AF, 0.0, y0, 2, 10.0, 1000, t, 1);
    */
    if (pasos < 1 || n < 1 || n_corr < 1) { print_error("euler_mejorado_sys: pasos, n y n_corr deben ser >= 1"); t_out = NULL; return NULL; }
    double h = (tf - t0) / pasos;
    double **Y = zeros_mat(pasos + 1, n);
    t_out = new double[pasos + 1];
    double *d0 = new double[n], *d1 = new double[n], *yp = new double[n];
    t_out[0] = t0;
    for (int j = 0; j < n; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        eval_sys(AF, t_out[i], Y[i], n, d0);
        for (int j = 0; j < n; j++) yp[j] = Y[i][j] + h * d0[j];                       // prediccion
        for (int c = 0; c < n_corr; c++) {
            eval_sys(AF, t_out[i] + h, yp, n, d1);
            for (int j = 0; j < n; j++) yp[j] = Y[i][j] + h * (d0[j] + d1[j]) / 2.0;   // correccion
        }
        for (int j = 0; j < n; j++) Y[i + 1][j] = yp[j];
        t_out[i + 1] = t0 + (i + 1) * h;
    }
    delete[] d0; delete[] d1; delete[] yp;
    return Y;
}

// Método de Runge-Kutta de cuarto orden para sistemas de EDO's
// Descripción: Calcula en paralelo los vectores k1..k4 de todas las variables dependientes. Mismos argumentos y salida que euler_sys.

double** rk4_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, int pasos, double *&t_out) {
    /*
    Ejemplo de uso:
        double **Y = rk4_sys(AF, 0.0, y0, 2, 10.0, 1000, t);   // oscilador armonico
        print_vect(get_row_mat(Y, 1001, 2, 1000), 2, "y(10), v(10)");
    */
    if (pasos < 1 || n < 1) { print_error("rk4_sys: pasos y n deben ser >= 1"); t_out = NULL; return NULL; }
    double h = (tf - t0) / pasos;
    double **Y = zeros_mat(pasos + 1, n);
    t_out = new double[pasos + 1];
    double *k1 = new double[n], *k2 = new double[n], *k3 = new double[n], *k4 = new double[n], *tmp = new double[n];
    t_out[0] = t0;
    for (int j = 0; j < n; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        double t = t_out[i];
        double *y = Y[i];
        eval_sys(AF, t, y, n, k1);
        for (int j = 0; j < n; j++) tmp[j] = y[j] + 0.5 * h * k1[j];
        eval_sys(AF, t + 0.5 * h, tmp, n, k2);
        for (int j = 0; j < n; j++) tmp[j] = y[j] + 0.5 * h * k2[j];
        eval_sys(AF, t + 0.5 * h, tmp, n, k3);
        for (int j = 0; j < n; j++) tmp[j] = y[j] + h * k3[j];
        eval_sys(AF, t + h, tmp, n, k4);
        for (int j = 0; j < n; j++) Y[i + 1][j] = y[j] + h / 6.0 * (k1[j] + 2.0 * k2[j] + 2.0 * k3[j] + k4[j]);
        t_out[i + 1] = t0 + (i + 1) * h;
    }
    delete[] k1; delete[] k2; delete[] k3; delete[] k4; delete[] tmp;
    return Y;
}

// Paso de Runge-Kutta-Fehlberg para sistemas
// Descripción: Avanza un paso h desde (t,y) para las n ecuaciones. Devuelve en y5 (n valores, new[]) la solucion de 5o orden y en err el vector y5 - y4 (new[]).

void rkf45_paso_sys(double (*AF[])(double, double*, int), double t, double *y, int n, double h, double *&y5, double *&err) {
    /*
    Ejemplo de uso:
        double *y5, *err;
        rkf45_paso_sys(AF, 0.0, y0, 2, 0.1, y5, err);
    */
    double **k = zeros_mat(6, n);
    double *tmp = new double[n];
    y5 = new double[n];
    err = new double[n];
    eval_sys(AF, t, y, n, k[0]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * k[0][j] / 4.0;
    eval_sys(AF, t + h / 4.0, tmp, n, k[1]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (3.0 * k[0][j] / 32.0 + 9.0 * k[1][j] / 32.0);
    eval_sys(AF, t + 3.0 * h / 8.0, tmp, n, k[2]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (1932.0 * k[0][j] / 2197.0 - 7200.0 * k[1][j] / 2197.0 + 7296.0 * k[2][j] / 2197.0);
    eval_sys(AF, t + 12.0 * h / 13.0, tmp, n, k[3]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (439.0 * k[0][j] / 216.0 - 8.0 * k[1][j] + 3680.0 * k[2][j] / 513.0 - 845.0 * k[3][j] / 4104.0);
    eval_sys(AF, t + h, tmp, n, k[4]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (-8.0 * k[0][j] / 27.0 + 2.0 * k[1][j] - 3544.0 * k[2][j] / 2565.0 + 1859.0 * k[3][j] / 4104.0 - 11.0 * k[4][j] / 40.0);
    eval_sys(AF, t + h / 2.0, tmp, n, k[5]);
    for (int j = 0; j < n; j++) {
        double y4 = y[j] + h * (25.0 * k[0][j] / 216.0 + 1408.0 * k[2][j] / 2565.0 + 2197.0 * k[3][j] / 4104.0 - k[4][j] / 5.0);
        y5[j] = y[j] + h * (16.0 * k[0][j] / 135.0 + 6656.0 * k[2][j] / 12825.0 + 28561.0 * k[3][j] / 56430.0 - 9.0 * k[4][j] / 50.0 + 2.0 * k[5][j] / 55.0);
        err[j] = y5[j] - y4;
    }
    del_mat(k, 6);
    delete[] tmp;
}

// Método de Runge-Kutta-Fehlberg adaptativo para sistemas
// Descripción: Como rkf45_edo pero para n ecuaciones; el error de un paso es el mayor |err_j|. Devuelve una matriz n_out x n (new[]) y t_out con los tiempos.

double** rkf45_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, double h0, double tol,
                   int max_pasos, double *&t_out, int &n_out) {
    /*
    Ejemplo de uso:
        double *t; int np;
        double **Y = rkf45_sys(AF, 0.0, y0, 2, 10.0, 0.1, 1e-8, 100000, t, np);
    */
    int cap = 64;
    double **Y = new double*[cap];
    t_out = new double[cap];
    Y[0] = copy_vect(y0, n);
    t_out[0] = t0;
    n_out = 1;
    double sentido = (tf >= t0) ? 1.0 : -1.0;
    double h = fabs(h0) * sentido;
    int pasos = 0;
    while ((tf - t_out[n_out - 1]) * sentido > 1e-14 * fabs(tf - t0) && pasos < max_pasos) {
        double t = t_out[n_out - 1];
        if ((t + h - tf) * sentido > 0.0) h = tf - t;
        double *y5, *err;
        rkf45_paso_sys(AF, t, Y[n_out - 1], n, h, y5, err);
        double e = 0.0;
        for (int j = 0; j < n; j++) if (fabs(err[j]) > e) e = fabs(err[j]);
        if (e <= tol || fabs(h) < 1e-14) {
            if (n_out >= cap) {
                int ncap = 2 * cap;
                double **tY = new double*[ncap], *tt = new double[ncap];
                for (int i = 0; i < n_out; i++) { tY[i] = Y[i]; tt[i] = t_out[i]; }
                delete[] Y; delete[] t_out;
                Y = tY; t_out = tt; cap = ncap;
            }
            Y[n_out] = y5;
            t_out[n_out] = t + h;
            n_out++;
        } else delete[] y5;
        delete[] err;
        double factor = (e == 0.0) ? 5.0 : 0.9 * pow(tol / e, 0.2);
        if (factor > 5.0) factor = 5.0;
        if (factor < 0.1) factor = 0.1;
        h *= factor;
        pasos++;
    }
    if (pasos >= max_pasos) print_warning("rkf45_sys alcanzo max_pasos antes de llegar a tf.");
    return Y;
}

// EDO de orden superior con Runge-Kutta de cuarto orden
// Descripción: Resuelve y^(m) = f(x, y, y', ..., y^(m-1)) con m = 'orden', convirtiendola en un sistema de m ecuaciones de primer orden (y1 = y, y2 = y', ...).
// f(x, y, m) recibe el vector y = {y, y', ..., y^(m-1)} y devuelve y^(m). y0[0..m-1] son las condiciones iniciales.
// Devuelve una matriz (pasos+1) x m: columna 0 = y, columna 1 = y', etc.; x_out contiene las abscisas.

double** rk4_orden_n(double (*f)(double, double*, int), double x0, double *y0, int orden, double xf, int pasos, double *&x_out) {
    /*
    Ejemplo de uso:
        // Circuito RLC: V'' = -(R/L)*V' - V/(L*C),  V(0) = 10, V'(0) = 0
        double rlc(double t, double *y, int m) { return -(1000.0/0.5)*y[1] - y[0]/(0.5*2e-6); }
        double y0[] = {10.0, 0.0}, *t;
        double **V = rk4_orden_n(rlc, 0.0, y0, 2, 0.02, 200, t);
    */
    if (pasos < 1 || orden < 1) { print_error("rk4_orden_n: pasos y orden deben ser >= 1"); x_out = NULL; return NULL; }
    int m = orden;
    double h = (xf - x0) / pasos;
    double **Y = zeros_mat(pasos + 1, m);
    x_out = new double[pasos + 1];
    double *k1 = new double[m], *k2 = new double[m], *k3 = new double[m], *k4 = new double[m], *tmp = new double[m];
    x_out[0] = x0;
    for (int j = 0; j < m; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        double x = x_out[i];
        double *y = Y[i];
        for (int j = 0; j < m - 1; j++) k1[j] = y[j + 1];
        k1[m - 1] = f(x, y, m);
        for (int j = 0; j < m; j++) tmp[j] = y[j] + 0.5 * h * k1[j];
        for (int j = 0; j < m - 1; j++) k2[j] = tmp[j + 1];
        k2[m - 1] = f(x + 0.5 * h, tmp, m);
        for (int j = 0; j < m; j++) tmp[j] = y[j] + 0.5 * h * k2[j];
        for (int j = 0; j < m - 1; j++) k3[j] = tmp[j + 1];
        k3[m - 1] = f(x + 0.5 * h, tmp, m);
        for (int j = 0; j < m; j++) tmp[j] = y[j] + h * k3[j];
        for (int j = 0; j < m - 1; j++) k4[j] = tmp[j + 1];
        k4[m - 1] = f(x + h, tmp, m);
        for (int j = 0; j < m; j++) Y[i + 1][j] = y[j] + h / 6.0 * (k1[j] + 2.0 * k2[j] + 2.0 * k3[j] + k4[j]);
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    delete[] k1; delete[] k2; delete[] k3; delete[] k4; delete[] tmp;
    return Y;
}

