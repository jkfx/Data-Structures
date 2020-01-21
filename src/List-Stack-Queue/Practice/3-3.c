void SwapWithNext_Singly(Position BeforeP, List L)
{
    Position P, AfterP;

    P = BeforeP->Next;
    AfterP = P->Next;

    P->Next = AfterP->Next;
    BeforeP->Next = AfterP;
    AfterP->Next = P;
}

void SwapWithNext_Double(Position P, List L)
{
    Position BeforeP, AfterP;

    BeforeP = P->Prev;
    AfterP = P->Next;

    P->Next = AfterP->Next;
    BeforeP->Next = AfterP;
    AfterP->Next = P;
    P->Next->Prev = P;
    P->Prev = AfterP;
    AfterP->Prev = BeforeP;
}