#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

typedef struct bstnode {
    int val;
    struct bstnode *left;
    struct bstnode *right;
    struct bstnode *parent;
} bstnode;

bstnode *bstnode_create(int val)
{
    bstnode *n = malloc(sizeof(bstnode));
    if (!n) exit(1);
    n->val = val;
    n->left = n->parent = n->right = NULL;
    return n;
}

void bst_insert(bstnode **root, int val)
{
    bstnode *n = bstnode_create(val);
    if (!*root) {
        *root = n;
        return;
    }

    bstnode *cur = *root;
    bstnode *parent = cur;
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

    n->parent = parent;
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
        bst_insert(&root, randWithRange(1, 30));
    return root;
}

void get_kth_node(bstnode *root, int *k, bstnode **target)
{
    if (!root || !k || *k < 1)
        return;

    if (!*target)
        get_kth_node(root->left, k, target);

    if (--(*k) == 0) 
        *target = root;
    
    if (!*target)
        get_kth_node(root->right, k, target);
}

void gen_test_case(bstnode *root, int size, bstnode **left, bstnode **right)
{
    if (!root)
        return;

    int r = 0;
    while (!*left) {
        r = randWithRange(1, size);
        get_kth_node(root, &r, left);
    }
        
    while (!*right || *right == *left) {
        *right = NULL;
        r = randWithRange(1, size);
        int t = r;
        get_kth_node(root, &r, right);
    }
}

void test_gen_test_case(void)
{
    int size = 10;
    bstnode *root = bst_create(size);
    bst_print(root);

    bstnode *left = NULL, *right = NULL;
    gen_test_case(root, size, &left, &right);

    printf("test case = %3d %3d\n", left->val, right->val);
}

bstnode *find_common_parent(bstnode *left, bstnode *right)
{
    if (!left || !right)
        return NULL;

    int lsize = 0, rsize = 0;
    bstnode *l = left, *r = right;

    while (l) 
        l = l->parent, lsize++;

    while (r)
        r = r->parent, rsize++;

    printf("l = %d r = %d\n", lsize, rsize);

    l = left, r = right;

    bstnode *far = lsize > rsize ? l : r;
    bstnode *near = far == l ? r : l;
    int diff = lsize - rsize;
    diff = diff < 0 ? -diff : diff;

    while (diff--)
        far = far->parent;

    while (far && far != near)
        far = far->parent, near = near->parent;

    return far;
}

void test_case(void)
{
          /*
           *                10
           *          9            8
           *     5        4
           *  3         2
           * 
           */

    bstnode *root = bstnode_create(10);

    root->left = bstnode_create(9);
    root->left->parent = root;

    root->right = bstnode_create(8);
    root->right->parent = root;

    root->left->left = bstnode_create(5);
    root->left->left->parent = root->left;

    root->left->right = bstnode_create(4);
    root->left->right->parent = root->left;

    root->left->left->left = bstnode_create(3);
    root->left->left->left->parent = root->left->left;

    root->left->right->left = bstnode_create(2);
    root->left->right->left->parent = root->left->right;
    bst_print(root);
}

int main(int argc, char *argv[])
{

    int size = 20;
    bstnode *root = bst_create(size);
    bst_print(root);

    bstnode *left = NULL, *right = NULL;
    gen_test_case(root, size, &left, &right);
    printf("%-3d %-3d\n", left->val, right->val);

    bstnode *common_parent = find_common_parent(left, right);
    if (common_parent)
        printf("%-3d\n", common_parent->val);
}























