// ============================================================================
// MATCLUB-CPP  |  COMPLEMENTOS (fuera de los 5 bloques)
// Estadistica descriptiva
// ============================================================================
// Mediana, histogramas, covarianza, correlacion, percentiles y media movil.
//
// Funciones (7): median_vect, hist_vect, hist_auto_vect, cov_vect, corr_vect, percentil_vect, movmean_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Calcula la mediana del vector (el valor central)

double median_vect(double *a, int n) { 
    // Ordenamos el vector usando tu funcion Introsort
    double *sorted = sort_vect(a, n); 
    double med = 0.0;
    
    if (n % 2 == 0) {
        // Si es par, es el promedio de los dos centrales
        med = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    } else {
        // Si es impar, es el del medio exacto
        med = sorted[n / 2];
    }
    
    // IMPORTANTE: Como sort_vect hizo un 'new', tenemos que borrar el 
    // vector temporal 'sorted' aqui para no causar fuga de memoria.
    delete[] sorted; 
    
    return med; 
}

// Histograma de Valores Únicos (Dominio Discreto Simplificado)
// Descripción: Extrae los valores únicos de 'datos', los ordena, y cuenta su frecuencia.
// Devuelve las frecuencias y guarda el dominio simplificado en 'dominio_out'. Actualiza 'n_out'.

