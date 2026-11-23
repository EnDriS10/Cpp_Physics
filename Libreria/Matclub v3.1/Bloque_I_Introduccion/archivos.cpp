// ============================================================================
// MATCLUB-CPP  |  BLOQUE I: INTRODUCCION
// Manipulacion de archivos
// ============================================================================
// Lectura y escritura de vectores, matrices y tablas (x,y) en archivos de texto.
//
// ARCHIVO INDEPENDIENTE: no necesita ningun otro archivo de MATCLUB.
// Uso:  #include "archivos.cpp"   (con la ruta donde lo tengas)
// Se pueden incluir varios modulos a la vez: cada funcion esta protegida
// contra duplicados (#ifndef MC_FN_<nombre>).
//
// Funciones propias (13): file_exists, skip_comments, count_text_lines_file, count_lines_file, read_xy_file, save_xy_file, save_mat_file, read_mat_file, count_rows_single_file, read_single_vector_file, save_vector_file, get_file_dimensions, read_mat_auto
// Dependencias copiadas (4): print_error, print_warning, print_info, gen_mat
// Made by Cesar with a little(to much) help of my friends (Gema y Jose)
// ============================================================================

#ifndef MATCLUB_ARCHIVOS_CPP
#define MATCLUB_ARCHIVOS_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------------------
// DEPENDENCIAS (copiadas de otros modulos de MATCLUB, sin modificar)
// ----------------------------------------------------------------------------

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
#ifndef MC_FN_print_info
#define MC_FN_print_info
// Informacion (p. ej. "archivo guardado")
void print_info(const char* mensaje, const char* detalle = NULL) {
    cout << "[MATCLUB INFO]: " << mensaje;
    if (detalle != NULL) cout << " (" << detalle << ")";
    cout << endl;
}
#endif // MC_FN_print_info

// (copiada de: matrices)
#ifndef MC_FN_gen_mat
#define MC_FN_gen_mat
//Crear Matriz
double** gen_mat(double **M, int f, int c){
	/* en el programa principal si queremos crear (reservar memoria) para la matriz B. 
   		double **B;
   		B=crearmatriz(B,fb,cb);
   	donde fb es el numero de filas de B y cb el numero de columnas de B
	*/
    M = new double * [f];
    	for (int i = 0; i < f; i++) { M[i] = new double[c];}
     return M;
}
#endif // MC_FN_gen_mat

// ----------------------------------------------------------------------------
// FUNCIONES DEL MODULO: Manipulacion de archivos
// ----------------------------------------------------------------------------

#ifndef MC_FN_file_exists
#define MC_FN_file_exists
// Comprueba si un archivo existe y se puede abrir
bool file_exists(const char* filename) {
    ifstream f(filename, ios::in);
    return f.good();
}
#endif // MC_FN_file_exists

#ifndef MC_FN_skip_comments
#define MC_FN_skip_comments
// Salta espacios y lineas de comentario que empiezan por '#' (cabeceras de gnuplot/numpy)
void skip_comments(ifstream &f) {
    while (f >> ws && f.peek() == '#') {
        char ch;
        while (f.get(ch) && ch != '\n') { }   // descarta el resto de la linea
    }
}
#endif // MC_FN_skip_comments

#ifndef MC_FN_count_text_lines_file
#define MC_FN_count_text_lines_file
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
#endif // MC_FN_count_text_lines_file

#ifndef MC_FN_count_lines_file
#define MC_FN_count_lines_file
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
#endif // MC_FN_count_lines_file

#ifndef MC_FN_read_xy_file
#define MC_FN_read_xy_file
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
#endif // MC_FN_read_xy_file

#ifndef MC_FN_save_xy_file
#define MC_FN_save_xy_file
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
#endif // MC_FN_save_xy_file

#ifndef MC_FN_save_mat_file
#define MC_FN_save_mat_file
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
#endif // MC_FN_save_mat_file

#ifndef MC_FN_read_mat_file
#define MC_FN_read_mat_file
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
#endif // MC_FN_read_mat_file

#ifndef MC_FN_count_rows_single_file
#define MC_FN_count_rows_single_file
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
#endif // MC_FN_count_rows_single_file

#ifndef MC_FN_read_single_vector_file
#define MC_FN_read_single_vector_file
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
#endif // MC_FN_read_single_vector_file

#ifndef MC_FN_save_vector_file
#define MC_FN_save_vector_file
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
#endif // MC_FN_save_vector_file

#ifndef MC_FN_get_file_dimensions
#define MC_FN_get_file_dimensions
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
#endif // MC_FN_get_file_dimensions

#ifndef MC_FN_read_mat_auto
#define MC_FN_read_mat_auto
// Lee una matriz SIN conocer sus dimensiones (las calcula con get_file_dimensions)
// Uso:  int f, c;  double **A = read_mat_auto("datos.txt", f, c);
double** read_mat_auto(const char* filename, int &f_out, int &c_out) {
    if (!get_file_dimensions(filename, f_out, c_out)) return NULL;
    return read_mat_file(filename, f_out, c_out);
}
#endif // MC_FN_read_mat_auto

#endif // MATCLUB_ARCHIVOS_CPP
