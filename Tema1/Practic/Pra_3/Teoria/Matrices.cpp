#include <iostream>

using namespace std;

// ==========================================
// PRIMER CÓDIGO: Ejemplo de Array 1D
// ==========================================
namespace EjemploArray {
    int a[5] = {1, 2, 3, 4, 5}; 
    int result = 0; 

    void ejecutar() {
        cout << "=== EJEMPLO DE ARRAYS ===" << endl; // No requiere instrucción 'return' (o usa simplemente 'return;') Void ejecuta pero no devuelve
        for (int n = 0; n < 5; n++) { 
            result += a[n]; 
        } 
        cout << "Resultado suma: " << result << endl << endl;
    }
}

// ==========================================
// SEGUNDO CÓDIGO: Representación Matricial 2D
// ==========================================
namespace RepresentacionMatricial {
    int n = 3, m = 3, p = 2;   
    int A[3][3] = {2, 3, 8, 2, 2, 4, 2, 2, 6};  // Se introducen por filas 
    int B[3][2] = {{4, 6}, {3, 9}, {1, 8}};  

    void ejecutar() {
        cout << "=== REPRESENTACION MATRICIAL ===" << endl;

        cout << "Matriz A (3x3)" << endl; 
        for (int i = 0; i < n; i++) {   
            cout << "fila " << i << " =  "; 
            for (int j = 0; j < m; j++) { 
                cout << A[i][j] << "  ";
            } 
            cout << endl; 
        } 

        cout << endl;  

        cout << "Matriz B (3x2)" << endl;                    
        for (int i = 0; i < m; i++) {  
            cout << "fila " << i << " =  "; 
            for (int j = 0; j < p; j++) { 
                cout << B[i][j] << "  ";
            } 
            cout << endl;
        } 
    }
}

// ==========================================
// PUNTO DE ENTRADA PRINCIPAL
// ==========================================
int main() {
    // Ejecuta el primer bloque aislado
    EjemploArray::ejecutar();

    // Ejecuta el segundo bloque aislado
    RepresentacionMatricial::ejecutar();

    return 0;
}
