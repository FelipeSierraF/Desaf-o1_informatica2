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

    char nombre[256];
    char rutaCompleta[512];
    unsigned char* buffer = nullptr; //Contenedor donde guardaremos el archivo leido en binarios
    int tam = 0;

    while(true){

        cout << "Ingrese el nombre del archivo: ";
        cin.getline(nombre, 256);

        if (strcmp(nombre, "salir") == 0) {
            break;
        }

        sprintf(
            rutaCompleta,
            "C:\\Users\\felip\\Documents\\Proyectos resueltos\\Desafio1\\datasetDesarrollo\\%s",
            nombre
        );


        if(leerArchivoBinario(rutaCompleta, buffer, tam)){
            cout << "Archivo leído correctamente (" << tam << " bytes)\n";

            delete[] buffer;
        }else{
            cout << "Fallo al leer el archivo " << endl;
        }
    }

}
