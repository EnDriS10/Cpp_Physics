// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.1
// El problema de los autovalores
// ============================================================================
// Polinomio caracteristico, cociente de Rayleigh, residuos, similaridad y metodo de la potencia (directa e inversa).
//
// Funciones (7): poly_caract_mat, rayleigh_mat, resid_eig, resid_eig_mat, similar_mat, potencia_eig, potencia_inv_eig
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_AUTOVALORES_H
#define MATCLUB_AUTOVALORES_H

// Polinomio característico de una matriz (Algoritmo de Faddeev-LeVerrier)
// Descripción: Devuelve los n+1 coeficientes (potencias decrecientes, listo para 'polyval') del polinomio monico det(lambda*I - A).
// Nota: el p(lambda) = det(A - lambda*I) de la teoria vale (-1)^n veces este polinomio; sus raices (los autovalores) son las mismas.
double* poly_caract_mat(double **A, int n);

// Cociente de Rayleigh
// Descripción: Calcula x^T*A*x / x^T*x. Si x es un autovector devuelve su autovalor; si no, es la mejor estimacion del autovalor.
double rayleigh_mat(double **A, int n, double *x);

// Residuo de un par autovalor-autovector
// Descripción: Devuelve la norma ||A*x - lambda*x||. Vale ~0 si (lambda, x) es un par autovalor-autovector correcto.
double resid_eig(double **A, int n, double lambda, double *x);

// Residuo máximo de todos los pares autovalor-autovector
// Descripción: Comprueba A*u_k = L[k]*u_k para cada columna u_k de U y devuelve el mayor residuo.
double resid_eig_mat(double **A, int n, double *L, double **U);

// Transformación de similaridad V^-1 * A * V
// Descripción: Si las columnas de V son autovectores de A, el resultado es la matriz diagonal de autovalores diag(l1,...,ln).
double** similar_mat(double **A, double **V, int n);

// Autovalor dominante: Método de la potencia
// Descripción: Itera x <- A*x/||A*x|| y estima el autovalor de mayor valor absoluto con el cociente de Rayleigh.
// Devuelve el autovalor y, por referencia, el autovector normalizado (v_out, reservado con new[]).
double potencia_eig(double **A, int n, double *&v_out, double tol, int max_iter);

// Autovalor más cercano a un valor dado: Método de la potencia inversa con desplazamiento
// Descripción: Itera (A - mu*I)*y = x, de forma que converge al autovalor de A mas cercano a 'mu'. Con mu = 0 da el de menor valor absoluto.
// Devuelve el autovalor y, por referencia, su autovector normalizado (v_out, reservado con new[]).
double potencia_inv_eig(double **A, int n, double mu, double *&v_out, double tol, int max_iter);

#endif // MATCLUB_AUTOVALORES_H
