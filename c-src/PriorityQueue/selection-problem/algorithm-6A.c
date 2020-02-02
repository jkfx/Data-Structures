#include <stdio.h>
#include <stdlib.h>

#define MaxData (99999999999999)

typedef int ElementType;

struct HeapStruct
{
    ElementType *Elements;
    int Capacity;
    int Size;
};
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxSize);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMax(PriorityQueue H);
int IsFull(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue BuildHeap(ElementType *Elements, int N);
void PercolateDown(int i, PriorityQueue H);
void PrintElements(PriorityQueue H);

int IsFull(PriorityQueue H)
{
    return H->Capacity = H->Size;
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0;
}

PriorityQueue Initialize(int MaxSize)
{
    PriorityQueue H;

    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if (H == NULL)
        exit(0);

    H->Elements = (ElementType *)malloc((MaxSize + 1) * (sizeof(ElementType)));
    if (H->Elements == NULL)
        exit(0);
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MaxData;
    return H;
}

void Insert(ElementType X, PriorityQueue H)
{
    int i;

    if (IsFull(H))
        exit(0);

    for (i = ++H->Size; H->Elements[i / 2] < X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

ElementType DeleteMax(PriorityQueue H)
{
    int i, Child;
    ElementType MaxElement, LastElement;

    if (IsEmpty(H))
        exit(0);

    MaxElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for (i = 1; i * 2 <= H->Size; i = Child)
    {
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] > H->Elements[Child])
            Child++;

        if (LastElement < H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MaxElement;
}

PriorityQueue BuildHeap(ElementType *Elements, int N)
{
    int i;
    PriorityQueue H;
    H = Initialize(N);

    for (H->Size = 1; H->Size <= N; H->Size++)
        H->Elements[H->Size] = Elements[H->Size - 1];
    H->Size--;

    for (i = N / 2; i > 0; i--)
        PercolateDown(i, H);
    return H;
}
void PercolateDown(int i, PriorityQueue H)
{
    int MinSon, Min;
    ElementType Tmp;

    if (i * 2 > H->Size - 1)
        return;

    MinSon = H->Elements[i * 2] > H->Elements[i * 2 + 1] ? i * 2 : i * 2 + 1;
    Min = H->Elements[i] > H->Elements[MinSon] ? i : MinSon;

    Tmp = H->Elements[i];
    H->Elements[i] = H->Elements[Min];
    H->Elements[Min] = Tmp;

    if (i * 2 <= H->Size)
        PercolateDown(MinSon, H);
}

void PrintElements(PriorityQueue H)
{
    int i;
    for (i = 1; i <= H->Size; i++)
        printf("%d  ", H->Elements[i]);
    printf("%\n");
}

void PrintArray(ElementType *Elements, int N)
{
    int i;
    for (i = 0; i < N; i++)
        printf("%d  ", Elements[i]);
    printf("\n");
}

int main()
{
    ElementType Array[15] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
    PriorityQueue H;
    int i, Capacity, k;
    ElementType Element;

    Capacity = 15;
    k = 6;
    PrintArray(Array, 15);
    H = BuildHeap(Array, Capacity);
    PrintElements(H);
    for (i = 0; i < k; i++)
        Element = DeleteMax(H);
    printf("%d\n", Element);

    system("pause");
    return 0;
}