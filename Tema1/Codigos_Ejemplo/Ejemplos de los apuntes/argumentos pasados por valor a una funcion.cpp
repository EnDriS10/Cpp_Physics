// Ejemplo:  argumentos pasados por valor
#include <iostream>                                                     
using namespace std;
int altera (int x, int y){
	int temp;
	temp=x; x=y; y=temp; 
	cout << "x=" << x << " y=" << y << endl; 
}
int main ( ) { 
int x=5,y=3; 
altera(x,y); 
cout << "x=" << x << " y=" << y << endl;                 Salida:
return 0;                                                                       
}          

