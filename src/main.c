#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include "server.h"
#include "http.h"

int main() {
    int servidor;
    int epoll_fd;
    int n;
    int i;
    int cliente;
    int leidos;
    int cerrar;
    char pedido[1024];
    struct epoll_event evento;
    struct epoll_event eventos[10];

    // para que no se caiga si un cliente se va
    signal(SIGPIPE, SIG_IGN);

    // crear servidor
    servidor = crear_servidor(8080);
    
    // crear epoll
    epoll_fd = epoll_create1(0);

    // meter servidor al epoll
    evento.events = EPOLLIN;
    evento.data.fd = servidor;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, servidor, &evento);

    printf("Servidor en http://localhost:8080\n");

    while (1) {
        // esperar eventos
        n = epoll_wait(epoll_fd, eventos, 10, -1);

        for (i = 0; i < n; i++) {
            
            // si es cliente nuevo
            if (eventos[i].data.fd == servidor) {
                cliente = accept(servidor, NULL, NULL);
                if (cliente >= 0) {
                    evento.events = EPOLLIN;
                    evento.data.fd = cliente;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cliente, &evento);
                }
            } 
            // si es cliente mandando datos
            else {
                cliente = eventos[i].data.fd;
                leidos = read(cliente, pedido, 1023);
                cerrar = 1;
                
                if (leidos > 0) {
                    pedido[leidos] = '\0';
                    cerrar = responder(cliente, pedido);
                }
                
                // cerrar conexion si es necesario
                if (cerrar == 1) {
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, cliente, NULL);
                    close(cliente);
                }
            }
        }
    }
    
    return 0;
}