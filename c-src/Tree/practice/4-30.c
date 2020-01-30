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
    Tree T;

    if (Height >= 0)
    {
        T = malloc(sizeof(struct TreeNode));
        if (T != NULL)
        {
            T->Left = GenTree(Height - 1, LastNode);
            T->Element = ++*LastNode;
            T->Right = GenTree(Height - 2, LastNode);
            return T;
        }
        else
            return NULL;
    }
    else
        return NULL;
}

Tree MinAvlTree(int H)
{
    int LastNodeAssigned;

    LastNodeAssigned = 0;
    return GenTree(H, &LastNodeAssigned);
}

int Avl(int Height)
{
    if (Height == 0)
        return 1;
    else if (Height == 1)
        return 2;
    else
        return Avl(Height - 1) + Avl(Height - 2) + 1;
}

int main()
{
    Tree T;
    int Avl_node;

    T = MinAvlTree(9);
    Avl_node = Avl(9);
    printf("%d\n", T->Element);
    printf("%d\n", Avl_node);
    system("pause");
    return 0;
}