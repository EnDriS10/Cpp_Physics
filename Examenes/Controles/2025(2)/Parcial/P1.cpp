#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;

double f1(double x){return log(x)*sin(x*x);}
double df1(double x){deriv_prog_5p(f1,x,1e-6);}
double* secante_multi(double (*f)(double), double a, double b, int puntos_inicio, double tol, int &num_raices);

int main() {
	int num_bis; int num_newt; int num_sec; 
	double* x_bis = biseccion_multi(f1, 1, 2*PI(10), 1e5, 1e-4, num_bis);
	double* x_newt = newton_multi(f1,df1, 1, 2*PI(10), 1e5, 1e-4, num_newt);
	double* x_sec = secante_multi(f1, 1, 2*PI(10), 1e5, 1e-4, num_sec);
	
	print_vect(x_bis,num_bis,"bis");
	print_vect(x_newt,num_newt,"newt");
	print_vect(x_sec,num_sec,"newt");
	
	cout<<num_bis<<"	"<<num_newt<<"	"<<num_sec<<"	"<<endl;
	
	delete [] x_bis; delete [] x_newt; delete [] x_sec;
	
	return 0;
}

double* secante_multi(double (*f)(double), double a, double b, int puntos_inicio, double tol, int &num_raices) {
    
    double* raices = new double[puntos_inicio + 1];
    num_raices = 0;
    double paso = (b - a) / puntos_inicio;

    for (int i = 0; i <= puntos_inicio; ++i) {
        double x0 = a + i * paso;
        double r = secante(f, x0, b, tol, tol, 1e5);

        if (!isNaN(r) && r >= a && r <= b && fabs(f(r)) < tol) {
            if (!isRoot(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        }
    }
    
    // Si no se encontraron raices, limpiamos memoria y devolvemos nulo
    if (num_raices == 0) {
        delete[] raices;
        return NULL;
    }
    
    return raices;
}

