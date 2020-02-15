#ifndef _Graph_h
#define _Graph_H

#define VERNUM (16)
#define INFINITY (999999999)

struct GraphCell;
typedef struct GraphCell *Graph;
typedef int WeightType;
typedef int VertexType;

Graph CreateGraph(void);
void Prim(Graph G);
void Kruskal(Graph G);

#endif  /* _Graph_H */