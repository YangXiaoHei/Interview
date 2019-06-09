#include <stdio.h>
#include <stdlib.h>

typedef void * val_type;

typedef struct snode {
    val_type val;
    struct snode *next;
} snode;

snode *snode_create(val_type val)
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

void push(stack *s, val_type val)
{
    if (!s) return;
    snode *n = snode_create(val);
    n->next = s->top;
    s->top = n;
    s->size++;
}

int empty(stack *s)
{
    return s->size <= 0;
}

val_type pop(stack* s)
{
    if (!s || empty(s)) 
        return (val_type)0;

    val_type val = s->top->val;
    snode *tofree = s->top;
    s->top = s->top->next;
    s->size--;
    free(tofree); 
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

void bst_layer_level_snake_traverse(bstnode *root)
{
    stack *s_even = stack_create();
    stack *s_odd = stack_create();
    int n = 0;
    int cur_level_cnt = 1, next_level_cnt = 0;
    push(s_even, root);
    bstnode *bn = NULL;
    while (!empty(s_even) || !empty(s_odd)) {

        /* 偶数 */
        if ((n & 1) == 0) {
            bn = pop(s_even);
            
            if (bn->left) {
                push(s_odd, bn->left);
                next_level_cnt++;
            } 
            if (bn->right) {
                push(s_odd, bn->right);
                next_level_cnt++;
            }
        /* 奇数 */
        } else {
            bn = pop(s_odd);

            if (bn->right) {
                push(s_even, bn->right);
                next_level_cnt++;
            }

            if (bn->left) {
                push(s_even, bn->left);
                next_level_cnt++;
            } 
        }

        printf("%-3d", bn->val);
        cur_level_cnt--;
        if (cur_level_cnt == 0) {
            printf("\n");
            cur_level_cnt = next_level_cnt;
            next_level_cnt = 0;
            n++;
        }
    }
}

int main(int argc, char *argv[])
{
    bstnode *root = bstnode_create(10);
    root->left = bstnode_create(8);
    root->right = bstnode_create(7);
    root->right->right = bstnode_create(99);
    root->right->right->right = bstnode_create(55);
    root->left->left = bstnode_create(1);
    root->left->right = bstnode_create(12);
    root->left->left->right = bstnode_create(9);
    root->right->left = bstnode_create(5);
    root->right->left->left = bstnode_create(4);

    bst_layer_level_snake_traverse(root);
}
