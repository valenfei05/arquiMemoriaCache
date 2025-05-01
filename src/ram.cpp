#include "RAM.h"
#include <cstdlib> 
#include <ctime>   

RAM::RAM() {
    memoria.resize(2048); 
    ifstream infile("./ram_data.txt");
    if (infile.is_open()) {
        string line;
        for (int i = 0; i < 2048; ++i) {
            getline(infile, line);
            memoria[i] = static_cast<unsigned char>(line[0]);
        }
        infile.close();
    }
}

unsigned char RAM::leerByte(int direccion) const {
    return memoria[direccion];
}

void RAM::guardar() {
    ofstream outfile("./ram_data.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < 2048; ++i) {
            outfile << memoria[i] << endl;
        }
        outfile.close();
    } else {
        cout << "[ERROR] No se pudo abrir el archivo para guardar los datos." << endl;
    }
}

void RAM::escribirByte(int direccion, unsigned char dato) {
    memoria[direccion] = dato;
    guardar(); 
}


/* void RAM::imprimir () const {
    for (int i = 0; i < memoria.size(); ++i) {
        cout << "RAM[" << i << "] = " << static_cast<int>(memoria[i]) << endl;
    }
} */
