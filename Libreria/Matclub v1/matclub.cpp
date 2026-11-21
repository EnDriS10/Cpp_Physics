
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

// Combinatoria (n en k)
	// Descripción: Calcula el número de combinaciones posibles de 'k' elementos elegidos de un conjunto de 'n'.
double comb(int n, int k) {
    if (k < 0 || k > n) return 0.0;
    if (k > n - k) k = n - k;
    double r = 1.0;
    for (int i = 1; i <= k; i++) r = r * (n - k + i) / i;
    return round(r);
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

// Devuelve el numero aureo (1+sqrt(5))/2 redondeado a 'n' decimales
// Descripcion: Igual que PI(n). Se usa en seccion_aurea (el factor de reduccion es 1/PHI = PHI-1).
double PHI(int n) {
    /*
    Ejemplo de uso:
        double fi = PHI(6); // Devuelve 1.618034
    */
    double base_phi = (1.0 + sqrt(5.0)) / 2.0;
    double factor = pow(10.0, n);
    return round(base_phi * factor) / factor;
}

// Minimo de una funcion unimodal por el metodo de la seccion aurea
// Descripcion: Reduce el intervalo [a,b] por el factor 1/PHI en cada paso, sin usar derivadas,
//              hasta que su longitud sea menor que 'tol'. Devuelve la posicion x del minimo.
double seccion_aurea(double (*f)(double), double a, double b, double tol) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return (x - 2.0) * (x - 2.0) + 1.0; }
        double xmin = seccion_aurea(mi_func, -10.0, 10.0, 1e-8); // Devuelve ~2.0
    */
    if (tol <= 0.0) { print_error("seccion_aurea: tol debe ser > 0"); return MC_NAN; }
    if (a > b) intercambiar_elem(a, b);
    const double r = 1.0 / PHI(15);
    double c = b - r * (b - a), d = a + r * (b - a);
    double fc = f(c), fd = f(d);
    while (fabs(b - a) > tol) {
        if (fc < fd) { b = d; d = c; fd = fc; c = b - r * (b - a); fc = f(c); }
        else         { a = c; c = d; fc = fd; d = a + r * (b - a); fd = f(d); }
    }
    return 0.5 * (a + b);
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

// Generador de variables aleatorias mediante distribución de probabilidad dada
// Descripción: Genera 'N' muestras aleatorias del 'dominio' basadas en sus 'probabilidades' asociadas.
double* gen_distrib_prob(double *dominio, double *probabilidades, int n_dom, int N) {
    /*
    Ejemplo de uso:
        double dominio[] = {2, 4, 7, 8};
        double distrib_prob[] = {0.2, 0.1, 0.5, 0.2};
        double *muestras = gen_distrib_prob(dominio, distrib_prob, 4, 1000);
    */
    double *R = new double[N];
    double *prob_cum = cumsum_vect(probabilidades, n_dom); // Usa tu función ya programada
    
    for (int i = 0; i < N; i++) {
        // r es un aleatorio uniforme entre 0 y 1
        double r = (double)rand() / RAND_MAX;
        
        for (int j = 0; j < n_dom; j++) {
            if (r <= prob_cum[j]) {
                R[i] = dominio[j];
                break;
            }
        }
    }
    
    delete[] prob_cum;
    return R;
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




// ============================================================================
// METODOS NUMERICOS PARA BUSQUEDA DE RAICES (CEROS)
// ============================================================================

// Método de la Biseccion (Una sola raiz)
double biseccion(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int max_iter) {
    if (f(x1) * f(x2) >= 0.0) {
        print_error("f(x1) y f(x2) deben tener signos opuestos");
        return MC_NAN; 
    }

    double x3 = 0.0;
    int iter = 0;

    do {
        x3 = (x1 + x2) / 2.0;
        if (f(x3) * f(x1) < 0.0) {
            x2 = x3;
        } else {
            x1 = x3;
        }
        iter++;
    } while ((fabs(x2 - x1) > 2.0 * tol1 && fabs(f(x3)) > tol2) && iter < max_iter);

    return x3;
}

// Biseccion Multiple: Busca multiples raices en un intervalo [a, b]
double* biseccion_multi(double (*f)(double), double a, double b, 
                        int subintervalos, double tol, int &num_raices) {
    
    // Reserva de memoria al estilo de la libreria
    double* raices = new double[subintervalos]; 
    num_raices = 0;
    double paso = (b - a) / subintervalos;

    for (int i = 0; i < subintervalos; ++i) {
        double x1 = a + i * paso;
        double x2 = x1 + paso;

        if (f(x1) * f(x2) < 0.0) {
            double r = biseccion(f, x1, x2, tol, tol, 100);
            // Uso de las utilidades isNaN e isRoot de matclub_2
            if (!isNaN(r) && !isRoot(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        } else if (fabs(f(x1)) < tol && !isRoot(raices, num_raices, x1, 1e-3)) {
            raices[num_raices] = x1;
            num_raices++;
        }
    }
    
    // Si no se encontraron raices, limpiamos memoria y devolvemos nulo
    if (num_raices == 0) {
        delete[] raices;
        return NULL;
    }
    
    return raices;
}

// Método de la Secante (Una sola raiz)
double secante(double (*f)(double), double x0, double x1, 
               double tol1, double tol2, int max_iter) {
    if (fabs(f(x0)) < fabs(f(x1))) {
        intercambiar_elem(x0, x1); // Uso de tu funcion de intercambio
    }

    double x2 = 0.0, dx = 0.0;
    int iter = 0;

    do {
        double f0 = f(x0);
        double f1 = f(x1);

        if (fabs(f0 - f1) < 1e-12) break;

        x2 = x1 - f1 * ((x0 - x1) / (f0 - f1));
        dx = x2 - x1;

        x0 = x1;
        x1 = x2;
        iter++;
    } while ((fabs(f(x2)) > tol1 || fabs(dx) > tol2) && iter < max_iter);

    return x2;
}

// Método de Newton (Una sola raiz)
double newton(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int max_iter) {
    double x1 = x0;
    double dx = 0.0;
    int iter = 0;

    do {
        double fx = f(x0);
        double dfx = df(x0);

        if (fx != 0.0 && dfx != 0.0) {
            x1 = x0 - (fx / dfx);
            dx = x1 - x0;
            x0 = x1;
        } else {
            break;
        }
        iter++;
    } while ((fabs(f(x1)) > tol1 || fabs(dx) > tol2) && iter < max_iter);

    return x1;
}

// Newton Multiple: Busca multiples raices lanzando Newton desde varios puntos
double* newton_multi(double (*f)(double), double (*df)(double), 
                     double a, double b, int puntos_inicio, double tol, int &num_raices) {
    
    double* raices = new double[puntos_inicio + 1];
    num_raices = 0;
    double paso = (b - a) / puntos_inicio;

    for (int i = 0; i <= puntos_inicio; ++i) {
        double x0 = a + i * paso;
        double r = newton(f, df, x0, tol, tol, 100);

        if (!isNaN(r) && r >= a && r <= b && fabs(f(r)) < tol) {
            if (!isRoot(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        }
    }
    
    // Si no se encontraron raices, limpiamos memoria y devolvemos nulo
    if (num_raices == 0) {
        delete[] raices;
        return NULL;
    }
    
    return raices;
}



// ============================================================================
// RESOLUCION DE SISTEMAS LINEALES
// ============================================================================

// ----------------------------------------------------------------------------
// 1. FACTORIZACION LU Y RESOLUCION
// ----------------------------------------------------------------------------

// Factorización LU (Forma 1 - Descomposición de Doolittle)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma1(double **A, int n, double **L, double **U) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                // Elementos de U (diagonal y por encima)
                double sum = 0.0;
                for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
                U[i][j] = A[i][j] - sum;

                // Diagonal de L es 1.0 (Doolittle)
                if (i == j) L[i][j] = 1.0; 
                else L[i][j] = 0.0;
            } else {
                // Elementos de L (por debajo de la diagonal)
                double sum = 0.0;
                for (int k = 0; k < j; k++) sum += L[i][k] * U[k][j];
                
                if (U[j][j] == 0.0) {
                    print_warning("Cero en la diagonal de U. La factorizacion LU puede fallar.");
                }
                L[i][j] = (A[i][j] - sum) / U[j][j];
                U[i][j] = 0.0;
            }
        }
    }
}

// Resuelve Ax = b usando LU Forma 1
double* lu_forma1_sol(double **A, double *b, int n) {
    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    double *z = new double[n];
    double *x = new double[n];

    // 1. Obtener L y U
    lu_forma1(A, n, L, U);

    // 2. Lz = b (Sustitución progresiva)
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) sum += L[i][j] * z[j];
        z[i] = b[i] - sum;
    }

    // 3. Ux = z (Sustitución regresiva)
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) sum += U[i][j] * x[j];
        x[i] = (z[i] - sum) / U[i][i];
    }

    del_mat(L, n);
    del_mat(U, n);
    delete[] z;
    return x;
}

