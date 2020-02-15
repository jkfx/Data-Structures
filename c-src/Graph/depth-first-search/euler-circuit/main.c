#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"

struct VertexCell
{
    VertexType data;
    Arc next;
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
    ElementType Element;
    List next;
};

List CreateList(void)
{
    List L;
    L = (List)malloc(sizeof(struct ListCell));
    L->next = NULL;
    return L;
}

void Insert(ElementType X, List L)
{
    List tmp, p;
    tmp = CreateList();
    tmp->Element = X;
    p = L;
    while (p->next != NULL)
        p = p->next;
    p->next = tmp;
}

void Merge(List L, List E)
{
    List p, e, l;
    p = L;
    while (p->next != NULL && p->Element != E->next->Element)
        p = p->next;
    l = p->next;
    p->next = E->next->next;
    e = E;
    while (e->next != NULL)
        e = e->next;
    e->next = l;
}

void PrintList(List L)
{
    List p;
    p = L->next;
    while (p != NULL)
    {
        printf("%d ", p->Element);
        p = p->next;
    }
    printf("\n");
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
        G->ver[i].next = NULL;
    }

    printf("Input arcnum: ");
    scanf("%d", &G->arcnum);

    for (i = 1; i <= G->arcnum; i++)
    {
        scanf("%d%d", &v, &w);
        edge = (Arc)malloc(sizeof(struct ArcCell));
        edge->adjver = w;
        edge->next = G->ver[v].next;
        G->ver[v].next = edge;

        edge = (Arc)malloc(sizeof(struct ArcCell));
        edge->adjver = v;
        edge->next = G->ver[w].next;
        G->ver[w].next = edge;
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
        edge = G->ver[i].next;
        while (edge != NULL)
        {
            printf("%d->", edge->adjver);
            edge = edge->next;
        }
        printf("^\n");
    }
}

void DeleteArc(Graph G, VertexType head, VertexType tail)
{
    Arc edge, pre;

    pre = &G->ver[head];
    edge = G->ver[head].next;
    while (edge->adjver != tail)
    {
        pre = edge;
        edge = edge->next;
    }
    pre->next = edge->next;
    free(edge);
    pre = &G->ver[tail];
    edge = G->ver[tail].next;
    while (edge->adjver != head)
    {
        pre = edge;
        edge = edge->next;
    }
    pre->next = edge->next;
    free(edge);
}

int HasEulerCircuit(Graph G)
{
    int degree[G->vernum + 1];
    int i;
    Arc edge;
    for (i = 1; i <= G->vernum; i++)
        degree[i] = 0;
    for (i = 1; i <= G->vernum; i++)
    {
        edge = G->ver[i].next;
        while (edge != NULL)
        {
            degree[i] += 1;
            degree[edge->adjver] += 1;
            edge = edge->next;
        }
    }
    for (i = 1; i <= G->vernum; i++)
        if (degree[i] != 0)
            break;
    if (i > G->vernum)
        return 0;
    for (i = 1; i <= G->vernum; i++)
    {
        if (degree[i] != 0 && (degree[i] / 2) % 2 == 1)
            return 0;
    }
    return 1;
}

void EulerCircuit(Graph G, VertexType s)
{
    List L, E;

    L = CreateList();
    Insert(s, L);
    while (HasEulerCircuit(G))
    {
        s = NextStart(L, G);
        E = NextEulerCircuit(G, s);
        Merge(L, E);
        //PrintGraph(G);
    }
    PrintList(L);
}

VertexType NextStart(List L, Graph G)
{
    List p;
    p = L->next;
    while (p != NULL)
    {
        if (G->ver[p->Element].next != NULL)
            return p->Element;
        p = p->next;
    }
    return 0; // 返回 0 表示没有顶点可用了
}

List NextEulerCircuit(Graph G, VertexType s)
{
    List L;
    Arc edge;
    VertexType tail;
    VertexType start;
    start = s;
    L = CreateList();
    Insert(s, L);
    while (tail != start)
    {
        edge = G->ver[s].next;
        tail = edge->adjver;
        Insert(tail, L);
        DeleteArc(G, s, tail);
        //PrintGraph(G);
        s = tail;
    }
    return L;
}

int main()
{
    Graph G;
    G = CreateGraph();
    PrintGraph(G);
    EulerCircuit(G, 5); // 从顶点5开始查找欧拉回路
    return 0;
}