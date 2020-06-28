#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "lista.h"
#include "testing.h"
#define ELEMENTOS 500

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

//Funcion destruir dato

void destruir_dato(void* valor){
	free(valor);
}

//Funciones de prueba de listas

void prueba_inser_ver_ultimo(lista_t* mi_lista,int valores[]){
	printf("Prueba de insertar ultimo y ver ultimo de la lista...\n");
	print_test("La lista esta vacia ",lista_esta_vacia(mi_lista));
	for(int i=0;i<ELEMENTOS;i++){
		printf("Prueba nro: %d\n",i+1);
		lista_insertar_ultimo(mi_lista,&valores[i]);
		print_test("Son iguales ultimo insertado y la direccion del arreglo ",lista_ver_ultimo(mi_lista)==&valores[i]);
	}
	printf("\n");
}

void prueba_borrar_lista(lista_t* mi_lista){
	printf("Prueba de borrado de lista...\n");
	while(!lista_esta_vacia(mi_lista)){
			print_test("La lista no esta vacia ",!lista_esta_vacia(mi_lista));
			printf("La cantidad de elementos en la lista es: %d\n",(int)lista_largo(mi_lista));
			lista_borrar_primero(mi_lista);
	}
	print_test("La lista esta vacia ",lista_esta_vacia(mi_lista));	
	printf("La cantidad de elementos en la lista es: %d\n",(int)lista_largo(mi_lista));
	printf("\n");
}

void prueba_inser_ver(lista_t* mi_lista1,lista_t* mi_lista2){
	printf("Prueba de insertar primero y ver primero de dos listas...\n");
	print_test("La lista 1 esta vacia ",lista_esta_vacia(mi_lista1));
	print_test("La lista 2 esta vacia ",lista_esta_vacia(mi_lista2));
	for(int i=0;i<ELEMENTOS;i++){
		printf("Prueba nro: %d\n",i+1);
		int* punt1 = malloc(sizeof(int));
		*punt1 = i;
		lista_insertar_primero(mi_lista1,punt1);
		lista_insertar_primero(mi_lista2,punt1);
		print_test("Son iguales primero insertado y puntero de la lista 1",lista_ver_primero(mi_lista1)==punt1);
		print_test("Son iguales primero insertado y puntero de la lista 2",lista_ver_primero(mi_lista2)==punt1);
	}
	printf("\n");
}

//Funciones de prueba de iteradores

void prueba_iter_insertar(lista_iter_t* mi_iter){
	printf("Comienzan las pruebas de insertar nodos por medio del iterador de la lista...\n");
	for(int i=0;i<ELEMENTOS;i++){
		printf("Se inserta el nodo nro: %d\n",i+1);
		int* punt = malloc(sizeof(int));
		*punt = i;
		void* act = lista_iter_ver_actual(mi_iter);
		lista_iter_insertar(mi_iter,punt);
		print_test("Son distintos anterior y actual ",lista_iter_ver_actual(mi_iter)!=act);
	}
	printf("\n");
}

void prueba_iter_borrar(lista_t* mi_lista,lista_iter_t* mi_iter){
	printf("Comienza el borrado de los elementos de la lista por medio del iterador...\n");
	print_test("La lista no esta vacia ",!lista_esta_vacia(mi_lista));
	while(!lista_esta_vacia(mi_lista)){
		destruir_dato(lista_iter_borrar(mi_iter));
	}
	print_test("La lista esta vacia ",lista_esta_vacia(mi_lista));
	printf("\n");
}

void prueba_avanzar_iter_actual_final(lista_iter_t* mi_iter1,lista_iter_t* mi_iter2){
	printf("Comienza la prueba de avanzar los iteradores de las listas...\n");
	print_test("El iterador1 no se encuentran al final ",!lista_iter_al_final(mi_iter1));
	print_test("El iterador2 no se encuentran al final ",!lista_iter_al_final(mi_iter2));
	while(lista_iter_avanzar(mi_iter1) && lista_iter_avanzar(mi_iter2)){
		print_test("Coinciden ambas direcciones de memoria ",lista_iter_ver_actual(mi_iter1)==lista_iter_ver_actual(mi_iter2));
	}
	print_test("El iterador1 se encuentran al final ",lista_iter_al_final(mi_iter1));
	print_test("El iterador2 se encuentran al final ",lista_iter_al_final(mi_iter2));
	printf("Ya se recorrieron ambas listas\n");
	printf("\n");
}

//Funcion de prueba de iterador interno

//Verifica si los elementos son pares o no, para cuando la suma de los pares es mayor o igual a 20
bool visitar(void *dato, void *extra){
	if(*(int*)extra>=20)return false;
	if(*(int*)dato%2==0){
		*(int*)extra+=*(int*)dato;
		printf("El numero ingresado es par!\n");
	} else {
		printf("El numero ingresado es impar!\n");
	}
	return true;
}

/*bool visitar(void *dato, void *extra){
	if(*(int*)dato%2==0){
		*(int*)extra+=*(int*)dato;
		printf("El numero ingresado es par!\n");
	} else {
		printf("El numero ingresado es impar!\n");
	}
	return true;
}*/

void prueba_iter_int(lista_t* mi_lista){
	printf("Comienzan las pruebas del iterador interno...\n");
	printf("Analizo si los numeros almacenados en la lista son pares o no!\n");
	for(int i=0;i<ELEMENTOS;i++){
		int* val = malloc(sizeof(int));
		if(val==NULL)return;
		*val=i;
		lista_insertar_ultimo(mi_lista,val);
	}
	int* extra = malloc(sizeof(int));
	if(extra==NULL)return;
	*extra = 0;
	lista_iterar(mi_lista,visitar,extra);
	free(extra);
	printf("\n");
}

void pruebas_lista_alumno(void){
	//Creo un array para despues apilar las direcciones de memoria en la lista
    int valores[ELEMENTOS];
    for(int i=0;i<ELEMENTOS;i++){
		valores[i]=i;
	}
	//Creo mis listas
	lista_t* mi_lista = lista_crear();
	lista_t* mi_lista1 = lista_crear();
	lista_t* mi_lista2 = lista_crear();
	
	//Creo mi iterador
	lista_iter_t* mi_iter = lista_iter_crear(mi_lista);
	
	//Funciones de prueba primera lista
	printf("Comienzan las pruebas de la lista enlazada...\n");
	printf("\n");
	prueba_inser_ver_ultimo(mi_lista,valores);
	prueba_borrar_lista(mi_lista);
	prueba_iter_insertar(mi_iter);
	prueba_iter_borrar(mi_lista,mi_iter);
	
	//Prueba del iterador interno
	prueba_iter_int(mi_lista);
	
	//Funciones de prueba par de listas
	prueba_inser_ver(mi_lista1,mi_lista2);
	
	//Creo mis iteradores
	lista_iter_t* mi_iter1 = lista_iter_crear(mi_lista1);
	lista_iter_t* mi_iter2 = lista_iter_crear(mi_lista2);
	
	//Funciones de prueba de los iteradores
	prueba_avanzar_iter_actual_final(mi_iter1,mi_iter2);
	
	//Destruyo el iterador
	lista_iter_destruir(mi_iter);
	lista_iter_destruir(mi_iter1);
	lista_iter_destruir(mi_iter2);
	
	//Destruyo la lista
	lista_destruir(mi_lista,destruir_dato);
	lista_destruir(mi_lista1,destruir_dato);
	lista_destruir(mi_lista2,NULL);
}
