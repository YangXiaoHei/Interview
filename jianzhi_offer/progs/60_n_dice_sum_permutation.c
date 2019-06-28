#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIDES 6

void n_dice_num_core(int orignal, int dice_idx, int sum, int *arr)
{
    if (dice_idx == 1) {
        arr[sum - orignal]++;
        return;
    }

    for (int i = 1; i <= SIDES; i++)
        n_dice_num_core(orignal, dice_idx - 1, sum + i, arr);
}

void n_dice_sum(int n)
{
    int *arr = malloc(sizeof(int) * (SIDES * n - n + 1));
    if (!arr) exit(1);

    memset(arr, 0, sizeof(int) * (SIDES * n - n + 1));

    for (int i = 1; i <= SIDES; i++)
        n_dice_num_core(n, n, i, arr);

    int total_times = 0;
    for (int i = 0; i < SIDES * n - n + 1; i++)
        total_times += arr[i];

    for (int i = 0; i < SIDES * n - n + 1; i++)
        printf("%-3d occur %3.3f %%\n", i + n, arr[i] * 1.0 / total_times * 100);

    free(arr);
}



int main(int argc, char *argv[])
{
    n_dice_sum(6);
}
