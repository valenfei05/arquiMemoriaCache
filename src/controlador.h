#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "ram.h"
#include "Cache.h"
#include <string>

using namespace std;

class Controlador {
    private:
        RAM ram;             
        //Cache cache;     CLASE cache   
        int hits;
        int Miss;        
        int totalAccesos;    
    
    public:
        Controlador();  
        void procesarLectura(int direccion);   
        void procesarEscritura(int direccion, unsigned char dato);  
        void mostrarEstadisticas() const; 

    };


#endif