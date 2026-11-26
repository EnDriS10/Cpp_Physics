
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

// Numero de elementos de un array estatico (equivalente a length de MATLAB)
// Descripción: Devuelve el tamaño de un array declarado con tamaño fijo (double a[5], int b[3]...). Funciona con cualquier tipo.
// OJO: con arrays dinamicos (new) el compilador no guarda el tamaño; en ese caso hay que conservar la 'n' con la que se crearon.
template <class T, int N> int length_vect(T (&a)[N]) {
    /*
    Ejemplo de uso:
        double datos[] = {4.5, 1.2, 7.8, 3.3};
        int n = length_vect(datos);     // n = 4
        double *m = mean_vect(datos, n);
    */
    return N;
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
// Descripción: Mediana del vector: el valor central de los datos ordenados (media de los dos centrales si n es par). No modifica el vector original.
double median_vect(double *a, int n) { 
    /*
    Ejemplo de uso:
        double a[5] = {5, 1, 4, 2, 3};
        double m = median_vect(a, 5);
        // Resultado: m = 3
    */
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
// Descripción: Media movil de ventana w: cada elemento es la media de los datos de su entorno (centrada; en los bordes la ventana se recorta). Sirve para suavizar ruido. Condicion: w >= 1.
double* movmean_vect(double *a, int n, int w) {
    /*
    Ejemplo de uso:
        double a[6] = {1, 2, 3, 4, 5, 6};
        double *m = movmean_vect(a, 6, 3);
        // Resultado: m = [1.5, 2, 3, 4, 5, 5.5]
    */
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

// Matriz a partir de un array plano (por filas)
// Descripción: Crea una matriz f x c (new) copiando los f*c valores del array v en orden de filas: v[i*c + j] pasa a M[i][j]. Liberar con del_mat(M, f).
double** mat_from_arr(double *v, int f, int c) {
    /*
    Ejemplo de uso:
        double aux[] = { 2, 3, 5, 7 };
        double **A = mat_from_arr(aux, 2, 2);
        print_mat(A, 2, 2, "A");
        del_mat(A, 2);
    */
    double **M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            M[i][j] = v[i * c + j];
        }
    }
    return M;
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
// Descripción: Encuentra una raiz de f en [x1,x2] partiendo el intervalo por la mitad en cada paso. Convergencia lineal, pero SIEMPRE converge.
// Condiciones: f continua y f(x1)*f(x2) < 0 (signos opuestos); no sirve para raices dobles (f no cambia de signo). Se detiene cuando el intervalo mide menos de 2*tol1 o |f| < tol2.
double biseccion(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return x*x*x + x*x - 3*x - 3; }
        double r = biseccion(f, 1.0, 2.0, 1e-10, 1e-10, 100);
        // Resultado: r = 1.732051   (raiz exacta: sqrt(3))
    */
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
// Descripción: Busca TODAS las raices de f en [a,b]: divide el intervalo en 'subintervalos', aplica biseccion en cada uno donde f cambia de signo y elimina duplicados. Devuelve el array y su tamaño en num_raices.
// Condiciones: f continua; no detecta raices dobles ni dos raices dentro de un mismo subintervalo (en ese caso aumenta 'subintervalos').
double* biseccion_multi(double (*f)(double), double a, double b, 
                        int subintervalos, double tol, int &num_raices) {
    /*
    Ejemplo de uso:
        int nr;
        double *r = biseccion_multi(sin, 1.0, 10.0, 100, 1e-10, nr);
        // Resultado: nr = 3 , r = [3.141593, 6.283185, 9.424778]   (raices de sin(x) en [1,10]: pi, 2pi, 3pi)
    */
    
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
// Descripción: Sustituye f'(x) de Newton por la pendiente de la recta por los dos ultimos puntos: x2 = x1 - f1*(x0-x1)/(f0-f1). Convergencia superlineal (p = 1.62) sin calcular derivadas.
// Condiciones: dos puntos iniciales cerca de la raiz (no hace falta que encierren la raiz); puede divergir si f(x0) ~ f(x1). Sigue mientras |f| > tol1 o |dx| > tol2.
double secante(double (*f)(double), double x0, double x1, 
               double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return 3*x + sin(x) - exp(x); }
        double r = secante(f, 1.0, 0.0, 1e-10, 1e-10, 100);
        // Resultado: r = 0.3604217
    */
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
// Descripción: Metodo de Newton-Raphson: x(n+1) = x(n) - f(x)/f'(x). Convergencia cuadratica (p = 2) cuando la raiz es simple y x0 esta cerca.
// Condiciones: f derivable y f'(x) != 0 en el entorno de la raiz; con raices multiples pierde velocidad (usa newton_modificado). Si f' se anula el proceso se detiene. Sigue mientras |f| > tol1 o |dx| > tol2.
double newton(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x)  { return 3*x + sin(x) - exp(x); }
        double df(double x) { return 3 + cos(x) - exp(x); }
        double r = newton(f, df, 0.0, 1e-12, 1e-12, 50);
        // Resultado: r = 0.3604217
    */
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
// Descripción: Busca varias raices de f en [a,b] lanzando Newton desde puntos equiespaciados de [a,b] ('puntos_inicio' de ellos) y descartando las que caen fuera del intervalo o estan repetidas. Devuelve el array (SIN ordenar) y su tamaño en num_raices.
// Condiciones: f derivable y df disponible; no garantiza encontrar todas las raices (depende de los puntos de partida).
double* newton_multi(double (*f)(double), double (*df)(double), 
                     double a, double b, int puntos_inicio, double tol, int &num_raices) {
    /*
    Ejemplo de uso:
        int nr;
        double *r = newton_multi(sin, cos, 1.0, 10.0, 30, 1e-10, nr);
        // Resultado: nr = 3 , r = [3.141593, 9.424778, 6.283185]   (raices de sin(x) en [1,10])
    */
    
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

// Método de la Falsa Posición (regula falsi)
// Descripción: Como la secante, pero conserva siempre un intervalo [x0,x1] que encierra la raiz, asi que no se descontrola como ella. Converge de forma lineal (mas rapido que la biseccion).
// Condiciones: f continua en [x0,x1] y f(x0)*f(x1) < 0. Falla con raices dobles (la funcion puede no cambiar de signo). Sigue mientras |f(x2)| > tol1 o |dx| > tol2.
double falsa_posicion(double (*f)(double), double x0, double x1, double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return 3*x + sin(x) - exp(x); }
        double r = falsa_posicion(f, 0.0, 1.0, 1e-10, 1e-10, 100);   // raiz en 0.3604217
    */
    if (f(x0) * f(x1) >= 0.0) {
        print_error("falsa_posicion: f(x0) y f(x1) deben tener signos opuestos");
        return MC_NAN;
    }
    double x2 = x1, dx = 0.0;
    int iter = 0;
    do {
        double f0 = f(x0), f1 = f(x1);
        double xant = x2;
        x2 = x1 - f1 * ((x0 - x1) / (f0 - f1));
        dx = x2 - xant;
        if (f(x2) * f0 < 0.0) x1 = x2;
        else                  x0 = x2;
        iter++;
    } while ((fabs(f(x2)) > tol1 || fabs(dx) > tol2) && iter < max_iter);
    return x2;
}

// Método de la Iteración de Punto Fijo: x = g(x)
// Descripción: Reescribe f(x)=0 como x=g(x) e itera x(n+1) = g(x(n)) hasta que |x(n+1)-x(n)| < tol. Convergencia lineal.
// Condicion suficiente: g y g' continuas cerca de la raiz con |g'(x)| < 1 y x0 dentro de ese intervalo. Si |g'| > 1 diverge (la funcion avisa y devuelve NaN).
double punto_fijo(double (*g)(double), double x0, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double g(double x) { return sqrt(2*x + 3); }    // de x^2 - 2x - 3 = 0, con |g'(3)| = 1/3 < 1
        double r = punto_fijo(g, 4.0, 1e-10, 200);       // converge a la raiz 3
    */
    double x1 = x0;
    int iter = 0;
    do {
        x0 = x1;
        x1 = g(x0);
        iter++;
        if (isNaN(x1) || fabs(x1) > 1e100) {
            print_error("punto_fijo: la iteracion diverge (comprueba que |g'(x)| < 1 cerca de la raiz)");
            return MC_NAN;
        }
    } while (fabs(x1 - x0) > tol && iter < max_iter);
    if (iter >= max_iter && fabs(x1 - x0) > tol) print_warning("punto_fijo alcanzo max_iter sin converger.");
    return x1;
}

// Método de Muller
// Descripción: Ajusta una parabola por tres puntos y toma la raiz de la parabola mas cercana a x0. Convergencia superlineal (p = 1.84), parecida a Newton, y sin necesitar f'.
// Condiciones: tres puntos iniciales distintos cerca de la raiz. Si la parabola no corta el eje x (discriminante negativo) la funcion avisa y devuelve NaN (la raiz seria compleja).
double muller(double (*f)(double), double xa, double xb, double xc, double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return 3*x + sin(x) - exp(x); }
        double r = muller(f, 0.0, 0.5, 1.0, 1e-10, 1e-10, 50);   // raiz en 0.3604217
    */
    double p[3] = {xa, xb, xc};                         // ordenar: x2 < x0 < x1
    for (int i = 0; i < 2; i++)
        for (int j = i + 1; j < 3; j++)
            if (p[j] < p[i]) intercambiar_elem(p[i], p[j]);
    double x2 = p[0], x0 = p[1], x1 = p[2];
    if (x2 == x0 || x0 == x1) { print_error("muller: los tres puntos iniciales deben ser distintos"); return MC_NAN; }
    double r = x0, dx = 0.0;
    int iter = 0;
    do {
        double f2 = f(x2), f0 = f(x0), f1 = f(x1);
        double h1 = x1 - x0, h2 = x0 - x2;
        double a = ((f2 - f0) + h2 * (f1 - f0) / h1) / (h2 * (h1 + h2));   // p(t) = a*t^2 + b*t + c, t = x - x0
        double b = (f1 - f0 - a * h1 * h1) / h1;
        double c = f0;
        double disc = b * b - 4.0 * a * c;
        if (disc < 0.0) {
            print_error("muller: la parabola no corta el eje x (raices complejas). Prueba otros puntos iniciales.");
            return MC_NAN;
        }
        double den = (b >= 0.0) ? b + sqrt(disc) : b - sqrt(disc);          // signo de b: denominador de mayor modulo
        if (den == 0.0) break;
        r = x0 - 2.0 * c / den;                                              // raiz mas cercana a x0
        dx = r - x0;
        if (r > x2 && r < x1) {                                              // reordenar como en la teoria
            if (r > x0) { x2 = x0; x0 = r; }
            else        { x1 = x0; x0 = r; }
        } else {                                                             // r fuera del intervalo: quedarse con los 3 puntos mas cercanos
            double q[4] = {x2, x0, x1, r};
            for (int i = 0; i < 3; i++)
                for (int j = i + 1; j < 4; j++)
                    if (fabs(q[j] - r) < fabs(q[i] - r)) intercambiar_elem(q[i], q[j]);
            double t[3] = {q[0], q[1], q[2]};
            for (int i = 0; i < 2; i++)
                for (int j = i + 1; j < 3; j++)
                    if (t[j] < t[i]) intercambiar_elem(t[i], t[j]);
            x2 = t[0]; x0 = t[1]; x1 = t[2];
        }
        iter++;
    } while ((fabs(f(r)) > tol1 || fabs(dx) > tol2) && iter < max_iter);
    return r;
}

// Método de Newton modificado para raices multiples
// Descripción: Usa x(n+1) = x(n) - K*f(x)/f'(x), donde K es la multiplicidad de la raiz, y asi recupera la convergencia cuadratica que Newton pierde con raices dobles o triples.
// Condiciones: conocer (o suponer) la multiplicidad K >= 1 y partir de un x0 razonablemente cerca. Con K = 1 es el metodo de Newton normal.
double newton_modificado(double (*f)(double), double (*df)(double), double x0, int K, double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x)  { return (x - 1) * (x - 1) * (x + 2); }     // raiz doble en x = 1
        double df(double x) { return 2 * (x - 1) * (x + 2) + (x - 1) * (x - 1); }
        double r = newton_modificado(f, df, 2.0, 2, 1e-12, 1e-12, 50);   // K = 2: raiz en 1
    */
    if (K < 1) { print_error_int("newton_modificado: la multiplicidad K debe ser >= 1", K); return MC_NAN; }
    double x1 = x0, dx = 0.0;
    int iter = 0;
    do {
        double fx = f(x0), dfx = df(x0);
        if (fx != 0.0 && dfx != 0.0) {
            x1 = x0 - K * (fx / dfx);
            dx = x1 - x0;
            x0 = x1;
        } else {
            break;
        }
        iter++;
    } while ((fabs(f(x1)) > tol1 || fabs(dx) > tol2) && iter < max_iter);
    return x1;
}

// Aceleración de Aitken (extrapolación de Aitken, Delta^2)
// Descripción: A partir de tres aproximaciones consecutivas x0, x1, x2 de un proceso que converge LINEALMENTE (biseccion, falsa posicion, punto fijo) estima la raiz mejorada:
// r = x0 - (x1-x0)^2 / (x2 - 2*x1 + x0). Si el denominador es nulo (ya ha convergido) devuelve x2.
double aitken(double x0, double x1, double x2) {
    /*
    Ejemplo de uso:
        // Punto fijo de g(x) = sqrt(2x+3) desde 4:  4, 3.31662, 3.10375
        double r = aitken(4.0, 3.31662, 3.10375);    // 3.00744 (mejor que x4 = 3.01144)
    */
    double d2 = x2 - 2.0 * x1 + x0;
    if (fabs(d2) < 1e-300) return x2;
    double d1 = x1 - x0;
    return x0 - d1 * d1 / d2;
}

// Punto fijo acelerado con Aitken (método de Steffensen)
// Descripción: En cada paso calcula x1 = g(x0), x2 = g(x1) y los sustituye por la extrapolacion de Aitken. Converge mucho mas rapido que punto_fijo (cuadraticamente) si |g'| < 1 cerca de la raiz.
double punto_fijo_aitken(double (*g)(double), double x0, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double g(double x) { return sqrt(2*x + 3); }
        double r = punto_fijo_aitken(g, 4.0, 1e-12, 50);    // 3 en muy pocas iteraciones
    */
    double dx = 0.0;
    int iter = 0;
    do {
        double x1 = g(x0), x2 = g(x1);
        double xn = aitken(x0, x1, x2);
        if (isNaN(xn) || fabs(xn) > 1e100) {
            print_error("punto_fijo_aitken: la iteracion diverge");
            return MC_NAN;
        }
        dx = xn - x0;
        x0 = xn;
        iter++;
    } while (fabs(dx) > tol && iter < max_iter);
    return x0;
}

// Orden de convergencia de un método iterativo
// Descripción: Dada la sucesion de errores |E_n| de un metodo, estima p en |E(n+1)| = cte*|E(n)|^p como la pendiente de la recta log|E(n+1)| frente a log|E(n)| (minimos cuadrados).
// Necesita al menos 3 errores positivos. p = 1 lineal, p = 2 cuadratica (Newton, raiz simple), p = 1.62 secante, p = 1.84 Muller.
double orden_convergencia(double *err, int n) {
    /*
    Ejemplo de uso:
        double E[] = {1e-1, 5e-3, 1.25e-5, 7.8125e-11};   // E(n+1) = 0.5 * E(n)^2
        double p = orden_convergencia(E, 4);               // p = 2 (convergencia cuadratica)
    */
    if (n < 3) { print_error_int("orden_convergencia: se necesitan al menos 3 errores", n); return MC_NAN; }
    double sx = 0.0, sy = 0.0, sxx = 0.0, sxy = 0.0;
    int m = 0;
    for (int i = 0; i < n - 1; i++) {
        if (err[i] == 0.0 || err[i + 1] == 0.0) continue;
        double X = log(fabs(err[i])), Y = log(fabs(err[i + 1]));
        sx += X; sy += Y; sxx += X * X; sxy += X * Y;
        m++;
    }
    double den = m * sxx - sx * sx;
    if (m < 2 || fabs(den) < 1e-300) { print_error("orden_convergencia: errores insuficientes o todos iguales"); return MC_NAN; }
    return (m * sxy - sx * sy) / den;
}



// ============================================================================
// RESOLUCION DE SISTEMAS LINEALES
// ============================================================================

// ----------------------------------------------------------------------------
// 1. FACTORIZACION LU Y RESOLUCION
// ----------------------------------------------------------------------------

// Factorización LU (Forma 1 - Descomposición de Doolittle)
// Las matrices L y U deben estar pre-creadas con zeros_mat(n, n)
// Descripción: Factorizacion LU de Doolittle: A = L*U con unos en la diagonal de L (L triangular inferior, U triangular superior). Sirve para resolver varios sistemas con la misma A.
// Condiciones: A cuadrada y con menores principales no nulos (si aparece un cero en la diagonal de U avisa: habria que pivotar). L y U se crean antes con zeros_mat(n, n).
void lu_forma1(double **A, int n, double **L, double **U) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **L = zeros_mat(3, 3), **U = zeros_mat(3, 3);
        lu_forma1(A, 3, L, U);
        // Resultado: L = [1, 0, 0; 2, 1, 0; 4, 3, 1] , U = [2, 1, 1; 0, 1, 1; 0, 0, 2]
    */
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
// Descripción: Resuelve A*x = b con la factorizacion de Doolittle: A = L*U, luego L*z = b (sustitucion progresiva) y U*x = z (sustitucion regresiva). Mismas condiciones que lu_forma1.
double* lu_forma1_sol(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {4, 10, 24};
        double *x = lu_forma1_sol(A, b, 3);
        // Resultado: x = [1, 1, 1]
    */
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
// Descripción: Factorizacion LU de Crout: A = L*U con unos en la diagonal de U (se calcula alternando una fila de U y una columna de L). Mismas condiciones que lu_forma1; L y U se crean antes con zeros_mat(n, n).
void lu_forma2(double **A, int n, double **L, double **U) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **L = zeros_mat(3, 3), **U = zeros_mat(3, 3);
        lu_forma2(A, 3, L, U);
        // Resultado: L = [1, 0, 0; 2, 1, 0; 4, 3, 1] , U = [2, 1, 1; 0, 1, 1; 0, 0, 2]
    */
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
// Descripción: Resuelve A*x = b con la factorizacion de Crout (unos en la diagonal de U). Mismas condiciones que lu_forma1.
double* lu_forma2_sol(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, 1, 1, 4, 3, 3, 8, 7, 9};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {4, 10, 24};
        double *x = lu_forma2_sol(A, b, 3);
        // Resultado: x = [1, 1, 1]
    */
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
// Descripción: Eliminacion gaussiana con pivoteo parcial (en cada columna toma el pivote de mayor valor absoluto) y sustitucion regresiva. No modifica A ni b.
// Condiciones: A cuadrada y no singular (si es singular o casi, avisa y devuelve NULL). El pivoteo evita dividir por cero y reduce el error de redondeo.
double* gauss_solve(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {4, -2, 1, -3, -1, 4, 1, -1, 3};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {15, 8, 13};
        double *x = gauss_solve(A, b, 3);
        // Resultado: x = [2, -2, 3]
    */
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
// Descripción: Metodo de Gauss-Jordan: lleva la matriz a la identidad (ceros por encima y por debajo de la diagonal) y la solucion queda en la columna de terminos independientes. No modifica A ni b.
// Condiciones: A cuadrada y no singular (si no, avisa y devuelve NULL). Hace mas operaciones que Gauss, pero sirve tambien para calcular inversas.
double* gauss_jordan_solve(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {4, -2, 1, -3, -1, 4, 1, -1, 3};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {15, 8, 13};
        double *x = gauss_jordan_solve(A, b, 3);
        // Resultado: x = [2, -2, 3]
    */
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
// Descripción: Resuelve A*x = f con A TRIDIAGONAL (algoritmo de Thomas: LU + sustitucion), extrayendo las tres diagonales de la matriz completa. Necesita solo ~8n operaciones en vez de n^3.
// Condiciones: A tridiagonal (todo lo demas ceros) y sin ceros en los pivotes (se cumple si es diagonalmente dominante). Si no quieres construir la matriz, usa tridiag_vect_solve.
double* tridiag_solve(double **A, double *f, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {2, -1, 0, -1, 2, -1, 0, -1, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double f[3] = {1, 0, 1};
        double *x = tridiag_solve(A, f, 3);
        // Resultado: x = [1, 1, 1]
    */
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


// Resolución de sistemas tridiagonales con las diagonales en vectores (Algoritmo de Thomas)
// Descripción: Resuelve A*x = f para una matriz tridiagonal de n x n SIN construirla: 'a' es la diagonal inferior (a[1..n-1], a[0] no se usa),
// 'b' la principal (b[0..n-1]) y 'c' la superior (c[0..n-2], c[n-1] no se usa). Es la funcion Tridiag de las practicas (factorizacion LU + sustitucion).
double* tridiag_vect_solve(double *a, double *b, double *c, double *f, int n) {
    /*
    Ejemplo de uso:
        // [2 -1 0; -1 2 -1; 0 -1 2] * x = [1 0 1]
        double a[] = {0, -1, -1}, b[] = {2, 2, 2}, c[] = {-1, -1, 0}, f[] = {1, 0, 1};
        double *x = tridiag_vect_solve(a, b, c, f, 3); // x = {1, 1, 1}
    */
    if (n < 1) { print_error_int("tridiag_vect_solve: n debe ser >= 1", n); return NULL; }
    double *beta = new double[n];
    double *z = new double[n];
    double *x = new double[n];

    // Paso 1: Factorización LU y sustitución progresiva (L*z = f)
    beta[0] = b[0];
    z[0] = f[0];
    for (int i = 1; i < n; i++) {
        if (beta[i - 1] == 0.0) print_warning("Cero en la diagonal durante el algoritmo de Thomas (posible division por cero).");
        double alpha = a[i] / beta[i - 1];
        beta[i] = b[i] - alpha * c[i - 1];
        z[i] = f[i] - alpha * z[i - 1];
    }
    // Paso 2: Sustitución regresiva (U*x = z)
    x[n - 1] = z[n - 1] / beta[n - 1];
    for (int i = n - 2; i >= 0; i--) x[i] = (z[i] - c[i] * x[i + 1]) / beta[i];

    delete[] beta; delete[] z;
    return x;
}

// ----------------------------------------------------------------------------
// 4. METODOS ITERATIVOS
// ----------------------------------------------------------------------------

/// Función Auxiliar: Comprueba estrictamente si una matriz es diagonalmente dominante
// Descripción: Comprueba si A es diagonalmente dominante por filas: |a_ii| >= suma de |a_ij| (j != i) en todas las filas. Es una condicion SUFICIENTE (no necesaria) para que converjan Jacobi y Gauss-Seidel. Esta funcion acepta tambien la igualdad (dominancia debil).
bool check_dominancia(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, -2, 7, 2, 1, 2, -5};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        bool ok = check_dominancia(A, 3);
        // Resultado: ok = true
    */
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
// Descripción: Intenta conseguir dominancia diagonal reordenando las filas de A y b EN SITIO (no cambia la solucion del sistema). Si A ya es dominante no hace nada. Devuelve true si lo consigue; si no, avisa de que la convergencia no esta garantizada.
bool reorder_diagonals(double **A, double *b, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, 1, 2, -5, -2, 7, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {11, -1, 5};
        bool ok = reorder_diagonals(A, b, 3);
        // Resultado: ok = true , A = [6, -2, 1; -2, 7, 2; 1, 2, -5] , b = [11, 5, -1]
    */
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
// Descripción: Metodo iterativo de Jacobi (desplazamientos simultaneos): x_i(k+1) = (b_i - sum_{j!=i} a_ij*x_j(k)) / a_ii. Para cuando la norma del cambio entre dos iteraciones es menor que tol o se llega a max_iter (en ese caso avisa).
// Condiciones: a_ii != 0 (si hay un cero en la diagonal avisa y devuelve NULL) y convergencia garantizada si A es diagonalmente dominante. Util en matrices grandes y dispersas. No modifica A ni b.
double* jacobi_solve(double **A, double *b, int n, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, -2, 7, 2, 1, 2, -5};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {11, 5, -1};
        double *x = jacobi_solve(A, b, 3, 1e-10, 500);
        // Resultado: x = [2, 1, 1]
    */
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
// Descripción: Metodo iterativo de Gauss-Seidel (desplazamientos sucesivos): usa en cada paso los valores ya actualizados de la misma iteracion, por lo que suele converger el doble de rapido que Jacobi.
// Condiciones: a_ii != 0 (si no, avisa y devuelve NULL); converge si A es diagonalmente dominante o simetrica definida positiva. Para cuando la norma del cambio entre iteraciones es menor que tol. No modifica A ni b.
double* gauss_seidel_solve(double **A, double *b, int n, double tol, int max_iter ) {
    /*
    Ejemplo de uso:
        double Ad[9] = {6, -2, 1, -2, 7, 2, 1, 2, -5};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double b[3] = {11, 5, -1};
        double *x = gauss_seidel_solve(A, b, 3, 1e-10, 500);
        // Resultado: x = [2, 1, 1]
    */
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
// Descripción: Sobrerrelajacion sucesiva (SOR): Gauss-Seidel con factor de relajacion w, x_i = (1-w)*x_i + w*x_i(GS). w = 1 es Gauss-Seidel; el optimo suele estar entre 1 y 2 (si w > 1 acelera).
// Condiciones: 0 < w < 2 (si no, avisa y devuelve NULL) y las mismas que Gauss-Seidel (A simetrica definida positiva o diagonalmente dominante). No modifica A ni b.
double* sor_solve(double **A, double *b, int n, double w, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double Ad[16] = {4, -1, -1, -1, -1, 4, -1, -1, -1, -1, 4, -1, -1, -1, -1, 4};
        double **A = zeros_mat(4, 4);
        for (int i = 0; i < 16; i++) A[i / 4][i % 4] = Ad[i];
        double b[4] = {1, 1, 1, 1};
        double *x = sor_solve(A, b, 4, 1.3, 1e-10, 500);
        // Resultado: x = [1, 1, 1, 1]
    */
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
// Descripción: Determinante por eliminacion gaussiana con pivoteo: producto de los pivotes, cambiando el signo en cada intercambio de filas. No modifica A. Condicion: A cuadrada. det = 0 indica matriz singular.
double det_gauss(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double d = det_gauss(A, 3);
        // Resultado: d = 5
    */
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
// Descripción: Determinante con la factorizacion LU de Doolittle: det(A) = producto de la diagonal de U (L tiene unos). Condicion: A cuadrada con menores principales no nulos. No modifica A.
double det_lu(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double d = det_lu(A, 3);
        // Resultado: d = 5
    */
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
// Descripción: Inversa por Gauss-Jordan sobre la matriz ampliada [A | I]: al reducir A a I, la parte derecha queda A^-1. Condicion: A cuadrada con det(A) != 0 (si |det| < 1e-12 avisa y devuelve NULL). No modifica A.
double** inv_gj(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **Ai = inv_gj(A, 3);
        // Resultado: Ai = [0, 0.4, -0.2; -1, 0, 1; 0, -0.2, 0.6]
    */
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
// Descripción: Inversa resolviendo A*x = e_j (columnas de la identidad) con la factorizacion LU, que se calcula una sola vez. Condicion: A cuadrada con det(A) != 0 (si |det| < 1e-12 avisa y devuelve NULL).
double** inv_lu(double **A, int n) {
    /*
    Ejemplo de uso:
        double Ad[9] = {1, -1, 2, 3, 0, 1, 1, 0, 2};
        double **A = zeros_mat(3, 3);
        for (int i = 0; i < 9; i++) A[i / 3][i % 3] = Ad[i];
        double **Ai = inv_lu(A, 3);
        // Resultado: Ai = [0, 0.4, -0.2; -1, 0, 1; 0, -0.2, 0.6]
    */
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
// Descripción: Minimos cuadrados ordinarios (OLS) para un sistema SOBREDETERMINADO A*x = b (m ecuaciones > n incognitas): resuelve las ecuaciones normales A^T*A*x = A^T*b. Devuelve los n parametros;
// por referencia, sus errores tipicos y el coeficiente de determinacion R2. Condiciones: m > n y columnas de A linealmente independientes (si A^T*A es singular avisa y devuelve NULL).
double* ols_reg(double **A, double *b, int m, int n, double *&errores, double &R2) {
    /*
    Ejemplo de uso:
        double Ad[10] = {1, 1, 1, 2, 1, 3, 1, 4, 1, 5};
        double **A = zeros_mat(5, 2);
        for (int i = 0; i < 10; i++) A[i / 2][i % 2] = Ad[i];
        double b[5] = {2.1, 3.9, 6.2, 7.8, 10.1};
        double *err, R2;
        double *p = ols_reg(A, b, 5, 2, err, R2);
        // Resultado: p = [0.05, 1.99] , err = [0.1980741, 0.05972158] , R2 = 0.9973053
    */
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
// Descripción: Regresion polinomica y = a0 + a1*x + ... + am*x^m por minimos cuadrados. Devuelve [a0, a1, ..., am], los errores de cada parametro y R2. Condicion: m_datos > grado + 1 (mas datos que parametros).
double* poly_reg(double *x, double *y, int m_datos, int grado, double *&errores, double &R2) {
    /*
    Ejemplo de uso:
        double x[6] = {0, 1, 2, 3, 4, 5};
        double y[6] = {1.1, 2.9, 9.2, 18.8, 33.1, 51.0};
        double *err, R2;
        double *a = poly_reg(x, y, 6, 2, err, R2);
        // Resultado: a = [1.067857, -0.05321429, 2.008929] , R2 = 0.9999452   (ajuste cuadratico y = a0 + a1*x + a2*x^2)
    */
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
// Descripción: Regresion lineal y = a0 + a1*x por minimos cuadrados (poly_reg de grado 1). Devuelve [a0, a1], los errores de cada parametro y R2 (R2 cercano a 1 = buen ajuste).
double* lin_reg(double *x, double *y, int m_datos, double *&errores, double &R2) {
    /*
    Ejemplo de uso:
        double x[5] = {1, 2, 3, 4, 5};
        double y[5] = {2.1, 3.9, 6.2, 7.8, 10.1};
        double *err, R2;
        double *p = lin_reg(x, y, 5, err, R2);
        // Resultado: p = [0.05, 1.99] , R2 = 0.9973053
    */
    return poly_reg(x, y, m_datos, 1, errores, R2);
}

// 3. Regresión Exponencial: y = a * e^(bx)
		// Devuelve [a, b]. Realiza la linealizacion: ln(y) = ln(a) + b*x
// Descripción: Regresion exponencial y = a*e^(b*x), linealizada como ln(y) = ln(a) + b*x. Devuelve [a, b], los errores y R2. Condicion: todos los y deben ser positivos.
double* exp_reg(double *x, double *y, int m_datos, double *&errores, double &R2) {
    /*
    Ejemplo de uso:
        double x[5] = {1, 2, 3, 4, 5};
        double y[5] = {3.30, 5.44, 8.96, 14.78, 24.37};
        double *err, R2;
        double *p = exp_reg(x, y, 5, err, R2);
        // Resultado: p = [2.001532, 0.4998357] , R2 = 0.9999998   (datos de y = 2*e^(0.5x))
    */
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
// Descripción: Regresion logaritmica y = a + b*ln(x), linealizada con X = ln(x). Devuelve [a, b], los errores y R2. Condicion: todos los x deben ser positivos.
double* regresion_logaritmica(double *x, double *y, int m_datos, double *&errores, double &R2) {
    /*
    Ejemplo de uso:
        double x[6] = {1, 2, 3, 4, 5, 6};
        double y[6] = {1.00, 2.39, 3.20, 3.77, 4.22, 4.58};
        double *err, R2;
        double *p = regresion_logaritmica(x, y, 6, err, R2);
        // Resultado: p = [1.002302, 1.998128] , R2 = 0.9999962   (datos de y = 1 + 2*ln(x))
    */
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
// Descripción: Regresion potencial y = a*x^b, linealizada como ln(y) = ln(a) + b*ln(x). Devuelve [a, b], los errores y R2. Condicion: todos los x e y deben ser positivos.
double* regresion_potencial(double *x, double *y, int m_datos, double *&errores, double &R2) {
    /*
    Ejemplo de uso:
        double x[5] = {1, 2, 3, 4, 5};
        double y[5] = {3.00, 8.49, 15.59, 24.00, 33.54};
        double *err, R2;
        double *p = regresion_potencial(x, y, 5, err, R2);
        // Resultado: p = [3.000646, 1.499905] , R2 = 0.9999999   (datos de y = 3*x^1.5)
    */
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
// Descripción: Regresion armonica y = a0 + a1*cos(w*x) + a2*sin(w*x) por minimos cuadrados, con la frecuencia angular w CONOCIDA (es lineal en a0, a1, a2). Devuelve [a0, a1, a2], los errores y R2.
// Condiciones: conocer w y tener al menos 3 datos repartidos a lo largo de un periodo o mas.
double* regresion_sinusoidal(double *x, double *y, int m_datos, double w, double *&errores, double &R2) {
    /*
    Ejemplo de uso:
        double x[8] = {0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5};
        double y[8] = {1.0 + 0.5*cos(2*0.0) + 0.8*sin(2*0.0), 1.0 + 0.5*cos(2*0.5) + 0.8*sin(2*0.5), 1.0 + 0.5*cos(2*1.0) + 0.8*sin(2*1.0), 1.0 + 0.5*cos(2*1.5) + 0.8*sin(2*1.5),
                       1.0 + 0.5*cos(2*2.0) + 0.8*sin(2*2.0), 1.0 + 0.5*cos(2*2.5) + 0.8*sin(2*2.5), 1.0 + 0.5*cos(2*3.0) + 0.8*sin(2*3.0), 1.0 + 0.5*cos(2*3.5) + 0.8*sin(2*3.5)};
        double *err, R2;
        double *p = regresion_sinusoidal(x, y, 8, 2.0, err, R2);
        // Resultado: p = [1, 0.5, 0.8]   (datos de y = 1 + 0.5cos(2x) + 0.8sin(2x))
    */
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
// Descripción: Calcula las segundas derivadas M[0..n-1] de la spline cubica NATURAL (M[0] = M[n-1] = 0) que pasa por los n puntos (x,y). Se calcula una vez y se usa con spline_eval.
// Condiciones: n >= 3 y x estrictamente creciente. Liberar con delete[] (o del_vect).
double* spline_coef(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[5] = {0, 1, 2, 3, 4};
        double y[5] = {0, 1, 4, 9, 16};          // y = x^2
        double *M = spline_coef(x, y, 5);
        // Resultado: M = [0, 2.571429, 1.714286, 2.571429, 0]
    */
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
// Descripción: Evalua en xi la spline cubica natural a partir de las segundas derivadas M (de spline_coef). Condiciones: x creciente; fuera de [x0, x(n-1)] extrapola con el tramo extremo (poco fiable).
double spline_eval(double *x, double *y, double *M, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[5] = {0, 1, 2, 3, 4};
        double y[5] = {0, 1, 4, 9, 16};          // y = x^2
        double *M = spline_coef(x, y, 5);
        double v = spline_eval(x, y, M, 5, 2.5);
        // Resultado: v = 6.232143
    */
    int k = 0;
    while (k < n - 2 && xi > x[k + 1]) k++;
    double h = x[k + 1] - x[k];
    double A = (x[k + 1] - xi) / h, B = (xi - x[k]) / h;
    return A * y[k] + B * y[k + 1] + ((A*A*A - A) * M[k] + (B*B*B - B) * M[k + 1]) * h * h / 6.0;
}
// Spline cúbica natural en una sola llamada
// Descripción: Spline cubica natural en una sola llamada (calcula M, evalua en xi y libera memoria). Si vas a evaluar muchos puntos usa spline_coef + spline_eval. Condiciones: n >= 3 y x creciente.
double spline_interp(double *x, double *y, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[5] = {0, 1, 2, 3, 4};
        double y[5] = {0, 1, 4, 9, 16};          // y = x^2
        double v = spline_interp(x, y, 5, 2.5);
        // Resultado: v = 6.232143   (exacto para y = x^2: 6.25 (la spline natural impone M = 0 en los extremos))
    */
    double *M = spline_coef(x, y, n);
    if (M == NULL) return MC_NAN;
    double r = spline_eval(x, y, M, n, xi);
    delete[] M;
    return r;
}

// 8. ---------------- NEWTON (diferencias divididas) ----------------
// Devuelve c[0..n-1] = f[x0], f[x0,x1], ... Liberar con del_vect.
// Descripción: Coeficientes del polinomio de Newton (diferencias divididas f[x0], f[x0,x1], ...). Se calculan una vez y permiten evaluar el polinomio con newton_eval o AÑADIR un punto sin rehacer los calculos anteriores.
// Condiciones: nodos x distintos (no hace falta que esten ordenados ni equiespaciados). Liberar con delete[].
double* newton_coef(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[4] = {3.2, 2.7, 1.0, 4.8};
        double y[4] = {22.0, 17.8, 14.2, 38.3};
        double *c = newton_coef(x, y, 4);
        // Resultado: c = [22, 8.4, 2.855615, -0.5274801]
    */
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
// Descripción: Evalua en xi el polinomio de Newton con la forma anidada (tipo Horner) a partir de los coeficientes c de newton_coef y los nodos x. Es el mismo polinomio que el de Lagrange (el polinomio interpolador es unico).
double newton_eval(double *x, double *c, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[4] = {3.2, 2.7, 1.0, 4.8};
        double y[4] = {22.0, 17.8, 14.2, 38.3};
        double *c = newton_coef(x, y, 4);
        double v = newton_eval(x, c, 4, 3.0);
        // Resultado: v = 20.21196
    */
    double r = c[n - 1];
    for (int i = n - 2; i >= 0; i--) r = r * (xi - x[i]) + c[i];
    return r;
}

// 9. ---------------- LAGRANGE (forma baricentrica) ----------------
// Devuelve los pesos w[i] = 1 / prod_{j!=i} (x[i]-x[j]). Liberar con del_vect.
// Descripción: Pesos baricentricos w[i] = 1 / prod_{j!=i}(x_i - x_j) del polinomio de Lagrange. Se calculan una vez y permiten evaluar con lagrange_val en O(n) por punto. Condicion: nodos x distintos. Liberar con delete[].
double* lagrange_coef(double *x, int n) {
    /*
    Ejemplo de uso:
        double x[4] = {3.2, 2.7, 1.0, 4.8};
        double y[4] = {22.0, 17.8, 14.2, 38.3};
        double *w = lagrange_coef(x, 4);
        // Resultado: w = [-0.5681818, 0.5602241, -0.07036307, 0.0783208]
    */
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
// Descripción: Evalua en xi el polinomio de Lagrange (forma baricentrica) con los pesos w de lagrange_coef. Si xi coincide con un nodo devuelve directamente su y. Mismo polinomio que newton_eval.
double lagrange_val(double *x, double *y, double *w, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[4] = {3.2, 2.7, 1.0, 4.8};
        double y[4] = {22.0, 17.8, 14.2, 38.3};
        double *w = lagrange_coef(x, 4);
        double v = lagrange_val(x, y, w, 4, 3.0);
        // Resultado: v = 20.21196
    */
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

// Polinomio base de Lagrange L_i(x)
// Descripción: Evalua L_i(xi) = prod_{j!=i} (xi - x_j)/(x_i - x_j), el polinomio de grado n-1 que vale 1 en x_i y 0 en el resto de nodos. El polinomio interpolador es P(x) = sum y_i*L_i(x).
double lagrange_base(double *x, int n, int i, double xi) {
    /*
    Ejemplo de uso:
        double x[] = {3.2, 2.7, 1.0, 4.8};
        double L0 = lagrange_base(x, 4, 0, 3.2);    // 1 (en su propio nodo)
        double L1 = lagrange_base(x, 4, 1, 3.2);    // 0 (en otro nodo)
    */
    if (i < 0 || i >= n) { print_error_int("lagrange_base: el indice i esta fuera de rango", i); return MC_NAN; }
    double L = 1.0;
    for (int j = 0; j < n; j++) {
        if (j == i) continue;
        if (x[i] == x[j]) { print_error("lagrange_base: hay nodos x repetidos"); return MC_NAN; }
        L *= (xi - x[j]) / (x[i] - x[j]);
    }
    return L;
}

// Interpolación de Lagrange en una sola llamada
// Descripción: Evalua en xi el polinomio de Lagrange que pasa por los n puntos (x,y) (calcula los pesos, evalua y libera memoria). Si vas a evaluar muchos puntos usa lagrange_coef + lagrange_val.
double lagrange_interp(double *x, double *y, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[] = {3.2, 2.7, 1.0, 4.8}, y[] = {22.0, 17.8, 14.2, 38.3};
        double v = lagrange_interp(x, y, 4, 3.0);   // 20.212
    */
    double *w = lagrange_coef(x, n);
    if (w == NULL) return MC_NAN;
    double r = lagrange_val(x, y, w, n, xi);
    delete[] w;
    return r;
}

// Interpolación de Newton en una sola llamada
// Descripción: Evalua en xi el polinomio de Newton (diferencias divididas) que pasa por los n puntos (x,y). Si vas a evaluar muchos puntos usa newton_coef + newton_eval.
double newton_interp(double *x, double *y, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[] = {3.2, 2.7, 1.0, 4.8}, y[] = {22.0, 17.8, 14.2, 38.3};
        double v = newton_interp(x, y, 4, 3.0);     // 20.212
    */
    double *c = newton_coef(x, y, n);
    if (c == NULL) return MC_NAN;
    double r = newton_eval(x, c, n, xi);
    delete[] c;
    return r;
}



// 10. ---------------- POLINOMIO DE INTERPOLACION POR EL SISTEMA DE VANDERMONDE ----------------

// Matriz de Vandermonde
// Descripción: Devuelve la matriz V (n x n) con V[i][j] = x[i]^j (potencias crecientes). Resolver V*a = y da los coeficientes del polinomio interpolador.
double** vandermonde_mat(double *x, int n) {
    /*
    Ejemplo de uso:
        double x[] = {1, 2, 3};
        double **V = vandermonde_mat(x, 3); // [1 1 1; 1 2 4; 1 3 9]
    */
    double **V = zeros_mat(n, n);
    for (int i = 0; i < n; i++) {
        double p = 1.0;
        for (int j = 0; j < n; j++) { V[i][j] = p; p *= x[i]; }
    }
    return V;
}

// Coeficientes del polinomio interpolador (resolviendo el sistema de Vandermonde)
// Descripción: Devuelve los n coeficientes del unico polinomio de grado n-1 que pasa por los n puntos, con potencias DECRECIENTES (listo para 'polyval').
// Es el metodo mas directo pero esta mal condicionado si n es grande; para evaluar conviene newton_eval o lagrange_val.
double* poly_interp_coef(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {0, 1, 2}, y[] = {1, 2, 5};        // y = x^2 + 1
        double *p = poly_interp_coef(x, y, 3);           // p = {1, 0, 1}
        double v = polyval(p, 3, 1.5);                   // 3.25
    */
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (x[i] == x[j]) { print_error("poly_interp_coef: hay nodos x repetidos"); return NULL; }
    double **V = vandermonde_mat(x, n);
    double *a = gauss_solve(V, y, n);              // a[0] = termino independiente
    del_mat(V, n);
    if (a == NULL) return NULL;
    double *p = new double[n];
    for (int i = 0; i < n; i++) p[i] = a[n - 1 - i];
    delete[] a;
    return p;
}

// 11. ---------------- TABLA DE DIFERENCIAS DIVIDIDAS (NEWTON) ----------------

// Tabla completa de diferencias divididas
// Descripción: T[i][j] = f[x_i, ..., x_{i+j}] (la columna j=0 es y). Los coeficientes del polinomio de Newton son la primera fila T[0][j].
// Los elementos por debajo de la diagonal secundaria valen 0. Liberar con del_mat(T, n).
double** dif_divididas_mat(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {3.2, 2.7, 1.0, 4.8, 5.6}, y[] = {22.0, 17.8, 14.2, 38.3, 51.7};
        double **T = dif_divididas_mat(x, y, 5);
        print_mat(T, 5, 5, "Dif. divididas");   // T[0][1] = 8.4, T[0][2] = -2.856, ...
    */
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (x[i] == x[j]) { print_error("dif_divididas_mat: hay nodos x repetidos"); return NULL; }
    double **T = zeros_mat(n, n);
    for (int i = 0; i < n; i++) T[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            T[i][j] = (T[i + 1][j - 1] - T[i][j - 1]) / (x[i + j] - x[i]);
    return T;
}

// 12. ---------------- ERROR DE INTERPOLACION ----------------

// Error de interpolación de Newton: regla del término siguiente
// Descripción: Estima E(xi) ~ f[x0,...,xn] * prod(xi - x_i) usando el siguiente termino que se sumaria al polinomio.
// El polinomio usa 'n' puntos (x[0..n-1]) y 'c' son los coeficientes de Newton calculados con UN punto mas (c[0..n], es decir n+1 coeficientes).
double newton_error_sig(double *x, double *c, int n, double xi) {
    /*
    Ejemplo de uso:
        double x[] = {3.2, 2.7, 1.0, 4.8, 5.6}, y[] = {22.0, 17.8, 14.2, 38.3, 51.7};
        double *c = newton_coef(x, y, 5);                  // 5 coeficientes (4 puntos + 1 extra)
        double E = newton_error_sig(x, c, 4, 3.0);         // error del polinomio de grado 3 en xi = 3.0
    */
    double prod = c[n];
    for (int i = 0; i < n; i++) prod *= (xi - x[i]);
    return prod;
}

// Cota del error de interpolación (Lagrange o Newton)
// Descripción: |E(xi)| <= M/n! * prod|xi - x_i|, donde n es el numero de puntos del polinomio y M una cota de |f^(n)| en el intervalo.
double interp_error_cota(double *x, int n, double xi, double M_deriv) {
    /*
    Ejemplo de uso:
        // Polinomio de 4 puntos para f(x) = e^x en [0,1], con |f''''| <= e
        double cota = interp_error_cota(x, 4, 0.5, exp(1.0));
    */
    double prod = 1.0;
    for (int i = 0; i < n; i++) prod *= fabs(xi - x[i]);
    return M_deriv * prod / factorial(n);
}

// 13. ---------------- PUNTOS EQUIESPACIADOS: DIFERENCIAS PROGRESIVAS ----------------

// Tabla de diferencias progresivas
// Descripción: D[i][k] = (Delta^k f)(x_i) para datos equiespaciados. La columna k=0 es y. Liberar con del_mat(D, n).
// Relacion con las diferencias divididas: f[x0,...,xk] = Delta^k f0 / (k! * h^k).
double** dif_progresivas_mat(double *y, int n) {
    /*
    Ejemplo de uso:
        double y[] = {0.000, 0.203, 0.423, 0.684, 1.030, 1.557, 2.572};  // tan(x), x = 0, 0.2, ..., 1.2
        double **D = dif_progresivas_mat(y, 7);
        print_mat(D, 7, 7, "Dif. progresivas");
    */
    double **D = zeros_mat(n, n);
    for (int i = 0; i < n; i++) D[i][0] = y[i];
    for (int k = 1; k < n; k++)
        for (int i = 0; i < n - k; i++)
            D[i][k] = D[i + 1][k - 1] - D[i][k - 1];
    return D;
}

// Polinomio de interpolación de Newton con diferencias progresivas
// Descripción: Evalua P(xi) = sum_k C(s,k) * Delta^k f0 con s = (xi - x0)/h, usando 'n' diferencias dif0[0..n-1] = Delta^k f(x0).
// Para centrar el polinomio, tomar como x0 el nodo adecuado y como dif0 la fila correspondiente de dif_progresivas_mat (D[i0]).
double newton_prog_eval(double x0, double h, double *dif0, int n, double xi) {
    /*
    Ejemplo de uso:
        // f(0.73) con un polinomio de grado 3 empezando en x0 = 0.4 (fila 2 de la tabla)
        double v = newton_prog_eval(0.4, 0.2, D[2], 4, 0.73);   // ~0.893
    */
    double s = (xi - x0) / h;
    double termino = 1.0, suma = 0.0;
    for (int k = 0; k < n; k++) {
        suma += termino * dif0[k];
        termino *= (s - k) / (k + 1.0);     // C(s,k+1) = C(s,k) * (s-k)/(k+1)
    }
    return suma;
}

// Error de Newton progresivo: regla del término siguiente
// Descripción: E ~ C(s,n) * Delta^n f0, donde el polinomio usa 'n' puntos y dif0[n] es la primera diferencia NO usada en el polinomio.
double newton_prog_error_sig(double x0, double h, double *dif0, int n, double xi) {
    /*
    Ejemplo de uso:
        double E = newton_prog_error_sig(0.4, 0.2, D[2], 4, 0.73);   // ~0.004
    */
    double s = (xi - x0) / h;
    double termino = 1.0;
    for (int k = 0; k < n; k++) termino *= (s - k) / (k + 1.0);
    return termino * dif0[n];
}

// ============================================================================
// CÁLCULO NUMÉRICO: DERIVADAS, GRADIENTES Y JACOBIANOS
// ============================================================================

// ----------------------------------------------------------------------------
// CALCULO NUMERICO CON FUNCIONES
// ----------------------------------------------------------------------------

// Pesos de derivación (derivada del polinomio de Lagrange)
// Descripción: Para los m nodos xs[0..m-1] calcula los pesos w[j] tales que f^(orden)(xt) ~ sum(w[j]*f(xs[j])), con orden = 1 o 2. Vale para nodos NO equiespaciados.
// Con nodos equiespaciados reproduce las formulas clasicas (centrales, progresivas y regresivas). 'w' debe tener m posiciones.
void pesos_deriv_lagrange(double *xs, int m, double xt, int orden, double *w) {
    /*
    Ejemplo de uso:
        double xs[] = {1.9, 2.0, 2.1}, w[3];
        pesos_deriv_lagrange(xs, 3, 2.0, 1, w);     // w = {-5, 0, 5}  (central: (f(x+h)-f(x-h))/(2h) con h = 0.1)
    */
    for (int j = 0; j < m; j++) {
        double D = 1.0;
        for (int k = 0; k < m; k++) if (k != j) D *= (xs[j] - xs[k]);
        double s = 0.0;
        for (int a = 0; a < m; a++) {
            if (a == j) continue;
            if (orden == 1) {
                double p = 1.0;
                for (int k = 0; k < m; k++) if (k != j && k != a) p *= (xt - xs[k]);
                s += p;
            } else {
                for (int l = 0; l < m; l++) {
                    if (l == j || l == a) continue;
                    double p = 1.0;
                    for (int k = 0; k < m; k++) if (k != j && k != a && k != l) p *= (xt - xs[k]);
                    s += p;
                }
            }
        }
        w[j] = s / D;
    }
}

// Derivada parcial CENTRAL de alta precisión
// Descripción: Calcula df/dx_j con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9; error O(h^(puntos-1))). Mas puntos = mas precision pero mas evaluaciones de f (puntos-1).
// Si h <= 0 elige automaticamente el paso que equilibra truncamiento y redondeo: h = eps^(1/puntos) * max(1, |x_j|). f debe ser suave (derivable) en el entorno del punto.
double part_derv_c(double (*f)(double*, int), double *x, int n, int j, double h, int puntos) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0]*v[1] + sin(v[1]); }
        double punto[] = {2.0, 0.5};
        double dfdx = part_derv_c(mi_func, punto, 2, 0, 0.0, 5);   // 2*x*y = 2.0 (paso automatico, 5 puntos)
        double dfdy = part_derv_c(mi_func, punto, 2, 1, 1e-3, 7);  // x^2 + cos(y) = 4.8775826 (h = 1e-3, 7 puntos)
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("part_derv_c: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    if (j < 0 || j >= n) { print_error_int("part_derv_c: la variable j esta fuera de rango", j); return MC_NAN; }
    if (h <= 0.0) h = pow(2.220446049250313e-16, 1.0 / puntos) * ((fabs(x[j]) > 1.0) ? fabs(x[j]) : 1.0);
    int m = puntos / 2;
    double xs[9], w[9];
    for (int k = 0; k < puntos; k++) xs[k] = (double)(k - m);
    pesos_deriv_lagrange(xs, puntos, 0.0, 1, w);          // pesos centrales para paso unidad
    double *xh = copy_vect(x, n);
    double suma = 0.0;
    for (int k = 0; k < puntos; k++) {
        if (k == m) continue;                              // el peso central es 0
        xh[j] = x[j] + (k - m) * h;
        suma += w[k] * f(xh, n);
    }
    delete[] xh;
    return suma / h;
}

// Derivada parcial segunda CENTRAL de alta precisión
// Descripción: Calcula d2f/dx_j2 con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9; error O(h^(puntos-1)) con puntos centrados). Si h <= 0 elige el paso automatico h = eps^(1/(puntos+1)) * max(1, |x_j|).
// Necesita puntos evaluaciones de f. f debe ser suave en el entorno del punto.
double part2_derv_c(double (*f)(double*, int), double *x, int n, int j, double h, int puntos) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0]*v[1] + sin(v[1]); }
        double punto[] = {2.0, 0.5};
        double d2fdx2 = part2_derv_c(mi_func, punto, 2, 0, 0.0, 5);   // 2*y = 1.0
        double d2fdy2 = part2_derv_c(mi_func, punto, 2, 1, 0.0, 5);   // -sin(y) = -0.4794255
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("part2_derv_c: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    if (j < 0 || j >= n) { print_error_int("part2_derv_c: la variable j esta fuera de rango", j); return MC_NAN; }
    if (h <= 0.0) h = pow(2.220446049250313e-16, 1.0 / (puntos + 1)) * ((fabs(x[j]) > 1.0) ? fabs(x[j]) : 1.0);
    int m = puntos / 2;
    double xs[9], w[9];
    for (int k = 0; k < puntos; k++) xs[k] = (double)(k - m);
    pesos_deriv_lagrange(xs, puntos, 0.0, 2, w);
    double *xh = copy_vect(x, n);
    double suma = 0.0;
    for (int k = 0; k < puntos; k++) {
        xh[j] = x[j] + (k - m) * h;
        suma += w[k] * f(xh, n);
    }
    delete[] xh;
    return suma / (h * h);
}

// Derivada parcial numérica CENTRAL de 5 puntos (error O(h^4)).
// Descripción: Calcula df/dx_j con diferencias centrales de 5 puntos y paso automatico (eps^(1/5)*max(1,|x_j|)). Para elegir el paso o el nº de puntos (3, 5, 7, 9) usa part_derv_c.
double part_derv(double (*f)(double*, int), double *x, int n, int j) {
    /*
    Ejemplo de uso:
        double mi_func(double *v, int n) { return v[0]*v[0] + sin(v[1]); }
        double punto[] = {2.0, 3.14};
        double df_dy = part_derv(mi_func, punto, 2, 1);
    */
    return part_derv_c(f, x, n, j, 0.0, 5);
}

// Derivada total
// Descripción: Calcula la derivada total dF/dt sumando el producto de las derivadas parciales por dx_i/dt. Usa part_derv (centrales de 5 puntos, O(h^4)).
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
// Descripción: Devuelve un vector con todas las derivadas parciales de una función escalar. Usa part_derv (centrales de 5 puntos); para elegir paso y puntos usa gradiente().
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
// Descripción: Construye la matriz nxn de derivadas parciales para un sistema de n funciones. Usa part_derv (centrales de 5 puntos, O(h^4)).
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

// Gradiente de un campo escalar (alta precisión)
// Descripción: Devuelve el vector (df/dx_1, ..., df/dx_n) en el punto x con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9) y paso h (h <= 0 = automatico). Es la mejor opcion para precision;
// grad_vect hace lo mismo con valores fijos (5 puntos, paso automatico). Liberar con delete[].
double* gradiente(double (*f)(double*, int), double *x, int n, double h, int puntos) {
    /*
    Ejemplo de uso:
        double campo(double *v, int n) { return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; }   // f = x^2 + y^2 + z^2
        double punto[] = {1.0, 2.0, 3.0};
        double *g = gradiente(campo, punto, 3, 0.0, 5);     // (2x, 2y, 2z) = (2, 4, 6)
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("gradiente: puntos debe ser impar entre 3 y 9", puntos); return NULL; }
    double *g = new double[n];
    for (int j = 0; j < n; j++) g[j] = part_derv_c(f, x, n, j, h, puntos);
    return g;
}

// Divergencia de un campo vectorial (alta precisión)
// Descripción: Calcula div F = dF_1/dx_1 + ... + dF_n/dx_n en el punto x. El campo se pasa como array de n funciones AF[i](x, n) (componente i). Diferencias centrales de 'puntos' puntos y paso h (h <= 0 = automatico).
double divergencia(double (*AF[])(double*, int), double *x, int n, double h, int puntos) {
    /*
    Ejemplo de uso:
        double Fx(double *v, int n) { return v[0]*v[1]; }    // F = (x*y, y*z, z*x)
        double Fy(double *v, int n) { return v[1]*v[2]; }
        double Fz(double *v, int n) { return v[2]*v[0]; }
        double (*F[3])(double*, int) = {Fx, Fy, Fz};
        double punto[] = {1.0, 2.0, 3.0};
        double div = divergencia(F, punto, 3, 0.0, 5);       // y + z + x = 6
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("divergencia: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    double suma = 0.0;
    for (int i = 0; i < n; i++) suma += part_derv_c(AF[i], x, n, i, h, puntos);
    return suma;
}

// Rotacional de un campo vectorial 3D (alta precisión)
// Descripción: Devuelve rot F = (dFz/dy - dFy/dz, dFx/dz - dFz/dx, dFy/dx - dFx/dy) en el punto x = (x, y, z). El campo son 3 funciones AF[0..2](x, 3). Diferencias centrales de 'puntos' puntos y paso h (h <= 0 = automatico).
// Para un campo plano (2 componentes) usa rotacional_2d. Liberar con delete[].
double* rotacional(double (*AF[])(double*, int), double *x, double h, int puntos) {
    /*
    Ejemplo de uso:
        double Fx(double *v, int n) { return v[0]*v[1]; }    // F = (x*y, y*z, z*x)
        double Fy(double *v, int n) { return v[1]*v[2]; }
        double Fz(double *v, int n) { return v[2]*v[0]; }
        double (*F[3])(double*, int) = {Fx, Fy, Fz};
        double punto[] = {1.0, 2.0, 3.0};
        double *rot = rotacional(F, punto, 0.0, 5);          // (-y, -z, -x) = (-2, -3, -1)
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("rotacional: puntos debe ser impar entre 3 y 9", puntos); return NULL; }
    double *r = new double[3];
    r[0] = part_derv_c(AF[2], x, 3, 1, h, puntos) - part_derv_c(AF[1], x, 3, 2, h, puntos);
    r[1] = part_derv_c(AF[0], x, 3, 2, h, puntos) - part_derv_c(AF[2], x, 3, 0, h, puntos);
    r[2] = part_derv_c(AF[1], x, 3, 0, h, puntos) - part_derv_c(AF[0], x, 3, 1, h, puntos);
    return r;
}

// Rotacional de un campo vectorial plano (componente z)
// Descripción: Para un campo F = (Fx, Fy) en el plano devuelve (rot F)_z = dFy/dx - dFx/dy en el punto x = (x, y). Es la circulacion por unidad de area. Diferencias centrales de 'puntos' puntos y paso h (h <= 0 = automatico).
double rotacional_2d(double (*AF[])(double*, int), double *x, double h, int puntos) {
    /*
    Ejemplo de uso:
        double Fx(double *v, int n) { return -v[1]; }       // rotacion rigida F = (-y, x)
        double Fy(double *v, int n) { return v[0]; }
        double (*F[2])(double*, int) = {Fx, Fy};
        double punto[] = {1.0, 1.0};
        double rz = rotacional_2d(F, punto, 0.0, 5);         // 2
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("rotacional_2d: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    return part_derv_c(AF[1], x, 2, 0, h, puntos) - part_derv_c(AF[0], x, 2, 1, h, puntos);
}

// Laplaciano de un campo escalar (alta precisión)
// Descripción: Calcula laplaciano f = d2f/dx_1^2 + ... + d2f/dx_n^2 en el punto x con diferencias centrales de 'puntos' puntos (3, 5, 7 o 9) y paso h (h <= 0 = automatico). Una funcion armonica da 0.
// Usa n*puntos evaluaciones de f. f debe ser suave en el entorno del punto.
double laplaciano(double (*f)(double*, int), double *x, int n, double h, int puntos) {
    /*
    Ejemplo de uso:
        double campo(double *v, int n) { return sin(v[0]) * sin(v[1]); }   // f = sin(x) sin(y)
        double punto[] = {0.7, 1.1};
        double lap = laplaciano(campo, punto, 2, 0.0, 5);     // -2 sin(x) sin(y) = -2*sin(0.7)*sin(1.1) = -1.1486...
    */
    if (puntos < 3 || puntos > 9 || puntos % 2 == 0) { print_error_int("laplaciano: puntos debe ser impar entre 3 y 9", puntos); return MC_NAN; }
    double suma = 0.0;
    for (int j = 0; j < n; j++) suma += part2_derv_c(f, x, n, j, h, puntos);
    return suma;
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

// Sistema lineal pequeño SIN mensajes (ayuda para Newton en rango)
// Descripción: Resuelve A*x = b por eliminacion gaussiana con pivoteo parcial sobre copias de A y b (no las modifica) y deja la solucion en x. Devuelve false, sin imprimir nada, si la matriz es singular.
// Se usa en las busquedas con muchos puntos de partida, donde un Jacobiano singular es normal y no debe llenar la pantalla de errores.
bool lineal_silencioso(double **A, double *b, int n, double *x) {
    /*
    Ejemplo de uso:
        double d[4] = {2, 1, 1, 3};
        double **A = mat_from_arr(d, 2, 2);
        double b[2] = {3, 5}, x[2];
        bool ok = lineal_silencioso(A, b, 2, x);     // ok = true, x = (0.8, 1.4)
    */
    double **M = coppy_mat(A, n, n);
    double *r = copy_vect(b, n);
    double esc = 0.0;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (fabs(A[i][j]) > esc) esc = fabs(A[i][j]);
    bool ok = (esc > 0.0);
    for (int k = 0; k < n && ok; k++) {
        int p = k;
        for (int i = k + 1; i < n; i++) if (fabs(M[i][k]) > fabs(M[p][k])) p = i;
        if (fabs(M[p][k]) < 1e-13 * esc) { ok = false; break; }
        if (p != k) {
            for (int j = 0; j < n; j++) intercambiar_elem(M[p][j], M[k][j]);
            intercambiar_elem(r[p], r[k]);
        }
        for (int i = k + 1; i < n; i++) {
            double fct = M[i][k] / M[k][k];
            for (int j = k; j < n; j++) M[i][j] -= fct * M[k][j];
            r[i] -= fct * r[k];
        }
    }
    if (ok) {
        for (int i = n - 1; i >= 0; i--) {
            double s = r[i];
            for (int j = i + 1; j < n; j++) s -= M[i][j] * x[j];
            x[i] = s / M[i][i];
        }
    }
    del_mat(M, n);
    delete[] r;
    return ok;
}

// Newton-Raphson para sistemas SIN mensajes (ayuda para Newton en rango)
// Descripción: Igual que newton_raphson_sys pero mejora x EN SITIO, no imprime nada y devuelve true solo si converge (paso < tol, sin NaN ni divergencia) en max_iter iteraciones.
// El Jacobiano se calcula por diferencias centrales de 5 puntos (jacobian_mat). Falla si el Jacobiano es singular o la iteracion se dispara.
bool newton_raphson_sys_ok(double (*AF[])(double*, int), int n, double *x, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double f1(double *v, int n) { return v[0]*v[0] + v[1]*v[1] - 4; }
        double f2(double *v, int n) { return v[0]*v[1] - 1; }
        double (*Sist[2])(double*, int) = {f1, f2};
        double p[2] = {1.5, 0.5};
        bool ok = newton_raphson_sys_ok(Sist, 2, p, 1e-12, 50);   // ok = true, p = (1.9318517, 0.5176381)
    */
    double *F = new double[n];
    double *dx = new double[n];
    bool conv = false;
    for (int it = 0; it < max_iter; it++) {
        for (int i = 0; i < n; i++) F[i] = -AF[i](x, n);
        double **J = jacobian_mat(AF, x, n);
        bool ok = lineal_silencioso(J, F, n, dx);
        del_mat(J, n);
        if (!ok) break;
        double paso = 0.0;
        for (int i = 0; i < n; i++) { x[i] += dx[i]; paso += dx[i] * dx[i]; }
        paso = sqrt(paso);
        bool malo = isNaN(paso);
        for (int i = 0; i < n; i++) if (isNaN(x[i]) || fabs(x[i]) > 1e100) malo = true;
        if (malo) break;
        if (paso < tol) { conv = true; break; }
    }
    delete[] F; delete[] dx;
    return conv;
}

// Newton-Raphson para sistemas: soluciones distintas a partir de una lista de semillas, solo las que caen en un rango
// Descripción: Lanza Newton desde cada fila de 'semillas' (num_semillas x n) y se queda solo con las soluciones que (1) han convergido, (2) cumplen |F_i| < 100*tol, (3) estan dentro del rango
// a[i] <= x_i <= b[i] y (4) no estan repetidas. Devuelve una matriz num_sol x n ordenada por la primera variable (new; liberar con del_mat(S, num_sol)) y NULL si no hay ninguna.
// Es la version "todas las soluciones" de newton_raphson_multi_sys, que devuelve una fila por semilla (con repetidas y NaN).
double** newton_raphson_sys_filtrado(double (*AF[])(double*, int), int n, double *a, double *b, double **semillas, int num_semillas,
                                     double tol, int max_iter, int &num_sol) {
    /*
    Ejemplo de uso:
        // f1 = x^2 + y^2 - 4, f2 = x*y - 1  (4 soluciones); semillas elegidas a mano
        double a[2] = {0, 0}, b[2] = {3, 3};
        double d[4] = {2, 0.5,  0.5, 2};
        double **sem = mat_from_arr(d, 2, 2);
        int ns;
        double **S = newton_raphson_sys_filtrado(Sist, 2, a, b, sem, 2, 1e-12, 50, ns);   // ns = 2
    */
    num_sol = 0;
    int cap = 16;
    double **sol = new double*[cap];
    double *x = new double[n];
    double *F = new double[n];
    for (int s = 0; s < num_semillas; s++) {
        for (int i = 0; i < n; i++) x[i] = semillas[s][i];
        if (!newton_raphson_sys_ok(AF, n, x, tol, max_iter)) continue;
        bool valido = true;
        for (int i = 0; i < n; i++) {                                   // dentro del rango (con un pequeño margen)
            double marg = 1e-8 * (b[i] - a[i]) + 1e-12;
            if (x[i] < a[i] - marg || x[i] > b[i] + marg) valido = false;
        }
        for (int i = 0; i < n && valido; i++) if (fabs(AF[i](x, n)) > 100.0 * tol) valido = false;   // residuo pequeño
        for (int k = 0; k < num_sol && valido; k++) {                   // no repetida
            bool igual = true;
            for (int i = 0; i < n; i++) if (fabs(x[i] - sol[k][i]) > 1e-6 * (1.0 + fabs(sol[k][i]))) igual = false;
            if (igual) valido = false;
        }
        if (!valido) continue;
        if (num_sol >= cap) {
            int ncap = 2 * cap;
            double **t = new double*[ncap];
            for (int k = 0; k < num_sol; k++) t[k] = sol[k];
            delete[] sol; sol = t; cap = ncap;
        }
        sol[num_sol] = copy_vect(x, n);
        num_sol++;
    }
    delete[] x; delete[] F;
    for (int i = 1; i < num_sol; i++) {                                 // ordenar por x_1, x_2, ...
        double *clave = sol[i];
        int k = i - 1;
        while (k >= 0) {
            bool mayor = false;
            for (int c = 0; c < n; c++) {
                if (sol[k][c] > clave[c]) { mayor = true; break; }
                if (sol[k][c] < clave[c]) break;
            }
            if (!mayor) break;
            sol[k + 1] = sol[k];
            k--;
        }
        sol[k + 1] = clave;
    }
    if (num_sol == 0) {
        print_warning("newton_raphson_sys_filtrado: no se encontro ninguna solucion en el rango (prueba mas semillas o un rango mayor).");
        delete[] sol;
        return NULL;
    }
    return sol;
}

// Newton-Raphson para sistemas: TODAS las soluciones en un rango (malla de semillas)
// Descripción: Resuelve F(r) = 0 con r = (x_1, ..., x_n) y devuelve todas las soluciones distintas con a[i] <= x_i <= b[i]. Lanza Newton desde una malla de 'divisiones' puntos por variable (divisiones^n semillas, extremos incluidos).
// Devuelve una matriz num_sol x n ordenada por la primera variable (liberar con del_mat(S, num_sol)); NULL si no hay ninguna. Condiciones: F derivable; encuentra todas las soluciones cuya cuenca de atraccion contenga alguna semilla,
// asi que usa mas 'divisiones' si sospechas que faltan (el coste crece como divisiones^n: para n >= 3 mejor newton_raphson_sys_rango_aleat).
double** newton_raphson_sys_rango(double (*AF[])(double*, int), int n, double *a, double *b, int divisiones, double tol, int max_iter, int &num_sol) {
    /*
    Ejemplo de uso:
        double f1(double *v, int n) { return v[0]*v[0] + v[1]*v[1] - 4; }     // circunferencia
        double f2(double *v, int n) { return v[0]*v[1] - 1; }                  // hiperbola
        double (*Sist[2])(double*, int) = {f1, f2};
        double a[2] = {-3, -3}, b[2] = {3, 3};      // rango: x en (-3,3), y en (-3,3)
        int ns;
        double **S = newton_raphson_sys_rango(Sist, 2, a, b, 12, 1e-12, 50, ns);   // 4 soluciones
        print_mat(S, ns, 2, "Soluciones (x, y)");
    */
    num_sol = 0;
    if (n < 1 || divisiones < 1) { print_error("newton_raphson_sys_rango: n >= 1 y divisiones >= 1"); return NULL; }
    double total = pow((double)divisiones, (double)n);
    if (total > 5e6) { print_error("newton_raphson_sys_rango: demasiadas semillas (divisiones^n > 5e6); usa newton_raphson_sys_rango_aleat"); return NULL; }
    int ns = (int)(total + 0.5);
    double **sem = zeros_mat(ns, n);
    int *idx = new int[n];
    for (int i = 0; i < n; i++) idx[i] = 0;
    for (int s = 0; s < ns; s++) {
        for (int i = 0; i < n; i++)
            sem[s][i] = (divisiones == 1) ? 0.5 * (a[i] + b[i]) : a[i] + (b[i] - a[i]) * idx[i] / (divisiones - 1);
        for (int i = n - 1; i >= 0; i--) {                     // contador en base 'divisiones'
            idx[i]++;
            if (idx[i] < divisiones) break;
            idx[i] = 0;
        }
    }
    delete[] idx;
    double **S = newton_raphson_sys_filtrado(AF, n, a, b, sem, ns, tol, max_iter, num_sol);
    del_mat(sem, ns);
    return S;
}

// Newton-Raphson para sistemas: TODAS las soluciones en un rango (semillas aleatorias)
// Descripción: Igual que newton_raphson_sys_rango, pero lanza Newton desde 'num_semillas' puntos aleatorios uniformes dentro del rango (en vez de una malla). Es la opcion para 3 o mas variables,
// donde una malla tendria demasiados puntos. Usa rand(): llama antes a srand(semilla) si quieres otra secuencia. Devuelve num_sol x n ordenada por la primera variable (liberar con del_mat) o NULL.
double** newton_raphson_sys_rango_aleat(double (*AF[])(double*, int), int n, double *a, double *b, int num_semillas, double tol, int max_iter, int &num_sol) {
    /*
    Ejemplo de uso:
        // mismo sistema que newton_raphson_sys_rango, ahora con 200 semillas aleatorias
        double a[2] = {0, 0}, b[2] = {3, 3};         // solo el primer cuadrante: 2 soluciones
        int ns;
        double **S = newton_raphson_sys_rango_aleat(Sist, 2, a, b, 200, 1e-12, 50, ns);   // ns = 2
    */
    num_sol = 0;
    if (n < 1 || num_semillas < 1) { print_error("newton_raphson_sys_rango_aleat: n >= 1 y num_semillas >= 1"); return NULL; }
    double **sem = zeros_mat(num_semillas, n);
    for (int s = 0; s < num_semillas; s++)
        for (int i = 0; i < n; i++)
            sem[s][i] = a[i] + (b[i] - a[i]) * (rand() / (double)RAND_MAX);
    double **S = newton_raphson_sys_filtrado(AF, n, a, b, sem, num_semillas, tol, max_iter, num_sol);
    del_mat(sem, num_semillas);
    return S;
}

// ----------------------------------------------------------------------------
// MÉTODOS DE MINIMIZACIÓN: DESCENSO MÁS RÁPIDO (STEEPEST DESCENT)
// ----------------------------------------------------------------------------

// Helper: Calcula S(x) = sum(fi(x)^2) para convertir un sistema de ecuaciones en un problema de minimización
// Descripción: Convierte un sistema de ecuaciones f_i(x) = 0 en un problema de minimizacion: devuelve S(x) = suma de f_i(x)^2, que vale 0 solo en una solucion del sistema. La usan los metodos de minimizacion (descenso mas rapido).
double func_S_error(double (*AF[])(double*, int), double *x, int n) {
    /*
    Ejemplo de uso:
        double f1(double *x, int n) { return x[0]*x[0] + x[1]*x[1] - 4; }
        double f2(double *x, int n) { return x[0] - x[1]; }
        double (*AF[2])(double*, int) = {f1, f2};
        double x[2] = {1.0, 1.0};
        double S = func_S_error(AF, x, 2);
        // Resultado: S = 4   ((1+1-4)^2 + 0^2)
    */
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

// ============================================================================
// BLOQUE III: DIAGONALIZACION DE MATRICES. AUTOVALORES Y AUTOVECTORES
// ============================================================================

// ----------------------------------------------------------------------------
// III.1 EL PROBLEMA DE LOS AUTOVALORES (A*x = lambda*x)
// ----------------------------------------------------------------------------

// Polinomio característico de una matriz (Algoritmo de Faddeev-LeVerrier)
// Descripción: Devuelve los n+1 coeficientes (potencias decrecientes, listo para 'polyval') del polinomio monico det(lambda*I - A).
// Nota: el p(lambda) = det(A - lambda*I) de la teoria vale (-1)^n veces este polinomio; sus raices (los autovalores) son las mismas.
double* poly_caract_mat(double **A, int n) {
    /*
    Ejemplo de uso:
        // A = [3 0 1; 0 -3 0; 1 0 3]  ->  p = lambda^3 - 3*lambda^2 - 10*lambda + 24 = (l-4)(l+3)(l-2)
        double *p = poly_caract_mat(A, 3);     // p = {1, -3, -10, 24}
        cout << polyval(p, 4, 4.0);            // 0 : lambda = 4 es autovalor
    */
    double *c = new double[n + 1];
    double **M = zeros_mat(n, n);              // M_0 = 0
    c[0] = 1.0;
    for (int k = 1; k <= n; k++) {
        // M_k = A*M_(k-1) + c_(n-k+1)*I
        double **AM = prod_mat(A, M, n, n, n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = AM[i][j] + ((i == j) ? c[k - 1] : 0.0);
        del_mat(AM, n);
        // c_(n-k) = -traza(A*M_k)/k
        double **AMk = prod_mat(A, M, n, n, n, n);
        c[k] = -trace_mat(AMk, n) / k;
        del_mat(AMk, n);
    }
    del_mat(M, n);
    return c;
}

// Cociente de Rayleigh
// Descripción: Calcula x^T*A*x / x^T*x. Si x es un autovector devuelve su autovalor; si no, es la mejor estimacion del autovalor.
double rayleigh_mat(double **A, int n, double *x) {
    /*
    Ejemplo de uso:
        double v[] = {1, 0, 1};
        double lambda = rayleigh_mat(A, 3, v);   // 4 para A = [3 0 1; 0 -3 0; 1 0 3]
    */
    double *Ax = prod_mat_vect(A, n, n, x, n);
    double num = 0.0, den = 0.0;
    for (int i = 0; i < n; i++) { num += x[i] * Ax[i]; den += x[i] * x[i]; }
    delete[] Ax;
    return num / den;
}

// Residuo de un par autovalor-autovector
// Descripción: Devuelve la norma ||A*x - lambda*x||. Vale ~0 si (lambda, x) es un par autovalor-autovector correcto.
double resid_eig(double **A, int n, double lambda, double *x) {
    /*
    Ejemplo de uso:
        double r = resid_eig(A, 3, 4.0, v);   // ~0
    */
    double *Ax = prod_mat_vect(A, n, n, x, n);
    double s = 0.0;
    for (int i = 0; i < n; i++) s += (Ax[i] - lambda * x[i]) * (Ax[i] - lambda * x[i]);
    delete[] Ax;
    return sqrt(s);
}

// Residuo máximo de todos los pares autovalor-autovector
// Descripción: Comprueba A*u_k = L[k]*u_k para cada columna u_k de U y devuelve el mayor residuo.
double resid_eig_mat(double **A, int n, double *L, double **U) {
    /*
    Ejemplo de uso:
        double r = resid_eig_mat(A, n, L, U);   // ~1e-12 si la diagonalizacion es buena
    */
    double mx = 0.0;
    for (int k = 0; k < n; k++) {
        double *u = get_col_mat(U, n, n, k);
        double r = resid_eig(A, n, L[k], u);
        delete[] u;
        if (r > mx) mx = r;
    }
    return mx;
}

// Transformación de similaridad V^-1 * A * V
// Descripción: Si las columnas de V son autovectores de A, el resultado es la matriz diagonal de autovalores diag(l1,...,ln).
double** similar_mat(double **A, double **V, int n) {
    /*
    Ejemplo de uso:
        double **D = similar_mat(A, V, 3);   // diag(4, -3, 2) si V = [1 0 1; 0 1 0; 1 0 -1]
    */
    double **Vi = inv_lu(V, n);
    if (Vi == NULL) { print_error("similar_mat: V no es invertible"); return NULL; }
    double **AV = prod_mat(A, V, n, n, n, n);
    double **R = prod_mat(Vi, AV, n, n, n, n);
    del_mat(Vi, n); del_mat(AV, n);
    return R;
}

// Autovalor dominante: Método de la potencia
// Descripción: Itera x <- A*x/||A*x|| y estima el autovalor de mayor valor absoluto con el cociente de Rayleigh.
// Devuelve el autovalor y, por referencia, el autovector normalizado (v_out, reservado con new[]).
double potencia_eig(double **A, int n, double *&v_out, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double *v;
        double lambda = potencia_eig(A, 3, v, 1e-12, 1000);   // 4 para A = [3 0 1; 0 -3 0; 1 0 3]
    */
    double *x = new double[n];
    for (int i = 0; i < n; i++) x[i] = 1.0 + 0.1 * i;        // vector de partida generico
    double lambda = 0.0;
    for (int it = 0; it < max_iter; it++) {
        double *y = prod_mat_vect(A, n, n, x, n);
        double nrm = 0.0;
        for (int i = 0; i < n; i++) nrm += y[i] * y[i];
        nrm = sqrt(nrm);
        if (nrm == 0.0) { delete[] y; break; }
        double num = 0.0, den = 0.0;
        for (int i = 0; i < n; i++) { num += x[i] * y[i]; den += x[i] * x[i]; }
        lambda = num / den;
        double dif_m = 0.0, dif_p = 0.0;                    // el signo del autovector puede alternar si lambda < 0
        for (int i = 0; i < n; i++) {
            double xn = y[i] / nrm;
            dif_m += (xn - x[i]) * (xn - x[i]);
            dif_p += (xn + x[i]) * (xn + x[i]);
            x[i] = xn;
        }
        delete[] y;
        if (sqrt(dif_m < dif_p ? dif_m : dif_p) < tol) { lambda = rayleigh_mat(A, n, x); break; }
    }
    v_out = x;
    return lambda;
}

// Autovalor más cercano a un valor dado: Método de la potencia inversa con desplazamiento
// Descripción: Itera (A - mu*I)*y = x, de forma que converge al autovalor de A mas cercano a 'mu'. Con mu = 0 da el de menor valor absoluto.
// Devuelve el autovalor y, por referencia, su autovector normalizado (v_out, reservado con new[]).
double potencia_inv_eig(double **A, int n, double mu, double *&v_out, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double *v;
        double lambda = potencia_inv_eig(A, 3, 1.8, v, 1e-12, 100);   // 2 para A = [3 0 1; 0 -3 0; 1 0 3]
    */
    double *x = new double[n];
    for (int i = 0; i < n; i++) x[i] = 1.0 + 0.1 * i;
    double lambda = mu;
    for (int it = 0; it < max_iter; it++) {
        double **M = coppy_mat(A, n, n);
        for (int i = 0; i < n; i++) M[i][i] -= mu;
        double *y = gauss_solve(M, x, n);
        del_mat(M, n);
        if (y == NULL) { mu += 1e-10 * (1.0 + fabs(mu)); continue; }   // mu era (casi) un autovalor exacto
        double nrm = 0.0;
        for (int i = 0; i < n; i++) nrm += y[i] * y[i];
        nrm = sqrt(nrm);
        for (int i = 0; i < n; i++) x[i] = y[i] / nrm;
        delete[] y;
        double nuevo = rayleigh_mat(A, n, x);
        if (fabs(nuevo - lambda) < tol) { lambda = nuevo; break; }
        lambda = nuevo;
    }
    v_out = x;
    return lambda;
}

// ----------------------------------------------------------------------------
// III.2 DIAGONALIZACION DE MATRICES SIMETRICAS: METODO DE JACOBI
// ----------------------------------------------------------------------------

// Ordenar autovalores y autovectores
// Descripción: Ordena L en valor absoluto decreciente (como en la teoria: l1 = 4, l2 = -3, l3 = 2) y permuta las columnas de U en consecuencia.
// U puede ser NULL (si solo hay autovalores).
void sort_eig(double *L, double **U, int n) {
    /*
    Ejemplo de uso:
        sort_eig(L, U, n);      // autovalores y autovectores
        sort_eig(L, NULL, n);   // solo autovalores
    */
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (fabs(L[j]) > fabs(L[m])) m = j;
        if (m != i) {
            intercambiar_elem(L[i], L[m]);
            if (U != NULL)
                for (int k = 0; k < n; k++) intercambiar_elem(U[k][i], U[k][m]);
        }
    }
}

// Diagonalización de una matriz simétrica: Método de Jacobi
// Descripción: Aplica rotaciones planas R_ij(theta) que anulan en cada paso el mayor elemento fuera de la diagonal (ecs. [7] y [8] de la teoria)
// hasta que todos sean menores que 'tol'. TU ELIGES que quieres obtener:
//   calc_autoval -> L = array con los autovalores (new[]). Si es false, L = NULL.
//   calc_autovec -> U = matriz n x n cuyas COLUMNAS son los autovectores (new[]). Si es false, U = NULL y no se calcula (ahorra trabajo).
//   ordenar      -> ordena por |autovalor| decreciente (los autovectores se reordenan con ellos).
// Devuelve el numero de rotaciones realizadas, o -1 si la matriz no es simetrica. La matriz A no se modifica.
int jacobi_eig(double **A, int n, double *&L, double **&U, bool calc_autoval, bool calc_autovec, bool ordenar, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double *L; double **U;
        jacobi_eig(A, n, L, U, true, true, true, 1e-10, 1000);    // autovalores y autovectores, ordenados
        jacobi_eig(A, n, L, U, true, false, false, 1e-10, 1000);  // solo autovalores (U = NULL)
        jacobi_eig(A, n, L, U, false, true, false, 1e-10, 1000);  // solo autovectores (L = NULL)
        print_vect(L, n, "Autovalores");
        print_mat(U, n, n, "Autovectores (columnas)");
    */
    L = NULL;
    U = NULL;
    if (!calc_autoval && !calc_autovec) {
        print_warning("jacobi_eig: no se pidieron ni autovalores ni autovectores, no hay nada que calcular.");
        return 0;
    }
    if (!is_symmetric_mat(A, n, 1e-10)) {
        print_error("jacobi_eig: la matriz debe ser simetrica");
        return -1;
    }
    double **B = coppy_mat(A, n, n);
    double **V = calc_autovec ? eye_mat(n) : NULL;
    int n_rot = 0;

    while (n > 1) {
        // Paso 3: maximo (en valor absoluto) por encima de la diagonal
        int i = 0, j = 1;
        double mx = 0.0;
        for (int ib = 0; ib < n; ib++)
            for (int jb = ib + 1; jb < n; jb++)
                if (fabs(B[ib][jb]) > mx) { mx = fabs(B[ib][jb]); i = ib; j = jb; }
        if (mx < tol) break;
        if (n_rot >= max_iter) { print_warning("jacobi_eig alcanzo max_iter sin converger plenamente."); break; }

        // Paso 4: angulo theta (ec. [8])
        double theta;
        if (fabs(B[i][i] - B[j][j]) < 1e-14 * (fabs(B[i][i]) + fabs(B[j][j])) + 1e-300) theta = atan(1.0);  // pi/4
        else theta = 0.5 * atan(2.0 * B[i][j] / (B[i][i] - B[j][j]));
        double si = sin(theta), co = cos(theta);

        // Paso 5: V = V*R (sin construir R), solo si se piden los autovectores
        if (V != NULL) {
            for (int k = 0; k < n; k++) {
                double vki = V[k][i];
                V[k][i] = vki * co + V[k][j] * si;
                V[k][j] = -vki * si + V[k][j] * co;
            }
        }
        // Paso 6: B = R^T * B * R (ecs. [7b] a [7e])
        for (int k = 0; k < n; k++) {
            if (k != i && k != j) {
                double bki = B[k][i];
                B[k][i] = bki * co + B[k][j] * si;
                B[k][j] = -bki * si + B[k][j] * co;
                B[i][k] = B[k][i];
                B[j][k] = B[k][j];
            }
        }
        double aii = B[i][i], ajj = B[j][j], aij = B[i][j];
        B[i][i] = aii * co * co + ajj * si * si + 2.0 * aij * si * co;
        B[j][j] = aii * si * si + ajj * co * co - 2.0 * aij * si * co;
        B[i][j] = 0.0;
        B[j][i] = 0.0;
        n_rot++;
    }
    double *Ld = get_diag_mat(B, n);
    del_mat(B, n);
    if (ordenar) sort_eig(Ld, V, n);
    U = V;
    if (calc_autoval) L = Ld; else delete[] Ld;
    return n_rot;
}

// ----------------------------------------------------------------------------
// III.3 MATRICES GENERICAS: HESSENBERG, HOUSEHOLDER Y METODO QR
// ----------------------------------------------------------------------------

// Forma de Hessenberg superior por transformaciones de similaridad (eliminacion)
// Descripción: Hace cero los elementos por debajo de la subdiagonal con B^-1*A*B (multiplicadores b_i = a_i,m-1 / a_m,m-1, como en la teoria).
// Si el elemento subdiagonal es cero se intercambian fila y columna con el de mayor magnitud (asi no cambian los autovalores). Devuelve H (new[]).
// Si calc_P es true, P (new[]) es la matriz de transformacion con H = P^-1*A*P (NO es ortogonal): si w es autovector de H, entonces P*w lo es de A.
// Si calc_P es false, P = NULL.
double** hessenberg_mat(double **A, int n, double **&P, bool calc_P) {
    /*
    Ejemplo de uso:
        // A = [7 8 6 6; 1 6 -1 -2; 1 -2 5 -2; 3 4 3 4]
        double **P;
        double **H = hessenberg_mat(A, 4, P, true);    // H = [7 32 -60 6; 1 -1 21 -2; 0 -2 6 0; 0 0 -38 10]
        double **H2 = hessenberg_mat(A, 4, P, false);  // solo H (P = NULL)
    */
    double **H = coppy_mat(A, n, n);
    P = calc_P ? eye_mat(n) : NULL;
    for (int m = 1; m < n - 1; m++) {
        if (H[m][m - 1] == 0.0) {                       // buscar pivote
            int p = m;
            double mx = 0.0;
            for (int j = m + 1; j < n; j++) if (fabs(H[j][m - 1]) > mx) { mx = fabs(H[j][m - 1]); p = j; }
            if (p != m) {
                for (int j = 0; j < n; j++) intercambiar_elem(H[p][j], H[m][j]);   // filas
                for (int j = 0; j < n; j++) intercambiar_elem(H[j][p], H[j][m]);   // columnas
                if (P != NULL)
                    for (int j = 0; j < n; j++) intercambiar_elem(P[j][p], P[j][m]);
            }
        }
        double piv = H[m][m - 1];
        if (piv == 0.0) continue;
        for (int i = m + 1; i < n; i++) {
            double b = H[i][m - 1] / piv;
            if (b != 0.0) {
                for (int j = 0; j < n; j++) H[i][j] -= b * H[m][j];   // B^-1 * H : fila i -= b*fila m
                for (int j = 0; j < n; j++) H[j][m] += b * H[j][i];   // (.) * B  : columna m += b*columna i
                if (P != NULL)
                    for (int j = 0; j < n; j++) P[j][m] += b * P[j][i];   // P = P*B
            }
            H[i][m - 1] = 0.0;
        }
    }
    return H;
}

// Forma de Hessenberg superior por reflexiones de Householder
// Descripción: Igual que hessenberg_mat pero con reflexiones P = I - 2*v*v^T/(v^T*v) (transformaciones ortogonales, mas estables numericamente).
// Devuelve H (new[]). Si A es simetrica, H es tridiagonal. Si calc_Q es true, Q (new[]) es ortogonal con H = Q^T*A*Q:
// si w es autovector de H, entonces Q*w lo es de A. Si calc_Q es false, Q = NULL.
double** hessenberg_householder_mat(double **A, int n, double **&Q, bool calc_Q) {
    /*
    Ejemplo de uso:
        double **Q;
        double **H = hessenberg_householder_mat(A, n, Q, true);    // H = Q^T*A*Q
        double **H2 = hessenberg_householder_mat(A, n, Q, false);  // solo H (Q = NULL)
    */
    double **H = coppy_mat(A, n, n);
    Q = calc_Q ? eye_mat(n) : NULL;
    double *v = new double[n];
    for (int k = 0; k < n - 2; k++) {
        double norma = 0.0;
        for (int i = k + 1; i < n; i++) norma += H[i][k] * H[i][k];
        norma = sqrt(norma);
        if (norma == 0.0) continue;
        double alfa = (H[k + 1][k] > 0.0) ? -norma : norma;
        for (int i = 0; i < n; i++) v[i] = 0.0;
        v[k + 1] = H[k + 1][k] - alfa;
        for (int i = k + 2; i < n; i++) v[i] = H[i][k];
        double vv = 0.0;
        for (int i = k + 1; i < n; i++) vv += v[i] * v[i];
        if (vv == 0.0) continue;
        for (int j = 0; j < n; j++) {                      // H = P*H
            double s = 0.0;
            for (int i = k + 1; i < n; i++) s += v[i] * H[i][j];
            for (int i = k + 1; i < n; i++) H[i][j] -= 2.0 * s * v[i] / vv;
        }
        for (int i = 0; i < n; i++) {                      // H = H*P
            double s = 0.0;
            for (int j = k + 1; j < n; j++) s += H[i][j] * v[j];
            for (int j = k + 1; j < n; j++) H[i][j] -= 2.0 * s * v[j] / vv;
        }
        if (Q != NULL) {                                   // Q = Q*P
            for (int i = 0; i < n; i++) {
                double s = 0.0;
                for (int j = k + 1; j < n; j++) s += Q[i][j] * v[j];
                for (int j = k + 1; j < n; j++) Q[i][j] -= 2.0 * s * v[j] / vv;
            }
        }
        for (int i = k + 2; i < n; i++) H[i][k] = 0.0;
    }
    delete[] v;
    return H;
}

// Factorización QR por Gram-Schmidt modificado
// Descripción: Descompone A = Q*R con Q ortogonal (columnas ortonormales) y R triangular superior. Q y R se devuelven por referencia (new[]).
// Necesita que las columnas de A sean linealmente independientes (A invertible).
void qr_gs_mat(double **A, int n, double **&Q, double **&R) {
    /*
    Ejemplo de uso:
        double **Q, **R;
        qr_gs_mat(A, n, Q, R);   // A = Q*R
    */
    Q = zeros_mat(n, n);
    R = zeros_mat(n, n);
    double *v = new double[n];
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) v[k] = A[k][j];
        for (int i = 0; i < j; i++) {
            double r = 0.0;
            for (int k = 0; k < n; k++) r += Q[k][i] * v[k];
            R[i][j] = r;
            for (int k = 0; k < n; k++) v[k] -= r * Q[k][i];
        }
        double nrm = 0.0;
        for (int k = 0; k < n; k++) nrm += v[k] * v[k];
        nrm = sqrt(nrm);
        if (nrm < 1e-14) {
            print_error("qr_gs_mat: columnas linealmente dependientes");
            del_mat(Q, n); del_mat(R, n); delete[] v;
            Q = NULL; R = NULL;
            return;
        }
        R[j][j] = nrm;
        for (int k = 0; k < n; k++) Q[k][j] = v[k] / nrm;
    }
    delete[] v;
}

// Factorización QR por rotaciones (Givens)
// Descripción: Hace cero los elementos por debajo de la diagonal uno a uno con rotaciones P_k (c = a_jj/d, s = a_ij/d, d = sqrt(a_jj^2 + a_ij^2)).
// R = P_m*...*P_1*A y Q = P_1^T*...*P_m^T, de modo que A = Q*R. Q y R se devuelven por referencia (new[]). Funciona para cualquier A (no necesita ser invertible).
void qr_givens_mat(double **A, int n, double **&Q, double **&R) {
    /*
    Ejemplo de uso:
        double **Q, **R;
        qr_givens_mat(A, n, Q, R);   // A = Q*R
    */
    R = coppy_mat(A, n, n);
    Q = eye_mat(n);
    for (int j = 0; j < n - 1; j++) {
        for (int i = j + 1; i < n; i++) {
            if (R[i][j] == 0.0) continue;
            double d = sqrt(R[j][j] * R[j][j] + R[i][j] * R[i][j]);
            double c = R[j][j] / d, s = R[i][j] / d;
            for (int k = 0; k < n; k++) {                  // filas j e i de R
                double rj = R[j][k], ri = R[i][k];
                R[j][k] = c * rj + s * ri;
                R[i][k] = -s * rj + c * ri;
            }
            for (int k = 0; k < n; k++) {                  // columnas j e i de Q
                double qj = Q[k][j], qi = Q[k][i];
                Q[k][j] = c * qj + s * qi;
                Q[k][i] = -s * qj + c * qi;
            }
            R[i][j] = 0.0;
        }
    }
}

// Método QR: forma triangular (de Schur) y matriz de transformacion
// Descripción: Itera A(i) = Q(i)*R(i) -> A(i+1) = R(i)*Q(i) (mismos autovalores) hasta que la suma de |elementos bajo la diagonal| sea < tol.
// 'hess' elige la reduccion previa: 0 = ninguna, 1 = Hessenberg por Householder (ortogonal), 2 = Hessenberg por eliminacion (la de la teoria).
// Devuelve la matriz triangular T (new[]) y el numero de iteraciones. Si calc_M es true, M (new[]) es la matriz acumulada de todas las
// transformaciones con T = M^-1*A*M (ortogonal si hess = 0 o 1); si es false, M = NULL. Con autovalores complejos no converge a triangular.
int qr_schur_mat(double **A, int n, double **&T, double **&M, bool calc_M, double tol, int max_iter, int hess) {
    /*
    Ejemplo de uso:
        double **T, **M;
        int it = qr_schur_mat(A, n, T, M, true, 1e-12, 1000, 1);   // diagonal de T = autovalores
    */
    if (hess < 0 || hess > 2) { print_error_int("qr_schur_mat: hess debe ser 0, 1 o 2", hess); T = NULL; M = NULL; return -1; }
    if (hess == 1)      T = hessenberg_householder_mat(A, n, M, calc_M);
    else if (hess == 2) T = hessenberg_mat(A, n, M, calc_M);
    else { T = coppy_mat(A, n, n); M = calc_M ? eye_mat(n) : NULL; }
    int iter = 0;
    while (iter < max_iter) {
        double bajo = 0.0;
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++) bajo += fabs(T[i][j]);
        if (bajo < tol) break;
        double **Q, **R;
        qr_givens_mat(T, n, Q, R);
        del_mat(T, n);
        T = prod_mat(R, Q, n, n, n, n);
        if (M != NULL) {
            double **Mn = prod_mat(M, Q, n, n, n, n);
            del_mat(M, n);
            M = Mn;
        }
        del_mat(Q, n); del_mat(R, n);
        iter++;
    }
    if (iter >= max_iter) print_warning("qr_schur_mat alcanzo max_iter (posibles autovalores complejos o poca convergencia).");
    return iter;
}

// Método QR: matriz triangular superior semejante a A
// Descripción: Version corta de qr_schur_mat: devuelve solo la matriz triangular T (new[]) y las iteraciones en 'iter_out'.
// Si 'usar_hess' es true se aplica antes la reduccion de Hessenberg (Householder). Su diagonal son los autovalores.
// Con autovalores complejos no converge a triangular (quedan bloques 2x2).
double** qr_triang_mat(double **A, int n, double tol, int max_iter, bool usar_hess, int &iter_out) {
    /*
    Ejemplo de uso:
        int it;
        double **T = qr_triang_mat(A, n, 1e-12, 1000, true, it);   // diagonal de T = autovalores
    */
    double **T, **M;
    iter_out = qr_schur_mat(A, n, T, M, false, tol, max_iter, usar_hess ? 1 : 0);
    return T;
}

// Autovalores y autovectores de una matriz generica: Método QR
// Descripción: Obtiene la forma triangular T = M^-1*A*M con qr_schur_mat; los autovalores son su diagonal y los autovectores se calculan por
// sustitucion regresiva sobre T (y se pasan a A multiplicando por M). TU ELIGES que quieres obtener:
//   calc_autoval -> L = array con los autovalores (new[]). Si es false, L = NULL.
//   calc_autovec -> U = matriz n x n cuyas COLUMNAS son los autovectores normalizados (new[]). Si es false, U = NULL y no se calcula.
//   ordenar      -> ordena por |autovalor| decreciente (los autovectores se reordenan con ellos).
//   hess         -> reduccion previa: 0 = ninguna, 1 = Hessenberg por Householder, 2 = Hessenberg por eliminacion (la de la teoria).
// Devuelve el numero de iteraciones QR (o -1 si hess no es valido). Valido para matrices con autovalores reales.
int qr_eig(double **A, int n, double *&L, double **&U, bool calc_autoval, bool calc_autovec, bool ordenar, double tol, int max_iter, int hess) {
    /*
    Ejemplo de uso:
        // A = [7 8 6 6; 1 6 -1 -2; 1 -2 5 -2; 3 4 3 4]  -> autovalores 10, 7, 4, 1
        double *L; double **U;
        int it = qr_eig(A, 4, L, U, true, true, true, 1e-12, 5000, 1);   // autovalores y autovectores
        qr_eig(A, 4, L, U, true, false, false, 1e-12, 5000, 2);          // solo autovalores (con Hessenberg por eliminacion)
        print_vect(L, 4, "Autovalores");
    */
    L = NULL;
    U = NULL;
    if (!calc_autoval && !calc_autovec) {
        print_warning("qr_eig: no se pidieron ni autovalores ni autovectores, no hay nada que calcular.");
        return 0;
    }
    double **T, **M;
    int iter = qr_schur_mat(A, n, T, M, calc_autovec, tol, max_iter, hess);
    if (iter < 0) return -1;
    double *Ld = get_diag_mat(T, n);
    double **V = NULL;
    if (calc_autovec) {
        // Autovectores de T (triangular superior): para cada k, w_k con w_k[k] = 1 y sustitucion regresiva
        double normT = 0.0;
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) if (fabs(T[i][j]) > normT) normT = fabs(T[i][j]);
        if (normT == 0.0) normT = 1.0;
        double smin = 1e-12 * normT;                       // evita dividir por 0 con autovalores repetidos
        double **W = zeros_mat(n, n);
        for (int k = 0; k < n; k++) {
            W[k][k] = 1.0;
            for (int i = k - 1; i >= 0; i--) {
                double s = 0.0;
                for (int j = i + 1; j <= k; j++) s += T[i][j] * W[j][k];
                double den = T[i][i] - T[k][k];
                if (fabs(den) < smin) den = smin;
                W[i][k] = -s / den;
            }
        }
        V = prod_mat(M, W, n, n, n, n);                    // autovectores de A = M * W
        for (int k = 0; k < n; k++) {                      // normalizar columnas
            double nrm = 0.0;
            for (int i = 0; i < n; i++) nrm += V[i][k] * V[i][k];
            nrm = sqrt(nrm);
            if (nrm > 0.0) for (int i = 0; i < n; i++) V[i][k] /= nrm;
        }
        del_mat(W, n);
        del_mat(M, n);
    }
    del_mat(T, n);
    if (ordenar) sort_eig(Ld, V, n);
    U = V;
    if (calc_autoval) L = Ld; else delete[] Ld;
    return iter;
}

// ----------------------------------------------------------------------------
// INTERFAZ GENERAL: AUTOVALORES Y AUTOVECTORES DE CUALQUIER MATRIZ
// ----------------------------------------------------------------------------

// Autovalores y autovectores de cualquier matriz real (elige el metodo automaticamente)
// Descripción: Si A es simetrica usa el metodo de Jacobi; si no, el metodo QR con reduccion de Householder a Hessenberg.
// Mismas opciones que jacobi_eig y qr_eig: calc_autoval (array L de autovalores), calc_autovec (matriz U con los autovectores en las columnas)
// y ordenar (por |autovalor| decreciente). Devuelve el numero de rotaciones (Jacobi) o de iteraciones (QR), o -1 si hay error.
int eig_mat(double **A, int n, double *&L, double **&U, bool calc_autoval, bool calc_autovec, bool ordenar, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double *L; double **U;
        eig_mat(A, n, L, U, true, true, true, 1e-12, 5000);    // autovalores y autovectores
        eig_mat(A, n, L, U, true, false, true, 1e-12, 5000);   // solo autovalores, ordenados
    */
    if (is_symmetric_mat(A, n, 1e-10))
        return jacobi_eig(A, n, L, U, calc_autoval, calc_autovec, ordenar, tol, max_iter);
    return qr_eig(A, n, L, U, calc_autoval, calc_autovec, ordenar, tol, max_iter, 1);
}

// ============================================================================
// BLOQUE IV: INTEGRACION Y DERIVACION NUMERICA
// ============================================================================

// ----------------------------------------------------------------------------
// IV.1 INTEGRACION NUMERICA
// (La regla compuesta de Simpson 1/3 con funcion ya existe: integral_def_func)
// ----------------------------------------------------------------------------

// Newton-Cotes cerrada n=1: Regla Trapezoidal simple
// Descripción: I = h/2*(f(a)+f(b)) con h = b-a. Error = -h^3/12*f''(xi). Exacta para polinomios de grado 1.
double nc_trapecio(double (*f)(double), double a, double b) {
    /*
    Ejemplo de uso:
        double mi_func(double x) { return x*x*x - 2*x*x + 7*x - 5; }
        double I = nc_trapecio(mi_func, 1.0, 3.0);   // 26 (exacto: 20.6667)
    */
    return (b - a) / 2.0 * (f(a) + f(b));
}

// Newton-Cotes cerrada n=2: Regla de 1/3 de Simpson simple
// Descripción: I = h/3*(f(x0)+4f(x1)+f(x2)) con h = (b-a)/2. Error = -h^5/90*f''''(xi). Exacta para polinomios de grado <= 3.
double nc_simpson13(double (*f)(double), double a, double b) {
    /*
    Ejemplo de uso:
        double I = nc_simpson13(mi_func, 1.0, 3.0);   // 20.6667 (exacto)
    */
    double h = (b - a) / 2.0;
    return h / 3.0 * (f(a) + 4.0 * f(a + h) + f(b));
}

// Newton-Cotes cerrada n=3: Regla de 3/8 de Simpson simple
// Descripción: I = 3h/8*(f(x0)+3f(x1)+3f(x2)+f(x3)) con h = (b-a)/3. Error = -3h^5/80*f''''(xi). Exacta para polinomios de grado <= 3.
double nc_simpson38(double (*f)(double), double a, double b) {
    /*
    Ejemplo de uso:
        double I = nc_simpson38(mi_func, 1.0, 3.0);   // 20.6667 (exacto)
    */
    double h = (b - a) / 3.0;
    return 3.0 * h / 8.0 * (f(a) + 3.0 * f(a + h) + 3.0 * f(a + 2.0 * h) + f(b));
}

// Regla Trapezoidal compuesta (con función)
// Descripción: Divide [a,b] en 'n' subintervalos y suma trapecios: h*(f0/2 + f1 + ... + f(n-1) + fn/2). Error global O(h^2).
double trapecio_comp_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = trapecio_comp_func(mi_func, 1.0, 3.0, 100);
    */
    if (n < 1) { print_error_int("trapecio_comp_func: n debe ser >= 1", n); return MC_NAN; }
    double h = (b - a) / n;
    double suma = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) suma += f(a + i * h);
    return h * suma;
}

// Regla de 1/3 de Simpson compuesta (con función)
// Descripción: Aplica Simpson 1/3 en grupos de 2 subintervalos (n debe ser par; si no lo es se sube al siguiente par). Error global O(h^4).
double simpson13_comp_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = simpson13_comp_func(mi_func, 1.0, 3.0, 100);
    */
    if (n < 2) n = 2;
    if (n % 2 != 0) n++;
    double h = (b - a) / n;
    double suma = f(a) + f(b);
    for (int i = 1; i < n; i++) suma += ((i % 2 == 0) ? 2.0 : 4.0) * f(a + i * h);
    return h / 3.0 * suma;
}

// Regla de 3/8 de Simpson compuesta (con función)
// Descripción: Aplica Simpson 3/8 en grupos de 3 subintervalos (n debe ser multiplo de 3; si no lo es se sube al siguiente multiplo). Error global O(h^4).
double simpson38_comp_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = simpson38_comp_func(mi_func, 0.0, 1.0, 99);
    */
    if (n < 3) n = 3;
    if (n % 3 != 0) n += 3 - (n % 3);
    double h = (b - a) / n;
    double suma = f(a) + f(b);
    for (int i = 1; i < n; i++) suma += ((i % 3 == 0) ? 2.0 : 3.0) * f(a + i * h);
    return 3.0 * h / 8.0 * suma;
}

// Regla Trapezoidal compuesta (datos tabulados equiespaciados)
// Descripción: Integra los valores y[0..n_puntos-1] separados una distancia 'h'. (Para espaciado no uniforme usar int_vect).
double trapecio_comp_vect(double *y, int n_puntos, double h) {
    /*
    Ejemplo de uso:
        double I = trapecio_comp_vect(y, 10, 0.2);   // 9 subintervalos de h = 0.2
    */
    if (n_puntos < 2) { print_error_int("trapecio_comp_vect: se necesitan al menos 2 puntos", n_puntos); return MC_NAN; }
    double suma = 0.5 * (y[0] + y[n_puntos - 1]);
    for (int i = 1; i < n_puntos - 1; i++) suma += y[i];
    return h * suma;
}

// Regla de 1/3 de Simpson compuesta (datos tabulados equiespaciados)
// Descripción: Necesita un numero PAR de subintervalos (n_puntos impar). Si es impar, se usa la regla trapezoidal en el ultimo subintervalo y Simpson en el resto.
double simpson13_comp_vect(double *y, int n_puntos, double h) {
    /*
    Ejemplo de uso:
        double I = simpson13_comp_vect(y, 11, 0.1);   // 10 subintervalos
    */
    if (n_puntos < 2) { print_error_int("simpson13_comp_vect: se necesitan al menos 2 puntos", n_puntos); return MC_NAN; }
    int m = n_puntos - 1;                 // numero de subintervalos
    int ms = m - (m % 2);                 // subintervalos tratados con Simpson
    double res = 0.0;
    if (ms > 0) {
        double suma = y[0] + y[ms];
        for (int i = 1; i < ms; i++) suma += ((i % 2 == 0) ? 2.0 : 4.0) * y[i];
        res = h / 3.0 * suma;
    }
    if (m % 2 == 1) res += h * (y[m - 1] + y[m]) / 2.0;
    return res;
}

// Regla de 3/8 de Simpson compuesta (datos tabulados equiespaciados)
// Descripción: Necesita que el numero de subintervalos (n_puntos-1) sea multiplo de 3.
double simpson38_comp_vect(double *y, int n_puntos, double h) {
    /*
    Ejemplo de uso:
        double I = simpson38_comp_vect(y, 10, 0.1);   // 9 subintervalos
    */
    int m = n_puntos - 1;
    if (m < 3 || m % 3 != 0) { print_error_int("simpson38_comp_vect: n_puntos-1 debe ser multiplo de 3", m); return MC_NAN; }
    double suma = y[0] + y[m];
    for (int i = 1; i < m; i++) suma += ((i % 3 == 0) ? 2.0 : 3.0) * y[i];
    return 3.0 * h / 8.0 * suma;
}

// Pesos de integración (integral del polinomio de Lagrange)
// Descripción: Para los m nodos xs[0..m-1] (NO tienen que estar equiespaciados) calcula los pesos w[j] = integral de L_j(x) entre xs[0] y xs[m-1], de modo que
// integral(f) ~ sum(w[j]*f(xs[j])). Con nodos equiespaciados reproduce trapecio (m=2), Simpson 1/3 (m=3), Simpson 3/8 (m=4), Boole (m=5)... 'w' debe tener m posiciones.
void pesos_integ_lagrange(double *xs, int m, double *w) {
    /*
    Ejemplo de uso:
        double xs[] = {0.0, 0.5, 1.0}, w[3];
        pesos_integ_lagrange(xs, 3, w);     // w = {1/6, 4/6, 1/6}: Simpson 1/3 con h = 0.5
    */
    double H = xs[m - 1] - xs[0];
    double *u = new double[m];
    double *c = new double[m + 1];
    for (int k = 0; k < m; k++) u[k] = (xs[k] - xs[0]) / H;          // nodos normalizados a [0,1]
    for (int j = 0; j < m; j++) {
        for (int i = 0; i <= m; i++) c[i] = 0.0;
        c[0] = 1.0;
        int deg = 0;
        double den = 1.0;
        for (int k = 0; k < m; k++) {                                // L_j(u) = prod (u - u_k)/(u_j - u_k)
            if (k == j) continue;
            for (int i = deg + 1; i >= 1; i--) c[i] = c[i - 1] - u[k] * c[i];
            c[0] = -u[k] * c[0];
            deg++;
            den *= (u[j] - u[k]);
        }
        double integ = 0.0;
        for (int i = 0; i <= deg; i++) integ += c[i] / (i + 1.0);
        w[j] = H * integ / den;
    }
    delete[] u; delete[] c;
}

// Integral de datos tabulados y(x) con la precisión (grado) que elijas
// Descripción: Integra y respecto a x con los n puntos (x[i], y[i]). x puede tener CUALQUIER espaciado (saltos, zonas densas y dispersas...) pero debe ser estrictamente creciente o decreciente.
// 'grado' elige la precision: 1 = trapecio (O(h^2)), 2 = Simpson 1/3 (O(h^4)), 3 = Simpson 3/8 (O(h^4)), 4 = Boole (O(h^6)), hasta 6. Integra el polinomio de Lagrange de cada grupo de 'grado' subintervalos;
// si sobran subintervalos, el ultimo grupo usa un grado menor. Con muestras ruidosas, un grado alto NO mejora el resultado.
double integral_xy(double *x, double *y, int n, int grado) {
    /*
    Ejemplo de uso:
        double x[] = {0.0, 0.1, 0.2, 0.4, 0.8, 1.6, 2.0};       // espaciado NO uniforme
        double y[] = {0.0, 0.01, 0.04, 0.16, 0.64, 2.56, 4.0};   // y = x^2
        double I1 = integral_xy(x, y, 7, 1);                      // trapecio (menos preciso)
        double I2 = integral_xy(x, y, 7, 2);                      // Simpson 1/3: 2.66667 (exacto 8/3)
    */
    if (n < 2) { print_error_int("integral_xy: se necesitan al menos 2 puntos", n); return MC_NAN; }
    if (grado < 1 || grado > 6) { print_error_int("integral_xy: el grado debe estar entre 1 y 6", grado); return MC_NAN; }
    double sentido = (x[1] > x[0]) ? 1.0 : -1.0;
    for (int i = 0; i < n - 1; i++)
        if ((x[i + 1] - x[i]) * sentido <= 0.0) {
            print_error("integral_xy: x debe ser estrictamente creciente o decreciente (sin puntos repetidos)");
            return MC_NAN;
        }
    int m = n - 1;                              // subintervalos
    if (grado > m) grado = m;                   // pocos datos: se usa el mayor grado posible
    double w[8], suma = 0.0;
    int i = 0;
    while (i + grado <= m) {
        pesos_integ_lagrange(x + i, grado + 1, w);
        for (int j = 0; j <= grado; j++) suma += w[j] * y[i + j];
        i += grado;
    }
    int r = m - i;                              // subintervalos restantes (grado menor)
    if (r > 0) {
        pesos_integ_lagrange(x + i, r + 1, w);
        for (int j = 0; j <= r; j++) suma += w[j] * y[i + j];
    }
    return suma;
}

// Regla Trapezoidal de datos tabulados (y respecto a x)
// Descripción: Integra y respecto a x sumando trapecios. x puede ser NO uniforme. Error O(h^2). Es integral_xy con grado 1.
double trapecio_xy(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4};
        double y[] = {6.050, 7.389, 9.025, 11.023, 13.464, 16.445, 20.086, 24.533, 29.964};   // e^x
        double I = trapecio_xy(x, y, 9);   // 23.9944 (exacto: 23.9144)
    */
    return integral_xy(x, y, n, 1);
}

// Regla de 1/3 de Simpson de datos tabulados (y respecto a x)
// Descripción: Integra y respecto a x con parabolas por grupos de 3 puntos. x puede ser NO uniforme. Error O(h^4). Si el numero de subintervalos es impar, el ultimo se integra con un grado menor (trapecio). Es integral_xy con grado 2.
double simpson13_xy(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {0.0, 0.5, 1.0, 1.5, 2.0};
        double y[] = {0.0, 0.25, 1.0, 2.25, 4.0};     // y = x^2
        double I = simpson13_xy(x, y, 5);             // 2.66667 (exacto 8/3)
    */
    return integral_xy(x, y, n, 2);
}

// Regla de 3/8 de Simpson de datos tabulados (y respecto a x)
// Descripción: Integra y respecto a x con cubicas por grupos de 4 puntos. x puede ser NO uniforme. Error O(h^4). Si (n-1) no es multiplo de 3, el ultimo grupo usa un grado menor. Es integral_xy con grado 3.
double simpson38_xy(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double x[] = {0, 1, 2, 3, 4, 5, 6};
        double y[] = {0, 1, 8, 27, 64, 125, 216};     // y = x^3
        double I = simpson38_xy(x, y, 7);             // 324 (exacto)
    */
    return integral_xy(x, y, n, 3);
}

// Integral de datos tabulados y(x) con la tolerancia que elijas
// Descripción: Prueba grados crecientes (1 a 6) de integral_xy y se detiene cuando dos grados consecutivos difieren menos que 'tol'. Devuelve la integral, el grado usado y una estimacion del error (|I_g - I_(g-1)|).
// Valido para datos suaves y sin ruido y con x NO uniforme. Si no se alcanza 'tol' avisa y devuelve el resultado de grado maximo.
double integral_xy_tol(double *x, double *y, int n, double tol, int &grado_usado, double &err_est) {
    /*
    Ejemplo de uso:
        int g; double err;
        double I = integral_xy_tol(x, y, n, 1e-6, g, err);    // g = grado necesario, err = error estimado
    */
    double prev = integral_xy(x, y, n, 1);
    grado_usado = 1;
    err_est = MC_NAN;
    if (isNaN(prev)) return MC_NAN;
    int gmax = (n - 1 < 6) ? n - 1 : 6;
    for (int g = 2; g <= gmax; g++) {
        double cur = integral_xy(x, y, n, g);
        err_est = fabs(cur - prev);
        grado_usado = g;
        if (err_est < tol) return cur;
        prev = cur;
    }
    print_warning("integral_xy_tol: no se alcanzo la tolerancia con los datos disponibles (se devuelve el mejor resultado).");
    return prev;
}

// Extrapolación de Richardson para integrales
// Descripción: Combina dos estimaciones I_n1 e I_n2 (con n1 y n2 subintervalos) en una mejorada: I* = I_n1 + (I_n2 - I_n1)/(1 - (n1/n2)^p).
// p = 2 para la regla trapezoidal y p = 4 para Simpson. Con n2 = 2*n1 equivale a (4*I_n2 - I_n1)/3 (trapecio) o (16*I_n2 - I_n1)/15 (Simpson).
double richardson_int(double I_n1, double I_n2, double n1, double n2, double p) {
    /*
    Ejemplo de uso:
        // Trapecio con n1 = 2 (I = 22) y n2 = 4 (I = 21) para x^3-2x^2+7x-5 en [1,3]
        double I = richardson_int(22.0, 21.0, 2, 4, 2);   // 20.6667 (exacto)
    */
    return I_n1 + (I_n2 - I_n1) / (1.0 - pow(n1 / n2, p));
}

// Tabla de Romberg
// Descripción: Devuelve la matriz T[(N+1)x(N+1)] triangular inferior. T[i][0] es la regla trapezoidal con 2^i subintervalos y
// T[i][j] = (4^j*T[i][j-1] - T[i-1][j-1])/(4^j - 1) la j-esima extrapolacion de Richardson. Liberar con del_mat(T, N+1).
double** romberg_mat(double (*f)(double), double a, double b, int N) {
    /*
    Ejemplo de uso:
        double f_inv(double x) { return 1.0 / x; }
        double **T = romberg_mat(f_inv, 1.0, 137.2, 6);
        print_mat(T, 7, 7, "Romberg");   // ln(137.2) = 4.92144
    */
    if (N < 0) { print_error_int("romberg_mat: N debe ser >= 0", N); return NULL; }
    double **T = zeros_mat(N + 1, N + 1);
    T[0][0] = (b - a) / 2.0 * (f(a) + f(b));
    for (int i = 1; i <= N; i++) {
        int npan = 1 << (i - 1);                 // nuevos puntos (puntos medios)
        double h = (b - a) / (2.0 * npan);
        double suma = 0.0;
        for (int k = 1; k <= npan; k++) suma += f(a + (2 * k - 1) * h);
        T[i][0] = 0.5 * T[i - 1][0] + h * suma;
        double p4 = 1.0;
        for (int j = 1; j <= i; j++) {
            p4 *= 4.0;
            T[i][j] = (p4 * T[i][j - 1] - T[i - 1][j - 1]) / (p4 - 1.0);
        }
    }
    return T;
}

// Integración de Romberg con criterio de parada
// Descripción: Aumenta N hasta que dos valores consecutivos de la ultima fila de la tabla difieran menos que 'tol'. N_out devuelve el N usado.
double romberg_int(double (*f)(double), double a, double b, double tol, int N_max, int &N_out) {
    /*
    Ejemplo de uso:
        int N;
        double I = romberg_int(f_inv, 1.0, 137.2, 1e-8, 15, N);   // 4.92144
    */
    double **T = romberg_mat(f, a, b, N_max);
    if (T == NULL) return MC_NAN;
    double res = T[0][0];
    N_out = 0;
    for (int i = 1; i <= N_max; i++) {
        res = T[i][i];
        N_out = i;
        if (fabs(T[i][i] - T[i][i - 1]) < tol) break;
    }
    if (N_out == N_max && fabs(T[N_max][N_max] - T[N_max][N_max - 1]) >= tol)
        print_warning("romberg_int alcanzo N_max sin cumplir la tolerancia.");
    del_mat(T, N_max + 1);
    return res;
}

// Helper de integral_adapt: Simpson adaptativo recursivo
// Descripción: Compara Simpson en [a,b] con la suma de Simpson en cada mitad; si difieren mas que 15*tol divide el intervalo y repite (con tol/2). 'prof' limita la profundidad de la recursion.
double simpson_adapt_rec(double (*f)(double), double a, double b, double fa, double fm, double fb, double S, double tol, int prof) {
    /*
    Ejemplo de uso: (se usa a traves de integral_adapt)
    */
    double m = 0.5 * (a + b);
    double flm = f(0.5 * (a + m)), frm = f(0.5 * (m + b));
    double Sl = (m - a) / 6.0 * (fa + 4.0 * flm + fm);
    double Sr = (b - m) / 6.0 * (fm + 4.0 * frm + fb);
    if (prof <= 0 || fabs(Sl + Sr - S) <= 15.0 * tol) return Sl + Sr + (Sl + Sr - S) / 15.0;
    return simpson_adapt_rec(f, a, m, fa, flm, fm, Sl, 0.5 * tol, prof - 1)
         + simpson_adapt_rec(f, m, b, fm, frm, fb, Sr, 0.5 * tol, prof - 1);
}

// Integral de una función con la tolerancia que elijas (Simpson adaptativo)
// Descripción: Calcula la integral de f en [a,b] con un error aproximado menor que 'tol', refinando solo donde hace falta (mas puntos donde f cambia deprisa). Funciona con singularidades suaves como sqrt(x) en 0.
// Condiciones: f continua y acotada en [a,b]. Para funciones muy oscilantes pide una tolerancia razonable (la recursion esta limitada a 40 niveles).
double integral_adapt(double (*f)(double), double a, double b, double tol) {
    /*
    Ejemplo de uso:
        double I = integral_adapt(sqrt, 0.0, 1.0, 1e-8);     // 0.666666667 (exacto 2/3)
    */
    if (tol <= 0.0) { print_error("integral_adapt: tol debe ser > 0"); return MC_NAN; }
    double fa = f(a), fb = f(b), fm = f(0.5 * (a + b));
    double S = (b - a) / 6.0 * (fa + 4.0 * fm + fb);
    return simpson_adapt_rec(f, a, b, fa, fm, fb, S, tol, 40);
}

// Nodos y pesos de la cuadratura de Gauss-Legendre
// Descripción: Calcula los 'n' nodos x (raices del polinomio de Legendre de grado n, en [-1,1]) y sus pesos w. Exacta para polinomios de grado <= 2n-1.
// x y w se devuelven por referencia (new[]).
void gauss_legendre_nodos(int n, double *&x, double *&w) {
    /*
    Ejemplo de uso:
        double *x, *w;
        gauss_legendre_nodos(3, x, w);   // x = {-0.7746, 0, 0.7746}, w = {5/9, 8/9, 5/9}
    */
    x = new double[n];
    w = new double[n];
    double pi = acos(-1.0);
    for (int i = 0; i < (n + 1) / 2; i++) {
        double z = cos(pi * (i + 0.75) / (n + 0.5)), pp = 1.0;
        for (int it = 0; it < 100; it++) {
            double p1 = 1.0, p2 = 0.0;
            for (int j = 1; j <= n; j++) {          // recurrencia de Legendre
                double p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3) / j;
            }
            pp = n * (z * p1 - p2) / (z * z - 1.0);  // derivada P_n'(z)
            double z1 = z;
            z = z1 - p1 / pp;
            if (fabs(z - z1) < 1e-15) break;
        }
        x[i] = -z;
        x[n - 1 - i] = z;
        w[i] = 2.0 / ((1.0 - z * z) * pp * pp);
        w[n - 1 - i] = w[i];
    }
}

// Cuadratura gaussiana (Gauss-Legendre) de una función en [a,b]
// Descripción: Cambio de variable z = ((b-a)*x + b + a)/2 y suma ponderada de 'n' evaluaciones. Muy precisa con pocas evaluaciones si f es suave.
double gauss_legendre_func(double (*f)(double), double a, double b, int n) {
    /*
    Ejemplo de uso:
        double I = gauss_legendre_func(sin, 0.0, PI(15)/2, 2);   // 0.99847 (exacto: 1)
    */
    if (n < 1) { print_error_int("gauss_legendre_func: n debe ser >= 1", n); return MC_NAN; }
    double *x, *w;
    gauss_legendre_nodos(n, x, w);
    double mitad = (b - a) / 2.0, centro = (b + a) / 2.0, suma = 0.0;
    for (int i = 0; i < n; i++) suma += w[i] * f(mitad * x[i] + centro);
    delete[] x; delete[] w;
    return mitad * suma;
}

// Pesos de Newton-Cotes compuestas
// Descripción: Devuelve los n+1 pesos para 'n' subintervalos de longitud h. regla = 1 (trapecio), 2 (Simpson 1/3, n par) o 3 (Simpson 3/8, n multiplo de 3).
// Sirve para escribir una integral como suma ponderada sum(w_i*f(x_i)) y extenderla a integrales multiples.
double* pesos_nc(int n, int regla, double h) {
    /*
    Ejemplo de uso:
        double *w = pesos_nc(4, 2, 0.5);   // h/3*{1,4,2,4,1}
    */
    if (n < 1) { print_error_int("pesos_nc: n debe ser >= 1", n); return NULL; }
    if (regla == 2 && n % 2 != 0) { print_error_int("pesos_nc: Simpson 1/3 necesita n par", n); return NULL; }
    if (regla == 3 && n % 3 != 0) { print_error_int("pesos_nc: Simpson 3/8 necesita n multiplo de 3", n); return NULL; }
    if (regla < 1 || regla > 3) { print_error_int("pesos_nc: regla debe ser 1, 2 o 3", regla); return NULL; }
    double *w = new double[n + 1];
    for (int i = 0; i <= n; i++) {
        bool extremo = (i == 0 || i == n);
        if (regla == 1)      w[i] = (extremo ? 1.0 : 2.0) * h / 2.0;
        else if (regla == 2) w[i] = (extremo ? 1.0 : ((i % 2 == 0) ? 2.0 : 4.0)) * h / 3.0;
        else                 w[i] = (extremo ? 1.0 : ((i % 3 == 0) ? 2.0 : 3.0)) * 3.0 * h / 8.0;
    }
    return w;
}

// Integral doble de una función f(x,y) sobre [ax,bx] x [ay,by]
// Descripción: Doble sumatoria sum_j sum_i wy[j]*wx[i]*f(x_i,y_j) con 'nx' y 'ny' subintervalos y la regla elegida en cada direccion (rx, ry = 1, 2 o 3 como en pesos_nc).
double integral_doble_func(double (*f)(double, double), double ax, double bx, double ay, double by,
                           int nx, int ny, int rx, int ry) {
    /*
    Ejemplo de uso:
        double g(double x, double y) { return x * y; }
        double I = integral_doble_func(g, 0, 2, 0, 3, 10, 10, 2, 2);   // 9
    */
    double hx = (bx - ax) / nx, hy = (by - ay) / ny;
    double *wx = pesos_nc(nx, rx, hx);
    double *wy = pesos_nc(ny, ry, hy);
    if (wx == NULL || wy == NULL) { delete[] wx; delete[] wy; return MC_NAN; }
    double suma = 0.0;
    for (int j = 0; j <= ny; j++)
        for (int i = 0; i <= nx; i++)
            suma += wy[j] * wx[i] * f(ax + i * hx, ay + j * hy);
    delete[] wx; delete[] wy;
    return suma;
}

// Integral triple de una función f(x,y,z) sobre un paralelepipedo
// Descripción: Triple sumatoria con pesos w_ijk = a_i*b_j*c_k (nx, ny, nz subintervalos; reglas rx, ry, rz = 1, 2 o 3).
double integral_triple_func(double (*f)(double, double, double), double ax, double bx, double ay, double by,
                            double az, double bz, int nx, int ny, int nz, int rx, int ry, int rz) {
    /*
    Ejemplo de uso:
        double g(double x, double y, double z) { return x + y + z; }
        double I = integral_triple_func(g, 0, 1, 0, 1, 0, 1, 4, 4, 4, 2, 2, 2);   // 1.5
    */
    double hx = (bx - ax) / nx, hy = (by - ay) / ny, hz = (bz - az) / nz;
    double *wx = pesos_nc(nx, rx, hx);
    double *wy = pesos_nc(ny, ry, hy);
    double *wz = pesos_nc(nz, rz, hz);
    if (wx == NULL || wy == NULL || wz == NULL) { delete[] wx; delete[] wy; delete[] wz; return MC_NAN; }
    double suma = 0.0;
    for (int k = 0; k <= nz; k++)
        for (int j = 0; j <= ny; j++)
            for (int i = 0; i <= nx; i++)
                suma += wz[k] * wy[j] * wx[i] * f(ax + i * hx, ay + j * hy, az + k * hz);
    delete[] wx; delete[] wy; delete[] wz;
    return suma;
}

// Integral doble de datos tabulados f(x_i, y_j) en una malla equiespaciada
// Descripción: F es una matriz (ny+1) x (nx+1) con F[j][i] = f(x_i, y_j). Aplica la regla rx en la direccion x y ry en la y (como el ejemplo de la teoria:
// trapecio en x y Simpson 1/3 en y).
double integral_doble_mat(double **F, int nx, int ny, double hx, double hy, int rx, int ry) {
    /*
    Ejemplo de uso:
        double I = integral_doble_mat(F, 3, 4, 0.5, 0.1, 1, 2);   // 4 puntos en x (trapecio) y 5 en y (Simpson 1/3)
    */
    double *wx = pesos_nc(nx, rx, hx);
    double *wy = pesos_nc(ny, ry, hy);
    if (wx == NULL || wy == NULL) { delete[] wx; delete[] wy; return MC_NAN; }
    double suma = 0.0;
    for (int j = 0; j <= ny; j++)
        for (int i = 0; i <= nx; i++)
            suma += wy[j] * wx[i] * F[j][i];
    delete[] wx; delete[] wy;
    return suma;
}

// Integral doble por cuadratura gaussiana
// Descripción: Usa 'nx' nodos de Gauss-Legendre en x y 'ny' en y (cada direccion puede tener un numero distinto de terminos).
double gauss_doble_func(double (*f)(double, double), double ax, double bx, double ay, double by, int nx, int ny) {
    /*
    Ejemplo de uso:
        double I = gauss_doble_func(g, 0, 2, 0, 3, 3, 3);   // 9
    */
    double *xn, *wx, *yn, *wy;
    gauss_legendre_nodos(nx, xn, wx);
    gauss_legendre_nodos(ny, yn, wy);
    double mx = (bx - ax) / 2.0, cx = (bx + ax) / 2.0, my = (by - ay) / 2.0, cy = (by + ay) / 2.0;
    double suma = 0.0;
    for (int j = 0; j < ny; j++)
        for (int i = 0; i < nx; i++)
            suma += wy[j] * wx[i] * f(mx * xn[i] + cx, my * yn[j] + cy);
    delete[] xn; delete[] wx; delete[] yn; delete[] wy;
    return mx * my * suma;
}

// Integral triple por cuadratura gaussiana
// Descripción: Usa nx, ny y nz nodos de Gauss-Legendre en cada direccion (ejemplo de la teoria: 3 terminos en x y 2 en y, z).
double gauss_triple_func(double (*f)(double, double, double), double ax, double bx, double ay, double by,
                         double az, double bz, int nx, int ny, int nz) {
    /*
    Ejemplo de uso:
        double I = gauss_triple_func(g3, 0, 1, 0, 1, 0, 1, 2, 2, 2);
    */
    double *xn, *wx, *yn, *wy, *zn, *wz;
    gauss_legendre_nodos(nx, xn, wx);
    gauss_legendre_nodos(ny, yn, wy);
    gauss_legendre_nodos(nz, zn, wz);
    double mx = (bx - ax) / 2.0, cx = (bx + ax) / 2.0;
    double my = (by - ay) / 2.0, cy = (by + ay) / 2.0;
    double mz = (bz - az) / 2.0, cz = (bz + az) / 2.0;
    double suma = 0.0;
    for (int k = 0; k < nz; k++)
        for (int j = 0; j < ny; j++)
            for (int i = 0; i < nx; i++)
                suma += wz[k] * wy[j] * wx[i] * f(mx * xn[i] + cx, my * yn[j] + cy, mz * zn[k] + cz);
    delete[] xn; delete[] wx; delete[] yn; delete[] wy; delete[] zn; delete[] wz;
    return mx * my * mz * suma;
}

// ----------------------------------------------------------------------------
// IV.2 DERIVACION NUMERICA
// (La derivada de datos discretos con diferencias de 2 puntos ya existe: deriv_vect)
// Con h < 0 las formulas progresivas se convierten en regresivas.
// ----------------------------------------------------------------------------

// Derivada primera, diferencias progresivas de 2 puntos
// Descripción: f'(x) ~ (f(x+h) - f(x))/h. Error O(h).
double deriv_prog_2p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double d = deriv_prog_2p(exp, 0.0, 1e-4);   // ~1
    */
    return (f(x + h) - f(x)) / h;
}

// Derivada primera, diferencias regresivas de 2 puntos
// Descripción: f'(x) ~ (f(x) - f(x-h))/h. Error O(h).
double deriv_reg_2p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_reg_2p(f, 2.0, 0.1);
        // Resultado: d = 20.74913   (exacta: 22.167168)
    */
    return (f(x) - f(x - h)) / h;
}

// Derivada primera, diferencias progresivas de 3 puntos
// Descripción: f'(x) ~ (-3f(x) + 4f(x+h) - f(x+2h))/(2h). Error O(h^2).
double deriv_prog_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_prog_3p(f, 2.0, 0.1);
        // Resultado: d = 22.0323   (exacta: 22.167168)
    */
    return (-3.0 * f(x) + 4.0 * f(x + h) - f(x + 2.0 * h)) / (2.0 * h);
}

// Derivada primera, diferencias regresivas de 3 puntos
// Descripción: f'(x) ~ (3f(x) - 4f(x-h) + f(x-2h))/(2h). Error O(h^2).
double deriv_reg_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_reg_3p(f, 2.0, 0.1);
        // Resultado: d = 22.05452   (exacta: 22.167168)
    */
    return deriv_prog_3p(f, x, -h);
}

// Derivada primera, diferencias centrales de 3 puntos
// Descripción: f'(x) ~ (f(x+h) - f(x-h))/(2h). Error O(h^2) (la mejor relacion precision/coste).
double deriv_cent_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double d = deriv_cent_3p(exp, 0.0, 1e-3);   // ~1
    */
    return (f(x + h) - f(x - h)) / (2.0 * h);
}

// Derivada primera, diferencias progresivas de 5 puntos
// Descripción: f'(x) ~ (-25f(x) + 48f(x+h) - 36f(x+2h) + 16f(x+3h) - 3f(x+4h))/(12h). Error O(h^4).
double deriv_prog_5p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_prog_5p(f, 2.0, 0.1);
        // Resultado: d = 22.16591   (exacta: 22.167168)
    */
    return (-25.0 * f(x) + 48.0 * f(x + h) - 36.0 * f(x + 2.0 * h) + 16.0 * f(x + 3.0 * h) - 3.0 * f(x + 4.0 * h)) / (12.0 * h);
}

// Derivada primera, diferencias centrales de 5 puntos
// Descripción: f'(x) ~ (f(x-2h) - 8f(x-h) + 8f(x+h) - f(x+2h))/(12h). Error O(h^4).
double deriv_cent_5p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv_cent_5p(f, 2.0, 0.1);
        // Resultado: d = 22.167   (exacta: 22.167168)
    */
    return (f(x - 2.0 * h) - 8.0 * f(x - h) + 8.0 * f(x + h) - f(x + 2.0 * h)) / (12.0 * h);
}

// Derivada segunda, diferencias progresivas de 3 puntos
// Descripción: f''(x) ~ (f(x) - 2f(x+h) + f(x+2h))/h^2. Error O(h).
double deriv2_prog_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv2_prog_3p(f, 2.0, 0.1);
        // Resultado: d = 33.52283   (exacta: 29.556224)
    */
    return (f(x) - 2.0 * f(x + h) + f(x + 2.0 * h)) / (h * h);
}

// Derivada segunda, diferencias centrales de 3 puntos
// Descripción: f''(x) ~ (f(x-h) - 2f(x) + f(x+h))/h^2. Error O(h^2).
double deriv2_cent_3p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double d2 = deriv2_cent_3p(exp, 0.0, 1e-3);   // ~1
    */
    return (f(x - h) - 2.0 * f(x) + f(x + h)) / (h * h);
}

// Derivada segunda, diferencias progresivas de 5 puntos
// Descripción: f''(x) ~ (35f(x) - 104f(x+h) + 114f(x+2h) - 56f(x+3h) + 11f(x+4h))/(12h^2). Error O(h^3).
double deriv2_prog_5p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv2_prog_5p(f, 2.0, 0.1);
        // Resultado: d = 29.608   (exacta: 29.556224)
    */
    return (35.0 * f(x) - 104.0 * f(x + h) + 114.0 * f(x + 2.0 * h) - 56.0 * f(x + 3.0 * h) + 11.0 * f(x + 4.0 * h)) / (12.0 * h * h);
}

// Derivada segunda, diferencias centrales de 5 puntos
// Descripción: f''(x) ~ (-f(x-2h) + 16f(x-h) - 30f(x) + 16f(x+h) - f(x+2h))/(12h^2). Error O(h^4).
double deriv2_cent_5p(double (*f)(double), double x, double h) {
    /*
    Ejemplo de uso:
        double f(double x) { return x * exp(x); }
        double d = deriv2_cent_5p(f, 2.0, 0.1);
        // Resultado: d = 29.55616   (exacta: 29.556224)
    */
    return (-f(x - 2.0 * h) + 16.0 * f(x - h) - 30.0 * f(x) + 16.0 * f(x + h) - f(x + 2.0 * h)) / (12.0 * h * h);
}

// Derivada numérica con selección de fórmula
// Descripción: orden = 1 o 2 (derivada primera o segunda); puntos = 2, 3 o 5; tipo = 'p' (progresiva), 'r' (regresiva) o 'c' (central).
// Combinaciones validas: orden 1: p/r con 2, 3 o 5 puntos y c con 3 o 5; orden 2: p/r con 3 o 5 puntos y c con 3 o 5.
double deriv_func(double (*f)(double), double x, double h, int orden, int puntos, char tipo) {
    /*
    Ejemplo de uso:
        double d = deriv_func(exp, 0.0, 0.01, 1, 5, 'c');   // f'(0) con diferencias centrales de 5 puntos
    */
    double s = (tipo == 'r') ? -1.0 : 1.0;        // regresiva = progresiva con h cambiada de signo
    if (orden == 1) {
        if (tipo == 'c' && puntos == 3) return deriv_cent_3p(f, x, h);
        if (tipo == 'c' && puntos == 5) return deriv_cent_5p(f, x, h);
        if (tipo != 'c' && puntos == 2) return deriv_prog_2p(f, x, s * h);
        if (tipo != 'c' && puntos == 3) return deriv_prog_3p(f, x, s * h);
        if (tipo != 'c' && puntos == 5) return deriv_prog_5p(f, x, s * h);
    } else if (orden == 2) {
        if (tipo == 'c' && puntos == 3) return deriv2_cent_3p(f, x, h);
        if (tipo == 'c' && puntos == 5) return deriv2_cent_5p(f, x, h);
        if (tipo != 'c' && puntos == 3) return deriv2_prog_3p(f, x, s * h);
        if (tipo != 'c' && puntos == 5) return deriv2_prog_5p(f, x, s * h);
    }
    print_error("deriv_func: combinacion de orden/puntos/tipo no disponible");
    return MC_NAN;
}

// Tabla de extrapolación de Richardson para derivadas
// Descripción: T[i][0] = diferencia central de 3 puntos con h_i = h0/2^i y T[i][j] = (4^j*T[i][j-1] - T[i-1][j-1])/(4^j - 1) (error O(h^(2j+2))).
// orden = 1 o 2 (derivada primera o segunda). Devuelve la matriz N x N (triangular inferior). Liberar con del_mat(T, N).
double** richardson_deriv_mat(double (*f)(double), double x0, double h0, int N, int orden) {
    /*
    Ejemplo de uso:
        double g(double x) { return x * x * cos(x); }
        double **T = richardson_deriv_mat(g, 1.0, 0.1, 4, 1);
        print_mat(T, 4, 4, "Richardson");   // T[3][3] = 0.239132 (exacto: 0.2391336)
    */
    if (N < 1 || (orden != 1 && orden != 2)) { print_error("richardson_deriv_mat: N >= 1 y orden = 1 o 2"); return NULL; }
    double **T = zeros_mat(N, N);
    double h = h0;
    for (int i = 0; i < N; i++) {
        T[i][0] = (orden == 1) ? deriv_cent_3p(f, x0, h) : deriv2_cent_3p(f, x0, h);
        double p4 = 1.0;
        for (int j = 1; j <= i; j++) {
            p4 *= 4.0;
            T[i][j] = (p4 * T[i][j - 1] - T[i - 1][j - 1]) / (p4 - 1.0);
        }
        h /= 2.0;
    }
    return T;
}

// Derivada por extrapolación de Richardson
// Descripción: Devuelve la mejor estimacion (ultimo elemento de la tabla) con N niveles, partiendo de un paso h0 que se divide por 2 en cada nivel.
double deriv_richardson(double (*f)(double), double x0, double h0, int N, int orden) {
    /*
    Ejemplo de uso:
        double d = deriv_richardson(g, 1.0, 0.1, 4, 1);   // 0.239132
    */
    double **T = richardson_deriv_mat(f, x0, h0, N, orden);
    if (T == NULL) return MC_NAN;
    double r = T[N - 1][N - 1];
    del_mat(T, N);
    return r;
}

// Derivada de una función con la tolerancia que elijas (Richardson)
// Descripción: Calcula f'(x0) (orden = 1) o f''(x0) (orden = 2) refinando el paso (h0, h0/2, h0/4...) con extrapolacion de Richardson hasta que dos estimaciones consecutivas difieran menos que 'tol'.
// Devuelve la derivada y, en 'err_est', el error estimado. Se detiene antes si el error de redondeo empieza a dominar (no se puede pedir una tolerancia por debajo de ~1e-10).
double deriv_tol(double (*f)(double), double x0, double h0, double tol, int orden, double &err_est) {
    /*
    Ejemplo de uso:
        double err;
        double d = deriv_tol(exp, 1.0, 0.1, 1e-9, 1, err);     // e = 2.718281828 con error estimado err
    */
    if (orden != 1 && orden != 2) { print_error_int("deriv_tol: orden debe ser 1 o 2", orden); err_est = MC_NAN; return MC_NAN; }
    const int NMAX = 10;
    double T[NMAX][NMAX];
    double h = h0, mejor = MC_NAN, mejor_e = 1e300;
    for (int i = 0; i < NMAX; i++) {
        T[i][0] = (orden == 1) ? deriv_cent_3p(f, x0, h) : deriv2_cent_3p(f, x0, h);
        double p4 = 1.0;
        for (int j = 1; j <= i; j++) {
            p4 *= 4.0;
            T[i][j] = (p4 * T[i][j - 1] - T[i - 1][j - 1]) / (p4 - 1.0);
        }
        if (i >= 1) {
            double e = fabs(T[i][i] - T[i - 1][i - 1]);
            if (e < tol) { err_est = e; return T[i][i]; }
            if (e < mejor_e) { mejor_e = e; mejor = T[i][i]; }
            else if (i >= 3) break;                         // el redondeo empieza a dominar
        }
        h /= 2.0;
    }
    print_warning("deriv_tol: no se alcanzo la tolerancia (se devuelve el mejor resultado).");
    err_est = mejor_e;
    return mejor;
}

// Estudio del error de la derivada en función de h (truncamiento frente a redondeo)
// Descripción: Devuelve una matriz n x 3 con [h, derivada central de 3 puntos, |error|] para h = h0, h0/10, h0/100, ... Muestra que reducir h indefinidamente
// empeora el resultado por el error de redondeo. 'exacta' es el valor exacto de f'(x0).
double** err_deriv_h_mat(double (*f)(double), double x0, double exacta, double h0, int n) {
    /*
    Ejemplo de uso:
        double **E = err_deriv_h_mat(exp, 0.0, 1.0, 0.1, 11);   // h de 0.1 a 1e-10
        print_mat(E, 11, 3, "[h, D, error]");
    */
    double **E = zeros_mat(n, 3);
    double h = h0;
    for (int i = 0; i < n; i++) {
        double d = deriv_cent_3p(f, x0, h);
        E[i][0] = h; E[i][1] = d; E[i][2] = fabs(d - exacta);
        h /= 10.0;
    }
    return E;
}

// Derivada primera de datos equiespaciados con error O(h^2) en todos los puntos
// Descripción: Diferencias centrales en el interior y progresiva/regresiva de 3 puntos en los extremos (n >= 3). Mejora a deriv_vect, que usa 2 puntos en los bordes.
double* deriv_vect_3p(double *y, int n, double h) {
    /*
    Ejemplo de uso:
        double *dy = deriv_vect_3p(y, n, 0.1);
    */
    if (n < 3) { print_error_int("deriv_vect_3p: se necesitan al menos 3 puntos", n); return NULL; }
    double *d = new double[n];
    d[0] = (-3.0 * y[0] + 4.0 * y[1] - y[2]) / (2.0 * h);
    d[n - 1] = (3.0 * y[n - 1] - 4.0 * y[n - 2] + y[n - 3]) / (2.0 * h);
    for (int i = 1; i < n - 1; i++) d[i] = (y[i + 1] - y[i - 1]) / (2.0 * h);
    return d;
}

// Derivada primera de datos equiespaciados con error O(h^4) en el interior
// Descripción: Centrales de 5 puntos en i = 2..n-3, progresiva/regresiva de 5 puntos en los extremos y centrales de 3 puntos en i = 1 y n-2 (n >= 5).
double* deriv_vect_5p(double *y, int n, double h) {
    /*
    Ejemplo de uso:
        double *dy = deriv_vect_5p(y, n, 0.1);
    */
    if (n < 5) { print_error_int("deriv_vect_5p: se necesitan al menos 5 puntos", n); return NULL; }
    double *d = new double[n];
    d[0] = (-25.0 * y[0] + 48.0 * y[1] - 36.0 * y[2] + 16.0 * y[3] - 3.0 * y[4]) / (12.0 * h);
    d[n - 1] = (25.0 * y[n - 1] - 48.0 * y[n - 2] + 36.0 * y[n - 3] - 16.0 * y[n - 4] + 3.0 * y[n - 5]) / (12.0 * h);
    d[1] = (y[2] - y[0]) / (2.0 * h);
    d[n - 2] = (y[n - 1] - y[n - 3]) / (2.0 * h);
    for (int i = 2; i < n - 2; i++) d[i] = (y[i - 2] - 8.0 * y[i - 1] + 8.0 * y[i + 1] - y[i + 2]) / (12.0 * h);
    return d;
}

// Derivada segunda de datos equiespaciados
// Descripción: Diferencias centrales de 3 puntos en el interior (O(h^2)) y progresiva/regresiva de 3 puntos en los extremos (O(h)). n >= 3.
double* deriv2_vect(double *y, int n, double h) {
    /*
    Ejemplo de uso:
        double *d2y = deriv2_vect(y, n, 0.1);
    */
    if (n < 3) { print_error_int("deriv2_vect: se necesitan al menos 3 puntos", n); return NULL; }
    double *d = new double[n];
    d[0] = (y[0] - 2.0 * y[1] + y[2]) / (h * h);
    d[n - 1] = (y[n - 1] - 2.0 * y[n - 2] + y[n - 3]) / (h * h);
    for (int i = 1; i < n - 1; i++) d[i] = (y[i - 1] - 2.0 * y[i] + y[i + 1]) / (h * h);
    return d;
}

// Derivada de datos tabulados y(x) con la precisión (nº de puntos) que elijas
// Descripción: Deriva y respecto a x en cada punto con una formula de 'puntos' puntos (derivada del polinomio de Lagrange). x puede tener CUALQUIER espaciado pero debe ser estrictamente monotono.
// orden = 1 o 2 (derivada primera o segunda); puntos = de orden+1 a 9. El error es O(h^(puntos-1)): 3 puntos -> O(h^2), 5 puntos -> O(h^4). Formulas centradas en el interior y laterales en los extremos.
// Con datos con ruido, mas puntos NO siempre mejoran el resultado (la derivada amplifica el ruido).
double* deriv_xy(double *x, double *y, int n, int orden, int puntos) {
    /*
    Ejemplo de uso:
        double x[] = {0.0, 0.1, 0.2, 0.4, 0.7, 1.0};           // espaciado NO uniforme
        double y[] = {0.0, 0.01, 0.04, 0.16, 0.49, 1.0};       // y = x^2
        double *dy  = deriv_xy(x, y, 6, 1, 3);                  // dy/dx = 2x (exacta con 3 puntos)
        double *d2y = deriv_xy(x, y, 6, 2, 3);                  // d2y/dx2 = 2
    */
    if (orden != 1 && orden != 2) { print_error_int("deriv_xy: orden debe ser 1 o 2", orden); return NULL; }
    if (puntos < orden + 1 || puntos > 9) { print_error_int("deriv_xy: puntos debe estar entre orden+1 y 9", puntos); return NULL; }
    if (n < puntos) { print_error_int("deriv_xy: hay menos datos que puntos de la formula", n); return NULL; }
    double sentido = (x[1] > x[0]) ? 1.0 : -1.0;
    for (int i = 0; i < n - 1; i++)
        if ((x[i + 1] - x[i]) * sentido <= 0.0) {
            print_error("deriv_xy: x debe ser estrictamente creciente o decreciente (sin puntos repetidos)");
            return NULL;
        }
    double *d = new double[n];
    double w[9];
    for (int i = 0; i < n; i++) {
        int s = i - (puntos - 1) / 2;                 // formula centrada si es posible
        if (s < 0) s = 0;
        if (s > n - puntos) s = n - puntos;
        pesos_deriv_lagrange(x + s, puntos, x[i], orden, w);
        double suma = 0.0;
        for (int k = 0; k < puntos; k++) suma += w[k] * y[s + k];
        d[i] = suma;
    }
    return d;
}

// Derivada primera de datos tabulados y(x), formulas de 3 puntos
// Descripción: dy/dx con error O(h^2) en todos los puntos (centrales en el interior, laterales en los extremos). x puede ser NO uniforme. Es deriv_xy con orden 1 y 3 puntos. Necesita n >= 3.
double* deriv_xy_3p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *dy = deriv_xy_3p(x, y, n);
        print_vect(dy, n, "dy/dx");
    */
    return deriv_xy(x, y, n, 1, 3);
}

// Derivada primera de datos tabulados y(x), formulas de 5 puntos
// Descripción: dy/dx con error O(h^4). x puede ser NO uniforme. Es deriv_xy con orden 1 y 5 puntos. Necesita n >= 5.
double* deriv_xy_5p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *x = linspace(0.0, 1.0, 11);
        double *y = sin_vect(x, 11);
        double *dy = deriv_xy_5p(x, y, 11);       // ~ cos(x) con error O(h^4)
    */
    return deriv_xy(x, y, n, 1, 5);
}

