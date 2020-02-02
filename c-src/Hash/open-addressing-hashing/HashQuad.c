#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HashQuad.h"

enum KindOfEntry
{
    Legitimate,
    Empty,
    Deleted
};

struct HashEntry
{
    ElementType Element;
    enum KindOfEntry Info;
};
typedef struct HashEntry Cell;

/**
 * Cell *TheCells will be an array of
 * HashEntry cells, allocated later.
 * */
struct HashTbl
{
    int TableSize;
    Cell *TheCells;
};

HashTable InitializeTable(int TableSize)
{
    HashTable H;
    int i;

    /* Allocate table */
    H = (HashTable)malloc(sizeof(struct HashTbl));
    if (H == NULL)
        exit(0);
    H->TableSize = NextPrime(TableSize);

    /* Allocate array of Cells */
    H->TheCells = (Cell *)malloc(sizeof(Cell) * H->TableSize);
    if (H->TheCells == NULL)
        exit(0);
    for (i = 0; i < H->TableSize; i++)
        H->TheCells[i].Info = Empty;

    return H;
}

Position Find(ElementType Key, HashTable H)
{
    Position CurrentPos;
    int CollisionNum;

    CollisionNum = 0;
    CurrentPos = Hash(Key, H->TableSize);
    while (H->TheCells[CurrentPos].Info != Empty && H->TheCells[CurrentPos].Element != Key) /* while 内的判断条件很重要，不能改变顺序 */
    {
        CurrentPos += 2 * ++CollisionNum - 1; /* 乘以 2 实际上就是进行一位二进制进位*/
        if (CurrentPos >= H->TableSize)
            CurrentPos -= H->TableSize;
    }
    return CurrentPos;
}

void Insert(ElementType Key, HashTable H)
{
    Position Pos;

    Pos = Find(Key, H);
    if (H->TheCells[Pos].Info != Legitimate)
    {
        /* OK to insert here */
        H->TheCells[Pos].Info = Legitimate;
        H->TheCells[Pos].Element = Key;
    }
}

Index Hash(ElementType Key, int TableSize)
{

    return Key % 10;
}

int NextPrime(int n)
{
    int i;
    for (;; n++)
    {
        for (i = 2; i < (int)sqrt(n); i++)
            if (n % i == 0)
                break;
        if (i == (int)sqrt(n))
            return n;
    }
}

int PreviousPrimer(int n)
{
    int i, j;
    for (i = n; i > 1; i--)
    {
        for (j = 2; j < i; j++)
            if (n % j == 0)
                break;
        if (j == i)
            return i;
    }
}

/* 双散列 */
Index DoubleHash(ElementType Key, int TableSize)
{
    int R;
    Index Pos;
    R = PreviousPrimer(TableSize);
    Pos = Hash(Key, TableSize);
    return Pos - (R % Pos);
}

/* 再散列 */
HashTable Rehash(HashTable H)
{
    int i, OldSize;
    Cell *OldCells;

    OldCells = H->TheCells;
    OldSize = H->TableSize;

    /* Get a new, empty table */
    H = InitializeTable(2 * OldSize);

    /* Scan through old table, reinserting into new */
    for (i = 0; i < OldSize; i++)
        if (OldCells[i].Info == Legitimate)
            Insert(OldCells[i].Element, H);

    free(OldCells);

    return H;
}
int main()
{
    HashTable H;
    H = InitializeTable(10);
    H->TableSize = 10;
    Insert(4371, H);
    Insert(1323, H);
    Insert(6173, H);
    Insert(4199, H);
    Insert(4344, H);
    Insert(9679, H);
    Insert(1989, H);
    printf("%d\n", Find(4371, H));
    printf("%d\n", Find(6173, H));
    printf("%d\n", Find(1989, H));
    printf("%d\n", Find(9679, H));
    system("pause");
    return 0;
}