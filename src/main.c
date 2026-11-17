#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "server.h"
#include "http.h"

int main() {
    int servidor;
    int epoll_fd;
    int n;
    int i;
    struct epoll_event evento;
    struct epoll_event eventos[10];

    servidor = crear_servidor(8080);
    epoll_fd = epoll_create1(0);

    // Metemos el servidor al epoll
    evento.events = EPOLLIN;
    evento.data.fd = servidor;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, servidor, &evento);

    printf("Servidor corriendo en http://localhost:8080\n");

    while (1) {
        // Esperamos a que pase algo
        n = epoll_wait(epoll_fd, eventos, 10, -1);

        for (i = 0; i < n; i++) {
            // Si el evento es en el servidor, es un cliente nuevo
            if (eventos[i].data.fd == servidor) {
                int cliente = accept(servidor, NULL, NULL);
                
                evento.events = EPOLLIN;
                evento.data.fd = cliente;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cliente, &evento);
            } 
            // Si no, es un cliente mandando datos
            else {
                int cliente = eventos[i].data.fd;
                char pedido[1000] = {0};
                char resp[5000] = {0};
                int leidos;

                leidos = read(cliente, pedido, 999);

                if (leidos <= 0) {
                    // El cliente se desconecto
                    close(cliente);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, cliente, NULL);
                } else {
                    // Procesamos la peticion y respondemos
                    procesar_peticion(pedido, resp);
                    write(cliente, resp, strlen(resp));
                }
            }
        }
    }

    return 0;
}