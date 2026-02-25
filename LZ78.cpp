#include "LZ78.h"

bool esCaracterValido(unsigned char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c == ' ');
}

bool validoLZ78(const unsigned char* buffer, int tam) {
    if (buffer == nullptr || tam <= 0)
        return false;

    //Debe ser múltiplo de 3 (2 bytes índice + 1 byte carácter)
    if (tam % 3 != 0)
        return false;

    int entradas = 0;

    //Recorrer bloques de 3 bytes
    for (int i = 0; i < tam; i += 3) {

        unsigned short indice =
            (buffer[i] << 8) | buffer[i + 1];

        unsigned char c = buffer[i + 2];

        if (!esCaracterValido(c))
            return false;

        // Validar coherencia del índice
        // No puede apuntar a una entrada que aún no existe
        if (indice > entradas + 1)
            return false;

        //6. Si todo es válido, se agrega una nueva entrada
        entradas++;
    }

    return true;
}

unsigned char* descomprimirLZ78(const unsigned char* buffer,int tam,int& tamSalida ){
    if (buffer == nullptr || tam <= 0)
        return nullptr;

    if (tam % 3 != 0)
        return nullptr;

    int maxEntradas = tam / 3;

    unsigned char** diccionario = new unsigned char*[maxEntradas + 1];
    int* longitudes = new int[maxEntradas + 1];

    int entradas = 0;

    int capacidadSalida = 1024;
    unsigned char* salida = new unsigned char[capacidadSalida];
    tamSalida = 0;

    for (int i = 0; i < tam; i += 3) {

        unsigned short indice =
            (buffer[i] << 8) | buffer[i + 1];

        unsigned char c = buffer[i + 2];

        if (indice > entradas) {
            delete[] salida;
            delete[] diccionario;
            delete[] longitudes;
            return nullptr;
        }

        int nuevaLong = (indice == 0 ? 0 : longitudes[indice]) + 1;

        unsigned char* nueva = new unsigned char[nuevaLong];

        if (indice != 0) {
            for (int j = 0; j < longitudes[indice]; j++)
                nueva[j] = diccionario[indice][j];
        }

        nueva[nuevaLong - 1] = c;

        // Expandir salida si es necesario
        if (tamSalida + nuevaLong >= capacidadSalida) {

            capacidadSalida *= 2;
            unsigned char* nuevaSalida =
                new unsigned char[capacidadSalida];

            for (int j = 0; j < tamSalida; j++)
                nuevaSalida[j] = salida[j];

            delete[] salida;
            salida = nuevaSalida;
        }

        for (int j = 0; j < nuevaLong; j++)
            salida[tamSalida++] = nueva[j];

        entradas++;
        diccionario[entradas] = nueva;
        longitudes[entradas] = nuevaLong;
    }

    // Liberar diccionario
    for (int i = 1; i <= entradas; i++)
        delete[] diccionario[i];

    delete[] diccionario;
    delete[] longitudes;

    return salida;
}
