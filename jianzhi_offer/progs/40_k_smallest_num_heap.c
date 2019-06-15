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

void print_k_smallest(int *arr, int size, int k)
{
    if (!arr)
        return;

    if (k < 0 || size < 0)
        return;

    if (k > size)
        return;

    heap *h = heap_create(max);
    for (int i = 0; i < k; i++)
        heap_insert(h, arr[i]);
    for (int i = k; i < size; i++) {
        if (arr[i] < heap_peek(h)) {
            heap_pop(h);
            heap_insert(h, arr[i]);
        }
    }
    printf("%d smallest num is:\n", k);
    while (!empty(h)) 
        printf("%-3d", heap_pop(h));
    printf("\n");
}

int main(int argc, char *argv[])
{
    int size = 20;
    int *arr = arrayWithRange(size, 0, 100);
    printArray(arr, size);
    int k = randWithRange(0, size);
    print_k_smallest(arr, size, k);
}
