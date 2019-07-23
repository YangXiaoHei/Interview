#include "ds.h"

treenode *in_order_next(treenode *root, treenode *n)
{
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

treenode *get_kth_node(treenode *root, int k)
{
    treenode *target = NULL;
    treenode *cur1 = root, *cur2 = NULL;
    while (cur1) {
        cur2 = cur1->left;
        if (cur2) {
            while (cur2->right && cur2->right != cur1)
                cur2 = cur2->right;

            if (!cur2->right) {
                cur2->right = cur1;
                cur1 = cur1->left;
                continue;
            }

            cur2->right = NULL;
        }
        if (--k <= 0 && !target)
            target = cur1;
        cur1 = cur1->right;
    }
    return target;
}

int main(int argc, char *argv[])
{
    int size = 6;
    treenode *root = bst_create(size);
    tree_draw(root);
    int k = randWithRange(0, size);
    printf("k = %d\n", k);
    treenode *knode = get_kth_node(root, k);
    treenode *nextnode = in_order_next(root, knode);
    printf("knode = %ld next = %ld\n", knode->val, nextnode->val);
}
