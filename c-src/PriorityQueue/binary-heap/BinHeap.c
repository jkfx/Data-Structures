#include <stdio.h>
#include <stdlib.h>
#include "BinHeap.h"

#define MinData (-2147483648)

struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};

PriorityQueue Initialize(int MaxELemnts)
{
    PriorityQueue H;

    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if (H == NULL)
        exit(0);

    /* Allocate the array plus one extra for sentinel */
    H->Elements = (ElementType *)malloc(sizeof(ElementType) * (MaxELemnts + 1));
    if (H->Elements == NULL)
        exit(0);

    H->Capacity = MaxELemnts;
    H->Size = 0;
    H->Elements[0] = MinData;

    return H;
}

void Insert(ElementType X, PriorityQueue H)
{
    int i;

    if (IsFull(H))
        exit(0);

    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;

    if (IsEmpty(H))
        return H->Elements[0];
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for (i = 1; i * 2 <= H->Size; i = Child)
    {
        /* Find smaller child */
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;

        /* Percolate one level */
        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
    return H->Size == H->Capacity - 1;
}

int main()
{
    PriorityQueue H;
    ElementType MinElement;
    H = Initialize(16);
    Insert(13, H);
    Insert(14, H);
    Insert(16, H);
    Insert(19, H);
    Insert(21, H);
    Insert(19, H);
    Insert(68, H);
    Insert(65, H);
    Insert(26, H);
    Insert(32, H);
    Insert(31, H);
    MinElement = DeleteMin(H);
    system("pause");
    return 0;
}