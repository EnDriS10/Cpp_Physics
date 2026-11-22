// ============================================================================
// MATCLUB-CPP  |  COMPLEMENTOS (fuera de los 5 bloques)
// Estadistica descriptiva
// ============================================================================
// Mediana, histogramas, covarianza, correlacion, percentiles y media movil.
//
// Funciones (7): median_vect, hist_vect, hist_auto_vect, cov_vect, corr_vect, percentil_vect, movmean_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ESTADISTICA_H
#define MATCLUB_ESTADISTICA_H

// Calcula la mediana del vector (el valor central)
double median_vect(double *a, int n);

// Histograma de Valores Únicos (Dominio Discreto Simplificado)
// Descripción: Extrae los valores únicos de 'datos', los ordena, y cuenta su frecuencia.
// Devuelve las frecuencias y guarda el dominio simplificado en 'dominio_out'. Actualiza 'n_out'.
double* hist_vect(double *datos, int n_datos, double *&dominio_out, int &n_out);

// Histograma Automático (Rango Continuo)
// Descripción: Agrupa los datos en 'n_bins' (barras) equiespaciadas entre el valor mínimo y máximo.
// Devuelve las frecuencias y guarda los centros de las barras en 'bins_out'.
double* hist_auto_vect(double *datos, int n_datos, int n_bins, double *&bins_out);

// Covarianza muestral entre dos vectores
// Descripcion: cov(a,b) = sum((ai-media_a)*(bi-media_b)) / (n-1). Necesita n >= 2.
double cov_vect(double *a, double *b, int n);

// Coeficiente de correlacion de Pearson entre dos vectores
// Descripcion: corr = cov(a,b) / (std(a)*std(b)). Devuelve un valor en [-1, 1].
double corr_vect(double *a, double *b, int n);

// Percentil p de un vector (interpolacion lineal entre datos ordenados)
// Descripcion: p en [0,100]. p=50 es la mediana, p=0 el minimo y p=100 el maximo. No modifica 'a'.
double percentil_vect(double *a, int n, double p);

// Media movil con ventana w (centrada; en los bordes la ventana se recorta)
double* movmean_vect(double *a, int n, int w);

#endif // MATCLUB_ESTADISTICA_H
