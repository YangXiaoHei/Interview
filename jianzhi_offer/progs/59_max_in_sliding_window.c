#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

typedef struct node {
    int val;
    struct node *prev;
    struct node *next;
} node;

node *node_create(int val)
{
    node *n = malloc(sizeof(node));
    if (!n) exit(1);
    n->val = val;
    n->prev = n->next = NULL;
    return n;
}

typedef struct deque {
    node *header;
    node *tailer;
    int size;
} deque;

deque *deque_create(void)
{
    deque *d = malloc(sizeof(deque));
    if (!d) exit(1);
    d->header = d->tailer = NULL;
    d->size = 0;
    return d;
}

void push_back(deque *d, int val)
{
    node *n = node_create(val);
    if (d->tailer) {
        d->tailer->next = n;
        n->prev = d->tailer;
    }
    d->tailer = n;
    if (!d->header)
        d->header = n;
    d->size++;
}

void push_front(deque *d, int val)
{
    node *n = node_create(val);
    if (d->header) {
        d->header->prev = n;
        n->next = d->header;
    }
    d->header = n;
    if (!d->tailer)
        d->tailer = n;
    d->size++;
}

int pop_back(deque *d)
{
    if (d->size <= 0)
        return -1;

    node *n = d->tailer;
    int val = n->val;
    d->tailer = d->tailer->prev;
    free(n);
    if (--d->size == 0)
        d->header = d->tailer = NULL;
    if (d->tailer)
        d->tailer->next = NULL;
    return val;
}

int pop_front(deque *d)
{
    if (d->size <= 0)
        return -1;

    node *n = d->header;
    int val = n->val;
    d->header = d->header->next;
    free(n);
    if (--d->size == 0)
        d->header = d->tailer = NULL;
    if (d->header)
        d->header->prev = NULL;
    return val;

}

int front(deque *d)
{
    if (d->size <= 0)
        return -1;

    return d->header->val;
}

int back(deque *d)
{
    if (d->size <= 0)
        return -1;

    return d->tailer->val;
}

void deque_print_front(deque *d)
{
    if (!d)
        return;

    printf("size=%d\n", d->size);
    for (node *n = d->header; n; n = n->next)
        printf("%-3d", n->val);
    printf("\n");
}

void deque_print_back(deque *d)
{
    if (!d)
        return;

    printf("size=%d\n", d->size);
    for (node *n = d->tailer; n; n = n->prev)
        printf("%-3d", n->val);
    printf("\n");
}

int empty(deque *d)
{
    if (!d)
        return 1;

    return d->size <= 0;
}

void deque_release(deque **dd)
{
    if (!dd || !*dd)
        return;

    deque *d = *dd;
    node *h = d->header;
    while (h) {
        if (h->next)
            free((h = h->next)->prev);
        else
            free(h), h = NULL;
    }

    free(d);
    *dd = NULL;
}

void deque_test(void)
{
    deque *d = deque_create();
    for (int i = 0; i < 10; i++)
        push_back(d, i);    

    deque_print_front(d);
    deque_print_back(d);

    while (!empty(d))
        printf("%-3d", pop_back(d));
    printf("\n");

    deque_release(&d);
}

deque *max_in_sliding_window(int *window, int size, int win_size)
{
    deque *index = deque_create();
    for (int i = 0; i < win_size; i++) {
        while (!empty(index) && window[i] > window[back(index)])
            pop_back(index);

        push_back(index, i);
    }

    deque *max = deque_create();
    push_back(max, window[front(index)]); 

    for (int i = win_size; i < size; i++) {
        while (!empty(index) && window[i] > window[back(index)])
            pop_back(index);

        if (!empty(index) && (i - front(index)) >= win_size)
            pop_front(index);
       
        push_back(index, i);
        push_back(max, window[front(index)]); 
    }
    deque_release(&index);
    return max;
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *win = arrayWithRange(size, 1, 20);
    printArray(win, size);
    deque *d = max_in_sliding_window(win, size, 3);
    deque_print_front(d);
}
