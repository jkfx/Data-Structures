#ifndef _Gcd_h
#define _Gcd_h

/* 欧几里得算法：计算最大公因数 */
unsigned int Gcd(unsigned int M, unsigned int N)
{
    unsigned int Rem;
    while (N > 0)
    {
        Rem = M % N;
        M = N;
        N = Rem;
    }
    return M;
}

#endif