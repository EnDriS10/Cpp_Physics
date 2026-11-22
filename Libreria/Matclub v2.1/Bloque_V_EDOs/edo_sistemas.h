// ============================================================================
// MATCLUB-CPP  |  BLOQUE V: EDOs  |  V.2
// Sistemas de EDO's y EDO's de orden superior
// ============================================================================
// Euler, Euler mejorado, Runge-Kutta 4 y Runge-Kutta-Fehlberg para sistemas, y EDO's de orden n.
//
// Funciones (7): eval_sys, euler_sys, euler_mejorado_sys, rk4_sys, rkf45_paso_sys, rkf45_sys, rk4_orden_n
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_EDO_SISTEMAS_H
#define MATCLUB_EDO_SISTEMAS_H

// Helper: evalua el vector de derivadas dy_i/dt = AF[i](t, y, n)
void eval_sys(double (*AF[])(double, double*, int), double t, double *y, int n, double *dy);

// Método de Euler para sistemas de EDO's
// Descripción: Resuelve y_i' = AF[i](t, y) con 'n' ecuaciones y condiciones iniciales y0[0..n-1]. Devuelve una matriz (pasos+1) x n (una fila por instante);
// t_out contiene los tiempos (new[]). Liberar la matriz con del_mat(Y, pasos+1).
double** euler_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, int pasos, double *&t_out);

// Método de Euler mejorado para sistemas de EDO's
// Descripción: Predictor-corrector aplicado a todas las ecuaciones a la vez ('n_corr' correcciones; 1 = Heun). Mismos argumentos y salida que euler_sys.
double** euler_mejorado_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, int pasos, double *&t_out, int n_corr);

// Método de Runge-Kutta de cuarto orden para sistemas de EDO's
// Descripción: Calcula en paralelo los vectores k1..k4 de todas las variables dependientes. Mismos argumentos y salida que euler_sys.
double** rk4_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, int pasos, double *&t_out);

// Paso de Runge-Kutta-Fehlberg para sistemas
// Descripción: Avanza un paso h desde (t,y) para las n ecuaciones. Devuelve en y5 (n valores, new[]) la solucion de 5o orden y en err el vector y5 - y4 (new[]).
void rkf45_paso_sys(double (*AF[])(double, double*, int), double t, double *y, int n, double h, double *&y5, double *&err);

// Método de Runge-Kutta-Fehlberg adaptativo para sistemas
// Descripción: Como rkf45_edo pero para n ecuaciones; el error de un paso es el mayor |err_j|. Devuelve una matriz n_out x n (new[]) y t_out con los tiempos.
double** rkf45_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, double h0, double tol, int max_pasos, double *&t_out, int &n_out);

// EDO de orden superior con Runge-Kutta de cuarto orden
// Descripción: Resuelve y^(m) = f(x, y, y', ..., y^(m-1)) con m = 'orden', convirtiendola en un sistema de m ecuaciones de primer orden (y1 = y, y2 = y', ...).
// f(x, y, m) recibe el vector y = {y, y', ..., y^(m-1)} y devuelve y^(m). y0[0..m-1] son las condiciones iniciales.
// Devuelve una matriz (pasos+1) x m: columna 0 = y, columna 1 = y', etc.; x_out contiene las abscisas.
double** rk4_orden_n(double (*f)(double, double*, int), double x0, double *y0, int orden, double xf, int pasos, double *&x_out);

#endif // MATCLUB_EDO_SISTEMAS_H
