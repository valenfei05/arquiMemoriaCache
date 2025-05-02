#ifndef CPU_H
#define CPU_H

#include "ram.h"
#include "cache.h"
#include "controlador.h"
#include <string>

using namespace std;

class CPU {
    private: 
        Controlador controlador;
    public:
        CPU();
        pair<string, pair<int, unsigned char>> generarInstruccionAleatoria();
        void ejecutarInstruccionesAleatorias(int numInstrucciones);
        //void imprimirRAM() const;
        void guardarRAMFinal(const string& nombreArchivo) const;
        

};

#endif