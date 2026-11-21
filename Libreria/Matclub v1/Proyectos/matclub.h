// ============================================================================
// matclub.h - Cabecera (prototipos) de MATCLU-CPP
// ============================================================================
//Made by Cesar with a little(to much) help of my friends (Gema y Jose)
//
// USO:
//   - En matclub.cpp: poner #include "matclub.h" al principio y QUITAR los valores por
//     defecto de las definiciones (solo se escriben aqui, en la declaracion).
//   - En tu programa:  #include "matclub.h"  y compilar:  g++ main.cpp matclub.cpp -o main
// ============================================================================

#ifndef matclub_h
#define matclub_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

extern const double MC_NAN;

// ============================================================================
// FUNCIONES PARA IMPRIMIR MENSAJES
// ============================================================================

// Imprime un mensaje de error formateado al estilo de la libreria
void print_error(const char* mensaje, const char* detalle = NULL);

// Aviso: algo no fue perfecto pero el programa puede continuar
void print_warning(const char* mensaje, const char* detalle = NULL);

// Informacion (p. ej. "archivo guardado")
void print_info(const char* mensaje, const char* detalle = NULL);

// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor);

// Error de dimensiones: "mensaje (faxca) * (fbxcb)"
void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb);

// Linea separadora para ordenar la salida por pantalla
void print_line(int n = 40, char c = '=');

// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

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

// Minimo de una funcion unimodal por el metodo de la seccion aurea
// Descripcion: Reduce el intervalo [a,b] por el factor 1/PHI en cada paso, sin usar derivadas,
//              hasta que su longitud sea menor que 'tol'. Devuelve la posicion x del minimo.
double seccion_aurea(double (*f)(double), double a, double b, double tol);

// ============================================================================
// FUNCIONES DE VECTORES
// ============================================================================

// Libera un vector (para que se lea igual que del_mat)
void del_vect(double *a);

// Copia un vector
double* copy_vect(double *a, int n);

//Producto Punto
double prod_vect(double *a,double *b ,int n);

//Modulo Vectorial
double mod_vect(double *a,int n);

//Coseno de angulo entre vectores
double cos_ang_vect(double *a,double *b ,int n);

// Suma de Vectores
double* suma_vect(double *a,double *b ,int n);

// Resta de Vectores
double* resta_vect(double *a,double *b ,int n);

//Producto por un Escalar
double* prod_esc_vect(double *a,double k ,int n);

//Combinacion Lineal
double* lincomb_vect(double *a,double *b,double p, double q,int n);

//Producto de cada elemento (Proucto punto en matlab)
double* prodeach_vect(double *a,double *b,int n);

//Division de cada elemento (Division punto en matlab)
double* diveach_vect(double *a,double *b,int n);

//Exponencial de cada elemento
double* exp_vect(double *a,int n);

//Producto Cruz
double* prodx_vect(double *a, double *b, int n);

// Vector de n elementos todos iguales a 'val'
double* full_vect(int n, double val);

//Array de 0s
double* zeros_vect(int n);

//Array de 1s
double* ones_vect(int n);

//linspace de matlab
double* linspace(double start, double end, int n);

// logspace: n puntos espaciados logaritmicamente entre 10^start y 10^end
double* logspace(double start, double end, int n);

//arange funcion star:step:end de matlab. La variable n por referencia &
//para que la función calcule el tamaño y te lo devuelva al main
double* arange(double start, double step, double end, int &n);

//^p a cada elemento del vector.
double* pow_vect(double *a, double p, int n);

//sqrt a cada elemento del vector.
double* sqrt_vect(double *a, int n);

//abs a cada elemento del vector.
double* abs_vect(double *a, int n);

// sin a cada elemento del vector.
double* sin_vect(double *a, int n);

// cos a cada elemento del vector.
double* cos_vect(double *a, int n);

// tan a cada elemento del vector.
double* tan_vect(double *a, int n);

// sec a cada elemento del vector.
double* sec_vect(double *a, int n);

