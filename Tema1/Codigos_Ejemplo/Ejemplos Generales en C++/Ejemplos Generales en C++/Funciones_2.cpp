// Ejemplo nº 2 de funciones: Distintas formas de llamada
#include <iostream>
using namespace std;

int resta (int a, int b)
{
    int r; 
    r = a - b; 
    return r;
}

int main()
{
    int x, y, z;
//    float x, y, z; 
    cout << "Por favor, introduce los dos numeros que no sabes restar: " << endl;
    cin >> x >> y; 
    z = resta(x,y); 
    cout << "Tu primer resultado, a partir del valor de z: " << z << endl;
    cout << "Tu segundo resultado, llamando directamente a la funcion : " << resta(x,y) << endl << endl;
  
    return 0;
}
