//Made by Cesar with a little(to much) help of my friends (Gema y Jose)

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <algorithm> //Solo para sort de momento.

using namespace std;
const double MC_NAN = sqrt(-1.0);

// ============================================================================
// FUNCIONES PARA IMPRIMIR MENSAJES
// ============================================================================

// Imprime un mensaje de error formateado al estilo de la libreria
void print_error(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB ERROR]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}

// Aviso: algo no fue perfecto pero el programa puede continuar
void print_warning(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB AVISO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}

// Informacion (p. ej. "archivo guardado")
void print_info(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB INFO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}

// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}

// Error de dimensiones: "mensaje (faxca) * (fbxcb)"
void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb) {
    cout << "[MATCLUB ERROR]: " << mensaje
         << " (" << fa << "x" << ca << ") * (" << fb << "x" << cb << ")" << endl;
}

// Linea separadora para ordenar la salida por pantalla
void print_line(int n = 40, char c = '=') {
    for (int i = 0; i < n; i++) cout << c;
    cout << endl;
}


// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

//Intercambia dos elementos
void intercambiar_elem(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}

bool isNaN(double v) {
    return v != v; // En norma IEEE 754, NaN es distinto de sí mismo
}

bool isRoot(const double* raices, int n, double r, double tol) {
    for (int i = 0; i < n; ++i) {
        if (fabs(raices[i] - r) < tol) return true;
    }
    return false;
}

// Comprueba si un número está dentro de un rango [min, max] con tolerancia
bool is_in_range(double val, double min_val, double max_val) {
    return (val >= min_val && val <= max_val);
}

// Limita un valor escalar entre un mínimo y un máximo (clamp escalar)
double clamp(double val, double min_val, double max_val) {
    if (val < min_val) return min_val;
    if (val > max_val) return max_val;
    return val;
}

// Grados <-> radianes
double deg2rad(double g) { return g * acos(-1.0) / 180.0; }
double rad2deg(double r) { return r * 180.0 / acos(-1.0); }

// Maximo y minimo de dos numeros (evita choques con macros max/min de Windows)
double max2(double a, double b) { return (a > b) ? a : b; }
double min2(double a, double b) { return (a < b) ? a : b; }

// Factorial (devuelve double para llegar hasta 170!)
double factorial(int n) {
    if (n < 0) {
        print_error("factorial no definido para n negativo");
        return MC_NAN;
    }
    double f = 1.0;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}

// Maximo comun divisor y minimo comun multiplo (enteros)
long mcd_int(long a, long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) { long t = a % b; a = b; b = t; }
    return a;
}
long mcm_int(long a, long b) {
    if (a == 0 || b == 0) return 0;
    long r = a / mcd_int(a, b) * b;
    return (r < 0) ? -r : r;
}