// Derivada segunda de datos tabulados y(x), formulas de 3 puntos
// Descripción: d2y/dx2 con error O(h^2) en el interior (O(h) en los extremos). x puede ser NO uniforme. Es deriv_xy con orden 2 y 3 puntos. Necesita n >= 3.
double* deriv2_xy_3p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *d2y = deriv2_xy_3p(x, y, n);
    */
    return deriv_xy(x, y, n, 2, 3);
}

// Derivada segunda de datos tabulados y(x), formulas de 5 puntos
// Descripción: d2y/dx2 con error O(h^4) en el interior. x puede ser NO uniforme. Es deriv_xy con orden 2 y 5 puntos. Necesita n >= 5.
double* deriv2_xy_5p(double *x, double *y, int n) {
    /*
    Ejemplo de uso:
        double *d2y = deriv2_xy_5p(x, y, n);       // ~ -sin(x) si y = sin(x)
    */
    return deriv_xy(x, y, n, 2, 5);
}

// Derivada de datos tabulados y(x) con la tolerancia que elijas
// Descripción: Prueba formulas con mas y mas puntos (de orden+1 hasta 9) y se detiene cuando dos consecutivas difieren, en todos los puntos, menos que 'tol'. Devuelve la derivada, los puntos usados y el error estimado (max |d_p - d_(p-1)|).
// Valido para datos suaves y sin ruido y con x NO uniforme. Si no se alcanza 'tol' avisa y devuelve el mejor resultado.
double* deriv_xy_tol(double *x, double *y, int n, int orden, double tol, int &puntos_usados, double &err_max) {
    /*
    Ejemplo de uso:
        int p; double err;
        double *dy = deriv_xy_tol(x, y, n, 1, 1e-6, p, err);     // p = puntos necesarios
    */
    int p0 = orden + 1;
    double *prev = deriv_xy(x, y, n, orden, p0);
    puntos_usados = p0;
    err_max = MC_NAN;
    if (prev == NULL) return NULL;
    int pmax = (n < 9) ? n : 9;
    for (int p = p0 + 1; p <= pmax; p++) {
        double *cur = deriv_xy(x, y, n, orden, p);
        double e = 0.0;
        for (int i = 0; i < n; i++) if (fabs(cur[i] - prev[i]) > e) e = fabs(cur[i] - prev[i]);
        delete[] prev;
        prev = cur;
        puntos_usados = p;
        err_max = e;
        if (e < tol) return prev;
    }
    print_warning("deriv_xy_tol: no se alcanzo la tolerancia con los datos disponibles (se devuelve el mejor resultado).");
    return prev;
}

