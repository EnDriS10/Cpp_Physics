// ejemplo básico de lectura y escritura en ficheros
#include<iostream>
#include<fstream>
using namespace std;
int main(){
	int dato;
	ifstream nombre1;
	nombre1.open("nombrefichero1");
	nombre1 >> dato;
	ofstream nombre2;
	nombre2.open("nombrefichero2");
	nombre2 << dato;
	nombre1.close();
		nombre2.close();
		return 0;
}

