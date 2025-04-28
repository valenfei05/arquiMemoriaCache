#include "cache.h"

Cache::Cache() : cantHits(0), cantMiss(0) {
    conjuntos.resize(8); 
    for (int i = 0; i < 8; ++i) {
        conjuntos[i] = Conjunto(); 
    }
}

void Cache::increaseHits() {
    cantHits++; 
}

void Cache::increaseMisses() {
    cantMiss++; 
}

int Cache::getHits() const {
    return cantHits; 
}

int Cache::getMisses() const {
    return cantMiss; 
}

pair<bool, pair<int, int>> Cache::isHit(int tag) {
    pair<bool, pair<int, int>> answer = {false, {-1, -1}};
    pair<bool, int> setHit = {false, -1}; 
    int i = 0;
    while (i < conjuntos.size() && !setHit.first) {
        setHit = conjuntos[i].isHit(tag); 
        if (setHit.first) {
            answer.first = true; 
            answer.second.first = i; // index
            answer.second.second = setHit.second; // via
            increaseHits();
        }
        i++;
    }

    if (!answer.first) {
        increaseMisses();
    }
    return answer;
}

unsigned char Cache::getValue(int index, int via, int offset) {
    return conjuntos[index].getValue(via, offset); 
}

void Cache::setValue(int index, int via, int offset, unsigned char valor) {
    conjuntos[index].setValue(via, offset, valor); 
}