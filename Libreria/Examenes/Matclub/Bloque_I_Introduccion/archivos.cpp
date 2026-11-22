// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Manipulacion de archivos
// ============================================================================
// Lectura y escritura de vectores, matrices y tablas (x,y) en archivos de texto.
//
// Funciones (13): file_exists, skip_comments, count_text_lines_file, count_lines_file, read_xy_file, save_xy_file, save_mat_file, read_mat_file, count_rows_single_file, read_single_vector_file, save_vector_file, get_file_dimensions, read_mat_auto
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#include "../matclub.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// Comprueba si un archivo existe y se puede abrir

bool file_exists(const char* filename) {
    ifstream f(filename, ios::in);
    return f.good();
}

// Salta espacios y lineas de comentario que empiezan por '#' (cabeceras de gnuplot/numpy)

void skip_comments(ifstream &f) {
    while (f >> ws && f.peek() == '#') {
        char ch;
        while (f.get(ch) && ch != '\n') { }   // descarta el resto de la linea
    }
}

// Cuenta TODAS las lineas de texto de un archivo (incluidas cabeceras y vacias)

int count_text_lines_file(const char* filename) {
    ifstream f(filename, ios::in);
    if (!f) {
        print_error("No se pudo abrir el archivo", filename);
        return -1;
    }
    int n = 0;
    bool con_texto = false;   // la linea actual tiene algun caracter
    char ch;
    while (f.get(ch)) {
        if (ch == '\n') { n++; con_texto = false; }
        else con_texto = true;
    }
    if (con_texto) n++;       // ultima linea sin salto de linea final
    return n;
}

// Cuenta cuántas líneas (puntos) tiene un archivo de datos con 2 columnas

int count_lines_file(const char* filename) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo", filename);
        return -1;
    }
    
    int m = 0;
    double x, y;
    // Lectura segura: el while comprueba si se pudo leer con éxito la pareja x, y
    while (fentrada >> x >> y) {
        m++;
    }
    fentrada.close();
    return m;
}

// Lee un archivo de 2 columnas y carga los datos en los vectores dinámicos x e y preexistentes

void read_xy_file(const char* filename, double *x, double *y, int m) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo para lectura", filename);
        return;
    }
    
    for (int i = 0; i < m; i++) {
        fentrada >> x[i] >> y[i];
    }
    fentrada.close();
}

// Guarda dos vectores x e y en un archivo de texto con dos columnas separadas por tabulador

void save_xy_file(const char* filename, double *x, double *y, int m) {
    ofstream fsalida(filename, ios::out);
    if (!fsalida) {
        print_error("No se pudo crear el archivo para guardado", filename);
        return;
    }
    
    for (int i = 0; i < m; i++) {
        fsalida << x[i] << "\t" << y[i] << endl;
    }
    fsalida.close();
    print_info("Datos guardados exitosamente", filename);
}

// Guarda una matriz completa (f x c) en un archivo de texto tabulado

void save_mat_file(const char* filename, double **A, int f, int c) {
    ofstream fsalida(filename, ios::out);
    if (!fsalida) {
        print_error("No se pudo abrir el archivo para guardar la matriz", filename);
        return;
    }
    
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            fsalida << A[i][j] << (j < c - 1 ? "\t" : "");
        }
        fsalida << endl;
    }
    fsalida.close();
}

// Lee una matriz de dimensiones conocidas (f x c) desde un archivo de texto

double** read_mat_file(const char* filename, int f, int c) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo para leer la matriz", filename);
        return NULL;
    }
    
    double **M = gen_mat(M, f, c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            if (!(fentrada >> M[i][j])) {
                print_warning("Faltaban datos en el archivo", filename);
            }
        }
    }
    fentrada.close();
    return M;
}

// Cuenta cuántos elementos (filas) tiene un archivo de una sola columna

int count_rows_single_file(const char* filename) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo", filename);
        return -1;
    }
    
    int m = 0;
    double val;
    while (fentrada >> val) {
        m++;
    }
    fentrada.close();
    return m;
}

// Lee un archivo de una sola columna y lo devuelve como un vector dinámico 1D

double* read_single_vector_file(const char* filename, int &n_out) {
    n_out = count_rows_single_file(filename);
    if (n_out <= 0) return NULL;
    
    double *v = new double[n_out];
    ifstream fentrada(filename, ios::in);
    for (int i = 0; i < n_out; i++) {
        fentrada >> v[i];
    }
    fentrada.close();
    return v;
}

// Guarda un vector dinámico 1D en un archivo de texto de una sola columna

void save_vector_file(const char* filename, double *v, int n) {
    ofstream fsalida(filename, ios::out);
    if (!fsalida) {
        print_error("No se pudo crear el archivo para guardar el vector", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        fsalida << v[i] << endl;
    }
    fsalida.close();
    print_info("Vector guardado exitosamente", filename);
}

// Cuenta el número de filas y columnas de un archivo de matriz desconocido sin usar sstream

bool get_file_dimensions(const char* filename, int &f_out, int &c_out) {
    ifstream fentrada(filename, ios::in);
    if (!fentrada) {
        print_error("No se pudo abrir el archivo", filename);
        return false;
    }
    
    f_out = 0;
    c_out = 0;
    
    // 1. Contar cuántas columnas hay en la primera línea
    double temp_val;
    char ch;
    
    // Leemos números de la primera línea hasta que se acabe o cambie de línea
    while (fentrada >> temp_val) {
        c_out++;
        // Verificamos si el siguiente carácter es un salto de línea
        ch = fentrada.peek();
        if (ch == '\n' || ch == '\r') {
            break; // Salimos del bucle al terminar la primera fila
        }
    }
    
    if (c_out == 0) {
        print_error("El archivo esta vacio", filename);
        fentrada.close();
        return false; // Archivo vacío
    }
    
    // 2. Contar el total de elementos en todo el archivo para sacar el número exacto de filas
    fentrada.clear(); // Limpiamos posibles estados de fin de archivo
    fentrada.seekg(0, ios::beg); // Volvemos al inicio del archivo
    
    int total_elementos = 0;
    while (fentrada >> temp_val) {
        total_elementos++;
    }
    
    fentrada.close();
    
    // El número de filas es el total de números divididos entre las columnas contadas
    f_out = total_elementos / c_out;
    
    return true;
}

// Lee una matriz SIN conocer sus dimensiones (las calcula con get_file_dimensions)
// Uso:  int f, c;  double **A = read_mat_auto("datos.txt", f, c);

double** read_mat_auto(const char* filename, int &f_out, int &c_out) {
    if (!get_file_dimensions(filename, f_out, c_out)) return NULL;
    return read_mat_file(filename, f_out, c_out);
}

