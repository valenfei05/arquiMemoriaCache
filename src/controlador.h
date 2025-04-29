#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "ram.h"
#include "cache.h"
#include <string>

using namespace std;

class Controlador {
    private:
        RAM ram;             
        Cache cache;    
        int hits;
        int Miss;        
        int totalAccesos;    
    
    public:
        Controlador(); 
        
        pair<bool, pair<int, int>> isHit(int tag);
        pair<int, pair<int, int>> splitAddress(int direccion);

        unsigned char getRAMValue(int direccion);
        void setRAMValue(int direccion, unsigned char valor);
        unsigned char getCacheValue(int index, int via, int offset);
        int selectVia(int index, int tag);
        void setCacheValue(int index, int via, int offset, unsigned char valor);

        void increaseHits();
        void increaseMisses();
        void increaseTotalAccesos();
        int getHits() const;
        int getMisses() const;
        int getTotalAccesos() const;

        unsigned char procesarLectura(int direccion);   
        unsigned char procesarEscritura(int direccion, unsigned char dato);

        void mostrarEstadisticas() const; 

    };


#endif