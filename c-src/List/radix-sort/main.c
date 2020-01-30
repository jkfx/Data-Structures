#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define OF 9999

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

struct Node
{
    ElementType Element;
    PtrToNode Next;
};

List CreateList();
void InitListArray(List *Radix);
void Insert(ElementType X, List L);
void EmptyList(List L);
void EmptyRadix(List *Radix);
void PrintList(List L);
void PrintRadix(List *Radix);
void Sort(ElementType *Array, List *Radix);
ElementType Pop(List L);
int PopAll(int i, ElementType *Array, List L);
void PrintArray(ElementType *Array);

/* 假设需要排序的数范围在0到999之间 */
int main()
{
    int i, of;
    ElementType Array[MAX] = {64, 8, 216, 512, 27, 729, 0, 1, 343, 125};
    List Radix[MAX];
    InitListArray(Radix);
    of = 1;
    while (of < OF)
    {
        for (i = 0; i < MAX; i++)
            Insert(Array[i], Radix[(Array[i] / of) % 10]);
        printf("第%d趟排序:\n", of);
        PrintRadix(Radix);
        Sort(Array, Radix);
        PrintArray(Array);
        of *= 10;
    }
    system("pause");
    return 0;
}

List CreateList()
{
    List L;
    L = (PtrToNode)malloc(sizeof(struct Node));
    L->Element = -1;
    L->Next = NULL;
    return L;
}

void InitListArray(List *Radix)
{
    int i;
    for (i = 0; i < MAX; i++)
        Radix[i] = CreateList();
}

void Insert(ElementType X, List L)
{
    Position Pos;
    Pos = L;
    while (Pos->Next != NULL)
        Pos = Pos->Next;
    Pos->Next = CreateList();
    Pos->Next->Element = X;
    Pos->Next->Next = NULL;
}

void PrintList(List L)
{
    Position Pos;
    Pos = L->Next;
    while (Pos != NULL)
    {
        printf("%d ", Pos->Element);
        Pos = Pos->Next;
    }
    printf("\n");
}

void PrintRadix(List *Radix)
{
    int i;
    for (i = 0; i < MAX; i++)
        PrintList(Radix[i]);
}

void EmptyList(List L)
{
    Position Pos, TmpCell;
    Pos = L->Next;
    L->Next = NULL;
    while (Pos != NULL)
    {
        TmpCell = Pos->Next;
        free(Pos);
        Pos = TmpCell;
    }
}

void EmptyRadix(List *Radix)
{
    int i;
    for (i = 0; i < MAX; i++)
        EmptyList(Radix[i]);
}

void Sort(ElementType *Array, List *Radix)
{
    int i, j;
    j = 0;
    for (i = 0; i < MAX; i++)
        j = PopAll(j, Array, Radix[i]);
}

ElementType Pop(List L)
{
    Position Pos;
    ElementType Element;
    if (L->Next == NULL)
        return;
    Pos = L->Next;
    return Pos->Element;
}

int PopAll(int i, ElementType *Array, List L)
{
    Position Pos, TmpCell;
    ElementType Element;
    Pos = L->Next;
    while (Pos)
    {
        Array[i++] = Pop(L);
        TmpCell = Pos->Next;
        L->Next = TmpCell;
        free(Pos);
        Pos = TmpCell;
    }
    return i;
}

void PrintArray(ElementType *Array)
{
    int i;
    for (i = 0; i < MAX; i++)
        printf("%d ", Array[i]);
    printf("\n");
}