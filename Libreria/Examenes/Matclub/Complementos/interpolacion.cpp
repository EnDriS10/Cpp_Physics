// ============================================================================
// MATCLUB-CPP  |  COMPLEMENTOS (fuera de los 5 bloques)
// Interpolacion numerica
// ============================================================================
// Splines, Newton (diferencias divididas y progresivas), Lagrange, Vandermonde y estimacion del error de interpolacion.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "interpolacion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (15): spline_coef, spline_eval, spline_interp, newton_coef, newton_eval, lagrange_coef, lagrange_val, vandermonde_mat, poly_interp_coef, dif_divididas_mat, newton_error_sig, interp_error_cota, dif_progresivas_mat, newton_prog_eval, newton_prog_error_sig
// Dependencias copiadas (10): MC_NAN, print_error, intercambiar_elem, factorial, copy_vect, gen_mat, del_mat, coppy_mat, zeros_mat, gauss_solve
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_INTERPOLACION_CPP
#define MATCLUB_INTERPOLACION_CPP

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
#ifndef MC_FN_factorial
#define MC_FN_factorial
// Factorial (devuelve double para llegar hasta 170!)
double factorial(int n) {
    if (n < 0) {
        print_error("factorial no definido para n negativo");
        return MC_NAN;
    }
    double f = 1.0;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}
#endif // MC_FN_factorial

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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Interpolacion numerica
// ----------------------------------------------------------------------------

#ifndef MC_FN_spline_coef
#define MC_FN_spline_coef
// 7. ---------------- SPLINE CUBICA NATURAL ----------------
// Devuelve las segundas derivadas M[0..n-1] (M[0]=M[n-1]=0). Liberar con del_vect.
double* spline_coef(double *x, double *y, int n) {
    if (n < 3) { print_error("spline_coef: se necesitan al menos 3 puntos"); return NULL; }
    double *M = new double[n];
    int m = n - 2;
    double *a = new double[m], *b = new double[m], *c = new double[m], *d = new double[m];
    for (int i = 1; i <= m; i++) {
        double h0 = x[i] - x[i - 1], h1 = x[i + 1] - x[i];
        a[i - 1] = h0;
        b[i - 1] = 2.0 * (h0 + h1);
        c[i - 1] = h1;
        d[i - 1] = 6.0 * ((y[i + 1] - y[i]) / h1 - (y[i] - y[i - 1]) / h0);
    }
    for (int i = 1; i < m; i++) {          // eliminacion (Thomas)
        double w = a[i] / b[i - 1];
        b[i] -= w * c[i - 1];
        d[i] -= w * d[i - 1];
    }
    M[0] = 0.0; M[n - 1] = 0.0;
    M[m] = d[m - 1] / b[m - 1];
    for (int i = m - 2; i >= 0; i--) M[i + 1] = (d[i] - c[i] * M[i + 2]) / b[i];
    delete[] a; delete[] b; delete[] c; delete[] d;
    return M;
}
#endif // MC_FN_spline_coef

#ifndef MC_FN_spline_eval
#define MC_FN_spline_eval
// x debe estar ordenado de menor a mayor. Fuera de [x0, xn-1] extrapola con el tramo extremo.
double spline_eval(double *x, double *y, double *M, int n, double xi) {
    int k = 0;
    while (k < n - 2 && xi > x[k + 1]) k++;
    double h = x[k + 1] - x[k];
    double A = (x[k + 1] - xi) / h, B = (xi - x[k]) / h;
    return A * y[k] + B * y[k + 1] + ((A*A*A - A) * M[k] + (B*B*B - B) * M[k + 1]) * h * h / 6.0;
}
#endif // MC_FN_spline_eval

#ifndef MC_FN_spline_interp
#define MC_FN_spline_interp
double spline_interp(double *x, double *y, int n, double xi) {
    double *M = spline_coef(x, y, n);
    if (M == NULL) return MC_NAN;
    double r = spline_eval(x, y, M, n, xi);
    delete[] M;
    return r;
}
#endif // MC_FN_spline_interp

#ifndef MC_FN_newton_coef
#define MC_FN_newton_coef
// 8. ---------------- NEWTON (diferencias divididas) ----------------
// Devuelve c[0..n-1] = f[x0], f[x0,x1], ... Liberar con del_vect.
double* newton_coef(double *x, double *y, int n) {
    if (n < 1) { print_error("newton_coef: n debe ser >= 1"); return NULL; }
    double *c = copy_vect(y, n);
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            double den = x[i] - x[i - j];
            if (den == 0.0) { print_error("newton_coef: hay nodos x repetidos"); delete[] c; return NULL; }
            c[i] = (c[i] - c[i - 1]) / den;
        }
    }
    return c;
}
#endif // MC_FN_newton_coef

#ifndef MC_FN_newton_eval
#define MC_FN_newton_eval
// Evalua el polinomio de Newton en xi (forma anidada tipo Horner)
double newton_eval(double *x, double *c, int n, double xi) {
    double r = c[n - 1];
    for (int i = n - 2; i >= 0; i--) r = r * (xi - x[i]) + c[i];
    return r;
}
#endif // MC_FN_newton_eval

