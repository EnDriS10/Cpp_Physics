// Matrices

#include <iostream>
using namespace std;

int a[]={1,2,3,4,5};
int n, result = 0;

int main()
{
  for (n = 0; n < 5; n++)
  {
  result += a[n] ;
  cout << a[n] << "\t" << result << "\n";
  }

 return 0;
}
