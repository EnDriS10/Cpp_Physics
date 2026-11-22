// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.3
// Metodo QR
// ============================================================================
// Factorizacion QR (Gram-Schmidt y rotaciones de Givens) e iteracion QR para obtener autovalores.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "qr.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (4): qr_gs_mat, qr_givens_mat, qr_triang_mat, qr_eig
// Dependencias copiadas (11): print_error, print_warning, print_error_dim, gen_mat, del_mat, prod_mat, coppy_mat, zeros_mat, eye_mat, get_diag_mat, hessenberg_householder_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_QR_CPP
#define MATCLUB_QR_CPP

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

// (copiada de: mensajes)
#ifndef MC_FN_print_error_dim
#define MC_FN_print_error_dim
// Error de dimensiones: "mensaje (faxca) * (fbxcb)"
void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb) {
    cout << "[MATCLUB ERROR]: " << mensaje
         << " (" << fa << "x" << ca << ") * (" << fb << "x" << cb << ")" << endl;
}
#endif // MC_FN_print_error_dim

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
#ifndef MC_FN_prod_mat
#define MC_FN_prod_mat
// Multiplicación de matrices (A de fa x ca, B de fb x cb)
double** prod_mat(double **A, double **B, int fa, int ca, int fb, int cb) {
    
    // Validar si se pueden multiplicar (Columnas de A == Filas de B)
    if (ca != fb) {
        print_error_dim("No se pueden multiplicar las matrices, dimensiones incompatibles", fa, ca, fb, cb);
        return NULL; // Retorna nulo si la multiplicación no es válida matemáticamente
    }

    double suma;
    double **Producto;
    
    // Creamos la matriz resultado de tamaño (fa x cb)
    Producto = gen_mat(Producto, fa, cb);

    for (int i = 0; i < fa; i++) {
        for (int j = 0; j < cb; j++) {
            suma = 0.0;
            for (int k = 0; k < ca; k++) { // O 'fb', ya que son iguales
                suma = suma + A[i][k] * B[k][j];
            }
            Producto[i][j] = suma;
        }
    }
    
    return Producto;
}
#endif // MC_FN_prod_mat

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
#ifndef MC_FN_get_diag_mat
#define MC_FN_get_diag_mat
// Extrae la diagonal principal de una matriz cuadrada como vector
double* get_diag_mat(double **A, int n) {
    double *d = new double[n];
    for (int i = 0; i < n; i++) d[i] = A[i][i];
    return d;
}
#endif // MC_FN_get_diag_mat

// (copiada de: householder)
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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Metodo QR
// ----------------------------------------------------------------------------

#ifndef MC_FN_qr_gs_mat
#define MC_FN_qr_gs_mat
// Factorización QR por Gram-Schmidt modificado
// Descripción: Descompone A = Q*R con Q ortogonal (columnas ortonormales) y R triangular superior. Q y R se devuelven por referencia (new[]).
// Necesita que las columnas de A sean linealmente independientes (A invertible).
void qr_gs_mat(double **A, int n, double **&Q, double **&R) {
    /*
    Ejemplo de uso:
        double **Q, **R;
        qr_gs_mat(A, n, Q, R);   // A = Q*R
    */
    Q = zeros_mat(n, n);
    R = zeros_mat(n, n);
    double *v = new double[n];
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) v[k] = A[k][j];
        for (int i = 0; i < j; i++) {
            double r = 0.0;
            for (int k = 0; k < n; k++) r += Q[k][i] * v[k];
            R[i][j] = r;
            for (int k = 0; k < n; k++) v[k] -= r * Q[k][i];
        }
        double nrm = 0.0;
        for (int k = 0; k < n; k++) nrm += v[k] * v[k];
        nrm = sqrt(nrm);
        if (nrm < 1e-14) {
            print_error("qr_gs_mat: columnas linealmente dependientes");
            del_mat(Q, n); del_mat(R, n); delete[] v;
            Q = NULL; R = NULL;
            return;
        }
        R[j][j] = nrm;
        for (int k = 0; k < n; k++) Q[k][j] = v[k] / nrm;
    }
    delete[] v;
}
#endif // MC_FN_qr_gs_mat

