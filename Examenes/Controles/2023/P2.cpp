#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

int main() {
	double **A =gen_mat(A,4,4);double b0[] = {8, 2, 1, 4}; double *b= copy_vect(b0, 4); double *sol;
	A[1][0] =-2; A[1][1] =6; A[1][2] =1; A[1][3] =1;
	A[2][0] =1; A[2][1] =-1; A[2][2] =3; A[2][3] =0;
	A[3][0] =0; A[3][1] =1; A[3][2] =1; A[3][3] =4;
	A[0][0] =10; A[0][1] =-1; A[0][2] =-2; A[0][3] =2;
	
	
	sol = gauss_seidel_solve(A, b, 4, 1e-10, 1e3 );
	print_vect(sol,4,"SOLUCION");
	return 0;
}
