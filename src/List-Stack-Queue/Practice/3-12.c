List ReverseList(List L)
{
    Position CurrentPos, NextPos, PreviousPos;

    PreviousPos = NULL;
    CurrentPos = L;
    NextPos = L->Next;
    while(NextPos != NULL)
    {
        CurrentPos->Next = PreviousPos;
        PreviousPos = CurrentPos;
        CurrentPos = NextPos;
        NextPos = NextPos->Next;
    }
    CurrentPos->Next = PreviousPos;
    return CurrentPos;
}