// Numero primo
bool is_prime(long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return (n == 2);
    for (long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Devuelve PI redondeado decimales 'n'
double PI(int n) {
    double base_pi = acos(-1.0);		double factor = pow(10.0, n);
    return round(base_pi * factor) / factor;
}

// ============================================================================
// FUNCIONES DE VECTORES
// ============================================================================


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
void print_vect(double *a, int n, const char* nombre = "ans") { 
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


// ============================================================================
// FUNCIONES PARA INTROSORT (incluyendo Introsort)
// ============================================================================

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

//FUNCION SORT USANDO ALGORITHM
double* sort_vect_algorithm(double *a, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = a[i];
    }   
    sort(c, c + n); // Aplica introsort directo sobre los punteros
    return c; 
}

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

// rand: Genera un vector con numeros aleatorios entre 0.0 y 1.0 uniformes
double* rand_vect(int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        // rand() genera enteros grandes, lo dividimos por el maximo para normalizar
        c[i] = (double)rand() / RAND_MAX;
    }   
    return c; 
}

// randi: Genera un vector con numeros enteros aleatorios entre min y max
double* randi_vect(int min, int max, int n) { 
    double *c ;        c = new double [n];
    for ( int i = 0; i<n ; i++){
        c[i] = min + rand() % ((max + 1) - min);
    }   
    return c; 
}

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

// Cuenta cuantos elementos cumplen la condicion
int count_if_vect(double *a, int n, bool (*cond)(double)) {
    int k = 0;
    for (int i = 0; i < n; i++) if (cond(a[i])) k++;
    return k;
}


// ============================================================================
// FUNCIONES DE MATRICES
// ============================================================================

//Crear Matriz
double** gen_mat(double **M, int f, int c){
	/* en el programa principal si queremos crear (reservar memoria) para la matriz B. 
   		double **B;
   		B=crearmatriz(B,fb,cb);
   	donde fb es el numero de filas de B y cb el numero de columnas de B
	*/
    M = new double * [f];
    	for (int i = 0; i < f; i++) { M[i] = new double[c];}
     return M;
}

//Borrar Matriz
void del_mat(double **M, int f){
	/* libera la memoria de la matriz pasada en la llamada. Por ejemplo una matriz B.
	borrarmatriz(B, fb);
	con fb el nÃºmero de filas de B.
	*/

	for (int i=0; i < f; i++) {
    	delete[] M[i];
    	}
    delete [] M;
}

// Multiplicación de matrices (A de fa x ca, B de fb x cb)
double** prod_mat(double **A, double **B, int fa, int ca, int fb, int cb) {
    
    // Validar si se pueden multiplicar (Columnas de A == Filas de B)
    if (ca != fb) {
        print_error_dim("No se pueden multiplicar las matrices, dimensiones incompatibles", fa, ca, fb, cb);
        return NULL; // Retorna nulo si la multiplicación no es válida matemáticamente
    }

    double suma;
    double **Producto;
    
    // Creamos la matriz resultado de tamaño (fa x cb)
    Producto = gen_mat(Producto, fa, cb);

    for (int i = 0; i < fa; i++) {
        for (int j = 0; j < cb; j++) {
            suma = 0.0;
            for (int k = 0; k < ca; k++) { // O 'fb', ya que son iguales
                suma = suma + A[i][k] * B[k][j];
            }
            Producto[i][j] = suma;
        }
    }
    
    return Producto;
}

// Introducir matriz por teclado
double**  input_mat(int f, int c){ 
/* 
En el programa principal:
double **A;
A=crearmatriz(A,fa,ca);
A=leermatriz(fa,ca);
con fa el numero de filas de A y ca el numero de columnas de A
*/

double **M;
M=gen_mat(M,f,c);
    int i, j;
    for( i = 0; i < f; i++){
        for (j = 0; j < c; j++){
          cout << "INTRODUCE ELEMENTO ["<<i<<"]"<<"["<<j<<"]"<< endl;
          cin >> M[i][j] ;
          }
     } 
return M;
} 

// Imprimir matriz
void print_mat(double **M, int f, int c, const char* nombre = "ans") {
    cout << nombre << " =" << endl;
    cout << "[" << endl;
    for (int i = 0; i < f; i++) {
        cout << " "; // Pequeña indentación para las filas
        for (int j = 0; j < c; j++) {
            cout << M[i][j] << (j < c - 1 ? ", " : " ");
        }
        cout << (i < f - 1 ? ";" : "") << endl;
    }
    cout << "]" << endl;
}

//Copiar la matriz
double** coppy_mat(double **M, int f, int c) {	
  /*Para hacrer una copia de la matriz B en el programa principal.
  	double **Bcopia;
	Bcopia=crearmatriz(Bcopia,fb,cb);
	Bcopia=copiarmatriz(fb,cb);
	con fb el numero de filas de b y cb el numero de columnas de b
  */
  
   double **Mcopia;
   Mcopia=gen_mat(Mcopia,f,c);
	for (int i = 0; i < f; i++){
		for (int j = 0; j < c; j++) {Mcopia[i][j] = M[i][j];}
		}
	return Mcopia;
}

//Matriz Transpuesta
double** transpose_mat(double **A, int fa, int ca) {
/* calcula la transpuesta de una matriz.
En el programa principal para calcular la transpuesta de una matriz B:
double **BTrans;
Btrans=crearmatriz(Btrans,fbtrans,cbtrans);
Btrans=transpuesta(B,fb,cb);
con fbtrans=cb y cbtrans=fb, fb el numero de filas de B y cb el numero de columnas de B
*/

	double aux;
	double **AT;
	AT=gen_mat(AT,ca,fa);
  
	for (int i = 0; i < fa; i++){
		for (int j = 0; j < ca; j++) {AT[j][i]=A[i][j]; }
	}
	return AT;
}

// Matriz de ceros (f x c)
double** zeros_mat(int f, int c) {
    double **M;
    M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = 0.0;
        }
    }
    return M;
}

