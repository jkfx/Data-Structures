#ifndef _BinomialQueue_H
#define _BinomialQueue_H

struct BinNode;
typedef struct BinNode *Position;
typedef struct BinNode *BinTree;
struct Collection;
typedef struct Collection *BinQueue;
typedef int ElementType;

BinTree CombineTrees(BinTree T1, BinTree B2);
BinQueue Merge(BinQueue H1, BinQueue H2);
ElementType DeleteMin(BinQueue H);
int IsEmpty(BinQueue H);
BinQueue Initialize(void);

#endif  /* _BinomialQueue_H */