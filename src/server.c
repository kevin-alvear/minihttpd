#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

int crear_servidor(int puerto) {
    int fd;
    int opcion = 1;
    struct sockaddr_in dir;

    // crear socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // configurar para reusar puerto
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opcion, sizeof(opcion));

    // llenar direccion
    dir.sin_family = AF_INET;
    dir.sin_addr.s_addr = INADDR_ANY;
    dir.sin_port = htons(puerto);

    // hacer bind
    bind(fd, (struct sockaddr*)&dir, sizeof(dir));
    
    // escuchar
    listen(fd, 10);
    
    return fd;
}