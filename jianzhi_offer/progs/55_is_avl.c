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
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int is_avl_core(bstnode *root, int *depth)
{
    if (!root) {
        *depth = 0;
        return 1;
    }

    int left = 0, right = 0;
    if (is_avl_core(root->left, &left) && is_avl_core(root->right, &right)) {
        int diff = left - right;
        if (diff >= -1 && diff <= 1)  {
            *depth = 1 + max(left, right);
            return 1;
        }
    }
    return 0;
}

int is_avl(bstnode *root)
{
    int depth = 0;
    return is_avl_core(root, &depth); 
}

int main(int argc, char *argv[])
{
#define N(x) bstnode_create(x)
    bstnode *root = N(5);
    root->left = N(4);
    root->left->left = N(2);
    root->right = N(3);
    root->right->right = N(1);
    root->left->right = N(7);
    root->left->left->left = N(8);
    root->left->left->left->left = N(9);

    printf("is avl : %d\n", is_avl(root));
}
