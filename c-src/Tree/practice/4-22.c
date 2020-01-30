Position DoubleRotateWithLeft(Position K3)
{
    Position K1, K2;

    K1 = K3->Left;
    K2 = K1->Right;

    K3->Left = K2;
    K1->Right = K2->Left;
    K2->Left = K1;
    K3->Left = K2->Right;
    K2->Right = K3;

    K1->Height = Max(Height(K1->Left),Height(K1->Right) + 1);
    K3->Height = Max(Height(K3->Left),Height(K3->Right) + 1);
    K2->Height = Max(Height(K2->Left),Height(K2->Right) + 1);

    return K2;
}