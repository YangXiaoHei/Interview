#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int game(int *m, int r, int c)
{
    if (!m || r <= 0 || c <= 0)
        return 0;

    int *dp = malloc(sizeof(int) * r * c);
    if (!dp) exit(1);
    memset(dp, 0, sizeof(int) * r * c);

    dp[(r - 1) * c + c - 1] = m[(r - 1) * c + c - 1] > 0 ? 1 : -m[(r - 1) * c + c - 1] + 1;
    for (int i = c - 2; i >= 0; i--)
        dp[(r - 1) * c + i] = max(dp[(r - 1) * c + i + 1] - m[(r - 1) * c + i], 1);

    for (int i = r - 2; i >= 0; i--)
        dp[i * c + c - 1] = max(dp[(i + 1) * c + c - 1] - m[i * c + c - 1], 1);

    for (int i = r - 2; i >= 0; i--) {
        for (int j = c - 2; j >= 0; j--) {
            int right = max(dp[i * c + j + 1] - m[i * c + j], 1);
            int down = max(dp[(i + 1) * c + j] - m[i * c + j], 1);
            dp[i * c + j] = min(down, right);
        }
    }

    int res = dp[0 * c + 0];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int m[] = { -2, -3, 3, -5, -10, 1, 0, 30, -5 };
    int r = 3, c = 3;
    int res = game(m, r, c);
    printf("%d\n", res);
}
