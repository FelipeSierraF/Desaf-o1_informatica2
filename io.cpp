#include "io.h"
#include <iostream>
#include <fstream>



//Funcion que recibe los parametros de nombre, buffer y tam
/*
    nombre: contiene la ruta y el nombre del archivo que buscamos
    buffer: contiene el archivo leido en binario
    tam: Variable con la que medimos el tamaño del archivo
*/
bool leerArchivoBinario(const char* nombre, unsigned char*& buffer, int& tam) {
    // Abrir el archivo en modo binario
    std::ifstream archivo(nombre, std::ios::binary | std::ios::ate);

    if (!archivo.is_open()) {
        return false;
    }

    // Obtener el tamaño del archivo
    tam = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    // Reservar memoria para el buffer
    buffer = new unsigned char[tam];

    // Leer el archivo completo
    archivo.read(reinterpret_cast<char*>(buffer), tam);

    // Verificar si la lectura fue exitosa
    if (!archivo) {
        delete[] buffer;
        buffer = nullptr;
        tam = 0;
        archivo.close();
        return false;
    }

    archivo.close();
    return true;
}
