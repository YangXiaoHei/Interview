#include "ds.h"

int probability(double p)
{
    int full_interval = 1000000; /* 1 ~ full_interval */
    int happen_interval = p * full_interval; 
    int r = (rand() % full_interval + 1);
    return r <= happen_interval;
}

int* sampling(int k, int N)
{
    int *res = malloc(sizeof(int) * k);
    memset(res, 0, sizeof(int) * k);

    int idx = 0;
    for (int i = 1; i <= k; i++) {
        res[idx++] = i;
    }

    for (int i = k + 1; i <= N; i++) {
        if (probability(k * 1.0 / i)) {
            int r = rand() % k;
            res[r] = i;
        }
    }
    return res;
}

void test(int times, int k, int N)
{
    int *stat = malloc(sizeof(int) * (N + 1));
    memset(stat, 0, sizeof(int) * (N + 1));
    for (int i = 0; i < times; i++) {
        int *res = sampling(k, N); 
        for (int j = 0; j < k; j++) {
            stat[res[j]]++;
        }
        free(res);
    }
    printf("standard : %.4f\n", k * 1.0 / N);
    for (int i = 1; i <= N; i++) {
        printf("%-3d(%-4.4f)  ", i, stat[i] * 1.0 / times);
        if (i % 10 == 0)
            printf("\n");
    }
}

int main()
{
    test(100000, 5, 1000); 
}
