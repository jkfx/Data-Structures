#include <stdio.h>
#include <stdlib.h>

typedef unsigned int Index;

Index Hash(const char *Key, int TableSize)
{
    unsigned int HashVal = 0;
    while (*Key != '\0')
        HashVal = (HashVal << 5) + *Key++;
    return HashVal % TableSize;
}

int main()
{
    printf("%d\n", Hash("jkfx",100));
    printf("%d\n", Hash("fxjk",100));
    printf("%d\n", Hash("pause",100));
    printf("%d\n", Hash("hash",100));
    printf("%d\n", Hash("a", 100));
    system("pause");
    return 0;
}