#include <iostream>
using namespace std;
void incrementa(int &a){ // referencia al parámetro a
	a = a + 1; }

int main() {
	int var = 1;
	cout << "Valor de var antes: " << var << endl; //Imprime 1
	incrementa(var);
	cout << "Valor de var después: " << var << endl; //Imprime 2
	return 0;
}

