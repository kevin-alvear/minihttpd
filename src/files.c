#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

int leer_archivo(char* pedido, char* buf, int* tam) {
    char ruta[300];
    char ruta_real[500];
    char ruta_www[500];
    FILE* archivo;

    // armar la ruta
    snprintf(ruta, 300, "www%s", pedido);

    // usar realpath para evitar salir de la carpeta
    if (realpath(ruta, ruta_real) == NULL) {
        return 404;
    }

    // revisar que este dentro de www
    if (realpath("www", ruta_www) == NULL) {
        return 500;
    }
    if (strncmp(ruta_real, ruta_www, strlen(ruta_www)) != 0) {
        return 403;
    }

    // abrir archivo
    archivo = fopen(ruta_real, "rb");
    if (archivo == NULL) {
        return 500;
    }

    // leer archivo
    *tam = fread(buf, 1, MAX, archivo);
    fclose(archivo);
    
    return 200;
}