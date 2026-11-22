// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: matrices tridiagonales
// ============================================================================
// Algoritmo de Thomas (LU para sistemas tridiagonales), con la matriz completa o solo con las tres diagonales.
//
// Funciones (2): tridiag_solve, tridiag_vect_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Algoritmo de Thomas (Sistemas Tridiagonales)
// Los vectores a, b, c son las diagonales (inferior, principal, superior)

// Se le pasa la matriz completa A y el vector independiente f.
// La funcion extrae las diagonales automaticamente.

double* tridiag_solve(double **A, double *f, int n) {
    // 1. Extraccion de las diagonales de la matriz A
    double *a = new double[n - 1]; // Diagonal inferior
    double *b = new double[n];     // Diagonal principal
    double *c = new double[n - 1]; // Diagonal superior

    for (int i = 0; i < n; i++) {
        b[i] = A[i][i];
        if (i < n - 1) {
            a[i] = A[i + 1][i]; // Elemento justo debajo de la diagonal
            c[i] = A[i][i + 1]; // Elemento justo encima de la diagonal
        }
    }

    // 2. Vectores auxiliares para el Algoritmo de Thomas
    double *alpha = new double[n];
    double *beta = new double[n];
    double *z = new double[n];
    double *x = new double[n];

    // Paso 1: Factorización LU y Sustitución Progresiva (L * z = f)
    beta[0] = b[0];
    z[0] = f[0];

    for (int i = 1; i < n; i++) {
        if (beta[i - 1] == 0.0) {
            print_warning("Cero en la diagonal durante el algoritmo de Thomas (posible division por cero).");
        }
        alpha[i] = a[i - 1] / beta[i - 1];
        beta[i] = b[i] - alpha[i] * c[i - 1];
        z[i] = f[i] - alpha[i] * z[i - 1];
    }

    // Paso 2: Sustitución Regresiva (U * x = z)
    x[n - 1] = z[n - 1] / beta[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = (z[i] - c[i] * x[i + 1]) / beta[i];
    }

    // 3. Liberar toda la memoria temporal utilizada
    delete[] a; 
    delete[] b; 
    delete[] c;
    delete[] alpha; 
    delete[] beta; 
    delete[] z;

    return x;
}

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

