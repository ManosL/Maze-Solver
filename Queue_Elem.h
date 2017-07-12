#ifndef __QUEUE_ELEM__
#define __QUEUE_ELEM__

typedef struct Queue_Element* Queue_ElementPtr;

Queue_ElementPtr QueueElement_Create();
void QueueElement_InsertFirst(Queue_ElementPtr,Queue_ElementPtr);
void QueueElement_Delete(Queue_ElementPtr*,int*,int*,int*);
void QueueElement_DestroyList(Queue_ElementPtr);
int QueueElement_Search(Queue_ElementPtr,int,int);

#endif