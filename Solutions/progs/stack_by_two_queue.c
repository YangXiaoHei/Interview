#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int size;
    int head;
    int tail;
    int cap;
    int *data;
} queue;

queue *queue_create(void)
{
    queue *q = malloc(sizeof(queue));
    if (!q) exit(1);
    q->size = 0;
    q->cap = 2;
    q->head = q->tail = 0;
    q->data = calloc(2, sizeof(int));
    if (!q->data) exit(1);
    return q;
}

void _queue_resize(queue *q, int nsize)
{
    int *data = calloc(nsize, sizeof(int));
    if (!data) exit(1);
    for (int i = q->head, j = 0; j < q->size; j++, i = (i + 1) % q->cap) 
        data[j] = q->data[i];
    free(q->data);
    q->head = 0;
    q->tail = q->size;
    q->cap = nsize;
    q->data = data;
}

int queue_full(queue *q)
{
    return q->size >= q->cap;
}

int queue_empty(queue *q)
{
    return q->size <= 0;
}

void enqueue(queue *q, int val)
{
    if (!q) return;

    if (queue_full(q))
        _queue_resize(q, q->size << 1);

    q->data[q->tail] = val;
    q->tail = (q->tail + 1) % q->cap;
    q->size++;
}

int dequeue(queue *q)
{
    if (!q) return -1;

    if (queue_empty(q))
        return -1;

    int val = q->data[q->head];
    q->head = (q->head + 1) % q->cap;
    q->size--;

    if (q->cap > 2 && q->size == q->cap >> 2)
        _queue_resize(q, q->cap >> 1);

    return val;
}

void queue_print(queue *q)
{
    if (!q) return;

    if (queue_empty(q))
        printf("empty queue\n");

    printf("queue size=%d cap=%d head=%d tail=%d\n", q->size, q->cap, q->head, q->tail);
    for (int i = q->head, j = 0; j < q->size; j++, i = (i + 1) % q->cap)
        printf("%-3d", q->data[i]);
    printf("\n");
}

void queue_test(void)
{
    queue *q = queue_create();

    for (int i = 0; i < 100; i++)  {
        enqueue(q, i);
        queue_print(q);
    }

    while (!queue_empty(q)) {
        printf("dequeue %-3d\n", dequeue(q));
        queue_print(q);
    }
}

int queue_size(queue *q)
{
    if (!q) return 0;
    return q->size;
}

typedef struct stack {
    queue *q1;
    queue *q2;
} stack;

stack *stack_create(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s) exit(1);
    s->q1 = queue_create();
    s->q2 = queue_create();
    return s;
}

int stack_empty(stack *s)
{
    if (!s) return 1;
    return queue_empty(s->q1) && queue_empty(s->q2);
}

void push(stack *s, int val)
{
    if (!queue_empty(s->q1))
        enqueue(s->q1, val);
    else
        enqueue(s->q2, val);
}

int pop(stack *s)
{
    if (stack_empty(s)) return -1;

    if (!queue_empty(s->q1) && !queue_empty(s->q2))
        exit(1);

    queue *empty = queue_empty(s->q1) ? s->q1 : s->q2;
    queue *have = empty == s->q1 ? s->q2 : s->q1;

    while (queue_size(have) > 1)
        enqueue(empty, dequeue(have));

    return dequeue(have);
}

int main(int argc, char *argv[])
{
    stack *s = stack_create();

    for (int i = 0; i < 10; i++) {
        printf("push %-3d\n", i);
        push(s, i);
    }

    printf("\n");

    for (int i = 0; i < 7; i++)
        printf("pop %-3d\n", pop(s));

    printf("\n");

    for (int i = 10; i < 20; i++) {
        printf("push %-3d\n", i);
        push(s, i);
    }

    printf("\n");

    while (!stack_empty(s))
        printf("%-3d\n", pop(s));

}
