// Incremento: pre y post
#include <iostream>
using namespace std;

int main()
{
  int a = 10, b;
  cout << "a = " << a << "\n";
  cout << "b = " << b << "\n" << "\n";
  
  b = ++a ; // Preincremento equivale a: a=a+1 y b=a
  cout << "a = " << a << "\n";
  cout << "b = " << b << "\n" << "\n";
  
  a = 10;
  b = a++; // Postincremento equivale a: b=a y a=a+1
  cout << "a = " << a << "\n";
  cout << "b = " << b << "\n";
  
 return 0;
}
