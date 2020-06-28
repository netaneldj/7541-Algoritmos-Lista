#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct lista;
typedef struct lista lista_t;

/*El iterador está planteado como para recorrer una lista de punteros genéricos*/

struct lista_iter;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista vacia o devuelve NULL en caso de error.
// Post: devuelve una nueva lista vacía o NULL.
lista_t* lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al comienzo de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al comienzo de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Borra el primer elemento de la lista y devuelve su valor o NULL en el caso en que lista haya estado vacia.
// Pre: la lista fue creada.
// Post: se elimino el primer elemento de la lista, cuando no está vacía.
void* lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del último, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t* lista);

// Devuelve el tamaño de la lista, la cantidad de elementos que posee.
// Pre: la lista fue creada.
// Post: se devolvió el tamaño de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


/* ******************************************************************
 *                    PRIMITIVAS DE ITERACIÓN EXTERNA
 * *****************************************************************/

// Crea un iterador para la lista o devuelve NULL en caso de error.
// Pre: la lista fue creada.
// Post: devuelve una nueva lista vacía o NULL.
lista_iter_t* lista_iter_crear(lista_t *lista);

// Avanza el iterdador al proximo elemento de la lista, devuelve false en el caso
// en que se haya terminado la lista
// Pre: el iterador fue creado.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el valor del elemento de la lista en el que se encuentra el iterador
// Pre: el iterador fue creado
// Post: se devolvío el valor elemento de la lista el que se encuentra el iterador
void* lista_iter_ver_actual(const lista_iter_t *iter);

// Pregunta si el iterador se encuentra al final de la lista
// devuelve true en el caso afirmativo o false en el caso contrario
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador
// Pre: el iterador fue creado
// Post: se destruyo el iterador
void lista_iter_destruir(lista_iter_t *iter);

// Intenta insertar un elemento entre el anterior y el actual del iterador, en la lista, devuelve falso en caso de error.
// Pre: el iterador fue creado
// Post: se inserto un elemento al iterador o false en el caso de error
bool lista_iter_insertar(lista_iter_t *iter, void *dato);


// Borra el elemento actual del iterador y lo devuelve
// Pre: el iterador fue creado
// Post: se borro el elemento actual de la lista o NULL en el caso de no poder realizarse la operacion
void* lista_iter_borrar(lista_iter_t *iter);


/* ******************************************************************
 *                    PRIMITIVAS DE ITERACIÓN INTERNA
 * *****************************************************************/
 
// la función de callback "visitar" recibe el dato y un puntero extra,
// y devuelve true si se debe seguir iterando, false en caso contrario
// Pre: la lista fue creada
// Post: se itero la lista

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.

void pruebas_lista_alumno(void);

#endif // LISTA_H
