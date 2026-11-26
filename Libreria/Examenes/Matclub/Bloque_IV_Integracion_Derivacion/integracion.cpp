// ============================================================================
// MATCLUB-CPP  |  BLOQUE IV: INTEGRACION Y DERIVACION  |  IV.1
// Integracion numerica
// ============================================================================
// Trapecio y Simpson (simples y compuestas), datos tabulados x-y con espaciado no uniforme y precision elegible (grado o tolerancia), Richardson, Romberg, Simpson adaptativo, Gauss-Legendre e integrales multiples.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "integracion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (31): integral_def_func, integral_indef_func, int_vect, nc_trapecio, nc_simpson13, nc_simpson38, trapecio_comp_func, simpson13_comp_func, simpson38_comp_func, trapecio_comp_vect, simpson13_comp_vect, simpson38_comp_vect, pesos_integ_lagrange, integral_xy, trapecio_xy, simpson13_xy, simpson38_xy, integral_xy_tol, richardson_int, romberg_mat, romberg_int, simpson_adapt_rec, integral_adapt, gauss_legendre_nodos, gauss_legendre_func, pesos_nc, integral_doble_func, integral_triple_func, integral_doble_mat, gauss_doble_func, gauss_triple_func
// Dependencias copiadas (8): MC_NAN, print_error, print_warning, print_error_int, isNaN, gen_mat, del_mat, zeros_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_INTEGRACION_CPP
#define MATCLUB_INTEGRACION_CPP

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
#ifndef MC_FN_isNaN
#define MC_FN_isNaN
bool isNaN(double v) {
    return v != v; // En norma IEEE 754, NaN es distinto de sí mismo
}
#endif // MC_FN_isNaN

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
// FUNCIONES DEL MODULO: Integracion numerica
// ----------------------------------------------------------------------------

#ifndef MC_FN_integral_def_func
#define MC_FN_integral_def_func
// Integral Definida Numérica de una función (Regla de Simpson 1/3)
// Descripción: Calcula el área bajo la curva de la función 'f' en el intervalo [a, b] con 'n' paneles (n par).
double integral_def_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return x * x; } // f(x) = x^2
        // Integral de 0 a 2 con 1000 paneles
        double area = integral_def_func(mi_func, 0.0, 2.0, 1000); 
    */
    if (n % 2 != 0) n++; // n debe ser par para Simpson 1/3
    double h = (b - a) / n;
    double suma = f(a) + f(b);
    
    for (int i = 1; i < n; i++) {
        double xi = a + i * h;
        if (i % 2 == 0) suma += 2.0 * f(xi); // Índices pares
        else            suma += 4.0 * f(xi); // Índices impares
    }
    return (h / 3.0) * suma;
}
#endif // MC_FN_integral_def_func

#ifndef MC_FN_integral_indef_func
#define MC_FN_integral_indef_func
// Integral Indefinida Numérica de una función sobre un dominio discreto
// Descripción: Evalúa la integral acumulativa de 'f' sobre los puntos del vector 'x', sumando la constante 'C'.
double* integral_indef_func(double (*f)(double), double *x, int n_puntos, double C) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return cos(x); }
        int n = 100;
        double *x = linspace(0.0, 3.14, n);
        double *F_x = integral_indef_func(mi_func, x, n, 0.0); // C = 0
    */
    double *F = new double[n_puntos];
    F[0] = C; // F(x0) = C
    
    for (int i = 0; i < n_puntos - 1; i++) {
        // Área del trapecio entre x[i] y x[i+1]
        double area = (x[i+1] - x[i]) * (f(x[i]) + f(x[i+1])) / 2.0;
        F[i+1] = F[i] + area;
    }
    return F;
}
#endif // MC_FN_integral_indef_func

#ifndef MC_FN_int_vect
#define MC_FN_int_vect
// Integral Numérica de datos discretos (Vectorial)
// Descripción: Calcula la integral definida e indefinida (acumulada) usando la regla del trapecio.
// Nota: 'int_indef' se devuelve por return, 'int_def' se extrae por referencia (&).
double* int_vect(double *x, double *y, int n, double y0, double &int_def) {
    /*
    Ejemplo de uso:
        double area_total;
        double *integral_acumulada = int_vect(x, y, n, 5.0, area_total); // C = 5.0
        cout << "Integral definida (Area): " << area_total << endl;
    */
    if (n < 2) return NULL;
    
    double *int_indef = new double[n];
    int_indef[0] = y0;
    
    for (int i = 0; i < n - 1; i++) {
        double area = (x[i+1] - x[i]) * (y[i] + y[i+1]) / 2.0;
        int_indef[i+1] = int_indef[i] + area;
    }
    
    // La integral definida es el valor acumulado final (sin contar la constante y0 inicial)
    int_def = int_indef[n - 1] - y0; 
    
    // Se pide que la integral definida devuelva también y0 + Int_def según tu MATLAB
    int_def = int_def + y0;
    
    return int_indef;
}
#endif // MC_FN_int_vect

