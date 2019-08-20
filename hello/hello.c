#include <stdio.h> // <> libreria en el sistema
// Se utiliza el libhello.h como intermediario hacia el libhello.c para que
// cada C file tenga sus librerias y no se acumule la misma libreria.
#include "./libhello.h" // "" : libreria local --- ./ : En este directorio

int main(int argc, char **argv){
    int i;
    for(i = 1; i < argc ; i++){
        printHello(argv[i]);
    }
    return 0;
}