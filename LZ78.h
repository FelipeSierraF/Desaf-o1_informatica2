#ifndef LZ78_H
#define LZ78_H

bool validoLZ78(const unsigned char* buffer, int tam);
unsigned char* descomprimirLZ78(const unsigned char* buffer,int tam,int& tamSalida);

#endif // LZ78_H
