#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

int crear_servidor(int puerto) {
    int fd;
    int opcion = 1;
    struct sockaddr_in dir;

    // Creamos el socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Para poder reusar el puerto si lo cerramos
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opcion, sizeof(opcion));

    // Llenamos los datos de la direccion
    dir.sin_family = AF_INET;
    dir.sin_addr.s_addr = INADDR_ANY;
    dir.sin_port = htons(puerto);

    // Hacemos el bind y el listen
    bind(fd, (struct sockaddr*)&dir, sizeof(dir));
    listen(fd, 10);
    
    return fd;
}