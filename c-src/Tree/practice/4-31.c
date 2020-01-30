#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *Tree;
typedef struct TreeNode Position;
struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
};

Tree GenTree(int Height, int *LastNode)
{
    Tree T = NULL;

    if (Height >= 0)
    {
        T = malloc(sizeof(struct TreeNode));
        T->Left = GenTree(Height - 1, LastNode);
        T->Element = ++*LastNode;
        T->Right = GenTree(Height - 1, LastNode);
    }
    return T;
}

Tree PerfectTree(int H)
{
    int LastNodeAssigned = 0;
    return GenTree(H, &LastNodeAssigned);
}

void PrintElement(Tree T)
{
    if (T != NULL)
        printf("%d ", T->Element);
}

void PrintTree(Tree T)
{
    if (T != NULL)
    {
        PrintElement(T);
        PrintTree(T->Left);
        PrintTree(T->Right);
    }
}

int main()
{
    Tree T;
    T=PerfectTree(3);
    PrintTree(T);
    printf("\n");
    system("pause");
    return 0;
}