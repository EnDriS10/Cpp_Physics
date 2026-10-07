#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


// ============================================================================
// FUNCIONES 
// ============================================================================

const double V0 = 50.0, r0 = 1.5 , p=0.01; //r0 [1e-15]
	
double Yukawa_Force(double r) {
    double k=(V0/r0);	double rr=r0/r;
    return -k*( pow(rr, 2) + (rr) )*exp(-1/rr);
}
double f(double r) {
    return p*Yukawa_Force(r) - Yukawa_Force(r0);
}
double df(double r) {
    double k=(V0/r0);	double rr=r0/r;
    return -(p/r0)*Yukawa_Force(r) + k*p*( 2*( pow(rr, 2)/r ) + ( rr/r ) )*exp(-1/rr);
}

void intercambiar(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}

// Método de Newton (Una sola raíz)
double newton(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int &iter) {
    double x1 = x0;
    double dx = 0.0;
    iter = 0;

    do {
        double fx = f(x0);
        double dfx = df(x0);

        if (fx != 0 && dfx != 0) {
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

// Método de la Secante (Una sola raíz)
double secante(double (*f)(double), double x0, double x1, 
               double tol1, double tol2, int &iter) {
    if (fabs(f(x0)) < fabs(f(x1))) {
        intercambiar(x0, x1);
    }

    double x2 = 0.0, dx = 0.0;
    iter = 0;

    do {
        double f0 = f(x0);
        double f1 = f(x1);

        if (fabs(f0 - f1) < 1e-12) break;

        x2 = x1 - f1 * ((x0 - x1) / (f0 - f1));
        dx = x2 - x1;

        x0 = x1;
        x1 = x2;
        iter++;
    } while ((fabs(f(x2)) > tol1 || fabs(dx) > tol2));
    return x2;
}

// Método de la Bisección (Una sola raíz)
double biseccion(double (*f)(double), double x1, double x2, 
                 double tol1, double tol2, int &iter) {
    if (f(x1) * f(x2) >= 0) {
        cerr << "[Biseccion] Error: f(x1) y f(x2) deben tener signos opuestos." << endl;
        return 0.0 / 0.0; // NaN
    }

    double x3 = 0.0;
    iter = 0;

    do {
        x3 = (x1 + x2) / 2.0;
        if (f(x3) * f(x1) < 0) {
            x2 = x3;
        } else {
            x1 = x3;
        }
        iter++;
    } while ((fabs(x2 - x1) > 2.0 * tol1 && fabs(f(x3)) > tol2));
    return x3;
}

int main() {
	double ep[3]= {1e-3,1e-5 , 1e-12}; int iter;
	setprecision(7);
	
	for (int i = 0; i < 3; i++) { 
	 	cout << "Precision ep = " << ep[i] << endl;
  		double r_bis = biseccion(f, 0.1*r0, r0, ep[i], ep[i], iter);
    	cout << "Raiz Biseccion en [0.1r0, 2r0]: " << r_bis <<" numero de iteraciones: "<<iter << endl;
    	double r_sec = secante(f, 0.1*r0, r0, ep[i], ep[i], iter);
    	cout << "Raiz Secante en [0.1r0, 2r0]:   " << r_sec <<" numero de iteraciones: "<<iter << endl;
    	double r_new = newton(f, df, 0.2*r0, ep[i], ep[i], iter);
    	cout << "Raiz Newton (x0=0.1r0):    " << r_new <<" numero de iteraciones: "<<iter << endl;
    	cout<<"------------------------------------------------------------------------------------"<<endl;
	} 

    return 0;
}
