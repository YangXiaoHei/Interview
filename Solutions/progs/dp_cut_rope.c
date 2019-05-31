#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

char record[1 << 10];

long cut_rope(int len)
{
    if (len < 0) return 0;

    long *dp = malloc(sizeof(long) * len);
    if (!dp) exit(1);
    
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 4;
    dp[5] = 6;

    long rel = 0;
    if (len < 6) {
        rel = dp[len];
        goto end;
    }
            
    for (int i = 6; i <= len; i++) {
        for (int j = 1; j <= i / 2; j++) {
            if (dp[i - j] * dp[j] > rel)
                rel = dp[i - j] * dp[j];
        }
        dp[i] = rel;
    }
end:
    free(dp);
    return rel;
}

int main(int argc, char *argv[])
{
    int r = randWithRange(10, 50);
    printf("r = %d, %ld\n", r, cut_rope(r));
}
