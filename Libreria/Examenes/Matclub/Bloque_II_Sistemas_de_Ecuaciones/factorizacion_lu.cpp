// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: factorizacion LU
// ============================================================================
// Factorizacion LU (Doolittle y Crout) y resolucion de sistemas con ella.
//
// Funciones (4): lu_forma1, lu_forma1_sol, lu_forma2, lu_forma2_sol
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Factorización LU (Forma 1 - Descomposición de Doolittle)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)

void lu_forma1(double **A, int n, double **L, double **U) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                // Elementos de U (diagonal y por encima)
                double sum = 0.0;
                for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
                U[i][j] = A[i][j] - sum;

                // Diagonal de L es 1.0 (Doolittle)
                if (i == j) L[i][j] = 1.0; 
                else L[i][j] = 0.0;
            } else {
                // Elementos de L (por debajo de la diagonal)
                double sum = 0.0;
                for (int k = 0; k < j; k++) sum += L[i][k] * U[k][j];
                
                if (U[j][j] == 0.0) {
                    print_warning("Cero en la diagonal de U. La factorizacion LU puede fallar.");
                }
                L[i][j] = (A[i][j] - sum) / U[j][j];
                U[i][j] = 0.0;
            }
        }
    }
}

// Resuelve Ax = b usando LU Forma 1

double* lu_forma1_sol(double **A, double *b, int n) {
    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    double *z = new double[n];
    double *x = new double[n];

    // 1. Obtener L y U
    lu_forma1(A, n, L, U);

    // 2. Lz = b (Sustitución progresiva)
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) sum += L[i][j] * z[j];
        z[i] = b[i] - sum;
    }

    // 3. Ux = z (Sustitución regresiva)
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) sum += U[i][j] * x[j];
        x[i] = (z[i] - sum) / U[i][i];
    }

    del_mat(L, n);
    del_mat(U, n);
    delete[] z;
    return x;
}

// Factorización LU (Forma 2 - Alternando fila U y columna L)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)

void lu_forma2(double **A, int n, double **L, double **U) {
    for (int i = 0; i < n; i++) {
        // Obtención de una fila de U
        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }
        
        // Obtención de una columna de L
        for (int j = i; j < n; j++) {
            if (j == i) {
                L[j][i] = 1.0; // Hacemos uno los elementos de la diagonal de L
            } else {
                double sum = 0.0;
                for (int k = 0; k < i; k++) sum += L[j][k] * U[k][i];
                
                if (U[i][i] == 0.0) {
                    print_warning("Cero en la diagonal de U. La factorizacion LU puede fallar.");
                }
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }
    }
}

// Resuelve Ax = b usando LU Forma 2

double* lu_forma2_sol(double **A, double *b, int n) {
    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    double *z = new double[n];
    double *x = new double[n];

    // 1. Obtener L y U a través de la nueva función void
    lu_forma2(A, n, L, U);

    // 2. Lz = b (Sustitución progresiva)
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) sum += L[i][j] * z[j];
        z[i] = b[i] - sum;
    }
    
    // 3. Ux = z (Sustitución regresiva)
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) sum += U[i][j] * x[j];
        x[i] = (z[i] - sum) / U[i][i];
    }

    del_mat(L, n); 
    del_mat(U, n); 
    delete[] z;
    
    return x;
}