#ifndef MC_FN_nc_trapecio
#define MC_FN_nc_trapecio
// Newton-Cotes cerrada n=1: Regla Trapezoidal simple
// Descripción: I = h/2*(f(a)+f(b)) con h = b-a. Error = -h^3/12*f''(xi). Exacta para polinomios de grado 1.
double nc_trapecio(double (*f)(double), double a, double b) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return x*x*x - 2*x*x + 7*x - 5; }
        double I = nc_trapecio(mi_func, 1.0, 3.0);   // 26 (exacto: 20.6667)
    */
    return (b - a) / 2.0 * (f(a) + f(b));
}
#endif // MC_FN_nc_trapecio

#ifndef MC_FN_nc_simpson13
#define MC_FN_nc_simpson13
// Newton-Cotes cerrada n=2: Regla de 1/3 de Simpson simple
// Descripción: I = h/3*(f(x0)+4f(x1)+f(x2)) con h = (b-a)/2. Error = -h^5/90*f''''(xi). Exacta para polinomios de grado <= 3.
double nc_simpson13(double (*f)(double), double a, double b) {
    /*
    Ejemplo de uso:
        double I = nc_simpson13(mi_func, 1.0, 3.0);   // 20.6667 (exacto)
    */
    double h = (b - a) / 2.0;
    return h / 3.0 * (f(a) + 4.0 * f(a + h) + f(b));
}
#endif // MC_FN_nc_simpson13

#ifndef MC_FN_nc_simpson38
#define MC_FN_nc_simpson38
// Newton-Cotes cerrada n=3: Regla de 3/8 de Simpson simple
// Descripción: I = 3h/8*(f(x0)+3f(x1)+3f(x2)+f(x3)) con h = (b-a)/3. Error = -3h^5/80*f''''(xi). Exacta para polinomios de grado <= 3.
double nc_simpson38(double (*f)(double), double a, double b) {
    /*
    Ejemplo de uso:
        double I = nc_simpson38(mi_func, 1.0, 3.0);   // 20.6667 (exacto)
    */
    double h = (b - a) / 3.0;
    return 3.0 * h / 8.0 * (f(a) + 3.0 * f(a + h) + 3.0 * f(a + 2.0 * h) + f(b));
}
#endif // MC_FN_nc_simpson38

#ifndef MC_FN_trapecio_comp_func
#define MC_FN_trapecio_comp_func
// Regla Trapezoidal compuesta (con función)
// Descripción: Divide [a,b] en 'n' subintervalos y suma trapecios: h*(f0/2 + f1 + ... + f(n-1) + fn/2). Error global O(h^2).
double trapecio_comp_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = trapecio_comp_func(mi_func, 1.0, 3.0, 100);
    */
    if (n < 1) { print_error_int("trapecio_comp_func: n debe ser >= 1", n); return MC_NAN; }
    double h = (b - a) / n;
    double suma = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) suma += f(a + i * h);
    return h * suma;
}
#endif // MC_FN_trapecio_comp_func

#ifndef MC_FN_simpson13_comp_func
#define MC_FN_simpson13_comp_func
// Regla de 1/3 de Simpson compuesta (con función)
// Descripción: Aplica Simpson 1/3 en grupos de 2 subintervalos (n debe ser par; si no lo es se sube al siguiente par). Error global O(h^4).
double simpson13_comp_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = simpson13_comp_func(mi_func, 1.0, 3.0, 100);
    */
    if (n < 2) n = 2;
    if (n % 2 != 0) n++;
    double h = (b - a) / n;
    double suma = f(a) + f(b);
    for (int i = 1; i < n; i++) suma += ((i % 2 == 0) ? 2.0 : 4.0) * f(a + i * h);
    return h / 3.0 * suma;
}
#endif // MC_FN_simpson13_comp_func

#ifndef MC_FN_simpson38_comp_func
#define MC_FN_simpson38_comp_func
// Regla de 3/8 de Simpson compuesta (con función)
// Descripción: Aplica Simpson 3/8 en grupos de 3 subintervalos (n debe ser multiplo de 3; si no lo es se sube al siguiente multiplo). Error global O(h^4).
double simpson38_comp_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = simpson38_comp_func(mi_func, 0.0, 1.0, 99);
    */
    if (n < 3) n = 3;
    if (n % 3 != 0) n += 3 - (n % 3);
    double h = (b - a) / n;
    double suma = f(a) + f(b);
    for (int i = 1; i < n; i++) suma += ((i % 3 == 0) ? 2.0 : 3.0) * f(a + i * h);
    return 3.0 * h / 8.0 * suma;
}
#endif // MC_FN_simpson38_comp_func

