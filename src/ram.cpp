#include "RAM.h"
#include <cstdlib> 
#include <ctime>   

RAM::RAM() {
    memoria.resize(2048); 
    srand(static_cast<unsigned int>(time(0)));

    //se llena la memoria con bytes aleatorioss
    for (int i = 0; i < 2048; ++i) {
        memoria[i] = static_cast<unsigned char>(rand() % 256);
    }
}

unsigned char RAM::leerByte(int direccion) const {
    return memoria[direccion];
}

void RAM::escribirByte(int direccion, unsigned char dato) {
    memoria[direccion] = dato;
}

/*
vector<unsigned char> RAM::leerBloque(int direccionBase) const {
    vector<unsigned char> bloque(16);
    for (int i = 0; i < 16; ++i) {
        bloque[i] = memoria[direccionBase + i];
    }
    return bloque;
}

void RAM::escribirBloque(int direccionBase, const vector<unsigned char>& bloque) {
    for (int i = 0; i < 16; ++i) {
        memoria[direccionBase + i] = bloque[i];
    }
}
*/