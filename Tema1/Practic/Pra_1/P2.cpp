#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	float N= 1e3;
	int a,b,c;
	int counter =0;
	
	for (int i=0; i<N; i++){ 
	a= i%10; b= (i%100)/10; c= i/100;
	
	if (i == a*a*a + b*b*b + c*c*c) { 
		counter++; 
		cout << "El numero de Armstrong " << counter << " es " <<i << endl;

} 

	}
	
	return 0;
}