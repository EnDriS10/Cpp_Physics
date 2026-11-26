// ============================================================================
// MATCLUB-CPP  |  BLOQUE IV: INTEGRACION Y DERIVACION  |  IV.2
// Derivacion numerica
// ============================================================================
// Derivadas parciales centrales de alta precision (3 a 9 puntos), gradiente, divergencia, rotacional, laplaciano y jacobiano; formulas de 2, 3 y 5 puntos; Richardson (con paso fijo o por tolerancia); derivadas de datos tabulados x-y con espaciado no uniforme y precision elegible (puntos o tolerancia).
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "derivacion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (38): pesos_deriv_lagrange, part_derv_c, part2_derv_c, part_derv, total_derv, grad_vect, jacobian_mat, gradiente, divergencia, rotacional, rotacional_2d, laplaciano, deriv_vect, deriv_prog_2p, deriv_reg_2p, deriv_prog_3p, deriv_reg_3p, deriv_cent_3p, deriv_prog_5p, deriv_cent_5p, deriv2_prog_3p, deriv2_cent_3p, deriv2_prog_5p, deriv2_cent_5p, deriv_func, richardson_deriv_mat, deriv_richardson, deriv_tol, err_deriv_h_mat, deriv_vect_3p, deriv_vect_5p, deriv2_vect, deriv_xy, deriv_xy_3p, deriv_xy_5p, deriv2_xy_3p, deriv2_xy_5p, deriv_xy_tol
// Dependencias copiadas (8): MC_NAN, print_error, print_warning, print_error_int, copy_vect, gen_mat, del_mat, zeros_mat
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

#ifndef MC_FN_part2_derv_c
#define MC_FN_part2_derv_c
// Derivada parcial segunda CENTRAL de alta precisión
// Descripción: Calcula d2f/dx_j2 con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9; error O(h^(puntos-1)) con puntos centrados). Si h <= 0 elige el paso automatico h = eps^(1/(puntos+1)) * max(1, |x_j|).
// Necesita puntos evaluaciones de f. f debe ser suave en el entorno del punto.
double part2_derv_c(double (*f)(double*, int), double *x, int n, int j, double h, int puntos) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0]*v[1] + sin(v[1]); }
        double punto[] = {2.0, 0.5};
        double d2fdx2 = part2_derv_c(mi_func, punto, 2, 0, 0.0, 5);   // 2*y = 1.0
        double d2fdy2 = part2_derv_c(mi_func, punto, 2, 1, 0.0, 5);   // -sin(y) = -0.4794255
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("part2_derv_c: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    if (j < 0 || j >= n) { print_error_int("part2_derv_c: la variable j esta fuera de rango", j); return MC_NAN; }
    if (h <= 0.0) h = pow(2.220446049250313e-16, 1.0 / (puntos + 1)) * ((fabs(x[j]) > 1.0) ? fabs(x[j]) : 1.0);
    int m = puntos / 2;
    double xs[9], w[9];
    for (int k = 0; k < puntos; k++) xs[k] = (double)(k - m);
    pesos_deriv_lagrange(xs, puntos, 0.0, 2, w);
    double *xh = copy_vect(x, n);
    double suma = 0.0;
    for (int k = 0; k < puntos; k++) {
        xh[j] = x[j] + (k - m) * h;
        suma += w[k] * f(xh, n);
    }
    delete[] xh;
    return suma / (h * h);
}
#endif // MC_FN_part2_derv_c

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

#ifndef MC_FN_total_derv
#define MC_FN_total_derv
// Derivada total
// Descripción: Calcula la derivada total dF/dt sumando el producto de las derivadas parciales por dx_i/dt. Usa part_derv (centrales de 5 puntos, O(h^4)).
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
// Descripción: Devuelve un vector con todas las derivadas parciales de una función escalar. Usa part_derv (centrales de 5 puntos); para elegir paso y puntos usa gradiente().
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

