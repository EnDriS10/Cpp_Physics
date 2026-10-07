#include <iostream>  
#include "librerias.cpp"  
using namespace std;

int main()
{ 
int fa, fb, ca, cb, fd, cd;
double **A, **B, **C, **D, **Dinv, **Ctrans;

cout << " introduzca numero de filas de A : ";
    cin >> fa;
cout << " introduzca numero de columnas de A : ";
    cin >> ca;
cout << " introduzca numero de filas de B : ";
    cin >> fb;
cout << " introduzca numero de columnas de B : ";
    cin >> cb;
int fc=fa, cc=cb;
A=crearmatriz(A,fa,ca);
B=crearmatriz(B,fb,cb);
C=crearmatriz(C,fc,cc);
cout << "Introduce datos matriz A" << endl;
cout << fa << "filas   y " << ca << "  columnas" << endl;
A=leermatriz (fa, ca);
muestramatriz(A,fa,ca);
cout << "Introduce datos matriz B" << endl;
cout << fb << "filas   y " << cb << "  columnas" << endl;
B=leermatriz(fb, cb);  
muestramatriz(B,fb,cb);  
cout << endl;
cout << "Matriz C:" << endl;
C=multmat(A,B,fa,ca,cb);
muestramatriz(C,fc,cc);

// transpuesta de C
Ctrans=crearmatriz(Ctrans,cc,fc);
Ctrans=transpuesta(C,fc,cc);
cout << "Matriz Ctranspuesta:" << endl;
muestramatriz(Ctrans,cc,fc);

// inversa de D
cout << " introduzca numero de filas de D : ";
    cin >> fd;
cout << " introduzca numero de columnas de D: ";
    cin >> cd;
D=crearmatriz(D,fd,cd);
D=leermatriz(fd,cd); 
Dinv=crearmatriz(Dinv,fd,cd);
Dinv=inversa(D,fd);
cout << "Matriz Dinversa:" << endl;
muestramatriz(Dinv,fd,cd);

borrarmatriz(A,fa);
borrarmatriz(B,fb);
borrarmatriz(C,fc);
borrarmatriz(D,fd);
borrarmatriz(Dinv,fd);
borrarmatriz(Ctrans,cc);
return 0;
}


