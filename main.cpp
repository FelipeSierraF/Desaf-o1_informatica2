#include "LZ78.h"
#include "auxiliares.h"
#include "contienepista.h"
#include "crypto.h"
#include "io.h"
#include "rle.h"
#include <cstring>
#include <iostream>
#include <windows.h>

using namespace std;


int main()
{
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);

    char cwd[512];
    GetCurrentDirectoryA(512, cwd);
    cout << "CWD = " << cwd << endl;

    unsigned char* buffer = nullptr; //Arreglo donde guardaremos el archivo leido en binarios
    unsigned char* bufferDes = nullptr;
    unsigned char* bufferPista = nullptr;
    char rutaCompleta[512];
    char rutaPista[512];
    int tam = 0;
    int tamPis = 0;

    cout << "=== PROGRAMA DE LECTURA DE ARCHIVOS ===" << endl;

    while(true){
        bool encontrado = false;

        int num = pedirNumero();

        construirRutas(num, rutaCompleta, rutaPista);

        if(num == 0) break;

        if(leerPista(rutaPista, bufferPista, tamPis)){}
        if(leerArchivoBinario(rutaCompleta, buffer, tam)){
            // bufferDes = bufferDesencriptado(buffer,tam,3,90);

            // cout << "Primeros 30 bytes (ASCII):" << endl;

            // for (int i = 0; i < 30 && i < tam; i++) {

            //     unsigned char c = bufferDes[i];

            //     if (c >= 32 && c <= 126)  // imprimible
            //         cout << c;
            //     else
            //         cout << ".";          // marcar no imprimible
            // }
            // cout << endl << endl;

            // cout << "Primeros 30 bytes (hex):" << endl;

            // for (int i = 0; i < 30 && i < tam; i++) {
            //     cout << hex << (int)bufferDes[i] << " ";
            // }
            // cout << dec << endl << endl;

            // int tamSalida = 0;
            // if(validoRLE(bufferDes,tam)){
            //     unsigned char* original = descomprimirRLE(bufferDes, tam, tamSalida);
            //     if(original != nullptr && contienePista(original, tamSalida, bufferPista, tamPis)){
            //         cout << "Metodo: RLE" << endl;
            //         cout << "n = " << 3 << "  k = " << 90 << endl;
            //     }
            // }else if(validoLZ78(bufferDes,tam)){
            //     unsigned char* original = descomprimirLZ78(bufferDes, tam, tamSalida);
            //     cout << "POSIBLE LZ78 con n="<< " 3 "<<" k="<< " 90 "<<endl;
            //     if(original != nullptr && contienePista(original, tamSalida, bufferPista, tamPis)){
            //         cout << "Metodo: LZ78" << endl;
            //         cout << "n = " << 3 << "  k = " << 90 << endl;
            //     }
            // }

            for (size_t n = 0; n < 8; n++){

                for(size_t k = 0; k <= 255; k ++){
                    bufferDes = bufferDesencriptado(buffer, tam, n, k);

                    int tamSalida = 0;
                    if(validoRLE(bufferDes,tam)){
                        unsigned char* original = descomprimirRLE(bufferDes, tam, tamSalida);

                        if(original != nullptr && contienePista(original, tamSalida, bufferPista, tamPis)){

                            cout << "Metodo: RLE" << endl;
                            cout << "n = " << n << "  k = " << k << endl;

                            encontrado = true;
                        }
                        delete[] original;
                        original = nullptr;

                    }else if(validoLZ78(bufferDes,tam)){
                        cout << "POSIBLE LZ78 con n="<<  n <<" k="<< k <<endl;
                        unsigned char* original = descomprimirLZ78(bufferDes, tam, tamSalida);

                        if(original != nullptr && contienePista(original, tamSalida, bufferPista, tamPis)){

                            cout << "Metodo: LZ78" << endl;
                            cout << "n = " << n << "  k = " << k << endl;

                            encontrado = true;
                        }

                        delete[] original;
                        original = nullptr;

                    }else{
                        // std::cout << "Llorelo" << std::endl;
                    }

                    delete[] bufferDes;
                    bufferDes = nullptr;
                }
            }
        }else{
            cout << "Fallo al leer el archivo Encriptado " << endl;
        }

        delete[] bufferPista;
        bufferPista = nullptr;
        delete[] buffer;
        buffer = nullptr;
    }


}
