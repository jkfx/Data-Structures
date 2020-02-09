#include <stdio.h>
#include <stdlib.h>
#include "grapg.h"
#include "disjset.h"
#include "heap.h"

struct VertexCell
{
    VertexType name;
    Arc first;
};

struct ArcCell
{
    VertexType adjacency;
    WeightType weight;
    Arc next;
};

struct GraphCell
{
    Vertex vertex;
    int arcnum;
    int vernum;
};

Graph InitGraph(void)
{
    Graph G;
    G = (Graph)malloc(sizeof(struct GraphCell));
    if (G == NULL)
        exit(0);
    G->arcnum = 0;
    G->vernum = 0;
    G->vertex = NULL;
    return G;
}

void CreateGraph(Graph G)
{
    int i;
    VertexType v, w;
    Arc new;
    WeightType weight;

    printf("Input vertex number: ");
    scanf("%d", &G->vernum);
    G->vertex = (Vertex)malloc(sizeof(struct VertexCell) * (G->vernum + 1));
    if (G->vertex == NULL)
        exit(0);
    for (i = 1; i <= G->vernum; i++)
    {
        G->vertex[i].name = i;
        G->vertex[i].first = NULL;
    }
    printf("Input edge number: ");
    scanf("%d", &G->arcnum);

    for (i = 1; i <= G->arcnum; i++)
    {
        scanf("%d%d%d", &v, &w, &weight);
        new = (Arc)malloc(sizeof(struct ArcCell));
        if (new == NULL)
            exit(0);
        new->adjacency = w;
        new->weight = weight;
        new->next = G->vertex[v].first;
        G->vertex[v].first = new;

        new = (Arc)malloc(sizeof(struct ArcCell));
        if (new == NULL)
            exit(0);
        new->adjacency = v;
        new->weight = weight;
        new->next = G->vertex[w].first;
        G->vertex[w].first = new;
    }
    G->arcnum *= 2;
}

struct TableCell
{
    VertexType v;
    int known;
    DistType dv;
    VertexType pv;
};

Table InitTable(Graph G)
{
    int i;
    Table T;
    T = (Table)malloc(sizeof(struct TableCell) * (G->vernum + 1));
    if (T == NULL)
        exit(0);
    for (i = 1; i <= G->vernum; i++)
    {
        T[i].v = i;
        T[i].known = 0;
        T[i].dv = Infinity;
        T[i].pv = NotAVertex;
    }
    return T;
}

VertexType FindVertex(Table T, Graph G)
{
    VertexType v;
    int i;
    v = NotAVertex;
    for (i = 1; i <= G->vernum; i++)
        if (T[i].known == 0)
        {
            v = i;
            break;
        }
    for (i = 1; i <= G->vernum; i++)
        if (T[i].known == 0 && T[i].dv < T[v].dv)
        {
            v = i;
        }
    return v;
}

Table Prim(Graph G, VertexType s)
{
    VertexType v;
    Arc w;
    Table T;
    int i;
    T = InitTable(G);
    T[s].dv = 0;
    while (1)
    {
        v = FindVertex(T, G);
        if (v == NotAVertex)
            break;
        T[v].known = 1;
        w = G->vertex[v].first;
        while (w != NULL)
        {
            if (T[w->adjacency].known == 0 && T[w->adjacency].dv > w->weight)
            {
                T[w->adjacency].dv = w->weight;
                T[w->adjacency].pv = v;
            }
            w = w->next;
        }
    }
    return T;
}

void DestroyGraph(Graph G)
{
    free(G->vertex);
    free(G);
}

void DestroyTable(Table T)
{
    free(T);
}

struct PriorityQueueCell
{
    Arc arc;
    Vertex vertex;
};

struct PriorityQueue
{
    HeapElement *Elements;
    int Capacity;
    int Size;
};

Heap BuildHeap(Graph G)
{
    int i;
    Heap H;
    Arc W;

    H = (Heap)malloc(sizeof(struct PriorityQueue));
    if (H == NULL)
        exit(0);
    H->Capacity = G->arcnum + 1;
    H->Size = 0;
    H->Elements = (HeapElement *)malloc(sizeof(HeapElement) * H->Capacity);
    if (H->Elements == NULL)
        exit(0);
    for (i = 1; i <= G->vernum; i++)
    {
        W = G->vertex[i].first;
        while (W != NULL)
        {
            H->Elements[++H->Size].vertex = &(G->vertex[i]);
            H->Elements[H->Size].arc = W;
            W = W->next;
        }
    }

    for (i = H->Size / 2; i > 0; i--)
        PercolateDown(i, H);

    return H;
}