// Factorización LU (Forma 2 - Alternando fila U y columna L)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
void lu_forma2(double **A, int n, double **L, double **U) {
    for (int i = 0; i < n; i++) {
        // Obtención de una fila de U
        for (int j = i; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }
        
        // Obtención de una columna de L
        for (int j = i; j < n; j++) {
            if (j == i) {
                L[j][i] = 1.0; // Hacemos uno los elementos de la diagonal de L
            } else {
                double sum = 0.0;
                for (int k = 0; k < i; k++) sum += L[j][k] * U[k][i];
                
                if (U[i][i] == 0.0) {
                    print_warning("Cero en la diagonal de U. La factorizacion LU puede fallar.");
                }
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }
    }
}

// Resuelve Ax = b usando LU Forma 2
double* lu_forma2_sol(double **A, double *b, int n) {
    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    double *z = new double[n];
    double *x = new double[n];

    // 1. Obtener L y U a través de la nueva función void
    lu_forma2(A, n, L, U);

    // 2. Lz = b (Sustitución progresiva)
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) sum += L[i][j] * z[j];
        z[i] = b[i] - sum;
    }
    
    // 3. Ux = z (Sustitución regresiva)
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) sum += U[i][j] * x[j];
        x[i] = (z[i] - sum) / U[i][i];
    }

    del_mat(L, n); 
    del_mat(U, n); 
    delete[] z;
    
    return x;
}

// ----------------------------------------------------------------------------
// 2. METODOS DE ELIMINACION Y MATRICES SINGULARES (Gauss y Gauss-Jordan)
// ----------------------------------------------------------------------------

// Eliminación de Gauss con pivoteo parcial
double* gauss_solve(double **A, double *b, int n) {
    // Trabajamos sobre copias para no destruir las matrices originales
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    double *x = new double[n];

    for (int j = 0; j < n - 1; j++) {
        // 1. Pivoteo parcial para evitar división por cero y reducir errores de redondeo
        double pivote = fabs(M[j][j]);
        int filapivote = j;
        for (int i = j + 1; i < n; i++) {
            if (fabs(M[i][j]) > pivote) {
                pivote = fabs(M[i][j]);
                filapivote = i;
            }
        }

        // Intercambio de filas si es necesario
        if (filapivote != j) {
            for (int k = 0; k < n; k++) intercambiar_elem(M[j][k], M[filapivote][k]);
            intercambiar_elem(vb[j], vb[filapivote]);
        }

        if (fabs(M[j][j]) < 1e-12) {
            print_error("Matriz singular o casi singular detectada en Gauss.");
            return NULL;
        }

        // 2. Hacer ceros por debajo de la diagonal
        for (int i = j + 1; i < n; i++) {
            double factor = M[i][j] / M[j][j]; // Razón de coeficientes
            for (int k = j; k < n; k++) {
                M[i][k] = M[i][k] - factor * M[j][k];
            }
            vb[i] = vb[i] - factor * vb[j];
        }
    }

    // 3. Sustitución regresiva
    for (int j = n - 1; j >= 0; j--) {
        x[j] = vb[j];
        for (int k = j + 1; k < n; k++) {
            x[j] = x[j] - M[j][k] * x[k];
        }
        x[j] = x[j] / M[j][j];
    }

    del_mat(M, n); delete[] vb;
    return x;
}

// Método de Gauss-Jordan (Diagonal a 1, ceros arriba y abajo)
double* gauss_jordan_solve(double **A, double *b, int n) {
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    for (int i = 0; i < n; i++) {
        // Pivoteo
        double pivote = fabs(M[i][i]);
        int filapivote = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(M[k][i]) > pivote) {
                pivote = fabs(M[k][i]);
                filapivote = k;
            }
        }
        if (filapivote != i) {
            for (int k = 0; k < n; k++) intercambiar_elem(M[i][k], M[filapivote][k]);
            intercambiar_elem(vb[i], vb[filapivote]);
        }
        
        // Normalizar la fila pivote para que el elemento diagonal sea 1
        double divisor = M[i][i];
        if (fabs(divisor) < 1e-12) {
            print_error("Matriz singular detectada en Gauss-Jordan.");
            return NULL;
        }
        for (int j = 0; j < n; j++) M[i][j] /= divisor;
        vb[i] /= divisor;
        
        // Hacer cero el resto de la columna i (por encima y por debajo)
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = M[k][i];
                for (int j = 0; j < n; j++) M[k][j] -= factor * M[i][j];
                vb[k] -= factor * vb[i];
            }
        }
    }
    
    del_mat(M, n); 
    return vb; // vb se ha transformado en el vector solución
}


