#include "ds.h"

typedef struct tsqueue {
    stack *s1;
    stack *s2;
} tsqueue;

tsqueue *tsqueue_create(void)
{
    tsqueue *t = malloc(sizeof(tsqueue));
    if (!t) exit(1);
    t->s1 = stack_create();
    t->s2 = stack_create();
    return t;
}

int tsqueue_empty(tsqueue *q)
{
    return stack_empty(q->s1) && stack_empty(q->s2);
}

void tsqueue_enqueue(tsqueue *q, int val)
{
    stack_push(q->s1, val);
}

int tsqueue_dequeue(tsqueue *q)
{
    if (tsqueue_empty(q))
        return -1;

    if (stack_empty(q->s2))
        while (!stack_empty(q->s1))
            stack_push(q->s2, stack_pop(q->s1));

    return stack_pop(q->s2);
}

int main(int argc, char *argv[])
{
    tsqueue *q = tsqueue_create();
    for (int i = 0; i < 10; i++)
        tsqueue_enqueue(q, i);

    int i = 5;
    while (i--)
        printf("%-3d", tsqueue_dequeue(q));

    for (int i = 20; i < 30; i++)
        tsqueue_enqueue(q, i);

    while (!tsqueue_empty(q))
        printf("%-3d", tsqueue_dequeue(q));
    printf("\n");
}
