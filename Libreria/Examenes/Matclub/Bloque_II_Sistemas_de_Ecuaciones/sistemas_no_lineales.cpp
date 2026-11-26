// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.3
// Sistemas no lineales
// ============================================================================
// Sustituciones sucesivas (Jacobi y Gauss-Seidel no lineales), Newton-Raphson para sistemas y busqueda de TODAS las soluciones dentro de un rango (malla o semillas aleatorias).
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "sistemas_no_lineales.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (10): check_convergence_nolin, jacobi_nolin, gauss_seidel_nolin, newton_raphson_sys, newton_raphson_multi_sys, lineal_silencioso, newton_raphson_sys_ok, newton_raphson_sys_filtrado, newton_raphson_sys_rango, newton_raphson_sys_rango_aleat
// Dependencias copiadas (20): MC_NAN, print_error, print_warning, print_error_int, intercambiar_elem, isNaN, copy_vect, prod_vect, mod_vect, resta_vect, gen_mat, del_mat, coppy_mat, zeros_mat, lu_forma2, lu_forma2_sol, pesos_deriv_lagrange, part_derv_c, part_derv, jacobian_mat
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

// (copiada de: mensajes)
#ifndef MC_FN_print_error_int
#define MC_FN_print_error_int
// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}
#endif // MC_FN_print_error_int

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

// (copiada de: auxiliares)
#ifndef MC_FN_isNaN
#define MC_FN_isNaN
bool isNaN(double v) {
    return v != v; // En norma IEEE 754, NaN es distinto de sí mismo
}
#endif // MC_FN_isNaN

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

// (copiada de: factorizacion_lu)
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

// (copiada de: derivacion)
#ifndef MC_FN_pesos_deriv_lagrange
#define MC_FN_pesos_deriv_lagrange
// Pesos de derivación (derivada del polinomio de Lagrange)
// Descripción: Para los m nodos xs[0..m-1] calcula los pesos w[j] tales que f^(orden)(xt) ~ sum(w[j]*f(xs[j])), con orden = 1 o 2. Vale para nodos NO equiespaciados.
// Con nodos equiespaciados reproduce las formulas clasicas (centrales, progresivas y regresivas). 'w' debe tener m posiciones.
void pesos_deriv_lagrange(double *xs, int m, double xt, int orden, double *w) {
    /*
    Ejemplo de uso:
        double xs[] = {1.9, 2.0, 2.1}, w[3];
        pesos_deriv_lagrange(xs, 3, 2.0, 1, w);     // w = {-5, 0, 5}  (central: (f(x+h)-f(x-h))/(2h) con h = 0.1)
    */
    for (int j = 0; j < m; j++) {
        double D = 1.0;
        for (int k = 0; k < m; k++) if (k != j) D *= (xs[j] - xs[k]);
        double s = 0.0;
        for (int a = 0; a < m; a++) {
            if (a == j) continue;
            if (orden == 1) {
                double p = 1.0;
                for (int k = 0; k < m; k++) if (k != j && k != a) p *= (xt - xs[k]);
                s += p;
            } else {
                for (int l = 0; l < m; l++) {
                    if (l == j || l == a) continue;
                    double p = 1.0;
                    for (int k = 0; k < m; k++) if (k != j && k != a && k != l) p *= (xt - xs[k]);
                    s += p;
                }
            }
        }
        w[j] = s / D;
    }
}
#endif // MC_FN_pesos_deriv_lagrange

