#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ============================================================================
// FUNCIONES AUXILIARES DE MEMORIA DINAMICA (C++98 / Dev-C++ 5.11)
// ============================================================================

double* crearVector(int n) {
    return new (std::nothrow) double[n];
}

void destruirVector(double* v) {
    if (v != NULL) {
        delete[] v;
    }
}

double** crearMatriz(int filas, int cols) {
    double** M = new (std::nothrow) double*[filas];
    if (M == NULL) return NULL;
    for (int i = 0; i < filas; i++) {
        M[i] = new (std::nothrow) double[cols];
        if (M[i] == NULL) return NULL;
    }
    return M;
}

void destruirMatriz(double** M, int filas) {
    if (M != NULL) {
        for (int i = 0; i < filas; i++) {
            delete[] M[i];
        }
        delete[] M;
    }
}

void mostrarVector(const char* nombre, const double* v, int n) {
    cout << nombre << " = [ ";
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(6) << v[i] << (i < n - 1 ? ", " : " ");
    }
    cout << "]" << endl;
}

void mostrarMatriz(const char* nombre, double** M, int n) {
    cout << "\n--- Matriz " << nombre << " (" << n << "x" << n << ") ---" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(6) << M[i][j] << "\t";
        }
        cout << endl;
    }
}

// ============================================================================
// 1. METODO LU GENERAL (Doolittle: L con unos en la diagonal)
// ============================================================================

/*
 * Factorizacion LU por el metodo de Doolittle.
 * Transforma A en L * U donde:
 *   L: Triangular inferior con L[i][i] = 1.0
 *   U: Triangular superior
 */
bool factorizacionLU(double** A, double** L, double** U, int n) {
    // Inicializar matrices L y U
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            U[i][j] = 0.0;
            if (i == j) {
                L[i][j] = 1.0;
            } else {
                L[i][j] = 0.0;
            }
        }
    }

    // Calculo alternado de filas de U y columnas de L
    for (int i = 0; i < n; i++) {
        // Obtenemos elementos de la fila i de U (para j >= i)
        for (int j = i; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < i; k++) {
                suma += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - suma;
        }

        // Comprobacion de pivote nulo
        if (fabs(U[i][i]) < 1e-15) {
            cerr << "[Error LU] Pivote nulo o matriz singular en U[" << i << "][" << i << "]." << endl;
            return false;
        }

        // Obtenemos elementos de la columna i de L (para j > i)
        for (int j = i + 1; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < i; k++) {
                suma += L[j][k] * U[k][i];
            }
            L[j][i] = (A[j][i] - suma) / U[i][i];
        }
    }
    return true;
}

/*
 * Sustitucion Progresiva para resolver: L * z = b
 */
void sustitucionProgresiva(double** L, const double* b, double* z, int n) {
    for (int i = 0; i < n; i++) {
        double suma = 0.0;
        for (int j = 0; j < i; j++) {
            suma += L[i][j] * z[j];
        }
        z[i] = b[i] - suma;
    }
}

/*
 * Sustitucion Regresiva para resolver: U * x = z
 */
void sustitucionRegresiva(double** U, const double* z, double* x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        double suma = 0.0;
        for (int j = i + 1; j < n; j++) {
            suma += U[i][j] * x[j];
        }
        x[i] = (z[i] - suma) / U[i][i];
    }
}

/*
 * Función General: Resuelve A * x = b utilizando Factorización LU (Doolittle)
 *   A: Matriz de coeficientes (n x n)
 *   b: Vector de términos independientes (n)
 *   x: Vector donde se almacena la solución (n)
 *   n: Dimensión del sistema
 */
bool resolverLU(double** A, const double* b, double* x, int n) {
    double** L = crearMatriz(n, n);
    double** U = crearMatriz(n, n);
    double* z = crearVector(n);

    if (L == NULL || U == NULL || z == NULL) {
        cerr << "[Error Memoria] No se pudo asignar memoria para resolver LU." << endl;
        destruirMatriz(L, n);
        destruirMatriz(U, n);
        destruirVector(z);
        return false;
    }

    bool exito = factorizacionLU(A, L, U, n);

    if (exito) {
        // Paso 1: L * z = b (Sustitucion progresiva)
        sustitucionProgresiva(L, b, z, n);
        // Paso 2: U * x = z (Sustitucion regresiva)
        sustitucionRegresiva(U, z, x, n);
    }

    // Liberar memoria intermedia
    destruirMatriz(L, n);
    destruirMatriz(U, n);
    destruirVector(z);

    return exito;
}


// ============================================================================
// 2. METODO LU PARA SISTEMAS TRIDIAGONALES (Algoritmo de Thomas)
// ============================================================================

/*
 * Función General: Resuelve un sistema tridiagonal A * x = f
 *   a: Subdiagonal de A (tamaño n-1, a[0] representa A[1][0] hasta a[n-2] que es A[n-1][n-2])
 *   b: Diagonal principal de A (tamaño n, b[0] hasta b[n-1])
 *   c: Superdiagonal de A (tamaño n-1, c[0] representa A[0][1] hasta c[n-2] que es A[n-2][n-1])
 *   f: Vector de términos independientes (tamaño n)
 *   x: Vector donde se almacena la solución calculada (tamaño n)
 *   n: Dimensión del sistema
 */
