#include "ds.h"

int is_balance_tree(treenode *n1, int level, int *balance)
{
    if (!n1)
        return level;

    int lh = is_balance_tree(n1->left, level + 1, balance);
    if (!*balance)
        return level;

    int rh = is_balance_tree(n1->right, level + 1, balance);
    if (!*balance)
        return level;

    if (rh - lh > 1 || rh - lh < -1)
        *balance = 0;
    return rh > lh ? rh : lh;
}

int is_balance(treenode *root)
{
    if (!root)
        return 0;

    int balance = 1;
    is_balance_tree(root, 0, &balance);
    return balance;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    tree_draw(root);
    printf("is balance : %d\n", is_balance(root));
}
