#include "ds.h"

void get_kth_node(treenode *root, treenode **target, int *k)
{
    if (!root)
        return;

    if (*target)
        return;

    get_kth_node(root->left, target, k);

    if ((*k)-- == 0)
        *target = root;

    get_kth_node(root->right, target, k);
}

treenode* tree_in_traverse_next_node(treenode *root, treenode *n)
{
    if (!root || !n)
        return NULL;
    
    if (n->right) {
        n = n->right;
        while (n->left)
            n = n->left;    
        return n;
    }

    while (n->parent && n->parent->left != n)
        n = n->parent;
    return n->parent;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    treenode *n1 = NULL;

    int k = randWithRange(0, 10);
    get_kth_node(root, &n1, &k);
    printf("target = %-3ld\n", n1->val);

    treenode *next = tree_in_traverse_next_node(root, n1);
    if (next)
        printf("in traverse next is %-3ld\n", next->val);
    else
        printf("not exist!\n");
}
