// Ejemplo punteros a funciones
#include <iostream> 
using namespace std;
int suma (int a, int b) 
         { return (a+b); }
int resta (int a, int b)
		{ return (a-b); }
int operacion (int x, int y, int (*funcion)(int,int)){
		int g; 
         g = funcion(x,y); 
         return g; }
int main (){
int m, n; 
m = operacion (7, 5, suma); 
cout << m << endl; 
n = operacion (20, m, resta);                                            
cout << n << endl;                                                                                                                
return 0;                                                                
}