// csc a cada elemento del vector.
double* csc_vect(double *a, int n);

// cot a cada elemento del vector.
double* cot_vect(double *a, int n);

// arcoseno (asin)
double* asin_vect(double *a, int n);

// Arcocoseno (acos)
double* acos_vect(double *a, int n);

// Arcotangente (atan)
double* atan_vect(double *a, int n);

// Arcosecante (asec)
double* asec_vect(double *a, int n);

// Arcocosecante (acsc)
double* acsc_vect(double *a, int n);

// Arcocotangente (acot)
double* acot_vect(double *a, int n);

// log neperiano a cada elemento del vector.
double* log_vect(double *a, int n);

// log en base 10 a cada elemento del vector.
double* log10_vect(double *a, int n);

// Seno hiperbolico (sinh)
double* sinh_vect(double *a, int n);

// Coseno hiperbolico (cosh)
double* cosh_vect(double *a, int n);

// Tangente hiperbolica (tanh)
double* tanh_vect(double *a, int n);

// Arcoseno hiperbolico (asinh)
double* asinh_vect(double *a, int n);

// Arcocoseno hiperbolico (acosh)
double* acosh_vect(double *a, int n);

// Arcotangente hiperbolica (atanh)
double* atanh_vect(double *a, int n);

// Suma total de cada elemento del vector.
double sum_elems(double *a, int n);

// Suma acumulativa
double* cumsum_vect(double *a, int n);

// Producto total de cada elemento.
double prod_elems(double *a, int n);

// Producto acumulativo
double* cumprod_vect(double *a, int n);

// Media del vect
double mean_vect(double *a, int n);

// Elemento Maximo del vector
double max_vect(double *a, int n);

// Elemento Minimo del vector
double min_vect(double *a, int n);

// Desviacion Estandar del Vect
double std_vect(double *a, int n);

//Invertir el orden (Flip)
double* flip_vect(double *a, int n);

// Devuelve el INDICE donde se encuentra el valor maximo
int argmax_vect(double *a, int n);

// Devuelve el INDICE donde se encuentra el valor minimo
int argmin_vect(double *a, int n);

// Diferencias adyacentes (El vector devuelto tiene tamano n-1)
double* diff_vect(double *a, int n);

// Une el vector a (tamano n_a) con el vector b (tamano n_b)
double* concat_vect(double *a, int n_a, double *b, int n_b);

// Redondea hacia abajo
double* floor_vect(double *a, int n);

// Redondea hacia arriba
double* ceil_vect(double *a, int n);

// Redondea al entero mas cercano
double* round_vect(double *a, int n);

// Print Vector
void print_vect(double *a, int n, const char* nombre = "ans");

// Introducir vector por teclado
double* input_vect(int n);

// Normaliza un vector (lo divide entre su modulo)
double* normalize_vect(double *a, int n);

// Extrae el signo de cada elemento: devuelve 1, -1 o 0
double* sign_vect(double *a, int n);

// clamp: Limita los valores de un vector entre un minimo y un maximo
double* clamp_vect(double *a, int n, double min_val, double max_val);

// polyval: Evalua un polinomio p (grado np-1) en los puntos del vector x
// Ejemplo: p = [3, 2, 1] evalua 3*x^2 + 2*x + 1
double* polyval_vect(double *p, int np, double *x, int nx);

// polyval_scalar: Evalua un polinomio p en un UNICO punto escalar x
// Devuelve un escalar (el valor del polinomio evaluado en ese punto)
//Esta funcion ademas es una funcion que devuelve calquier vector
double polyval(double *p, int np, double x);

// Subvector desde ini hasta fin (ambos incluidos, indices desde 0). Como a(ini:fin) de MATLAB
double* slice_vect(double *a, int n, int ini, int fin);

// Suma un escalar a cada elemento (a + k en MATLAB)
double* sum_esc_vect(double *a, double k, int n);

// Varianza muestral (n-1)
double var_vect(double *a, int n);

