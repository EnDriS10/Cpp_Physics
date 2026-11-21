#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

double** crearmatriz(double **M, int f, int c)
{
/* en el programa principal si queremos crear (reservar memoria) para la matriz B. 
   double **B;
   B=crearmatriz(B,fb,cb);
   donde fb es el numero de filas de B y cb el numero de columnas de B
*/
     M = new double * [f];
     for (int i = 0; i < f; i++) { M[i] = new double[c];}
     return M;
}

void borrarmatriz(double **M, int f)
/* libera la memoria de la matriz pasada en la llamada. Por ejemplo una matriz B.
borrarmatriz(B, fb);
con fb el nÃºmero de filas de B.
*/
{
for (int i=0; i < f; i++) {
    delete[] M[i];
    }
    delete [] M;
}

double** multmat(double **A, double **B, int fa, int ca, int cb)
/* Multiplica la matriz A x B. La matriz producto es devuelta como un puntero doble al programa principal 
que ha hecho la llamada.
En el programa principal:
double **C;
C=multmat(A,B,fa,ca,cb); 
con C la matriz producto, fa: numero de filas de A, ca: numero de columnas de A, y cb: numero de columnas de B
*/
{
     double suma;
     double **Producto;
     Producto=crearmatriz(Producto,fa,cb);
for (int i=0; i<fa; i++) {
    for (int j=0; j<cb; j++) {
        suma=0.0;
        for (int k=0; k<ca; k++) {
            suma=suma+A[i][k]*B[k][j];
            }
        Producto[i][j]=suma;
     }
 }
 return Producto;
}

double**  leermatriz (int f, int c)
{ 
/* 
En el programa principal:
double **A;
A=crearmatriz(A,fa,ca);
A=leermatriz(fa,ca);
con fa el numero de filas de A y ca el numero de columnas de A
*/

double **M;
M=crearmatriz(M,f,c);
    int i, j;
    for( i = 0; i < f; i++){
        for (j = 0; j < c; j++){
          cout << "INTRODUCE ELEMENTO ["<<i<<"]"<<"["<<j<<"]"<< endl;
          cin >> M[i][j] ;
          }
     } 
return M;
} 
  
void muestramatriz( double **M, int f, int c)
{
for (int i=0; i<f; i++) {
    for (int j=0; j<c; j++) {
    cout << M[i][j] << " ";
     }
     cout << endl;
 }
}

void muestravector(double v[], int d)
{
for (int k=0; k < d; k++)
{ cout << v[k] << endl; }
  cout << endl;
}

double** transpuesta(double **A, int fa, int ca)
{
/* calcula la transpuesta de una matriz.
En el programa principal para calcular la transpuesta de una matriz B:
double **BTrans;
Btrans=crearmatriz(Btrans,fbtrans,cbtrans);
Btrans=transpuesta(B,fb,cb);
con fbtrans=cb y cbtrans=fb, fb el numero de filas de B y cb el numero de columnas de B
*/

  double aux;
  double **AT;
  AT=crearmatriz(AT,ca,fa);
  
  for (int i = 0; i < fa; i++){
      for (int j = 0; j < ca; j++)
      {AT[j][i]=A[i][j]; }}
	return AT;
}

double** copiarmatriz (double **M, int f, int c)
{
  /*Para hacrer una copia de la matriz B en el programa principal.
  	double **Bcopia;
	Bcopia=crearmatriz(Bcopia,fb,cb);
	Bcopia=copiarmatriz(fb,cb);
	con fb el numero de filas de b y cb el numero de columnas de b
  */
   double **Mcopia;
   Mcopia=crearmatriz(Mcopia,f,c);
	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++)
			{Mcopia[i][j] = M[i][j];}}
	return Mcopia;
}


int numerodepuntos(char nombrearchivo[]) 
{
int m=0;
// Detecta el numero de puntos de un fichero de datos con dos columnas x y
double x, y;    
// Crear un flujo de entrada y llamarlo fentrada
ifstream fentrada(nombrearchivo, ios::in);
if (!fentrada)  
{ cout << "ERROR. No se puede leer el archivo." << endl;
  system ("PAUSE");
  return -1;  }
                
  while (!fentrada.eof())   // utilizacion de eof
    {
    fentrada >> x >> y;
    m=m+1;
    }
    fentrada.close();  // cerrar el archivo
    return m;
}

