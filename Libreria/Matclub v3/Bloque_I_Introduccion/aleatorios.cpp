// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Numeros aleatorios
// ============================================================================
// Vectores aleatorios uniformes, enteros y normales, y generacion de muestras de una distribucion discreta.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "aleatorios.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (5): rand_vect, randi_vect, randn_vect, randnorm_vect, gen_distrib_prob
// Dependencias copiadas (2): PI, cumsum_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ALEATORIOS_CPP
#define MATCLUB_ALEATORIOS_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

// (copiada de: auxiliares)
#ifndef MC_FN_PI
#define MC_FN_PI
// Devuelve PI redondeado decimales 'n'
double PI(int n) {
    double base_pi = acos(-1.0);		double factor = pow(10.0, n);
    return round(base_pi * factor) / factor;
}
#endif // MC_FN_PI

// (copiada de: vectores)
#ifndef MC_FN_cumsum_vect
#define MC_FN_cumsum_vect
// Suma acumulativa
double* cumsum_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    double suma = 0.0; 
    for ( int i = 0; i<n ; i++){
        suma = suma + a[i];
        c[i] = suma;
    }   
    return c; 
}
#endif // MC_FN_cumsum_vect

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Numeros aleatorios
// ----------------------------------------------------------------------------

#ifndef MC_FN_rand_vect
#define MC_FN_rand_vect
// rand: Genera un vector con numeros aleatorios entre 0.0 y 1.0 uniformes
double* rand_vect(int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        // rand() genera enteros grandes, lo dividimos por el maximo para normalizar
        c[i] = (double)rand() / RAND_MAX;
    }   
    return c; 
}
#endif // MC_FN_rand_vect

#ifndef MC_FN_randi_vect
#define MC_FN_randi_vect
// randi: Genera un vector con numeros enteros aleatorios entre min y max
double* randi_vect(int min, int max, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = min + rand() % ((max + 1) - min);
    }   
    return c; 
}
#endif // MC_FN_randi_vect

#ifndef MC_FN_randn_vect
#define MC_FN_randn_vect
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
#endif // MC_FN_randn_vect

#ifndef MC_FN_randnorm_vect
#define MC_FN_randnorm_vect
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
#endif // MC_FN_randnorm_vect

#ifndef MC_FN_gen_distrib_prob
#define MC_FN_gen_distrib_prob
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
#endif // MC_FN_gen_distrib_prob

#endif // MATCLUB_ALEATORIOS_CPP
