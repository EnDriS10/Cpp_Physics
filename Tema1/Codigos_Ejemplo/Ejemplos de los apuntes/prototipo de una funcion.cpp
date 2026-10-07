#include <iostream>
using namespace std;
double potencia(double val, int potencia); // prototipo
int main() {
	double a, c;
	int b;
	cout << "Este programa calcula una potencia, a^b" << endl;
	cout << "Introduce el valor de a: ";
	cin >> a;
	cout << "Introduce el valor de b; ";
	cin >> b;
	c=potencia(a,b);
	cout << "El resultado es: " << c << endl;
	return 0;
}
double potencia(double val, int potencia){
	double resultado=1.0;
	for (int i=1; i<=potencia; i++){
		resultado *= val; }
return resultado;
}

