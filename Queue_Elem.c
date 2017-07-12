#include <stdio.h>
#include <stdlib.h>

#include "Queue_Elem.h"

struct Queue_Element{
	int row,column;
	int move;

	Queue_ElementPtr next,prev;
};

Queue_ElementPtr QueueElement_Create(int r,int c,int move_num){
	Queue_ElementPtr queue_elem;

	queue_elem = malloc(sizeof(struct Queue_Element));

	queue_elem->row = r;
	queue_elem->column = c;
	queue_elem->move = move_num;

	queue_elem->next = NULL;
	queue_elem->prev = NULL;

	return queue_elem;
}

void QueueElement_InsertFirst(Queue_ElementPtr new,Queue_ElementPtr first){

	new->next = first;
	first->prev = new;

	return;
}

void QueueElement_Delete(Queue_ElementPtr* last,int* row,int* column,int* moves){
	Queue_ElementPtr temp = *last;

	*row = (*last)->row;
	*column = (*last)->column;
	*moves = (*last)->move;

	(*last) = (*last)->prev;
	if((*last) != NULL)
		(*last)->next = NULL;
	
	free(temp);
}



void QueueElement_DestroyList(Queue_ElementPtr element){
	if(element != NULL){
		QueueElement_DestroyList(element->next);
		free(element);
	}
}

int QueueElement_Search(Queue_ElementPtr first,int row,int column){
	Queue_ElementPtr current;

	current = first;

	while(current != NULL){
		if(current->row == row && current->column == column){
			return 1;
		}

		current = current->next;
	}

	return 0;
}