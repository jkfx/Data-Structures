#include <stdio.h>
#include <stdlib.h>
#include "LeftHeap.h"

struct TreeNode
{
    ElementType Element;
    PriorityQueue Left;
    PriorityQueue Right;
    int Npl;
};

PriorityQueue Initialize(void)
{
    return NULL;
}

int IsEmpty(PriorityQueue H)
{
    return H == NULL;
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
    if (H1->Left == NULL) /* Single node */
        H1->Left = H2;    /* H1->Right is already NULL,
                            H1->Npl is already 0 */
    else
    {
        H1->Right = Merge(H1->Right, H2);
        if (H1->Left->Npl < H1->Right->Npl)
            SwapChildren(H1);
        H1->Npl = H1->Right->Npl + 1;
    }
    return H1;
}

void SwapChildren(PriorityQueue H)
{
    PriorityQueue TmpCell;
    TmpCell = H->Left;
    H->Left = H->Right;
    H->Right = TmpCell;
}

PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
    PriorityQueue SingleNode;

    SingleNode = (PriorityQueue)malloc(sizeof(struct TreeNode));
    if (SingleNode == NULL)
        exit(0);
    else
    {
        SingleNode->Element = X;
        SingleNode->Npl = 0;
        SingleNode->Left = SingleNode->Right = NULL;
        H = Merge(SingleNode, H);
    }
    return H;
}

/* DeleteMin1 returns the new tree; */
/* To get the minmum, use FindMin */
/* This is for convenience */
PriorityQueue DeleteMin1(PriorityQueue H)
{
    PriorityQueue LeftHeap, RightHeap;

    if (IsEmpty(H))
        exit(0);
    LeftHeap = H->Left;
    RightHeap = H->Right;
    free(H);
    return Merge(LeftHeap, RightHeap);
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
    Insert(17, H1);
    Insert(26, H1);
    Insert(21, H1);
    Insert(14, H1);
    Insert(23, H1);
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