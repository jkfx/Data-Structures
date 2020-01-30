#ifndef _HashSep_H
#define _HashSep_H

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef char* ElementType;
typedef unsigned int Index;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType X, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);

int NextPrime(int n);
Index Hash(ElementType Key, int TableSize);

#endif /* _HashSep_H */