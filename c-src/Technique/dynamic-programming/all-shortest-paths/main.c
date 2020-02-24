#include <stdio.h>
#include <stdlib.h>

#define NUM (8)
#define INFINITY (999999999)
#define NotAVertex (-1)

typedef int TwoDimArray[NUM][NUM];

void AllPairs(TwoDimArray A, TwoDimArray D, TwoDimArray Path, int N)
{
    int i, j, k;

    /* Initialize D and path */
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            D[i][j] = A[i][j];
            Path[i][j] = NotAVertex;
        }

    for (k = 0; k < N; k++)
        /* Consider each vertex as an intermediate */
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                if (D[i][j] + D[k][j] < D[i][j])
                {
                    /* Update shortest path */
                    D[i][j] = D[i][k] + D[k][j];
                    Path[i][j] = k;
                }

    printf("the values of the shortest path:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%d ", D[i][j]);
        printf("\n");
    }

    printf("Actual path:\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%d ", D[i][j]);
        printf("\n");
    }
}

int main()
{
    int vernum, arcnum;
    int i, j;
    int v, w, d;
    TwoDimArray A, D, Path;

    printf("Input vernum: ");
    scanf("%d", &vernum);
    printf("Input arcnum: ");
    scanf("%d", &arcnum);
    for (i = 0; i < vernum; i++)
        for (j = 0; j < vernum; j++)
            A[i][j] = -INFINITY;
    for (i = 0; i < arcnum; i++)
    {
        scanf("%d%d%d", &v, &w, &d);
        A[v][w] = d;
    }
    AllPairs(A, D, Path, vernum);
    system("pause");
    return 0;
}