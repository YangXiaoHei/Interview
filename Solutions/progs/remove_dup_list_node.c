#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

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

void list_insert(node **head, int val)
{
    if (!head) return;
    node *n = node_create(val);
    if (!*head) {
        *head = n;
        return;
    }

    node *last = *head;
    while (last->next)
        last = last->next;

    last->next = n;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quick_core(int *a, int lo, int hi)
{
    if (lo >= hi) return;

    int pivot = a[lo];
    int i = lo, j = hi + 1;
    while (1) {
        while (i < hi && a[++i] < pivot);
        while (j > lo && a[--j] > pivot);
        if (i >= j) break;
        swap(&a[i], &a[j]);
    }
    swap(&a[lo], &a[j]);

    quick_core(a, lo, j - 1);
    quick_core(a, j + 1, hi);
}

void quick(int *a, int size)
{
    if (!a || size <= 0) return;
    quick_core(a, 0, size - 1);
}

void list_print(node *list)
{
    if (!list) return;
    while (list) {
        printf("%-3d", list->val);
        list = list->next;
    }
    printf("\n");
}

node *sorted_list_create(int size)
{
    int *a = arrayWithRange(size, 1, size / 2);
    quick(a, size);
    node *list = NULL;
    for (int i = 0; i < size; i++)
        list_insert(&list, a[i]);
    return list;
}

void remove_dup_node(node *list)
{
    if (!list) return;
    node *p = list;
    node *q = list->next;
    while (q) {
        if (p->val != q->val) {
            p = q;
            q = q->next;
        } else {
            p->next = q->next;
            free(q);
            q = p->next;
        }
    }
}

int main(int argc, char *argv[])
{
    node *list = sorted_list_create(30);
    list_print(list);
    remove_dup_node(list);
    list_print(list);
}
