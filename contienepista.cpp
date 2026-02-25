#include "contienepista.h"

bool contienePista(const unsigned char* texto,int tamTexto,const unsigned char* pista,int tamPista){
    if (texto == nullptr || pista == nullptr)
        return false;

    if (tamTexto <= 0 || tamPista <= 0)
        return false;

    if (tamPista > tamTexto)
        return false;

    for (int i = 0; i <= tamTexto - tamPista; i++) {

        bool coincide = true;

        for (int j = 0; j < tamPista; j++) {
            if (texto[i + j] != pista[j]) {
                coincide = false;
                break;
            }
        }

        if (coincide)
            return true;
    }

    return false;
}
