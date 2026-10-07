// Ejemplo nº 5 de funciones: Paso "por valor".

#include <iostream>
using namespace std;

int altera (int x, int y)

{
    int temp, s;
    
    temp = x;
    x = y;
    y = temp;
    
    cout << "Este nuevo mensaje te lo envia la funcion altera: ";
    cout << "x = " << x << " " << "y = " << y << endl;
    cout << "Y como ves, dentro de la funcion, los valores se han cambiado." << endl << endl;

}

int main()
{
    int x, y;
    
    cout << "Por favor, introduce dos numeros " << endl;
    cin >> x >> y ;
    cout << "Ahora x = " << x << " " << "e y = " << y << endl << endl;
    
    altera(x, y);
    cout << "Este otro mensaje te lo envia el programa principal: ";
    cout << "x = " << x << " " << "y = " << y << endl << endl;
    cout << "Y como ves, los valores de x e y, no han cambiado en el mismo." << endl << endl;

    return 0;
}