// ----------------------------------------------------------------------------
// 3. SISTEMAS ESPECIALES
// ----------------------------------------------------------------------------

// Algoritmo de Thomas (Sistemas Tridiagonales)
// Los vectores a, b, c son las diagonales (inferior, principal, superior)

// Se le pasa la matriz completa A y el vector independiente f.
// La funcion extrae las diagonales automaticamente.
double* tridiag_solve(double **A, double *f, int n) {
    // 1. Extraccion de las diagonales de la matriz A
    double *a = new double[n - 1]; // Diagonal inferior
    double *b = new double[n];     // Diagonal principal
    double *c = new double[n - 1]; // Diagonal superior

    for (int i = 0; i < n; i++) {
        b[i] = A[i][i];
        if (i < n - 1) {
            a[i] = A[i + 1][i]; // Elemento justo debajo de la diagonal
            c[i] = A[i][i + 1]; // Elemento justo encima de la diagonal
        }
    }

    // 2. Vectores auxiliares para el Algoritmo de Thomas
    double *alpha = new double[n];
    double *beta = new double[n];
    double *z = new double[n];
    double *x = new double[n];

    // Paso 1: Factorización LU y Sustitución Progresiva (L * z = f)
    beta[0] = b[0];
    z[0] = f[0];

    for (int i = 1; i < n; i++) {
        if (beta[i - 1] == 0.0) {
            print_warning("Cero en la diagonal durante el algoritmo de Thomas (posible division por cero).");
        }
        alpha[i] = a[i - 1] / beta[i - 1];
        beta[i] = b[i] - alpha[i] * c[i - 1];
        z[i] = f[i] - alpha[i] * z[i - 1];
    }

    // Paso 2: Sustitución Regresiva (U * x = z)
    x[n - 1] = z[n - 1] / beta[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = (z[i] - c[i] * x[i + 1]) / beta[i];
    }

    // 3. Liberar toda la memoria temporal utilizada
    delete[] a; 
    delete[] b; 
    delete[] c;
    delete[] alpha; 
    delete[] beta; 
    delete[] z;

    return x;
}


// ----------------------------------------------------------------------------
// 4. METODOS ITERATIVOS
// ----------------------------------------------------------------------------

/// Función Auxiliar: Comprueba estrictamente si una matriz es diagonalmente dominante
bool check_dominancia(double **A, int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) sum += fabs(A[i][j]);
        }
        // Condición teórica: |A_ii| >= sum_{j!=i} |A_ij|
        if (fabs(A[i][i]) < sum) {
            return false; 
        }
    }
    return true;
}

// Función Auxiliar: Reordena las filas (A y b) solo si la matriz no es dominante de entrada
bool reorder_diagonals(double **A, double *b, int n) {
    // 1. Si ya es dominante de fábrica, no alteramos el sistema original
    if (check_dominancia(A, n)) {
        return true; 
    }

    // 2. Si no lo es, intentamos rescatarla reordenando el mayor elemento a la diagonal
    bool swapped = false;
    for (int i = 0; i < n; i++) {
        int max_row = i;
        double max_val = fabs(A[i][i]);
        
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > max_val) {
                max_val = fabs(A[k][i]);
                max_row = k;
            }
        }
        
        if (max_row != i) {
            for (int j = 0; j < n; j++) {
                intercambiar_elem(A[i][j], A[max_row][j]);
            }
            intercambiar_elem(b[i], b[max_row]);
            swapped = true;
        }
    }
    
    // 3. Comprobar si el "Plan B" (reordenamiento) logró hacerla dominante
    bool es_dominante = check_dominancia(A, n);
    
    if (swapped) print_info("El sistema original no era optimo. Ha sido reordenado por filas.");
    if (!es_dominante) {
        print_warning("Incluso tras reordenar, la matriz no es diagonalmente dominante. La convergencia NO esta garantizada.");
    }
    
    return es_dominante;
}


// Método Iterativo de Jacobi (Desplazamientos simultáneos)
double* jacobi_solve(double **A, double *b, int n, double tol, int max_iter) {
    // 1. Trabajamos con copias para no destruir las matrices originales del main
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    // 2. Intentar hacer la matriz diagonalmente dominante
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    // 3. Aproximación inicial: x_i^(0) = b_i / A_ii
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Jacobi no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
    }

    int iter = 0;
    double error = tol + 1.0;

    // 4. Bucle principal de Jacobi
    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Jacobi usa exclusivamente los valores de la iteración anterior oldx[j]
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * oldx[j];
                }
            }
        }

        // Calculamos error evaluando la norma euclidiana de la diferencia
        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;

        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        iter++;
    }
    
    if (iter == max_iter) print_warning("Jacobi alcanzo max_iter sin converger.");
    
    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}


// Método Iterativo de Gauss-Seidel (Desplazamientos sucesivos)
double* gauss_seidel_solve(double **A, double *b, int n, double tol, int max_iter ) {
    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. Gauss-Seidel no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
        newx[i] = oldx[i];
    }

    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        
        for (int i = 0; i < n; i++) {
            newx[i] = vb[i] / M[i][i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    // Gauss-Seidel usa newx[j] porque el valor se actualiza inmediatamente
                    newx[i] = newx[i] - (M[i][j] / M[i][i]) * newx[j]; 
                }
            }
        }

        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    if (iter == max_iter) print_warning("Gauss-Seidel alcanzo max_iter sin converger.");

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}


// Método de Sobrerrelajación (SOR) - Extensión de Gauss-Seidel
// El valor óptimo de w está entre 1 y 2. Para w=1 es idéntico a Gauss-Seidel.
double* sor_solve(double **A, double *b, int n, double w, double tol, int max_iter) {
    if (w <= 0.0 || w >= 2.0) {
        print_error("El factor de relajacion w debe estar estrictamente entre 0 y 2 para evitar divergencias.");
        return NULL;
    }

    double **M = coppy_mat(A, n, n);
    double *vb = copy_vect(b, n);
    
    reorder_diagonals(M, vb, n);

    double *oldx = new double[n];
    double *newx = new double[n];
    
    for (int i = 0; i < n; i++) {
        if (fabs(M[i][i]) < 1e-12) {
            print_error("Cero en la diagonal detectado. SOR no puede continuar.");
            del_mat(M, n); delete[] vb; delete[] oldx; delete[] newx;
            return NULL;
        }
        oldx[i] = vb[i] / M[i][i];
        newx[i] = oldx[i];
    }

    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) oldx[i] = newx[i];
        
        for (int i = 0; i < n; i++) {
            // Calcular el valor temporal como si fuera Gauss-Seidel
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += M[i][j] * newx[j];
                }
            }
            
            // Aplicar la corrección con el factor de relajación w multiplicando al residuo
            newx[i] = oldx[i] + (w / M[i][i]) * (vb[i] - sum - M[i][i] * oldx[i]);
        }

        double *rest = resta_vect(newx, oldx, n);
        error = mod_vect(rest, n);
        delete[] rest;
        
        iter++;
    }

    if (iter == max_iter) print_warning("SOR alcanzo max_iter sin converger.");

    del_mat(M, n); delete[] vb; delete[] oldx;
    return newx;
}



