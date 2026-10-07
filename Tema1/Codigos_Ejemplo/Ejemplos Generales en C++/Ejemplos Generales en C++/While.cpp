// While
#include <iostream>
using namespace std;

int main()
{
  int n;
  cout << "Introduce el valor de partida > \n";
  cin  >> n;
 
  while (n > 0)
  {
  cout << n << "," ;
  --n;
  }
  cout << "\n";
    
  return 0;
}
