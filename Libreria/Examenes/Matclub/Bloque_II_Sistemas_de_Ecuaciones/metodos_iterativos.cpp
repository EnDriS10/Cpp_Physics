// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas lineales: metodos iterativos
// ============================================================================
// Comprobacion de dominancia diagonal, Jacobi, Gauss-Seidel y sobrerrelajacion (SOR).
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "metodos_iterativos.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (5): check_dominancia, reorder_diagonals, jacobi_solve, gauss_seidel_solve, sor_solve
// Dependencias copiadas (11): print_error, print_warning, print_info, intercambiar_elem, copy_vect, prod_vect, mod_vect, resta_vect, gen_mat, del_mat, coppy_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_METODOS_ITERATIVOS_CPP
#define MATCLUB_METODOS_ITERATIVOS_CPP

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
#ifndef MC_FN_print_info
#define MC_FN_print_info
// Informacion (p. ej. "archivo guardado")
void print_info(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB INFO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_info

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

// (copiada de: vectores)
#ifndef MC_FN_prod_vect
#define MC_FN_prod_vect
//Producto Punto
   double prod_vect(double *a,double *b ,int n) { 
   		double prod=0; 
   		for ( int i = 0; i<n ; i++){
		prod = prod + a[i]*b[i];
		}    
        return prod; 
    }
#endif // MC_FN_prod_vect

// (copiada de: vectores)
#ifndef MC_FN_mod_vect
#define MC_FN_mod_vect
//Modulo Vectorial
    double mod_vect(double *a,int n) { 
   		double mod;
		mod= sqrt(prod_vect(a,a,n)); 
        return mod; 
    }   
#endif // MC_FN_mod_vect

// (copiada de: vectores)
#ifndef MC_FN_resta_vect
#define MC_FN_resta_vect
// Resta de Vectores
   double* resta_vect(double *a,double *b ,int n) { 
   		double *c ;		c=new double [n];
   		for ( int i = 0; i<n ; i++){
			c[i] = a[i] - b[i];
		}   
    return c; 
	}
#endif // MC_FN_resta_vect

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
// FUNCIONES DEL MODULO: Sistemas lineales: metodos iterativos
// ----------------------------------------------------------------------------

#ifndef MC_FN_check_dominancia
#define MC_FN_check_dominancia
/// Función Auxiliar: Comprueba estrictamente si una matriz es diagonalmente dominante
// Descripción: Comprueba si A es diagonalmente dominante por filas: |a_ii| >= suma de |a_ij| (j != i) en todas las filas. Es una condicion SUFICIENTE (no necesaria) para que converjan Jacobi y Gauss-Seidel. Esta funcion acepta tambien la igualdad (dominancia debil).
bool check_dominancia(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, -2, 7, 2, 1, 2, -5};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        bool ok = check_dominancia(A, 3);
        // Resultado: ok = true
    */
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) sum += fabs(A[i][j]);
        }
        // Condición teórica: |A_ii| >= sum_{j!=i} |A_ij|
        if (fabs(A[i][i]) < sum) {
            return false; 
        }
    }
    return true;
}
#endif // MC_FN_check_dominancia

#ifndef MC_FN_reorder_diagonals
#define MC_FN_reorder_diagonals
// Función Auxiliar: Reordena las filas (A y b) solo si la matriz no es dominante de entrada
// Descripción: Intenta conseguir dominancia diagonal reordenando las filas de A y b EN SITIO (no cambia la solucion del sistema). Si A ya es dominante no hace nada. Devuelve true si lo consigue; si no, avisa de que la convergencia no esta garantizada.
bool reorder_diagonals(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, 1, 2, -5, -2, 7, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {11, -1, 5};
        bool ok = reorder_diagonals(A, b, 3);
        // Resultado: ok = true , A = [6, -2, 1; -2, 7, 2; 1, 2, -5] , b = [11, 5, -1]
    */
    // 1. Si ya es dominante de fábrica, no alteramos el sistema original
    if (check_dominancia(A, n)) {
        return true; 
    }

    // 2. Si no lo es, intentamos rescatarla reordenando el mayor elemento a la diagonal
    bool swapped = false;
    for (int i = 0; i < n; i++) {
        int max_row = i;
        double max_val = fabs(A[i][i]);
        
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > max_val) {
                max_val = fabs(A[k][i]);
                max_row = k;
            }
        }
        
        if (max_row != i) {
            for (int j = 0; j < n; j++) {
                intercambiar_elem(A[i][j], A[max_row][j]);
            }
            intercambiar_elem(b[i], b[max_row]);
            swapped = true;
        }
    }
    
    // 3. Comprobar si el "Plan B" (reordenamiento) logró hacerla dominante
    bool es_dominante = check_dominancia(A, n);
    
    if (swapped) print_info("El sistema original no era optimo. Ha sido reordenado por filas.");
    if (!es_dominante) {
        print_warning("Incluso tras reordenar, la matriz no es diagonalmente dominante. La convergencia NO esta garantizada.");
    }
    
    return es_dominante;
}
#endif // MC_FN_reorder_diagonals

