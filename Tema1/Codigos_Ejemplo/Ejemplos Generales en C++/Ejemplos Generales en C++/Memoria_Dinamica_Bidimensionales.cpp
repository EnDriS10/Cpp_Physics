// Memoria Dinamica en matrices bidimensionales

#include <iostream>
using namespace std;

int main()
{
    int **A;
    int fa, ca;

    cout << "Introduce numero de filas: ";
    cin >> fa;
    cout << endl;
    cout << "Introduce numero de columnas: ";
    cin >> ca;
//  Reserva dinamica de memoria. 
//  Primera etapa: Se reserva memoria para el array de punteros que apuntan a las filas de A.
    A = new int * [fa]; // Primera etapa.
    
    cout << "A = " << A << endl;

//  Segunda etapa: Se reserva memoria para cada uno de los ca elementos que forman cada una de las filas fa de la matriz A.
    for(int i = 0; i < fa; i++)
    {
            A[i] = new int[ca]; // Segunda etapa.
            cout << "A[" << i << "]" << " = " << A[i] << endl;
    }
    cout << endl;

// Rellenamos la matriz
   for (int i = 0; i < fa; i++)
   {
       for(int j = 0; j < ca; j++)
       {
               A[i][j] = 2*i + 3*j;
       }
   }
   
   cout << "Matriz A(" << fa << ", " << ca << ")" << endl;
     for(int i = 0; i < fa; i++)
     {
           cout << "Fila " << i << ": ";
           for(int j = 0; j < ca; j++)
                 {
                     cout << A[i][j] << " ";
                 } // Cuidado con olvidarse apertura y cierre de los "for" !
           cout << endl;
     }
   
// Y finalmente, se libera la memoria ocupada por A en dos etapas.
   for (int i = 0; i < fa; i++)
   {
       delete [] A[i];
   }
   delete [] A;
   cout << endl;
            
  return 0;
}
