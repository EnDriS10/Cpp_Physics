// Ejemplo nº 4 de funciones: Matrices como parametros de funciones.

#include <iostream>
using namespace std;

void print_vector (int x[], int dim) // Aquí la funcion ya espera un vector.
{
    for(int n = 0; n < dim; n++)
    {
            cout << x[n] << " ";
    }
}

int main()
{
    int x[] = {5, 10, 15};
    int y[] = {2, 4, 6, 8, 10};
    
    print_vector(x, 3);
    cout << endl;
            
    print_vector(y, 5);
    cout << endl << endl;
    
    return 0;
}
    
