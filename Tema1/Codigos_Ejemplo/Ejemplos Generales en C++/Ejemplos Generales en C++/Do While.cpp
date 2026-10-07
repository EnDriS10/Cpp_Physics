// While
#include <iostream>
using namespace std;

int main()
{
  int n, i;
  
  do 
     {
  cout << "Prueba a introducir un numero, por favor \n";
  cin  >> n;
  cout << "Has introducido " << n << "\n";
     }
  while (n <= 10);
  cout << "Prueba superada!" << "Bye, bye..." << endl;
  
   
  return 0;
}
