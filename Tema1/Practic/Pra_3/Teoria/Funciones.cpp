#include <iostream>

using namespace std;

// ============================================================================
// CONCEPTO 1: Funciones básicas con retorno de valor (suma y resta)
// ============================================================================
namespace Concepto1_FuncionesBasicas {
    // Sintaxis: tipo_retorno nombre_funcion(tipo_par1 par1, tipo_par2 par2)
    int suma(int a, int b) { 
        int r;  
        r = a + b;  
        return r; // Devuelve el resultado al punto de llamada
    }  

    int resta(int a, int b) {  
        int r;  
        r = a - b;  
        return r; 
    } 

    void ejecutar() {
        cout << "=== 1. FUNCIONES BASICAS CON RETORNO ===" << endl;

        // Asignación directa del retorno a una variable
        int z = suma(5, 3);  
        cout << "Resultado suma(5,3) = " << z << endl;  

        int x = 5, y = 3;  
        // Distintas formas de invocar y usar el retorno de una función
        z = resta(7, 2); 
        cout << "Primer resultado (variable z): " << z << endl;  
        cout << "Segundo resultado (llamada en cout): " << resta(7, 2) << endl;  
        cout << "Tercer resultado (con variables x, y): " << resta(x, y) << endl;  
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 2: Funciones sin retorno (tipo void)
// ============================================================================
namespace Concepto2_FuncionesVoid {
    // Cuando no devuelve ningún valor, se especifica 'void'
    void funcionerror() { 
        cout << "He terminado el contador" << endl;  
        // No requiere la instrucción 'return'
    }  

    void ejecutar() {
        cout << "=== 2. FUNCIONES SIN RETORNO (VOID) ===" << endl;

        int n = 10; 
        for (int i = 0; i < n; i++) { 
            if (i == n - 1) { 
                funcionerror(); // Llamada a función void 
            }
        } 
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 3: Paso de argumentos por VALOR (copia)
// ============================================================================
namespace Concepto3_PasoPorValor {
    // Las variables 'x' e 'y' son COPIAS locales. 
    // Los cambios dentro de la función NO afectan a las variables fuera de ella.
    void altera(int x, int y) { 
        int temp; 
        temp = x; 
        x = y; 
        y = temp;  
        cout << "[Dentro de altera] x=" << x << " y=" << y << endl;  
    } 

    void ejecutar() {
        cout << "=== 3. PASO DE ARGUMENTOS POR VALOR ===" << endl;

        int x = 5, y = 3;  
        altera(x, y);  
        // Las variables originales conservan sus valores
        cout << "[Fuera de altera]  x=" << x << " y=" << y << " (Sin cambios)" << endl;  
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 4: Paso de argumentos por REFERENCIA (&)
// ============================================================================
namespace Concepto4_PasoPorReferencia {
    // Al usar '&', 'a' es una referencia directa a la variable original.
    // Modificar 'a' dentro de la función MODIFICA la variable original.
    void incrementa(int &a) { 
        a = a + 1; 
    }  

    void ejecutar() {
        cout << "=== 4. PASO DE ARGUMENTOS POR REFERENCIA (&) ===" << endl;

        int var = 1; 
        cout << "Valor de var antes: " << var << endl; // Imprime 1 
        incrementa(var); 
        cout << "Valor de var despues: " << var << endl; // Imprime 2 (Modificado)
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 5: Arrays como parámetros de funciones (1D y 2D)
// ============================================================================
namespace Concepto5_ArraysComoParametros {
    // 1D: Se pasa la dirección del primer elemento y el tamaño por separado
    void print_vector(int x[], int dim) {                             
        for (int n = 0; n < dim; n++) {
            cout << x[n] << " ";
        } 
        cout << endl;
    } 

    // 2D: En matrices estáticas es obligatorio especificar las columnas [ca]
    const int fa = 3, ca = 3; 
    void muestramatriz(double matriz[fa][ca]) { 
        cout << "Matriz (3x3):" << endl; 
        for (int i = 0; i < fa; i++) { 
            for (int j = 0; j < ca; j++) {
                cout << matriz[i][j] << " ";
            } 
            cout << endl; 
        } 
    } 

    void ejecutar() {
        cout << "=== 5. ARRAYS COMO PARAMETROS DE FUNCIONES ===" << endl;

        int x[] = {5, 10, 15};  
        int y[] = {2, 4, 6, 8, 10};  

        cout << "Vector X: ";
        print_vector(x, 3); 
        cout << "Vector Y: ";
        print_vector(y, 5); 

        cout << endl;

        double A[fa][ca] = { {2, 3, 8}, {2, 2, 4}, {2, 2, 6} }; 
        muestramatriz(A); 
        cout << endl;
    }
}

// ============================================================================
// CONCEPTO 6: Prototipos de funciones (Declaración previa)
// ============================================================================
namespace Concepto6_Prototipos {
    // Declaración del PROTOTIPO (informa al compilador que la función existe más abajo)
    double potencia(double val, int exp); 

    void ejecutar() {
        cout << "=== 6. PROTOTIPOS DE FUNCIONES ===" << endl;

        double a = 2.0; 
        int b = 3; 
        
        // Uso de la función declarada antes de su definición
        double c = potencia(a, b); 
        cout << "Calculo de " << a << "^" << b << " = " << c << endl; 
        cout << endl;
    }

    // DEFINICIÓN completa de la función
    double potencia(double val, int exp) { 
        double resultado = 1.0; 
        for (int i = 1; i <= exp; i++) { 
            resultado *= val; 
        } 
        return resultado; 
    }
}

// ============================================================================
// CONCEPTO 7: Punteros a funciones
// ============================================================================
namespace Concepto7_PunterosAFunciones {
    int suma(int a, int b) { 
        return (a + b); 
    } 

    int resta(int a, int b) { 
        return (a - b); 
    } 

    // La función 'operacion' recibe como 3er parámetro un puntero a función:
    // int (*funcion)(int, int) -> Puntero a función que recibe 2 int y devuelve int
    int operacion(int x, int y, int (*funcion)(int, int)) { 
        int g = funcion(x, y);  
        return g; 
    } 

    void ejecutar() {
        cout << "=== 7. PUNTEROS A FUNCIONES ===" << endl;

        // Pasamos la función 'suma' como argumento
        int m = operacion(7, 5, suma);  
        cout << "Operacion (7 + 5 via puntero a funcion) = " << m << endl;  

        // Pasamos la función 'resta' como argumento
        int n = operacion(20, m, resta);                                            
        cout << "Operacion (20 - " << m << " via puntero a funcion) = " << n << endl;                                                            
        cout << endl;
    }
}

// ============================================================================
// PUNTO DE ENTRADA PRINCIPAL
// ============================================================================
int main() {
    Concepto1_FuncionesBasicas::ejecutar();
    Concepto2_FuncionesVoid::ejecutar();
    Concepto3_PasoPorValor::ejecutar();
    Concepto4_PasoPorReferencia::ejecutar();
    Concepto5_ArraysComoParametros::ejecutar();
    Concepto6_Prototipos::ejecutar();
    Concepto7_PunterosAFunciones::ejecutar();

    cout << "=== PROGRAMA DE FUNCIONES CONCLUIDO CON EXITO ===" << endl;
    return 0;
}
