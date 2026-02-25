#include "crypto.h"
#include <cstddef>
#include <iostream>
#include <cstring>

unsigned char rotarBitsDerecha(unsigned char byte, size_t n){
    n &= 7;
    return (unsigned char)((byte >> n) | ((byte << (8 - n)) & 0xFF));
}

unsigned char rotarBitsIzquierda(unsigned char byte, size_t n){
    n &= 7;
    return (unsigned char)(((byte << n) & 0xFF) | (byte >> (8 - n)));
}

unsigned char* bufferDesencriptado(const unsigned char* buffer, int tam, size_t n, size_t k){
    if (buffer == nullptr || tam <= 0)
        return nullptr;

    unsigned char* salida = new unsigned char[tam];

    for (int i = 0; i < tam; i++){
        unsigned char byte = buffer[i];

        // Paso 1: deshacer XOR
        byte ^= k;

        // Paso 2: deshacer rotación
        byte = rotarBitsDerecha(byte, n);

        salida[i] = byte;
    }

    return salida;
}