#ifndef MC_FN_trapecio_comp_vect
#define MC_FN_trapecio_comp_vect
// Regla Trapezoidal compuesta (datos tabulados equiespaciados)
// Descripción: Integra los valores y[0..n_puntos-1] separados una distancia 'h'. (Para espaciado no uniforme usar int_vect).
double trapecio_comp_vect(double *y, int n_puntos, double h) {
    /*
    Ejemplo de uso:
        double I = trapecio_comp_vect(y, 10, 0.2);   // 9 subintervalos de h = 0.2
    */
    if (n_puntos < 2) { print_error_int("trapecio_comp_vect: se necesitan al menos 2 puntos", n_puntos); return MC_NAN; }
    double suma = 0.5 * (y[0] + y[n_puntos - 1]);
    for (int i = 1; i < n_puntos - 1; i++) suma += y[i];
    return h * suma;
}
#endif // MC_FN_trapecio_comp_vect

#ifndef MC_FN_simpson13_comp_vect
#define MC_FN_simpson13_comp_vect
// Regla de 1/3 de Simpson compuesta (datos tabulados equiespaciados)
// Descripción: Necesita un numero PAR de subintervalos (n_puntos impar). Si es impar, se usa la regla trapezoidal en el ultimo subintervalo y Simpson en el resto.
double simpson13_comp_vect(double *y, int n_puntos, double h) {
    /*
    Ejemplo de uso:
        double I = simpson13_comp_vect(y, 11, 0.1);   // 10 subintervalos
    */
    if (n_puntos < 2) { print_error_int("simpson13_comp_vect: se necesitan al menos 2 puntos", n_puntos); return MC_NAN; }
    int m = n_puntos - 1;                 // numero de subintervalos
    int ms = m - (m % 2);                 // subintervalos tratados con Simpson
    double res = 0.0;
    if (ms > 0) {
        double suma = y[0] + y[ms];
        for (int i = 1; i < ms; i++) suma += ((i % 2 == 0) ? 2.0 : 4.0) * y[i];
        res = h / 3.0 * suma;
    }
    if (m % 2 == 1) res += h * (y[m - 1] + y[m]) / 2.0;
    return res;
}
#endif // MC_FN_simpson13_comp_vect

#ifndef MC_FN_simpson38_comp_vect
#define MC_FN_simpson38_comp_vect
// Regla de 3/8 de Simpson compuesta (datos tabulados equiespaciados)
// Descripción: Necesita que el numero de subintervalos (n_puntos-1) sea multiplo de 3.
double simpson38_comp_vect(double *y, int n_puntos, double h) {
    /*
    Ejemplo de uso:
        double I = simpson38_comp_vect(y, 10, 0.1);   // 9 subintervalos
    */
    int m = n_puntos - 1;
    if (m < 3 || m % 3 != 0) { print_error_int("simpson38_comp_vect: n_puntos-1 debe ser multiplo de 3", m); return MC_NAN; }
    double suma = y[0] + y[m];
    for (int i = 1; i < m; i++) suma += ((i % 3 == 0) ? 2.0 : 3.0) * y[i];
    return 3.0 * h / 8.0 * suma;
}
#endif // MC_FN_simpson38_comp_vect

#ifndef MC_FN_pesos_integ_lagrange
#define MC_FN_pesos_integ_lagrange
// Pesos de integración (integral del polinomio de Lagrange)
// Descripción: Para los m nodos xs[0..m-1] (NO tienen que estar equiespaciados) calcula los pesos w[j] = integral de L_j(x) entre xs[0] y xs[m-1], de modo que
// integral(f) ~ sum(w[j]*f(xs[j])). Con nodos equiespaciados reproduce trapecio (m=2), Simpson 1/3 (m=3), Simpson 3/8 (m=4), Boole (m=5)... 'w' debe tener m posiciones.
void pesos_integ_lagrange(double *xs, int m, double *w) {
    /*
    Ejemplo de uso:
        double xs[] = {0.0, 0.5, 1.0}, w[3];
        pesos_integ_lagrange(xs, 3, w);     // w = {1/6, 4/6, 1/6}: Simpson 1/3 con h = 0.5
    */
    double H = xs[m - 1] - xs[0];
    double *u = new double[m];
    double *c = new double[m + 1];
    for (int k = 0; k < m; k++) u[k] = (xs[k] - xs[0]) / H;          // nodos normalizados a [0,1]
    for (int j = 0; j < m; j++) {
        for (int i = 0; i <= m; i++) c[i] = 0.0;
        c[0] = 1.0;
        int deg = 0;
        double den = 1.0;
        for (int k = 0; k < m; k++) {                                // L_j(u) = prod (u - u_k)/(u_j - u_k)
            if (k == j) continue;
            for (int i = deg + 1; i >= 1; i--) c[i] = c[i - 1] - u[k] * c[i];
            c[0] = -u[k] * c[0];
            deg++;
            den *= (u[j] - u[k]);
        }
        double integ = 0.0;
        for (int i = 0; i <= deg; i++) integ += c[i] / (i + 1.0);
        w[j] = H * integ / den;
    }
    delete[] u; delete[] c;
}
#endif // MC_FN_pesos_integ_lagrange

