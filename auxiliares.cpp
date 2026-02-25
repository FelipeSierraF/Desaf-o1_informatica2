#include "auxiliares.h"
#include <cctype>
#include <iostream>
#include <cstdio>
#include <cstring>

int pedirNumero() {
    char c;

    while (true) {
        std::cout << "Ingresa un numero o el 0 para finalizar el programa: ";
        std::cin >> c;

        // Validar que sea un dígito
        if (isdigit(c)) {
            // Convertir de char a int
            return c - '0';
        } else {
            std::cout << "Error: '" << c << "' no es un numero valido. Intenta de nuevo." << std::endl;
            // Limpiar el buffer en caso de entrada incorrecta
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
}

void construirRutas(int num, char* rutaCompleta, char* rutaPista){
    const char* rutaBase =
        "C:\\Users\\felip\\Documents\\Proyectos resueltos\\Desafio1\\datasetDesarrollo\\";

    // Construir ruta EncriptadoX.txt
    sprintf(rutaCompleta, "%sEncriptado%d.txt", rutaBase, num);

    // Construir ruta pistaX.txt
    sprintf(rutaPista, "%spista%d.txt", rutaBase, num);
}

