#pragma once

#include <stdio.h>

#include "Queue.h"
#include "List.h"

#define ARR_LEN 52
#define ARR_LEN_REDUX 51


typedef struct USUARIO {
	char nombre[ARR_LEN];
	char contrasena[ARR_LEN];
} USUARIO;


void writeAction(FILE* f_actions, char action[], char nombre[], int id);

void agregarUsuario(FILE* f_database, QUEUE* que_idsToAssign, LIST* lst_idsXNombres[], FILE* f_actions);

void writeDeleted(FILE* f_actions, USUARIO* Usuario, int id, FILE* f_database, QUEUE* que_idsToAssign);
void eliminarUsuario(FILE* f_database, QUEUE* que_idsToAssign, LIST* lst_idsXNombres[], FILE* f_actions);

void fullyModifyUser(char opcion, int id, char nuevoDato[], FILE* f_database, FILE* f_actions);
void modificarDatosUsuario(FILE* f_database, LIST* lst_idsXNombres[], FILE* f_actions);

void generarCopiaTxtDB(FILE* f_database);
