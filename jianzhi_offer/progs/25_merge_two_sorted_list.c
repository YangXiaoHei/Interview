#include <stdio.h>
#include "tool.h"
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

node *node_create(int val)
{
    node *n = malloc(sizeof(node));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    return n;
}

void list_insert(node **list, int val)
{
    node *n = node_create(val);
    if (!*list) {
        *list = n;
        return;
    }

    node *last = *list;
    while (last->next)
        last = last->next;
    last->next = n;
}

node *list_create(int size)
{
    node *list = NULL;
    for (int i = 0; i < size; i++)
        list_insert(&list, i);
    return list;
}

void quick_core(int *a, int lo, int hi)
{
    if (lo >= hi) return;
    
    int i = lo, j = hi + 1;
    int pivot = a[lo];
    while (1) {
        while (a[++i] < pivot);
        while (a[--j] > pivot);
        if (i >= j) break;
        swap(&a[i], &a[j]);
    }
    swap(&a[lo], &a[j]);
    quick_core(a, lo, j - 1);
    quick_core(a, j + 1, hi);
}

void quick(int *a, int size)
{
    quick_core(a, 0, size - 1);    
}

void list_print(node *list)
{
    while (list) {
        printf("%-3d", list->val);
        list = list->next;
    }
    printf("\n");
}

node *sorted_list_create(int size)
{
    int *arr = arrayWithSize(size);
    quick(arr, size);
    node *list = NULL;
    for (int i = 0; i < size; i++)
        list_insert(&list, arr[i]);
    return list;
}

node *merge_two_sorted_list(node *list1, node *list2)
{
    node *merged = NULL;
    node *merged_last = NULL;
    node *smaller = NULL;
    while (list1 || list2) {
        if (!list1) {
            smaller = list2;
            list2 = list2->next;
        } else if (!list2) {
            smaller = list1;
            list1 = list1->next;
        } else {
            smaller = list1->val < list2->val ? list1 : list2;
            if (smaller == list1)
                list1 = list1->next;
            else
                list2 = list2->next;
        }

        if (!merged) {
            merged = smaller;
            merged_last = merged;
        } else {
            merged_last->next = smaller;
            merged_last = merged_last->next;
        }
    }
    return merged;
}

int main(int argc, char *argv[])
{
    node *list1 = sorted_list_create(10);
    list_print(list1);

    node *list2 = sorted_list_create(20);
    list_print(list2);

    node *list3 = merge_two_sorted_list(list1, list2);
    list_print(list3);
}
