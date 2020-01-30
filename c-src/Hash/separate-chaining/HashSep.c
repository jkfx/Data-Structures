#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HashSep.h"

struct ListNode
{
    ElementType Element;
    Position Next;
};
typedef Position List;

int NextPrime(int n)
{
    int i;
    for (;; n++)
    {
        for (i = 2; i < (int)sqrt(n); i++)
            if (n % i == 0)
                break;
        if (i == (int)sqrt(n))
            return n;
    }
}

/**
 * List *TheList will be an array of lists, allocated later.
 * The lists use headers (for simplicity),
 * though this wastes space.
 * */
struct HashTbl
{
    int TableSize;
    List *TheLists;
};

HashTable InitializeTable(int TableSize)
{
    HashTable H;
    int i;

    /* Aallocate table */
    H = (HashTable)malloc(sizeof(struct HashTbl));
    if (H == NULL)
        exit(0);
    H->TableSize = NextPrime(TableSize);

    /* Allocate array of lists */
    H->TheLists = (List *)malloc(sizeof(struct ListNode) * H->TableSize);
    if (H->TheLists == NULL)
        exit(0);

    /* Allocate list headers */
    for (i = 0; i < H->TableSize; i++)
    {
        H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
        if (H->TheLists[i] == NULL)
            exit(0);
        else
            H->TheLists[i]->Next = NULL;
    }
    return H;
}

Index Hash(ElementType Key, int TableSize)
{
    unsigned int HashVal = 0;
    while (*Key != '\0')
        HashVal = (HashVal << 5) + *Key++;
    return HashVal % TableSize;
}

Position Find(ElementType Key, HashTable H)
{
    Position P;
    List L;

    L = H->TheLists[Hash(Key, H->TableSize)];
    P = L->Next;
    while (P != NULL && strcmp(P->Element, Key))
        P = P->Next;
    return P;
}

/**
 * 这个插入例程写得并不好，因为它计算了两次散列函数。
 * 多余的计算总是不好的。
 * 如果这些散列例程真的构成程序运行时间的重要成分，
 * 那么这个程序就应该重写。
 * */
void Insert(ElementType Key, HashTable H)
{
    Position Pos, NewCell;
    List L;

    Pos = Find(Key, H);
    if (Pos == NULL)
    {
        NewCell = (Position)malloc(sizeof(struct ListNode));
        if (NewCell == NULL)
            exit(0);
        else
        {
            L = H->TheLists[Hash(Key, H->TableSize)];
            NewCell->Next = L->Next;
            //strcpy(NewCell->Element, Key);
            NewCell->Element = Key;
            L->Next = NewCell;
        }
    }
}

int main()
{
    HashTable H;
    H = InitializeTable(20);
    Insert("jkfx", H);
    Insert("pause", H);
    Insert("a", H);
    printf("%s\n", Find("jkfx", H)->Element);
    system("pause");
    return 0;
}