#ifndef MC_FN_integral_xy
#define MC_FN_integral_xy
// Integral de datos tabulados y(x) con la precisión (grado) que elijas
// Descripción: Integra y respecto a x con los n puntos (x[i], y[i]). x puede tener CUALQUIER espaciado (saltos, zonas densas y dispersas...) pero debe ser estrictamente creciente o decreciente.
// 'grado' elige la precision: 1 = trapecio (O(h^2)), 2 = Simpson 1/3 (O(h^4)), 3 = Simpson 3/8 (O(h^4)), 4 = Boole (O(h^6)), hasta 6. Integra el polinomio de Lagrange de cada grupo de 'grado' subintervalos;
// si sobran subintervalos, el ultimo grupo usa un grado menor. Con muestras ruidosas, un grado alto NO mejora el resultado.
double integral_xy(double *x, double *y, int n, int grado) {
    /*
    Ejemplo de uso:
        double x[] = {0.0, 0.1, 0.2, 0.4, 0.8, 1.6, 2.0};       // espaciado NO uniforme
        double y[] = {0.0, 0.01, 0.04, 0.16, 0.64, 2.56, 4.0};   // y = x^2
        double I1 = integral_xy(x, y, 7, 1);                      // trapecio (menos preciso)
        double I2 = integral_xy(x, y, 7, 2);                      // Simpson 1/3: 2.66667 (exacto 8/3)
    */
    if (n < 2) { print_error_int("integral_xy: se necesitan al menos 2 puntos", n); return MC_NAN; }
    if (grado < 1 || grado > 6) { print_error_int("integral_xy: el grado debe estar entre 1 y 6", grado); return MC_NAN; }
    double sentido = (x[1] > x[0]) ? 1.0 : -1.0;
    for (int i = 0; i < n - 1; i++)
        if ((x[i + 1] - x[i]) * sentido <= 0.0) {
            print_error("integral_xy: x debe ser estrictamente creciente o decreciente (sin puntos repetidos)");
            return MC_NAN;
        }
    int m = n - 1;                              // subintervalos
    if (grado > m) grado = m;                   // pocos datos: se usa el mayor grado posible
    double w[8], suma = 0.0;
    int i = 0;
    while (i + grado <= m) {
        pesos_integ_lagrange(x + i, grado + 1, w);
        for (int j = 0; j <= grado; j++) suma += w[j] * y[i + j];
        i += grado;
    }
    int r = m - i;                              // subintervalos restantes (grado menor)
    if (r > 0) {
        pesos_integ_lagrange(x + i, r + 1, w);
        for (int j = 0; j <= r; j++) suma += w[j] * y[i + j];
    }
    return suma;
}
#endif // MC_FN_integral_xy

#ifndef MC_FN_trapecio_xy
#define MC_FN_trapecio_xy
// Regla Trapezoidal de datos tabulados (y respecto a x)
// Descripción: Integra y respecto a x sumando trapecios. x puede ser NO uniforme. Error O(h^2). Es integral_xy con grado 1.
double trapecio_xy(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4};
        double y[] = {6.050, 7.389, 9.025, 11.023, 13.464, 16.445, 20.086, 24.533, 29.964};   // e^x
        double I = trapecio_xy(x, y, 9);   // 23.9944 (exacto: 23.9144)
    */
    return integral_xy(x, y, n, 1);
}
#endif // MC_FN_trapecio_xy

#ifndef MC_FN_simpson13_xy
#define MC_FN_simpson13_xy
// Regla de 1/3 de Simpson de datos tabulados (y respecto a x)
// Descripción: Integra y respecto a x con parabolas por grupos de 3 puntos. x puede ser NO uniforme. Error O(h^4). Si el numero de subintervalos es impar, el ultimo se integra con un grado menor (trapecio). Es integral_xy con grado 2.
double simpson13_xy(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {0.0, 0.5, 1.0, 1.5, 2.0};
        double y[] = {0.0, 0.25, 1.0, 2.25, 4.0};     // y = x^2
        double I = simpson13_xy(x, y, 5);             // 2.66667 (exacto 8/3)
    */
    return integral_xy(x, y, n, 2);
}
#endif // MC_FN_simpson13_xy

#ifndef MC_FN_simpson38_xy
#define MC_FN_simpson38_xy
// Regla de 3/8 de Simpson de datos tabulados (y respecto a x)
// Descripción: Integra y respecto a x con cubicas por grupos de 4 puntos. x puede ser NO uniforme. Error O(h^4). Si (n-1) no es multiplo de 3, el ultimo grupo usa un grado menor. Es integral_xy con grado 3.
double simpson38_xy(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {0, 1, 2, 3, 4, 5, 6};
        double y[] = {0, 1, 8, 27, 64, 125, 216};     // y = x^3
        double I = simpson38_xy(x, y, 7);             // 324 (exacto)
    */
    return integral_xy(x, y, n, 3);
}
#endif // MC_FN_simpson38_xy

