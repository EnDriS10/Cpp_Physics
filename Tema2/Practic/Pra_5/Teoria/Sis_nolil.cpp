#include <iostream>
#include <iomanip>
#include <cmath>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\Bloque_II_Sistemas_de_Ecuaciones\sistemas_no_lineales.cpp"

using namespace std;

// 1. Definir las ecuaciones del sistema IGUALADAS A CERO: f_i(x) = 0
// En C++, x[0] corresponde a 'x' y x[1] corresponde a 'y'
double f1(double *x, int n) {
    return x[0]*x[0] + x[1]*x[1] - 5.0;
}

double f2(double *x, int n) {
    return x[0]*x[1] - 2.0;
}

int main() {
    int n = 2;              // Número de ecuaciones / incógnitas
    int num_puntos = 4;     // Cantidad de puntos iniciales (semillas) a probar
    double tol = 1e-8;      // Tolerancia de convergencia
    int max_iter = 50;      // Máximo de iteraciones por semilla

    // 2. Agrupar las funciones en un array de punteros a función
    double (*Sistema[2])(double*, int) = {f1, f2};

    // 3. Crear y rellenar la matriz de semillas iniciales (num_puntos x n)
    double **semillas = NULL;
    semillas = gen_mat(semillas, num_puntos, n);

    // Semilla 0 -> converge a (2, 1)
    semillas[0][0] =  2.5;  semillas[0][1] =  0.5;
    // Semilla 1 -> converge a (1, 2)
    semillas[1][0] =  0.5;  semillas[1][1] =  2.5;
    // Semilla 2 -> converge a (-2, -1)
    semillas[2][0] = -2.5;  semillas[2][1] = -0.5;
    // Semilla 3 -> converge a (-1, -2)
    semillas[3][0] = -0.5;  semillas[3][1] = -2.5;

    // 4. Ejecutar Newton-Raphson para todas las semillas
    double **soluciones = newton_raphson_multi_sys(Sistema, semillas, num_puntos, n, tol, max_iter);

    // 5. Mostrar resultados
    cout << fixed << setprecision(6);
    cout << "Soluciones encontradas (una fila por cada semilla):\n";
    cout << "---------------------------------------------------\n";
    for (int k = 0; k < num_puntos; k++) {
        cout << "Semilla " << k << " (" << semillas[k][0] << ", " << semillas[k][1] << ") -> ";
        if (std::isnan(soluciones[k][0])) {
            cout << "No convergio (NaN)\n";
        } else {
            cout << "x = " << setw(10) << soluciones[k][0] 
                 << ", y = " << setw(10) << soluciones[k][1] << "\n";
        }
    }

    // 6. Liberar la memoria dinámica reservada
    del_mat(semillas, num_puntos);
    del_mat(soluciones, num_puntos);

    return 0;
}