// ============================================================================
// BLOQUE V: SOLUCION NUMERICA DE ECUACIONES DIFERENCIALES ORDINARIAS (EDO's)
// Convenios: una EDO y' = f(x,y) se pasa como double f(double x, double y).
//            Un sistema se pasa como array de funciones AF[i](t, y, n) = dy_i/dt.
// ============================================================================

// Error máximo entre dos vectores
// Descripción: Devuelve max|a[i]-b[i]|. Util para comparar la solucion numerica con la analitica.
double err_max_vect(double *a, double *b, int n) {
    /*
    Ejemplo de uso:
        double e = err_max_vect(y_num, y_exacta, n + 1);
    */
    double mx = 0.0;
    for (int i = 0; i < n; i++) if (fabs(a[i] - b[i]) > mx) mx = fabs(a[i] - b[i]);
    return mx;
}

// ----------------------------------------------------------------------------
// V.1 EDO's CON VALORES INICIALES: TAYLOR, EULER Y RUNGE-KUTTA
// ----------------------------------------------------------------------------

// Método de la serie de Taylor
// Descripción: Evalua y(x0+h) = sum_k y^(k)(x0)*h^k/k! a partir de las 'n' derivadas conocidas derivs[k] = y^(k)(x0), k = 0..n-1.
double taylor_eval(double *derivs, int n, double h) {
    /*
    Ejemplo de uso:
        // y' = -2x - y, y(0) = -1  ->  derivadas en 0: -1, 1, -3, 3, -3
        double d[] = {-1, 1, -3, 3, -3};
        double y = taylor_eval(d, 5, 0.1);   // -0.91451
    */
    double suma = 0.0, termino = 1.0;
    for (int k = 0; k < n; k++) {
        suma += derivs[k] * termino;
        termino *= h / (k + 1.0);
    }
    return suma;
}

