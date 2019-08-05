#include "ds.h"

int max(int a, int b) { return a > b ? a : b; }

int is_bstnode(treenode *test, treenode *head)
{
    if (!head)
        return 0;

    if (head == test)
        return 1;

    return is_bstnode(test, test->val < head->val ? head->left : head->right);
}

int max_topo(treenode *root, treenode *head)
{
    if (root && head && is_bstnode(root, head)) 
        return 1 + max_topo(root->left, head) + max_topo(root->right, head);
    return 0;
}

int find_max_topo(treenode *root)
{
    if (!root)
        return 0;

    int m = max_topo(root, root);

    m = max(m, find_max_topo(root->left));
    m = max(m, find_max_topo(root->right));
    return m;
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    treenode *root = N(6);
    root->left = N(1);
    root->left->left = N(0);
    root->left->right = N(3);
    root->right = N(12);
    root->right->left = N(10);
    root->right->left->left = N(4);
    root->right->left->left->left = N(2);
    root->right->left->left->right = N(5);
    root->right->left->right = N(14);
    root->right->left->right->left = N(11);
    root->right->left->right->right = N(15);
    root->right->right = N(13);
    root->right->right->left = N(20);
    root->right->right->right = N(16);
    tree_draw(root);
    printf("biggest bst topo size %d\n", find_max_topo(root));
}
