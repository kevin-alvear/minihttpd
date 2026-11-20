#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "http.h"
#include "mime.h"
#include "files.h"

// funcion para mandar error
void enviar_error(int cliente, char* estado) {
    char resp[200];
    snprintf(resp, 200, "HTTP/1.1 %s\r\nContent-Length: 0\r\nConnection: keep-alive\r\n\r\n", estado);
    write(cliente, resp, strlen(resp));
}

int responder(int cliente, char* pedido) {
    char metodo[10] = "";
    char ruta[1000] = "";
    char version[20] = "";
    char cabecera[300];
    char contenido[MAX];
    int tam = 0;
    int estado;

    // revisar tamano del pedido
    if (strlen(pedido) > 1000) {
        enviar_error(cliente, "400 Bad Request");
        return 0;
    }

    // revisar que tenga host
    if (strstr(pedido, "Host:") == NULL) {
        enviar_error(cliente, "400 Bad Request");
        return 0;
    }

    // sacar metodo y ruta
    sscanf(pedido, "%s %s", metodo, ruta);

    // revisar si es get
    if (strcmp(metodo, "GET") != 0) {
        enviar_error(cliente, "405 Method Not Allowed");
        return 0;
    }

    // si es la raiz pedir index
    if (strcmp(ruta, "/") == 0) {
        snprintf(ruta, 1000, "/index.html");
    }

    // buscar archivo
    estado = leer_archivo(ruta, contenido, &tam);

    if (estado == 404) {
        enviar_error(cliente, "404 Not Found");
    } 
    else if (estado == 403) {
        enviar_error(cliente, "403 Forbidden");
    } 
    else if (estado == 500) {
        enviar_error(cliente, "500 Internal Server Error");
    } 
    else {
        // mandar respuesta 200
        snprintf(cabecera, 300, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\nConnection: keep-alive\r\n\r\n", buscar_mime(ruta), tam);
        write(cliente, cabecera, strlen(cabecera));
        write(cliente, contenido, tam);
    }

    // revisar si hay que cerrar
    if (strstr(pedido, "Connection: close") != NULL) {
        return 1;
    }
    
    return 0;
}