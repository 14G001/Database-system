#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Queue.h"


void create(QUEUE* que)
{
	que->head = NULL;
	que->tail = NULL;
	return;
}


void queue(int valor, QUEUE* que)
{
	Q_NODE* newQue = malloc(sizeof(Q_NODE));
	newQue->valor = valor;
	newQue->next = NULL;
	if (que->head == NULL) {
		que->head = newQue;
	} else {
		que->tail->next = newQue;
	}
	que->tail = newQue;
	return;
}


int dequeue(QUEUE* que)
{
	int valor = que->head->valor;
	Q_NODE* recQue = que->head;
	que->head = que->head->next;
	free(recQue);
	return valor;
}


void clear(QUEUE* que)
{
	while (que->head != NULL) {
		dequeue(que);
	}
	return;
}
