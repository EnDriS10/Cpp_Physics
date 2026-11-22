// ============================================================================
// MATCLUB-CPP: ejemplo de uso (un ejemplo por bloque)
// Compilar desde la carpeta MATCLUB:   make ejemplo     (o ver README.md)
// ============================================================================

#include "../matclub.h"
using namespace std;

double f_cuad(double x)  { return x * x - 2.0; }             // raiz: sqrt(2)
double f_sin(double x)   { return sin(x); }
double f_edo(double x, double y) { return -2.0 * x - y; }    // y' = -2x - y, y(0) = -1

int main() {
    print_line(60);
    cout << "MATCLUB-CPP: ejemplo de uso" << endl;
    print_line(60);

    // ---- BLOQUE I: vectores y matrices ----
    int n = 7;
    double *x = linspace(0.0, 3.0, n);
    double *y = sin_vect(x, n);
    print_vect(y, n, "sin(x)");

    // ---- BLOQUE II: ceros de una funcion y sistema lineal ----
    cout << "raiz de x^2-2 (biseccion) = " << biseccion(f_cuad, 0.0, 2.0, 1e-10, 1e-10, 100) << endl;
    double **A = zeros_mat(3, 3);
    A[0][0] = 2;  A[0][1] = 1;  A[0][2] = -1;
    A[1][0] = -3; A[1][1] = -1; A[1][2] = 2;
    A[2][0] = -2; A[2][1] = 1;  A[2][2] = 2;
    double b[3] = {8, -11, -3};
    double *s = gauss_solve(A, b, 3);
    print_vect(s, 3, "solucion del sistema (2, 3, -1)");

    // ---- BLOQUE III: autovalores de una matriz simetrica (Jacobi) ----
    double **S = zeros_mat(2, 2);
    S[0][0] = 2; S[0][1] = 1; S[1][0] = 1; S[1][1] = 2;
    double *L; int rot;
    double **U = jacobi_eig(S, 2, L, 1e-12, 100, rot);
    sort_eig(L, U, 2);
    print_vect(L, 2, "autovalores (3, 1)");

    // ---- BLOQUE IV: integral y derivada ----
    int N;
    cout << "integral de sin en [0,pi] (Romberg) = " << romberg_int(f_sin, 0.0, PI(15), 1e-10, 12, N) << endl;
    cout << "d/dx sin(x) en x=1 (Richardson)     = " << deriv_richardson(f_sin, 1.0, 0.1, 4, 1)
         << "   (cos(1) = " << cos(1.0) << ")" << endl;

    // ---- BLOQUE V: EDO con valores iniciales (Runge-Kutta 4) ----
    double *t;
    double *yy = rk4_edo(f_edo, 0.0, -1.0, 0.5, 5, t);
    cout << "y(0.5) de y' = -2x - y (RK4) = " << yy[5] << "   (exacto: " << -3*exp(-0.5) - 1 + 2 << ")" << endl;

    // ---- COMPLEMENTOS: interpolacion ----
    cout << "spline en 1.234 = " << spline_interp(x, y, n, 1.234) << "   (sin(1.234) = " << sin(1.234) << ")" << endl;

    print_info("ejemplo terminado");

    // ---- liberar memoria ----
    del_vect(x); del_vect(y); del_vect(s); del_vect(L); del_vect(t); del_vect(yy);
    del_mat(A, 3); del_mat(S, 2); del_mat(U, 2);
    return 0;
}
