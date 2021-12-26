#pragma once

#include <stdbool.h>


typedef struct Q_NODE {
	int valor;
	struct Q_NODE* next;
} Q_NODE;


typedef struct QUEUE {
	Q_NODE* head; // Se sacan los valores
	Q_NODE* tail; // Ingresan los valores
} QUEUE;


void create(QUEUE* que);

void queue(int valor, QUEUE* que);

int dequeue(QUEUE* que);

void clear(QUEUE* que);
