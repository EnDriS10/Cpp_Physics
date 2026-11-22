// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: eliminacion de Gauss y Gauss-Jordan
// ============================================================================
// Metodos directos de eliminacion, con deteccion de matrices singulares.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "eliminacion_gauss.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (2): gauss_solve, gauss_jordan_solve
// Dependencias copiadas (6): print_error, intercambiar_elem, copy_vect, gen_mat, del_mat, coppy_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ELIMINACION_GAUSS_CPP
#define MATCLUB_ELIMINACION_GAUSS_CPP

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

// (copiada de: vectores)
#ifndef MC_FN_copy_vect
#define MC_FN_copy_vect
// Copia un vector
double* copy_vect(double *a, int n) {
    double *c = new double[n];
    for (int i = 0; i < n; i++) c[i] = a[i];
    return c;
}
#endif // MC_FN_copy_vect

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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Sistemas lineales: eliminacion de Gauss y Gauss-Jordan
// ----------------------------------------------------------------------------

#ifndef MC_FN_gauss_solve
#define MC_FN_gauss_solve
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
#endif // MC_FN_gauss_solve

#ifndef MC_FN_gauss_jordan_solve
#define MC_FN_gauss_jordan_solve
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
#endif // MC_FN_gauss_jordan_solve

#endif // MATCLUB_ELIMINACION_GAUSS_CPP
