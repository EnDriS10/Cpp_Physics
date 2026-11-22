// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Determinantes e inversas
// ============================================================================
// Determinante e inversa por Gauss, Gauss-Jordan y LU.
//
// Funciones (4): det_gauss, det_lu, inv_gj, inv_lu
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// 1A. Determinante usando Eliminación Gaussiana (con pivoteo)

double det_gauss(double **A, int n) {
    double **M = coppy_mat(A, n, n);
    double det = 1.0;
    int swaps = 0;

    for (int j = 0; j < n - 1; j++) {
        double pivote = fabs(M[j][j]);
        int filapivote = j;
        for (int i = j + 1; i < n; i++) {
            if (fabs(M[i][j]) > pivote) {
                pivote = fabs(M[i][j]);
                filapivote = i;
            }
        }

        if (filapivote != j) {
            for (int k = 0; k < n; k++) intercambiar_elem(M[j][k], M[filapivote][k]);
            swaps++; // Contamos los intercambios de filas
        }

        if (fabs(M[j][j]) < 1e-12) {
            del_mat(M, n);
            return 0.0; // Rango menor que n, determinante es cero
        }

        for (int i = j + 1; i < n; i++) {
            double factor = M[i][j] / M[j][j];
            for (int k = j; k < n; k++) {
                M[i][k] = M[i][k] - factor * M[j][k];
            }
        }
    }

    // El determinante es el producto de la diagonal de la matriz triangularizada
    for (int i = 0; i < n; i++) det *= M[i][i];
    
    // Aplicamos (-1)^swaps por los intercambios de filas
    if (swaps % 2 != 0) det = -det;

    del_mat(M, n);
    return det;
}

// 1B. Determinante usando Factorización LU (Doolittle)

double det_lu(double **A, int n) {
    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    
    // Llamamos a la función de descomposición que creaste antes
    lu_forma1(A, n, L, U); 

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        det *= U[i][i]; // El determinante es el producto de la diagonal de U
    }

    del_mat(L, n);
    del_mat(U, n);
    
    // Si la diagonal tiene ceros absolutos, el det es 0
    if (fabs(det) < 1e-12) return 0.0;
    return det;
}

// 2A. Inversa de una matriz usando Gauss-Jordan

double** inv_gj(double **A, int n) {
    if (fabs(det_gauss(A, n)) < 1e-12) {
        print_error("No tiene inversa. Matriz singular o determinante cero.");
        return NULL;
    }

    // Crear matriz aumentada [A | I] de n x 2n
    double **M = gen_mat(M, n, 2 * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) M[i][j] = A[i][j];
        for (int j = n; j < 2 * n; j++) M[i][j] = (j - n == i) ? 1.0 : 0.0;
    }

    // Reducción de Gauss-Jordan
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
            for (int k = 0; k < 2 * n; k++) intercambiar_elem(M[i][k], M[filapivote][k]);
        }
        
        // Normalizar
        double divisor = M[i][i];
        for (int j = 0; j < 2 * n; j++) M[i][j] /= divisor;
        
        // Hacer ceros el resto de la columna
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = M[k][i];
                for (int j = 0; j < 2 * n; j++) M[k][j] -= factor * M[i][j];
            }
        }
    }

    // Extraer la matriz inversa (la mitad derecha)
    double **Inv = gen_mat(Inv, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Inv[i][j] = M[i][j + n];
        }
    }

    del_mat(M, n);
    return Inv;
}

// 2B. Inversa de una matriz usando Factorización LU

double** inv_lu(double **A, int n) {
    if (fabs(det_lu(A, n)) < 1e-12) {
        print_error("No tiene inversa. Matriz singular o determinante cero.");
        return NULL;
    }

    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    lu_forma1(A, n, L, U);

    double **Inv = gen_mat(Inv, n, n);
    double *e = new double[n]; // Vector para cada columna de la identidad
    double *z = new double[n]; // Lz = e
    double *x = new double[n]; // Ux = z

    // Calculamos cada columna de la matriz inversa resolviendo LUx = e
    for (int col = 0; col < n; col++) {
        // 1. Generar la columna 'col' de la matriz identidad
        for (int i = 0; i < n; i++) {
            e[i] = (i == col) ? 1.0 : 0.0;
        }

        // 2. Sustitución progresiva (Lz = e)
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) sum += L[i][j] * z[j];
            z[i] = e[i] - sum;
        }

        // 3. Sustitución regresiva (Ux = z)
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++) sum += U[i][j] * x[j];
            x[i] = (z[i] - sum) / U[i][i];
        }

        // 4. Guardar el resultado en la columna correspondiente de la matriz inversa
        for (int i = 0; i < n; i++) {
            Inv[i][col] = x[i];
        }
    }

    del_mat(L, n);
    del_mat(U, n);
    delete[] e;
    delete[] z;
    delete[] x;

    return Inv;
}

