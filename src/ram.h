#ifndef RAM_H
#define RAM_H
#include <vector>
#include <list>
#include <iostream>
#include <array>

using namespace std;

class RAM{
    private:
        vector<char> memoria;
    
    public:
        RAM();
        unsigned char leerByte(int direccion) const;
        void escribirByte(int direccion, unsigned char dato);

        /* Según lo que me dijo Juliana, la profe no quiere esto, solo quiere que se lea y escriba 1 byte a la vez
        vector<unsigned char> leerBloque(int base) const; 
        void escribirBloque(int base, const vector<unsigned char>& bloque);*/
};  

#endif