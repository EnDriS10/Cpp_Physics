#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ============================================================================
// FUNCIONES
// ============================================================================
   double sum_cuad(double a[], int n) { 
   		double Sum=0; 
   		for ( int i = 0; i<n ; i++){
		Sum = Sum + a[i]*a[i];
		}    
        return Sum; 
    }
    
       double sum_inv(double a[], int n) { 
   		double Sum=0; 
   		for ( int i = 0; i<n ; i++){
		Sum = Sum + ( 1/a[i] );
		}    
        return Sum; 
    }

   double media_c(double a[], int n) {
   		double mc;   
        mc = sqrt( (sum_cuad(a,n)) / (n) );  
        return mc; 
    } 
    
   double media_a(double a[], int n) {
   		double ma;   
        ma = n/sum_inv(a,n);  
        return ma;   
    } 


int main() {
	const int MAX = 100; // Tamaño máximo predefinido para 'a'
    double a[MAX];       // Array estático
    double *A;           // Puntero dinámico
    int n; 

    cout << "Introduce el valor de n (max 100): "; 
    cin >> n; 

    // 1. Reserva dinámica
    A = new double[n]; 

    // 2. Llenamos el array dinámico A
    for (int i = 0; i < n; i++) {
        cout << "Introduce el valor " << i + 1 << " de a: "; 
        cin >> A[i];
		a[i] = A[i]; 
    } 

    // 4. Liberamos A (a conserva su propia copia de los datos)
    delete [] A; 		A = NULL; // Evita que 'A' quede como puntero colgado

//    // Comprobación de que 'a' conserva los datos
//    cout << "\nDatos almacenados en 'a' tras borrar A:" << endl;
//    for (int i = 0; i < n; i++) {
//        cout << "a[" << i << "] = " << a[i] << endl;
//    }	

	cout << "La Media Cuadratica de a es " << media_c(a,n) << endl;
	cout << "La Media Armonica de a es " << media_a(a,n) << endl;
	
	return 0;
}
