// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.2
// Diagonalizacion de matrices simetricas: Metodo de Jacobi
// ============================================================================
// Rotaciones de Jacobi para obtener autovalores y autovectores de matrices simetricas (a eleccion: autovalores, autovectores o ambos) y ordenacion de los resultados.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "jacobi.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (2): sort_eig, jacobi_eig
// Dependencias copiadas (9): print_error, print_warning, intercambiar_elem, gen_mat, del_mat, coppy_mat, eye_mat, is_symmetric_mat, get_diag_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_JACOBI_CPP
#define MATCLUB_JACOBI_CPP

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
#ifndef MC_FN_eye_mat
#define MC_FN_eye_mat
// Matriz Identidad (n x n), eye(n) en MATLAB
double** eye_mat(int n) {
    double **M;
    M = gen_mat(M, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) M[i][j] = 1.0;
            else M[i][j] = 0.0;
        }
    }
    return M;
}
#endif // MC_FN_eye_mat

// (copiada de: matrices)
#ifndef MC_FN_is_symmetric_mat
#define MC_FN_is_symmetric_mat
// Comprueba si una matriz cuadrada es simétrica
bool is_symmetric_mat(double **A, int n, double tolerancia) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Comparamos con un pequeño margen de error por decimales (tolerancia)
            if (fabs(A[i][j] - A[j][i]) > tolerancia) {
                return false;
            }
        }
    }
    return true;
}
#endif // MC_FN_is_symmetric_mat

// (copiada de: matrices)
#ifndef MC_FN_get_diag_mat
#define MC_FN_get_diag_mat
// Extrae la diagonal principal de una matriz cuadrada como vector
double* get_diag_mat(double **A, int n) {
    double *d = new double[n];
    for (int i = 0; i < n; i++) d[i] = A[i][i];
    return d;
}
#endif // MC_FN_get_diag_mat

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Diagonalizacion de matrices simetricas: Metodo de Jacobi
// ----------------------------------------------------------------------------

#ifndef MC_FN_sort_eig
#define MC_FN_sort_eig
// Ordenar autovalores y autovectores
// Descripción: Ordena L en valor absoluto decreciente (como en la teoria: l1 = 4, l2 = -3, l3 = 2) y permuta las columnas de U en consecuencia.
// U puede ser NULL (si solo hay autovalores).
void sort_eig(double *L, double **U, int n) {
    /*
    Ejemplo de uso:
        sort_eig(L, U, n);      // autovalores y autovectores
        sort_eig(L, NULL, n);   // solo autovalores
    */
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (fabs(L[j]) > fabs(L[m])) m = j;
        if (m != i) {
            intercambiar_elem(L[i], L[m]);
            if (U != NULL)
                for (int k = 0; k < n; k++) intercambiar_elem(U[k][i], U[k][m]);
        }
    }
}
#endif // MC_FN_sort_eig

#ifndef MC_FN_jacobi_eig
#define MC_FN_jacobi_eig
// Diagonalización de una matriz simétrica: Método de Jacobi
// Descripción: Aplica rotaciones planas R_ij(theta) que anulan en cada paso el mayor elemento fuera de la diagonal (ecs. [7] y [8] de la teoria)
// hasta que todos sean menores que 'tol'. TU ELIGES que quieres obtener:
//   calc_autoval -> L = array con los autovalores (new[]). Si es false, L = NULL.
//   calc_autovec -> U = matriz n x n cuyas COLUMNAS son los autovectores (new[]). Si es false, U = NULL y no se calcula (ahorra trabajo).
//   ordenar      -> ordena por |autovalor| decreciente (los autovectores se reordenan con ellos).
// Devuelve el numero de rotaciones realizadas, o -1 si la matriz no es simetrica. La matriz A no se modifica.
int jacobi_eig(double **A, int n, double *&L, double **&U, bool calc_autoval, bool calc_autovec, bool ordenar, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double *L; double **U;
        jacobi_eig(A, n, L, U, true, true, true, 1e-10, 1000);    // autovalores y autovectores, ordenados
        jacobi_eig(A, n, L, U, true, false, false, 1e-10, 1000);  // solo autovalores (U = NULL)
        jacobi_eig(A, n, L, U, false, true, false, 1e-10, 1000);  // solo autovectores (L = NULL)
        print_vect(L, n, "Autovalores");
        print_mat(U, n, n, "Autovectores (columnas)");
    */
    L = NULL;
    U = NULL;
    if (!calc_autoval && !calc_autovec) {
        print_warning("jacobi_eig: no se pidieron ni autovalores ni autovectores, no hay nada que calcular.");
        return 0;
    }
    if (!is_symmetric_mat(A, n, 1e-10)) {
        print_error("jacobi_eig: la matriz debe ser simetrica");
        return -1;
    }
    double **B = coppy_mat(A, n, n);
    double **V = calc_autovec ? eye_mat(n) : NULL;
    int n_rot = 0;

    while (n > 1) {
        // Paso 3: maximo (en valor absoluto) por encima de la diagonal
        int i = 0, j = 1;
        double mx = 0.0;
        for (int ib = 0; ib < n; ib++)
            for (int jb = ib + 1; jb < n; jb++)
                if (fabs(B[ib][jb]) > mx) { mx = fabs(B[ib][jb]); i = ib; j = jb; }
        if (mx < tol) break;
        if (n_rot >= max_iter) { print_warning("jacobi_eig alcanzo max_iter sin converger plenamente."); break; }

        // Paso 4: angulo theta (ec. [8])
        double theta;
        if (fabs(B[i][i] - B[j][j]) < 1e-14 * (fabs(B[i][i]) + fabs(B[j][j])) + 1e-300) theta = atan(1.0);  // pi/4
        else theta = 0.5 * atan(2.0 * B[i][j] / (B[i][i] - B[j][j]));
        double si = sin(theta), co = cos(theta);

        // Paso 5: V = V*R (sin construir R), solo si se piden los autovectores
        if (V != NULL) {
            for (int k = 0; k < n; k++) {
                double vki = V[k][i];
                V[k][i] = vki * co + V[k][j] * si;
                V[k][j] = -vki * si + V[k][j] * co;
            }
        }
        // Paso 6: B = R^T * B * R (ecs. [7b] a [7e])
        for (int k = 0; k < n; k++) {
            if (k != i && k != j) {
                double bki = B[k][i];
                B[k][i] = bki * co + B[k][j] * si;
                B[k][j] = -bki * si + B[k][j] * co;
                B[i][k] = B[k][i];
                B[j][k] = B[k][j];
            }
        }
        double aii = B[i][i], ajj = B[j][j], aij = B[i][j];
        B[i][i] = aii * co * co + ajj * si * si + 2.0 * aij * si * co;
        B[j][j] = aii * si * si + ajj * co * co - 2.0 * aij * si * co;
        B[i][j] = 0.0;
        B[j][i] = 0.0;
        n_rot++;
    }
    double *Ld = get_diag_mat(B, n);
    del_mat(B, n);
    if (ordenar) sort_eig(Ld, V, n);
    U = V;
    if (calc_autoval) L = Ld; else delete[] Ld;
    return n_rot;
}
#endif // MC_FN_jacobi_eig

#endif // MATCLUB_JACOBI_CPP
