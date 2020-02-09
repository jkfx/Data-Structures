#ifndef _Graph_H
#define _Graph_H

#define Infinity (999999999)
#define NotAVertex (-1)
struct GraphCell;
struct VertexCell;
struct ArcCell;
struct TableCell;
typedef struct GraphCell *Graph;
typedef struct VertexCell *Vertex;
typedef struct ArcCell *Arc;
typedef struct TableCell *Table;
typedef int VertexType;
typedef int WeightType;
typedef int DistType;

Graph InitGraph(void);
void CreateGraph(Graph G);
Table InitTable(Graph G);
VertexType FindVertex(Table T,Graph G);
Table Prim(Graph G, VertexType s);
void DestroyGraph(Graph G);
void DestroyTable(Table T);
void Kruskal(Graph G);

#endif /*  _Graph_H */