#ifndef MC_FN_lagrange_coef
#define MC_FN_lagrange_coef
// 9. ---------------- LAGRANGE (forma baricentrica) ----------------
// Devuelve los pesos w[i] = 1 / prod_{j!=i} (x[i]-x[j]). Liberar con del_vect.
double* lagrange_coef(double *x, int n) {
    if (n < 1) { print_error("lagrange_coef: n debe ser >= 1"); return NULL; }
    double *w = new double[n];
    for (int i = 0; i < n; i++) {
        double p = 1.0;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            double den = x[i] - x[j];
            if (den == 0.0) { print_error("lagrange_coef: hay nodos x repetidos"); delete[] w; return NULL; }
            p *= den;
        }
        w[i] = 1.0 / p;
    }
    return w;
}
#endif // MC_FN_lagrange_coef

#ifndef MC_FN_lagrange_val
#define MC_FN_lagrange_val
// Evalua el polinomio de Lagrange en xi con los pesos w (O(n) por punto)
double lagrange_val(double *x, double *y, double *w, int n, double xi) {
    double num = 0.0, den = 0.0;
    for (int i = 0; i < n; i++) {
        double d = xi - x[i];
        if (d == 0.0) return y[i];          // xi coincide con un nodo
        double t = w[i] / d;
        num += t * y[i];
        den += t;
    }
    return num / den;
}
#endif // MC_FN_lagrange_val

#ifndef MC_FN_vandermonde_mat
#define MC_FN_vandermonde_mat
// 10. ---------------- POLINOMIO DE INTERPOLACION POR EL SISTEMA DE VANDERMONDE ----------------

// Matriz de Vandermonde
// Descripción: Devuelve la matriz V (n x n) con V[i][j] = x[i]^j (potencias crecientes). Resolver V*a = y da los coeficientes del polinomio interpolador.
double** vandermonde_mat(double *x, int n) {
    /*
    Ejemplo de uso:
        double x[] = {1, 2, 3};
        double **V = vandermonde_mat(x, 3); // [1 1 1; 1 2 4; 1 3 9]
    */
    double **V = zeros_mat(n, n);
    for (int i = 0; i < n; i++) {
        double p = 1.0;
        for (int j = 0; j < n; j++) { V[i][j] = p; p *= x[i]; }
    }
    return V;
}
#endif // MC_FN_vandermonde_mat

#ifndef MC_FN_poly_interp_coef
#define MC_FN_poly_interp_coef
// Coeficientes del polinomio interpolador (resolviendo el sistema de Vandermonde)
// Descripción: Devuelve los n coeficientes del unico polinomio de grado n-1 que pasa por los n puntos, con potencias DECRECIENTES (listo para 'polyval').
// Es el metodo mas directo pero esta mal condicionado si n es grande; para evaluar conviene newton_eval o lagrange_val.
double* poly_interp_coef(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {0, 1, 2}, y[] = {1, 2, 5};        // y = x^2 + 1
        double *p = poly_interp_coef(x, y, 3);           // p = {1, 0, 1}
        double v = polyval(p, 3, 1.5);                   // 3.25
    */
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (x[i] == x[j]) { print_error("poly_interp_coef: hay nodos x repetidos"); return NULL; }
    double **V = vandermonde_mat(x, n);
    double *a = gauss_solve(V, y, n);              // a[0] = termino independiente
    del_mat(V, n);
    if (a == NULL) return NULL;
    double *p = new double[n];
    for (int i = 0; i < n; i++) p[i] = a[n - 1 - i];
    delete[] a;
    return p;
}
#endif // MC_FN_poly_interp_coef

#ifndef MC_FN_dif_divididas_mat
#define MC_FN_dif_divididas_mat
// 11. ---------------- TABLA DE DIFERENCIAS DIVIDIDAS (NEWTON) ----------------

