#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define INFINITY (999999999)
struct ListCell
{
    ElementType dist;
    List next;
};
typedef List DistSet;

DistSet CreateList(void)
{
    DistSet D;
    D = malloc(sizeof(struct ListCell));
    D->dist = 0;
    D->next = NULL;
    return D;
}

int IsEmpty(DistSet D)
{
    return D->next == NULL;
}

Position FindPre(Position p, DistSet D)
{
    Position pre;

    if (IsEmpty(D))
        return NULL;

    pre = D;

    while (pre->next != p)
        pre = pre->next;

    return pre;
}

ElementType DeleteMax(DistSet D)
{
    Position p, max_p;
    ElementType max;

    if (IsEmpty(D))
        return -INFINITY;

    p = D->next;
    max_p = NULL;
    max = -INFINITY;

    while (p != NULL)
    {
        if (p->dist > max)
        {
            max = p->dist;
            max_p = p;
        }
        p = p->next;
    }

    p = FindPre(max_p, D);
    p->next = max_p->next;
    free(max_p);
    D->dist--;

    return max;
}

void Remove(ElementType dist, DistSet D)
{
    Position p, pre;

    if (IsEmpty(D))
        return;

    p = D->next;
    while (p != NULL)
    {
        if (p->dist == dist)
            break;
        p = p->next;
    }

    pre = FindPre(p, D);
    pre->next = p->next;
    free(p);
    D->dist--;
}

ElementType FindMax(DistSet D)
{
    Position p;
    ElementType max;

    if (IsEmpty(D))
        return -INFINITY;

    p = D->next;
    max = -INFINITY;

    while (p != NULL)
    {
        if (p->dist > max)
            max = p->dist;
        p = p->next;
    }

    return max;
}

int IsBloneTo(ElementType dist, DistSet D)
{
    Position p;

    if (IsEmpty(D))
        return 0;

    p = D->next;
    while (p != NULL)
    {
        if (p->dist == dist)
            return 1;
        p = p->next;
    }

    return 0;
}

void Delete(ElementType dist, DistSet D)
{
    Remove(dist, D);
}

/* 头插法(这将丢失集合中的有序性) */
void Insert(ElementType dist, DistSet D)
{
    Position p, tmp;

    p = CreateList();
    p->dist = dist;
    tmp = D->next;
    D->next = p;
    p->next = tmp;
    D->dist++;
}

void PrintList(List L)
{
    Position p;

    p = L->next;

    while (p != NULL)
    {
        printf("%d ", p->dist);
        p = p->next;
    }
    printf("\n");
}

void PrintArray(int a[], int n)
{
    int i;

    for (i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

DistSet ArrayToDistSet(int *a, int n)
{
    int i;
    DistSet D;

    D = CreateList();

    for (i = 0; i < n; i++)
        Insert(a[i], D);

    return D;
}

void MergeDistSet(DistSet F, DistSet T)
{
    Position p;

    p = F->next;
    while (p != NULL)
    {
        Insert(p->dist, T);
        p = p->next;
    }
}

void MakeEmpty(DistSet D)
{
    Position p, tmp;

    p = D->next;
    while (p != NULL)
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
    D->dist = 0;
    D->next = NULL;
}

/**
 * 收费公路重建算法
 * int Turnpike(int X[], DistSet D, int N);
 *  驱动例程
 * int Place(int X[], DistSet D, int N, itn Left, int Right);
 *  回溯
 * */
int Place(int X[], DistSet D, int N, int Left, int Right);
int Turnpike(int X[], DistSet D, int N)
{
    X[1] = 0;
    X[N] = DeleteMax(D);
    X[N - 1] = DeleteMax(D);
    if (IsBloneTo(X[N] - X[N - 1], D))
    {
        Remove(X[N] - X[N - 1], D);
        return Place(X, D, N, 2, N - 2);
    }
    else
        return 0; // False
}

int Place(int X[], DistSet D, int N, int Left, int Right)
{
    int DMax, Found = 0; // False
    int i, flag;
    DistSet Del;
    printf("Array: ");
    PrintArray(X, N);
    printf("DistSet: ");
    PrintList(D);
    printf("\n");

    if (IsEmpty(D))
        return 1; // True

    Del = CreateList();
    DMax = FindMax(D);
    /* Check if setting X[Right] = DMax is feasible. */
    X[Right] = DMax;
    for (i = 1; i <= N; i++)
        if ((i >= 1 && i < Left) || (i > Right && i <= N))
        {
            if (IsBloneTo(abs(X[i] - DMax), D))
            {
                flag = 1;
                Delete(abs(X[i] - DMax), D);
                Insert(abs(X[i] - DMax), Del);
            }
            else
            {
                flag = 0;
                break;
            }
        }
    if (flag == 1)
        Found = Place(X, D, N, Left, Right - 1);

    /**
     * If first attempt failed, try to see if setting
     * X[Left] = X[N] - DMax is feasible.
     * */
    if (Found == 0)
    {
        MergeDistSet(Del, D);
        MakeEmpty(Del);
        X[Left] = X[N] - DMax;
        for (i = 1; i <= N; i++)
            if ((i >= 1 && i < Left) || (i > Right && i <= N))
            {
                if (IsBloneTo(abs(X[N] - DMax - X[i]), D))
                {
                    flag = 1;
                    Delete(abs(X[N] - DMax - X[i]), D);
                    Insert(abs(X[N] - DMax - X[i]), Del);
                }
                else
                {
                    flag = 0;
                    break;
                }
            }
        if (flag == 1)
            Found = Place(X, D, N, Left + 1, Right);
        if (Found == 0)
        {
            MergeDistSet(Del, D);
            MakeEmpty(Del);
        }
    }

    return Found;
}

int main()
{
    int a[15] = {1, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 10};
    int X[7] = {0};
    DistSet D;

    D = ArrayToDistSet(a, 15);

    printf("{1, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 10}\n");
    Turnpike(X, D, 6);

    system("pause");
    return 0;
}