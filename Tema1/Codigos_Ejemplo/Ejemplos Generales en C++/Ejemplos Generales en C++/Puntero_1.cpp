// Ejemplo 1 de punteros.

#include <iostream>
using namespace std;

int main()
{
  int primervalor = 5, segundovalor = 7;
  int *mipuntero; //variable tipo puntero
  
  mipuntero = &primervalor; // el puntero apunta a la variable primer valor. 
  cout << "primervalor antes de usar el puntero para cambiarlo es " << primervalor << endl;
  *mipuntero = 10;
  cout << "primervalor ahora es " << primervalor << endl << endl;
  
  mipuntero = &segundovalor; // el puntero apunta a la variable segundo valor.
  cout << "segundovalor antes de usar el puntero para cambiarlo es " << segundovalor << endl;
  *mipuntero = 20;
  cout << "segundovalor ahora es " << segundovalor << endl << endl;
 
  return 0;
}
