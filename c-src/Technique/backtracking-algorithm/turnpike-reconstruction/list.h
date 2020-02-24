#ifndef _List_H
#define _List_H

struct ListCell;
typedef struct ListCell *List;
typedef List Position;
typedef int ElementType;

List CreateList(void);
ElementType DeleteMax(List L);
void Remove(ElementType dist, List L);
int IsEmpty(List L);
ElementType FindMax(List L);
int IsBloneTo(ElementType dist, List L);
void Delete(ElementType dist, List L);
void Insert(ElementType dist, List L);
Position FindPre(Position p, List L);
void PrintList(List L);
void MakeEmpty(List L);

#endif /* _List_H */