// Proyeccion del vector a sobre el vector b: (a.b / b.b) * b
double* proj_vect(double *a, double *b, int n);

// ============================================================================
// FUNCIONES PARA INTROSORT (incluyendo Introsort)
// ============================================================================

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

// Calcula la mediana del vector (el valor central)
double median_vect(double *a, int n);

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

// find_gt: Devuelve los INDICES donde los elementos son mayores que un umbral
// La variable 'n_out' por referencia te dirá cuántos elementos cumplieron la condición
double* find_gt_vect(double *a, int n, double umbral, int &n_out);

// find generico: indices donde la funcion-condicion devuelve true
// Ejemplo:  bool es_negativo(double x){ return x < 0; }
//           double *idx = find_if_vect(v, n, es_negativo, k);
double* find_if_vect(double *a, int n, bool (*cond)(double), int &n_out);

// Media movil con ventana w (centrada; en los bordes la ventana se recorta)
double* movmean_vect(double *a, int n, int w);

// Cuenta cuantos elementos cumplen la condicion
int count_if_vect(double *a, int n, bool (*cond)(double));

// ============================================================================
// FUNCIONES DE MATRICES
// ============================================================================

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

// ============================================================================
// FUNCIONES DE MANIPULACION DE ARCHIVOS
// ============================================================================

// Comprueba si un archivo existe y se puede abrir
bool file_exists(const char* filename);

// Salta espacios y lineas de comentario que empiezan por '#' (cabeceras de gnuplot/numpy)
void skip_comments(std::ifstream &f);

// Cuenta TODAS las lineas de texto de un archivo (incluidas cabeceras y vacias)
int count_text_lines_file(const char* filename);

// Cuenta cuántas líneas (puntos) tiene un archivo de datos con 2 columnas
int count_lines_file(const char* filename);

// Lee un archivo de 2 columnas y carga los datos en los vectores dinámicos x e y preexistentes
void read_xy_file(const char* filename, double *x, double *y, int m);

// Guarda dos vectores x e y en un archivo de texto con dos columnas separadas por tabulador
void save_xy_file(const char* filename, double *x, double *y, int m);

// Guarda una matriz completa (f x c) en un archivo de texto tabulado
void save_mat_file(const char* filename, double **A, int f, int c);

// Lee una matriz de dimensiones conocidas (f x c) desde un archivo de texto
double** read_mat_file(const char* filename, int f, int c);

// Cuenta cuántos elementos (filas) tiene un archivo de una sola columna
int count_rows_single_file(const char* filename);

// Lee un archivo de una sola columna y lo devuelve como un vector dinámico 1D
double* read_single_vector_file(const char* filename, int &n_out);

// Guarda un vector dinámico 1D en un archivo de texto de una sola columna
void save_vector_file(const char* filename, double *v, int n);

// Cuenta el número de filas y columnas de un archivo de matriz desconocido sin usar sstream
bool get_file_dimensions(const char* filename, int &f_out, int &c_out);

// Lee una matriz SIN conocer sus dimensiones (las calcula con get_file_dimensions)
// Uso:  int f, c;  double **A = read_mat_auto("datos.txt", f, c);
double** read_mat_auto(const char* filename, int &f_out, int &c_out);

// ============================================================================
// METODOS NUMERICOS PARA BUSQUEDA DE RAICES (CEROS)
// ============================================================================

// Método de la Biseccion (Una sola raiz)
double biseccion(double (*f)(double), double x1, double x2, double tol1, double tol2, int max_iter);

// Biseccion Multiple: Busca multiples raices en un intervalo [a, b]
double* biseccion_multi(double (*f)(double), double a, double b, int subintervalos, double tol, int &num_raices);

// Método de la Secante (Una sola raiz)
double secante(double (*f)(double), double x0, double x1, double tol1, double tol2, int max_iter);

// Método de Newton (Una sola raiz)
double newton(double (*f)(double), double (*df)(double), double x0, double tol1, double tol2, int max_iter);

