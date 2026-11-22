// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas sobredeterminados y regresiones
// ============================================================================
// Minimos cuadrados (ecuaciones normales) y regresiones lineal, polinomica, exponencial, logaritmica, potencial y sinusoidal.
//
// Funciones (7): ols_reg, poly_reg, lin_reg, exp_reg, regresion_logaritmica, regresion_potencial, regresion_sinusoidal
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// 0. MOTOR CENTRAL: Resuelve Ax = b para sistemas sobredeterminados (m > n)
		// Devuelve el vector solucion 'x', y por referencia el vector de 'errores' de 
							// cada parametro, y el coeficiente de determinacion 'R2'.
							// -----> Ordinary Least Squares, OLS, minimos cuadrados

double* ols_reg(double **A, double *b, int m, int n, double *&errores, double &R2) {
    if (m <= n) {
        print_error("El sistema no esta sobredeterminado (m debe ser mayor que n).");
        return NULL;
    }

    // 1. Ecuaciones normales: (A^T * A) * x = A^T * b
    double **AT = transpose_mat(A, m, n);
    double **ATA = prod_mat(AT, A, n, m, m, n);  // Matriz cuadrada (n x n)
    double *ATb = prod_mat_vect(AT, n, m, b, m); // Vector (n x 1)

    // 2. Resolver el sistema para encontrar los parametros óptimos (x) usando LU Forma 2
    double *x = lu_forma2_sol(ATA, ATb, n);
    if (x == NULL) {
        print_error("Fallo al resolver minimos cuadrados (A^T*A es singular o casi singular).");
        del_mat(AT, n); del_mat(ATA, n); delete[] ATb;
        return NULL;
    }

    // 3. Calculo del coeficiente de determinacion R2
    double *b_est = prod_mat_vect(A, m, n, x, n);
    double mean_b = mean_vect(b, m);

    double SS_res = 0.0; // Suma de los residuos al cuadrado
    double SS_tot = 0.0; // Suma total al cuadrado
    for (int i = 0; i < m; i++) {
        SS_res += pow(b[i] - b_est[i], 2);
        SS_tot += pow(b[i] - mean_b, 2);
    }
    R2 = (SS_tot == 0.0) ? 1.0 : (1.0 - (SS_res / SS_tot));

    // 4. Calculo de Errores estadisticos (usando la matriz de covarianza con la inversa LU)
    double s2 = SS_res / (m - n); // Varianza residual
    double **ATA_inv = inv_lu(ATA, n); // Cambiado para usar el metodo LU en la inversa
    errores = new double[n];
    
    if (ATA_inv != NULL) {
        for (int j = 0; j < n; j++) {
            // Error estandar del parametro j (raiz de la diagonal de la covarianza)
            errores[j] = sqrt(fabs(s2 * ATA_inv[j][j])); 
        }
        del_mat(ATA_inv, n);
    } else {
        print_warning("No se pudieron calcular los errores de los parametros mediante LU.");
        for (int j = 0; j < n; j++) errores[j] = MC_NAN;
    }

    // Limpieza de memoria
    del_mat(AT, n);
    del_mat(ATA, n);
    delete[] ATb;
    delete[] b_est;

    return x;
}

// 1. Regresión Polinómica: y = a0 + a1*x + a2*x^2 + ... + am*x^m
						// Devuelve un vector con [a0, a1, ..., am]

double* poly_reg(double *x, double *y, int m_datos, int grado, double *&errores, double &R2) {
    int n = grado + 1; // Numero de incognitas (parametros)
    double **A = gen_mat(A, m_datos, n);
    
    // Matriz de Vandermonde truncada
    for (int i = 0; i < m_datos; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = pow(x[i], j);
        }
    }
    
    double *params = ols_reg(A, y, m_datos, n, errores, R2);
    del_mat(A, m_datos);
    return params;
}

// 2. Regresión Lineal: y = a0 + a1*x 
// (Es simplemente un caso particular de la regresion polinomica de grado 1)

double* lin_reg(double *x, double *y, int m_datos, double *&errores, double &R2) {
    return poly_reg(x, y, m_datos, 1, errores, R2);
}

