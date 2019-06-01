#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shift(int *input, int len, int dist)
{
    if (!input || len <= 0 || dist < 0 || dist % len == 0)
        return;

    dist %= len;
    int i = 0, j = len - 1;
    while (i < j) 
        swap(&input[i++], &input[j--]);

    i = 0; j = dist - 1;
    while (i < j)
        swap(&input[i++], &input[j--]);

    i = dist; j = len - 1;
    while (i < j)
        swap(&input[i++], &input[j--]);
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