// Método de Euler
// Descripción: y_(n+1) = y_n + h*f(x_n,y_n) con 'n' pasos entre x0 y xf. Devuelve y[0..n] y los puntos x en x_out (ambos new[]). Error global O(h).
double* euler_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out) {
    /*
    Ejemplo de uso:
        double f(double x, double y) { return -2*x - y; }
        double *x, *y = euler_edo(f, 0.0, -1.0, 0.5, 5, x);   // h = 0.1
    */
    if (n < 1) { print_error_int("euler_edo: n debe ser >= 1", n); x_out = NULL; return NULL; }
    double h = (xf - x0) / n;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        y[i + 1] = y[i] + h * f(x_out[i], y[i]);
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}

// Método de Euler mejorado (predictor-corrector)
// Descripción: Predice y_p = y_n + h*f(x_n,y_n) y corrige y_c = y_n + h*(f(x_n,y_n) + f(x_n+h,y_p))/2. 'n_corr' es el numero de correcciones (1 = metodo de Heun).
// Error local O(h^3) y global O(h^2).
double* euler_mejorado_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out, int n_corr) {
    /*
    Ejemplo de uso:
        double *x, *y = euler_mejorado_edo(f, 0.0, -1.0, 0.5, 5, x, 1);
    */
    if (n < 1 || n_corr < 1) { print_error("euler_mejorado_edo: n y n_corr deben ser >= 1"); x_out = NULL; return NULL; }
    double h = (xf - x0) / n;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        double f0 = f(x_out[i], y[i]);
        double yp = y[i] + h * f0;                     // prediccion (Euler)
        for (int c = 0; c < n_corr; c++) yp = y[i] + h * (f0 + f(x_out[i] + h, yp)) / 2.0;   // correccion
        y[i + 1] = yp;
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}

