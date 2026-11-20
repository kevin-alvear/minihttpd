#include <string.h>
#include "mime.h"

char* buscar_mime(char* ruta) {
    // si es la raiz devolvemos html
    if (strcmp(ruta, "/") == 0) {
        return "text/html";
    }
    // buscar la extension con strstr
    if (strstr(ruta, ".html") != NULL) {
        return "text/html";
    }
    else if (strstr(ruta, ".css") != NULL) {
        return "text/css";
    }
    else if (strstr(ruta, ".js") != NULL) {
        return "application/javascript";
    }
    else if (strstr(ruta, ".png") != NULL) {
        return "image/png";
    }
    else if (strstr(ruta, ".jpg") != NULL) {
        return "image/jpeg";
    }
    else {
        return "text/plain";
    }
}