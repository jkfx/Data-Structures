#ifndef _Pow_h
#define _Pow_h

/* 高效率的取幂运算 */
int IsEven(int N)
{
    return !(N % 2);
}

long int Pow(long int X, unsigned int N)
{
    if (N == 0)
        return 1;
    if (N == 1)
        return X;
    if (IsEven(N))
        return Pow(X * X, N / 2);
    else
        return Pow(X * X, N / 2) * X;
}

#endif /* _Pow_h */