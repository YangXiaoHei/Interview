#include "ds.h"

void is_bst_core(treenode *root, treenode **prev, int *bst)
{
    if (!root)
        return;

    if (!*bst)
        return;

    is_bst_core(root->left, prev, bst);
    if (*prev && (*prev)->val > root->val)
        *bst = 0;
    *prev = root;
    is_bst_core(root->right, prev, bst);
}

int is_bst(treenode *root)
{
    if (!root)
        return 0;
    int bst = 1;
    treenode *prev = NULL;
    is_bst_core(root, &prev, &bst);
    return bst;
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(1);
    root->left = N(2);
    root->right = N(3);
    /* treenode *root = bst_create(5); */
    tree_draw(root);
    printf("%d\n", is_bst(root));
}
