/* 
Parcial práctico 2
Memoria cache
Integrantes: Valentina Feijoo y Daniel Posada.

*/

#include <iostream>
#include "CPU.h"
#include "controlador.h"

using namespace std;

int main(){

    //falta crear clase cpu 
    //CPU cpu;
    Controlador controlador;

    int instrucciones = 50;

    for(int i = 0; i < instrucciones; i++){


        //el metodo generarinstruccion deberia crear aleatoreamente una operacion como dice maribel jeje
        // el formato es: tipo de instruccion(lectura o escritura), direccion, y dato
        pair<string, pair<int, unsigned char>> instruccion = cpu.generarInstruccion();
        string operacion = instruccion.first;
        int direccion = instruccion.second.first;
        unsigned char dato = instruccion.second.second;

        if (operacion == "lectura") {
            controlador.procesarLectura(direccion);
        } else {
            controlador.procesarEscritura(direccion, dato);
        }

        controlador.mostrarEstadisticas();

    }

    return 0;
}