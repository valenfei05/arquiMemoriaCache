#include "CPU.h"

#include <iostream>
#include <string>
#include <fstream> 
#include <ctime>

CPU::CPU(){
    controlador = Controlador();
    srand(static_cast<unsigned int>(time(0)));
}

pair<string, pair<int, unsigned char>> CPU::generarInstruccionAleatoria() {
    string operacion = (rand() % 2 == 0) ? "lectura" : "escritura";
    int direccion = rand() % 2048;
    unsigned char dato = static_cast<unsigned char>(rand() % 256); 
    return {operacion, {direccion, dato}};
}


void CPU::ejecutarInstruccionesAleatorias(int numInstrucciones) {
    unsigned char datoRead = 0;

    ofstream archivo("resultados.csv");
    archivo << "Acceso,Misses,TasaFallos\n";


    for (int i = 0; i < numInstrucciones; i++) {
        cout << "Instruccion " << (i + 1) << ": " << endl;
        pair<string, pair<int, unsigned char>> instruccion = generarInstruccionAleatoria();
        string operacion = instruccion.first;
        int direccion = instruccion.second.first;
        unsigned char datoWrite = instruccion.second.second;

        if (operacion == "lectura") {
            datoRead = controlador.procesarLectura(direccion);
            cout << "Lectura de la direccion " << direccion << ": " << static_cast<int>(datoRead) << endl;
        } else {
            controlador.procesarEscritura(direccion, datoWrite);
            cout << "Escritura en la direccion " << direccion << ": " << static_cast<int>(datoWrite) << endl;
        }

        cout << " --> " << (controlador.fueUltimoHit() ? "HIT" : "MISS") << endl;
        controlador.mostrarEstadisticas(); 


        // Calcular tasa de fallos acumulada hasta el acceso actual
        int total = controlador.getTotalAccesos();
        int fallos = controlador.getMisses();
        double tasaFallos = (total > 0) ? static_cast<double>(fallos) / total * 100.0 : 0.0;

        // Registrar acceso y tasa en el CSV
        if ((i + 1) % 5 == 0 || (i + 1) == numInstrucciones) {
            float missRate = static_cast<float>(controlador.getMisses()) / controlador.getTotalAccesos();
            archivo << (i + 1) << "," << controlador.getMisses() << "," << (missRate * 100.0f) << "\n";
        }
        
    }

    archivo.close(); 
    //controlador.mostrarEstadisticas();
}
/* 
void CPU::imprimirRAM() const {
    controlador.imprimirRAM(); // lo defines tú ahora
}
 */

 void CPU::guardarRAMFinal(const string& nombreArchivo) const {
    controlador.guardarRAMFinal(nombreArchivo);
}

