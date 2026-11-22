// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Matrices (arrays dinamicos 2D)
// ============================================================================
// Creacion, copia, operaciones basicas, producto, traspuesta, submatrices, filas/columnas, diagonales, busqueda, aleatorias, entrada y salida.
//
// Funciones (43): gen_mat, del_mat, prod_mat, input_mat, print_mat, coppy_mat, transpose_mat, zeros_mat, ones_mat, eye_mat, prod_esc_mat, trace_mat, get_row_mat, get_col_mat, suma_mat, resta_mat, prodeach_mat, sub_mat, horzcat_mat, vertcat_mat, flatten_mat, funeach_mat, apply_scalar_vect, apply_scalar_mat, remove_row_col_mat, is_symmetric_mat, swap_rows_mat, swap_cols_mat, find_val_mat, find_gt_mat, sum_all_mat, prod_all_mat, max_mat, max_abs_mat, min_mat, rand_mat, randi_mat, randn_mat, clamp_mat, reshape_mat, diag_mat, get_diag_mat, prod_mat_vect
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

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

void print_mat(double **M, int f, int c, const char* nombre) {
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

