// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Vectores (arrays dinamicos)
// ============================================================================
// Creacion, copia, operaciones elemento a elemento, funciones matematicas, sumas, acumulados, busqueda, polinomios, proyecciones, entrada y salida.
//
// Funciones (72): del_vect, copy_vect, prod_vect, mod_vect, cos_ang_vect, suma_vect, resta_vect, prod_esc_vect, lincomb_vect, prodeach_vect, diveach_vect, exp_vect, prodx_vect, full_vect, zeros_vect, ones_vect, linspace, logspace, arange, pow_vect, sqrt_vect, abs_vect, sin_vect, cos_vect, tan_vect, sec_vect, csc_vect, cot_vect, asin_vect, acos_vect, atan_vect, asec_vect, acsc_vect, acot_vect, log_vect, log10_vect, sinh_vect, cosh_vect, tanh_vect, asinh_vect, acosh_vect, atanh_vect, sum_elems, cumsum_vect, prod_elems, cumprod_vect, mean_vect, max_vect, min_vect, std_vect, flip_vect, argmax_vect, argmin_vect, diff_vect, concat_vect, floor_vect, ceil_vect, round_vect, print_vect, input_vect, normalize_vect, sign_vect, clamp_vect, polyval_vect, polyval, slice_vect, sum_esc_vect, var_vect, proj_vect, find_gt_vect, find_if_vect, count_if_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Libera un vector (para que se lea igual que del_mat)

void del_vect(double *a) {
    delete[] a;
}

// Copia un vector

double* copy_vect(double *a, int n) {
    double *c = new double[n];
    for (int i = 0; i < n; i++) c[i] = a[i];
    return c;
}

//Producto Punto

   double prod_vect(double *a,double *b ,int n) { 
   		double prod=0; 
   		for ( int i = 0; i<n ; i++){
		prod = prod + a[i]*b[i];
		}    
        return prod; 
    }

//Modulo Vectorial

    double mod_vect(double *a,int n) { 
   		double mod;
		mod= sqrt(prod_vect(a,a,n)); 
        return mod; 
    }   

//Coseno de angulo entre vectores

   double cos_ang_vect(double *a,double *b ,int n) { 
   		double cos_;
		cos_=(prod_vect(a,b,n))/((mod_vect(a,n))*(mod_vect(b,n)));    
        return cos_; 
    }

// Suma de Vectores

   double* suma_vect(double *a,double *b ,int n) { 
   		double *c ;		c=new double [n];
   		for ( int i = 0; i<n ; i++){
			c[i] = a[i] + b[i];
		}   
    return c; 
    }

// Resta de Vectores

   double* resta_vect(double *a,double *b ,int n) { 
   		double *c ;		c=new double [n];
   		for ( int i = 0; i<n ; i++){
			c[i] = a[i] - b[i];
		}   
    return c; 
	}

//Producto por un Escalar

   double* prod_esc_vect(double *a,double k ,int n) {
   		double *c ;		c=new double [n]; 
   		for ( int i = 0; i<n ; i++){
		c[i] = k*a[i];
		}    
        return c; 
    }

//Combinacion Lineal 

	double* lincomb_vect(double *a,double *b,double p, double q,int n) {
   		double *c ;		c=new double [n]; 
   		for ( int i = 0; i<n ; i++){
		c[i] = p*a[i]+q*b[i];
		}    
        return c; 
    }

//Producto de cada elemento (Proucto punto en matlab)    

	double* prodeach_vect(double *a,double *b,int n) {
   		double *c ;		c=new double [n]; 
   		for ( int i = 0; i<n ; i++){
		c[i] = a[i]*b[i];
		}    
        return c; 
    }

//Division de cada elemento (Division punto en matlab)    

	double* diveach_vect(double *a,double *b,int n) {
   		double *c ;		c=new double [n]; 
   		for ( int i = 0; i<n ; i++){
		c[i] = a[i]/b[i];
		}    
        return c; 
    }

//Exponencial de cada elemento    

	double* exp_vect(double *a,int n) {
   		double *c ;		c=new double [n]; 
   		for ( int i = 0; i<n ; i++){
		c[i] = exp(a[i]);
		}    
        return c; 
    }

//Producto Cruz

double* prodx_vect(double *a, double *b, int n) { 
    if (n != 3) {
        print_error_int("No existe producto cruz en esa dimension (solo n = 3)", n);
        return NULL; // Retorna nulo si no es 3D
    }
    
    double *c ;        c = new double [3];
    c[0] = a[1]*b[2] - a[2]*b[1];
    c[1] = a[2]*b[0] - a[0]*b[2];
    c[2] = a[0]*b[1] - a[1]*b[0];
    
    return c; 
}