#ifndef MC_FN_integral_xy_tol
#define MC_FN_integral_xy_tol
// Integral de datos tabulados y(x) con la tolerancia que elijas
// Descripción: Prueba grados crecientes (1 a 6) de integral_xy y se detiene cuando dos grados consecutivos difieren menos que 'tol'. Devuelve la integral, el grado usado y una estimacion del error (|I_g - I_(g-1)|).
// Valido para datos suaves y sin ruido y con x NO uniforme. Si no se alcanza 'tol' avisa y devuelve el resultado de grado maximo.
double integral_xy_tol(double *x, double *y, int n, double tol, int &grado_usado, double &err_est) {
    /*
    Ejemplo de uso:
        int g; double err;
        double I = integral_xy_tol(x, y, n, 1e-6, g, err);    // g = grado necesario, err = error estimado
    */
    double prev = integral_xy(x, y, n, 1);
    grado_usado = 1;
    err_est = MC_NAN;
    if (isNaN(prev)) return MC_NAN;
    int gmax = (n - 1 < 6) ? n - 1 : 6;
    for (int g = 2; g <= gmax; g++) {
        double cur = integral_xy(x, y, n, g);
        err_est = fabs(cur - prev);
        grado_usado = g;
        if (err_est < tol) return cur;
        prev = cur;
    }
    print_warning("integral_xy_tol: no se alcanzo la tolerancia con los datos disponibles (se devuelve el mejor resultado).");
    return prev;
}
#endif // MC_FN_integral_xy_tol

#ifndef MC_FN_richardson_int
#define MC_FN_richardson_int
// Extrapolación de Richardson para integrales
// Descripción: Combina dos estimaciones I_n1 e I_n2 (con n1 y n2 subintervalos) en una mejorada: I* = I_n1 + (I_n2 - I_n1)/(1 - (n1/n2)^p).
// p = 2 para la regla trapezoidal y p = 4 para Simpson. Con n2 = 2*n1 equivale a (4*I_n2 - I_n1)/3 (trapecio) o (16*I_n2 - I_n1)/15 (Simpson).
double richardson_int(double I_n1, double I_n2, double n1, double n2, double p) {
    /*
    Ejemplo de uso:
        // Trapecio con n1 = 2 (I = 22) y n2 = 4 (I = 21) para x^3-2x^2+7x-5 en [1,3]
        double I = richardson_int(22.0, 21.0, 2, 4, 2);   // 20.6667 (exacto)
    */
    return I_n1 + (I_n2 - I_n1) / (1.0 - pow(n1 / n2, p));
}
#endif // MC_FN_richardson_int

#ifndef MC_FN_romberg_mat
#define MC_FN_romberg_mat
// Tabla de Romberg
// Descripción: Devuelve la matriz T[(N+1)x(N+1)] triangular inferior. T[i][0] es la regla trapezoidal con 2^i subintervalos y
// T[i][j] = (4^j*T[i][j-1] - T[i-1][j-1])/(4^j - 1) la j-esima extrapolacion de Richardson. Liberar con del_mat(T, N+1).
double** romberg_mat(double (*f)(double), double a, double b, int N) {
    /*
    Ejemplo de uso:
        double f_inv(double x) { return 1.0 / x; }
        double **T = romberg_mat(f_inv, 1.0, 137.2, 6);
        print_mat(T, 7, 7, "Romberg");   // ln(137.2) = 4.92144
    */
    if (N < 0) { print_error_int("romberg_mat: N debe ser >= 0", N); return NULL; }
    double **T = zeros_mat(N + 1, N + 1);
    T[0][0] = (b - a) / 2.0 * (f(a) + f(b));
    for (int i = 1; i <= N; i++) {
        int npan = 1 << (i - 1);                 // nuevos puntos (puntos medios)
        double h = (b - a) / (2.0 * npan);
        double suma = 0.0;
        for (int k = 1; k <= npan; k++) suma += f(a + (2 * k - 1) * h);
        T[i][0] = 0.5 * T[i - 1][0] + h * suma;
        double p4 = 1.0;
        for (int j = 1; j <= i; j++) {
            p4 *= 4.0;
            T[i][j] = (p4 * T[i][j - 1] - T[i - 1][j - 1]) / (p4 - 1.0);
        }
    }
    return T;
}
#endif // MC_FN_romberg_mat

