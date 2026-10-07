#include <iostream>

using namespace std;

// ============================================================================
// CONCEPTO 1: Declaración de punteros y operador dirección-de (&)
// ============================================================================
namespace Concepto1_Direccion {
    void ejecutar() {
        cout << "=== 1. DECLARACION DE PUNTEROS Y OPERADOR (&) ===" << endl;

        // Declaración de variables tipo puntero (almacenan direcciones de memoria)
        int *puntero1;   // Puntero a un valor entero
        double *puntero2; // Puntero a un valor real (double)

        int a = 7;

        // El operador '&' extrae la dirección de memoria donde reside 'a'
        puntero1 = &a; 

        cout << "Valor de la variable 'a': " << a << endl;
        cout << "Direccion de memoria de 'a' (&a): " << &a << endl;
        cout << "Direccion almacenada en 'puntero1': " << puntero1 << endl;
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 2: Desreferenciación (*) y asignación indirecta
// ============================================================================
namespace Concepto2_Desreferenciacion {
    void ejecutar() {
        cout << "=== 2. DESREFERENCIACION (*) Y LECTURA DE VALORES ===" << endl;

        int *px; // px se declara como un puntero a un entero
        int x = 7;
        
        px = &x; // En px se almacena la dirección de la variable x
        
        int y; 
        // El operador '*' (desreferenciación) accede al contenido guardado
        // en la dirección a la que apunta 'px'.
        y = *px; // En 'y' se almacena el valor localizado en la dirección guardada en px

        cout << "Direccion de memoria en px: " << px << endl;
        cout << "Valor guardado en y (a traves de *px): " << y << endl;
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 3: Modificación de variables apuntadas por un puntero
// ============================================================================
namespace Concepto3_Modificacion {
    void ejecutar() {
        cout << "=== 3. MODIFICACION DE VALORES VIA PUNTERO ===" << endl;

        int primervalor = 5, segundovalor = 7;  
        int *mipuntero; // Variable tipo puntero a un entero

        // El puntero apunta a 'primervalor' y modifica su valor original
        mipuntero = &primervalor; 
        *mipuntero = 10; // Ahora primervalor = 10
        cout << "primervalor es " << primervalor << endl;   

        // El mismo puntero reasigna su dirección para apuntar a 'segundovalor'
        mipuntero = &segundovalor; 
        *mipuntero = 20; // Ahora segundovalor = 20
        cout << "segundovalor es " << segundovalor << endl; 
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 4: Relación entre punteros y arrays (Aritmética de Punteros)
// ============================================================================
namespace Concepto4_ArraysYPunteros {
    void ejecutar() {
        cout << "=== 4. RELACION ENTRE ARRAYS Y PUNTEROS ===" << endl;

        // Cuando declaramos double A[5], 'A' actúa como un puntero
        // que apunta al primer elemento del array.
        double A[5] = {10.5, 20.1, 30.2, 40.3, 50.4};

        // Aritmética de punteros: A + i es equivalente a &(A[i])
        cout << "A   = &(A[0]): " << A       << " -> Valor: " << *A       << endl;
        cout << "A+1 = &(A[1]): " << (A + 1) << " -> Valor: " << *(A + 1) << endl;
        cout << "A+2 = &(A[2]): " << (A + 2) << " -> Valor: " << *(A + 2) << endl;
        cout << "A+3 = &(A[3]): " << (A + 3) << " -> Valor: " << *(A + 3) << endl;
        cout << "A+4 = &(A[4]): " << (A + 4) << " -> Valor: " << *(A + 4) << endl;
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 5: Reglas de compatibilidad de tipos entre punteros
// ============================================================================
namespace Concepto5_CompatibilidadTipos {
    void ejecutar() {
        cout << "=== 5. COMPATIBILIDAD DE TIPOS EN PUNTEROS ===" << endl;

        int i = 42;
        double d = 3.1416;

        int *ip = &i;     // Puntero a int
        double *dp = &d;  // Puntero a double

        /* 
         * NOTA TEÓRICA:
         * dp = ip; 
         * ¡ERROR DE COMPILACIÓN! No se pueden asignar punteros de tipos
         * diferentes directamente (int* no es compatible con double*).
         */

        cout << "Valor inicial de *ip (int): " << *ip << endl;
        cout << "Valor inicial de *dp (double): " << *dp << endl;

        // Se pueden, sin embargo, realizar asignaciones entre contenidos (*dp = *ip),
        // ya que el compilador realiza una conversión implícita entre int y double.
        *dp = *ip; // Asigna el valor 42 a la variable double 'd'

        cout << "Nuevo valor de *dp tras (*dp = *ip): " << *dp << " (convertido a double)" << endl;
        cout << endl;
    }
}

// ============================================================================
// PUNTO DE ENTRADA PRINCIPAL
// ============================================================================
int main() {
    // Ejecutamos cada concepto de forma ordenada
    Concepto1_Direccion::ejecutar();
    Concepto2_Desreferenciacion::ejecutar();
    Concepto3_Modificacion::ejecutar();
    Concepto4_ArraysYPunteros::ejecutar();
    Concepto5_CompatibilidadTipos::ejecutar();

    cout << "Programa terminado con exito." << endl;
    return 0;
}
