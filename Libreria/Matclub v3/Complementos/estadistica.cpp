// ============================================================================
// MATCLUB-CPP  |  COMPLEMENTOS (fuera de los 5 bloques)
// Estadistica descriptiva
// ============================================================================
// Mediana, histogramas, covarianza, correlacion, percentiles y media movil.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "estadistica.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (7): median_vect, hist_vect, hist_auto_vect, cov_vect, corr_vect, percentil_vect, movmean_vect
// Dependencias copiadas (15): MC_NAN, print_error, intercambiar_elem, zeros_vect, sum_elems, mean_vect, max_vect, min_vect, std_vect, insertion_sort, heapify, heapsort_util, partition, introsort_util, sort_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ESTADISTICA_CPP
#define MATCLUB_ESTADISTICA_CPP

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

// (copiada de: auxiliares)
#ifndef MC_FN_intercambiar_elem
#define MC_FN_intercambiar_elem
//Intercambia dos elementos
void intercambiar_elem(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}
#endif // MC_FN_intercambiar_elem

// (copiada de: vectores)
#ifndef MC_FN_zeros_vect
#define MC_FN_zeros_vect
//Array de 0s   
    double* zeros_vect(int n) { 
    	double *c ;        c = new double [n]();
    return c; 
}
#endif // MC_FN_zeros_vect

// (copiada de: vectores)
#ifndef MC_FN_sum_elems
#define MC_FN_sum_elems
// Suma total de cada elemento del vector.
double sum_elems(double *a, int n) { 
    double suma = 0; 
    for ( int i = 0; i<n ; i++){
        suma = suma + a[i];
    }   
    return suma; 
}
#endif // MC_FN_sum_elems

// (copiada de: vectores)
#ifndef MC_FN_mean_vect
#define MC_FN_mean_vect
// Media del vect
double mean_vect(double *a, int n) { 
    double mean;
    mean = sum_elems(a, n) / n;   
    return mean; 
}
#endif // MC_FN_mean_vect

// (copiada de: vectores)
#ifndef MC_FN_max_vect
#define MC_FN_max_vect
// Elemento Maximo del vector
double max_vect(double *a, int n) { 
    double max_v = a[0]; 
    for ( int i = 1; i<n ; i++){
        if(a[i] > max_v) {
            max_v = a[i];
        }
    }   
    return max_v; 
}
#endif // MC_FN_max_vect

// (copiada de: vectores)
#ifndef MC_FN_min_vect
#define MC_FN_min_vect
// Elemento Minimo del vector
double min_vect(double *a, int n) { 
    double min_v = a[0]; 
    for ( int i = 1; i<n ; i++){
        if(a[i] < min_v) {
            min_v = a[i];
        }
    }   
    return min_v; 
}
#endif // MC_FN_min_vect

// (copiada de: vectores)
#ifndef MC_FN_std_vect
#define MC_FN_std_vect
// Desviacion Estandar del Vect
double std_vect(double *a, int n) { 
    double mean = mean_vect(a, n);
    double sum_sq = 0; 
    for ( int i = 0; i<n ; i++){
        sum_sq = sum_sq + pow((a[i] - mean), 2);
    }   
    return sqrt(sum_sq / (n - 1)); 
}
#endif // MC_FN_std_vect

// (copiada de: ordenacion)
#ifndef MC_FN_insertion_sort
#define MC_FN_insertion_sort
// 1. Insertion Sort (Se activa cuando el sub-arreglo tiene menos de 16 elementos)
void insertion_sort(double *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        double key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
#endif // MC_FN_insertion_sort

// (copiada de: ordenacion)
#ifndef MC_FN_heapify
#define MC_FN_heapify
// 2. Funciones para Heap Sort (Se activan si Quicksort entra en su peor caso)
void heapify(double *arr, int n, int i, int offset) {
    int largest = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    if (left_child < n && arr[offset + left_child] > arr[offset + largest])
        largest = left_child;

    if (right_child < n && arr[offset + right_child] > arr[offset + largest])
        largest = right_child;

    if (largest != i) {
        intercambiar_elem(arr[offset + i], arr[offset + largest]);
        heapify(arr, n, largest, offset);
    }
}
#endif // MC_FN_heapify

// (copiada de: ordenacion)
#ifndef MC_FN_heapsort_util
#define MC_FN_heapsort_util
void heapsort_util(double *arr, int left, int right) {
    int n = right - left + 1;
    // Construir Max-Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, left);
    // Extraer elementos
    for (int i = n - 1; i > 0; i--) {
        intercambiar_elem(arr[left], arr[left + i]);
        heapify(arr, i, 0, left);
    }
}
#endif // MC_FN_heapsort_util

// (copiada de: ordenacion)
#ifndef MC_FN_partition
#define MC_FN_partition
// 3. Partition (El núcleo de Quicksort)
int partition(double *arr, int left, int right) {
    double pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            intercambiar_elem(arr[i], arr[j]);
        }
    }
    intercambiar_elem(arr[i + 1], arr[right]);
    return i + 1;
}
#endif // MC_FN_partition

// (copiada de: ordenacion)
#ifndef MC_FN_introsort_util
#define MC_FN_introsort_util
// 4. Lógica central de Introsort
void introsort_util(double *arr, int left, int right, int depth_limit) {
    int size = right - left + 1;
    
    // Condición 1: Sub-arreglo pequeño -> Insertion Sort
    if (size < 16) {
        insertion_sort(arr, left, right);
        return;
    }
    
    // Condición 2: Exceso de recursión -> Heapsort
    if (depth_limit == 0) {
        heapsort_util(arr, left, right);
        return;
    }
    
    // Condición 3: Operación normal -> Quicksort
    int pivot = partition(arr, left, right);
    introsort_util(arr, left, pivot - 1, depth_limit - 1);
    introsort_util(arr, pivot + 1, right, depth_limit - 1);
}
#endif // MC_FN_introsort_util

// (copiada de: ordenacion)
#ifndef MC_FN_sort_vect
#define MC_FN_sort_vect
//FUNCION FINAL INTROSORT
double* sort_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = a[i];
    }   
    
    if (n > 1) {
        // El límite de profundidad matemático es 2 * log2(n)
        int depth_limit = 2 * (log(n) / log(2.0)); 
        introsort_util(c, 0, n - 1, depth_limit);
    }
    
    return c; 
}
#endif // MC_FN_sort_vect

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Estadistica descriptiva
// ----------------------------------------------------------------------------

#ifndef MC_FN_median_vect
#define MC_FN_median_vect
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
#endif // MC_FN_median_vect

#ifndef MC_FN_hist_vect
#define MC_FN_hist_vect
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
#endif // MC_FN_hist_vect

#ifndef MC_FN_hist_auto_vect
#define MC_FN_hist_auto_vect
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
#endif // MC_FN_hist_auto_vect

#ifndef MC_FN_cov_vect
#define MC_FN_cov_vect
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
#endif // MC_FN_cov_vect

#ifndef MC_FN_corr_vect
#define MC_FN_corr_vect
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
#endif // MC_FN_corr_vect

#ifndef MC_FN_percentil_vect
#define MC_FN_percentil_vect
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
#endif // MC_FN_percentil_vect

#ifndef MC_FN_movmean_vect
#define MC_FN_movmean_vect
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
#endif // MC_FN_movmean_vect

#endif // MATCLUB_ESTADISTICA_CPP
