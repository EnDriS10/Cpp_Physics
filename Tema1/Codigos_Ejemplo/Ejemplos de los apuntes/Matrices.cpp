#include <iostream>    
using namespace std;	
const int fa=3, ca=3;

void muestramatriz(double matriz[fa][ca])
{
cout << "Matriz:" << endl;
for (int i=0; i<fa; i++) {
    for (int j=0; j<ca; j++) {cout << matriz[i][j] << " ";}
     cout << endl;
 }
}

int main()
{ 
double A[fa][ca]={2,3,8,2,2,4,2,2,6};
muestramatriz(A);
return 0;
}


