#include <stdio.h>
#include <stdlib.h>

#define SIDES 6

void n_dice_sum(int n)
{
    int **dp = malloc(sizeof(int *) * (n + 1));
    for (int i = 0; i < n + 1; i++) {
        dp[i] = malloc(sizeof(int) * (SIDES * n + 1)); 
        for (int j = 0; j < SIDES * n + 1; j++)
            dp[i][j] = 0;
    }

    dp[1][6] = dp[1][5] = dp[1][4] = dp[1][3] = dp[1][2] = dp[1][1] = 1; 

    for (int i = 2; i <= n; i++) 
        for (int j = i; j <= SIDES * i; j++) 
            for (int k = 1; k <= 6 && j - k >= 1; k++)
                dp[i][j] += dp[i - 1][j - k];

    int total_times = 0;
    for (int i = n; i <= SIDES * n; i++)
        total_times += dp[n][i];

    for (int i = n; i <= SIDES * n; i++)
        printf("%-3d occur %-3.3f %%\n", i, dp[n][i] * 1.0 / total_times * 100);

#ifdef DEBUG
    for (int i = 0; i <= n; i++)  {
        for (int j = 0; j <= SIDES * n; j++) 
            printf("%-3d", dp[i][j]);
        printf("\n");
    }
#endif

    for (int i = 0; i < n; i++)
        free(dp[i]);
    free(dp);
}

int main(int argc, char *argv[])
{
    n_dice_sum(6);
}
