#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

typedef char tString[256];

WSADATA wsaData;
SOCKET Socket;

struct sockaddr_in servidor;

void inicializarWinsock();
void crearSocket();
void configurarServidor();
void conectarSocket();
void crearHilos();
void controlarHilos();
void enviarDato();
void cerrarSocket();

HANDLE hilos[3];

DWORD WINAPI controlarHiloMovimientos();

void enviarPosicion();

DWORD WINAPI controlarHiloEnemigos();
DWORD WINAPI controlarHiloAtaques();

int x = 300;

int main() {
    inicializarWinsock();
    crearSocket();
    configurarServidor();
    conectarSocket();
    crearHilos();
    controlarHilos();
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

void crearHilos() {
    DWORD idHilo;

    int i;

    for(i = 0; i < 3; i++) {
        hilos[i] = CreateThread(
            NULL,
            0,
            i == 0
            ? controlarHiloMovimientos
            : i == 1
              ? controlarHiloEnemigos
              : controlarHiloAtaques,
            NULL,
            0,
            &idHilo
        );

        if(hilos[i] == NULL) {
            printf("Error al crear hilo %d\n", i);

            exit(1);
        }
    }
}

void controlarHilos() {
    DWORD resultado;

    resultado = WaitForMultipleObjects(
        3,
        hilos,
        TRUE,
        INFINITE
    );

    if(resultado != WAIT_OBJECT_0) {
        printf("Error al controlar los hilos\n");

        exit(1);
    }
}

void enviarDato(tString dato) {
    if(send(Socket, dato, strlen(dato), 0) < 0) {
        printf("Error al enviar dato\n");

        exit(1);
    }
}

DWORD WINAPI controlarHiloMovimientos() {
    int resultado;

    enviarPosicion();

    do {
        tString direccion = {};

        resultado = recv(Socket, direccion, 256, 0);

        if(resultado > 0) {
            if(strcmp(direccion, "right") == 0) {
                x = x < 600 ? x + 10 : x;
            } else {
                x = x > 0 ? x - 10 : x;
            }

            enviarPosicion();
        }
    } while(resultado > 0);
}

void enviarPosicion() {
    tString dato = {};
    tString posicion = {};

    itoa(x, posicion, 10);

    strcpy(dato, "position");
    
    strcat(dato, "-");

    strcat(dato, posicion);

    enviarDato(dato);
}

DWORD WINAPI controlarHiloEnemigos() {}

DWORD WINAPI controlarHiloAtaques() {}

void cerrarSocket() {
    closesocket(Socket);

    WSACleanup();
}

// Fran estuvo aqui
// Hiras estuvo aqui