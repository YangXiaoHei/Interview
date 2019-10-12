#include "ds.h"

void kdigit_core(int N, int k)
{
    if (N < k) {
        printf("%d", N);
        return;
    }
    int r = N % k;
    kdigit_core(N / k, k);
    printf("%d", r);
}

void kdigit(int N, int k)
{
    kdigit_core(N, k);
    printf("\n");
}

int main()
{
    kdigit(72, 3);
    kdigit(72, 4);
    kdigit(72, 5);
}
