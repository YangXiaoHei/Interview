#include "ds.h"

long normal_hash(long key)
{
    return key;
}

int longest_sequence_of_sum(int *arr, int size, int key)
{
    if (!arr || size <= 0)
        return 0;
    ht *h = ht_create(normal_hash);    
    ht_insert(h, 0, -1);

    stack *s = stack_create();

    int sum = 0;
    int len = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        if (ht_contain(h, sum - key)) {
            int idx = ht_get(h, sum - key);
            if (i - idx > len) {
                len = i - idx;

                stack_clear(s);
                for (int k = idx + 1; k <= i; k++)
                    stack_push(s, arr[k]);
            }
        }
        if (!ht_contain(h, sum))
            ht_insert(h, sum, i);
    }
    printf("sequence : ");
    stack_print_r(s);
    return len;
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, -10, 10);
    printArray(arr, size);
    int k = randWithRange(0, 15);
    printf("k = %d\n", k);
    printf("len = %d\n", longest_sequence_of_sum(arr, size, k));
}
