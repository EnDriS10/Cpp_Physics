// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Ordenacion de vectores (Introsort)
// ============================================================================
// Introsort = quicksort + heapsort + insercion, y la ordenacion con la libreria estandar.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "ordenacion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (7): insertion_sort, heapify, heapsort_util, partition, introsort_util, sort_vect, sort_vect_algorithm
// Dependencias copiadas (1): intercambiar_elem
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ORDENACION_CPP
#define MATCLUB_ORDENACION_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <algorithm>   // solo para sort_vect_algorithm

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Ordenacion de vectores (Introsort)
// ----------------------------------------------------------------------------

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

#ifndef MC_FN_sort_vect_algorithm
#define MC_FN_sort_vect_algorithm
//FUNCION SORT USANDO ALGORITHM
double* sort_vect_algorithm(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = a[i];
    }   
    sort(c, c + n); // Aplica introsort directo sobre los punteros
    return c; 
}
#endif // MC_FN_sort_vect_algorithm

#endif // MATCLUB_ORDENACION_CPP
