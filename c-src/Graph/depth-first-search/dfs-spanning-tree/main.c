#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct VertexCell
{
    VertexType data;
    Arc first;
};

struct ArcCell
{
    //WeightType weight;
    VertexType adjver;
    Arc next;
};

struct GraphCell
{
    Vertex ver;
    int vernum;
    int arcnum;
};

Graph CreateGraph(void)
{
    int i;
    Graph G;
    VertexType v, w;
    Arc edge;

    G = (Graph)malloc(sizeof(struct GraphCell));

    printf("Input vernum: ");
    scanf("%d", &G->vernum);
    G->ver = (Vertex)malloc(sizeof(struct VertexCell) * (G->vernum + 1));
    for (i = 0; i <= G->vernum; i++)
    {
        G->ver[i].data = i;
        G->ver[i].first = NULL;
    }

    printf("Input arcnum: ");
    scanf("%d", &G->arcnum);

    for (i = 1; i <= G->arcnum; i++)
    {
        scanf("%d%d", &v, &w);
        edge = (Arc)malloc(sizeof(struct ArcCell));
        edge->adjver = w;
        edge->next = G->ver[v].first;
        G->ver[v].first = edge;

        edge = (Arc)malloc(sizeof(struct ArcCell));
        edge->adjver = v;
        edge->next = G->ver[w].first;
        G->ver[w].first = edge;
    }

    return G;
}

void PrintGraph(Graph G)
{
    Arc edge;
    int i;

    for (i = 1; i <= G->vernum; i++)
    {
        printf("%d:", G->ver[i].data);
        edge = G->ver[i].first;
        while (edge != NULL)
        {
            printf("%d->", edge->adjver);
            edge = edge->next;
        }
        printf("^\n");
    }
}

int visited[VERNUM][VERNUM];
void DfsSpanningTree(Graph G, VertexType s)
{
    Arc edge;

    visited[0][s] = 1;

    edge = G->ver[s].first;
    while (edge != NULL)
    {
        if (visited[0][edge->adjver] == 0)
        {
            printf("(%d, %d)\n", s, edge->adjver);
            visited[s][edge->adjver] = 1;
            DfsSpanningTree(G, edge->adjver);
        }
        else
        {
            if(visited[edge->adjver][s]==0)
            {
                printf("(%d, %d) back edge\n", s, edge->adjver);
                visited[s][edge->adjver] = 1;
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
    DfsSpanningTree(G, 1);
    system("pause");
    return 0;
}