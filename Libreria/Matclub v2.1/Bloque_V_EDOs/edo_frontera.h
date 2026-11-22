// ============================================================================
// MATCLUB-CPP  |  BLOQUE V: EDOs  |  V.3
// EDO's con condiciones de frontera
// ============================================================================
// Metodo del disparo (con secante) y metodo de las diferencias finitas para problemas de valores de frontera.
//
// Funciones (3): ivp_rk4_2o, disparo_edo, dif_finitas_bvp
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_EDO_FRONTERA_H
#define MATCLUB_EDO_FRONTERA_H

// Helper: resuelve el IVP y'' = f(t,y,y'), y(a) = alfa, y'(a) = p con RK4 y devuelve y(b).
// Si ys != NULL guarda la solucion en ys[0..n] (n pasos).
double ivp_rk4_2o(double (*f)(double, double, double), double a, double b, double alfa, double p, int n, double *ys);

// Método del disparo (con secante)
// Descripción: Resuelve el BVP y'' = f(t,y,y'), y(a) = alfa, y(b) = beta. Busca la pendiente inicial p* tal que E(p) = y_p(b) - beta = 0 con el metodo de la secante,
// resolviendo cada IVP con RK4 y 'n' pasos. Arranque: p0 = (beta-alfa)/(b-a); p1 = p0/2 si p0*E0 > 0, 2*p0 si p0*E0 < 0 (si p0 = 0: p1 = -1 si E0 > 0, +1 si E0 < 0).
// Devuelve y[0..n] (new[]), x_out con las abscisas y p_out con la pendiente final. Si el BVP es lineal converge en una sola iteracion de la secante.
double* disparo_edo(double (*f)(double, double, double), double a, double b, double alfa, double beta, int n, double tol, int max_iter, double *&x_out, double &p_out);

// Método de las diferencias finitas para un BVP lineal
// Descripción: Resuelve y'' = p(t)*y' + q(t)*y + r(t), y(a) = alfa, y(b) = beta con 'N' puntos interiores (h = (b-a)/(N+1)). Sustituye las derivadas por diferencias
// centrales y resuelve el sistema tridiagonal resultante con tridiag_vect_solve. Devuelve w[0..N+1] (incluye los dos extremos) y x_out con los puntos.
double* dif_finitas_bvp(double (*p)(double), double (*q)(double), double (*r)(double), double a, double b, double alfa, double beta, int N, double *&x_out);

#endif // MATCLUB_EDO_FRONTERA_H