// Newton Multiple: Busca multiples raices lanzando Newton desde varios puntos
double* newton_multi(double (*f)(double), double (*df)(double), double a, double b, int puntos_inicio, double tol, int &num_raices);

// ============================================================================
// RESOLUCION DE SISTEMAS LINEALES
// ============================================================================

// ----------------------------------------------------------------------------
// 1. FACTORIZACION LU Y RESOLUCION
// ----------------------------------------------------------------------------

// Factorización LU (Forma 1 - Descomposición de Doolittle)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma1(double **A, int n, double **L, double **U);

// Resuelve Ax = b usando LU Forma 1
double* lu_forma1_sol(double **A, double *b, int n);

// Factorización LU (Forma 2 - Alternando fila U y columna L)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma2(double **A, int n, double **L, double **U);

// Resuelve Ax = b usando LU Forma 2
double* lu_forma2_sol(double **A, double *b, int n);

// ----------------------------------------------------------------------------
// 2. METODOS DE ELIMINACION Y MATRICES SINGULARES (Gauss y Gauss-Jordan)
// ----------------------------------------------------------------------------

// Eliminación de Gauss con pivoteo parcial
double* gauss_solve(double **A, double *b, int n);

// Método de Gauss-Jordan (Diagonal a 1, ceros arriba y abajo)
double* gauss_jordan_solve(double **A, double *b, int n);

// ----------------------------------------------------------------------------
// 3. SISTEMAS ESPECIALES
// ----------------------------------------------------------------------------

// Algoritmo de Thomas (Sistemas Tridiagonales)
// Los vectores a, b, c son las diagonales (inferior, principal, superior)
// Se le pasa la matriz completa A y el vector independiente f.
// La funcion extrae las diagonales automaticamente.
double* tridiag_solve(double **A, double *f, int n);

// ----------------------------------------------------------------------------
// 4. METODOS ITERATIVOS
// ----------------------------------------------------------------------------

/// Función Auxiliar: Comprueba estrictamente si una matriz es diagonalmente dominante
bool check_dominancia(double **A, int n);

// Función Auxiliar: Reordena las filas (A y b) solo si la matriz no es dominante de entrada
bool reorder_diagonals(double **A, double *b, int n);

// Método Iterativo de Jacobi (Desplazamientos simultáneos)
double* jacobi_solve(double **A, double *b, int n, double tol, int max_iter);

// Método Iterativo de Gauss-Seidel (Desplazamientos sucesivos)
double* gauss_seidel_solve(double **A, double *b, int n, double tol, int max_iter );

// Método de Sobrerrelajación (SOR) - Extensión de Gauss-Seidel
// El valor óptimo de w está entre 1 y 2. Para w=1 es idéntico a Gauss-Seidel.
double* sor_solve(double **A, double *b, int n, double w, double tol, int max_iter);

// ============================================================================
// DETERMINANTES E INVERSAS (MÚLTIPLES MÉTODOS)
// ============================================================================

// 1A. Determinante usando Eliminación Gaussiana (con pivoteo)
double det_gauss(double **A, int n);

// 1B. Determinante usando Factorización LU (Doolittle)
double det_lu(double **A, int n);

// 2A. Inversa de una matriz usando Gauss-Jordan
double** inv_gj(double **A, int n);

// 2B. Inversa de una matriz usando Factorización LU
double** inv_lu(double **A, int n);

// ============================================================================
// SISTEMAS SOBREDETERMINADOS Y REGRESIONES (MINIMOS CUADRADOS)
// ============================================================================

// 0. MOTOR CENTRAL: Resuelve Ax = b para sistemas sobredeterminados (m > n)
// Devuelve el vector solucion 'x', y por referencia el vector de 'errores' de
// cada parametro, y el coeficiente de determinacion 'R2'.
// -----> Ordinary Least Squares, OLS, minimos cuadrados
double* ols_reg(double **A, double *b, int m, int n, double *&errores, double &R2);

