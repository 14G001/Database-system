#pragma once

#include <stdbool.h>

#include "Database.h"


bool esLetra(char c);
bool nombreValido(char nombre[]);
int nombreYaUsado(char nombre[], LIST* lst_idsXNombres[]);
bool contrasenaValida(char contrasena[]);
USUARIO idValida(int id, FILE* file);
