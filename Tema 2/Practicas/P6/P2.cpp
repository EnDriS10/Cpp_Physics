#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

// Dimensión global fijada en tiempo de compilación
const int n = 5;


// ============================================================================
// 2. METODO LU GENERAL - FORMA 2 (Alterna una fila de U y una columna de L)
// ============================================================================
void lu_forma2(double A[n][n], double b[n], double x[n], int n) {
    // Resuelve sistema lineal por el metodo LU: Ax=b -> LUx=b -> Lz=b -> Ux=z -> x
    double U[n][n], L[n][n], z[n];
    double sum;
    int k;

    // Inicializar los elementos U y L a cero
    for (int i = 0; i <= n - 1; i++) {
        for (int j = 0; j <= n - 1; j++) {
            U[i][j] = 0.0;
            L[i][j] = 0.0;
        }
    }

    // Pasamos a calcular los elementos distintos de cero
    for (int i = 0; i <= n - 1; i++) { // i barre filas para U y columnas para L
        // Obtencion de una fila de U
        for (int j = i; j <= n - 1; j++) { // j barre los elementos de la fila i
            sum = 0.0;
            for (k = 0; k <= i - 1; k++) {
                sum = sum + L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }

        // Obtencion de una columna de L
        for (int j = i; j <= n - 1; j++) { // j barre los elementos de la columna i
            if (j == i) {
                L[j][i] = 1.0; // Hacemos uno los elementos de la diagonal de L
            } else {
                sum = 0.0;
                for (k = 0; k <= i - 1; k++) {
                    sum = sum + L[j][k] * U[k][i];
                }
                L[j][i] = (A[j][i] - sum) / U[i][i];
            }
        }
    }

    // Obtener z <- Lz=b (Sustitución progresiva)
    for (int i = 0; i <= n - 1; i++) {
        sum = 0.0;
        for (int j = 0; j <= i - 1; j++) {
            sum = sum + L[i][j] * z[j];
        }
        z[i] = b[i] - sum;
    }

    // Obtener x <- Ux=z (Sustitución regresiva)
    for (int i = n - 1; i >= 0; i--) {
        sum = 0.0;
        for (int j = i + 1; j <= n - 1; j++) {
            sum = sum + U[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / U[i][i];
    }
}

int main() {
    cout << fixed << setprecision(6);
    double A[n][n];    double b[n] = {14, -10, 4, 6, 12};    double x[n];
	char archivo_entrada[30]; 
	cout << "Introduzca nombre del archivo de entrada: "; 
	cin >> archivo_entrada; 
	// Crear un flujo de entrada y llamarlo fentrada 
	ifstream fentrada(archivo_entrada, ios::in); 
	for (int i=0; i<n; i++){ 
  		for (int j=0; j<n; j++){   
			fentrada >> A[i][j];
		} 
		} 
	fentrada.close(); // cerrar el archivo 

    lu_forma2(A, b, x, n);
    cout << "=== El resultado es ===" << endl;
    for (int i = 0; i <= n - 1; i++) {
        cout << "x(" << i << ") = " << x[i] << endl;
    }

    return 0;
}
