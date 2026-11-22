// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Funciones auxiliares y aritmetica basica
// ============================================================================
// Constantes (PI, PHI, MC_NAN), comprobaciones (NaN, primos, rangos), maximo/minimo, factorial, combinatorios, mcd/mcm y conversion de angulos.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "auxiliares.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (16): intercambiar_elem, isNaN, isRoot, is_in_range, clamp, deg2rad, rad2deg, max2, min2, factorial, comb, mcd_int, mcm_int, is_prime, PI, PHI
// Dependencias copiadas (2): MC_NAN, print_error
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_AUXILIARES_CPP
#define MATCLUB_AUXILIARES_CPP

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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Funciones auxiliares y aritmetica basica
// ----------------------------------------------------------------------------

#ifndef MC_FN_intercambiar_elem
#define MC_FN_intercambiar_elem
//Intercambia dos elementos
void intercambiar_elem(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}
#endif // MC_FN_intercambiar_elem

#ifndef MC_FN_isNaN
#define MC_FN_isNaN
bool isNaN(double v) {
    return v != v; // En norma IEEE 754, NaN es distinto de sí mismo
}
#endif // MC_FN_isNaN

#ifndef MC_FN_isRoot
#define MC_FN_isRoot
bool isRoot(const double* raices, int n, double r, double tol) {
    for (int i = 0; i < n; ++i) {
        if (fabs(raices[i] - r) < tol) return true;
    }
    return false;
}
#endif // MC_FN_isRoot

#ifndef MC_FN_is_in_range
#define MC_FN_is_in_range
// Comprueba si un número está dentro de un rango [min, max] con tolerancia
bool is_in_range(double val, double min_val, double max_val) {
    return (val >= min_val && val <= max_val);
}
#endif // MC_FN_is_in_range

#ifndef MC_FN_clamp
#define MC_FN_clamp
// Limita un valor escalar entre un mínimo y un máximo (clamp escalar)
double clamp(double val, double min_val, double max_val) {
    if (val < min_val) return min_val;
    if (val > max_val) return max_val;
    return val;
}
#endif // MC_FN_clamp

#ifndef MC_FN_deg2rad
#define MC_FN_deg2rad
// Grados <-> radianes
double deg2rad(double g) { return g * acos(-1.0) / 180.0; }
#endif // MC_FN_deg2rad

#ifndef MC_FN_rad2deg
#define MC_FN_rad2deg
double rad2deg(double r) { return r * 180.0 / acos(-1.0); }
#endif // MC_FN_rad2deg

#ifndef MC_FN_max2
#define MC_FN_max2
// Maximo y minimo de dos numeros (evita choques con macros max/min de Windows)
double max2(double a, double b) { return (a > b) ? a : b; }
#endif // MC_FN_max2

#ifndef MC_FN_min2
#define MC_FN_min2
double min2(double a, double b) { return (a < b) ? a : b; }
#endif // MC_FN_min2

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

#ifndef MC_FN_comb
#define MC_FN_comb
// Combinatoria (n en k)
	// Descripción: Calcula el número de combinaciones posibles de 'k' elementos elegidos de un conjunto de 'n'.
double comb(int n, int k) {
    if (k < 0 || k > n) return 0.0;
    if (k > n - k) k = n - k;
    double r = 1.0;
    for (int i = 1; i <= k; i++) r = r * (n - k + i) / i;
    return round(r);
}
#endif // MC_FN_comb

#ifndef MC_FN_mcd_int
#define MC_FN_mcd_int
// Maximo comun divisor y minimo comun multiplo (enteros)
long mcd_int(long a, long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) { long t = a % b; a = b; b = t; }
    return a;
}
#endif // MC_FN_mcd_int

#ifndef MC_FN_mcm_int
#define MC_FN_mcm_int
long mcm_int(long a, long b) {
    if (a == 0 || b == 0) return 0;
    long r = a / mcd_int(a, b) * b;
    return (r < 0) ? -r : r;
}
#endif // MC_FN_mcm_int

#ifndef MC_FN_is_prime
#define MC_FN_is_prime
// Numero primo
bool is_prime(long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return (n == 2);
    for (long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
#endif // MC_FN_is_prime

#ifndef MC_FN_PI
#define MC_FN_PI
// Devuelve PI redondeado decimales 'n'
double PI(int n) {
    double base_pi = acos(-1.0);		double factor = pow(10.0, n);
    return round(base_pi * factor) / factor;
}
#endif // MC_FN_PI

#ifndef MC_FN_PHI
#define MC_FN_PHI
// Devuelve el numero aureo (1+sqrt(5))/2 redondeado a 'n' decimales
// Descripcion: Igual que PI(n). Se usa en seccion_aurea (el factor de reduccion es 1/PHI = PHI-1).
double PHI(int n) {
    /*
    Ejemplo de uso:
        double fi = PHI(6); // Devuelve 1.618034
    */
    double base_phi = (1.0 + sqrt(5.0)) / 2.0;
    double factor = pow(10.0, n);
    return round(base_phi * factor) / factor;
}
#endif // MC_FN_PHI

#endif // MATCLUB_AUXILIARES_CPP