// ============================================================================
// DETERMINANTES E INVERSAS (MÚLTIPLES MÉTODOS)
// ============================================================================

// 1A. Determinante usando Eliminación Gaussiana (con pivoteo)
double det_gauss(double **A, int n) {
    double **M = coppy_mat(A, n, n);
    double det = 1.0;
    int swaps = 0;

    for (int j = 0; j < n - 1; j++) {
        double pivote = fabs(M[j][j]);
        int filapivote = j;
        for (int i = j + 1; i < n; i++) {
            if (fabs(M[i][j]) > pivote) {
                pivote = fabs(M[i][j]);
                filapivote = i;
            }
        }

        if (filapivote != j) {
            for (int k = 0; k < n; k++) intercambiar_elem(M[j][k], M[filapivote][k]);
            swaps++; // Contamos los intercambios de filas
        }

        if (fabs(M[j][j]) < 1e-12) {
            del_mat(M, n);
            return 0.0; // Rango menor que n, determinante es cero
        }

        for (int i = j + 1; i < n; i++) {
            double factor = M[i][j] / M[j][j];
            for (int k = j; k < n; k++) {
                M[i][k] = M[i][k] - factor * M[j][k];
            }
        }
    }

    // El determinante es el producto de la diagonal de la matriz triangularizada
    for (int i = 0; i < n; i++) det *= M[i][i];
    
    // Aplicamos (-1)^swaps por los intercambios de filas
    if (swaps % 2 != 0) det = -det;

    del_mat(M, n);
    return det;
}

// 1B. Determinante usando Factorización LU (Doolittle)
double det_lu(double **A, int n) {
    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    
    // Llamamos a la función de descomposición que creaste antes
    lu_forma1(A, n, L, U); 

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        det *= U[i][i]; // El determinante es el producto de la diagonal de U
    }

    del_mat(L, n);
    del_mat(U, n);
    
    // Si la diagonal tiene ceros absolutos, el det es 0
    if (fabs(det) < 1e-12) return 0.0;
    return det;
}

// 2A. Inversa de una matriz usando Gauss-Jordan
double** inv_gj(double **A, int n) {
    if (fabs(det_gauss(A, n)) < 1e-12) {
        print_error("No tiene inversa. Matriz singular o determinante cero.");
        return NULL;
    }

    // Crear matriz aumentada [A | I] de n x 2n
    double **M = gen_mat(M, n, 2 * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) M[i][j] = A[i][j];
        for (int j = n; j < 2 * n; j++) M[i][j] = (j - n == i) ? 1.0 : 0.0;
    }

    // Reducción de Gauss-Jordan
    for (int i = 0; i < n; i++) {
        // Pivoteo
        double pivote = fabs(M[i][i]);
        int filapivote = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(M[k][i]) > pivote) {
                pivote = fabs(M[k][i]);
                filapivote = k;
            }
        }
        if (filapivote != i) {
            for (int k = 0; k < 2 * n; k++) intercambiar_elem(M[i][k], M[filapivote][k]);
        }
        
        // Normalizar
        double divisor = M[i][i];
        for (int j = 0; j < 2 * n; j++) M[i][j] /= divisor;
        
        // Hacer ceros el resto de la columna
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = M[k][i];
                for (int j = 0; j < 2 * n; j++) M[k][j] -= factor * M[i][j];
            }
        }
    }

    // Extraer la matriz inversa (la mitad derecha)
    double **Inv = gen_mat(Inv, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Inv[i][j] = M[i][j + n];
        }
    }

    del_mat(M, n);
    return Inv;
}

// 2B. Inversa de una matriz usando Factorización LU
double** inv_lu(double **A, int n) {
    if (fabs(det_lu(A, n)) < 1e-12) {
        print_error("No tiene inversa. Matriz singular o determinante cero.");
        return NULL;
    }

    double **L = zeros_mat(n, n);
    double **U = zeros_mat(n, n);
    lu_forma1(A, n, L, U);

    double **Inv = gen_mat(Inv, n, n);
    double *e = new double[n]; // Vector para cada columna de la identidad
    double *z = new double[n]; // Lz = e
    double *x = new double[n]; // Ux = z

    // Calculamos cada columna de la matriz inversa resolviendo LUx = e
    for (int col = 0; col < n; col++) {
        // 1. Generar la columna 'col' de la matriz identidad
        for (int i = 0; i < n; i++) {
            e[i] = (i == col) ? 1.0 : 0.0;
        }

        // 2. Sustitución progresiva (Lz = e)
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) sum += L[i][j] * z[j];
            z[i] = e[i] - sum;
        }

        // 3. Sustitución regresiva (Ux = z)
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++) sum += U[i][j] * x[j];
            x[i] = (z[i] - sum) / U[i][i];
        }

        // 4. Guardar el resultado en la columna correspondiente de la matriz inversa
        for (int i = 0; i < n; i++) {
            Inv[i][col] = x[i];
        }
    }

    del_mat(L, n);
    del_mat(U, n);
    delete[] e;
    delete[] z;
    delete[] x;

    return Inv;
}



// ============================================================================
// SISTEMAS SOBREDETERMINADOS Y REGRESIONES (MINIMOS CUADRADOS)
// ============================================================================


// 0. MOTOR CENTRAL: Resuelve Ax = b para sistemas sobredeterminados (m > n)
		// Devuelve el vector solucion 'x', y por referencia el vector de 'errores' de 
							// cada parametro, y el coeficiente de determinacion 'R2'.
							// -----> Ordinary Least Squares, OLS, minimos cuadrados
