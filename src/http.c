#include <stdio.h>
#include <string.h>
#include "http.h"
#include "mime.h"
#include "files.h"

int procesar_peticion(char* pedido, char* resp) {
    char metodo[10];
    char ruta[200];
    char contenido[4000];
    int tam = 0;
    int estado;
    const char* tipo;

    // 1. Revisamos que no sea muy largo (Buffer Overflow)
    if (strlen(pedido) > 1000) {
        snprintf(resp, 100, "HTTP/1.1 400 Bad Request\r\n\r\n");
        return 400;
    }

    // 2. Sacamos el metodo y la ruta
    sscanf(pedido, "%s %s", metodo, ruta);

    // 3. LA CORRECCIÓN: Si piden la raiz "/", pedimos el index.html
    if (strcmp(ruta, "/") == 0) {
        snprintf(ruta, 200, "/index.html");
    }

    // 4. Revisamos si es GET (solo aceptamos GET)
    if (strcmp(metodo, "GET") != 0) {
        snprintf(resp, 100, "HTTP/1.1 405 Method Not Allowed\r\n\r\n");
        return 405;
    }

    // 5. Analizamos los encabezados basicos (Host)
    if (strstr(pedido, "Host:") == NULL) {
        snprintf(resp, 100, "HTTP/1.1 400 Bad Request\r\n\r\n");
        return 400;
    }

    // 6. Buscamos el archivo
    estado = leer_archivo(ruta, contenido, &tam);

    // 7. Dependiendo del estado, armamos la respuesta
    if (estado == 404) {
        snprintf(resp, 100, "HTTP/1.1 404 Not Found\r\n\r\n");
    } 
    else if (estado == 403) {
        snprintf(resp, 100, "HTTP/1.1 403 Forbidden\r\n\r\n");
    } 
    else if (estado == 500) {
        snprintf(resp, 100, "HTTP/1.1 500 Internal Server Error\r\n\r\n");
    } 
    else {
        // Si llegamos aqui, es 200 OK
        tipo = buscar_mime(ruta);
        
        snprintf(resp, 500, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\nConnection: keep-alive\r\n\r\n", tipo, tam);
        
        // Pegamos el contenido del archivo
        memcpy(resp + strlen(resp), contenido, tam);
        
        // Le decimos a C donde termina el texto para que no salga basura
        resp[strlen(resp) + tam] = '\0'; 
    }

    return estado;
}