#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

Stack CreateStack(int MaxElements)
{
    Stack S;
    if (MaxElements < MinStackSize)
        printf("%s\n", "Stack size is too small");
    S = (Stack)malloc(sizeof(struct StackRecord));
    if (S == NULL)
        printf("%s\n", "Out of space!!!");
    S->Array = (ElementType *)malloc(sizeof(ElementType) * MaxElements);
    if (S->Array == NULL)
        printf("%s\n", "Out of space!!!");
    S->Capacity = MaxElements;
    MakeEmpty(S);
    return S;
}

void DisposeStack(Stack S)
{
    if (S != NULL)
    {
        free(S->Array);
        free(S);
    }
}

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}

void Push(ElementType X, Stack S)
{
    if (IsFull(S))
        Error("Full stack");
    else
        S->Array[++S->TopOfStack] = X;
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack];
    Error("Empty stack");
    return 0; /* Return value used to avoid warning */
}

void Pop(Stack S)
{
    if (IsEmpty(S))
        Error("Empty stack");
    else
        S->TopOfStack--;
}

ElementType TopAndPop(Stack S)
{
    if (!IsEmpty(S))
        return S->Array[S->TopOfStack--];
    Error("Empty stack");
    return 0; /* Return value used to avoid warning */
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
    {
        printf("Stack use CreateStack first\n");
        return;
    }
    while (!IsEmpty(S))
    {
        Pop(S);
    }
}