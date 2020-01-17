#ifndef _BinarySearch_h

#define _BinarySearch_h

#define NotFound -1
typedef int ElementType;

/* 对分查找的算法实现 */
int BinarySearch(const ElementType A[], ElementType X, int N)
{
    int Low, Mid, High;
    Low = 0;
    High = N - 1;
    while (Low <= High)
    {
        Mid = (Low + High) / 2;
        if (A[Mid] < X)
            Low = Mid + 1;
        else if (A[Mid] > X)
            High = Mid - 1;
        else
            return Mid; /* Found */
    }
    return NotFound; /* NotFound is defined as -1 */
}

#endif /* _BinarySearch_h */