// Tabla completa de diferencias divididas
// Descripción: T[i][j] = f[x_i, ..., x_{i+j}] (la columna j=0 es y). Los coeficientes del polinomio de Newton son la primera fila T[0][j].
// Los elementos por debajo de la diagonal secundaria valen 0. Liberar con del_mat(T, n).
double** dif_divididas_mat(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {3.2, 2.7, 1.0, 4.8, 5.6}, y[] = {22.0, 17.8, 14.2, 38.3, 51.7};
        double **T = dif_divididas_mat(x, y, 5);
        print_mat(T, 5, 5, "Dif. divididas");   // T[0][1] = 8.4, T[0][2] = -2.856, ...
    */
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (x[i] == x[j]) { print_error("dif_divididas_mat: hay nodos x repetidos"); return NULL; }
    double **T = zeros_mat(n, n);
    for (int i = 0; i < n; i++) T[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            T[i][j] = (T[i + 1][j - 1] - T[i][j - 1]) / (x[i + j] - x[i]);
    return T;
}
#endif // MC_FN_dif_divididas_mat

#ifndef MC_FN_newton_error_sig
#define MC_FN_newton_error_sig
// 12. ---------------- ERROR DE INTERPOLACION ----------------

// Error de interpolación de Newton: regla del término siguiente
// Descripción: Estima E(xi) ~ f[x0,...,xn] * prod(xi - x_i) usando el siguiente termino que se sumaria al polinomio.
// El polinomio usa 'n' puntos (x[0..n-1]) y 'c' son los coeficientes de Newton calculados con UN punto mas (c[0..n], es decir n+1 coeficientes).
double newton_error_sig(double *x, double *c, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[] = {3.2, 2.7, 1.0, 4.8, 5.6}, y[] = {22.0, 17.8, 14.2, 38.3, 51.7};
        double *c = newton_coef(x, y, 5);                  // 5 coeficientes (4 puntos + 1 extra)
        double E = newton_error_sig(x, c, 4, 3.0);         // error del polinomio de grado 3 en xi = 3.0
    */
    double prod = c[n];
    for (int i = 0; i < n; i++) prod *= (xi - x[i]);
    return prod;
}
#endif // MC_FN_newton_error_sig

#ifndef MC_FN_interp_error_cota
#define MC_FN_interp_error_cota
// Cota del error de interpolación (Lagrange o Newton)
// Descripción: |E(xi)| <= M/n! * prod|xi - x_i|, donde n es el numero de puntos del polinomio y M una cota de |f^(n)| en el intervalo.
double interp_error_cota(double *x, int n, double xi, double M_deriv) {
    /*
    Ejemplo de uso:
        // Polinomio de 4 puntos para f(x) = e^x en [0,1], con |f''''| <= e
        double cota = interp_error_cota(x, 4, 0.5, exp(1.0));
    */
    double prod = 1.0;
    for (int i = 0; i < n; i++) prod *= fabs(xi - x[i]);
    return M_deriv * prod / factorial(n);
}
#endif // MC_FN_interp_error_cota

#ifndef MC_FN_dif_progresivas_mat
#define MC_FN_dif_progresivas_mat
// 13. ---------------- PUNTOS EQUIESPACIADOS: DIFERENCIAS PROGRESIVAS ----------------

// Tabla de diferencias progresivas
// Descripción: D[i][k] = (Delta^k f)(x_i) para datos equiespaciados. La columna k=0 es y. Liberar con del_mat(D, n).
// Relacion con las diferencias divididas: f[x0,...,xk] = Delta^k f0 / (k! * h^k).
double** dif_progresivas_mat(double *y, int n) {
    /*
    Ejemplo de uso:
        double y[] = {0.000, 0.203, 0.423, 0.684, 1.030, 1.557, 2.572};  // tan(x), x = 0, 0.2, ..., 1.2
        double **D = dif_progresivas_mat(y, 7);
        print_mat(D, 7, 7, "Dif. progresivas");
    */
    double **D = zeros_mat(n, n);
    for (int i = 0; i < n; i++) D[i][0] = y[i];
    for (int k = 1; k < n; k++)
        for (int i = 0; i < n - k; i++)
            D[i][k] = D[i + 1][k - 1] - D[i][k - 1];
    return D;
}
#endif // MC_FN_dif_progresivas_mat

#ifndef MC_FN_newton_prog_eval
#define MC_FN_newton_prog_eval
// Polinomio de interpolación de Newton con diferencias progresivas
// Descripción: Evalua P(xi) = sum_k C(s,k) * Delta^k f0 con s = (xi - x0)/h, usando 'n' diferencias dif0[0..n-1] = Delta^k f(x0).
// Para centrar el polinomio, tomar como x0 el nodo adecuado y como dif0 la fila correspondiente de dif_progresivas_mat (D[i0]).
double newton_prog_eval(double x0, double h, double *dif0, int n, double xi) {
    /*
    Ejemplo de uso:
        // f(0.73) con un polinomio de grado 3 empezando en x0 = 0.4 (fila 2 de la tabla)
        double v = newton_prog_eval(0.4, 0.2, D[2], 4, 0.73);   // ~0.893
    */
    double s = (xi - x0) / h;
    double termino = 1.0, suma = 0.0;
    for (int k = 0; k < n; k++) {
        suma += termino * dif0[k];
        termino *= (s - k) / (k + 1.0);     // C(s,k+1) = C(s,k) * (s-k)/(k+1)
    }
    return suma;
}
#endif // MC_FN_newton_prog_eval

#ifndef MC_FN_newton_prog_error_sig
#define MC_FN_newton_prog_error_sig
// Error de Newton progresivo: regla del término siguiente
// Descripción: E ~ C(s,n) * Delta^n f0, donde el polinomio usa 'n' puntos y dif0[n] es la primera diferencia NO usada en el polinomio.
double newton_prog_error_sig(double x0, double h, double *dif0, int n, double xi) {
    /*
    Ejemplo de uso:
        double E = newton_prog_error_sig(0.4, 0.2, D[2], 4, 0.73);   // ~0.004
    */
    double s = (xi - x0) / h;
    double termino = 1.0;
    for (int k = 0; k < n; k++) termino *= (s - k) / (k + 1.0);
    return termino * dif0[n];
}
#endif // MC_FN_newton_prog_error_sig

#endif // MATCLUB_INTERPOLACION_CPP
