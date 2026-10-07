#include <iostream>
using namespace std;
int resta (int a, int b){ 
	int r; 
	r = a-b; 
	return (r); }
int main ( ) { 
int x=5, y=3, z; 
z = resta (7,2);
cout << "primer resultado= " << z << endl; 
cout << "segundo resultado= " << resta (7,2) << endl; 
cout << "tercer resultado= " << resta (x,y) << endl; 
return 0;
}

