#include <stdio.h>
#include <stdlib.h>

#define NotAVertex (-1)
#define MVNum (10) // 最大顶点数
typedef int VertexType;
typedef int ArcType;

typedef struct ArcNode // 边结点
{
    VertexType adjvex;       // 该边所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
    ArcType weight;          // 边的权值
} * ArcNode;

typedef struct VNode // 顶点信息
{
    // VertexType data;
    ArcNode firstarc;    // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum]; // AdjList 表示邻接类型

typedef struct // 邻接表
{
    AdjList vertices;
    int vexnum, arcnum;  // 图的当前定点数和边数
    int Indegree[MVNum]; // 每个顶点的入度
} * ALGraph;

void CreateUDG(ALGraph G)
{
    int i, j;
    int v1, v2;
    ArcNode p1, p2;
    ArcType weight;

    printf("Input vexnum: ");
    scanf("%d", &G->vexnum);
    printf("Input arcnum: ");
    scanf("%d", &G->arcnum);

    // 输入各点，构造表头结点表
    for (i = 1; i <= G->vexnum; i++)
    {
        G->vertices[i].firstarc = NULL;
        G->Indegree[i] = 0;
    }

    // 输入一条边依附的两个顶点
    for (j = 0; j < G->arcnum; j++)
    {
        scanf("%d%d%d", &v1, &v2, &weight);
        p1 = (ArcNode)malloc(sizeof(*p1));
        if (p1 == NULL)
            exit(0);
        p1->adjvex = v2;
        p1->weight = weight;
        p1->nextarc = G->vertices[v1].firstarc;
        G->vertices[v1].firstarc = p1;
        G->Indegree[v2] += 1;
        /*p2 = (ArcNode)malloc(sizeof(struct ArcNode));
        p2->adjvex = i;
        p2->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = p2;
        G->Indegree[v1] += 1;*/
    }
}

ALGraph CreateGraph(void)
{
    ALGraph G;
    G = (ALGraph)malloc(sizeof(*G));
    if (G == NULL)
        exit(0);
    return G;
}

typedef VertexType ElementType;
typedef struct QueueNode *Queue;
struct QueueNode
{
    ElementType Array[MVNum];
    int Capacity;
    int Size;
    int Front;
    int Rear;
};
int IsFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}
int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

Queue CreateQueue(int Capacity)
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QueueNode));
    if (Q == NULL)
        exit(0);
    Q->Capacity = Capacity;
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
    return Q;
}

void Enqueue(ElementType X, Queue Q)
{
    if (IsFull(Q))
    {
        printf("The queue is full\n");
        system("pause");
        exit(0);
    }
    Q->Size++;
    if (++Q->Rear == Q->Capacity)
        Q->Rear = 0;
    Q->Array[Q->Rear] = X;
}

void Dequeue(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("The queue is empty\n");
        system("pause");
        exit(0);
    }
    Q->Size--;
    if (++Q->Front == Q->Capacity)
        Q->Front = 0;
}

ElementType Front(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("The queue is empty\n");
        system("pause");
        exit(0);
    }
    return Q->Array[Q->Front];
}

ElementType FrontAndDequeue(Queue Q)
{
    if (IsEmpty(Q))
    {
        printf("The queue is empty\n");
        system("pause");
        exit(0);
    }
    Q->Size--;
    return Q->Array[(Q->Front++) % Q->Capacity];
}

void DisposeQueue(Queue Q)
{
    free(Q);
}

void Topsort(ALGraph G)
{
    Queue Q;
    int Counter;
    VertexType V;
    ArcNode W;

    Q = CreateQueue(MVNum);
    Counter = 0;

    for (V = 1; V <= G->vexnum; V++)
        if (G->Indegree[V] == 0)
            Enqueue(V, Q);

    while (!IsEmpty(Q))
    {
        V = FrontAndDequeue(Q);
        printf("%d->", V);
        Counter++;

        W = G->vertices[V].firstarc;
        while (W != NULL)
        {
            if (--G->Indegree[W->adjvex] == 0)
                Enqueue(W->adjvex, Q);
            W = W->nextarc;
        }
    }
    printf("^\n");

    if (Counter != G->vexnum)
        printf("Graph has a cycle\n");

    DisposeQueue(Q);
}

int main()
{
    ALGraph G;
    G = CreateGraph();
    CreateUDG(G);
    Topsort(G);
    system("pause");
    return 0;
}