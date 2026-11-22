// ============================================================================
// MATCLUB-CPP  |  BLOQUE IV: INTEGRACION Y DERIVACION  |  IV.1
// Integracion numerica
// ============================================================================
// Trapecio y Simpson (simples y compuestas), Richardson, Romberg, cuadratura de Gauss-Legendre e integrales multiples.
//
// Funciones (22): integral_def_func, integral_indef_func, int_vect, nc_trapecio, nc_simpson13, nc_simpson38, trapecio_comp_func, simpson38_comp_func, trapecio_comp_vect, simpson13_comp_vect, simpson38_comp_vect, richardson_int, romberg_mat, romberg_int, gauss_legendre_nodos, gauss_legendre_func, pesos_nc, integral_doble_func, integral_triple_func, integral_doble_mat, gauss_doble_func, gauss_triple_func
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_INTEGRACION_H
#define MATCLUB_INTEGRACION_H

// Integral Definida Numérica de una función (Regla de Simpson 1/3)
// Descripción: Calcula el área bajo la curva de la función 'f' en el intervalo [a, b] con 'n' paneles (n par).
double integral_def_func(double (*f)(double), double a, double b, int n);

// Integral Indefinida Numérica de una función sobre un dominio discreto
// Descripción: Evalúa la integral acumulativa de 'f' sobre los puntos del vector 'x', sumando la constante 'C'.
double* integral_indef_func(double (*f)(double), double *x, int n_puntos, double C);

// Integral Numérica de datos discretos (Vectorial)
// Descripción: Calcula la integral definida e indefinida (acumulada) usando la regla del trapecio.
// Nota: 'int_indef' se devuelve por return, 'int_def' se extrae por referencia (&).
double* int_vect(double *x, double *y, int n, double y0, double &int_def);

// Newton-Cotes cerrada n=1: Regla Trapezoidal simple
// Descripción: I = h/2*(f(a)+f(b)) con h = b-a. Error = -h^3/12*f''(xi). Exacta para polinomios de grado 1.
double nc_trapecio(double (*f)(double), double a, double b);

// Newton-Cotes cerrada n=2: Regla de 1/3 de Simpson simple
// Descripción: I = h/3*(f(x0)+4f(x1)+f(x2)) con h = (b-a)/2. Error = -h^5/90*f''''(xi). Exacta para polinomios de grado <= 3.
double nc_simpson13(double (*f)(double), double a, double b);

// Newton-Cotes cerrada n=3: Regla de 3/8 de Simpson simple
// Descripción: I = 3h/8*(f(x0)+3f(x1)+3f(x2)+f(x3)) con h = (b-a)/3. Error = -3h^5/80*f''''(xi). Exacta para polinomios de grado <= 3.
double nc_simpson38(double (*f)(double), double a, double b);

// Regla Trapezoidal compuesta (con función)
// Descripción: Divide [a,b] en 'n' subintervalos y suma trapecios: h*(f0/2 + f1 + ... + f(n-1) + fn/2). Error global O(h^2).
double trapecio_comp_func(double (*f)(double), double a, double b, int n);

// Regla de 3/8 de Simpson compuesta (con función)
// Descripción: Aplica Simpson 3/8 en grupos de 3 subintervalos (n debe ser multiplo de 3; si no lo es se sube al siguiente multiplo). Error global O(h^4).
double simpson38_comp_func(double (*f)(double), double a, double b, int n);

// Regla Trapezoidal compuesta (datos tabulados equiespaciados)
// Descripción: Integra los valores y[0..n_puntos-1] separados una distancia 'h'. (Para espaciado no uniforme usar int_vect).
double trapecio_comp_vect(double *y, int n_puntos, double h);

// Regla de 1/3 de Simpson compuesta (datos tabulados equiespaciados)
// Descripción: Necesita un numero PAR de subintervalos (n_puntos impar). Si es impar, se usa la regla trapezoidal en el ultimo subintervalo y Simpson en el resto.
double simpson13_comp_vect(double *y, int n_puntos, double h);

// Regla de 3/8 de Simpson compuesta (datos tabulados equiespaciados)
// Descripción: Necesita que el numero de subintervalos (n_puntos-1) sea multiplo de 3.
double simpson38_comp_vect(double *y, int n_puntos, double h);

