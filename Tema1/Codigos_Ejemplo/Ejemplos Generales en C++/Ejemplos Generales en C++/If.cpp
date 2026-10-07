// If

#include <iostream>
using namespace std;

int main()
{
    int x;
    
    cout << "Introduce un numero por favor:" << "\n";
    cin >> x;
    
    if (x == 100)
    {
        cout << "x es " << x << "\n" << "Enhorabuena!" << "\n"; // Si x!=100, la sentencia no se ejecuta y continua el programa.
    }
    
    return 0;
}

