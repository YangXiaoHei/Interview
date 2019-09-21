#include "ds.h"

int maxheap(long a, long b)
{
    int t = a == b ? 0 : a > b ? 1 : -1;
    return -t;
}

void min_k(int *arr, int size, int k)
{
    heap *h = heap_create_(maxheap);
    for (int i = 0; i < k; i++) 
        heap_insert(h, arr[i]);

    for (int i = k; i < size; i++) {
        int val = arr[i];
        if (val >= heap_peek(h))
            continue;

        heap_pop(h);
        heap_insert(h, arr[i]);
    }
    
    while (!heap_empty(h))
        printf("%-3d", heap_pop(h));
    printf("\n");

    heap_release(&h);
}

int main()
{
    int size = 20;
    int *arr = arrayWithRange(size, 0, 10);
    printArray(arr, size);
    min_k(arr, size, 5);
}
