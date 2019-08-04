#include "ds.h"

int is_bst(treenode *root)
{
    if (!root)
        return 0;

    int isbst = 1;
    treenode *cur1 = root, *cur2 = NULL;
    treenode *prev = NULL;
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
        if (prev && prev->val > root->val) 
            isbst = 0;
        cur1 = cur1->right;
    }
    return isbst;
}

int main(int argc, char *argv[])
{
    treenode *root = bst_create(8);
    tree_draw(root);
    printf("%d\n", is_bst(root));
}
