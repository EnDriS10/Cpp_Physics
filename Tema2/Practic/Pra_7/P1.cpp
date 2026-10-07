#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;
// Dimensión global fijada en tiempo de compilación
const int n = 4;

   	double prod(double a[],double b[] ,int n) { 
   		double prod=0; 
   		for ( int i = 0; i<n ; i++){
		prod = prod + a[i]*b[i];
		}    
    return prod; 
    }
    double mod_vect(double a[],int n) { 
   		double mod;
		mod= prod(a,a,n); 
    return mod; 
    }
    void resta_vect(double a[],double b[],double rest[],int n) {
		for (int i=0; i<n; i++) { 
			rest[i]= a[i]-b[i]; 
    	}
	}
	
	void leer_vect(double a[],int n) {  
   		for ( int i = 0; i<n ; i++){
			cout<< " "<< a[i]<< " ";
		}    
    } 
    
// ============================================================================
// 1. METODO ITERATIVO JACOBI
// ============================================================================
    
	void iter_jacobi(double A[n][n], double b[n], double newx[n], int n, double tol) {
		double oldx[n]; double rest[n]; int iter=0;
		for (int i=0; i<=n-1; i++) {   
			oldx[i]= b[i]/ A[i][i]; 
		}
		for (int i=0; i<=n-1; i++) {   
			newx[i]=oldx[i];
		}  
		do {
	
			
			for (int i=0; i<=n-1; i++) {  
				oldx[i]=newx[i];
			} // final bucle i 
			for (int i=0; i<=n-1; i++) {  
				newx[i]=b[i]/ A[i][i]; 
				for (int j=0; j<=n-1; j++) {
				if (j!=i){ 
					newx[i]=newx[i] - (A[i][j]/A[i][i]) * oldx[j];
					}
				} // final bucle j 
			} // final bucle i
		iter++;
 		cout<<"Iteracion " << iter <<": "; leer_vect(newx,n); cout<<endl;
		
 		resta_vect(newx,oldx,rest,n);
 		} while (fabs(mod_vect(rest,n)) > tol); 
	}
	
// ============================================================================
// 2. METODO ITERATIVO GAUSS-SEIDEL
// ============================================================================
    
void iter_gauss_seidel(double A[n][n], double b[n], double newx[n], int n, double tol) {
// La aproximación inicial se almacena en el vector oldx. Sugerencia oldx[i]= b[i]/a[i][i] 
	double oldx[n]; double rest[n]; int iter=0;
	for (int i=0; i<=n-1; i++) {   
		oldx[i]= b[i]/ A[i][i]; 
	}
	for (int i=0; i<=n-1; i++) {   
		newx[i]=oldx[i]; 
	}  
	do { 
		for (int i=0; i<=n-1; i++) {  
			oldx[i]=newx[i]; 
 		} // final bucle i 
		for (int i=0; i<=n-1; i++) {  
			newx[i]=b[i]/A[i][i]; 
			for (int j=0; j<=n-1; j++) { 
				if (j != i) { 
					newx[i]=newx[i] - (A[i][j]/A[i][i])*newx[j];
				}  // ? se utiliza el valor actual 
			} // final bucle j 
 		} // final bucle i
 		iter++;
 		cout<<"Iteracion " << iter <<": "; leer_vect(newx,n); cout<<endl;
		
 		resta_vect(newx,oldx,rest,n);
 	} while (fabs(mod_vect(rest,n)) > tol);
}

int main() {
    cout << fixed << setprecision(6);
    double A[n][n];    double b[n] = {3, -4, 5, -2};    double x[n];
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
	
	cout << "=== Metodo Jacobi ===" << endl;
	iter_jacobi(A,b,x,n,1e-6);
    cout << "=== El resultado con Jacobi de los cojones es ===" << endl;
    for (int i = 1; i <= n ; i++) {
        cout << "x(" << i << ") = " << x[i-1] << endl;
	}
	
	cout << "=== Metodo Gauss & Seidel ===" << endl;
	iter_gauss_seidel(A,b,x,n,1e-6);
    cout << "=== El resultado con Gauss (mi amor) es ===" << endl;
    for (int i = 1; i <= n ; i++) {
        cout << "x(" << i << ") = " << x[i-1] << endl;
	}
    return 0;
}
