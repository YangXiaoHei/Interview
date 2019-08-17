#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int dragon_game(int *map, int r, int c)
{
    if (!map || r <= 0 || c <= 0)
        return 0;

    int *dp = malloc(sizeof(int) * r * c);
    dp[(r - 1) * c + c - 1] = map[(r - 1) * c + c - 1] >= 0 ? 1 : 1 - map[(r - 1) * c + c - 1];
    for (int j = c - 2; j >= 0; j--)
        dp[(r - 1) * c + j] = max(1, dp[(r - 1) * c + j + 1] - map[(r - 1) * c + j]);

    for (int i = r - 2; i >= 0; i--) {
        dp[i * c + c - 1] = max(1, dp[(i + 1) * c + c - 1] - map[i * c + c - 1]);
        for (int j = c - 2; j >= 0; j--) {
            int right = max(1, dp[i * c + j + 1] - map[i * c + j]);
            int down = max(1, dp[(i + 1) * c + j] - map[i * c + j]);
            dp[i * c + j] = min(right, down);
        }
    }

    int res = dp[0 * c + 0];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int m[] = {
        -2, -3, 3,
        -5, -10, 1,
        0, 30, -5
    };
    int r = 3, c = 3;
    printf("%d\n", dragon_game(m, r, c));
}
