#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	int N= 10; int i = 1 ; int j;
	
	cout << "Bucle while" << endl;
	while ( i <= N){
		cout << i*N << endl;
		i++;
		}
		
	cout << endl << "Bucle for" << endl;	
	for ( int i = 1; i<=N ; i++){
		cout << i*N << endl;
		}
		
	cout << endl << "Bucle do - while" << endl;	
	do {
	j=i-9;
 	cout << j*N << "\n";
	i++; 
	} while (j < N); 
	
	return 0;
}
