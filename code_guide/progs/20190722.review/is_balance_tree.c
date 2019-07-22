#include "ds.h"

int is_balance_tree(treenode *root, int level, int *balance)
{
    if (!root)
       return level; 

    int leftlv = is_balance_tree(root->left, level + 1, balance);
    int rightlv = is_balance_tree(root->right, level + 1, balance);

    if (leftlv - rightlv < -1 || leftlv - rightlv > 1) 
        *balance = 0;
    return leftlv > rightlv ? leftlv : rightlv; 
}

int is_balance(treenode *root)
{
    if (!root)
        return 0;

    int balance = 1;
    is_balance_tree(root, 1, &balance);
    return balance;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    tree_draw(root);
    printf("is balance %d\n", is_balance(root));
}
