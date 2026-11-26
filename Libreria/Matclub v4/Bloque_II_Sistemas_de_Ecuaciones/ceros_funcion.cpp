// ============================================================================
// MATCLUB-CPP  |  BLOQUE II: SISTEMAS DE ECUACIONES  |  II.1
// Busqueda de ceros de una funcion
// ============================================================================
// Biseccion, falsa posicion, secante, Newton (simple y modificado para raices multiples), Muller, punto fijo, aceleracion de Aitken y estimacion del orden de convergencia; con versiones para buscar varias raices.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "ceros_funcion.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (12): biseccion, biseccion_multi, secante, newton, newton_multi, falsa_posicion, punto_fijo, muller, newton_modificado, aitken, punto_fijo_aitken, orden_convergencia
// Dependencias copiadas (7): MC_NAN, print_error, print_warning, print_error_int, intercambiar_elem, isNaN, isRoot
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
#ifndef MC_FN_print_error_int
#define MC_FN_print_error_int
// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}
#endif // MC_FN_print_error_int

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
// Descripción: Encuentra una raiz de f en [x1,x2] partiendo el intervalo por la mitad en cada paso. Convergencia lineal, pero SIEMPRE converge.
// Condiciones: f continua y f(x1)*f(x2) < 0 (signos opuestos); no sirve para raices dobles (f no cambia de signo). Se detiene cuando el intervalo mide menos de 2*tol1 o |f| < tol2.
double biseccion(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return x*x*x + x*x - 3*x - 3; }
        double r = biseccion(f, 1.0, 2.0, 1e-10, 1e-10, 100);
        // Resultado: r = 1.732051   (raiz exacta: sqrt(3))
    */
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
// Descripción: Busca TODAS las raices de f en [a,b]: divide el intervalo en 'subintervalos', aplica biseccion en cada uno donde f cambia de signo y elimina duplicados. Devuelve el array y su tamaño en num_raices.
// Condiciones: f continua; no detecta raices dobles ni dos raices dentro de un mismo subintervalo (en ese caso aumenta 'subintervalos').
double* biseccion_multi(double (*f)(double), double a, double b, 
                        int subintervalos, double tol, int &num_raices) {
    /*
    Ejemplo de uso:
        int nr;
        double *r = biseccion_multi(sin, 1.0, 10.0, 100, 1e-10, nr);
        // Resultado: nr = 3 , r = [3.141593, 6.283185, 9.424778]   (raices de sin(x) en [1,10]: pi, 2pi, 3pi)
    */
    
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
// Descripción: Sustituye f'(x) de Newton por la pendiente de la recta por los dos ultimos puntos: x2 = x1 - f1*(x0-x1)/(f0-f1). Convergencia superlineal (p = 1.62) sin calcular derivadas.
// Condiciones: dos puntos iniciales cerca de la raiz (no hace falta que encierren la raiz); puede divergir si f(x0) ~ f(x1). Sigue mientras |f| > tol1 o |dx| > tol2.
double secante(double (*f)(double), double x0, double x1, 
               double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return 3*x + sin(x) - exp(x); }
        double r = secante(f, 1.0, 0.0, 1e-10, 1e-10, 100);
        // Resultado: r = 0.3604217
    */
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
// Descripción: Metodo de Newton-Raphson: x(n+1) = x(n) - f(x)/f'(x). Convergencia cuadratica (p = 2) cuando la raiz es simple y x0 esta cerca.
// Condiciones: f derivable y f'(x) != 0 en el entorno de la raiz; con raices multiples pierde velocidad (usa newton_modificado). Si f' se anula el proceso se detiene. Sigue mientras |f| > tol1 o |dx| > tol2.
double newton(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x)  { return 3*x + sin(x) - exp(x); }
        double df(double x) { return 3 + cos(x) - exp(x); }
        double r = newton(f, df, 0.0, 1e-12, 1e-12, 50);
        // Resultado: r = 0.3604217
    */
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
// Descripción: Busca varias raices de f en [a,b] lanzando Newton desde puntos equiespaciados de [a,b] ('puntos_inicio' de ellos) y descartando las que caen fuera del intervalo o estan repetidas. Devuelve el array (SIN ordenar) y su tamaño en num_raices.
// Condiciones: f derivable y df disponible; no garantiza encontrar todas las raices (depende de los puntos de partida).
double* newton_multi(double (*f)(double), double (*df)(double), 
                     double a, double b, int puntos_inicio, double tol, int &num_raices) {
    /*
    Ejemplo de uso:
        int nr;
        double *r = newton_multi(sin, cos, 1.0, 10.0, 30, 1e-10, nr);
        // Resultado: nr = 3 , r = [3.141593, 9.424778, 6.283185]   (raices de sin(x) en [1,10])
    */
    
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

#ifndef MC_FN_falsa_posicion
#define MC_FN_falsa_posicion
// Método de la Falsa Posición (regula falsi)
// Descripción: Como la secante, pero conserva siempre un intervalo [x0,x1] que encierra la raiz, asi que no se descontrola como ella. Converge de forma lineal (mas rapido que la biseccion).
// Condiciones: f continua en [x0,x1] y f(x0)*f(x1) < 0. Falla con raices dobles (la funcion puede no cambiar de signo). Sigue mientras |f(x2)| > tol1 o |dx| > tol2.
double falsa_posicion(double (*f)(double), double x0, double x1, double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return 3*x + sin(x) - exp(x); }
        double r = falsa_posicion(f, 0.0, 1.0, 1e-10, 1e-10, 100);   // raiz en 0.3604217
    */
    if (f(x0) * f(x1) >= 0.0) {
        print_error("falsa_posicion: f(x0) y f(x1) deben tener signos opuestos");
        return MC_NAN;
    }
    double x2 = x1, dx = 0.0;
    int iter = 0;
    do {
        double f0 = f(x0), f1 = f(x1);
        double xant = x2;
        x2 = x1 - f1 * ((x0 - x1) / (f0 - f1));
        dx = x2 - xant;
        if (f(x2) * f0 < 0.0) x1 = x2;
        else                  x0 = x2;
        iter++;
    } while ((fabs(f(x2)) > tol1 || fabs(dx) > tol2) && iter < max_iter);
    return x2;
}
#endif // MC_FN_falsa_posicion

#ifndef MC_FN_punto_fijo
#define MC_FN_punto_fijo
// Método de la Iteración de Punto Fijo: x = g(x)
// Descripción: Reescribe f(x)=0 como x=g(x) e itera x(n+1) = g(x(n)) hasta que |x(n+1)-x(n)| < tol. Convergencia lineal.
// Condicion suficiente: g y g' continuas cerca de la raiz con |g'(x)| < 1 y x0 dentro de ese intervalo. Si |g'| > 1 diverge (la funcion avisa y devuelve NaN).
double punto_fijo(double (*g)(double), double x0, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double g(double x) { return sqrt(2*x + 3); }    // de x^2 - 2x - 3 = 0, con |g'(3)| = 1/3 < 1
        double r = punto_fijo(g, 4.0, 1e-10, 200);       // converge a la raiz 3
    */
    double x1 = x0;
    int iter = 0;
    do {
        x0 = x1;
        x1 = g(x0);
        iter++;
        if (isNaN(x1) || fabs(x1) > 1e100) {
            print_error("punto_fijo: la iteracion diverge (comprueba que |g'(x)| < 1 cerca de la raiz)");
            return MC_NAN;
        }
    } while (fabs(x1 - x0) > tol && iter < max_iter);
    if (iter >= max_iter && fabs(x1 - x0) > tol) print_warning("punto_fijo alcanzo max_iter sin converger.");
    return x1;
}
#endif // MC_FN_punto_fijo

#ifndef MC_FN_muller
#define MC_FN_muller
// Método de Muller
// Descripción: Ajusta una parabola por tres puntos y toma la raiz de la parabola mas cercana a x0. Convergencia superlineal (p = 1.84), parecida a Newton, y sin necesitar f'.
// Condiciones: tres puntos iniciales distintos cerca de la raiz. Si la parabola no corta el eje x (discriminante negativo) la funcion avisa y devuelve NaN (la raiz seria compleja).
double muller(double (*f)(double), double xa, double xb, double xc, double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x) { return 3*x + sin(x) - exp(x); }
        double r = muller(f, 0.0, 0.5, 1.0, 1e-10, 1e-10, 50);   // raiz en 0.3604217
    */
    double p[3] = {xa, xb, xc};                         // ordenar: x2 < x0 < x1
    for (int i = 0; i < 2; i++)
        for (int j = i + 1; j < 3; j++)
            if (p[j] < p[i]) intercambiar_elem(p[i], p[j]);
    double x2 = p[0], x0 = p[1], x1 = p[2];
    if (x2 == x0 || x0 == x1) { print_error("muller: los tres puntos iniciales deben ser distintos"); return MC_NAN; }
    double r = x0, dx = 0.0;
    int iter = 0;
    do {
        double f2 = f(x2), f0 = f(x0), f1 = f(x1);
        double h1 = x1 - x0, h2 = x0 - x2;
        double a = ((f2 - f0) + h2 * (f1 - f0) / h1) / (h2 * (h1 + h2));   // p(t) = a*t^2 + b*t + c, t = x - x0
        double b = (f1 - f0 - a * h1 * h1) / h1;
        double c = f0;
        double disc = b * b - 4.0 * a * c;
        if (disc < 0.0) {
            print_error("muller: la parabola no corta el eje x (raices complejas). Prueba otros puntos iniciales.");
            return MC_NAN;
        }
        double den = (b >= 0.0) ? b + sqrt(disc) : b - sqrt(disc);          // signo de b: denominador de mayor modulo
        if (den == 0.0) break;
        r = x0 - 2.0 * c / den;                                              // raiz mas cercana a x0
        dx = r - x0;
        if (r > x2 && r < x1) {                                              // reordenar como en la teoria
            if (r > x0) { x2 = x0; x0 = r; }
            else        { x1 = x0; x0 = r; }
        } else {                                                             // r fuera del intervalo: quedarse con los 3 puntos mas cercanos
            double q[4] = {x2, x0, x1, r};
            for (int i = 0; i < 3; i++)
                for (int j = i + 1; j < 4; j++)
                    if (fabs(q[j] - r) < fabs(q[i] - r)) intercambiar_elem(q[i], q[j]);
            double t[3] = {q[0], q[1], q[2]};
            for (int i = 0; i < 2; i++)
                for (int j = i + 1; j < 3; j++)
                    if (t[j] < t[i]) intercambiar_elem(t[i], t[j]);
            x2 = t[0]; x0 = t[1]; x1 = t[2];
        }
        iter++;
    } while ((fabs(f(r)) > tol1 || fabs(dx) > tol2) && iter < max_iter);
    return r;
}
#endif // MC_FN_muller

