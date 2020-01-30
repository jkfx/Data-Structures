#ifndef _HashQuad_H
#define _HashQuad_H

typedef unsigned int Index;
typedef Index Position;
typedef int ElementType;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroryTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable Rehash(HashTable H);

int NextPrime(int n);
int PreviousPrime(int n);
Index Hash(ElementType Key, int TableSize);
Index DoubleHash(ElementType Key, int TableSize);

#endif /* _HashQuad_H */