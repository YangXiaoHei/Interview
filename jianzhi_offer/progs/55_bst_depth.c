#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

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

void bst_insert(bstnode **root, int val)
{
    bstnode *n = bstnode_create(val);
    if (!*root) {
        *root = n;
        return;
    }

    bstnode *parent = NULL, *cur = *root;
    while (cur) {
        if (val == cur->val) {
            free(n);
            return;
        }

        parent = cur;
        if (val < cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }

    if (val < parent->val)
        parent->left = n;
    else
        parent->right = n;
}

bstnode *bst_create(int size)
{
    bstnode *root = NULL;
    while (size--) 
        bst_insert(&root, randWithRange(0, 30));
    return root;
}

void bst_in_traverse(bstnode *root)
{
    if (!root)
        return;

    bst_in_traverse(root->left);
    printf("%-3d", root->val);
    bst_in_traverse(root->right);
}

void bst_print(bstnode *root)
{
    bst_in_traverse(root);
    printf("\n");
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int bst_depth(bstnode *root)
{
    if (!root)
        return 0;

    return 1 + max(bst_depth(root->left), bst_depth(root->right));
}

int main(int argc, char *argv[])
{
    bstnode *root = bst_create(10);
    bst_print(root);
    printf("%-3d\n", bst_depth(root));
}
