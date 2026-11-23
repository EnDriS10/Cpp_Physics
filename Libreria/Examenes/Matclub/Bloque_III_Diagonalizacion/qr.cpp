// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.3
// Metodo QR
// ============================================================================
// Factorizacion QR (Gram-Schmidt y rotaciones de Givens) e iteracion QR para obtener autovalores y autovectores (a eleccion), con o sin reduccion previa de Hessenberg.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "qr.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (5): qr_gs_mat, qr_givens_mat, qr_schur_mat, qr_triang_mat, qr_eig
// Dependencias copiadas (15): print_error, print_warning, print_error_int, print_error_dim, intercambiar_elem, gen_mat, del_mat, prod_mat, coppy_mat, zeros_mat, eye_mat, get_diag_mat, sort_eig, hessenberg_mat, hessenberg_householder_mat
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
#ifndef MC_FN_print_error_int
#define MC_FN_print_error_int
// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}
#endif // MC_FN_print_error_int

// (copiada de: mensajes)
#ifndef MC_FN_print_error_dim
#define MC_FN_print_error_dim
// Error de dimensiones: "mensaje (faxca) * (fbxcb)"
void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb) {
    cout << "[MATCLUB ERROR]: " << mensaje
         << " (" << fa << "x" << ca << ") * (" << fb << "x" << cb << ")" << endl;
}
#endif // MC_FN_print_error_dim

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

// (copiada de: jacobi)
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

// (copiada de: householder)
#ifndef MC_FN_hessenberg_mat
#define MC_FN_hessenberg_mat
// Forma de Hessenberg superior por transformaciones de similaridad (eliminacion)
// Descripción: Hace cero los elementos por debajo de la subdiagonal con B^-1*A*B (multiplicadores b_i = a_i,m-1 / a_m,m-1, como en la teoria).
// Si el elemento subdiagonal es cero se intercambian fila y columna con el de mayor magnitud (asi no cambian los autovalores). Devuelve H (new[]).
// Si calc_P es true, P (new[]) es la matriz de transformacion con H = P^-1*A*P (NO es ortogonal): si w es autovector de H, entonces P*w lo es de A.
// Si calc_P es false, P = NULL.
double** hessenberg_mat(double **A, int n, double **&P, bool calc_P) {
    /*
    Ejemplo de uso:
        // A = [7 8 6 6; 1 6 -1 -2; 1 -2 5 -2; 3 4 3 4]
        double **P;
        double **H = hessenberg_mat(A, 4, P, true);    // H = [7 32 -60 6; 1 -1 21 -2; 0 -2 6 0; 0 0 -38 10]
        double **H2 = hessenberg_mat(A, 4, P, false);  // solo H (P = NULL)
    */
    double **H = coppy_mat(A, n, n);
    P = calc_P ? eye_mat(n) : NULL;
    for (int m = 1; m < n - 1; m++) {
        if (H[m][m - 1] == 0.0) {                       // buscar pivote
            int p = m;
            double mx = 0.0;
            for (int j = m + 1; j < n; j++) if (fabs(H[j][m - 1]) > mx) { mx = fabs(H[j][m - 1]); p = j; }
            if (p != m) {
                for (int j = 0; j < n; j++) intercambiar_elem(H[p][j], H[m][j]);   // filas
                for (int j = 0; j < n; j++) intercambiar_elem(H[j][p], H[j][m]);   // columnas
                if (P != NULL)
                    for (int j = 0; j < n; j++) intercambiar_elem(P[j][p], P[j][m]);
            }
        }
        double piv = H[m][m - 1];
        if (piv == 0.0) continue;
        for (int i = m + 1; i < n; i++) {
            double b = H[i][m - 1] / piv;
            if (b != 0.0) {
                for (int j = 0; j < n; j++) H[i][j] -= b * H[m][j];   // B^-1 * H : fila i -= b*fila m
                for (int j = 0; j < n; j++) H[j][m] += b * H[j][i];   // (.) * B  : columna m += b*columna i
                if (P != NULL)
                    for (int j = 0; j < n; j++) P[j][m] += b * P[j][i];   // P = P*B
            }
            H[i][m - 1] = 0.0;
        }
    }
    return H;
}
#endif // MC_FN_hessenberg_mat

