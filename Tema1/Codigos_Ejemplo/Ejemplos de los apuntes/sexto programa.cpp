#include <iostream>
using namespace std; 
int main ()
{
int n;
cout << "Introduce el valor de partida:";
cin >> n; 
while (n>0) {
		cout << n << ", ";
		-- n;
	   }	
cout << "Terminado!" << endl;
return 0;	
}

