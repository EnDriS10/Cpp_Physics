#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream> 

using namespace std;

int main() {
	float Num;
	
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
	
	return 0;
}

   

