#include <iostream>
#include <iomanip>
#include<cmath>

using namespace std;

const int n = 8, m=3;// Dimensión global fijada 

void lu_forma2(double A[m][m], double b[m], double x[m], int m) {
    // Resuelve sistema lineal por el metodo LU: Ax=b -> LUx=b -> Lz=b -> Ux=z -> x
    double U[m][m], L[m][m], z[m];
    double sum;
    int k;

    // Inicializar los elementos U y L a cero
    for (int i = 0; i <= m - 1; i++) {
        for (int j = 0; j <= m - 1; j++) {
            U[i][j] = 0.0;
            L[i][j] = 0.0;
        }
    }

    // Pasamos a calcular los elementos distintos de cero
    for (int i = 0; i <= m - 1; i++) { // i barre filas para U y columnas para L
        // Obtencion de una fila de U
        for (int j = i; j <= m - 1; j++) { // j barre los elementos de la fila i
            sum = 0.0;
            for (k = 0; k <= i - 1; k++) {
                sum = sum + L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - sum;
        }

        // Obtencion de una columna de L
        for (int j = i; j <= m - 1; j++) { // j barre los elementos de la columna i
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
    for (int i = 0; i <= m - 1; i++) {
        sum = 0.0;
        for (int j = 0; j <= i - 1; j++) {
            sum = sum + L[i][j] * z[j];
        }
        z[i] = b[i] - sum;
    }

    // Obtener x <- Ux=z (Sustitución regresiva)
    for (int i = m - 1; i >= 0; i--) {
        sum = 0.0;
        for (int j = i + 1; j <= n - 1; j++) {
            sum = sum + U[i][j] * x[j];
        }
        x[i] = (z[i] - sum) / U[i][i];
    }
}


void inv_landa(double Land[] , double inv[], int n){
	for (int i = 0; i < n; i++) {
        inv[i] = 1/(Land[i]);
    }
}


// ============================================================================
// MAIN DE PRUEBA
// ============================================================================
int main() {
    cout << scientific << setprecision(5);

    // Sistema A * x = b de prueba
    double Land[n] = { 6563, 6439, 5890, 5338, 5086, 4861, 4340, 3988};
	double N_[n] = {1.50883 ,1.50917 ,1.51124 ,1.51386 ,1.51534 , 1.51690, 1.52136, 1.52546 };
	int ind[m] = {2,4,7};
	double A[m][m]; double Land_inv[n];		inv_landa(Land,Land_inv,n);
	double b[m]; double x[m];char a[m]= {'A','B','C'} ;
	
	// Rellenar y mostrar la matriz
   for (int i = 0; i < m; i++) {
	int k = 0;
   		for (int j = 0; j < m; j++) {  
            A[i][j] = pow( Land_inv[ ind[i] ] ,k);            
			k=k+2;
            //cout << A[i][j] << "  ";
 		}
 	//cout << endl;
   } 
	for (int i = 0; i < m; i++) {b[i]=N_[ ind[i] ];}
	
	lu_forma2(A, b, x, m);
    cout << "===  LU FORMA 2 (Alternando fila U y columna L) ===" << endl;
    for (int i = 0; i < m; i++) {
        cout << a[i] << " = " << x[i] << endl;
    }

    return 0;
}
