#include <iostream>

using namespace std;

int main() {
	int N= 2e2;
	int fact_int= 1; 		float fact_flo= 1;			double fact_dou = 1;		//long long fact_lolo = 1;

	for (int i=1; i<=N; i++){ 
	fact_int=fact_int*i;	fact_flo=fact_flo*i; 	fact_dou=fact_dou*i; 	//fact_lolo=fact_lolo*i;
	
	cout << "El factorial (entero) de " << i << "! es " <<fact_int<< endl;
	cout << "El factorial (simple) de " << i << "! es " <<fact_flo<< endl;
	cout << "El factorial (doble)  de " << i << "! es " <<fact_dou<< endl;
	//cout << "El factorial (largo largo) de " << i << "! es " <<fact_lolo<< endl;
	cout << endl;
	} 
	return 0;
}