#ifndef _Graph_H
#define _Graph_H

#define numver (16)
struct VertexCell;
struct ArcCell;
struct GraphCell;
typedef struct VertexCell *Vertex;
typedef struct ArcCell *Arc;
typedef struct GraphCell *Graph;
typedef int VertexType;
typedef int WeightType;

void PrintGraph(Graph G);
Graph CreateGraph(void);
void DfsSpanningTree(Graph G,VertexType s);

#endif /* _Graph_H */