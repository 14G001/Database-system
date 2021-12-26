#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 52


typedef struct USUARIO {
	char nombre[ARR_LEN];
	char contrasena[ARR_LEN];
} USUARIO;


int main()
{
	USUARIO Usuario;

	FILE* f_dbout = fopen("Database/Database.dat", "rb");
	if (f_dbout == NULL) {
		printf("No se encontro la base de datos.\n\n");
		system("pause");
		return -1;
	}


	printf("\t\tLISTA DE USUARIOS\n\n\n");

	int i = 0;
	fread(&Usuario, sizeof(USUARIO), 1, f_dbout);
	while (!feof(f_dbout)) {
		printf("ID: %i\n", i);
		printf("Nombre: %s\n", Usuario.nombre);
		printf("Contrasena: %s\n\n", Usuario.contrasena);
		fread(&Usuario, sizeof(USUARIO), 1, f_dbout);
		i++;
	}

	fclose(f_dbout);
	free(f_dbout);
	

	printf("\n\n\nWrite 'U' if you want to update data, 'E' if you want to exit: ");

	char opcion;
	scanf("%c", &opcion);

	if (opcion == 'u' || opcion == 'U') {
		main();
	} else if (opcion == 'e' || opcion == 'E') {
		return 0;
	}

	main();
}
