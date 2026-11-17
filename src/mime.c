#include <string.h>
#include "mime.h"

const char *tipo_mime(const char *ruta) {
    const char *p = strrchr(ruta, '.');
    if (p == NULL) return "application/octet-stream";
    if (strcmp(p, ".html") == 0) return "text/html";
    if (strcmp(p, ".css") == 0)  return "text/css";
    if (strcmp(p, ".js") == 0)   return "application/javascript";
    if (strcmp(p, ".png") == 0)  return "image/png";
    if (strcmp(p, ".jpg") == 0)  return "image/jpeg";
    return "application/octet-stream";
}