// (copiada de: derivacion)
#ifndef MC_FN_part_derv_c
#define MC_FN_part_derv_c
// Derivada parcial CENTRAL de alta precisión
// Descripción: Calcula df/dx_j con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9; error O(h^(puntos-1))). Mas puntos = mas precision pero mas evaluaciones de f (puntos-1).
// Si h <= 0 elige automaticamente el paso que equilibra truncamiento y redondeo: h = eps^(1/puntos) * max(1, |x_j|). f debe ser suave (derivable) en el entorno del punto.
double part_derv_c(double (*f)(double*, int), double *x, int n, int j, double h, int puntos) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0]*v[1] + sin(v[1]); }
        double punto[] = {2.0, 0.5};
        double dfdx = part_derv_c(mi_func, punto, 2, 0, 0.0, 5);   // 2*x*y = 2.0 (paso automatico, 5 puntos)
        double dfdy = part_derv_c(mi_func, punto, 2, 1, 1e-3, 7);  // x^2 + cos(y) = 4.8775826 (h = 1e-3, 7 puntos)
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("part_derv_c: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    if (j < 0 || j >= n) { print_error_int("part_derv_c: la variable j esta fuera de rango", j); return MC_NAN; }
    if (h <= 0.0) h = pow(2.220446049250313e-16, 1.0 / puntos) * ((fabs(x[j]) > 1.0) ? fabs(x[j]) : 1.0);
    int m = puntos / 2;
    double xs[9], w[9];
    for (int k = 0; k < puntos; k++) xs[k] = (double)(k - m);
    pesos_deriv_lagrange(xs, puntos, 0.0, 1, w);          // pesos centrales para paso unidad
    double *xh = copy_vect(x, n);
    double suma = 0.0;
    for (int k = 0; k < puntos; k++) {
        if (k == m) continue;                              // el peso central es 0
        xh[j] = x[j] + (k - m) * h;
        suma += w[k] * f(xh, n);
    }
    delete[] xh;
    return suma / h;
}
#endif // MC_FN_part_derv_c

// (copiada de: derivacion)
#ifndef MC_FN_part_derv
#define MC_FN_part_derv
// Derivada parcial numérica CENTRAL de 5 puntos (error O(h^4)).
// Descripción: Calcula df/dx_j con diferencias centrales de 5 puntos y paso automatico (eps^(1/5)*max(1,|x_j|)). Para elegir el paso o el nº de puntos (3, 5, 7, 9) usa part_derv_c.
double part_derv(double (*f)(double*, int), double *x, int n, int j) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0] + sin(v[1]); }
        double punto[] = {2.0, 3.14};
        double df_dy = part_derv(mi_func, punto, 2, 1);
    */
    return part_derv_c(f, x, n, j, 0.0, 5);
}
#endif // MC_FN_part_derv

// (copiada de: derivacion)
#ifndef MC_FN_jacobian_mat
#define MC_FN_jacobian_mat
// Matriz Jacobiana
// Descripción: Construye la matriz nxn de derivadas parciales para un sistema de n funciones. Usa part_derv (centrales de 5 puntos, O(h^4)).
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

#ifndef MC_FN_lineal_silencioso
#define MC_FN_lineal_silencioso
// Sistema lineal pequeño SIN mensajes (ayuda para Newton en rango)
// Descripción: Resuelve A*x = b por eliminacion gaussiana con pivoteo parcial sobre copias de A y b (no las modifica) y deja la solucion en x. Devuelve false, sin imprimir nada, si la matriz es singular.
// Se usa en las busquedas con muchos puntos de partida, donde un Jacobiano singular es normal y no debe llenar la pantalla de errores.
bool lineal_silencioso(double **A, double *b, int n, double *x) {
    /*
    Ejemplo de uso:
        double d[4] = {2, 1, 1, 3};
        double **A = mat_from_arr(d, 2, 2);
        double b[2] = {3, 5}, x[2];
        bool ok = lineal_silencioso(A, b, 2, x);     // ok = true, x = (0.8, 1.4)
    */
    double **M = coppy_mat(A, n, n);
    double *r = copy_vect(b, n);
    double esc = 0.0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (fabs(A[i][j]) > esc) esc = fabs(A[i][j]);
    bool ok = (esc > 0.0);
    for (int k = 0; k < n && ok; k++) {
        int p = k;
        for (int i = k + 1; i < n; i++) if (fabs(M[i][k]) > fabs(M[p][k])) p = i;
        if (fabs(M[p][k]) < 1e-13 * esc) { ok = false; break; }
        if (p != k) {
            for (int j = 0; j < n; j++) intercambiar_elem(M[p][j], M[k][j]);
            intercambiar_elem(r[p], r[k]);
        }
        for (int i = k + 1; i < n; i++) {
            double fct = M[i][k] / M[k][k];
            for (int j = k; j < n; j++) M[i][j] -= fct * M[k][j];
            r[i] -= fct * r[k];
        }
    }
    if (ok) {
        for (int i = n - 1; i >= 0; i--) {
            double s = r[i];
            for (int j = i + 1; j < n; j++) s -= M[i][j] * x[j];
            x[i] = s / M[i][i];
        }
    }
    del_mat(M, n);
    delete[] r;
    return ok;
}
#endif // MC_FN_lineal_silencioso

