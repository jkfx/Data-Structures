#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MinData (-999999)

typedef int ElementType;
struct HeapStruct
{
    ElementType *Elements;
    int Size;
    int Capacity;
};
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int Capacity);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
PriorityQueue BuildHeap(ElementType *Elements, int N);
void PercolateDown(int i, PriorityQueue H);
int IsFull(PriorityQueue H);
int IsEmpty(PriorityQueue H);
ElementType *RandomIntArray(int Capacity);
void PrintElements(PriorityQueue H);
void PrintArray(ElementType *Elements, int N);

int IsFull(PriorityQueue H)
{
    return H->Size == H->Capacity;
}

int IsEmpty(PriorityQueue H)
{
    return H->Size == 0;
}

PriorityQueue Initialize(int Capacity)
{
    PriorityQueue H;

    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if (H == NULL)
        exit(0);

    H->Size = 0;
    H->Elements = (ElementType *)malloc(sizeof(ElementType) * (Capacity + 1));
    if (H->Elements == NULL)
        exit(0);
    H->Elements[0] = MinData;
    H->Capacity = Capacity;
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
        exit(0);

    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    for (i = 1; i * 2 <= H->Size; i = Child)
    {
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;
        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

PriorityQueue BuildHeap(ElementType *Elements, int N)
{
    int i;
    PriorityQueue H;
    H = Initialize(N);

    for (i = 1; i <= N; i++)
        H->Elements[i] = Elements[i - 1];
    H->Size = N;

    for (i = N / 2; i > 0; i--)
        PercolateDown(i, H);

    return H;
}

void PercolateDown(int i, PriorityQueue H)
{
    int MinSon, Min;
    ElementType Tmp;

    if (i <= H->Size / 2)
    {
        MinSon = i * 2 + 1 <= H->Size && H->Elements[i * 2] > H->Elements[i * 2 + 1] ? i * 2 + 1 : i * 2;
        Min = H->Elements[i] < H->Elements[MinSon] ? i : MinSon;
        Tmp = H->Elements[i];
        H->Elements[i] = H->Elements[MinSon];
        H->Elements[MinSon] = Tmp;
        PercolateDown(MinSon, H);
    }
}

ElementType *RandomIntArray(int Capacity)
{
    int i;
    ElementType *Elements;
    Elements = (ElementType *)malloc(sizeof(ElementType) * Capacity);
    srand((unsigned)time(NULL));
    for (i = 0; i < Capacity; i++)
        Elements[i] = rand() % 90;
    return Elements;
}

void PrintElements(PriorityQueue H)
{
    int i;
    for (i = 1; i <= H->Size; i++)
        printf("%d ", H->Elements[i]);
    printf("\n");
}

void PrintArray(ElementType *Elements, int N)
{
    int i;
    for (i = 0; i < N; i++)
        printf("%d ", Elements[i]);
    printf("\n");
}

int main()
{
    ElementType *Elements;
    int Capacity, k, i;
    PriorityQueue H;

    Capacity = 16;
    k = 6;
    Elements = RandomIntArray(Capacity);
    PrintArray(Elements, Capacity);
    H = BuildHeap(Elements, k);
    PrintElements(H);
    for (i = k; i < Capacity; i++)
    {
        if (Elements[i] > H->Elements[1])
        {
            DeleteMin(H);
            Insert(Elements[i], H);
        }
    }
    PrintElements(H);
    system("pause");
    return 0;
}