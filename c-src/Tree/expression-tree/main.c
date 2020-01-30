#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (32)
#define EMPTY (-1)

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
};

typedef struct StackNode *Stack;
struct StackNode
{
    Tree *Array;
    int Capacity;
    int TopOfStack;
};

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct StackNode));
    S->Array = (Tree *)malloc(sizeof(struct TreeNode) * MAX);
    S->Capacity = MAX;
    S->TopOfStack = EMPTY;
    return S;
}

int IsOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
Tree CreateTree(ElementType X)
{
    Tree T;
    T = (Tree)malloc(sizeof(struct TreeNode));
    T->Element = X;
    T->Left = NULL;
    T->Right = NULL;
    return T;
}

void Push(Tree T, Stack S)
{
    S->Array[++S->TopOfStack] = T;
}

Tree TopAndPop(Stack S)
{
    return S->Array[S->TopOfStack--];
}

void InorderTraversal(Tree T)
{
    if (T != NULL)
    {
        InorderTraversal(T->Left);
        printf("%c", T->Element);
        InorderTraversal(T->Right);
    }
}

void PostorderTraversal(Tree T)
{
    if (T != NULL)
    {
        PostorderTraversal(T->Left);
        PostorderTraversal(T->Right);
        printf("%c", T->Element);       
    }
}

void PreorderTraversal(Tree T)
{
    if (T != NULL)
    {
        printf("%c", T->Element);
        PreorderTraversal(T->Left);
        PreorderTraversal(T->Right);
    }
}

Tree Top(Stack S)
{
    return S->Array[S->TopOfStack];
}

/* 构造一棵后缀表达式树 */
int main()
{
    int i;
    Tree Cell;
    Stack S;
    char *str = "abc*+de*f+g*+";
    S = CreateStack();
    for (i = 0; i < strlen(str); i++)
    {
        if (!IsOperator(str[i]))
        {
            Cell = CreateTree(str[i]);
            Push(Cell, S);
        }
        else
        {
            Cell = CreateTree(str[i]);
            Cell->Right = TopAndPop(S);
            Cell->Left = TopAndPop(S);
            Push(Cell, S);
        }
    }
    InorderTraversal(Top(S));
    printf("\n");
    PostorderTraversal(Top(S));
    printf("\n");
    PreorderTraversal(Top(S));
    printf("\n");
    system("pause");
    return 0;
}