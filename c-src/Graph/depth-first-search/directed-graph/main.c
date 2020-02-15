/**
 * 求图的 前向边（forward edge）后向边（back edge）交叉边（cross edge）
 * 目前只能求出前向边和后向边而且会出现混淆
 * 交叉边可能需要表示连通分量的并查集（不相交集）
 * 懒得弄了
 * 2020-2-15
 * 输入数据：
 *  顶点数 10
 *  边数 15
 *  邻接点（有向图）
1 2
1 4
2 3
2 6
3 1
3 4
3 5
4 5
6 3
7 6
7 8
8 6
8 10
9 8
10 9
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct VertexCell
{
    Arc first;
};

struct ArcCell
{
    //WeightType weight;
    VertexType adj;
    Arc next;
};

struct GraphCell
{
    Vertex ver;
    int arcnum;
    int vernum;
};

Graph CreateGraph(void)
{
    int i;
    Arc edge;
    VertexType v, w;
    Graph G;
    G = (Graph)malloc(sizeof(struct GraphCell));
    printf("Input vernum: ");
    scanf("%d", &G->vernum);
    G->ver = (Vertex)malloc(sizeof(struct VertexCell) * (G->vernum + 1));
    for (i = 0; i <= G->vernum; i++)
        G->ver[i].first = NULL;
    printf("Input vernum: ");
    scanf("%d", &G->arcnum);
    for (i = 0; i < G->arcnum; i++)
    {
        scanf("%d%d", &v, &w);
        edge = (Arc)malloc(sizeof(struct ArcCell));
        edge->adj = w;
        edge->next = G->ver[v].first;
        G->ver[v].first = edge;
    }
    return G;
}

void PrintGraph(Graph G)
{
    int i;
    Arc edge;
    for (i = 1; i <= G->vernum; i++)
    {
        printf("%d: ", i);
        edge = G->ver[i].first;
        while (edge != NULL)
        {
            printf("%d->", edge->adj);
            edge = edge->next;
        }
        printf("^\n");
    }
}
int visited[numver];
int num[numver];
int parent[numver];
int Count;
void DfsSpanningTree(Graph G, VertexType s)
{
    Arc edge;

    visited[s] = 1;
    num[s] = ++Count;
    edge = G->ver[s].first;
    while (edge != NULL)
    {

        if (visited[edge->adj] == 0)
        {
            printf("(%d, %d)\n", s, edge->adj);
            DfsSpanningTree(G, edge->adj);
            parent[edge->adj] = s;
        }
        else
        {
            /*if (num[s] > num[edge->adj])
                printf("(%d, %d) back edge\n", s, edge->adj);*/
/*if (num[s] < num[parent[edge->adj]])
                printf("(%d, %d) forward edge\n", s, edge->adj);*/

if (num[s] > num[edge->adj] && num[parent[s]] < edge->adj)
    printf("(%d, %d) back edge\n", s, edge->adj);
else
{
    if (num[s] < num[edge->adj] && num[s] < num[parent[edge->adj]])
        printf("(%d, %d) forward edge\n", s, edge->adj);
    else
        printf("(%d, %d) cross edge\n", s, edge->adj);
            }
        }
        edge = edge->next;
    }
}

int main()
{
    Graph G;
    G = CreateGraph();
    PrintGraph(G);
    DfsSpanningTree(G, 2);
    return 0;
}