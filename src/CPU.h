#ifndef CPU_H
#define CPU_H

#include "ram.h"
#include "cache.h"
#include "controlador.h"

class CPU {
    private: 
        RAM ram; 
        Cache cache; 
        Controlador controlador;
    public:
        CPU();
        void ejecutarInstruccionesAleatorias(int numInstrucciones);
        pair<string, pair<int, unsigned char>> generarInstruccionAleatoria();
};

#endif