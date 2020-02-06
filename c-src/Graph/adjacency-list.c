#include <stdio.h>
#include <stdlib.h>

#define MVNum (10) // 最大顶点数
typedef int VertexType;
typedef int ArcType;

typedef struct ArcNode // 边结点
{
    int adjvex;              // 该边所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
    ArcType weight;          // 边的权值
} * ArcNode;

typedef struct VNode // 顶点信息
{
    VertexType data;
    ArcNode firstarc;   // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum]; // AdjList 表示邻接类型

typedef struct // 邻接表
{
    AdjList vertices;
    int vexnum, arcnum; // 图的当前定点数和边数
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
        scanf("%d", &G->vertices[i].data);
        G->vertices[i].firstarc = NULL;
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
        /*p2 = (ArcNode)malloc(sizeof(struct ArcNode));
        p2->adjvex = i;
        p2->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = p2;*/
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

int main()
{
    ALGraph G;
    G = CreateGraph();
    CreateUDG(G);
    system("pause");
    return 0;
}