#ifndef MC_FN_qr_givens_mat
#define MC_FN_qr_givens_mat
// Factorización QR por rotaciones (Givens)
// Descripción: Hace cero los elementos por debajo de la diagonal uno a uno con rotaciones P_k (c = a_jj/d, s = a_ij/d, d = sqrt(a_jj^2 + a_ij^2)).
// R = P_m*...*P_1*A y Q = P_1^T*...*P_m^T, de modo que A = Q*R. Q y R se devuelven por referencia (new[]). Funciona para cualquier A (no necesita ser invertible).
void qr_givens_mat(double **A, int n, double **&Q, double **&R) {
    /*
    Ejemplo de uso:
        double **Q, **R;
        qr_givens_mat(A, n, Q, R);   // A = Q*R
    */
    R = coppy_mat(A, n, n);
    Q = eye_mat(n);
    for (int j = 0; j < n - 1; j++) {
        for (int i = j + 1; i < n; i++) {
            if (R[i][j] == 0.0) continue;
            double d = sqrt(R[j][j] * R[j][j] + R[i][j] * R[i][j]);
            double c = R[j][j] / d, s = R[i][j] / d;
            for (int k = 0; k < n; k++) {                  // filas j e i de R
                double rj = R[j][k], ri = R[i][k];
                R[j][k] = c * rj + s * ri;
                R[i][k] = -s * rj + c * ri;
            }
            for (int k = 0; k < n; k++) {                  // columnas j e i de Q
                double qj = Q[k][j], qi = Q[k][i];
                Q[k][j] = c * qj + s * qi;
                Q[k][i] = -s * qj + c * qi;
            }
            R[i][j] = 0.0;
        }
    }
}
#endif // MC_FN_qr_givens_mat

#ifndef MC_FN_qr_triang_mat
#define MC_FN_qr_triang_mat
// Método QR: matriz triangular superior semejante a A
// Descripción: Itera A(i) = Q(i)*R(i) -> A(i+1) = R(i)*Q(i) (misma traza y autovalores) hasta que la suma de |elementos bajo la diagonal| sea < tol.
// Si 'usar_hess' es true se aplica antes la transformacion de Hessenberg (converge con menos trabajo por iteracion). Devuelve la matriz (new[]) e 'iter_out' iteraciones.
// Con autovalores complejos no converge a triangular (quedan bloques 2x2).
double** qr_triang_mat(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out) {
    /*
    Ejemplo de uso:
        int it;
        double **T = qr_triang_mat(A, n, 1e-12, 1000, true, it);   // diagonal de T = autovalores
    */
    double **T = usar_hess ? hessenberg_householder_mat(A, n) : coppy_mat(A, n, n);
    iter_out = 0;
    while (iter_out < max_iter) {
        double bajo = 0.0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++) bajo += fabs(T[i][j]);
        if (bajo < tol) break;
        double **Q, **R;
        qr_givens_mat(T, n, Q, R);
        del_mat(T, n);
        T = prod_mat(R, Q, n, n, n, n);
        del_mat(Q, n); del_mat(R, n);
        iter_out++;
    }
    if (iter_out >= max_iter) print_warning("qr_triang_mat alcanzo max_iter (posibles autovalores complejos o poca convergencia).");
    return T;
}
#endif // MC_FN_qr_triang_mat

#ifndef MC_FN_qr_eig
#define MC_FN_qr_eig
// Autovalores de una matriz genérica: Método QR
// Descripción: Devuelve (new[]) los autovalores de A, que son los elementos diagonales de la matriz triangular obtenida con qr_triang_mat.
double* qr_eig(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out) {
    /*
    Ejemplo de uso:
        // A = [7 8 6 6; 1 6 -1 -2; 1 -2 5 -2; 3 4 3 4]  -> autovalores 10, 7, 4, 1
        int it;
        double *L = qr_eig(A, 4, 1e-12, 1000, true, it);
        print_vect(L, 4, "Autovalores");
    */
    double **T = qr_triang_mat(A, n, tol, max_iter, usar_hess, iter_out);
    double *L = get_diag_mat(T, n);
    del_mat(T, n);
    return L;
}
#endif // MC_FN_qr_eig

#endif // MATCLUB_QR_CPP
