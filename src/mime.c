#include <string.h>
#include "mime.h"

const char* buscar_mime(char* ruta) {
    // Revisamos que extension tiene el archivo
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
        // Si no es ninguna, mandamos texto plano
        return "text/plain";
    }
}