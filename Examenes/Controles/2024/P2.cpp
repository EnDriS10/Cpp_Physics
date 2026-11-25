#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;
double k = 0.635;

int main() {
	double **x =gen_mat(x, 5, 1); double **y =gen_mat(y, 5, 1);
	double **z =gen_mat(z, 5, 1); double **m =gen_mat(m, 5, 1);
	
	
	m[0][0]= 12; m[1][0]= 1;m[2][0]= 1;m[3][0]= 1;m[4][0]= 28;
	x[0][0]= 0; x[1][0]= k;x[2][0]= -k;x[3][0]= -k;x[4][0]= k;
	y[0][0]= 0; y[1][0]= k;y[2][0]= -k;y[3][0]= k;y[4][0]= -k;
	z[0][0]= 0; z[1][0]= k;z[2][0]= k;z[3][0]= -k;z[4][0]= -k;
	
	//==========================CM=======================================
	double Mt = sum_all_mat(m, 5, 1);
	double xcm= sum_all_mat( ( prodeach_mat(x, m, 5, 1) ) , 5, 1)/Mt;
	double ycm= sum_all_mat( ( prodeach_mat(y, m, 5, 1) ) , 5, 1)/Mt;
	double zcm= sum_all_mat( ( prodeach_mat(z, m, 5, 1) ) , 5, 1)/Mt;
	
	for (int i = 0; i < 5; i++) {
		x[i][0] -= xcm;
		y[i][0] -= ycm;
		z[i][0] -= zcm;
	}
	
	//==========================I=======================================
	double **I =gen_mat(I, 3, 3);
	
	I[0][0]=sum_all_mat( prodeach_mat( suma_mat( prodeach_mat(y, y, 5, 1) , prodeach_mat(z, z, 5, 1) ,5,1) , m, 5, 1) , 5, 1);
	I[1][1]=sum_all_mat( prodeach_mat( suma_mat( prodeach_mat(x, x, 5, 1) , prodeach_mat(z, z, 5, 1) ,5,1) , m, 5, 1) , 5, 1);
	I[2][2]=sum_all_mat( prodeach_mat( suma_mat( prodeach_mat(y, y, 5, 1) , prodeach_mat(x, x, 5, 1) ,5,1) , m, 5, 1) , 5, 1);
	
	I[0][1]=-sum_all_mat( prodeach_mat( prodeach_mat(x, y, 5, 1) , m, 5, 1) , 5, 1);
	I[0][2]=-sum_all_mat( prodeach_mat( prodeach_mat(x, z, 5, 1) , m, 5, 1) , 5, 1);
	I[1][2]=-sum_all_mat( prodeach_mat( prodeach_mat(y, z, 5, 1) , m, 5, 1) , 5, 1);
	
	I[1][0]=I[0][1]; I[2][0]=I[0][2]; I[2][1]=I[1][2];
	
	//==========================Diag_I=======================================
    double *L; double **U; double ** U_trans;
    jacobi_eig(I, 3, L, U, true, true, false, 1e-10, 1000);
    //print_vect(L, 3, "Autovalores");
    //print_mat(U, 3, 3, "Autovectores (columnas)");

	//==========================Rotar Ejes=======================================
	U_trans= transpose_mat(U, 3, 3);
	
	double **r_0 =gen_mat(r_0 ,3, 1); r_0[0][0] = x[0][0] ; r_0[1][0] = y[0][0] ; r_0[2][0] = z[0][0]; 
	double **r_1 =gen_mat(r_1, 3, 1); r_1[0][0] = x[1][0] ; r_1[1][0] = y[1][0] ; r_1[2][0] = z[1][0]; 
	double **r_2 =gen_mat(r_2, 3, 1); r_2[0][0] = x[2][0] ; r_2[1][0] = y[2][0] ; r_2[2][0] = z[2][0]; 
	double **r_3 =gen_mat(r_3, 3, 1); r_3[0][0] = x[3][0] ; r_3[1][0] = y[3][0] ; r_3[2][0] = z[3][0];
	double **r_4 =gen_mat(r_4, 3, 1); r_4[0][0] = x[4][0] ; r_4[1][0] = y[4][0] ; r_4[2][0] = z[4][0]; 
	
	r_0= prod_mat(U_trans, r_0, 3, 3, 3, 1);
	r_1= prod_mat(U_trans, r_1, 3, 3, 3, 1);
	r_2= prod_mat(U_trans, r_2, 3, 3, 3, 1);
	r_3= prod_mat(U_trans, r_3, 3, 3, 3, 1);
	r_4= prod_mat(U_trans, r_4, 3, 3, 3, 1);
	
	
	x[0][0]= r_0[0][0]; x[1][0]= r_1[0][0];x[2][0]= r_2[0][0];x[3][0]= r_3[0][0];x[4][0]= r_4[0][0];
	y[0][0]= r_0[1][0]; y[1][0]= r_1[1][0];y[2][0]= r_2[1][0];y[3][0]= r_3[1][0];y[4][0]= r_4[1][0];
	z[0][0]= r_0[2][0]; z[1][0]= r_1[2][0];z[2][0]= r_2[2][0];z[3][0]= r_3[2][0];z[4][0]= r_4[2][0];
	
	
	print_mat(x, 5 ,1, "x_new"); cout<<endl;
	print_mat(y, 5 ,1, "y_new"); cout<<endl;
	print_mat(z, 5 ,1, "z_new"); cout<<endl;
	
	del_mat(x,5); del_mat(y,5); del_mat(z,5); del_mat(m,5);
	del_mat(r_0,3); del_mat(r_1,3); del_mat(r_2,3); del_mat(r_3,3); del_mat(r_4,3);
	del_mat(I,3); del_mat(U,3); del_mat(U_trans,3); delete [] L; 
	return 0;
}
