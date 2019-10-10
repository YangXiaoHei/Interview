#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int min_unformed_sum(int *arr, int size)
{
    int *help = malloc(sizeof(int) * size);
    memset(help, 0, sizeof(int) * size);

    help[0] = arr[0];
    for (int i = 1; i < size; i++) {
        help[i] = help[i - 1] + arr[i];
    }
    ht *h = ht_create();

    int sum = 0;
    int minv = 2147483647;
    for (int i = 0; i < size; i++) {
        sum = help[i];
        ht_insert(h, sum, 0);
        minv = min(minv, sum);
        for (int j = 0; j <= i - 1; j++) {
            sum = help[i] - arr[j];
            ht_insert(h, sum, 0);
            minv = min(minv, sum);
        }
    }
    int res = 0;
    for (int i = minv; i <= 2147483647; i++) {
        if (!ht_contain(h, i)) {
            res = i;
            break;
        }
    }
    free(help);
    ht_release(&h);
    return res;
}


int main()
{
    int arr[] = { 3, 2, 5 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int res = min_unformed_sum(arr, size);
    printf("%d\n", res);
}
