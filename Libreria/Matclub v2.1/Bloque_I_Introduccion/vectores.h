// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Vectores (arrays dinamicos)
// ============================================================================
// Creacion, copia, operaciones elemento a elemento, funciones matematicas, sumas, acumulados, busqueda, polinomios, proyecciones, entrada y salida.
//
// Funciones (72): del_vect, copy_vect, prod_vect, mod_vect, cos_ang_vect, suma_vect, resta_vect, prod_esc_vect, lincomb_vect, prodeach_vect, diveach_vect, exp_vect, prodx_vect, full_vect, zeros_vect, ones_vect, linspace, logspace, arange, pow_vect, sqrt_vect, abs_vect, sin_vect, cos_vect, tan_vect, sec_vect, csc_vect, cot_vect, asin_vect, acos_vect, atan_vect, asec_vect, acsc_vect, acot_vect, log_vect, log10_vect, sinh_vect, cosh_vect, tanh_vect, asinh_vect, acosh_vect, atanh_vect, sum_elems, cumsum_vect, prod_elems, cumprod_vect, mean_vect, max_vect, min_vect, std_vect, flip_vect, argmax_vect, argmin_vect, diff_vect, concat_vect, floor_vect, ceil_vect, round_vect, print_vect, input_vect, normalize_vect, sign_vect, clamp_vect, polyval_vect, polyval, slice_vect, sum_esc_vect, var_vect, proj_vect, find_gt_vect, find_if_vect, count_if_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_VECTORES_H
#define MATCLUB_VECTORES_H

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

// find_gt: Devuelve los INDICES donde los elementos son mayores que un umbral
// La variable 'n_out' por referencia te dirá cuántos elementos cumplieron la condición
double* find_gt_vect(double *a, int n, double umbral, int &n_out);

// find generico: indices donde la funcion-condicion devuelve true
// Ejemplo:  bool es_negativo(double x){ return x < 0; }
//           double *idx = find_if_vect(v, n, es_negativo, k);
double* find_if_vect(double *a, int n, bool (*cond)(double), int &n_out);

// Cuenta cuantos elementos cumplen la condicion
int count_if_vect(double *a, int n, bool (*cond)(double));

#endif // MATCLUB_VECTORES_H
