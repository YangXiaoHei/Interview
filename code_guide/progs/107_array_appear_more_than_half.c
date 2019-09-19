#include "ds.h"

int *gen_arr(int size) 
{
    int *arr = malloc(sizeof(int) * size);
    int count = size / 2 + 1;
    int extra = randWithRange(0, size - count + 1);
    int total = count + extra;

    int r = randWithRange(0, size);
    for (int i = 0; i < total; i++) {
        arr[i] = r; 
    }
    for (int i = total; i < size; i++) {
        arr[i] = randWithRange(r, size * 2);
    }
    shuffle(arr, size);
    return arr;
}

int appear_more_than_half(int *arr, int size)
{
    if (!arr || size <= 0)
        return -1;
    
    int times = 0;
    int cand = 0;
    for (int i = 0; i < size; i++) {
        if (times == 0) {
            cand = arr[i];
            times = 1;
        } else if (arr[i] == cand) {
            times++;
        } else {
            times--;
        }
    }
    times = 0;
    for (int i = 0; i < size; i++) {
        if (cand == arr[i])
            times++;
    }

    if (times > size / 2) {
        printf("number is %d\n", cand);
    } else {
        printf("no such number\n");
    }
    return cand;
}

int main()
{
    int size = 20;
    int *arr = gen_arr(size);
    printArray(arr, size);
    appear_more_than_half(arr, size);
}
