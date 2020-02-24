#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define A 48271L
#define M 2147483647L
#define Q (M / A)
#define R (M % A)

static unsigned long Seed = 1;
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

int RandInt(int left, int right)
{
    return (int)(Random() * (right - left+1) + left);
}

/**
 * If Witness does not return 1, N is definitely composite.
 * Do this by computing (A ^ i) mod N and looking for non-trivial
 * square roots of 1 along the way.
 * We are assuming very large numbers, so this is pseudocode */
typedef long long HugeInt;
HugeInt Witness(HugeInt a, HugeInt i, HugeInt n)
{
    HugeInt X, Y;

    if (i == 0)
        return 1;

    X = Witness(a, i / 2, n);
    if (X == 0) // If N is recursively composite, stop
        return 0;

    /* N is not prime if we find a non-trivial root of 1 */
    Y = (X * X) % n;
    if (Y == 1 && X != 1 && X != n - 1)
        return 0;

    if (i % 2 != 0)
        Y = (a * Y) % n;

    return Y;
}

/**
 * IsPrime: Test if N >= 3 is prime using one value of A.
 * Repeat this procedure as many time as needed for desired error rate
 * */
int IsPrime(HugeInt N)
{
    return Witness(RandInt(2, N - 2), N - 1, N) == 1;
}

int main()
{
    Intialized((unsigned)time(NULL));
    printf("11 IsPrime: %d\n", IsPrime(11));
    printf("12 IsPrime: %d\n", IsPrime(12));
    printf("13 IsPrime: %d\n", IsPrime(13));
    printf("341 IsPrime: %d\n", IsPrime(341));
    printf("561 IsPrime: %d\n", IsPrime(561));
    return 0;
}