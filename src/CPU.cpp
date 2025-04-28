#include "CPU.h"

#include <iostream>
#include <string>

CPU::CPU(){
    ram = RAM();
    cache = Cache();
    controlador = Controlador();
}

pair<string, pair<int, unsigned char>> CPU::generarInstruccionAleatoria() {
    string operacion = (rand() % 2 == 0) ? "lectura" : "escritura";
    int direccion = rand() % 2048;
    unsigned char dato = static_cast<unsigned char>(rand() % 256); 

    return {operacion, {direccion, dato}};
}

void CPU::ejecutarInstruccionesAleatorias(int numInstrucciones) {
    for (int i = 0; i < numInstrucciones; i++) {
        pair<string, pair<int, unsigned char>> instruccion = generarInstruccionAleatoria();
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
}