// Método de Runge-Kutta de segundo orden (familia de un parametro)
// Descripción: y_(n+1) = y_n + a*k1 + b*k2 con b = 1-a, k1 = h*f(x,y), k2 = h*f(x+alfa*h, y+beta*k1) y alfa = beta = 1/(2b). 0 <= a < 1.
// a = 1/2 es Euler mejorado (Heun), a = 0 es el metodo del punto medio, a = 1/3 es Ralston.
double* rk2_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out, double a) {
    /*
    Ejemplo de uso:
        double *x, *y = rk2_edo(f, 0.0, -1.0, 0.5, 5, x, 0.5);   // = Heun
    */
    if (n < 1 || a < 0.0 || a >= 1.0) { print_error("rk2_edo: n >= 1 y 0 <= a < 1"); x_out = NULL; return NULL; }
    double h = (xf - x0) / n, b = 1.0 - a, alfa = 1.0 / (2.0 * b);
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        double k1 = h * f(x_out[i], y[i]);
        double k2 = h * f(x_out[i] + alfa * h, y[i] + alfa * k1);
        y[i + 1] = y[i] + a * k1 + b * k2;
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}

// Método de Runge-Kutta de cuarto orden
// Descripción: y_(n+1) = y_n + (k1 + 2k2 + 2k3 + k4)/6. Error local O(h^5) y global O(h^4).
double* rk4_edo(double (*f)(double, double), double x0, double y0, double xf, int n, double *&x_out) {
    /*
    Ejemplo de uso:
        double *x, *y = rk4_edo(f, 0.0, -1.0, 0.5, 5, x);   // y(0.5) = -0.81959 (exacto hasta 5 cifras)
    */
    if (n < 1) { print_error_int("rk4_edo: n debe ser >= 1", n); x_out = NULL; return NULL; }
    double h = (xf - x0) / n;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    x_out[0] = x0; y[0] = y0;
    for (int i = 0; i < n; i++) {
        double xi = x_out[i], yi = y[i];
        double k1 = h * f(xi, yi);
        double k2 = h * f(xi + 0.5 * h, yi + 0.5 * k1);
        double k3 = h * f(xi + 0.5 * h, yi + 0.5 * k2);
        double k4 = h * f(xi + h, yi + k3);
        y[i + 1] = yi + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    return y;
}

// Paso de Runge-Kutta-Fehlberg (4o y 5o orden)
// Descripción: Avanza un paso h desde (x,y) con 6 evaluaciones de f. Devuelve el valor de 5o orden y, en 'err', la estimacion del error
// y5 - y4 = k1/360 - 128k3/4275 - 2197k4/75240 + k5/50 + 2k6/55.
double rkf45_paso(double (*f)(double, double), double x, double y, double h, double &err) {
    /*
    Ejemplo de uso:
        double e, y1 = rkf45_paso(f, 0.0, -1.0, 0.1, e);   // y(0.1) = -0.914512251, e ~ -4e-8
    */
    double k1 = h * f(x, y);
    double k2 = h * f(x + h / 4.0, y + k1 / 4.0);
    double k3 = h * f(x + 3.0 * h / 8.0, y + 3.0 * k1 / 32.0 + 9.0 * k2 / 32.0);
    double k4 = h * f(x + 12.0 * h / 13.0, y + 1932.0 * k1 / 2197.0 - 7200.0 * k2 / 2197.0 + 7296.0 * k3 / 2197.0);
    double k5 = h * f(x + h, y + 439.0 * k1 / 216.0 - 8.0 * k2 + 3680.0 * k3 / 513.0 - 845.0 * k4 / 4104.0);
    double k6 = h * f(x + h / 2.0, y - 8.0 * k1 / 27.0 + 2.0 * k2 - 3544.0 * k3 / 2565.0 + 1859.0 * k4 / 4104.0 - 11.0 * k5 / 40.0);
    double y4 = y + 25.0 * k1 / 216.0 + 1408.0 * k3 / 2565.0 + 2197.0 * k4 / 4104.0 - k5 / 5.0;
    double y5 = y + 16.0 * k1 / 135.0 + 6656.0 * k3 / 12825.0 + 28561.0 * k4 / 56430.0 - 9.0 * k5 / 50.0 + 2.0 * k6 / 55.0;
    err = y5 - y4;
    return y5;
}

// Método de Runge-Kutta-Fehlberg con paso adaptativo
// Descripción: Parte del paso h0 y lo ajusta en cada iteracion (h_nuevo = 0.9*h*(tol/|err|)^(1/5)) para que el error por paso sea menor que 'tol'.
// Devuelve los valores y (new[]) en los puntos aceptados, x_out con las abscisas y n_out = numero de puntos. max_pasos limita el trabajo total.
double* rkf45_edo(double (*f)(double, double), double x0, double y0, double xf, double h0, double tol,
                  int max_pasos, double *&x_out, int &n_out) {
    /*
    Ejemplo de uso:
        double *x; int n;
        double *y = rkf45_edo(f, 0.0, -1.0, 0.5, 0.1, 1e-8, 10000, x, n);
    */
    int cap = 64;
    double *y = new double[cap];
    x_out = new double[cap];
    n_out = 1;
    x_out[0] = x0; y[0] = y0;
    double h = h0;
    double sentido = (xf >= x0) ? 1.0 : -1.0;
    h = fabs(h) * sentido;
    int pasos = 0;
    while ((xf - x_out[n_out - 1]) * sentido > 1e-14 * fabs(xf - x0) && pasos < max_pasos) {
        double x = x_out[n_out - 1];
        if ((x + h - xf) * sentido > 0.0) h = xf - x;          // no pasarse de xf
        double err;
        double ynew = rkf45_paso(f, x, y[n_out - 1], h, err);
        double e = fabs(err);
        if (e <= tol || fabs(h) < 1e-14) {                      // paso aceptado
            if (n_out >= cap) {
                int ncap = 2 * cap;
                double *ty = new double[ncap], *tx = new double[ncap];
                for (int i = 0; i < n_out; i++) { ty[i] = y[i]; tx[i] = x_out[i]; }
                delete[] y; delete[] x_out;
                y = ty; x_out = tx; cap = ncap;
            }
            y[n_out] = ynew;
            x_out[n_out] = x + h;
            n_out++;
        }
        double factor = (e == 0.0) ? 5.0 : 0.9 * pow(tol / e, 0.2);
        if (factor > 5.0) factor = 5.0;
        if (factor < 0.1) factor = 0.1;
        h *= factor;
        pasos++;
    }
    if (pasos >= max_pasos) print_warning("rkf45_edo alcanzo max_pasos antes de llegar a xf.");
    return y;
}

// ----------------------------------------------------------------------------
// V.2 SISTEMAS DE EDO's DE PRIMER ORDEN Y EDO's DE ORDEN SUPERIOR
// ----------------------------------------------------------------------------

// Helper: evalua el vector de derivadas dy_i/dt = AF[i](t, y, n)
// Descripción: Funcion auxiliar de los metodos para sistemas de EDO's: evalua el vector de derivadas dy[i] = AF[i](t, y, n) para las n ecuaciones del sistema en el instante t.
void eval_sys(double (*AF[])(double, double*, int), double t, double *y, int n, double *dy) {
    /*
    Ejemplo de uso:
        double f1(double t, double *y, int n) { return y[1]; }          // y' = v
        double f2(double t, double *y, int n) { return -y[0]; }         // v' = -y
        double (*AF[2])(double, double*, int) = {f1, f2};
        double y[2] = {1.0, 0.0}, dy[2];
        eval_sys(AF, 0.0, y, 2, dy);
        // Resultado: dy = [0, -1]
    */
    for (int i = 0; i < n; i++) dy[i] = AF[i](t, y, n);
}

// Método de Euler para sistemas de EDO's
// Descripción: Resuelve y_i' = AF[i](t, y) con 'n' ecuaciones y condiciones iniciales y0[0..n-1]. Devuelve una matriz (pasos+1) x n (una fila por instante);
// t_out contiene los tiempos (new[]). Liberar la matriz con del_mat(Y, pasos+1).
double** euler_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, int pasos, double *&t_out) {
    /*
    Ejemplo de uso:
        double f1(double t, double *y, int n) { return y[1]; }          // y' = v
        double f2(double t, double *y, int n) { return -y[0]; }         // v' = -y
        double (*AF[2])(double, double*, int) = {f1, f2};
        double y0[] = {1.0, 0.0}, *t;
        double **Y = euler_sys(AF, 0.0, y0, 2, 10.0, 1000, t);
    */
    if (pasos < 1 || n < 1) { print_error("euler_sys: pasos y n deben ser >= 1"); t_out = NULL; return NULL; }
    double h = (tf - t0) / pasos;
    double **Y = zeros_mat(pasos + 1, n);
    t_out = new double[pasos + 1];
    double *dy = new double[n];
    t_out[0] = t0;
    for (int j = 0; j < n; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        eval_sys(AF, t_out[i], Y[i], n, dy);
        for (int j = 0; j < n; j++) Y[i + 1][j] = Y[i][j] + h * dy[j];
        t_out[i + 1] = t0 + (i + 1) * h;
    }
    delete[] dy;
    return Y;
}

