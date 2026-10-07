#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

// ============================================================================
// FUNCIONES DE MEMORIA DINAMICA (Extraidas de Memoria_Dinamica.cpp)
// ============================================================================

// Creacion dinamica de vector 1D
double* crearVector(int n) {
    return new (std::nothrow) double[n]; // Devuelve NULL si se queda sin RAM
}

// Destruccion dinamica de vector 1D
void destruirVector(double* v) {
    if (v != NULL) {
        delete[] v; // Liberacion de memoria
    }
}

// Creacion dinamica de matriz 2D (Tomada de FuncionesMatrizDinamica)
double** crearMatriz(int filas, int cols) {
    double** M = new (std::nothrow) double*[filas];
    if (M == NULL) return NULL;
    for (int i = 0; i < filas; i++) {
        M[i] = new (std::nothrow) double[cols];
    }
    return M;
}

// Destruccion dinamica de matriz 2D (Tomada de FuncionesMatrizDinamica)
void destruirMatriz(double** M, int filas) {
    if (M != NULL) {
        for (int i = 0; i < filas; i++) {
            delete[] M[i];
        }
        delete[] M;
    }
}

// ============================================================================
// FUNCIONES AUXILIARES DE BUSQUEDA NUMERICA
// ============================================================================

void intercambiar(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}

bool esNaN(double v) {
    return v != v; // En norma IEEE 754, NaN es distinto de sí mismo
}

bool existeRaiz(const double* raices, int n, double r, double tol) {
    for (int i = 0; i < n; ++i) {
        if (fabs(raices[i] - r) < tol) return true;
    }
    return false;
}

void mostrarRaices(const char* metodo, const double* raices, int n) {
    cout << "\n==========================================" << endl;
    cout << "Raices encontradas (" << metodo << "): " << n << endl;
    cout << "==========================================" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Raiz [" << i + 1 << "] = " << fixed << setprecision(7) << raices[i] << endl;
    }
}

// ============================================================================
// METODOS NUMERICOS PARA BUSQUEDA DE CEROS
// ============================================================================

// 1. Método de la Bisección (Una sola raíz)
double biseccion(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int max_iter) {
    if (f(x1) * f(x2) >= 0) {
        cerr << "[Biseccion] Error: f(x1) y f(x2) deben tener signos opuestos." << endl;
        return 0.0 / 0.0; // NaN
    }

    double x3 = 0.0;
    int iter = 0;

    do {
        x3 = (x1 + x2) / 2.0;
        if (f(x3) * f(x1) < 0) {
            x2 = x3;
        } else {
            x1 = x3;
        }
        iter++;
    } while ((fabs(x2 - x1) > 2.0 * tol1 && fabs(f(x3)) > tol2) && iter < max_iter);

    return x3;
}

// Bisección Múltiple (Usa crearVector del módulo de memoria)
double* biseccion_multiples(double (*f)(double), double a, double b, 
                            int subintervalos, double tol, int &num_raices) {
    // Uso de crearVector()
    double* raices = crearVector(subintervalos);
    if (raices == NULL) return NULL;

    num_raices = 0;
    double paso = (b - a) / subintervalos;

    for (int i = 0; i < subintervalos; ++i) {
        double x1 = a + i * paso;
        double x2 = x1 + paso;

        if (f(x1) * f(x2) < 0) {
            double r = biseccion(f, x1, x2, tol, tol, 100);
            if (!esNaN(r) && !existeRaiz(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        } else if (fabs(f(x1)) < tol && !existeRaiz(raices, num_raices, x1, 1e-3)) {
            raices[num_raices] = x1;
            num_raices++;
        }
    }
    return raices;
}

// 2. Método de la Secante (Una sola raíz)
double secante(double (*f)(double), double x0, double x1, 
               double tol1, double tol2, int max_iter) {
    if (fabs(f(x0)) < fabs(f(x1))) {
        intercambiar(x0, x1);
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

// 3. Método de Newton (Una sola raíz)
double newton(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int max_iter) {
    double x1 = x0;
    double dx = 0.0;
    int iter = 0;

    do {
        double fx = f(x0);
        double dfx = df(x0);

        if (fx != 0 && dfx != 0) {
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

// Newton Múltiple (Usa crearVector del módulo de memoria)
double* newton_multiples(double (*f)(double), double (*df)(double), 
                         double a, double b, int puntos_inicio, double tol, int &num_raices) {
    // Uso de crearVector()
    double* raices = crearVector(puntos_inicio + 1);
    if (raices == NULL) return NULL;

    num_raices = 0;
    double paso = (b - a) / puntos_inicio;

    for (int i = 0; i <= puntos_inicio; ++i) {
        double x0 = a + i * paso;
        double r = newton(f, df, x0, tol, tol, 100);

        if (!esNaN(r) && r >= a && r <= b && fabs(f(r)) < tol) {
            if (!existeRaiz(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        }
    }
    return raices;
}

// ============================================================================
// FUNCIONES MATEMATICAS DE PRUEBA
// ============================================================================

double f1(double x) {
    return pow(x, 3) + pow(x, 2) - 3.0 * x - 3.0;
}

double df1(double x) {
    return 3.0 * pow(x, 2) + 2.0 * x - 3.0;
}

// ============================================================================
// MAIN PRINCIPAL
// ============================================================================

int main() {
    cout << fixed << setprecision(7);

    cout << "=== BUSQUEDA DE CEROS CON MODULOS DE MEMORIA DINAMICA ===" << endl;

    // 1. Pruebas individuales
    double r_bis = biseccion(f1, 1.0, 2.0, 1e-5, 1e-5, 100);
    cout << "Raiz Biseccion en [1, 2]: " << r_bis << endl;

    double r_sec = secante(f1, 1.0, 2.0, 1e-5, 1e-5, 100);
    cout << "Raiz Secante en [1, 2]:   " << r_sec << endl;

    double r_new = newton(f1, df1, 1.5, 1e-5, 1e-5, 100);
    cout << "Raiz Newton (x0=1.5):    " << r_new << endl;

    // 2. Uso de crearVector() en Bisección Múltiple
    int num_raices_bis = 0;
    double* lista_biseccion = biseccion_multiples(f1, -3.0, 3.0, 1000, 1e-5, num_raices_bis);
    mostrarRaices("Biseccion Multiple", lista_biseccion, num_raices_bis);

    // 3. Uso de crearVector() en Newton Múltiple
    int num_raices_new = 0;
    double* lista_newton = newton_multiples(f1, df1, -3.0, 3.0, 50, 1e-5, num_raices_new);
    mostrarRaices("Newton Multiple", lista_newton, num_raices_new);

    // 4. Liberación de memoria con destruirVector()
    destruirVector(lista_biseccion);
    lista_biseccion = NULL;

    destruirVector(lista_newton);
    lista_newton = NULL;

    // 5. Ejemplo de uso de crearMatriz() y destruirMatriz() de Memoria_Dinamica.cpp
    cout << "\n=== DEMOSTRACION DE CREAR Y DESTRUIR MATRIZ (2D) ===" << endl;
    int filas = 2, cols = 3;
    double** M = crearMatriz(filas, cols);

    if (M != NULL) {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < cols; j++) {
                M[i][j] = (i + 1) * 1.5 + j;
                cout << M[i][j] << "\t";
            }
            cout << endl;
        }
        destruirMatriz(M, filas); // Destrucción modular
        M = NULL;
    }

    cout << "\n=== EJECUCION FINALIZADA CON EXITO ===" << endl;
    return 0;
}
