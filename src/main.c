#include <signal.h>
#include "server.h"

int main() {
    signal(SIGPIPE, SIG_IGN);
    iniciar_servidor(8080);
    return 0;
}