// 1. Regresión Polinómica: y = a0 + a1*x + a2*x^2 + ... + am*x^m
// Devuelve un vector con [a0, a1, ..., am]
double* poly_reg(double *x, double *y, int m_datos, int grado, double *&errores, double &R2);

// 2. Regresión Lineal: y = a0 + a1*x
// (Es simplemente un caso particular de la regresion polinomica de grado 1)
double* lin_reg(double *x, double *y, int m_datos, double *&errores, double &R2);

// 3. Regresión Exponencial: y = a * e^(bx)
// Devuelve [a, b]. Realiza la linealizacion: ln(y) = ln(a) + b*x
double* exp_reg(double *x, double *y, int m_datos, double *&errores, double &R2);

// 4. Regresión Logarítmica: y = a + b * ln(x)
// Devuelve [a, b]. Realiza la linealizacion: Y = a + b*X (con X = ln(x))
double* regresion_logaritmica(double *x, double *y, int m_datos, double *&errores, double &R2);

// 5. Regresión Potencial: y = a * x^b
// Devuelve [a, b]. Realiza linealizacion bilogaritmica: ln(y) = ln(a) + b*ln(x)
double* regresion_potencial(double *x, double *y, int m_datos, double *&errores, double &R2);

// 6. Regresión Sinusoidal / Armónica: y = a0 + a1*cos(w*x) + a2*sin(w*x)
// Devuelve [a0, a1, a2]. Requiere que le introduzcas la frecuencia angular 'w'
double* regresion_sinusoidal(double *x, double *y, int m_datos, double w, double *&errores, double &R2);

// ----------------------------------------------------------------------------
// INTERPOLACION NUMERICA
// ----------------------------------------------------------------------------

// ============================================================================
// INTERPOLACION: familia coef / eval / interp
//   *_coef   : precalcula lo necesario una sola vez (devuelve array con new[])
//   *_eval   : evalua en un punto xi usando lo precalculado (rapido)
//   *_interp : todo en uno (coef + eval + liberar), igual que lagrange_interp
// ============================================================================

// 7. ---------------- SPLINE CUBICA NATURAL ----------------
// Devuelve las segundas derivadas M[0..n-1] (M[0]=M[n-1]=0). Liberar con del_vect.
double* spline_coef(double *x, double *y, int n);

// x debe estar ordenado de menor a mayor. Fuera de [x0, xn-1] extrapola con el tramo extremo.
double spline_eval(double *x, double *y, double *M, int n, double xi);

double spline_interp(double *x, double *y, int n, double xi);

// 8. ---------------- NEWTON (diferencias divididas) ----------------
// Devuelve c[0..n-1] = f[x0], f[x0,x1], ... Liberar con del_vect.
double* newton_coef(double *x, double *y, int n);

// Evalua el polinomio de Newton en xi (forma anidada tipo Horner)
double newton_eval(double *x, double *c, int n, double xi);

// 9. ---------------- LAGRANGE (forma baricentrica) ----------------
// Devuelve los pesos w[i] = 1 / prod_{j!=i} (x[i]-x[j]). Liberar con del_vect.
double* lagrange_coef(double *x, int n);

// Evalua el polinomio de Lagrange en xi con los pesos w (O(n) por punto)
double lagrange_val(double *x, double *y, double *w, int n, double xi);

// ============================================================================
// CÁLCULO NUMÉRICO: DERIVADAS, GRADIENTES Y JACOBIANOS
// ============================================================================

// ----------------------------------------------------------------------------
// CALCULO NUMERICO CON FUNCIONES
// ----------------------------------------------------------------------------

// Derivada parcial numérica usando diferencias finitas progresivas.
// Descripción: Calcula el cambio de la función 'f' respecto a la variable 'j' variando 'h'.
double part_derv(double (*f)(double*, int), double *x, int n, int j);

// Derivada total
// Descripción: Calcula la derivada total dF/dt sumando el producto de las derivadas parciales por dx_i/dt.
double total_derv(double (*f)(double*, int), double *x, double *dx_dt, int n);

