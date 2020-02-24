/**
 * 三连游戏棋(tic-tac-toe)
 *  极大极小策略
 *  α-β剪裁
 * 2020-2-23 18:53
 * 输了 彻底的输了 无所事事 根本学不进去 还找各种借口
 * 还博弈 还 alpha-beta 剪裁
 * 我呸 吊毛都学不会 还蓝桥杯
 * 还为了省一、那300块钱报名费 都是屁
 * 吃屁吧 mother fucker, son of bitch
 * */
#include <stdio.h>
#include <stdlib.h>

/**
 * 枚举类型
 *  定义形式:
 *      enum typeName {valueName1, valueName2, ... };
 *  例如: 列出一个星期的几天
 *      enum week {Mon, Tues, Wed, Thurs, Fri, Sat, Sun};
 *  默认从 0 开始，也可以为每一个枚举名指定要给值
 *      enum week {Mon = 1, Tues = 2, Wed = 3, Thurs = 4, Fri = 5, Sat = 6, Sun = 7 };
 *  也可以只给第一个名字指定一个值
 *      enum week {Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun};
 *      这样枚举值就从 1 开始递增
 *  枚举是一种类型，通过它可以定义枚举变量:
 *      enum week a, b, c;
 *  也可以在定义枚举类型的同时定义变量
 *      enum week {Mon, Tues, Wed, Thurs, Fri, Sat, Sun} a, b, c;
 *  有了枚举变量，就可以把列表中的值赋给它:
 *      enum week a = Mon, b = Wed, c = Sat;
 * */
enum Board_Sign
{
    Empty,    // 空位置(0)
    Comp,     // 计算机的棋(1)
    Human,    // 人的棋(2)
    CompLoss, // 计算机输(3)
    Draw,     // 平局(4)
    CompWin   // 计算机胜利(5)
};

typedef int BoardType[10];

int FullBoard(BoardType Board)
{
    int i;

    for (i = 1; i <= 9; i++)
        if (Board[i] == Empty)
            return 0;
    return 1;
}

void Place(BoardType Board, int i, int sign)
{
    if (Board[i] == Empty)
        Board[i] = sign;
}

void Unplace(BoardType Board, int i)
{
    Board[i] = Empty;
}

/* 判断在棋盘 i 的位置放完棋后传入参数是否胜利 */
int ImmediateWin(BoardType Board, int i, int sign)
{
    int column, row, dia;
    int status;

    Place(Board, i, sign);

    column = i % 3; // 获取位置 i 所在列
    /* 判断所在行是否胜利 */
    switch (column)
    {
    case 0:
        status = Board[3] == Board[6] && Board[6] == Board[9] && Board[9] == sign;
        break;
    case 1:
        status = Board[1] == Board[4] && Board[4] == Board[7] && Board[7] == sign;
        break;
    case 2:
        status = Board[2] == Board[5] && Board[5] == Board[8] && Board[8] == sign;
        break;
    }

    row = (i * 3) % 10 % 3; // 获取位置 i 所在列
    /* 判断所在列是否胜利 */
    if (status == 0)
        switch (row)
        {
        case 0:
            status = Board[1] == Board[2] && Board[2] == Board[3] && Board[3] == sign;
            break;
        case 1:
            status = Board[4] == Board[5] && Board[5] == Board[6] && Board[6] == sign;
            break;
        case 2:
            status = Board[7] == Board[8] && Board[8] == Board[9] && Board[9] == sign;
            break;
        }

    dia = abs(i - 5); // 获取是否为对角线位置
    /* 判断对角线是否胜利 */
    if (status == 0)
    {
        switch (dia)
        {
        case 2:
            status = Board[3] == Board[5] && Board[5] == Board[7] && Board[7] == sign;
            break;
        case 4:
            status = Board[1] == Board[5] && Board[5] == Board[9] && Board[9] == sign;
            break;
        }
    }

    Unplace(Board, i);

    return status;
}

/* 判断在棋盘 i 的位置放完棋后计算机是否胜利 */
int ImmediateCompWin(BoardType Board, int i)
{
    return ImmediateWin(Board, i, Comp);
}

/* 判断在棋盘 i 的位置放完棋后人类是否胜利 */
int ImmediateHumanWin(BoardType Board, int i)
{
    return ImmediateWin(Board, i, Human);
}

int IsEmpty(BoardType Board, int i)
{
    return Board[i] == Empty;
}

void PrintBoard(BoardType Board)
{
    int i;

    for (i = 1; i <= 9; i++)
    {
        switch (Board[i])
        {
        case Comp:
            printf(" O ");
            break;
        case Human:
            printf(" X ");
            break;
        case Empty:
            printf("   ");
            break;
        }
        if (i % 3 == 0)
            printf("\n");
    }
}

/**
 * Recursive procedure to find best move for computer
 * BestMove points to a number from 1 to 9 indicating(指示)
 * square Possible evalueations satisfy(满足) CompLoss < Draw < CompWin
 * Complementary(互补的) procedure FindHumanMove, Board is an array and
 * thus can be changed by Place
 * */
void FindHumanMove(BoardType Board, int *BestMove, int *Value);
void FindCompMove(BoardType Board, int *BestMove, int *Value);
void FindCompMove(BoardType Board, int *BestMove, int *Value)
{
    int Dc, i, Response;

    if (FullBoard(Board))
        *Value = Draw;
    else if (ImmediateCompWin(Board, *BestMove))
        *Value = CompWin;
    else
    {
        *Value = CompLoss;
        for (i = 1; i <= 9; i++)
        {
            if (IsEmpty(Board, i))
            {
                Place(Board, i, Comp);

                for (Dc = 1; Dc <= 9; Dc++)
                    if (IsEmpty(Board, Dc))
                        break;
                FindHumanMove(Board, &Dc, &Response);
                Unplace(Board, i); /* Restore Board */

                if (Response > *Value)
                {
                    /* Update best move */
                    *Value = Response;
                    *BestMove = i;
                }
            }
        }
    }
    //printf("BCompMove: %d, %d\n", *BestMove, *Value);
}

void FindHumanMove(BoardType Board, int *BestMove, int *Value)
{
    int Dc, i, Response;

    if (FullBoard(Board))
        *Value = Draw;
    else if (ImmediateHumanWin(Board, *BestMove))
        *Value = CompLoss;
    else
    {
        *Value = CompWin;
        for (i = 1; i <= 9; i++)
        {
            if (IsEmpty(Board, i))
            {
                Place(Board, i, Human);

                for (Dc = 1; Dc <= 9; Dc++)
                    if (IsEmpty(Board, Dc))
                        break;
                FindCompMove(Board, &Dc, &Response);
                Unplace(Board, i); /* Restore Board */

                if (Response < *Value)
                {
                    /* Update best move */
                    *Value = Response;
                    *BestMove = i;
                }
            }
        }
    }
    //printf("BHumanMove: %d, %d\n", *BestMove, *Value);
}

int main()
{
    BoardType Board = {Empty};
    int i;
    int BestMove, Value;

    while (1)
    {
        system("cls");
        PrintBoard(Board);
        scanf("%d", &i);
        Place(Board, i, Human);

        for (BestMove = 1; BestMove <= 9; BestMove++)
            if (IsEmpty(Board, BestMove))
                break;

        FindCompMove(Board, &BestMove, &Value);
        Place(Board, BestMove, Comp);
    }

    system("pause");
    return 0;
}