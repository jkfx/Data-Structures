#include <stdio.h>
#define MaxSize 10  // 定义最大长度

typedef struct {
    int data[MaxSize];  // 静态“数组”存放数据元素
    int length; // 顺序表的当前长度
}SqList;    // 顺序表的类型定义

// 基本操作——初始化一个顺序表
void InitList(SqList &L) {
    for (int i=0; i<MaxSize; i++)
        L.data[i] = 0;
    L.length = 0;
}

int main() {
    SqList L;
    InitList(L);
    return 0;
}