// ============================================================================
// MATCLUB-CPP  |  BLOQUE IV: INTEGRACION Y DERIVACION  |  IV.2
// Derivacion numerica
// ============================================================================
// Derivadas parciales, gradientes y jacobianos; formulas de 2, 3 y 5 puntos; extrapolacion de Richardson y derivadas de datos tabulados.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "derivacion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (23): part_derv, total_derv, grad_vect, jacobian_mat, deriv_vect, deriv_prog_2p, deriv_reg_2p, deriv_prog_3p, deriv_reg_3p, deriv_cent_3p, deriv_prog_5p, deriv_cent_5p, deriv2_prog_3p, deriv2_cent_3p, deriv2_prog_5p, deriv2_cent_5p, deriv_func, richardson_deriv_mat, deriv_richardson, err_deriv_h_mat, deriv_vect_3p, deriv_vect_5p, deriv2_vect
// Dependencias copiadas (7): MC_NAN, print_error, print_error_int, copy_vect, gen_mat, del_mat, zeros_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_DERIVACION_CPP
#define MATCLUB_DERIVACION_CPP

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
#ifndef MC_FN_print_error_int
#define MC_FN_print_error_int
// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}
#endif // MC_FN_print_error_int

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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Derivacion numerica
// ----------------------------------------------------------------------------

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

#ifndef MC_FN_total_derv
#define MC_FN_total_derv
// Derivada total
// Descripción: Calcula la derivada total dF/dt sumando el producto de las derivadas parciales por dx_i/dt.
double total_derv(double (*f)(double*, int), double *x, double *dx_dt, int n) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[1]; }
        double punto[] = {2.0, 3.0};
        double velocidades[] = {0.5, -0.1}; // dx/dt, dy/dt
        double dF_dt = total_derv(mi_func, punto, velocidades, 2);
    */
    double dTotal = 0.0;
    for (int j = 0; j < n; j++) {
        dTotal += part_derv(f, x, n, j) * dx_dt[j];
    }
    return dTotal;
}
#endif // MC_FN_total_derv

#ifndef MC_FN_grad_vect
#define MC_FN_grad_vect
// Gradiente
// Descripción: Devuelve un vector con todas las derivadas parciales de una función escalar.
double* grad_vect(double (*f)(double*, int), double *x, int n) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0] + v[1]*v[1]; }
        double punto[] = {1.0, 2.0};
        double *grad = grad_vect(mi_func, punto, 2);
        print_vect(grad, 2, "Gradiente");
        delete[] grad;
    */
    double *g = new double[n];
    for (int j = 0; j < n; j++) {
        g[j] = part_derv(f, x, n, j);
    }
    return g;
}
#endif // MC_FN_grad_vect

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

#ifndef MC_FN_deriv_vect
#define MC_FN_deriv_vect
// Derivada Numérica de datos discretos (Vectorial)
// Descripción: Calcula dy/dx usando diferencias finitas. Diferencias centrales en el interior y progresivas/regresivas en los bordes.
double* deriv_vect(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *dy_dx = deriv_vect(x, y, n);
        print_vect(dy_dx, n, "Derivada");
    */
    if (n < 2) return NULL;
    
    double *dydx = new double[n];
    
    // Borde izquierdo (diferencia progresiva)
    dydx[0] = (y[1] - y[0]) / (x[1] - x[0]);
    
    // Borde derecho (diferencia regresiva)
    dydx[n - 1] = (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]);
    
    // Puntos interiores (diferencia central)
    for (int i = 1; i < n - 1; i++) {
        dydx[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1]);
    }
    
    return dydx;
}
#endif // MC_FN_deriv_vect

#ifndef MC_FN_deriv_prog_2p
#define MC_FN_deriv_prog_2p
// Derivada primera, diferencias progresivas de 2 puntos
// Descripción: f'(x) ~ (f(x+h) - f(x))/h. Error O(h).
double deriv_prog_2p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double d = deriv_prog_2p(exp, 0.0, 1e-4);   // ~1
    */
    return (f(x + h) - f(x)) / h;
}
#endif // MC_FN_deriv_prog_2p

#ifndef MC_FN_deriv_reg_2p
#define MC_FN_deriv_reg_2p
// Derivada primera, diferencias regresivas de 2 puntos
// Descripción: f'(x) ~ (f(x) - f(x-h))/h. Error O(h).
double deriv_reg_2p(double (*f)(double), double x, double h) {
    return (f(x) - f(x - h)) / h;
}
#endif // MC_FN_deriv_reg_2p

#ifndef MC_FN_deriv_prog_3p
#define MC_FN_deriv_prog_3p
// Derivada primera, diferencias progresivas de 3 puntos
// Descripción: f'(x) ~ (-3f(x) + 4f(x+h) - f(x+2h))/(2h). Error O(h^2).
double deriv_prog_3p(double (*f)(double), double x, double h) {
    return (-3.0 * f(x) + 4.0 * f(x + h) - f(x + 2.0 * h)) / (2.0 * h);
}
#endif // MC_FN_deriv_prog_3p