#ifndef MC_FN_newton_modificado
#define MC_FN_newton_modificado
// Método de Newton modificado para raices multiples
// Descripción: Usa x(n+1) = x(n) - K*f(x)/f'(x), donde K es la multiplicidad de la raiz, y asi recupera la convergencia cuadratica que Newton pierde con raices dobles o triples.
// Condiciones: conocer (o suponer) la multiplicidad K >= 1 y partir de un x0 razonablemente cerca. Con K = 1 es el metodo de Newton normal.
double newton_modificado(double (*f)(double), double (*df)(double), double x0, int K, double tol1, double tol2, int max_iter) {
    /*
    Ejemplo de uso:
        double f(double x)  { return (x - 1) * (x - 1) * (x + 2); }     // raiz doble en x = 1
        double df(double x) { return 2 * (x - 1) * (x + 2) + (x - 1) * (x - 1); }
        double r = newton_modificado(f, df, 2.0, 2, 1e-12, 1e-12, 50);   // K = 2: raiz en 1
    */
    if (K < 1) { print_error_int("newton_modificado: la multiplicidad K debe ser >= 1", K); return MC_NAN; }
    double x1 = x0, dx = 0.0;
    int iter = 0;
    do {
        double fx = f(x0), dfx = df(x0);
        if (fx != 0.0 && dfx != 0.0) {
            x1 = x0 - K * (fx / dfx);
            dx = x1 - x0;
            x0 = x1;
        } else {
            break;
        }
        iter++;
    } while ((fabs(f(x1)) > tol1 || fabs(dx) > tol2) && iter < max_iter);
    return x1;
}
#endif // MC_FN_newton_modificado

