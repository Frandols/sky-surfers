#include <stdio.h>
#include <stdbool.h>

#define MAX 10

typedef int tVectorEntero[MAX];

bool existeElementoBuscadoSecuencialmenteEnArregloOrdenado(tVectorEntero, int);
void notificarExistencia(int, bool);


bool existeElementoBuscadoSecuencialmenteEnArregloOrdenado(tVectorEntero _Vector, int elementoBuscado) {

    int i = 0;

    while(_Vector[i] < elementoBuscado && i <= MAX) i++;

    if(_Vector[i] == elementoBuscado) return true;

    return false;
}

void notificarExistencia(int elementoBuscado, bool existeElementoBuscado) {
    printf("Resultado de la busqueda del elemento %.2f: El elemento %s existe en el vector\n", elementoBuscado, existeElementoBuscado ? "si" : "no");
}