double* ols_reg(double **A, double *b, int m, int n, double *&errores, double &R2) {
    if (m <= n) {
        print_error("El sistema no esta sobredeterminado (m debe ser mayor que n).");
        return NULL;
    }

    // 1. Ecuaciones normales: (A^T * A) * x = A^T * b
    double **AT = transpose_mat(A, m, n);
    double **ATA = prod_mat(AT, A, n, m, m, n);  // Matriz cuadrada (n x n)
    double *ATb = prod_mat_vect(AT, n, m, b, m); // Vector (n x 1)

    // 2. Resolver el sistema para encontrar los parametros óptimos (x) usando LU Forma 2
    double *x = lu_forma2_sol(ATA, ATb, n);
    if (x == NULL) {
        print_error("Fallo al resolver minimos cuadrados (A^T*A es singular o casi singular).");
        del_mat(AT, n); del_mat(ATA, n); delete[] ATb;
        return NULL;
    }

    // 3. Calculo del coeficiente de determinacion R2
    double *b_est = prod_mat_vect(A, m, n, x, n);
    double mean_b = mean_vect(b, m);

    double SS_res = 0.0; // Suma de los residuos al cuadrado
    double SS_tot = 0.0; // Suma total al cuadrado
    for (int i = 0; i < m; i++) {
        SS_res += pow(b[i] - b_est[i], 2);
        SS_tot += pow(b[i] - mean_b, 2);
    }
    R2 = (SS_tot == 0.0) ? 1.0 : (1.0 - (SS_res / SS_tot));

    // 4. Calculo de Errores estadisticos (usando la matriz de covarianza con la inversa LU)
    double s2 = SS_res / (m - n); // Varianza residual
    double **ATA_inv = inv_lu(ATA, n); // Cambiado para usar el metodo LU en la inversa
    errores = new double[n];
    
    if (ATA_inv != NULL) {
        for (int j = 0; j < n; j++) {
            // Error estandar del parametro j (raiz de la diagonal de la covarianza)
            errores[j] = sqrt(fabs(s2 * ATA_inv[j][j])); 
        }
        del_mat(ATA_inv, n);
    } else {
        print_warning("No se pudieron calcular los errores de los parametros mediante LU.");
        for (int j = 0; j < n; j++) errores[j] = MC_NAN;
    }

    // Limpieza de memoria
    del_mat(AT, n);
    del_mat(ATA, n);
    delete[] ATb;
    delete[] b_est;

    return x;
}


// 1. Regresión Polinómica: y = a0 + a1*x + a2*x^2 + ... + am*x^m
						// Devuelve un vector con [a0, a1, ..., am]
double* poly_reg(double *x, double *y, int m_datos, int grado, double *&errores, double &R2) {
    int n = grado + 1; // Numero de incognitas (parametros)
    double **A = gen_mat(A, m_datos, n);
    
    // Matriz de Vandermonde truncada
    for (int i = 0; i < m_datos; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = pow(x[i], j);
        }
    }
    
    double *params = ols_reg(A, y, m_datos, n, errores, R2);
    del_mat(A, m_datos);
    return params;
}

// 2. Regresión Lineal: y = a0 + a1*x 
// (Es simplemente un caso particular de la regresion polinomica de grado 1)
double* lin_reg(double *x, double *y, int m_datos, double *&errores, double &R2) {
    return poly_reg(x, y, m_datos, 1, errores, R2);
}

// 3. Regresión Exponencial: y = a * e^(bx)
		// Devuelve [a, b]. Realiza la linealizacion: ln(y) = ln(a) + b*x
double* exp_reg(double *x, double *y, int m_datos, double *&errores, double &R2) {
    double *ln_y = new double[m_datos];
    for (int i = 0; i < m_datos; i++) {
        if (y[i] <= 0.0) {
            print_error("Valores de y deben ser positivos para la regresion exponencial.");
            delete[] ln_y; return NULL;
        }
        ln_y[i] = log(y[i]);
    }

    double *err_lin = NULL;
    double *params_lin = lin_reg(x, ln_y, m_datos, err_lin, R2);
    delete[] ln_y;

    if (params_lin == NULL) return NULL;

    double *params = new double[2];
    params[0] = exp(params_lin[0]); // Deshacemos el ln(a): a = e^A0
    params[1] = params_lin[1];      // b se mantiene igual

    errores = new double[2];
    // Propagacion de errores: si A0 = ln(a) -> a = e^A0 -> Error_a = a * Error_A0
    errores[0] = params[0] * err_lin[0]; 
    errores[1] = err_lin[1];

    delete[] params_lin;
    delete[] err_lin;
    
    return params;
}

// 4. Regresión Logarítmica: y = a + b * ln(x)
// Devuelve [a, b]. Realiza la linealizacion: Y = a + b*X (con X = ln(x))
double* regresion_logaritmica(double *x, double *y, int m_datos, double *&errores, double &R2) {
    double *ln_x = new double[m_datos];
    for (int i = 0; i < m_datos; i++) {
        if (x[i] <= 0.0) {
            print_error("Valores de x deben ser positivos para la regresion logaritmica.");
            delete[] ln_x; return NULL;
        }
        ln_x[i] = log(x[i]);
    }

    double *params = lin_reg(ln_x, y, m_datos, errores, R2);
    delete[] ln_x;
    
    return params;
}

// 5. Regresión Potencial: y = a * x^b
// Devuelve [a, b]. Realiza linealizacion bilogaritmica: ln(y) = ln(a) + b*ln(x)
double* regresion_potencial(double *x, double *y, int m_datos, double *&errores, double &R2) {
    double *ln_x = new double[m_datos];
    double *ln_y = new double[m_datos];
    
    for (int i = 0; i < m_datos; i++) {
        if (x[i] <= 0.0 || y[i] <= 0.0) {
            print_error("Valores de x e y deben ser positivos para regresion potencial.");
            delete[] ln_x; delete[] ln_y; return NULL;
        }
        ln_x[i] = log(x[i]);
        ln_y[i] = log(y[i]);
    }

    double *err_lin = NULL;
    double *params_lin = lin_reg(ln_x, ln_y, m_datos, err_lin, R2);
    delete[] ln_x; delete[] ln_y;

    if (params_lin == NULL) return NULL;

    double *params = new double[2];
    params[0] = exp(params_lin[0]); // a = e^A0
    params[1] = params_lin[1];      // b = A1

    errores = new double[2];
    // Propagacion de errores similar a la exponencial
    errores[0] = params[0] * err_lin[0];
    errores[1] = err_lin[1];

    delete[] params_lin;
    delete[] err_lin;
    
    return params;
}

