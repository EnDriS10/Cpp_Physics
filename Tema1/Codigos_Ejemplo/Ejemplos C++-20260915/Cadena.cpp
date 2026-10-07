#include <iostream>
#include <string>  // Incluye la clase string

using namespace std;

int main() {
    // Crear una cadena de texto
    string saludo = "Hola, mundo!";

    // Mostrar la cadena
    cout << saludo << endl;

    // Concatenar cadenas
    string nombre = "Carlos";
    string mensaje = saludo + " ¿Cómo estás, " + nombre + "?";
    cout << mensaje << endl;

    // Obtener la longitud de la cadena
    cout << "La longitud del mensaje es: " << mensaje.length() << endl;

    // Acceder a un carácter individual (índice empieza en 0)
    cout << "El primer carácter es: " << mensaje[0] << endl;

    return 0;
}

