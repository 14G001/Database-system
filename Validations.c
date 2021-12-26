#include <stdbool.h>

#include "Database.h"
#include "File.h"


bool esLetra(char c)
{
//							Compares:
	if (c > 64 && c < 91 ||	// A - Z
		c > 96 && c < 123	// a - z
	) {
	   	return true;
	}	
	return false;
}


bool nombreValido(char nombre[])
{
	if (!esLetra(nombre[0])) {
		printf("\n\nERROR: El primer caracter debe ser una letra.\n\n");
		return false;
	}
	
	for (char i = 1; i < ARR_LEN; i++) {
		if (nombre[i] == '\0') {
			if (i > 4) {
				if (nombre[i - 1] == ' ') {
					printf("\n\nERROR: El ultimo caracter no puede ser un espacio (' ').\n\n");
					return false;
				}
				return true;
			} else {
				printf("\n\nERROR: El nombre debe tener 5 caracteres como minimo.\n\n");
				return false;	
			}
		}
	}
	
	printf("\n\nERROR: El nombre debe tener menos de 51 caracteres.\n\n");
	return false;
}


int nombreYaUsado(char nombre[], LIST* lst_idsXNombres[])
{
	int id;
	
	if (nombre[0] < 91){ // Es mayuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
		id = isin(nombre, &lst_idsXNombres[nombre[0] - 65]);
	} else { // Es minuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa:
		id = isin(nombre, &lst_idsXNombres[nombre[0] - 72]);
	}
	
	return id;
}


bool contrasenaValida(char contrasena[])
{
	if (contrasena[0] == ' ') {
		printf("\n\nERROR: El primer caracter no puede ser un espacio (' ').\n\n");
		return false;
	}
	
	for (char i = 0; i < ARR_LEN; i++) {
		if (contrasena[i] == '\0') {
			if (i > 7) {
				return true;
			} else {
				printf("\n\nERROR: La contrasena debe tener 8 caracteres como minimo.\n\n");
				return false;	
			}
		}
	}
	printf("\n\nERROR: El nombre debe tener menos de 51 caracteres.\n\n");
	return false;
}


// Se chequea que las dimensiones del archivo sean mas grandes que las del valor del ID ingresado.
USUARIO idValida(int id, FILE* f_database)
{
	USUARIO Usuario;
	fseek(f_database, 0, SEEK_END);
	int F_LEN = ftell(f_database)/sizeof(USUARIO);
	
	if (id >= F_LEN) {
		printf("\n\nERROR: Esa ID no existe.\n\n");
		Usuario.nombre[0] = '-';
		return Usuario;
	}
	
	fseek(f_database, id*sizeof(USUARIO), SEEK_SET);
	read(&Usuario, f_database);
	if (Usuario.nombre[0] == '-') {
		printf("\n\nERROR: El usuario con esa ID ya habia sido eliminado.\n\n");
		// Usuario.nombre[0] = '-'; // <--- Ya hecho.
		return Usuario;
	}
	return Usuario;
}
