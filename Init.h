#pragma once

#include "Queue.h"
#include "List.h"


void loadDatabase(LIST* lst_idsXNombres[], QUEUE* que_idsToAssign, FILE* f_database);

void saveIdsToAssign(QUEUE* que_idsToAssign);
