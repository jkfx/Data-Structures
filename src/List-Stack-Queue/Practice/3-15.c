/**
 * 当一个元素被Find访问时，它就被移到表头而并不改变其余的项的相对顺序
 * 3-15 a.数组实现
 * */
Position Find(ElementType X, List L)
{
    int i, Where;

    Where = 0;
    for (i = 1; i < L.SizeOfList; i++)
    {
        if (X == L[i].Element)
        {
            Where = i;
            break;
        }
        if (Where)
        { /* Move to front */
            for (i = Where; i > 1; i--)
                L[i].Element = L[i - 1].Element;
            L[1].Element = X;
            return 1;
        }
        else
            return 0; /* Not found */
    }
}

/**
 * 当一个元素被Find访问时，它就被移到表头而并不改变其余的项的相对顺序
 * 3-15 a.链表实现
 * */
Position Find(ElementType X, List L)
{
    Position PrevPos, XPos;

    PrevPos = FindPrevious(X, L);
    if (PrevPos->Next != NULL) /* Found */
    {
        XPos = PrevPos->Next;
        PrevPos->Next = XPos->Next;
        XPos->Next = L->Next;
        L->Next = XPos;
        return XPos;
    }
    else
        return NULL;
}