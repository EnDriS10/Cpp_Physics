#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
const int natomos=5;
void jacobi (double **A, double **U, double *L, int d);
double** crearmatriz(double **M, int f, int c);
void muestramatriz( double **M, int f, int c);
void muestravector(double v[], int d);

int main()
{

// masas y posiciones de los atomos de la molecula de metano donde hemos sustituido un átomo de hidrógeno por uno de Si
double m[natomos] = {12.000, 1.000, 1.000, 1.000, 28.000};   
double x[natomos]= {0.000, 0.635,-0.635,-0.635, 0.635};     
double y[natomos] = {0.000, 0.635,-0.635, 0.635,-0.635};
double z[natomos] = {0.000, 0.635, 0.635,-0.635,-0.635};
int n=3;  
double **I, **U;
I=crearmatriz(I,n,n);
U=crearmatriz(U,n,n);
double *L=new double[n];
double xCM=0, yCM=0, zCM=0, mCM=0;
// calculamos el CM de la molecula.
for (int i=0; i<natomos; i++) {
      mCM += m[i];
      xCM += m[i] * x[i];
      yCM += m[i] * y[i];
      zCM += m[i] * z[i];
   }
xCM /= mCM; 
yCM /= mCM; 
zCM /= mCM;
cout << "Centro de masas :";
cout << xCM << "  " << yCM << "   " << zCM << endl<<endl; 

// situamos la molecula en el sistema del CM
for (int i=0; i<natomos; i++) {
      x[i] -= xCM; 
	  y[i] -= yCM; 
	  z[i] -= zCM;
   }
cout << "Posiciones de los atomos en el sistema CM :" << endl; 
cout << "coordenadas x :" << endl; 
muestravector(x,natomos);
cout << "coordenadas y :" << endl;
muestravector(y,natomos);
cout << "coordenadas z :" << endl;
muestravector(z,natomos);

// Construimos la matriz I en el sistema del CM
for (int i=0; i<n; i++){
      for (int j=0; j<n; j++){I[i][j]=0;}
	  }
// construimos el tensor de inercia
for (int i=0; i<natomos; i++) {
      I[0][0] = I[0][0] + m[i]*(y[i]*y[i]+z[i]*z[i]); //Ixx 
      I[1][1] = I[1][1] + m[i]*(x[i]*x[i]+z[i]*z[i]); //Iyy
      I[2][2] = I[2][2] + m[i]*(x[i]*x[i]+y[i]*y[i]);  //Izz
      I[1][0] = I[1][0] - m[i]*x[i]*y[i]; //Ixy=Iyx
      I[2][0] = I[2][0] - m[i]*x[i]*z[i]; //Ixz=Izx
      I[2][1] = I[2][1] - m[i]*y[i]*z[i]; // Iyz=Izy
      }
	I[0][1]=I[1][0];
	I[0][2]=I[2][0];
	I[1][2]=I[2][1];
cout << "Tensor de inercia en el sistema CM: " << endl; 
muestramatriz(I,n,n);

jacobi(I,U,L,n);
// En L estan los autovalores y en U los autovectores     
cout << "Autovalores:" << endl;
muestravector(L,n);
cout << "Matriz I diagonalizada:" << endl;
muestramatriz(I,n,n);
cout << endl << "Matriz de autovectores:" << endl;
muestramatriz(U,n,n);
// rotamos la molecula al sistema de los ejes principales
double xi, yi, zi;
for (int i=0; i<natomos; i++) {                  
      xi = x[i], yi = y[i], zi = z[i];
      x[i] = U[0][0] * xi + U[1][0] * yi + U[2][0] * zi;
      y[i] = U[0][1] * xi + U[1][1] * yi + U[2][1] * zi;
      z[i] = U[0][2] * xi + U[1][2] * yi + U[2][2] * zi;
      }
cout << endl << "Posiciones de los atomos en el sistema CM utilizando los ejes principales :" << endl<< endl; 
cout << "coordenadas x :" << endl; 
muestravector(x,natomos);
cout << "coordenadas y :" << endl;
muestravector(y,natomos);
cout << "coordenadas z :" << endl;
muestravector(z,natomos);


return 0;
}

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
void jacobi (double **A, double **U, double *L, int d)
{
double theta, si, co, uki, aii, maxoffdiag, tolerancia=1e-10;
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

} while (fabs(maxoffdiag) > tolerancia);     
/* al final U es la matriz producto de todos las rotaciones y sus columnas 
seran los autovectores, y los elementos diagonales de A son los autovalores que
pasamos al vector L */
cout << endl << "Numero de iteraciones=" << iter << endl << endl;
for (int k=0; k < d; k++) { L[k]=A[k][k];}
}





