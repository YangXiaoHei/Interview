#include "ds.h"

int *gen_arr(int size, int *outsize)
{
    *outsize = size * 2 + 2;
    int r1, r2;
    do {
        r1 = randWithRange(0, size);
        r2 = randWithRange(0, size);
    } while (r1 == r2);

    int *arr = malloc(sizeof(int) * *outsize);
    int k = 0;
    for (int i = 0; i < size; i++) {
        arr[k++] = i;
        arr[k++] = i;
        if (i == r1)
            arr[k++] = i;
        if (i == r2)
            arr[k++] = i;
    }
    return arr;
}

int *appear_odd(int *arr, int size)
{
    int *ret = malloc(sizeof(int) * 2);
    int res = 0;
    for (int i = 0; i < size; i++)
        res ^= arr[i];

    int j;
    for (j = 0; j <= 31; j++) {
        if ((res >> j) & 1)
            break;
    }

    int res1 = 0, res2 = 0;
    for (int i = 0; i < size; i++) {
        if ((arr[i] >> j) & 1) {
            res1 ^= arr[i];
        } else {
            res2 ^= arr[i];
        }
    }
    ret[0] = res1;
    ret[1] = res2;
    return ret;
}

int main()
{
    int size = 10;
    int *arr = gen_arr(size, &size);
    printArray(arr, size);

    int *res = appear_odd(arr, size);
    printf("%d %d\n", res[0], res[1]);
}
