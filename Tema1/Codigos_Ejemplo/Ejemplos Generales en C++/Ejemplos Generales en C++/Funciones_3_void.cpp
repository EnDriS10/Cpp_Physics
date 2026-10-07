// Ejemplo nº 3 de funciones: funciones sin tipo
#include <iostream>
using namespace std;


void funcionerror()
{
    cout << "Se me ha terminado el contador! " << endl;
    return; // Puede omitirse.
//    return 0; // Si se usa esta sentencia el compilador daria error.
}

int main()
{
    int i, n;
    
    cout << "Hasta donde quieres que llegue tu contador? " << endl;
    cin >> n;
    for (i=0; i < n; i++)
    {
        cout << "Ahora mismo, i vale: " << i << endl;
        if (i == n - 1)
        funcionerror();
    }
  
    return 0;
}
