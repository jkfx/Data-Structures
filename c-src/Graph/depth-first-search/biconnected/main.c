#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

struct VertexCell
{
    VertexType name;
    Arc first;
    // int visited;
};

struct ArcCell
{
    Vertex adjacency;
    Arc next;
    //WeightType weight;
};

struct GraphCell
{
    Vertex vertex;
    int vernum;
    int arcnum;
};

Graph CreateGraph(void)
{
    int i;
    VertexType u, w;
    Arc v;
    Graph G;
    G = (Graph)malloc(sizeof(struct GraphCell));
    printf("Input vernum: ");
    scanf("%d", &G->vernum);
    G->vertex = (Vertex)malloc(sizeof(struct VertexCell) * (G->vernum + 1));
    for (i = 1; i <= G->vernum; i++)
    {
        G->vertex[i].name = i;
        G->vertex[i].first = NULL;
        //G->vertex[i].visited = 0;
    }
    printf("Input arcnum: ");
    scanf("%d", &G->arcnum);
    for (i = 1; i <= G->arcnum; i++)
    {
        scanf("%d%d", &u, &w);
        v = (Arc)malloc(sizeof(struct ArcCell));
        v->adjacency = &G->vertex[w];
        v->next = G->vertex[u].first;
        G->vertex[u].first = v;
        /* 无向图 不带权值 */
        v = (Arc)malloc(sizeof(struct ArcCell));
        v->adjacency = &G->vertex[u];
        v->next = G->vertex[w].first;
        G->vertex[w].first = v;
    }
    return G;
}

void PrintGraph(Graph G)
{
    int i;
    Arc A;
    for (i = 1; i <= G->vernum; i++)
    {
        printf("%d: ", i);
        A = G->vertex[i].first;
        while (A != NULL)
        {
            printf("%d->", A->adjacency->name);
            A = A->next;
        }
        printf("^\n");
    }
}

int Visited[16], Num[16], Low[16], Parent[16], Counter = 1;
void AssignNum(Graph G, VertexType v)
{
    Arc w;
    Num[v] = Counter++;
    Visited[v] = 1;
    w = G->vertex[v].first;
    while (w != NULL)
    {
        if (Visited[w->adjacency->name] == 0)
        {
            Parent[w->adjacency->name] = v;
            AssignNum(G, w->adjacency->name);
        }
        w = w->next;
    }
}

void AssignLow(Graph G, VertexType v)
{
    Arc w;
    Low[v] = Num[v];
    w = G->vertex[v].first;
    while (w != NULL)
    {
        if (Num[w->adjacency->name] > Num[v])
        {
            AssignLow(G, w->adjacency->name);
            if (Low[w->adjacency->name] >= Num[v])
                printf("%d is an actticulation point\n", v);
            Low[v] = Low[v] < Low[w->adjacency->name] ? Low[v] : Low[w->adjacency->name];
        }
        else
        {
            if (Parent[v] != w->adjacency->name)
                Low[v] = Low[v] < Num[w->adjacency->name] ? Low[v] : Num[w->adjacency->name];
        }
        w = w->next;
    }
}

void FindAct(Graph G, VertexType v)
{
    Arc w;
    Visited[v] = 1;
    Low[v] = Num[v] = Counter++;
    w = G->vertex[v].first;
    while (w != NULL)
    {
        if (Visited[w->adjacency->name] == 0)
        {
            Parent[w->adjacency->name] = v;
            FindAct(G, w->adjacency->name);
            if (Low[w->adjacency->name] >= Num[v])
                printf("%d is an acticulation point\n", v);
            Low[v] = Low[v] < Low[w->adjacency->name] ? Low[v] : Low[w->adjacency->name];
        }
        else
        {
            if (Parent[v] != w->adjacency->name)
                Low[v] = Low[v] < Num[w->adjacency->name] ? Low[v] : Low[w->adjacency->name];
        }
        w = w->next;
    }
}

int main()
{
    Graph G;
    G = CreateGraph();
    PrintGraph(G);
    //AssignNum(G, 3);
    //AssignLow(G, 3);
    FindAct(G, 3);
    system("pause");
    return 0;
}