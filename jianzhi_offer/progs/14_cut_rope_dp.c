#include <stdio.h>
#include <stdlib.h>

long cut_rope(int len)
{
    if (len <= 0) return 0;

    long *dp = malloc(sizeof(long) * (len + 1));
    if (!dp) exit(1);
    
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 2;

    long rel = 0;
    if (len < 4) {
        rel = dp[len];
        goto end;
    }
            
    for (int i = 4; i <= len; i++) {
        for (int j = 1; j <= i / 2; j++) 
            if (dp[i - j] * dp[j] > rel)
                rel = dp[i - j] * dp[j];
        dp[i] = rel;
    }
end:
    free(dp);
    return rel;
}

int main(int argc, char *argv[])
{
    for (int r = 4; r < 20; r++)
        printf("r = %d, %ld\n", r, cut_rope(r));
}