#ifndef MC_FN_romberg_int
#define MC_FN_romberg_int
// Integración de Romberg con criterio de parada
// Descripción: Aumenta N hasta que dos valores consecutivos de la ultima fila de la tabla difieran menos que 'tol'. N_out devuelve el N usado.
double romberg_int(double (*f)(double), double a, double b, double tol, int N_max, int &N_out) {
    /*
    Ejemplo de uso:
        int N;
        double I = romberg_int(f_inv, 1.0, 137.2, 1e-8, 15, N);   // 4.92144
    */
    double **T = romberg_mat(f, a, b, N_max);
    if (T == NULL) return MC_NAN;
    double res = T[0][0];
    N_out = 0;
    for (int i = 1; i <= N_max; i++) {
        res = T[i][i];
        N_out = i;
        if (fabs(T[i][i] - T[i][i - 1]) < tol) break;
    }
    if (N_out == N_max && fabs(T[N_max][N_max] - T[N_max][N_max - 1]) >= tol)
        print_warning("romberg_int alcanzo N_max sin cumplir la tolerancia.");
    del_mat(T, N_max + 1);
    return res;
}
#endif // MC_FN_romberg_int

#ifndef MC_FN_simpson_adapt_rec
#define MC_FN_simpson_adapt_rec
// Helper de integral_adapt: Simpson adaptativo recursivo
// Descripción: Compara Simpson en [a,b] con la suma de Simpson en cada mitad; si difieren mas que 15*tol divide el intervalo y repite (con tol/2). 'prof' limita la profundidad de la recursion.
double simpson_adapt_rec(double (*f)(double), double a, double b, double fa, double fm, double fb, double S, double tol, int prof) {
    /*
    Ejemplo de uso: (se usa a traves de integral_adapt)
    */
    double m = 0.5 * (a + b);
    double flm = f(0.5 * (a + m)), frm = f(0.5 * (m + b));
    double Sl = (m - a) / 6.0 * (fa + 4.0 * flm + fm);
    double Sr = (b - m) / 6.0 * (fm + 4.0 * frm + fb);
    if (prof <= 0 || fabs(Sl + Sr - S) <= 15.0 * tol) return Sl + Sr + (Sl + Sr - S) / 15.0;
    return simpson_adapt_rec(f, a, m, fa, flm, fm, Sl, 0.5 * tol, prof - 1)
         + simpson_adapt_rec(f, m, b, fm, frm, fb, Sr, 0.5 * tol, prof - 1);
}
#endif // MC_FN_simpson_adapt_rec

#ifndef MC_FN_integral_adapt
#define MC_FN_integral_adapt
// Integral de una función con la tolerancia que elijas (Simpson adaptativo)
// Descripción: Calcula la integral de f en [a,b] con un error aproximado menor que 'tol', refinando solo donde hace falta (mas puntos donde f cambia deprisa). Funciona con singularidades suaves como sqrt(x) en 0.
// Condiciones: f continua y acotada en [a,b]. Para funciones muy oscilantes pide una tolerancia razonable (la recursion esta limitada a 40 niveles).
double integral_adapt(double (*f)(double), double a, double b, double tol) {
    /*
    Ejemplo de uso:
        double I = integral_adapt(sqrt, 0.0, 1.0, 1e-8);     // 0.666666667 (exacto 2/3)
    */
    if (tol <= 0.0) { print_error("integral_adapt: tol debe ser > 0"); return MC_NAN; }
    double fa = f(a), fb = f(b), fm = f(0.5 * (a + b));
    double S = (b - a) / 6.0 * (fa + 4.0 * fm + fb);
    return simpson_adapt_rec(f, a, b, fa, fm, fb, S, tol, 40);
}
#endif // MC_FN_integral_adapt

#ifndef MC_FN_gauss_legendre_nodos
#define MC_FN_gauss_legendre_nodos
// Nodos y pesos de la cuadratura de Gauss-Legendre
// Descripción: Calcula los 'n' nodos x (raices del polinomio de Legendre de grado n, en [-1,1]) y sus pesos w. Exacta para polinomios de grado <= 2n-1.
// x y w se devuelven por referencia (new[]).
void gauss_legendre_nodos(int n, double *&x, double *&w) {
    /*
    Ejemplo de uso:
        double *x, *w;
        gauss_legendre_nodos(3, x, w);   // x = {-0.7746, 0, 0.7746}, w = {5/9, 8/9, 5/9}
    */
    x = new double[n];
    w = new double[n];
    double pi = acos(-1.0);
    for (int i = 0; i < (n + 1) / 2; i++) {
        double z = cos(pi * (i + 0.75) / (n + 0.5)), pp = 1.0;
        for (int it = 0; it < 100; it++) {
            double p1 = 1.0, p2 = 0.0;
            for (int j = 1; j <= n; j++) {          // recurrencia de Legendre
                double p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3) / j;
            }
            pp = n * (z * p1 - p2) / (z * z - 1.0);  // derivada P_n'(z)
            double z1 = z;
            z = z1 - p1 / pp;
            if (fabs(z - z1) < 1e-15) break;
        }
        x[i] = -z;
        x[n - 1 - i] = z;
        w[i] = 2.0 / ((1.0 - z * z) * pp * pp);
        w[n - 1 - i] = w[i];
    }
}
#endif // MC_FN_gauss_legendre_nodos

