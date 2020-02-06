#ifndef _Queue_H
#define _Queue_H
#include "graph.h"

typedef VertexType ElementType;
struct QueueNode;
typedef struct QueueNode *Queue;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int Capacity);
void Enqueue(ElementType X, Queue Q);
void Dequeue(Queue Q);
ElementType Front(Queue Q);
ElementType FrontAndDequeue(Queue Q);
void DisposeQueue(Queue Q);
int IsInQueue(ElementType X,Queue Q);

#endif /*  _Queue_H */