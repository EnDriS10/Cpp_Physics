#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	double Sum =1;	double tP =1; double x = 1; double Err = 1e-6;
	double N= 1e4; int counter =1 ;
	cout << setprecision(7);
	
	for (double i=0; i<=N; i++){
		tP= tP*( (x)/ (i+1));
		if ( tP > Err ) {
		Sum= Sum + tP;
		counter ++;
			cout << "La suma parcial (de " << counter << " terminos) es " <<Sum << endl;	 
		}
		else{
			break;

		} 
	}
	

	
	return 0;
}
