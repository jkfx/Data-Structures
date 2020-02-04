#include <stdio.h>
#include <stdlib.h>
#include "disj-set.h"

void Initialize(DisjSet S)
{
    int i;
    for (i = 0; i <= MAX; i++)
        S[i] = 0;
}

SetType Union(DisjSet S, ElementType Element1, ElementType Element2)
{
    SetType Root1, Root2;
    Root1 = Find(Element1, S);
    Root2 = Find(Element2, S);
    if (Root1 == Root2)
        return Root1;
    else
        return Union1(S, Root1, Root2);
}

/* 按高度（秩）求并 高度小的树合并到高度大的树 */
SetType Union1(DisjSet S, SetType Root1, SetType Root2)
{
    if (S[Root1] > S[Root2])
        S[Root1] = Root2;
    else
    {
        if (S[Root1] == S[Root2])
            S[Root1]--;
        S[Root2] = Root1;
    }
}

SetType Find(ElementType X, DisjSet S)
{
    if (S[X] <= 0)
        return X;
    else
        //return S[X] = Find(S[X], S); /* 压缩路径法 */
        return Find(S[X], S);
}

/* 偏路径压缩-路径平分 */
SetType Find1(ElementType X, DisjSet S)
{
    while (S[X] > 0 && S[S[X]] > 0)
    {
        S[X] = S[S[X]];
        X = S[X];
    }
    if (S[X] > 0)
        X = S[X];
    return X;
}

int main()
{
    DisjSet S;
    Initialize(S);
    Union(S, 1, 2);
    Union(S, 3, 4);
    Union(S, 3, 6);
    Union(S, 5, 7);
    Union(S, 4, 6);
    Union(S, 2, 4);
    Union(S, 8, 9);
    Union(S, 5, 8);
    printf("%d\n", Find(6,S));
    printf("%d\n", Find1(6,S));
    printf("%d\n", Find1(9,S));
    system("pause");
    return 0;
}