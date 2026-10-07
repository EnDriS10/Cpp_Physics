#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ============================================================================
// FUNCIONES
// ============================================================================
  
    const int fa = 3, ca = 3,fb = fa, cb = 2; 
    
	void muestramatriz(double matriz[fa][cb]) { 
        cout << "Matriz:" << endl; 
        for (int i = 0; i < fa; i++) { 
            for (int j = 0; j < cb; j++) {
                cout << matriz[i][j] << " ";
            } 
            cout << endl; 
        } 
    }

   double prod_vec(double a[],double b[] ,int n) { 
   		double prod=0; 
   		for ( int i = 0; i<n ; i++){
		prod = prod + a[i]*b[i];
		}    
        return prod; 
    }
    
   void prod(double a[fa][ca],double b[fb][cb], double resul[fa][cb]) { 
   		double vector[fb];
		if (ca==fb){ 		
   			for ( int i = 0; i<cb ; i++){
   				for ( int j = 0; j<fb ; j++){
				vector[j]=b[j][i];
				}
			for ( int k = 0; k<fa ; k++) {
				resul[k][i] =prod_vec(a[k],vector,ca);
				}
			}
		}
		else{
			cout<<"Error de indexacion"<<endl;
		}   
    }
    
int main() {
	double a[fa][ca] = {{2, 3, 8}, {2, 2, 4}, {2, 2, 8}}; double b[fb][cb] = {{4, 6}, {3, 9}, {1, 8}} ;
	double c[fa][cb];
	
	prod(a,b,c);
	muestramatriz(c);
	
	
	return 0;
}
