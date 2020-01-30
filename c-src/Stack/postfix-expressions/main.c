#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (16)
#define EmptyStack (-1)

typedef int ElementType;
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

int IsNumber(char ch)
{
    return ch >= '0' && ch <= '9';
}

ElementType TransformNumber(char ch)
{
    return ch - '0';
}

/* 假设计算的后缀表达式的运算数都不大于10 */
int main()
{
    char *Str = "6523+8*+3+*";
    int num1, num2;
    int i;
    Stack S;
    S = CreateStack();
    for (i = 0; i < strlen(Str); i++)
    {
        if (IsNumber(Str[i]))
            Push(TransformNumber(Str[i]), S);
        else
        {
            switch (Str[i])
            {
            case '+':
                Push(TopAndPop(S) + TopAndPop(S), S);
                break;
            case '-':
                Push(TopAndPop(S) - TopAndPop(S), S);
                break;
            case '*':
                Push(TopAndPop(S) * TopAndPop(S), S);
                break;
            case '/':
                Push(TopAndPop(S) / TopAndPop(S), S);
                break;
            default:
                printf("Error: It is not operator!\n");
                system("pause");
                exit(0);
            }
        }
    }
    printf("%d\n", TopAndPop(S));
    system("pause");
    return 0;
}