// 6. Regresión Sinusoidal / Armónica: y = a0 + a1*cos(w*x) + a2*sin(w*x)
// Devuelve [a0, a1, a2]. Requiere que le introduzcas la frecuencia angular 'w'
double* regresion_sinusoidal(double *x, double *y, int m_datos, double w, double *&errores, double &R2) {
    int n = 3;
    double **A = gen_mat(A, m_datos, n);
    
    for (int i = 0; i < m_datos; i++) {
        A[i][0] = 1.0;
        A[i][1] = cos(w * x[i]);
        A[i][2] = sin(w * x[i]);
    }
    
    double *params = ols_reg(A, y, m_datos, n, errores, R2);
    del_mat(A, m_datos);
    
    return params;
}

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
double* spline_coef(double *x, double *y, int n) {
    if (n < 3) { print_error("spline_coef: se necesitan al menos 3 puntos"); return NULL; }
    double *M = new double[n];
    int m = n - 2;
    double *a = new double[m], *b = new double[m], *c = new double[m], *d = new double[m];
    for (int i = 1; i <= m; i++) {
        double h0 = x[i] - x[i - 1], h1 = x[i + 1] - x[i];
        a[i - 1] = h0;
        b[i - 1] = 2.0 * (h0 + h1);
        c[i - 1] = h1;
        d[i - 1] = 6.0 * ((y[i + 1] - y[i]) / h1 - (y[i] - y[i - 1]) / h0);
    }
    for (int i = 1; i < m; i++) {          // eliminacion (Thomas)
        double w = a[i] / b[i - 1];
        b[i] -= w * c[i - 1];
        d[i] -= w * d[i - 1];
    }
    M[0] = 0.0; M[n - 1] = 0.0;
    M[m] = d[m - 1] / b[m - 1];
    for (int i = m - 2; i >= 0; i--) M[i + 1] = (d[i] - c[i] * M[i + 2]) / b[i];
    delete[] a; delete[] b; delete[] c; delete[] d;
    return M;
}
// x debe estar ordenado de menor a mayor. Fuera de [x0, xn-1] extrapola con el tramo extremo.
double spline_eval(double *x, double *y, double *M, int n, double xi) {
    int k = 0;
    while (k < n - 2 && xi > x[k + 1]) k++;
    double h = x[k + 1] - x[k];
    double A = (x[k + 1] - xi) / h, B = (xi - x[k]) / h;
    return A * y[k] + B * y[k + 1] + ((A*A*A - A) * M[k] + (B*B*B - B) * M[k + 1]) * h * h / 6.0;
}
double spline_interp(double *x, double *y, int n, double xi) {
    double *M = spline_coef(x, y, n);
    if (M == NULL) return MC_NAN;
    double r = spline_eval(x, y, M, n, xi);
    delete[] M;
    return r;
}

// 8. ---------------- NEWTON (diferencias divididas) ----------------
// Devuelve c[0..n-1] = f[x0], f[x0,x1], ... Liberar con del_vect.
double* newton_coef(double *x, double *y, int n) {
    if (n < 1) { print_error("newton_coef: n debe ser >= 1"); return NULL; }
    double *c = copy_vect(y, n);
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            double den = x[i] - x[i - j];
            if (den == 0.0) { print_error("newton_coef: hay nodos x repetidos"); delete[] c; return NULL; }
            c[i] = (c[i] - c[i - 1]) / den;
        }
    }
    return c;
}
// Evalua el polinomio de Newton en xi (forma anidada tipo Horner)
double newton_eval(double *x, double *c, int n, double xi) {
    double r = c[n - 1];
    for (int i = n - 2; i >= 0; i--) r = r * (xi - x[i]) + c[i];
    return r;
}

// 9. ---------------- LAGRANGE (forma baricentrica) ----------------
// Devuelve los pesos w[i] = 1 / prod_{j!=i} (x[i]-x[j]). Liberar con del_vect.
double* lagrange_coef(double *x, int n) {
    if (n < 1) { print_error("lagrange_coef: n debe ser >= 1"); return NULL; }
    double *w = new double[n];
    for (int i = 0; i < n; i++) {
        double p = 1.0;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            double den = x[i] - x[j];
            if (den == 0.0) { print_error("lagrange_coef: hay nodos x repetidos"); delete[] w; return NULL; }
            p *= den;
        }
        w[i] = 1.0 / p;
    }
    return w;
}
// Evalua el polinomio de Lagrange en xi con los pesos w (O(n) por punto)
double lagrange_val(double *x, double *y, double *w, int n, double xi) {
    double num = 0.0, den = 0.0;
    for (int i = 0; i < n; i++) {
        double d = xi - x[i];
        if (d == 0.0) return y[i];          // xi coincide con un nodo
        double t = w[i] / d;
        num += t * y[i];
        den += t;
    }
    return num / den;
}


// ============================================================================
// CÁLCULO NUMÉRICO: DERIVADAS, GRADIENTES Y JACOBIANOS
// ============================================================================

// ----------------------------------------------------------------------------
// CALCULO NUMERICO CON FUNCIONES
// ----------------------------------------------------------------------------

// Derivada parcial numérica usando diferencias finitas progresivas.
// Descripción: Calcula el cambio de la función 'f' respecto a la variable 'j' variando 'h'.
double part_derv(double (*f)(double*, int), double *x, int n, int j) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0] + sin(v[1]); }
        double punto[] = {2.0, 3.14};
        double df_dy = part_derv(mi_func, punto, 2, 1);
    */
    double *xh = copy_vect(x, n);
    double h = (fabs(x[j]) > 1e-8) ? 0.0001 * x[j] : 1e-5; 
    
    xh[j] = x[j] + h; 
    double deriv = (f(xh, n) - f(x, n)) / h; // Fórmula de diferencias progresivas
    
    delete[] xh;
    return deriv;
}

// Derivada total
// Descripción: Calcula la derivada total dF/dt sumando el producto de las derivadas parciales por dx_i/dt.
double total_derv(double (*f)(double*, int), double *x, double *dx_dt, int n) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[1]; }
        double punto[] = {2.0, 3.0};
        double velocidades[] = {0.5, -0.1}; // dx/dt, dy/dt
        double dF_dt = total_derv(mi_func, punto, velocidades, 2);
    */
    double dTotal = 0.0;
    for (int j = 0; j < n; j++) {
        dTotal += part_derv(f, x, n, j) * dx_dt[j];
    }
    return dTotal;
}

// Gradiente
// Descripción: Devuelve un vector con todas las derivadas parciales de una función escalar.
double* grad_vect(double (*f)(double*, int), double *x, int n) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0] + v[1]*v[1]; }
        double punto[] = {1.0, 2.0};
        double *grad = grad_vect(mi_func, punto, 2);
        print_vect(grad, 2, "Gradiente");
        delete[] grad;
    */
    double *g = new double[n];
    for (int j = 0; j < n; j++) {
        g[j] = part_derv(f, x, n, j);
    }
    return g;
}

