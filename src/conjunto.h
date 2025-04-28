#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <vector>
#include "bloque.h"

using namespace std;

class Conjunto {
    private:
        vector<Bloque> vias; 
        int numVias;         

    public:
        Conjunto(); 

        void increaseLRU();
        int getNumVias() const;
        pair<bool, int> isHit(int tag); 
        unsigned char getValue(int via, int offset); 
        void setValue(int via, int offset, unsigned char valor); 
}

#endif 