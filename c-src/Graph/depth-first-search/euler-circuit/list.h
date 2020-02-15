#ifndef _List_H
#define _List_H

struct ListCell;
typedef int ElementType;
typedef struct ListCell *List;

struct VertexCell;
struct ArcCell;
struct GraphCell;
typedef struct VertexCell *Vertex;
typedef struct ArcCell *Arc;
typedef struct GraphCell *Graph;
typedef int VertexType;
typedef int WeightType;

List CreateList(void);
void Insert(ElementType X, List L);
List NextEulerCircuit(Graph G, VertexType s);
void Merge(List L, List E);
VertexType NextStart(List L, Graph G);
void PrinList(List L);

#endif /*  _List_H */