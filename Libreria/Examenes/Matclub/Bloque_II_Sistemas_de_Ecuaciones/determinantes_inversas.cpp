// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Determinantes e inversas
// ============================================================================
// Determinante e inversa por Gauss, Gauss-Jordan y LU.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "determinantes_inversas.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (4): det_gauss, det_lu, inv_gj, inv_lu
// Dependencias copiadas (8): print_error, print_warning, intercambiar_elem, gen_mat, del_mat, coppy_mat, zeros_mat, lu_forma1
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_DETERMINANTES_INVERSAS_CPP
#define MATCLUB_DETERMINANTES_INVERSAS_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

// (copiada de: mensajes)
#ifndef MC_FN_print_error
#define MC_FN_print_error
void print_error(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB ERROR]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_error

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

// (copiada de: auxiliares)
#ifndef MC_FN_intercambiar_elem
#define MC_FN_intercambiar_elem
//Intercambia dos elementos
void intercambiar_elem(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}
#endif // MC_FN_intercambiar_elem

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
#ifndef MC_FN_coppy_mat
#define MC_FN_coppy_mat
//Copiar la matriz
double** coppy_mat(double **M, int f, int c) {	
  /*Para hacrer una copia de la matriz B en el programa principal.
  	double **Bcopia;
	Bcopia=crearmatriz(Bcopia,fb,cb);
	Bcopia=copiarmatriz(fb,cb);
	con fb el numero de filas de b y cb el numero de columnas de b
  */
  
   double **Mcopia;
   Mcopia=gen_mat(Mcopia,f,c);
	for (int i = 0; i < f; i++){
		for (int j = 0; j < c; j++) {Mcopia[i][j] = M[i][j];}
		}
	return Mcopia;
}
#endif // MC_FN_coppy_mat

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

// (copiada de: factorizacion_lu)
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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Determinantes e inversas
// ----------------------------------------------------------------------------

#ifndef MC_FN_det_gauss
#define MC_FN_det_gauss
// 1A. Determinante usando Eliminación Gaussiana (con pivoteo)
// Descripción: Determinante por eliminacion gaussiana con pivoteo: producto de los pivotes, cambiando el signo en cada intercambio de filas. No modifica A. Condicion: A cuadrada. det = 0 indica matriz singular.
double det_gauss(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double d = det_gauss(A, 3);
        // Resultado: d = 5
    */
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
#endif // MC_FN_det_gauss

#ifndef MC_FN_det_lu
#define MC_FN_det_lu
// 1B. Determinante usando Factorización LU (Doolittle)
// Descripción: Determinante con la factorizacion LU de Doolittle: det(A) = producto de la diagonal de U (L tiene unos). Condicion: A cuadrada con menores principales no nulos. No modifica A.
double det_lu(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double d = det_lu(A, 3);
        // Resultado: d = 5
    */
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
#endif // MC_FN_det_lu

#ifndef MC_FN_inv_gj
#define MC_FN_inv_gj
// 2A. Inversa de una matriz usando Gauss-Jordan
// Descripción: Inversa por Gauss-Jordan sobre la matriz ampliada [A | I]: al reducir A a I, la parte derecha queda A^-1. Condicion: A cuadrada con det(A) != 0 (si |det| < 1e-12 avisa y devuelve NULL). No modifica A.
double** inv_gj(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **Ai = inv_gj(A, 3);
        // Resultado: Ai = [0, 0.4, -0.2; -1, 0, 1; 0, -0.2, 0.6]
    */
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
#endif // MC_FN_inv_gj

#ifndef MC_FN_inv_lu
#define MC_FN_inv_lu
// 2B. Inversa de una matriz usando Factorización LU
// Descripción: Inversa resolviendo A*x = e_j (columnas de la identidad) con la factorizacion LU, que se calcula una sola vez. Condicion: A cuadrada con det(A) != 0 (si |det| < 1e-12 avisa y devuelve NULL).
double** inv_lu(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **Ai = inv_lu(A, 3);
        // Resultado: Ai = [0, 0.4, -0.2; -1, 0, 1; 0, -0.2, 0.6]
    */
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
#endif // MC_FN_inv_lu

#endif // MATCLUB_DETERMINANTES_INVERSAS_CPP
