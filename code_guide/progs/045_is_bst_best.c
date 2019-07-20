#include "ds.h"

int is_bst(treenode *root)
{
    if (!root)
        return 0;

    treenode *cur1 = root, *cur2 = NULL;
    treenode *prev = NULL;
    int is = 1;
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
            is = 0;
        prev = cur1;
        cur1 = cur1->right;
    }
    return is;
}

int main(int argc, char *argv[])
{
#define N(x) treenode_create(x)
    /* treenode *root = bst_create(7); */
    treenode *root = N(1);
    root->left = N(2);
    root->left->left = N(4);
    root->left->right = N(5);
    root->right = N(3);
    root->right->left = N(6);
    root->right->right = N(7);
    tree_draw(root);
    printf("is bst : %d\n", is_bst(root));
}
