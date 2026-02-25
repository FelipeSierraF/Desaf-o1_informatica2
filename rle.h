#ifndef RLE_H
#define RLE_H

bool validoRLE(const unsigned char* buffer, int tam);
unsigned char* descomprimirRLE(const unsigned char* buffer,int tam,int& tamSalida);

#endif // RLE_H
