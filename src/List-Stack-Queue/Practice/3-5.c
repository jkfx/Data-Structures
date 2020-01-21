List Union(List L1, List L2)
{
    List Result;
    Position L1Pos, L2Pos, ResultPos;
    Result = MakeEmpty(NULL);
    L1Pos = First(L1);
    L2Pos = First(L2);
    ResultPos = First(Result);
    while (L1Pos || L2Pos)
    {
        if (L1Pos == NULL)
        {
            Insert(L2Pos->Element, Result, ResultPos);
            L2Pos = Next(L2Pos, L2);
            ResultPos = Next(ResultPos);
            continue;
        }
        if (L2Pos == NULL)
        {
            Insert(L1Pos->Element, Result, ResultPos);
            L1Pos = Next(L1Pos, L1);
            ResultPos = Next(ResultPos);
            continue;
        }
        if (L1Pos->Element > L2Pos->Element)
        {
            Insert(L2->Element, Result, ResultPos);
            L2Pos = Next(L2Pos, L2);
            ResultPos = Next(ResultPos, Result);
        }
        else if (L1Pos->Element < L2Pos->Element)
        {
            Insert(L1Pos->Element, Result, ResultPos);
            L1Pos = Next(L1Pos, L1);
            ResultPos = Next(ResultPos);
        }
        else
        {
            Insert(L1Pos->Element, Result, ResultPos);
            L1Pos = Next(L1Pos, L1);
            L2Pos = Next(L2Pos, L2);
            ResultPos = Next(ResultPos);
        }
    }
    return Result;
}

List Union(List L1, List L2)
{
    List Result;
    ElementType InsertElement;
    Position L1Pos, L2Pos, ResultPos;
    L1Pos = First(L1);
    L2Pos = First(L2);
    Result = MakeEmpty(NULL);
    ResultPos = First(Result);
    while (L1Pos != NULL && L2Pos != NULL)
    {
        if (L1Pos->Element < L2Pos->Element)
        {
            InsertElement = L1Pos->Element;
            L1Pos = Next(L1Pos, L1);
        }
        else if (L1Pos->Element > L2Pos->Element)
        {
            InsertElement = L2Pos->Element;
            L2Pos = Next(L2Pos, L2);
        }
        else
        {
            InsertElement = L1Pos->Element;
            L1Pos = Next(L1Pos, L1);
            L2Pos = Next(L2Pos, L2);
        }
        Insert(InsertElement, Result, ResultPos);
        ResultPos = Next(ResultPos, Result);
    }
    /* Flush out remaining list */
    while (L1Pos != NULL)
    {
        Insert(L1Pos->Element, Result, ResultPos);
        L1Pos = Next(L1Pos, L1);
        ResultPos = Next(ResultPos, Result);
    }
    while (L2Pos != NULL)
    {
        Insert(L2Pos->Element, Result, ResultPos);
        L2Pos = Next(L2Pos, L2);
        ResultPos = Next(ResultPos, Result);
    }
    return Result;
