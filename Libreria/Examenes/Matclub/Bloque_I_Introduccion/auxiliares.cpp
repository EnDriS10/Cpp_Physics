// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Funciones auxiliares y aritmetica basica
// ============================================================================
// Constantes (PI, PHI, MC_NAN), comprobaciones (NaN, primos, rangos), maximo/minimo, factorial, combinatorios, mcd/mcm y conversion de angulos.
//
// Funciones (16): intercambiar_elem, isNaN, isRoot, is_in_range, clamp, deg2rad, rad2deg, max2, min2, factorial, comb, mcd_int, mcm_int, is_prime, PI, PHI
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const double MC_NAN = sqrt(-1.0);

//Intercambia dos elementos

void intercambiar_elem(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}

bool isNaN(double v) {
    return v != v; // En norma IEEE 754, NaN es distinto de sí mismo
}

bool isRoot(const double* raices, int n, double r, double tol) {
    for (int i = 0; i < n; ++i) {
        if (fabs(raices[i] - r) < tol) return true;
    }
    return false;
}

// Comprueba si un número está dentro de un rango [min, max] con tolerancia

bool is_in_range(double val, double min_val, double max_val) {
    return (val >= min_val && val <= max_val);
}

// Limita un valor escalar entre un mínimo y un máximo (clamp escalar)

double clamp(double val, double min_val, double max_val) {
    if (val < min_val) return min_val;
    if (val > max_val) return max_val;
    return val;
}

// Grados <-> radianes

double deg2rad(double g) { return g * acos(-1.0) / 180.0; }

double rad2deg(double r) { return r * 180.0 / acos(-1.0); }

// Maximo y minimo de dos numeros (evita choques con macros max/min de Windows)

double max2(double a, double b) { return (a > b) ? a : b; }

double min2(double a, double b) { return (a < b) ? a : b; }

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

// Combinatoria (n en k)
	// Descripción: Calcula el número de combinaciones posibles de 'k' elementos elegidos de un conjunto de 'n'.

double comb(int n, int k) {
    if (k < 0 || k > n) return 0.0;
    if (k > n - k) k = n - k;
    double r = 1.0;
    for (int i = 1; i <= k; i++) r = r * (n - k + i) / i;
    return round(r);
}

// Maximo comun divisor y minimo comun multiplo (enteros)

long mcd_int(long a, long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) { long t = a % b; a = b; b = t; }
    return a;
}

long mcm_int(long a, long b) {
    if (a == 0 || b == 0) return 0;
    long r = a / mcd_int(a, b) * b;
    return (r < 0) ? -r : r;
}

// Numero primo

bool is_prime(long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return (n == 2);
    for (long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Devuelve PI redondeado decimales 'n'

double PI(int n) {
    double base_pi = acos(-1.0);		double factor = pow(10.0, n);
    return round(base_pi * factor) / factor;
}

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

