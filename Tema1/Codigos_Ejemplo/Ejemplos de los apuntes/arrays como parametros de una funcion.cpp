#include <iostream>
using namespace std;
// tambien: void print_vector (int *x, int dim)
void print_vector (int x[ ], int dim) {                             
for (int n=0; n<dim; n++)
	{cout <<x[n] << " ";}
}
int main ( ) {
int x[ ]= {5, 10, 15}; 
int y[ ]= {2,4,6,8,10}; 
print_vector (x, 3); // llamada
cout << endl;
print_vector (y, 5); //llamada
return 0;                                
}

