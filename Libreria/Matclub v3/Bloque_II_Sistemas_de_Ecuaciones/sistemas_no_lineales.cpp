// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.3
// Sistemas no lineales
// ============================================================================
// Sustituciones sucesivas (Jacobi y Gauss-Seidel no lineales) y Newton-Raphson para sistemas.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "sistemas_no_lineales.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (5): check_convergence_nolin, jacobi_nolin, gauss_seidel_nolin, newton_raphson_sys, newton_raphson_multi_sys
// Dependencias copiadas (14): MC_NAN, print_error, print_warning, copy_vect, prod_vect, mod_vect, resta_vect, gen_mat, del_mat, zeros_mat, lu_forma2, lu_forma2_sol, part_derv, jacobian_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_SISTEMAS_NO_LINEALES_CPP
#define MATCLUB_SISTEMAS_NO_LINEALES_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

// (constante global)
#ifndef MC_FN_MC_NAN
#define MC_FN_MC_NAN
const double MC_NAN = sqrt(-1.0);
#endif // MC_FN_MC_NAN

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
#ifndef MC_FN_lu_forma2
#define MC_FN_lu_forma2
// Factorización LU (Forma 2 - Alternando fila U y columna L)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma2(double **A, int n, double **L, double **U) {
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

// (copiada de: factorizacion_lu)
#ifndef MC_FN_lu_forma2_sol
#define MC_FN_lu_forma2_sol
// Resuelve Ax = b usando LU Forma 2
double* lu_forma2_sol(double **A, double *b, int n) {
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

// (copiada de: derivacion)
#ifndef MC_FN_part_derv
#define MC_FN_part_derv
// Derivada parcial numérica usando diferencias finitas progresivas.
// Descripción: Calcula el cambio de la función 'f' respecto a la variable 'j' variando 'h'.
double part_derv(double (*f)(double*, int), double *x, int n, int j) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0] + sin(v[1]); }
        double punto[] = {2.0, 3.14};
        double df_dy = part_derv(mi_func, punto, 2, 1);
    */
    double *xh = copy_vect(x, n);
    double h = (fabs(x[j]) > 1e-8) ? 0.0001 * x[j] : 1e-5; 
    
    xh[j] = x[j] + h; 
    double deriv = (f(xh, n) - f(x, n)) / h; // Fórmula de diferencias progresivas
    
    delete[] xh;
    return deriv;
}
#endif // MC_FN_part_derv

// (copiada de: derivacion)
#ifndef MC_FN_jacobian_mat
#define MC_FN_jacobian_mat
// Matriz Jacobiana
// Descripción: Construye la matriz nxn de derivadas parciales para un sistema de n funciones.
double** jacobian_mat(double (*AF[])(double*, int), double *x, int n) {
    /*
    Ejemplo de uso:
        double (*Sist[2])(double*, int) = {f1, f2};
        double punto[] = {1.0, 1.0};
        double **J = jacobian_mat(Sist, punto, 2);
        print_mat(J, 2, 2, "Jacobiano");
        del_mat(J, 2);
    */
    double **J = gen_mat(J, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            J[i][j] = part_derv(AF[i], x, n, j);
        }
    }
    return J;
}
#endif // MC_FN_jacobian_mat

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Sistemas no lineales
// ----------------------------------------------------------------------------

#ifndef MC_FN_check_convergence_nolin
#define MC_FN_check_convergence_nolin
// Comprobador de Condición de Convergencia
// Descripción: Verifica si la suma del valor absoluto de las derivadas parciales de cada función es <= 1.
bool check_convergence_nolin(double (*AF[])(double*, int), double *x, int n) {
    /*
    Ejemplo de uso: (Se utiliza internamente en Jacobi y Gauss-Seidel)
        bool converge = check_convergence_nolin(AF, punto_inicial, n);
    */
    for (int i = 0; i < n; i++) {
        double sum_derivs = 0.0;
        for (int j = 0; j < n; j++) {
            sum_derivs += fabs(part_derv(AF[i], x, n, j));
        }
        if (sum_derivs > 1.0) return false;
    }
    return true;
}
#endif // MC_FN_check_convergence_nolin

#ifndef MC_FN_jacobi_nolin
#define MC_FN_jacobi_nolin
// 1. Jacobi para Sistemas No Lineales
// Descripción: Resuelve iterativamente un sistema reordenado xi = Fi(x1...xn) usando desplazamientos simultáneos.
double* jacobi_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        // Las funciones deben estar despejadas: x = F1(...), y = F2(...)
        double (*Sist[2])(double*, int) = {F1, F2};
        double p0[] = {0.4, 3.0};
        double *sol = jacobi_nolin_sys(Sist, p0, 2, 1e-6, 100);
    */
    if (!check_convergence_nolin(AF, x_init, n)) {
        print_warning("La condicion suficiente de convergencia (suma derivadas <= 1) NO se cumple. Podria diverger.");
    }

    double *x_old = copy_vect(x_init, n);
    double *x_new = new double[n];
    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) x_new[i] = AF[i](x_old, n);

        double *diff = resta_vect(x_new, x_old, n);
        error = mod_vect(diff, n);
        delete[] diff;

        for (int i = 0; i < n; i++) x_old[i] = x_new[i];
        iter++;
    }
    delete[] x_old;
    return x_new;
}
#endif // MC_FN_jacobi_nolin

