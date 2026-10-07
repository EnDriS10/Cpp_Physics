// #Define y const
#include <iostream>
using namespace std;
//#define PI 3.1416 //#define está obsoleto
#define NL '\n'
const double PI = 3.1416;

int main()
{
  cout << PI << NL;
  double r = 5.0;
  cout << r << "\n";
  double circle;
  circle = 2*PI*r;
  cout << circle;
  cout << NL;
//  PI = 1; Demuestra que no se pueda asignar un valor a PI
  
  return 0;
}
