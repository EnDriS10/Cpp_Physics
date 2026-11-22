// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Numeros aleatorios
// ============================================================================
// Vectores aleatorios uniformes, enteros y normales, y generacion de muestras de una distribucion discreta.
//
// Funciones (5): rand_vect, randi_vect, randn_vect, randnorm_vect, gen_distrib_prob
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ALEATORIOS_H
#define MATCLUB_ALEATORIOS_H

// rand: Genera un vector con numeros aleatorios entre 0.0 y 1.0 uniformes
double* rand_vect(int n);

// randi: Genera un vector con numeros enteros aleatorios entre min y max
double* randi_vect(int min, int max, int n);

// randn: Genera distribucion normal estandar, media = 0, desviacion = 1 (Como randn en MATLAB)
double* randn_vect(int n);

// randnorm: Genera distribucion normal con la media (mu) y desviacion estandar (sigma) que elijas
double* randnorm_vect(double mu, double sigma, int n);

// Generador de variables aleatorias mediante distribución de probabilidad dada
// Descripción: Genera 'N' muestras aleatorias del 'dominio' basadas en sus 'probabilidades' asociadas.
double* gen_distrib_prob(double *dominio, double *probabilidades, int n_dom, int N);

#endif // MATCLUB_ALEATORIOS_H
