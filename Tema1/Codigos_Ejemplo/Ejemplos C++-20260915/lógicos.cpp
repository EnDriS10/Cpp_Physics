#include <iostream>
using namespace std;

int main() {
    
	int edad;
    cout<<"introduce tu edad"<<" ";
    cin>>edad;
    
    bool tieneLicencia = true;

    if (edad >= 18 && tieneLicencia) {
       cout << "Puedes conducir un coche." << std::endl;
    } else {
        cout << "No puedes conducir un coche." << std::endl;
    }

    return 0;
}

