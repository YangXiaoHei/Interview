#include "ds.h"

int joseph(int n, int k)
{
    int last = 0;
    for (int i = 2; i <= n; i++)
        last = (last + k) % i;
    return last;
}

int main(int argc, char *argv[])
{
    int *arr = arrayWithRange(5, 1, 10);
    printArray(arr, 5);
    printf("%d\n", arr[joseph(5, 3)]);
}
