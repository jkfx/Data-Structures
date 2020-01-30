#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Tree;
typedef struct TreeNode *Position;
struct TreeNode
{
    ElementType Element;
    Tree Son;
    Tree Bro;
};

Position Insert(ElementType X, Tree T)
{
    if (T == NULL)
    {
        T = malloc(sizeof(struct TreeNode));
        T->Element = X;
        T->Son = T->Bro = NULL;
    }
    else if (X > T->Element)
        T->Bro = Insert(X, T->Bro);
    else if (X < T->Element)
        T->Son = Insert(X, T->Son);
    return T;
}

void PrintElement(Tree T)
{
    printf("%d ", T->Element);
}

void PrintTree(Tree T)
{
    if (T != NULL)
    {
        PrintElement(T);
        PrintTree(T->Son);
        PrintTree(T->Bro);
    }
}

int main()
{
    Tree T;
    int i;
    T = NULL;
    srand((unsigned)time(NULL));
    for (i = 0; i < 4; i++)
        T = Insert(rand(), T);
    PrintTree(T);
    system("pause");
    return 0;
}