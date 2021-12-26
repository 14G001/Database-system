#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "File.h"


FILE* openb(char name[])
{
	FILE* file = fopen(name, "rb+");
	if (file == NULL) {
		file = fopen(name, "wb+");
	}
	return file;
}


FILE* opent()
{
	time_t acttime;
	time(&acttime); // <--- Obtiene la hora actual.
	struct tm* t = localtime(&acttime);

	char filePath[32]; // Format: "Database/Backups/DD-MM-AAAA.txt"
	sprintf(filePath, "Database/Actions registry/%i-%i-%i.txt", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
	
	FILE* file = fopen(filePath, "a");
	if (file == NULL) {
		file = fopen(filePath, "w");
	}
	
	return file;
}


void readi(int* valor, FILE* file)
{
	fread(valor, sizeof(int), 1, file);
	return;
}


void writei(int* valor, FILE* file)
{
	fwrite(valor, sizeof(int), 1, file);
	return;
}


void read(USUARIO* valor, FILE* file)
{
	fread(valor, sizeof(USUARIO), 1, file);
	return;
}


void write(USUARIO* valor, FILE* file)
{
	fwrite(valor, sizeof(USUARIO), 1, file);
	fflush(file);
	return;
}


void close(FILE* file)
{
	fclose(file);
	free(file);
	return;
}