// Matriz Jacobiana
// Descripción: Construye la matriz nxn de derivadas parciales para un sistema de n funciones.
double** jacobian_mat(double (*AF[])(double*, int), double *x, int n) {
    /*
    Ejemplo de uso:
        double (*Sist[2])(double*, int) = {f1, f2};
        double punto[] = {1.0, 1.0};
        double **J = jacobian_mat(Sist, punto, 2);
        print_mat(J, 2, 2, "Jacobiano");
        del_mat(J, 2);
    */
    double **J = gen_mat(J, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            J[i][j] = part_derv(AF[i], x, n, j);
        }
    }
    return J;
}

// Integral Definida Numérica de una función (Regla de Simpson 1/3)
// Descripción: Calcula el área bajo la curva de la función 'f' en el intervalo [a, b] con 'n' paneles (n par).
double integral_def_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return x * x; } // f(x) = x^2
        // Integral de 0 a 2 con 1000 paneles
        double area = integral_def_func(mi_func, 0.0, 2.0, 1000); 
    */
    if (n % 2 != 0) n++; // n debe ser par para Simpson 1/3
    double h = (b - a) / n;
    double suma = f(a) + f(b);
    
    for (int i = 1; i < n; i++) {
        double xi = a + i * h;
        if (i % 2 == 0) suma += 2.0 * f(xi); // Índices pares
        else            suma += 4.0 * f(xi); // Índices impares
    }
    return (h / 3.0) * suma;
}

// Integral Indefinida Numérica de una función sobre un dominio discreto
// Descripción: Evalúa la integral acumulativa de 'f' sobre los puntos del vector 'x', sumando la constante 'C'.
double* integral_indef_func(double (*f)(double), double *x, int n_puntos, double C) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return cos(x); }
        int n = 100;
        double *x = linspace(0.0, 3.14, n);
        double *F_x = integral_indef_func(mi_func, x, n, 0.0); // C = 0
    */
    double *F = new double[n_puntos];
    F[0] = C; // F(x0) = C
    
    for (int i = 0; i < n_puntos - 1; i++) {
        // Área del trapecio entre x[i] y x[i+1]
        double area = (x[i+1] - x[i]) * (f(x[i]) + f(x[i+1])) / 2.0;
        F[i+1] = F[i] + area;
    }
    return F;
}


// ----------------------------------------------------------------------------
// CALCULO NUMERICO CON VECTORES (ARRAYS)
// ----------------------------------------------------------------------------

// Derivada Numérica de datos discretos (Vectorial)
// Descripción: Calcula dy/dx usando diferencias finitas. Diferencias centrales en el interior y progresivas/regresivas en los bordes.
double* deriv_vect(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *dy_dx = deriv_vect(x, y, n);
        print_vect(dy_dx, n, "Derivada");
    */
    if (n < 2) return NULL;
    
    double *dydx = new double[n];
    
    // Borde izquierdo (diferencia progresiva)
    dydx[0] = (y[1] - y[0]) / (x[1] - x[0]);
    
    // Borde derecho (diferencia regresiva)
    dydx[n - 1] = (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]);
    
    // Puntos interiores (diferencia central)
    for (int i = 1; i < n - 1; i++) {
        dydx[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1]);
    }
    
    return dydx;
}

// Integral Numérica de datos discretos (Vectorial)
// Descripción: Calcula la integral definida e indefinida (acumulada) usando la regla del trapecio.
// Nota: 'int_indef' se devuelve por return, 'int_def' se extrae por referencia (&).
double* int_vect(double *x, double *y, int n, double y0, double &int_def) {
    /*
    Ejemplo de uso:
        double area_total;
        double *integral_acumulada = int_vect(x, y, n, 5.0, area_total); // C = 5.0
        cout << "Integral definida (Area): " << area_total << endl;
    */
    if (n < 2) return NULL;
    
    double *int_indef = new double[n];
    int_indef[0] = y0;
    
    for (int i = 0; i < n - 1; i++) {
        double area = (x[i+1] - x[i]) * (y[i] + y[i+1]) / 2.0;
        int_indef[i+1] = int_indef[i] + area;
    }
    
    // La integral definida es el valor acumulado final (sin contar la constante y0 inicial)
    int_def = int_indef[n - 1] - y0; 
    
    // Se pide que la integral definida devuelva también y0 + Int_def según tu MATLAB
    int_def = int_def + y0;
    
    return int_indef;
}

// ============================================================================
// SISTEMAS NO LINEALES
// ============================================================================

// ----------------------------------------------------------------------------
// SUSTITUCIONES SUCESIVAS
// ----------------------------------------------------------------------------

// Comprobador de Condición de Convergencia
// Descripción: Verifica si la suma del valor absoluto de las derivadas parciales de cada función es <= 1.
bool check_convergence_nolin(double (*AF[])(double*, int), double *x, int n) {
    /*
    Ejemplo de uso: (Se utiliza internamente en Jacobi y Gauss-Seidel)
        bool converge = check_convergence_nolin(AF, punto_inicial, n);
    */
    for (int i = 0; i < n; i++) {
        double sum_derivs = 0.0;
        for (int j = 0; j < n; j++) {
            sum_derivs += fabs(part_derv(AF[i], x, n, j));
        }
        if (sum_derivs > 1.0) return false;
    }
    return true;
}

// 1. Jacobi para Sistemas No Lineales
// Descripción: Resuelve iterativamente un sistema reordenado xi = Fi(x1...xn) usando desplazamientos simultáneos.
double* jacobi_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        // Las funciones deben estar despejadas: x = F1(...), y = F2(...)
        double (*Sist[2])(double*, int) = {F1, F2};
        double p0[] = {0.4, 3.0};
        double *sol = jacobi_nolin_sys(Sist, p0, 2, 1e-6, 100);
    */
    if (!check_convergence_nolin(AF, x_init, n)) {
        print_warning("La condicion suficiente de convergencia (suma derivadas <= 1) NO se cumple. Podria diverger.");
    }

    double *x_old = copy_vect(x_init, n);
    double *x_new = new double[n];
    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) x_new[i] = AF[i](x_old, n);

        double *diff = resta_vect(x_new, x_old, n);
        error = mod_vect(diff, n);
        delete[] diff;

        for (int i = 0; i < n; i++) x_old[i] = x_new[i];
        iter++;
    }
    delete[] x_old;
    return x_new;
}