#ifndef MC_FN_gauss_seidel_nolin
#define MC_FN_gauss_seidel_nolin
// 2. Gauss-Seidel para Sistemas No Lineales
// Descripción: Similar a Jacobi, pero usa los valores recién calculados (desplazamientos sucesivos).
double* gauss_seidel_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double (*Sist[2])(double*, int) = {F1, F2};
        double p0[] = {0.4, 3.0};
        double *sol = gauss_seidel_nolin_sys(Sist, p0, 2, 1e-6, 100);
    */
    if (!check_convergence_nolin(AF, x_init, n)) {
        print_warning("La condicion suficiente de convergencia (suma derivadas <= 1) NO se cumple. Podria diverger.");
    }

    double *x_old = copy_vect(x_init, n);
    double *x_new = copy_vect(x_init, n);
    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) x_old[i] = x_new[i];

        for (int i = 0; i < n; i++) x_new[i] = AF[i](x_new, n);

        double *diff = resta_vect(x_new, x_old, n);
        error = mod_vect(diff, n);
        delete[] diff;
        iter++;
    }
    delete[] x_old;
    return x_new;
}
#endif // MC_FN_gauss_seidel_nolin

#ifndef MC_FN_newton_raphson_sys
#define MC_FN_newton_raphson_sys
// 3. Newton-Raphson Multivariable (Generalizado para n ecuaciones)
// Descripción: Resuelve el sistema F(x)=0 aproximando las derivadas por diferencias finitas (Jacobiano).
double* newton_raphson_sys(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        // Las funciones deben estar igualadas a cero: f1(x,y)=0, f2(x,y)=0
        double (*Sist[2])(double*, int) = {f1, f2};
        double p0[] = {0.6, 3.0};
        double *sol = newton_raphson_sys(Sist, p0, 2, 1e-8, 100);
    */
    double *x_old = copy_vect(x_init, n);
    double *x_new = new double[n];
    double *F = new double[n];
    double *dx = NULL;
    
    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) F[i] = -AF[i](x_old, n);
        
        double **J = jacobian_mat(AF, x_old, n); // Jacobiano por diferencias finitas
        dx = lu_forma2_sol(J, F, n);
        del_mat(J, n);
        
        if (dx == NULL) {
            print_error("Jacobiano singular en Newton-Raphson.");
            delete[] F; delete[] x_old; delete[] x_new;
            return NULL;
        }

        for (int i = 0; i < n; i++) x_new[i] = x_old[i] + dx[i];

        error = mod_vect(dx, n);
        for (int i = 0; i < n; i++) x_old[i] = x_new[i];
        
        iter++;
        delete[] dx; 
    }
    delete[] F; delete[] x_old;
    return x_new;
}
#endif // MC_FN_newton_raphson_sys

#ifndef MC_FN_newton_raphson_multi_sys
#define MC_FN_newton_raphson_multi_sys
// 4. Newton-Raphson Array de Soluciones
// Descripción: Ejecuta Newton-Raphson sobre múltiples puntos de inicio. Devuelve una matriz de soluciones.
double** newton_raphson_multi_sys(double (*AF[])(double*, int), double **x_inits, int num_puntos, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double **puntos_iniciales = gen_mat(puntos_iniciales, 3, 2);
        // Llenar puntos_iniciales con 3 semillas distintas (ej. {0.6, 3.0}, {-0.4, 1.7}, etc.)
        double **soluciones = newton_raphson_multi_sys(Sist, puntos_iniciales, 3, 2, 1e-8, 50);
        print_mat(soluciones, 3, 2, "Array de Soluciones");
    */
    double **soluciones = gen_mat(soluciones, num_puntos, n);
    
    for (int k = 0; k < num_puntos; k++) {
        double *sol = newton_raphson_sys(AF, x_inits[k], n, tol, max_iter);
        if (sol != NULL) {
            for (int i = 0; i < n; i++) soluciones[k][i] = sol[i];
            delete[] sol;
        } else {
            for (int i = 0; i < n; i++) soluciones[k][i] = MC_NAN; // Si falla, rellena con NaN
        }
    }
    return soluciones;
}
#endif // MC_FN_newton_raphson_multi_sys

#endif // MATCLUB_SISTEMAS_NO_LINEALES_CPP
