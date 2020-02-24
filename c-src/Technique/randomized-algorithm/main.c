#include <stdio.h>
#include <stdlib.h>

static unsigned long Seed = 1;

#define A 48271L
#define M 2147483647L
#define Q (M / A)
#define R (M % A)

/**
 * 不能正常工作的随机数生成器
 * 乘法可能溢出
 * */
double Random_DoesNotWork(void)
{
    Seed = (A * Seed) % M;
    return (double)Seed / M;
}

/**
 * 工作于 32 位机上的随机数生成器
 * */
double Random(void)
{
    long TmpSeed = A * (Seed % Q) - R * (Seed / Q);
    if (TmpSeed >= 0)
        Seed = TmpSeed;
    else
        Seed = TmpSeed + M;
    return (double)Seed / M;
}

void Intialized(unsigned long InitVal)
{
    Seed = InitVal;
}

int main()
{
    int i;
    Intialized(1);
    for (i = 0; i < Seed; i++)
        printf("%lf\n", Random());
    system("pause");
    return 0;
}