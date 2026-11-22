// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: metodos iterativos
// ============================================================================
// Comprobacion de dominancia diagonal, Jacobi, Gauss-Seidel y sobrerrelajacion (SOR).
//
// Funciones (5): check_dominancia, reorder_diagonals, jacobi_solve, gauss_seidel_solve, sor_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

/// Función Auxiliar: Comprueba estrictamente si una matriz es diagonalmente dominante

bool check_dominancia(double **A, int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) sum += fabs(A[i][j]);
        }
        // Condición teórica: |A_ii| >= sum_{j!=i} |A_ij|
        if (fabs(A[i][i]) < sum) {
            return false; 
        }
    }
    return true;
}

// Función Auxiliar: Reordena las filas (A y b) solo si la matriz no es dominante de entrada

bool reorder_diagonals(double **A, double *b, int n) {
    // 1. Si ya es dominante de fábrica, no alteramos el sistema original
    if (check_dominancia(A, n)) {
        return true; 
    }

    // 2. Si no lo es, intentamos rescatarla reordenando el mayor elemento a la diagonal
    bool swapped = false;
    for (int i = 0; i < n; i++) {
        int max_row = i;
        double max_val = fabs(A[i][i]);
        
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > max_val) {
                max_val = fabs(A[k][i]);
                max_row = k;
            }
        }
        
        if (max_row != i) {
            for (int j = 0; j < n; j++) {
                intercambiar_elem(A[i][j], A[max_row][j]);
            }
            intercambiar_elem(b[i], b[max_row]);
            swapped = true;
        }
    }
    
    // 3. Comprobar si el "Plan B" (reordenamiento) logró hacerla dominante
    bool es_dominante = check_dominancia(A, n);
    
    if (swapped) print_info("El sistema original no era optimo. Ha sido reordenado por filas.");
    if (!es_dominante) {
        print_warning("Incluso tras reordenar, la matriz no es diagonalmente dominante. La convergencia NO esta garantizada.");
    }
    
    return es_dominante;
}

// Método Iterativo de Jacobi (Desplazamientos simultáneos)

double* jacobi_solve(double **A, double *b, int n, double tol, int max_iter) {
    // 1. Trabajamos con copias para no destruir las matrices originales del main
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    // 2. Intentar hacer la matriz diagonalmente dominante
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    // 3. Aproximación inicial: x_i^(0) = b_i / A_ii
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Jacobi no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
    }

    int iter = 0;
    double error = tol + 1.0;

    // 4. Bucle principal de Jacobi
    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Jacobi usa exclusivamente los valores de la iteración anterior oldx[j]
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * oldx[j];
                }
            }
        }

        // Calculamos error evaluando la norma euclidiana de la diferencia
        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;

        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        iter++;
    }
    
    if (iter == max_iter) print_warning("Jacobi alcanzo max_iter sin converger.");
    
    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}

// Método Iterativo de Gauss-Seidel (Desplazamientos sucesivos)

double* gauss_seidel_solve(double **A, double *b, int n, double tol, int max_iter ) {
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Gauss-Seidel no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
        newx[i] = oldx[i];
    }

    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Gauss-Seidel usa newx[j] porque el valor se actualiza inmediatamente
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * newx[j]; 
                }
            }
        }

        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    if (iter == max_iter) print_warning("Gauss-Seidel alcanzo max_iter sin converger.");

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}

// Método de Sobrerrelajación (SOR) - Extensión de Gauss-Seidel
// El valor óptimo de w está entre 1 y 2. Para w=1 es idéntico a Gauss-Seidel.

double* sor_solve(double **A, double *b, int n, double w, double tol, int max_iter) {
    if (w <= 0.0 || w >= 2.0) {
        print_error("El factor de relajacion w debe estar estrictamente entre 0 y 2 para evitar divergencias.");
        return NULL;
    }

    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. SOR no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
        newx[i] = oldx[i];
    }

    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        
        for (int i = 0; i < n; i++) {
            // Calcular el valor temporal como si fuera Gauss-Seidel
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += M[i][j] * newx[j];
                }
            }
            
            // Aplicar la corrección con el factor de relajación w multiplicando al residuo
            newx[i] = oldx[i] + (w / M[i][i]) * (vb[i] - sum - M[i][i] * oldx[i]);
        }

        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    if (iter == max_iter) print_warning("SOR alcanzo max_iter sin converger.");

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}

