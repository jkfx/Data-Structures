#ifndef _SkewHeap_H
#define _SkewHeap_H

struct TreeNode;
typedef struct TreeNode *PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(void);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);
PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2);
#define Insert(X, H) (H = Insert1((X), H))
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
void SwapChildren(PriorityQueue H);
void OrderTraversal(PriorityQueue H);

#endif /* _SkewHeap_H */