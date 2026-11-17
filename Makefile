# Makefile para compilar el proyecto
# Para compilar, escribir en la terminal: make
# Para borrar el ejecutable, escribir: make clean

all:
	gcc -Iinclude -Wall src/main.c src/server.c src/http.c src/mime.c src/files.c -o minihttpd

clean:
	rm -f minihttpd