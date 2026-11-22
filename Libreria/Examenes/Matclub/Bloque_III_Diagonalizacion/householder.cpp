// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.4
// Transformacion de Householder (forma de Hessenberg / tridiagonal)
// ============================================================================
// Reduccion a forma de Hessenberg superior (tridiagonal si la matriz es simetrica) por eliminacion y por reflexiones de Householder.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "householder.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (2): hessenberg_mat, hessenberg_householder_mat
// Dependencias copiadas (3): intercambiar_elem, gen_mat, coppy_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_HOUSEHOLDER_CPP
#define MATCLUB_HOUSEHOLDER_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

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
// FUNCIONES DEL MODULO: Transformacion de Householder (forma de Hessenberg / tridiagonal)
// ----------------------------------------------------------------------------

#ifndef MC_FN_hessenberg_mat
#define MC_FN_hessenberg_mat
// Forma de Hessenberg superior por transformaciones de similaridad (eliminacion)
// Descripción: Hace cero los elementos por debajo de la subdiagonal con B^-1*A*B (multiplicadores b_i = a_i,m-1 / a_m,m-1, como en la teoria).
// Si el elemento subdiagonal es cero se intercambian fila y columna con el de mayor magnitud (asi no cambian los autovalores). Devuelve una matriz nueva.
double** hessenberg_mat(double **A, int n) {
    /*
    Ejemplo de uso:
        // A = [7 8 6 6; 1 6 -1 -2; 1 -2 5 -2; 3 4 3 4]
        double **H = hessenberg_mat(A, 4);   // H = [7 32 -60 6; 1 -1 21 -2; 0 -2 6 0; 0 0 -38 10]
    */
    double **H = coppy_mat(A, n, n);
    for (int m = 1; m < n - 1; m++) {
        if (H[m][m - 1] == 0.0) {                       // buscar pivote
            int p = m;
            double mx = 0.0;
            for (int j = m + 1; j < n; j++) if (fabs(H[j][m - 1]) > mx) { mx = fabs(H[j][m - 1]); p = j; }
            if (p != m) {
                for (int j = 0; j < n; j++) intercambiar_elem(H[p][j], H[m][j]);   // filas
                for (int j = 0; j < n; j++) intercambiar_elem(H[j][p], H[j][m]);   // columnas
            }
        }
        double piv = H[m][m - 1];
        if (piv == 0.0) continue;
        for (int i = m + 1; i < n; i++) {
            double b = H[i][m - 1] / piv;
            if (b != 0.0) {
                for (int j = 0; j < n; j++) H[i][j] -= b * H[m][j];   // B^-1 * H : fila i -= b*fila m
                for (int j = 0; j < n; j++) H[j][m] += b * H[j][i];   // (.) * B  : columna m += b*columna i
            }
            H[i][m - 1] = 0.0;
        }
    }
    return H;
}
#endif // MC_FN_hessenberg_mat

#ifndef MC_FN_hessenberg_householder_mat
#define MC_FN_hessenberg_householder_mat
// Forma de Hessenberg superior por reflexiones de Householder
// Descripción: Igual que hessenberg_mat pero con reflexiones P = I - 2*v*v^T/(v^T*v) (transformaciones ortogonales, mas estables numericamente).
// Mantiene los autovalores (P es ortogonal y simetrica: H = P*A*P). Si A es simetrica el resultado es tridiagonal.
double** hessenberg_householder_mat(double **A, int n) {
    /*
    Ejemplo de uso:
        double **H = hessenberg_householder_mat(A, n);
    */
    double **H = coppy_mat(A, n, n);
    double *v = new double[n];
    for (int k = 0; k < n - 2; k++) {
        double norma = 0.0;
        for (int i = k + 1; i < n; i++) norma += H[i][k] * H[i][k];
        norma = sqrt(norma);
        if (norma == 0.0) continue;
        double alfa = (H[k + 1][k] > 0.0) ? -norma : norma;
        for (int i = 0; i < n; i++) v[i] = 0.0;
        v[k + 1] = H[k + 1][k] - alfa;
        for (int i = k + 2; i < n; i++) v[i] = H[i][k];
        double vv = 0.0;
        for (int i = k + 1; i < n; i++) vv += v[i] * v[i];
        if (vv == 0.0) continue;
        for (int j = 0; j < n; j++) {                      // H = P*H
            double s = 0.0;
            for (int i = k + 1; i < n; i++) s += v[i] * H[i][j];
            for (int i = k + 1; i < n; i++) H[i][j] -= 2.0 * s * v[i] / vv;
        }
        for (int i = 0; i < n; i++) {                      // H = H*P
            double s = 0.0;
            for (int j = k + 1; j < n; j++) s += H[i][j] * v[j];
            for (int j = k + 1; j < n; j++) H[i][j] -= 2.0 * s * v[j] / vv;
        }
        for (int i = k + 2; i < n; i++) H[i][k] = 0.0;
    }
    delete[] v;
    return H;
}
#endif // MC_FN_hessenberg_householder_mat

#endif // MATCLUB_HOUSEHOLDER_CPP
