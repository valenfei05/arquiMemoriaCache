#include "RAM.h"
#include <fstream>
#include <sstream>
#include <iomanip>

RAM::RAM() {
    memoria.resize(2048); 
    ifstream infile("ram_data.txt");

    if (infile.is_open()) {
        string line;
        for (int i = 0; i < 2048 && getline(infile, line); ++i) {
            int valor = 0;
            stringstream ss;
            ss << hex << line;
            ss >> valor;
            memoria[i] = static_cast<unsigned char>(valor);
        }
        infile.close();
    } else {
        // Si no hay archivo, inicializa aleatoriamente
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < 2048; ++i) {
            memoria[i] = static_cast<unsigned char>(rand() % 256);
        }
        guardar();
    }
}


unsigned char RAM::leerByte(int direccion) const {
    return memoria[direccion];
}

void RAM::escribirByte(int direccion, unsigned char dato) {
    memoria[direccion] = dato;
}

/* void RAM::imprimir() const {
    cout << "\n=== Estado final de la RAM ===" << endl;
    for (int i = 0; i < 2048; ++i) {
        cout << "RAM[" << setw(4) << setfill('0') << i << "] = "
             << hex << uppercase << setw(2) << setfill('0')
             << static_cast<int>(memoria[i]) << endl;
    }
    cout << dec;
} */

void RAM::guardarFinal(const string& nombreArchivo) const {
    ofstream outfile(nombreArchivo);
    if (outfile.is_open()) {
        for (int i = 0; i < 2048; ++i) {
            outfile << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(memoria[i]) << endl;
        }
        outfile.close();
        cout << "RAM final guardada en " << nombreArchivo << endl;
    } else {
        cout << "[ERROR] No se pudo guardar la RAM final." << endl;
    }
}



void RAM::guardar() {
    ofstream outfile("ram_data.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < 2048; ++i) {
            outfile << hex << uppercase << setw(2) << setfill('0') << static_cast<int>(memoria[i]) << endl;
        }
        outfile.close();
    } else {
        cout << "[ERROR] No se pudo abrir el archivo para guardar los datos." << endl;
    }
}
