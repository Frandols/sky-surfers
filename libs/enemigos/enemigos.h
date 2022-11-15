#include <stdio.h>

typedef struct {
    int nivel, golpe, delay;
} Enemigo;

Enemigo enemigo;

FILE * enemigos;

void leerEnemigo();

void leerEnemigo() {
    fread(&enemigo, sizeof(Enemigo), 1, enemigos);
}