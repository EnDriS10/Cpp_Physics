// ============================================================================
// matclub.h - Cabecera MAESTRA de MATCLUB-CPP
// ============================================================================
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
//
// Basta con:   #include "matclub.h"   en tu programa.
// Incluye las cabeceras de todos los bloques. Compilar junto con todos los .cpp
// de las carpetas (ver README.md).
// ============================================================================

#ifndef MATCLUB_H
#define MATCLUB_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

// --- Bloque_I_Introduccion ---
#include "Bloque_I_Introduccion/mensajes.h"
#include "Bloque_I_Introduccion/auxiliares.h"
#include "Bloque_I_Introduccion/vectores.h"
#include "Bloque_I_Introduccion/matrices.h"
#include "Bloque_I_Introduccion/ordenacion.h"
#include "Bloque_I_Introduccion/aleatorios.h"
#include "Bloque_I_Introduccion/archivos.h"
// --- Bloque_II_Sistemas_de_Ecuaciones ---
#include "Bloque_II_Sistemas_de_Ecuaciones/ceros_funcion.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/factorizacion_lu.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/eliminacion_gauss.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/sistemas_tridiagonales.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/determinantes_inversas.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/metodos_iterativos.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/minimos_cuadrados.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/sistemas_no_lineales.h"
#include "Bloque_II_Sistemas_de_Ecuaciones/minimizacion.h"
// --- Bloque_III_Diagonalizacion ---
#include "Bloque_III_Diagonalizacion/autovalores.h"
#include "Bloque_III_Diagonalizacion/jacobi.h"
#include "Bloque_III_Diagonalizacion/qr.h"
#include "Bloque_III_Diagonalizacion/householder.h"
// --- Bloque_IV_Integracion_Derivacion ---
#include "Bloque_IV_Integracion_Derivacion/integracion.h"
#include "Bloque_IV_Integracion_Derivacion/derivacion.h"
// --- Bloque_V_EDOs ---
#include "Bloque_V_EDOs/edo_valores_iniciales.h"
#include "Bloque_V_EDOs/edo_sistemas.h"
#include "Bloque_V_EDOs/edo_frontera.h"
#include "Bloque_V_EDOs/edps.h"
// --- Complementos ---
#include "Complementos/interpolacion.h"
#include "Complementos/estadistica.h"

#endif // MATCLUB_H
