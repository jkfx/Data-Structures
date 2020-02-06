#include <stdio.h>
#include <stdlib.h>

#define MaxInt (999999999) // 表示极大值
#define MVNum 16           // 最大顶点数

typedef int VertexType; // 顶点数据类型
typedef int ArcType;    // 边的权值

typedef struct
{
    VertexType vexs[MVNum];     // 顶点表
    ArcType arcs[MVNum][MVNum]; // 邻接矩阵
    int vexnum, arcnum;         // 图的当前点数和边数
} * AMGraph;

AMGraph CreateGraph(void)
{
    AMGraph G;
    G = (AMGraph)malloc(sizeof(*G));
    return G;
}

/**
 * 采用邻接矩阵表示法创建无向网
 * 1. 输入总定点数和总边数
 * 2. 依次输入点的信息存入顶点表中
 * 3. 初始化邻接矩阵，使每个权值初始化为极大值
 * 4. 构造邻接矩阵。依次输入每条边依附的顶点和其权值
 * */
void CreateUDN(AMGraph G)
{
    int i, j, k;
    VertexType v1, v2;
    ArcType w;

    /* 输入总顶点数、总边数 */
    printf("Input vexnum: ");
    scanf("%d", &G->vexnum);
    printf("Input arcnum: ");
    scanf("%d", &G->arcnum);

    /* 初始化邻接矩阵，边的权值赋为极大值 */
    for (i = 0; i < G->vexnum; i++)
        for (j = 0; j < G->vexnum; j++)
            G->arcs[i][i] = MaxInt;

    /* 构造邻接矩阵 */
    for (k = 0; k < G->arcnum; k++)
    {
        /* 输入一条边依附的顶点及权值 */
        scanf("%d%d%d", &v1, &v2, &w);
        G->arcs[v1][v2] = w;
        // G->arcs[v2][v1]=G->arcs[i][j];
    }
}

int main()
{
    AMGraph G;
    G = CreateGraph();
    CreateUDN(G);
    system("pause");
    return 0;
}