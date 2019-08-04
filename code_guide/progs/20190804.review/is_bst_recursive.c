#include "ds.h"

void is_bst_core(treenode *root, treenode **prev, int *isbst)
{
    if (!root)
        return;

    if (!*isbst)
        return;

    is_bst_core(root->left, prev, isbst);
    if (*prev && (*prev)->val > root->val) 
        *isbst = 0;
    *prev = root;
    is_bst_core(root->right, prev, isbst);
}

int is_bst(treenode *root)
{
    treenode *prev = NULL;
    int isbst = 1;
    is_bst_core(root, &prev, &isbst);
    return isbst;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    printf("%d\n", is_bst(root));
}