// Gradiente
// Descripción: Devuelve un vector con todas las derivadas parciales de una función escalar.
double* grad_vect(double (*f)(double*, int), double *x, int n);

// Matriz Jacobiana
// Descripción: Construye la matriz nxn de derivadas parciales para un sistema de n funciones.
double** jacobian_mat(double (*AF[])(double*, int), double *x, int n);

// Integral Definida Numérica de una función (Regla de Simpson 1/3)
// Descripción: Calcula el área bajo la curva de la función 'f' en el intervalo [a, b] con 'n' paneles (n par).
double integral_def_func(double (*f)(double), double a, double b, int n);

// Integral Indefinida Numérica de una función sobre un dominio discreto
// Descripción: Evalúa la integral acumulativa de 'f' sobre los puntos del vector 'x', sumando la constante 'C'.
double* integral_indef_func(double (*f)(double), double *x, int n_puntos, double C);

// ----------------------------------------------------------------------------
// CALCULO NUMERICO CON VECTORES (ARRAYS)
// ----------------------------------------------------------------------------

// Derivada Numérica de datos discretos (Vectorial)
// Descripción: Calcula dy/dx usando diferencias finitas. Diferencias centrales en el interior y progresivas/regresivas en los bordes.
double* deriv_vect(double *x, double *y, int n);

// Integral Numérica de datos discretos (Vectorial)
// Descripción: Calcula la integral definida e indefinida (acumulada) usando la regla del trapecio.
// Nota: 'int_indef' se devuelve por return, 'int_def' se extrae por referencia (&).
double* int_vect(double *x, double *y, int n, double y0, double &int_def);

// ============================================================================
// SISTEMAS NO LINEALES
// ============================================================================

// ----------------------------------------------------------------------------
// SUSTITUCIONES SUCESIVAS
// ----------------------------------------------------------------------------

// Comprobador de Condición de Convergencia
// Descripción: Verifica si la suma del valor absoluto de las derivadas parciales de cada función es <= 1.
bool check_convergence_nolin(double (*AF[])(double*, int), double *x, int n);

// 1. Jacobi para Sistemas No Lineales
// Descripción: Resuelve iterativamente un sistema reordenado xi = Fi(x1...xn) usando desplazamientos simultáneos.
double* jacobi_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter);

// 2. Gauss-Seidel para Sistemas No Lineales
// Descripción: Similar a Jacobi, pero usa los valores recién calculados (desplazamientos sucesivos).
double* gauss_seidel_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter);

// 3. Newton-Raphson Multivariable (Generalizado para n ecuaciones)
// Descripción: Resuelve el sistema F(x)=0 aproximando las derivadas por diferencias finitas (Jacobiano).
double* newton_raphson_sys(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter);

// 4. Newton-Raphson Array de Soluciones
// Descripción: Ejecuta Newton-Raphson sobre múltiples puntos de inicio. Devuelve una matriz de soluciones.
double** newton_raphson_multi_sys(double (*AF[])(double*, int), double **x_inits, int num_puntos, int n, double tol, int max_iter);

// ----------------------------------------------------------------------------
// MÉTODOS DE MINIMIZACIÓN: DESCENSO MÁS RÁPIDO (STEEPEST DESCENT)
// ----------------------------------------------------------------------------

// Helper: Calcula S(x) = sum(fi(x)^2) para convertir un sistema de ecuaciones en un problema de minimización
double func_S_error(double (*AF[])(double*, int), double *x, int n);

// 5. Descenso más rápido / Máxima pendiente (Steepest Descent)
// Descripción: Resuelve el sistema encontrando el mínimo global de la función escalar S(x) = sum(fi^2).
// Utiliza un factor de avance alfa dinámico (backtracking simple) para asegurar que S siempre disminuya.
double* steepest_descent_sys(double (*AF[])(double*, int), double *x_init, int n, double alpha_init, double tol, int max_iter);


#endif // MATCLUB_H
