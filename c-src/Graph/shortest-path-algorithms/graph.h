#ifndef _Graph_H
#define _Graph_H

// #define NumVer (8)
#define NotAVertex (-1)
#define Infinity (999999999)

typedef int VertexType;
typedef int WeightType;
typedef int DistType;
struct GraphNode;
struct VertexNode;
struct TableNode;
typedef struct GraphNode *Graph;
typedef struct VertexNode *Vertex;
typedef struct TableNode *Table;

Graph CreateGraph(void);
Table InitTable(VertexType Start, Graph G);
void Unweighted1(Table T, Graph G);
void Unweighted2(Table T, Graph G, VertexType Start);
void PrintPath(VertexType V, Table T);
void Dijkstra(Table T, Graph G);
VertexType FindSmallestUnknownDistanceVertex(Table T, Graph G);
void NegativeEdge(Table T, Graph G, VertexType Start);

#endif /* _Graph_H*/