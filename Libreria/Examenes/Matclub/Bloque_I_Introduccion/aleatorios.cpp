// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Numeros aleatorios
// ============================================================================
// Vectores aleatorios uniformes, enteros y normales, y generacion de muestras de una distribucion discreta.
//
// Funciones (5): rand_vect, randi_vect, randn_vect, randnorm_vect, gen_distrib_prob
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// rand: Genera un vector con numeros aleatorios entre 0.0 y 1.0 uniformes

double* rand_vect(int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        // rand() genera enteros grandes, lo dividimos por el maximo para normalizar
        c[i] = (double)rand() / RAND_MAX;
    }   
    return c; 
}

// randi: Genera un vector con numeros enteros aleatorios entre min y max

double* randi_vect(int min, int max, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = min + rand() % ((max + 1) - min);
    }   
    return c; 
}

// randn: Genera distribucion normal estandar, media = 0, desviacion = 1 (Como randn en MATLAB)

double* randn_vect(int n) { 
    double *c ;        c = new double [n];		double PI_ = PI(20) ;
    for ( int i = 0; i<n ; i++){
        // Generamos dos numeros uniformes u1 y u2 en el intervalo (0, 1]
        // (Sumamos 1.0 para que nunca valga exactamente 0, ya que el log(0) da error)
        double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
        double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
        
        // Transformada matematica de Box-Muller (produce el valor Z)
        double z = sqrt(-2.0 * log(u1)) * cos(2.0 * PI_ * u2);
        
        c[i] = z;
    }   
    return c; 
}

// randnorm: Genera distribucion normal con la media (mu) y desviacion estandar (sigma) que elijas

double* randnorm_vect(double mu, double sigma, int n) { 
    double *c ;        c = new double [n];		double PI_ = PI(20) ;

    for ( int i = 0; i<n ; i++){
        double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
        double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
        
        // Transformada de Box-Muller
        double z = sqrt(-2.0 * log(u1)) * cos(2.0 * PI_ * u2);
        
        // Desplazamos y escalamos la campana de Gauss
        c[i] = mu + z * sigma;
    }   
    return c; 
}

// Generador de variables aleatorias mediante distribución de probabilidad dada
// Descripción: Genera 'N' muestras aleatorias del 'dominio' basadas en sus 'probabilidades' asociadas.

double* gen_distrib_prob(double *dominio, double *probabilidades, int n_dom, int N) {
    /*
    Ejemplo de uso:
        double dominio[] = {2, 4, 7, 8};
        double distrib_prob[] = {0.2, 0.1, 0.5, 0.2};
        double *muestras = gen_distrib_prob(dominio, distrib_prob, 4, 1000);
    */
    double *R = new double[N];
    double *prob_cum = cumsum_vect(probabilidades, n_dom); // Usa tu función ya programada
    
    for (int i = 0; i < N; i++) {
        // r es un aleatorio uniforme entre 0 y 1
        double r = (double)rand() / RAND_MAX;
        
        for (int j = 0; j < n_dom; j++) {
            if (r <= prob_cum[j]) {
                R[i] = dominio[j];
                break;
            }
        }
    }
    
    delete[] prob_cum;
    return R;
}