#ifndef MC_FN_newton_raphson_sys_ok
#define MC_FN_newton_raphson_sys_ok
// Newton-Raphson para sistemas SIN mensajes (ayuda para Newton en rango)
// Descripción: Igual que newton_raphson_sys pero mejora x EN SITIO, no imprime nada y devuelve true solo si converge (paso < tol, sin NaN ni divergencia) en max_iter iteraciones.
// El Jacobiano se calcula por diferencias centrales de 5 puntos (jacobian_mat). Falla si el Jacobiano es singular o la iteracion se dispara.
bool newton_raphson_sys_ok(double (*AF[])(double*, int), int n, double *x, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double f1(double *v, int n) { return v[0]*v[0] + v[1]*v[1] - 4; }
        double f2(double *v, int n) { return v[0]*v[1] - 1; }
        double (*Sist[2])(double*, int) = {f1, f2};
        double p[2] = {1.5, 0.5};
        bool ok = newton_raphson_sys_ok(Sist, 2, p, 1e-12, 50);   // ok = true, p = (1.9318517, 0.5176381)
    */
    double *F = new double[n];
    double *dx = new double[n];
    bool conv = false;
    for (int it = 0; it < max_iter; it++) {
        for (int i = 0; i < n; i++) F[i] = -AF[i](x, n);
        double **J = jacobian_mat(AF, x, n);
        bool ok = lineal_silencioso(J, F, n, dx);
        del_mat(J, n);
        if (!ok) break;
        double paso = 0.0;
        for (int i = 0; i < n; i++) { x[i] += dx[i]; paso += dx[i] * dx[i]; }
        paso = sqrt(paso);
        bool malo = isNaN(paso);
        for (int i = 0; i < n; i++) if (isNaN(x[i]) || fabs(x[i]) > 1e100) malo = true;
        if (malo) break;
        if (paso < tol) { conv = true; break; }
    }
    delete[] F; delete[] dx;
    return conv;
}
#endif // MC_FN_newton_raphson_sys_ok

