#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"

using namespace std;
double m= 101;

double f1(double* r, int n){return pow(r[0],3) + 6*pow(r[1],2) - 76;}
double f2(double* r, int n){return r[0]*r[1] + 8*pow(r[0],3)*pow(r[1],2) - 1024; }

int main() {
    double (*Sist[2])(double*, int) = {f1, f2};;
    double *p = new double[2]; double *sol= new double[2]; double **mat_sol =gen_mat(mat_sol,m,2); int counter =0;
      
        for (int i = 0; i < m ; i++){
			for (int j = 0; j < m ; j++){
				p[0] = 5*i/(m-1) ; p[1] = -4 + 8*j/(m-1);
           		//print_vect(p,2,"p="); cout<<endl;
				sol = newton_raphson_sys(Sist, p, 2, 1e-14, 1000);
				
				if (sol != NULL && fabs(f1(sol, 2)) < 1e-10 && fabs(f2(sol, 2)) < 1e-10) {
               		// Comprobar que no este repetida respecto a NINGUNA raiz previa
               		bool repetida = false;
               		for (int k = 0; k < counter; k++) {
                   		if (fabs(mat_sol[k][0] - sol[0]) < 1e-10 && fabs(mat_sol[k][1] - sol[1]) < 1e-10) {
                       		repetida = true;
                       		break;
                   		}
               		}
               	if (!repetida) {
                   	mat_sol[counter][0] = sol[0];
                   	mat_sol[counter][1] = sol[1];
                   	counter++;
               	}
           		}
			}
		}
		
		double **mat_sol2 = sub_mat(mat_sol, 0, counter-1, 0, 1);
		print_mat(mat_sol2,counter,2,"Sol"); cout<<endl;
		cout<<counter;
			
	return 0;
}
