#include <iostream>
#include <iomanip>

using namespace std;

// Dimensión global fijada en tiempo de compilación
const int n = 4;

// ============================================================================
// 1. METODO LU GENERAL - FORMA 1 (Recorrido celda por celda con if-else)
// ============================================================================
void lu_forma1(double A[n][n], double b[n], double x[n], int n) {
    // Resuelve sistema lineal por el metodo LU: Ax=b -> LUx=b -> Lz=b -> Ux=z -> x
    double U[n][n], L[n][n], z[n];
    double sum;
    int i, j, k;

    // Obtener L y U
    for (i = 0; i <= n - 1; i++) { // i barre las filas
        for (j = 0; j <= n - 1; j++) { // j barre las columnas
            if (i <= j) {
                // Elementos de la diagonal y por encima de la diagonal (i <= j)
                sum = 0.0;
                for (k = 0; k <= i - 1; k++) {
                    sum = sum + L[i][k] * U[k][j];
                }
                U[i][j] = A[i][j] - sum;

                if (i < j) {
                    L[i][j] = 0.0;
                } else {
                    L[i][j] = 1.0;
                }
            } else {
                // Elementos por debajo de la diagonal (i > j)
                sum = 0.0;
                for (k = 0; k <= j - 1; k++) {
                    sum = sum + L[i][k] * U[k][j];
                }
                L[i][j] = (A[i][j] - sum) / U[j][j];
                U[i][j] = 0.0;
            }
        }
    }

    // Obtener z <- Lz=b (Sustitución progresiva)
    for (i = 0; i <= n - 1; i++) {
        sum = 0.0;
        for (j = 0; j <= i - 1; j++) {
            sum = sum + L[i][j] * z[j];
        }
        z[i] = b[i] - sum;
    }

    // Obtener x <- Ux=z (Sustitución regresiva)
    for (i = n - 1; i >= 0; i--) {
        sum = 0.0;
        for (j = i + 1; j <= n - 1; j++) {
            sum = sum + U[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / U[i][i];
    }
}

// ============================================================================
// 2. METODO LU GENERAL - FORMA 2 (Alterna una fila de U y una columna de L)
// ============================================================================
void lu_forma2(double A[n][n], double b[n], double x[n], int n) {
    // Resuelve sistema lineal por el metodo LU: Ax=b -> LUx=b -> Lz=b -> Ux=z -> x
    double U[n][n], L[n][n], z[n];
    double sum;
    int k;

    // Inicializar los elementos U y L a cero
    for (int i = 0; i <= n - 1; i++) {
        for (int j = 0; j <= n - 1; j++) {
            U[i][j] = 0.0;
            L[i][j] = 0.0;
        }
    }

    // Pasamos a calcular los elementos distintos de cero
    for (int i = 0; i <= n - 1; i++) { // i barre filas para U y columnas para L
        // Obtencion de una fila de U
        for (int j = i; j <= n - 1; j++) { // j barre los elementos de la fila i
            sum = 0.0;
            for (k = 0; k <= i - 1; k++) {
                sum = sum + L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }

        // Obtencion de una columna de L
        for (int j = i; j <= n - 1; j++) { // j barre los elementos de la columna i
            if (j == i) {
                L[j][i] = 1.0; // Hacemos uno los elementos de la diagonal de L
            } else {
                sum = 0.0;
                for (k = 0; k <= i - 1; k++) {
                    sum = sum + L[j][k] * U[k][i];
                }
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }
    }

    // Obtener z <- Lz=b (Sustitución progresiva)
    for (int i = 0; i <= n - 1; i++) {
        sum = 0.0;
        for (int j = 0; j <= i - 1; j++) {
            sum = sum + L[i][j] * z[j];
        }
        z[i] = b[i] - sum;
    }

    // Obtener x <- Ux=z (Sustitución regresiva)
    for (int i = n - 1; i >= 0; i--) {
        sum = 0.0;
        for (int j = i + 1; j <= n - 1; j++) {
            sum = sum + U[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / U[i][i];
    }
}

// ============================================================================
// 3. METODO LU TRIDIAGONAL (Algoritmo de Thomas)
// ============================================================================
void tridiag(double a[], double b[], double c[], double f[], double x[], int n) {
    double alpha[n], beta[n], z[n];

    // Paso 1: Factorización LU y Sustitución Progresiva (L * z = f)
    beta[0] = b[0];
    z[0] = f[0];

    for (int i = 1; i <= n - 1; i++) {
        alpha[i] = a[i - 1] / beta[i - 1];
        beta[i] = b[i] - alpha[i] * c[i - 1];
        z[i] = f[i] - alpha[i] * z[i - 1];
    }

    // Paso 2: Sustitución Regresiva (U * x = z)
    x[n - 1] = z[n - 1] / beta[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = (z[i] - c[i] * x[i + 1]) / beta[i];
    }
}

// ============================================================================
// MAIN DE PRUEBA
// ============================================================================
int main() {
    cout << fixed << setprecision(6);

    // Sistema A * x = b de prueba
    double A[n][n] = {
        {4, 3, 2, 1},
        {3, 4, 3, 2},
        {2, 3, 4, 3},
        {1, 2, 3, 4}
    };
    double b[n] = {1, 1, -1, -1};
    double x1[n], x2[n];

    // 1. Ejecución de la Forma 1
    lu_forma1(A, b, x1, n);
    cout << "=== 1. LU FORMA 1 (Recorrido celda por celda) ===" << endl;
    for (int i = 0; i <= n - 1; i++) {
        cout << "x(" << i << ") = " << x1[i] << endl;
    }

    cout << "\n-----------------------------------------------------\n" << endl;

    // 2. Ejecución de la Forma 2
    lu_forma2(A, b, x2, n);
    cout << "=== 2. LU FORMA 2 (Alternando fila U y columna L) ===" << endl;
    for (int i = 0; i <= n - 1; i++) {
        cout << "x(" << i << ") = " << x2[i] << endl;
    }

    cout << "\n-----------------------------------------------------\n" << endl;

    // 3. Ejecución del Solver Tridiagonal
    double sub[n - 1] = {-1, -1, -1};
    double diag[n]    = { 2,  2,  2,  2};
    double sup[n - 1] = {-1, -1, -1};
    double term[n]    = { 1,  0,  0,  1};
    double x_tri[n];

    tridiag(sub, diag, sup, term, x_tri, n);
    cout << "=== 3. SISTEMA TRIDIAGONAL (Thomas) ===" << endl;
    for (int i = 0; i <= n - 1; i++) {
        cout << "x(" << i << ") = " << x_tri[i] << endl;
    }

    return 0;
}
