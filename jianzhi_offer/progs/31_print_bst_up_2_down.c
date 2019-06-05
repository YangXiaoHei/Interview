#include <stdio.h>
#include <stdlib.h>

typedef int val_type;

typedef struct qnode {
    val_type val;
    struct qnode *next;
} qnode;

qnode *qnode_create(int val)
{
    qnode *n = malloc(sizeof(qnode));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    return n;
}

typedef struct queue {
    int size;
    qnode *head;
    qnode *tail;
} queue;

queue *queue_create(void)
{
    queue *q = malloc(sizeof(queue));
    if (!q) exit(1);
    q->size = 0;
    q->head = q->tail = NULL;
    return q;
}

int empty(queue *q)
{
    return q->size <= 0;
}

void enqueue(queue *q, val_type val)
{
    if (!q) return;

    qnode *n = qnode_create(val);
    if (!q->head) {
        q->head = q->tail = n;
        q->size++;
        return;
    }

    q->tail->next = n;
    q->tail = n;
    q->size++;
}

val_type dequeue(queue* q)
{
    if (!q) return (val_type)-1;

    if (q->size <= 0)
        return (val_type)-1;

    val_type val = q->head->val;
    qnode *del = q->head;
    q->head = q->head->next;

    if (!q->head)
        q->tail = NULL;
    free(del);
    q->size--;
    return val;
}

typedef struct 

int main(int argc, char *argv[])
{
    queue *q = queue_create();
    for (int i = 0; i < 10; i++)
        enqueue(q, i);
    while (!empty(q))
        printf("%-3d", dequeue(q));
    printf("\n");
}


