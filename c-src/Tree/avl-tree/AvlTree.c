#include <stdio.h>
#include <stdlib.h>
#include "AvlTree.h"

struct AvlNode
{
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};
/**
 * 效率超过执行两个单旋转的双旋转函数
 * */
Position DoubleRotateWithLeftn(Position K3)
{
    Position K1, K2;

    K1 = K3->Left;
    K2 = K1->Right;

    K3->Left = K2;
    K1->Right = K2->Left;
    K2->Left = K1;
    K3->Left = K2->Right;
    K2->Right = K3;

    K1->Height = Max(Height(K1->Left), Height(K1->Right) + 1);
    K3->Height = Max(Height(K3->Left), Height(K3->Right) + 1);
    K2->Height = Max(Height(K2->Left), Height(K2->Right) + 1);

    return K2;
}

int Height(Position P)
{
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

AvlTree Insert(ElementType X, AvlTree T)
{
    if (T == NULL)
    {
        /* Create and return a one-node tree */
        T = (AvlTree)malloc(sizeof(struct AvlNode));
        T->Element = X;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Element)
    {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2)
            if (X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeftn(T);
    }
    else if (X > T->Element)
    {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2)
            if (X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
    }
    /* Else X is in the tree already; we'll do nothing */
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

/**
 * This function can be called only if K2 has a left child,
 * Perform a rotate between a node (K2) and its left child,
 * Update heights, then return new root.
 * */
Position SingleRotateWithLeft(Position K2)
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
    return K1; /* New root */
}

/**
 * This function can be called only if K3 has a left
 * child and K3's left child has a right child,
 * Do the left-right double rotation,
 * Update heights, then return new root.
 * */
Position DoubleRotateWithLeft(Position K3)
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight(K3->Left);

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft(K3);
}

Position SingleRotateWithRight(Position K2)
{
    Position K1;

    K1 = K2->Right;
    K2->Right = K1->Left;
    K1->Left = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;

    return K1;
}

Position DoubleRotateWithRight(Position K3)
{
    K3->Right = SingleRotateWithLeft(K3->Right);
    return SingleRotateWithRight(K3);
}

ElementType Max(ElementType E1, ElementType E2)
{
    if (E1 > E2)
        return E1;
    else
        return E2;
}

void InorderTraversal(AvlTree T)
{
    if (T != NULL)
    {
        InorderTraversal(T->Left);
        printf("%d ", T->Element);
        InorderTraversal(T->Right);
    }
}

void PreviousTraversal(AvlTree T)
{
    if (T != NULL)
    {
        printf("%d ", T->Element);
        PreviousTraversal(T->Left);
        PreviousTraversal(T->Right);
    }
}

void TailTraversal(AvlTree T)
{
    if (T != NULL)
    {
        TailTraversal(T->Left);
        TailTraversal(T->Right);
        printf("%d ", T->Element);
    }
}

int main()
{
    AvlTree T;
    T = NULL;

    T = Insert(10, T);
    T = Insert(7, T);
    T = Insert(9, T);
    T = Insert(2, T);
    T = Insert(5, T);
    T = Insert(6, T);
    T = Insert(3, T);
    T = Insert(1, T);
    T = Insert(4, T);

    printf("中序遍历: ");
    InorderTraversal(T);
    printf("\n");
    printf("前序遍历: ");
    PreviousTraversal(T);
    printf("\n");
    printf("后序遍历: ");
    TailTraversal(T);
    printf("\n");

    system("pause");
    return 0;
}