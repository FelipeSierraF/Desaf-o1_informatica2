#include "io.h"
#include <iostream>
#include <fstream>
#include <cstdio>




//Funcion que recibe los parametros de nombre, buffer y tam
/*
    ruta: contiene la ruta y el ruta del archivo que buscamos
    buffer: contiene el archivo leido en binario
    tam: Variable con la que medimos el tamaño del archivo
*/
bool leerArchivoBinario(const char* ruta, unsigned char*& buffer, int& tam){
    FILE* archivo = fopen(ruta, "rb");
    if (!archivo)
        return false;

    // Obtener tamaño
    fseek(archivo, 0, SEEK_END);
    long size = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    if (size <= 0)
    {
        fclose(archivo);
        return false;
    }

    buffer = new unsigned char[size];
    if (!buffer)
    {
        fclose(archivo);
        return false;
    }

    size_t leidos = fread(buffer, 1, size, archivo);
    fclose(archivo);

    if ((long)leidos != size)
    {
        delete[] buffer;
        buffer = nullptr;
        return false;
    }

    tam = (int)size;
    return true;
}

bool leerPista(const char* ruta, unsigned char*& buffer, int& tam){
    FILE* archivo = fopen(ruta, "rb");
    if (!archivo)
        return false;

    // Obtener tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long size = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    if (size <= 0)
    {
        fclose(archivo);
        return false;
    }

    // Reservar memoria
    buffer = new unsigned char[size];
    if (!buffer)
    {
        fclose(archivo);
        return false;
    }

    // Leer contenido
    size_t leidos = fread(buffer, 1, size, archivo);
    fclose(archivo);

    if ((long)leidos != size)
    {
        delete[] buffer;
        buffer = nullptr;
        return false;
    }

    tam = (int)size;
    return true;
}
