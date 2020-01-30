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

int IsNumber(char ch)
{
    return ch >= '0' && ch <= '9';
}

int IsOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
}

ElementType TransformNumber(char ch)
{
    return ch - '0';
}

int Priority(char ch1, char ch2)
{
    int Pr1, Pr2;
    switch (ch1)
    {
    case '+':
        Pr1 = 1;
        break;
    case '-':
        Pr1 = 1;
        break;
    case '*':
        Pr1 = 2;
        break;
    case '/':
        Pr1 = 2;
        break;
    case '(':
        Pr1 = 3;
        break;
    case ')':
        Pr1 = 3;
        break;
    }
    switch (ch2)
    {
    case '+':
        Pr2 = 1;
        break;
    case '-':
        Pr2 = 1;
        break;
    case '*':
        Pr2 = 2;
        break;
    case '/':
        Pr2 = 2;
        break;
    case '(':
        Pr2 = 3;
        break;
    case ')':
        Pr2 = 3;
        break;
    }
    return Pr1 <= Pr2;
}

int main()
{
    char *Str = "a+b*c+(d*e+f)*g";
    Stack S;
    int i;
    S = CreateStack();
    for (i = 0; i < strlen(Str); i++)
    {
        if (!IsOperator(Str[i])) /* 运算数直接输出 */
            printf("%c", Str[i]);
        else if (Str[i] == ')') /* 右括号直接弹出栈直到碰到左括号 */
        {
            while (Top(S) != '(')
                printf("%c", TopAndPop(S));
            Pop(S);
        }
        else if (IsEmpty(S))
        {
            Push(Str[i], S);
        }
        else
        {
            while (Top(S) != '(' && Priority(Str[i], Top(S)) && !IsEmpty(S))
                printf("%c", TopAndPop(S));
            Push(Str[i], S);
        }
    }
    if (!IsEmpty(S))
        while (!IsEmpty(S))
            printf("%c", TopAndPop(S));
    printf("\n");
    system("pause");
    return 0;
}