#ifndef MC_FN_jacobi_solve
#define MC_FN_jacobi_solve
// Método Iterativo de Jacobi (Desplazamientos simultáneos)
// Descripción: Metodo iterativo de Jacobi (desplazamientos simultaneos): x_i(k+1) = (b_i - sum_{j!=i} a_ij*x_j(k)) / a_ii. Para cuando la norma del cambio entre dos iteraciones es menor que tol o se llega a max_iter (en ese caso avisa).
// Condiciones: a_ii != 0 (si hay un cero en la diagonal avisa y devuelve NULL) y convergencia garantizada si A es diagonalmente dominante. Util en matrices grandes y dispersas. No modifica A ni b.
double* jacobi_solve(double **A, double *b, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, -2, 7, 2, 1, 2, -5};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {11, 5, -1};
        double *x = jacobi_solve(A, b, 3, 1e-10, 500);
        // Resultado: x = [2, 1, 1]
    */
    // 1. Trabajamos con copias para no destruir las matrices originales del main
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    // 2. Intentar hacer la matriz diagonalmente dominante
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    // 3. Aproximación inicial: x_i^(0) = b_i / A_ii
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Jacobi no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
    }

    int iter = 0;
    double error = tol + 1.0;

    // 4. Bucle principal de Jacobi
    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Jacobi usa exclusivamente los valores de la iteración anterior oldx[j]
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * oldx[j];
                }
            }
        }

        // Calculamos error evaluando la norma euclidiana de la diferencia
        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;

        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        iter++;
    }
    
    if (iter == max_iter) print_warning("Jacobi alcanzo max_iter sin converger.");
    
    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}
#endif // MC_FN_jacobi_solve

#ifndef MC_FN_gauss_seidel_solve
#define MC_FN_gauss_seidel_solve
// Método Iterativo de Gauss-Seidel (Desplazamientos sucesivos)
// Descripción: Metodo iterativo de Gauss-Seidel (desplazamientos sucesivos): usa en cada paso los valores ya actualizados de la misma iteracion, por lo que suele converger el doble de rapido que Jacobi.
// Condiciones: a_ii != 0 (si no, avisa y devuelve NULL); converge si A es diagonalmente dominante o simetrica definida positiva. Para cuando la norma del cambio entre iteraciones es menor que tol. No modifica A ni b.
double* gauss_seidel_solve(double **A, double *b, int n, double tol, int max_iter ) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, -2, 7, 2, 1, 2, -5};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {11, 5, -1};
        double *x = gauss_seidel_solve(A, b, 3, 1e-10, 500);
        // Resultado: x = [2, 1, 1]
    */
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Gauss-Seidel no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
        newx[i] = oldx[i];
    }

    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Gauss-Seidel usa newx[j] porque el valor se actualiza inmediatamente
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * newx[j]; 
                }
            }
        }

        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    if (iter == max_iter) print_warning("Gauss-Seidel alcanzo max_iter sin converger.");

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}
#endif // MC_FN_gauss_seidel_solve

#ifndef MC_FN_sor_solve
#define MC_FN_sor_solve
// Método de Sobrerrelajación (SOR) - Extensión de Gauss-Seidel
// El valor óptimo de w está entre 1 y 2. Para w=1 es idéntico a Gauss-Seidel.
// Descripción: Sobrerrelajacion sucesiva (SOR): Gauss-Seidel con factor de relajacion w, x_i = (1-w)*x_i + w*x_i(GS). w = 1 es Gauss-Seidel; el optimo suele estar entre 1 y 2 (si w > 1 acelera).
// Condiciones: 0 < w < 2 (si no, avisa y devuelve NULL) y las mismas que Gauss-Seidel (A simetrica definida positiva o diagonalmente dominante). No modifica A ni b.
double* sor_solve(double **A, double *b, int n, double w, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double Ad[16] = {4, -1, -1, -1, -1, 4, -1, -1, -1, -1, 4, -1, -1, -1, -1, 4};
        double **A = zeros_mat(4, 4);
        for (int i = 0; i < 16; i++) A[i / 4][i % 4] = Ad[i];
        double b[4] = {1, 1, 1, 1};
        double *x = sor_solve(A, b, 4, 1.3, 1e-10, 500);
        // Resultado: x = [1, 1, 1, 1]
    */
    if (w <= 0.0 || w >= 2.0) {
        print_error("El factor de relajacion w debe estar estrictamente entre 0 y 2 para evitar divergencias.");
        return NULL;
    }

    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. SOR no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
        newx[i] = oldx[i];
    }

    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        
        for (int i = 0; i < n; i++) {
            // Calcular el valor temporal como si fuera Gauss-Seidel
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += M[i][j] * newx[j];
                }
            }
            
            // Aplicar la corrección con el factor de relajación w multiplicando al residuo
            newx[i] = oldx[i] + (w / M[i][i]) * (vb[i] - sum - M[i][i] * oldx[i]);
        }

        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    if (iter == max_iter) print_warning("SOR alcanzo max_iter sin converger.");

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}
#endif // MC_FN_sor_solve

#endif // MATCLUB_METODOS_ITERATIVOS_CPP
