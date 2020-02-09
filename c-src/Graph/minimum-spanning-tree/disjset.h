#ifndef _DisjSet_H
#define _DisjSet_H

struct DisjointSetCell;
struct DisjointSet;
typedef struct DisjointSetCell SetElement;
typedef struct DisjointSet *Set;
typedef int SetType;

Set InitSet(Graph G);
SetType Find(SetType X, Set S);
void Union(Set S, SetType r1, SetType r2);
void DestroySet(Set S);

#endif  /*  _DisjSet_H */