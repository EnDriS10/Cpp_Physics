// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Mensajes de error, aviso e informacion
// ============================================================================
// Funciones para imprimir mensajes por pantalla con formato homogeneo ([MATCLUB ERROR], [MATCLUB AVISO], [MATCLUB INFO]).
//
// Funciones (6): print_error, print_warning, print_info, print_error_int, print_error_dim, print_line
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_MENSAJES_H
#define MATCLUB_MENSAJES_H

#include <iostream>   // NULL

void print_error(const char* mensaje, const char* detalle = NULL);

// Aviso: algo no fue perfecto pero el programa puede continuar
void print_warning(const char* mensaje, const char* detalle = NULL);

// Informacion (p. ej. "archivo guardado")
void print_info(const char* mensaje, const char* detalle = NULL);

// Error con un valor entero: "mensaje: valor"
void print_error_int(const char* mensaje, int valor);

// Error de dimensiones: "mensaje (faxca) * (fbxcb)"
void print_error_dim(const char* mensaje, int fa, int ca, int fb, int cb);

// Linea separadora para ordenar la salida por pantalla
void print_line(int n = 40, char c = '=');

#endif // MATCLUB_MENSAJES_H
