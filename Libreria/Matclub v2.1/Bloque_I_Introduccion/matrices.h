// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Matrices (arrays dinamicos 2D)
// ============================================================================
// Creacion, copia, operaciones basicas, producto, traspuesta, submatrices, filas/columnas, diagonales, busqueda, aleatorias, entrada y salida.
//
// Funciones (43): gen_mat, del_mat, prod_mat, input_mat, print_mat, coppy_mat, transpose_mat, zeros_mat, ones_mat, eye_mat, prod_esc_mat, trace_mat, get_row_mat, get_col_mat, suma_mat, resta_mat, prodeach_mat, sub_mat, horzcat_mat, vertcat_mat, flatten_mat, funeach_mat, apply_scalar_vect, apply_scalar_mat, remove_row_col_mat, is_symmetric_mat, swap_rows_mat, swap_cols_mat, find_val_mat, find_gt_mat, sum_all_mat, prod_all_mat, max_mat, max_abs_mat, min_mat, rand_mat, randi_mat, randn_mat, clamp_mat, reshape_mat, diag_mat, get_diag_mat, prod_mat_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_MATRICES_H
#define MATCLUB_MATRICES_H

//Crear Matriz
double** gen_mat(double **M, int f, int c);

//Borrar Matriz
void del_mat(double **M, int f);

// Multiplicación de matrices (A de fa x ca, B de fb x cb)
double** prod_mat(double **A, double **B, int fa, int ca, int fb, int cb);

// Introducir matriz por teclado
double** input_mat(int f, int c);

// Imprimir matriz
void print_mat(double **M, int f, int c, const char* nombre = "ans");

//Copiar la matriz
double** coppy_mat(double **M, int f, int c);

//Matriz Transpuesta
double** transpose_mat(double **A, int fa, int ca);

// Matriz de ceros (f x c)
double** zeros_mat(int f, int c);

// Matriz de unos (f x c)
double** ones_mat(int f, int c);

// Matriz Identidad (n x n), eye(n) en MATLAB
double** eye_mat(int n);

// Producto de matriz por escalar
double** prod_esc_mat(double **A, double k, int f, int c);

// Traza de una matriz cuadrada (suma de la diagonal principal)
double trace_mat(double **A, int n);

// Extrae la fila 'fila_idx' de una matriz y la devuelve como un vector dinámico 1D
//Importante: LOS CONVIERTE EN UN POINTER, VECT EN ESTA LIBRERIA
double* get_row_mat(double **A, int f, int c, int fila_idx);

// Extrae la columna 'col_idx' de una matriz y la devuelve como un vector dinámico 1D
//Importante: LOS CONVIERTE EN UN POINTER, VECT EN ESTA LIBRERIA
double* get_col_mat(double **A, int f, int c, int col_idx);

// Suma de matrices (A + B)
double** suma_mat(double **A, double **B, int f, int c);

// Resta de matrices (A - B)
double** resta_mat(double **A, double **B, int f, int c);

// Producto celda a celda (A .* B en MATLAB)
double** prodeach_mat(double **A, double **B, int f, int c);

// Extrae una submatriz desde (f_ini, c_ini) hasta (f_fin, c_fin)
double** sub_mat(double **A, int f_ini, int f_fin, int c_ini, int c_fin);

// Une dos matrices lado a lado: [A, B]
double** horzcat_mat(double **A, int fa, int ca, double **B, int fb, int cb);

// Apila una matriz sobre otra: [A; B]
double** vertcat_mat(double **A, int fa, int ca, double **B, int fb, int cb);

// Convierte una matriz en un vector 1D (como A(:) en MATLAB, orden columna por columna)
double* flatten_mat(double **A, int f, int c, int &n_out);

// Función maestra para matrices usando un puntero a una función de vectores
double** funeach_mat(double **A, int f, int c, double* (*vec_func)(double*, int));

// Aplica una función matemática de <cmath> a cada elemento de un vector
double* apply_scalar_vect(double *a, int n, double (*func)(double));

// Aplica una función matemática de <cmath> a cada elemento de una matriz
double** apply_scalar_mat(double **A, int f, int c, double (*func)(double));

// Devuelve una nueva matriz eliminando la fila 'f_del' y la columna 'c_del'
double** remove_row_col_mat(double **A, int f, int c, int f_del, int c_del);

// Comprueba si una matriz cuadrada es simétrica
bool is_symmetric_mat(double **A, int n, double tolerancia);

// Intercambia la fila r1 con la fila r2 (devuelve una nueva matriz)
double** swap_rows_mat(double **A, int f, int c, int r1, int r2);

// Intercambia la columna c1 con la columna c2 (devuelve una nueva matriz)
double** swap_cols_mat(double **A, int f, int c, int c1, int c2);

// Busca un valor en la matriz y devuelve su posición (fila y columna) por referencia
// Retorna true si lo encuentra, false si no está en la matriz
//Poniendo tolerencia a 0 pues es excatamente ese valor
bool find_val_mat(double **A, int f, int c, double val, int &out_f, int &out_c, double tolerancia);

// find_mat: Encuentra las coordenadas (filas y columnas) donde los elementos son mayores que un umbral
// Devuelve una matriz de n_out x 2 donde cada fila es [fila, columna]
double** find_gt_mat(double **A, int f, int c, double umbral, int &n_out);

// Suma de todos los elementos de la matriz
double sum_all_mat(double **A, int f, int c);

// Producto de todos los elementos de la matriz
double prod_all_mat(double **A, int f, int c);

// Devuelve el valor máximo absoluto de toda la matriz
double max_mat(double **A, int f, int c);

// Valor maximo en valor absoluto de la matriz (este SI es absoluto)
double max_abs_mat(double **A, int f, int c);

// Devuelve el valor mínimo absoluto de toda la matriz
double min_mat(double **A, int f, int c);

// Genera una matriz (f x c) con números aleatorios uniformes entre 0.0 y 1.0 (rand(f,c) en MATLAB)
double** rand_mat(int f, int c);

// randi_mat: Genera una matriz (f x c) con enteros aleatorios entre min y max
double** randi_mat(int min_val, int max_val, int f, int c);

// Genera una matriz (f x c) con distribución normal estándar (randn(f,c) en MATLAB)
double** randn_mat(int f, int c);

// Limita los valores de una matriz entre un mínimo y un máximo
double** clamp_mat(double **A, int f, int c, double min_val, double max_val);

// reshape: Reorganiza los datos de una matriz en una nueva de dimensiones (nuevo_f x nuevo_c)
double** reshape_mat(double **A, int f, int c, int nuevo_f, int nuevo_c);

// Matriz diagonal n x n a partir de un vector, diag(v) en MATLAB
double** diag_mat(double *v, int n);

// Extrae la diagonal principal de una matriz cuadrada como vector
double* get_diag_mat(double **A, int n);

// Producto matriz x vector: y = A*x  (A de f x c, x de tamano n = c)
double* prod_mat_vect(double **A, int f, int c, double *x, int n);

#endif // MATCLUB_MATRICES_H
