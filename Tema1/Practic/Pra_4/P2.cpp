#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ============================================================================
// FUNCIONES
// ============================================================================
  
    const int fa = 3, ca = 3;
    
	void muestramatriz(double matriz[fa][ca]) { 
        cout << "Matriz:" << endl; 
        for (int i = 0; i < fa; i++) { 
            for (int j = 0; j < ca; j++) {
                cout << matriz[i][j] << " ";
            } 
            cout << endl; 
        } 
    }
    
   void trans(double a[fa][ca]) {
   		double bbsita[fa][ca]; 	
		if (fa==ca){
			for ( int i = 0; i<fa ; i++){
   				for ( int j = 0; j<ca ; j++){
					bbsita[i][j]=a[j][i];
				}
			}
			for ( int i = 0; i<fa ; i++){
   				for ( int j = 0; j<ca ; j++){
					a[i][j]=bbsita[i][j];
				}
			}
		}
		else
			cout<<"No es una matriz cuadrada"<<endl; 
		}
		
    
int main() {
	double a[fa][ca] = {{2, 3, 8}, {2, 2, 4}, {2, 2, 8}};
	
	trans(a);
	muestramatriz(a);
	
	
	return 0;
}
