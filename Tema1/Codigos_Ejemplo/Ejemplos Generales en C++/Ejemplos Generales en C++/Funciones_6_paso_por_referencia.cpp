// Ejemplo nº 6 de funciones: paso por referencia
// Para paso por referencia estilo C, ver pagina 110 del Joyanes - Schaum.
#include <cstdlib>
#include <iostream>
using namespace std;

void referencia (int & x) // Parametro por referencia
// void referencia (int& x) // Valido
// void referencia (int &x) // Tambien valido
{
    x += 2;
}

int main()
{
    int x;

    cout << "Por favor, introduce un numero... " << endl;
    cin  >> x;
    cout << endl << "Antes de la llamada a la funcion referencia, x = " << x << endl;
    referencia (x); // Llamada con nombre de variable
    cout << "Despues de la llamada a la misma funcion, x = " << x << endl << endl;

  
   return 0;
}
