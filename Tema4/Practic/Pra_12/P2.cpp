
#include <iostream>
#include <cmath>
#include <iomanip>
#include "C:\_Stuff\FFisica\2do\Cpp_Physics\Libreria\Examenes\Matclub\matclub.cpp"
#include <iomanip>

using namespace std;

double f1(double w){return 1/w;}
double f2(double th,double c,double d){
	double k=sqrt((c*c - d*d)) /c ;
	return 4*c*sqrt( 1 - pow( k*sin(th) ,2) ) ;}

double simpson38_comp(double (*f)(double,double,double), double a, double b,double c,double d, int n) {
    /*
    Ejemplo de uso:
        double I = simpson38_comp_func(mi_func, 0.0, 1.0, 99);
    */
    if (n < 3) n = 3;
    if (n % 3 != 0) n += 3 - (n % 3);
    double h = (b - a) / n;
    double suma = f(a,c,d) + f(b,c,d);
    for (int i = 1; i < n; i++) suma += ((i % 3 == 0) ? 2.0 : 3.0) * f(a + i * h,c,d);
    return 3.0 * h / 8.0 * suma;
}

int main() {
	cout << setprecision(12);
	
	cout<<"P1"<<endl;
	int n=10; double *x = new double[n]; double I ;
    for (int i = 0; i < n-1; i++){
		x[i] = i+1;
		I=simpson38_comp_func(f1, 1, x[i], 9e2);
		cout<<"Ln("<<x[i] <<") = "<<I<<" y su error relativo es del "<< fabs ( (log(x[i])-I )/( I ) ) <<endl;
		
		}
	cout<<endl;
	cout<<"P2"<<endl;	
    
    double c=4; double d=2;
    double I_2=simpson38_comp( f2 , 0, 0.5*PI(10), c , d ,9);
    double I_2_def=simpson38_comp( f2 , 0, 0.5*PI(10), c , d ,3e6);
    
    cout<<"El area A= "<<I_2<<" y su error relativo es del "<< fabs ( I_2-I_2_def )/( I_2_def ) <<endl;
    
	return 0;
}
