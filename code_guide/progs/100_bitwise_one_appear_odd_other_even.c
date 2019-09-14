#include "ds.h"

int *gen_arr(int insize, int *outsize)
{
    *outsize = insize * 2 + 1; 
    int *arr = malloc(sizeof(int) * *outsize);
    int r = randWithRange(0, insize);
    int k = 0;
    for (int i = 0; i < insize; i++) {
        arr[k++] = i; 
        arr[k++] = i; 
        if (i == r)
            arr[k++] = i;
    }
    return arr;
}

int appear_odd(int *arr, int size)
{
    int res = 0;
    for (int i = 0; i < size; i++)
        res ^= arr[i];
    return res;
}

int main()
{
    int size = 10;
    int *arr = gen_arr(size, &size); 
    printArray(arr, size);

    printf("res = %d\n", appear_odd(arr, size));
}