// 3. Regresión Exponencial: y = a * e^(bx)
		// Devuelve [a, b]. Realiza la linealizacion: ln(y) = ln(a) + b*x

double* exp_reg(double *x, double *y, int m_datos, double *&errores, double &R2) {
    double *ln_y = new double[m_datos];
    for (int i = 0; i < m_datos; i++) {
        if (y[i] <= 0.0) {
            print_error("Valores de y deben ser positivos para la regresion exponencial.");
            delete[] ln_y; return NULL;
        }
        ln_y[i] = log(y[i]);
    }

    double *err_lin = NULL;
    double *params_lin = lin_reg(x, ln_y, m_datos, err_lin, R2);
    delete[] ln_y;

    if (params_lin == NULL) return NULL;

    double *params = new double[2];
    params[0] = exp(params_lin[0]); // Deshacemos el ln(a): a = e^A0
    params[1] = params_lin[1];      // b se mantiene igual

    errores = new double[2];
    // Propagacion de errores: si A0 = ln(a) -> a = e^A0 -> Error_a = a * Error_A0
    errores[0] = params[0] * err_lin[0]; 
    errores[1] = err_lin[1];

    delete[] params_lin;
    delete[] err_lin;
    
    return params;
}

// 4. Regresión Logarítmica: y = a + b * ln(x)
// Devuelve [a, b]. Realiza la linealizacion: Y = a + b*X (con X = ln(x))

double* regresion_logaritmica(double *x, double *y, int m_datos, double *&errores, double &R2) {
    double *ln_x = new double[m_datos];
    for (int i = 0; i < m_datos; i++) {
        if (x[i] <= 0.0) {
            print_error("Valores de x deben ser positivos para la regresion logaritmica.");
            delete[] ln_x; return NULL;
        }
        ln_x[i] = log(x[i]);
    }

    double *params = lin_reg(ln_x, y, m_datos, errores, R2);
    delete[] ln_x;
    
    return params;
}

// 5. Regresión Potencial: y = a * x^b
// Devuelve [a, b]. Realiza linealizacion bilogaritmica: ln(y) = ln(a) + b*ln(x)

double* regresion_potencial(double *x, double *y, int m_datos, double *&errores, double &R2) {
    double *ln_x = new double[m_datos];
    double *ln_y = new double[m_datos];
    
    for (int i = 0; i < m_datos; i++) {
        if (x[i] <= 0.0 || y[i] <= 0.0) {
            print_error("Valores de x e y deben ser positivos para regresion potencial.");
            delete[] ln_x; delete[] ln_y; return NULL;
        }
        ln_x[i] = log(x[i]);
        ln_y[i] = log(y[i]);
    }

    double *err_lin = NULL;
    double *params_lin = lin_reg(ln_x, ln_y, m_datos, err_lin, R2);
    delete[] ln_x; delete[] ln_y;

    if (params_lin == NULL) return NULL;

    double *params = new double[2];
    params[0] = exp(params_lin[0]); // a = e^A0
    params[1] = params_lin[1];      // b = A1

    errores = new double[2];
    // Propagacion de errores similar a la exponencial
    errores[0] = params[0] * err_lin[0];
    errores[1] = err_lin[1];

    delete[] params_lin;
    delete[] err_lin;
    
    return params;
}

// 6. Regresión Sinusoidal / Armónica: y = a0 + a1*cos(w*x) + a2*sin(w*x)
// Devuelve [a0, a1, a2]. Requiere que le introduzcas la frecuencia angular 'w'

double* regresion_sinusoidal(double *x, double *y, int m_datos, double w, double *&errores, double &R2) {
    int n = 3;
    double **A = gen_mat(A, m_datos, n);
    
    for (int i = 0; i < m_datos; i++) {
        A[i][0] = 1.0;
        A[i][1] = cos(w * x[i]);
        A[i][2] = sin(w * x[i]);
    }
    
    double *params = ols_reg(A, y, m_datos, n, errores, R2);
    del_mat(A, m_datos);
    
    return params;
}

