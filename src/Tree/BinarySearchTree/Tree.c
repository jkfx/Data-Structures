#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T)
{
    if (T == NULL)
        return NULL;
    if (X < T->Element)
        return Find(X, T->Right);
    else if (X > T->Element)
        return Find(X, T->Left);
    else
        return T;
}

Position FindMin(SearchTree T)
{
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

Position FindMax(SearchTree T)
{
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}

SearchTree Insert(ElementType X, SearchTree T)
{
    if (T == NULL)
    {
        /* Create and return a one-node tree */
        T = (Position)malloc(sizeof(struct TreeNode));
        if (T == NULL)
            printf("Out of space!!!");
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    /* Else X is in the tree already; we'll do nothing */
    return T; /* Do not forget this line!!! */
}

SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;

    if (T == NULL)
        printf("Element not found");
    else if (X < T->Element) /* Go left */
        T->Left = Delete(X, T->Left);
    else if (X > T->Element) /* Go right */
        T->Right = Delete(X, T->Right);
    else                         /* Found element to be deleted */
        if (T->Left && T->Right) /* Two children */
    {
        /* Replace with smallest in right subtree */
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element, T->Right);
    }
    else /* One or zero children */
    {
        TmpCell = T;
        if (T->Left == NULL) /* Also handles 0 children */
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(TmpCell);
    }
    return T;
}

int main()
{
    SearchTree T;
    T = MakeEmpty(NULL);
    T = Insert(199, T);
    T = Insert(1, T);
    T = Insert(3, T);
    T = Insert(2, T);
    T = Insert(9, T);
    T = Insert(4, T);
    printf("%d\n", FindMax(T)->Element);
    printf("%d\n", FindMin(T)->Element);
    printf("%d\n", T->Element);
    printf("%d\n", (T->Right==NULL));
    system("pause");
    return 0;
}