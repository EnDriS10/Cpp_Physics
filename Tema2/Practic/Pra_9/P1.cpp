#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;

int main() {
	int n= 100;
	double **A = zeros_mat(n, n); double *x = new double[n]; double *y = new double[n];
	
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j){ A[i][j] = 4.0;
				if (j<n-1){ A[i][j+1] = -2.0;}
					if(j>0){ A[i][j-1] = -2.0;}
        	}
    	}
    }
    
    for (int i = 0; i < n; i++) { x[i] =200.0; }
    x[0]=100; x[n-1]= 100;
    
    y= tridiag_solve(A, x,n);
	save_vector_file("vector.dat",y, n);
	del_mat(A, n);
	delete[] x;
	delete[] y;
	return 0;
}