// Matriz de unos (f x c)
double** ones_mat(int f, int c) {
    double **M;
    M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = 1.0;
        }
    }
    return M;
}

// Matriz Identidad (n x n), eye(n) en MATLAB
double** eye_mat(int n) {
    double **M;
    M = gen_mat(M, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) M[i][j] = 1.0;
            else M[i][j] = 0.0;
        }
    }
    return M;
}

// Producto de matriz por escalar
double** prod_esc_mat(double **A, double k, int f, int c) {
    double **M;
    M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = k * A[i][j];
        }
    }
    return M;
}

// Traza de una matriz cuadrada (suma de la diagonal principal)
double trace_mat(double **A, int n) {
    double tr = 0.0;
    for (int i = 0; i < n; i++) {
        tr += A[i][i];
    }
    return tr;
}

// Extrae la fila 'fila_idx' de una matriz y la devuelve como un vector dinámico 1D
					//Importante: LOS CONVIERTE EN UN POINTER, VECT EN ESTA LIBRERIA
double* get_row_mat(double **A, int f, int c, int fila_idx) {
    double *v = new double[c];
    for (int j = 0; j < c; j++) {
        v[j] = A[fila_idx][j];
    }
    return v;
}

// Extrae la columna 'col_idx' de una matriz y la devuelve como un vector dinámico 1D
					//Importante: LOS CONVIERTE EN UN POINTER, VECT EN ESTA LIBRERIA
double* get_col_mat(double **A, int f, int c, int col_idx) {
    double *v = new double[f];
    for (int i = 0; i < f; i++) {
        v[i] = A[i][col_idx];
    }
    return v;
}


// Suma de matrices (A + B)
double** suma_mat(double **A, double **B, int f, int c) {
    double **M;
    M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = A[i][j] + B[i][j];
        }
    }
    return M;
}

// Resta de matrices (A - B)
double** resta_mat(double **A, double **B, int f, int c) {
    double **M;
    M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = A[i][j] - B[i][j];
        }
    }
    return M;
}

// Producto celda a celda (A .* B en MATLAB)
double** prodeach_mat(double **A, double **B, int f, int c) {
    double **M;
    M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = A[i][j] * B[i][j];
        }
    }
    return M;
}

// Extrae una submatriz desde (f_ini, c_ini) hasta (f_fin, c_fin)
double** sub_mat(double **A, int f_ini, int f_fin, int c_ini, int c_fin) {
    int f_out = f_fin - f_ini + 1;
    int c_out = c_fin - c_ini + 1;
    
    double **M;
    M = gen_mat(M, f_out, c_out);
    
    for (int i = 0; i < f_out; i++) {
        for (int j = 0; j < c_out; j++) {
            M[i][j] = A[f_ini + i][c_ini + j];
        }
    }
    return M;
}

// Une dos matrices lado a lado: [A, B]
double** horzcat_mat(double **A, int fa, int ca, double **B, int fb, int cb) {
    if (fa != fb) {
        print_error("No se pueden unir horizontalmente, tienen diferente numero de filas");
        return NULL;
    }
    
    int c_out = ca + cb;
    double **M;
    M = gen_mat(M, fa, c_out);
    
    for (int i = 0; i < fa; i++) {
        // Copiar matriz A
        for (int j = 0; j < ca; j++) {
            M[i][j] = A[i][j];
        }
        // Copiar matriz B a continuación
        for (int j = 0; j < cb; j++) {
            M[i][ca + j] = B[i][j];
        }
    }
    return M;
}

