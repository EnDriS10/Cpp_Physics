#include <iostream> 
using namespace std; 
void funcionerror()
{
cout << "He terminado el contador" << endl; 
// no lleva return. 
} 
int main ( ) { 
int i, n=10;
for (i=0; i<n; i++) {
if (i==n-1) 
funcionerror();   
}
return 0;
}

