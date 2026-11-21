
#include <iostream>
#include <cmath>
#include <fstream>
#include "librerias.cpp"
using namespace std;
void jacobi (double **A, double **U, double *L, int d);
void ordena(double *L, int n);

int main()
{
int n;
cout << "Introduce dimension de la matriz simetrica " << endl;
cin >> n;
double **A, **U;
double *L=new double[n];
// reserva memoria dinamica para A y U.
A=crearmatriz(A,n,n);
U=crearmatriz(U,n,n);
// Construimos las matrices M y K. Primero las relleno de ceros
for (int i=0; i<n;i++){
	for (int j=0; j<n; j++){A[i][j]=0;
	}
}
for (int i=0 ; i<=n-1 ; i++){A[i][i] = 2.0;}
A[0][0]=1;
A[n-1][n-1]=1;
for (int i=0 ; i<n-1 ; i++){
A[i][i+1] = -1.0;
A[i+1][i] = -1.0;
}
A[0][1]=0;
A[1][0]=0;
A[n-2][n-1]=0;
A[n-1][n-2]=0;
muestramatriz(A,n,n);
system("PAUSE");
jacobi(A,U,L,n);
// En L estan los autovalores y en U los autovectores     
cout << "Autovalores" << endl;
muestravector(L,n);
ordena(L,n);
cout << "Frecuencias ordenadas" << endl;
for (int i=0; i<=n-1; i++){cout << sqrt(L[i])<< "   ";}
cout << endl;
//cout << "Matriz A" << endl;
//muestramatriz(A,n,n);
//cout << endl << "Matriz U" << endl;
//muestramatriz(U,n,n);
return 0;
}

void jacobi (double **A, double **U, double *L, int d)
{
double theta, si, co, uki, aii, maxoffdiag, tolerancia=1e-10;
ofstream fsalida("Traza.dat", ios::out);
if (!fsalida) {cout << "No se puede abrir el archivo";}	
int i, j, iter=0;
// matriz U -> I
for (int i=0; i <d ;i++) {
    for (int j=0; j<d; j++)
    { if (i==j) { U[i][j]=1.0;}
      else { U[i][j]=0.0;}
    }
    }
do 
{
// Buscamos el elemento maximo por encima de la diagonal
maxoffdiag=fabs(A[0][1]), i=0, j=1;
for (int ib=0; ib < d ;ib++) {
    for (int jb=ib+1; jb < d; jb++)
    { if (fabs(A[ib][jb]) > maxoffdiag) 
      { maxoffdiag=fabs(A[ib][jb]), i=ib, j=jb;}
      }
     }
// llevamos a cabo la rotacion Rij
if (fabs(A[i][i]-A[j][j]) < tolerancia*fabs(A[i][i]))
   { theta = atan(1.0);}   // pi/4
else
   { theta = 0.5*atan(2.0*A[i][j]/(A[i][i]-A[j][j]));}
// cout << iter << "  " << theta << endl;

si=sin(theta);
co=cos(theta);
for (int k=0; k<d; k++)
{ 
uki=U[k][i];
U[k][i]=uki*co + U[k][j]*si;
U[k][j]=-uki*si + U[k][j]*co;
if (k!=i && k!=j)
{
 A[k][i]=A[i][k]*co + A[j][k]*si;
 A[k][j]=-A[i][k]*si + A[j][k]*co;
 A[j][k]=A[k][j];
 A[i][k]=A[k][i];
}
}  // cerramos bucle for en k
aii=A[i][i];
A[i][i]=aii*pow(co,2.0) + A[j][j]*pow(si,2.0) + 2.0*A[i][j]*si*co;    
A[j][j]=aii*pow(si,2.0) + A[j][j]*pow(co,2.0) - 2.0*A[i][j]*si*co;    
A[i][j]=0.0; // Se impone que sea cero despues de la rotacion
A[j][i]=0.0; // Se impone que sea cero despues de la rotacion
iter=iter+1;
// calculo de la traza
double traza=0;
for (int i=0; i<d; i++)   { traza=traza+A[i][i];} 
if (iter%100==0) {
cout << iter << "  " << traza << endl; 
fsalida << iter << "  " << traza << endl; 	
}

} while (fabs(maxoffdiag) > tolerancia);     
/* al final U es la matriz producto de todos las rotaciones y sus columnas 
seran los autovectores, y los elementos diagonales de A son los autovalores que
pasamos al vector L */
cout << endl << "Numero de iteraciones=" << iter << endl << endl;
for (int k=0; k < d; k++) { L[k]=A[k][k];}
fsalida.close();
}

void ordena(double *datos, int n)
{
double temp;
for (int i=0; i<n-1;i++) {
    for (int j=0; j<n-1-i; j++) {
        if (datos[j]>datos[j+1]) {
           // intercambio
           temp=datos[j];
           datos[j]=datos[j+1];
           datos[j+1]=temp;
           }
    }
}
}






