/* 
Parcial práctico 2
Memoria cache
Integrantes: Valentina Feijoo y Daniel Posada.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "./src/CPU.h"

using namespace std;

struct Instruccion {
    char tipo; 
    int direccion;
    string dato; 
};

vector<Instruccion> leerInstruccionesDeArchivo(const string& nombreArchivo) {
    vector<Instruccion> instrucciones;
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Instruccion inst;
        ss >> inst.tipo >> inst.direccion;

        if (inst.tipo == 'W') {
            ss >> inst.dato;
        }

        instrucciones.push_back(inst);
    }

    return instrucciones;
}

int main() {
    CPU cpu;
    int modo;
    cout << "Simulacion memoria Cache :\n1. Instrucciones aleatorias\n2. Leer instrucciones desde archivo\n";
    cout << "Seleccione la opcion que desea: ";
    cin >> modo;

    if (modo == 1) {
        int instrucciones;
        cout << "Digite la cantidad de instrucciones a ejecutar: ";
        cin >> instrucciones;
        cpu.ejecutarInstruccionesAleatorias(instrucciones);

    } else if (modo == 2) {
        string nombreArchivo;
        cout << "Ingrese el nombre del archivo: ";
        cin >> nombreArchivo;

        vector<Instruccion> instrucciones = leerInstruccionesDeArchivo(nombreArchivo);

        for (Instruccion inst : instrucciones) {
            if (inst.tipo == 'R') {
                cpu.leer(inst.direccion);
            } else if (inst.tipo == 'W') {
                cpu.escribir(inst.direccion, inst.dato);
            } else {
                cout << "Instruccion invalida: " << inst.tipo << endl;
            }
        }
    } else {
        cout << "Opcion invalida." << endl;
        return 1;
    }

    cout << "Fin de la simulacion" << endl;
    cpu.guardarRAMFinal("ram_final.txt");

    return 0;
}
