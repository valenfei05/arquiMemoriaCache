#include "controlador.h"

#include <iostream>
#include <vector>
#include <fstream>

Controlador::Controlador() : hits(0), Miss(0), totalAccesos(0) {
    ram = RAM();
    cache = Cache(); 
}

pair<bool, int> Controlador::isHit(int tag, int index) {
    return cache.isHit(tag, index); 
}

pair<int, pair<int, int>> Controlador::splitAddress(int direccion) {
    // Offset = bits [3:0] → máscara 0xF (0000 1111)
    int offset = direccion & 0xF;
    // Index = bits [6:4] → desplazar 4, máscara 0x7 (0000 0111)
    int index  = (direccion >> 4) & 0x7;
    // Tag = bits [10:7] → desplazar 7, máscara 0xF (0000 1111)
    int tag    = (direccion >> 7) & 0xF;
    return {tag, {index, offset}}; 
}

unsigned char Controlador::getRAMValue(int direccion) {
    return ram.leerByte(direccion); 
}

void Controlador::setRAMValue(int direccion, unsigned char valor) {
    ram.escribirByte(direccion, valor); 
}

unsigned char Controlador::getCacheValue(int index, int via, int offset) {
    return cache.getValue(index, via, offset); 
}

void Controlador::setCacheValue(int index, int via, int offset, unsigned char valor) {
    cache.setValue(index, via, offset, valor); 
}

void Controlador::increaseHits() {
    hits++; 
}

void Controlador::increaseMisses() {
    Miss++; 
}

void Controlador::increaseTotalAccesos() {
    totalAccesos++; 
}

int Controlador::getHits() const {
    return hits; 
}

int Controlador::getMisses() const {
    return Miss; 
}

int Controlador::getTotalAccesos() const {
    return totalAccesos; 
}

int Controlador::selectVia(int index) {
    int numVias = cache.getNumVias(index); 
    int via = 0;
    if (numVias == 4)
        via = cache.getWayLRU(index);
    else
        via = numVias;
    return via; 
}

unsigned char Controlador::procesarLectura(int direccion) {
    pair<int, pair<int, int>> dir = splitAddress(direccion);
    pair<int, int> indexOffset = dir.second;
    int tag = dir.first;
    int index = indexOffset.first, offset = indexOffset.second;

    pair<bool, int> infoHit = isHit(tag, index);
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
        cache.addBloque(tag, index, via, datosBloque); 
    }

    answer = getCacheValue(index, via, offset);
    return answer; 
}

unsigned char Controlador::procesarEscritura(int direccion, unsigned char dato) {
    pair<int, pair<int, int>> dir = splitAddress(direccion);
    int tag = dir.first;
    int index = dir.second.first;
    int offset = dir.second.second;

    pair<bool, int> infoHit = isHit(tag, index);
    bool esHit = infoHit.first;
    int via = infoHit.second;

    increaseTotalAccesos();


    if (esHit) {
        increaseHits();
        setCacheValue(index, via, offset, dato);
        setRAMValue(direccion, dato); // write-through
        return dato;
    }

    increaseMisses();

    vector<unsigned char> datosBloque(16, 0);
    int baseDireccion = direccion & ~0xF;
    for (int i = 0; i < 16; ++i) {
        datosBloque[i] = getRAMValue(baseDireccion + i);
    }

    datosBloque[offset] = dato;

    via = selectVia(index);
    cache.addBloque(tag, index, via, datosBloque);
    setRAMValue(direccion, dato);

    return dato;
}


void Controlador::mostrarEstadisticas() const {
    double tasaFallos = (totalAccesos > 0) ? (static_cast<double>(Miss) / totalAccesos) * 100.0 : 0.0;

    // Mostrar por consola
    cout << "Total accesos: " << totalAccesos << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << Miss << endl;
    cout << "Tasa de fallos: " << tasaFallos << "%" << endl;

    // Guardar en CSV
    ofstream archivo("resultados.csv");
    if (archivo.is_open()) {
        archivo << "TotalAccesos,Hits,Misses,TasaFallos\n";
        archivo << totalAccesos << "," << hits << "," << Miss << "," << tasaFallos << "\n";
        archivo.close();
        cout << "Archivo resultados.csv generado correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo para escribir resultados." << endl;
    }
}
