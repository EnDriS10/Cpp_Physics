// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.2
// Sistemas sobredeterminados y regresiones
// ============================================================================
// Minimos cuadrados (ecuaciones normales) y regresiones lineal, polinomica, exponencial, logaritmica, potencial y sinusoidal.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "minimos_cuadrados.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (7): ols_reg, poly_reg, lin_reg, exp_reg, regresion_logaritmica, regresion_potencial, regresion_sinusoidal
// Dependencias copiadas (17): MC_NAN, print_error, print_warning, print_error_dim, sum_elems, mean_vect, gen_mat, del_mat, prod_mat, transpose_mat, zeros_mat, prod_mat_vect, lu_forma1, lu_forma2, lu_forma2_sol, det_lu, inv_lu
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_MINIMOS_CUADRADOS_CPP
#define MATCLUB_MINIMOS_CUADRADOS_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

// (constante global)
#ifndef MC_FN_MC_NAN
#define MC_FN_MC_NAN
const double MC_NAN = sqrt(-1.0);
#endif // MC_FN_MC_NAN

// (copiada de: mensajes)
#ifndef MC_FN_print_error
#define MC_FN_print_error
void print_error(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB ERROR]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_error

// (copiada de: mensajes)
#ifndef MC_FN_print_warning
#define MC_FN_print_warning
// Aviso: algo no fue perfecto pero el programa puede continuar
void print_warning(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB AVISO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_warning

// (copiada de: mensajes)
#ifndef MC_FN_print_error_dim
#define MC_FN_print_error_dim
// Error de dimensiones: "mensaje (faxca) * (fbxcb)"
void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb) {
    cout << "[MATCLUB ERROR]: " << mensaje
         << " (" << fa << "x" << ca << ") * (" << fb << "x" << cb << ")" << endl;
}
#endif // MC_FN_print_error_dim

// (copiada de: vectores)
#ifndef MC_FN_sum_elems
#define MC_FN_sum_elems
// Suma total de cada elemento del vector.
double sum_elems(double *a, int n) { 
    double suma = 0; 
    for ( int i = 0; i<n ; i++){
        suma = suma + a[i];
    }   
    return suma; 
}
#endif // MC_FN_sum_elems

// (copiada de: vectores)
#ifndef MC_FN_mean_vect
#define MC_FN_mean_vect
// Media del vect
double mean_vect(double *a, int n) { 
    double mean;
    mean = sum_elems(a, n) / n;   
    return mean; 
}
#endif // MC_FN_mean_vect

// (copiada de: matrices)
#ifndef MC_FN_gen_mat
#define MC_FN_gen_mat
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
#endif // MC_FN_gen_mat

// (copiada de: matrices)
#ifndef MC_FN_del_mat
#define MC_FN_del_mat
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
#endif // MC_FN_del_mat

// (copiada de: matrices)
#ifndef MC_FN_prod_mat
#define MC_FN_prod_mat
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
#endif // MC_FN_prod_mat

// (copiada de: matrices)
#ifndef MC_FN_transpose_mat
#define MC_FN_transpose_mat
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
#endif // MC_FN_transpose_mat

// (copiada de: matrices)
#ifndef MC_FN_zeros_mat
#define MC_FN_zeros_mat
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
#endif // MC_FN_zeros_mat

// (copiada de: matrices)
#ifndef MC_FN_prod_mat_vect
#define MC_FN_prod_mat_vect
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
#endif // MC_FN_prod_mat_vect

// (copiada de: factorizacion_lu)
#ifndef MC_FN_lu_forma1
#define MC_FN_lu_forma1
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
#endif // MC_FN_lu_forma1

// (copiada de: factorizacion_lu)
#ifndef MC_FN_lu_forma2
#define MC_FN_lu_forma2
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
#endif // MC_FN_lu_forma2

// (copiada de: factorizacion_lu)
#ifndef MC_FN_lu_forma2_sol
#define MC_FN_lu_forma2_sol
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
#endif // MC_FN_lu_forma2_sol

// (copiada de: determinantes_inversas)
#ifndef MC_FN_det_lu
#define MC_FN_det_lu
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
#endif // MC_FN_det_lu

// (copiada de: determinantes_inversas)
#ifndef MC_FN_inv_lu
#define MC_FN_inv_lu
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
#endif // MC_FN_inv_lu

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Sistemas sobredeterminados y regresiones
// ----------------------------------------------------------------------------

#ifndef MC_FN_ols_reg
#define MC_FN_ols_reg
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
#endif // MC_FN_ols_reg

#ifndef MC_FN_poly_reg
#define MC_FN_poly_reg
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
#endif // MC_FN_poly_reg

#ifndef MC_FN_lin_reg
#define MC_FN_lin_reg
// 2. Regresión Lineal: y = a0 + a1*x 
// (Es simplemente un caso particular de la regresion polinomica de grado 1)
double* lin_reg(double *x, double *y, int m_datos, double *&errores, double &R2) {
    return poly_reg(x, y, m_datos, 1, errores, R2);
}
#endif // MC_FN_lin_reg

#ifndef MC_FN_exp_reg
#define MC_FN_exp_reg
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
#endif // MC_FN_exp_reg

#ifndef MC_FN_regresion_logaritmica
#define MC_FN_regresion_logaritmica
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
#endif // MC_FN_regresion_logaritmica

#ifndef MC_FN_regresion_potencial
#define MC_FN_regresion_potencial
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
#endif // MC_FN_regresion_potencial

#ifndef MC_FN_regresion_sinusoidal
#define MC_FN_regresion_sinusoidal
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
#endif // MC_FN_regresion_sinusoidal

#endif // MATCLUB_MINIMOS_CUADRADOS_CPP