// Método de Euler mejorado para sistemas de EDO's
// Descripción: Predictor-corrector aplicado a todas las ecuaciones a la vez ('n_corr' correcciones; 1 = Heun). Mismos argumentos y salida que euler_sys.
double** euler_mejorado_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf,
                            int pasos, double *&t_out, int n_corr) {
    /*
    Ejemplo de uso:
        double **Y = euler_mejorado_sys(AF, 0.0, y0, 2, 10.0, 1000, t, 1);
    */
    if (pasos < 1 || n < 1 || n_corr < 1) { print_error("euler_mejorado_sys: pasos, n y n_corr deben ser >= 1"); t_out = NULL; return NULL; }
    double h = (tf - t0) / pasos;
    double **Y = zeros_mat(pasos + 1, n);
    t_out = new double[pasos + 1];
    double *d0 = new double[n], *d1 = new double[n], *yp = new double[n];
    t_out[0] = t0;
    for (int j = 0; j < n; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        eval_sys(AF, t_out[i], Y[i], n, d0);
        for (int j = 0; j < n; j++) yp[j] = Y[i][j] + h * d0[j];                       // prediccion
        for (int c = 0; c < n_corr; c++) {
            eval_sys(AF, t_out[i] + h, yp, n, d1);
            for (int j = 0; j < n; j++) yp[j] = Y[i][j] + h * (d0[j] + d1[j]) / 2.0;   // correccion
        }
        for (int j = 0; j < n; j++) Y[i + 1][j] = yp[j];
        t_out[i + 1] = t0 + (i + 1) * h;
    }
    delete[] d0; delete[] d1; delete[] yp;
    return Y;
}

