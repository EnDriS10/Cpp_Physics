// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Ordenacion de vectores (Introsort)
// ============================================================================
// Introsort = quicksort + heapsort + insercion, y la ordenacion con la libreria estandar.
//
// Funciones (7): insertion_sort, heapify, heapsort_util, partition, introsort_util, sort_vect, sort_vect_algorithm
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ORDENACION_H
#define MATCLUB_ORDENACION_H

// 1. Insertion Sort (Se activa cuando el sub-arreglo tiene menos de 16 elementos)
void insertion_sort(double *arr, int left, int right);

// 2. Funciones para Heap Sort (Se activan si Quicksort entra en su peor caso)
void heapify(double *arr, int n, int i, int offset);

void heapsort_util(double *arr, int left, int right);

// 3. Partition (El núcleo de Quicksort)
int partition(double *arr, int left, int right);

// 4. Lógica central de Introsort
void introsort_util(double *arr, int left, int right, int depth_limit);

//FUNCION FINAL INTROSORT
double* sort_vect(double *a, int n);

//FUNCION SORT USANDO ALGORITHM
double* sort_vect_algorithm(double *a, int n);

#endif // MATCLUB_ORDENACION_H
