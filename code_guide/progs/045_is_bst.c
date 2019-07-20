#include "ds.h"

void is_bst_core(treenode *root, treenode **prev, int *is)
{
    if (!root)
        return;

    is_bst_core(root->left, prev, is);

    if (*prev && (*prev)->val > root->val)
       *is = 0;

    if (!*prev)
        *prev = root;

    is_bst_core(root->right, prev, is);
}

int is_bst(treenode *root)
{
    int is = 1;
    treenode *prev = NULL;
    is_bst_core(root, &prev, &is);
    return is;
}

int main(int argc, char *argv[])
{
    /* treenode *root = bst_create(7); */
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    root->left->left = N(4);
    root->left->right = N(5);
    root->right->left = N(6);
    root->right->right = N(7);
    tree_draw(root);
    printf("is bst : %d\n", is_bst(root));
}