// Vector de n elementos todos iguales a 'val'

double* full_vect(int n, double val) {
    double *c = new double[n];
    for (int i = 0; i < n; i++) c[i] = val;
    return c;
}

//Array de 0s   

    double* zeros_vect(int n) { 
    	double *c ;        c = new double [n]();
    return c; 
}

//Array de 1s 

	double* ones_vect(int n) { 
		double *c = full_vect(n,1.0); 
    return c; 
}

//linspace de matlab

double* linspace(double start, double end, int n) { 
    double *c ;        c = new double [n];
    double step = (end - start) / (n - 1);
    for ( int i = 0; i<n ; i++){
        c[i] = start + i * step;
    }   
    return c; 
}

// logspace: n puntos espaciados logaritmicamente entre 10^start y 10^end

double* logspace(double start, double end, int n) { 
    double *c ;        c = new double [n];
    double step = (end - start) / (n - 1);
    for ( int i = 0; i < n ; i++){
        c[i] = pow(10.0, start + i * step);
    }   
    return c; 
}

//arange funcion star:step:end de matlab. La variable n por referencia & 
		//para que la función calcule el tamaño y te lo devuelva al main

double* arange(double start, double step, double end, int &n) { 
    n = (int)( (end - start) / step ) + 1;
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = start + i * step;
    }   
    return c; 
}

//^p a cada elemento del vector.

double* pow_vect(double *a, double p, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = pow(a[i], p);
    }   
    return c; 
}

//sqrt a cada elemento del vector.

double* sqrt_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = sqrt(a[i]);
    }   
    return c; 
}

//abs a cada elemento del vector.

double* abs_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = fabs(a[i]);
    }   
    return c; 
}

// sin a cada elemento del vector.

double* sin_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = sin(a[i]);
    }   
    return c; 
}

// cos a cada elemento del vector.

double* cos_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = cos(a[i]);
    }   
    return c; 
}

// tan a cada elemento del vector.

double* tan_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = tan(a[i]);
    }   
    return c; 
}

// sec a cada elemento del vector.

double* sec_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = 1.0 / cos(a[i]);
    }   
    return c; 
}

// csc a cada elemento del vector.

double* csc_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = 1.0 / sin(a[i]);
    }   
    return c; 
}

// cot a cada elemento del vector.

double* cot_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = 1.0 / tan(a[i]);
    }   
    return c; 
}

// arcoseno (asin)

double* asin_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        c[i] = asin(a[i]);
    }   
    return c; 
}

// Arcocoseno (acos)

double* acos_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        c[i] = acos(a[i]);
    }   
    return c; 
}

// Arcotangente (atan)

double* atan_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        c[i] = atan(a[i]);
    }   
    return c; 
}

// Arcosecante (asec)

double* asec_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        c[i] = acos(1.0 / a[i]);
    }   
    return c; 
}

// Arcocosecante (acsc)

double* acsc_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        c[i] = asin(1.0 / a[i]);
    }   
    return c; 
}

// Arcocotangente (acot)

double* acot_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        // Usamos atan2(y, x) equivalente a atan(y/x) -> atan(1.0 / a[i])
        // Esto evita errores matematicos si a[i] es exactamente 0.0
        c[i] = atan2(1.0, a[i]);
    }   
    return c; 
}

// log neperiano a cada elemento del vector.

double* log_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = log(a[i]);
    }   
    return c; 
}

// log en base 10 a cada elemento del vector.

double* log10_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = log10(a[i]);
    }   
    return c; 
}

// Seno hiperbolico (sinh)

double* sinh_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = sinh(a[i]);
    }   
    return c; 
}

// Coseno hiperbolico (cosh)

double* cosh_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = cosh(a[i]);
    }   
    return c; 
}

// Tangente hiperbolica (tanh)

double* tanh_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = tanh(a[i]);
    }   
    return c; 
}

// Arcoseno hiperbolico (asinh)

double* asinh_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = asinh(a[i]);
    }   
    return c; 
}

// Arcocoseno hiperbolico (acosh)

double* acosh_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        // Nota matematica: a[i] debe ser >= 1
        c[i] = acosh(a[i]);
    }   
    return c; 
}

// Arcotangente hiperbolica (atanh)

double* atanh_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        // Nota matematica: a[i] debe estar estrictamente entre -1 y 1
        c[i] = atanh(a[i]);
    }   
    return c; 
}