#ifndef MC_FN_gradiente
#define MC_FN_gradiente
// Gradiente de un campo escalar (alta precisión)
// Descripción: Devuelve el vector (df/dx_1, ..., df/dx_n) en el punto x con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9) y paso h (h <= 0 = automatico). Es la mejor opcion para precision;
// grad_vect hace lo mismo con valores fijos (5 puntos, paso automatico). Liberar con delete[].
double* gradiente(double (*f)(double*, int), double *x, int n, double h, int puntos) {
    /*
    Ejemplo de uso:
        double campo(double *v, int n) { return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; }   // f = x^2 + y^2 + z^2
        double punto[] = {1.0, 2.0, 3.0};
        double *g = gradiente(campo, punto, 3, 0.0, 5);     // (2x, 2y, 2z) = (2, 4, 6)
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("gradiente: puntos debe ser impar entre 3 y 9", puntos); return NULL; }
    double *g = new double[n];
    for (int j = 0; j < n; j++) g[j] = part_derv_c(f, x, n, j, h, puntos);
    return g;
}
#endif // MC_FN_gradiente

#ifndef MC_FN_divergencia
#define MC_FN_divergencia
// Divergencia de un campo vectorial (alta precisión)
// Descripción: Calcula div F = dF_1/dx_1 + ... + dF_n/dx_n en el punto x. El campo se pasa como array de n funciones AF[i](x, n) (componente i). Diferencias centrales de 'puntos' puntos y paso h (h <= 0 = automatico).
double divergencia(double (*AF[])(double*, int), double *x, int n, double h, int puntos) {
    /*
    Ejemplo de uso:
        double Fx(double *v, int n) { return v[0]*v[1]; }    // F = (x*y, y*z, z*x)
        double Fy(double *v, int n) { return v[1]*v[2]; }
        double Fz(double *v, int n) { return v[2]*v[0]; }
        double (*F[3])(double*, int) = {Fx, Fy, Fz};
        double punto[] = {1.0, 2.0, 3.0};
        double div = divergencia(F, punto, 3, 0.0, 5);       // y + z + x = 6
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("divergencia: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    double suma = 0.0;
    for (int i = 0; i < n; i++) suma += part_derv_c(AF[i], x, n, i, h, puntos);
    return suma;
}
#endif // MC_FN_divergencia

#ifndef MC_FN_rotacional
#define MC_FN_rotacional
// Rotacional de un campo vectorial 3D (alta precisión)
// Descripción: Devuelve rot F = (dFz/dy - dFy/dz, dFx/dz - dFz/dx, dFy/dx - dFx/dy) en el punto x = (x, y, z). El campo son 3 funciones AF[0..2](x, 3). Diferencias centrales de 'puntos' puntos y paso h (h <= 0 = automatico).
// Para un campo plano (2 componentes) usa rotacional_2d. Liberar con delete[].
double* rotacional(double (*AF[])(double*, int), double *x, double h, int puntos) {
    /*
    Ejemplo de uso:
        double Fx(double *v, int n) { return v[0]*v[1]; }    // F = (x*y, y*z, z*x)
        double Fy(double *v, int n) { return v[1]*v[2]; }
        double Fz(double *v, int n) { return v[2]*v[0]; }
        double (*F[3])(double*, int) = {Fx, Fy, Fz};
        double punto[] = {1.0, 2.0, 3.0};
        double *rot = rotacional(F, punto, 0.0, 5);          // (-y, -z, -x) = (-2, -3, -1)
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("rotacional: puntos debe ser impar entre 3 y 9", puntos); return NULL; }
    double *r = new double[3];
    r[0] = part_derv_c(AF[2], x, 3, 1, h, puntos) - part_derv_c(AF[1], x, 3, 2, h, puntos);
    r[1] = part_derv_c(AF[0], x, 3, 2, h, puntos) - part_derv_c(AF[2], x, 3, 0, h, puntos);
    r[2] = part_derv_c(AF[1], x, 3, 0, h, puntos) - part_derv_c(AF[0], x, 3, 1, h, puntos);
    return r;
}
#endif // MC_FN_rotacional

#ifndef MC_FN_rotacional_2d
#define MC_FN_rotacional_2d
// Rotacional de un campo vectorial plano (componente z)
// Descripción: Para un campo F = (Fx, Fy) en el plano devuelve (rot F)_z = dFy/dx - dFx/dy en el punto x = (x, y). Es la circulacion por unidad de area. Diferencias centrales de 'puntos' puntos y paso h (h <= 0 = automatico).
double rotacional_2d(double (*AF[])(double*, int), double *x, double h, int puntos) {
    /*
    Ejemplo de uso:
        double Fx(double *v, int n) { return -v[1]; }       // rotacion rigida F = (-y, x)
        double Fy(double *v, int n) { return v[0]; }
        double (*F[2])(double*, int) = {Fx, Fy};
        double punto[] = {1.0, 1.0};
        double rz = rotacional_2d(F, punto, 0.0, 5);         // 2
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("rotacional_2d: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    return part_derv_c(AF[1], x, 2, 0, h, puntos) - part_derv_c(AF[0], x, 2, 1, h, puntos);
}
#endif // MC_FN_rotacional_2d

#ifndef MC_FN_laplaciano
#define MC_FN_laplaciano
// Laplaciano de un campo escalar (alta precisión)
// Descripción: Calcula laplaciano f = d2f/dx_1^2 + ... + d2f/dx_n^2 en el punto x con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9) y paso h (h <= 0 = automatico). Una funcion armonica da 0.
// Usa n*puntos evaluaciones de f. f debe ser suave en el entorno del punto.
double laplaciano(double (*f)(double*, int), double *x, int n, double h, int puntos) {
    /*
    Ejemplo de uso:
        double campo(double *v, int n) { return sin(v[0]) * sin(v[1]); }   // f = sin(x) sin(y)
        double punto[] = {0.7, 1.1};
        double lap = laplaciano(campo, punto, 2, 0.0, 5);     // -2 sin(x) sin(y) = -2*sin(0.7)*sin(1.1) = -1.1486...
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("laplaciano: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    double suma = 0.0;
    for (int j = 0; j < n; j++) suma += part2_derv_c(f, x, n, j, h, puntos);
    return suma;
}
#endif // MC_FN_laplaciano

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
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_reg_2p(f, 2.0, 0.1);
        // Resultado: d = 20.74913   (exacta: 22.167168)
    */
    return (f(x) - f(x - h)) / h;
}
#endif // MC_FN_deriv_reg_2p

