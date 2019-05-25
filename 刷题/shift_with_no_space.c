#include <stdio.h>
#include <stdlib.h>

void shift_one(int *input, int len)
{
    int tmp = input[len - 1];
    for (int i = len - 1; i > 0; i--)
        input[i] = input[i - 1];
    input[0] = tmp;
}

void shift(int *input, int len, int dist)
{
    if (!input || len <= 0 || dist < 0 || dist % len == 0)
        return;
    dist %= len;
    while (dist--) 
        shift_one(input, len);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage : %s <shift>\n", argv[0]);
        exit(1);
    }
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    shift(a, 7, atoi(argv[1]));

    for (int i = 0; i < 7; i++)
        printf("%2d", a[i]);

    printf("\n");
}
