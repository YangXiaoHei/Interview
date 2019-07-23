#include "ds.h"

int is_bst(treenode *root)
{
    treenode *prev = NULL;
    treenode *cur1 = root, *cur2 = NULL;
    int is_bst = 1;
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
        if (prev && prev->val > cur1->val)
            is_bst = 0;
        prev = cur1;
        cur1 = cur1->right;
    }
    return is_bst;
}

int main(int argc, char *argv[])
{
    int size = 7;
    treenode *n = bst_create(size);
    tree_draw(n);
    printf("is bst : %d\n", is_bst(n));
}