// Método de Runge-Kutta de cuarto orden para sistemas de EDO's
// Descripción: Calcula en paralelo los vectores k1..k4 de todas las variables dependientes. Mismos argumentos y salida que euler_sys.
double** rk4_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, int pasos, double *&t_out) {
    /*
    Ejemplo de uso:
        double **Y = rk4_sys(AF, 0.0, y0, 2, 10.0, 1000, t);   // oscilador armonico
        print_vect(get_row_mat(Y, 1001, 2, 1000), 2, "y(10), v(10)");
    */
    if (pasos < 1 || n < 1) { print_error("rk4_sys: pasos y n deben ser >= 1"); t_out = NULL; return NULL; }
    double h = (tf - t0) / pasos;
    double **Y = zeros_mat(pasos + 1, n);
    t_out = new double[pasos + 1];
    double *k1 = new double[n], *k2 = new double[n], *k3 = new double[n], *k4 = new double[n], *tmp = new double[n];
    t_out[0] = t0;
    for (int j = 0; j < n; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        double t = t_out[i];
        double *y = Y[i];
        eval_sys(AF, t, y, n, k1);
        for (int j = 0; j < n; j++) tmp[j] = y[j] + 0.5 * h * k1[j];
        eval_sys(AF, t + 0.5 * h, tmp, n, k2);
        for (int j = 0; j < n; j++) tmp[j] = y[j] + 0.5 * h * k2[j];
        eval_sys(AF, t + 0.5 * h, tmp, n, k3);
        for (int j = 0; j < n; j++) tmp[j] = y[j] + h * k3[j];
        eval_sys(AF, t + h, tmp, n, k4);
        for (int j = 0; j < n; j++) Y[i + 1][j] = y[j] + h / 6.0 * (k1[j] + 2.0 * k2[j] + 2.0 * k3[j] + k4[j]);
        t_out[i + 1] = t0 + (i + 1) * h;
    }
    delete[] k1; delete[] k2; delete[] k3; delete[] k4; delete[] tmp;
    return Y;
}

