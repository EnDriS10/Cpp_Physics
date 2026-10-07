#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// ============================================================================
// FUNCIONES
// ============================================================================
   double prod(double a[],double b[] ,int n) { 
   		double prod=0; 
   		for ( int i = 0; i<n ; i++){
		prod = prod + a[i]*b[i];
		}    
        return prod; 
    }
    
  double Messy_fun ( double (*funcion) (double), double x) { 
		double bbsita;
		if (funcion(x) < 1) 
			bbsita = 2.5; 
		else if ( (funcion(x) >= 1) && (funcion(x) < 2) ) 
			bbsita = 2.0; 
		else if ( (funcion(x) >= 2) && (funcion(x) < 3) ) 
			bbsita = 2.0;
		else
			bbsita =1.0; 
    return bbsita; 
}   
    double f1(double x) {  
		return sin(x);}
    double f2(double x) {  
		return exp(5*x);}
	double f3(double x) {  
		return log(0.01+x);}
	
int main() {
	double x;
	cout << "Introduce un valor de x entre 0 y 1" << endl;
	cin >> x;
		
	cout << "F(sin(x)) = " << Messy_fun(f1,x) << endl;
	cout << "F(exp(5x)) = " << Messy_fun(f2,x) << endl;
	cout << "F(ln(0.01 + x)) = " << Messy_fun(f1,x) << endl;
	
	return 0;
}
