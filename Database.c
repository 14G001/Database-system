#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "Database.h"
#include "File.h"
#include "Queue.h"
#include "Input.h"
#include "List.h"
#include "Validations.h"




void writeAction(FILE* f_actions, char action[], char nombre[], int id)
{
	time_t acttime;
	time(&acttime); // <--- Obtiene la hora actual.
	struct tm* t = localtime(&acttime); // <--- Convierte la estructura en la fecha actual

	fprintf(f_actions, "%i:%i:%i - %s: %s - ID: %i\n", t->tm_hour, t->tm_min, t->tm_sec, action, nombre, id);
	fflush(f_actions);
	
	return;
}




void agregarUsuario(FILE* f_database, QUEUE* que_idsToAssign, LIST* lst_idsXNombres[], FILE* f_actions)
{
	USUARIO Usuario;
	
	printf("\n\nIngrese los datos del usuario:\n\n");
	printf("Nombre: ");
	inputString(Usuario.nombre, sizeof(char)*ARR_LEN);
	if (!nombreValido(Usuario.nombre)) { return; }
	int id = nombreYaUsado(Usuario.nombre, lst_idsXNombres);
	if (id != -1) {
		printf("\n\nERROR: Ya existe un usuario con ese nombre.\n\n");
		return;
	}
	
	printf("Contrasena: ");
	inputString(Usuario.contrasena, sizeof(char)*ARR_LEN);
	printf("\n\n\n");
	if (!contrasenaValida(Usuario.contrasena)) { return; }
	
	
	if (que_idsToAssign->head != NULL) { // is not empty
		// EL ID DEL USUARIO EQUIVALE A SU POSICION EN EL ARCHIVO.
		// IDS: Van de 0 a N.
		fseek(f_database, dequeue(que_idsToAssign)*sizeof(USUARIO), SEEK_SET);
	} else {
		fseek(f_database, 0, SEEK_END);
	}
	
	ID_X_NOMBRE IdXNombre;
	IdXNombre.id = (ftell(f_database)/sizeof(USUARIO));
	strcpy(IdXNombre.nombre, Usuario.nombre); // Se podria sacar el primer caracter para procesar un caracter menos ya que por su posicion, se conoce el primer caracter de las listas y por cada comparasion, se compararia un caracter menos y por cada registro se tendria un byte menos; sin embargo; esto seria mas optimo para una base de datos que funcione como servidor web o que reciba grandes cantidades de datos y no para un programa local dentro de la misma maquina, ya que habria que convertir muchas cadenas para sacarles el primer caracter y volverselo a poner luego y hacer mas procesamiento innecesario.	
	
	write(&Usuario, f_database);
	
	if (Usuario.nombre[0] < 91){ // Es mayuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
		// Inserta ordenado alfabeticamente para que despues sea mas facil encontrarlo:
		insertOrdered(IdXNombre, &lst_idsXNombres[Usuario.nombre[0] - 65]);
	} else { // Es minuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
		insertOrdered(IdXNombre, &lst_idsXNombres[Usuario.nombre[0] - 72]);
	}
	
	writeAction(f_actions, "ADDED", IdXNombre.nombre, IdXNombre.id);
	
	return;
}




void writeDeleted(FILE* f_actions, USUARIO* Usuario, int id, FILE* f_database, QUEUE* que_idsToAssign)
{
	writeAction(f_actions, "DELETED", Usuario->nombre, id);

	// PARA MARCAR UN USUARIO COMO ELIMINADO, SE DEJA EL PRIMER CARACTER DE SU NOMBRE COMO "-":
	Usuario->nombre[0] = '-';
	fseek(f_database, (-1)*sizeof(USUARIO), SEEK_CUR);
	write(Usuario, f_database);
	queue(id, que_idsToAssign);
	
	return;
}


void eliminarUsuario(FILE* f_database, QUEUE* que_idsToAssign, LIST* lst_idsXNombres[], FILE* f_actions)
{
	printf("\n\nIngrese 1 si quiere eliminar al usuario por su nombre y 2 si quiere eliminarlo por su ID: ");
	char opcion = inputChar(3);
	
	if (opcion == '1') {
		// NO FUNCIONA ESTA OPCION DE ELIMINAR POR EL NOMBRE:
		
		char nombre[ARR_LEN];
		printf("\n\nIngrese el nombre del usuario que quiere eliminar: ");
		inputString(nombre, sizeof(char)*ARR_LEN);
		
		if (!nombreValido(nombre)) { return; }
		
		int id;
		if (nombre[0] < 91){ // Es mayuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
			id = deleteByName(nombre, &lst_idsXNombres[nombre[0] - 65]);
		} else { // Es minuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
			id = deleteByName(nombre, &lst_idsXNombres[nombre[0] - 72]);
		}
		
		if (id == -1) {
			printf("\n\nERROR: No se ha podido encontrar un usuario con ese nombre.\n\n");
			return;
		}
		
		USUARIO Usuario;
	
		// Recordar que las IDs de los usuarios van de 0 a N.
		fseek(f_database, id*sizeof(USUARIO), SEEK_SET);
		read(&Usuario, f_database);
		if (Usuario.nombre[0] == '-') {
			printf("\n\nERROR: El usuario con esa ID ya habia sido eliminado.\n\n");
			return;
		}
		
		writeDeleted(f_actions, &Usuario, id, f_database, que_idsToAssign);
		
	} else if (opcion == '2') {
		
		printf("\n\nIngrese el ID del usuario que quiere eliminar: ");
		int id = inputInt(20);
		
		USUARIO Usuario = idValida(id, f_database);
		if (Usuario.nombre[0] == '-') { return; }
	
		// Recordar que las IDs de los usuarios van de 0 a N.
		if (Usuario.nombre[0] < 91){ // Es mayuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
			deleteByName(Usuario.nombre, &lst_idsXNombres[Usuario.nombre[0] - 65]);
		} else { // Es minuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
			deleteByName(Usuario.nombre, &lst_idsXNombres[Usuario.nombre[0] - 72]);
		}
		
		writeDeleted(f_actions, &Usuario, id, f_database, que_idsToAssign);
		
	} else {
		printf("\n\nERROR: Esa opcion no existe.\n\n");
	}
	
	printf("\n\n\n");
	return;
}




