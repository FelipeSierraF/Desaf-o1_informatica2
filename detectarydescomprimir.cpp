#include "detectarydescomprimir.h"
#include <iostream>

bool esDigito(unsigned char c)
{
    return c >= '0' && c <= '9';
}

bool esLetraOEspacio(unsigned char c)
{
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           c == ' ' || c == '\n' || c == '\r';
}

int charAInt(const unsigned char* buffer, int& i)
{
    int num = 0;
    while (esDigito(buffer[i]))
    {
        num = num * 10 + (buffer[i] - '0');
        i++;
    }
    return num;
}

bool esRLE(const unsigned char* buffer, int tam)
{
    int i = 0;
    int pares = 0;

    while (i < tam)
    {
        if (!esDigito(buffer[i]))
            return false;

        // Saltar dígitos
        while (i < tam && esDigito(buffer[i]))
            i++;

        if (i >= tam)
            break;

        // Debe seguir un caracter válido
        if (!esLetraOEspacio(buffer[i]))
            return false;

        i++;
        pares++;
    }

    return pares > 0;
}

bool esLZ78(const unsigned char* buffer, int tam)
{
    int i = 0;
    int pares = 0;

    while (i < tam)
    {
        if (buffer[i] != '(') return false;
        i++; // saltar '('

        // Leer índice numérico
        if (!esDigito(buffer[i])) return false;
        while (i < tam && esDigito(buffer[i])) i++;

        if (buffer[i] != ',') return false;
        i++; // saltar ','

        // Caracter (puede ser letra, espacio, etc.)
        i++; // saltar el caracter

        if (buffer[i] != ')') return false;
        i++; // saltar ')'

        pares++;
    }

    return pares > 0;
}

unsigned char* descomprimirRLE(const unsigned char* buffer, int tam, int& tamSalida)
{
    // Primero calculamos el tamaño del resultado
    tamSalida = 0;
    int i = 0;
    while (i < tam)
    {
        int conteo = charAInt(buffer, i);
        if (i < tam) i++; // saltar caracter
        tamSalida += conteo;
    }

    unsigned char* resultado = new unsigned char[tamSalida + 1];
    int pos = 0;
    i = 0;

    while (i < tam)
    {
        int conteo = charAInt(buffer, i);
        unsigned char c = buffer[i];
        i++;

        for (int j = 0; j < conteo; j++)
            resultado[pos++] = c;
    }

    resultado[tamSalida] = '\0';
    return resultado;
}

unsigned char* descomprimirLZ78(const unsigned char* buffer, int tam, int& tamSalida)
{
    int maxEntradas = tam / 3 + 1;
    unsigned char** diccionario  = new unsigned char*[maxEntradas];
    int* longitudes = new int[maxEntradas];
    int numEntradas = 0;

    // Resultado estimado
    unsigned char* resultado = new unsigned char[tam * 10 + 1];
    tamSalida = 0;

    int i = 0;
    while (i < tam)
    {
        if (buffer[i] != '(') break;
        i++; // '('

        // Leer índice
        int indice = charAInt(buffer, i);

        i++; // ','

        // Leer caracter
        unsigned char c = buffer[i];
        i++; // caracter

        i++;

        // Construir nueva entrada: diccionario[indice] + c
        int longBase = (indice == 0) ? 0 : longitudes[indice - 1];
        int longNueva = longBase + 1;

        unsigned char* nuevaEntrada = new unsigned char[longNueva + 1];

        if (indice != 0)
        {
            for (int j = 0; j < longBase; j++)
                nuevaEntrada[j] = diccionario[indice - 1][j];
        }
        nuevaEntrada[longBase] = c;
        nuevaEntrada[longNueva] = '\0';

        // Guardar en diccionario
        diccionario[numEntradas]  = nuevaEntrada;
        longitudes[numEntradas]   = longNueva;
        numEntradas++;

        // Escribir en resultado
        for (int j = 0; j < longNueva; j++)
            resultado[tamSalida++] = nuevaEntrada[j];
    }

    resultado[tamSalida] = '\0';

    // Liberar diccionario
    for (int j = 0; j < numEntradas; j++)
        delete[] diccionario[j];
    delete[] diccionario;
    delete[] longitudes;

    return resultado;
}

unsigned char* detectarYDescomprimir(const unsigned char* buffer, int tam, int& tamSalida)
{
    tamSalida = 0;

    if (esRLE(buffer, tam))
    {
        std::cout << "Método detectado: RLE" << std::endl;
        return descomprimirRLE(buffer, tam, tamSalida);
    }
    else if (esLZ78(buffer, tam))
    {
        std::cout << "Método detectado: LZ78" << std::endl;
        return descomprimirLZ78(buffer, tam, tamSalida);
    }
    else
    {
        std::cout << "No se pudo detectar el método de compresión." << std::endl;
        return nullptr;
    }
}
