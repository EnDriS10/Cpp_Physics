// Ejemplo 2 de punteros.

#include <iostream>
using namespace std;

int main()
{
  int firstvalue = 5, secondvalue = 15;
  int *p1, *p2; // variables tipo puntero
  
  p1 = &firstvalue; // el puntero apunta a la dirección de la variable firstvalue. 
  p2 = &secondvalue; // el puntero apunta a la dirección de la variable secondvalue. 
  
  cout << "La direccion de memoria de firstvalue es: " << p1 << endl;
  cout << "y su contenido es: " << *p1 << endl << endl;
  cout << "La direccion de memoria de secondvalue es: " << p2 << endl;
  cout << "y su contenido es: " << *p2 << endl << endl;
  
  *p1 = 10; // nuevo valor residente en la dirección p1;
  cout << "*p1 = 10; El nuevo contenido en la direccion p1 es: " << *p1 << endl << endl;
  *p2 = *p1; // el contenido en la dirección de memoria p1, lo copiamos en la dirección de memoria p2;
  cout << "*p2 = *p1; y hacemos que el nuevo contenido en la direccion p2 sea: " << *p2 << endl << endl;
  
  p1 = p2; // Ahora copiamos la dirección de memoria p2 en p1;
  cout << "p1 = p2; Ahora p1 hace referencia a otra direccion: la de p2; " << p1 << endl;
  *p1 = 20; // Esa direccion la rellenamos con 20.
  cout << "*p1 = 20; con lo cual tambien estamos rellenando p2: secondvalue; " << secondvalue << endl;
  cout << "mientras que firstvalue sigue siendo: " << firstvalue << endl;
  cout << "y su direccion sigue siendo &firstvalue: " << &firstvalue  << endl;
  cout << "hemos cambiado la VARIABLE p1, que ahora contiene tambien la direccion de secondvalue: " << p1 << endl << endl;
  
  
  return 0;
}
