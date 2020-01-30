#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;

struct Node
{
    int Coeefficient;
    int Exponent;
    PtrToNode Next;
};

typedef PtrToNode Polynomial;

Polynomial CreatePoly(void)
{
    Polynomial Poly;
    Poly = (PtrToNode)malloc(sizeof(struct Node));
    Poly->Coeefficient = 0;
    Poly->Exponent = 0;
    Poly->Next = NULL;
    return Poly;
}

PtrToNode FindPrevious(Polynomial Poly, Polynomial Pos)
{
    Polynomial TmpCell;

    if (Poly->Next == NULL)
        return Poly;
    TmpCell = Poly;
    while (TmpCell->Next != NULL && TmpCell->Next != Pos)
        TmpCell = TmpCell->Next;
    return TmpCell;
}

void Insert(int Coee, int Expo, Polynomial Poly)
{
    Polynomial NPoly, TmpCell;
    NPoly = CreatePoly();
    NPoly->Coeefficient = Coee;
    NPoly->Exponent = Expo;
    TmpCell = Poly->Next;
    if (TmpCell != NULL)
        while (TmpCell && TmpCell->Exponent > Expo)
            TmpCell = TmpCell->Next;
    NPoly->Next = TmpCell;
    TmpCell = FindPrevious(Poly, TmpCell);
    TmpCell->Next = NPoly;
}

void PrintPoly(Polynomial Poly)
{
    Polynomial Pos;
    Pos = Poly->Next;
    while (Pos != NULL)
    {
        printf("%dX^%d + ", Pos->Coeefficient, Pos->Exponent);
        Pos = Pos->Next;
    }
    printf("\n");
}

Polynomial AddPoly(const Polynomial Poly1, const Polynomial Poly2)
{
    Polynomial PolySum, Pos1, Pos2, PosS;
    PolySum = CreatePoly();
    Pos1 = Poly1->Next;
    Pos2 = Poly2->Next;
    PosS = PolySum;
    while (Pos1 != NULL && Pos2 != NULL)
    {
        PosS->Next = CreatePoly();
        PosS = PosS->Next;
        PosS->Next = NULL;
        if (Pos1->Exponent > Pos2->Exponent)
        {
            PosS->Exponent = Pos1->Exponent;
            PosS->Coeefficient = Pos1->Coeefficient;
            Pos1 = Pos1->Next;
        }
        else if (Pos1->Exponent < Pos2->Exponent)
        {
            PosS->Exponent = Pos2->Exponent;
            PosS->Coeefficient = Pos2->Coeefficient;
            Pos2 = Pos2->Next;
        }
        else
        {
            PosS->Exponent = Pos1->Exponent;
            PosS->Coeefficient = Pos1->Coeefficient + Pos2->Coeefficient;
            Pos1 = Pos1->Next;
            Pos2 = Pos2->Next;
        }
    }
    while (Pos1 != NULL)
    {
        PosS->Next = CreatePoly();
        PosS = PosS->Next;
        PosS->Next = NULL;
        PosS->Exponent = Pos1->Exponent;
        PosS->Coeefficient = Pos1->Coeefficient;
        Pos1 = Pos1->Next;
    }
    while (Pos2 != NULL)
    {
        PosS->Next = CreatePoly();
        PosS = PosS->Next;
        PosS->Next = NULL;
        PosS->Exponent = Pos2->Exponent;
        PosS->Coeefficient = Pos2->Coeefficient;
        Pos1 = Pos2->Next;
    }
    return PolySum;
}

int main()
{
    Polynomial Poly1, Poly2, PolySum;
    Poly1 = CreatePoly();
    Poly2 = CreatePoly();
    Insert(4, 2, Poly1);
    Insert(4, 8, Poly1);
    Insert(4, 1, Poly1);

    Insert(4, 2, Poly2);
    Insert(4, 6, Poly2);
    Insert(4, 4, Poly2);
    PrintPoly(Poly1);
    PrintPoly(Poly2);
    PolySum = AddPoly(Poly1, Poly2);
    PrintPoly(PolySum);
    system("pause");
    return 0;
}