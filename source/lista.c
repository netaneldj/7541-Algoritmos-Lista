#include "lista.h"
#include <stdlib.h>
#define VACIA 0

typedef struct nodo_lista{
	void* dato;
	struct nodo_lista* prox;
} nodo_lista_t;

struct lista{
	nodo_lista_t* primero;
	nodo_lista_t* ultimo;
	size_t largo;
};

struct lista_iter{
	nodo_lista_t* actual;
	nodo_lista_t* anterior;
	lista_t* lista;
};

//Funcion auxiliar para crear nodo
nodo_lista_t* nodo_crear(void* valor){
	nodo_lista_t* nuevo_nodo = malloc(sizeof(nodo_lista_t));
	if(nuevo_nodo==NULL)return NULL;
	nuevo_nodo->dato = valor;
	nuevo_nodo->prox = NULL;
	return nuevo_nodo;
}

//Funciones a completar

//Primitivas de la lista
lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if(lista==NULL)return NULL;
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->largo = VACIA;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	if(lista->largo==VACIA && lista->primero==NULL)return true;
	return false;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_lista_t* nuevo_nodo = nodo_crear(dato);
	if(nuevo_nodo==NULL)return false;
	if(lista_esta_vacia(lista)){
		lista->primero = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	} else {
		nuevo_nodo->prox = lista->primero;
		lista->primero = nuevo_nodo;
	}
	lista->largo++;
	return true;		
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_lista_t* nuevo_nodo = nodo_crear(dato);
	if(nuevo_nodo==NULL)return false;
	if(lista_esta_vacia(lista)){
		lista->primero = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	} else {
		lista->ultimo->prox = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	}
	lista->largo++;
	return true;			
}

void* lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista))return NULL;
	nodo_lista_t* nodo_destruir = lista->primero;
	void* valor = lista->primero->dato;
	lista->primero = lista->primero->prox;
	free(nodo_destruir);
	lista->largo--;
	return valor;
}

void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista))return NULL;
	return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista))return NULL;
	return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t* lista, void (*destruir_dato)(void *)){
	while(!lista_esta_vacia(lista)){
		if(destruir_dato!=NULL){
			destruir_dato(lista_borrar_primero(lista));
		} else {
			lista_borrar_primero(lista);
		}
	}
	free(lista);
}

// Primitivas del iterador externo
lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if(iter==NULL)return NULL;
	iter->actual = lista->primero;
	iter->anterior = NULL;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(iter->actual==NULL){
		return false;
	}
	iter->anterior = iter->actual;
	iter->actual = iter->anterior->prox;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(iter->actual==NULL)return NULL;
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	if(iter->actual==NULL)return true;
	return false;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if(iter->actual == iter->lista->primero){
		if(lista_insertar_primero(iter->lista,dato)){
			iter->actual = iter->lista->primero;
			return true;
		}
		return false;
	} else if(iter->actual==NULL){
		if(lista_insertar_ultimo(iter->lista,dato)){
			iter->actual = iter->lista->ultimo;
			return true;
		}
		return false;
	} else {
		nodo_lista_t* nodo_insertar = nodo_crear(dato);
		if(nodo_insertar==NULL)return false;
		iter->anterior->prox = nodo_insertar;
		nodo_insertar->prox =iter->actual;
		iter->actual = nodo_insertar;
		iter->lista->largo++;
		return true; 
	}
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(iter->actual==NULL){
		return NULL;
	} else if(iter->actual==iter->lista->primero){
		iter->actual = iter->actual->prox;
		return lista_borrar_primero(iter->lista);
	} else {
		nodo_lista_t* nodo_destruir = iter->actual;
		void* valor = nodo_destruir->dato;
		iter->anterior->prox = iter->actual->prox;
		iter->actual = iter->anterior->prox;
		if(iter->anterior->prox==NULL){
			iter->lista->ultimo=iter->anterior;
		}
		free(nodo_destruir);
		iter->lista->largo--;
		return valor;
	}
}

// Primitivas del iterador interno
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	if(lista->largo==0)return;
	nodo_lista_t* ant = lista->primero;
	nodo_lista_t* act = ant->prox;
	if(!visitar(ant->dato,extra))return;
	while(act!=NULL){
		ant = act;
		if(!visitar(ant->dato,extra))break;
		act = ant->prox;
	}
}