#ifndef MC_FN_deriv_reg_3p
#define MC_FN_deriv_reg_3p
// Derivada primera, diferencias regresivas de 3 puntos
// Descripción: f'(x) ~ (3f(x) - 4f(x-h) + f(x-2h))/(2h). Error O(h^2).
double deriv_reg_3p(double (*f)(double), double x, double h) {
    return deriv_prog_3p(f, x, -h);
}
#endif // MC_FN_deriv_reg_3p

#ifndef MC_FN_deriv_cent_3p
#define MC_FN_deriv_cent_3p
// Derivada primera, diferencias centrales de 3 puntos
// Descripción: f'(x) ~ (f(x+h) - f(x-h))/(2h). Error O(h^2) (la mejor relacion precision/coste).
double deriv_cent_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double d = deriv_cent_3p(exp, 0.0, 1e-3);   // ~1
    */
    return (f(x + h) - f(x - h)) / (2.0 * h);
}
#endif // MC_FN_deriv_cent_3p

#ifndef MC_FN_deriv_prog_5p
#define MC_FN_deriv_prog_5p
// Derivada primera, diferencias progresivas de 5 puntos
// Descripción: f'(x) ~ (-25f(x) + 48f(x+h) - 36f(x+2h) + 16f(x+3h) - 3f(x+4h))/(12h). Error O(h^4).
double deriv_prog_5p(double (*f)(double), double x, double h) {
    return (-25.0 * f(x) + 48.0 * f(x + h) - 36.0 * f(x + 2.0 * h) + 16.0 * f(x + 3.0 * h) - 3.0 * f(x + 4.0 * h)) / (12.0 * h);
}
#endif // MC_FN_deriv_prog_5p

#ifndef MC_FN_deriv_cent_5p
#define MC_FN_deriv_cent_5p
// Derivada primera, diferencias centrales de 5 puntos
// Descripción: f'(x) ~ (f(x-2h) - 8f(x-h) + 8f(x+h) - f(x+2h))/(12h). Error O(h^4).
double deriv_cent_5p(double (*f)(double), double x, double h) {
    return (f(x - 2.0 * h) - 8.0 * f(x - h) + 8.0 * f(x + h) - f(x + 2.0 * h)) / (12.0 * h);
}
#endif // MC_FN_deriv_cent_5p

#ifndef MC_FN_deriv2_prog_3p
#define MC_FN_deriv2_prog_3p
// Derivada segunda, diferencias progresivas de 3 puntos
// Descripción: f''(x) ~ (f(x) - 2f(x+h) + f(x+2h))/h^2. Error O(h).
double deriv2_prog_3p(double (*f)(double), double x, double h) {
    return (f(x) - 2.0 * f(x + h) + f(x + 2.0 * h)) / (h * h);
}
#endif // MC_FN_deriv2_prog_3p

#ifndef MC_FN_deriv2_cent_3p
#define MC_FN_deriv2_cent_3p
// Derivada segunda, diferencias centrales de 3 puntos
// Descripción: f''(x) ~ (f(x-h) - 2f(x) + f(x+h))/h^2. Error O(h^2).
double deriv2_cent_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double d2 = deriv2_cent_3p(exp, 0.0, 1e-3);   // ~1
    */
    return (f(x - h) - 2.0 * f(x) + f(x + h)) / (h * h);
}
#endif // MC_FN_deriv2_cent_3p

#ifndef MC_FN_deriv2_prog_5p
#define MC_FN_deriv2_prog_5p
// Derivada segunda, diferencias progresivas de 5 puntos
// Descripción: f''(x) ~ (35f(x) - 104f(x+h) + 114f(x+2h) - 56f(x+3h) + 11f(x+4h))/(12h^2). Error O(h^3).
double deriv2_prog_5p(double (*f)(double), double x, double h) {
    return (35.0 * f(x) - 104.0 * f(x + h) + 114.0 * f(x + 2.0 * h) - 56.0 * f(x + 3.0 * h) + 11.0 * f(x + 4.0 * h)) / (12.0 * h * h);
}
#endif // MC_FN_deriv2_prog_5p

#ifndef MC_FN_deriv2_cent_5p
#define MC_FN_deriv2_cent_5p
// Derivada segunda, diferencias centrales de 5 puntos
// Descripción: f''(x) ~ (-f(x-2h) + 16f(x-h) - 30f(x) + 16f(x+h) - f(x+2h))/(12h^2). Error O(h^4).
double deriv2_cent_5p(double (*f)(double), double x, double h) {
    return (-f(x - 2.0 * h) + 16.0 * f(x - h) - 30.0 * f(x) + 16.0 * f(x + h) - f(x + 2.0 * h)) / (12.0 * h * h);
}
#endif // MC_FN_deriv2_cent_5p

