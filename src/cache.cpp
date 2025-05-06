#include "cache.h"

Cache::Cache() {
    conjuntos.resize(8); 
    for (int i = 0; i < 8; ++i) {
        conjuntos[i] = Conjunto(); 
    }
}

int Cache::getNumeroConjuntos() const {
    return conjuntos.size();
}

const Bloque& Cache::getBloque(int index, int via) const {
    return conjuntos[index].getBloque(via);
}


pair<bool, int> Cache::isHit(int tag, int index) {
    pair<bool, int> answer = conjuntos[index].isHit(tag); 
    return answer;
}

unsigned char Cache::getValue(int index, int via, int offset) {
    conjuntos[index].increaseLRU();
    return conjuntos[index].getValue(via, offset); 
}

int Cache::getNumVias(int index) const {
    return conjuntos[index].getNumVias();
}


void Cache::setValue(int index, int via, int offset, unsigned char valor) {
    conjuntos[index].increaseLRU();
    conjuntos[index].setValue(via, offset, valor); 
}

void Cache::addBloque(int tag, int index, int via, vector<unsigned char> &datosBloque) {
    conjuntos[index].increaseLRU();
    Bloque bloque(datosBloque);
    conjuntos[index].addBloque(tag, via, bloque); 
}

int Cache::getWayLRU(int index) {
    return conjuntos[index].getWayLRU(); 
}