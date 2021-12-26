#pragma once

#include <stdbool.h>

#define ARR_LEN 52


typedef struct ID_X_NOMBRE {
	int id;
	char nombre[ARR_LEN];
} ID_X_NOMBRE;


typedef struct LIST {
	ID_X_NOMBRE valor;
	struct LIST* next;
} LIST;


void createL(LIST** list);
int isin(char nombre[], LIST** list);
void insertOrdered(ID_X_NOMBRE valor, LIST** list);
int deleteByName(char nombre[], LIST** list);
void modifyName(char nombre[], char nuevoNombre[], LIST** list);
int modifyPassword(char nombre[], char nuevaContrasena[], LIST** list);
void clearL(LIST** list);
