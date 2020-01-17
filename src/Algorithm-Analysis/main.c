#include <stdio.h>
#include <stdlib.h>
#include "MaxSubSequenceSum.h"
#include "BinarySearch.h"
#include "Pow.h"

int main()
{
    int A[] = {4, -3, 5, -2, -1, 2, 6, -2};
    int N = 8;
    printf("%d\n", MaxSubSequenceSum4(A, N));
    printf("%d\n", BinarySearch(A, 6, N));
    printf("%d\n", Pow(2, 10));
    system("pause");
    return 0;
}
