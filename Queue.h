#ifndef __QUEUE__
#define __QUEUE__

typedef struct Queue* QueuePtr;

QueuePtr Queue_Create();
void Queue_Insert(QueuePtr,int,int,int);
void Queue_Delete(QueuePtr,int*,int*,int*);
int Queue_Empty(QueuePtr);
void Queue_Destroy(QueuePtr*);
int Queue_Search(QueuePtr,int,int);

#endif