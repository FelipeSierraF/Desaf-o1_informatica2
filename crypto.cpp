#include "crypto.h"
#include <cstddef>
#include <iostream>
#include <cstring>

unsigned char rotarBitsDerecha(unsigned char byte, size_t n)
{
    n = n % 8;
    return (byte >> n) | (byte << (8 - n));
}

unsigned char* bufferDesencriptado(const unsigned char* buffer, int tam, size_t n, size_t k)
{
    if (buffer == nullptr || tam <= 0)
        return nullptr;

    unsigned char* resultado = new unsigned char[tam];

    for (int i = 0; i < tam; i++)
    {
        // Paso 1: Deshacer XOR con k
        unsigned char paso1 = buffer[i] ^ (unsigned char)k;

        // Paso 2: Deshacer la rotación de bits (rotar en sentido contrario)
        resultado[i] = rotarBitsDerecha(paso1, n);
    }

    return resultado;
}
