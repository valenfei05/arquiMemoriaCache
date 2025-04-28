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

        vector<unsigned char> leerBloque(int base) const; 
        void escribirBloque(int base, const vector<unsigned char>& bloque);
};  


#endif