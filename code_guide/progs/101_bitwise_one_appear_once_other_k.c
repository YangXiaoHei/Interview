#include "ds.h"

int *gen_arr(int size, int k, int *outsize)
{
    *outsize = (size - 1) * k + 1;
    int *arr = malloc(sizeof(int) * *outsize);
    int j = 0;
    int r = randWithRange(0, size);
    for (int i = 0; i < size; i++) {
        if (r != i) {
            for (int n = 0; n < k; n++) 
                arr[j++] = i;
        } else {
            arr[j++] = i;
        }
    }
    return arr;
}

int appear_once(int *arr, int size, int k)
{
    int res[32] = { 0 };
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 32; j++) {
            res[j] += (arr[i] >> j) & 1;
        }
    }
    int num = 0;
    for (int i = 0; i < 32; i++) 
        num |= (res[i] % k) << i;
    return num;
}

int main()
{
    int size = 10;
    int k = 3;
    int *arr = gen_arr(size, k, &size);
    printArray(arr, size);

    printf("%d\n", appear_once(arr, size, k));
}
