// Punteros a funciones: Nos permite pasar una funcion como argumento de otra.

#include <iostream>
using namespace std;

int addition (int a, int b)
{
    return (a + b);
}

int subtraction (int a, int b)
{
    return (a - b);
}

int operation (int x, int y, int (*functocall)(int, int))
{
    int g;
    g = (*functocall)(x,y);
    return (g);
}
    
int main()
{
    int m, n, a, b, c;
//    int (*minus)(int,int) = subtraction;
//    int minus(int,int) = subtraction; // Mostrar que no funcionaria.

    cout << "Por favor, escribe los dos numeros que querias sumar: " << endl;
    cin >> a >> b;  
    m = operation(a, b, addition);
    cout << "Su suma es: " << m << endl << endl;
    cout << "Ahora escribe un numero para restarle al resultado: " << endl;
    cin >> c;  
    n = operation(m, c, subtraction);
//    n = operation(m, c, minus); // Solo necesario para mostrar que ahora el contenido de minus coincide con subtraction. 
    cout << "La resta es: " << n << endl << endl;
    cout << endl << "Programa terminado. Gracias! " << endl << endl;
  
    return 0;
}
