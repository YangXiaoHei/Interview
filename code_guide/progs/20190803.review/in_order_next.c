#include "ds.h"

treenode *in_order_next(treenode *root, treenode *target)
{
    if (!root || !target)
        return NULL;

    if (target->right) {
        root = target->right;
        while (root->left)
            root = root->left;
        return root;
    } 

    while (target->parent && target->parent->left != target)
        target = target->parent;

    return target->parent;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    treenode *n1 = NULL;
    tree_random_twonodes(root, &n1, NULL);
    printf("n1 = %-3ld\n", n1->val);
    treenode *next = in_order_next(root, n1);
    if (next)
        printf("next = %-3ld\n", next->val);
    else
        printf("next node not exist!\n");

}
