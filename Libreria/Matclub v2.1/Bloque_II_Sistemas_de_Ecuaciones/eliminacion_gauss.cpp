// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: eliminacion de Gauss y Gauss-Jordan
// ============================================================================
// Metodos directos de eliminacion, con deteccion de matrices singulares.
//
// Funciones (2): gauss_solve, gauss_jordan_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Eliminación de Gauss con pivoteo parcial

double* gauss_solve(double **A, double *b, int n) {
    // Trabajamos sobre copias para no destruir las matrices originales
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    double *x = new double[n];

    for (int j = 0; j < n - 1; j++) {
        // 1. Pivoteo parcial para evitar división por cero y reducir errores de redondeo
        double pivote = fabs(M[j][j]);
        int filapivote = j;
        for (int i = j + 1; i < n; i++) {
            if (fabs(M[i][j]) > pivote) {
                pivote = fabs(M[i][j]);
                filapivote = i;
            }
        }

        // Intercambio de filas si es necesario
        if (filapivote != j) {
            for (int k = 0; k < n; k++) intercambiar_elem(M[j][k], M[filapivote][k]);
            intercambiar_elem(vb[j], vb[filapivote]);
        }

        if (fabs(M[j][j]) < 1e-12) {
            print_error("Matriz singular o casi singular detectada en Gauss.");
            return NULL;
        }

        // 2. Hacer ceros por debajo de la diagonal
        for (int i = j + 1; i < n; i++) {
            double factor = M[i][j] / M[j][j]; // Razón de coeficientes
            for (int k = j; k < n; k++) {
                M[i][k] = M[i][k] - factor * M[j][k];
            }
            vb[i] = vb[i] - factor * vb[j];
        }
    }

    // 3. Sustitución regresiva
    for (int j = n - 1; j >= 0; j--) {
        x[j] = vb[j];
        for (int k = j + 1; k < n; k++) {
            x[j] = x[j] - M[j][k] * x[k];
        }
        x[j] = x[j] / M[j][j];
    }

    del_mat(M, n); delete[] vb;
    return x;
}

// Método de Gauss-Jordan (Diagonal a 1, ceros arriba y abajo)

double* gauss_jordan_solve(double **A, double *b, int n) {
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    for (int i = 0; i < n; i++) {
        // Pivoteo
        double pivote = fabs(M[i][i]);
        int filapivote = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(M[k][i]) > pivote) {
                pivote = fabs(M[k][i]);
                filapivote = k;
            }
        }
        if (filapivote != i) {
            for (int k = 0; k < n; k++) intercambiar_elem(M[i][k], M[filapivote][k]);
            intercambiar_elem(vb[i], vb[filapivote]);
        }
        
        // Normalizar la fila pivote para que el elemento diagonal sea 1
        double divisor = M[i][i];
        if (fabs(divisor) < 1e-12) {
            print_error("Matriz singular detectada en Gauss-Jordan.");
            return NULL;
        }
        for (int j = 0; j < n; j++) M[i][j] /= divisor;
        vb[i] /= divisor;
        
        // Hacer cero el resto de la columna i (por encima y por debajo)
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = M[k][i];
                for (int j = 0; j < n; j++) M[k][j] -= factor * M[i][j];
                vb[k] -= factor * vb[i];
            }
        }
    }
    
    del_mat(M, n); 
    return vb; // vb se ha transformado en el vector solución
}

