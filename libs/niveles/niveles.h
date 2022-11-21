#include <stdio.h>

#define MAX 3

typedef struct{
	int codigo, golpesRecibidos;
} Nivel;

typedef Nivel Niveles[MAX];

void insertarNivel(Nivel);
void ordenarNiveles();
void buscarMejorNivel();

Niveles niveles;
Nivel mejorNivel;

void insertarNivel(Nivel nivel) {
    niveles[nivel.codigo - 1] = nivel;
}

void ordenarNiveles() {
    Nivel valorMenor, auxiliar;
    int i, j, posicionMenor;

    for(i = 0; i < MAX - 1; i++) {
        valorMenor = niveles[i];
        posicionMenor = i;

        for(j = i + 1; j < MAX; j++) {
            if(niveles[j].golpesRecibidos < valorMenor.golpesRecibidos) {
                valorMenor = niveles[j];
                posicionMenor = j;
            }
        }

        if(posicionMenor != i) {
            auxiliar = niveles[i];
            niveles[i] = valorMenor;
            niveles[posicionMenor] = auxiliar;
        }
    }

    printf("\nSeleccion directa: Vector ordenado exitosamente\n");
}

void buscarMejorNivel() {
    int i = 0;

    for(i = 0; i < MAX; i++) {
        if(niveles[i].codigo != 0 && niveles[i].golpesRecibidos < mejorNivel.golpesRecibidos) mejorNivel = niveles[i];
    }
}