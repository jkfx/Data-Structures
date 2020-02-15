#ifndef _Graph_H
#define _Graph_H

struct VertexCell;
struct ArcCell;
struct GraphCell;
typedef struct VertexCell *Vertex;
typedef struct ArcCell *Arc;
typedef struct GraphCell *Graph;
typedef int VertexType;
typedef int WeightType;

Graph CreateGraph(void);
void PrintGraph(Graph G);
void AssignNum(Graph G, VertexType v);
void AssignLow(Graph G, VertexType v);
void FindAct(Graph G, VertexType v);

#endif  /*  _Graph_H */