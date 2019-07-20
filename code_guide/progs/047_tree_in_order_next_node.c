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

    root = target;
    while (root->parent && root->parent->left != root)
        root = root->parent;
    return root->parent;
}

treenode *get_kth_node(treenode *root, int k)
{
    treenode *cur1 = root, *cur2 = NULL;
    treenode *target = NULL;
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
        if (k-- <= 0)
            target = !target ? cur1 : target;
        cur1 = cur1->right;
    }
    return target;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(10);
    tree_draw(root);
    int k = randWithRange(0, 10);
    printf("k = %d\n", k);
    treenode *n = get_kth_node(root, k);
    treenode *next = in_order_next(root, n);
    if (next) 
        printf("n=%ld next=%ld\n", n->val, next->val);
    else
        printf("n=%ld next not exist!\n", n->val);
}
