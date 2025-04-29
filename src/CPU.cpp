#include "CPU.h"

#include <iostream>
#include <string>

CPU::CPU(){
    controlador = Controlador();
}

pair<string, pair<int, unsigned char>> CPU::generarInstruccionAleatoria() {
    string operacion = (rand() % 2 == 0) ? "lectura" : "escritura";
    int direccion = rand() % 2048;
    unsigned char dato = static_cast<unsigned char>(rand() % 256); 

    return {operacion, {direccion, dato}};
}

void CPU::ejecutarInstruccionesAleatorias(int numInstrucciones) {
    unsigned char datoRead = 0; 
    for (int i = 0; i < numInstrucciones; i++) {
        pair<string, pair<int, unsigned char>> instruccion = generarInstruccionAleatoria();
        string operacion = instruccion.first;
        int direccion = instruccion.second.first;
        unsigned char datoWrite = instruccion.second.second;

        if (operacion == "lectura") {
            datoRead = controlador.procesarLectura(direccion);
            cout << "Lectura de la direccion " << direccion << ": " << static_cast<int>(datoRead) << endl;
        } 
        else {
            controlador.procesarEscritura(direccion, datoWrite);
            cout << "Escritura en la direccion " << direccion << ": " << static_cast<int>(datoWrite) << endl;
        }

    }
    controlador.mostrarEstadisticas();
}