#ifndef MC_FN_deriv_func
#define MC_FN_deriv_func
// Derivada numérica con selección de fórmula
// Descripción: orden = 1 o 2 (derivada primera o segunda); puntos = 2, 3 o 5; tipo = 'p' (progresiva), 'r' (regresiva) o 'c' (central).
// Combinaciones validas: orden 1: p/r con 2, 3 o 5 puntos y c con 3 o 5; orden 2: p/r con 3 o 5 puntos y c con 3 o 5.
double deriv_func(double (*f)(double), double x, double h, int orden, int puntos, char tipo) {
    /*
    Ejemplo de uso:
        double d = deriv_func(exp, 0.0, 0.01, 1, 5, 'c');   // f'(0) con diferencias centrales de 5 puntos
    */
    double s = (tipo == 'r') ? -1.0 : 1.0;        // regresiva = progresiva con h cambiada de signo
    if (orden == 1) {
        if (tipo == 'c' && puntos == 3) return deriv_cent_3p(f, x, h);
        if (tipo == 'c' && puntos == 5) return deriv_cent_5p(f, x, h);
        if (tipo != 'c' && puntos == 2) return deriv_prog_2p(f, x, s * h);
        if (tipo != 'c' && puntos == 3) return deriv_prog_3p(f, x, s * h);
        if (tipo != 'c' && puntos == 5) return deriv_prog_5p(f, x, s * h);
    } else if (orden == 2) {
        if (tipo == 'c' && puntos == 3) return deriv2_cent_3p(f, x, h);
        if (tipo == 'c' && puntos == 5) return deriv2_cent_5p(f, x, h);
        if (tipo != 'c' && puntos == 3) return deriv2_prog_3p(f, x, s * h);
        if (tipo != 'c' && puntos == 5) return deriv2_prog_5p(f, x, s * h);
    }
    print_error("deriv_func: combinacion de orden/puntos/tipo no disponible");
    return MC_NAN;
}
#endif // MC_FN_deriv_func

#ifndef MC_FN_richardson_deriv_mat
#define MC_FN_richardson_deriv_mat
// Tabla de extrapolación de Richardson para derivadas
// Descripción: T[i][0] = diferencia central de 3 puntos con h_i = h0/2^i y T[i][j] = (4^j*T[i][j-1] - T[i-1][j-1])/(4^j - 1) (error O(h^(2j+2))).
// orden = 1 o 2 (derivada primera o segunda). Devuelve la matriz N x N (triangular inferior). Liberar con del_mat(T, N).
double** richardson_deriv_mat(double (*f)(double), double x0, double h0, int N, int orden) {
    /*
    Ejemplo de uso:
        double g(double x) { return x * x * cos(x); }
        double **T = richardson_deriv_mat(g, 1.0, 0.1, 4, 1);
        print_mat(T, 4, 4, "Richardson");   // T[3][3] = 0.239132 (exacto: 0.2391336)
    */
    if (N < 1 || (orden != 1 && orden != 2)) { print_error("richardson_deriv_mat: N >= 1 y orden = 1 o 2"); return NULL; }
    double **T = zeros_mat(N, N);
    double h = h0;
    for (int i = 0; i < N; i++) {
        T[i][0] = (orden == 1) ? deriv_cent_3p(f, x0, h) : deriv2_cent_3p(f, x0, h);
        double p4 = 1.0;
        for (int j = 1; j <= i; j++) {
            p4 *= 4.0;
            T[i][j] = (p4 * T[i][j - 1] - T[i - 1][j - 1]) / (p4 - 1.0);
        }
        h /= 2.0;
    }
    return T;
}
#endif // MC_FN_richardson_deriv_mat

#ifndef MC_FN_deriv_richardson
#define MC_FN_deriv_richardson
// Derivada por extrapolación de Richardson
// Descripción: Devuelve la mejor estimacion (ultimo elemento de la tabla) con N niveles, partiendo de un paso h0 que se divide por 2 en cada nivel.
double deriv_richardson(double (*f)(double), double x0, double h0, int N, int orden) {
    /*
    Ejemplo de uso:
        double d = deriv_richardson(g, 1.0, 0.1, 4, 1);   // 0.239132
    */
    double **T = richardson_deriv_mat(f, x0, h0, N, orden);
    if (T == NULL) return MC_NAN;
    double r = T[N - 1][N - 1];
    del_mat(T, N);
    return r;
}
#endif // MC_FN_deriv_richardson

