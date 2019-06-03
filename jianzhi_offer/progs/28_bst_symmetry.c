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
}

