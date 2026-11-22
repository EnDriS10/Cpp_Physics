// ============================================================================
// MATCLUB-CPP  |  BLOQUE IV: INTEGRACION Y DERIVACION  |  IV.2
// Derivacion numerica
// ============================================================================
// Derivadas parciales, gradientes y jacobianos; formulas de 2, 3 y 5 puntos; extrapolacion de Richardson y derivadas de datos tabulados.
//
// Funciones (23): part_derv, total_derv, grad_vect, jacobian_mat, deriv_vect, deriv_prog_2p, deriv_reg_2p, deriv_prog_3p, deriv_reg_3p, deriv_cent_3p, deriv_prog_5p, deriv_cent_5p, deriv2_prog_3p, deriv2_cent_3p, deriv2_prog_5p, deriv2_cent_5p, deriv_func, richardson_deriv_mat, deriv_richardson, err_deriv_h_mat, deriv_vect_3p, deriv_vect_5p, deriv2_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_DERIVACION_H
#define MATCLUB_DERIVACION_H

// Derivada parcial numérica usando diferencias finitas progresivas.
// Descripción: Calcula el cambio de la función 'f' respecto a la variable 'j' variando 'h'.
double part_derv(double (*f)(double*, int), double *x, int n, int j);

// Derivada total
// Descripción: Calcula la derivada total dF/dt sumando el producto de las derivadas parciales por dx_i/dt.
double total_derv(double (*f)(double*, int), double *x, double *dx_dt, int n);

// Gradiente
// Descripción: Devuelve un vector con todas las derivadas parciales de una función escalar.
double* grad_vect(double (*f)(double*, int), double *x, int n);

// Matriz Jacobiana
// Descripción: Construye la matriz nxn de derivadas parciales para un sistema de n funciones.
double** jacobian_mat(double (*AF[])(double*, int), double *x, int n);

// Derivada Numérica de datos discretos (Vectorial)
// Descripción: Calcula dy/dx usando diferencias finitas. Diferencias centrales en el interior y progresivas/regresivas en los bordes.
double* deriv_vect(double *x, double *y, int n);

// Derivada primera, diferencias progresivas de 2 puntos
// Descripción: f'(x) ~ (f(x+h) - f(x))/h. Error O(h).
double deriv_prog_2p(double (*f)(double), double x, double h);

// Derivada primera, diferencias regresivas de 2 puntos
// Descripción: f'(x) ~ (f(x) - f(x-h))/h. Error O(h).
double deriv_reg_2p(double (*f)(double), double x, double h);

// Derivada primera, diferencias progresivas de 3 puntos
// Descripción: f'(x) ~ (-3f(x) + 4f(x+h) - f(x+2h))/(2h). Error O(h^2).
double deriv_prog_3p(double (*f)(double), double x, double h);

// Derivada primera, diferencias regresivas de 3 puntos
// Descripción: f'(x) ~ (3f(x) - 4f(x-h) + f(x-2h))/(2h). Error O(h^2).
double deriv_reg_3p(double (*f)(double), double x, double h);

// Derivada primera, diferencias centrales de 3 puntos
// Descripción: f'(x) ~ (f(x+h) - f(x-h))/(2h). Error O(h^2) (la mejor relacion precision/coste).
double deriv_cent_3p(double (*f)(double), double x, double h);

// Derivada primera, diferencias progresivas de 5 puntos
// Descripción: f'(x) ~ (-25f(x) + 48f(x+h) - 36f(x+2h) + 16f(x+3h) - 3f(x+4h))/(12h). Error O(h^4).
double deriv_prog_5p(double (*f)(double), double x, double h);

// Derivada primera, diferencias centrales de 5 puntos
// Descripción: f'(x) ~ (f(x-2h) - 8f(x-h) + 8f(x+h) - f(x+2h))/(12h). Error O(h^4).
double deriv_cent_5p(double (*f)(double), double x, double h);

