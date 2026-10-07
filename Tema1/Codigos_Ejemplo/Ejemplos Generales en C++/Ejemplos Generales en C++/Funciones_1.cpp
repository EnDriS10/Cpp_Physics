// Ejemplo nº 1 de funciones
#include <iostream>
using namespace std;

int suma (int a, int b)
{
    int r; 
    r = a + b; 
    return r;
}

int main()
{
    int x, y, z;
//    float x, y, z; 
    cout << "Por favor, introduce los dos numeros que no sabes sumar: " << endl;
    cin >> x >> y; 
    z = suma(x,y); 
    cout << "El resultado deseado es: " << z << endl << endl;
  
    return 0;
}
