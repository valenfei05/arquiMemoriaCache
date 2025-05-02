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


        bool ultimoFueHit;

    public:
        Controlador(); 
        
        pair<bool, int> isHit(int tag, int index);
        pair<int, pair<int, int>> splitAddress(int direccion);

        unsigned char getRAMValue(int direccion);
        void setRAMValue(int direccion, unsigned char valor);
        unsigned char getCacheValue(int index, int via, int offset);
        int selectVia(int index);
        void setCacheValue(int index, int via, int offset, unsigned char valor);


        void validarLRU(int index);
        void increaseHits();
        void increaseMisses();
        void increaseTotalAccesos();
        int getHits() const;
        int getMisses() const;
        int getTotalAccesos() const;

        unsigned char procesarLectura(int direccion);   
        unsigned char procesarEscritura(int direccion, unsigned char dato);

        void mostrarEstadisticas() const; 


        bool fueUltimoHit() const;
        void guardarRAMFinal(const string& nombreArchivo) const;
        
       // void imprimirRAM() const;

    };


#endif