// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Manipulacion de archivos
// ============================================================================
// Lectura y escritura de vectores, matrices y tablas (x,y) en archivos de texto.
//
// Funciones (13): file_exists, skip_comments, count_text_lines_file, count_lines_file, read_xy_file, save_xy_file, save_mat_file, read_mat_file, count_rows_single_file, read_single_vector_file, save_vector_file, get_file_dimensions, read_mat_auto
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ARCHIVOS_H
#define MATCLUB_ARCHIVOS_H

#include <fstream>

// Comprueba si un archivo existe y se puede abrir
bool file_exists(const char* filename);

// Salta espacios y lineas de comentario que empiezan por '#' (cabeceras de gnuplot/numpy)
void skip_comments(std::ifstream &f);

// Cuenta TODAS las lineas de texto de un archivo (incluidas cabeceras y vacias)
int count_text_lines_file(const char* filename);

// Cuenta cuántas líneas (puntos) tiene un archivo de datos con 2 columnas
int count_lines_file(const char* filename);

// Lee un archivo de 2 columnas y carga los datos en los vectores dinámicos x e y preexistentes
void read_xy_file(const char* filename, double *x, double *y, int m);

// Guarda dos vectores x e y en un archivo de texto con dos columnas separadas por tabulador
void save_xy_file(const char* filename, double *x, double *y, int m);

// Guarda una matriz completa (f x c) en un archivo de texto tabulado
void save_mat_file(const char* filename, double **A, int f, int c);

// Lee una matriz de dimensiones conocidas (f x c) desde un archivo de texto
double** read_mat_file(const char* filename, int f, int c);

// Cuenta cuántos elementos (filas) tiene un archivo de una sola columna
int count_rows_single_file(const char* filename);

// Lee un archivo de una sola columna y lo devuelve como un vector dinámico 1D
double* read_single_vector_file(const char* filename, int &n_out);

// Guarda un vector dinámico 1D en un archivo de texto de una sola columna
void save_vector_file(const char* filename, double *v, int n);

// Cuenta el número de filas y columnas de un archivo de matriz desconocido sin usar sstream
bool get_file_dimensions(const char* filename, int &f_out, int &c_out);

// Lee una matriz SIN conocer sus dimensiones (las calcula con get_file_dimensions)
// Uso:  int f, c;  double **A = read_mat_auto("datos.txt", f, c);
double** read_mat_auto(const char* filename, int &f_out, int &c_out);

#endif // MATCLUB_ARCHIVOS_H