#ifndef MC_FN_deriv_prog_3p
#define MC_FN_deriv_prog_3p
// Derivada primera, diferencias progresivas de 3 puntos
// Descripción: f'(x) ~ (-3f(x) + 4f(x+h) - f(x+2h))/(2h). Error O(h^2).
double deriv_prog_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_prog_3p(f, 2.0, 0.1);
        // Resultado: d = 22.0323   (exacta: 22.167168)
    */
    return (-3.0 * f(x) + 4.0 * f(x + h) - f(x + 2.0 * h)) / (2.0 * h);
}
#endif // MC_FN_deriv_prog_3p

#ifndef MC_FN_deriv_reg_3p
#define MC_FN_deriv_reg_3p
// Derivada primera, diferencias regresivas de 3 puntos
// Descripción: f'(x) ~ (3f(x) - 4f(x-h) + f(x-2h))/(2h). Error O(h^2).
double deriv_reg_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_reg_3p(f, 2.0, 0.1);
        // Resultado: d = 22.05452   (exacta: 22.167168)
    */
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
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_prog_5p(f, 2.0, 0.1);
        // Resultado: d = 22.16591   (exacta: 22.167168)
    */
    return (-25.0 * f(x) + 48.0 * f(x + h) - 36.0 * f(x + 2.0 * h) + 16.0 * f(x + 3.0 * h) - 3.0 * f(x + 4.0 * h)) / (12.0 * h);
}
#endif // MC_FN_deriv_prog_5p

#ifndef MC_FN_deriv_cent_5p
#define MC_FN_deriv_cent_5p
// Derivada primera, diferencias centrales de 5 puntos
// Descripción: f'(x) ~ (f(x-2h) - 8f(x-h) + 8f(x+h) - f(x+2h))/(12h). Error O(h^4).
double deriv_cent_5p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_cent_5p(f, 2.0, 0.1);
        // Resultado: d = 22.167   (exacta: 22.167168)
    */
    return (f(x - 2.0 * h) - 8.0 * f(x - h) + 8.0 * f(x + h) - f(x + 2.0 * h)) / (12.0 * h);
}
#endif // MC_FN_deriv_cent_5p

#ifndef MC_FN_deriv2_prog_3p
#define MC_FN_deriv2_prog_3p
// Derivada segunda, diferencias progresivas de 3 puntos
// Descripción: f''(x) ~ (f(x) - 2f(x+h) + f(x+2h))/h^2. Error O(h).
double deriv2_prog_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv2_prog_3p(f, 2.0, 0.1);
        // Resultado: d = 33.52283   (exacta: 29.556224)
    */
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
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv2_prog_5p(f, 2.0, 0.1);
        // Resultado: d = 29.608   (exacta: 29.556224)
    */
    return (35.0 * f(x) - 104.0 * f(x + h) + 114.0 * f(x + 2.0 * h) - 56.0 * f(x + 3.0 * h) + 11.0 * f(x + 4.0 * h)) / (12.0 * h * h);
}
#endif // MC_FN_deriv2_prog_5p

#ifndef MC_FN_deriv2_cent_5p
#define MC_FN_deriv2_cent_5p
// Derivada segunda, diferencias centrales de 5 puntos
// Descripción: f''(x) ~ (-f(x-2h) + 16f(x-h) - 30f(x) + 16f(x+h) - f(x+2h))/(12h^2). Error O(h^4).
double deriv2_cent_5p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv2_cent_5p(f, 2.0, 0.1);
        // Resultado: d = 29.55616   (exacta: 29.556224)
    */
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

