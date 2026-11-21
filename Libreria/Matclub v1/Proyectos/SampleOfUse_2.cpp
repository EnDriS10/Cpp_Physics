#include "matclub.h"
using namespace std;

double f_integrando(double x) { return x * sin(x); }
double parabola(double x)     { return (x - 2.0) * (x - 2.0) + 1.0; }

int main() {
    print_line(50);
    cout << "MATCLUB-CPP: ejemplo de uso" << endl;
    print_line(50);

    // 1. VECTORES: 8 puntos entre 0 y 3, y sus senos
    int n = 8;
    double *x = linspace(0.0, 3.0, n);
    double *y = sin_vect(x, n);
    print_vect(y, n, "sin(x)");

    // 2. INTERPOLACION: precalcular una vez, evaluar donde quieras
    double *M = spline_coef(x, y, n);       // spline cubica natural
    double *w = lagrange_coef(x, n);        // pesos de Lagrange
    double xi = 1.234;
    cout << "sin(1.234) real    = " << sin(xi) << endl;
    cout << "spline_eval        = " << spline_eval(x, y, M, n, xi) << endl;
    cout << "lagrange_val       = " << lagrange_val(x, y, w, n, xi) << endl;

    // 3. SISTEMA LINEAL  A*s = b
    double **A = zeros_mat(3, 3);
    A[0][0] = 2;  A[0][1] = 1;  A[0][2] = -1;
    A[1][0] = -3; A[1][1] = -1; A[1][2] = 2;
    A[2][0] = -2; A[2][1] = 1;  A[2][2] = 2;
    double b[3] = {8, -11, -3};
    double *s = gauss_solve(A, b, 3);
    print_mat(A, 3, 3, "A");
    print_vect(s, 3, "solucion");               // esperado: 2, 3, -1

    // 4. REGRESION LINEAL  y = a0 + a1*x
    double xd[5] = {1, 2, 3, 4, 5};
    double yd[5] = {2.1, 3.9, 6.2, 7.8, 10.1};
    double *err, R2;
    double *p = lin_reg(xd, yd, 5, err, R2);
    cout << "y = " << p[0] << " + " << p[1] << " x   (R2 = " << R2 << ")" << endl;

    // 5. NUMERICO: integral de x*sin(x) en [0, pi] y minimo de una parabola
    cout << "Integral (Simpson) = " << integral_def_func(f_integrando, 0.0, PI(15), 1000)
         << "   (exacto: pi = " << PI(6) << ")" << endl;
    cout << "Minimo en x = " << seccion_aurea(parabola, -10.0, 10.0, 1e-8)
         << "   (phi = " << PHI(6) << ")" << endl;

    // 6. MENSAJES de la libreria
    print_info("calculo terminado");
    print_error("esto es un error de prueba", "detalle opcional");

    // 7. LIBERAR MEMORIA
    del_vect(x); del_vect(y); del_vect(M); del_vect(w);
    del_mat(A, 3); del_vect(s); del_vect(p); del_vect(err);
    return 0;
}
