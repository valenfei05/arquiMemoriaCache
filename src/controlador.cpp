#include "controlador.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

Controlador::Controlador() : hits(0), Miss(0), totalAccesos(0), ultimoFueHit(false) {
    ram = RAM();
    cache = Cache(); 
}

pair<bool, int> Controlador::isHit(int tag, int index) {
    return cache.isHit(tag, index); 
}

pair<int, pair<int, int>> Controlador::splitAddress(int direccion) {
    int offset = direccion & 0xF;
    int index  = (direccion >> 4) & 0x7;
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
    int tag = dir.first;
    int index = dir.second.first;
    int offset = dir.second.second;

    pair<bool, int> infoHit = isHit(tag, index);
    bool isHit = infoHit.first;
    int via = infoHit.second;

    increaseTotalAccesos();
    unsigned char answer;
    vector<unsigned char> datosBloque(16, 0);

    if (isHit) {
        increaseHits();
        ultimoFueHit = true;
    } else {
        increaseMisses();
        ultimoFueHit = false;
        int base = direccion & ~0xF;
        for (int i = 0; i < 16; ++i) {
            datosBloque[i] = getRAMValue(base + i);
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
        ultimoFueHit = true;
        setCacheValue(index, via, offset, dato);
        setRAMValue(direccion, dato); // Write-through
        return dato;
    }

    increaseMisses();
    ultimoFueHit = false;

    vector<unsigned char> datosBloque(16, 0);
    int baseDireccion = direccion & ~0xF;
    for (int i = 0; i < 16; ++i) {
        datosBloque[i] = getRAMValue(baseDireccion + i);
    }
        // Añade esto después del for que carga datosBloque:
    cout << "Bloque cargado desde DRAM (direcciones " 
    << hex << uppercase << baseDireccion << " a " << (baseDireccion + 15) << "): ";
    for (int i = 0; i < 16; ++i) {
    cout << setw(2) << setfill('0') << static_cast<int>(datosBloque[i]) << " ";
    }
    cout << dec << endl;

    datosBloque[offset] = dato;
    via = selectVia(index);
    cache.addBloque(tag, index, via, datosBloque);
    setRAMValue(direccion, dato);

    return dato;
}

void Controlador::mostrarEstadisticas() const {
    double tasaFallos = (totalAccesos > 0) ? (static_cast<double>(Miss) / totalAccesos) * 100.0 : 0.0;

    cout << "\n=== Estadisticas ===" << endl;
    cout << "Total de accesos: " << totalAccesos << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << Miss << endl;
    cout << "Tasa de fallos: " << tasaFallos << "%" << endl;

    cout << "\n=== Estado actual de la Cache ===" << endl;

    for (int i = 0; i < 8; ++i) {
        cout << "Conjunto " << i << ":" << endl;
        for (int j = 0; j < 4; ++j) {
            const Bloque& bloque = cache.getBloque(i, j);
            cout << "  Via " << j << ": ";
            if (bloque.esValido()) {
                cout << "Valido | Tag: " << bloque.getTag() << " | LRU: " << bloque.getLRU() << " | Datos: ";
                for (int k = 0; k < 16; ++k) {
                    cout << hex << static_cast<int>(bloque.leerDato(k)) << " ";
                }
                cout << dec;
            } else {
                cout << "Invalido";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void Controlador::guardarRAMFinal(const string& nombreArchivo) const {
    ram.guardarFinal(nombreArchivo);
}


/* void Controlador::imprimirRAM() const {
    ram.imprimir();
}
 */
bool Controlador::fueUltimoHit() const {
    return ultimoFueHit;
}

