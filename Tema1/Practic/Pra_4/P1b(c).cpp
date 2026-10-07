#include <iostream>     
using namespace std;
  	
  	void fil_col(int &f, int &c, char x);
  	double** crearMatriz(int filas, int cols);
  	void leermatriz (double **M, int f, int c, char x); 
  	void muestramatriz(double **M, int f, int c,char x);
	void multmat(double **A, double **B, double **C, int fa, int ca, int cb); 
	void borrarmatriz(double **M, int f);
	 

int main() {  
	int fa, fb, ca, cb;
	char a = 'A'; char b='B'; char c='C';
	double **A, **B, **C;  

	fil_col(fa,ca,a);		A= crearMatriz(fa,ca);		leermatriz (A, fa, ca, a);		muestramatriz(A,fa,ca,a); 
	fil_col(fb,cb,b);		B= crearMatriz(fb,cb);		leermatriz (B, fb, cb, c); 		muestramatriz(B,fb,cb,b); 		
	
	int fc=fa, cc=cb;		C= crearMatriz(fc,cc);		multmat(A,B,C,fa,ca,cb); 		muestramatriz(C,fc,cc,c);
	 
	// liberamos la memoria ocupada por A, B y C 
	borrarmatriz(A,fa); 	borrarmatriz(B,fb); 	borrarmatriz(C,fc); 
return 0; 
} 


void fil_col(int &f, int &c, char x) {
	cout << " Introduzca numero de filas de "<< x <<": "<<endl; 
	cin >> f; 
	cout << " Introduzca numero de columnas de "<< x <<": "<<endl; 
	cin >> c; 
}
double** crearMatriz(int filas, int cols) {
    double** M = new double*[filas];
    for (int i = 0; i < filas; i++) {
        M[i] = new double[cols];
    }
    return M;
}

void  leermatriz (double **M, int f, int c, char x) {  
	int i, j; 
	for( i = 0; i < f; i++){ 
		for (j = 0; j < c; j++){  
			cout << "INTRODUCE ELEMENTO ["<<i<<"]"<<"["<<j<<"] a la matriz Matriz "<< x<< endl; 
			cin >> M[i][j] ; 
		} 
	}	  
} 

void muestramatriz( double **M, int f, int c, char x) {
	cout << "LA MATRIZ "<< x <<"("<<f<<"x"<<c<<") es "<< endl;
	for (int i=0; i<f; i++) { 
		for (int j=0; j<c; j++) { 
		cout << M[i][j] << " "; 
		}	 
	cout << endl;  
	}
	cout << endl; 
} 

void multmat(double **A, double **B, double **C, int fa, int ca, int cb){ 
	double suma; 
	for (int i=0; i<fa; i++) { 
		for (int j=0; j<cb; j++) { 
			suma=0.0; 
			for (int k=0; k<ca; k++) { 
				suma=suma+A[i][k]*B[k][j]; 
			} 
			C[i][j]=suma; 
		} 
	} 
} 
   

void borrarmatriz(double **M, int f) { // libera memoria  
	for (int i=0; i < f; i++) { 
		delete[] M[i]; 
	} 
	delete [] M; 
}