#ifndef MC_FN_err_deriv_h_mat
#define MC_FN_err_deriv_h_mat
// Estudio del error de la derivada en función de h (truncamiento frente a redondeo)
// Descripción: Devuelve una matriz n x 3 con [h, derivada central de 3 puntos, |error|] para h = h0, h0/10, h0/100, ... Muestra que reducir h indefinidamente
// empeora el resultado por el error de redondeo. 'exacta' es el valor exacto de f'(x0).
double** err_deriv_h_mat(double (*f)(double), double x0, double exacta, double h0, int n) {
    /*
    Ejemplo de uso:
        double **E = err_deriv_h_mat(exp, 0.0, 1.0, 0.1, 11);   // h de 0.1 a 1e-10
        print_mat(E, 11, 3, "[h, D, error]");
    */
    double **E = zeros_mat(n, 3);
    double h = h0;
    for (int i = 0; i < n; i++) {
        double d = deriv_cent_3p(f, x0, h);
        E[i][0] = h; E[i][1] = d; E[i][2] = fabs(d - exacta);
        h /= 10.0;
    }
    return E;
}
#endif // MC_FN_err_deriv_h_mat

#ifndef MC_FN_deriv_vect_3p
#define MC_FN_deriv_vect_3p
// Derivada primera de datos equiespaciados con error O(h^2) en todos los puntos
// Descripción: Diferencias centrales en el interior y progresiva/regresiva de 3 puntos en los extremos (n >= 3). Mejora a deriv_vect, que usa 2 puntos en los bordes.
double* deriv_vect_3p(double *y, int n, double h) {
    /*
    Ejemplo de uso:
        double *dy = deriv_vect_3p(y, n, 0.1);
    */
    if (n < 3) { print_error_int("deriv_vect_3p: se necesitan al menos 3 puntos", n); return NULL; }
    double *d = new double[n];
    d[0] = (-3.0 * y[0] + 4.0 * y[1] - y[2]) / (2.0 * h);
    d[n - 1] = (3.0 * y[n - 1] - 4.0 * y[n - 2] + y[n - 3]) / (2.0 * h);
    for (int i = 1; i < n - 1; i++) d[i] = (y[i + 1] - y[i - 1]) / (2.0 * h);
    return d;
}
#endif // MC_FN_deriv_vect_3p

#ifndef MC_FN_deriv_vect_5p
#define MC_FN_deriv_vect_5p
// Derivada primera de datos equiespaciados con error O(h^4) en el interior
// Descripción: Centrales de 5 puntos en i = 2..n-3, progresiva/regresiva de 5 puntos en los extremos y centrales de 3 puntos en i = 1 y n-2 (n >= 5).
double* deriv_vect_5p(double *y, int n, double h) {
    /*
    Ejemplo de uso:
        double *dy = deriv_vect_5p(y, n, 0.1);
    */
    if (n < 5) { print_error_int("deriv_vect_5p: se necesitan al menos 5 puntos", n); return NULL; }
    double *d = new double[n];
    d[0] = (-25.0 * y[0] + 48.0 * y[1] - 36.0 * y[2] + 16.0 * y[3] - 3.0 * y[4]) / (12.0 * h);
    d[n - 1] = (25.0 * y[n - 1] - 48.0 * y[n - 2] + 36.0 * y[n - 3] - 16.0 * y[n - 4] + 3.0 * y[n - 5]) / (12.0 * h);
    d[1] = (y[2] - y[0]) / (2.0 * h);
    d[n - 2] = (y[n - 1] - y[n - 3]) / (2.0 * h);
    for (int i = 2; i < n - 2; i++) d[i] = (y[i - 2] - 8.0 * y[i - 1] + 8.0 * y[i + 1] - y[i + 2]) / (12.0 * h);
    return d;
}
#endif // MC_FN_deriv_vect_5p

#ifndef MC_FN_deriv2_vect
#define MC_FN_deriv2_vect
// Derivada segunda de datos equiespaciados
// Descripción: Diferencias centrales de 3 puntos en el interior (O(h^2)) y progresiva/regresiva de 3 puntos en los extremos (O(h)). n >= 3.
double* deriv2_vect(double *y, int n, double h) {
    /*
    Ejemplo de uso:
        double *d2y = deriv2_vect(y, n, 0.1);
    */
    if (n < 3) { print_error_int("deriv2_vect: se necesitan al menos 3 puntos", n); return NULL; }
    double *d = new double[n];
    d[0] = (y[0] - 2.0 * y[1] + y[2]) / (h * h);
    d[n - 1] = (y[n - 1] - 2.0 * y[n - 2] + y[n - 3]) / (h * h);
    for (int i = 1; i < n - 1; i++) d[i] = (y[i - 1] - 2.0 * y[i] + y[i + 1]) / (h * h);
    return d;
}
#endif // MC_FN_deriv2_vect

#endif // MATCLUB_DERIVACION_CPP
