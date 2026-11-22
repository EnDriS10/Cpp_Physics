// ============================================================================
// MATCLUB-CPP  |  BLOQUE III: DIAGONALIZACION  |  III.1
// El problema de los autovalores
// ============================================================================
// Polinomio caracteristico, cociente de Rayleigh, residuos, similaridad y metodo de la potencia (directa e inversa).
//
// Funciones (7): poly_caract_mat, rayleigh_mat, resid_eig, resid_eig_mat, similar_mat, potencia_eig, potencia_inv_eig
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

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

