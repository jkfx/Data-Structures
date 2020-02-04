#include <stdio.h>
#include <stdlib.h>
#include "BinomialQueue.h"

#define Infinity (999999999)
#define MaxTrees (128)
#define Capacity MaxTrees

struct BinNode
{
    ElementType Elelemt;
    Position LeftChild;
    Position NextSibling;
};

struct Collection
{
    int CurrentSize;
    BinTree TheTrees[MaxTrees];
};

/* Return the result of merging equal-sized T1 and T2 */
BinTree CombineTrees(BinTree T1, BinTree T2)
{
    if (T1->Elelemt > T2->Elelemt)
        return CombineTrees(T2, T1);
    T2->NextSibling = T1->LeftChild;
    T1->LeftChild = T2;
    return T1;
}

/* Merge two binomial queues */
/* Not optimized for early termination */
/* H1 contains merged result */
BinQueue Merge(BinQueue H1, BinQueue H2)
{
    BinTree T1, T2, Carry;
    int i, j;
    Carry = NULL;
    if (H1->CurrentSize + H2->CurrentSize > Capacity)
        exit(0);
    if (H1 == H2)
        return H1;
    if (H1->CurrentSize < H2->CurrentSize)
        return Merge(H2, H1);
    H1->CurrentSize += H2->CurrentSize;
    for (i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2)
    {
        T1 = H1->TheTrees[i];
        T2 = H2->TheTrees[i];
        switch (!!T1 + 2 * !!T2 + 4 * !!Carry)
        {
        case 0: /* No trees */
        case 1: /* Only H1 */
            break;
        case 2: /* Only H2 */
            H1->TheTrees[i] = T2;
            H2->TheTrees[i] = NULL;
            break;
        case 3: /* H1 and H2 */
            Carry = CombineTrees(T1, T2);
            H1->TheTrees[i] = H2->TheTrees[i] = NULL;
            break;
        case 4: /* Only carry */
            H1->TheTrees[i] = Carry;
            Carry = NULL;
            break;
        case 5: /* H1 and Carry */
            Carry = CombineTrees(T1, Carry);
            H1->TheTrees[i] = NULL;
            break;
        case 6: /* H2 and Carry */
            Carry = CombineTrees(T2, Carry);
            H2->TheTrees[i] = NULL;
            break;
        case 7: /* All three */
            H1->TheTrees[i] = Carry;
            Carry = CombineTrees(T1, T2);
            H2->TheTrees[i] = NULL;
            break;
        }
    }
    return H1;
}

ElementType DeleteMin(BinQueue H)
{
    int i, j;
    int MinTree; /* The tree with the minimum itrm */
    BinQueue DeletedQueue;
    Position DeletedTree, OldRoot;
    ElementType MinItem;

    if (IsEmpty(H))
        exit(0);

    MinItem = Infinity;
    for (i = 0; i < MaxTrees; i++)
    {
        if (H->TheTrees[i] && H->TheTrees[i]->Elelemt < MinItem)
        {
            /* Update minimum */
            MinItem = H->TheTrees[i]->Elelemt;
            MinTree = i;
        }
    }

    DeletedTree = H->TheTrees[MinTree];
    OldRoot = DeletedTree;
    DeletedTree = DeletedTree->LeftChild;
    free(OldRoot);

    DeletedQueue = Initialize();
    DeletedQueue->CurrentSize = (1 << MinTree) - 1;
    for (j = MinTree - 1; j >= 0; j--)
    {
        DeletedQueue->TheTrees[j] = DeletedTree;
        DeletedTree = DeletedTree->NextSibling;
        DeletedQueue->TheTrees[j]->NextSibling = NULL;
    }

    H->TheTrees[MinTree] = NULL;
    H->CurrentSize -= DeletedQueue->CurrentSize + 1;

    Merge(H, DeletedQueue);
    return MinItem;
}

int IsEmpty(BinQueue H)
{
    return H->CurrentSize == 0;
}

BinQueue Initialize(void)
{
    int i;
    BinQueue H;
    H = (BinQueue)malloc(sizeof(struct Collection));
    if (H == NULL)
        exit(0);
    H->CurrentSize = 0;
    for (i = 0; i < MaxTrees; i++)
        H->TheTrees[i] = NULL;
    return H;
}

BinQueue Insert(ElementType X, BinQueue H)
{
    BinQueue NewQueue;
    BinTree NewTree;

    NewTree = (BinTree)malloc(sizeof(struct BinNode));
    if (NewTree == NULL)
        exit(0);
    NewTree->LeftChild = NewTree->NextSibling = NULL;
    NewTree->Elelemt = X;

    NewQueue = Initialize();
    NewQueue->CurrentSize = 1;
    NewQueue->TheTrees[0] = NewTree;

    return Merge(NewQueue, H);
}

int main()
{
    BinQueue bq;
    bq = Initialize();
    bq = Insert(23, bq);
    bq = Insert(51, bq);
    bq = Insert(24, bq);
    bq = Insert(65, bq);
    system("pause");
    return 0;
}