#ifndef MC_FN_deriv_tol
#define MC_FN_deriv_tol
// Derivada de una función con la tolerancia que elijas (Richardson)
// Descripción: Calcula f'(x0) (orden = 1) o f''(x0) (orden = 2) refinando el paso (h0, h0/2, h0/4...) con extrapolacion de Richardson hasta que dos estimaciones consecutivas difieran menos que 'tol'.
// Devuelve la derivada y, en 'err_est', el error estimado. Se detiene antes si el error de redondeo empieza a dominar (no se puede pedir una tolerancia por debajo de ~1e-10).
double deriv_tol(double (*f)(double), double x0, double h0, double tol, int orden, double &err_est) {
    /*
    Ejemplo de uso:
        double err;
        double d = deriv_tol(exp, 1.0, 0.1, 1e-9, 1, err);     // e = 2.718281828 con error estimado err
    */
    if (orden != 1 && orden != 2) { print_error_int("deriv_tol: orden debe ser 1 o 2", orden); err_est = MC_NAN; return MC_NAN; }
    const int NMAX = 10;
    double T[NMAX][NMAX];
    double h = h0, mejor = MC_NAN, mejor_e = 1e300;
    for (int i = 0; i < NMAX; i++) {
        T[i][0] = (orden == 1) ? deriv_cent_3p(f, x0, h) : deriv2_cent_3p(f, x0, h);
        double p4 = 1.0;
        for (int j = 1; j <= i; j++) {
            p4 *= 4.0;
            T[i][j] = (p4 * T[i][j - 1] - T[i - 1][j - 1]) / (p4 - 1.0);
        }
        if (i >= 1) {
            double e = fabs(T[i][i] - T[i - 1][i - 1]);
            if (e < tol) { err_est = e; return T[i][i]; }
            if (e < mejor_e) { mejor_e = e; mejor = T[i][i]; }
            else if (i >= 3) break;                         // el redondeo empieza a dominar
        }
        h /= 2.0;
    }
    print_warning("deriv_tol: no se alcanzo la tolerancia (se devuelve el mejor resultado).");
    err_est = mejor_e;
    return mejor;
}
#endif // MC_FN_deriv_tol

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

#ifndef MC_FN_deriv_xy
#define MC_FN_deriv_xy
// Derivada de datos tabulados y(x) con la precisión (nº de puntos) que elijas
// Descripción: Deriva y respecto a x en cada punto con una formula de 'puntos' puntos (derivada del polinomio de Lagrange). x puede tener CUALQUIER espaciado pero debe ser estrictamente monotono.
// orden = 1 o 2 (derivada primera o segunda); puntos = de orden+1 a 9. El error es O(h^(puntos-1)): 3 puntos -> O(h^2), 5 puntos -> O(h^4). Formulas centradas en el interior y laterales en los extremos.
// Con datos con ruido, mas puntos NO siempre mejoran el resultado (la derivada amplifica el ruido).
double* deriv_xy(double *x, double *y, int n, int orden, int puntos) {
    /*
    Ejemplo de uso:
        double x[] = {0.0, 0.1, 0.2, 0.4, 0.7, 1.0};           // espaciado NO uniforme
        double y[] = {0.0, 0.01, 0.04, 0.16, 0.49, 1.0};       // y = x^2
        double *dy  = deriv_xy(x, y, 6, 1, 3);                  // dy/dx = 2x (exacta con 3 puntos)
        double *d2y = deriv_xy(x, y, 6, 2, 3);                  // d2y/dx2 = 2
    */
    if (orden != 1 && orden != 2) { print_error_int("deriv_xy: orden debe ser 1 o 2", orden); return NULL; }
    if (puntos < orden + 1 || puntos > 9) { print_error_int("deriv_xy: puntos debe estar entre orden+1 y 9", puntos); return NULL; }
    if (n < puntos) { print_error_int("deriv_xy: hay menos datos que puntos de la formula", n); return NULL; }
    double sentido = (x[1] > x[0]) ? 1.0 : -1.0;
    for (int i = 0; i < n - 1; i++)
        if ((x[i + 1] - x[i]) * sentido <= 0.0) {
            print_error("deriv_xy: x debe ser estrictamente creciente o decreciente (sin puntos repetidos)");
            return NULL;
        }
    double *d = new double[n];
    double w[9];
    for (int i = 0; i < n; i++) {
        int s = i - (puntos - 1) / 2;                 // formula centrada si es posible
        if (s < 0) s = 0;
        if (s > n - puntos) s = n - puntos;
        pesos_deriv_lagrange(x + s, puntos, x[i], orden, w);
        double suma = 0.0;
        for (int k = 0; k < puntos; k++) suma += w[k] * y[s + k];
        d[i] = suma;
    }
    return d;
}
#endif // MC_FN_deriv_xy