#ifndef MC_FN_gauss_legendre_func
#define MC_FN_gauss_legendre_func
// Cuadratura gaussiana (Gauss-Legendre) de una función en [a,b]
// Descripción: Cambio de variable z = ((b-a)*x + b + a)/2 y suma ponderada de 'n' evaluaciones. Muy precisa con pocas evaluaciones si f es suave.
double gauss_legendre_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = gauss_legendre_func(sin, 0.0, PI(15)/2, 2);   // 0.99847 (exacto: 1)
    */
    if (n < 1) { print_error_int("gauss_legendre_func: n debe ser >= 1", n); return MC_NAN; }
    double *x, *w;
    gauss_legendre_nodos(n, x, w);
    double mitad = (b - a) / 2.0, centro = (b + a) / 2.0, suma = 0.0;
    for (int i = 0; i < n; i++) suma += w[i] * f(mitad * x[i] + centro);
    delete[] x; delete[] w;
    return mitad * suma;
}
#endif // MC_FN_gauss_legendre_func

#ifndef MC_FN_pesos_nc
#define MC_FN_pesos_nc
// Pesos de Newton-Cotes compuestas
// Descripción: Devuelve los n+1 pesos para 'n' subintervalos de longitud h. regla = 1 (trapecio), 2 (Simpson 1/3, n par) o 3 (Simpson 3/8, n multiplo de 3).
// Sirve para escribir una integral como suma ponderada sum(w_i*f(x_i)) y extenderla a integrales multiples.
double* pesos_nc(int n, int regla, double h) {
    /*
    Ejemplo de uso:
        double *w = pesos_nc(4, 2, 0.5);   // h/3*{1,4,2,4,1}
    */
    if (n < 1) { print_error_int("pesos_nc: n debe ser >= 1", n); return NULL; }
    if (regla == 2 && n % 2 != 0) { print_error_int("pesos_nc: Simpson 1/3 necesita n par", n); return NULL; }
    if (regla == 3 && n % 3 != 0) { print_error_int("pesos_nc: Simpson 3/8 necesita n multiplo de 3", n); return NULL; }
    if (regla < 1 || regla > 3) { print_error_int("pesos_nc: regla debe ser 1, 2 o 3", regla); return NULL; }
    double *w = new double[n + 1];
    for (int i = 0; i <= n; i++) {
        bool extremo = (i == 0 || i == n);
        if (regla == 1)      w[i] = (extremo ? 1.0 : 2.0) * h / 2.0;
        else if (regla == 2) w[i] = (extremo ? 1.0 : ((i % 2 == 0) ? 2.0 : 4.0)) * h / 3.0;
        else                 w[i] = (extremo ? 1.0 : ((i % 3 == 0) ? 2.0 : 3.0)) * 3.0 * h / 8.0;
    }
    return w;
}
#endif // MC_FN_pesos_nc

#ifndef MC_FN_integral_doble_func
#define MC_FN_integral_doble_func
// Integral doble de una función f(x,y) sobre [ax,bx] x [ay,by]
// Descripción: Doble sumatoria sum_j sum_i wy[j]*wx[i]*f(x_i,y_j) con 'nx' y 'ny' subintervalos y la regla elegida en cada direccion (rx, ry = 1, 2 o 3 como en pesos_nc).
double integral_doble_func(double (*f)(double, double), double ax, double bx, double ay, double by,
                           int nx, int ny, int rx, int ry) {
    /*
    Ejemplo de uso:
        double g(double x, double y) { return x * y; }
        double I = integral_doble_func(g, 0, 2, 0, 3, 10, 10, 2, 2);   // 9
    */
    double hx = (bx - ax) / nx, hy = (by - ay) / ny;
    double *wx = pesos_nc(nx, rx, hx);
    double *wy = pesos_nc(ny, ry, hy);
    if (wx == NULL || wy == NULL) { delete[] wx; delete[] wy; return MC_NAN; }
    double suma = 0.0;
    for (int j = 0; j <= ny; j++)
        for (int i = 0; i <= nx; i++)
            suma += wy[j] * wx[i] * f(ax + i * hx, ay + j * hy);
    delete[] wx; delete[] wy;
    return suma;
}
#endif // MC_FN_integral_doble_func

#ifndef MC_FN_integral_triple_func
#define MC_FN_integral_triple_func
// Integral triple de una función f(x,y,z) sobre un paralelepipedo
// Descripción: Triple sumatoria con pesos w_ijk = a_i*b_j*c_k (nx, ny, nz subintervalos; reglas rx, ry, rz = 1, 2 o 3).
double integral_triple_func(double (*f)(double, double, double), double ax, double bx, double ay, double by,
                            double az, double bz, int nx, int ny, int nz, int rx, int ry, int rz) {
    /*
    Ejemplo de uso:
        double g(double x, double y, double z) { return x + y + z; }
        double I = integral_triple_func(g, 0, 1, 0, 1, 0, 1, 4, 4, 4, 2, 2, 2);   // 1.5
    */
    double hx = (bx - ax) / nx, hy = (by - ay) / ny, hz = (bz - az) / nz;
    double *wx = pesos_nc(nx, rx, hx);
    double *wy = pesos_nc(ny, ry, hy);
    double *wz = pesos_nc(nz, rz, hz);
    if (wx == NULL || wy == NULL || wz == NULL) { delete[] wx; delete[] wy; delete[] wz; return MC_NAN; }
    double suma = 0.0;
    for (int k = 0; k <= nz; k++)
        for (int j = 0; j <= ny; j++)
            for (int i = 0; i <= nx; i++)
                suma += wz[k] * wy[j] * wx[i] * f(ax + i * hx, ay + j * hy, az + k * hz);
    delete[] wx; delete[] wy; delete[] wz;
    return suma;
}
#endif // MC_FN_integral_triple_func

