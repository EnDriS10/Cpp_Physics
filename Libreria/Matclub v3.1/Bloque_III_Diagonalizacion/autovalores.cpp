// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.1
// El problema de los autovalores
// ============================================================================
// Polinomio caracteristico, cociente de Rayleigh, residuos, similaridad y metodo de la potencia (directa e inversa).
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "autovalores.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (7): poly_caract_mat, rayleigh_mat, resid_eig, resid_eig_mat, similar_mat, potencia_eig, potencia_inv_eig
// Dependencias copiadas (17): print_error, print_warning, print_error_dim, intercambiar_elem, copy_vect, gen_mat, del_mat, prod_mat, coppy_mat, zeros_mat, trace_mat, get_col_mat, prod_mat_vect, lu_forma1, gauss_solve, det_lu, inv_lu
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_AUTOVALORES_CPP
#define MATCLUB_AUTOVALORES_CPP

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
#ifndef MC_FN_trace_mat
#define MC_FN_trace_mat
// Traza de una matriz cuadrada (suma de la diagonal principal)
double trace_mat(double **A, int n) {
    double tr = 0.0;
    for (int i = 0; i < n; i++) {
        tr += A[i][i];
    }
    return tr;
}
#endif // MC_FN_trace_mat

// (copiada de: matrices)
#ifndef MC_FN_get_col_mat
#define MC_FN_get_col_mat
// Extrae la columna 'col_idx' de una matriz y la devuelve como un vector dinámico 1D
					//Importante: LOS CONVIERTE EN UN POINTER, VECT EN ESTA LIBRERIA
double* get_col_mat(double **A, int f, int c, int col_idx) {
    double *v = new double[f];
    for (int i = 0; i < f; i++) {
        v[i] = A[i][col_idx];
    }
    return v;
}
#endif // MC_FN_get_col_mat

// (copiada de: matrices)
#ifndef MC_FN_prod_mat_vect
#define MC_FN_prod_mat_vect
// Producto matriz x vector: y = A*x  (A de f x c, x de tamano n = c)
double* prod_mat_vect(double **A, int f, int c, double *x, int n) {
    if (c != n) {
        print_error_dim("prod_mat_vect: dimensiones incompatibles", f, c, n, 1);
        return NULL;
    }
    double *y = new double[f];
    for (int i = 0; i < f; i++) {
        double s = 0.0;
        for (int j = 0; j < c; j++) s += A[i][j] * x[j];
        y[i] = s;
    }
    return y;
}
#endif // MC_FN_prod_mat_vect

// (copiada de: factorizacion_lu)
#ifndef MC_FN_lu_forma1
#define MC_FN_lu_forma1
// Factorización LU (Forma 1 - Descomposición de Doolittle)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma1(double **A, int n, double **L, double **U) {
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

// (copiada de: eliminacion_gauss)
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

