
# Proyecto MiniHTTPd

**Materia:** Computación Distribuida  
**Profesor:** Ing. Luis Enrique Mafla  
**Estudiante:** Kevin Alvear  
**Fecha de entrega:** 20 de Noviembre del 2026

## ¿Qué es este proyecto?
Es un servidor web básico hecho en lenguaje C. 
El servidor puede mostrar archivos estáticos como HTML y CSS, y usa `epoll` para atender a varios clientes.

## ¿Cómo compilarlo?
Abrir la terminal en la carpeta del proyecto y escribir:
```bash
make
```

## ¿Cómo ejecutarlo?
Escribir en la terminal:
```bash
./minihttpd
```

Luego abrir el navegador y entrar a: `http://localhost:8080`

## ¿Qué carpetas tiene?
- `src/`: Aquí están los archivos de código en C.
- `include/`: Aquí están los archivos de cabecera (.h).
- `www/`: Aquí están los archivos de la página web (html y css).
```