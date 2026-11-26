#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;
double K =0.25e-3;double D =0.3; double Re = 200000; double Land0 =0.0001;

double f1(double L){return pow(L,-0.5) + 2*log10( ((2.51)/(sqrt(L)*Re)) + ((K)/(3.71*D)) ) ;}
double df1(double L){return deriv_prog_5p(f1, L, 1e-8);}

// Método de la Biseccion (Una sola raiz)
double biseccion_iter(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int &iter) {
    if (f(x1) * f(x2) >= 0.0) {
        print_error("f(x1) y f(x2) deben tener signos opuestos");
        return MC_NAN; 
    }

    double x3 = 0.0;
    iter = 0;

    do {
        x3 = (x1 + x2) / 2.0;
        if (f(x3) * f(x1) < 0.0) {
            x2 = x3;
        } else {
            x1 = x3;
        }
        iter++;
    } while ((fabs(x2 - x1) > 2.0 * tol1 && fabs(f(x3)) > tol2));

    return x3;
}

// Biseccion Multiple: Busca multiples raices en un intervalo [a, b]
double* biseccion_multi_iter(double (*f)(double), double a, double b, 
                        int subintervalos, double tol, int &num_raices, int *iter_arr) {
    
    // Reserva de memoria al estilo de la libreria
    double* raices = new double[subintervalos]; 
    num_raices = 0;
    double paso = (b - a) / subintervalos;
    int iter;

    for (int i = 0; i < subintervalos; ++i) {
        double x1 = a + i * paso;
        double x2 = x1 + paso;

        if (f(x1) * f(x2) < 0.0) {
            double r = biseccion_iter(f, x1, x2, tol, tol, iter);
            iter_arr[num_raices] = iter;
            
            // Uso de las utilidades isNaN e isRoot de matclub_2
            if (!isNaN(r) && !isRoot(raices, num_raices, r, 1e-3)) {
                raices[num_raices] = r;
                num_raices++;
            }
        } else if (fabs(f(x1)) < tol && !isRoot(raices, num_raices, x1, 1e-3)) {
            raices[num_raices] = x1;
            num_raices++;
            
        }
    }
    
    // Si no se encontraron raices, limpiamos memoria y devolvemos nulo
    if (num_raices == 0) {
        delete[] raices;
        return NULL;
    }
    
    return raices;
}

double newton_iter(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int &iter) {
    double x1 = x0;
    double dx = 0.0;
    iter = 0;

    do {
        double fx = f(x0);
        double dfx = df(x0);

        if (fx != 0.0 && dfx != 0.0) {
            x1 = x0 - (fx / dfx);
            dx = x1 - x0;
            x0 = x1;
        } else {
            break;
        }
        iter++;
    } while ((fabs(f(x1)) > tol1 || fabs(dx) > tol2));

    return x1;
}

int main() {
	cout << setprecision(7);
	int num_raices; int n= 1e5; int *iter_arr = new int[n]; int iter;
	double *raices = biseccion_multi_iter(f1, Land0, 1, n, 1e-9, num_raices, iter_arr);
	print_vect(raices,num_raices,"Sol");
	
	cout << "Num_iter" << " = [ ";
    for ( int i = 0; i<num_raices ; i++){
        cout << iter_arr[i] << (i < num_raices - 1 ? ", " : " ");
    }   
    cout << "]" << endl;
	cout<<endl;
	
	double Newt_Sol = newton_iter(f1, df1, Land0, 1e-9, 1e-9, iter);
    cout<<Newt_Sol<<endl;
	cout<<iter<<endl;
	cout<<endl;
	
	double Sec_Sol = secante(f1, Land0, 1, 1e-9, 1e-9, n);  
	cout<<Sec_Sol<<endl;
	cout<<endl;
	
	double *land_arr = linspace(Land0, 1.0, n);
	double *f1_arr = new double [n];
    for ( int i = 0; i<n ; i++){ f1_arr[i] = f1(land_arr[i]);}
    save_xy_file("f1_arr.dat", land_arr, f1_arr, n);
	        	
	return 0;
}