#ifndef MC_FN_newton_raphson_sys_filtrado
#define MC_FN_newton_raphson_sys_filtrado
// Newton-Raphson para sistemas: soluciones distintas a partir de una lista de semillas, solo las que caen en un rango
// Descripción: Lanza Newton desde cada fila de 'semillas' (num_semillas x n) y se queda solo con las soluciones que (1) han convergido, (2) cumplen |F_i| < 100*tol, (3) estan dentro del rango
// a[i] <= x_i <= b[i] y (4) no estan repetidas. Devuelve una matriz num_sol x n ordenada por la primera variable (new; liberar con del_mat(S, num_sol)) y NULL si no hay ninguna.
// Es la version "todas las soluciones" de newton_raphson_multi_sys, que devuelve una fila por semilla (con repetidas y NaN).
double** newton_raphson_sys_filtrado(double (*AF[])(double*, int), int n, double *a, double *b, double **semillas, int num_semillas,
                                     double tol, int max_iter, int &num_sol) {
    /*
    Ejemplo de uso:
        // f1 = x^2 + y^2 - 4, f2 = x*y - 1  (4 soluciones); semillas elegidas a mano
        double a[2] = {0, 0}, b[2] = {3, 3};
        double d[4] = {2, 0.5,  0.5, 2};
        double **sem = mat_from_arr(d, 2, 2);
        int ns;
        double **S = newton_raphson_sys_filtrado(Sist, 2, a, b, sem, 2, 1e-12, 50, ns);   // ns = 2
    */
    num_sol = 0;
    int cap = 16;
    double **sol = new double*[cap];
    double *x = new double[n];
    double *F = new double[n];
    for (int s = 0; s < num_semillas; s++) {
        for (int i = 0; i < n; i++) x[i] = semillas[s][i];
        if (!newton_raphson_sys_ok(AF, n, x, tol, max_iter)) continue;
        bool valido = true;
        for (int i = 0; i < n; i++) {                                   // dentro del rango (con un pequeño margen)
            double marg = 1e-8 * (b[i] - a[i]) + 1e-12;
            if (x[i] < a[i] - marg || x[i] > b[i] + marg) valido = false;
        }
        for (int i = 0; i < n && valido; i++) if (fabs(AF[i](x, n)) > 100.0 * tol) valido = false;   // residuo pequeño
        for (int k = 0; k < num_sol && valido; k++) {                   // no repetida
            bool igual = true;
            for (int i = 0; i < n; i++) if (fabs(x[i] - sol[k][i]) > 1e-6 * (1.0 + fabs(sol[k][i]))) igual = false;
            if (igual) valido = false;
        }
        if (!valido) continue;
        if (num_sol >= cap) {
            int ncap = 2 * cap;
            double **t = new double*[ncap];
            for (int k = 0; k < num_sol; k++) t[k] = sol[k];
            delete[] sol; sol = t; cap = ncap;
        }
        sol[num_sol] = copy_vect(x, n);
        num_sol++;
    }
    delete[] x; delete[] F;
    for (int i = 1; i < num_sol; i++) {                                 // ordenar por x_1, x_2, ...
        double *clave = sol[i];
        int k = i - 1;
        while (k >= 0) {
            bool mayor = false;
            for (int c = 0; c < n; c++) {
                if (sol[k][c] > clave[c]) { mayor = true; break; }
                if (sol[k][c] < clave[c]) break;
            }
            if (!mayor) break;
            sol[k + 1] = sol[k];
            k--;
        }
        sol[k + 1] = clave;
    }
    if (num_sol == 0) {
        print_warning("newton_raphson_sys_filtrado: no se encontro ninguna solucion en el rango (prueba mas semillas o un rango mayor).");
        delete[] sol;
        return NULL;
    }
    return sol;
}
#endif // MC_FN_newton_raphson_sys_filtrado

