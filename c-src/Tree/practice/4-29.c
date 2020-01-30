#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N (500)

typedef int ElementType;

int Array[N+1] = {0};

typedef struct TreeNode *Position;
typedef struct TreeNode *Tree;
struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
};

Tree CreateTree(ElementType X)
{
    Tree T;
    T = malloc(sizeof(struct TreeNode));
    T->Element = X;
    T->Left = T->Right = NULL;
    return T;
}

Position Insert(ElementType X, Tree T)
{
    if (T == NULL)
        T = CreateTree(X);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    return T;
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
        PrintTree(T->Left);
        PrintElement(T);
        PrintTree(T->Right);
    }
}

int RandomInt(int Lower, int Upper)
{
    int RandomValue;
    RandomValue = rand() % Upper + Lower;
    printf("%d\n",RandomValue);
     return RandomValue;
}

Tree MakeRandomTree(int Lower, int Upper)
{
    int i, RandomVal;
    Tree T;
    T = NULL;
    srand((unsigned)time(NULL));
    for (i = 0; i < N; i++)
    {
        RandomVal = RandomInt(Lower, Upper);
        if (Array[RandomVal] != 0)
        {
            i--;
            continue;
        }
        T = Insert(RandomVal, T);
        Array[RandomVal] = 1;
    }
    return T;
}

Tree MakeRandomTree1(int Lower, int Upper)
{
    Tree T;
    int RandomValue;
    T = NULL;
    if (Lower <= Upper)
    {
        T = malloc(sizeof(struct TreeNode));
        if (T != NULL)
        {
            T->Element = RandomValue = RandomInt(Lower, Upper);
            T->Left = MakeRandomTree1(Lower, RandomValue - 1);
            T->Right = MakeRandomTree1(RandomValue + 1, Upper);
        }
        else
            printf("NULL\n");
    }
    return T;
}

void DeleteTree(Tree T)
{
    if(T!=NULL)
    {
        DeleteTree(T->Left);
        DeleteTree(T->Right);
        free(T);
    }
}

int main()
{
    Tree T;
    T = NULL;
    T = MakeRandomTree(1, N);
    PrintTree(T);
    printf("\n");
    DeleteTree(T);
    system("pause");
    return 0;
}