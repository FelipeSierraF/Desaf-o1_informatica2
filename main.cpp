#include "auxiliares.h"
#include "crypto.h"
#include "detectarydescomprimir.h"
#include "io.h"
#include <cstring>
#include <iostream>
#include <windows.h>

using namespace std;


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char cwd[512];
    GetCurrentDirectoryA(512, cwd);
    cout << "CWD = " << cwd << endl;

    unsigned char* buffer = nullptr; //Arreglo donde guardaremos el archivo leido en binarios
    unsigned char* bufferDes = nullptr;
    unsigned char* bufferPista = nullptr;
    int tam = 0;
    int tamPis = 0;
    bool encontrado = false;

    cout << "=== PROGRAMA DE LECTURA DE ARCHIVOS ===" << endl;

    while(true){

        int num = pedirNumero();

        string rutaBase = "C:\\Users\\felip\\Documents\\Proyectos resueltos\\Desafio1\\datasetDesarrollo\\";

        string rutaCompleta = rutaBase + "Encriptado" + to_string(num) + ".txt";
        string rutaPista = rutaBase + "pista" + to_string(num) + ".txt";
        if(leerArchivoBinario(rutaCompleta, buffer, tam)){
            for (size_t n = 1; n < 8 && !encontrado; n++){
                for(size_t k = 0; k <= 255 && !encontrado; k ++){
                    bufferDes = bufferDesencriptado(buffer, tam, n, k);
                    delete[] bufferDes;
                    bufferDes = nullptr;
                }
            }
        }else{
            cout << "Fallo al leer el archivo Encriptado " << endl;
        }
    }
    delete[] buffer;

}
