#include <iostream>
using namespace std;

// Definición de la función void
void mostrarSuma(int a, int b) {
    int suma = a + b; // Realiza la operación de suma
    cout << "La suma de " << a << " y " << b << " es " << suma << std::endl;
}

int main() {
    int num1 = 5;
    int num2 = 10;
    
    // Llamada a la función con dos argumentos
    mostrarSuma(num1, num2);

    return 0;
}