void fullyModifyUser(char opcion, int id, char nuevoDato[], FILE* f_database, FILE* f_actions)
{
	USUARIO Usuario;
	fseek(f_database, id*sizeof(USUARIO), SEEK_SET);
	read(&Usuario, f_database);
	if (opcion == '1') {
		strcpy(Usuario.nombre, nuevoDato);
	} else { // Opcion == '2'
		strcpy(Usuario.contrasena, nuevoDato);	
	}
	fseek(f_database, (-1)*sizeof(USUARIO), SEEK_CUR);
	write(&Usuario, f_database);

	writeAction(f_actions, "MODIFIED", Usuario.nombre, id);
		
	return;
}


void modificarDatosUsuario(FILE* f_database, LIST* lst_idsXNombres[], FILE* f_actions)
{
	char nombre[ARR_LEN];
	printf("\n\nIngrese el nombre del usuario: ");
	inputString(nombre, ARR_LEN);
	if (!nombreValido(nombre)) { return; }
	int id = nombreYaUsado(nombre, lst_idsXNombres);
	if (id == -1) {
		printf("\n\nERROR: Ese usuario no existe.\n\n");	
		return;
	}
	
	printf("\n\nIngrese 1 si quiere modificar su nombre y 2 si quiere modificar su contrasena: ");
	char opcion = inputChar(3);

	char nuevoDato[ARR_LEN];
	
	if (opcion == '1') {

		printf("\n\nIngrese el nuevo nombre: ");
		inputString(nuevoDato, ARR_LEN);
		if (!nombreValido(nuevoDato)) { return; }
		if (nombreYaUsado(nuevoDato, lst_idsXNombres) != -1) {
			printf("\n\nERROR: Ya existe un usuario con ese nombre.\n\n");
			return;
		}

		if (nombre[0] < 91){ // Es mayuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
			modifyName(nombre, nuevoDato, &lst_idsXNombres[nombre[0] - 65]);
		} else { // Es minuscula; sino no podria estar en la base de datos a no ser que haya sido agregado con otro programa.
			modifyName(nombre, nuevoDato, &lst_idsXNombres[nombre[0] - 72]);
		}
		
		fullyModifyUser(opcion, id, nuevoDato, f_database, f_actions);
		
	} else if (opcion == '2') {

		printf("\n\nIngrese la nueva contrasena: ");
		inputString(nuevoDato, ARR_LEN);
		if (!contrasenaValida(nuevoDato)) { return; }
		fullyModifyUser(opcion, id, nuevoDato, f_database, f_actions);
		
	} else {
		printf("\n\nERROR: Esa opcion no existe.\n\n");
	}
	
	printf("\n\n\n");
	return;
}




void generarCopiaTxtDB(FILE* f_database)
{
	time_t acttime;
	time(&acttime); // <--- Obtiene la hora actual.
	struct tm* t = localtime(&acttime); // <--- Convierte la estructura en la fecha actual

	char filePath[41]; // Format: "Database/Backups/DD-MM-AAAA HH-MM-SS.txt"
	sprintf(filePath, "Database/Backups/%i-%i-%i %i-%i-%i.txt", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,  t->tm_hour, t->tm_min, t->tm_sec);
	
	FILE* f_backup = fopen(filePath, "w");
	fprintf(f_backup, "ID\tUsername\tPassword\n\n");
	
	
	USUARIO Usuario;
	
	int i = 0;
	fseek(f_database, 0, SEEK_SET);
	read(&Usuario, f_database);
	while (!feof(f_database)) {
		// Format: <Username>\t<Password>
		if (Usuario.nombre[0] != '-') {
			fprintf(f_backup, "%i\t%s\t%s\n", i, Usuario.nombre, Usuario.contrasena);
		}
		read(&Usuario, f_database);
		i++;
	}

	printf("\n\nCopia de seguridad generada en el archivo \"%s\".\n\n\n", filePath);	
	// free(t); <--- No hay que hacer eso por alguna razon. Se ve que toma el tiempo de la maquina y tratar de liberar su memoria seria como tratar de liberar la memoria del tiempo del sistema operativo.
	close(f_backup);
	return;
}