void PercolateDown(int i, Heap H)
{
    int MinSon, Min;
    HeapElement Tmp;
    if (i <= H->Size / 2)
    {
        if (i * 2 + 1 <= H->Size)
            MinSon = H->Elements[i * 2].arc->weight < H->Elements[i * 2 + 1].arc->weight ? i * 2 : i * 2 + 1;
        else
            MinSon = i * 2;
        Min = H->Elements[i].arc->weight < H->Elements[MinSon].arc->weight ? i : MinSon;
        Tmp = H->Elements[i];
        H->Elements[i] = H->Elements[Min];
        H->Elements[Min] = Tmp;
        PercolateDown(MinSon, H);
    }
}

HeapElement DeleteMin(Heap H)
{
    int i, Child;
    HeapElement Last, Min;

    Min = H->Elements[1];
    Last = H->Elements[H->Size--];
    for (i = 1; i <= H->Size / 2; i = Child)
    {
        Child = i * 2;
        if (Child != H->Size - 1 && H->Elements[Child].arc->weight > H->Elements[Child + 1].arc->weight)
            Child++;
        if (Last.arc->weight > H->Elements[Child].arc->weight)
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = Last;
    return Min;
}

void DestroyHeap(Heap H)
{
    free(H->Elements);
    free(H);
}

struct DisjointSetCell
{
    Vertex vertex;
    int parent;
    int index;
};

struct DisjointSet
{
    SetElement *Elements;
    int Capacity;
};

Set InitSet(Graph G)
{
    int i;
    Set S;

    S = (Set)malloc(sizeof(struct DisjointSet));
    if (S == NULL)
        exit(0);
    S->Capacity = G->vernum + 1;
    S->Elements = (SetElement *)malloc(sizeof(SetElement) * S->Capacity);
    if (S->Elements == NULL)
        exit(0);
    for (i = 1; i < S->Capacity; i++)
    {
        S->Elements[i].vertex = &(G->vertex[i]);
        S->Elements[i].parent = -1;
        S->Elements[i].index = i;
    }
    return S;
}

/* 按大小求并操作 */
void Union(Set S, SetType r1, SetType r2)
{
    if (S->Elements[r1].parent > S->Elements[r2].parent)
    {
        S->Elements[r2].parent += S->Elements[r1].parent;
        S->Elements[r1].parent = r2;
    }
    else
    {
        S->Elements[r1].parent += S->Elements[r2].parent;
        S->Elements[r2].parent = r1;
    }
}

/* 路径压缩 */
SetType FindSet(SetType X, Set S)
{
    if (S->Elements[X].parent < 0)
        return X;
    else
        return S->Elements[X].parent = FindSet(S->Elements[X].parent, S);
}

void Kruskal(Graph G)
{
    int EdgeAccepted;
    Set S;
    Heap H;
    SetType Uset, Vset;
    HeapElement E;
    int i;

    S = InitSet(G);
    H = BuildHeap(G);

    EdgeAccepted = 0;
    printf("Kruskal\nvertex | weight | adjacency\n");
    while (EdgeAccepted < G->vernum - 1)
    {
        E = DeleteMin(H);
        Uset = FindSet(E.vertex->name, S);
        Vset = FindSet(E.arc->adjacency, S);
        if (Uset != Vset)
        {
            /* Accept the edge */
            EdgeAccepted++;
            Union(S, Uset, Vset);
            printf("%d | %d | %d\n", E.vertex->name, E.arc->weight, E.arc->adjacency);
        }
        
    }
    printf("\n");
}

int main()
{
    Graph G;
    Table T;
    int i;
    Arc W;
    Set S;
    Heap H;

    G = InitGraph();
    CreateGraph(G);

    printf("adjacency list:\n");
    for (i = 1; i <= G->vernum; i++)
    {
        printf("%d: ", G->vertex[i].name);
        W = G->vertex[i].first;
        while (W != NULL)
        {
            printf("%d->", W->adjacency);
            W = W->next;
        }
        printf("^\n");
    }
    printf("\n");

    T = Prim(G, 1);

    printf("v | known | dv | pv\n");
    for (i = 1; i <= G->vernum; i++)
        printf("%d | %d | %d| %d\n", T[i].v, T[i].known, T[i].dv, T[i].pv);
    printf("\n");

    H = BuildHeap(G);

    //DeleteMin(H);

    

    S = InitSet(G);

    

    Kruskal(G);

    //DestroyGraph(G);
    //DestroyTable(T);
    //DestroyHeap(H);
    system("pause");
    return 0;
}