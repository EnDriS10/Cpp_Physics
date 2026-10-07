// incializacion y visualizacion de un array con punteros 
#include <iostream> 
using namespace std; 
int main() 
{  
double V[6]; 
for (int j = 0; j < 6; j++) 
*(V+j) = (j + 1) * 10 + 1; 
cout << "    Direccion        Contenido" << endl; 
for (int j= 0; j < 6; j++) 
{ 
cout <<  " V+" << j << " = " << V+j ; 
cout << "      V[" << j<<"] = "<< *(V+j)<< "\n" ; 
} 
return 0; 
} 
