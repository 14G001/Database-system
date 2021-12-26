#pragma once

#include "Database.h"


FILE* openb(char name[]);

FILE* opent();

void readi(int* valor, FILE* file);

void writei(int* valor, FILE* file);

void read(USUARIO* valor, FILE* file);

void write(USUARIO* valor, FILE* file);

void close(FILE* file);
