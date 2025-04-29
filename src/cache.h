#ifndef CACHE_H
#define CACHE_H

#include "conjunto.h"
#include "bloque.h"
#include <vector>

class Cache {
    private: 
        vector<Conjunto> conjuntos; 
    public:
        Cache(); 

        int getWayLRU(int index); // Devuelve la vía menos recientemente usada
        int getNumVias(int index) const;

        pair<bool, int>isHit(int tag, int index); // Verifica si hay un hit en la cache, devuelve un par con el index y la vía
        unsigned char getValue(int index, int via, int offset); 
        void setValue(int index, int via, int offset, unsigned char valor);
        void addBloque(int tag, int index, int via, vector<unsigned char> &datosBloque); // Añade un bloque a la cache
};

#endif 