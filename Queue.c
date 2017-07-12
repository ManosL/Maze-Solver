/*Simple Queue Implementations with linked double connected linked list+ last node pointer*/

#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"
#include "Queue_Elem.h"

struct Queue{
	Queue_ElementPtr first;
	Queue_ElementPtr last;
};

QueuePtr Queue_Create(void){
	QueuePtr Queue;

	Queue = malloc(sizeof(struct Queue));
	Queue->first = NULL;
	Queue->last = NULL;

	return Queue;
}

int Queue_Empty(QueuePtr Queue){
	return (Queue->first == NULL && Queue->last == NULL);
}

void Queue_Insert(QueuePtr Queue,int row,int column,int moves){
	Queue_ElementPtr new_element;

	if(Queue_Empty(Queue)){
		new_element = QueueElement_Create(row,column,moves);
		Queue->first = new_element;
		Queue->last = new_element;
	}
	else{
		new_element = QueueElement_Create(row,column,moves);
		QueueElement_InsertFirst(new_element,Queue->first);
		Queue->first = new_element;
	}
}

void Queue_Delete(QueuePtr Queue,int* row,int* column,int* moves){

	if(Queue_Empty(Queue)){
		printf("Error: Queue is empty\n");
		return ;
	}
	else{
		QueueElement_Delete(&(Queue->last),row,column,moves);
		if(Queue->last == NULL){
			Queue->first = NULL;
		}
	}
}

void Queue_Destroy(QueuePtr* Queue){
		QueueElement_DestroyList((*Queue)->first);
		free(*Queue);
		*Queue = NULL;	
	
	return;
}

int Queue_Search(QueuePtr Queue,int row,int column){
	return QueueElement_Search(Queue->first,row,column);
}