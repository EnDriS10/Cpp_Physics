//punteros1
#include <iostream> 
using namespace std;
int main ( )
{ 
int primervalor=5, segundovalor=7; 
int *mipuntero; // variable tipo puntero a un valor entero
mipuntero=&primervalor; //el puntero apunta a la variable primervalor
*mipuntero=10; // ahora primervalor=10
cout<<"primervalor es " << primervalor << endl;  
mipuntero=&segundovalor; //el puntero apunta a la variable segundovalor
*mipuntero=20; // ahora segundovalor=20
cout << "segundovalor es " << segundovalor << endl;
cout << endl << "Programa terminado" << endl; 
return 0; 
}

