#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

typedef char tString[256];

WSADATA wsaData;
SOCKET Socket;

struct sockaddr_in servidor;

void inicializarWinsock();
void crearSocket();
void configurarServidor();
void conectarSocket();
void enviarMensaje(int);
void recibirMensajes();
void cerrarSocket();

int x = 300;

int main() {
    inicializarWinsock();
    crearSocket();
    configurarServidor();
    conectarSocket();
    enviarMensaje(x);
    recibirMensajes();
    cerrarSocket();
    
    return 0;
}

void inicializarWinsock() {
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error al inicializar Winsock\n");

        exit(1);
    }
}

void crearSocket() {
    Socket = socket(AF_INET, SOCK_STREAM, 0);

    if(Socket == INVALID_SOCKET) {
        printf("Error al crear socket\n");

        exit(1);
    }
}

void configurarServidor() {
    struct hostent *he;
    const char hostname[] = "localhost";

    he = gethostbyname(hostname);

    if(he == NULL) {
        printf("Error al obtener host\n");

        exit(1);
    }

    memcpy(&servidor.sin_addr, he->h_addr_list[0], he->h_length);
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(3000);
}

void conectarSocket() {
    if(connect(Socket, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Error al conectar socket\n");

        exit(1);
    }
}

void enviarMensaje(int posicion) {
    tString mensaje;

    itoa(posicion, mensaje, 10);

    if(send(Socket, mensaje, strlen(mensaje), 0) < 0) {
        printf("Error al enviar mensaje\n");

        exit(1);
    }
}

void recibirMensajes() {
    int resultado;

    do {
        tString mensaje = {};

        resultado = recv(Socket, mensaje, 256, 0);

        if(resultado > 0) {
            if(strcmp(mensaje, "right") == 0) {
                x = x < 600 ? x + 10 : x;
            } else {
                x = x > 0 ? x - 10 : x;
            }

            enviarMensaje(x);
        }
    } while(resultado > 0);
}

void cerrarSocket() {
    closesocket(Socket);

    WSACleanup();
}

// Fran estuvo aqui
// Hiras estuvo aqui