// Derivada segunda, diferencias progresivas de 3 puntos
// Descripción: f''(x) ~ (f(x) - 2f(x+h) + f(x+2h))/h^2. Error O(h).
double deriv2_prog_3p(double (*f)(double), double x, double h);

// Derivada segunda, diferencias centrales de 3 puntos
// Descripción: f''(x) ~ (f(x-h) - 2f(x) + f(x+h))/h^2. Error O(h^2).
double deriv2_cent_3p(double (*f)(double), double x, double h);

// Derivada segunda, diferencias progresivas de 5 puntos
// Descripción: f''(x) ~ (35f(x) - 104f(x+h) + 114f(x+2h) - 56f(x+3h) + 11f(x+4h))/(12h^2). Error O(h^3).
double deriv2_prog_5p(double (*f)(double), double x, double h);

// Derivada segunda, diferencias centrales de 5 puntos
// Descripción: f''(x) ~ (-f(x-2h) + 16f(x-h) - 30f(x) + 16f(x+h) - f(x+2h))/(12h^2). Error O(h^4).
double deriv2_cent_5p(double (*f)(double), double x, double h);

// Derivada numérica con selección de fórmula
// Descripción: orden = 1 o 2 (derivada primera o segunda); puntos = 2, 3 o 5; tipo = 'p' (progresiva), 'r' (regresiva) o 'c' (central).
// Combinaciones validas: orden 1: p/r con 2, 3 o 5 puntos y c con 3 o 5; orden 2: p/r con 3 o 5 puntos y c con 3 o 5.
double deriv_func(double (*f)(double), double x, double h, int orden, int puntos, char tipo);

// Tabla de extrapolación de Richardson para derivadas
// Descripción: T[i][0] = diferencia central de 3 puntos con h_i = h0/2^i y T[i][j] = (4^j*T[i][j-1] - T[i-1][j-1])/(4^j - 1) (error O(h^(2j+2))).
// orden = 1 o 2 (derivada primera o segunda). Devuelve la matriz N x N (triangular inferior). Liberar con del_mat(T, N).
double** richardson_deriv_mat(double (*f)(double), double x0, double h0, int N, int orden);

// Derivada por extrapolación de Richardson
// Descripción: Devuelve la mejor estimacion (ultimo elemento de la tabla) con N niveles, partiendo de un paso h0 que se divide por 2 en cada nivel.
double deriv_richardson(double (*f)(double), double x0, double h0, int N, int orden);

// Estudio del error de la derivada en función de h (truncamiento frente a redondeo)
// Descripción: Devuelve una matriz n x 3 con [h, derivada central de 3 puntos, |error|] para h = h0, h0/10, h0/100, ... Muestra que reducir h indefinidamente
// empeora el resultado por el error de redondeo. 'exacta' es el valor exacto de f'(x0).
double** err_deriv_h_mat(double (*f)(double), double x0, double exacta, double h0, int n);

// Derivada primera de datos equiespaciados con error O(h^2) en todos los puntos
// Descripción: Diferencias centrales en el interior y progresiva/regresiva de 3 puntos en los extremos (n >= 3). Mejora a deriv_vect, que usa 2 puntos en los bordes.
double* deriv_vect_3p(double *y, int n, double h);

// Derivada primera de datos equiespaciados con error O(h^4) en el interior
// Descripción: Centrales de 5 puntos en i = 2..n-3, progresiva/regresiva de 5 puntos en los extremos y centrales de 3 puntos en i = 1 y n-2 (n >= 5).
double* deriv_vect_5p(double *y, int n, double h);

// Derivada segunda de datos equiespaciados
// Descripción: Diferencias centrales de 3 puntos en el interior (O(h^2)) y progresiva/regresiva de 3 puntos en los extremos (O(h)). n >= 3.
double* deriv2_vect(double *y, int n, double h);

#endif // MATCLUB_DERIVACION_H
