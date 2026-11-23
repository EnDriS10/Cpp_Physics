#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

int main() {
	int n=4;
	double **A = zeros_mat(n,n); double *L = new double[n]; int rot;
	A = read_mat_file("Matriz.dat", n, n); 
	double **U = jacobi_eig(A, n, L, 1e-10, 1e6, rot);
	
	
	print_mat(U, n, n, "Aguacate");
	print_vect(L, n, "eigenAguacates");

	del_mat(A, n);
	del_mat(U, n);
	delete[] L;
	
	return 0;
}
