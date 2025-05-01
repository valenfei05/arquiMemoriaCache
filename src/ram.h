#ifndef RAM_H
#define RAM_H
#include <vector>
#include <iostream>

using namespace std;

class RAM{
    private:
        vector<unsigned char> memoria;

    public:
        RAM();
        unsigned char leerByte(int direccion) const;
        void escribirByte(int direccion, unsigned char dato);
        
        //void imprimir() const;
};  

#endif