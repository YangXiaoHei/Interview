#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tool.h"

int poker[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
int poker_size = sizeof(poker) / sizeof(poker[0]);

void shuffle(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        int r = i + randWithRange(0, size - i);
        swap(arr + i, arr + r);
    }
}

int *gen_arr(int n)
{
    int *random = malloc(sizeof(int) * n);
    shuffle(poker, poker_size);
    for (int i = 0; i < n; i++)
        random[i] = poker[i];
    return random;
}

int is_poker_seq(int *arr, int size)
{
    if (!arr || size < 5)
        return 0;

    tool_sort(arr, size);
    printArray(arr, size);

    int zero = 0;
    for (int i = 0; i < size && arr[i] == 0; i++)
        zero++;

    int gap = 0;
    int tmp = 0;
    for (int i = zero + 1; i < size; i++) {
        if (arr[i] == arr[i - 1])
            return 0;
        
        tmp = arr[i] - arr[i - 1] - 1;
        gap += tmp > 0 ? tmp : 0;
    }
    printf("gap=%d zero=%d\n", gap, zero);

    return zero >= gap;
}

int main(int argc, char *argv[])
{
    int n = 5;
    int *random = gen_arr(n);
    printf("is seq ? %d\n", is_poker_seq(random, n));
}