#ifndef MC_FN_aitken
#define MC_FN_aitken
// Aceleración de Aitken (extrapolación de Aitken, Delta^2)
// Descripción: A partir de tres aproximaciones consecutivas x0, x1, x2 de un proceso que converge LINEALMENTE (biseccion, falsa posicion, punto fijo) estima la raiz mejorada:
// r = x0 - (x1-x0)^2 / (x2 - 2*x1 + x0). Si el denominador es nulo (ya ha convergido) devuelve x2.
double aitken(double x0, double x1, double x2) {
    /*
    Ejemplo de uso:
        // Punto fijo de g(x) = sqrt(2x+3) desde 4:  4, 3.31662, 3.10375
        double r = aitken(4.0, 3.31662, 3.10375);    // 3.00744 (mejor que x4 = 3.01144)
    */
    double d2 = x2 - 2.0 * x1 + x0;
    if (fabs(d2) < 1e-300) return x2;
    double d1 = x1 - x0;
    return x0 - d1 * d1 / d2;
}
#endif // MC_FN_aitken

#ifndef MC_FN_punto_fijo_aitken
#define MC_FN_punto_fijo_aitken
// Punto fijo acelerado con Aitken (método de Steffensen)
// Descripción: En cada paso calcula x1 = g(x0), x2 = g(x1) y los sustituye por la extrapolacion de Aitken. Converge mucho mas rapido que punto_fijo (cuadraticamente) si |g'| < 1 cerca de la raiz.
double punto_fijo_aitken(double (*g)(double), double x0, double tol, int max_iter) {
    /*
    Ejemplo de uso:
        double g(double x) { return sqrt(2*x + 3); }
        double r = punto_fijo_aitken(g, 4.0, 1e-12, 50);    // 3 en muy pocas iteraciones
    */
    double dx = 0.0;
    int iter = 0;
    do {
        double x1 = g(x0), x2 = g(x1);
        double xn = aitken(x0, x1, x2);
        if (isNaN(xn) || fabs(xn) > 1e100) {
            print_error("punto_fijo_aitken: la iteracion diverge");
            return MC_NAN;
        }
        dx = xn - x0;
        x0 = xn;
        iter++;
    } while (fabs(dx) > tol && iter < max_iter);
    return x0;
}
#endif // MC_FN_punto_fijo_aitken

