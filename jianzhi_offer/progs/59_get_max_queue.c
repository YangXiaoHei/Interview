#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

typedef struct node {
    long val;
    struct node *prev;
    struct node *next;
} node;

node *node_create(long val)
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

void push_back(deque *d, long val)
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

void push_front(deque *d, long val)
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
    long val = n->val;
    d->tailer = d->tailer->prev;
    free(n);
    if (--d->size == 0)
        d->header = d->tailer = NULL;
    return val;
}

int pop_front(deque *d)
{
    if (d->size <= 0)
        return -1;

    node *n = d->header;
    long val = n->val;
    d->header = d->header->next;
    free(n);
    if (--d->size == 0)
        d->header = d->tailer = NULL;
    return val;

}

long front(deque *d)
{
    if (d->size <= 0)
        return -1;

    return d->header->val;
}

long back(deque *d)
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
        printf("%-3ld", n->val);
    printf("\n");
}

void deque_print_back(deque *d)
{
    if (!d)
        return;

    printf("size=%d\n", d->size);
    for (node *n = d->tailer; n; n = n->prev)
        printf("%-3ld", n->val);
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

typedef struct queue {
    deque *max;
    deque *normal;
    long idx;
} queue;

queue *queue_create(void)
{
    queue *q = malloc(sizeof(queue));
    if (!q) exit(1);
    q->idx = 0;
    q->max = deque_create();
    q->normal = deque_create();
    return q;
}

#define INDEX(x) ((unsigned long)x >> 32)
#define VALUE(x) ((unsigned long)x & 0x00000000FFFFFFFFL)

void enqueue(queue *q, long val)
{
    if (!q)
       return;

    while (!empty(q->max) && val > VALUE(back(q->max)))
      pop_back(q->max); 

    val |= (q->idx << 32);
    q->idx++;
    push_back(q->max, val);
    push_back(q->normal, val); 
}

int dequeue(queue *q)
{
    if (!q)
        return -1;

    if (empty(q->normal))
        return -1;
    
    long val1 = front(q->max);
    long val2 = front(q->normal);
    if (INDEX(val2) == INDEX(val1)) {
        pop_front(q->max); 
    }

    pop_front(q->normal);
    return VALUE(val2);
}

int queue_max(queue *q)
{
    if (!q)
        return -1;

    if (empty(q->normal))
        return -1;

    return VALUE(front(q->max));
}

int queue_empty(queue *q)
{
    if (!q)
        return 1;
    return empty(q->normal);
}

int main(int argc, char *argv[])
{
    int size = 10;
    int *arr = arrayWithRange(size, 1, 20);
    printArray(arr, size);
    queue *q = queue_create();
    for (int i = 0; i < size; i++) {
        enqueue(q, arr[i]);
        printf("enqueue %-3d max value is %-3d\n", arr[i], queue_max(q));
    }
    printf("\n");

    while (!queue_empty(q)) {
        printf("dequeue %-3d  ", dequeue(q));
        printf("max value is %-3d\n", queue_max(q));
    }
}