// Suma total de cada elemento del vector.

double sum_elems(double *a, int n) { 
    double suma = 0; 
    for ( int i = 0; i<n ; i++){
        suma = suma + a[i];
    }   
    return suma; 
}

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

// Producto total de cada elemento.

double prod_elems(double *a, int n) { 
    double producto = 1.0; // Importante inicializar en 1, no en 0
    for ( int i = 0; i<n ; i++){
        producto = producto * a[i];
    }   
    return producto; 
}

// Producto acumulativo

double* cumprod_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    double producto = 1.0; 
    for ( int i = 0; i<n ; i++){
        producto = producto * a[i];
        c[i] = producto;
    }   
    return c; 
}

// Media del vect

double mean_vect(double *a, int n) { 
    double mean;
    mean = sum_elems(a, n) / n;   
    return mean; 
}

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

// Desviacion Estandar del Vect

double std_vect(double *a, int n) { 
    double mean = mean_vect(a, n);
    double sum_sq = 0; 
    for ( int i = 0; i<n ; i++){
        sum_sq = sum_sq + pow((a[i] - mean), 2);
    }   
    return sqrt(sum_sq / (n - 1)); 
}

//Invertir el orden (Flip)

double* flip_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = a[n - 1 - i];
    }   
    return c; 
}

// Devuelve el INDICE donde se encuentra el valor maximo

int argmax_vect(double *a, int n) { 
    int idx = 0;
    double max_v = a[0]; 
    for ( int i = 1; i<n ; i++){
        if(a[i] > max_v) {
            max_v = a[i];
            idx = i;
        }
    }   
    return idx; 
}

// Devuelve el INDICE donde se encuentra el valor minimo

int argmin_vect(double *a, int n) { 
    int idx = 0;
    double min_v = a[0]; 
    for ( int i = 1; i<n ; i++){
        if(a[i] < min_v) {
            min_v = a[i];
            idx = i;
        }
    }   
    return idx; 
}

// Diferencias adyacentes (El vector devuelto tiene tamano n-1)

double* diff_vect(double *a, int n) { 
    double *c ;        c = new double [n - 1];
    for ( int i = 0; i<n-1 ; i++){
        c[i] = a[i + 1] - a[i];
    }   
    return c; 
}

// Une el vector a (tamano n_a) con el vector b (tamano n_b)

double* concat_vect(double *a, int n_a, double *b, int n_b) { 
    double *c ;        c = new double [n_a + n_b];
    
    // Copiar el primer vector
    for ( int i = 0; i<n_a ; i++){
        c[i] = a[i];
    }
    // Añadir el segundo vector a continuacion
    for ( int i = 0; i<n_b ; i++){
        c[n_a + i] = b[i];
    }   
    return c; 
}

// Redondea hacia abajo

double* floor_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = floor(a[i]);
    }   
    return c; 
}

// Redondea hacia arriba 

double* ceil_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = ceil(a[i]);
    }   
    return c; 
}

// Redondea al entero mas cercano

double* round_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        // round() requiere <cmath>
        c[i] = round(a[i]); 
    }   
    return c; 
}

// Print Vector

void print_vect(double *a, int n, const char* nombre) { 
    cout << nombre << " = [ ";
    for ( int i = 0; i<n ; i++){
        cout << a[i] << (i < n - 1 ? ", " : " ");
    }   
    cout << "]" << endl;
}

// Introducir vector por teclado

double* input_vect(int n) {
/* 
En el programa principal:
int n = 5;
double *v;
v = input_vect(n);
con n el tamaño del vector
*/

    double *v = new double[n]; // Crea el vector dinámico de tamaño n
    
    for (int i = 0; i < n; i++) {
        cout << "INTRODUCE ELEMENTO [" << i << "]: ";
        cin >> v[i];
    }
    
    return v;
}

// Normaliza un vector (lo divide entre su modulo)

double* normalize_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    double mod = mod_vect(a, n); // Usamos la funcion que ya creaste antes
    
    if (mod == 0.0) {
        print_error("No se puede normalizar un vector nulo");
        // Devuelve ceros si falla
        for (int i = 0; i < n; i++) c[i] = 0.0;
        return c;
    }
    
    for (int i = 0; i < n; i++) {
        c[i] = a[i] / mod;
    }   
    return c; 
}

// Extrae el signo de cada elemento: devuelve 1, -1 o 0

