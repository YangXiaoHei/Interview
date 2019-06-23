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

bstnode *bst_create(int size)
{
    bstnode *root = NULL;
    while (size--)
        bst_insert(&root, randWithRange(0, 30));
    return root;
}

void bst_test(void)
{
    int size = randWithRange(1, 30);
    bstnode *root = bst_create(size);
    bst_print(root);
}

bstnode *find_kth_node(bstnode *root, int *k)
{
    if (!root || !k || *k < 0)
        return NULL;

    bstnode *target = find_kth_node(root->left, k);

    if ((*k)-- == 0)
        target = root;

    if (!target && *k >= 0)
        target = find_kth_node(root->right, k);
    return target;
}

int main(int argc, char *argv[])
{
    bstnode *root = bst_create(10);
    bst_print(root);
    int k = randWithRange(0, 20);
    int t = k;
    bstnode *kth = find_kth_node(root, &t);
    if (kth)
        printf("%-2dth node is %-3d\n", k, kth->val);
    else
        printf("%-2d th node not exist\n", k);
}
