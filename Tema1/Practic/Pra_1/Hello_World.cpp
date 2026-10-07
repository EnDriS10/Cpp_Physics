#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	float Sum1sim =0; double Sum1do =0;
	float Sum2sim =0; double Sum2do =0;
	float j; float N= 1e4;
	cout << setprecision(10);
	float PI = 4*atan(1);
	
	
	for (float i=1; i<=N; i++){ 
	Sum1sim= Sum1sim + 1 / (i*i); 
	j=( N + 1)  - i ; 
	Sum2sim= Sum2sim + 1 / (j*j);
	}
	
	for (double i=1; i<=N; i++){ 
	Sum1do= Sum1do + 1 / (i*i); 
	j=( N + 1)  - i ; 
	Sum2do= Sum2do + 1 / (j*j);
	}
	

	
	cout << "Suma en terminos simples directa "<< Sum1sim<<endl;	
	cout << "Suma en terminos simples inversa "<<Sum2sim<<endl;
	
	cout <<  "Suma en terminos dobles directa "<< Sum1do<<endl;	
	cout <<  "Suma en terminos dobles inversa "<<Sum2do<<endl;
	cout <<  "El valor anlitico es "<<(PI*PI/6)<<endl;
	
	return 0;
}