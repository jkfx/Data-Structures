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

struct ListCell
{
    ElementType ver;
    List next;
};

List CreateList(void)
{
    List L;
    L = (List)malloc(sizeof(struct ListCell));
    L->ver = 0; // 头节点的数据域当作长度
    L->next = NULL;
    return L;
}

void Insert(ElementType X, List L)
{
    Position p, t;
    p = CreateList();
    p->ver = X;
    t = L;
    while (t->next != NULL)
        t = t->next;
    t->next = p;
    p->next = NULL;
    L->ver++;
}

void PrintList(List L)
{
    Position p;
    p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->ver);
        p = p->next;
    }
    printf("\n");
}

void DisposeList(List L)
{
    Position p, tmp;
    if (L != NULL)
    {
        p = L->next;
        while (p != NULL)
        {
            tmp = p;
            p = p->next;
            free(tmp);
        }
        L->next = NULL;
    }
}

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

int visited[VERNUM];
void Dfs(Graph G, VertexType v, List L)
{
    Arc edge;

    visited[v] = 1;
    Insert(v, L);
    edge = G->ver[v].first;
    while (edge != NULL)
    {
        if (visited[edge->adjver] == 0)
            Dfs(G, edge->adjver, L);
        edge = edge->next;
    }
}

Graph ReverseGraph(Graph G)
{
    Graph Gr;
    int i;
    Arc Ge, Gre;

    Gr = (Graph)malloc(sizeof(struct GraphCell));
    Gr->vernum = G->vernum;
    Gr->ver = (Vertex)malloc(sizeof(struct VertexCell) * (Gr->vernum + 1));
    for (i = 0; i <= Gr->vernum; i++)
    {
        Gr->ver[i].first = NULL;
        Gr->ver[i].data = i;
    }
    Gr->arcnum = G->arcnum;
    for (i = 1; i <= Gr->vernum; i++)
    {
        Ge = G->ver[i].first;
        while (Ge != NULL)
        {
            Gre = (Arc)malloc(sizeof(struct ArcCell));
            Gre->adjver = i;
            Gre->next = Gr->ver[Ge->adjver].first;
            Gr->ver[Ge->adjver].first = Gre;
            Ge = Ge->next;
        }
    }
    return Gr;
}

int main()
{
    Graph G, Gr;
    List L, T;
    Position p;
    int i;

    G = CreateGraph();
    PrintGraph(G);
    L = CreateList();
    Dfs(G, 7, L);
    PrintList(L);
    Gr = ReverseGraph(G);
    for (i = 0; i < VERNUM; i++)
        visited[i] = 0;
    PrintGraph(Gr);
    T = CreateList();
    p = L->next;
    while (p != NULL)
    {
        if (visited[p->ver] == 0)
            Dfs(Gr, p->ver, T);
        if (T->next != NULL)
        {
            PrintList(T);
            DisposeList(T);
        }
        p = p->next;
    }
    system("pause");
    return 0;
}