double* hist_vect(double *datos, int n_datos, double *&dominio_out, int &n_out) {
    /*
    Ejemplo de uso: (Sustituye a la función tabulate de MATLAB)
        double datos[] = {2, 2, 4, 4, 4, 7};
        double *dominio_simplificado;
        int n_unicos;
        
        double *frecuencias = hist_unique_vect(datos, 6, dominio_simplificado, n_unicos);
        
        // Resultado automático:
        // dominio_simplificado = [2, 4, 7]
        // frecuencias = [2, 3, 1]
        // n_unicos = 3
    */
    
    // Arrays temporales (el tamaño máximo posible es n_datos)
    double *temp_dom = new double[n_datos];
    int *temp_freq = new int[n_datos](); // Inicializado a 0
    int unicos = 0;

    // 1. Extraer el dominio único y contar apariciones
    for (int i = 0; i < n_datos; i++) {
        bool encontrado = false;
        for (int j = 0; j < unicos; j++) {
            if (fabs(datos[i] - temp_dom[j]) < 1e-8) { // Si ya existe en el dominio
                temp_freq[j]++;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            temp_dom[unicos] = datos[i];
            temp_freq[unicos] = 1;
            unicos++;
        }
    }

    // 2. Ordenar el dominio de menor a mayor (sincronizando las frecuencias)
    for (int i = 0; i < unicos - 1; i++) {
        for (int j = i + 1; j < unicos; j++) {
            if (temp_dom[j] < temp_dom[i]) {
                // Intercambiar dominio
                double tmp_d = temp_dom[i];
                temp_dom[i] = temp_dom[j];
                temp_dom[j] = tmp_d;
                // Intercambiar frecuencia
                int tmp_f = temp_freq[i];
                temp_freq[i] = temp_freq[j];
                temp_freq[j] = tmp_f;
            }
        }
    }

    // 3. Pasar a los arrays dinámicos definitivos con el tamaño exacto
    n_out = unicos;
    dominio_out = new double[unicos];
    double *frecuencias = new double[unicos];

    for (int i = 0; i < unicos; i++) {
        dominio_out[i] = temp_dom[i];
        frecuencias[i] = (double)temp_freq[i];
    }

    delete[] temp_dom;
    delete[] temp_freq;

    return frecuencias;
}

// Histograma Automático (Rango Continuo)
// Descripción: Agrupa los datos en 'n_bins' (barras) equiespaciadas entre el valor mínimo y máximo.
// Devuelve las frecuencias y guarda los centros de las barras en 'bins_out'.

double* hist_auto_vect(double *datos, int n_datos, int n_bins, double *&bins_out) {
    /*
    Ejemplo de uso: // Equivalente exacto a [v, x] = hist(datos, 10) en MATLAB
        double *x_centros;
        // Genera 10 barras automáticamente a partir de los datos
        double *frecuencias = hist_auto_vect(datos, n_datos, 10, x_centros);
        
        print_vect(x_centros, 10, "Dominio (Centros)");
        print_vect(frecuencias, 10, "Frecuencias (v)");
    */
    
    // Utilizamos tus funciones min_vect y max_vect previas
    double val_min = min_vect(datos, n_datos);
    double val_max = max_vect(datos, n_datos);
    
    // Si todos los datos son iguales, evitamos dividir por cero
    if (val_max == val_min) {
        val_max += 0.5;
        val_min -= 0.5;
    }
    
    bins_out = new double[n_bins];
    double *frecuencias = zeros_vect(n_bins); // Inicializa a 0
    double paso = (val_max - val_min) / n_bins;
    
    // 1. Calcular los centros exactos de cada barra (dominio simplificado)
    for (int i = 0; i < n_bins; i++) {
        bins_out[i] = val_min + (paso / 2.0) + (i * paso);
    }
    
    // 2. Llenar las frecuencias con cálculo matemático directo (más eficiente que los bucles fabs)
    for (int i = 0; i < n_datos; i++) {
        // Encontramos el índice de la barra correspondiente por proporción
        int idx = (int)((datos[i] - val_min) / paso);
        
        // Corrección de seguridad para el valor máximo exacto
        if (idx >= n_bins) {
            idx = n_bins - 1;
        } else if (idx < 0) {
            idx = 0;
        }
        
        frecuencias[idx] += 1.0;
    }
    
    return frecuencias;
}

// Covarianza muestral entre dos vectores
// Descripcion: cov(a,b) = sum((ai-media_a)*(bi-media_b)) / (n-1). Necesita n >= 2.

double cov_vect(double *a, double *b, int n) {
    /*
    Ejemplo de uso:
        double a[] = {1, 2, 3, 4, 5}, b[] = {2, 4, 6, 8, 10};
        double c = cov_vect(a, b, 5); // Devuelve 5.0
    */
    if (n < 2) { print_error("cov_vect: se necesitan al menos 2 datos"); return MC_NAN; }
    double ma = mean_vect(a, n), mb = mean_vect(b, n), s = 0.0;
    for (int i = 0; i < n; i++) s += (a[i] - ma) * (b[i] - mb);
    return s / (n - 1);
}

// Coeficiente de correlacion de Pearson entre dos vectores
// Descripcion: corr = cov(a,b) / (std(a)*std(b)). Devuelve un valor en [-1, 1].

double corr_vect(double *a, double *b, int n) {
    /*
    Ejemplo de uso:
        double r = corr_vect(a, b, 5); // 1.0 = relacion lineal perfecta, 0 = sin relacion lineal
    */
    double sa = std_vect(a, n), sb = std_vect(b, n);
    if (sa == 0.0 || sb == 0.0) { print_error("corr_vect: desviacion tipica nula (vector constante)"); return MC_NAN; }
    return cov_vect(a, b, n) / (sa * sb);
}

// Percentil p de un vector (interpolacion lineal entre datos ordenados)
// Descripcion: p en [0,100]. p=50 es la mediana, p=0 el minimo y p=100 el maximo. No modifica 'a'.

double percentil_vect(double *a, int n, double p) {
    /*
    Ejemplo de uso:
        double v[] = {1, 2, 3, 4, 5};
        double q = percentil_vect(v, 5, 90); // Devuelve 4.6
    */
    if (n < 1 || p < 0.0 || p > 100.0) { print_error("percentil_vect: datos vacios o p fuera de [0,100]"); return MC_NAN; }
    double *s = sort_vect(a, n);
    double pos = p / 100.0 * (n - 1);
    int i = (int)floor(pos);
    double fr = pos - i;
    double r = (i + 1 < n) ? s[i] + fr * (s[i + 1] - s[i]) : s[i];
    delete[] s;
    return r;
}

// Media movil con ventana w (centrada; en los bordes la ventana se recorta)

double* movmean_vect(double *a, int n, int w) {
    if (w < 1) {
        print_error("movmean_vect: la ventana debe ser >= 1");
        return NULL;
    }
    double *c = new double[n];
    int mitad = w / 2;
    for (int i = 0; i < n; i++) {
        int ini = (i - mitad < 0) ? 0 : i - mitad;
        int fin = (i + mitad >= n) ? n - 1 : i + mitad;
        double s = 0.0;
        for (int k = ini; k <= fin; k++) s += a[k];
        c[i] = s / (fin - ini + 1);
    }
    return c;
}

