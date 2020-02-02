#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int i, j, k;
    char *str1 = "asdjkfxqwe";
    char *str2 = "jkfx";
    char str3[100] = "";
    for (i = 0; i < strlen(str1) - strlen(str2) + 1; i++)
    {
        k = 0;
        for (j = i; j < strlen(str2) + i; j++)
        {
            str3[k++] = str1[j];
        }
        printf("str2: %d\n",Hash(str2,100));
        printf("str3: %d\n\n",Hash(str3,100));
    }
    system("pause");
    return 0;
}