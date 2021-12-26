#include <stdio.h>
#include <string.h>

#include "Init.h"
#include "Queue.h"
#include "List.h"
#include "File.h"


void loadDatabase(LIST* lst_idsXNombres[], QUEUE* que_idsToAssign, FILE* f_database)
{
	/* Vector de listas de nombres por usuario:
	25 letras distintas en total (sin la enie) (25 minusculas + 25 mayusculas)
	Ordenados por letras // a = pos0, b = pos1, c = pos2, ...
	A = pos25, B = pos26, C = pos27, Z = pos 49...
	En codifo ASCII, la 'a' es 65 y la 'A' es 97; por lo que para que las 'a' se guarden en la posicion 0 del vector; habra que restarle
	65 y a 'A' en la posicion 25 del vector, habra que restarle 97 - 25 (72).
	*/ 
	
	USUARIO Usuario;
	ID_X_NOMBRE IdXNombre;
	int i = 0;

	read(&Usuario, f_database);
	while (!feof(f_database)) {
		// Si el primer caracter del nombre era '-', el usuario con la ID de esa posicion habia sido eliminado (i en este caso representa la ID):
		if (Usuario.nombre[0] != '-') {
			IdXNombre.id = i;
			strcpy(IdXNombre.nombre, Usuario.nombre);
			if (Usuario.nombre[0] < 91){ // Es mayuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
				// Se insertan ordenados alfabeticamente para poder encontrarse los valores por nombre de forma mas rapida:
				insertOrdered(IdXNombre, &lst_idsXNombres[Usuario.nombre[0] - 65]);
			} else { // Es minuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
				insertOrdered(IdXNombre, &lst_idsXNombres[Usuario.nombre[0] - 72]);
			}
		} else {
			queue(i, que_idsToAssign);
		}
		read(&Usuario, f_database);
		i++;
	}

	return;
}
