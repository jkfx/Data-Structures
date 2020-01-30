#include <stdio.h>
#include <stdlib.h>

#define MaxDegree 8

/* 多项式ADT的数组实现的类型声明 */
typedef struct Poly
{
    int CoeffArray[MaxDegree + 1];
    int HighPower;
} * Polynomial;

void ZeroPolynomial(Polynomial Poly)
{
    int i;
    for (i = 0; i <= MaxDegree; i++)
        Poly->CoeffArray[i] = 0;
    Poly->HighPower = 0;
}

void InitPoly(Polynomial Poly, int *Coeff, int HighPower)
{
    int i;
    for (i = 0; i <= MaxDegree; i++)
        Poly->CoeffArray[i] = Coeff[i];
    Poly->HighPower = HighPower;
}

void PrintPoly(Polynomial Poly)
{
    int i;
    for (i = 0; i <= MaxDegree; i++)
        printf("%dX^%d + ", Poly->CoeffArray[i], Poly->HighPower - i);
    printf("\n");
}

int main()
{
    Polynomial Poly1, Poly2;
    int Coeff1[] = {19, 99, 10, 30, 20, 10, 12, 30, 66};
    int Coeff2[] = {19, 49, 10, 30, 19, 99, 11, 11, 88};
    Poly1 = (Polynomial)malloc(sizeof(struct Poly));
    Poly2 = (Polynomial)malloc(sizeof(struct Poly));
    ZeroPolynomial(Poly1);
    ZeroPolynomial(Poly2);
    InitPoly(Poly1, Coeff1, 8);
    InitPoly(Poly2, Coeff2, 16);
    PrintPoly(Poly1);
    PrintPoly(Poly2);
    system("pause");
    return 0;
}