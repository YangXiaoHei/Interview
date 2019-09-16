#include "ds.h"

int maxheap(long a, long b)
{
    int minheap = a == b ? 0 : (a > b ? 1 : -1);
    return -minheap;
}

int *min_k(int *arr, int size, int k)
{
    if (k >= size)
        return NULL;

    heap *h = heap_create_(maxheap);

    int *res = malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) 
        heap_insert(h, arr[i]);

    for (int i = k; i < size; i++) {
        int t = arr[i];
        if (t > heap_peek(h))
            continue;

        heap_pop(h);
        heap_insert(h, arr[i]);
    }

    int i = 0;
    while (!heap_empty(h))
        res[i++] = heap_pop(h);

    heap_release(&h);
    return res;
}

int main()
{
    int size = 100;
    int k = 10;
    int *arr = array(size);
    shuffle(arr, size);
    printArray(arr, size);
    printArray(min_k(arr, size, k), k);
}
