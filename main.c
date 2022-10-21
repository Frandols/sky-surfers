#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_BUFLEN 512

typedef char tString[256];

WSADATA wsaData;
SOCKET socketServidor, socketCliente;

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

    printf("Winsock inicializado\n");
}

void crearSocket() {
    socketServidor = socket(AF_INET, SOCK_STREAM, 0);

    if(socketServidor == INVALID_SOCKET) {
        printf("Error al crear socket\n");

        exit(1);
    }

    printf("Socket creado\n");
}

void configurarServidor() {
    struct hostent *he;
    const char hostname[] = "localhost";

    if ((he = gethostbyname(hostname)) == NULL) exit(1);

    memcpy(&servidor.sin_addr, he->h_addr_list[0], he->h_length);
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(3000);
}

void conectarSocket() {
    if(connect(socketServidor, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Error al conectar socket\n");

        exit(1);
    }

    printf("Socket conectado\n");
}

void enviarMensaje(int pos) {
    tString mensaje;

    itoa(pos, mensaje, 10);

    if(send(socketServidor, mensaje, strlen(mensaje), 0) < 0) {
        printf("Error al enviar mensaje\n");

        exit(1);
    }

    printf("Enviado: %s\n", mensaje);
}

void recibirMensajes() {
    int resultado;

    do {
        tString buffer = {};

        resultado = recv(socketServidor, buffer, 256, 0);

        if (resultado > 0) {
            if(strcmp(buffer, "none") != 0) {
                printf("Movimiento recibido: %s\n", buffer);

                if(strcmp(buffer, "right") == 0 && x < 600) x = x + 10;
                else if(strcmp(buffer, "left") == 0 && x > 0) x = x - 10;
            }
        } else if (resultado == 0) printf("Conexion cerrada\n");
        else printf("Error al recibir mensaje\n");

        enviarMensaje(x);
    } while(resultado > 0);
}

void cerrarSocket() {
    closesocket(socketServidor);

    WSACleanup();
}

// Fran estuvo aqui
// Hiras estuvo aqui