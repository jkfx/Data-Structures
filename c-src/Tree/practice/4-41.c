int Similar(Tree T1, Tree T2)
{
    if (T1 == NULL || T2 == NULL)
        return T1 == NULL && T2 == NULL;
    return Similar(T1->Left, T2->Left) && Similar(T1->Right, T2->Right);
}