// Operador Indireccion: permite acceder a un valor indirectamente a través de una dirección (un puntero).
// La expresión "Endirección", sería más adecuada en español.

#include <iostream>
using namespace std;

int main()
{
  int *px; // px es un puntero a un valor entero: variable capaz de contener una direccion de memoria
  int x = 7; px = &x; // en el puntero px, se almacena la direccion del entero x
  
  int y, z;
  y = *px; // en y almacenamos el valor localizado en la dirección almacenada en px
  z = *&x; // en z almacenamos el valor localizado en la dirección de x;
  
  cout << "Direccion de memoria px = " << px << ", x = " << x << "\n";
  cout << "Contenido de la direccion anterior *px = " << y << "\n" << "\n";
  cout << &y << endl;
  
  cout << "Direccion de memoria &x = " << &x << ", x = " << x << "\n";
  cout << "Contenido de la direccion anterior *&x = " << z << "\n" << "\n";
  
  
  return 0;
}
