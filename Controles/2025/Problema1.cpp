#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;
const int n=2;
const double k1=10, D=1, L1=1, L2=1, m=0.1, g=9.81;
double k2;
int contador=0;
double tolerancia=1e-10, sumafs;
void lu(double A[n][n], double b[n], double x[n], int n);
double f1 (double x[n]), f2 (double x[n]);
double f1x (double x[n]), f1y (double x[n]);
double f2x (double x[n]), f2y (double x[n]);
double norma (double x[n], int n);
double derivada(double (*funcion)(double x[n]), int j, double x[n]);


int main(){
  double J[n][n], F[n], dx[n];
  // valores iniciales de partida
  double (*Af[n]) (double x[n])={f1,f2};
  double (*AfD[n][n]) (double x[n])={f1x,f1y,f2x,f2y};
  double xold[n],xnew[n];
  // arrays de punteros a funciones que retornan reales
  cout << setprecision(15);
  
  ofstream fsalida("resultados.dat");
  
  for (k2=0; k2<=20; k2++)
{
	contador=0;
	xold[0]=2, xold[1]=-2, xnew[0]=2, xnew[1]=-2;
do {
   for(int i=0;i<=n-1;i++){
    xold[i]=xnew[i];
   }    
   // construimos -F
   for (int i=0; i<=n-1; i++) {
       F[i]=-Af[i](xold);
   }
   // construimos la matriz jacobiana, J
   for (int i=0; i<=n-1; i++) {
       for (int j=0; j<=n-1; j++) {
            J[i][j]=AfD[i][j] (xold);
            // J[i][j]=derivada(Af[i], j, xold);
            }
   }
  // resolvemos el sistema J·dx=F
  lu(J,F,dx,n); 
  contador=contador+1; 
  sumafs=0.0;     
  // cout << "Iteracion " << contador << endl;
  for(int i=0;i<=n-1;i++){
    xnew[i]=xold[i]+dx[i];
    sumafs=sumafs+Af[i](xnew);
  }        
   }
while (fabs(norma(xnew,n)-norma(xold,n))> tolerancia);
// while (fabs(sumafs) > tolerancia);  
cout << "k2=" << k2 << "    xe=" << xnew[0] << "  ye=" << xnew[1] << endl;
fsalida << "k2=" << k2 << "    xe=" << xnew[0] << "  ye=" << xnew[1] << endl;
}

fsalida.close();
         
  return 0;
}

double derivada(double (*f)(double x[n]), int j, double x[n])
       {
       double h[n], xh[n],ratio;     
       for (int k=0; k<=n-1; k++){
           if (k==j) {h[k]=0.0001*x[k];}    // cuidado si x[k]=0
           else {h[k]=0.0;}
           xh[k]=x[k]+h[k];
       }
     ratio=(f(xh)-f(x))/h[j];
     return ratio;
}


double f1 (double x[n])
{
double raiz1=sqrt(x[0]*x[0]+x[1]*x[1]);
double raiz2=sqrt((x[0]-D)*(x[0]-D)+x[1]*x[1]);
return (-k1*x[0]*(1-L1/raiz1)-k2*(x[0]-D)*(1-L2/raiz2));}

double f2 (double x[n])
{
double raiz1=sqrt(x[0]*x[0]+x[1]*x[1]);
double raiz2=sqrt((x[0]-D)*(x[0]-D)+x[1]*x[1]);
return (-k1*x[1]*(1-L1/raiz1)-k2*x[1]*(1-L2/raiz2)+m*g);}

double f1x (double x[n])
{
double raiz1=sqrt(x[0]*x[0]+x[1]*x[1]);
double raiz2=sqrt((x[0]-D)*(x[0]-D)+x[1]*x[1]);
double raiz3=pow(x[0]*x[0]+x[1]*x[1],-1.5);
double raiz4=pow((x[0]-D)*(x[0]-D)+x[1]*x[1],-1.5);	
return (-k1*(1-L1/raiz1+L1*x[0]*x[0]*raiz3)-k2*(1-L2/raiz2+L2*(x[0]-D)*(x[0]-D)*raiz4));}

double f1y (double x[n])
{
double raiz3=pow(x[0]*x[0]+x[1]*x[1],-1.5);
double raiz4=pow((x[0]-D)*(x[0]-D)+x[1]*x[1],-1.5);
return (-k1*x[0]*x[1]*L1*raiz3-k2*(x[0]-D)*x[1]*L2*raiz4);}

double f2x (double x[n])
{
double raiz3=pow(x[0]*x[0]+x[1]*x[1],-1.5);
double raiz4=pow((x[0]-D)*(x[0]-D)+x[1]*x[1],-1.5);
return (-k1*x[0]*x[1]*L1*raiz3-k2*(x[0]-D)*x[1]*L2*raiz4);}

double f2y (double x[n])
{
double raiz1=sqrt(x[0]*x[0]+x[1]*x[1]);
double raiz2=sqrt((x[0]-D)*(x[0]-D)+x[1]*x[1]);
double raiz3=pow(x[0]*x[0]+x[1]*x[1],-1.5);
double raiz4=pow((x[0]-D)*(x[0]-D)+x[1]*x[1],-1.5);	
return (-k1*(1-L1/raiz1+L1*x[1]*x[1]*raiz3)-k2*(1-L2/raiz2+L2*x[1]*x[1]*raiz4));}

double norma (double x[n], int n)
{
       double suma=0.0;
       for (int i=0; i<=n-1; i++){
           suma=suma+x[i]*x[i];
       }
return (sqrt(suma));
}
               

void lu(double A[n][n],double b[n],double x[n], int n)
{
//Resuelve ecuacion algebraica lineal por el metodo LU
//Ax=b --> LUx=b --> Lz=b --> Ux=z --> x

  double U[n][n],L[n][n],z[n];
  double sum;
  int i,j,k;

 //Obtener L y U
  for(i=0;i<=n-1;i++){
    for(j=0;j<=n-1;j++){
      if(i<=j){
        sum=0.0;
        for(k=0;k<=i-1;k++){
          sum=sum+L[i][k]*U[k][j];
        }
        U[i][j]=A[i][j]-sum;
        if(i<j) {L[i][j]=0.0;} else {L[i][j]=1.0;}
      }
      else{
        sum=0.0;
        for(k=0;k<=j-1;k++){
          sum=sum+L[i][k]*U[k][j];
        }
        L[i][j]=(A[i][j]-sum)/U[j][j];
        U[i][j]=0.0;
      }
    }
  }

  //Obtener z
  for(i=0;i<=n-1;i++){
    sum=0.0;
    for(j=0;j<=i-1;j++){
      sum=sum+L[i][j]*z[j];
    }
    z[i]=b[i]-sum;
  }

  //Obtener x
  for(i=n-1;i>=0;i--){
    sum=0.0;
    for(j=i+1;j<=n-1;j++){
      sum=sum+U[i][j]*x[j];
    }
    x[i]=(z[i]-sum)/U[i][i];
  }
}


