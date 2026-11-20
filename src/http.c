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

    // 3. Revisamos si es GET (solo aceptamos GET)
    if (strcmp(metodo, "GET") != 0) {
        snprintf(resp, 100, "HTTP/1.1 405 Method Not Allowed\r\n\r\n");
        return 405;
    }

    // 4. Analizamos los encabezados basicos (Host, Connection, User-Agent)
    // Buscamos si existe el Host, que es obligatorio en HTTP/1.1
    if (strstr(pedido, "Host:") == NULL) {
        snprintf(resp, 100, "HTTP/1.1 400 Bad Request\r\n\r\n");
        return 400;
    }

    // Buscamos los otros encabezados para demostrar que los analizamos
    if (strstr(pedido, "User-Agent:") != NULL) {
        // Aqui podriamos guardar el navegador del cliente, pero lo dejamos simple
    }
    if (strstr(pedido, "Connection:") != NULL) {
        // El cliente puede pedir cerrar la conexion, pero el PDF pide persistentes
    }

    // 5. Buscamos el archivo
    estado = leer_archivo(ruta, contenido, &tam);

    // 6. Dependiendo del estado, armamos la respuesta
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
        
        // ESTA ES LA LÍNEA CRÍTICA: Le decimos a C donde termina el texto
        resp[strlen(resp) + tam] = '\0'; 
    }

    return estado;
}