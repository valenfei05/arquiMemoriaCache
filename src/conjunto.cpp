#include "conjunto.h"
#include <iostream>

Conjunto::Conjunto() { 
    vias.resize(4);
    for (int i = 0; i < 4; ++i) {
        vias[i] = Bloque(); 
    } 
    numVias = 0; 
}

void Conjunto::increaseLRU() {
    int valLRU = 0;
    for (int i = 0; i < numVias; ++i) {
        valLRU = vias[i].getLRU();
        vias[i].setLRU(valLRU + 1); 
    }
}

int Conjunto::getNumVias() const {
    return numVias; 
}

const Bloque& Conjunto::getBloque(int via) const {
    return vias[via];
}


pair<bool, int> Conjunto::isHit(int tag) {
    pair<bool, int> answer = {false, -1};
    int i = 0;
    while (i < numVias && !answer.first) {
        if (vias[i].esValido() && vias[i].getTag() == tag) {
            answer.first = true;
            answer.second = i; 
            increaseLRU();
            vias[i].setLRU(0); 
        }
        i++;
    }
    return answer; 
}

unsigned char Conjunto::getValue(int via, int offset) {
    /* if (via < 0 || via >= 4) {
        cout << "[ERROR] vía fuera de rango: " << via << endl;
        break
    } */
    vias[via].setLRU(0);
    return vias[via].leerDato(offset); 
}

void Conjunto::setValue(int via, int offset, unsigned char valor) {
    /* if (via < 0 || via >= 4) {
        cout << "[ERROR] vía fuera de rango: " << via << endl;
        break
    } */
    vias[via].setLRU(0);
    vias[via].escribirDato(offset, valor); 
}

void Conjunto::addBloque(int tag, int via, Bloque &bloque) {
    bloque.setTag(tag);
    bloque.setValido(true);
    bloque.setLRU(0);
    vias[via] = bloque;

    if (via >= numVias) {
        numVias = via + 1;
    }
}


int Conjunto::getWayLRU() const {
    int i, answer = 0;
    int maxLRU = vias[0].getLRU();
    for (i = 1; i < numVias; i++) {
        if (vias[i].getLRU() > maxLRU) {
            maxLRU = vias[i].getLRU();
            answer = i; 
        }
    }
    return answer;
}