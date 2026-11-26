// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: factorizacion LU
// ============================================================================
// Factorizacion LU (Doolittle y Crout) y resolucion de sistemas con ella.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "factorizacion_lu.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (4): lu_forma1, lu_forma1_sol, lu_forma2, lu_forma2_sol
// Dependencias copiadas (4): print_warning, gen_mat, del_mat, zeros_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_FACTORIZACION_LU_CPP
#define MATCLUB_FACTORIZACION_LU_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

// (copiada de: mensajes)
#ifndef MC_FN_print_warning
#define MC_FN_print_warning
// Aviso: algo no fue perfecto pero el programa puede continuar
void print_warning(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB AVISO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_warning

// (copiada de: matrices)
#ifndef MC_FN_gen_mat
#define MC_FN_gen_mat
//Crear Matriz
double** gen_mat(double **M, int f, int c){
	/* en el programa principal si queremos crear (reservar memoria) para la matriz B. 
   		double **B;
   		B=crearmatriz(B,fb,cb);
   	donde fb es el numero de filas de B y cb el numero de columnas de B
	*/
    M = new double * [f];
    	for (int i = 0; i < f; i++) { M[i] = new double[c];}
     return M;
}
#endif // MC_FN_gen_mat

// (copiada de: matrices)
#ifndef MC_FN_del_mat
#define MC_FN_del_mat
//Borrar Matriz
void del_mat(double **M, int f){
	/* libera la memoria de la matriz pasada en la llamada. Por ejemplo una matriz B.
	borrarmatriz(B, fb);
	con fb el nÃºmero de filas de B.
	*/

	for (int i=0; i < f; i++) {
    	delete[] M[i];
    	}
    delete [] M;
}
#endif // MC_FN_del_mat

// (copiada de: matrices)
#ifndef MC_FN_zeros_mat
#define MC_FN_zeros_mat
// Matriz de ceros (f x c)
double** zeros_mat(int f, int c) {
    double **M;
    M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = 0.0;
        }
    }
    return M;
}
#endif // MC_FN_zeros_mat

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Sistemas lineales: factorizacion LU
// ----------------------------------------------------------------------------

#ifndef MC_FN_lu_forma1
#define MC_FN_lu_forma1
// Factorización LU (Forma 1 - Descomposición de Doolittle)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
// Descripción: Factorizacion LU de Doolittle: A = L*U con unos en la diagonal de L (L triangular inferior, U triangular superior). Sirve para resolver varios sistemas con la misma A.
// Condiciones: A cuadrada y con menores principales no nulos (si aparece un cero en la diagonal de U avisa: habria que pivotar). L y U se crean antes con zeros_mat(n, n).
void lu_forma1(double **A, int n, double **L, double **U) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **L = zeros_mat(3, 3), **U = zeros_mat(3, 3);
        lu_forma1(A, 3, L, U);
        // Resultado: L = [1, 0, 0; 2, 1, 0; 4, 3, 1] , U = [2, 1, 1; 0, 1, 1; 0, 0, 2]
    */
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
#endif // MC_FN_lu_forma1

#ifndef MC_FN_lu_forma1_sol
#define MC_FN_lu_forma1_sol
// Resuelve Ax = b usando LU Forma 1
// Descripción: Resuelve A*x = b con la factorizacion de Doolittle: A = L*U, luego L*z = b (sustitucion progresiva) y U*x = z (sustitucion regresiva). Mismas condiciones que lu_forma1.
double* lu_forma1_sol(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {4, 10, 24};
        double *x = lu_forma1_sol(A, b, 3);
        // Resultado: x = [1, 1, 1]
    */
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
#endif // MC_FN_lu_forma1_sol

#ifndef MC_FN_lu_forma2
#define MC_FN_lu_forma2
// Factorización LU (Forma 2 - Alternando fila U y columna L)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
// Descripción: Factorizacion LU de Crout: A = L*U con unos en la diagonal de U (se calcula alternando una fila de U y una columna de L). Mismas condiciones que lu_forma1; L y U se crean antes con zeros_mat(n, n).
void lu_forma2(double **A, int n, double **L, double **U) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **L = zeros_mat(3, 3), **U = zeros_mat(3, 3);
        lu_forma2(A, 3, L, U);
        // Resultado: L = [1, 0, 0; 2, 1, 0; 4, 3, 1] , U = [2, 1, 1; 0, 1, 1; 0, 0, 2]
    */
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
#endif // MC_FN_lu_forma2

#ifndef MC_FN_lu_forma2_sol
#define MC_FN_lu_forma2_sol
// Resuelve Ax = b usando LU Forma 2
// Descripción: Resuelve A*x = b con la factorizacion de Crout (unos en la diagonal de U). Mismas condiciones que lu_forma1.
double* lu_forma2_sol(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {4, 10, 24};
        double *x = lu_forma2_sol(A, b, 3);
        // Resultado: x = [1, 1, 1]
    */
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
#endif // MC_FN_lu_forma2_sol

#endif // MATCLUB_FACTORIZACION_LU_CPP
