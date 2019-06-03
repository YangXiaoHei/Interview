#include <stdio.h>
#include <stdlib.h>

typedef struct bstnode {
    int val;
    struct bstnode *left;
    struct bstnode *right;
} bstnode;

bstnode *bstnode_create(int val)
{
    bstnode *n = malloc(sizeof(bstnode));
    if (!n) exit(1);
    n->left = n->right = NULL;
    n->val = val;
    return n;
}

int bst_symmetry_core(bstnode *root1, bstnode *root2)
{
    if (!root1 && !root2)
        return 1;

    if (!root1 || !root2)
        return 0;

    if (root1->val != root2->val)
        return 0;

    if (root1 == root2)
        return bst_symmetry_core(root1->left, root2->right);

    return bst_symmetry_core(root1->left, root2->right) && bst_symmetry_core(root1->right, root2->left);
}

int bst_symmetry(bstnode *root)
{
    return bst_symmetry_core(root, root);
}

typedef struct qnode {
    void * val;
    struct qnode *next;
} qnode;

typedef struct queue {
    int size;
    qnode *head;
    qnode *tail;
} queue;

qnode *qnode_create(void *val)
{
    qnode *n = malloc(sizeof(qnode));
    if (!n) exit(1);
    n->val = val;
    n->next = NULL;
    return n;
}

queue *queue_create(void)
{
    queue *q = malloc(sizeof(queue));
    if (!q) exit(1);
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

void enqueue(queue *q, void* val)
{
    if (!q) return;
    qnode *n = qnode_create(val);
    if (!q->tail) {
        q->head = n;
        q->tail = n;
    } else {
       q->tail->next = n; 
       q->tail = q->tail->next;
    }
    q->size++;
}

void* dequeue(queue *q)
{
    if (!q) return NULL;
    if (!q->head) return NULL;
    void * val = q->head->val;
    qnode *n = q->head;
    q->head = q->head->next;
    if (!q->head) 
        q->tail = NULL;
    free(n);
    q->size--;
    return val; 
}

int empty(queue *q)
{
    return q->size <= 0;
}

int bst_symmetry_bfs(bstnode *root)
{
    if (!root) return 1;

    if (!root->left && !root->right) 
        return 1;

    if (!root->left || !root->right) 
        return 0;

    queue *q = queue_create();
    enqueue(q, root->left);
    enqueue(q, root->right);
    while (!empty(q)) {
        bstnode *b1 = dequeue(q);
        bstnode *b2 = dequeue(q);

        if (!b1 && !b2)
            continue;

        if (!b1 || !b2)
            return 0;

        if (b1->val != b2->val)
            return 0;

        enqueue(q, b1->left); enqueue(q, b2->right);
        enqueue(q, b1->right); enqueue(q, b2->left);
    }
    return 1;
}

void queue_test(void)
{
    queue *q = queue_create();
    for (int i = 0; i < 100; i++)
        enqueue(q, i);
    while (!empty(q))
        printf("%-3d", dequeue(q));
    printf("\n");
}

int main(int argc, char *argv[])
{
    bstnode *root = bstnode_create(10);
    root->left = bstnode_create(9);
    root->right = bstnode_create(9);
    root->left->left = bstnode_create(8);
    root->right->right = bstnode_create(8);
    root->left->right = bstnode_create(7);
    root->right->left = bstnode_create(7);

    printf("%d\n", bst_symmetry(root));

    queue_test();

    printf("%d\n", bst_symmetry_bfs(root));
}

