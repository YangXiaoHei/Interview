#include "ds.h"

int longest_sequence_of_sum(int *arr, int size, int k)
{
    stack *s = stack_create();

    int l = 0, h = 0;
    int sum = 0;
    int len = 0;

    while (h < size) {
        if (sum < k) {
            sum += arr[h++];
            if (h >= size)
                break;
        } else if (sum == k) {
            if (h - l > len) {
                len = h - l;
                stack_clear(s);
                for (int i = l; i < h; i++)
                    stack_push(s, arr[i]);
            }
            sum -= arr[l++];
        } else {
            sum -= arr[l++];
        }
    }

    printf("sequence : ");
    stack_print(s);
    stack_release(&s);
    return len;
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 0, 10);
    int k = randWithRange(1, 30);
    printf("k = %-3d\n", k);
    printArray(arr, size);
    printf("len = %d\n", longest_sequence_of_sum(arr, size, k));
}
