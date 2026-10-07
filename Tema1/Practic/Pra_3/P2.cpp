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
    
    double mod(double a[],int n) { 
   		double mod;
		mod= prod(a,a,n); 
        return mod; 
    }   

   double cos_ang(double a[],double b[] ,int n) { 
   		double cos_;
		cos_=(prod(a,b,n))/((mod(a,n))*(mod(b,n)));    
        return cos_; 
    }
    
int main() {
	int dim =3;
	double a[dim] = {1,2,3} ; double b[dim] = {3,2,0} ;
	
	cout << "El producto escalar entre a y b es " << prod(a,b,dim) << endl;
	cout << "El modulo de a es " << mod(a,dim) << endl;
	cout << "El modulo de b es " << mod(b,dim) << endl;
	cout << "El coseno entre a y b es " << cos_ang(a,b,dim) << endl;
	
	return 0;
}
