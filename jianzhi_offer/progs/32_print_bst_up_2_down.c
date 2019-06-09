#include <stdio.h>
#include <stdlib.h>

typedef void * val_type;

typedef struct qnode {
    val_type val;
    struct qnode *next;
} qnode;

qnode *qnode_create(val_type val)
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

typedef struct bstnode {
    int val;
    struct bstnode *left;
    struct bstnode *right;
} bstnode;

bstnode *bstnode_create(int val)
{
    bstnode *n = malloc(sizeof(bstnode));
    if (!n) exit(1);
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

void bst_level_traverse(bstnode *root)
{
    queue *q = queue_create();
    enqueue(q, root);
    while (!empty(q)) {
        bstnode *bn = dequeue(q);
        printf("%-3d", bn->val);
        if (bn->left)
            enqueue(q, bn->left);
        if (bn->right)
            enqueue(q, bn->right);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    bstnode *root = bstnode_create(10);
    root->left = bstnode_create(8);
    root->right = bstnode_create(7);
    root->left->left = bstnode_create(1);
    root->left->right = bstnode_create(12);
    root->left->left->left = NULL;
    root->left->left->right = bstnode_create(9);
    root->right->left = bstnode_create(5);
    root->right->left->left = bstnode_create(4);

    bst_level_traverse(root);
}