#ifndef MC_FN_deriv_xy_3p
#define MC_FN_deriv_xy_3p
// Derivada primera de datos tabulados y(x), formulas de 3 puntos
// Descripción: dy/dx con error O(h^2) en todos los puntos (centrales en el interior, laterales en los extremos). x puede ser NO uniforme. Es deriv_xy con orden 1 y 3 puntos. Necesita n >= 3.
double* deriv_xy_3p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *dy = deriv_xy_3p(x, y, n);
        print_vect(dy, n, "dy/dx");
    */
    return deriv_xy(x, y, n, 1, 3);
}
#endif // MC_FN_deriv_xy_3p

#ifndef MC_FN_deriv_xy_5p
#define MC_FN_deriv_xy_5p
// Derivada primera de datos tabulados y(x), formulas de 5 puntos
// Descripción: dy/dx con error O(h^4). x puede ser NO uniforme. Es deriv_xy con orden 1 y 5 puntos. Necesita n >= 5.
double* deriv_xy_5p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *x = linspace(0.0, 1.0, 11);
        double *y = sin_vect(x, 11);
        double *dy = deriv_xy_5p(x, y, 11);       // ~ cos(x) con error O(h^4)
    */
    return deriv_xy(x, y, n, 1, 5);
}
#endif // MC_FN_deriv_xy_5p

#ifndef MC_FN_deriv2_xy_3p
#define MC_FN_deriv2_xy_3p
// Derivada segunda de datos tabulados y(x), formulas de 3 puntos
// Descripción: d2y/dx2 con error O(h^2) en el interior (O(h) en los extremos). x puede ser NO uniforme. Es deriv_xy con orden 2 y 3 puntos. Necesita n >= 3.
double* deriv2_xy_3p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *d2y = deriv2_xy_3p(x, y, n);
    */
    return deriv_xy(x, y, n, 2, 3);
}
#endif // MC_FN_deriv2_xy_3p

#ifndef MC_FN_deriv2_xy_5p
#define MC_FN_deriv2_xy_5p
// Derivada segunda de datos tabulados y(x), formulas de 5 puntos
// Descripción: d2y/dx2 con error O(h^4) en el interior. x puede ser NO uniforme. Es deriv_xy con orden 2 y 5 puntos. Necesita n >= 5.
double* deriv2_xy_5p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *d2y = deriv2_xy_5p(x, y, n);       // ~ -sin(x) si y = sin(x)
    */
    return deriv_xy(x, y, n, 2, 5);
}
#endif // MC_FN_deriv2_xy_5p

#ifndef MC_FN_deriv_xy_tol
#define MC_FN_deriv_xy_tol
// Derivada de datos tabulados y(x) con la tolerancia que elijas
// Descripción: Prueba formulas con mas y mas puntos (de orden+1 hasta 9) y se detiene cuando dos consecutivas difieren, en todos los puntos, menos que 'tol'. Devuelve la derivada, los puntos usados y el error estimado (max |d_p - d_(p-1)|).
// Valido para datos suaves y sin ruido y con x NO uniforme. Si no se alcanza 'tol' avisa y devuelve el mejor resultado.
double* deriv_xy_tol(double *x, double *y, int n, int orden, double tol, int &puntos_usados, double &err_max) {
    /*
    Ejemplo de uso:
        int p; double err;
        double *dy = deriv_xy_tol(x, y, n, 1, 1e-6, p, err);     // p = puntos necesarios
    */
    int p0 = orden + 1;
    double *prev = deriv_xy(x, y, n, orden, p0);
    puntos_usados = p0;
    err_max = MC_NAN;
    if (prev == NULL) return NULL;
    int pmax = (n < 9) ? n : 9;
    for (int p = p0 + 1; p <= pmax; p++) {
        double *cur = deriv_xy(x, y, n, orden, p);
        double e = 0.0;
        for (int i = 0; i < n; i++) if (fabs(cur[i] - prev[i]) > e) e = fabs(cur[i] - prev[i]);
        delete[] prev;
        prev = cur;
        puntos_usados = p;
        err_max = e;
        if (e < tol) return prev;
    }
    print_warning("deriv_xy_tol: no se alcanzo la tolerancia con los datos disponibles (se devuelve el mejor resultado).");
    return prev;
}
#endif // MC_FN_deriv_xy_tol

#endif // MATCLUB_DERIVACION_CPP
