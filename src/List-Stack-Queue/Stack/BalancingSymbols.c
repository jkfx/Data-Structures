#include <stdio.h>
#include <stdlib.h>
#include "Array/Stack.h"
#include "Array/Stack.c"

int main()
{
    Stack S;
    S = CreateStack(16);
    char* str = "([])";
    Push('(', S);
    printf("%c\n", Top(S));
    system("pause");
    return 0;
}