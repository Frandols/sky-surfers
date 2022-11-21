#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#include "libs/enemigos/enemigos.h"
#include "libs/ataques/ataques.h"
#include "libs/niveles/niveles.h"

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
void enviarDato(tString);
void enviarClaveValor(tString, tString);
void cerrarSocket();

HANDLE hilos[2];

DWORD WINAPI controlarHiloMovimientos();

void enviarPosicion();

DWORD WINAPI controlarHiloEnemigos();

void enviarEnemigo(int);
void golpearJugador(int);
void enviarAtaque(int);
void enviarNivel(int);
void notificarDerrota(int);
void enviarEstadisticas();
void enviarMejorNivel();

volatile int x = 300;
int vida = 200;
bool finalizado = false;
bool derrotado = false;

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

    for(i = 0; i < 2; i++) {
        hilos[i] = CreateThread(
            NULL,
            0,
            i == 0
            ? controlarHiloMovimientos
            : controlarHiloEnemigos,
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
        2,
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

void enviarClaveValor(tString clave, tString valor) {
    tString dato;

    strcpy(dato, clave);
    strcat(dato, "-");
    strcat(dato, valor);

    enviarDato(dato);
}

DWORD WINAPI controlarHiloMovimientos() {
    int resultado;

    enviarPosicion();

    do {
        tString direccion = {};

        resultado = recv(Socket, direccion, 256, 0);

        if(resultado > 0) {
            if(strcmp(direccion, "right") == 0) {
                x = x < 600 ? x + 20 : x;
            } else {
                x = x > 0 ? x - 20 : x;
            }

            enviarPosicion();
        }
    } while(resultado > 0);
}

void enviarPosicion() {
    tString posicion;

    itoa(x, posicion, 10);

    enviarClaveValor("position", posicion);
}

DWORD WINAPI controlarHiloEnemigos() {
    srand(time(NULL));

    int r, p, ultimoNivelLeido, golpesRecibidos;
    float espera;
    Ataque ataque;
    Nivel nivel;

    enemigos = fopen("./db/enemigos.dat", "rb");

    leerEnemigo();

    ultimoNivelLeido = enemigo.nivel;

    while(!finalizado && !feof(enemigos)) {
        Sleep(7500);

        golpesRecibidos = 0;
        nivel.codigo = enemigo.nivel;

        while(!finalizado && enemigo.nivel == ultimoNivelLeido) {
            r = rand() % 600;

            enviarEnemigo(r);

            p = x;

            ataque.y = -200;
            ataque.x = r;

            espera = tiempoDeEspera(ataque, x);

            Sleep(espera);

            if(ataqueGolpeoJugador(p, x)) {
                golpearJugador(enemigo.golpe);

                golpesRecibidos++;
            }

            Sleep(1500 - espera);

            p = x;

            ataque.y = 50;

            espera = tiempoDeEspera(ataque, x);

            Sleep(espera);

            if(ataqueGolpeoJugador(p, x)) {
                golpearJugador(enemigo.golpe);

                golpesRecibidos++;
            }

            Sleep(enemigo.delay - (1500 + espera));

            leerEnemigo();
        }

        nivel.golpesRecibidos = golpesRecibidos;
        insertarNivel(nivel);

        ultimoNivelLeido = enemigo.nivel;

        if(!finalizado) enviarNivel(enemigo.nivel);
    }

    Sleep(2000);

    if(derrotado) {
        notificarDerrota(ultimoNivelLeido);

        Sleep(5000);
    }

    ordenarNiveles();
    enviarEstadisticas();

    Sleep(5000);

    if(ultimoNivelLeido > 1) {
        mejorNivel = niveles[ultimoNivelLeido];

        buscarMejorNivel();

        enviarMejorNivel();
    }
}

void enviarEnemigo(int posicion) {
    tString enemigo;

    itoa(posicion, enemigo, 10);

    enviarClaveValor("enemy", enemigo);
}

void golpearJugador(int golpe) {
    vida = vida - golpe;

    if(vida <= 0) {
        finalizado = true;
        derrotado = true;
    }

    enviarAtaque(enemigo.golpe);
}

void enviarAtaque(int golpe) {
    tString ataque;

    itoa(golpe, ataque, 10);

    enviarClaveValor("atack", ataque);
}

void enviarNivel(int codigo) {
    tString nivel;

    itoa(codigo, nivel, 10);

    enviarClaveValor("level", nivel);
}

void notificarDerrota(int nivel) {
    tString derrota;

    itoa(nivel, derrota, 10);

    enviarClaveValor("defeat", derrota);
}

void enviarEstadisticas() {
    tString estadisticas = {};

    int i;
    for(i = 0; i < 3; i++) {
        tString codigo, golpesRecibidos;

        itoa(niveles[i].codigo, codigo, 10);
        itoa(niveles[i].golpesRecibidos, golpesRecibidos, 10);

        strcat(estadisticas, codigo);
        strcat(estadisticas, ",");
        strcat(estadisticas, golpesRecibidos);
        
        if(i < 2) strcat(estadisticas, ".");
    }

    enviarClaveValor("statistics", estadisticas);
}

void enviarMejorNivel() {
    tString nivel, codigo, golpesRecibidos;

    itoa(mejorNivel.codigo, codigo, 10);
    itoa(mejorNivel.golpesRecibidos, golpesRecibidos, 10);

    strcpy(nivel, codigo);
    strcat(nivel, ",");
    strcat(nivel, golpesRecibidos);

    enviarClaveValor("bestLevel", nivel);
}

void cerrarSocket() {
    closesocket(Socket);

    WSACleanup();
}

// Fran estuvo aqui
// Hiras estuvo aqui