// Apila una matriz sobre otra: [A; B]
double** vertcat_mat(double **A, int fa, int ca, double **B, int fb, int cb) {
    if (ca != cb) {
        print_error("No se pueden unir verticalmente, tienen diferente numero de columnas");
        return NULL;
    }
    
    int f_out = fa + fb;
    double **M;
    M = gen_mat(M, f_out, ca);
    
    for (int j = 0; j < ca; j++) {
        // Copiar filas de A
        for (int i = 0; i < fa; i++) {
            M[i][j] = A[i][j];
        }
        // Copiar filas de B debajo
        for (int i = 0; i < fb; i++) {
            M[fa + i][j] = B[i][j];
        }
    }
    return M;
}

// Convierte una matriz en un vector 1D (como A(:) en MATLAB, orden columna por columna)
double* flatten_mat(double **A, int f, int c, int &n_out) {
    n_out = f * c;
    double *v = new double[n_out];
    
    int idx = 0;
    for (int j = 0; j < c; j++) {
        for (int i = 0; i < f; i++) {
            v[idx] = A[i][j];
            idx++;
        }
    }
    return v;
}

// Función maestra para matrices usando un puntero a una función de vectores
double** funeach_mat(double **A, int f, int c, double* (*vec_func)(double*, int)) {
    double **M = new double*[f];
    for (int i = 0; i < f; i++) {
        M[i] = vec_func(A[i], c); // Ejecuta la función que le pases sobre cada fila
    }
    // ejemplo en main: double **A_exp = map_mat(A, f, c, exp_vect);   // Aplica exponencial a la matriz
    return M;
}


// Aplica una función matemática de <cmath> a cada elemento de un vector
double* apply_scalar_vect(double *a, int n, double (*func)(double)) {
    double *c = new double[n];
    for (int i = 0; i < n; i++) {
        c[i] = func(a[i]); // Llama a la función (ej. sin(x)) ejemplo: double *v_senos = applyscalar_vect(a, n,sin)
    }
    return c;
}

// Aplica una función matemática de <cmath> a cada elemento de una matriz
double** apply_scalar_mat(double **A, int f, int c, double (*func)(double)) {
    double **M = new double*[f];
    for (int i = 0; i < f; i++) {
        M[i] = apply_scalar_vect(A[i], c, func);
    } //double **M_senos = apply_scalar_mat(A, f, c, sin);
    return M;
}


// Devuelve una nueva matriz eliminando la fila 'f_del' y la columna 'c_del'
double** remove_row_col_mat(double **A, int f, int c, int f_del, int c_del) {
    int f_out = f - 1;
    int c_out = c - 1;
    double **M = gen_mat(M, f_out, c_out);
    
    int r_out = 0;
    for (int i = 0; i < f; i++) {
        if (i == f_del) continue; // Salta la fila a eliminar
        int col_out = 0;
        for (int j = 0; j < c; j++) {
            if (j == c_del) continue; // Salta la columna a eliminar
            M[r_out][col_out] = A[i][j];
            col_out++;
        }
        r_out++;
    }
    return M;
}

// Comprueba si una matriz cuadrada es simétrica
bool is_symmetric_mat(double **A, int n, double tolerancia) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Comparamos con un pequeño margen de error por decimales (tolerancia)
            if (fabs(A[i][j] - A[j][i]) > tolerancia) {
                return false;
            }
        }
    }
    return true;
}

// Intercambia la fila r1 con la fila r2 (devuelve una nueva matriz)
double** swap_rows_mat(double **A, int f, int c, int r1, int r2) {
    if (r1 < 0 || r1 >= f || r2 < 0 || r2 >= f) {
        print_error("Indices de fila fuera de rango");
        return NULL;
    }
    
    // Hacemos una copia para no alterar la original
    double **M = coppy_mat(A, f, c);
    
    // Truco con punteros dobles: intercambiamos los punteros de las filas directamente
    double *temp = M[r1];
    M[r1] = M[r2];
    M[r2] = temp;
    
    return M;
}

