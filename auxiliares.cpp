#include "auxiliares.h"
#include <cctype>
#include <iostream>

int pedirNumero() {
    char c;

    while (true) {
        std::cout << "Ingresa un numero (0-9): ";
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

