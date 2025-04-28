#ifndef CACHE_H
#define CACHE_H

#include "conjunto.h"
#include <vector>

class Cache {
    private: 
        int cantHits;
        int cantMiss; 
        vector<Conjunto> conjuntos; 
    public:
        Cache(); 
        void increaseHits(); 
        void increaseMisses(); 
        int getHits() const;
        int getMisses() const;

        pair<bool, pair<int, int>> isHit(int); // Verifica si hay un hit en la cache, devuelve un par con el index y la vía
        unsigned char getValue(int index, int via, int offset); 
        void setValue(int index, int via, int offset, unsigned char valor); 
};

#endif 