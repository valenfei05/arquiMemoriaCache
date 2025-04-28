#include "controlador.h"

#include <iostream>
#include <vector>

Controlador::Controlador() : hits(0), Miss(0), totalAccesos(0) {
    ram = RAM();
    cache = Cache(); 
}

Controlador::pair<bool, pair<int, int>> Controlador::isHit(int tag) {
    return cache.isHit(tag); 
}

Controlador::pair<int, pair<int, int>> Controlador::splitAddress(int direccion) {
    // Offset = bits [3:0] → máscara 0xF (0000 1111)
    int offset = direccion & 0xF;
    // Index = bits [6:4] → desplazar 4, máscara 0x7 (0000 0111)
    int index  = (direccion >> 4) & 0x7;
    // Tag = bits [10:7] → desplazar 7, máscara 0xF (0000 1111)
    int tag    = (direccion >> 7) & 0xF;
    return {tag, {index, offset}}; 
}

Controlador::unsigned char Controlador::getRAMValue(int direccion) {
    return ram.leerDato(direccion); 
}

Controlador::void Controlador::setRAMValue(int direccion, unsigned char valor) {
    ram.escribirDato(direccion, valor); 
}

Controlador::unsigned char Controlador::getCacheValue(int index, int via, int offset) {
    return cache.getValue(index, via, offset); 
}

Controlador::void Controlador::setCacheValue(int index, int via, int offset, unsigned char valor) {
    cache.setValue(index, via, offset, valor); 
}

Controlador::void Controlador::increaseHits() {
    hits++; 
}

Controlador::void Controlador::increaseMisses() {
    Miss++; 
}

Controlador::void Controlador::increaseTotalAccesos() {
    totalAccesos++; 
}

Controlador::int Controlador::getHits() const {
    return hits; 
}

Controlador::int Controlador::getMisses() const {
    return Miss; 
}

Controlador::int Controlador::getTotalAccesos() const {
    return totalAccesos; 
}

int Controlador::selectVia(int index) {
    int numVias = cache.getNumVias(); 
    int via = 0;
    if (numVias == 4)
        via = cache.getWayLRU(index);
    else
        via = numVias;
    return via; 
}

Controlador::unsigned char Controlador::procesarLectura(int direccion) {
    pair<int, pair<int, int>> dir = splitAddress(direccion);
    pair<int, int> indexOffset = dir.second;
    int tag = dir.first;
    int index = indexOffset.first, offset = indexOffset.second;

    pair<bool, int> infoHit = isHit(tag);
    bool isHit = infoHit.first;
    int via = infoHit.second;

    increaseTotalAccesos();
    unsigned char answer;
    vector<unsigned char> datosBloque(16, 0);

    if (isHit) {
        increaseHits();
    } 
    else {
        increaseMisses();
        int i, direccionBaseBloque = direccion & ~0xF; 
        for (i = 0; i < 16; ++i) {
            datosBloque[i] = getRAMValue(direccionBaseBloque + i);
        }
        via = selectVia(index);
        cache.agregarBloque(tag, index, via, datosBloque); 
    }

    answer = getCacheValue(index, via, offset);
    return answer; 
}