#ifndef MC_FN_orden_convergencia
#define MC_FN_orden_convergencia
// Orden de convergencia de un método iterativo
// Descripción: Dada la sucesion de errores |E_n| de un metodo, estima p en |E(n+1)| = cte*|E(n)|^p como la pendiente de la recta log|E(n+1)| frente a log|E(n)| (minimos cuadrados).
// Necesita al menos 3 errores positivos. p = 1 lineal, p = 2 cuadratica (Newton, raiz simple), p = 1.62 secante, p = 1.84 Muller.
double orden_convergencia(double *err, int n) {
    /*
    Ejemplo de uso:
        double E[] = {1e-1, 5e-3, 1.25e-5, 7.8125e-11};   // E(n+1) = 0.5 * E(n)^2
        double p = orden_convergencia(E, 4);               // p = 2 (convergencia cuadratica)
    */
    if (n < 3) { print_error_int("orden_convergencia: se necesitan al menos 3 errores", n); return MC_NAN; }
    double sx = 0.0, sy = 0.0, sxx = 0.0, sxy = 0.0;
    int m = 0;
    for (int i = 0; i < n - 1; i++) {
        if (err[i] == 0.0 || err[i + 1] == 0.0) continue;
        double X = log(fabs(err[i])), Y = log(fabs(err[i + 1]));
        sx += X; sy += Y; sxx += X * X; sxy += X * Y;
        m++;
    }
    double den = m * sxx - sx * sx;
    if (m < 2 || fabs(den) < 1e-300) { print_error("orden_convergencia: errores insuficientes o todos iguales"); return MC_NAN; }
    return (m * sxy - sx * sy) / den;
}
#endif // MC_FN_orden_convergencia

#endif // MATCLUB_CEROS_FUNCION_CPP
