#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct GraphCell
{
    VertexType ver[VERNUM];
    WeightType arc[VERNUM][VERNUM];
    int vernum;
    int arcnum;
};

Graph CreateGraph(void)
{
    int i, j;
    Graph g;
    VertexType v, w;
    WeightType weight;
    g = (Graph)malloc(sizeof(struct GraphCell));

    /**
     * 手动输入顶点和边及权值
     * */
    printf("Input vernum: ");
    scanf("%d", &g->vernum);
    printf("Input arcnum: ");
    scanf("%d", &g->arcnum);
    for (i = 0; i < g->vernum; i++)
        g->ver[i] = i;
    for (i = 0; i < VERNUM; i++)
    {
        for (j = 0; j < VERNUM; j++)
            g->arc[i][j] = INFINITY;
        g->arc[i][i] = 0;
    }
    for (i = 0; i < g->arcnum; i++)
    {
        scanf("%d%d%d", &v, &w, &weight);
        g->arc[v - 1][w - 1] = g->arc[w - 1][v - 1] = weight;
    }
    return g;
}

void Prim(Graph g)
{
    VertexType adjver[VERNUM];
    WeightType lowcost[VERNUM];
    int i, j, k;
    WeightType min;

    for (i = 0; i < g->vernum; i++)
    {
        lowcost[i] = g->arc[0][i];
        adjver[i] = 0;
    }

    for (i = 1; i < g->vernum; i++)
    {
        k = 0;
        min = INFINITY;

        for (j = 1; j < g->vernum; j++)
            if (lowcost[j] != 0 && lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }

        printf("(%d, %d)\n", adjver[k] + 1, k + 1);
        lowcost[k] = 0;

        for (j = 1; j < g->vernum; j++)
            if (lowcost[j] != 0 && g->arc[k][j] < lowcost[j])
            {
                adjver[j] = k;
                lowcost[j] = g->arc[k][j];
            }
    }
}

int main()
{
    Graph g;
    g = CreateGraph();
    Prim(g);
    system("pause");
    return 0;
}