// (copiada de: determinantes_inversas)
#ifndef MC_FN_det_lu
#define MC_FN_det_lu
// 1B. Determinante usando Factorización LU (Doolittle)
double det_lu(double **A, int n) {
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

// (copiada de: determinantes_inversas)
#ifndef MC_FN_inv_lu
#define MC_FN_inv_lu
// 2B. Inversa de una matriz usando Factorización LU
double** inv_lu(double **A, int n) {
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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: El problema de los autovalores
// ----------------------------------------------------------------------------

#ifndef MC_FN_poly_caract_mat
#define MC_FN_poly_caract_mat
// Polinomio característico de una matriz (Algoritmo de Faddeev-LeVerrier)
// Descripción: Devuelve los n+1 coeficientes (potencias decrecientes, listo para 'polyval') del polinomio monico det(lambda*I - A).
// Nota: el p(lambda) = det(A - lambda*I) de la teoria vale (-1)^n veces este polinomio; sus raices (los autovalores) son las mismas.
double* poly_caract_mat(double **A, int n) {
    /*
    Ejemplo de uso:
        // A = [3 0 1; 0 -3 0; 1 0 3]  ->  p = lambda^3 - 3*lambda^2 - 10*lambda + 24 = (l-4)(l+3)(l-2)
        double *p = poly_caract_mat(A, 3);     // p = {1, -3, -10, 24}
        cout << polyval(p, 4, 4.0);            // 0 : lambda = 4 es autovalor
    */
    double *c = new double[n + 1];
    double **M = zeros_mat(n, n);              // M_0 = 0
    c[0] = 1.0;
    for (int k = 1; k <= n; k++) {
        // M_k = A*M_(k-1) + c_(n-k+1)*I
        double **AM = prod_mat(A, M, n, n, n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = AM[i][j] + ((i == j) ? c[k - 1] : 0.0);
        del_mat(AM, n);
        // c_(n-k) = -traza(A*M_k)/k
        double **AMk = prod_mat(A, M, n, n, n, n);
        c[k] = -trace_mat(AMk, n) / k;
        del_mat(AMk, n);
    }
    del_mat(M, n);
    return c;
}
#endif // MC_FN_poly_caract_mat

#ifndef MC_FN_rayleigh_mat
#define MC_FN_rayleigh_mat
// Cociente de Rayleigh
// Descripción: Calcula x^T*A*x / x^T*x. Si x es un autovector devuelve su autovalor; si no, es la mejor estimacion del autovalor.
double rayleigh_mat(double **A, int n, double *x) {
    /*
    Ejemplo de uso:
        double v[] = {1, 0, 1};
        double lambda = rayleigh_mat(A, 3, v);   // 4 para A = [3 0 1; 0 -3 0; 1 0 3]
    */
    double *Ax = prod_mat_vect(A, n, n, x, n);
    double num = 0.0, den = 0.0;
    for (int i = 0; i < n; i++) { num += x[i] * Ax[i]; den += x[i] * x[i]; }
    delete[] Ax;
    return num / den;
}
#endif // MC_FN_rayleigh_mat

#ifndef MC_FN_resid_eig
#define MC_FN_resid_eig
// Residuo de un par autovalor-autovector
// Descripción: Devuelve la norma ||A*x - lambda*x||. Vale ~0 si (lambda, x) es un par autovalor-autovector correcto.
double resid_eig(double **A, int n, double lambda, double *x) {
    /*
    Ejemplo de uso:
        double r = resid_eig(A, 3, 4.0, v);   // ~0
    */
    double *Ax = prod_mat_vect(A, n, n, x, n);
    double s = 0.0;
    for (int i = 0; i < n; i++) s += (Ax[i] - lambda * x[i]) * (Ax[i] - lambda * x[i]);
    delete[] Ax;
    return sqrt(s);
}
#endif // MC_FN_resid_eig

#ifndef MC_FN_resid_eig_mat
#define MC_FN_resid_eig_mat
// Residuo máximo de todos los pares autovalor-autovector
// Descripción: Comprueba A*u_k = L[k]*u_k para cada columna u_k de U y devuelve el mayor residuo.
double resid_eig_mat(double **A, int n, double *L, double **U) {
    /*
    Ejemplo de uso:
        double r = resid_eig_mat(A, n, L, U);   // ~1e-12 si la diagonalizacion es buena
    */
    double mx = 0.0;
    for (int k = 0; k < n; k++) {
        double *u = get_col_mat(U, n, n, k);
        double r = resid_eig(A, n, L[k], u);
        delete[] u;
        if (r > mx) mx = r;
    }
    return mx;
}
#endif // MC_FN_resid_eig_mat

#ifndef MC_FN_similar_mat
#define MC_FN_similar_mat
// Transformación de similaridad V^-1 * A * V
// Descripción: Si las columnas de V son autovectores de A, el resultado es la matriz diagonal de autovalores diag(l1,...,ln).
double** similar_mat(double **A, double **V, int n) {
    /*
    Ejemplo de uso:
        double **D = similar_mat(A, V, 3);   // diag(4, -3, 2) si V = [1 0 1; 0 1 0; 1 0 -1]
    */
    double **Vi = inv_lu(V, n);
    if (Vi == NULL) { print_error("similar_mat: V no es invertible"); return NULL; }
    double **AV = prod_mat(A, V, n, n, n, n);
    double **R = prod_mat(Vi, AV, n, n, n, n);
    del_mat(Vi, n); del_mat(AV, n);
    return R;
}
#endif // MC_FN_similar_mat

#ifndef MC_FN_potencia_eig
#define MC_FN_potencia_eig
// Autovalor dominante: Método de la potencia
// Descripción: Itera x <- A*x/||A*x|| y estima el autovalor de mayor valor absoluto con el cociente de Rayleigh.
// Devuelve el autovalor y, por referencia, el autovector normalizado (v_out, reservado con new[]).
double potencia_eig(double **A, int n, double *&v_out, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double *v;
        double lambda = potencia_eig(A, 3, v, 1e-12, 1000);   // 4 para A = [3 0 1; 0 -3 0; 1 0 3]
    */
    double *x = new double[n];
    for (int i = 0; i < n; i++) x[i] = 1.0 + 0.1 * i;        // vector de partida generico
    double lambda = 0.0;
    for (int it = 0; it < max_iter; it++) {
        double *y = prod_mat_vect(A, n, n, x, n);
        double nrm = 0.0;
        for (int i = 0; i < n; i++) nrm += y[i] * y[i];
        nrm = sqrt(nrm);
        if (nrm == 0.0) { delete[] y; break; }
        double num = 0.0, den = 0.0;
        for (int i = 0; i < n; i++) { num += x[i] * y[i]; den += x[i] * x[i]; }
        lambda = num / den;
        double dif_m = 0.0, dif_p = 0.0;                    // el signo del autovector puede alternar si lambda < 0
        for (int i = 0; i < n; i++) {
            double xn = y[i] / nrm;
            dif_m += (xn - x[i]) * (xn - x[i]);
            dif_p += (xn + x[i]) * (xn + x[i]);
            x[i] = xn;
        }
        delete[] y;
        if (sqrt(dif_m < dif_p ? dif_m : dif_p) < tol) { lambda = rayleigh_mat(A, n, x); break; }
    }
    v_out = x;
    return lambda;
}
#endif // MC_FN_potencia_eig

#ifndef MC_FN_potencia_inv_eig
#define MC_FN_potencia_inv_eig
// Autovalor más cercano a un valor dado: Método de la potencia inversa con desplazamiento
// Descripción: Itera (A - mu*I)*y = x, de forma que converge al autovalor de A mas cercano a 'mu'. Con mu = 0 da el de menor valor absoluto.
// Devuelve el autovalor y, por referencia, su autovector normalizado (v_out, reservado con new[]).
double potencia_inv_eig(double **A, int n, double mu, double *&v_out, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double *v;
        double lambda = potencia_inv_eig(A, 3, 1.8, v, 1e-12, 100);   // 2 para A = [3 0 1; 0 -3 0; 1 0 3]
    */
    double *x = new double[n];
    for (int i = 0; i < n; i++) x[i] = 1.0 + 0.1 * i;
    double lambda = mu;
    for (int it = 0; it < max_iter; it++) {
        double **M = coppy_mat(A, n, n);
        for (int i = 0; i < n; i++) M[i][i] -= mu;
        double *y = gauss_solve(M, x, n);
        del_mat(M, n);
        if (y == NULL) { mu += 1e-10 * (1.0 + fabs(mu)); continue; }   // mu era (casi) un autovalor exacto
        double nrm = 0.0;
        for (int i = 0; i < n; i++) nrm += y[i] * y[i];
        nrm = sqrt(nrm);
        for (int i = 0; i < n; i++) x[i] = y[i] / nrm;
        delete[] y;
        double nuevo = rayleigh_mat(A, n, x);
        if (fabs(nuevo - lambda) < tol) { lambda = nuevo; break; }
        lambda = nuevo;
    }
    v_out = x;
    return lambda;
}
#endif // MC_FN_potencia_inv_eig

#endif // MATCLUB_AUTOVALORES_CPP
