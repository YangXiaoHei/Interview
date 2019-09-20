#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int max_length(int *arr, int size, int key)
{
    int len = 0;
    int sum = 0;
    ht *h = ht_create();
    ht_insert(h, 0, -1);
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        if (ht_contain(h, sum - key)) 
            len = max(len, i - ht_get(h, sum - key));

        if (!ht_contain(h, sum)) 
            ht_insert(h, sum, i);
    } 
    ht_release(&h);

    /* for debug */
    int tmp = 0;
    for (int i = 0; i < size; i++) {
        tmp = 0;
        for (int j = 0; j < len; j++) {
            tmp += arr[j + i];
        }
        if (tmp == key) {
            for (int j = 0; j < len; j++) {
                printf("%-3d", arr[j + i]);
            }
            printf("\n");
        }
    }

    return len;
}

int main()
{
    int size = 10;
    int *arr = arrayWithRange(size, -10, 10);
    printArray(arr, size);

    int key = randWithRange(0, 15);
    printf("key=%d\n", key);

    printf("len=%d\n", max_length(arr, size, key));
}