bool resolverTridiagonal(const double* a, const double* b, const double* c, 
                         const double* f, double* x, int n) {
    double* alpha = crearVector(n); // Elementos subdiagonales de L
    double* beta = crearVector(n);  // Elementos diagonales de U
    double* z = crearVector(n);      // Vector intermedio (L * z = f)

    if (alpha == NULL || beta == NULL || z == NULL) {
        cerr << "[Error Memoria] No se pudo asignar memoria para el sistema tridiagonal." << endl;
        destruirVector(alpha);
        destruirVector(beta);
        destruirVector(z);
        return false;
    }

    // Paso 1: Factorizacion LU y Sustitucion Progresiva (L * z = f)
    beta[0] = b[0];
    if (fabs(beta[0]) < 1e-15) {
        cerr << "[Error Tridiagonal] Pivote nulo en beta[0]." << endl;
        destruirVector(alpha);
        destruirVector(beta);
        destruirVector(z);
        return false;
    }

    z[0] = f[0];

    for (int i = 1; i < n; i++) {
        alpha[i] = a[i - 1] / beta[i - 1];
        beta[i] = b[i] - alpha[i] * c[i - 1];

        if (fabs(beta[i]) < 1e-15) {
            cerr << "[Error Tridiagonal] Pivote nulo en beta[" << i << "]." << endl;
            destruirVector(alpha);
            destruirVector(beta);
            destruirVector(z);
            return false;
        }

        z[i] = f[i] - alpha[i] * z[i - 1];
    }

    // Paso 2: Sustitucion Regresiva (U * x = z)
    x[n - 1] = z[n - 1] / beta[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = (z[i] - c[i] * x[i + 1]) / beta[i];
    }

    // Liberar memoria intermedia
    destruirVector(alpha);
    destruirVector(beta);
    destruirVector(z);

    return true;
}


// ============================================================================
// DEMOSTRACION / PROGRAMA PRINCIPAL
// ============================================================================

int main() {
    cout << "=========================================================" << endl;
    cout << "  RESOLUCION DE SISTEMAS LINEALES POR METODOS LU (C++)" << endl;
    cout << "=========================================================" << endl;

    // ------------------------------------------------------------------------
    // CASO 1: Sistema General Densidad 4x4 (Ejemplo de las diapositivas)
    // ------------------------------------------------------------------------
    int n1 = 4;
    double** A1 = crearMatriz(n1, n1);
    double* b1 = crearVector(n1);
    double* x1 = crearVector(n1);

    // Inicialización del sistema A1 * x1 = b1
    double datosA1[4][4] = {
        {4.0, 3.0, 2.0, 1.0},
        {3.0, 4.0, 3.0, 2.0},
        {2.0, 3.0, 4.0, 3.0},
        {1.0, 2.0, 3.0, 4.0}
    };
    double datosB1[4] = {1.0, 1.0, -1.0, -1.0};

    for (int i = 0; i < n1; i++) {
        b1[i] = datosB1[i];
        for (int j = 0; j < n1; j++) {
            A1[i][j] = datosA1[i][j];
        }
    }

    cout << "\n>>> 1. RESOLUCION DE SISTEMA GENERAL A * x = b (Doolittle LU) <<<" << endl;
    mostrarMatriz("A", A1, n1);
    mostrarVector("Vector b", b1, n1);

    if (resolverLU(A1, b1, x1, n1)) {
        cout << "\nSolucion obtenida con exito:" << endl;
        mostrarVector("Vector x", x1, n1);
    }

    destruirMatriz(A1, n1);
    destruirVector(b1);
    destruirVector(x1);


    // ------------------------------------------------------------------------
    // CASO 2: Sistema Tridiagonal n x n (Algoritmo de Thomas)
    // ------------------------------------------------------------------------
    int n2 = 4;
    double* a2 = crearVector(n2 - 1); // Subdiagonal (longitud n-1)
    double* b2 = crearVector(n2);     // Diagonal principal (longitud n)
    double* c2 = crearVector(n2 - 1); // Superdiagonal (longitud n-1)
    double* f2 = crearVector(n2);     // Términos independientes
    double* x2 = crearVector(n2);     // Vector solución

    // Definimos el sistema tridiagonal:
    //  b0=2, c0=-1
    //  a0=-1, b1=2, c1=-1
    //  a1=-1, b2=2, c2=-1
    //  a2=-1, b3=2
    double datosA_sub[3] = {-1.0, -1.0, -1.0};
    double datosDiag[4]  = { 2.0,  2.0,  2.0,  2.0};
    double datosA_sup[3] = {-1.0, -1.0, -1.0};
    double datosF[4]     = { 1.0,  0.0,  0.0,  1.0};

    for (int i = 0; i < n2; i++) {
        b2[i] = datosDiag[i];
        f2[i] = datosF[i];
    }
    for (int i = 0; i < n2 - 1; i++) {
        a2[i] = datosA_sub[i];
        c2[i] = datosA_sup[i];
    }

    cout << "\n\n>>> 2. RESOLUCION DE SISTEMA TRIDIAGONA A * x = f (Thomas LU) <<<" << endl;
    mostrarVector("Subdiagonal (a)", a2, n2 - 1);
    mostrarVector("Diagonal (b)   ", b2, n2);
    mostrarVector("Superdiagonal(c)", c2, n2 - 1);
    mostrarVector("Terminos ind (f)", f2, n2);

    if (resolverTridiagonal(a2, b2, c2, f2, x2, n2)) {
        cout << "\nSolucion obtenida con exito:" << endl;
        mostrarVector("Vector x", x2, n2);
    }

    destruirVector(a2);
    destruirVector(b2);
    destruirVector(c2);
    destruirVector(f2);
    destruirVector(x2);

    cout << "\n=========================================================" << endl;
    return 0;
}