double* sign_vect(double *a, int n) { 
    double *c ;        c = new double [n];
    for (int i = 0; i < n; i++) {
        if (a[i] > 0.0) {
            c[i] = 1.0;
        } else if (a[i] < 0.0) {
            c[i] = -1.0;
        } else {
            c[i] = 0.0;
        }
    }   
    return c; 
}

// clamp: Limita los valores de un vector entre un minimo y un maximo

double* clamp_vect(double *a, int n, double min_val, double max_val) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i < n ; i++){
        if (a[i] < min_val) {
            c[i] = min_val;
        } else if (a[i] > max_val) {
            c[i] = max_val;
        } else {
            c[i] = a[i];
        }
    }   
    return c; 
}

// polyval: Evalua un polinomio p (grado np-1) en los puntos del vector x
						// Ejemplo: p = [3, 2, 1] evalua 3*x^2 + 2*x + 1

double* polyval_vect(double *p, int np, double *x, int nx) { 
    double *c ;        c = new double [nx];
    for ( int i = 0; i < nx ; i++){
        double val = 0.0;
        for ( int j = 0; j < np ; j++){
            val = val * x[i] + p[j]; // Regla de Horner
        }
        c[i] = val;
    }   
    return c; 
}

// polyval_scalar: Evalua un polinomio p en un UNICO punto escalar x
		// Devuelve un escalar (el valor del polinomio evaluado en ese punto)
		//Esta funcion ademas es una funcion que devuelve calquier vector

double polyval(double *p, int np, double x) { 
    double val = 0.0;
    for ( int i = 0; i < np ; i++){
        val = val * x + p[i]; // Regla de Horner
    }   
    return val; 
}

// Subvector desde ini hasta fin (ambos incluidos, indices desde 0). Como a(ini:fin) de MATLAB

double* slice_vect(double *a, int n, int ini, int fin) {
    if (ini < 0 || fin >= n || ini > fin) {
        print_error("slice_vect: indices fuera de rango");
        return NULL;
    }
    int m = fin - ini + 1;
    double *c = new double[m];
    for (int i = 0; i < m; i++) c[i] = a[ini + i];
    return c;
}

// Suma un escalar a cada elemento (a + k en MATLAB)

double* sum_esc_vect(double *a, double k, int n) {
    double *c = new double[n];
    for (int i = 0; i < n; i++) c[i] = a[i] + k;
    return c;
}

// Varianza muestral (n-1)

double var_vect(double *a, int n) {
    if (n < 2) {
        print_error("var_vect: se necesitan al menos 2 elementos");
        return MC_NAN;
    }
    double m = mean_vect(a, n);
    double s = 0.0;
    for (int i = 0; i < n; i++) s += pow( (a[i] - m) ,2);
    return s / (n - 1);
}

// Proyeccion del vector a sobre el vector b: (a.b / b.b) * b

double* proj_vect(double *a, double *b, int n) {
    double bb = prod_vect(b, b, n);
    if (bb == 0.0) {
        print_error("proj_vect: no se puede proyectar sobre un vector nulo");
        return NULL;
    }
    return prod_esc_vect(b, prod_vect(a, b, n) / bb, n);
}

// find_gt: Devuelve los INDICES donde los elementos son mayores que un umbral
		// La variable 'n_out' por referencia te dirá cuántos elementos cumplieron la condición

double* find_gt_vect(double *a, int n, double umbral, int &n_out) {
    // 1. Contar cuántos cumplen la condición para saber el tamaño del nuevo vector
    n_out = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > umbral) n_out++;
    }
    
    if (n_out == 0) return NULL; // Si ninguno cumple, retorna nulo
    
    // 2. Crear el vector dinámico y guardar los índices
    double *c = new double[n_out];
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > umbral) {
            c[idx] = (double)i; // Guardamos el índice como double
            idx++;
        }
    }
    return c;
}

// find generico: indices donde la funcion-condicion devuelve true
			// Ejemplo:  bool es_negativo(double x){ return x < 0; }
				//           double *idx = find_if_vect(v, n, es_negativo, k);

double* find_if_vect(double *a, int n, bool (*cond)(double), int &n_out) {
    n_out = 0;
    for (int i = 0; i < n; i++) if (cond(a[i])) n_out++;
    if (n_out == 0) return NULL;
    double *c = new double[n_out];
    int idx = 0;
    for (int i = 0; i < n; i++) if (cond(a[i])) c[idx++] = (double)i;
    return c;
}

// Cuenta cuantos elementos cumplen la condicion

int count_if_vect(double *a, int n, bool (*cond)(double)) {
    int k = 0;
    for (int i = 0; i < n; i++) if (cond(a[i])) k++;
    return k;
}

