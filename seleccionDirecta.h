#include <stdio.h>

#define MAX 10

typedef struct{
	int valor, posicion;
}Elemento;

typedef int tVectorEntero[MAX];

void ordenarVectorSeleccionDirecta(tVectorEntero);

void ordenarVectorSeleccionDirecta(tVectorEntero _Vector) {

    int i, j, auxiliar;
    
    Elemento menor;

    for(i = 0; i < MAX - 1; i++) {
        menor.valor = _Vector[i];
        menor.posicion = i;

        for(j = i + 1; j < MAX; j++) {
            if(_Vector[j] < menor.valor) {
                menor.valor = _Vector[j];
                menor.posicion = j;
            }
        }

        if(menor.posicion != i) {
            auxiliar = _Vector[i];
            _Vector[i] = menor.valor;
            _Vector[menor.posicion] = auxiliar;
        }
    }

    printf("\nSeleccion directa: Vector ordenado exitosamente\n");
}
