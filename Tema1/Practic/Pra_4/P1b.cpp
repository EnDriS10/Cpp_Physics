#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ============================================================================
// FUNCIONES
// ============================================================================
  
    void Array() {
        cout << "=== 1. VECTORES UNIDIMENSIONALES DINAMICOS ===" << endl;

    	double *A;
    	int n;
    	
    	cout << "Introduzca dimension del array" << endl;
    	cin >> n;

        // Reserva dinámica de memoria para n enteros
        A = new double[n]; 

        // Rellenado e impresión del vector[cite: 6]
        cout << "Valores generados en el vector A[" << n << "]:" << endl;
        for (int i = 0; i < n; i++) { 
            A[i] = (i * i + 1); 
            cout << "A[" << i << "] = " << A[i] << endl; 
        } 

        // Liberación de la memoria reservada
        delete[] A;		A = NULL; 
    }
    
        void Matriz() {
        cout << "=== 2. MATRICES BIDIMENSIONALES DINAMICAS (double**) ===" << endl;
		
		double **A; // Declaración como puntero a puntero
    	int fa; int ca;
		
		cout << "Introduzca el numero de filas de la matriz" << endl;
    	cin >> fa;
    	cout << "Introduzca el numero de columnas de la matriz" << endl;
    	cin >> ca;


        // ETAPA (a): Reserva del array de punteros que apunten a cada fila
        A = new double*[fa]; 

        // ETAPA (b): Reserva de los elementos de cada una de las filas
        for (int i = 0; i < fa; i++) { 
            A[i] = new double[ca]; 
        } 

        // Rellenar y mostrar la matriz
        cout << "Matriz A (" << fa << "x" << ca << "):" << endl;
        for (int i = 0; i < fa; i++) {  
            for (int j = 0; j < ca; j++) { 
                A[i][j] = 2 * i + 3 * j; 
                cout << A[i][j] << "\t";
            } 
            cout << endl;
        }  


        // LIBERACIÓN DE MEMORIA EN DOS ETAPAS (A la inversa)
        for (int i = 0; i < fa; i++) { 
            delete[] A[i];       // 1. Liberar los elementos de cada fila
        } 
        delete[] A; 	A = NULL; // 2. Liberar el array de punteros principal

        cout << endl;
    }
    
int main() {
	
	Array();
	Matriz();
	
	return 0;
}
