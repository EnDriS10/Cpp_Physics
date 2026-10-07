// Memoria Dinamica

#include <iostream>
using namespace std;

int main()
{
    int A[]={1,2,3,4,5};
    int i, n;
    n = 5;
    for (i = 0; i < n; i++)
    {
        cout << "A[" << i << "]" << " = " << A[i] << endl;
    }
    cout << "Pero... A = " << A << " " << " Es decir, el nombre de una matriz es una direccion de memoria!" << endl << endl;
    
    int *B;
    int j, m;
    cout << "Escribe la dimension de tu vector: " << endl;
    cin >> m;
    
    B = new int[m]; // reserva dinamica de memoria: damos las dimensiones para acomodar el contenido de B

    for (int j = 0; j < m; j++)
    {
        B[j] = (j*j +1);
        cout << "B[" << j << "]" << " = " << B[j] << endl;
    }

    cout << "Y... B = " << B << "" << " es decir, direccion de memoria!" << endl;
    
    delete [] B; // Liberamos la memoria ocupada por B
    
    return 0;
}
