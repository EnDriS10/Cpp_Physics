#include <iostream>
#include <cstring> // Para manipular cadenas de texto

using namespace std;

// ============================================================================
// BLOQUE 1: Arrays Unidimensionales (1D)
// ============================================================================
namespace EjemploArray {
    int a[5] = {1, 2, 3, 4, 5}; 
    int result = 0; 

    void ejecutar() {
        cout << "=== 1. SUMA DE ARRAYS UNIDIMENSIONALES ===" << endl;
        for (int n = 0; n < 5; n++) { 
            result += a[n]; 
        } 
        cout << "Resultado de la suma: " << result << endl << endl;
    }
}

// ============================================================================
// BLOQUE 2: Arrays Multidimensionales (Matrices 2D)
// ============================================================================
namespace RepresentacionMatricial {
    int n = 3, m = 3, p = 2;   
    int A[3][3] = {2, 3, 8, 2, 2, 4, 2, 2, 6};  // Matriz 3x3
    int B[3][2] = {{4, 6}, {3, 9}, {1, 8}};     // Matriz 3x2

    void ejecutar() {
        cout << "=== 2. REPRESENTACION MATRICIAL (2D) ===" << endl;

        cout << "Matriz A (3x3):" << endl; 
        for (int i = 0; i < n; i++) {   
            cout << "fila " << i << " =  "; 
            for (int j = 0; j < m; j++) { 
                cout << A[i][j] << "  ";
            } 
            cout << endl; 
        } 

        cout << endl;  

        cout << "Matriz B (3x2):" << endl;                    
        for (int i = 0; i < m; i++) {  
            cout << "fila " << i << " =  "; 
            for (int j = 0; j < p; j++) { 
                cout << B[i][j] << "  ";
            } 
            cout << endl;
        } 
        cout << endl;
    }
}

// ============================================================================
// BLOQUE 3: Declaración de Punteros y Operador Dirección-de (&)
// ============================================================================
namespace Concepto1_Direccion {
    void ejecutar() {
        cout << "=== 3. DECLARACION Y OPERADOR DIRECCION (&) ===" << endl;

        int *puntero1;    // Puntero a entero
        double *puntero2; // Puntero a double

        int a = 7;
        puntero1 = &a; // Asigna la dirección de 'a' a 'puntero1'

        cout << "Valor de 'a': " << a << endl;
        cout << "Direccion de memoria de 'a' (&a): " << &a << endl;
        cout << "Direccion en 'puntero1': " << puntero1 << endl << endl;
    }
}

// ============================================================================
// BLOQUE 4: Operador de Desreferenciación (*)
// ============================================================================
namespace Concepto2_Desreferenciacion {
    void ejecutar() {
        cout << "=== 4. DESREFERENCIACION DE PUNTEROS (*) ===" << endl;

        int *px; // Declaración de puntero
        int x = 7;
        px = &x; // Armacena la dirección de x
        
        int y; 
        y = *px; // Obtiene el valor ubicado en la dirección 'px' y lo asigna a 'y'

        cout << "Direccion de memoria px: " << px << endl;
        cout << "Valor obtenido (*px) almacenado en y: " << y << endl << endl;
    }
}

// ============================================================================
// BLOQUE 5: Modificación Indirecta mediante Punteros
// ============================================================================
namespace Concepto3_Modificacion {
    void ejecutar() {
        cout << "=== 5. MODIFICACION VIA PUNTEROS ===" << endl;

        int primervalor = 5, segundovalor = 7;  
        int *mipuntero;

        // Modifica 'primervalor'
        mipuntero = &primervalor; 
        *mipuntero = 10; 
        cout << "primervalor modificado: " << primervalor << endl;   

        // Cambia la dirección apuntada a 'segundovalor' y lo modifica
        mipuntero = &segundovalor; 
        *mipuntero = 20; 
        cout << "segundovalor modificado: " << segundovalor << endl << endl;
    }
}

// ============================================================================
// BLOQUE 6: Aritmética Baste de Punteros con Arrays
// ============================================================================
namespace Concepto4_ArraysYPunteros {
    void ejecutar() {
        cout << "=== 6. ARITMETICA DE PUNTEROS EN ARRAYS ===" << endl;

        double A[5] = {10.5, 20.1, 30.2, 40.3, 50.4};

        // El nombre del array 'A' es equivalente a un puntero a A[0]
        cout << "A   = &(A[0]): " << A       << " -> Valor (*A): "       << *A       << endl;
        cout << "A+1 = &(A[1]): " << (A + 1) << " -> Valor (*(A+1)): " << *(A + 1) << endl;
        cout << "A+2 = &(A[2]): " << (A + 2) << " -> Valor (*(A+2)): " << *(A + 2) << endl;
        cout << "A+3 = &(A[3]): " << (A + 3) << " -> Valor (*(A+3)): " << *(A + 3) << endl;
        cout << "A+4 = &(A[4]): " << (A + 4) << " -> Valor (*(A+4)): " << *(A + 4) << endl << endl;
    }
}

