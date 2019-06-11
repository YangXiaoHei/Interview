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
    n->left = n->right = NULL;
    n->val = val;
    return n;
}

void bst_mirror_core(bstnode *root)
{
    if (!root) 
        return;

    if (!root->left && !root->right)
        return;

    bstnode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;

    bst_mirror_core(root->left);
    bst_mirror_core(root->right);
}

bstnode *bst_mirror(bstnode *root)
{
    bst_mirror_core(root);
    return root; 
}

bstnode *bst_mirror_faster(bstnode *root)
{
    if (!root) return NULL;
    if (!root->left && !root->right) return root;

    bstnode *stack[1000];
    int size = 0;
    stack[size++] = root;
    while (size) {
        bstnode *n = stack[--size];

        if (n->left || n->right) {
            bstnode *tmp = n->left;
            n->left = n->right;
            n->right = tmp;
        }

        if (n->right)
            stack[size++] = n->right;

        if (n->left)
            stack[size++] = n->left;
    }
    return root;
}

void bst_insert(bstnode **root, int val)
{
    bstnode *n = bstnode_create(val);
    if (!*root) {
        *root = n;
        return;
    }

    bstnode *parent = NULL;
    bstnode *cur = *root;
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
    for (int i = 0; i < size; i++) {
        int r = randWithRange(1, 30);
        printf("bst_insert %-3d\n", r);
        bst_insert(&root, r);
    }
    return root;
}


void bst_in_traverse(bstnode *root)
{
    if (!root) return;

    bst_in_traverse(root->left);
    printf("%-3d", root->val);
    bst_in_traverse(root->right);
}

void bst_pre_traverse(bstnode *root)
{
    if (!root) return;

    printf("%-3d", root->val);
    bst_pre_traverse(root->left);
    bst_pre_traverse(root->right);
}

void bst_pre_traverse_faster(bstnode *root)
{
    bstnode *stack[10000];
    int size = 0;

    stack[size++] = root;
    while (size) {
        bstnode *n = stack[--size];
        printf("%-3d", n->val);

        if (n->right)
            stack[size++] = n->right;

        if (n->left)
            stack[size++] = n->left;
    }
}

int main(int argc, char *argv[])
{
    bstnode *root = bst_create(20);
    bst_in_traverse(root); 
    printf("\n");

    bst_mirror(root);

    bst_in_traverse(root);
    printf("\n");

    bst_mirror_faster(root);

    bst_in_traverse(root);
    printf("\n");
}