// Intercambia la columna c1 con la columna c2 (devuelve una nueva matriz)
double** swap_cols_mat(double **A, int f, int c, int c1, int c2) {
    if (c1 < 0 || c1 >= c || c2 < 0 || c2 >= c) {
        print_error("Indices de columna fuera de rango");
        return NULL;
    }
    
    double **M = coppy_mat(A, f, c);
    
    for (int i = 0; i < f; i++) {
        double temp = M[i][c1];
        M[i][c1] = M[i][c2];
        M[i][c2] = temp;
    }
    
    return M;
}


// Busca un valor en la matriz y devuelve su posición (fila y columna) por referencia
						// Retorna true si lo encuentra, false si no está en la matriz
						//Poniendo tolerencia a 0 pues es excatamente ese valor
bool find_val_mat(double **A, int f, int c, double val, int &out_f, int &out_c, double tolerancia) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (fabs( A[i][j] - val ) < tolerancia) {
                out_f = i;
                out_c = j;
                return true; // Encontrado
            }
        }
    }
    return false; // No se encontró el valor
}

// find_mat: Encuentra las coordenadas (filas y columnas) donde los elementos son mayores que un umbral
								// Devuelve una matriz de n_out x 2 donde cada fila es [fila, columna]
double** find_gt_mat(double **A, int f, int c, double umbral, int &n_out) {
    // 1. Contar cuántos cumplen
    n_out = 0;
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (A[i][j] > umbral) n_out++;
        }
    }
    
    if (n_out == 0) return NULL;
    
    // 2. Crear matriz de resultados (n_out filas, 2 columnas: [fila, col])
    double **coords = gen_mat(coords, n_out, 2);
    int idx = 0;
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (A[i][j] > umbral) {
                coords[idx][0] = (double)i;
                coords[idx][1] = (double)j;
                idx++;
            }
        }
    }
    return coords;
}

// Suma de todos los elementos de la matriz
double sum_all_mat(double **A, int f, int c) {
    double suma = 0.0;
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            suma += A[i][j];
        }
    }
    return suma;
}

// Producto de todos los elementos de la matriz
double prod_all_mat(double **A, int f, int c) {
    double producto = 1.0;
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            producto *= A[i][j];
        }
    }
    return producto;
}

// Devuelve el valor máximo absoluto de toda la matriz
double max_mat(double **A, int f, int c) {
    double max_v = A[0][0];
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (A[i][j] > max_v) {
                max_v = A[i][j];
            }
        }
    }
    return max_v;
}

// Valor maximo en valor absoluto de la matriz (este SI es absoluto)
double max_abs_mat(double **A, int f, int c) {
    double m = 0.0;
    for (int i = 0; i < f; i++)
        for (int j = 0; j < c; j++)
            if (fabs(A[i][j]) > m) m = fabs(A[i][j]);
    return m;
}

// Devuelve el valor mínimo absoluto de toda la matriz
double min_mat(double **A, int f, int c) {
    double min_v = A[0][0];
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (A[i][j] < min_v) {
                min_v = A[i][j];
            }
        }
    }
    return min_v;
}

// Genera una matriz (f x c) con números aleatorios uniformes entre 0.0 y 1.0 (rand(f,c) en MATLAB)
double** rand_mat(int f, int c) {
    double **M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = (double)rand() / RAND_MAX;
        }
    }
    return M;
}

// randi_mat: Genera una matriz (f x c) con enteros aleatorios entre min y max
double** randi_mat(int min_val, int max_val, int f, int c) {
    double **M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = (double)(min_val + rand() % ((max_val + 1) - min_val));
        }
    }
    return M;
}

// Genera una matriz (f x c) con distribución normal estándar (randn(f,c) en MATLAB)
double** randn_mat(int f, int c) {
    double **M = gen_mat(M, f, c);
    double PI_ = acos(-1.0);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            double u1 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
            double u2 = ((double)rand() + 1.0) / ((double)RAND_MAX + 1.0);
            double z = sqrt(-2.0 * log(u1)) * cos(2.0 * PI_ * u2);
            M[i][j] = z;
        }
    }
    return M;
}

// Limita los valores de una matriz entre un mínimo y un máximo
double** clamp_mat(double **A, int f, int c, double min_val, double max_val) {
    double **M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (A[i][j] < min_val) {
                M[i][j] = min_val;
            } else if (A[i][j] > max_val) {
                M[i][j] = max_val;
            } else {
                M[i][j] = A[i][j];
            }
        }
    }
    return M;
}

