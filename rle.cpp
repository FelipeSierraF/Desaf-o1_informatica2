#include "rle.h"

bool esDigito(unsigned char c) {
    return c >= '0' && c <= '9';
}

bool validoRLE(const unsigned char* buffer, int tam) {

    if(buffer == nullptr || tam <= 0) return false;

    int i = 0;
    int totalSalida = 0;

    while(i < tam) {

        if(!esDigito(buffer[i])) return false;

        int valor = 0;

        while(i < tam && esDigito(buffer[i])) {
            valor = valor * 10 + (buffer[i] - '0');
            i++;
        }

        if(valor <= 0 || valor > 10000) return false;

        if(i >= tam) return false;

        unsigned char c = buffer[i];

        if(c < 32 || c > 126) return false;

        totalSalida += valor;

        if(totalSalida > 1000000) return false; // protección

        i++;
    }

    return true;
}


unsigned char* descomprimirRLE(const unsigned char* buffer,int tam,int& tamSalida){
    if (buffer == nullptr || tam <= 0)
        return nullptr;

    // Primero calculamos cuánto va a medir la salida
    tamSalida = 0;
    int i = 0;

    while (i < tam) {

        if (buffer[i] < '0' || buffer[i] > '9')
            return nullptr;

        int cantidad = 0;

        while (i < tam && buffer[i] >= '0' && buffer[i] <= '9') {
            cantidad = cantidad * 10 + (buffer[i] - '0');
            i++;
        }

        if (cantidad <= 0 || i >= tam)
            return nullptr;

        tamSalida += cantidad;
        i++;
    }

    // Crear salida
    unsigned char* salida = new unsigned char[tamSalida];

    i = 0;
    int pos = 0;

    while (i < tam) {

        int cantidad = 0;

        while (i < tam && buffer[i] >= '0' && buffer[i] <= '9') {
            cantidad = cantidad * 10 + (buffer[i] - '0');
            i++;
        }

        unsigned char simbolo = buffer[i];
        i++;

        for (int j = 0; j < cantidad; j++)
            salida[pos++] = simbolo;
    }

    return salida;
}
