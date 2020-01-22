#ifndef _Tree_h
#define _Tree_h

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

typedef int ElementType;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);

#endif /* _Tree_h */