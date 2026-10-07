#include <iostream>    
using namespace std;	
// el programa calcula los numeros de Armstrong entre 0 y 999. Un numero de 
// Armstrong, es un numero tal que la suma de sus digitos al cubo es igual al 
// propio numero. Por ejemplo el 371, ya que 371=3*3*3+7*7*7+1*1*1
int main()
{   
int abc, a3b3c3, contador=0;
for (int a=0;a<=9; a++) {
    for (int b=0;b<=9; b++) {
        for (int c=0;c<=9; c++) {
            abc=a*100+b*10+c;
            a3b3c3=(a*a*a)+(b*b*b)+(c*c*c);
            if (abc==a3b3c3) {
               contador=contador +1;
               cout << "Armstrong number " << contador << ":   " << abc << endl;
               }
            }
        }
    }
        return 0;
}
