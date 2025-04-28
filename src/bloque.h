#ifndef BLOQUE_H
#define BLOQUE_H

#include <vector>

using namespace std;

class Bloque {

    private:
        bool valido;
        int tag;
        int lru;
        vector<unsigned char> datos;  

    public:
        Bloque();

        bool esValido() const;
        void setValido(bool v);

        int getTag() const;
        void setTag(int t);

        int getLRU() const;
        void setLRU(int valor);

        unsigned char leerDato(int offset) const;
        void escribirDato(int offset, unsigned char valor);

        // No entiendo como la funcion inicializarDatos, si no se supone que la cache inicie con ningun dato
        void inicializarDatos(const vector<unsigned char>& datosBloque);

};

#endif 