#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (16)
#define EmptyStack (-1)

typedef char ElementType;
struct Node
{
    ElementType *Array;
    int Capacity;
    int TopOfStack;
};
typedef struct Node *Stack;

Stack CreateStack()
{
    Stack S;
    S = (struct Node *)malloc(sizeof(struct Node));
    S->Array = (ElementType *)malloc(sizeof(ElementType) * MAX);
    S->Capacity = MAX;
    S->TopOfStack = EmptyStack;
}

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyStack;
}

int IsFull(Stack S)
{
    return S->TopOfStack + 1 == MAX;
}

void Push(ElementType X, Stack S)
{
    if (!IsFull(S))
        S->Array[++S->TopOfStack] = X;
    else
    {
        printf("Stack is full!\n");
        system("pause");
        exit(0);
    }
}

void Pop(Stack S)
{
    if (!IsEmpty(S))
        S->TopOfStack--;
    else
    {
        printf("Stack is empty!\n");
        system("pause");
        exit(0);
    }
}
ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack];
    else
        return EmptyStack;
}

ElementType TopAndPop(Stack S)
{
    return S->Array[S->TopOfStack--];
}

int main()
{
    Stack S;
    char *Str = "({[<>]}){}<>()";
    int i;
    S = CreateStack();
    for (i = 0; i < strlen(Str); i++)
    {
        switch (Str[i])
        {
        case '[':
            Push(Str[i], S);
            break;
        case '{':
            Push(Str[i], S);
            break;
        case '(':
            Push(Str[i], S);
            break;
        case '<':
            Push(Str[i], S);
            break;

        case ']':
            if (IsEmpty(S))
            {
                printf("Error: stack is empty!\n");
                system("pause");
                exit(0);
            }
            else if (TopAndPop(S) != '[')
            {
                printf("Error: symbol is not corresponding!\n");
                system("pause");
                exit(0);
            }
            break;
        case '}':
            if (IsEmpty(S))
            {
                printf("Error: stack is empty!\n");
                system("pause");
                exit(0);
            }
            else if (TopAndPop(S) != '{')
            {
                printf("Error: symbol is not corresponding!\n");
                system("pause");
                exit(0);
            }
            break;
        case ')':
            if (IsEmpty(S))
            {
                printf("Error: stack is empty!\n");
                system("pause");
                exit(0);
            }
            else if (TopAndPop(S) != '(')
            {
                printf("Error: symbol is not corresponding!\n");
                system("pause");
                exit(0);
            }
            break;
        case '>':
            if (IsEmpty(S))
            {
                printf("Error: stack is empty!\n");
                system("pause");
                exit(0);
            }
            else if (TopAndPop(S) != '<')
            {
                printf("Error: symbol is not corresponding!\n");
                system("pause");
                exit(0);
            }
            break;
        }
    }
    if (!IsEmpty(S))
    {
        printf("Error: Stack is not empty!\n");
        system("pause");
        exit(0);
    }
    printf("Symbol is correspnding!\n");
    system("pause");
    return 0;
}