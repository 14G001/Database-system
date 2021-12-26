#include <stdio.h>
#include <stdlib.h>

#include "Input.h"


void inputString(char input[], int size)
{
    fgets(input, size, stdin);

    int i = 0;
    for (i; i < size && input[i] != '\n' && input[i] != '\0'; i++);

    if (input[i] == '\n') {
        input[i] = '\0';
        i++;
        while (i < size) { // si hay mas de 2 '\0' en el espacio de memoria de un string, el SO entiende que termino de analizar el "string" completamente.
            if (input[i] == '\0') {
                input[i] = 'a';
            }
            i++;
        }
    }
    return;
}


int inputInt(int size)
{
    char input[size];
    fgets(input, size, stdin);
    return atoi(input);
}


float inputFloat(int size)
{
    char input[size];
    fgets(input, size, stdin);
    return atof(input);
}


char inputChar(int size)
{
    char input[size];
    fgets(input, size, stdin);
    return input[0];
}


char elegirOpcion()
{
    char input[3];
    printf("1- Agregar un nuevo usuario\n");
    printf("2- Eliminar un usuario\n");
    printf("3- Modificar los datos de un usuario\n");
    printf("4- Generar un archivo de texto con los datos de la base de datos\n");
    printf("5- Salir\n\n");
    fgets(input, 3, stdin);
    printf("\n\n");
    return input[0];
}