// 2. Gauss-Seidel para Sistemas No Lineales
// Descripción: Similar a Jacobi, pero usa los valores recién calculados (desplazamientos sucesivos).
double* gauss_seidel_nolin(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double (*Sist[2])(double*, int) = {F1, F2};
        double p0[] = {0.4, 3.0};
        double *sol = gauss_seidel_nolin_sys(Sist, p0, 2, 1e-6, 100);
    */
    if (!check_convergence_nolin(AF, x_init, n)) {
        print_warning("La condicion suficiente de convergencia (suma derivadas <= 1) NO se cumple. Podria diverger.");
    }

    double *x_old = copy_vect(x_init, n);
    double *x_new = copy_vect(x_init, n);
    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) x_old[i] = x_new[i];

        for (int i = 0; i < n; i++) x_new[i] = AF[i](x_new, n);

        double *diff = resta_vect(x_new, x_old, n);
        error = mod_vect(diff, n);
        delete[] diff;
        iter++;
    }
    delete[] x_old;
    return x_new;
}



// 3. Newton-Raphson Multivariable (Generalizado para n ecuaciones)
// Descripción: Resuelve el sistema F(x)=0 aproximando las derivadas por diferencias finitas (Jacobiano).
double* newton_raphson_sys(double (*AF[])(double*, int), double *x_init, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        // Las funciones deben estar igualadas a cero: f1(x,y)=0, f2(x,y)=0
        double (*Sist[2])(double*, int) = {f1, f2};
        double p0[] = {0.6, 3.0};
        double *sol = newton_raphson_sys(Sist, p0, 2, 1e-8, 100);
    */
    double *x_old = copy_vect(x_init, n);
    double *x_new = new double[n];
    double *F = new double[n];
    double *dx = NULL;
    
    int iter = 0;
    double error = tol + 1.0;

    while (error > tol && iter < max_iter) {
        for (int i = 0; i < n; i++) F[i] = -AF[i](x_old, n);
        
        double **J = jacobian_mat(AF, x_old, n); // Jacobiano por diferencias finitas
        dx = lu_forma2_sol(J, F, n);
        del_mat(J, n);
        
        if (dx == NULL) {
            print_error("Jacobiano singular en Newton-Raphson.");
            delete[] F; delete[] x_old; delete[] x_new;
            return NULL;
        }

        for (int i = 0; i < n; i++) x_new[i] = x_old[i] + dx[i];

        error = mod_vect(dx, n);
        for (int i = 0; i < n; i++) x_old[i] = x_new[i];
        
        iter++;
        delete[] dx; 
    }
    delete[] F; delete[] x_old;
    return x_new;
}

// 4. Newton-Raphson Array de Soluciones
// Descripción: Ejecuta Newton-Raphson sobre múltiples puntos de inicio. Devuelve una matriz de soluciones.
double** newton_raphson_multi_sys(double (*AF[])(double*, int), double **x_inits, int num_puntos, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double **puntos_iniciales = gen_mat(puntos_iniciales, 3, 2);
        // Llenar puntos_iniciales con 3 semillas distintas (ej. {0.6, 3.0}, {-0.4, 1.7}, etc.)
        double **soluciones = newton_raphson_multi_sys(Sist, puntos_iniciales, 3, 2, 1e-8, 50);
        print_mat(soluciones, 3, 2, "Array de Soluciones");
    */
    double **soluciones = gen_mat(soluciones, num_puntos, n);
    
    for (int k = 0; k < num_puntos; k++) {
        double *sol = newton_raphson_sys(AF, x_inits[k], n, tol, max_iter);
        if (sol != NULL) {
            for (int i = 0; i < n; i++) soluciones[k][i] = sol[i];
            delete[] sol;
        } else {
            for (int i = 0; i < n; i++) soluciones[k][i] = MC_NAN; // Si falla, rellena con NaN
        }
    }
    return soluciones;
}

// ----------------------------------------------------------------------------
// MÉTODOS DE MINIMIZACIÓN: DESCENSO MÁS RÁPIDO (STEEPEST DESCENT)
// ----------------------------------------------------------------------------

// Helper: Calcula S(x) = sum(fi(x)^2) para convertir un sistema de ecuaciones en un problema de minimización
double func_S_error(double (*AF[])(double*, int), double *x, int n) {
    double S = 0.0;
    for (int i = 0; i < n; i++) {
        double val = AF[i](x, n);
        S += val * val;
    }
    return S;
}

// 5. Descenso más rápido / Máxima pendiente (Steepest Descent)
// Descripción: Resuelve el sistema encontrando el mínimo global de la función escalar S(x) = sum(fi^2).
// Utiliza un factor de avance alfa dinámico (backtracking simple) para asegurar que S siempre disminuya.
double* steepest_descent_sys(double (*AF[])(double*, int), double *x_init, int n, double alpha_init, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        // Sist debe contener funciones igualadas a cero. alpha_init = 0.1 o 1.0 suele ser un buen punto de partida.
        double (*Sist[2])(double*, int) = {f1, f2};
        double p0[] = {0.6, 3.0};
        double *sol = steepest_descent_sys(Sist, p0, 2, 0.5, 1e-6, 500);
    */
    double *x_old = copy_vect(x_init, n);
    double *x_new = new double[n];
    double *grad_S = new double[n];
    
    int iter = 0;
    double S_actual = func_S_error(AF, x_old, n);
    
    while (S_actual > tol && iter < max_iter) {
        // 1. Calcular el gradiente de S(x) manualmente usando la regla de la cadena: dS/dxj = 2 * sum( fi * dfi/dxj )
        for (int j = 0; j < n; j++) {
            grad_S[j] = 0.0;
            for (int i = 0; i < n; i++) {
                grad_S[j] += 2.0 * AF[i](x_old, n) * part_derv(AF[i], x_old, n, j);
            }
        }
        
        // 2. Moviéndonos en la dirección negativa del gradiente iterativamente
        double alpha = alpha_init;
        bool mejorado = false;
        
        // Búsqueda lineal simplificada (backtracking): reduce alpha a la mitad si la aproximación no mejora a S(x)
        while (alpha > 1e-8) {
            for (int i = 0; i < n; i++) {
                x_new[i] = x_old[i] - alpha * grad_S[i];
            }
            double S_nuevo = func_S_error(AF, x_new, n);
            
            if (S_nuevo < S_actual) {
                S_actual = S_nuevo;
                mejorado = true;
                break;
            }
            alpha /= 2.0; // Achicamos el paso
        }
        
        if (!mejorado) {
            print_warning("Steepest Descent se atasco en un minimo local o valle plano.");
            break;
        }

        for (int i = 0; i < n; i++) x_old[i] = x_new[i];
        iter++;
    }
    
    if (iter == max_iter) print_warning("Steepest Descent alcanzo max_iter sin converger plenamente.");
    
    delete[] grad_S;
    delete[] x_old;
    return x_new;
}
