
#include <iostream>


/* 
char 											1 byte  
int 		Enteros (con signo o sin signo)		4 bytes 
float 		Números reales en simple precisión	4 bytes
double 		Números reales en doble precisión 	8 bytes

#include <iomanip>
cout << setprecision(7);


sin(x) : devuelve el seno de x. 
cos(x) : devuelve el coseno de x. 
tan(x) : devuelve la tangente de x. 
asin(x)  : devuelve el arco seno de x. El resultado se devuelve en radianes. 
acos(x) : devuelve el arco coseno de x. El resultado se devuelve en radianes. 
atan(x)  : devuelve el arco tangente de x. El resultado se devuelve en radianes. 
sinh(x) :  devuelve el seno hiperbólico de x. 
cosh(x)  : devuelve el coseno hiperbólico de x. 
tanh(x)  : devuelve la tangente hiperbólica de x. 
exp(x)  : devuelve la exponencial de x. 
log(x) : devuelve el logaritmo neperiano de x. 
log10(x) : devuelve el logaritmo decimal de x. 
pow(x,y) : devuelve xy. 
sqrt(x) : devuelve la raíz cuadrada de x. 
ceil(x) :  devuelve  el número entero mayor que o igual a x. 
floor(x) : redondea por defecto el valor de x. 
fabs(x) : devuelve el valor absoluto de un número en coma flotante. 
labs(x) : devuelve el valor absoluto de un entero largo (long). 
abs(x) : valor absoluto de un número entero. 
fmod(x,y) : calcula el resto de la división real x/y. 




Operador Descripción 
< 		Menor que 
<=		Menor o igual que
> 		Mayor que 
>= 		Mayor o igual que 
== 		Igual a 
!= 		Distinto de


=====CONDICIONALES===============
	if (x > 0) 
		cout << "x es positiva" << endl;  
		else if (x < 0)  
			cout << "x es negativa" << endl;  
		else  
			cout << "x es 0" << endl; 


=====BUCLES=====================


while (n>0) { 
	cout << n << ", "; 
	- - n; 
    } 

do {  
	cout << "Introduce un número= ";  
	cin >> n; 
	cout << "Tu has introducido= " << n << "\n"; 
	} while (n != 0); 

for (int n=1; n<=10; n++) { 
cout << n << ", "; 
} 

=====Datos=====================

 ifstream Fichero1; 
 Fichero1.open("nombrefichero1"); 
 Fichero1 >> dato; 
 ofstream Fichero2; 
 Fichero2.open("nombrefichero2"); 
 Fichero2 << dato; 
 Fichero1.close(); 
 Fichero2.close(); 


  ifstream fentrada;      
  ofstream fsalida;  
  fentrada.open ("datos.txt");   
  fsalida.open ("resultados.txt");  
        while (!fentrada.eof()){  
  fentrada >> numero;   
  fsalida << numero*numero << endl;  
       }  


void save_mat_dat(const char* filename, double **A, int f, int c) {
    ofstream fsalida(filename, ios::out);
    if (!fsalida) {
        print_error("No se pudo crear el archivo .dat para guardar la matriz", filename); //
        return;
    }

    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            fsalida << A[i][j] << (j < c - 1 ? "\t" : "");
        }
        fsalida << endl;
    }

    fsalida.close();
    print_info("Matriz .dat guardada exitosamente", filename); //
}


	ifstream fichero_1;
	fichero_1.open ("datos.dat");	
	ofstream fichero_2;
	fichero_2.open ("resultados.dat");
	
	while (!fichero_1.eof()){  
  		fichero_1 >> Num;
		if ( Num > 1  ) {
  			fichero_2 << Num*Num << endl;
  		}
			    
    }
	
	fichero_1.close() ; fichero_2.close();


*/





int main() {
	return 0;
}