#ifndef MC_FN_newton_raphson_sys_rango
#define MC_FN_newton_raphson_sys_rango
// Newton-Raphson para sistemas: TODAS las soluciones en un rango (malla de semillas)
// Descripción: Resuelve F(r) = 0 con r = (x_1, ..., x_n) y devuelve todas las soluciones distintas con a[i] <= x_i <= b[i]. Lanza Newton desde una malla de 'divisiones' puntos por variable (divisiones^n semillas, extremos incluidos).
// Devuelve una matriz num_sol x n ordenada por la primera variable (liberar con del_mat(S, num_sol)); NULL si no hay ninguna. Condiciones: F derivable; encuentra todas las soluciones cuya cuenca de atraccion contenga alguna semilla,
// asi que usa mas 'divisiones' si sospechas que faltan (el coste crece como divisiones^n: para n >= 3 mejor newton_raphson_sys_rango_aleat).
double** newton_raphson_sys_rango(double (*AF[])(double*, int), int n, double *a, double *b, int divisiones, double tol, int max_iter, int &num_sol) {
    /*
    Ejemplo de uso:
        double f1(double *v, int n) { return v[0]*v[0] + v[1]*v[1] - 4; }     // circunferencia
        double f2(double *v, int n) { return v[0]*v[1] - 1; }                  // hiperbola
        double (*Sist[2])(double*, int) = {f1, f2};
        double a[2] = {-3, -3}, b[2] = {3, 3};      // rango: x en (-3,3), y en (-3,3)
        int ns;
        double **S = newton_raphson_sys_rango(Sist, 2, a, b, 12, 1e-12, 50, ns);   // 4 soluciones
        print_mat(S, ns, 2, "Soluciones (x, y)");
    */
    num_sol = 0;
    if (n < 1 || divisiones < 1) { print_error("newton_raphson_sys_rango: n >= 1 y divisiones >= 1"); return NULL; }
    double total = pow((double)divisiones, (double)n);
    if (total > 5e6) { print_error("newton_raphson_sys_rango: demasiadas semillas (divisiones^n > 5e6); usa newton_raphson_sys_rango_aleat"); return NULL; }
    int ns = (int)(total + 0.5);
    double **sem = zeros_mat(ns, n);
    int *idx = new int[n];
    for (int i = 0; i < n; i++) idx[i] = 0;
    for (int s = 0; s < ns; s++) {
        for (int i = 0; i < n; i++)
            sem[s][i] = (divisiones == 1) ? 0.5 * (a[i] + b[i]) : a[i] + (b[i] - a[i]) * idx[i] / (divisiones - 1);
        for (int i = n - 1; i >= 0; i--) {                     // contador en base 'divisiones'
            idx[i]++;
            if (idx[i] < divisiones) break;
            idx[i] = 0;
        }
    }
    delete[] idx;
    double **S = newton_raphson_sys_filtrado(AF, n, a, b, sem, ns, tol, max_iter, num_sol);
    del_mat(sem, ns);
    return S;
}
#endif // MC_FN_newton_raphson_sys_rango

#ifndef MC_FN_newton_raphson_sys_rango_aleat
#define MC_FN_newton_raphson_sys_rango_aleat
// Newton-Raphson para sistemas: TODAS las soluciones en un rango (semillas aleatorias)
// Descripción: Igual que newton_raphson_sys_rango, pero lanza Newton desde 'num_semillas' puntos aleatorios uniformes dentro del rango (en vez de una malla). Es la opcion para 3 o mas variables,
// donde una malla tendria demasiados puntos. Usa rand(): llama antes a srand(semilla) si quieres otra secuencia. Devuelve num_sol x n ordenada por la primera variable (liberar con del_mat) o NULL.
double** newton_raphson_sys_rango_aleat(double (*AF[])(double*, int), int n, double *a, double *b, int num_semillas, double tol, int max_iter, int &num_sol) {
    /*
    Ejemplo de uso:
        // mismo sistema que newton_raphson_sys_rango, ahora con 200 semillas aleatorias
        double a[2] = {0, 0}, b[2] = {3, 3};         // solo el primer cuadrante: 2 soluciones
        int ns;
        double **S = newton_raphson_sys_rango_aleat(Sist, 2, a, b, 200, 1e-12, 50, ns);   // ns = 2
    */
    num_sol = 0;
    if (n < 1 || num_semillas < 1) { print_error("newton_raphson_sys_rango_aleat: n >= 1 y num_semillas >= 1"); return NULL; }
    double **sem = zeros_mat(num_semillas, n);
    for (int s = 0; s < num_semillas; s++)
        for (int i = 0; i < n; i++)
            sem[s][i] = a[i] + (b[i] - a[i]) * (rand() / (double)RAND_MAX);
    double **S = newton_raphson_sys_filtrado(AF, n, a, b, sem, num_semillas, tol, max_iter, num_sol);
    del_mat(sem, num_semillas);
    return S;
}
#endif // MC_FN_newton_raphson_sys_rango_aleat

#endif // MATCLUB_SISTEMAS_NO_LINEALES_CPP