// ============================================================================
// BLOQUE 7: Reglas de Compatibilidad de Tipos entre Punteros
// ============================================================================
namespace Concepto5_CompatibilidadTipos {
    void ejecutar() {
        cout << "=== 7. COMPATIBILIDAD DE TIPOS ===" << endl;

        int i = 42;
        double d = 3.1416;

        int *ip = &i;     
        double *dp = &d;  

        /* 
         * dp = ip; 
         * ERROR DE COMPILACION: No se pueden asignar directo tipos distintos.
         */

        // Sin embargo, sí podemos asignar los valores (*dp = *ip)
        *dp = *ip; // Asigna el valor numérico 42 (convertido a double)

        cout << "Nuevo valor en *dp despues de (*dp = *ip): " << *dp << endl << endl;
    }
}

// ============================================================================
// BLOQUE 8: Acceso Modificativo a Arrays con Punteros (Imagen 1)
// ============================================================================
namespace AccesoArraysPunteros {
    void ejecutar() {
        cout << "=== 8. ACCESO Y DESPLAZAMIENTO RELATIVO (+=" << ") ===" << endl;

        int lista[5] = {0}; 
        int *ptr;           

        ptr = lista; // Apunta al primer elemento (lista[0])
        ptr += 2;    // Avanza 2 posiciones (apunta a lista[2])
        *ptr = 5;    // Cambia lista[2] a 5

        cout << "Elemento lista[2] modificado con ptr += 2: " << lista[2] << endl << endl;
    }
}

// ============================================================================
// BLOQUE 9: Desplazamiento Secuencial con ++ y -- (Imagen 2)
// ============================================================================
namespace DesplazamientoPunteros {
    void ejecutar() {
        cout << "=== 9. INCREMENTO Y DECREMENTO (++, --) ===" << endl;

        char a[10] = "ABCDEFGHI"; 
        char *p;                  

        p = &a[0]; // Apunta al primer elemento ('A')
        cout << "Inicio -> *p: " << *p << endl;

        p++; // Avanza a 'B'
        cout << "p++    -> *p: " << *p << endl;

        p++; // Avanza a 'C'
        cout << "p++    -> *p: " << *p << endl;

        p--; // Retrocede a 'B'
        cout << "p--    -> *p: " << *p << endl << endl;
    }
}

// ============================================================================
// BLOQUE 10: Comparación de Direcciones vs Contenidos (Imagen 3)
// ============================================================================
namespace ComparacionPunteros {
    void ejecutar() {
        cout << "=== 10. COMPARACION DE PUNTEROS vs CONTENIDOS ===" << endl;

        int *ptr1, *ptr2;
        int a[2] = {10, 10}; 

        ptr1 = a;        // Apunta a a[0]
        ptr2 = ptr1 + 1; // Apunta a a[1]

        // 1. Comparar las Direcciones de Memoria
        if (ptr1 == ptr2) {
            cout << "ptr1 es igual a ptr2 (misma direccion)" << endl;
        } else {
            cout << "ptr1 NO es igual a ptr2 (distinta direccion)" << endl;
        }

        // 2. Comparar los Valores Guardados (*ptr1 == *ptr2)
        if (*ptr1 == *ptr2) {
            cout << "*ptr1 es igual a *ptr2 (mismo valor: " << *ptr1 << ")" << endl;
        } else {
            cout << "*ptr1 NO es igual a *ptr2" << endl;
        }
        cout << endl;
    }
}

// ============================================================================
// BLOQUE 11: Asignación Dinámica de Memoria con new y delete (Imagen 4)
// ============================================================================
namespace MemoriaDinamica {
    void ejecutar() {
        cout << "=== 11. MEMORIA DINAMICA (new Y delete con NULL) ===" << endl;

        // Reserva dinámica individual
        int *ptr1 = new int;         
        double *ptr2 = new double;   

        *ptr1 = 5;
        *ptr2 = 6.55;

        cout << "Valor en ptr1 (dinamico): " << *ptr1 << endl;
        cout << "Valor en ptr2 (dinamico): " << *ptr2 << endl;

        // Liberar la memoria
        delete ptr1;
        delete ptr2;

        ptr1 = NULL; 
        ptr2 = NULL;

        // Reserva dinámica de arrays
        char *c = new char[512];

        strncpy(c, "Texto almacenado en memoria dinamica mediante new char[512]", 512);
        cout << "Contenido de c: " << c << endl;

        // Liberación de arrays dinámicos
        delete[] c;
        c = NULL;

        cout << endl;
    }
}

// ============================================================================
// PUNTO DE ENTRADA PRINCIPAL
// ============================================================================
int main() {
    EjemploArray::ejecutar();
    RepresentacionMatricial::ejecutar();
    Concepto1_Direccion::ejecutar();
    Concepto2_Desreferenciacion::ejecutar();
    Concepto3_Modificacion::ejecutar();
    Concepto4_ArraysYPunteros::ejecutar();
    Concepto5_CompatibilidadTipos::ejecutar();
    AccesoArraysPunteros::ejecutar();
    DesplazamientoPunteros::ejecutar();
    ComparacionPunteros::ejecutar();
    MemoriaDinamica::ejecutar();

    cout << "=== TODO EL PROGRAMA SE HA EJECUTADO CON EXITO ===" << endl;
    return 0;
}
