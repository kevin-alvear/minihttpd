CC = gcc
CFLAGS = -Iinclude -Wall

all: minihttpd

minihttpd: src/main.c src/server.c src/http.c src/mime.c src/files.c
	$(CC) $(CFLAGS) -o minihttpd src/main.c src/server.c src/http.c src/mime.c src/files.c

clean:
	rm -f minihttpd