// Declaracion de funciones

#include <iostream>
using namespace std;

void impar (int a); // Prototipo. Comentar para ver el efecto.
void par (int a); // Prototipo. Comentar para ver el efecto.

int main()
{
    int i;
    do
        {
        cout << "Escriba un numero (0 para salir): ";
        cin >> i;
        impar(i);
        }
    while (i!=0);
    
    return 0;
}

void impar (int a)
{
     if ((a%2) != 0)
        cout << "Numero impar" << endl << endl;
     else par(a);
}

void par (int a)
{
     if ((a%2) == 0)
        cout << "Numero par " << endl << endl;
//     else impar(a);
}
