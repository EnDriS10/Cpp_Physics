// ============================================================================
// MATCLUB-CPP  |  BLOQUE V: EDOs  |  V.1
// EDO's con valores iniciales
// ============================================================================
// Serie de Taylor, Euler, Euler mejorado, Runge-Kutta de 2o y 4o orden y Runge-Kutta-Fehlberg adaptativo.
//
// Funciones (8): err_max_vect, taylor_eval, euler_edo, euler_mejorado_edo, rk2_edo, rk4_edo, rkf45_paso, rkf45_edo
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_EDO_VALORES_INICIALES_H
#define MATCLUB_EDO_VALORES_INICIALES_H

// Error máximo entre dos vectores
// Descripción: Devuelve max|a[i]-b[i]|. Util para comparar la solucion numerica con la analitica.
double err_max_vect(double *a, double *b, int n);

// Método de la serie de Taylor
// Descripción: Evalua y(x0+h) = sum_k y^(k)(x0)*h^k/k! a partir de las 'n' derivadas conocidas derivs[k] = y^(k)(x0), k = 0..n-1.
double taylor_eval(double *derivs, int n, double h);

// Método de Euler
// Descripción: y_(n+1) = y_n + h*f(x_n,y_n) con 'n' pasos entre x0 y xf. Devuelve y[0..n] y los puntos x en x_out (ambos new[]). Error global O(h).
double* euler_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out);

// Método de Euler mejorado (predictor-corrector)
// Descripción: Predice y_p = y_n + h*f(x_n,y_n) y corrige y_c = y_n + h*(f(x_n,y_n) + f(x_n+h,y_p))/2. 'n_corr' es el numero de correcciones (1 = metodo de Heun).
// Error local O(h^3) y global O(h^2).
double* euler_mejorado_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out, int n_corr);

// Método de Runge-Kutta de segundo orden (familia de un parametro)
// Descripción: y_(n+1) = y_n + a*k1 + b*k2 con b = 1-a, k1 = h*f(x,y), k2 = h*f(x+alfa*h, y+beta*k1) y alfa = beta = 1/(2b). 0 <= a < 1.
// a = 1/2 es Euler mejorado (Heun), a = 0 es el metodo del punto medio, a = 1/3 es Ralston.
double* rk2_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out, double a);

// Método de Runge-Kutta de cuarto orden
// Descripción: y_(n+1) = y_n + (k1 + 2k2 + 2k3 + k4)/6. Error local O(h^5) y global O(h^4).
double* rk4_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out);

// Paso de Runge-Kutta-Fehlberg (4o y 5o orden)
// Descripción: Avanza un paso h desde (x,y) con 6 evaluaciones de f. Devuelve el valor de 5o orden y, en 'err', la estimacion del error
// y5 - y4 = k1/360 - 128k3/4275 - 2197k4/75240 + k5/50 + 2k6/55.
double rkf45_paso(double (*f)(double, double), double x, double y, double h, double &err);

// Método de Runge-Kutta-Fehlberg con paso adaptativo
// Descripción: Parte del paso h0 y lo ajusta en cada iteracion (h_nuevo = 0.9*h*(tol/|err|)^(1/5)) para que el error por paso sea menor que 'tol'.
// Devuelve los valores y (new[]) en los puntos aceptados, x_out con las abscisas y n_out = numero de puntos. max_pasos limita el trabajo total.
double* rkf45_edo(double (*f)(double, double), double x0, double y0, double xf, double h0, double tol, int max_pasos, double *&x_out, int &n_out);

#endif // MATCLUB_EDO_VALORES_INICIALES_H
