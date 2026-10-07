#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


// ============================================================================
// FUNCIONES 
// ============================================================================

double f1(double x) {
    return pow(x, 2) - 2;
}

double df1(double x) {
    return 2*x;
}

double newton(double (*f)(double), double (*df)(double), double x0, 
              double tol1, double tol2, int max_iter) {
    double x1 = x0;
    double dx = 0.0;
    int iter = 0;

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
    } while ((fabs(f(x1)) > tol1 || fabs(dx) > tol2) && iter < max_iter);

    return x1;
}

int main() {
	double x;
	
	x = newton( f1,df1, 1, 1e-5, 1e-5, 9);
	cout << "Raiz Newton (x0=1):    " << x << endl;

    return 0;
}
