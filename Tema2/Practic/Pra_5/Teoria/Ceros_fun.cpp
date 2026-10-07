#include <iostream>
#include <cmath>

// 1. Librerías estándar compatibles con C++98
#include <vector>      // [USO DE <vector>]: Para manejar arreglos dinámicos de raíces
#include <iomanip>     // [USO DE <iomanip>]: Para fijar la precisión decimal de los resultados
#include <algorithm>   // [USO DE <algorithm>]: Para usar std::swap en el intercambio de variables

using namespace std;

// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

// Comprobación de NaN compatible con C++98 (en IEEE 754, NaN es el único número distinto de sí mismo)
bool esNaN(double v) {
    return v != v;
}

// [USO DE <vector>]: Recibe 'const vector<double>&' por referencia para leer la lista de raíces
bool existeRaiz(const vector<double>& raices, double r, double tol) {
    // Bucle indexado tradicional de C++98
    for (size_t i = 0; i < raices.size(); ++i) {
        if (fabs(raices[i] - r) < tol) return true;
    }
    return false;
}

// [USO DE <vector>]: Recibe el vector con las raíces encontradas para imprimirlas
// [USO DE <iomanip>]: Usa 'fixed' y 'setprecision(7)' para mostrar 7 decimales
void mostrarRaices(const string& metodo, const vector<double>& raices) {
    cout << "\n==========================================" << endl;
    cout << "Raices encontradas (" << metodo << "): " << raices.size() << endl; // .size() del vector
    cout << "==========================================" << endl;
    for (size_t i = 0; i < raices.size(); ++i) {
        // [USO DE <iomanip>]: 'fixed' establece decimales fijos y 'setprecision(7)' limita a 7 dígitos
        cout << "Raiz [" << i + 1 << "] = " << fixed << setprecision(7) << raices[i] << endl;
    }
}

// ============================================================================
// 1. METODO DE LA BISECCION
// ============================================================================

// Se utiliza un puntero a función 'double (*f)(double)' compatible con C++98
double biseccion(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int max_iter) {
    if (f(x1) * f(x2) >= 0) {
        cerr << "[Biseccion] Error: f(x1) y f(x2) deben tener signos opuestos." << endl;
        return 0.0 / 0.0; // Retorna NaN en C++98
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

// [USO DE <vector>]: Retorna un 'vector<double>' con todas las raíces halladas en [a, b]
vector<double> biseccion_multiples(double (*f)(double), double a, double b, 
                                   int subintervalos, double tol) {
    vector<double> raices; // [USO DE <vector>]: Vector dinámico inicialmente vacío
    double paso = (b - a) / subintervalos;

    for (int i = 0; i < subintervalos; ++i) {
        double x1 = a + i * paso;
        double x2 = x1 + paso;

        if (f(x1) * f(x2) < 0) {
            double r = biseccion(f, x1, x2, tol, tol, 100);
            if (!esNaN(r) && !existeRaiz(raices, r, 1e-3)) {
                raices.push_back(r); // [USO DE <vector>]: Añade la raíz al arreglo dinámico
            }
        } else if (fabs(f(x1)) < tol && !existeRaiz(raices, x1, 1e-3)) {
            raices.push_back(x1); // [USO DE <vector>]: Inserta un cero directo
        }
    }
    return raices;
}

// ============================================================================
// 2. METODO DE LA SECANTE
// ============================================================================

double secante(double (*f)(double), double x0, double x1, 
               double tol1, double tol2, int max_iter) {
    if (fabs(f(x0)) < fabs(f(x1))) {
        // [USO DE <algorithm>]: std::swap intercambia x0 y x1 de forma eficiente
        swap(x0, x1);
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

// ============================================================================
// 3. METODO DE NEWTON
// ============================================================================

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

// [USO DE <vector>]: Retorna las raíces acumuladas mediante la búsqueda por Newton
vector<double> newton_multiples(double (*f)(double), double (*df)(double), 
                                double a, double b, int puntos_inicio, double tol) {
    vector<double> raices; // [USO DE <vector>]: Creación del contenedor
    double paso = (b - a) / puntos_inicio;

    for (int i = 0; i <= puntos_inicio; ++i) {
        double x0 = a + i * paso;
        double r = newton(f, df, x0, tol, tol, 100);

        if (!esNaN(r) && r >= a && r <= b && fabs(f(r)) < tol) {
            if (!existeRaiz(raices, r, 1e-3)) {
                raices.push_back(r); // [USO DE <vector>]: Almacena la raíz
            }
        }
    }
    return raices;
}

// ============================================================================
// FUNCIONES MATEMATICAS COMPATIBLES CON C++98 (Sin expresiones Lambda)
// ============================================================================

double f1(double x) {
    return pow(x, 3) + pow(x, 2) - 3.0 * x - 3.0;
}

double df1(double x) {
    return 3.0 * pow(x, 2) + 2.0 * x - 3.0;
}

// ============================================================================
// MAIN DE PRUEBA
// ============================================================================

int main() {
    // [USO DE <iomanip>]: Configura la salida global de la consola a 7 decimales fijos
    cout << fixed << setprecision(7);

    cout << "=== PRUEBA DE METODOS (COMPATIBLE CON DEV-C++ 5.11) ===" << endl;

    // Cálculo individual pasando la función 'f1'
    double raiz_unica = biseccion(f1, 1.0, 2.0, 1e-5, 1e-5, 100);
    cout << "Raiz biseccion en [1, 2]: " << raiz_unica << endl;

    // Método de la secante
    double raiz_secante = secante(f1, 1.0, 2.0, 1e-5, 1e-5, 100);
    cout << "Raiz secante en [1, 2]:   " << raiz_secante << endl;

    // Método de Newton
    double raiz_newton = newton(f1, df1, 1.5, 1e-5, 1e-5, 100);
    cout << "Raiz Newton (x0=1.5):    " << raiz_newton << endl;

    // [USO DE <vector>]: Obtención e impresión de un arreglo dinámico de raíces
    vector<double> lista_raices = biseccion_multiples(f1, -3.0, 3.0, 1000, 1e-5);
    mostrarRaices("Biseccion Multiple", lista_raices);

    vector<double> lista_newton = newton_multiples(f1, df1, -3.0, 3.0, 50, 1e-5);
    mostrarRaices("Newton Multiple", lista_newton);

    return 0;
}
