#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

struct Node
{
    ElementType Element;
    PtrToNode Next;
};

/* 测试栈是否空栈例程————链表实现 */
int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

/* 创建一个空栈的例程————链表实现 */
Stack CreateStack(void)
{
    Stack S;

    S = (PtrToNode)malloc(sizeof(struct Node));
    if (S == NULL)
    {
        // FatalError("Out of space!!!");
        printf("Out of space!!!\n");
        return NULL;
    }
    S->Next = NULL;
    MakeEmpty(S);
    return S;
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
    {
        // Error( "Must use CreateStack first" );
        printf("Must use CreateStack first");
        return;
    }
    else
    {
        while (!IsEmpty(S))
        {
            Pop(S);
        }
    }
}

/* Push进栈的例程————链表实现 */
void Push(ElementType X, Stack S)
{
    PtrToNode TmpCell;

    TmpCell = (PtrToNode)malloc(sizeof(struct Node));
    if (TmpCell == NULL)
    {
        // FatalError( "Out of space!!!" );
        printf("Out of space!!!\n");
        return;
    }
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
}

/* 返回栈顶元素的例程————链表实现 */
ElementType Top(Stack S)
{
    if (!IsEmpty(S))
    {
        return S->Next->Element;
    }
    // Error( "Empty stack" );
    return 0; /* Return value used to avoid warning */
}

/* 从栈弹出元素的例程————链表实现 */
void Pop(Stack S)
{
    PtrToNode FirstCell;

    if (IsEmpty(S))
    {
        // Error( "Empty stack");
        printf("Empty stack");
        return;
    }
    else
    {
        FirstCell = S->Next;
        S->Next = S->Next->Next;
        free(FirstCell);
    }
}

int main()
{
    Stack S = CreateStack();
    Push(11, S);
    Push(22, S);
    ElementType element = Top(S);
    printf("%d\n", element);
    system("pause");
    return 0;
}
