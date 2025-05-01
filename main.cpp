/* 
Parcial práctico 2
Memoria cache
Integrantes: Valentina Feijoo y Daniel Posada.
*/

#include <iostream>
#include "./src/CPU.h"

using namespace std;

int main(){
    CPU cpu;
    int instrucciones;
    cout << "Digite la cantidad de instrucciones a ejecutar: ";
    cin >> instrucciones;
    cpu.ejecutarInstruccionesAleatorias(instrucciones);
   
    cout << "Fin de la simulacion" << endl;
    cpu.guardarRAMFinal("ram_final.txt");


    return 0;
}