#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct{
	int id;
	int posicion;
}tDatosEnemigos;

typedef struct nodo{
	tDatosEnemigos  datosEnemigos;
	struct nodo * siguiente;
}tNodoEnemigos;

typedef struct{
	tNodoEnemigos * principio;
	tNodoEnemigos * final;
}tCola;

tCola colaEnemigos;
tDatosEnemigos datoEnemigo;

void inicializarCola(tCola);
bool colaVacia(tCola);
void push(tDatosEnemigos);
void pop();

void inicializarCola(){
	colaEnemigos.principio = NULL;
	colaEnemigos.final = NULL;
}

bool colaVacia(tCola pCola){
	return (pCola.principio == NULL && pCola.final == NULL);
}

void push(tDatosEnemigos pDatosEnemigos){
	tNodoEnemigos * nuevoNodo;
	nuevoNodo=(tNodoEnemigos*) malloc(sizeof(tNodoEnemigos));
	nuevoNodo->datosEnemigos = pDatosEnemigos;
	nuevoNodo->siguiente = NULL;
	if(colaVacia(colaEnemigos)){
		colaEnemigos.principio;
		colaEnemigos.final;
	}else{
		colaEnemigos.final->siguiente=nuevoNodo;
		colaEnemigos.final=nuevoNodo;
	}
	printf("\nElemento insertado!...\n");
}

void pop(){
	if(!colaVacia(colaEnemigos)){
		tNodoEnemigos * nodoSuprimir;
		nodoSuprimir = colaEnemigos.principio;
		if(colaEnemigos.principio==colaEnemigos.final){
			inicializarCola();
		}
		free(nodoSuprimir);
		nodoSuprimir = NULL;
	}
}