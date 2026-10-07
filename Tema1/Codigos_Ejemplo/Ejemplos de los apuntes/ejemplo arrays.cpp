// ejemplo de arrays 
#include <iostream> 
using namespace std;
int a[5]={1,2,3,4,5};
int result=0;
int main () 
{
for (int n=0; n<5; n++)
{
result +=a[n];
}
cout << result;
return 0;
}

