#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Init.h"
#include "File.h"
#include "Input.h"
#include "Database.h"
#include "Queue.h"
#include "List.h"


int main() 
{
	// Para poder crear los archivos, tiene que existir la siguiente carpeta.
	// El segundo parametro de "mkdir" son permisos (que no se exactamente de que sirven).
	mkdir("Database", 0777); // Returns 0 if it could create the directory and -1 if it couldn't.
	mkdir("Database/Backups", 0777);
	mkdir("Database/Actions registry", 0777);
	
	FILE* f_database = openb("Database/Database.dat");
	FILE* f_actions = opent();
	
	QUEUE que_idsToAssign; create(&que_idsToAssign);
	LIST* lst_idsXNombres[50];
	for (char i = 0; i < 50; i++) { createL(&lst_idsXNombres[i]); }
	
	// Init:
	loadDatabase(lst_idsXNombres, &que_idsToAssign,f_database);
	
	
	char opcion = elegirOpcion();
	
	while (opcion != '5') {
		// system("cls"); <--- No usar "system()"; tiene vulnerabilidades y no es optimo.
		
		if (opcion == '1') {
			agregarUsuario(f_database, &que_idsToAssign, lst_idsXNombres, f_actions);	
		} else if (opcion == '2') {
			eliminarUsuario(f_database, &que_idsToAssign, lst_idsXNombres, f_actions);
		} else if (opcion == '3') {
			modificarDatosUsuario(f_database, lst_idsXNombres, f_actions);
		} else if (opcion == '4') {
			generarCopiaTxtDB(f_database);
		} else if (opcion != '5') {
			printf("\n\nERROR: Esa opcion no existe.\n\n");
		}

		opcion = elegirOpcion();
	}


	for (char i = 0; i < 50; i++) { clearL(&lst_idsXNombres[i]); }
	close(f_database);
	close(f_actions);
	return 0;
}
