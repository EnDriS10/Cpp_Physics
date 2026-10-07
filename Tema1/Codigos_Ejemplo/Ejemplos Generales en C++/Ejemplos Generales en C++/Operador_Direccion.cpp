// Operador Direccion
#include <iostream>
using namespace std;

int main()
{
  double a = 7, b = 5;
  
  cout << "Direccion de memoria = " << &a << ", a = " << a << "\n";
  cout << "Direccion de memoria = " << &b << ", b = " << b << "\n";
  
  a = 9;
  cout << "Direccion de memoria = " << &a << ", a = " << a << "\n";
  
  return 0;
}
