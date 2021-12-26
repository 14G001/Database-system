#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "List.h"


void createL(LIST** list)
{
	*list = NULL;
	return;
}


int isin(char nombre[], LIST** list)
{
	LIST* lst_aux = (*list);
	
	// Ya sabemos que la primer letra es la misma que la del nombre; por haber usado un vector con cada nombre que inicie ordenado por codigo ASCII de la letra.
	while (lst_aux != NULL && lst_aux->valor.nombre[2] < nombre[2]) {
		lst_aux = lst_aux->next;
	}
	while (lst_aux != NULL && lst_aux->valor.nombre[2] == nombre[2] && lst_aux->valor.nombre[3] < nombre[3]) {
		lst_aux = lst_aux->next;
	}
	while (lst_aux != NULL && strcmp(lst_aux->valor.nombre, nombre) < 0) {
		lst_aux = lst_aux->next;
	}
	
	if (lst_aux != NULL && strcmp(lst_aux->valor.nombre, nombre) == 0) { // Se encontraba en la lista:
		return lst_aux->valor.id;
	}
	return -1;
}


void insertOrdered(ID_X_NOMBRE valor, LIST** list)
{
	LIST* newNode = malloc(sizeof(LIST));
	newNode->valor = valor;
	newNode->next = NULL;

	LIST* auxList = *list;
	LIST* prevNode = NULL;

	// Ya sabemos que la primer letra es la misma que la del nombre; por haber usado un vector con cada nombre que inicie ordenado por codigo ASCII de la letra.
	while (auxList != NULL && auxList->valor.nombre[2] < valor.nombre[2]) {
		prevNode = auxList;
		auxList = auxList->next;
	}
	while (auxList != NULL && auxList->valor.nombre[2] == valor.nombre[2] && auxList->valor.nombre[3] < valor.nombre[3]) {
		prevNode = auxList;
		auxList = auxList->next;
	}
	while (auxList != NULL && strcmp(auxList->valor.nombre, valor.nombre) < 0) {
		prevNode = auxList;
		auxList = auxList->next;
	}

	if (prevNode != NULL) {
		prevNode->next = newNode;
	} else {
		*list = newNode;
	}

	newNode->next = auxList;
	return;
}


int deleteByName(char nombre[], LIST** list)
{
	LIST* auxList = (*list);
	LIST* prevNode = NULL;

	// Ya sabemos que la primer letra es la misma que la del nombre; por haber usado un vector con cada nombre que inicie ordenado por codigo ASCII de la letra.
	while (auxList != NULL && auxList->valor.nombre[2] < nombre[2]) {
		prevNode = auxList;
		auxList = auxList->next;
	}
	while (auxList != NULL && auxList->valor.nombre[2] == nombre[2] && auxList->valor.nombre[3] < nombre[3]) {
		prevNode = auxList;
		auxList = auxList->next;
	}
	while (auxList != NULL && strcmp(auxList->valor.nombre, nombre) < 0) {
		prevNode = auxList;
		auxList = auxList->next;
	}
	
	// Si  strcmp(auxList->valor.nombre, nombre) es >= 0  Y  auxList->valor.nombre != nombre,  el nombre no se encontraba en la base de datos.
	if (auxList == NULL || strcmp(auxList->valor.nombre, nombre) != 0) {
		return -1;
	} // Sino, se elimina el valor de la lista:
	
	int id = auxList->valor.id;
	
	if (prevNode != NULL) {
		prevNode->next = auxList->next;
	} else {
		*list = auxList->next;
	}
	
	free(auxList);
	
	// Y se retorna la ID buscada:
	return id;
}


void modifyName(char nombre[], char nuevoNombre[], LIST** list)
{
	LIST* lst_aux = (*list);
	
	// Ya sabemos que la primer letra es la misma que la del nombre; por haber usado un vector con cada nombre que inicie ordenado por codigo ASCII de la letra.
	while (lst_aux != NULL && lst_aux->valor.nombre[2] < nombre[2]) {
		lst_aux = lst_aux->next;
	}
	while (lst_aux != NULL && lst_aux->valor.nombre[2] == nombre[2] && lst_aux->valor.nombre[3] < nombre[3]) {
		lst_aux = lst_aux->next;
	}
	while (lst_aux != NULL && strcmp(lst_aux->valor.nombre, nombre) < 0) {
		lst_aux = lst_aux->next;
	}
	
	// Ya sabemos que lo va a encontrar porque fue comprobado antes de ejecutar esta funcion.
	strcpy(lst_aux->valor.nombre, nuevoNombre);
	return;
}


void clearL(LIST** list)
{
	LIST* recNode;
	while (*list != NULL) {
		recNode = *list;
		*list = (*list)->next;
		free(recNode);
	}
	return;
}
