#ifndef _Graph_H
#define _Graph_H

struct VertexCell;
struct ArcCell;
struct GraphCell;
struct ListCell;
typedef struct VertexCell *Vertex;
typedef struct ArcCell *Arc;
typedef struct GraphCell *Graph;
typedef struct ListCell *List;
typedef int VertexType;
typedef int WeightType;

void PrintGraph(Graph G);
void PrintList(List L);
Graph CreateGraph(void);
Graph CreateFlowGraph(Graph G);
Graph CreateResidualGraph(Graph G);
List FindPath(Graph G, VertexType s, VertexType e);

#endif  /* _Graph_H */