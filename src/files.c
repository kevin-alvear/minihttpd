#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

int leer_archivo(char* pedido, char* buf, int* tam) {
    char ruta_real[200];
    char ruta_www[200];
    char ruta[200];
    FILE* archivo;
    
    // Si pide la raiz "/", le damos el index.html
    if (strcmp(pedido, "/") == 0) {
        snprintf(ruta, 200, "www/index.html");
    } else {
        // Si pide otra cosa, se la pegamos a la carpeta www
        snprintf(ruta, 200, "www%s", pedido);
    }

    // AQUI EVITAMOS EL DIRECTORY TRAVERSAL
    if (realpath(ruta, ruta_real) == NULL) {
        return 404; // No existe
    }
    
    realpath("www", ruta_www);
    
    // Revisamos que la ruta real no se salga de la carpeta www
    if (strncmp(ruta_real, ruta_www, strlen(ruta_www)) != 0) {
        return 403; // Prohibido
    }

    // Abrimos el archivo
    archivo = fopen(ruta_real, "r");
    if (archivo == NULL) {
        return 500; // Error interno
    }

    // Leemos maximo 4000 bytes
    *tam = fread(buf, 1, 4000, archivo);
    
    fclose(archivo);
    return 200; // Todo bien
}