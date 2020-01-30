/**
 * 只使用指向二叉树的根额一个指针T，并计算：
 * (a). T 中节点的个数
 * (b). T 中树叶的片数
 * (c). T 中满节点的个数
 * */

/* (a). T 中节点的个数 */
int CountNodes(BinaryTree T)
{
    if (T == NULL)
        return 0;
    return 1 + CountNodes(T->Left) + CountNodes(T->Right);
}

/* (b). T 中树叶的片数 */
int CountLeaves(BinaryTree T)
{
    if (T == NULL)
        return 0;
    else if (T->Left == NULL && T->Right == NULL)
        return 1;
    return CountLeaves(T->Left) + CountLeaves(T->Right);
}

/**
 * (c). T 中满节点的个数
 * 也可以使用一个结论：
 *  满节点的个数加1等于非空二叉树的树叶的个数
 * */
int CountFull(BinaryTree T)
{
    if (T == NULL)
        return 0;
    return (T->Left != NULL && T->Right != NULL) + CountFull(T->Left) + CountFull(T->Right);
}