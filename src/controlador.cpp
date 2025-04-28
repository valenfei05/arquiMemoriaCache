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
