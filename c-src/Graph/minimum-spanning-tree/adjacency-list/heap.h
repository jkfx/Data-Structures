#ifndef _PriorityQueue_H
#define _PriorityQueue_H

struct PriorityQueueCell;
struct PriorityQueue;
typedef struct PriorityQueueCell HeapElement;
typedef struct PriorityQueue *Heap;

Heap BuildHeap(Graph G);
HeapElement DeleteMin(Heap H);
void DestroyHeap(Heap G);
void PercolateDown(int i, Heap H);
#endif /*  _PriorityQueue_H */