// Extrapolación de Richardson para integrales
// Descripción: Combina dos estimaciones I_n1 e I_n2 (con n1 y n2 subintervalos) en una mejorada: I* = I_n1 + (I_n2 - I_n1)/(1 - (n1/n2)^p).
// p = 2 para la regla trapezoidal y p = 4 para Simpson. Con n2 = 2*n1 equivale a (4*I_n2 - I_n1)/3 (trapecio) o (16*I_n2 - I_n1)/15 (Simpson).
double richardson_int(double I_n1, double I_n2, double n1, double n2, double p);

// Tabla de Romberg
// Descripción: Devuelve la matriz T[(N+1)x(N+1)] triangular inferior. T[i][0] es la regla trapezoidal con 2^i subintervalos y
// T[i][j] = (4^j*T[i][j-1] - T[i-1][j-1])/(4^j - 1) la j-esima extrapolacion de Richardson. Liberar con del_mat(T, N+1).
double** romberg_mat(double (*f)(double), double a, double b, int N);

// Integración de Romberg con criterio de parada
// Descripción: Aumenta N hasta que dos valores consecutivos de la ultima fila de la tabla difieran menos que 'tol'. N_out devuelve el N usado.
double romberg_int(double (*f)(double), double a, double b, double tol, int N_max, int &N_out);

// Nodos y pesos de la cuadratura de Gauss-Legendre
// Descripción: Calcula los 'n' nodos x (raices del polinomio de Legendre de grado n, en [-1,1]) y sus pesos w. Exacta para polinomios de grado <= 2n-1.
// x y w se devuelven por referencia (new[]).
void gauss_legendre_nodos(int n, double *&x, double *&w);

// Cuadratura gaussiana (Gauss-Legendre) de una función en [a,b]
// Descripción: Cambio de variable z = ((b-a)*x + b + a)/2 y suma ponderada de 'n' evaluaciones. Muy precisa con pocas evaluaciones si f es suave.
double gauss_legendre_func(double (*f)(double), double a, double b, int n);

// Pesos de Newton-Cotes compuestas
// Descripción: Devuelve los n+1 pesos para 'n' subintervalos de longitud h. regla = 1 (trapecio), 2 (Simpson 1/3, n par) o 3 (Simpson 3/8, n multiplo de 3).
// Sirve para escribir una integral como suma ponderada sum(w_i*f(x_i)) y extenderla a integrales multiples.
double* pesos_nc(int n, int regla, double h);

// Integral doble de una función f(x,y) sobre [ax,bx] x [ay,by]
// Descripción: Doble sumatoria sum_j sum_i wy[j]*wx[i]*f(x_i,y_j) con 'nx' y 'ny' subintervalos y la regla elegida en cada direccion (rx, ry = 1, 2 o 3 como en pesos_nc).
double integral_doble_func(double (*f)(double, double), double ax, double bx, double ay, double by, int nx, int ny, int rx, int ry);

// Integral triple de una función f(x,y,z) sobre un paralelepipedo
// Descripción: Triple sumatoria con pesos w_ijk = a_i*b_j*c_k (nx, ny, nz subintervalos; reglas rx, ry, rz = 1, 2 o 3).
double integral_triple_func(double (*f)(double, double, double), double ax, double bx, double ay, double by, double az, double bz, int nx, int ny, int nz, int rx, int ry, int rz);

// Integral doble de datos tabulados f(x_i, y_j) en una malla equiespaciada
// Descripción: F es una matriz (ny+1) x (nx+1) con F[j][i] = f(x_i, y_j). Aplica la regla rx en la direccion x y ry en la y (como el ejemplo de la teoria:
// trapecio en x y Simpson 1/3 en y).
double integral_doble_mat(double **F, int nx, int ny, double hx, double hy, int rx, int ry);

// Integral doble por cuadratura gaussiana
// Descripción: Usa 'nx' nodos de Gauss-Legendre en x y 'ny' en y (cada direccion puede tener un numero distinto de terminos).
double gauss_doble_func(double (*f)(double, double), double ax, double bx, double ay, double by, int nx, int ny);

// Integral triple por cuadratura gaussiana
// Descripción: Usa nx, ny y nz nodos de Gauss-Legendre en cada direccion (ejemplo de la teoria: 3 terminos en x y 2 en y, z).
double gauss_triple_func(double (*f)(double, double, double), double ax, double bx, double ay, double by, double az, double bz, int nx, int ny, int nz);

#endif // MATCLUB_INTEGRACION_H
