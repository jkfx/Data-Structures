#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    Linked,
    Thread
} PointerTag;

typedef int ElementType;
struct ThreadTree;
typedef struct ThreadTree *Tree;
typedef struct ThreadTree *Position;
struct ThreadTree
{
    ElementType Element;
    Tree Left;
    Tree Right;
    PointerTag LTag;
    PointerTag RTag;
};

Tree pre; // 头结点声明

void PrintElement(Tree T)
{
    printf("%d ", T->Element);
}

/**
 * 以结点 p 为根的子树中序线索化
 * 1. 如果 p 非空，左子树递归线索化
 * 2. 如果 p 的左孩子为空，则给 p 加上左线索，将其 Ltag 置为 1，让 p 的左孩子指针指向 pre（前驱）；否则将 p 的 LTag 置为 0 。
 * 3. 如果 pre 的右孩子为空，则给 pre 加上右线索，将其 RTag 置为 1，让 pre 的右孩子指针指向 p（后继）；否则将 pre 的 RTag 置为 0 。
 * 4. 将 pre 指向刚访问过的结点 p，即 pre = p 。
 * 5. 右子树递归线索化。
 * */
void InThreading(Tree p)
{
    // pre 是全局变量，初始化时右孩子指针为空，便于在树的最左点开始建立线索
    if (p != NULL)
    {
        InThreading(p->Left);
        if (p->Left == NULL)
        {
            p->LTag = Thread;
            p->Left = pre;
        }
        else
            p->LTag = Linked;
        if (pre->Right == NULL)
        {
            pre->RTag = Thread;
            pre->Right = p;
        }
        else
            p->RTag = Linked;
        pre = p;
        InThreading(p->Right);
    }
}

void InOrderThreading(Tree *Thrt, Tree T)
{
    // 中序遍历二叉树 T，并将其中序线索化，Thrt 指向头结点
    (*Thrt) = (Tree)malloc(sizeof(struct ThreadTree)); // 建立头结点
    (*Thrt)->LTag = Linked;                            // 头结点有左孩子，如树为空，则其左孩子为树根
    (*Thrt)->RTag = Thread;                            // 头结点的右孩子指针为右线索
    (*Thrt)->Right = (*Thrt);
    if (!T)
        (*Thrt)->Left = (*Thrt); // 若树为空，则作指针也指向自己
    else
    {
        (*Thrt)->Left = T;
        pre = (*Thrt);
        InThreading(T);       //中序线索化
        pre->Right = (*Thrt); // pre 为最右结点，pre 的右线索指向头结点
        pre->RTag = Thread;
        (*Thrt)->Right = pre;
    }
}

/**
 * 遍历线索二叉树
 * 1. 指针 p 指向根节点。
 * 2. p 为非空树或遍历未结束时，循环执行以下操作：
 *  - 沿着左孩子向下，到达最左下结点 *p，它是中序的第一个结点；
 *  - 访问 *p
 *  - 沿着右线索反复查找当前结点 *p 的后继结点并访问后继结点，直至右线索为 0 或者遍历结束
 *  - 转向 p 的右子树
 * 时间复杂度：O(N)
 * 空间复杂度：O(1)
 * 因为没有使用栈实现递归操作
 * */
void InOrderTraverse_Thr(Tree T)
{
    // T 指向头结点，头结点的左孩子 Left 指向根结点
    // 中序遍历二叉线索树 T 的非递归算法，对数据元素直接输出
    Tree p;
    p = T->Left;
    while (p != T) // 空树或遍历结束时， p == T
    {
        while (p->LTag == Linked)
            p = p->Left; // 沿着左孩子向下
        PrintElement(p); // 访问其左子树为空的结点
        while (p->RTag == Thread && p->Right != T)
        {
            p = p->Right;
            PrintElement(p);
        }
        p = p->Right;
    }
}

Position Insert(ElementType X, Tree T)
{
    if (T == NULL)
    {
        T = (Tree)malloc(sizeof(struct ThreadTree));
        T->Element = X;
        T->Left = T->Right = NULL;
        T->LTag = T->RTag = Linked;
    }
    else if (X < T->Element)
        T->Left = Insert(X, T->Left);
    else if (X > T->Element)
        T->Right = Insert(X, T->Right);
    return T;
}

int main()
{
    Tree T;    // 树的根节点
    Tree Thrt; // 树的头结点
    T = NULL;
    T = Insert(3, T);
    T = Insert(1, T);
    T = Insert(4, T);
    T = Insert(5, T);
    T = Insert(9, T);
    InOrderThreading(&Thrt, T);
    InOrderTraverse_Thr(Thrt);
    printf("\n");
    system("pause");
    return 0;
}