// Paso de Runge-Kutta-Fehlberg para sistemas
// Descripción: Avanza un paso h desde (t,y) para las n ecuaciones. Devuelve en y5 (n valores, new[]) la solucion de 5o orden y en err el vector y5 - y4 (new[]).
void rkf45_paso_sys(double (*AF[])(double, double*, int), double t, double *y, int n, double h, double *&y5, double *&err) {
    /*
    Ejemplo de uso:
        double *y5, *err;
        rkf45_paso_sys(AF, 0.0, y0, 2, 0.1, y5, err);
    */
    double **k = zeros_mat(6, n);
    double *tmp = new double[n];
    y5 = new double[n];
    err = new double[n];
    eval_sys(AF, t, y, n, k[0]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * k[0][j] / 4.0;
    eval_sys(AF, t + h / 4.0, tmp, n, k[1]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (3.0 * k[0][j] / 32.0 + 9.0 * k[1][j] / 32.0);
    eval_sys(AF, t + 3.0 * h / 8.0, tmp, n, k[2]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (1932.0 * k[0][j] / 2197.0 - 7200.0 * k[1][j] / 2197.0 + 7296.0 * k[2][j] / 2197.0);
    eval_sys(AF, t + 12.0 * h / 13.0, tmp, n, k[3]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (439.0 * k[0][j] / 216.0 - 8.0 * k[1][j] + 3680.0 * k[2][j] / 513.0 - 845.0 * k[3][j] / 4104.0);
    eval_sys(AF, t + h, tmp, n, k[4]);
    for (int j = 0; j < n; j++) tmp[j] = y[j] + h * (-8.0 * k[0][j] / 27.0 + 2.0 * k[1][j] - 3544.0 * k[2][j] / 2565.0 + 1859.0 * k[3][j] / 4104.0 - 11.0 * k[4][j] / 40.0);
    eval_sys(AF, t + h / 2.0, tmp, n, k[5]);
    for (int j = 0; j < n; j++) {
        double y4 = y[j] + h * (25.0 * k[0][j] / 216.0 + 1408.0 * k[2][j] / 2565.0 + 2197.0 * k[3][j] / 4104.0 - k[4][j] / 5.0);
        y5[j] = y[j] + h * (16.0 * k[0][j] / 135.0 + 6656.0 * k[2][j] / 12825.0 + 28561.0 * k[3][j] / 56430.0 - 9.0 * k[4][j] / 50.0 + 2.0 * k[5][j] / 55.0);
        err[j] = y5[j] - y4;
    }
    del_mat(k, 6);
    delete[] tmp;
}

// Método de Runge-Kutta-Fehlberg adaptativo para sistemas
// Descripción: Como rkf45_edo pero para n ecuaciones; el error de un paso es el mayor |err_j|. Devuelve una matriz n_out x n (new[]) y t_out con los tiempos.
double** rkf45_sys(double (*AF[])(double, double*, int), double t0, double *y0, int n, double tf, double h0, double tol,
                   int max_pasos, double *&t_out, int &n_out) {
    /*
    Ejemplo de uso:
        double *t; int np;
        double **Y = rkf45_sys(AF, 0.0, y0, 2, 10.0, 0.1, 1e-8, 100000, t, np);
    */
    int cap = 64;
    double **Y = new double*[cap];
    t_out = new double[cap];
    Y[0] = copy_vect(y0, n);
    t_out[0] = t0;
    n_out = 1;
    double sentido = (tf >= t0) ? 1.0 : -1.0;
    double h = fabs(h0) * sentido;
    int pasos = 0;
    while ((tf - t_out[n_out - 1]) * sentido > 1e-14 * fabs(tf - t0) && pasos < max_pasos) {
        double t = t_out[n_out - 1];
        if ((t + h - tf) * sentido > 0.0) h = tf - t;
        double *y5, *err;
        rkf45_paso_sys(AF, t, Y[n_out - 1], n, h, y5, err);
        double e = 0.0;
        for (int j = 0; j < n; j++) if (fabs(err[j]) > e) e = fabs(err[j]);
        if (e <= tol || fabs(h) < 1e-14) {
            if (n_out >= cap) {
                int ncap = 2 * cap;
                double **tY = new double*[ncap], *tt = new double[ncap];
                for (int i = 0; i < n_out; i++) { tY[i] = Y[i]; tt[i] = t_out[i]; }
                delete[] Y; delete[] t_out;
                Y = tY; t_out = tt; cap = ncap;
            }
            Y[n_out] = y5;
            t_out[n_out] = t + h;
            n_out++;
        } else delete[] y5;
        delete[] err;
        double factor = (e == 0.0) ? 5.0 : 0.9 * pow(tol / e, 0.2);
        if (factor > 5.0) factor = 5.0;
        if (factor < 0.1) factor = 0.1;
        h *= factor;
        pasos++;
    }
    if (pasos >= max_pasos) print_warning("rkf45_sys alcanzo max_pasos antes de llegar a tf.");
    return Y;
}

// EDO de orden superior con Runge-Kutta de cuarto orden
// Descripción: Resuelve y^(m) = f(x, y, y', ..., y^(m-1)) con m = 'orden', convirtiendola en un sistema de m ecuaciones de primer orden (y1 = y, y2 = y', ...).
// f(x, y, m) recibe el vector y = {y, y', ..., y^(m-1)} y devuelve y^(m). y0[0..m-1] son las condiciones iniciales.
// Devuelve una matriz (pasos+1) x m: columna 0 = y, columna 1 = y', etc.; x_out contiene las abscisas.
double** rk4_orden_n(double (*f)(double, double*, int), double x0, double *y0, int orden, double xf, int pasos, double *&x_out) {
    /*
    Ejemplo de uso:
        // Circuito RLC: V'' = -(R/L)*V' - V/(L*C),  V(0) = 10, V'(0) = 0
        double rlc(double t, double *y, int m) { return -(1000.0/0.5)*y[1] - y[0]/(0.5*2e-6); }
        double y0[] = {10.0, 0.0}, *t;
        double **V = rk4_orden_n(rlc, 0.0, y0, 2, 0.02, 200, t);
    */
    if (pasos < 1 || orden < 1) { print_error("rk4_orden_n: pasos y orden deben ser >= 1"); x_out = NULL; return NULL; }
    int m = orden;
    double h = (xf - x0) / pasos;
    double **Y = zeros_mat(pasos + 1, m);
    x_out = new double[pasos + 1];
    double *k1 = new double[m], *k2 = new double[m], *k3 = new double[m], *k4 = new double[m], *tmp = new double[m];
    x_out[0] = x0;
    for (int j = 0; j < m; j++) Y[0][j] = y0[j];
    for (int i = 0; i < pasos; i++) {
        double x = x_out[i];
        double *y = Y[i];
        for (int j = 0; j < m - 1; j++) k1[j] = y[j + 1];
        k1[m - 1] = f(x, y, m);
        for (int j = 0; j < m; j++) tmp[j] = y[j] + 0.5 * h * k1[j];
        for (int j = 0; j < m - 1; j++) k2[j] = tmp[j + 1];
        k2[m - 1] = f(x + 0.5 * h, tmp, m);
        for (int j = 0; j < m; j++) tmp[j] = y[j] + 0.5 * h * k2[j];
        for (int j = 0; j < m - 1; j++) k3[j] = tmp[j + 1];
        k3[m - 1] = f(x + 0.5 * h, tmp, m);
        for (int j = 0; j < m; j++) tmp[j] = y[j] + h * k3[j];
        for (int j = 0; j < m - 1; j++) k4[j] = tmp[j + 1];
        k4[m - 1] = f(x + h, tmp, m);
        for (int j = 0; j < m; j++) Y[i + 1][j] = y[j] + h / 6.0 * (k1[j] + 2.0 * k2[j] + 2.0 * k3[j] + k4[j]);
        x_out[i + 1] = x0 + (i + 1) * h;
    }
    delete[] k1; delete[] k2; delete[] k3; delete[] k4; delete[] tmp;
    return Y;
}

// ----------------------------------------------------------------------------
// V.3 EDO's CON CONDICIONES DE FRONTERA (BVP): DISPARO Y DIFERENCIAS FINITAS
// ----------------------------------------------------------------------------

// Helper: resuelve el IVP y'' = f(t,y,y'), y(a) = alfa, y'(a) = p con RK4 y devuelve y(b).
// Si ys != NULL guarda la solucion en ys[0..n] (n pasos).
// Descripción: Funcion auxiliar del metodo del disparo: resuelve el problema de valores iniciales y'' = f(t,y,y'), y(a) = alfa, y'(a) = p con Runge-Kutta 4 (n pasos) y devuelve y(b).
// Si ys != NULL guarda tambien la solucion en ys[0..n].
double ivp_rk4_2o(double (*f)(double, double, double), double a, double b, double alfa, double p, int n, double *ys) {
    /*
    Ejemplo de uso:
        double f(double t, double y, double yp) { return -y; }          // y'' = -y
        double yb = ivp_rk4_2o(f, 0.0, 1.5707963267949, 0.0, 1.0, 100, NULL);
        // Resultado: yb = 1   (la solucion es y = sin(t), asi que y(pi/2) = 1)
    */
    double h = (b - a) / n, t = a, y = alfa, v = p;
    if (ys != NULL) ys[0] = y;
    for (int i = 0; i < n; i++) {
        double k1y = v,                 k1v = f(t, y, v);
        double k2y = v + 0.5*h*k1v,     k2v = f(t + 0.5*h, y + 0.5*h*k1y, v + 0.5*h*k1v);
        double k3y = v + 0.5*h*k2v,     k3v = f(t + 0.5*h, y + 0.5*h*k2y, v + 0.5*h*k2v);
        double k4y = v + h*k3v,         k4v = f(t + h, y + h*k3y, v + h*k3v);
        y += h / 6.0 * (k1y + 2.0*k2y + 2.0*k3y + k4y);
        v += h / 6.0 * (k1v + 2.0*k2v + 2.0*k3v + k4v);
        t = a + (i + 1) * h;
        if (ys != NULL) ys[i + 1] = y;
    }
    return y;
}

// Método del disparo (con secante)
// Descripción: Resuelve el BVP y'' = f(t,y,y'), y(a) = alfa, y(b) = beta. Busca la pendiente inicial p* tal que E(p) = y_p(b) - beta = 0 con el metodo de la secante,
// resolviendo cada IVP con RK4 y 'n' pasos. Arranque: p0 = (beta-alfa)/(b-a); p1 = p0/2 si p0*E0 > 0, 2*p0 si p0*E0 < 0 (si p0 = 0: p1 = -1 si E0 > 0, +1 si E0 < 0).
// Devuelve y[0..n] (new[]), x_out con las abscisas y p_out con la pendiente final. Si el BVP es lineal converge en una sola iteracion de la secante.
double* disparo_edo(double (*f)(double, double, double), double a, double b, double alfa, double beta,
                    int n, double tol, int max_iter, double *&x_out, double &p_out) {
    /*
    Ejemplo de uso:
        // y'' = -(2/t)y' + (2/t^2)y + sin(ln t)/t^2, y(1) = 1, y(2) = 2   (p* = 0.917621...)
        double f(double t, double y, double yp) { return -2.0/t*yp + 2.0/(t*t)*y + sin(log(t))/(t*t); }
        double *x, p;
        double *y = disparo_edo(f, 1.0, 2.0, 1.0, 2.0, 100, 1e-10, 50, x, p);
    */
    if (n < 1) { print_error_int("disparo_edo: n debe ser >= 1", n); x_out = NULL; return NULL; }
    double p0 = (beta - alfa) / (b - a);
    double E0 = ivp_rk4_2o(f, a, b, alfa, p0, n, NULL) - beta;
    double p1;
    if (p0 == 0.0)        p1 = (E0 > 0.0) ? -1.0 : 1.0;
    else if (p0 * E0 > 0.0) p1 = p0 / 2.0;
    else                  p1 = 2.0 * p0;
    double E1 = ivp_rk4_2o(f, a, b, alfa, p1, n, NULL) - beta;
    double p2 = p1, E2 = E1;
    if (fabs(E0) < tol) { p2 = p0; E2 = E0; }
    else {
        int it = 0;
        while (fabs(E1) >= tol && it < max_iter) {
            if (E1 == E0) { print_warning("disparo_edo: E(p0) = E(p1), la secante no puede continuar."); break; }
            p2 = p1 - E1 * (p1 - p0) / (E1 - E0);
            E2 = ivp_rk4_2o(f, a, b, alfa, p2, n, NULL) - beta;
            p0 = p1; E0 = E1;
            p1 = p2; E1 = E2;
            it++;
        }
        if (fabs(E1) >= tol && it >= max_iter) print_warning("disparo_edo alcanzo max_iter sin converger plenamente.");
        p2 = p1;
    }
    p_out = p2;
    double *y = new double[n + 1];
    x_out = new double[n + 1];
    ivp_rk4_2o(f, a, b, alfa, p2, n, y);
    double h = (b - a) / n;
    for (int i = 0; i <= n; i++) x_out[i] = a + i * h;
    return y;
}

// Método de las diferencias finitas para un BVP lineal
// Descripción: Resuelve y'' = p(t)*y' + q(t)*y + r(t), y(a) = alfa, y(b) = beta con 'N' puntos interiores (h = (b-a)/(N+1)). Sustituye las derivadas por diferencias
// centrales y resuelve el sistema tridiagonal resultante con tridiag_vect_solve. Devuelve w[0..N+1] (incluye los dos extremos) y x_out con los puntos.
double* dif_finitas_bvp(double (*p)(double), double (*q)(double), double (*r)(double), double a, double b,
                        double alfa, double beta, int N, double *&x_out) {
    /*
    Ejemplo de uso:
        double p(double t) { return -2.0/t; }
        double q(double t) { return 2.0/(t*t); }
        double r(double t) { return sin(log(t))/(t*t); }
        double *x, *w = dif_finitas_bvp(p, q, r, 1.0, 2.0, 1.0, 2.0, 99, x);
    */
    if (N < 1) { print_error_int("dif_finitas_bvp: N debe ser >= 1", N); x_out = NULL; return NULL; }
    double h = (b - a) / (N + 1);
    double *ai = new double[N], *bi = new double[N], *ci = new double[N], *fi = new double[N];
    x_out = new double[N + 2];
    for (int i = 0; i <= N + 1; i++) x_out[i] = a + i * h;
    for (int i = 1; i <= N; i++) {
        double t = x_out[i];
        ai[i - 1] = -(1.0 / (h * h) + p(t) / (2.0 * h));
        bi[i - 1] = 2.0 / (h * h) + q(t);
        ci[i - 1] = -(1.0 / (h * h) - p(t) / (2.0 * h));
        fi[i - 1] = -r(t);
    }
    fi[0]     -= ai[0] * alfa;          // a_1 y c_N pasan al termino independiente
    fi[N - 1] -= ci[N - 1] * beta;
    double *w_int = tridiag_vect_solve(ai, bi, ci, fi, N);
    double *w = new double[N + 2];
    w[0] = alfa; w[N + 1] = beta;
    for (int i = 0; i < N; i++) w[i + 1] = w_int[i];
    delete[] ai; delete[] bi; delete[] ci; delete[] fi; delete[] w_int;
    return w;
}

// ============================================================================
// BLOQUE V (cont.): ECUACIONES DIFERENCIALES EN DERIVADAS PARCIALES (EDP's)
// ============================================================================

// ----------------------------------------------------------------------------
// EDP PARABOLICA: ECUACION DEL CALOR ADIMENSIONAL  d(theta)/d(tau) = d2(theta)/dX2,  0 <= X <= 1
// ----------------------------------------------------------------------------

// Ecuación del calor: forma explícita (diferencias progresivas)
// Descripción: w[i][n+1] = lambda*w[i-1][n] + (1-2*lambda)*w[i][n] + lambda*w[i+1][n], con lambda = dtau/dX^2 y dX = 1/M. f0(X) es la condicion inicial y g0(tau), g1(tau)
// las condiciones de contorno en X = 0 y X = 1. Estable solo si lambda <= 1/2 (aviso si no se cumple). Devuelve una matriz (N+1) x (M+1), una fila por instante tau_n;
// N_out = numero de pasos de tiempo hasta tau_max. Liberar con del_mat(W, N_out+1).
double** calor_explicito(double (*f0)(double), double (*g0)(double), double (*g1)(double),
                         int M, double dtau, double tau_max, int &N_out) {
    /*
    Ejemplo de uso:
        double f0(double X) { return 0.0; }   double g(double tau) { return 1.0; }
        int N;
        double **W = calor_explicito(f0, g, g, 10, 0.004, 0.2, N);   // lambda = 0.4
    */
    if (M < 2 || dtau <= 0.0 || tau_max <= 0.0) { print_error("calor_explicito: M >= 2, dtau > 0 y tau_max > 0"); N_out = 0; return NULL; }
    double dX = 1.0 / M, lambda = dtau / (dX * dX);
    if (lambda > 0.5) print_warning("calor_explicito: lambda > 1/2, el metodo explicito es inestable (criterio de Von Neumann).");
    int N = (int)ceil(tau_max / dtau - 1e-12);
    N_out = N;
    double **W = zeros_mat(N + 1, M + 1);
    for (int i = 0; i <= M; i++) W[0][i] = f0(i * dX);
    for (int n = 0; n < N; n++) {
        double tau = (n + 1) * dtau;
        W[n + 1][0] = g0(tau);
        W[n + 1][M] = g1(tau);
        for (int i = 1; i < M; i++)
            W[n + 1][i] = lambda * W[n][i - 1] + (1.0 - 2.0 * lambda) * W[n][i] + lambda * W[n][i + 1];
    }
    return W;
}

// Ecuación del calor: forma implícita (diferencias regresivas)
// Descripción: -lambda*w[i-1][n+1] + (1+2*lambda)*w[i][n+1] - lambda*w[i+1][n+1] = w[i][n]. En cada instante se resuelve un sistema tridiagonal de M-1 ecuaciones con
// tridiag_vect_solve. Es estable para cualquier dtau y dX. Mismos argumentos y salida que calor_explicito.
double** calor_implicito(double (*f0)(double), double (*g0)(double), double (*g1)(double),
                         int M, double dtau, double tau_max, int &N_out) {
    /*
    Ejemplo de uso:
        int N;
        double **W = calor_implicito(f0, g, g, 10, 0.02, 0.2, N);   // lambda = 2, valido
    */
    if (M < 2 || dtau <= 0.0 || tau_max <= 0.0) { print_error("calor_implicito: M >= 2, dtau > 0 y tau_max > 0"); N_out = 0; return NULL; }
    double dX = 1.0 / M, lambda = dtau / (dX * dX);
    int N = (int)ceil(tau_max / dtau - 1e-12);
    N_out = N;
    double **W = zeros_mat(N + 1, M + 1);
    for (int i = 0; i <= M; i++) W[0][i] = f0(i * dX);
    int m = M - 1;                                       // puntos interiores
    double *a = new double[m], *b = new double[m], *c = new double[m], *d = new double[m];
    for (int i = 0; i < m; i++) { a[i] = -lambda; b[i] = 1.0 + 2.0 * lambda; c[i] = -lambda; }
    for (int n = 0; n < N; n++) {
        double tau = (n + 1) * dtau;
        W[n + 1][0] = g0(tau);
        W[n + 1][M] = g1(tau);
        for (int i = 0; i < m; i++) d[i] = W[n][i + 1];
        d[0]     += lambda * W[n + 1][0];
        d[m - 1] += lambda * W[n + 1][M];
        double *w = tridiag_vect_solve(a, b, c, d, m);
        for (int i = 0; i < m; i++) W[n + 1][i + 1] = w[i];
        delete[] w;
    }
    delete[] a; delete[] b; delete[] c; delete[] d;
    return W;
}

// ----------------------------------------------------------------------------
// EDP ELIPTICA: ECUACION DE LAPLACE EN UNA PLACA CUADRADA
// ----------------------------------------------------------------------------

// Ecuación de Laplace 2D: Gauss-Seidel con sobrerrelajación
// Descripción: T es una matriz (n+1) x (n+1) con la frontera ya fijada y un valor inicial en el interior. Itera T_new = T_old + omega/4*(T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1] - 4*T_old)
// hasta que sum|T_new - T_old| < tol. omega = 1 es Gauss-Seidel puro; 1 < omega < 2 acelera la convergencia (omega ~ 1.94 para n = 100). Devuelve el numero de iteraciones.
int laplace_gs(double **T, int n, double tol, int max_iter, double omega) {
    /*
    Ejemplo de uso:
        int it = laplace_gs(T, 20, 1e-7, 50000, 1.5);   // T se modifica con la solucion
    */
    int iter = 0;
    double diferencia = tol + 1.0;
    while (diferencia > tol && iter < max_iter) {
        diferencia = 0.0;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                double viejo = T[i][j];
                double nuevo = viejo + omega / 4.0 * (T[i + 1][j] + T[i - 1][j] + T[i][j + 1] + T[i][j - 1] - 4.0 * viejo);
                T[i][j] = nuevo;
                diferencia += fabs(nuevo - viejo);
            }
        }
        iter++;
    }
    if (iter >= max_iter && diferencia > tol) print_warning("laplace_gs alcanzo max_iter sin converger plenamente.");
    return iter;
}

// Placa cuadrada con temperaturas constantes en los bordes
// Descripción: Crea la matriz (n+1) x (n+1) con T_sup (fila 0), T_inf (fila n), T_izq (columna 0) y T_der (columna n) constantes y el interior a 0, y resuelve Laplace con laplace_gs.
// 'iter_out' devuelve las iteraciones. Liberar con del_mat(T, n+1).
double** laplace_placa(int n, double T_sup, double T_inf, double T_izq, double T_der,
                       double tol, int max_iter, double omega, int &iter_out) {
    /*
    Ejemplo de uso:
        int it;
        double **T = laplace_placa(20, 0.0, 0.0, 100.0, 0.0, 1e-7, 50000, 1.5, it);   // un borde a 100 y los otros a 0
    */
    double **T = zeros_mat(n + 1, n + 1);
    for (int k = 0; k <= n; k++) {
        T[0][k] = T_sup; T[n][k] = T_inf;
        T[k][0] = T_izq; T[k][n] = T_der;
    }
    iter_out = laplace_gs(T, n, tol, max_iter, omega);
    return T;
}
