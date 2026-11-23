// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.1
// Busqueda de ceros de una funcion
// ============================================================================
// Biseccion, secante y Newton (con version para buscar varias raices en un intervalo).
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "ceros_funcion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (5): biseccion, biseccion_multi, secante, newton, newton_multi
// Dependencias copiadas (5): MC_NAN, print_error, intercambiar_elem, isNaN, isRoot
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_CEROS_FUNCION_CPP
#define MATCLUB_CEROS_FUNCION_CPP

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

// (copiada de: auxiliares)
#ifndef MC_FN_intercambiar_elem
#define MC_FN_intercambiar_elem
//Intercambia dos elementos
void intercambiar_elem(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}
#endif // MC_FN_intercambiar_elem

// (copiada de: auxiliares)
#ifndef MC_FN_isNaN
#define MC_FN_isNaN
bool isNaN(double v) {
    return v != v; // En norma IEEE 754, NaN es distinto de sí mismo
}
#endif // MC_FN_isNaN

// (copiada de: auxiliares)
#ifndef MC_FN_isRoot
#define MC_FN_isRoot
bool isRoot(const double* raices, int n, double r, double tol) {
    for (int i = 0; i < n; ++i) {
        if (fabs(raices[i] - r) < tol) return true;
    }
    return false;
}
#endif // MC_FN_isRoot

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Busqueda de ceros de una funcion
// ----------------------------------------------------------------------------

#ifndef MC_FN_biseccion
#define MC_FN_biseccion
// Método de la Biseccion (Una sola raiz)
double biseccion(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int max_iter) {
    if (f(x1) * f(x2) >= 0.0) {
        print_error("f(x1) y f(x2) deben tener signos opuestos");
        return MC_NAN; 
    }

    double x3 = 0.0;
    int iter = 0;

    do {
        x3 = (x1 + x2) / 2.0;
        if (f(x3) * f(x1) < 0.0) {
            x2 = x3;
        } else {
            x1 = x3;
        }
        iter++;
    } while ((fabs(x2 - x1) > 2.0 * tol1 && fabs(f(x3)) > tol2) && iter < max_iter);

    return x3;
}
#endif // MC_FN_biseccion

#ifndef MC_FN_biseccion_multi
#define MC_FN_biseccion_multi
// Biseccion Multiple: Busca multiples raices en un intervalo [a, b]
double* biseccion_multi(double (*f)(double), double a, double b, 
                        int subintervalos, double tol, int &num_raices) {
    
    // Reserva de memoria al estilo de la libreria
    double* raices = new double[subintervalos]; 
    num_raices = 0;
    double paso = (b - a) / subintervalos;

    for (int i = 0; i < subintervalos; ++i) {
        double x1 = a + i * paso;
        double x2 = x1 + paso;

        if (f(x1) * f(x2) < 0.0) {
            double r = biseccion(f, x1, x2, tol, tol, 100);
            // Uso de las utilidades isNaN e isRoot de matclub_2
            if (!isNaN(r) && !isRoot(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        } else if (fabs(f(x1)) < tol && !isRoot(raices, num_raices, x1, 1e-3)) {
            raices[num_raices] = x1;
            num_raices++;
        }
    }
    
    // Si no se encontraron raices, limpiamos memoria y devolvemos nulo
    if (num_raices == 0) {
        delete[] raices;
        return NULL;
    }
    
    return raices;
}
#endif // MC_FN_biseccion_multi

#ifndef MC_FN_secante
#define MC_FN_secante
// Método de la Secante (Una sola raiz)
double secante(double (*f)(double), double x0, double x1, 
               double tol1, double tol2, int max_iter) {
    if (fabs(f(x0)) < fabs(f(x1))) {
        intercambiar_elem(x0, x1); // Uso de tu funcion de intercambio
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
#endif // MC_FN_secante

#ifndef MC_FN_newton
#define MC_FN_newton
// Método de Newton (Una sola raiz)
double newton(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int max_iter) {
    double x1 = x0;
    double dx = 0.0;
    int iter = 0;

    do {
        double fx = f(x0);
        double dfx = df(x0);

        if (fx != 0.0 && dfx != 0.0) {
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
#endif // MC_FN_newton

#ifndef MC_FN_newton_multi
#define MC_FN_newton_multi
// Newton Multiple: Busca multiples raices lanzando Newton desde varios puntos
double* newton_multi(double (*f)(double), double (*df)(double), 
                     double a, double b, int puntos_inicio, double tol, int &num_raices) {
    
    double* raices = new double[puntos_inicio + 1];
    num_raices = 0;
    double paso = (b - a) / puntos_inicio;

    for (int i = 0; i <= puntos_inicio; ++i) {
        double x0 = a + i * paso;
        double r = newton(f, df, x0, tol, tol, 100);

        if (!isNaN(r) && r >= a && r <= b && fabs(f(r)) < tol) {
            if (!isRoot(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        }
    }
    
    // Si no se encontraron raices, limpiamos memoria y devolvemos nulo
    if (num_raices == 0) {
        delete[] raices;
        return NULL;
    }
    
    return raices;
}
#endif // MC_FN_newton_multi

#endif // MATCLUB_CEROS_FUNCION_CPP
