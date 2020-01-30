#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define MinQueueSize (5)

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

int IsFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

void MakeEmpty(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

static int Succ(int Value, Queue Q)
{
    if (++Value == Q->Capacity)
        Value = 0;
    return Value;
}

void Enqueue(ElementType X, Queue Q)
{
    if (IsFull(Q))
    {
        printf("Queue is full!\n");
        system("pause");
        exit(0);
    }
    else
    {
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

void Dequeue(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("Queue is empty!\n");
        system("pause");
        exit(0);
    }else{
        Q->Size--;
    }
}