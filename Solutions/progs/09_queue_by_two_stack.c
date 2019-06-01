#include <stdio.h>
#include <stdlib.h>

typedef struct snode {
    int val;
    struct snode *next;
} snode;

snode *snode_create(int val)
{
    snode *n = malloc(sizeof(snode));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    return n;
}

typedef struct stack {
    int size;
    snode *top;
} stack;

stack *stack_create(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s) exit(1);
    s->size = 0;
    s->top = NULL;
    return s;
}

void push(stack *s, int val)
{
    if (!s) return;
    snode *n = snode_create(val);
    n->next = s->top;
    s->top = n;
    s->size++;
}

int stack_empty(stack *s)
{
    return s->size == 0;
}

int pop(stack *s)
{
    if (!s) return -1;
    snode *n = s->top;
    if (!n) return -1;
    int p = n->val;
    s->top = s->top->next;
    s->size--;
    free(n);
    return p;
}

typedef struct queue {
    stack *head;
    stack *tail;
} queue;

queue *queue_create(void)
{
    queue *q = malloc(sizeof(queue));
    if (!q) exit(1);
    q->head = stack_create();
    q->tail = stack_create();
    return q;
}

void enqueue(queue *q, int val)
{
    if (!q) return;
    push(q->tail, val);
}

int queue_empty(queue *q)
{
    return stack_empty(q->head) && stack_empty(q->tail);
}

int dequeue(queue *q)
{
    if (!q) return -1;

    if (queue_empty(q)) return -1;

    if (stack_empty(q->head)) 
        while (!stack_empty(q->tail))
            push(q->head, pop(q->tail));

    return pop(q->head);
}

int main(int argc, char *argv[])
{
    queue *q = queue_create();
    for (int i = 0; i < 10; i++) {
        printf("enqueue %-3d\n", i);
        enqueue(q, i);
    }
    printf("\n");

    for (int i = 0; i < 7; i++) 
        printf("dequeue %-3d\n", dequeue(q)); 
    printf("\n");

    for (int i = 10; i < 20; i++) {
        printf("enqueue %-3d\n", i);
        enqueue(q, i);
    }
    printf("\n");

    while (!queue_empty(q))
        printf("dequeue %-3d\n", dequeue(q));
}


