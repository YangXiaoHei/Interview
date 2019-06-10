#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

typedef struct stack {
    int size;
    int cap;
    void **data;
} stack;

stack *stack_create(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s) exit(1);
    s->size = 0;
    s->cap = 1000;
    s->data = malloc(sizeof(void *) * s->cap);
    if (!s->data) exit(1);
    return s;
}

void push(stack *s, void *val)
{
    if (!s) return;
    assert(s->size < s->cap);
    s->data[s->size++] = val; 
}

void* pop(stack *s)
{
    if (s->size <= 0)
        return NULL;
    return s->data[--s->size];
}

void stack_print(stack *s, void(*pr_stk)(void *elem))
{
    for (int i = 0; i < s->size; i++)
        pr_stk(s->data[i]);
    printf("\n");
}

void stack_print_core(void *elem)
{
    bstnode *bn = elem;
    printf("%-3d", bn->val);
}

void path_of_sum_core(bstnode *root, int sum, stack *s, int acc_sum)
{
    if (!root) 
        return;

    push(s, root);
    acc_sum += root->val;

    if (!root->left && !root->right) 
        if (acc_sum == sum) 
            stack_print(s, stack_print_core);

    path_of_sum_core(root->left, sum, s, acc_sum);
    path_of_sum_core(root->right, sum, s, acc_sum);

    pop(s);
}

void path_of_sum(bstnode *root, int sum)
{
    if (!root) return;
    stack *s = stack_create();
    path_of_sum_core(root, sum, s, 0);    
}

int main(int argc, char *argv[])
{
    bstnode *root = bstnode_create(10);
    root->left = bstnode_create(5);
    root->left->left = bstnode_create(4);
    root->left->right = bstnode_create(7);
    root->right = bstnode_create(12);

    path_of_sum(root, 22);

    bstnode *root1 = bstnode_create(10);
    root1->left = bstnode_create(7);
    root1->right = bstnode_create(5);
    root1->left->left = bstnode_create(8);
    root1->left->right = bstnode_create(9);
    root1->left->left->right = bstnode_create(0);
    root1->left->left->right->left = bstnode_create(1);
    root1->right->left = bstnode_create(4);
    root1->right->left->right = bstnode_create(7);
    root1->right->right = bstnode_create(6);

    path_of_sum(root1, 26);
}
