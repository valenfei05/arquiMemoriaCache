#include "Bloque.h"


Bloque::Bloque(){
    valido = false;
    tag = 0;
    lru = 0;
    datos.resize(16);
    for (int i = 0; i < 16; ++i) {
        datos[i] = 0;
    }
}


bool Bloque::esValido() const {
    return valido;
}

void Bloque::setValido(bool v) {
    valido = v;
}

int Bloque::getTag() const {
    return tag;
}

void Bloque::setTag(int t) {
    tag = t;
}

int Bloque::getLRU() const {
    return lru;
}

void Bloque::setLRU(int valor) {    
    lru = valor;
}

unsigned char Bloque::leerDato(int offset) const {
    return datos[offset];
}

void Bloque::escribirDato(int offset, unsigned char valor) {
    datos[offset] = valor;
}

void Bloque::inicializarDatos(const vector<unsigned char>& datosBloque) {
    for (int i = 0; i < 16; ++i) {
        datos[i] = datosBloque[i];
    }
}
