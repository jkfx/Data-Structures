#include <stdio.h>
#include <stdlib.h>
#include "Cursor.h"

#define SpaceSize 11

struct Node
{
    ElementType Element;
    Position Next;
};

struct Node CursorSpace[SpaceSize];

List MakeEmpty(List L)
{
    int i;
    CursorSpace[SpaceSize - 1].Next = 0;
    for (i = 0; i < SpaceSize - 1; i++)
        CursorSpace[i].Next = i + 1;
    return L;
}

Position CursorAlloc(void)
{
    Position P;
    P = CursorSpace[0].Next;
    CursorSpace[0].Next = CursorSpace[P].Next;
    return P;
}

void CursorFree(Position P)
{
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}

/* Return true if L is empty */
int IsEmpty(List L)
{
    return CursorSpace[L].Next == 0;
}

/* Return true if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast(Position P, List L)
{
    return CursorSpace[P].Next == 0;
}

/* Return Position of X in L; 0 if not found */
/* Uses a header node */
Position Find(ElementType X, List L)
{
    Position P;
    P = CursorSpace[L].Next;
    while (P && CursorSpace[P].Element != X)
        P = CursorSpace[P].Next;
    return P;
}

/* Delete first occurrence of X from a list */
/* Assume use of a header node */
void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if (!IsLast(P, L)) /* Assumeption of header use */
    {                  /* X is found; delete it */
        TmpCell = CursorSpace[P].Next;
        CursorSpace[P].Next = CursorSpace[TmpCell].Next;
        CursorFree(TmpCell);
    }
}

Position FindPrevious(ElementType X, const List L)
{
    Position P;
    P = CursorSpace[L].Next;
    while (P && CursorSpace[CursorSpace[P].Next].Element != X)
        P = CursorSpace[P].Next;
    return P;
}

/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */
void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = CursorAlloc();
    if (TmpCell == 0)
        printf("%s\n", "Out of space!!!");
    CursorSpace[TmpCell].Element = X;
    CursorSpace[TmpCell].Next = CursorSpace[P].Next;
    CursorSpace[P].Next = TmpCell;
}

int main()
{
    List L;
    Position P;
    L = MakeEmpty(L);
    P = CursorSpace[0].Next;
    Insert(11, L, P);
    Insert(22, L, P);
    system("pause");
}