// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Mensajes de error, aviso e informacion
// ============================================================================
// Funciones para imprimir mensajes por pantalla con formato homogeneo ([MATCLUB ERROR], [MATCLUB AVISO], [MATCLUB INFO]).
//
// Funciones (6): print_error, print_warning, print_info, print_error_int, print_error_dim, print_line
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

void print_error(const char* mensaje, const char* detalle) {
    cout << "[MATCLUB ERROR]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}

// Aviso: algo no fue perfecto pero el programa puede continuar

void print_warning(const char* mensaje, const char* detalle) {
    cout << "[MATCLUB AVISO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}

// Informacion (p. ej. "archivo guardado")

void print_info(const char* mensaje, const char* detalle) {
    cout << "[MATCLUB INFO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}

// Error con un valor entero: "mensaje: valor"

void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}

// Error de dimensiones: "mensaje (faxca) * (fbxcb)"

void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb) {
    cout << "[MATCLUB ERROR]: " << mensaje
         << " (" << fa << "x" << ca << ") * (" << fb << "x" << cb << ")" << endl;
}

// Linea separadora para ordenar la salida por pantalla

void print_line(int n, char c) {
    for (int i = 0; i < n; i++) cout << c;
    cout << endl;
}

