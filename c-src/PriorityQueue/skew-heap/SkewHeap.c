#include <stdio.h>
#include <stdlib.h>
#include "SkewHeap.h"

struct TreeNode
{
    ElementType Element;
    PriorityQueue Left;
    PriorityQueue Right;
};

int IsEmpty(PriorityQueue H)
{
    return H == NULL;
}

PriorityQueue Initialize(void)
{
    return NULL;
}

void SwapChildren(PriorityQueue H)
{
    PriorityQueue TmpCell;

    TmpCell = H->Left;
    H->Left = H->Right;
    H->Right = TmpCell;
}

PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
    if (H1 == NULL)
        return H2;
    if (H2 == NULL)
        return H1;
    if (H1->Element < H2->Element)
        return Merge1(H1, H2);
    else
        return Merge1(H2, H1);
}

PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
    if (H1->Left == NULL)
        H1->Left = H2;
    else
    {
        H1->Right = Merge(H1->Right, H2);
        SwapChildren(H1);
    }
    return H1;
}

PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
    PriorityQueue NewNode;
    NewNode = (PriorityQueue)malloc(sizeof(struct TreeNode));
    NewNode->Element = X;
    NewNode->Left = NewNode->Right = NULL;
    return Merge(NewNode, H);
}

PriorityQueue DeleteMin(PriorityQueue H)
{
    PriorityQueue Left, Right;
    if (IsEmpty(H))
        return NULL;
    Left = H->Left;
    Right = H->Right;
    free(H);
    return Merge(Left, Right);
}

void OrderTraversal(PriorityQueue H)
{
    if (H != NULL)
    {
        OrderTraversal(H->Left);
        printf("%d  ", H->Element);
        OrderTraversal(H->Right);
    }
}

int main()
{
    PriorityQueue H1, H2, H3;

    H1 = Initialize();
    Insert(3, H1);
    Insert(10, H1);
    Insert(8, H1);
    Insert(21, H1);
    Insert(14, H1);
    Insert(17, H1);
    Insert(23, H1);
    Insert(26, H1);
    OrderTraversal(H1);
    printf("\n");

    H2 = Initialize();
    Insert(6, H2);
    Insert(12, H2);
    Insert(7, H2);
    Insert(18, H2);
    Insert(24, H2);
    Insert(37, H2);
    Insert(18, H2);
    Insert(33, H2);
    OrderTraversal(H2);
    printf("\n");

    H3 = Merge(H1, H2);
    OrderTraversal(H3);
    printf("\n");

    system("pause");
    return 0;
}