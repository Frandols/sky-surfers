#include <stdio.h>

typedef struct {
    int nivel, golpe, delay;
} Enemigo;

FILE * archivo;

int main() {
    int i;

    archivo = fopen("../../db/enemigos.dat", "wb");

    Enemigo enemigo;
    enemigo.nivel = 1;
    enemigo.golpe = 10;
    enemigo.delay = 5000;

    for(i = 0; i < 8; i++) {
        fwrite(&enemigo, sizeof(Enemigo), 1, archivo);
    }

    enemigo.nivel = 2;
    enemigo.golpe = 20;
    enemigo.delay = 4000;

    for(i = 0; i < 10; i++) {
        fwrite(&enemigo, sizeof(Enemigo), 1, archivo);
    }

    enemigo.nivel = 3;
    enemigo.golpe = 20;
    enemigo.delay = 3000;

    for(i = 0; i < 20; i++) {
        fwrite(&enemigo, sizeof(Enemigo), 1, archivo);
    }

    fclose(archivo);

    return 0;
}