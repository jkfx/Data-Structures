/**
 * 2020-2-13
 * 网络流问题中最大流问题
 * <<数据结构与算法分析>> 书中并没有太过详细介绍最大流算法，只是简单地说明了下步骤。
 * 码住，将来有一天要接触这个算法时在补充吧 = =
 * 估计到时候代码肯定会重写，我写下这段话只是证明我曾经来过~
 * */
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
    WeightType weight;
    Vertex adjacency;
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
    VertexType ver;
    Arc edge;
    List next;
};

Graph CreateGraph(void)
{
    int i;
    Graph G;
    VertexType v, w, weight;
    Arc edge;
    G = (Graph)malloc(sizeof(struct GraphCell));
    printf("Input vernum: ");
    scanf("%d", &G->vernum);
    G->ver = (Vertex)malloc(sizeof(struct VertexCell) * (G->vernum + 1));
    // 对没个顶点初始化
    for (i = 1; i <= G->vernum; i++)
    {
        G->ver[i].data = i;
        G->ver[i].first = NULL;
    }
    printf("Input arcnum: ");
    scanf("%d", &G->arcnum);
    for (i = 0; i < G->arcnum; i++)
    {
        scanf("%d%d%d", &v, &w, &weight);
        // 构造带权有向图
        edge = (Arc)malloc(sizeof(struct ArcCell));
        edge->adjacency = &G->ver[w];
        edge->weight = weight;
        edge->next = G->ver[v].first;
        G->ver[v].first = edge;
    }
    return G;
}

Graph CreateFlowGraph(Graph G)
{
    Graph Gf;
    int i;
    Arc gfe, ge;
    Gf = (Graph)malloc(sizeof(struct GraphCell));
    Gf->vernum = G->vernum;
    Gf->arcnum = G->arcnum;
    Gf->ver = (Vertex)malloc(sizeof(struct VertexCell) * Gf->vernum);
    for (i = 1; i <= Gf->vernum; i++)
    {
        // 顶点 i 初始化
        Gf->ver[i].data = i;
        Gf->ver[i].first = NULL;
        // 顶点 i 邻接边构造
        ge = G->ver[i].first;
        while (ge != NULL)
        {
            gfe = (Arc)malloc(sizeof(struct ArcCell));
            gfe->weight = 0;
            gfe->adjacency = &Gf->ver[ge->adjacency->data];
            gfe->next = Gf->ver[i].first;
            Gf->ver[i].first = gfe;
            ge = ge->next;
        }
    }
    return Gf;
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
            //printf("%d->", edge->adjacency->data);
            printf("%d(%d)->", edge->adjacency->data, edge->weight);
            edge = edge->next;
        }
        printf("^\n");
    }
}

Graph CreateResidualGraph(Graph G)
{
    int i;
    Arc ge, gre;
    Graph Gr;
    Gr = (Graph)malloc(sizeof(struct GraphCell));
    Gr->vernum = G->vernum;
    Gr->ver = (Vertex)malloc(sizeof(struct VertexCell) * Gr->vernum);
    Gr->arcnum = G->arcnum;
    for (i = 1; i <= Gr->vernum; i++)
    {
        // 初始化残余图 Gr 的顶点 i
        Gr->ver[i].data = i;
        Gr->ver[i].first = NULL;
        // 构造残余图
        ge = G->ver[i].first;
        while (ge != NULL)
        {
            gre = (Arc)malloc(sizeof(struct ArcCell));
            gre->weight = ge->weight;
            gre->adjacency = &Gr->ver[ge->adjacency->data];
            gre->next = Gr->ver[i].first;
            Gr->ver[i].first = gre;
            ge = ge->next;
        }
    }
    return Gr;
}

List FindPath(Graph G, VertexType s, VertexType e)
{
    Arc edge;
    List L;

    L = (List)malloc(sizeof(struct ListCell));

    edge = G->ver[s].first;
    while (edge != NULL)
    {
        if (edge->adjacency->data == e && edge->weight != 0)
        {
            L->ver = s;
            L->edge = edge;
            L->next = NULL;
            return L;
        }
        else
        {
            L->ver = s;
            L->edge = edge;
            L->next = FindPath(G, edge->adjacency->data, e);
            return L;
        }
    }
    return NULL;
}

void PrintList(List L)
{
    printf("%d->", L->ver);
    while (L != NULL)
    {
        printf("%d->", L->edge->adjacency->data);
        L = L->next;
    }
    printf("^\n");
}

int MaxmumFlow(Graph g, VertexType s, VertexType e)
{
    Graph gf, gr;
    List l;
    Arc edge;

    gf = CreateFlowGraph(g);
    gr = CreateResidualGraph(g);
    l = FindPath(gr, s, e);
    while(l!=NULL)
    {
        edge=l->edge;
    }
}

int main()
{
    Graph G, Gf, Gr;

    G = CreateGraph();
    Gf = CreateFlowGraph(G);
    Gr = CreateResidualGraph(G);

    printf("G\n");
    PrintGraph(G);

    printf("Gf\n");
    PrintGraph(Gf);

    printf("Gr\n");
    PrintGraph(Gr);

    system("pause");
    return 0;
}