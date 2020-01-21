List Intersect(List L1, List L2)
{
    List Result;
    Position L1Pos, L2Pos, ResultPos;

    L1Pos = FIrst(L1);
    L2Pos = First(L2);
    Result = MakeEmpty(NULL);
    ResultPos = First(Result);
    while (L1Pos != NULL && L2 != NULL)
    {
        if (L1Pos->Element < L2Pos->Element)
            L1Pos = Next(L1Pos, L1);
        else if (L1Pos->Element > L2Pos->Element)
            L2Pos = Next(L2Pos, L2);
        else
        {
            Insert(L1Pos->Element, Result, ResultPos);
            L1 = Next(L1Pos, L1);
            L2 = Next(L2Pos, L2);
            ResultPos = Next(ResultPos, Result);
        }
    }
    return Result;
}