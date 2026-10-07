#include <iostream>

using namespace std;

// ============================================================================
// CONCEPTO 1: Array Unidimensional Dinámico (Vector 1D)
// ============================================================================
namespace VectorDinamico1D {
    void ejecutar() {
        cout << "=== 1. VECTORES UNIDIMENSIONALES DINAMICOS ===" << endl;

        int *A;
        int n = 5; // Tamaño determinado en tiempo de ejecución[cite: 5, 6]

        // Reserva dinámica de memoria para n enteros[cite: 6]
        A = new int[n]; 

        // Rellenado e impresión del vector[cite: 6]
        cout << "Valores generados en el vector A[" << n << "]:" << endl;
        for (int i = 0; i < n; i++) { 
            A[i] = (i * i + 1); 
            cout << "A[" << i << "] = " << A[i] << endl; 
        } 

        // Liberación de la memoria reservada[cite: 5, 6]
        delete[] A; 
        A = NULL; // Buena práctica: evitar punteros colgados
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 2: Array Bidimensional Dinámico (Matriz 2D mediante **A)
// ============================================================================
namespace MatrizDinamica2D {
    void ejecutar() {
        cout << "=== 2. MATRICES BIDIMENSIONALES DINAMICAS (double**) ===" << endl;

        double **A; // Declaración como puntero a puntero[cite: 7]
        int fa = 3, ca = 3; // Filas y Columnas

        // --------------------------------------------------------------------
        // ETAPA (a): Reserva del array de punteros que apunten a cada fila[cite: 7, 8]
        // --------------------------------------------------------------------
        A = new double*[fa]; 

        // --------------------------------------------------------------------
        // ETAPA (b): Reserva de los elementos de cada una de las filas[cite: 7, 8]
        // --------------------------------------------------------------------
        for (int i = 0; i < fa; i++) { 
            A[i] = new double[ca]; 
        } 

        // Rellenar y mostrar la matriz[cite: 8]
        cout << "Matriz A (" << fa << "x" << ca << "):" << endl;
        for (int i = 0; i < fa; i++) {  
            for (int j = 0; j < ca; j++) { 
                A[i][j] = 2 * i + 3 * j; 
                cout << A[i][j] << "\t";
            } 
            cout << endl;
        }  

        // --------------------------------------------------------------------
        // LIBERACIÓN DE MEMORIA EN DOS ETAPAS (A la inversa)[cite: 7, 8]
        // --------------------------------------------------------------------
        // 1. Liberar los elementos de cada fila[cite: 8]
        for (int i = 0; i < fa; i++) { 
            delete[] A[i]; 
        } 
        // 2. Liberar el array de punteros principal[cite: 8]
        delete[] A; 
        A = NULL;

        cout << endl;
    }
}

// ============================================================================
// NUEVO CONCEPTO 3: Asignación Dinámica Individual e Inicialización Directa
// ============================================================================
namespace AsignacionEInicializacion {
    void ejecutar() {
        cout << "=== 3. ASIGNACION INDIVIDUAL E INICIALIZACION DIRECTA ===" << endl;

        // 1. Asignar un solo entero dinámicamente e inicializarlo con valor 100
        int *pVar = new int(100);
        cout << "Variable individual reservada con valor: " << *pVar << endl;
        delete pVar;
        pVar = NULL;

        // 2. Reserva de array con inicialización automática a cero usando ()
        int n = 4;
        int *vecCero = new int[n](); // Los paréntesis () limpian la memoria poniendo ceros
        
        cout << "Array inicializado a cero dinamicamente: ";
        for (int i = 0; i < n; i++) {
            cout << vecCero[i] << " ";
        }
        cout << endl;

        delete[] vecCero;
        vecCero = NULL;
        cout << endl;
    }
}

// ============================================================================
// NUEVO CONCEPTO 4: Control de Errores al Reservar Memoria (std::nothrow)
// ============================================================================
namespace ControlDeErroresRAM {
    void ejecutar() {
        cout << "=== 4. MANEJO DE ERRORES AL RESERVAR MEMORIA (std::nothrow) ===" << endl;

        // Si 'new' se queda sin RAM suficiente, por defecto lanza una excepción.
        // Usando (std::nothrow) devuelve NULL en lugar de romper el programa.
        int *pSeguro = new (std::nothrow) int[1000];

        if (pSeguro == NULL) {
            cout << "Error: No hay suficiente memoria RAM disponible." << endl;
        } else {
            cout << "Memoria reservada con exito usando std::nothrow." << endl;
            delete[] pSeguro;
            pSeguro = NULL;
        }
        cout << endl;
    }
}

// ============================================================================
// NUEVO CONCEPTO 5: Modularización con Funciones (Crear y Destruir Matrices)
// ============================================================================
namespace FuncionesMatrizDinamica {

    // Función auxiliar que abstrae el proceso de creación en 2 etapas
    double** crearMatriz(int filas, int cols) {
        double** M = new double*[filas];
        for (int i = 0; i < filas; i++) {
            M[i] = new double[cols];
        }
        return M;
    }

    // Función auxiliar que abstrae el proceso de liberación en 2 etapas
    void destruirMatriz(double** M, int filas) {
        for (int i = 0; i < filas; i++) {
            delete[] M[i];
        }
        delete[] M;
    }

    void ejecutar() {
        cout << "=== 5. CREACION Y DESTRUCCION DE MATRICES CON FUNCIONES ===" << endl;

        int f = 2, c = 4;
        
        // Creamos la matriz dinámicamente llamando a la función
        double** miMatriz = crearMatriz(f, c);

        // Asignar valores
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < c; j++) {
                miMatriz[i][j] = (i + 1) * 10 + (j + 1);
            }
        }

        // Imprimir valores
        cout << "Matriz (2x4) generada dinamicamente mediante funcion:" << endl;
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < c; j++) {
                cout << miMatriz[i][j] << "\t";
            }
            cout << endl;
        }

        // Liberar la matriz llamando a la función
        destruirMatriz(miMatriz, f);
        miMatriz = NULL;

        cout << endl;
    }
}

// ============================================================================
// PUNTO DE ENTRADA PRINCIPAL
// ============================================================================
int main() {
    VectorDinamico1D::ejecutar();
    MatrizDinamica2D::ejecutar();
    AsignacionEInicializacion::ejecutar();
    ControlDeErroresRAM::ejecutar();
    FuncionesMatrizDinamica::ejecutar();

    cout << "=== GESTION DE MEMORIA DINAMICA CONCLUIDA CON EXITO ===" << endl;
    return 0;
}
