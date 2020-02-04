#ifndef _DisjSet_H
#define _DesjSet_H

#define MAX (16)
typedef int ElementType;
typedef int SetType;
typedef int DisjSet[MAX+1];

void Initialize(DisjSet S);
SetType Find(ElementType X, DisjSet S); /* 路径压缩 */
SetType Find1(ElementType X, DisjSet S);    /* 路径评分 */
SetType Union(DisjSet S, SetType Root1, SetType Root2);
SetType Union1(DisjSet S, SetType Root1, SetType Root2);


#endif  /* _DesjSet_H */