// reshape: Reorganiza los datos de una matriz en una nueva de dimensiones (nuevo_f x nuevo_c)
double** reshape_mat(double **A, int f, int c, int nuevo_f, int nuevo_c) {
    if (f * c != nuevo_f * nuevo_c) {
        print_error("El numero total de elementos no coincide para hacer reshape");
        return NULL;
    }
    
    // 1. Aplanamos la matriz actual en un vector temporal 1D
    int n_temp;
    double *temp_v = flatten_mat(A, f, c, n_temp);
    
    // 2. Creamos la nueva matriz y la rellenamos secuencialmente por columnas (estilo MATLAB)
    double **M = gen_mat(M, nuevo_f, nuevo_c);
    int idx = 0;
    for (int j = 0; j < nuevo_c; j++) {
        for (int i = 0; i < nuevo_f; i++) {
            M[i][j] = temp_v[idx];
            idx++;
        }
    }
    
    // 3. Liberar memoria temporal del vector
    delete[] temp_v;
    
    return M;
}

// Matriz diagonal n x n a partir de un vector, diag(v) en MATLAB
double** diag_mat(double *v, int n) {
    double **M = zeros_mat(n, n);
    for (int i = 0; i < n; i++) M[i][i] = v[i];
    return M;
}

// Extrae la diagonal principal de una matriz cuadrada como vector
double* get_diag_mat(double **A, int n) {
    double *d = new double[n];
    for (int i = 0; i < n; i++) d[i] = A[i][i];
    return d;
}

// Producto matriz x vector: y = A*x  (A de f x c, x de tamano n = c)
double* prod_mat_vect(double **A, int f, int c, double *x, int n) {
    if (c != n) {
        print_error_dim("prod_mat_vect: dimensiones incompatibles", f, c, n, 1);
        return NULL;
    }
    double *y = new double[f];
    for (int i = 0; i < f; i++) {
        double s = 0.0;
        for (int j = 0; j < c; j++) s += A[i][j] * x[j];
        y[i] = s;
    }
    return y;
}


// ============================================================================
// FUNCIONES DE MANIPULACION DE ARCHIVOS
// ============================================================================

// Comprueba si un archivo existe y se puede abrir
bool file_exists(const char* filename) {
    ifstream f(filename, ios::in);
    return f.good();
}

// Salta espacios y lineas de comentario que empiezan por '#' (cabeceras de gnuplot/numpy)
void skip_comments(ifstream &f) {
    while (f >> ws && f.peek() == '#') {
        char ch;
        while (f.get(ch) && ch != '\n') { }   // descarta el resto de la linea
    }
}

// Cuenta TODAS las lineas de texto de un archivo (incluidas cabeceras y vacias)
int count_text_lines_file(const char* filename) {
    ifstream f(filename, ios::in);
    if (!f) {
        print_error("No se pudo abrir el archivo", filename);
        return -1;
    }
    int n = 0;
    bool con_texto = false;   // la linea actual tiene algun caracter
    char ch;
    while (f.get(ch)) {
        if (ch == '\n') { n++; con_texto = false; }
        else con_texto = true;
    }
    if (con_texto) n++;       // ultima linea sin salto de linea final
    return n;
}

// Cuenta cuántas líneas (puntos) tiene un archivo de datos con 2 columnas
int count_lines_file(const char* filename) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo", filename);
        return -1;
    }
    
    int m = 0;
    double x, y;
    // Lectura segura: el while comprueba si se pudo leer con éxito la pareja x, y
    while (fentrada >> x >> y) {
        m++;
    }
    fentrada.close();
    return m;
}

// Lee un archivo de 2 columnas y carga los datos en los vectores dinámicos x e y preexistentes
void read_xy_file(const char* filename, double *x, double *y, int m) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo para lectura", filename);
        return;
    }
    
    for (int i = 0; i < m; i++) {
        fentrada >> x[i] >> y[i];
    }
    fentrada.close();
}

