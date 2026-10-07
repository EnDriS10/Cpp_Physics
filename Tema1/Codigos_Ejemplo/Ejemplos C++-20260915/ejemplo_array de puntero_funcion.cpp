#include <iostream>
using namespace std;

void imprimirValores(int* arr[], int tamaño) {
    for (int i = 0; i < tamaño; ++i) {
       cout << "Valor en la dirección almacenada en el puntero " << i << " es: " << *arr[i] << std::endl;
    }
}

int main() {
    int valor1 = 10;
    int valor2 = 20;
    int valor3 = 30;

    // Declaramos un array de punteros a enteros
    int* arrayPunteros[3] = { &valor1, &valor2, &valor3 };

    // Llamamos a la función que imprime los valores
    imprimirValores(arrayPunteros, 3);

    return 0;
}

