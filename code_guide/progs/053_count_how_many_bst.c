#include "ds.h"

int count_how_many_bst(int n)
{
    if (n < 2)
        return 1;

    // dp[i] 表示有 i 个节点的序列 { 1, 2, 3...i } 可以组成的不同形态二叉树的个数
    // 比如 dp[0] 表示空树，只有一种情况 null
    // 比如 dp[1] 表示有 1 个节点, 二叉树有 1 中形态
    // 比如 dp[2] 表示有 2 个节点时, 二叉树有 2 种形态
    // 比如 dp[3] 表示有 3 个节点时, 那么就有 dp[0] * dp[2] + 左侧空树, 右侧两个节点
    //                                        dp[1] * dp[1] + 左侧一个节点, 右侧一个节点
    //                                        dp[2] * dp[0] + 左侧两个绩点, 右侧空树
    int *dp = malloc(sizeof(int) * (n + 1));
    memset(dp, 0, sizeof(int) * (n + 1));

    // 空树
    dp[0] = 1;

    for (int i = 1; i <= n; i++)  // i 表示有多少个节点
        for (int j = 1; j <= i; j++)  // j 表示选谁当头节点, j = 1 表示选 1 当头, j = 2 表示选 2 当头 
            dp[i] += dp[j - 1] * dp[i - j];
                    // dp[j - 1] 表示选了 j 作为头节点后, 左侧的 j - 1 个节点的二叉树有多少种形态
                    // dp[i - j] 表示选了 j 作为头节点后, 右侧的 i - j 个节点的二叉树有多少种形态 

    int res = dp[n];
    free(dp);
    return res;
}

int main(int argc, char *argv[])
{
    int n = randWithRange(1, 10);
    printf("n = %d, bst count = %d\n", n, count_how_many_bst(n));
}