// (copiada de: householder)
#ifndef MC_FN_hessenberg_householder_mat
#define MC_FN_hessenberg_householder_mat
// Forma de Hessenberg superior por reflexiones de Householder
// Descripción: Igual que hessenberg_mat pero con reflexiones P = I - 2*v*v^T/(v^T*v) (transformaciones ortogonales, mas estables numericamente).
// Devuelve H (new[]). Si A es simetrica, H es tridiagonal. Si calc_Q es true, Q (new[]) es ortogonal con H = Q^T*A*Q:
// si w es autovector de H, entonces Q*w lo es de A. Si calc_Q es false, Q = NULL.
double** hessenberg_householder_mat(double **A, int n, double **&Q, bool calc_Q) {
    /*
    Ejemplo de uso:
        double **Q;
        double **H = hessenberg_householder_mat(A, n, Q, true);    // H = Q^T*A*Q
        double **H2 = hessenberg_householder_mat(A, n, Q, false);  // solo H (Q = NULL)
    */
    double **H = coppy_mat(A, n, n);
    Q = calc_Q ? eye_mat(n) : NULL;
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
        if (Q != NULL) {                                   // Q = Q*P
            for (int i = 0; i < n; i++) {
                double s = 0.0;
                for (int j = k + 1; j < n; j++) s += Q[i][j] * v[j];
                for (int j = k + 1; j < n; j++) Q[i][j] -= 2.0 * s * v[j] / vv;
            }
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

#ifndef MC_FN_qr_schur_mat
#define MC_FN_qr_schur_mat
// Método QR: forma triangular (de Schur) y matriz de transformacion
// Descripción: Itera A(i) = Q(i)*R(i) -> A(i+1) = R(i)*Q(i) (mismos autovalores) hasta que la suma de |elementos bajo la diagonal| sea < tol.
// 'hess' elige la reduccion previa: 0 = ninguna, 1 = Hessenberg por Householder (ortogonal), 2 = Hessenberg por eliminacion (la de la teoria).
// Devuelve la matriz triangular T (new[]) y el numero de iteraciones. Si calc_M es true, M (new[]) es la matriz acumulada de todas las
// transformaciones con T = M^-1*A*M (ortogonal si hess = 0 o 1); si es false, M = NULL. Con autovalores complejos no converge a triangular.
int qr_schur_mat(double **A, int n, double **&T, double **&M, bool calc_M, double tol, int max_iter, int hess) {
    /*
    Ejemplo de uso:
        double **T, **M;
        int it = qr_schur_mat(A, n, T, M, true, 1e-12, 1000, 1);   // diagonal de T = autovalores
    */
    if (hess < 0 || hess > 2) { print_error_int("qr_schur_mat: hess debe ser 0, 1 o 2", hess); T = NULL; M = NULL; return -1; }
    if (hess == 1)      T = hessenberg_householder_mat(A, n, M, calc_M);
    else if (hess == 2) T = hessenberg_mat(A, n, M, calc_M);
    else { T = coppy_mat(A, n, n); M = calc_M ? eye_mat(n) : NULL; }
    int iter = 0;
    while (iter < max_iter) {
        double bajo = 0.0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++) bajo += fabs(T[i][j]);
        if (bajo < tol) break;
        double **Q, **R;
        qr_givens_mat(T, n, Q, R);
        del_mat(T, n);
        T = prod_mat(R, Q, n, n, n, n);
        if (M != NULL) {
            double **Mn = prod_mat(M, Q, n, n, n, n);
            del_mat(M, n);
            M = Mn;
        }
        del_mat(Q, n); del_mat(R, n);
        iter++;
    }
    if (iter >= max_iter) print_warning("qr_schur_mat alcanzo max_iter (posibles autovalores complejos o poca convergencia).");
    return iter;
}
#endif // MC_FN_qr_schur_mat

#ifndef MC_FN_qr_triang_mat
#define MC_FN_qr_triang_mat
// Método QR: matriz triangular superior semejante a A
// Descripción: Version corta de qr_schur_mat: devuelve solo la matriz triangular T (new[]) y las iteraciones en 'iter_out'.
// Si 'usar_hess' es true se aplica antes la reduccion de Hessenberg (Householder). Su diagonal son los autovalores.
// Con autovalores complejos no converge a triangular (quedan bloques 2x2).
double** qr_triang_mat(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out) {
    /*
    Ejemplo de uso:
        int it;
        double **T = qr_triang_mat(A, n, 1e-12, 1000, true, it);   // diagonal de T = autovalores
    */
    double **T, **M;
    iter_out = qr_schur_mat(A, n, T, M, false, tol, max_iter, usar_hess ? 1 : 0);
    return T;
}
#endif // MC_FN_qr_triang_mat

#ifndef MC_FN_qr_eig
#define MC_FN_qr_eig
// Autovalores y autovectores de una matriz generica: Método QR
// Descripción: Obtiene la forma triangular T = M^-1*A*M con qr_schur_mat; los autovalores son su diagonal y los autovectores se calculan por
// sustitucion regresiva sobre T (y se pasan a A multiplicando por M). TU ELIGES que quieres obtener:
//   calc_autoval -> L = array con los autovalores (new[]). Si es false, L = NULL.
//   calc_autovec -> U = matriz n x n cuyas COLUMNAS son los autovectores normalizados (new[]). Si es false, U = NULL y no se calcula.
//   ordenar      -> ordena por |autovalor| decreciente (los autovectores se reordenan con ellos).
//   hess         -> reduccion previa: 0 = ninguna, 1 = Hessenberg por Householder, 2 = Hessenberg por eliminacion (la de la teoria).
// Devuelve el numero de iteraciones QR (o -1 si hess no es valido). Valido para matrices con autovalores reales.
int qr_eig(double **A, int n, double *&L, double **&U, bool calc_autoval, bool calc_autovec, bool ordenar, double tol, int max_iter, int hess) {
    /*
    Ejemplo de uso:
        // A = [7 8 6 6; 1 6 -1 -2; 1 -2 5 -2; 3 4 3 4]  -> autovalores 10, 7, 4, 1
        double *L; double **U;
        int it = qr_eig(A, 4, L, U, true, true, true, 1e-12, 5000, 1);   // autovalores y autovectores
        qr_eig(A, 4, L, U, true, false, false, 1e-12, 5000, 2);          // solo autovalores (con Hessenberg por eliminacion)
        print_vect(L, 4, "Autovalores");
    */
    L = NULL;
    U = NULL;
    if (!calc_autoval && !calc_autovec) {
        print_warning("qr_eig: no se pidieron ni autovalores ni autovectores, no hay nada que calcular.");
        return 0;
    }
    double **T, **M;
    int iter = qr_schur_mat(A, n, T, M, calc_autovec, tol, max_iter, hess);
    if (iter < 0) return -1;
    double *Ld = get_diag_mat(T, n);
    double **V = NULL;
    if (calc_autovec) {
        // Autovectores de T (triangular superior): para cada k, w_k con w_k[k] = 1 y sustitucion regresiva
        double normT = 0.0;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) if (fabs(T[i][j]) > normT) normT = fabs(T[i][j]);
        if (normT == 0.0) normT = 1.0;
        double smin = 1e-12 * normT;                       // evita dividir por 0 con autovalores repetidos
        double **W = zeros_mat(n, n);
        for (int k = 0; k < n; k++) {
            W[k][k] = 1.0;
            for (int i = k - 1; i >= 0; i--) {
                double s = 0.0;
                for (int j = i + 1; j <= k; j++) s += T[i][j] * W[j][k];
                double den = T[i][i] - T[k][k];
                if (fabs(den) < smin) den = smin;
                W[i][k] = -s / den;
            }
        }
        V = prod_mat(M, W, n, n, n, n);                    // autovectores de A = M * W
        for (int k = 0; k < n; k++) {                      // normalizar columnas
            double nrm = 0.0;
            for (int i = 0; i < n; i++) nrm += V[i][k] * V[i][k];
            nrm = sqrt(nrm);
            if (nrm > 0.0) for (int i = 0; i < n; i++) V[i][k] /= nrm;
        }
        del_mat(W, n);
        del_mat(M, n);
    }
    del_mat(T, n);
    if (ordenar) sort_eig(Ld, V, n);
    U = V;
    if (calc_autoval) L = Ld; else delete[] Ld;
    return iter;
}
#endif // MC_FN_qr_eig

#endif // MATCLUB_QR_CPP
