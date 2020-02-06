#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"

struct VertexNode
{
    VertexType VertexName;
    WeightType Weight;
    Vertex Next;
};

struct GraphNode
{
    Vertex Array; // 顶点数组
    int VerNum;   // 顶点数
    int ArcNum;   // 边数
};

struct TableNode
{
    VertexType VertexName;
    int Known;
    DistType Dist;
    VertexType Path;
};

struct QueueNode
{
    ElementType *Array;
    int Capacity;
    int Size;
    int Front;
    int Rear;
};

Queue CreateQueue(int Capacity)
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QueueNode));
    if (Q == NULL)
        exit(0);
    Q->Array = (ElementType *)malloc(sizeof(ElementType) * Capacity);
    Q->Size = 0;
    Q->Capacity = Capacity;
    Q->Front = 0;
    Q->Rear = 0;
    return Q;
}

int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

int IsFull(Queue Q)
{
    return Q->Capacity == Q->Size;
}

void Enqueue(ElementType X, Queue Q)
{
    if (IsFull(Q))
        exit(0);
    Q->Size++;
    Q->Array[(Q->Rear++) % Q->Capacity] = X;
}

ElementType FrontAndDequeue(Queue Q)
{
    if (IsEmpty(Q))
        exit(0);
    Q->Size--;
    return Q->Array[Q->Front++ % Q->Capacity];
}

void DisposeQueue(Queue Q)
{
    free(Q->Array);
    free(Q);
}

Table InitTable(VertexType Start, Graph G)
{
    Table T;
    int i;

    T = (Table)malloc(sizeof(struct TableNode) * (G->VerNum + 1));
    if (T == NULL)
        exit(0);
    for (i = 1; i <= G->VerNum; i++)
    {
        T[i].VertexName = i;
        T[i].Known = 0;
        T[i].Dist = Infinity;
        T[i].Path = NotAVertex;
    }
    T[Start].Dist = 0;
    return T;
}

Graph CreateGraph(void)
{
    Graph G;
    int i;
    VertexType V1, V2;
    WeightType Weight;
    Vertex TmpCell;

    G = (Graph)malloc(sizeof(struct GraphNode));
    if (G == NULL)
        exit(0);
    printf("Input VerNum: ");
    scanf("%d", &G->VerNum);
    G->Array = (Vertex)malloc(sizeof(struct VertexNode) * (G->VerNum + 1));
    if (G->Array == NULL)
        exit(0);
    for (i = 1; i <= G->VerNum; i++)
    {
        G->Array[i].VertexName = i;
        G->Array[i].Next = NULL;
        G->Array[i].Weight = 0;
    }
    printf("Input ArcNum: ");
    scanf("%d", &G->ArcNum);

    for (i = 1; i <= G->ArcNum; i++)
    {
        scanf("%d%d%d", &V1, &V2, &Weight);
        TmpCell = (Vertex)malloc(sizeof(struct VertexNode));
        if (TmpCell == NULL)
            exit(0);
        TmpCell->Next = G->Array[V1].Next;
        TmpCell->VertexName = V2;
        TmpCell->Weight = Weight;
        G->Array[V1].Next = TmpCell;
    }

    return G;
}

void Unweighted1(Table T, Graph G)
{
    DistType CurrDist;
    VertexType V;
    Vertex W;

    for (CurrDist = 0; CurrDist < G->VerNum; CurrDist++)
        for (V = 1; V <= G->VerNum; V++)
            if (!T[V].Known && T[V].Dist == CurrDist)
            {
                T[V].Known = 1;
                W = G->Array[V].Next;
                while (W != NULL)
                {
                    if (T[W->VertexName].Dist == Infinity)
                    {
                        T[W->VertexName].Dist = CurrDist + 1;
                        T[W->VertexName].Path = V;
                    }
                    W = W->Next;
                }
            }
}

void Unweighted2(Table T, Graph G, VertexType Start)
{
    Queue Q;
    VertexType V;
    Vertex W;

    Q = CreateQueue(G->VerNum);
    Enqueue(Start, Q);

    while (!IsEmpty(Q))
    {
        V = FrontAndDequeue(Q);
        T[V].Known = 1;

        W = G->Array[V].Next;
        while (W != NULL)
        {
            if (T[W->VertexName].Dist == Infinity)
            {
                T[W->VertexName].Dist = T[V].Dist + 1;
                T[W->VertexName].Path = V;
                Enqueue(W->VertexName, Q);
            }
            W = W->Next;
        }
    }
    DisposeQueue(Q);
}

VertexType FindSmallestUnknownDistanceVertex(Table T, Graph G)
{
    VertexType i, Smallest;
    Smallest = NotAVertex;
    for (i = 1; i <= G->VerNum; i++)
        if (T[i].Known == 0)
        {
            Smallest = i;
            break;
        }
    for (i = 1; i <= G->VerNum; i++)
    {
        if (T[i].Known == 0 && T[Smallest].Dist > T[i].Dist)
            Smallest = i;
    }
    return Smallest;
}

void Dijkstra(Table T, Graph G)
{
    VertexType V;
    Vertex W;

    for (;;)
    {
        V = FindSmallestUnknownDistanceVertex(T, G);
        if (V == NotAVertex)
            break;
        T[V].Known = 1;
        W = G->Array[V].Next;
        while (W != NULL)
        {
            if (!T[W->VertexName].Known)
                if (T[V].Dist + W->Weight < T[W->VertexName].Dist)
                {
                    T[W->VertexName].Dist = T[V].Dist + W->Weight;
                    T[W->VertexName].Path = V;
                }
            W = W->Next;
        }
    }
}

void NegativeEdge(Table T, Graph G, VertexType Start)
{
    Queue Q;
    VertexType V;
    Vertex W;

    Q = CreateQueue(G->VerNum);
    Enqueue(Start, Q);

    while (!IsEmpty(Q))
    {
        V = DequeueQ(Q);
        W = G->Array[V].Next;
        while (W != NULL)
            if (T[V].Dist + W->Weight < T[W->VertexName].Dist)
            {
                T[W->VertexName].Dist = T[V].Dist + W->Weight;
                T[W->VertexName].Path = V;
                if (!IsInQueue(W, Q))
                    Enqueue(W, Q);
            }
    }
    DisposeQueue(Q);
}

void PrintPath(VertexType V, Table T)
{
    if (T[V].Path != NotAVertex)
    {
        PrintPath(T[V].Path, T);
        printf("->");
    }
    printf("%d", V);
}

int main()
{
    Graph G;
    Table T1, T2, T3;

    G = CreateGraph();

    T1 = InitTable(3, G);
    Unweighted1(T1, G);
    PrintPath(5, T1);
    printf("\n");

    T2 = InitTable(3, G);
    Unweighted2(T2, G, 3);
    PrintPath(7, T2);
    printf("\n");

    T3 = InitTable(1, G);
    Dijkstra(T3, G);
    PrintPath(6, T3);
    printf("\n");

    system("pause");
    return 0;
}