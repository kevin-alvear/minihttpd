# compilar todo
minihttpd: src/main.c src/server.c src/http.c src/mime.c src/files.c
	gcc -Iinclude -o minihttpd src/main.c src/server.c src/http.c src/mime.c src/files.c

# limpiar
clean:
	rm -f minihttpd