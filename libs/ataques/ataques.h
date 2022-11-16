#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct nodo{
	int x, y;
	struct nodo *siguiente;
} Ataque;

typedef struct{
	Ataque *principio;
	Ataque *final;
} Ataques;

Ataques ataques;

void inicializar();
bool colaVacia();
void insertarAtaque(Ataque);
void eliminarAtaque();
float tiempoDeEspera(Ataque, int);
bool ataqueGolpeoJugador(int, int);

void inicializar(){
	ataques.principio = NULL;
	ataques.final = NULL;
}

bool colaVacia(){
	return ataques.final == NULL;
}

void insertarAtaque(Ataque ataque){
	Ataque *nuevoAtaque;
	nuevoAtaque = (Ataque *) malloc(sizeof(Ataque));
	nuevoAtaque->x = ataque.x;
	nuevoAtaque->y	= ataque.y;
	nuevoAtaque->siguiente = NULL;
	
	if(colaVacia()) {
		ataques.principio = nuevoAtaque;
		ataques.final = nuevoAtaque;

		return;
	}

	ataques.final->siguiente = nuevoAtaque;
	ataques.final = nuevoAtaque;
}

void eliminarAtaque(){
	if(colaVacia()) return;

	Ataque *aux;
	aux = ataques.principio;
	
	if (ataques.principio == ataques.final){		
		free(aux);
		inicializar();

		return;
	}

	ataques.principio = aux->siguiente;
	free(aux);
}

float tiempoDeEspera(Ataque ataque, int posicionJugador) {
	int catetoOpuesto = posicionJugador - ataque.x;
	int catetoAdyacente = 441 - ataque.y;
	float hipotenusa = (float) sqrt(pow(catetoOpuesto, 2) + pow(catetoAdyacente, 2));

	return (float) (hipotenusa / 800) * 1000;
}

bool ataqueGolpeoJugador(int destinoDelAtaque, int posicionJugador) {
	return posicionJugador > destinoDelAtaque - 100 && posicionJugador < destinoDelAtaque + 100;
}