void leerdatos(char nombrearchivo[], double x[], double y[], int m) 
{
// Crear un flujo de entrada y llamarlo fentrada
// lee un fichero de datos con dos columnas x y
ifstream fentrada(nombrearchivo, ios::in);
for (int i=0;i<=m-1;i++) {   fentrada >> x[i] >> y[i];     }
fentrada.close(); // cerrar el archivo
}

void grabardatos(char nombrearchivo[], double x[], double y[], int m)
{
// Crear un flujo de salida y llamarlo fsalida
// Graba un fichero de datos con dos columnas x y
ofstream fsalida (nombrearchivo, ios::out);
for (int i=0; i<m-1; i++){ fsalida << x[i] << "   " << y[i] << endl;   }
fsalida << x[m-1] << "   " << y[m-1];
fsalida.close(); // cerrar el archivo 
}
 

double** inversa (double **a, int n) {
/* Calcula la inversa de la matriz pasada como argumento en la llamada de la funcion
	En el programa principal, para calcular la inversa de una matriz cuadrada (nxn) B
	double **Binv;
	Binv=crearmatriz(Binv,fb,fb);
	Binv=inversa(B,n);
*/
double **ainv;
ainv=crearmatriz(ainv,n,n);
// Algoritmo para la eliminación simple de Gauss
 int i, j, k;
 double factor;
 double **L, *D, *X;
 X = new double [n]; D = new double [n];
 L = new double* [n];
 for (j = 0; j < n; j++) 
  L[j] = new double [n];
 for (k = 0; k < n - 1; k++) {
  for (i = k+1; i < n;  i++) {
   factor = a[i][k]/a[k][k]; 
   for (j = k+1; j < n + 1; j++) {
    a[i][j] = a[i][j] - factor * a[k][j];
   }
  }
 }
 
// Cálculo del determinante
 double determ = 1.;
 for (i = 0; i < n; i++) {
  determ = determ * a[i][i];
 }
// Rutina para determinar las matrices  L (inferior)
//  y U (superior) de ladescomposición LU
  for (i = 0; i < n; i++) {
   for (j = 0; j < n; j++) {
    if (i > j) {
     L[i][j] = a[i][j]/a[j][j];
     a[i][j] = 0;
    }
   }
  }
  for (i = 0; i < n; i++) {
   for (j = 0; j < n; j++) {
    L[j][j] = 1;
   }
  }
// cálculo de la inversa
 for (k = 0; k < n; k++) {
// Esta rutina inicializa los L[i][n] 
  for (i = 0; i < n; i++) {
   if (i == k) L[i][n] = 1;
    else  L[i][n] = 0;
  }
// Esta función implementa la sustitución hacia adelante con
// los L[i][n] que produce la rutina anterior
  double sum;
  D[0] = L[0][n];
  for (i = 1; i < n; i++) {
   sum = 0;
   for (j = 0; j < i; j++) {
    sum = sum + L[i][j]*D[j];
   }
   D[i] = L[i][n] - sum;
  }
// Esta rutina asigna los D[i] que produce forward para
// ser utilizados con la matriz U
  for (i = 0; i < n; i++) {
   a[i][n] = D[i];
  }
// Rutina que aplica la sustitución hacia atras
 X[n-1] = a[n-1][n]/a[n-1][n-1];
// Determinación de las raíces restantes
  for (i = n - 2; i > -1; i--) {
   sum = 0;
   for (j = i+1; j < n; j++) {
    sum = sum + a[i][j]*X[j];
   }
   X[i] = (a[i][n] - sum)/a[i][i];
  }
// Esta rutina asigna los X[i] que produce Sustituir
// como los elementos de la matriz inversa
  for (i = 0; i < n; i++) {
   ainv[i][k] = X[i];
  }
 }   // llave de cierre del for para k
 return ainv;
}