// Guarda dos vectores x e y en un archivo de texto con dos columnas separadas por tabulador
void save_xy_file(const char* filename, double *x, double *y, int m) {
    ofstream fsalida(filename, ios::out);
    if (!fsalida) {
        print_error("No se pudo crear el archivo para guardado", filename);
        return;
    }
    
    for (int i = 0; i < m; i++) {
        fsalida << x[i] << "\t" << y[i] << endl;
    }
    fsalida.close();
    print_info("Datos guardados exitosamente", filename);
}

// Guarda una matriz completa (f x c) en un archivo de texto tabulado
void save_mat_file(const char* filename, double **A, int f, int c) {
    ofstream fsalida(filename, ios::out);
    if (!fsalida) {
        print_error("No se pudo abrir el archivo para guardar la matriz", filename);
        return;
    }
    
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            fsalida << A[i][j] << (j < c - 1 ? "\t" : "");
        }
        fsalida << endl;
    }
    fsalida.close();
}

// Lee una matriz de dimensiones conocidas (f x c) desde un archivo de texto
double** read_mat_file(const char* filename, int f, int c) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo para leer la matriz", filename);
        return NULL;
    }
    
    double **M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (!(fentrada >> M[i][j])) {
                print_warning("Faltaban datos en el archivo", filename);
            }
        }
    }
    fentrada.close();
    return M;
}

// Cuenta cuántos elementos (filas) tiene un archivo de una sola columna
int count_rows_single_file(const char* filename) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo", filename);
        return -1;
    }
    
    int m = 0;
    double val;
    while (fentrada >> val) {
        m++;
    }
    fentrada.close();
    return m;
}

// Lee un archivo de una sola columna y lo devuelve como un vector dinámico 1D
double* read_single_vector_file(const char* filename, int &n_out) {
    n_out = count_rows_single_file(filename);
    if (n_out <= 0) return NULL;
    
    double *v = new double[n_out];
    ifstream fentrada(filename, ios::in);
    for (int i = 0; i < n_out; i++) {
        fentrada >> v[i];
    }
    fentrada.close();
    return v;
}

// Guarda un vector dinámico 1D en un archivo de texto de una sola columna
void save_vector_file(const char* filename, double *v, int n) {
    ofstream fsalida(filename, ios::out);
    if (!fsalida) {
        print_error("No se pudo crear el archivo para guardar el vector", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        fsalida << v[i] << endl;
    }
    fsalida.close();
    print_info("Vector guardado exitosamente", filename);
}

// Cuenta el número de filas y columnas de un archivo de matriz desconocido sin usar sstream
bool get_file_dimensions(const char* filename, int &f_out, int &c_out) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo", filename);
        return false;
    }
    
    f_out = 0;
    c_out = 0;
    
    // 1. Contar cuántas columnas hay en la primera línea
    double temp_val;
    char ch;
    
    // Leemos números de la primera línea hasta que se acabe o cambie de línea
    while (fentrada >> temp_val) {
        c_out++;
        // Verificamos si el siguiente carácter es un salto de línea
        ch = fentrada.peek();
        if (ch == '\n' || ch == '\r') {
            break; // Salimos del bucle al terminar la primera fila
        }
    }
    
    if (c_out == 0) {
        print_error("El archivo esta vacio", filename);
        fentrada.close();
        return false; // Archivo vacío
    }
    
    // 2. Contar el total de elementos en todo el archivo para sacar el número exacto de filas
    fentrada.clear(); // Limpiamos posibles estados de fin de archivo
    fentrada.seekg(0, ios::beg); // Volvemos al inicio del archivo
    
    int total_elementos = 0;
    while (fentrada >> temp_val) {
        total_elementos++;
    }
    
    fentrada.close();
    
    // El número de filas es el total de números divididos entre las columnas contadas
    f_out = total_elementos / c_out;
    
    return true;
}

// Lee una matriz SIN conocer sus dimensiones (las calcula con get_file_dimensions)
// Uso:  int f, c;  double **A = read_mat_auto("datos.txt", f, c);
double** read_mat_auto(const char* filename, int &f_out, int &c_out) {
    if (!get_file_dimensions(filename, f_out, c_out)) return NULL;
    return read_mat_file(filename, f_out, c_out);
}


