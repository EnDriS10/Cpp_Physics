// Matrices Multidimensionales

#include <iostream>
using namespace std;

int main()
{
int n=3, m=3, p=2;
int i, j, k;

int A[3][3]={2,3,8,2,2,4,2,2,6};
int B[3][2]={{4,6},{3,9},{1,8}};
//int B[2][3]={{4,6},{3,9},{1,8}}; // Caso de declaración errónea

cout << "Matriz A(3,3)" << endl;
     for(i = 0; i < n; i++)
     {
           cout << "Fila " << i << ": ";
           for(j = 0; j < m; j++)
                 {cout << A[i][j] << " ";} // Cuidado con olvidarse apertura y cierre de los "for" !
           cout << endl;
     }

cout << "Matriz B(3,2)" << endl;
     for(i = 0; i < m; i++)
     {
           cout << "Fila " << i << ": ";
           for(j = 0; j < p; j++)
                 {cout << B[i][j] << " ";}
           cout << endl;
     }

  return 0;
}
