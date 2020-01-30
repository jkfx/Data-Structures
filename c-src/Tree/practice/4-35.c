#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX (64)

typedef int ElementType;
typedef struct TreeNode *Tree;
typedef struct TreeNode *Position;
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

ElementType RandomElement(int N)
{
    return rand() % N;
}

typedef struct QueueNode *Queue;
struct QueueNode
{
    Tree *Array;
    int Left;
    int Right;
    int Capacity;
    int Size;
};

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

int IsFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

Queue CreateQueue()
{
    Queue Q;
    Q = malloc(sizeof(struct QueueNode));
    Q->Array = malloc(sizeof(ElementType) * MAX);
    Q->Size = 0;
    Q->Capacity = MAX;
    Q->Left = 1;
    Q->Right = 0;
    return Q;
}

void Enqueue(Tree X, Queue Q)
{
    if (!IsFull(Q))
    {
        Q->Size++;
        if (++Q->Right == Q->Capacity)
            Q->Right = 0;
        Q->Array[Q->Right] = X;
    }
    else
    {
        printf("Queue is full!\n");
        system("pause");
        exit(0);
    }
}

Tree Front(Queue Q)
{
    if (!IsEmpty(Q))
        return Q->Array[Q->Left];
    else
    {
        printf("Queue is empty!\n");
        system("pause");
        exit(0);
    }
}

void Dequeue(Queue Q)
{
    if (!IsEmpty(Q))
    {
        Q->Size--;
        if (++Q->Left == Q->Capacity)
            Q->Left = 0;
    }
    else
    {
        printf("Queue is empty!\n");
        system("pause");
        exit(0);
    }
}

Tree FrontAndDequeue(Queue Q)
{
    if (!IsEmpty(Q))
    {
        Q->Size--;
        if (Q->Left == Q->Capacity)
            Q->Left = 0;
        return Q->Array[Q->Left++];
    }
    else
    {
        printf("Queue is empty!\n");
        system("pause");
        exit(0);
    }
}

void PrintLevel(Tree T)
{
    Queue Q;
    Q = CreateQueue();
    Enqueue(T, Q);
    while (!IsEmpty(Q))
    {
        T = FrontAndDequeue(Q);
        PrintElement(T);
        if (T->Left != NULL)
            Enqueue(T->Left, Q);
        if (T->Right != NULL)
            Enqueue(T->Right, Q);
    }
}

int main()
{
    Tree T;
    int i;
    T = NULL;
    for (i = 0; i < 5; i++)
        T = Insert(RandomElement(50), T);
    PrintTree(T);
    printf("\n");
    PrintLevel(T);
    system("pause");
    return 0;
}