#ifndef MC_FN_integral_doble_mat
#define MC_FN_integral_doble_mat
// Integral doble de datos tabulados f(x_i, y_j) en una malla equiespaciada
// Descripción: F es una matriz (ny+1) x (nx+1) con F[j][i] = f(x_i, y_j). Aplica la regla rx en la direccion x y ry en la y (como el ejemplo de la teoria:
// trapecio en x y Simpson 1/3 en y).
double integral_doble_mat(double **F, int nx, int ny, double hx, double hy, int rx, int ry) {
    /*
    Ejemplo de uso:
        double I = integral_doble_mat(F, 3, 4, 0.5, 0.1, 1, 2);   // 4 puntos en x (trapecio) y 5 en y (Simpson 1/3)
    */
    double *wx = pesos_nc(nx, rx, hx);
    double *wy = pesos_nc(ny, ry, hy);
    if (wx == NULL || wy == NULL) { delete[] wx; delete[] wy; return MC_NAN; }
    double suma = 0.0;
    for (int j = 0; j <= ny; j++)
        for (int i = 0; i <= nx; i++)
            suma += wy[j] * wx[i] * F[j][i];
    delete[] wx; delete[] wy;
    return suma;
}
#endif // MC_FN_integral_doble_mat

#ifndef MC_FN_gauss_doble_func
#define MC_FN_gauss_doble_func
// Integral doble por cuadratura gaussiana
// Descripción: Usa 'nx' nodos de Gauss-Legendre en x y 'ny' en y (cada direccion puede tener un numero distinto de terminos).
double gauss_doble_func(double (*f)(double, double), double ax, double bx, double ay, double by, int nx, int ny) {
    /*
    Ejemplo de uso:
        double I = gauss_doble_func(g, 0, 2, 0, 3, 3, 3);   // 9
    */
    double *xn, *wx, *yn, *wy;
    gauss_legendre_nodos(nx, xn, wx);
    gauss_legendre_nodos(ny, yn, wy);
    double mx = (bx - ax) / 2.0, cx = (bx + ax) / 2.0, my = (by - ay) / 2.0, cy = (by + ay) / 2.0;
    double suma = 0.0;
    for (int j = 0; j < ny; j++)
        for (int i = 0; i < nx; i++)
            suma += wy[j] * wx[i] * f(mx * xn[i] + cx, my * yn[j] + cy);
    delete[] xn; delete[] wx; delete[] yn; delete[] wy;
    return mx * my * suma;
}
#endif // MC_FN_gauss_doble_func

#ifndef MC_FN_gauss_triple_func
#define MC_FN_gauss_triple_func
// Integral triple por cuadratura gaussiana
// Descripción: Usa nx, ny y nz nodos de Gauss-Legendre en cada direccion (ejemplo de la teoria: 3 terminos en x y 2 en y, z).
double gauss_triple_func(double (*f)(double, double, double), double ax, double bx, double ay, double by,
                         double az, double bz, int nx, int ny, int nz) {
    /*
    Ejemplo de uso:
        double I = gauss_triple_func(g3, 0, 1, 0, 1, 0, 1, 2, 2, 2);
    */
    double *xn, *wx, *yn, *wy, *zn, *wz;
    gauss_legendre_nodos(nx, xn, wx);
    gauss_legendre_nodos(ny, yn, wy);
    gauss_legendre_nodos(nz, zn, wz);
    double mx = (bx - ax) / 2.0, cx = (bx + ax) / 2.0;
    double my = (by - ay) / 2.0, cy = (by + ay) / 2.0;
    double mz = (bz - az) / 2.0, cz = (bz + az) / 2.0;
    double suma = 0.0;
    for (int k = 0; k < nz; k++)
        for (int j = 0; j < ny; j++)
            for (int i = 0; i < nx; i++)
                suma += wz[k] * wy[j] * wx[i] * f(mx * xn[i] + cx, my * yn[j] + cy, mz * zn[k] + cz);
    delete[] xn; delete[] wx; delete[] yn; delete[] wy; delete[] zn; delete[] wz;
    return mx * my * mz * suma;
}
#endif // MC_FN_gauss_triple_func

#endif // MATCLUB_INTEGRACION_CPP
