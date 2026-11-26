// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Mensajes de error, aviso e informacion
// ============================================================================
// Funciones para imprimir mensajes por pantalla con formato homogeneo ([MATCLUB ERROR], [MATCLUB AVISO], [MATCLUB INFO]).
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "mensajes.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (6): print_error, print_warning, print_info, print_error_int, print_error_dim, print_line
// Dependencias copiadas: ninguna
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_MENSAJES_CPP
#define MATCLUB_MENSAJES_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Mensajes de error, aviso e informacion
// ----------------------------------------------------------------------------

#ifndef MC_FN_print_error
#define MC_FN_print_error
void print_error(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB ERROR]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_error

#ifndef MC_FN_print_warning
#define MC_FN_print_warning
// Aviso: algo no fue perfecto pero el programa puede continuar
void print_warning(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB AVISO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_warning

#ifndef MC_FN_print_info
#define MC_FN_print_info
// Informacion (p. ej. "archivo guardado")
void print_info(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB INFO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_info

#ifndef MC_FN_print_error_int
#define MC_FN_print_error_int
// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor) {
    cout << "[MATCLUB ERROR]: " << mensaje << ": " << valor << endl;
}
#endif // MC_FN_print_error_int

#ifndef MC_FN_print_error_dim
#define MC_FN_print_error_dim
// Error de dimensiones: "mensaje (faxca) * (fbxcb)"
void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb) {
    cout << "[MATCLUB ERROR]: " << mensaje
         << " (" << fa << "x" << ca << ") * (" << fb << "x" << cb << ")" << endl;
}
#endif // MC_FN_print_error_dim

#ifndef MC_FN_print_line
#define MC_FN_print_line
// Linea separadora para ordenar la salida por pantalla
void print_line(int n = 40, char c = '=') {
    for (int i = 0; i < n; i++) cout << c;
    cout << endl;
}
#endif // MC_FN_print_line

#endif // MATCLUB_MENSAJES_CPP
