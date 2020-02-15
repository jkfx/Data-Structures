#ifndef _Graph_H
#define _Graph_H

#define VERNUM (16)
struct VertexCell;
struct ArcCell;
struct GraphCell;
struct ListCell;
typedef int ElementType;
typedef struct ListCell *List;
typedef struct ListCell *Position;
typedef struct VertexCell *Vertex;
typedef struct ArcCell *Arc;
typedef struct GraphCell *Graph;
typedef int VertexType;

void PrintGraph(Graph G);
Graph CreateGraph(void);
void Dfs(Graph G, VertexType v, List L);
List CreateList(void);
void Insert(ElementType X, List L);
void PrintList(List L);
void DisposeList(List L);
Graph ReverseGraph(Graph G);

#endif /* _Graph_H */