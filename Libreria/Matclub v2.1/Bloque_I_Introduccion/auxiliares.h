// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Funciones auxiliares y aritmetica basica
// ============================================================================
// Constantes (PI, PHI, MC_NAN), comprobaciones (NaN, primos, rangos), maximo/minimo, factorial, combinatorios, mcd/mcm y conversion de angulos.
//
// Funciones (16): intercambiar_elem, isNaN, isRoot, is_in_range, clamp, deg2rad, rad2deg, max2, min2, factorial, comb, mcd_int, mcm_int, is_prime, PI, PHI
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_AUXILIARES_H
#define MATCLUB_AUXILIARES_H

// Constante NaN (definida en auxiliares.cpp)
extern const double MC_NAN;

//Intercambia dos elementos
void intercambiar_elem(double &a, double &b);

bool isNaN(double v);

bool isRoot(const double* raices, int n, double r, double tol);

// Comprueba si un número está dentro de un rango [min, max] con tolerancia
bool is_in_range(double val, double min_val, double max_val);

// Limita un valor escalar entre un mínimo y un máximo (clamp escalar)
double clamp(double val, double min_val, double max_val);

// Grados <-> radianes
double deg2rad(double g);

double rad2deg(double r);

// Maximo y minimo de dos numeros (evita choques con macros max/min de Windows)
double max2(double a, double b);

double min2(double a, double b);

// Factorial (devuelve double para llegar hasta 170!)
double factorial(int n);

// Combinatoria (n en k)
// Descripción: Calcula el número de combinaciones posibles de 'k' elementos elegidos de un conjunto de 'n'.
double comb(int n, int k);

// Maximo comun divisor y minimo comun multiplo (enteros)
long mcd_int(long a, long b);

long mcm_int(long a, long b);

// Numero primo
bool is_prime(long n);

// Devuelve PI redondeado decimales 'n'
double PI(int n);

// Devuelve el numero aureo (1+sqrt(5))/2 redondeado a 'n' decimales
// Descripcion: Igual que PI(n). Se usa en seccion_aurea (el factor de reduccion es 1/PHI = PHI-1).
double PHI(int n);

#endif // MATCLUB_AUXILIARES_H
