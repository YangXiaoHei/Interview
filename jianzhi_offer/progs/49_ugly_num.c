#include <stdio.h>

int is_ugly_num(int num)
{
    while (num % 2 == 0)
        num /= 2;
    while (num % 5 == 0)
        num /= 5;
    while (num % 3 == 0)
        num /= 3;
    return num == 1;
}

int ugly_num(int idx)
{
    if (idx <= 0)
        return 1;

    int i = 0;
    int num = 1;
    while (i < idx) 
        if (is_ugly_num(++num)) 
            i++;
    return num;
}

int main(int argc, char *argv[])
{
    printf("%-5d\n", ugly_num(1500));
}
