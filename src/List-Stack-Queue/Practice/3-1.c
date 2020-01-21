#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int Element;
    struct Node *Next;
};

typedef struct Node *Position;

typedef Position List;

Position CreateList()
{
    List L = (Position)malloc(sizeof(struct Node));
    L->Next = NULL;
    return L;
}

int IsEmpty(List L)
{
    return L->Next == NULL;
}

void MakeEmpty(List L)
{
    Position P, TmpCell;
    if (!IsEmpty(L))
    {
        P = L->Next;
        L->Next = NULL;
        while (P)
        {
            TmpCell = P->Next;
            free(P);
            P = TmpCell;
        }
    }
}

Position FindPrevious(List L, Position P)
{
    if (L->Next == NULL || L->Next == P)
    {
        return L;
    }
    Position T = L->Next;
    while (T && T->Next != P)
    {
        T = T->Next;
    }
    return T;
}

void Insert(int X, Position P, List L)
{
    Position PP = (Position)malloc(sizeof(struct Node));
    Position Pre;
    PP->Element = X;
    PP->Next = P;
    Pre = FindPrevious(L, P);
    Pre->Next = PP;
}

void PrintList(List L)
{
    Position P;
    if (!IsEmpty(L))
    {
        P = L->Next;
        while (P)
        {
            printf("%d\t", P->Element);
            P = P->Next;
        }
        printf("\n");
    }
}

int main()
{
    List L = CreateList();
    Insert(55, L->Next, L);
    Insert(44, L->Next, L);
    Insert(33, L->Next, L);
    Insert(22, L->Next, L);
    Insert(11, L->Next, L);
    Insert(00, L->Next, L);
    PrintList(L);
    system("pause");
    return 0;
}