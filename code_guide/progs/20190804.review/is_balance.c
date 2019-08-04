#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int xabs(int a, int b) {
    int diff = a - b;
    return diff < 0 ? -diff : diff;
}

int is_balance_core(treenode *root, int *balance)
{
    if (!root)
        return 0;

    if (!*balance)
        return 0; // 这里已经不 care 最终返回什么了

    int lheight = is_balance_core(root->left, balance);
    int rheight = is_balance_core(root->right, balance);

    if (xabs(lheight, rheight) > 1) {
        *balance = 0;
        return 0;
    }
    return 1 + max(lheight, rheight);
}

int is_balance(treenode *root)
{
    int balance = 1;
    is_balance_core(root, &balance);
    return balance;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(5);
    tree_draw(root);
    printf("is balance : %d\n", is_balance(root));
}
