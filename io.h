#ifndef IO_H
#define IO_H

#include <string>

bool leerArchivoBinario(const char* ruta, unsigned char*& buffer, int& tam);
bool leerPista(const char* ruta, unsigned char*& buffer, int& tam);

#endif // IO_H
