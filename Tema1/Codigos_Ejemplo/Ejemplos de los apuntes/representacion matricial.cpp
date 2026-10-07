//Representacion matricial 
#include <iostream>
using namespace std;
int main() {
int n=3, m=3, p=2;  
int A[3][3]={2,3,8,2,2,4,2,2,6};  // Se introducen por filas.
int B[3][2]={{4,6},{3,9},{1,8}}; 
cout << "Matriz A (3x3)" << endl;
for (int i=0; i<n; i++){  
	cout << "fila " << i << "=  ";
	for (int j=0; j<m; j++) { cout << A[i][j] << "  ";}
	cout << endl; }
cout << endl << endl; 
cout << "Matriz B (3x2)" << endl;                    
for (int i=0; i<m; i++){ 
	cout << "fila " << i << "=  ";
	for (int j=0; j<p; j++) { cout << B[i][j] << "  ";}
	cout << endl;}
return 0;
	}

