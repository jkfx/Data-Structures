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

void PrintGraph(Graph G);
Graph CreateGraph(void);
int HasEulerCircuit(Graph G);
void EulerCircuit(Graph G, VertexType s);
void DeleteArc(Graph G, VertexType head, VertexType tail);

#endif /*  _Graph_H */