#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

typedef int val_type;
typedef int (*comparator)(val_type, val_type);
const int heap_min_cap = 11;

typedef struct heap {
    int size;
    int cap;
    val_type *data;
    comparator cmp;
} heap;

heap *heap_create(comparator cmp)
{
    heap *h = malloc(sizeof(heap));
    if (!h) exit(1);
    h->size = 0;
    h->cap = heap_min_cap;
    h->data = malloc(sizeof(val_type) * h->cap);
    if (!h->data) exit(1);
    h->cmp = cmp;
    return h;
}

void heap_print(heap *h)
{
    printf("size=%-3d cap=%-3d\n", h->size, h->cap);
    printf("%-3c", '?');
    for (int i = 1; i <= h->size; i++) 
        printf("%-3d", h->data[i]);
    printf("\n");
}

void heap_resize(heap *h, int newsize)
{
    val_type *ndata = malloc(sizeof(val_type) * newsize);
    memcpy(ndata, h->data, (h->size + 1) * sizeof(val_type));
    free(h->data);
    h->data = ndata;
    h->cap = newsize;
}

int heap_size(heap *h)
{
    if (!h) return 0;
    return h->size;
}

void swim(heap *h, int k)
{
    while (k > 1 && h->cmp(h->data[k], h->data[k / 2])) {
        swap(h->data + k / 2, h->data + k);
        k /= 2;
    }
}

void sink(heap *h, int k)
{
    while (k * 2 <= h->size) {
        int j = k * 2;
        if (j < h->size && h->cmp(h->data[j + 1], h->data[j])) j++;
        if (!h->cmp(h->data[j], h->data[k])) break;
        swap(h->data + k, h->data + j);
        k = j;
    }
}

int empty(heap *h)
{
    if (!h) return 1;
    return h->size <= 0;
}

val_type heap_peek(heap *h)
{
   if (empty(h))
      return (val_type)0;

   return h->data[1];
}

val_type heap_pop(heap *h)
{
    val_type top = h->data[1];
    swap(h->data + 1, h->data + h->size);    
    h->size--;
    sink(h, 1);
    if (h->cap > heap_min_cap && h->size + 1 == h->cap / 4)
        heap_resize(h, h->cap / 2);
#ifdef DEBUG
    heap_print(h);
#endif
    return top;
}

void heap_insert(heap *h, val_type val)
{
    if (h->size + 1 == h->cap)
        heap_resize(h, h->cap * 2);
    h->data[++h->size] = val; 
    swim(h, h->size);
#ifdef DEBUG
    heap_print(h);
#endif
}


void shuffle(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        int r = i + randWithRange(0, size - i);
        swap(arr + r, arr + i);
    }
}

int min(val_type a, val_type b)
{
    return a < b;
}

int max(val_type a, val_type b)
{
    return a > b;
}

void heap_test(void)
{
    int size = 50;
    int *arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        arr[i] = i;
    shuffle(arr, size);
    printArray(arr, size);

    heap *h = heap_create(max);
    for (int i = 0; i < size; i++) 
        heap_insert(h, arr[i]);
    while (!empty(h)) 
        printf("%-3d\n", heap_pop(h));
}

void sort_core(int *arr, int lo, int hi)
{
    if (lo >= hi)
        return;

    int i = lo, j = hi + 1;
    int pivot = arr[lo];
    while (1) {
        while (i < hi && arr[++i] < pivot);
        while (j > lo && arr[--j] > pivot);
        if (i >= j) break;
        swap(arr + i, arr + j);
    }
    swap(arr + j, arr + lo);

    sort_core(arr, lo, j - 1);
    sort_core(arr, j + 1, hi);
}

void sort(int *arr, int size)
{
    if (!arr || size <= 1)
        return;
    sort_core(arr, 0, size - 1);
}

int main(int argc, char *argv[])
{
    heap *max_heap = heap_create(max);
    heap *min_heap = heap_create(min);

    int size = 30;
    int *arr = array(size);
    shuffle(arr, size);

    for (int i = 0; i < size; i++) {

        int *copy = copyArray(arr, i + 1);
        sort(copy, i + 1);
        printArray(copy, i + 1);
        free(copy);

        if (empty(max_heap) && empty(min_heap)) {
            heap_insert(max_heap, arr[i]);
        } else {
            if (arr[i] < heap_peek(max_heap)) {
                heap_insert(max_heap, arr[i]);
                if (heap_size(max_heap) - heap_size(min_heap) > 1) 
                    heap_insert(min_heap, heap_pop(max_heap));
            } else {
                heap_insert(min_heap, arr[i]);
                if (heap_size(min_heap) - heap_size(max_heap) > 1)
                    heap_insert(max_heap, heap_pop(min_heap));
            }
        }

        int total = heap_size(min_heap) + heap_size(max_heap);
        if (total & 1) {
            if (heap_size(min_heap) > heap_size(max_heap))
                printf("median is %-3d\n", heap_peek(min_heap));
            else
                printf("median is %-3d\n", heap_peek(max_heap));
        } else {
            printf("median is %-5.2f\n", (heap_peek(max_heap) + heap_peek(min_heap)) / 2.0);
        }
    }
}
