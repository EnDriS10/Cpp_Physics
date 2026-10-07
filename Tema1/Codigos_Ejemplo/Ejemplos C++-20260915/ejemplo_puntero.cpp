#include <iostream>
using namespace std;

int main() {
    int numero = 25;  // Variable normal
    int* ptr = &numero; // Puntero que almacena la dirección de 'numero'

    cout << "Valor de numero: " << numero << std::endl; // Imprime el valor de 'numero'
    cout << "Dirección de numero: " << &numero << std::endl; // Imprime la dirección de memoria de 'numero'
    cout << "Valor almacenado en el puntero: " << ptr << std::endl; // Imprime la dirección de memoria guardada en el puntero
    cout << "Valor al que apunta el puntero: " << *ptr << std::endl; // Imprime el valor en la dirección a la que apunta el puntero

    return 0;
}

