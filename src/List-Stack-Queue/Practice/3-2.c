void PrintLos(List L, List P)
{
    int Counter;
    Position Lpos, Ppos;
    Lpos = First(L);
    Ppos = First(P);
    Counter = 1;
    while (Lpos != NULL && Ppos != NULL)
    {
        if (Ppos->Element == Counter++)
        {
            printf("%?", Lpos->Element);
            Ppos = Next(Ppos, P);
        }
        Lpos = Next(Lpos, L);
    }
}