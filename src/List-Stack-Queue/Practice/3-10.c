#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);
struct Node
{
    ElementType Element;
    Position Next;
};

/* Return true if L is empty */
int IsEmpty(List L)
{
    return L->Next == NULL;
}

/* Return tyue if P is the last position in list L */
/* Parameter L is unused in this implementation */
int IsLast(Position P, List L)
{
    return P->Next == NULL;
}

/* Return Position of X in L; NULL if not found */
Position Find(ElementType X, List L)
{
    Position P;
    P = L->Next;
    while (P != NULL && P->Element != X)
    {
        P = P->Next;
    }
    return P;
}

/* Delete first occurrence of X from a list */
/* Assume use of a header node */
void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if (!IsLast(P, L))
    {                            /* Assumption of header use */
        TmpCell = P->Next;       /* X is found; delete it */
        P->Next = TmpCell->Next; /* Bypass deleted cell */
        free(TmpCell);
    }
}

/* If X is not found, then Next field of returned */
/* Position is NULL */
/* Assumes a header */
Position FindPrevious(ElementType X, List L)
{
    Position P;
    P = L;
    while (P->Next != NULL && P->Next->Element != X)
    {
        P = P->Next;
    }
    return P;
}

/* Insert (after legal position P) */
/* Header implementation assumed */
/* Parameter L is unuserd in this implementation */
void Insert(ElementType X, List L, Position P)
{
    Position TmpCell, Pre;

    TmpCell = malloc(sizeof(struct Node));
    if (TmpCell == NULL)
    {
        // FatalError("Out of space!!!");
        printf("Out of space!!!\n");
        return;
    }

    Pre = FindPrevious(P->Element, L);
    TmpCell->Next = P;
    Pre->Next = TmpCell;
    TmpCell->Element = X;

   /* TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;*/
}

/* Correct DeleteList algorithm */
void DeleteList(List L)
{
    Position P, Tmp;

    P = L->Next; /* Header assumed */
    L->Next = NULL;
    while (P != NULL)
    {
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}

List MakeEmpty(List L)
{
    if (L == NULL)
    {
        L = (Position)malloc(sizeof(struct Node));
        L->Next = NULL;
    }
    else
        L->Next = NULL;
    return L;
}

Position First(List L)
{
    if (L->Next == NULL)
    {
        L->Next = (Position)malloc(sizeof(struct Node));
        L->Next->Next = NULL;
    }
    return L->Next;
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

Position Next(Position Pos, List L)
{
    if (Pos->Next == NULL)
    {
        Pos->Next = (Position)malloc(sizeof(struct Node));
        Pos->Next->Next = NULL;
    }
    return Pos->Next;
}
/**
 * 未完成，与2020-1-21领取了驾驶证太皮筋
 * 有一些BUG等着后人去修改，First()和Next()的机制要统一起来
 * 这个问题还没开始解决，先把上面两个问题解决后再说吧
 * flag：等我一天自己完善这些链表的基本例程
 * */
void Josephus(int N, int M)
{
    int i;
    List L;
    Position LPos;
    L = MakeEmpty(NULL);
    LPos = First(L);
    for (i = 1; i <= N; i++)
    {
        Insert(i, L, LPos);
        LPos = Next(LPos, L);
    }
    LPos = First(L);
    for (i = 1; i <= N; i++)
    {
        if (i <= M)
        {
            i = 1;
            Delete(LPos->Element, L);
            continue;
        }
        LPos = Next(LPos, L);
        PrintList(L);
    }
}

int main(){
    Josephus(8,1);
    system("pause");
    return 0;
}