// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas sobredeterminados y regresiones
// ============================================================================
// Minimos cuadrados (ecuaciones normales) y regresiones lineal, polinomica, exponencial, logaritmica, potencial y sinusoidal.
//
// Funciones (7): ols_reg, poly_reg, lin_reg, exp_reg, regresion_logaritmica, regresion_potencial, regresion_sinusoidal
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_MINIMOS_CUADRADOS_H
#define MATCLUB_MINIMOS_CUADRADOS_H

// 0. MOTOR CENTRAL: Resuelve Ax = b para sistemas sobredeterminados (m > n)
// Devuelve el vector solucion 'x', y por referencia el vector de 'errores' de
// cada parametro, y el coeficiente de determinacion 'R2'.
// -----> Ordinary Least Squares, OLS, minimos cuadrados
double* ols_reg(double **A, double *b, int m, int n, double *&errores, double &R2);

// 1. Regresión Polinómica: y = a0 + a1*x + a2*x^2 + ... + am*x^m
// Devuelve un vector con [a0, a1, ..., am]
double* poly_reg(double *x, double *y, int m_datos, int grado, double *&errores, double &R2);

// 2. Regresión Lineal: y = a0 + a1*x
// (Es simplemente un caso particular de la regresion polinomica de grado 1)
double* lin_reg(double *x, double *y, int m_datos, double *&errores, double &R2);

// 3. Regresión Exponencial: y = a * e^(bx)
// Devuelve [a, b]. Realiza la linealizacion: ln(y) = ln(a) + b*x
double* exp_reg(double *x, double *y, int m_datos, double *&errores, double &R2);

// 4. Regresión Logarítmica: y = a + b * ln(x)
// Devuelve [a, b]. Realiza la linealizacion: Y = a + b*X (con X = ln(x))
double* regresion_logaritmica(double *x, double *y, int m_datos, double *&errores, double &R2);

// 5. Regresión Potencial: y = a * x^b
// Devuelve [a, b]. Realiza linealizacion bilogaritmica: ln(y) = ln(a) + b*ln(x)
double* regresion_potencial(double *x, double *y, int m_datos, double *&errores, double &R2);

// 6. Regresión Sinusoidal / Armónica: y = a0 + a1*cos(w*x) + a2*sin(w*x)
// Devuelve [a0, a1, a2]. Requiere que le introduzcas la frecuencia angular 'w'
double* regresion_sinusoidal(double *x, double *y, int m_datos, double w, double *&errores, double &R2);

#endif // MATCLUB_MINIMOS_CUADRADOS_H
