#include <stdio.h>

typedef struct {
    int nivel, golpe, delay;
} Enemigo;

FILE * archivo;

int main() {
    int i;
    Enemigo enemigo;

    archivo = fopen("../../db/enemigos.dat", "rb");    

    fread(&enemigo, sizeof(Enemigo), 1, archivo);
    while(!feof(archivo)) {
        printf("Enemigo - nivel: %d | golpe: %d | delay: %d\n", enemigo.nivel, enemigo.golpe, enemigo.delay);

        fread(&enemigo, sizeof(Enemigo), 1, archivo);
    }

    fclose(archivo);

    return 0;
}