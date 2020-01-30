#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElementType;

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);
int RandomInt();
void PrintElement(SearchTree T);
void PrintTree(SearchTree T);

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
        return Find(X, T->Left);
    else if (X > T->Right)
        return Find(X, T->Right);
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
        T = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        T->Element = X;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    /* Else X is in the tree already; we'll do nothing */
    return T; /* Do not forget this line */
}

SearchTree Delete(ElementType X, SearchTree T)
{
    Position TmpCell;

    if (T != NULL)
    {
        if (X < T->Element)
            T->Left = Delete(X, T->Left);
        else if (X > T->Element)
            T->Right = Delete(X, T->Right);
        else if (T->Left && T->Right)
        {
            TmpCell = FindMin(T->Right);
            T->Element = TmpCell->Element;
            T->Right = Delete(T->Element, T->Right);
        }
        else
        {
            TmpCell = T;
            if (T->Left == NULL)
                T = T->Right;
            else if (T->Right == NULL)
                T = T->Left;
            free(TmpCell);
        }
    }
    return T;
}

void PrintElement(SearchTree T)
{
    if (T != NULL)
        printf("%d ", T->Element);
}

void PrintTree(SearchTree T)
{
    if (T != NULL)
    {
        PrintTree(T->Left);
        PrintElement(T);
        PrintTree(T->Right);
    }
}

int RandomInt(int N)
{
    return rand() % N;
}

void PrintRange(SearchTree T, ElementType Lower, ElementType Upper)
{
    if (T != NULL)
    {
        if (T->Element >= Lower && T->Element <= Upper)
        {

            PrintRange(T->Left, Lower, Upper);
            PrintElement(T);
            PrintRange(T->Right, Lower, Upper);
        }
        else if (T->Element < Lower)
            PrintRange(T->Right, Lower, Upper);
        else if (T->Element > Upper)
            PrintRange(T->Left, Lower, Upper);
    }
}

int main()
{
    int i;
    SearchTree T;
    T = NULL;
    for (i = 0; i < 15; i++)
        T = Insert(RandomInt(100), T);
    PrintTree(T);
    printf("\n");
    PrintRange(T, 10, 70);
    printf("\n");
    system("pause");
    return 0;
}